#include "Bezier.h"

Bezier::Bezier()
	:mS(0, 0)
	, mE(0, 0)
	, mA(0, 0)
{
}

Bezier::Bezier(Vec2 startPos, Vec2 endPos, Vec2 anchorPos)
	:mS{ startPos }
	, mE{ endPos }
	, mA{ anchorPos }
{
}

Bezier::Bezier(Vec2 startPos, Vec2 endPos, float height)
	: mS{ startPos }
	, mE{ endPos }
{
	mA = pointStartToEnd(0.5f);
	mA.sety(mA.gety() + height);
}

Vec2 Bezier::getEndPos() const
{
	return mE;
}
Vec2 Bezier::getStartPos() const
{
	return mS;
}

Vec2 Bezier::pointStartToEnd(float t)
{
	Vec2 pt = mS.lerpTo(mE, t);
	return pt;
}

Vec2 Bezier::pointStartToAnchor(float t)
{
	Vec2 pt = mS.lerpTo(mA, t);
	return pt;
}

Vec2 Bezier::pointAnchorToEnd(float t)
{
	Vec2 pt = mA.lerpTo(mE, t);
	return pt;
}

Vec2 Bezier::resultPoint(float t)
{
	Vec2 pointA = pointStartToAnchor(t);
	Vec2 pointB = pointAnchorToEnd(t);
	Vec2 pt = pointA.lerpTo(pointB, t);
	return pt;
}

void Bezier::DebugDraw(sf::RenderWindow& window, float t)
{
	sf::CircleShape start(5);
	sf::CircleShape end(5);
	sf::CircleShape anchor(5);
	sf::CircleShape starttoanchor(5);
	sf::CircleShape endtoanchor(5);
	sf::CircleShape result(5);

	start.setOrigin(2.5, 2.5);
	end.setOrigin(2.5, 2.5);
	anchor.setOrigin(2.5, 2.5);
	starttoanchor.setOrigin(2.5, 2.5);
	endtoanchor.setOrigin(2.5, 2.5);
	result.setOrigin(2.5, 2.5);

	start.setFillColor(sf::Color::Red);
	end.setFillColor(sf::Color::Red);
	anchor.setFillColor(sf::Color::Cyan);
	starttoanchor.setFillColor(sf::Color::Green);
	endtoanchor.setFillColor(sf::Color::Green);
	result.setFillColor(sf::Color::Blue);

	start.setPosition(mS.getAsSFVec2F());
	end.setPosition(mE.getAsSFVec2F());
	anchor.setPosition(mA.getAsSFVec2F());
	starttoanchor.setPosition(pointStartToAnchor(t).getAsSFVec2F());
	endtoanchor.setPosition(pointAnchorToEnd(t).getAsSFVec2F());
	result.setPosition(resultPoint(t).getAsSFVec2F());

	window.draw(start);
	window.draw(end);
	window.draw(anchor);
	window.draw(starttoanchor);
	window.draw(endtoanchor);
	window.draw(result);
}
#pragma once
#include <Vec2.h>
#include <SFML/Graphics.hpp>

class Bezier
{
public:
	Bezier();
	Bezier(Vec2 startPos, Vec2 endPos, Vec2 anchorPos);
	Bezier(Vec2 startPos, Vec2 endPos, float height);
	
	Vec2 resultPoint(float t);
	void DebugDraw(sf::RenderWindow& window, float t);

	Vec2 getEndPos();
	Vec2 getStartPos();

private:
	Vec2 mS;	// Start point
	Vec2 mE;	// End Point
	Vec2 mA;	// Anchor Point

	Vec2 pointStartToEnd(float t);
	Vec2 pointStartToAnchor(float t);
	Vec2 pointAnchorToEnd(float t);
};
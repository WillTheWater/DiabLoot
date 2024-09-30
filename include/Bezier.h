#pragma once
#include <Vec2.h>
#include <SFML/Graphics.hpp>

class Bezier
{
public:
	Bezier();
	Bezier(Vec2 startPos, Vec2 endPos, Vec2 anchorPos);
	Bezier(Vec2 startPos, Vec2 endPos, float height);

	Vec2 ResultPoint(float t);
	void DebugDraw(sf::RenderWindow& window, float t);

	Vec2 GetEndPos() const;
	Vec2 GetStartPos() const;

private:
	Vec2 mS;	// Start point
	Vec2 mE;	// End Point
	Vec2 mA;	// Anchor Point

	Vec2 PointStartToEnd(float t);
	Vec2 PointStartToAnchor(float t);
	Vec2 PointAnchorToEnd(float t);
};
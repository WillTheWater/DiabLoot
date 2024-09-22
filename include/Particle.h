#include "Bezier.h"
#include "PlayState.h"
#include "Vec2.h"
#include "sfml/Graphics.hpp"
#include <functional>

class Particle
{
public:
	// Constructors
	Particle() = delete;
	// anchorHeight sets how hight the partile travels, stepIncrement is used to go between 0 to 1 each step for the animation, 
	// callback is the function called when the particle lands
	Particle(int id, sf::Vector2f pathStart, sf::Vector2f pathEnd, float anchorHeight, float stepIncrement, std::function<void(sf::Vector2f, Particle&)> callback);

	void						stepParticle();
	int							getId();
	sf::Vector2f				getCurrentPos();




private:
	int mId;
	Bezier mPath;
	Vec2 mCurrentPos;
	Vec2 mPreviousPos;
	float mIncrement;
	float mStepProgress;
	std::function<void(sf::Vector2f, Particle&)> mCallback;
	bool mFinished;
	
};
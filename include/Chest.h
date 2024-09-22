#include "SFML/Graphics.hpp"
#include "InputManager.h"
#include "Vec2.h"
#include "functional"

class Chest : public InputObserver
{
public:
	Chest(sf::Vector2f position, bool mirrored, std::function<void(sf::Vector2f)> callback);

	// Observer overrides
	void								OnMouseMove(int x, int y) override;
	void								OnKeyPress(sf::Keyboard::Key key) override;
	void								OnKeyRelease(sf::Keyboard::Key key) override;
	void								OnMouseClick(sf::Mouse::Button button) override;
	void								OnMouseRelease(sf::Mouse::Button button) override;
	void								OpenChest();
	sf::Vector2f						GetPosition();
	bool								IsOpened();
	bool								IsMirrored();

private:
	bool mMirrored;
	bool mOpened;
	sf::Vector2f mPos;
	sf::RectangleShape mRect;
	bool mMouseOver;
	std::function<void(sf::Vector2f)> mCallback;
};

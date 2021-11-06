#ifndef BUTTONS_HPP_
#define BUTTONS_HPP_

#include <SFML/Graphics.hpp>

class Buttons
{
private:
	sf::Texture textureFrameButton;
	sf::Sprite spriteFrameButton;
	sf::Text playButton;
	sf::Text exitButton;
	sf::Font font;

	const int CHARACTER_SIZE=72;
	const int BUTTON_FRAME_WIDTH = 506;
	const int BUTTON_FRAME_HEIGHT = 96;
	const int X_AXIS_TEXT_OF_BUTTON_ORIGIN = 450;
	const int Y_AXIS_TEXT_OF_PLAY_BUTTON_ORIGIN = 200;
	const int Y_AXIS_TEXT_OF_EXIT_BUTTON_ORIGIN = 500;

	void setBasicButtonOptions(sf::Text * button, std::string buttonName, int positionX, int positionY);

public:
	Buttons();
	~Buttons();

	sf::Sprite getSpriteFrameButton();
	int getButtonFrameWidth();
	int getButtonFrameHeight();

	sf::Text getPlayButton();
	sf::Text getExitButton();

	int getX_AxisTextOfButtonOrigin();
	int getY_AxisTextOfPlayButtonOrigin();
	int getY_AxisTextOfExitButtonOrigin();

	void drawButton(sf::RenderWindow * renderedWindow, sf::Text usedPlayButton,
			int X_AXIS_FRAME_OF_BUTTONS_ORIGIN, int Y_AXIS_FRAME_OF_PLAY_BUTTON_ORIGIN);

	void checkIfButtonIsHighlighted(sf::Text * usedText, bool * confirmationOfHighlight, sf::Event event,
			int X_AXIS_FRAME_OF_BUTTON_ORIGIN, int Y_AXIS_FRAME_OF_BUTTON_ORIGIN);

	void checkIfButtonWasPressed(bool * buttonPressed, bool buttonHighlighted);

};

#endif

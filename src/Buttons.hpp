#ifndef BUTTONS_HPP_
#define BUTTONS_HPP_

#include <SFML/Graphics.hpp>
#include "Settings.hpp"

class Buttons
{
private:
	sf::Texture textureFrameButton;
	sf::Texture textureThinFrameButton;
	sf::Sprite spriteFrameButton;
	sf::Sprite spriteThinFrameButton;
	sf::Font font;
	sf::Text playButton;
	sf::Text settingsButton;
	sf::Text scoreboardButton;
	sf::Text exitButton;
	sf::Text backButton;
	sf::Text keyboardThinButton;
	sf::Text joystickThinButton;
	sf::Text mouseThinButton;
	sf::Text resumeButton;

	const int BUTTON_FRAME_WIDTH = 506;
	const int BUTTON_THIN_FRAME_WIDTH = 168;
	const int BUTTON_FRAME_HEIGHT = 96;

	const int CHARACTER_SIZE=72;
	const int CHARACTER_THIN_SIZE=30;
	const int X_AXIS_TEXT_OF_BUTTON_ORIGIN = 450;
	const int Y_AXIS_TEXT_OF_PLAY_BUTTON_ORIGIN = 200;
	const int Y_AXIS_TEXT_OF_SETTINGS_BUTTON_ORIGIN = 300;
	const int Y_AXIS_TEXT_OF_SCOREBOARD_BUTTON_ORIGIN = 400;
	const int Y_AXIS_TEXT_OF_EXIT_BUTTON_ORIGIN = 500;
	const int Y_AXIS_TEXT_OF_BACK_BUTTON_ORIGIN = 500;
	const int Y_AXIS_TEXT_OF_RESUME_BUTTON_ORIGIN = 200;


	const int X_AXIS_TEXT_OF_THIN_KEYBOARD_BUTTON_ORIGIN = 460;
	const int X_AXIS_TEXT_OF_THIN_JOYSTICK_BUTTON_ORIGIN = 630;
	const int X_AXIS_TEXT_OF_THIN_MOUSE_BUTTON_ORIGIN = 800;
	const int Y_AXIS_TEXT_OF_THIN_BUTTONS_ORIGIN = 230;

	void setBasicButtonOptions(sf::Text * button, std::string buttonName, int charSize, int positionX, int positionY);

public:
	Buttons();
	~Buttons();

	sf::Text getPlayButton();
	sf::Text getSettingsButton();
	sf::Text getScoreboardButton();
	sf::Text getExitButton();
	sf::Text getBackButton();
	sf::Text getResumeButton();
	sf::Text getKeyboardThinButton();
	sf::Text getJoystickThinButton();
	sf::Text getMouseThinButton();

	int getButtonFrameWidth();
	int getButtonFrameHeight();

	int getX_AxisTextOfButtonOrigin();
	int getY_AxisTextOfPlayButtonOrigin();
	int getY_AxisTextOfSettingsButtonOrigin();
	int getY_AxisTextOfScoreboardButtonOrigin();
	int getY_AxisTextOfExitButtonOrigin();
	int getY_AxisTextOfBackButtonOrigin();
	int getY_AxisTextOfResumeButtonOrigin();

	int getX_AxisTextOfThinKeyboardButtonOrigin();
	int getX_AxisTextOfThinJoystickButtonOrigin();
	int getX_AxisTextOfThinMouseButtonOrigin();
	int getY_AxisTextOfThinButtonsOrigin();

	void drawButton(sf::RenderWindow * renderedWindow, sf::Text usedPlayButton,
			int X_AXIS_FRAME_OF_BUTTON_ORIGIN, int Y_AXIS_FRAME_OF_BUTTON_ORIGIN);
	void drawThinButton(sf::RenderWindow * renderedWindow, sf::Text usedPlayButton,
			int X_AXIS_FRAME_OF_BUTTON_ORIGIN, int Y_AXIS_FRAME_OF_BUTTON_ORIGIN);
	void checkIfButtonIsHighlighted(sf::Text * usedText, bool * confirmationOfHighlight, sf::Event event,
			int X_AXIS_FRAME_OF_BUTTON_ORIGIN, int Y_AXIS_FRAME_OF_BUTTON_ORIGIN);
	void checkIfButtonWasPressed(bool * buttonPressed, bool buttonHighlighted);
	void checkIfThinButtonIsHighlighted(sf::Text * usedText, bool * confirmationOfHighlight, sf::Event event,
			int X_AXIS_FRAME_OF_BUTTON_ORIGIN, int Y_AXIS_FRAME_OF_BUTTON_ORIGIN);

	void setProperControlColor(sf::Text * usedKeyboardThinButton, sf::Text * usedMouseThinButton,
			sf::Text * usedJoystickThinButton, Settings::ControlType controlType);
};

#endif

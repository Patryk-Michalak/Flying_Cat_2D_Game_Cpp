#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

class Settings {
private:
	sf::Texture textureUnderVolumeSlider;
	sf::Texture textureVolumeSlider;
	sf::Sprite spriteUnderVolumeSlider;
	sf::Sprite spriteVolumeSlider;

	sf::Font font;
	sf::Text gameControlsText;
	const int CHARACTER_SIZE=30;
	const int GAME_CONTROLS_TEXT_POSITION_X=195;
	const int GAME_CONTROLS_TEXT_POSITION_Y=230;

	sf::Text volumeText;
	const int VOLUME_TEXT_POSITION_X=195;
	const int VOLUME_TEXT_POSITION_Y=330;

	const int UNDER_VOLUME_SLIDER_WIDTH = 506;
	const int UNDER_VOLUME_SLIDER_HEIGHT = 8;

	const int X_AXIS_UNDER_VOLUME_SLIDER = 450;
	const int Y_AXIS_UNDER_VOLUME_SLIDER = 350;

	const int VOLUME_SLIDER_WIDTH = 20;
	const int VOLUME_SLIDER_HEIGHT = 30;

	int xAxisVolumeSlider = 550;
	int Y_AXIS_VOLUME_SLIDER = 339;

	const int MIN_X_AXIS_VOLUME_SLIDER = 450;
	const int MAX_X_AXIS_VOLUME_SLIDER = MIN_X_AXIS_VOLUME_SLIDER + UNDER_VOLUME_SLIDER_WIDTH - VOLUME_SLIDER_WIDTH;

	int soundVolume = 100/486*(xAxisVolumeSlider)-92.592;


	void setBasicButtonOptions(sf::Text * button, std::string buttonName, int charSize, int positionX, int positionY);

public:
	Settings();
	~Settings();

	enum ControlType
	{
		KEYBOARD,
		MOUSE,
		JOYSTICK,
	};

	void showSettingTexts(sf::RenderWindow * renderedWindow);
	void drawUnderVolumeSlider(sf::RenderWindow * renderedWindow);
	void drawVolumeSlider(sf::RenderWindow * renderedWindow);

	void checkIfVolumeButtonIsHighlighted(bool * volumeHighlighted, sf::Event event);
	void checkIfVolumeButtonWasPressed(bool * volumePressed, bool volumeHighlighted);
	void moveVolumeSlider(sf::Event event);
	int getVolumeValue();
};

#endif

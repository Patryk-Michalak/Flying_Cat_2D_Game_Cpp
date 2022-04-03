#include "Settings.hpp"

Settings::Settings()
{
	textureUnderVolumeSlider.loadFromFile("src/Graphics/Objects/UnderVolumeSlider.png");
	textureVolumeSlider.loadFromFile("src/Graphics/Objects/VolumeSlider.png");
	spriteUnderVolumeSlider.setTexture(textureUnderVolumeSlider);
	spriteVolumeSlider.setTexture(textureVolumeSlider);
	font.loadFromFile("src/Fonts/Montserrat-Regular.ttf");
	setBasicButtonOptions(&gameControlsText, "Game Controller", CHARACTER_SIZE, GAME_CONTROLS_TEXT_POSITION_X, GAME_CONTROLS_TEXT_POSITION_Y);
	setBasicButtonOptions(&volumeText, "Volume: ", CHARACTER_SIZE, VOLUME_TEXT_POSITION_X, VOLUME_TEXT_POSITION_Y);
}

Settings::~Settings()
{
}

void Settings::setBasicButtonOptions(sf::Text * button, std::string buttonName, int charSize, int positionX, int positionY)
{
	button->setFont(font);
	button->setCharacterSize(charSize);
	button->setPosition(positionX, positionY);
	button->setString(buttonName);
	button->setFillColor(sf::Color::Black);
}

void Settings::showSettingTexts(sf::RenderWindow * renderedWindow)
{
	renderedWindow->draw(gameControlsText);
	std::string soundVolumeString = "Volume: ";
	std::stringstream  stringStreamOfActualSoundVolume;
	soundVolume = (100.0/486.0)*((float)xAxisVolumeSlider)-92.592;
	stringStreamOfActualSoundVolume << soundVolume;
	soundVolumeString = soundVolumeString + stringStreamOfActualSoundVolume.str();
	volumeText.setString(soundVolumeString);
	renderedWindow->draw(volumeText);
}

void Settings::drawUnderVolumeSlider(sf::RenderWindow * renderedWindow)
{
	spriteUnderVolumeSlider.setPosition(X_AXIS_UNDER_VOLUME_SLIDER, Y_AXIS_UNDER_VOLUME_SLIDER);
	renderedWindow->draw(spriteUnderVolumeSlider);
}

void Settings::drawVolumeSlider(sf::RenderWindow * renderedWindow)
{
	spriteVolumeSlider.setPosition(xAxisVolumeSlider, Y_AXIS_VOLUME_SLIDER);
	renderedWindow->draw(spriteVolumeSlider);
}

void Settings::checkIfVolumeButtonIsHighlighted(bool * volumeHighlighted, sf::Event event)
{
	if(event.mouseMove.x>xAxisVolumeSlider
		&& event.mouseMove.x<xAxisVolumeSlider+VOLUME_SLIDER_WIDTH
			&& event.mouseMove.y>Y_AXIS_VOLUME_SLIDER
			&& event.mouseMove.y<Y_AXIS_VOLUME_SLIDER+VOLUME_SLIDER_HEIGHT)
	{
		*volumeHighlighted=true;
	}
	else
	{
		*volumeHighlighted=false;
	}
}

void Settings::checkIfVolumeButtonWasPressed(bool * volumePressed, bool volumeHighlighted)
{
	if(volumeHighlighted)
	{
		*volumePressed=true;
	}
	else
	{
		*volumePressed=false;
	}
}

void Settings::moveVolumeSlider(sf::Event event)
{

	if(event.mouseMove.x<MIN_X_AXIS_VOLUME_SLIDER)
	{
		xAxisVolumeSlider=MIN_X_AXIS_VOLUME_SLIDER;
	}
	else if(event.mouseMove.x>MAX_X_AXIS_VOLUME_SLIDER)
	{
		xAxisVolumeSlider=MAX_X_AXIS_VOLUME_SLIDER;
	}
	else
	{
		xAxisVolumeSlider=event.mouseMove.x;
	}
	soundVolume = (100.0/486.0)*((float)xAxisVolumeSlider)-92.592;
}

int Settings::getVolumeValue()
{
	return soundVolume;
}

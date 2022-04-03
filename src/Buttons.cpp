#include "Buttons.hpp"

Buttons::Buttons()
{
	textureFrameButton.loadFromFile("src/Graphics/Objects/UnderButtons.png");
	textureThinFrameButton.loadFromFile("src/Graphics/Objects/UnderThinButtons.png");
	spriteFrameButton.setTexture(textureFrameButton);
	spriteThinFrameButton.setTexture(textureThinFrameButton);
	font.loadFromFile("src/Fonts/Montserrat-Regular.ttf");
	setBasicButtonOptions(&playButton, "Play", CHARACTER_SIZE, X_AXIS_TEXT_OF_BUTTON_ORIGIN, Y_AXIS_TEXT_OF_PLAY_BUTTON_ORIGIN);
	setBasicButtonOptions(&settingsButton, "Settings", CHARACTER_SIZE, X_AXIS_TEXT_OF_BUTTON_ORIGIN, Y_AXIS_TEXT_OF_SETTINGS_BUTTON_ORIGIN);
	setBasicButtonOptions(&scoreboardButton, "Scoreboard", CHARACTER_SIZE, X_AXIS_TEXT_OF_BUTTON_ORIGIN, Y_AXIS_TEXT_OF_SCOREBOARD_BUTTON_ORIGIN);
	setBasicButtonOptions(&exitButton, "Exit", CHARACTER_SIZE, X_AXIS_TEXT_OF_BUTTON_ORIGIN, Y_AXIS_TEXT_OF_EXIT_BUTTON_ORIGIN);
	setBasicButtonOptions(&backButton, "Back", CHARACTER_SIZE, X_AXIS_TEXT_OF_BUTTON_ORIGIN, Y_AXIS_TEXT_OF_BACK_BUTTON_ORIGIN);
	setBasicButtonOptions(&resumeButton, "Resume", CHARACTER_SIZE, X_AXIS_TEXT_OF_BUTTON_ORIGIN, Y_AXIS_TEXT_OF_RESUME_BUTTON_ORIGIN);

	setBasicButtonOptions(&keyboardThinButton, "Keyboard", CHARACTER_THIN_SIZE, X_AXIS_TEXT_OF_THIN_KEYBOARD_BUTTON_ORIGIN, Y_AXIS_TEXT_OF_THIN_BUTTONS_ORIGIN);
	setBasicButtonOptions(&joystickThinButton, "Joystick", CHARACTER_THIN_SIZE, X_AXIS_TEXT_OF_THIN_JOYSTICK_BUTTON_ORIGIN, Y_AXIS_TEXT_OF_THIN_BUTTONS_ORIGIN);
	setBasicButtonOptions(&mouseThinButton, "Mouse", CHARACTER_THIN_SIZE, X_AXIS_TEXT_OF_THIN_MOUSE_BUTTON_ORIGIN, Y_AXIS_TEXT_OF_THIN_BUTTONS_ORIGIN);

}

Buttons::~Buttons()
{
}

void Buttons::setBasicButtonOptions(sf::Text * button, std::string buttonName, int charSize, int positionX, int positionY)
{
	button->setFont(font);
	button->setCharacterSize(charSize);
	button->setPosition(positionX, positionY);
	button->setString(buttonName);
	button->setFillColor(sf::Color::Black);
}

sf::Text Buttons::getPlayButton()
{
	return playButton;
}

sf::Text Buttons::getSettingsButton()
{
	return settingsButton;
}

sf::Text Buttons::getScoreboardButton()
{
	return scoreboardButton;
}

sf::Text Buttons::getExitButton()
{
	return exitButton;
}

sf::Text Buttons::getBackButton()
{
	return backButton;
}

sf::Text Buttons::getResumeButton()
{
	return resumeButton;
}

sf::Text Buttons::getKeyboardThinButton()
{
	return keyboardThinButton;
}

sf::Text Buttons::getJoystickThinButton()
{
	return joystickThinButton;
}

sf::Text Buttons::getMouseThinButton()
{
	return mouseThinButton;
}

int Buttons::getButtonFrameWidth()
{
	return BUTTON_FRAME_WIDTH;
}

int Buttons::getButtonFrameHeight()
{
	return BUTTON_FRAME_HEIGHT;
}


int Buttons::getX_AxisTextOfButtonOrigin()
{
	return X_AXIS_TEXT_OF_BUTTON_ORIGIN;
}

int Buttons::getY_AxisTextOfPlayButtonOrigin()
{
	return Y_AXIS_TEXT_OF_PLAY_BUTTON_ORIGIN;
}

int Buttons::getY_AxisTextOfSettingsButtonOrigin()
{
	return Y_AXIS_TEXT_OF_SETTINGS_BUTTON_ORIGIN;
}

int Buttons::getY_AxisTextOfScoreboardButtonOrigin()
{
	return Y_AXIS_TEXT_OF_SCOREBOARD_BUTTON_ORIGIN;
}

int Buttons::getY_AxisTextOfExitButtonOrigin()
{
	return Y_AXIS_TEXT_OF_EXIT_BUTTON_ORIGIN;
}

int Buttons::getY_AxisTextOfBackButtonOrigin()
{
	return Y_AXIS_TEXT_OF_BACK_BUTTON_ORIGIN;
}

int Buttons::getY_AxisTextOfResumeButtonOrigin()
{
	return Y_AXIS_TEXT_OF_RESUME_BUTTON_ORIGIN;
}

int Buttons::getX_AxisTextOfThinKeyboardButtonOrigin()
{
	return X_AXIS_TEXT_OF_THIN_KEYBOARD_BUTTON_ORIGIN;
}

int Buttons::getX_AxisTextOfThinJoystickButtonOrigin()
{
	return X_AXIS_TEXT_OF_THIN_JOYSTICK_BUTTON_ORIGIN;
}

int Buttons::getX_AxisTextOfThinMouseButtonOrigin()
{
	return X_AXIS_TEXT_OF_THIN_MOUSE_BUTTON_ORIGIN;
}

int Buttons::getY_AxisTextOfThinButtonsOrigin()
{
	return Y_AXIS_TEXT_OF_THIN_BUTTONS_ORIGIN;
}

void Buttons::drawButton(sf::RenderWindow * renderedWindow, sf::Text usedButton,
		int X_AXIS_FRAME_OF_BUTTON_ORIGIN, int Y_AXIS_FRAME_OF_BUTTON_ORIGIN)
{
	spriteFrameButton.setPosition(X_AXIS_FRAME_OF_BUTTON_ORIGIN, Y_AXIS_FRAME_OF_BUTTON_ORIGIN);
	renderedWindow->draw(spriteFrameButton);
	renderedWindow->draw(usedButton);
}

void Buttons::drawThinButton(sf::RenderWindow * renderedWindow, sf::Text usedButton,
		int X_AXIS_FRAME_OF_BUTTON_ORIGIN, int Y_AXIS_FRAME_OF_BUTTON_ORIGIN)
{
	spriteThinFrameButton.setPosition(X_AXIS_FRAME_OF_BUTTON_ORIGIN, Y_AXIS_FRAME_OF_BUTTON_ORIGIN);
	renderedWindow->draw(spriteThinFrameButton);
	renderedWindow->draw(usedButton);
}

void Buttons::checkIfButtonIsHighlighted(sf::Text * usedText, bool * confirmationOfHighlight, sf::Event event,
		int X_AXIS_FRAME_OF_BUTTON_ORIGIN, int Y_AXIS_FRAME_OF_BUTTON_ORIGIN)
{

	if(event.mouseMove.x>X_AXIS_FRAME_OF_BUTTON_ORIGIN
		&& event.mouseMove.x<X_AXIS_FRAME_OF_BUTTON_ORIGIN+BUTTON_FRAME_WIDTH
			&& event.mouseMove.y>Y_AXIS_FRAME_OF_BUTTON_ORIGIN
			&& event.mouseMove.y<Y_AXIS_FRAME_OF_BUTTON_ORIGIN+BUTTON_FRAME_HEIGHT)
	{
		usedText->setFillColor(sf::Color::Green);
		*confirmationOfHighlight=true;
	}
	else
	{
		usedText->setFillColor(sf::Color::Black);
		*confirmationOfHighlight=false;
	}
}



void Buttons::checkIfButtonWasPressed(bool * buttonPressed, bool buttonHighlighted)
{
	if(buttonHighlighted)
	{
		*buttonPressed=true;
	}
	else
	{
		*buttonPressed=false;
	}
}

void Buttons::checkIfThinButtonIsHighlighted(sf::Text * usedText, bool * confirmationOfHighlight, sf::Event event,
		int X_AXIS_FRAME_OF_BUTTON_ORIGIN, int Y_AXIS_FRAME_OF_BUTTON_ORIGIN)
{

	if(event.mouseMove.x>X_AXIS_FRAME_OF_BUTTON_ORIGIN
		&& event.mouseMove.x<X_AXIS_FRAME_OF_BUTTON_ORIGIN+BUTTON_THIN_FRAME_WIDTH
			&& event.mouseMove.y>Y_AXIS_FRAME_OF_BUTTON_ORIGIN
			&& event.mouseMove.y<Y_AXIS_FRAME_OF_BUTTON_ORIGIN+BUTTON_FRAME_HEIGHT)
	{
		usedText->setFillColor(sf::Color::Green);
		*confirmationOfHighlight=true;
	}
	else
	{
		usedText->setFillColor(sf::Color::Black);
		*confirmationOfHighlight=false;
	}
}

void Buttons::setProperControlColor(sf::Text * usedKeyboardThinButton, sf::Text * usedMouseThinButton,
		sf::Text * usedJoystickThinButton, Settings::ControlType controlType)
{
	if(controlType == Settings::KEYBOARD)
	{
		usedKeyboardThinButton->setFillColor(sf::Color::Red);
	}
	if(controlType == Settings::JOYSTICK)
	{
		usedJoystickThinButton->setFillColor(sf::Color::Red);
	}
	if(controlType == Settings::MOUSE)
	{
		usedMouseThinButton->setFillColor(sf::Color::Red);
	}

}

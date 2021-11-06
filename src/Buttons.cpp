#include "Buttons.hpp"

Buttons::Buttons()
{
	textureFrameButton.loadFromFile("src/Graphics/Objects/UnderButtons.png");
	spriteFrameButton.setTexture(textureFrameButton);
	font.loadFromFile("src/Fonts/Montserrat-Regular.ttf");
	setBasicButtonOptions(&playButton, "Play", X_AXIS_TEXT_OF_BUTTON_ORIGIN, Y_AXIS_TEXT_OF_PLAY_BUTTON_ORIGIN);
	setBasicButtonOptions(&exitButton, "Exit", X_AXIS_TEXT_OF_BUTTON_ORIGIN, Y_AXIS_TEXT_OF_EXIT_BUTTON_ORIGIN);
}

Buttons::~Buttons()
{
}

/*
 * private functions
 */

void Buttons::setBasicButtonOptions(sf::Text * button, std::string buttonName, int positionX, int positionY)
{
	button->setFont(font);
	button->setCharacterSize(CHARACTER_SIZE);
	button->setPosition(positionX, positionY);
	button->setString(buttonName);
	button->setFillColor(sf::Color::Black);
}

/*
 * public functions
 */

sf::Sprite Buttons::getSpriteFrameButton()
{
	return spriteFrameButton;
}

int Buttons::getButtonFrameWidth()
{
	return BUTTON_FRAME_WIDTH;
}

int Buttons::getButtonFrameHeight()
{
	return BUTTON_FRAME_HEIGHT;
}



sf::Text Buttons::getPlayButton()
{
	return playButton;
}

sf::Text Buttons::getExitButton()
{
	return exitButton;
}



int Buttons::getX_AxisTextOfButtonOrigin()
{
	return X_AXIS_TEXT_OF_BUTTON_ORIGIN;
}

int Buttons::getY_AxisTextOfPlayButtonOrigin()
{
	return Y_AXIS_TEXT_OF_PLAY_BUTTON_ORIGIN;
}

int Buttons::getY_AxisTextOfExitButtonOrigin()
{
	return Y_AXIS_TEXT_OF_EXIT_BUTTON_ORIGIN;
}



void Buttons::drawButton(sf::RenderWindow * renderedWindow, sf::Text usedButton,
		int X_AXIS_FRAME_OF_BUTTONS_ORIGIN, int Y_AXIS_FRAME_OF_PLAY_BUTTON_ORIGIN)
{
	spriteFrameButton.setPosition(X_AXIS_FRAME_OF_BUTTONS_ORIGIN, Y_AXIS_FRAME_OF_PLAY_BUTTON_ORIGIN);
	renderedWindow->draw(spriteFrameButton);
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

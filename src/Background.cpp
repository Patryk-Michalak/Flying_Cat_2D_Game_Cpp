#include "Background.hpp"

Background::Background()
{
	textureIntroBackground.loadFromFile("src/Graphics/Backgrounds/Intro.png");
	textureMainMenuBackground.loadFromFile("src/Graphics/Backgrounds/MainMenu.png");
	textureGameplayBackground.loadFromFile("src/Graphics/Backgrounds/Gameplay.png");
	texturePauseBackground.loadFromFile("src/Graphics/Backgrounds/Pause.png");
	textureGameOverBackground.loadFromFile("src/Graphics/GameOver.png");

	spriteIntroBackground.setTexture(textureIntroBackground);
	spriteMainMenuBackground.setTexture(textureMainMenuBackground);
	spriteGameplayBackground.setTexture(textureGameplayBackground);
	spritePauseBackground.setTexture(texturePauseBackground);
	spriteGameOverBackground.setTexture(textureGameOverBackground);
}

Background::~Background()
{
}

sf::Sprite Background::getIntroBackground()
{
	return spriteIntroBackground;
}

sf::Sprite Background::getMainMenuBackground()
{
	return spriteMainMenuBackground;
}

sf::Sprite Background::getGameplayBackground()
{
	return spriteGameplayBackground;
}

sf::Sprite Background::getPauseBackground()
{
	return spritePauseBackground;
}

sf::Sprite Background::getGameOverBackground()
{
	return spriteGameOverBackground;
}

void Background::drawBackground(sf::RenderWindow * renderedWindow, sf::Sprite usedBackground)
{
	renderedWindow->draw(usedBackground);
}

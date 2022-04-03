#include "Background.hpp"

Background::Background()
{
	textureIntroBackground.loadFromFile("src/Graphics/Backgrounds/Intro.png");
	textureMainMenuBackground.loadFromFile("src/Graphics/Backgrounds/MainMenu.png");
	textureGameplayBackground.loadFromFile("src/Graphics/Backgrounds/Gameplay.png");
	texturePauseBackground.loadFromFile("src/Graphics/Backgrounds/Pause.png");
	textureGameOverBackground.loadFromFile("src/Graphics/Backgrounds/GameOver.png");

	spriteIntroBackground.setTexture(textureIntroBackground);
	spriteMainMenuBackground.setTexture(textureMainMenuBackground);
	spriteGameplayBackground.setTexture(textureGameplayBackground);
	spritePauseBackground.setTexture(texturePauseBackground);
	spriteGameOverBackground.setTexture(textureGameOverBackground);
}

Background::~Background()
{
}

void Background::drawBackground(sf::RenderWindow * renderedWindow, std::string typeOfBackground)
{
	if (typeOfBackground == "introBackground")
	{
		renderedWindow->draw(spriteIntroBackground);
	}
	if (typeOfBackground == "pauseBackground")
	{
		renderedWindow->draw(spritePauseBackground);
	}
	if (typeOfBackground == "mainMenuBackground")
	{
		renderedWindow->draw(spriteMainMenuBackground);
	}
	if (typeOfBackground == "gameplayBackground")
	{
		renderedWindow->draw(spriteGameplayBackground);
	}
	if (typeOfBackground == "gameOverBackground")
	{
		renderedWindow->draw(spriteGameOverBackground);
	}
}

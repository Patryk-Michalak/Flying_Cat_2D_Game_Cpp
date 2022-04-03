#ifndef BACKGROUND_HPP_
#define BACKGROUND_HPP_

#include <SFML/Graphics.hpp>

class Background
{
private:
	sf::Texture textureIntroBackground;
	sf::Texture textureMainMenuBackground;
	sf::Texture textureGameplayBackground;
	sf::Texture texturePauseBackground;
	sf::Texture textureGameOverBackground;

	sf::Sprite spriteIntroBackground;
	sf::Sprite spriteMainMenuBackground;
	sf::Sprite spriteGameplayBackground;
	sf::Sprite spritePauseBackground;
	sf::Sprite spriteGameOverBackground;

public:
	Background();
	~Background();

	void drawBackground(sf::RenderWindow * renderedWindow, std::string typeOfBackground);
};

#endif

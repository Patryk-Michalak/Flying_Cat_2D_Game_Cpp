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

	sf::Sprite getIntroBackground();
	sf::Sprite getMainMenuBackground();
	sf::Sprite getGameplayBackground();
	sf::Sprite getPauseBackground();
	sf::Sprite getGameOverBackground();

	void drawBackground(sf::RenderWindow * renderedWindow, sf::Sprite usedBackground);
};



#endif

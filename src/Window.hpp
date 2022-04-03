#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <SFML/Graphics.hpp>

class Window
{
private:
	sf::RenderWindow renderedWindow;
	int windowResolutionWidth = 1366;
	int windowResolutionHeight = 768;
	const std::string TITLE_GAME = "Flying Cat";
public:
	Window();
	virtual ~Window();

	void createWindow();
	sf::RenderWindow * returnRenderedWindow();
	int returnWindowResolutionWidth();
	int returnWindowResolutionHeight();
};

#endif

#include "Window.hpp"

Window::Window()
{
}

Window::~Window()
{
}

void Window::createWindow()
{
	renderedWindow.create(sf::VideoMode(windowResolutionWidth, windowResolutionHeight), TITLE_GAME, sf::Style::Close);
}

sf::RenderWindow * Window::returnRenderedWindow()
{
	return &renderedWindow;
}

int Window::returnWindowResolutionWidth()
{
	return windowResolutionWidth;
}

int Window::returnWindowResolutionHeight()
{
	return windowResolutionHeight;
}

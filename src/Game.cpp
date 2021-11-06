#include "Game.hpp"
#include "Window.hpp"

Game::Game()
{
}

Game::~Game()
{
}

void Game::runGame()
{
	Window window;
	window.createWindow();
	window.showDataInWindow();
}




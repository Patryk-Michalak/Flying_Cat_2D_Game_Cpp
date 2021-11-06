#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <cstdio>

#include "Background.hpp"
#include "Buttons.hpp"
#include "Objects.hpp"

using timeValueType = std::chrono::high_resolution_clock::time_point;

class Window
{
private:

	timeValueType windowStartTime;

	Background background;
	Buttons buttons;
	sf::Sprite usedSpriteBackground;
	sf::Text usedPlayButton;
	sf::Text usedExitButton;

	sf::RenderWindow renderedWindow;
	const int WINDOW_RESOLUTION_WIDTH = 1366;
	const int WINDOW_RESOLUTION_HEIGHT = 768;
	const std::string TITLE_GAME = "Flying Cat";

	bool introWasShowed = false;
	const int TIME_OF_INTRO_DURATION = 2000;
	bool showMenu = false;
	bool makeGameplay = false;

	const int X_AXIS_FRAME_OF_BUTTONS_ORIGIN = WINDOW_RESOLUTION_WIDTH/2-buttons.getButtonFrameWidth()/2;
	const int Y_AXIS_FRAME_OF_PLAY_BUTTON_ORIGIN = buttons.getY_AxisTextOfPlayButtonOrigin();
	const int Y_AXIS_FRAME_OF_EXIT_BUTTON_ORIGIN = buttons.getY_AxisTextOfExitButtonOrigin();

	bool playHighlighted=false;
	bool exitHighlighted=false;

	bool playPressed=false;
	bool exitPressed=false;

	Objects objects;
	bool catPositionNeedsInitialization = true;
	int catFPS_Limiter = 10;
	int catFPS_Increment = 0;

	float catPixelJumpRight = 0;
	float catPixelJumpLeft = 0;
	float catPixelJumpDown = 0;
	float catPixelJumpUp = 0;

	bool firstObstacleWasInitialized = false;
	bool randomizedObstacle1 = false;
	bool randomizedObstacle2 = false;
	bool randomizedObstacle3 = false;
	int obstacleFPS_Limiter = 10;
	int obstacleFPS_Increment = 0;
	Obstacles * obstacle1 = objects.getObstacle1();
	Obstacles * obstacle2 = objects.getObstacle2();
	Obstacles * obstacle3 = objects.getObstacle3();

	bool collisionDetected = false;

public:
	Window();
	~Window();

	void createWindow();
	void showDataInWindow();

	timeValueType measureExactTimeEvent();

	void checkTimeOfWindowOpening();
	void checkTime(); //////

	void checkIfPlayButtonWasProperlyReleased();
	void checkIfExitButtonWasProperlyReleased();

	void completeEventsList();
};

#endif

#ifndef OBJECTS_HPP_
#define OBJECTS_HPP_

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

struct Obstacles
{
	int Y_PositionOfHoleBeggining;
	int X_PositionOfPipe;
	int X_PositionOfPipeRest;
};

class Objects
{
private:
	sf::Texture textureCat;
	sf::Texture texturePipeFromTop;
	sf::Texture texturePipeFromBot;
	sf::Texture texturePipeRestFromTop;
	sf::Texture texturePipeRestFromBot;

	sf::Sprite spriteCat;
	sf::Sprite spritePipeFromTop;
	sf::Sprite spritePipeFromBot;
	sf::Sprite spritePipeRestFromTop;
	sf::Sprite spritePipeRestFromBot;

	const int CAT_WIDTH = 50;
	const int CAT_HEIGHT = 45;
	const int PIPE_WIDTH = 169;
	const int PIPE_HEIGHT = 86;
	const int PIPE_REST_WIDTH = 105;
	const int PIPE_REST_HEIGHT = 216;

	int catPositionX=300;
	int catPositionY=359;
	const float CAT_INERTION_RATIO = 0.9;
	const float CAT_ACTUAL_SPEED_RATIO = 0.1;

	float catMoveRightActualSpeed = 0;
	float catMoveLeftActualSpeed = 0;
	float catMoveDownActualSpeed = 0;
	float catMoveUpActualSpeed = 0;

	float catMoveRightPreviousSpeed = 0;
	float catMoveLeftPreviousSpeed = 0;
	float catMoveDownPreviousSpeed = 0;
	float catMoveUpPreviousSpeed = 0;


	Obstacles obstacle1;
	Obstacles obstacle2;
	Obstacles obstacle3;

	const int OBSTACLE_HOLE_HEIGHT = 100;
	const int HOLE_FROM_THE_EDGES = 150;
	int obstaclesSpeed = 5;

public:
	Objects();
	~Objects();

	void initializeCatPosition();
	void calculateCatMove(int windowResolutionWidth, int windowResolutionHeight, float catPixelJumpRight,
			float catPixelJumpLeft, float catPixelJumpDown, float catPixelJumpUp);
	void drawCat(sf::RenderWindow * renderedWindow, Objects object);

	Obstacles * getObstacle1();
	Obstacles * getObstacle2();
	Obstacles * getObstacle3();

	void initializeObstacle(Obstacles * obstacle, int windowResolutionWidth, int windowResolutionHeight);
	void initializeFarAwayObstacle(Obstacles * obstacle, int windowResolutionWidth, int windowResolutionHeight);
	void calculateMoveObstacle(Obstacles * obstacle);
	void drawObstacle(sf::RenderWindow * renderedWindow, Obstacles obstacle, int windowResolutionHeight);

	bool checkCollision(int windowResolutionWidth, int windowResolutionHeight);
	bool checkCollisionWithProperObstacle(Obstacles obstacle, int windowResolutionWidth, int windowResolutionHeight);

};

#endif

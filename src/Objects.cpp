#include "Objects.hpp"

Objects::Objects()
{
	srand(time(NULL));

	textureCat.loadFromFile("src/Graphics/Objects/Cat.png");
	texturePipeFromTop.loadFromFile("src/Graphics/Objects/PipeFromTop.png");
	texturePipeFromBot.loadFromFile("src/Graphics/Objects/PipeFromBot.png");
	texturePipeRestFromTop.loadFromFile("src/Graphics/Objects/PipeRestFromTop.png");
	texturePipeRestFromBot.loadFromFile("src/Graphics/Objects/PipeRestFromTop.png");

	spriteCat.setTexture(textureCat);
	spritePipeFromTop.setTexture(texturePipeFromTop);
	spritePipeFromBot.setTexture(texturePipeFromBot);
	spritePipeRestFromTop.setTexture(texturePipeRestFromTop);
	spritePipeRestFromBot.setTexture(texturePipeRestFromBot);

}

Objects::~Objects()
{
}

Obstacles * Objects::getObstacle1()
{
	return &obstacle1;
}

Obstacles * Objects::getObstacle2()
{
	return &obstacle2;
}

Obstacles * Objects::getObstacle3()
{
	return &obstacle3;
}

void Objects::initializeCatPosition()
{
	catPositionX=CAT_START_POSITION_X;
	catPositionY=CAT_START_POSITION_Y;
}

void Objects::initializeObstacle(Obstacles * obstacle, int windowResolutionWidth, int windowResolutionHeight)
{
	obstacle->Y_PositionOfHoleBeggining = (rand()%(windowResolutionHeight-HOLE_FROM_THE_EDGES*2-OBSTACLE_HOLE_HEIGHT))+HOLE_FROM_THE_EDGES;
	obstacle->X_PositionOfPipe = windowResolutionWidth;
	obstacle->X_PositionOfPipeRest = windowResolutionWidth+(PIPE_WIDTH-PIPE_REST_WIDTH)/2;
}

void Objects::initializeFarAwayObstacle(Obstacles * obstacle, int windowResolutionWidth, int windowResolutionHeight)
{
	obstacle->Y_PositionOfHoleBeggining= windowResolutionHeight*3;
	obstacle->X_PositionOfPipe = windowResolutionWidth*3;
	obstacle->X_PositionOfPipeRest = windowResolutionWidth*3;
}

void Objects::resetObjectsSpeed()
{
	catMoveRightActualSpeed = 0;
	catMoveRightPreviousSpeed = 0;
	catMoveLeftActualSpeed = 0;
	catMoveLeftPreviousSpeed = 0;
	catMoveDownActualSpeed = 0;
	catMoveDownPreviousSpeed = 0;
	catMoveUpActualSpeed = 0;
	catMoveUpPreviousSpeed = 0;
}

void Objects::calculateCatMove(int windowResolutionWidth, int windowResolutionHeight, float catPixelJumpRight,
		float catPixelJumpLeft, float catPixelJumpDown, float catPixelJumpUp)
{

	catMoveRightActualSpeed=(CAT_INERTION_RATIO*catMoveRightPreviousSpeed+CAT_ACTUAL_SPEED_RATIO*catPixelJumpRight/SCALING_SPEED);
	catMoveLeftActualSpeed=(CAT_INERTION_RATIO*catMoveLeftPreviousSpeed+CAT_ACTUAL_SPEED_RATIO*catPixelJumpLeft/SCALING_SPEED);
	catMoveDownActualSpeed=(CAT_INERTION_RATIO*catMoveDownPreviousSpeed+CAT_ACTUAL_SPEED_RATIO*catPixelJumpDown/SCALING_SPEED);
	catMoveUpActualSpeed=(CAT_INERTION_RATIO*catMoveUpPreviousSpeed+CAT_ACTUAL_SPEED_RATIO*catPixelJumpUp/SCALING_SPEED);

	catPositionX+=(int)catMoveRightActualSpeed-(int)catMoveLeftActualSpeed;
	catPositionY+=(int)catMoveDownActualSpeed-(int)catMoveUpActualSpeed;

	catMoveRightPreviousSpeed=catMoveRightActualSpeed;
	catMoveLeftPreviousSpeed=catMoveLeftActualSpeed;
	catMoveDownPreviousSpeed=catMoveDownActualSpeed;
	catMoveUpPreviousSpeed=catMoveUpActualSpeed;

	if(catPositionX<0)
	{
		catPositionX=0;
	}

	if(catPositionX>windowResolutionWidth-CAT_WIDTH)
	{
		catPositionX=windowResolutionWidth-CAT_WIDTH;
	}

	if(catPositionY<0)
	{
		catPositionY=0;
	}

	if(catPositionY>windowResolutionHeight-CAT_HEIGHT)
	{
		catPositionY=windowResolutionHeight-CAT_HEIGHT;
	}
}

void Objects::calculateMoveObstacle(Obstacles * obstacle, int obstacleSpeed)
{
	obstacle->X_PositionOfPipe -= obstacleSpeed/SCALING_SPEED;
	obstacle->X_PositionOfPipeRest -= obstacleSpeed/SCALING_SPEED;
}

void Objects::drawCat(sf::RenderWindow * renderedWindow, Objects object)
{
	spriteCat.setPosition(object.catPositionX, object.catPositionY);
	renderedWindow->draw(spriteCat);
}

void Objects::drawObstacle(sf::RenderWindow * renderedWindow, Obstacles obstacle, int windowResolutionHeight)
{
	spritePipeFromTop.setPosition(obstacle.X_PositionOfPipe, obstacle.Y_PositionOfHoleBeggining-PIPE_HEIGHT);
	spritePipeFromBot.setPosition(obstacle.X_PositionOfPipe, obstacle.Y_PositionOfHoleBeggining+OBSTACLE_HOLE_HEIGHT);
	renderedWindow->draw(spritePipeFromTop);
	renderedWindow->draw(spritePipeFromBot);

	int initialPositionOfPipeRestFromTop = obstacle.Y_PositionOfHoleBeggining-PIPE_HEIGHT-PIPE_REST_HEIGHT;
	do
	{

		sf::Sprite calculatedSpritePipeRestFromTop = spritePipeRestFromTop;
		calculatedSpritePipeRestFromTop.setPosition(obstacle.X_PositionOfPipeRest, initialPositionOfPipeRestFromTop);
		renderedWindow->draw(calculatedSpritePipeRestFromTop);
		initialPositionOfPipeRestFromTop -= PIPE_REST_HEIGHT;

	} while (initialPositionOfPipeRestFromTop>-PIPE_REST_HEIGHT);



	int initialPositionOfPipeRestFromBot = obstacle.Y_PositionOfHoleBeggining+100+PIPE_HEIGHT;
	do
	{

		sf::Sprite calculatedSpritePipeRestFromBot = spritePipeRestFromBot;
		calculatedSpritePipeRestFromBot.setPosition(obstacle.X_PositionOfPipeRest, initialPositionOfPipeRestFromBot);
		renderedWindow->draw(calculatedSpritePipeRestFromBot);
		initialPositionOfPipeRestFromBot += PIPE_REST_HEIGHT;

	} while (initialPositionOfPipeRestFromBot<windowResolutionHeight);

}

bool Objects::checkCollision(int windowResolutionWidth, int windowResolutionHeight)
{
	bool temporaryValue = false;
	temporaryValue = temporaryValue | checkCollisionWithProperObstacle(obstacle1, windowResolutionWidth, windowResolutionHeight);
	temporaryValue = temporaryValue | checkCollisionWithProperObstacle(obstacle2, windowResolutionWidth, windowResolutionHeight);
	temporaryValue = temporaryValue | checkCollisionWithProperObstacle(obstacle3, windowResolutionWidth, windowResolutionHeight);
	return temporaryValue;
}

bool Objects::checkCollisionWithProperObstacle(Obstacles obstacle, int windowResolutionWidth, int windowResolutionHeight)
{
	// top of pipe
	if(catPositionX+CAT_WIDTH>obstacle.X_PositionOfPipe
			&& catPositionX<obstacle.X_PositionOfPipe+PIPE_WIDTH
			&& catPositionY+CAT_HEIGHT>obstacle.Y_PositionOfHoleBeggining-PIPE_HEIGHT
			&& catPositionY<obstacle.Y_PositionOfHoleBeggining)
	{
		catMoveRightPreviousSpeed=0;
		catMoveLeftPreviousSpeed=0;
		catMoveUpPreviousSpeed=0;
		catMoveDownPreviousSpeed=0;
		return true;
	}

	// top of rest pipe
	if(catPositionX+CAT_WIDTH>obstacle.X_PositionOfPipeRest
			&& catPositionX<obstacle.X_PositionOfPipeRest+PIPE_REST_WIDTH
			&& catPositionY+CAT_HEIGHT>0
			&& catPositionY<obstacle.Y_PositionOfHoleBeggining-PIPE_HEIGHT)
	{
		catMoveRightPreviousSpeed=0;
		catMoveLeftPreviousSpeed=0;
		catMoveUpPreviousSpeed=0;
		catMoveDownPreviousSpeed=0;
		return true;
	}

	// bot of pipe
	if(catPositionX+CAT_WIDTH>obstacle.X_PositionOfPipe
			&& catPositionX<obstacle.X_PositionOfPipe+PIPE_WIDTH
			&& catPositionY+CAT_HEIGHT>obstacle.Y_PositionOfHoleBeggining+OBSTACLE_HOLE_HEIGHT
			&& catPositionY<obstacle.Y_PositionOfHoleBeggining+OBSTACLE_HOLE_HEIGHT+PIPE_HEIGHT)
	{
		catMoveRightPreviousSpeed=0;
		catMoveLeftPreviousSpeed=0;
		catMoveUpPreviousSpeed=0;
		catMoveDownPreviousSpeed=0;
		return true;
	}

	// bot of rest pipe
	if(catPositionX+CAT_WIDTH>obstacle.X_PositionOfPipeRest
			&& catPositionX<obstacle.X_PositionOfPipeRest+PIPE_REST_WIDTH
			&& catPositionY+CAT_HEIGHT>obstacle.Y_PositionOfHoleBeggining+OBSTACLE_HOLE_HEIGHT+PIPE_HEIGHT
			&& catPositionY<windowResolutionHeight)
	{
		catMoveRightPreviousSpeed=0;
		catMoveLeftPreviousSpeed=0;
		catMoveUpPreviousSpeed=0;
		catMoveDownPreviousSpeed=0;
		return true;
	}
	return false;
}

int Objects::returnCatPositionX()
{
	return catPositionX;
}

int Objects::returnCatPositionY()
{
	return catPositionY;
}

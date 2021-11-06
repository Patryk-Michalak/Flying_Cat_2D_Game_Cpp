#include "Window.hpp"

Window::Window()
{
	windowStartTime = Window::measureExactTimeEvent();

	usedPlayButton = buttons.getPlayButton();
	usedExitButton = buttons.getExitButton();
}

Window::~Window()
{
}

void Window::createWindow()
{
	renderedWindow.create(sf::VideoMode(WINDOW_RESOLUTION_WIDTH, WINDOW_RESOLUTION_HEIGHT), TITLE_GAME, sf::Style::Close);
}

void Window::showDataInWindow()
{

	while (renderedWindow.isOpen())
	{
		fflush(stdout); //this line enable showing info in console, cause eclipse console is bugged
		completeEventsList(); // complete event list, last function in this file

		renderedWindow.clear();
		if(!introWasShowed)
		{
			checkTimeOfWindowOpening();
			usedSpriteBackground = background.getIntroBackground();
			background.drawBackground(&renderedWindow, usedSpriteBackground);
		}

		else if(showMenu)
		{
			usedSpriteBackground = background.getMainMenuBackground();
			background.drawBackground(&renderedWindow, usedSpriteBackground);
			buttons.drawButton(&renderedWindow, usedPlayButton, X_AXIS_FRAME_OF_BUTTONS_ORIGIN, Y_AXIS_FRAME_OF_PLAY_BUTTON_ORIGIN);
			buttons.drawButton(&renderedWindow, usedExitButton, X_AXIS_FRAME_OF_BUTTONS_ORIGIN, Y_AXIS_FRAME_OF_EXIT_BUTTON_ORIGIN);
		}

		else if(makeGameplay)
		{
			usedSpriteBackground = background.getGameplayBackground();
			background.drawBackground(&renderedWindow, usedSpriteBackground);

			if(++catFPS_Increment>catFPS_Limiter)
			{
				if(catPositionNeedsInitialization)
				{
					objects.initializeCatPosition();
					catPositionNeedsInitialization=false;
				}
				//checkTime();
				catFPS_Increment=0;
				objects.calculateCatMove(WINDOW_RESOLUTION_WIDTH, WINDOW_RESOLUTION_HEIGHT, catPixelJumpRight,
						catPixelJumpLeft, catPixelJumpDown, catPixelJumpUp);
			}
			objects.drawCat(&renderedWindow, objects);



			if(!firstObstacleWasInitialized)
			{
				objects.initializeObstacle(obstacle1, WINDOW_RESOLUTION_WIDTH, WINDOW_RESOLUTION_HEIGHT);
				objects.initializeFarAwayObstacle(obstacle2, WINDOW_RESOLUTION_WIDTH, WINDOW_RESOLUTION_HEIGHT);
				objects.initializeFarAwayObstacle(obstacle3, WINDOW_RESOLUTION_WIDTH, WINDOW_RESOLUTION_HEIGHT);
				firstObstacleWasInitialized=true;
				randomizedObstacle1=true;
			}

			if(++obstacleFPS_Increment>obstacleFPS_Limiter)
			{
				objects.calculateMoveObstacle(obstacle1);
				objects.calculateMoveObstacle(obstacle2);
				objects.calculateMoveObstacle(obstacle3);
				obstacleFPS_Increment=0;

				if(obstacle1->X_PositionOfPipe<WINDOW_RESOLUTION_WIDTH/2 && !randomizedObstacle2)
				{
					objects.initializeObstacle(obstacle2, WINDOW_RESOLUTION_WIDTH, WINDOW_RESOLUTION_HEIGHT);
					randomizedObstacle2=true;
					randomizedObstacle3=false;
				}

				if(obstacle2->X_PositionOfPipe<WINDOW_RESOLUTION_WIDTH/2 && !randomizedObstacle3)
				{
					objects.initializeObstacle(obstacle3, WINDOW_RESOLUTION_WIDTH, WINDOW_RESOLUTION_HEIGHT);
					randomizedObstacle3=true;
					randomizedObstacle1=false;
				}

				if(obstacle3->X_PositionOfPipe<WINDOW_RESOLUTION_WIDTH/2 && !randomizedObstacle1)
				{
					objects.initializeObstacle(obstacle1, WINDOW_RESOLUTION_WIDTH, WINDOW_RESOLUTION_HEIGHT);
					randomizedObstacle1=true;
					randomizedObstacle2=false;
				}

				collisionDetected=objects.checkCollision(WINDOW_RESOLUTION_WIDTH, WINDOW_RESOLUTION_HEIGHT);

				if(collisionDetected)
				{
					collisionDetected=false;
					makeGameplay=false;
					showMenu=true;

					catPositionNeedsInitialization=true;
					firstObstacleWasInitialized=false;
					randomizedObstacle1=false;
					randomizedObstacle2=false;
					randomizedObstacle3=false;

					catPixelJumpRight=0;
					catPixelJumpLeft=0;
					catPixelJumpUp=0;
					catPixelJumpDown=0;
				}
			}

			objects.drawObstacle(&renderedWindow, *obstacle1,  WINDOW_RESOLUTION_HEIGHT);
			objects.drawObstacle(&renderedWindow, *obstacle2,  WINDOW_RESOLUTION_HEIGHT);
			objects.drawObstacle(&renderedWindow, *obstacle3,  WINDOW_RESOLUTION_HEIGHT);

		}

		renderedWindow.display();
	}
}

timeValueType Window::measureExactTimeEvent()
{
	return std::chrono::high_resolution_clock::now();
}

void Window::checkTimeOfWindowOpening()
{
	auto actualTime = Window::measureExactTimeEvent();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(actualTime-windowStartTime);
	if(elapsedTime.count()>TIME_OF_INTRO_DURATION)
	{
		introWasShowed = true;
		showMenu = true;
	}

	//std::cout<<elapsedTime.count()<<"\n"; //temporary function to debug, to delete later
}

////////
void Window::checkTime()
{
	auto actualTime = Window::measureExactTimeEvent();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(actualTime-windowStartTime);
	std::cout<<elapsedTime.count()<<"\n"; //temporary function to debug, to delete later
}
///////

void Window::checkIfPlayButtonWasProperlyReleased()
{
	if(playPressed==true && playHighlighted==true)
	{
		playPressed=false;
		showMenu=false;
		makeGameplay=true;
		std::cout<<"Button properly released in play\n"; // temporary function
	}
}

void Window::checkIfExitButtonWasProperlyReleased()
{
	if(exitPressed==true && exitHighlighted==true)
	{
		renderedWindow.close();
	}
}



void Window::completeEventsList()
{
	sf::Event event;

	while (renderedWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			renderedWindow.close();
		}

		if (event.type == sf::Event::MouseMoved)
		{
			//checkTime();
			if(showMenu)
			{
				buttons.checkIfButtonIsHighlighted(&usedPlayButton, &playHighlighted, event,
						X_AXIS_FRAME_OF_BUTTONS_ORIGIN, Y_AXIS_FRAME_OF_PLAY_BUTTON_ORIGIN);
				buttons.checkIfButtonIsHighlighted(&usedExitButton, &exitHighlighted, event,
						X_AXIS_FRAME_OF_BUTTONS_ORIGIN, Y_AXIS_FRAME_OF_EXIT_BUTTON_ORIGIN);
			}
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if(showMenu)
			{
				buttons.checkIfButtonWasPressed(&playPressed, playHighlighted);
				buttons.checkIfButtonWasPressed(&exitPressed, exitHighlighted);
			}

		}

		if (event.type == sf::Event::MouseButtonReleased)
		{
			if(showMenu)
			{
				checkIfPlayButtonWasProperlyReleased();
				checkIfExitButtonWasProperlyReleased();
			}
		}

		if (event.type == sf::Event::EventType::KeyPressed )
		{

			if(makeGameplay)
			{
				if (event.key.code == sf::Keyboard::D)
				{
					catPixelJumpRight=10;
				}

				if (event.key.code == sf::Keyboard::A)
				{
					catPixelJumpLeft=10;
				}

				if (event.key.code == sf::Keyboard::S)
				{
					catPixelJumpDown=10;
				}

				if (event.key.code == sf::Keyboard::W)
				{
					catPixelJumpUp=10;
				}
			}
		}

		if (event.type == sf::Event::EventType::KeyReleased )
		{
			if(makeGameplay)
			{
				if (event.key.code == sf::Keyboard::D)
				{
					catPixelJumpRight=0;
				}

				if (event.key.code == sf::Keyboard::A)
				{
					catPixelJumpLeft=0;
				}

				if (event.key.code == sf::Keyboard::S)
				{
					catPixelJumpDown=0;
				}

				if (event.key.code == sf::Keyboard::W)
				{
					catPixelJumpUp=0;
				}
			}
		}
	}
}

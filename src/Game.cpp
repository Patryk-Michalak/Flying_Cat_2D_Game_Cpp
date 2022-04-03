#include "Game.hpp"

Game::Game()
{
	startTimeOfGameInNanoseconds = timeMeasurement.returnExactTimeInNanoseconds();
}

Game::~Game()
{
}

void Game::runGame()
{
	window.createWindow();
	displayData();
}

void Game::displayData()
{
	while (renderedWindow->isOpen())
	{
		fflush(stdout); //this line enable showing info in console, cause eclipse console is bugged
		completeEventsList();
		renderedWindow->clear();
		defineLogicState();
		renderedWindow->display();
	}
}

void Game::defineLogicState()
{
	if(introductionState)
	{
		showIntroduction();
		chooseMusic(music.MAIN_MENU);
	}
	else if(mainMenuState)
	{
		if(!settingsState && !scoreboardState)
		{
			showMainMenu();
		}
		else if (settingsState)
		{
			showSettingsMenu();
		}
		else if (scoreboardState)
		{
			showScoreboardMenu();
		}
		chooseMusic(music.MAIN_MENU);
	}
	else if(gameplayState && !pauseState)
	{
		showGameplay();
		chooseMusic(music.GAMEPLAY);
	}
	else if(pauseState)
	{
		showPause();
		chooseMusic(music.MAIN_MENU);
	}
	else if(gameOverState)
	{
		showGameOver();
		chooseMusic(music.GAMEOVER);
	}
}

void Game::showIntroduction()
{
	int timeFromRunningTheGameInMiliseconds = timeMeasurement.calculateElapsedTimeFromValueInMiliseconds(startTimeOfGameInNanoseconds);
	if(timeFromRunningTheGameInMiliseconds > TIME_OF_INTRO_DURATION_IN_MILISECONDS)
	{
		introductionState = false;
	}
	background.drawBackground(renderedWindow, "introBackground");
	mainMenuState = not introductionState;

}

void Game::chooseMusic(enum Music::MusicInGameLogicState musicInGameLogicState)
{
	music.setMusicVolume(musicInGameLogicState, settings.getVolumeValue());
	music.playMusic(musicInGameLogicState);
}

void Game::showMainMenu()
{
	background.drawBackground(renderedWindow, "mainMenuBackground");
	showMainMenuButtons();
	if(catPositionNeedsInitialization)
	{
		objects.initializeCatPosition();
		catPositionNeedsInitialization=false;
	}

	if(obstaclePositionNeedsInitialization)
	{
		objects.initializeObstacle(obstacle1, windowResolutionWidth, windowResolutionHeight);
		objects.initializeFarAwayObstacle(obstacle2, windowResolutionWidth, windowResolutionHeight);
		objects.initializeFarAwayObstacle(obstacle3, windowResolutionWidth, windowResolutionHeight);
		obstaclePositionNeedsInitialization=false;
		randomizedObstacle1 = true;
		randomizedObstacle2 = false;
		randomizedObstacle3 = false;
		objects.resetObjectsSpeed();
	}
	scoreboardOpened = false;
}

void Game::showMainMenuButtons()
{
	buttons.drawButton(renderedWindow, usedPlayButton, X_AXIS_FRAME_OF_BUTTONS_ORIGIN, Y_AXIS_FRAME_OF_PLAY_BUTTON_ORIGIN);
	buttons.drawButton(renderedWindow, usedSettingsButton, X_AXIS_FRAME_OF_BUTTONS_ORIGIN, Y_AXIS_FRAME_OF_SETTINGS_BUTTON_ORIGIN);
	buttons.drawButton(renderedWindow, usedScoreboardButton, X_AXIS_FRAME_OF_BUTTONS_ORIGIN, Y_AXIS_FRAME_OF_SCOREBOARD_BUTTON_ORIGIN);
	buttons.drawButton(renderedWindow, usedExitButton, X_AXIS_FRAME_OF_BUTTONS_ORIGIN, Y_AXIS_FRAME_OF_EXIT_BUTTON_ORIGIN);
}

void Game::showSettingsMenu()
{
	background.drawBackground(renderedWindow, "mainMenuBackground");
	showSettingsOptions();
}

void Game::showSettingsOptions()
{
	buttons.drawThinButton(renderedWindow, usedKeyboardThinButton, X_AXIS_FRAME_OF_THIN_KEYBOARD_BUTTON_ORIGIN, Y_AXIS_FRAME_OF_THIN_BUTTONS_ORIGIN);
	buttons.drawThinButton(renderedWindow, usedJoystickThinButton, X_AXIS_FRAME_OF_THIN_JOYSTICK_BUTTON_ORIGIN, Y_AXIS_FRAME_OF_THIN_BUTTONS_ORIGIN);
	buttons.drawThinButton(renderedWindow, usedMouseThinButton, X_AXIS_FRAME_OF_THIN_MOUSE_BUTTON_ORIGIN, Y_AXIS_FRAME_OF_THIN_BUTTONS_ORIGIN);
	buttons.drawButton(renderedWindow, usedBackButton, X_AXIS_FRAME_OF_BUTTONS_ORIGIN, Y_AXIS_FRAME_OF_BACK_BUTTON_ORIGIN);
	settings.showSettingTexts(renderedWindow);
	settings.drawUnderVolumeSlider(renderedWindow);
	settings.drawVolumeSlider(renderedWindow);
}

void Game::showScoreboardMenu()
{
	background.drawBackground(renderedWindow, "mainMenuBackground");
	buttons.drawButton(renderedWindow, usedBackButton, X_AXIS_FRAME_OF_BUTTONS_ORIGIN, Y_AXIS_FRAME_OF_BACK_BUTTON_ORIGIN);
	if(!scoreboardOpened)
	{
		scoreboardOpened = true;
		scoreAndScoreboard.readScoreboardTXT();
	}
	scoreAndScoreboard.drawScoreboard(renderedWindow);

}

void Game::showGameplay()
{
	background.drawBackground(renderedWindow, "gameplayBackground");
	moveManagement();
	scoreManagement();
}

void Game::moveManagement()
{
	if(!FPS_TimeCounterBool)
	{
		timerForFPSCounter = timeMeasurement.returnExactTimeInNanoseconds();
		FPS_TimeCounterBool = true;
	}
	if(timeMeasurement.calculateElapsedTimeFromValueInMiliseconds(timerForFPSCounter)>16)
	{
		FPS_TimeCounterBool = false;
		FPS_Counter = timeMeasurement.returnBasicFPS_Counter(timerForFPSCounter);
		if(controlType == settings.MOUSE)
		{
			mouseMoveForGameplay();
		}
		createCatMovement();
		createObstaclesMovement();
		collisionDetected=objects.checkCollision(windowResolutionWidth, windowResolutionHeight);
		isCollisionDetected();
	}
	objects.drawCat(renderedWindow, objects);
	objects.drawObstacle(renderedWindow, *obstacle1,  windowResolutionHeight);
	objects.drawObstacle(renderedWindow, *obstacle2,  windowResolutionHeight);
	objects.drawObstacle(renderedWindow, *obstacle3,  windowResolutionHeight);

}

void Game::scoreManagement()
{
	if(pointIncrementEvent)
	{
		pointIncrementEvent = false;
		actualScore++;
	}
	scoreAndScoreboard.showScore(renderedWindow, actualScore);
}

void Game::createCatMovement()
{
	objects.calculateCatMove(windowResolutionWidth, windowResolutionHeight, catPixelJumpRight,
			catPixelJumpLeft, catPixelJumpDown, catPixelJumpUp);
}

void Game::createObstaclesMovement()
{
	if(obstacle1->X_PositionOfPipe<windowResolutionWidth/2 && !randomizedObstacle2)
	{
		objects.initializeObstacle(obstacle2, windowResolutionWidth, windowResolutionHeight);
		randomizedObstacle1=true;
		randomizedObstacle2=true;
		randomizedObstacle3=false;
		pointIncrementEvent = true;
	}

	if(obstacle2->X_PositionOfPipe<windowResolutionWidth/2 && !randomizedObstacle3)
	{
		objects.initializeObstacle(obstacle3, windowResolutionWidth, windowResolutionHeight);
		randomizedObstacle1=false;
		randomizedObstacle2=true;
		randomizedObstacle3=true;
		pointIncrementEvent = true;
	}

	if(obstacle3->X_PositionOfPipe<windowResolutionWidth/2 && !randomizedObstacle1)
	{
		objects.initializeObstacle(obstacle1, windowResolutionWidth, windowResolutionHeight);
		randomizedObstacle1=true;
		randomizedObstacle2=false;
		randomizedObstacle3=true;
		pointIncrementEvent = true;
	}

	objects.calculateMoveObstacle(obstacle1, BASIC_OBSTACLE_MODIFICATOR_Y/FPS_Counter);
	objects.calculateMoveObstacle(obstacle2, BASIC_OBSTACLE_MODIFICATOR_Y/FPS_Counter);
	objects.calculateMoveObstacle(obstacle3, BASIC_OBSTACLE_MODIFICATOR_Y/FPS_Counter);
}

void Game::isCollisionDetected()
{
	if(collisionDetected)
	{
		collisionDetected=false;
		gameplayState=false;
		gameOverState=true;

		catPositionNeedsInitialization=true;
		obstaclePositionNeedsInitialization=true;
		randomizedObstacle1=false;
		randomizedObstacle2=false;
		randomizedObstacle3=false;

		catPixelJumpRight=0;
		catPixelJumpLeft=0;
		catPixelJumpUp=0;
		catPixelJumpDown=0;
	}
}

void Game::mouseMoveForGameplay()
{
	if(objects.returnCatPositionX()<sf::Mouse::getPosition(*renderedWindow).x)
	{
		if(sf::Mouse::getPosition(*renderedWindow).x-objects.returnCatPositionX()>50)
		{
			catPixelJumpRight=BASIC_SECOND_MODIFICATOR_Y/FPS_Counter;
		}
		else
		{
			catPixelJumpRight=BASIC_SECOND_MODIFICATOR_Y/FPS_Counter*(sf::Mouse::getPosition(*renderedWindow).x-objects.returnCatPositionX())/50;
		}
		catPixelJumpLeft=0;

	}

	if(objects.returnCatPositionX()>sf::Mouse::getPosition(*renderedWindow).x)
	{
		catPixelJumpRight=0;
		if(objects.returnCatPositionX()-sf::Mouse::getPosition(*renderedWindow).x>50)
		{
			catPixelJumpLeft=BASIC_SECOND_MODIFICATOR_Y/FPS_Counter;
		}
		else
		{
			catPixelJumpLeft=BASIC_SECOND_MODIFICATOR_Y/FPS_Counter*(objects.returnCatPositionX()-sf::Mouse::getPosition(*renderedWindow).x)/50;
		}

	}
	if(objects.returnCatPositionX()==sf::Mouse::getPosition(*renderedWindow).x)
	{
		catPixelJumpRight=0;
		catPixelJumpLeft=0;
	}

	if(objects.returnCatPositionY()<sf::Mouse::getPosition(*renderedWindow).y)
	{
		if(sf::Mouse::getPosition(*renderedWindow).y-objects.returnCatPositionY()>50)
		{
			catPixelJumpDown=BASIC_SECOND_MODIFICATOR_X/FPS_Counter;
		}
		else
		{
			catPixelJumpDown=BASIC_SECOND_MODIFICATOR_X/FPS_Counter*(sf::Mouse::getPosition(*renderedWindow).y-objects.returnCatPositionY())/50;
		}
		catPixelJumpUp=0;
	}

	if(objects.returnCatPositionY()>sf::Mouse::getPosition(*renderedWindow).y)
	{
		catPixelJumpDown=0;
		if(objects.returnCatPositionY()-sf::Mouse::getPosition(*renderedWindow).y>50)
		{
			catPixelJumpUp=BASIC_SECOND_MODIFICATOR_X/FPS_Counter;
		}
		else
		{
			catPixelJumpUp=BASIC_SECOND_MODIFICATOR_X/FPS_Counter*(objects.returnCatPositionY()-sf::Mouse::getPosition(*renderedWindow).y)/50;
		}
	}
	if(objects.returnCatPositionY()==sf::Mouse::getPosition(*renderedWindow).y)
	{
		catPixelJumpDown=0;
		catPixelJumpUp=0;
	}
}

void Game::showPause()
{
	background.drawBackground(renderedWindow, "pauseBackground");
	FPS_TimeCounterBool = false;
	showPauseButtons();
}

void Game::showPauseButtons()
{
	buttons.drawButton(renderedWindow, usedResumeButton, X_AXIS_FRAME_OF_BUTTONS_ORIGIN, Y_AXIS_FRAME_OF_RESUME_BUTTON_ORIGIN);
	buttons.drawButton(renderedWindow, usedExitButton, X_AXIS_FRAME_OF_BUTTONS_ORIGIN, Y_AXIS_FRAME_OF_EXIT_BUTTON_ORIGIN);
}

void Game::showGameOver()
{
	if(!scoreboardOpened)
	{
		scoreboardOpened = true;
		scoreAndScoreboard.readScoreboardTXT();
		scoreAndScoreboard.checkIfBestScoreAchieved(actualScore);
	}
	actualScore=0;
	background.drawBackground(renderedWindow, "gameOverBackground");
	if(!gameOverHappeningBool)
		{
			timerForGameOverHappening = timeMeasurement.returnExactTimeInNanoseconds();
			gameOverHappeningBool = true;
		}
		if((timeMeasurement.calculateElapsedTimeFromValueInMiliseconds(timerForFPSCounter) > timeOfGameOverMusicEffectInMiliseconds))
		{
			gameOverState=false;
			mainMenuState=true;
			gameOverHappeningBool = false;
		}
}

void Game::completeEventsList()
{
	sf::Event event;
	while (renderedWindow->pollEvent(event))
	{
		closeGameEvent(event);
		if(mainMenuState && !settingsState && !scoreboardState)
		{
			mouseEventsForMainMenuState(event);
		}
		if(mainMenuState && settingsState && !scoreboardState)
		{
			mouseEventsForSettingsState(event);
		}
		if(mainMenuState && !settingsState && scoreboardState)
		{
			mouseEventsForScoreboardsState(event);
		}
		if(gameplayState && !pauseState)
		{
			if(controlType == settings.KEYBOARD)
			{
				keyboardMoveForGameplay(event);
			}
			if(controlType == settings.JOYSTICK)
			{
				joystickMoveForGameplay(event);
			}
			keyboardEventsForGameplay(event);
		}
		else if(pauseState)
		{
			keyboardEventsForPauseState(event);
			mouseEventsForPauseState(event);
		}
	}
}

void Game::closeGameEvent(sf::Event event)
{
	if (event.type == sf::Event::Closed)
	{
		renderedWindow->close();
	}
}

void Game::mouseEventsForMainMenuState(sf::Event event)
{
	if (event.type == sf::Event::MouseMoved)
	{
		buttons.checkIfButtonIsHighlighted(&usedPlayButton, &playHighlighted, event,
				X_AXIS_FRAME_OF_BUTTONS_ORIGIN, Y_AXIS_FRAME_OF_PLAY_BUTTON_ORIGIN);
		buttons.checkIfButtonIsHighlighted(&usedSettingsButton, &settingsHighlighted, event,
				X_AXIS_FRAME_OF_BUTTONS_ORIGIN, Y_AXIS_FRAME_OF_SETTINGS_BUTTON_ORIGIN);
		buttons.checkIfButtonIsHighlighted(&usedScoreboardButton, &scoreboardHighlighted, event,
				X_AXIS_FRAME_OF_BUTTONS_ORIGIN, Y_AXIS_FRAME_OF_SCOREBOARD_BUTTON_ORIGIN);
		buttons.checkIfButtonIsHighlighted(&usedExitButton, &exitHighlighted, event,
				X_AXIS_FRAME_OF_BUTTONS_ORIGIN, Y_AXIS_FRAME_OF_EXIT_BUTTON_ORIGIN);
	}

	if (event.type == sf::Event::MouseButtonPressed)
	{
		buttons.checkIfButtonWasPressed(&playPressed, playHighlighted);
		buttons.checkIfButtonWasPressed(&settingsPressed, settingsHighlighted);
		buttons.checkIfButtonWasPressed(&scoreboardPressed, scoreboardHighlighted);
		buttons.checkIfButtonWasPressed(&exitPressed, exitHighlighted);
	}

	if (event.type == sf::Event::MouseButtonReleased)
	{
		checkIfPlayButtonWasProperlyReleased();
		checkIfSettingsButtonWasProperlyReleased();
		checkIfScoreboardButtonWasProperlyReleased();
		checkIfExitButtonWasProperlyReleased();
	}
}

void Game::checkIfPlayButtonWasProperlyReleased()
{
	if(playPressed==true && playHighlighted==true)
	{
		playPressed=false;
		mainMenuState=false;
		gameplayState=true;
	}
}

void Game::checkIfSettingsButtonWasProperlyReleased()
{
	if(settingsPressed==true && settingsHighlighted==true)
	{
		settingsPressed=false;
		settingsState=true;
	}
}

void Game::checkIfScoreboardButtonWasProperlyReleased()
{
	if(scoreboardPressed==true && scoreboardHighlighted==true)
	{
		scoreboardPressed=false;
		scoreboardState=true;
	}
}

void Game::checkIfExitButtonWasProperlyReleased()
{
	if(exitPressed==true && exitHighlighted==true)
	{
		renderedWindow->close();
	}
}

void Game::mouseEventsForSettingsState(sf::Event event)
{
	if (event.type == sf::Event::MouseMoved)
	{
		buttons.checkIfButtonIsHighlighted(&usedBackButton, &backHighlighted, event,
				X_AXIS_FRAME_OF_BUTTONS_ORIGIN, Y_AXIS_FRAME_OF_BACK_BUTTON_ORIGIN);
		buttons.checkIfThinButtonIsHighlighted(&usedKeyboardThinButton, &keyboardHighlighted, event,
				X_AXIS_FRAME_OF_THIN_KEYBOARD_BUTTON_ORIGIN, Y_AXIS_FRAME_OF_THIN_BUTTONS_ORIGIN);
		buttons.checkIfThinButtonIsHighlighted(&usedJoystickThinButton, &joystickHighlighted, event,
				X_AXIS_FRAME_OF_THIN_JOYSTICK_BUTTON_ORIGIN, Y_AXIS_FRAME_OF_THIN_BUTTONS_ORIGIN);
		buttons.checkIfThinButtonIsHighlighted(&usedMouseThinButton, &mouseHighlighted, event,
				X_AXIS_FRAME_OF_THIN_MOUSE_BUTTON_ORIGIN, Y_AXIS_FRAME_OF_THIN_BUTTONS_ORIGIN);

		settings.checkIfVolumeButtonIsHighlighted(&volumeHighlighted, event);
	}
	if (event.type == sf::Event::MouseButtonPressed)
	{
		buttons.checkIfButtonWasPressed(&backPressed, backHighlighted);
		buttons.checkIfButtonWasPressed(&keyboardPressed, keyboardHighlighted);
		buttons.checkIfButtonWasPressed(&joystickPressed, joystickHighlighted);
		buttons.checkIfButtonWasPressed(&mousePressed, mouseHighlighted);

		settings.checkIfVolumeButtonWasPressed(&volumePressed, volumeHighlighted);
	}

	if (event.type == sf::Event::MouseButtonReleased)
	{
		checkIfBackButtonWasProperlyReleased();
		checkIfKeyboardButtonWasProperlyReleased();
		checkIfJoystickButtonWasProperlyReleased();
		checkIfMouseButtonWasProperlyReleased();

		checkIfVolumeButtonWasProperlyReleased();
	}
	buttons.setProperControlColor(&usedKeyboardThinButton, &usedMouseThinButton, &usedJoystickThinButton, controlType);

	if (event.type == sf::Event::MouseMoved && volumePressed)
	{
		settings.moveVolumeSlider(event);
	}
}

void Game::checkIfBackButtonWasProperlyReleased()
{
	if(backPressed==true && backHighlighted==true)
	{
		backPressed=false;
		settingsState = false;
		scoreboardState = false;
	}
}

void Game::checkIfKeyboardButtonWasProperlyReleased()
{
	if(keyboardPressed==true && keyboardHighlighted==true)
	{
		keyboardPressed=false;
		controlType = settings.KEYBOARD;
	}
}

void Game::checkIfJoystickButtonWasProperlyReleased()
{
	if(joystickPressed==true && joystickHighlighted==true)
	{
		joystickPressed=false;
		controlType = settings.JOYSTICK;
	}
}

void Game::checkIfMouseButtonWasProperlyReleased()
{

	if(mousePressed==true && mouseHighlighted==true)
	{
		mousePressed=false;
		controlType = settings.MOUSE;
	}
}

void Game::checkIfVolumeButtonWasProperlyReleased()
{

	if(volumePressed==true)
	{
		volumePressed=false;
	}
}

void Game::mouseEventsForScoreboardsState(sf::Event event)
{
	if (event.type == sf::Event::MouseMoved)
	{
		buttons.checkIfButtonIsHighlighted(&usedBackButton, &backHighlighted, event,
				X_AXIS_FRAME_OF_BUTTONS_ORIGIN, Y_AXIS_FRAME_OF_BACK_BUTTON_ORIGIN);
	}

	if (event.type == sf::Event::MouseButtonPressed)
	{
		buttons.checkIfButtonWasPressed(&backPressed, backHighlighted);
	}

	if (event.type == sf::Event::MouseButtonReleased)
	{
		checkIfBackButtonWasProperlyReleased();
	}
}

void Game::keyboardEventsForGameplay(sf::Event event)
{
	if (event.type == sf::Event::EventType::KeyPressed )
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			pauseState = true;
		}
	}
}

void Game::keyboardMoveForGameplay(sf::Event event)
{
	if (event.type == sf::Event::EventType::KeyPressed )
	{
		if (event.key.code == sf::Keyboard::D)
		{
			catPixelJumpRight=BASIC_SECOND_MODIFICATOR_Y/FPS_Counter;
		}

		if (event.key.code == sf::Keyboard::A)
		{
			catPixelJumpLeft=BASIC_SECOND_MODIFICATOR_Y/FPS_Counter;
		}

		if (event.key.code == sf::Keyboard::S)
		{
			catPixelJumpDown=BASIC_SECOND_MODIFICATOR_X/FPS_Counter;
		}

		if (event.key.code == sf::Keyboard::W)
		{
			catPixelJumpUp=BASIC_SECOND_MODIFICATOR_X/FPS_Counter;
		}
		if (event.key.code == sf::Keyboard::Escape)
		{
			pauseState = true;
		}
	}

	if (event.type == sf::Event::EventType::KeyReleased )
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

void Game::joystickMoveForGameplay(sf::Event event)
{
	catPixelJumpRight=BASIC_SECOND_MODIFICATOR_Y/FPS_Counter* sf::Joystick::getAxisPosition(0, sf::Joystick::X)/100;
	catPixelJumpLeft=0;
	catPixelJumpDown=BASIC_SECOND_MODIFICATOR_X/FPS_Counter* sf::Joystick::getAxisPosition(0, sf::Joystick::Y)/100;
	catPixelJumpUp=0;
}

void Game::keyboardEventsForPauseState(sf::Event event)
{
	if (event.type == sf::Event::EventType::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				pauseState = false;
			}
		}
}

void Game::mouseEventsForPauseState(sf::Event event)
{
	if (event.type == sf::Event::MouseMoved)
	{
		buttons.checkIfButtonIsHighlighted(&usedResumeButton, &resumeHighlighted, event,
				X_AXIS_FRAME_OF_BUTTONS_ORIGIN, Y_AXIS_FRAME_OF_RESUME_BUTTON_ORIGIN);
		buttons.checkIfButtonIsHighlighted(&usedExitButton, &exitHighlighted, event,
				X_AXIS_FRAME_OF_BUTTONS_ORIGIN, Y_AXIS_FRAME_OF_EXIT_BUTTON_ORIGIN);
	}

	if (event.type == sf::Event::MouseButtonPressed)
	{
		buttons.checkIfButtonWasPressed(&resumePressed, resumeHighlighted);
		buttons.checkIfButtonWasPressed(&exitPressed, exitHighlighted);
	}

	if (event.type == sf::Event::MouseButtonReleased)
	{
		checkIfResumeButtonWasProperlyReleased();
		checkIfExitButtonWasProperlyReleased();
	}
}

void Game::checkIfResumeButtonWasProperlyReleased()
{
	if(resumePressed==true && resumeHighlighted==true)
	{
		gameplayState = true;
		pauseState = false;
	}
}

void Game::checkTime()
{
	auto actualTime = timeMeasurement.returnExactTimeInNanoseconds();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(actualTime-startTimeOfGameInNanoseconds);
	std::cout<<elapsedTime.count()<<"\n"; //temporary function to debug, to delete later
}


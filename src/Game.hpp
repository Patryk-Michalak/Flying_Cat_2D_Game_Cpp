#ifndef GAME_HPP_
#define GAME_HPP_

#include "TimeMeasurement.hpp"
#include "Window.hpp"
#include "Background.hpp"
#include "Music.hpp"
#include "Buttons.hpp"
#include "Objects.hpp"
#include "ScoreAndScoreboard.hpp"
#include "Settings.hpp"

class Game
{
private:
	TimeMeasurement timeMeasurement;
	timeValueTypeInNanoseconds startTimeOfGameInNanoseconds;

	Window window;
	sf::RenderWindow * renderedWindow = window.returnRenderedWindow();
	int windowResolutionWidth = window.returnWindowResolutionWidth();
	int windowResolutionHeight = window.returnWindowResolutionHeight();

	bool introductionState = true;
	bool mainMenuState = false;
	bool settingsState = false;
	bool scoreboardState = false;
	bool gameplayState = false;
	bool pauseState = false;
	bool gameOverState = false;
	const int TIME_OF_INTRO_DURATION_IN_MILISECONDS = 2000;

	Background background;
	Music music;

	Buttons buttons;
	sf::Text usedPlayButton = buttons.getPlayButton();
	sf::Text usedSettingsButton = buttons.getSettingsButton();
	sf::Text usedScoreboardButton = buttons.getScoreboardButton();
	sf::Text usedExitButton = buttons.getExitButton();
	sf::Text usedBackButton = buttons.getBackButton();
	sf::Text usedResumeButton = buttons.getResumeButton();

	sf::Text usedKeyboardThinButton = buttons.getKeyboardThinButton();
	sf::Text usedJoystickThinButton = buttons.getJoystickThinButton();
	sf::Text usedMouseThinButton = buttons.getMouseThinButton();

	const int X_AXIS_FRAME_OF_BUTTONS_ORIGIN = windowResolutionWidth/2-buttons.getButtonFrameWidth()/2;
	const int Y_AXIS_FRAME_OF_PLAY_BUTTON_ORIGIN = buttons.getY_AxisTextOfPlayButtonOrigin();
	const int Y_AXIS_FRAME_OF_SETTINGS_BUTTON_ORIGIN = buttons.getY_AxisTextOfSettingsButtonOrigin();
	const int Y_AXIS_FRAME_OF_SCOREBOARD_BUTTON_ORIGIN = buttons.getY_AxisTextOfScoreboardButtonOrigin();
	const int Y_AXIS_FRAME_OF_EXIT_BUTTON_ORIGIN = buttons.getY_AxisTextOfExitButtonOrigin();
	const int Y_AXIS_FRAME_OF_RESUME_BUTTON_ORIGIN = buttons.getY_AxisTextOfResumeButtonOrigin();
	const int Y_AXIS_FRAME_OF_BACK_BUTTON_ORIGIN = buttons.getY_AxisTextOfExitButtonOrigin();

	const int X_AXIS_FRAME_OF_THIN_KEYBOARD_BUTTON_ORIGIN = buttons.getX_AxisTextOfThinKeyboardButtonOrigin()-10;
	const int X_AXIS_FRAME_OF_THIN_JOYSTICK_BUTTON_ORIGIN = buttons.getX_AxisTextOfThinJoystickButtonOrigin()-10;
	const int X_AXIS_FRAME_OF_THIN_MOUSE_BUTTON_ORIGIN = buttons.getX_AxisTextOfThinMouseButtonOrigin()-10;
	const int Y_AXIS_FRAME_OF_THIN_BUTTONS_ORIGIN = buttons.getY_AxisTextOfThinButtonsOrigin()-30;

	Settings settings;
	Settings::ControlType controlType = settings.KEYBOARD;

	Objects objects;
	timeValueTypeInNanoseconds timerForFPSCounter;
	Obstacles * obstacle1 = objects.getObstacle1();
	Obstacles * obstacle2 = objects.getObstacle2();
	Obstacles * obstacle3 = objects.getObstacle3();

	bool catPositionNeedsInitialization = true;
	bool obstaclePositionNeedsInitialization = true;
	bool firstObstacleWasInitialized = false;
	bool randomizedObstacle1 = false;
	bool randomizedObstacle2 = false;
	bool randomizedObstacle3 = false;

	bool FPS_TimeCounterBool = false;
	int FPS_Counter = 0;

	float catPixelJumpRight = 0;
	float catPixelJumpLeft = 0;
	float catPixelJumpDown = 0;
	float catPixelJumpUp = 0;

	const int BASIC_SECOND_MODIFICATOR_X = 3072;
	const int BASIC_SECOND_MODIFICATOR_Y = 5464;
	const int BASIC_OBSTACLE_MODIFICATOR_Y = 3900;

	bool collisionDetected = false;

	ScoreAndScoreboard scoreAndScoreboard;
	int actualScore = 0;
	bool pointIncrementEvent = false;

	bool gameOverHappeningBool = false;
	timeValueTypeInNanoseconds timerForGameOverHappening;
	const int timeOfGameOverMusicEffectInMiliseconds = 4000;

	bool playHighlighted = false;
	bool settingsHighlighted = false;
	bool scoreboardHighlighted = false;
	bool exitHighlighted = false;
	bool backHighlighted = false;
	bool keyboardHighlighted = false;
	bool mouseHighlighted = false;
	bool joystickHighlighted = false;
	bool resumeHighlighted = false;
	bool volumeHighlighted = false;

	bool playPressed = false;
	bool settingsPressed = false;
	bool scoreboardPressed = false;
	bool exitPressed = false;
	bool backPressed = false;
	bool keyboardPressed = false;
	bool mousePressed = false;
	bool joystickPressed = false;
	bool resumePressed = false;
	bool volumePressed = false;

	bool scoreboardOpened = false;

public:
	Game();
	virtual ~Game();

	void runGame();
	void displayData();
	void defineLogicState();
	void showIntroduction();
	void showMainMenu();
	void showMainMenuButtons();
	void chooseMusic(enum Music::MusicInGameLogicState musicInGameLogicState);
	void showSettingsMenu();
	void showSettingsOptions();
	void showScoreboardMenu();
	void showGameplay();
	void moveManagement();
	void scoreManagement();
	void createCatMovement();
	void createObstaclesMovement();
	void isCollisionDetected();
	void mouseMoveForGameplay();
	void showPause();
	void showPauseButtons();
	void showGameOver();

	void completeEventsList();
	void closeGameEvent(sf::Event);
	void keyboardEventsForPauseState(sf::Event event);
	void mouseEventsForMainMenuState(sf::Event event);
	void mouseEventsForSettingsState(sf::Event event);
	void checkIfPlayButtonWasProperlyReleased();
	void checkIfSettingsButtonWasProperlyReleased();
	void checkIfScoreboardButtonWasProperlyReleased();
	void checkIfExitButtonWasProperlyReleased();
	void checkIfBackButtonWasProperlyReleased();
	void checkIfKeyboardButtonWasProperlyReleased();
	void checkIfJoystickButtonWasProperlyReleased();
	void checkIfMouseButtonWasProperlyReleased();
	void checkIfVolumeButtonWasProperlyReleased();
	void mouseEventsForScoreboardsState(sf::Event event);
	void keyboardEventsForGameplay(sf::Event event);
	void keyboardMoveForGameplay(sf::Event event);
	void joystickMoveForGameplay(sf::Event event);
	void mouseEventsForPauseState(sf::Event event);
	void checkIfResumeButtonWasProperlyReleased();
	void checkTime();


};

#endif

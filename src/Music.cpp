#include "Music.hpp"
#include <iostream>

Music::Music()
{
	if (!mainMenuMusic.openFromFile("src/Music/alexander-nakarada-chase.ogg"))
	{
		std::cout<<"Error to load main menu song";
	}
	if (!gameplayMusic.openFromFile("src/Music/test.ogg"))
	{
		std::cout<<"Error to load gameplay song";
	}
	if (!gameOverMusic.openFromFile("src/Music/Sad_Trombone.ogg"))
	{
		std::cout<<"Error to load gameplay song";
	}
}

Music::~Music()
{
}

void Music::playMusic(enum Music::MusicInGameLogicState musicInGameLogicState)
{
	int status = statusOfPlayedMusic(musicInGameLogicState);
	if(status != MUSIC_PLAYING)
	{
		startPlayingMusic(musicInGameLogicState);
	}
}

int Music::statusOfPlayedMusic(enum Music::MusicInGameLogicState musicInGameLogicState)
{
	int status = 0;
	switch (musicInGameLogicState) {
		case MAIN_MENU:
			status = mainMenuMusic.getStatus();
			break;
		case GAMEPLAY:
			status = gameplayMusic.getStatus();
			break;
		case GAMEOVER:
			status = gameOverMusic.getStatus();
			break;
		default:
			break;
	}
	return status;
}

void Music::startPlayingMusic(Music::MusicInGameLogicState musicInGameLogicState)
{
	stopAllMusics();
	switch (musicInGameLogicState) {
		case MAIN_MENU:
			mainMenuMusic.setVolume(20);
			mainMenuMusic.play();
			break;
		case GAMEPLAY:
			gameplayMusic.setVolume(20);
			gameplayMusic.play();
			break;
		case GAMEOVER:
			gameOverMusic.setVolume(20);
			gameOverMusic.play();
			break;
		default:
			break;
	}
}

void Music::stopAllMusics()
{
	mainMenuMusic.stop();
	gameplayMusic.stop();
	gameOverMusic.stop();
}

void Music::setMusicVolume(Music::MusicInGameLogicState musicInGameLogicState, int soundVolume)
{
	switch (musicInGameLogicState) {
		case MAIN_MENU:
			mainMenuMusic.setVolume(soundVolume);
			break;
		case GAMEPLAY:
			gameplayMusic.setVolume(soundVolume);
			break;
		case GAMEOVER:
			gameOverMusic.setVolume(soundVolume);
			break;
		default:
			break;
	}
}


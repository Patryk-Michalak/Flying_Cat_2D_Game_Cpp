#ifndef MUSIC_HPP_
#define MUSIC_HPP_

#include <SFML/Audio.hpp>

class Music {
private:
	sf::Music mainMenuMusic;
	sf::Music gameplayMusic;
	sf::Music gameOverMusic;

	const int MUSIC_STOPPED = 0;
	const int MUSIC_PAUSED = 1;
	const int MUSIC_PLAYING = 2;
public:
	Music();
	virtual ~Music();

	enum MusicStatus
	{
		STOPPED,
		PAUSED,
		PLAYING
	};

	enum MusicInGameLogicState
	{
		MAIN_MENU,
		GAMEPLAY,
		GAMEOVER
	};

	void playMusic(enum Music::MusicInGameLogicState musicInGameLogicState);
	int statusOfPlayedMusic(enum Music::MusicInGameLogicState musicInGameLogicState);
	void startPlayingMusic(enum Music::MusicInGameLogicState musicInGameLogicState);
	void stopAllMusics();
	void setMusicVolume(Music::MusicInGameLogicState musicInGameLogicState, int soundVolume);
};

#endif

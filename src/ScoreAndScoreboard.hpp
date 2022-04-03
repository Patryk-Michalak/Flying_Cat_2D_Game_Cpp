#ifndef SCOREANDSCOREBOARD_HPP_
#define SCOREANDSCOREBOARD_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

class ScoreAndScoreboard {
private:

	sf::Font font;
	sf::Text scoreText;

	sf::Text scoreFirst;
	sf::Text scoreSecond;
	sf::Text scoreThird;

	int lastScore = 0;
	const int CHARACTER_SIZE = 30;
	const int POSITION_X = 1150;
	const int POSITION_Y = 15;

	std::string scoreboardFirstPosition;
	std::string scoreboardSecondPosition;
	std::string scoreboardThirdPosition;

public:
	ScoreAndScoreboard();
	~ScoreAndScoreboard();

	void showScore(sf::RenderWindow * renderedWindow, int actualScore);
	void readScoreboardTXT();
	void drawScoreboard(sf::RenderWindow * renderedWindow);
	void checkIfBestScoreAchieved(int actualScore);

};

#endif

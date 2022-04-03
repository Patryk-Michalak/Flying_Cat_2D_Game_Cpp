#include "ScoreAndScoreboard.hpp"

ScoreAndScoreboard::ScoreAndScoreboard()
{
	font.loadFromFile("src/Fonts/Montserrat-Regular.ttf");
	scoreText.setFont(font);
	scoreText.setCharacterSize(CHARACTER_SIZE);
	scoreText.setPosition(POSITION_X, POSITION_Y);
	scoreText.setFillColor(sf::Color::Black);
	scoreText.setString("Score: 0");
	readScoreboardTXT();

	scoreFirst.setFont(font);
	scoreFirst.setCharacterSize(CHARACTER_SIZE);
	scoreFirst.setPosition(450,250);
	scoreFirst.setFillColor(sf::Color::Black);

	scoreSecond.setFont(font);
	scoreSecond.setCharacterSize(CHARACTER_SIZE);
	scoreSecond.setPosition(450,300);
	scoreSecond.setFillColor(sf::Color::Black);

	scoreThird.setFont(font);
	scoreThird.setCharacterSize(CHARACTER_SIZE);
	scoreThird.setPosition(450,350);
	scoreThird.setFillColor(sf::Color::Black);

}

ScoreAndScoreboard::~ScoreAndScoreboard()
{
}

void ScoreAndScoreboard::showScore(sf::RenderWindow * renderedWindow, int actualScore)
{
	lastScore=actualScore;
	std::string scoreString = "Score: ";
	std::stringstream  stringStreamOfActualScore;
	stringStreamOfActualScore << actualScore;
	scoreString = scoreString + stringStreamOfActualScore.str();
	scoreText.setString(scoreString);
	renderedWindow->draw(scoreText);
}

void ScoreAndScoreboard::readScoreboardTXT()
{
	std::ifstream scoreboardTXT ("src/Scoreboard.txt");
	std::string lineOfText;
	if(scoreboardTXT.is_open())
	{
		bool readLine = bool(getline(scoreboardTXT, lineOfText));
		if(!readLine)
		{
			scoreboardFirstPosition = "---";
			scoreboardSecondPosition = "---";
			scoreboardThirdPosition = "---";
		}
		else
		{
			scoreboardFirstPosition = lineOfText;
			bool readLine2 = bool(getline(scoreboardTXT, lineOfText));
			if(!readLine2)
			{
				scoreboardSecondPosition = "---";
				scoreboardThirdPosition = "---";
			}
			else
			{
				scoreboardSecondPosition = lineOfText;
				bool readLine3 = bool(getline(scoreboardTXT, lineOfText));
				if(!readLine3)
				{
					scoreboardThirdPosition = "---";
				}
				else
				{
					scoreboardThirdPosition = lineOfText;
				}
			}
		}
		scoreboardTXT.close();
	}
	else
	{
		std::cout<<"unable to open file\n";
	}
	std::cout<<scoreboardFirstPosition<<"\n"<<scoreboardSecondPosition<<"\n"<<scoreboardThirdPosition<<"\n";
}



void ScoreAndScoreboard::drawScoreboard(sf::RenderWindow * renderedWindow)
{

	scoreFirst.setString(scoreboardFirstPosition);
	scoreSecond.setString(scoreboardSecondPosition);
	scoreThird.setString(scoreboardThirdPosition);


	renderedWindow->draw(scoreFirst);
	renderedWindow->draw(scoreSecond);
	renderedWindow->draw(scoreThird);
}

void ScoreAndScoreboard::checkIfBestScoreAchieved(int actualScore)
{
	int firstStringLength = scoreboardFirstPosition.length();
	int secondStringLength = scoreboardSecondPosition.length();
	int thirdStringLength = scoreboardThirdPosition.length();
	int separatorPosition = firstStringLength;
	std::string scoreboardFirstPositionName;
	std::string scoreboardFirstPositionResult;
	std::string scoreboardSecondPositionName;
	std::string scoreboardSecondPositionResult;
	std::string scoreboardThirdPositionName;
	std::string scoreboardThirdPositionResult;

	for(int i=0; i<firstStringLength-1;i++)
	{
		if(scoreboardFirstPosition[i]==':' && scoreboardFirstPosition[i+1]==' ')
		{
			separatorPosition = i;
			break;
		}
	}
	for(int i=0; i<firstStringLength;i++)
	{
		if(i<separatorPosition)
		{
			scoreboardFirstPositionName += scoreboardFirstPosition[i];
		}
		else if(i>separatorPosition+1)
		{
			scoreboardFirstPositionResult += scoreboardFirstPosition[i];
		}
	}

	separatorPosition = secondStringLength;
	for(int i=0; i<secondStringLength-1;i++)
	{
		if(scoreboardSecondPosition[i]==':' && scoreboardSecondPosition[i+1]==' ')
		{
			separatorPosition = i;
			break;
		}
	}
	for(int i=0; i<secondStringLength;i++)
	{
		if(i<separatorPosition)
		{
			scoreboardSecondPositionName += scoreboardSecondPosition[i];
		}
		else if(i>separatorPosition+1)
		{
			scoreboardSecondPositionResult += scoreboardSecondPosition[i];
		}
	}

	separatorPosition = thirdStringLength;
	for(int i=0; i<thirdStringLength-1;i++)
	{
		if(scoreboardThirdPosition[i]==':' && scoreboardThirdPosition[i+1]==' ')
		{
			separatorPosition = i;
			break;
		}
	}
	for(int i=0; i<thirdStringLength;i++)
	{
		if(i<separatorPosition)
		{
			scoreboardThirdPositionName += scoreboardThirdPosition[i];
		}
		else if(i>separatorPosition+1)
		{
			scoreboardThirdPositionResult += scoreboardThirdPosition[i];
		}
	}

	std::cout<<scoreboardFirstPositionName<<"\n";
	std::cout<<scoreboardFirstPositionResult<<"\n";
	std::cout<<scoreboardSecondPositionName<<"\n";
	std::cout<<scoreboardSecondPositionResult<<"\n";
	std::cout<<scoreboardThirdPositionName<<"\n";
	std::cout<<scoreboardThirdPositionResult<<"\n";
	std::cout<<"Here\n";
	if(scoreboardThirdPositionResult == "")
	{
		std::cout<<"True\n";
	}
}

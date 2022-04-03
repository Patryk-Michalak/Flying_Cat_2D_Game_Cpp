#include "TimeMeasurement.hpp"

TimeMeasurement::TimeMeasurement()
{
}

TimeMeasurement::~TimeMeasurement()
{
}

timeValueTypeInNanoseconds TimeMeasurement::returnExactTimeInNanoseconds()
{
	return std::chrono::high_resolution_clock::now();
}

int TimeMeasurement::calculateElapsedTimeFromValueInMiliseconds(timeValueTypeInNanoseconds entryTime)
{
	auto actualTime = returnExactTimeInNanoseconds();
	auto elapsedTimeInMiliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(actualTime-entryTime);
	return elapsedTimeInMiliseconds.count();
}

int TimeMeasurement::returnBasicFPS_Counter(timeValueTypeInNanoseconds entryTime)
{
	return (int)(1000.0/calculateElapsedTimeFromValueInMiliseconds(entryTime));
}

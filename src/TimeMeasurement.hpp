#ifndef TIMEMEASUREMENT_HPP_
#define TIMEMEASUREMENT_HPP_

#include <chrono>
using timeValueTypeInNanoseconds = std::chrono::high_resolution_clock::time_point;

class TimeMeasurement {
private:

public:
	TimeMeasurement();
	virtual ~TimeMeasurement();

	timeValueTypeInNanoseconds returnExactTimeInNanoseconds();
	int calculateElapsedTimeFromValueInMiliseconds(timeValueTypeInNanoseconds entryTime);
	int returnBasicFPS_Counter(timeValueTypeInNanoseconds entryTime);
};

#endif

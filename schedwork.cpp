#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool isValid(const AvailabilityMatrix& avail, size_t day, Worker_T worker);
bool backtrackSch(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, DailySchedule& curr, std::vector<size_t> numShiftsWorked,size_t day);
// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched //end result. finalized with true/ return statement
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
		size_t numWorkers = avail[0].size();
		size_t numDays = avail.size();
		std::vector<size_t> numShiftsWorked(numWorkers,0);
		DailySchedule curr(numDays);
		//cout << curr.size();
		bool result = backtrackSch(avail, dailyNeed, maxShifts, sched, curr, numShiftsWorked, 0);
		cout << curr[0].size();
		return result;
}

bool isValid(const AvailabilityMatrix& avail, size_t day, Worker_T worker) { //check if a day is valid for a worker to work (doesnt include num of shifts worked)
    return avail[day][worker];
}

bool backtrackSch(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, DailySchedule& curr, std::vector<size_t> numShiftsWorked,size_t day)
{
	size_t numWorkers = avail[0].size();
	size_t numDays = avail.size();
	//if at end of work week 
	if (day == numDays){
		sched = curr;
		return true;
	}
	size_t workersSched = 0;
	for (Worker_T w = 0; w < numWorkers; w++)
	{
		if (isValid(avail, day, w) && numShiftsWorked[w] < maxShifts)//if work day is valid and worker is not over booked attempt to add them to schedule
		{
			curr[day].push_back(w);
			numShiftsWorked[w]++;
			workersSched += 1;
			if (workersSched < dailyNeed)
				continue;
			if (backtrackSch(avail, dailyNeed, maxShifts, sched, curr, numShiftsWorked, day+1)) ///backtrace worker
				return true;
		}	
		if (!curr[day].empty()) 
			curr[day].pop_back();//if fails then they are removed and others are tried
		numShiftsWorked[w] = numShiftsWorked[w] - 1;
	}
	return false;
}

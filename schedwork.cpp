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
bool assignment(const AvailabilityMatrix& avail,
		const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, 
		std::vector<size_t>& shiftCount, 
		size_t day, size_t slot);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0){
        return false;
    }
    sched.clear();
    // Add your code below
	if(avail.empty() || avail[0].empty()) return false; 

	size_t days = avail.size();
	size_t employees = avail[0].size();

	sched.assign(days, std::vector<Worker_T>());
	std::vector<size_t> shiftCount(employees, 0);


	return assignment(avail, dailyNeed, maxShifts, sched, shiftCount, 0, 0);





}
bool assignment(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, std::vector<size_t>& shiftCount, size_t day, size_t slot){
	if(day == avail.size()){
		return true; 
	}
	size_t employees = avail[0].size();
	// std::vector<Worker_T>& currentSchedule = sched[day];

	for(Worker_T i = 0; i < employees; ++i){
		if(!avail[day][i]) continue;
		if (shiftCount[i] >= maxShifts) continue;
		if(std::find(sched[day].begin(), sched[day].end(), i)!= sched[day].end()) continue;

		sched[day].push_back(i);
		shiftCount[i]++;

		bool right = false;
		if(sched[day].size() == dailyNeed){
			right = assignment(avail, dailyNeed, maxShifts, sched, shiftCount, day + 1, 0); 
		}
		else{
				right = assignment(avail, dailyNeed, maxShifts, sched, shiftCount, day, slot + 1); 
		}

		if (right) return true; 
		
		sched[day].pop_back();
		shiftCount[i]--; 
	}
	return false; 
}



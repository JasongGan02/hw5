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
bool recursion(size_t day, size_t worker, const AvailabilityMatrix& avail, const size_t dailyNeed, vector<int>& shiftCount, DailySchedule& sched, vector<bool>& workerAssignedToday) {
    if (day >= sched.size()) return true;

    if (worker == 0) {
        fill(workerAssignedToday.begin(), workerAssignedToday.end(), false); // Reset for new day
    }

    for (size_t w = 0; w < avail[day].size(); w++) 
    {
        if (avail[day][w] && shiftCount[w] > 0 && !workerAssignedToday[w]) 
        {
            sched[day][worker] = w;
            shiftCount[w]--;
            workerAssignedToday[w] = true;


            if (worker + 1 < dailyNeed) 
            {
                if (recursion(day, worker + 1, avail, dailyNeed, shiftCount, sched, workerAssignedToday)) return true;
            } 
            else 
            {
                vector<bool> newWorkerAssignedToday(avail[day].size(), false);
                if (recursion(day + 1, 0, avail, dailyNeed, shiftCount, sched, newWorkerAssignedToday)) return true;
            }

            // Backtrack
            shiftCount[w]++;
            workerAssignedToday[w] = false;
            sched[day][worker] = INVALID_ID;
        }
    }

    return false; // No valid assignment found
}



// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    vector<int> shiftCount(avail[0].size(), maxShifts);
    vector<bool> workerAssignedToday(avail[0].size(), false);
    size_t numDays = avail.size();
    sched.resize(numDays, vector<Worker_T>(dailyNeed, INVALID_ID));
    return recursion(0, 0, avail, dailyNeed, shiftCount, sched, workerAssignedToday);
}


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
bool dfs(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<size_t>& shiftCount, size_t slot);


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

    size_t numDays = avail.size();
    size_t numWorkers = avail[0].size();

    sched.resize(numDays, vector<Worker_T>(dailyNeed, INVALID_ID));
    vector<size_t>shiftCount(numWorkers, 0);

    bool result = dfs(avail, dailyNeed, maxShifts, sched, shiftCount, 0);
    return result;

}

bool dfs(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<size_t>& shiftCount, size_t slot){
  size_t numDays = avail.size();
  size_t numWorkers = avail[0].size();

  if(slot == numDays * dailyNeed){
    return true;

  }

  size_t day = slot/ dailyNeed;
  size_t position = slot % dailyNeed;

  for(size_t i = 0;i<numWorkers; i++ ){
    //check for good conditions first
    if(avail[day][i] == false || shiftCount[i] >= maxShifts){
      continue;
    }
    else if(std::find(sched[day].begin(), sched[day].end(), i) != sched[day].end()){
      continue;
    }
    sched[day][position] = i;
    shiftCount[i]++;

    if(dfs(avail, dailyNeed, maxShifts, sched, shiftCount, slot+1)){
      return true;
    }

    shiftCount[i]--;
    sched[day][position] = INVALID_ID;
  }

  return false; //return false by default
}

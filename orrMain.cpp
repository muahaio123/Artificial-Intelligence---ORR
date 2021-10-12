// CS 4318, spring 2021
// Agent Challenge 3: Off-road rally
//
// Here's the main function that plays all agents against each other and
// summarizes the results.

#include "orr.h"

extern const int numAgents;
extern vector<drivingDirection> (*agentFunc[])(TerrainMap &);
extern string agentStr[];

void printRoute(vector<drivingDirection> &route);

int main()
{
   const int numRaces = 1000;   // Change if you like.
   int i, j, lowestTime, numFinished[numAgents], numWins[numAgents],
       order[numAgents], raceTime, raceTimes[numAgents], temp,
       totalLooksAtMap[numAgents], totalMoves[numAgents],
       totalTime[numAgents];
   vector<drivingDirection> route;

   srandom(time(0));

   cout << "Agent Challenge 3: Off-road rally\n"
        << "Iteration results\n\n";
   for (i = 0; i < numAgents; i += 1)
   {
      numFinished[i] = 0;
      numWins[i] = 0;
      totalTime[i] = 0;
      totalLooksAtMap[i] = 0;
      totalMoves[i] = 0;
   }
   for (i = 0; i < numRaces; i += 1)
   {
      Terrain terrain(3 * (i % 10 + 1));
      cout << "Race " << i + 1 << ":\n";
      terrain.printTerrain();
      cout << "\n";
      for (j = 0; j < numAgents; j += 1)
      {
         TerrainMap map(&terrain);
         cout << setw(20) << left << agentStr[j] << flush;
         route = (*agentFunc[j])(map);
         raceTime = terrain.getRouteTime(route);
         cout << " " << setw(5) << right << raceTime << " ";
         printRoute(route);
         if (terrain.doesRouteFinish(route))
         {
            cout << " finished";
            numFinished[j] += 1;
            raceTimes[j] = raceTime;
         }
         else
         {
            raceTimes[j] = 0;
         }
         cout << "\n";
         totalTime[j] += raceTime;
         totalLooksAtMap[j] += map.getNumLooksAtMap();
         totalMoves[j] += route.size();
      }
      cout << "\n";
      lowestTime = 0;
      for (j = 0; j < numAgents; j += 1)
      {
         if (raceTimes[j] > 0 && (lowestTime == 0 || raceTimes[j] < lowestTime))
         {
            lowestTime = raceTimes[j];
         }
      }
      for (j = 0; j < numAgents; j += 1)
      {
         if (raceTimes[j] > 0 && raceTimes[j] <= lowestTime)
         {
            numWins[j] += 1;
         }
      }
   }

   for (i = 0; i < numAgents; i += 1)
   {
      order[i] = i;
   }
   for (i = 0; i < numAgents - 1; i += 1)
   {
      for (j = i + 1; j < numAgents; j += 1)
      {
         if (numFinished[order[i]] < numFinished[order[j]] || (numFinished[order[i]] == numFinished[order[j]] &&
             (totalTime[order[i]] > totalTime[order[j]] || (totalTime[order[i]] == totalTime[order[j]] &&
              (numWins[order[i]] < numWins[order[j]] || (numWins[order[i]] == numWins[order[j]] &&
               (totalLooksAtMap[order[i]] > totalLooksAtMap[order[j]] || (totalLooksAtMap[order[i]] == totalLooksAtMap[order[j]] &&
                agentStr[order[i]] > agentStr[order[j]]))))))))
         {
            temp = order[i];
            order[i] = order[j];
            order[j] = temp;
         }
      }
   }
   cout << "\n"
        << "Overall standings:      races     total    races     looks     total\n"
        << "                     finished      time      won    at map     moves\n";
   for (i = 0; i < numAgents; i += 1)
   {
      cout << setw(20) << left << agentStr[order[i]]
           << " " << setw(8) << right << numFinished[order[i]]
           << " " << setw(9) << right << totalTime[order[i]]
           << " " << setw(8) << right << numWins[order[i]]
           << " " << setw(9) << right << totalLooksAtMap[order[i]]
           << " " << setw(9) << right << totalMoves[order[i]] << "\n";
   }

   return 0;
}

void printRoute(vector<drivingDirection> &route)
{
   int whichMove;
   cout << "[";
   for (whichMove = 0; whichMove < static_cast<int>(route.size()) && whichMove < 900; whichMove += 1)
   {
      if (route.at(whichMove) == driveW)
      {
         cout << "W";
      }
      else if (route.at(whichMove) == driveK)
      {
         cout << "K";
      }
      else if (route.at(whichMove) == driveS)
      {
         cout << "S";
      }
      else if (route.at(whichMove) == driveN)
      {
         cout << "N";
      }
      else if (route.at(whichMove) == driveX)
      {
         cout << "X";
      }
      else if (route.at(whichMove) == driveE)
      {
         cout << "E";
      }
      else
      {
         cout << "*";
      }
   }
   if (route.size() > 900)
   {
      cout << "...";
   }
   cout << "]";
}

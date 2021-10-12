// CS 4318, spring 2021
// Agent Challenge 3: Off-road rally
//
// Here's an example agent function.  You can do much better than this.

#include "orr.h"

vector<drivingDirection> orrAgentTwoGreedy(TerrainMap &map)
{
   // Take the fastest single move, then look for the finish in one more move from there.
   drivingDirection bestMove, moveToTry;
   int bestTime, next;
   vector<drivingDirection> route;

   const int start = map.getStartHex();
   const int finish = map.getFinishHex();

   route.clear();
   bestMove = driveE;
   bestTime = INT_MAX;
   // Consider each possible move one by one.
   for (moveToTry = driveW; moveToTry <= driveE; moveToTry = static_cast<drivingDirection>(moveToTry + 1))
   {
      next = map.getNeighborHex(start, moveToTry);
      if (next == finish)
      {
         // If it reaches the finish, add it to the route and return it.
         route.push_back(moveToTry);
         return route;
      }
      else if (map.getMoveTime(start, moveToTry) < bestTime)
      {
         // Remember the fastest move available.
         bestMove = moveToTry;
         bestTime = map.getMoveTime(start, moveToTry);
      }
   }
   route.push_back(bestMove);
   next = map.getNeighborHex(start, bestMove);
   // Consider each possible next move.
   for (moveToTry = driveW; moveToTry <= driveE; moveToTry = static_cast<drivingDirection>(moveToTry + 1))
   {
      if (map.getNeighborHex(next, moveToTry) == finish)
      {
         // If it reaches the finish, add it to the route and return it.
         route.push_back(moveToTry);
         return route;
      }
   }
   return route;
}

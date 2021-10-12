// CS 4318, spring 2021
// Agent Challenge 3: Off-road rally
//
// Here's an example agent function.  You can do much better than this.

#include "orr.h"

vector<drivingDirection> orrAgentOneMove(TerrainMap &map)
{
   // Try to get to the finish in just one move.
   drivingDirection moveToTry;
   vector<drivingDirection> route;

   const int start = map.getStartHex();
   const int finish = map.getFinishHex();

   route.clear();
   // Consider each possible move one by one.
   for (moveToTry = driveW; moveToTry <= driveE; moveToTry = static_cast<drivingDirection>(moveToTry + 1))
   {
      if (map.getNeighborHex(start, moveToTry) == finish)
      {
         // If it reaches the finish, add it to the route and return it.
         route.push_back(moveToTry);
         return route;
      }
   }

   // If one move isn't enough to reach the finish, return an empty route.
   return route;
}

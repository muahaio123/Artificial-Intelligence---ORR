// YOUR NAME: Thanh Long Le
//
// CS 4318, spring 2021
// Agent Challenge 3: Off-road rally
//
// Rename this file and the function below.  For example, if your agent name
// is Jones, rename this orrAgentSmith.cpp file to orrAgentJones.cpp and the
// orrAgentSmith function below to orrAgentJones.  Complete your agent
// function and turn it in on Blackboard.  Random-number generation is not
// allowed; your agent must be entirely deterministic.  Feel free to create
// other agents--each in a separate .cpp file--for yours to race against,
// but turn in only one.  Test your agent(s) with
//
//    nice bash orrBuild.bash
//
// and then
//
//    nice ./orrRunSim
//
// Each submitted agent will race on each of at least 100 terrains, with
// sizes ranging from 3x3 to 30x30, to determine the standings, which will
// be posted soon after the agents are due.

#include "orr.h"
using namespace std;

namespace
{
	// If you need to define any new types or functions, put them here in
	// this unnamed namespace.  But no variables allowed!
	
	pair<int, int> decipher(TerrainMap &map, int currentHex)	// decipher to get the collum and row of the hex
	{	return pair<int, int>(currentHex / map.getSize(), currentHex % map.getSize());	}
	
}
	

// Rename and complete this agent function.
vector<drivingDirection> orrAgentSmith(TerrainMap &map)
{
	// Your function must end up returning a vector of moves.
	// No random-number generation allowed!
	// map.getSize() gives the size of the terrain: 6 for a 6x6 map, etc.
	// map.getStartHex() gives the number of the start hex.
	// map.getFinishHex() gives the number of the finish hex.
	// map.getMoveTime(fromHex, move) gives the driving time of one move.
	// map.getNeighborHex(fromHex, move) gives the hex got to by one move.
	
	const int finish = map.getFinishHex();
	const pair<int, int> finishXY = decipher(map, finish);
	
	
	// set the next move as the starting point and find its coordinate
	int next = map.getStartHex();
	pair<int, int> nextXY = decipher(map, next);
	
	
	vector<drivingDirection> route, directions;
	route.clear();
	directions.clear();
	
	while (next != finish)	// run until find the finish line
	{
		// re-evaluate each time the agent makes a move	
		//-------------find which directions to go-----------------
		if (finishXY.first > nextXY.first)	// if finish is on the right of currentHex
		{
			if (finishXY.second > nextXY.second)
				directions = {driveN, driveE};
			else if (finishXY.second < nextXY.second)
				directions = {driveE, driveX};
			else
				directions = {driveN, driveE, driveX};
		}
		else if (finishXY.first < nextXY.first)	// if finish is on the left of currentHex
		{
			if (finishXY.second > nextXY.second)
				directions = {driveK, driveW};
			else if (finishXY.second < nextXY.second)
				directions = {driveW, driveS};
			else
				directions = {driveK, driveW, driveS};
		}
		else	// if finish is on the same row as currentHex
		{
			if (finishXY.second > nextXY.second)
				directions = {driveK, driveN};
			else
				directions = {driveS, driveX};
		}
		//-------------find which directions to go-----------------
		
		int leastCost = INT_MAX; 
		drivingDirection bestMove = driveW;
		
		// find the next move with either the finish or least cost
		for (uint i = 0; i < directions.size(); ++i)
		{
			// if it is not 1 of the banned directions
			int move = map.getNeighborHex(next, directions[i]);
			
			if (move == finish)	// if found the finish line -> put to route and end the for loop
			{
				route.push_back(directions[i]);
				return route;
			}
				
			if (move != next)	// avoid going out of hex
			{	
				int time = map.getMoveTime(next, directions[i]);
				
				if (time <= leastCost)	// find the best move with the least cost
				{
					leastCost = time;
					bestMove = directions[i];
				}
			}
		}
		
		// Thank you professor LeGrand for helping me figure out what is wrong
		// do the best move with the least time
		route.push_back(bestMove);
		next = map.getNeighborHex(next, bestMove);	// go to the next best Hex
		nextXY = decipher(map, next);	// update the x-y coordiante of the next move
	}
	
	return route;
}

/*

 - First, carefully comment your code above to clarify how it works.
 - Here, describe your approach and analyze it.  How exactly did you develop
   and test it?  What are its strengths and weaknesses?  Why do you expect
   it to do well against the other submitted agents?
 - Also make a note here if you talked about the assignment with anyone or
   gave or received any kind of help.
	- Create a really greedy agent that:
	- Basically, the agent re-evaluate where it is relative to the finish line after each move
	- It always look at 1 hex ahead and determine where it would go next with the least amount of time possible
*/

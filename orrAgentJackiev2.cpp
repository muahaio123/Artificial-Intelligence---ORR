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
	
	// evaluate theposition of the current hex and the finish line
	vector<drivingDirection> eval(TerrainMap &map, int next, int finish)
	{
		vector<drivingDirection> directions;
		directions.clear();
		
		pair<int, int> nextXY = decipher(map, next);
		const pair<int, int> finishXY = decipher(map, finish);
		
		//-------------find which directions to go-----------------
		if (finishXY.first > nextXY.first)	// if finish is on the right of currentHex
		{
			if (finishXY.second > nextXY.second)
				directions = {driveK, driveN, driveE, driveX};
			else if (finishXY.second < nextXY.second)
				directions = {driveN, driveE, driveX, driveS};
			else
				directions = {driveN, driveE, driveX};
		}
		else if (finishXY.first < nextXY.first)	// if finish is on the left of currentHex
		{
			if (finishXY.second > nextXY.second)
				directions = {driveN, driveK, driveW, driveS};
			else if (finishXY.second < nextXY.second)
				directions = {driveK, driveW, driveS, driveX};
			else
				directions = {driveK, driveW, driveS};
		}
		else	// if finish is on the same row as currentHex
		{
			if (finishXY.second > nextXY.second)
				directions = {driveK, driveN, driveW, driveE};
			else
				directions = {driveS, driveX, driveW, driveE};
		}
		//-------------find which directions to go-----------------
		
		return directions;
	}
}
	

// Rename and complete this agent function.
vector<drivingDirection> orrAgentJackiev2(TerrainMap &map)
{
	// Your function must end up returning a vector of moves.
	// No random-number generation allowed!
	// map.getSize() gives the size of the terrain: 6 for a 6x6 map, etc.
	// map.getStartHex() gives the number of the start hex.
	// map.getFinishHex() gives the number of the finish hex.
	// map.getMoveTime(fromHex, move) gives the driving time of one move.
	// map.getNeighborHex(fromHex, move) gives the hex got to by one move.
	
	// get the finish hex
	const int finish = map.getFinishHex();
	
	// set the next move as the starting point and find its coordinate
	int next = map.getStartHex();
	
	// a vector of all the directions
	vector<drivingDirection> directions;
	
	// initialize a vector to hold all the possible routes to the goal
	vector<vector<drivingDirection>> record(map.getSize() * map.getSize());
	
	// initialize a vector of Booleans to check if the hexes is visited or not
	// and initialize it to false
	vector<bool> isVisited(map.getSize() * map.getSize(), false);
	
	// initialize a vector to hold the time of to reach that hexes
	vector<int> moveTime(map.getSize() * map.getSize(), 0);
	
	// a copy of the current route
	vector<drivingDirection> route;
	route.clear();
	
	// initialize a vector to hold the frontier of hexes to be explored
	vector<int> frontier;
	frontier.push_back(next);
	
	while (!frontier.empty())	// run until the frontier is empty
	{
		// use a FIFO (FIRST In FIRST Out) frontier
		next = frontier.front();
		frontier.erase(frontier.begin());
		
		// re-evaluate each time the agent makes a move	to "steer" the agent to the finish
		directions = eval(map, next, finish);
		
		for (uint i = 0; i < directions.size(); ++i)
		{
			int nextNext = map.getNeighborHex(next, directions[i]);
			
			if (nextNext != next)	// avoid going out of hex
			{
				// get the moving time up to the current hex
				int time = moveTime[next] + map.getMoveTime(next, directions[i]);
				
				// get the copy of the route up to the previous hex, not the current nextNext route
				route = record[next];
				route.push_back(directions[i]);
				
				if (isVisited[nextNext] == false)
				{
					isVisited[nextNext] = true;	// set that hex to have been visited
					
					frontier.push_back(nextNext);	// push to explore that hex later
					
					moveTime[nextNext] = time;	// save the moving time
					
					record[nextNext] = route;	// save the direction that agent just took
				}
				else	// if that hex is already visited
				{
					// will not explore the same hex again by not putting it in the frontier
					if (time < moveTime[nextNext])
					{
						moveTime[nextNext] = time;	// update to the shorter route time
						
						record[nextNext] = route;	// update the route to that hex with the shorter one
					}
				}
			}
		}
	}
	
	route = record[finish];
	
	// clear all the used vectors
	directions.clear();
	record.clear();
	isVisited.clear();
	moveTime.clear();
	frontier.clear();
	
	return route;
}

/*

 - First, carefully comment your code above to clarify how it works.
 - Here, describe your approach and analyze it.  How exactly did you develop
   and test it?  What are its strengths and weaknesses?  Why do you expect
   it to do well against the other submitted agents?
 - Also make a note here if you talked about the assignment with anyone or
   gave or received any kind of help.
	- I am doing a graph search (BFS?), but do not know the name of that method
	- basically, it will explore every hex in the direction between the start and finish.
	- if a hex is not explored, put it in frontier to explore is later
	- if already visited, update the route to that hex with the shorter one.
*/

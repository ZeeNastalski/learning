//#include <map>
//#include <set>
//#include <list>
#include <cmath>
//#include <ctime>
//#include <deque>
//#include <queue>
//#include <stack>
//#include <string>
//#include <bitset>
//#include <cstdio>
#include <limits>
#include <vector>
//#include <climits>
//#include <cstring>
//#include <cstdlib>
//#include <fstream>
//#include <numeric>
//#include <sstream>
#include <iostream>
//#include <algorithm>
using namespace std;

/*
* Complete the function below.
*/

vector < vector < int > > getLockerDistanceGrid(int cityLength, int cityWidth, vector < int > lockerXCoordinates, vector < int > lockerYCoordinates) {

	std::vector< std::vector< int > > grid(cityLength, std::vector<int>(cityWidth, INT_MAX));

	for (int locker = 0; locker < lockerXCoordinates.size(); locker++)
	{
		int lockerX = lockerXCoordinates[locker] - 1;
		int lockerY = lockerYCoordinates[locker] - 1;

		for (int x = 0; x < cityLength; x++)
		{
			for (int y = 0; y < cityWidth; y++)
			{
				int dist = abs(lockerX - x) + abs(lockerY - y);
				
				if (dist < grid[x][y])
				{
					grid[x][y] = dist;
				}
			}
		}
		
	}

	return grid;

}

int main()
{
	vector<int> x = { 1 };
	vector<int> y = { 1 };
	vector<vector < int >> lockers = getLockerDistanceGrid(3, 5, { 1 }, { 1 });
}

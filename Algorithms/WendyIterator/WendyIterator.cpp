#include <iostream>
#include <fstream>

#include "Solution.h"

using namespace std;

int main()
{
	ifstream stream;
	Solution sol(stream);

	
	for (Solution::iterator it = sol.begin(); it != sol.end(); ++it)
	{
		int x = *it;
		cout << x << endl;
	}
	

	return 0;
}
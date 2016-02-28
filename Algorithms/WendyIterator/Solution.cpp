#include "Solution.h"
#include <iostream>

using namespace std;

Solution::Solution(istream& s)
{

	//TODO parse input
	vec = { 5,6,7,8 };
}


Solution::~Solution()
{
}

Solution::iterator Solution::begin()
{
	Solution::iterator it( 0, vec);
	return it;
}

Solution::iterator Solution::end()
{
	Solution::iterator it(vec.size(), vec);
	it.idx = vec.size();

	return it;
}
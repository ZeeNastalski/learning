#include <vector>
#include <iostream>
using namespace std;

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(vector<int> &A) {

	// finding leader using stack

	unsigned int stackSize = 0;
	int stackVal = 0;

	for (int i : A)
	{
		if (stackSize > 0)
		{
			if (i == stackVal)
			{
				stackSize++;
			}
			else
			{
				stackSize--;
			}
		}
		else
		{
			stackSize = 1;
			stackVal = i;
		}
	}

	cout << "suspected leader " << stackVal << endl;

	int cnt = 0;
	int idx = -1;
	for (unsigned i = 0; i<A.size(); i++)
	{
		if (A[i] == stackVal)
		{
			cnt++;
			idx = i;
		}
	}

	if (cnt > A.size() / 2.0) return idx;
	return -1;

}

int main()
{
	cout << solution(vector<int> {1, 2, 3}) << endl;
	cout << solution(vector<int> {1, 3, 3}) << endl;
	return 0;
}
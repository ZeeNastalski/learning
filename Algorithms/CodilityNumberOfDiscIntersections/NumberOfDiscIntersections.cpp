#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct disc {
	int value;
	bool isStart;
};

bool compareDiscsByValue(const disc &a, const disc &b)
{
	if (a.value == b.value)
	{
		if (a.isStart) 
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	return a.value < b.value;
}

int solution(vector<int> &A) {
	
	vector<disc> discs;

	for (unsigned i = 0; i < A.size(); i++)
	{
		disc start;
		disc end;
		start.value = i - A[i];
		start.isStart = true;
		
		end.value = i + A[i];
		end.isStart = false;
		discs.push_back(start);
		discs.push_back(end);
	}

	sort(discs.begin(), discs.end(), compareDiscsByValue);

	// calculate overlaps
	unsigned long activeDiscs = 0;
	unsigned long overlapingPairs = 0;

	vector<disc>::iterator it;
	for (it = discs.begin(); it != discs.end(); it++)
	{
		if (it->isStart)
		{
			activeDiscs++;
		}
		else
		{
			activeDiscs--;
			overlapingPairs += activeDiscs;

			if (overlapingPairs > 10000000UL) return -1;
		}
	}


	return overlapingPairs;
}

int main()
{
	vector<int> v1 = vector<int>{ 1,5,2,1,4,0 };
	vector<int> v2 = vector<int>{ 1,1,1 };
	cout << solution(v1);
	cout << solution(v2);
}
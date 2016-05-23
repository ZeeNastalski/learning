#include <iostream>
#include <vector>

using namespace std;
// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;


void calcSum(char letter, string &S, vector<int> &sumVec)
{
	sumVec[0] = 0;

	for (unsigned int i = 0; i < S.length(); i++)
	{
		if (S[i] == letter)
		{
			sumVec[i+1] = sumVec[i] + 1;
		}
		else
		{
			sumVec[i + 1] = sumVec[i];
		}
	}
}

vector<int> solution(string &S, vector<int> &P, vector<int> &Q) {

	vector<int> ans = vector<int>(P.size());

	vector<int> sumsA = vector<int>(S.length()+1);
	vector<int> sumsC = vector<int>(S.length()+1);
	vector<int> sumsG = vector<int>(S.length()+1);

	calcSum('A', S, sumsA);
	calcSum('C', S, sumsC);
	calcSum('G', S, sumsG);

	for (unsigned int i = 0; i < P.size(); i++)
	{
		int p = P[i];
		int q = Q[i];

		if (sumsA[q+1] - sumsA[p] > 0)
		{
			ans[i] = 1;
			continue;
		}

		if (sumsC[q+1] - sumsC[p] > 0)
		{
			ans[i] = 2;
			continue;
		}

		if (sumsG[q+1] - sumsG[p] > 0)
		{
			ans[i] = 3;
			continue;
		}

	
		//Not A,C,G then it T must be there.
		ans[i] = 4;
			
		
	}

	return ans;
}


int main()
{
	solution(string("CAGCCTA"), vector<int> {2, 5, 0}, vector<int> {4, 5, 6});
}

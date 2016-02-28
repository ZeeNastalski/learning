#include <iostream>
#include <vector>
using namespace std;


int solution(vector<int> &A)
{
	int N = A.size();
	int maxPit = -1;

	if (A.size() < 3) return -1;


	int P = 0;
	int Q = 0;
	int R = 0;
	while (true)
	{

		while (P < N - 1 && A[P] <= A[P + 1]) P++;
		if (P == N - 1) return maxPit;

		Q = P + 1;
		while (Q< N - 1 && A[Q] >= A[Q + 1]) Q++;

		if (Q == N - 1) return maxPit;

		R = Q + 1;
		while (A[R] <= A[R - 1])



			R = Q + 1;


		for (int i = P + 1; i < N; i++)
		{

		}

	}
}


/*
int solution(vector<int> &A)
{
int N = A.size();
int maxPit = -1;

if (A.size() < 3) return -1;


int P = 0;
int Q = 0;
int R = 0;

string state = "down";

for (int i = 1; i < N; i++)
{

if (state == "down" && A[i] >= A[i-1] )
{
P = A[i];
Q = A[i];
R = A[i];
}

if (state == "down" && A[i] < A[i - 1]);
{
Q = A[i-1];
state = "up";
}

if( state == "up" && )











}
}

*/

/*
int solution(vector<int> &A)
{
int N = A.size();
int maxPit = -1;

if (A.size() < 3) return -1;

int i = 0;

//find first descending step
while (i+1<N && A[i] <= A[i + 1])
i++;

if (i == N) return -1; //no dips, sequence is ascending

int P = i;

//find first ascending step
while (i + 1 < N && A[i] > A[i + 1])
i++;

if (i == N) return -1; //no dips,

int Q = i;













//find first ascending step







return maxPit;
}
*/

int main()
{
	vector<int> v = { 0,1,3,-2,0,1,0,-3,2,3 };
	if (solution(v) != 4) return 1;

	v = {};
	if (solution(v) != -1) return 1;

	v = { 1,-1 };
	if (solution(v) != -1) return 1;

	v = { 1,-1, 1 };
	if (solution(v) != 2) return 1;

	v = { 4,3,2,1 };
	if (solution(v) != -1) return 1;

	v = { 1,2,3,4 };
	if (solution(v) != -1) return 1;



	return 0;
}
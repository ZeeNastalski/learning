#include <vector>
#include <algorithm>
#include <limits>

using namespace std;


int distance(int a, int b)
{
	int d = a - b;

	if (d < 0) { d = b - a; };

	return d;
}


int solution(vector<int> &A)
{
	sort(A.begin(), A.end());
	
	int min = INT_MAX;
	for (int i = 0; i < A.size() - 1; i++)
	{
		int d = distance(A[i], A[i + 1]);
		if (d < min) { min = d; }
	}

	return min;
}


int main()
{
	vector<int> t1 = { 8, 24, 3, 20, 1, 17 };
	solution(t1);


	return 0;
}
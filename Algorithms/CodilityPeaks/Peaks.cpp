// you can use includes, for example:
#include <algorithm>
#include <vector>
using namespace std;
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

bool check(vector<int> &peaks, int flags)
{
	int N = peaks.size();
	
	int pos = 0;
	int flagsLeft = flags;

	while (pos < N-1 && flags>0)
	{
		if (peaks[pos])
		{
			flagsLeft--;
			pos = pos + flags;
		}
		else
		{
			pos++;
		}
	}

	if (pos = flags) return 0;


	return (flags == 0);
}

int solution(vector<int> &A) {

	int N = (int)A.size();

	vector<bool> peaks(N, false);

	int peaksCount = 0;
	for (int i = 1; i<N - 1; i++)
	{
		if (A[i] > max(A[i - 1], A[i + 1]))
		{
			peaks[i] = true;
			peaksCount++;
		}
	}

	//bisecion 0 to peaks

}
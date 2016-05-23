#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int solution(vector<int> &A) {
	
	if (A.size() <= 1) return 0;

	int current_max_profit = 0;
	int global_max_ptofit = 0;
	
	for (unsigned i = 1; i < A.size(); i++)
	{
		current_max_profit = max(0, current_max_profit + A[i] - A[i-1]);
		global_max_ptofit = max(global_max_ptofit, current_max_profit);
	}

	return global_max_ptofit;

}


int main() {
	cout << solution(vector<int> {5, 1, 2, 1, 3, 1}) << endl;
	cout << solution(vector<int> {23171, 21011, 21123, 21366, 21013, 21367}) << endl;
	cout << solution(vector<int> {1,2,3,4,5}) << endl;
	cout << solution(vector<int> {5,4,3,2,1}) << endl;
	cout << solution(vector<int> {}) << endl;
	return 0;
}
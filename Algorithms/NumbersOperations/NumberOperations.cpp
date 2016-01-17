#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define N 5

/*
* Problem: https://www.codeeval.com/browse/190/
*/

using namespace std;


template<class T> class VectorCombinatorics
{
	typedef bool(*CallbackType)(vector<T>&);

	public:
		VectorCombinatorics() {};
		virtual ~VectorCombinatorics() {};
		
		// makes a callback for every permutation. 
		// Permutating stops when callback returns true.
		void permutations(vector<T> vec, CallbackType callback)
		{
			// vector passed by value here. Don't want to modify original vector.
			permutateRecursively(vec, 0, callback);
		}

		void combinations(vector<T> values, int length, CallbackType callback)
		{
			vector<T> combination(length);
			combinationsRecursively(values, combination, 0, callback);
						
		}

	protected:
		
		void combinationsRecursively(const vector<T> &values, vector<T> &combination, int from, CallbackType callback)
		{
			if (from == combination.size())
			{
				callback(combination);
				return;
			}

			for (int v : values)
			{
				combination[from] = v;
				combinationsRecursively(values, combination, from + 1, callback);
			}

		}

		void permutateRecursively(vector<T> &vec, int from, CallbackType callback)
		{
			if (from == vec.size())
			{
				callback(vec);
				return;
			}

			for (int i = from; i < vec.size(); i++)
			{
				swap(vec, i, from);
				permutateRecursively(vec, from + 1, callback);
				swap(vec, i, from);
			}
		}

		void swap(vector<T> &vec, int i, int j)
		{
			int tmp = vec[i];
			vec[i] = vec[j];
			vec[j] = tmp;
		}
};



bool YES = false;
vector<int> currentPermutation;

int apply_op(int a, int b, int op)
{
	if (op == 0) return a + b;
	if (op == 1) return a - b;
	if (op == 2) return a * b;
}


string opCodeToString(int op)
{
	if (op == 0) return "+";
	if (op == 1) return "-";
	if (op == 2) return "*";
}


void printOperation(const vector<int> nums, const vector<int> ops, int result)
{
	for (int i = 0; i < ops.size(); i++)
	{
		cout << nums[i] << opCodeToString(ops[i]);
	}

	cout << nums[nums.size() - 1] << "=" << result << endl;
}

void test_result(const vector<int> nums, const vector<int> ops)
{	

	int value = nums[0];
	for (int i = 1; i < N; i++)
	{
		value = apply_op(value, nums[i], ops[i - 1]);
	}

	//printOperation(nums, ops, value);
	
	if (value == 42) { 
		YES = true;
	}
}


bool nextCombination(vector<int> &comb)
{
	test_result(currentPermutation, comb);

	return false;
}

bool nextPermutation(vector<int> &perm)
{
	currentPermutation = perm;
	
	VectorCombinatorics<int> combinatorics;

	combinatorics.combinations(vector<int> {0, 1, 2}, N-1, nextCombination);

	return false;
}

/*
int main() {

	vector<int> arr(N);
	for (int i = 0; i < N; i++) { 
		cin >> arr[i]; 
	}

	VectorCombinatorics<int> combinatorics;
	
	combinatorics.permutations(arr, nextPermutation);

	if (YES) cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}
*/

int main(int argc, char *argv[]) {
	
	ifstream stream(argv[1]);
	string line;
	vector<int> arr(N);

	while (getline(stream, line)) {		
		sscanf(line.c_str(), "%d %d %d %d %d", &arr[0], &arr[1], &arr[2], &arr[3], &arr[4]);
		
		VectorCombinatorics<int> combinatorics;
		combinatorics.permutations(arr, nextPermutation);

		if (YES) 
			{ cout << "YES" << endl; }
		else
		{
			cout << "NO" << endl;
		}

		YES = false;

	}

	
	return 0;

}
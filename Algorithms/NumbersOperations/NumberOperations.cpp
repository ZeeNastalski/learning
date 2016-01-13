#include <iostream>
#include <string>
#define N 5

/*
* Problem: https://www.codeeval.com/browse/190/
*/

using namespace std;


bool YES = false;
int cnt = 0;
int perms = 0;

void swap(int arr[], int i, int j)
{
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}


int apply_op(int a, int b, int op)
{
	if (op == 0) return a + b;
	if (op == 1) return a - b;
	if (op == 2) return a * b;
}

string print_op(int op)
{
	if (op == 0) return "+";
	if (op == 1) return "-";
	if (op == 2) return "*";
}



void test_result(int arr[], int ops[])
{
	
	cout << arr[0] << print_op(ops[0]) << arr[1] << print_op(ops[1]) << arr[2] << print_op(ops[2]) << arr[3] << print_op(ops[3]) << arr[4];

	int value = arr[0];
	for (int i = 1; i < N; i++)
	{
		value = apply_op(value, arr[i], ops[i - 1]);
	}

	cout << "=" << value << endl;
	
	if (value == 42) { 
		YES = true;
	}
	
	cnt++;
	
}


void test_combinations_of_operations(int arr[])
{
	perms++;
	/* having a permutation of number we need to test all possible combinations of operations
	convention
		0 plus
		1 minus
		2 times
	*/
	

	int ops[4];

	for (ops[0] = 0; ops[0] < 2; ops[0]++)
		for (ops[1] = 0; ops[1] < 2; ops[1]++)
			for (ops[2] = 0; ops[2] < 2; ops[2]++)
				for (ops[3] = 0; ops[3] < 2; ops[3]++)
				{
					test_result(arr, ops);
				}
		
}

void permutate(int arr[], int from)
{
	
	if (from == N - 1)
	{
		test_combinations_of_operations(arr);
	}

	for (int i = from; i < N; i++)
	{
		swap(arr, i, from);
		permutate(arr, from + 1);
		swap(arr, i, from);
	}
}

int main() {

	int arr[N];
	for (int i = 0; i < N; i++) { cin >> arr[i]; };

	permutate(arr, 0);

	if (YES) cout << "YES";
	else cout << "NO";
	return 0;


}

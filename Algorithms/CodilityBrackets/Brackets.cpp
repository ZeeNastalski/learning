#include <string>
#include <iostream>
using namespace std;

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

struct stackEl
{
	char bracket;
	stackEl* next;
};

class Stack
{
public:

	void push(char c)
	{
		stackEl* s = new stackEl;
		s->bracket = c;
		s->next = head;
		head = s;
	}

	char pop()
	{
		if (head == NULL) return 0;

		stackEl* tmp = head;
		char ret = head->bracket;
		head = head->next;
		delete tmp;
		return ret;
	}

	char peek()
	{
		if (head == NULL) return 0;

		return head->bracket;
	}

private:

	stackEl* head = NULL;

};


int solution(string &S) {

	Stack stack;
	string::iterator it;


	for (it = S.begin(); it != S.end(); it++)
	{
		if (*it == '(' || *it == '{' || *it == '[')
		{
			stack.push(*it);
		}
		else
		{
			char b = stack.pop();
			if (b == '{' && *it == '}') continue;
			if (b == '[' && *it == ']') continue;
			if (b == '(' && *it == ')') continue;
			return 0;
		}

	}

	if (stack.peek() != 0) { return 0; }
	return 1;
}

int main() {

	cout << solution(string("()")) << endl;
	cout << solution(string("{[()()]}")) << endl;
	cout << solution(string("")) << endl;
	cout << solution(string("{[()()]}{[()()]}")) << endl;
	cout << solution(string("{[(()]}")) << endl;
	cout << solution(string("{")) << endl;
	
	return 0;
}
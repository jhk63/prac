
#include <stack>
#include <iostream>
using namespace std;


int main()
{
	stack<int> number_stack;

	number_stack.push(1);
	number_stack.push(2);
	number_stack.push(3);

	cout << number_stack.top() << endl;

	number_stack.pop();
	cout << number_stack.top() << endl;

	return 0;
}
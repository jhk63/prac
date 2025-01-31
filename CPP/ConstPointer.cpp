
#include <iostream>
using namespace std;


int main()
{
	int a = 5;
	int b = 10;

	// 1. Pointer to a Constant
	int const * ptr1 = &a;

	// allowed: Changing address
	ptr1 = &b;

	// not allowed: Trying to change a constant value
	// *ptr1 = 10;

	cout << *ptr1 << endl;


	// 2. Constant Pointer
	int * const ptr2 = &a;

	// allowed: Changing non-const value
	*ptr2 = 10;

	// not allowed: Trying to change a constant address
	// ptr2 = &b;

	cout << *ptr2 << endl;

	return 0;
}
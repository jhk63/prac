
#include <iostream>
using namespace std;


int main()
{
	int var = 5;
	int *ptr = &var;
	int *newPtr = ptr;

	cout << "ptr address: " << ptr << ", value: " << *ptr << endl;
	cout << "newPtr address: " << newPtr << ", value: " << *newPtr << endl; 

	*newPtr = 25;

	cout << "var = " << var << endl;
	cout << "ptr = " << *ptr << ", address: " << ptr << endl;
	cout << "newPtr = " << *newPtr << ", address: " << newPtr << endl;

	return 0;
}
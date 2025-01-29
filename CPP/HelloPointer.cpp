
#include <iostream>
using namespace std;


int main()
{
	int var = 5;
	int *ptr = &var;

	cout << "Var Address: " << ptr << " with " << *ptr << endl;

	return 0;
}

void Challenge()
{
	int num;
	int *intPtr = &num;

	cin >> num;
	cout << *intPtr;
}
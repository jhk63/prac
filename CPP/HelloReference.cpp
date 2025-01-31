
#include <iostream>
using namespace std;


int main()
{
	int a = 10;
	// int &ref;			// ref must be initialized when declared
	int &ref = a;
	
	ref = 20;
	cout << "a = " << a;

	return 0;
}

void Challenge()
{
	int a, b;
    cin >> a >> b;

    int &refA = a;
    int &refB = b;

    refA *= 4;
    refB -= a;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "refA = " << refA << endl;
    cout << "refB = " << refB << endl;
}
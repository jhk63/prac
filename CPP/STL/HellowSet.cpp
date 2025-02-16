
#include <set>
#include <iostream>
using namespace std;


int main()
{
	set<int> mySet = {5, 10, 3, 5};
	// mySet.insert(50);

	// for (int i = mySet.begin(); i != mySet.end(); i++) // error
	for (auto i = mySet.begin(); i != mySet.end(); i++)
	    cout << *i << " ";

	return 0;
}
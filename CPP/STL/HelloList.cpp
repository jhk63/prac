
#include <list>
#include <forward_list>
#include <iostream>
using namespace std;


int main()
{
	forward_list<int> flist = {1, 2, 3};

	flist.push_front(5);
	// flist.push_back(4);	// error
	for (int &x : flist)
	    cout << x << " ";
	cout << endl;


	flist.pop_front();
	for (int &x : flist)
	    cout << x << " ";
	cout << endl;

	return 0;
}
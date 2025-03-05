
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


bool descending(int a, int b)
{
	return a > b;
}

int main()
{
	vector<int> numbers = {3, 5, 1, 2, 4, 10, 7};

	// sort(numbers.begin(), numbers.end());
	sort(numbers.begin(), numbers.end(), descending);

	// partial_sort(numbers.begin(), numbers.begin() + 3, numbers.end());

	// cout << is_sorted(numbers.begin(), numbers.end()) << endl;
	cout << is_sorted(numbers.begin(), numbers.end(), descending) << endl;
	// Output: 
	// 0 = false, 
	// 1 = true

	for(auto i = numbers.begin(); i != numbers.end(); i++)
	    cout << *i << " ";

	cout << endl;
	
	return 0;
}
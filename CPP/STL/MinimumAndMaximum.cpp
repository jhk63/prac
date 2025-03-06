
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


int main()
{
	int a = 10, b = 20;

	cout << "min(): " << min(a, b) << endl;
	cout << "max(): " << max(a, b) << endl;

	vector<int> numbers = {5, 10, 3, 1, 7, 20};

	cout << "min_element(): " << *min_element(numbers.begin(), numbers.end()) << endl;
	cout << "max_element(): " << *max_element(numbers.begin(), numbers.end()) << endl;

	return 0;
}
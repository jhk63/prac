
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


int main()
{
	vector<int> v1 = {1, 2, 3};
	vector<int> v2(v1.size());

	cout << "copy() method:" << endl;
	copy(v1.begin(), v1.end(), v2.begin());

	for(const auto& value : v2)
	{
	    cout << value << " ";
	}
	cout << endl << endl;
	// ----------------------------------------------------------------

	vector<int> numbers(10);

	cout << "fill() method:" << endl;
	fill(numbers.begin(), numbers.end(), 1);

	for(auto value : numbers)
	    cout << value << " ";

	cout << endl;

	fill(numbers.begin(), numbers.end() - 3, 2);

	for(auto value : numbers)
	    cout << value << " ";

	cout << endl << endl;
	// ----------------------------------------------------------------

	vector<string> names;

	string first = "John";
	string second = "Max";

	cout << "move() method:" << endl;
	names.push_back(first);
	names.push_back(move(second));

	cout << first << endl;
	cout << second << endl;
	cout << names[1] << endl << endl;
	// ----------------------------------------------------------------

	cout << "swap() method:" << endl;

	vector<int> v3 = {1, 2, 3};
	vector<int> v4 = {4, 5, 6};

	for(auto value : v3)
	    cout << value << " ";
	for(auto value : v4)
	    cout << value << " ";

	cout << endl;

	swap(v3, v4);

	for(auto value : v3)
	    cout << value << " ";
	for(auto value : v4)
	    cout << value << " ";

	cout << endl << endl;
	// ----------------------------------------------------------------

	cout << "reverse() method:" << endl;
	vector<int> a = {1, 2, 3, 4, 5};

	for(auto value : a)
	    cout << value << " ";
	    
	cout << endl;
	
	reverse(a.begin(), a.end());

	for(auto value : a)
	    cout << value << " ";

	cout << endl;

	return 0;
}
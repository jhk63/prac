
#include <iostream>
#include <vector>
using namespace std;


int main()
{
	vector<int> numbers = {4, 2, 5, 8, 3};
	vector<int>::iterator it1, it2;
	vector<int>::iterator it;

	it1 = numbers.begin();
	it2 = numbers.begin() + 1;

	cout << *it1 << endl;
	cout << *it2 << endl;

	it = numbers.begin();
	cout << "First value is: " << *it << endl;

	it++;
	cout << "Second value is: " << *it << endl;

	++it;
	cout << "Third value is: " << *it << endl;

}

void Challenge()
{
	vector<int> numbers;
    vector<int>::iterator it;

    for (int i = 0; i < 5; i++)
    {
        int input;
        cin >> input;
        numbers.push_back(input);
    }

    for(it = numbers.begin(); it != numbers.end(); it++)
    {
        cout << *it << " ";
    }
}
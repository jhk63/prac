
#include <deque>
#include <iostream>
using namespace std;


int main()
{
	deque<int> numbers = {1, 2, 3, 4, 5};

	for(int &num : numbers)
	{
	    cout << num << " ";
	}
	cout << endl;

	numbers.push_front(1);
	numbers.push_back(4);

	for(int &num : numbers)
	{
	    cout << num << " ";
	}
	cout << endl;
}

void Challenge()
{
	int input;
    deque<int> numbers;
    bool toggle = false;

    while (true)
    {
        cin >> input;
        if (input == -1) break;

        if (!toggle)
        {
	        numbers.push_front(input);
	        toggle = true;
        }
	    else
	    {
	        numbers.push_back(input);
	        toggle = false;
	    }
    }

    for(int &num : numbers)
	{
	    cout << num << " ";
	}
	cout << endl;
}
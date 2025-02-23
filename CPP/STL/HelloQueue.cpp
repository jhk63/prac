
#include <queue>
#include <iostream>
using namespace std;


int main()
{
	return 0;
}

void Challenge()
{
	queue<int> numbers;

    for (int i = 0; i < 10; i++)
    {
        int num;
        cin >> num;

        numbers.push(num);
    }

    while(!numbers.empty())
    {
        if (numbers.front() % 2 == 0)
        {
            cout << numbers.front() << " ";
        }

        numbers.pop();
    }
}
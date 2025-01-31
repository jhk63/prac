
// When we declare an array the name of the array is actually a
// constant pointer to a non-constant value
#include <iostream>
using namespace std;


int main()
{
	int list[] = {10, 20, 30, 40, 50};
	cout << "First: " << *list << endl;
	cout << "Third: " << *(list + 2) << endl;

	int *ptr = list;
	cout << "First again: " << *ptr << endl;

	for(int i = 0; i < 5; i++)
	{
	    cout << *ptr++ << " ";
	}
	cout << endl;


	return 0;
}

void Challenge()
{
	int n, x;
    n = 5;

    int numbers[n] = {1, 2, 3, 4, 5};

    for (int j = 0; j < n; j++)
    {
        if (*(numbers+j) % 2 == 0)
        {
            cout << *(numbers+j) << " ";
        }
    }
}
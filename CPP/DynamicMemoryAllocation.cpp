
#include <iostream>
using namespace std;


int main()
{
	// 1. 
	int *ptr;
	ptr = new int;
	*ptr = 10;

	cout << "*ptr = " << *ptr << endl;

	delete ptr;

	// 2. Dynamic Array
	int *array = new int[5];
	    
	for(int i = 0; i < 5; i++)
        array[i] = i + 1;
	for(int i = 0; i < 5; i++)
	    cout << array[i] << " ";
	    
	delete[] array;

	return 0;
}

void Challenge()
{
	int N;
    cin >> N;

    int *numbers = new int[N];

    for (int i = 0; i < N; i++)
    {
        cin >> numbers[i];
    }
    
    for (int i = 0; i < N; i ++)
    {
        if (i == 0 || i % 2 == 0)
        {
            cout << numbers[i] << " ";
        }
    }
    cout << endl;

    delete[] numbers;
}

#include <iostream>
using namespace std;


int main()
{
	int list[] = {1, 3, 2, 4, 6};
	int *ptr = &list[0];

	// ++ / --
	cout << *ptr << " ";
	ptr++;
	cout << *ptr << " ";
	ptr--;
	cout << *ptr << endl;
	
	// += / -=
	ptr = &list[0];
	ptr += 4;
	cout << *ptr << " ";
	ptr -= 2;
	cout << *ptr << endl;

	// n = p2 - p1
	ptr = &list[0];
	int *ptr2 = &list[4];
	cout << "Between " << *ptr << " and " << *ptr2 
		<< " there's " << ptr2-ptr << " elements" << endl;


	return 0;
}

void Challenge()
{
	int numbers[] = {10, 20, 30, 40, 50, 60, 70, 80};

	int *ptr1 = &numbers[0];
	int *ptr2 = ptr1 + 3;
	int *ptr3 = ptr2 - 2;

	int *first = &numbers[0];
	int *last = &numbers[7];
	cout << "There are " << last - first << " elements between " 
		<< *first << " and " << *last << endl;

	cout << "*ptr1 -> " << *ptr1 << endl;
    cout << "*ptr2 -> " << *ptr2 << endl;
    cout << "*ptr3 -> " << *ptr3 << endl;
}
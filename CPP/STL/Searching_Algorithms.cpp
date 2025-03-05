
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


int LinearSearch(int array[], int n, int x)
{
    for(int i = 0; i < n; i++)
    {
    	if(array[i] == x) return i;
    }

    return 0;
}

int BinarySearch(int array[], int x, int left, int right) 
{
  while (left <= right) 
  {
    int mid = left + (right - left) / 2;

    if (array[mid] == x)
      return mid;

    if (array[mid] < x)
      left = mid + 1;

    else
      right  = mid - 1;
  }

  return -1;
}

int main()
{
	// LinearSearch
    int array[] = {1, 2, 3, 4, 5};
    int n = 5;
    int x = 3;
    
    cout << "The index of the element " << x << " is ";
    cout << LinearSearch(array, n, x) << endl;

    // BinarySearch: must be sorted
    array[] = {1, 5, 8, 10, 20};
    x = 10;
    n = 5;
    int result = BinarySearch(array, x, 0, n - 1);
    
    if(result == -1)
        cout << "Not found.";
    else
        cout << "The element is found at " << result;
}

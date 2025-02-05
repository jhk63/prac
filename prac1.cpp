
#include <iostream>
using namespace std;


int main()
{
    int x[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    for (int y : x)
    {
        cout << y << " ";
    }
    cout << endl;

    // int *array = new int[5];
    // for (int i = 0; i < 5; i++)
    //     array[i] = i + 1;

    // for (int num : array)
    // {
    //     cout << num << " ";
    // }
    // cout << endl;

    // delete[] array;

    return 0;
}

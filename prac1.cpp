
#include <iostream>
using namespace std;


int main()
{
    int n;
    n = 5;

    int row = (n + 1) / 2;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < (n / 2) - i; j++)
            cout << " ";
        
        for (int j = 0; j < (2 * i) + 1; j++)
            cout << "*";

        for (int j = 0; j < (n / 2) - i; j++)
            cout << " ";
        
        cout << endl;
    }
    
    return 0;
}

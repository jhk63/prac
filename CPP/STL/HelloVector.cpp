
#include <vector>
#include <iostream>
using namespace std;


int main()
{
    vector<int> numbers = {1, 2, 3};
    
    for (int i=0; i<numbers.size(); i++)
    {
        cout << numbers[i] << " ";
    }
    cout << endl;
    cout << "numbers.size(): " << numbers.size() << endl;
    
    numbers.push_back(10);
    for (int i=0; i<numbers.size(); i++)
    {
        cout << numbers[i] << " ";
    }
    cout << endl;
    cout << "numbers.size(): " << numbers.size() << endl;

    numbers.pop_back();
    cout << "numbers.size(): " << numbers.size() << endl;

    cout << "numbers.front(): " << numbers.front() << endl;
    cout << "numbers.back(): " << numbers.back() << endl;

    cout << "numbers.empty(): " << numbers.empty() << endl;
    
    return 0;
}

void Challenge()
{
    int input;
    vector<int> numbers;

    while (true)
    {
        cin >> input;
        if (input == -1) break;
        numbers.push_back(input);
    }

    cin >> input;
    for (int i = 0; i < numbers.size(); i++)
    {
        if (input % numbers[i] != 0) continue;

        cout << numbers[i] << endl;
    }
}
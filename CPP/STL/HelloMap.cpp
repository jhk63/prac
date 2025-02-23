
#include <map>
#include <iostream>
using namespace std;


int main()
{
	map<string, int> myMap;

	myMap["apple"] = 3;
	cout << myMap["apple"] << endl;

	myMap.insert({"banana", 1});
	cout << myMap["banana"] << endl;

	return 0;
}

void Challenge()
{
	int count = 5;
    
    map<string, int> scores;
    string name;
    int input;

    int i = 0;
    while (i < count)
    {
        cin >> name >> input;
        scores[name] = input;

        ++i;
    }

    cin >> input;
    count = input;

    i = 0;
    while (i < count)
    {
        cin >> name;
        cout << scores[name] << endl;

        ++i;
    }
}
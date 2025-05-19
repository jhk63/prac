
#include <iostream>
#include <vector>
using namespace std;


int CalculateLevel(int totalExp, const vector<int>& expThresholds)
{
    int level = 1;
    for (const auto& threshold : expThresholds)
    {
        if (totalExp >= threshold)
        {
            level++;
        }
        else
        {
            break;
        }
    }

    return level;
}

int main()
{
    vector<int> expThresholds = {50, 100, 300, 600, 1000};

    int currentExp = 460;
    int level = CalculateLevel(currentExp, expThresholds);
    cout << "Level: " << level << endl;
}
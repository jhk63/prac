
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;


class Character
{
public:
    unordered_map<string, int> stats
    {
        {"STR", 0},
        {"DEX", 0},
        {"INT", 0},
        {"LUK" , 0}
    };

    int availablePoints;

    Character(int initPoints)
    : availablePoints(initPoints)
    {

    }

    void DistributeStat(const string& statName, int points)
    {
        if (availablePoints >= points && stats.count(statName))
        {
            stats[statName] += points;
            availablePoints -= points;

            cout << statName << " 스텟이 " << points << " 포인트만큼 증가했습니다.\n";
        }
        else 
        {
            cout << (points - availablePoints) << "포인트가 부족합니다.\n";
        }
    }

    void ShowStats() const
    {
        cout << "=== Character Stats ===\n";
        for (const auto& [name, value] : stats)
        {
            cout << name << ": " << value << '\n';
        }

        cout << "Available Points: " << availablePoints << '\n';
    }
};

int main()
{
    Character player(10);

    player.ShowStats();

    player.DistributeStat("STR", 3);
    player.DistributeStat("DEX", 3);
    player.DistributeStat("INT", 5);

    player.ShowStats();

    return 0;
}
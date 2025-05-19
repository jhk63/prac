
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;


struct DropItem
{
    string name;
    int chance;
};

struct Monster
{
    string name;
    vector<DropItem> drops;
};

void dropItem(const Monster& monster)
{
    cout << monster.name << " 처치했습니다.\n";

    int roll = rand() % 100;
    int accumulated = 0;

    for (const auto& item : monster.drops)
    {
        accumulated += item.chance;
        if (roll < accumulated)
        {
            cout << item.name << " 드랍\n";
            return;
        }
    }

    cout << "아이템을 획득하지 못했습니다.\n";
}

int main()
{
    srand((unsigned)time(0));

    vector<Monster> monsters = {
        {"Slime", {{"체력 물약", 70}}},
        {"Goblin", {{"철 무기", 40}, {"돈", 60}}},
        {"Dragon", {{"전설 무기", 20}, {"희귀 방어구", 40}}}
    };

    cout << "몬스터 처치 시작\n\n";
    for (const auto& monster : monsters)
    {
        dropItem(monster);
    }

    return 0;
}
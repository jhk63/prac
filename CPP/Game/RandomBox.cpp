
#include <iostream>
#include <string>
#include <vector>
#include <random>
using namespace std;


struct Reward
{
    string name;
    float chance;
};

string OpenRewardBox(const vector<Reward>& rewards)
{
    // 하드웨어 시드용 난수 생성
    random_device rd;
    // 고성능 의사 난수 생성기
    mt19937 gen(rd());

    uniform_real_distribution<> dis(0, 100);

    float roll = dis(gen);
    float cumulative = 0.f;

    for (const auto& reward : rewards)
    {
        cumulative += reward.chance;
        if (roll <= cumulative)
        {
            return reward.name;
        }
    }

    return "Nothing";
}

int main()
{
    vector<Reward> box = {
        {"Gold", 40.f},
        {"Potion", 25.f},
        {"Gem", 10.f},
        {"Rare Sword", 5.f},
        {"Nothing", 20.f}
    };

    cout << "Opening the box...\n";

    string reward = OpenRewardBox(box);
    cout << "You got: " << reward << endl;

    return 0;
}
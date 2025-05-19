
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;


unordered_map<string, float> cooldowns;

const float FIREBALL_COOLTIME = 5.0f;
const string FIRE_BALL = "FireBall";
const string DASH = "Dash";

bool UseSkill(const string& skillName, float cooldownTime)
{
    if (cooldowns[skillName] <= 0.0f)
    {
        cooldowns[skillName] = cooldownTime;
        cout << "Used " << skillName << '\n';
        return true;
    }
    else
    {
        cout << skillName << " is cooling down: " << cooldowns[skillName] << "s left\n";
        return false;
    }
}

void Update(float deltaTime)
{
    for (auto& [skill, time] : cooldowns)
    {
        time = max(0.0f, time - deltaTime);
    }
}

int main()
{
    cooldowns[FIRE_BALL] = 0.0f;
    cooldowns[DASH] = 0.0f;

    UseSkill(FIRE_BALL, FIREBALL_COOLTIME);
    UseSkill(DASH, 3.0f);

    Update(2.0f);
    
    UseSkill(FIRE_BALL, FIREBALL_COOLTIME);
    
    Update(3.0f);

    // 이제 사용 가능
    UseSkill(FIRE_BALL, FIREBALL_COOLTIME);

    return 0;
}
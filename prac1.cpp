
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


int main()
{
    int N = 3;

    vector<float> score = {40, 80, 60};

    float max = *max_element(score.begin(), score.end());

    float result = 0;
    for (int i = 0; i < N; i++)
    {
        result += score[i] / max * 100;
    }
    result = result / N;

    cout << result << "\n";

    return 0;
}

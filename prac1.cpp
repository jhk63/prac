
#include <iostream>
#include <iomanip>
using namespace std;


int main()
{
    int C;
    cin >> C;

    for (int i = 0; i < C; i++)
    {
        int N;
        cin >> N;

        float average = 0;
        int scores[N];
        for (int j = 0; j < N; j++)
        {
            cin >> scores[j];
            average += scores[j];
        }
        average /= N;

        float result = 0;
        for (int j = 0; j < N; j++)
        {
            if (scores[j] > average)
            {
                result += 1;
            }
        }

        cout << fixed << setprecision(3) << (result / N) * 100 << "%\n";
    }

    return 0;
}


/*
*   첫 번째 코드는 직관적이지 않고 공식의 숫자의 의미를 파악하려면 분석이 필요
*   두 번째 코드는 매핑으로 명시적으로 표현해, 규칙을 쉽게 파악할 수 있고 별도 예외 처리가 불필요
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    // string a = "ABC DEF GHI JKL MNO PQRS TUV WXYZ";
    //              111 222 333 444 555 6667 778 8899
    //              111 222 333 444 555 6666 777 8888

    string s;
    // s = "WA";        // 13
    // s = "UNUCIC";    // 36
    cin >> s;

    // Wrong
    vector<int> index;
    for (auto word : s)
    {
        if (word == 'S' || word == 'V' || word == 'Y' || word == 'Z')
        {
            index.push_back(((int)word - 62) / 3 - 1);
            continue;
        }
        
        index.push_back(((int)word - 62) / 3);
    }

    int result = 0;
    for (auto i : index)
    {
        result += 2 + i;
    }
    cout << result << '\n';

    return 0;
}

void Another()
{
    // string a = "ABC DEF GHI JKL MNO PQRS TUV WXYZ";
    //              111 222 333 444 555 6667 778 8899
    //              111 222 333 444 555 6666 777 8888
    int number[26] = { 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 10, 10, 10, 10 };

    string s;
    // s = "WA";        // 13
    // s = "UNUCIC";    // 36
    cin >> s;

    int result = 0;
    for (auto word : s)
    {
        int index = (int)(word - 'A');
        result += number[index];
    }

    cout << result << '\n';
}

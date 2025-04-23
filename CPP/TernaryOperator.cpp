
#include <iostream>
using namespace std;


int main()
{
    // 조건 ? true 반환값 : false 반환값
    int a = 7;
    cout << ((a % 2 == 0) ? "Even" : "Odd") << endl;

    int b = -22;
    cout << ((b >= 0) ? b : -1 * b) << endl;

    // 조건식 ? true 반환값 : 다음 조건
    int score = 45;
    cout << ((score >= 90) ? "A" : 
        (score >= 80) ? "B" : 
        (score >= 70) ? "C" : "F") << endl;
    
    return 0;
}


#include <iostream>
#include <vector>
using namespace std;


void printNums(const vector<int> numbers)
{
    for (const auto num : numbers)
    {
        cout << num << " ";
    }
    cout << '\n';
}

int main()
{
    vector<int> numbers = {1, 2, 3};

    // 값 복사 (Value Copy) 방식
    for (auto num : numbers)
    {
        num = 10;
    }
    printNums(numbers);
    
    // 참조 (Reference) 방식
    for (auto& num : numbers)
    {
        num = 10;
    }
    printNums(numbers);

    return 0;
}

#include <iostream>
using namespace std;

#include "LinkedList.cpp"


int main()
{
    cout << "Running LinkedList tests...\n"
         << endl;

    // 테스트 결과 출력 헬퍼 함수
    auto printTestResult = [](const string &testName, bool passed)
    {
        cout << "Test " << testName << ": " << (passed ? "PASSED" : "FAILED") << endl;
    };

    int testCount = 0;
    int passedCount = 0;

    // 테스트 1: 빈 리스트 생성 및 isEmpty 확인
    {
        LinkedList list;
        bool passed = list.isEmpty();
        printTestResult("Empty list isEmpty", passed);
        testCount++;
        if (passed)
            passedCount++;
    }

    // 테스트 2: append로 노드 추가
    {
        LinkedList list;
        list.append(10);
        bool passed = list.size() == 1 && list.getNode(0)->item == 10;
        printTestResult("Append single node", passed);
        testCount++;
        if (passed)
            passedCount++;
    }

    // 테스트 3: 여러 노드 append
    {
        LinkedList list;
        list.append(10);
        list.append(20);
        list.append(30);
        bool passed = list.size() == 3 &&
                      list.getNode(0)->item == 10 &&
                      list.getNode(1)->item == 20 &&
                      list.getNode(2)->item == 30;
        printTestResult("Append multiple nodes", passed);
        testCount++;
        if (passed)
            passedCount++;
    }

    // 테스트 4: insert at valid index
    {
        LinkedList list;
        list.append(10);
        list.append(30);
        list.insert(20, 1);
        bool passed = list.size() == 3 &&
                      list.getNode(0)->item == 10 &&
                      list.getNode(1)->item == 20 &&
                      list.getNode(2)->item == 30;
        printTestResult("Insert at valid index", passed);
        testCount++;
        if (passed)
            passedCount++;
    }

    // 테스트 5: insert at invalid index
    {
        LinkedList list;
        list.append(10);
        list.insert(20, 5); // 유효하지 않은 인덱스
        bool passed = list.size() == 1 && list.getNode(0)->item == 10;
        printTestResult("Insert at invalid index", passed);
        testCount++;
        if (passed)
            passedCount++;
    }

    // 테스트 6: pop at index 0
    {
        LinkedList list;
        list.append(10);
        list.append(20);
        list.pop(0);
        bool passed = list.size() == 1 && list.getNode(0)->item == 20;
        printTestResult("Pop at index 0", passed);
        testCount++;
        if (passed)
            passedCount++;
    }

    // 테스트 7: pop at middle index
    {
        LinkedList list;
        list.append(10);
        list.append(20);
        list.append(30);
        list.pop(1);
        bool passed = list.size() == 2 &&
                      list.getNode(0)->item == 10 &&
                      list.getNode(1)->item == 30;
        printTestResult("Pop at middle index", passed);
        testCount++;
        if (passed)
            passedCount++;
    }

    // 테스트 8: pop at invalid index
    {
        LinkedList list;
        list.append(10);
        list.pop(5); // 유효하지 않은 인덱스
        bool passed = list.size() == 1 && list.getNode(0)->item == 10;
        printTestResult("Pop at invalid index", passed);
        testCount++;
        if (passed)
            passedCount++;
    }

    // 테스트 9: remove by value (existing value)
    {
        LinkedList list;
        list.append(10);
        list.append(20);
        list.append(30);
        list.remove(20);
        bool passed = list.size() == 2 &&
                      list.getNode(0)->item == 10 &&
                      list.getNode(1)->item == 30;
        printTestResult("Remove existing value", passed);
        testCount++;
        if (passed)
            passedCount++;
    }

    // 테스트 10: remove by value (non-existing value)
    {
        LinkedList list;
        list.append(10);
        list.remove(99); // 존재하지 않는 값
        bool passed = list.size() == 1 && list.getNode(0)->item == 10;
        printTestResult("Remove non-existing value", passed);
        testCount++;
        if (passed)
            passedCount++;
    }

    // 테스트 11: findNode with existing value
    {
        LinkedList list;
        list.append(10);
        list.append(20);
        Node *node = list.findNode(20);
        bool passed = node != nullptr && node->item == 20;
        printTestResult("FindNode existing value", passed);
        testCount++;
        if (passed)
            passedCount++;
    }

    // 테스트 12: findNode with non-existing value
    {
        LinkedList list;
        list.append(10);
        Node *node = list.findNode(99);
        bool passed = node == nullptr;
        printTestResult("FindNode non-existing value", passed);
        testCount++;
        if (passed)
            passedCount++;
    }

    // 테스트 13: findIndex with existing value
    {
        LinkedList list;
        list.append(10);
        list.append(20);
        int index = list.findIndex(20);
        bool passed = index == 1;
        printTestResult("FindIndex existing value", passed);
        testCount++;
        if (passed)
            passedCount++;
    }

    // 테스트 14: findIndex with non-existing value
    {
        LinkedList list;
        list.append(10);
        int index = list.findIndex(99);
        bool passed = index == -2;
        printTestResult("FindIndex non-existing value", passed);
        testCount++;
        if (passed)
            passedCount++;
    }

    // 테스트 15: getNode with valid index
    {
        LinkedList list;
        list.append(10);
        list.append(20);
        Node *node = list.getNode(1);
        bool passed = node != nullptr && node->item == 20;
        printTestResult("GetNode valid index", passed);
        testCount++;
        if (passed)
            passedCount++;
    }

    // 테스트 16: getNode with invalid index
    {
        LinkedList list;
        list.append(10);
        Node *node = list.getNode(5);
        bool passed = node == nullptr;
        printTestResult("GetNode invalid index", passed);
        testCount++;
        if (passed)
            passedCount++;
    }

    // 테스트 17: clear list
    {
        LinkedList list;
        list.append(10);
        list.append(20);
        list.clear();
        bool passed = list.isEmpty() && list.size() == 0;
        printTestResult("Clear list", passed);
        testCount++;
        if (passed)
            passedCount++;
    }

    // 테스트 18: isValidIndex with valid and invalid indices
    {
        LinkedList list;
        list.append(10);
        bool passed = list.isValidIndex(0) && !list.isValidIndex(5);
        printTestResult("IsValidIndex valid and invalid", passed);
        testCount++;
        if (passed)
            passedCount++;
    }

    // 테스트 19: size after multiple operations
    {
        LinkedList list;
        list.append(10);
        list.append(20);
        list.pop(0);
        list.append(30);
        bool passed = list.size() == 2;
        printTestResult("Size after operations", passed);
        testCount++;
        if (passed)
            passedCount++;
    }

    // 테스트 20: pop from empty list
    {
        LinkedList list;
        list.pop(0);
        bool passed = list.size() == 0;
        printTestResult("Pop from empty list", passed);
        testCount++;
        if (passed)
            passedCount++;
    }

    // 최종 결과 출력
    cout << "\nTest Summary: " << passedCount << "/" << testCount << " tests passed" << endl;

    return 0;
}

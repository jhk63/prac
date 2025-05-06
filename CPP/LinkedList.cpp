
#include <iostream>
using namespace std;

/**
 *  Represents a node in a singly linked list.
 */
class Node
{
public:
    int item;
    Node* next;

    Node(int value) : item(value), next(nullptr) {}
    Node(int value, Node *nextNode) : item(value), next(nextNode) {}
};

class LinkedList
{
private:
    Node* head;
    int nodeCount;

public:
    LinkedList() : head(nullptr), nodeCount(0) {}
    ~LinkedList()
    {
        clear();
    }

    /**
     * @brief Inserts a value at the specified index.
     * @param value The value to insert.
     * @param index The index where the value should be inserted (0 to nodeCount).
     */
    void insert(int value, int index)
    {
        if (!isValidIndex(index)) return;

        if (index == 0) 
        {
            head = new Node(value, head);
        }
        else
        {
            Node* prevNode = getNode(index - 1);
            if (!prevNode) return;

            Node* newNode = new Node(value, prevNode->next);
            prevNode->next = newNode;
        }

        nodeCount += 1;
    }

    /**
     * @brief Appends a value to the end of the list.
     * @param value The value to append.
     */
    void append(int value)
    {
        Node* newNode = new Node(value);

        if (isEmpty())
        {
            head = newNode;
        }
        else
        {
            Node* prevNode = getNode(nodeCount - 1);
            if (!prevNode) return;
    
            prevNode->next = newNode;
        }

        nodeCount += 1;
    }

    /**
     * @brief Removes the node at the specified index.
     * @param index The index of the node to remove (0 to nodeCount-1).
     */
    void pop(int index)
    {
        if (isEmpty() || !isValidIndex(index)) return;

        Node* currNode;
        if (index == 0)
        {
            currNode = head;
            head = currNode->next;
        }
        else
        {
            Node* prevNode = getNode(index - 1);
            if (!prevNode) return;

            currNode = prevNode->next;
            prevNode->next = currNode->next;
        }

        delete currNode;
        nodeCount -= 1;
    }

    /**
     * @brief Removes the first node with the specified value.
     * @param value The value to remove.
     */
    void remove(int value)
    {
        int index = findIndex(value);
        if (index == -2) return;

        Node* currNode;
        if (index == 0)
        {
            currNode = head;
            head = currNode->next;
        }
        else
        {
            Node* prevNode = getNode(index - 1);
            if (!prevNode) return;

            currNode = prevNode->next;
            prevNode->next = currNode->next;
        }

        delete currNode;
        nodeCount -= 1;
    }

    /**
     * @brief Clears all nodes in the list.
     */
    void clear()
    {
        Node* currNode = head;
        while (currNode != nullptr)
        {
            Node* next = currNode->next;
            delete currNode;
            currNode = next;
        }

        head = nullptr;
        nodeCount = 0;
    }

    /**
     * @brief Prints all values in the list.
     */
    void printList()
    {
        Node* currNode = head;
        while (currNode != nullptr)
        {
            cout << currNode->item << " ";
            currNode = currNode->next;
        }
        cout << "\n";
    }

    /**
     * @brief Finds the first node with the specified value.
     * @param value The value to search for.
     * @return Pointer to the node, or nullptr if not found.
     */
    Node* findNode(int value)
    {
        if (isEmpty()) return nullptr;

        int index = findIndex(value);
        if (index == -2) return nullptr;

        return getNode(index);
    }

    /**
     * @brief Gets the node at the specified index.
     * @param index The index of the node (0 to nodeCount-1).
     * @return Pointer to the node, or nullptr if invalid.
     */
    Node* getNode(int index)
    {
        if (isEmpty() || !isValidIndex(index)) return nullptr;

        Node* currNode = head;
        for (int i = 0; i < index; i++)
        {
            currNode = currNode->next;
        }

        return currNode;
    }

    /**
     * @brief Finds the index of the first node with the specified value.
     * @param value The value to search for.
     * @return The index of the node, or -2 if not found.
     */
    int findIndex(int value)
    {
        if (isEmpty()) return -2;

        int index = 0;
        Node* currNode = head;
        while (currNode != nullptr)
        {
            if (currNode->item == value)
            {
                return index;
            }

            currNode = currNode->next;
            index += 1;
        }

        return -2;
    }

    /**
     * @brief Checks if the index is valid for insertion or access.
     * @param index The index to check.
     * @return True if the index is valid (0 to nodeCount), false otherwise.
     */
    bool isValidIndex(int index) 
    {
        bool result = (index >= 0 && index <= nodeCount);
        if (!result) 
        { 
            // cout << "index is out of range!" << "\n";
            return false;
        }
        return true;
    }

    /**
     * @brief Checks if the list is empty.
     * @return True if the list is empty, false otherwise.
     */
    bool isEmpty() 
    {
        bool result = (head == nullptr);
        if (result)
        {
            // cout << "head is empty!" << "\n";
            return true;
        }
        return false;
    }

    /**
     * @brief Returns the number of nodes in the list.
     * @return The size of the list.
     */
    int size() 
    { 
        return nodeCount; 
    }
};

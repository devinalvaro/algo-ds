/* Linked List with double pointer */

#include <iostream>
#include <limits>

using namespace std;

class LinkedListNode
{
private:
    int data;

public:
    LinkedListNode *prev_node;
    LinkedListNode *next_node;

    LinkedListNode(int _data, LinkedListNode *_prev_node, LinkedListNode *_next_node)
    {
        data = _data;
        prev_node = _prev_node;
        next_node = _next_node;
    }

    ~LinkedListNode() { delete next_node; }

    int getData() { return data; }
};

class LinkedList
{
private:
    LinkedListNode *head;
    LinkedListNode *tail;

public:
    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    ~LinkedList()
    {
        delete head;
        delete tail;
    }

    void push_front(int data)
    {
        if (head == nullptr) {
            head = tail = new LinkedListNode(data, nullptr, nullptr);

            return;
        }

        head->prev_node = new LinkedListNode(data, nullptr, head);
        head->prev_node->next_node = head;
        head = head->prev_node;
    }

    void pop_front()
    {
        if (head == nullptr)
            return;

        if (head == tail) {
            head = nullptr;
            tail = nullptr;

            return;
        }

        head = head->next_node;
        head->prev_node = nullptr;
    }

    void push_back(int data)
    {
        if (tail == nullptr) {
            head = tail = new LinkedListNode(data, nullptr, nullptr);

            return;
        }

        tail->next_node = new LinkedListNode(data, tail, nullptr);
        tail->next_node->prev_node = tail;
        tail = tail->next_node;
    }

    void pop_back()
    {
        if (tail == nullptr)
            return;

        if (head == tail) {
            head = nullptr;
            tail = nullptr;

            return;
        }

        tail = tail->prev_node;
        tail->next_node = nullptr;
    }

    int get_head_data() { return head->getData(); }

    int get_tail_data() { return tail->getData(); }
};

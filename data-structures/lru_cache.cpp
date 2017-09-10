#include <unordered_map>

using namespace std;

struct Node {
    Node *nextNode = nullptr;
    Node *prevNode = nullptr;
    int pageNumber;

    Node(int _pageNumber) { pageNumber = _pageNumber; }
};

class LruCache
{
private:
    // hash map
    unordered_map<int, Node *> hashMap;

    // deque
    Node *head = nullptr;
    Node *tail = nullptr;
    int cacheAmount = 0;
    int cacheCapacity;

    bool isCacheFull() { return cacheAmount == cacheCapacity; }

    bool isCacheEmpty() { return cacheAmount == 0; }

    void enqueue(int pageNumber)
    {
        if (isCacheFull()) {
            dequeue();
        }

        Node *temp = new Node(pageNumber);
        temp->nextNode = head;

        if (isCacheEmpty()) {
            tail = temp;
        } else {
            head->prevNode = temp;
        }
        head = temp;

        cacheAmount++;
    }

    void dequeue()
    {
        if (isCacheEmpty())
            return;

        if (head == tail) {
            head = nullptr;
        }

        Node *temp = tail;
        tail = tail->prevNode;
        if (tail) {
            tail->nextNode = nullptr;
        }
        delete temp;

        cacheAmount--;
    }

public:
    LruCache(int _cacheCapacity) { cacheCapacity = _cacheCapacity; }

    void insertPage(int pageNumber)
    {
        if (isCacheFull()) {
            hashMap[tail->pageNumber] = nullptr;
        }

        enqueue(pageNumber);

        hashMap[pageNumber] = head;
    }

    void referPage(int pageNumber)
    {
        Node *page = hashMap[pageNumber];

        if (!page) {
            insertPage(pageNumber);
        } else if (page != head) {
            page->prevNode->nextNode = page->nextNode;

            if (page->nextNode) {
                page->nextNode->prevNode = page->prevNode;
            }

            if (page == tail) {
                tail = tail->prevNode;
                tail->nextNode = nullptr;
            }

            page->nextNode = head;
            page->prevNode = nullptr;

            head->prevNode = page;
            head = page;
        }
    }
};

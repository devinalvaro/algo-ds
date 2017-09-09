#include <vector>

using namespace std;

class Node
{
public:
    Node *prevNode = nullptr;
    Node *nextNode = nullptr;
    int pageNumber;

    Node(int _pageNumber) { pageNumber = _pageNumber; }
};

class Queue
{
public:
    Node *frontNode = nullptr;
    Node *rearNode = nullptr;
    int numberOfFrames;
    int numberOfFilledFrames = 0;

    Queue(int _numberOfFrames) { numberOfFrames = _numberOfFrames; }

    bool isEmpty() { return rearNode == nullptr; }

    bool isFull() { return numberOfFilledFrames == numberOfFrames; }

    void dequeue()
    {
        if (isEmpty())
            return;

        if (frontNode == rearNode) {
            frontNode = nullptr;
        }

        Node *temp = rearNode;
        rearNode = rearNode->prevNode;
        if (rearNode != nullptr) {
            rearNode->nextNode = nullptr;
        }
        delete temp;

        numberOfFilledFrames--;
    }
};

class LruCache
{
public:
    Queue frameQueue;
    vector<Node *> pageArray;
    int numberOfPages;

    LruCache(int numberOfFrames, int _numberOfPages)
        : frameQueue(numberOfFrames)
    {
        numberOfPages = _numberOfPages;

        pageArray = vector<Node *>(numberOfPages);
    }

    void insertPage(int pageNumber)
    {
        if (frameQueue.isFull()) {
            pageArray[frameQueue.rearNode->pageNumber] = nullptr;
            frameQueue.dequeue();
        }

        Node *temp = new Node(pageNumber);
        temp->nextNode = frameQueue.frontNode;

        if (frameQueue.isEmpty()) {
            frameQueue.rearNode = temp;
        } else {
            frameQueue.frontNode->prevNode = temp;
        }
        frameQueue.frontNode = temp;

        pageArray[pageNumber] = temp;

        frameQueue.numberOfFilledFrames++;
    }

    void getPage(int pageNumber)
    {
        Node *requestedPage = pageArray[pageNumber];

        if (requestedPage == nullptr) {
            insertPage(pageNumber);
        } else if (requestedPage != frameQueue.frontNode) {
            requestedPage->prevNode->nextNode = requestedPage->nextNode;

            if (requestedPage->nextNode != nullptr) {
                requestedPage->nextNode->prevNode = requestedPage->prevNode;
            }

            if (requestedPage == frameQueue.rearNode) {
                frameQueue.rearNode = frameQueue.rearNode->prevNode;
                frameQueue.rearNode->nextNode = nullptr;
            }

            requestedPage->nextNode = frameQueue.frontNode;

            frameQueue.frontNode->prevNode = requestedPage;
            frameQueue.frontNode = requestedPage;
        }
    }
};

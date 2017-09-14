#include <list>
#include <unordered_map>

using namespace std;

class LRUCache
{
private:
    int capacity;
    unordered_map<int, list<pair<int, int>>::iterator> pageMap;
    list<pair<int, int>> pageList;

public:
    LRUCache(int capacity) { this->capacity = capacity; }

    int get(int key)
    {
        auto page = pageMap.find(key);

        if (page == pageMap.end()) // key doesn't exist
            return -1;

        pageList.splice(pageList.begin(), pageList, page->second);

        return page->second->second;
    }

    void put(int key, int value)
    {
        auto page = pageMap.find(key);

        if (page != pageMap.end()) { // key already exists
            page->second->second = value;
            pageList.splice(pageList.begin(), pageList, page->second);

            return;
        }

        if ((int)pageMap.size() == capacity) {
            pageMap.erase(pageList.back().first);
            pageList.pop_back();
        }

        pageList.emplace_front(make_pair(key, value));
        pageMap[key] = pageList.begin();
    }
};

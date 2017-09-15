#include <list>
#include <unordered_map>

using namespace std;

class LruCache
{
private:
    int cacheCapacity;
    unordered_map<int, list<pair<int, int>>::iterator> pageMap;
    list<pair<int, int>> pageList;

public:
    LruCache(int cacheCapacity) { this->cacheCapacity = cacheCapacity; }

    int get(int key)
    {
        auto page = pageMap.find(key);

        if (page == pageMap.end())
            return -1;

        pageList.splice(pageList.begin(), pageList, page->second);

        return page->second->second;
    }

    void put(int key, int value)
    {
        auto page = pageMap.find(key);

        if (page != pageMap.end()) {
            page->second->second = value;
            pageList.splice(pageList.begin(), pageList, page->second);

            return;
        }

        if ((int)pageMap.size() == cacheCapacity) {
            pageMap.erase(pageList.back().first);
            pageList.pop_back();
        }

        pageList.emplace_front(make_pair(key, value));
        pageMap[key] = pageList.begin();
    }
};

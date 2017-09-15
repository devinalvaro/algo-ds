#include <list>
#include <unordered_map>

using namespace std;

template <class T>
class LruCache
{
private:
    const int cacheCapacity;
    unordered_map<int, typename list<pair<int, T>>::iterator> pageMap;
    list<pair<int, T>> pageList;

public:
    LruCache(int _cacheCapacity) : cacheCapacity(_cacheCapacity) {}

    T get(int key);

    void put(int key, T value)
    {
        auto page = pageMap.find(key);

        if (page != pageMap.end()) {
            pageList.splice(pageList.begin(), pageList, page->second);
            pageList.begin()->second = value;

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

template <class T>
T LruCache<T>::get(int key)
{
    auto page = pageMap.find(key);

    if (page == pageMap.end())
        return -1;

    pageList.splice(pageList.begin(), pageList, page->second);

    return pageList.begin()->second;
}

#include <bits/stdc++.h>
using namespace std;

/**
 * Not a thread safe implementation
 */ 
template <typename K, typename V>
class LRU {
    
    list<const V> cacheDQ;
    // function<size_t(K key)> hashingFn;
    class hashClass;// = std::hash<Key>
    unordered_map<K, list<const V>::iterator, hashClass> cacheMap;
    function<const K(const V &ele)> getKey;
    int capacity;
    
    void insert(const V &ele) {
        if(cacheDQ.size()==capacity) {
            del(getKey(cacheDQ.back()));
        }
        cacheDQ.push_front(V);
        cacheMap[getKey(V)] = cacheDQ.begin();
    }
    
    public:
    LRU(int capacity, function<K(const V &ele)> getKey): 
    capacity(capacity), 
    getKey(getKey),
    hashClass(std::hash<K>) {
        if(capacity<1) {
            throw new string("Invalid Capacity");
        }
    }
    
    void put(const V &ele) {
        del(getKey(ele));
        insert(ele);
    }
    
    void del(const K &key) {
        if(cacheMap.find(key)!=cacheMap.end()) {
            cacheDQ.erase(cacheMap[key]);
            cacheMap.erase(key);
        }
    }
    
    const V* get(const K &key) {
        if(cacheMap.find(key)==cacheMap.end()) {
            return NULL;
        }
        put(*cacheMap[key]);
        return &(*cacheMap[key]);
    }
};

int main() {
	LRU<string, string> lruTest = LRU(3, [&](const string &x){ return x;});
	lruTest.put("a", "value-a");
	lruTest.put("b", "value-b");
	lruTest.put("c", "value-c");
	auto value = lruTest.get("a");
	if(value!=NULL) {
	    cout<<(*value)<<"\n";
	}
	return 0;
}

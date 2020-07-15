#include <bits/stdc++.h>
using namespace std;

// ****************** LRU Class ******************************************************

/**
 * Not a thread safe implementation
 */ 
template <typename K, typename V, typename Hash = hash<K>>
class LRU {
    
    list<pair<const K, const V>> cacheDQ;
    unordered_map<const K, typename list<pair<const K, const V>>::iterator, Hash> cacheMap;
    int capacity;
    
    void insert(const K &key, const V &value) {
        if(cacheDQ.size()==capacity) {
            auto leastRecentElement = cacheDQ.front();
            del(leastRecentElement.first);
        }
        cacheDQ.push_back({key, value});
        cacheMap[key] = prev(cacheDQ.end());
    }
    
    public:
    
    LRU(int capacity):  capacity(capacity) {
        if(capacity<1) {
            throw new string("Invalid Capacity");
        }
    }
    
    void put(const K &key, const V &value) {
        del(key);
        insert(key, value);
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
        auto &cachedEntry = cacheMap[key];
        put(cachedEntry->first, cachedEntry->second);
        return &(cacheMap[key]->second);
    }
};

// ******************************************************************************************

/* **********************************************
 * Example Usages
 * **********************************************
 */
void normalStringTest() {
    cout<<"----- normalStringTest Start ----------\n";
    LRU<string, string> lruTest = LRU<string, string>(3);
	lruTest.put("a", "value-a");
	lruTest.put("b", "value-b");
	lruTest.put("c", "value-c");
// 	auto value = lruTest.get("a");
// 	if(value!=NULL) {
// 	    cout<<(*value)<<"\n";
// 	}
    lruTest.put("b", "value-x");
    lruTest.put("b", "value-x");
    lruTest.put("b", "value-x");
	lruTest.put("d", "value-d");
	auto value = lruTest.get("a");
	if(value!=NULL) {
	    cout<<(*value)<<"\n";
	}
	value = lruTest.get("c");
	if(value!=NULL) {
	    cout<<(*value)<<"\n";
	}
	cout<<"----- normalStringTest End ----------\n";
}

class CustomClass {
    public:
    int a;
    string b;
    CustomClass(int a, string b): a(a), b(b) {}
    
    bool operator==(const CustomClass &other) const { 
        return (a == other.a && b == other.b);
    }
};

void customClassAsValueTest() {
    cout<<"----- customClassAsValueTest Start ----------\n";
    LRU<string, CustomClass> lruTest = LRU<string, CustomClass>(3);
    lruTest.put("a", CustomClass(1, "val-a"));
	lruTest.put("b", CustomClass(1, "val-b"));
	lruTest.put("c", CustomClass(1, "val-c"));
	auto value = lruTest.get("a");
	if(value!=NULL) {
	    cout<<value->a<<" "<<value->b<<"\n";
	}
    lruTest.put("b", CustomClass(2, "val-b"));
    lruTest.put("b", CustomClass(3, "val-b"));
	lruTest.put("d", CustomClass(1, "val-d"));
	value = lruTest.get("a");
	if(value!=NULL) {
	    cout<<value->a<<" "<<value->b<<"\n";
	}
	value = lruTest.get("b");
	if(value!=NULL) {
	    cout<<value->a<<" "<<value->b<<"\n";
	}
	value = lruTest.get("c");
	if(value!=NULL) {
	    cout<<value->a<<" "<<value->b<<"\n";
	}
	value = lruTest.get("d");
	if(value!=NULL) {
	    cout<<value->a<<" "<<value->b<<"\n";
	}
	cout<<"----- customClassAsValueTest End ----------\n";
}

struct CustomClassKeyHasher {
    std::size_t operator()(const CustomClass& obj) const {
      return hash<int>()(obj.a)^hash<string>()(obj.b);
    }
};

void customClassAsKeyTest() {
    cout<<"----- customClassAsKeyTest Start ----------\n";
    LRU<CustomClass, CustomClass, CustomClassKeyHasher> lruTest = LRU<CustomClass, CustomClass, CustomClassKeyHasher>(3);
    lruTest.put(CustomClass(1, "a"), CustomClass(1, "val-a"));
	lruTest.put(CustomClass(1, "b"), CustomClass(1, "val-b"));
	lruTest.put(CustomClass(1, "c"), CustomClass(1, "val-c"));
	auto value = lruTest.get(CustomClass(1, "a"));
	if(value!=NULL) {
	    cout<<value->a<<" "<<value->b<<"\n";
	}
    lruTest.put(CustomClass(1, "b"), CustomClass(2, "val-b"));
    lruTest.put(CustomClass(1, "b"), CustomClass(3, "val-b"));
	lruTest.put(CustomClass(1, "d"), CustomClass(1, "val-d"));
	value = lruTest.get(CustomClass(1, "a"));
	if(value!=NULL) {
	    cout<<value->a<<" "<<value->b<<"\n";
	}
	value = lruTest.get(CustomClass(1, "b"));
	if(value!=NULL) {
	    cout<<value->a<<" "<<value->b<<"\n";
	}
	value = lruTest.get(CustomClass(1, "c"));
	if(value!=NULL) {
	    cout<<value->a<<" "<<value->b<<"\n";
	}
	value = lruTest.get(CustomClass(1, "d"));
	if(value!=NULL) {
	    cout<<value->a<<" "<<value->b<<"\n";
	}
	cout<<"----- customClassAsKeyTest End ----------\n";
}

int main() {
	normalStringTest();
	customClassAsValueTest();
	customClassAsKeyTest();
	return 0;
}

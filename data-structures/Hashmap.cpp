#include <bits/stdc++.h>
using namespace std;

template<typename K, typename V> 
class HashMap {
  
  static const int default_size = 10;
  forward_list<pair<K,V>> arr[default_size];
  int current_elements;
  function<int(K key)> hashingFunction;
  
  static int defaultHashingFunction(K key) {
    return 0;
  }
  
  int getIdx(K key) {    
    int hash = hashingFunction(key);
    return hash%default_size;
  }
  
  public:
  
  HashMap(): hashingFunction(defaultHashingFunction) {}
  HashMap(function<int(K key)> customHashingFunction): hashingFunction(customHashingFunction) {}
  
  void put(K key, V value) { 
    V* vPtr = get(key);
    if(vPtr==NULL){
      int idx = getIdx(key);
      arr[getIdx(key)].push_front({key,value});
    } else {
      *vPtr = value;
    }
  }
  
  V* get(K key) {
    int idx = getIdx(key);
    forward_list<pair<K,V>> &targetList = arr[idx];    
    for(auto &x: targetList ){
        if(x.first==key){
          return &x.second;
        }
    }
    return NULL;    
  }
};

int main() {

  HashMap<int,int> hashMapTest = HashMap<int,int>([](int a){return a;});
  
  hashMapTest.put(1,6);
  int * x = hashMapTest.get(1);
  cout<<*x;
  
  hashMapTest.put(1,7);
  x = hashMapTest.get(1);
  cout<<*x;
  
  hashMapTest.put(3,7);
  x = hashMapTest.get(1);
  cout<<*x;
  return 0;
}

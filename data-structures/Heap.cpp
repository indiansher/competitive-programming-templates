#include<bits/stdc++.h>

/*
 * !!!NOT A Thread Safe Implementation!!!
 */
template <typename T> 
class Heap {
    
    // Can be populated by providing a comparator function
    // Eg: MaxHeap: std::greater<T>(), 
    // Eg: MinHeap: std::less<T>()
    std::function<bool(const T&,const T&)> heapCompareFn;
    std::vector<T> vec;
    
    int getParentIdx(int x) { return (x-1)/2; }
    int getLeftChildIdx(int x) { return (2*x)+1; }
    int getRightChildIdx(int x) { return (2*x)+2; }
    bool hasLeftChild(int x) { return getLeftChildIdx(x)<vec.size(); }
    bool hasRightChild(int x) { return getRightChildIdx(x)<vec.size(); }

    void convertToHeap() {
        int n = vec.size();
        for(int i=(n/2)-1;i>=0;i--) { heapifyDown(i); }
    }

    void heapifyDown(int idx) {
        if(idx<0 || idx>=vec.size()) {
            return;
        }
        while(1) {
            if(!hasLeftChild(idx)) { break; }
            int baseIdx = getLeftChildIdx(idx);
            T baseElement = vec[baseIdx];
            
            if(hasRightChild(idx)) {
                int tempIdx = getRightChildIdx(idx);
                T tempElement = vec[tempIdx];
                if(heapCompareFn(tempElement, baseElement)) {
                    baseElement = tempElement;
                    baseIdx = tempIdx;
                }
            }
            
            if(heapCompareFn(baseElement, vec[idx])) {
                std::swap(vec[baseIdx], vec[idx]);
                idx=baseIdx;
            } else {
                break;
            }
        }
    }
    
    void heapifyUp(int idx) {
        if(idx<0 || idx>=vec.size()) {
            return;
        }
        while(idx>0) {
            int parentIdx = getParentIdx(idx);
            if(heapCompareFn(vec[idx], vec[parentIdx])) {
                std::swap(vec[idx], vec[parentIdx]);
                idx=parentIdx;
            } else {
                break;
            }
        }
    }
    
    public:
    
    Heap(std::function<bool(const T&,const T&)> comparator): heapCompareFn(comparator){}
    
    Heap(std::function<bool(const T&,const T&)> comparator, std::vector<T> vec): heapCompareFn(comparator), vec(vec) {
        convertToHeap();
    }
    
    void push(T ele) {
        vec.push_back(ele);
        heapifyUp(vec.size()-1);
    }
    
    T poll() {
        if(vec.size()<1) {
            throw std::string("Heap is Empty!!");
        }
        T element = vec[0];
        vec[0] = vec[vec.size()-1];
        vec.pop_back();
        heapifyDown(0);
        return element;
    }
    
    std::vector<T> getSorted() {
        std::vector<T> copyOfCurrentVec = vec, sortedVec;
        while(vec.size()>0) { sortedVec.push_back(poll()); }
        vec = copyOfCurrentVec;
        return sortedVec;
    }
    
    std::vector<T> getHeap() {
        return vec;
    }
    
    int size() {
        return vec.size();
    }
};


/**
 * Examples 
 */
void minHeapTest() {
    std::cout<<"----------MinHeap Test (Start)----------\n";
    std::vector<double> vec = {2.112, 3.5, 5.5, 2.1, 1};
    Heap<double> minHeap = Heap<double>(std::less<double>(), vec);
    std::vector<double> sorted = minHeap.getSorted();
	for(auto &num : sorted) { std::cout<<num<<" "; }
	std::cout<<std::endl;
	std::vector<double> heap = minHeap.getHeap();
	for(auto &num : heap) { std::cout<<num<<" "; }
	std::cout<<std::endl;
	std::cout<<"----------MinHeap Test (End)----------\n";
}

void maxHeapTest() {
    std::cout<<"----------MaxHeap Test (Start)----------\n";
    std::vector<double> vec = {2.112, 3.5, 5.5, 2.1, 1};
    Heap<double> maxHeap = Heap<double>(std::greater<double>(), vec);
    std::vector<double> sorted = maxHeap.getSorted();
	for(auto &num : sorted) { std::cout<<num<<" "; }
	std::cout<<std::endl;
	std::vector<double> heap = maxHeap.getHeap();
	for(auto &num : heap) { std::cout<<num<<" "; }
	std::cout<<std::endl;
	std::cout<<"----------MaxHeap Test (End)----------\n";
}

bool pairLessThanByFirst(const std::pair<int, int> &lhs, const std::pair<int, int> &rhs) {
    return lhs.first < rhs.first;
}
void minHeapByVecIndexTest() {
    std::cout<<"----------MinHeap [Maintain Index] Test (Start)----------\n";
    std::vector<int> vec = {2, 3, 5, 21, 1, 9, 12};
    Heap<std::pair<int, int>> minPairHeap = Heap<std::pair<int, int>>(pairLessThanByFirst);
    for(int i=0;i<vec.size();i++) {
        minPairHeap.push({vec[i], i});
    }
    auto sorted = minPairHeap.getSorted();
	for(auto &entry : sorted) { 
	    std::cout<<"("<<entry.first<<","<<entry.second<<") "; 
	}
	std::cout<<std::endl;
	auto heap = minPairHeap.getHeap();
	for(auto &entry : heap) { 
	    std::cout<<"("<<entry.first<<","<<entry.second<<") "; 
	}
	std::cout<<std::endl;
	std::cout<<"----------MinHeap [Maintain Index] Test (End)----------\n";
}

int main(void) {
	minHeapTest();
	maxHeapTest();
	minHeapByVecIndexTest();
	return 0;
}


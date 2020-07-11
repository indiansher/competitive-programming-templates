#include<bits/stdc++.h>

/*
 * !!!NOT A Thread Safe Implementation!!!
 */
template <typename T> 
class Heap {
    
    bool isMinHeap;
    std::vector<T> vec;
    std::function<bool(const T&,const T&)> heapCompareFn;
    
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
    
    Heap(bool isMinHeap, std::vector<T> vec): isMinHeap(isMinHeap), vec(vec) {
        if(isMinHeap) { heapCompareFn = std::less<T>(); }
        else { heapCompareFn = std::greater<T>(); }
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
};

int main(void) {
//  Test Implementation
// 	Heap<double> minHeap = Heap<double>(true, {2.112, 3.5, 5.5, 2.1, 1});
// 	std::vector<double> sorted = minHeap.getSorted();
// 	for(auto &num : sorted) {
// 	    std::cout<<num<<" ";
// 	}
// 	std::cout<<std::endl;
// 	std::vector<double> heap = minHeap.getHeap();
// 	for(auto &num : heap) {
// 	    std::cout<<num<<" ";
// 	}
// 	std::cout<<std::endl;
	return 0;
}


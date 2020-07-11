#include <bits/stdc++.h>

/**
 * PAIR Comparator Templates
 */
template <typename T1, typename T2> 
bool pairLessThanByFirst(const std::pair<T1, T2> &lhs, const std::pair<T1, T2> &rhs) {
    return lhs.first < rhs.first;
}


/**
 * Examples 
 */
void pairLessThanByFirstTest() {
    std::cout<<"----------pairLessThanByFirst Test (Start)----------\n";
    std::pair<int, int> a = {1, 2} , b = {2, 2};
    std::cout<<pairLessThanByFirst<int, int>(a, b)<<"\n";
    std::cout<<pairLessThanByFirst<int, int>(b, a)<<"\n";
	std::cout<<"----------pairLessThanByFirst Test (End)----------\n";
}
int main() {
	pairLessThanByFirstTest();
	return 0;
}

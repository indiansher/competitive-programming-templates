#include <bits/stdc++.h>
using namespace std;

class TrieNode {
public:
    char ch;
    bool isWordEnd;
    unordered_map<char, TrieNode*> nextMap;
    TrieNode() {
        isWordEnd = false;
    }
};

class Trie {
    
    // Root Node
    TrieNode* root;
    
    /** Insert New String into Trie */
    void insert(const string &a, TrieNode *ptr) {
        for(char ch : a) {
            if(ptr->nextMap[ch]==NULL) {
                TrieNode *node = new TrieNode();
                node->ch = ch;
                ptr->nextMap[ch]=node;
            }
            ptr = ptr->nextMap[ch];
        }
        ptr->isWordEnd = true;
    }
    
    /** Get at max (limit) complete words from this ptr */
    vector<string> getWords(string x, TrieNode *ptr, int limit) {
        if(limit<=0 || ptr==NULL) {
            return {};
        }
        
        vector<string> results;
        if(ptr->isWordEnd){
            results.push_back(x);
        }
        
        for(auto it=ptr->nextMap.begin();it!=ptr->nextMap.end() && results.size()<limit;it++) {
            if(it->second==NULL) {
                continue;
            }
            auto newResults = getWords(x+it->first, it->second, limit-results.size());
            if(newResults.size()>0) {
                results.insert(end(results), begin(newResults), end(newResults));
            }
        }
        return results;
    }
    
    /** Get Pointer to last character */
    TrieNode* getPtrToLastChar(const string &x) {
        TrieNode* ptr = root;
        for(char ch : x) {
            if(ptr==NULL) {
                break;
            }
            ptr = ptr->nextMap[ch];
        }
        return ptr;
    }
    
    /** Get startsWith results */
    vector<string> startsWith(const string &x, const int& limit) {
        return getWords(x, getPtrToLastChar(x), limit);
    }
    
    
    
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        insert(word, root);
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        auto ptr = getPtrToLastChar(word);
        return ptr!=NULL && ptr->isWordEnd;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        auto results = startsWith(prefix, 1);
        return results.size()>0;
    }
    
    /** Returns autocomplete results */
    vector<string> startsWithResults(string prefix, int limit = 10) {
        return startsWith(prefix, limit);
    }
};

/**
 * Trie object will be instantiated and called like this:
 *
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
int main() {
    
    Trie trie;
    
    int input_size;
    cin>>input_size;
    string input;
    while(input_size--) {
        cin>>input;
        trie.insert(input);
    }
    
    cin>>input_size;
    while(input_size--) {
        cin>>input;
        cout<<"-------------------\n";
        cout<<input<<"\n\n";
        auto results = trie.startsWithResults(input, 2);
        for(auto result : results) {
            cout<<result<<"\n";
        }
    }
    
    return 0;
}

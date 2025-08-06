#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Represents a single node in the Trie.
struct Node {
    Node* links[26];      // Pointers to child nodes for 'a' through 'z'.
    int countEnd = 0;     // Counts words ending at this node.
    int countPrefix = 0;  // Counts words sharing this prefix.

    Node() {
        for (int i = 0; i < 26; i++) {
            links[i] = NULL;
        }
    }

    bool containKey(char ch) {
        return (links[ch - 'a'] != NULL);
    }

    void put(char ch, Node* node) {
        links[ch - 'a'] = node;
    }

    Node* get(char ch) {
        return links[ch - 'a'];
    }

    void increaseEnd() {
        countEnd++;
    }

    void decreaseEnd() {
        countEnd--;
    }

    void increasePrefix() {
        countPrefix++;
    }

    void decreasePrefix() {
        countPrefix--;
    }
};

// Implements the Trie data structure.
class Trie {
private:
    Node* root;

    // DFS helper to find all words from a given node.
    void dfsFindWords(Node* node, string currentWord, vector<string>& result) {
        if (node->countEnd > 0) {
            result.push_back(currentWord);
        }
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            if (node->containKey(ch)) {
                dfsFindWords(node->get(ch), currentWord + ch, result);
            }
        }
    }

public:
    // Initializes the Trie.
    Trie() {
        root = new Node();
    }

    // Inserts a word into the Trie.
    void insert(string& word) {
        Node* node = root;
        for (char ch : word) {
            if (!node->containKey(ch)) {
                node->put(ch, new Node());
            }
            node = node->get(ch);
            node->increasePrefix();
        }
        node->increaseEnd();
    }

    // Checks if a word exists in the Trie.
    bool search(string& word) {
        Node* node = root;
        for (char ch : word) {
            if (!node->containKey(ch)) return false;
            node = node->get(ch);
        }
        return (node->countEnd > 0);
    }

    // Checks if any word starts with the given prefix.
    bool startsWith(string& prefix) {
        Node* node = root;
        for (char ch : prefix) {
            if (!node->containKey(ch)) return false;
            node = node->get(ch);
        }
        return (node->countPrefix > 0);
    }

    // Counts the number of times a word appears.
    int countWordsEqualTo(string& word) {
        Node* node = root;
        for (char ch : word) {
            if (!node->containKey(ch)) return 0;
            node = node->get(ch);
        }
        return node->countEnd;
    }

    // Counts words starting with a given prefix.
    int countWordsStartingWith(string& prefix) {
        Node* node = root;
        for (char ch : prefix) {
            if (!node->containKey(ch)) return 0;
            node = node->get(ch);
        }
        return node->countPrefix;
    }

    // Removes one instance of a word from the Trie.
    void erase(string& word) {
        if (!search(word)) return;
        Node* node = root;
        for (char ch : word) {
            node = node->get(ch);
            node->decreasePrefix();
        }
        node->decreaseEnd();
    }

    // Returns all words that start with a given prefix.
    vector<string> findAllWordsWithPrefix(string& prefix) {
        Node* node = root;
        vector<string> result;
        for (char ch : prefix) {
            if (!node->containKey(ch)) return result;
            node = node->get(ch);
        }
        dfsFindWords(node, prefix, result);
        return result;
    }
};

// Main function to demonstrate Trie functionality.
int main() {
    Trie trie;

    // --- Insert words ---
    cout << "Inserting words...\n";
    string w1 = "app";
    string w2 = "apple";
    string w3 = "apps";
    string w4 = "apricot";
    trie.insert(w1);
    trie.insert(w2);
    trie.insert(w2); // Insert "apple" again
    trie.insert(w3);
    trie.insert(w4);
    
    // --- Test counting ---
    cout << "\n--- Counting ---\n";
    cout << "Count of 'apple': " << trie.countWordsEqualTo(w2) << endl; // Expected: 2
    string prefix_ap = "ap";
    cout << "Count of words starting with 'ap': " << trie.countWordsStartingWith(prefix_ap) << endl; // Expected: 5

    // --- Test erase ---
    cout << "\n--- Erasing 'apple' ---\n";
    trie.erase(w2);
    cout << "Count of 'apple' after erase: " << trie.countWordsEqualTo(w2) << endl; // Expected: 1
    cout << "Count of words starting with 'ap' after erase: " << trie.countWordsStartingWith(prefix_ap) << endl; // Expected: 4

    // --- Test autocomplete ---
    cout << "\n--- Autocomplete for 'app' ---\n";
    string prefix_app = "app";
    vector<string> words = trie.findAllWordsWithPrefix(prefix_app);
    for (const string& word : words) {
        cout << "  - " << word << endl;
    }
    // Expected: app, apple, apps

    return 0;
}
#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Node {
 public:
  char ch;
  bool ends;
  std::unordered_map<char, Node *> map;
  Node() {}
  Node(char __ch) : ch(__ch), ends(false) {}
  Node(char __ch, bool __ends) : ch(__ch), ends(__ends) {}
};

class Trie {
  Node *root;

 public:
  Trie() { root = new Node(); }

  void insert(string word) {
    auto curr = root;
    for (auto ch : word) {
      if (curr->map.count(ch) == 0) {
        curr->map[ch] = new Node(ch);
      }
      curr = curr->map[ch];
    }
    curr->ends = true;
  }

  bool search(string word) {
    auto curr = root;
    for (size_t i = 0; i < word.size(); ++i) {
      if (curr->map.count(word[i]) == 0) return false;
      if (i == word.size() - 1 && curr->map[word[i]]->ends) return true;
      curr = curr->map[word[i]];
    }
    return false;
  }

  bool startsWith(string prefix) {
    auto curr = root;
    for (size_t i = 0; i < prefix.size(); ++i) {
      if (curr->map.count(prefix[i]) == 0) return false;
      curr = curr->map[prefix[i]];
    }
    return true;
  }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

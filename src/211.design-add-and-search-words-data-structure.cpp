#ifdef __LOCAL__
#include <leetcode.h>
#endif

struct Node {
  char ch;
  bool ends = false;
  std::array<Node*, 26> map{};
  Node(char __ch) : ch(__ch) {}
};

class WordDictionary {
  Node* root;

 public:
  WordDictionary() { root = new Node('\0'); }

  void insert(const std::string& word) {
    auto curr = root;
    for (auto ch : word) {
      if (curr->map[ch - 'a'] == nullptr) curr->map[ch - 'a'] = new Node(ch);
      curr = curr->map[ch - 'a'];
    }
    curr->ends = true;
  }

  bool search(Node* prev, std::string& word, size_t lo) {
    if (prev == nullptr) return false;
    if (lo == word.size()) return prev->ends;

    for (size_t i = lo; i < word.size(); ++i) {
      const auto ch = word[i];
      // cout << prev->ch << " " << ch << " " << lo << endl;

      // ..a
      if (ch == '.') {
        for (auto& v : prev->map)
          if (search(v, word, i + 1)) return true;
        return false;
      }

      if (prev->map[ch - 'a'] == nullptr) return false;

      prev = prev->map[ch - 'a'];
    }
    return prev->ends;
  }

  void addWord(string word) { insert(word); }

  bool search(string word) { return search(root, word, 0); }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */

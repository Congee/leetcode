#ifdef __LOCAL__
#include <leetcode.h>
#endif

struct Node {
  char ch;
  std::array<Node*, 26> map = {};
  bool ends = false;
  Node(char __ch) : ch(__ch) {}
};

struct Trie {
  Node* root;
  Trie() : root(new Node('\0')) {}

  void __rest_of(
    const Node* curr, std::string& stack, std::vector<std::string>& vec
  ) {
    for (auto&& child : curr->map) {
      if (child == nullptr) continue;
      stack.push_back(child->ch);
      if (child->ends) vec.push_back(stack);
      __rest_of(child, stack, vec);
      stack.pop_back();
    }
  }

  std::vector<std::string> filter(const std::string& prefix) {
    auto curr = root;
    for (char ch : prefix) {
      if (curr->map[ch - 'a'] == nullptr) return {};
      curr = curr->map[ch - 'a'];
    }

    auto stack = prefix;
    std::vector<std::string> vec;
    if (curr->ends) vec.push_back(stack);
    __rest_of(curr, stack, vec);
    return vec;
  }

  bool search(const std::string& word) const {
    auto curr = root;
    for (char ch : word) {
      if (curr->map[ch - 'a'] == nullptr) return false;
      curr = curr->map[ch - 'a'];
    }
    return curr->ends;
  }

  bool startswith(const std::string& str) const {
    auto curr = root;
    for (char ch : str) {
      if (curr->map[ch - 'a'] == nullptr) return false;
      curr = curr->map[ch - 'a'];
    }
    return true;
  }

  void insert(const std::string& word) {
    auto curr = root;
    for (char ch : word) {
      if (curr->map[ch - 'a'] == nullptr) curr->map[ch - 'a'] = new Node(ch);
      curr = curr->map[ch - 'a'];
    }
    curr->ends = true;
  }
};

class Solution {
  Trie* trie;
  vector<string> words;
  size_t n;

 public:
  vector<vector<string>> wordSquares(vector<string>& __words) {
    n = __words[0].size();
    words = std::move(__words);
    trie = new Trie();
    for (auto&& w : words) trie->insert(w);

    std::vector<std::vector<std::string>> vec;
    std::vector<std::string> square;

    backtrack(vec, square);

    return vec;
  }

  void backtrack(
    std::vector<std::vector<std::string>>& vec, std::vector<std::string>& square
  ) {
    std::string prefix;
    for (auto&& w : square) {
      prefix += w[square.size()];
    }

    for (auto&& w : trie->filter(prefix)) {
      // ball
      // area
      // lead
      // lady

      square.push_back(w);
      // cout << square << endl;
      if (square.size() == n)
        vec.push_back(square);
      else
        backtrack(vec, square);
      square.pop_back();
    }
  }

  void backtrack_naive_pruning(
    std::vector<std::vector<std::string>>& vec, std::vector<std::string>& square
  ) {
    for (auto&& w : words) {
      // ball
      // area
      // lead
      // lady
      if (square.size() == 0)
        ;
      else if (square.size() == 1) {
        if (w[0] != square[0][1]) continue;
      } else if (square.size() == 2) {
        if (w[0] != square[0][2]) continue;
        if (w[1] != square[1][2]) continue;
      } else if (square.size() == 3) {
        if (w[0] != square[0][3]) continue;
        if (w[1] != square[1][3]) continue;
        if (w[2] != square[2][3]) continue;
      }

      square.push_back(w);
      // cout << square << endl;
      if (square.size() == n)
        vec.push_back(square);
      else
        backtrack(vec, square);
      square.pop_back();
    }
  }
};

#if 0
["area","lead","wall","lady","ball"]
["a","b"]
["ab","ba","bc"]
["aaa"]
#endif

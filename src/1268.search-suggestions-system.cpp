#ifdef __LOCAL__
#include <leetcode.h>
#endif

struct Node {
  char ch;
  std::array<Node*, 26> map;
  bool ends;
  Node(char __ch) : ch(__ch), map({}), ends(false) {}
};

class Solution {
  Node* root = new Node('\0');

  Node* __insert(const std::string& word) {
    auto curr = root;
    for (char __ch : word) {
      auto ch = __ch - 'a';
      if (curr->map[ch] == nullptr) curr->map[ch] = new Node(ch);
      curr = curr->map[ch];
    }
    return curr;
  }

  inline void insert(const std::string& word) { __insert(word)->ends = true; }

  std::vector<std::string> startswith(std::string& prefix) {
    auto curr = __insert(prefix);
    std::vector<std::string> vec;
    backtrack(curr, prefix, vec);
    return vec;
  }

  void backtrack(
    const Node* root, std::string& stack, std::vector<std::string>& vec
  ) {
    if (vec.size() == 3) return;
    if (root->ends) vec.push_back(stack);
    auto curr = root;
    for (auto&& node : curr->map) {
      if (node == nullptr) continue;
      stack.push_back(node->ch + 'a');
      backtrack(node, stack, vec);
      stack.pop_back();
    }
  }

 public:
  vector<vector<string>> suggestedProducts(
    vector<string>& products, const string& searchWord
  ) {
    for (auto&& p : products) insert(p);

    std::vector<std::vector<std::string>> result;

    for (size_t i = 0; i < searchWord.size(); ++i) {
      auto str = searchWord.substr(0, i + 1);
      result.push_back(startswith(str));
    }

    return result;
  }
};

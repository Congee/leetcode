#ifdef __LOCAL__
#include <leetcode.h>
#endif

struct Node {
  char ch = '\0';
  std::array<Node*, 26> map = {};
  bool ends = false;
  int word_idx = -1;
  Node() {}
  Node(char __ch) : ch(__ch) {}
};

class Solution {
  Node* root;
  std::vector<std::pair<std::string_view, size_t>> stack;
  std::vector<std::string> result;

  void insert(const std::string_view word, int word_idx) {
    auto curr = root;
    for (char __ch : word) {
      char ch = __ch - 'a';
      if (curr->map[ch] == 0) curr->map[ch] = new Node(ch);
      curr = curr->map[ch];
    }
    curr->ends = true;
    curr->word_idx = word_idx;
  }

  void search(
    Node* curr, const std::string_view word, std::vector<int>& good_ends
  ) const {
    for (size_t i = 0; i < word.size(); ++i) {
      char ch = word[i] - 'a';
      if (!curr->map[ch]) return;
      if (curr->map[ch]->ends) good_ends.push_back(curr->map[ch]->word_idx);
      curr = curr->map[ch];
    }
  }

 public:
  vector<string> wordBreak(string s, vector<string>& wordDict) {
    // 1. construct a Trie from dict; maintain a stack of word indices
    // 2. dfs on s
    // 2.1 if match succeeds, start from the end of the current word
    // 2.2 if match fails, start from the next char

    root = new Node();
    for (size_t i = 0; i < wordDict.size(); ++i) insert(wordDict[i], i);

    dfs(0, s, wordDict);

    return result;
  }

  std::string join(std::vector<std::pair<std::string_view, size_t>>& strs) {
    std::string str;
    for (auto&& [word, _] : strs) {
      str += word;
      str += ' ';
    }
    str.pop_back();
    return str;
  }

  void dfs(size_t start, std::string_view s, std::vector<std::string>& dict) {
    if (start == s.size()) {
      if (stack.empty()) return;
      if (stack.back().second < s.size()) return;
      result.push_back(join(stack));
      return;
    }

    // NOTE: here we don't have to visit every char, we can queue indices where
    // words end and just consume that queue
    for (size_t i = start; i < s.size(); ++i) {
      std::vector<int> good_ends;
      search(root, s.substr(i), good_ends);
      for (int word_idx : good_ends) {
        auto&& word = dict[word_idx];
        size_t prev_total = stack.empty() ? 0 : stack.back().second;
        stack.emplace_back(word, prev_total + word.size());
        dfs(i + word.size(), s, dict);
        stack.pop_back();
      }
    }
  }
};

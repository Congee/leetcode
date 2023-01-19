#ifdef __LOCAL__
#include <leetcode.h>
#endif

struct Node {
  char ch;
  bool ends = false;
  bool is_target = false;
  bool seen = false;
  std::array<Node*, 26> map = {};
  Node() {}
  Node(char __ch) : ch(__ch) {}
};

class Solution {
  Node* root;
  void insert(const std::string_view word, bool is_target) {
    auto curr = root;
    for (char __ch : word) {
      char ch = __ch - 'a';
      if (curr->map[ch] == 0) curr->map[ch] = new Node(ch);
      curr = curr->map[ch];
    }
    curr->ends = true;
    curr->is_target = is_target;
  }

  Node* search(const std::string_view word) {
    auto curr = root;
    for (char __ch : word) {
      char ch = __ch - 'a';
      if (curr->map[ch] == 0) return nullptr;
      if (curr->map[ch]->ends) return curr->map[ch];  // words have same length
      curr = curr->map[ch];
    }

    return nullptr;
  }

 public:
  int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    // BFS improved with Trie
    // worst time complexity (word_len * 25) * steps * 26 * word_len
    // 10 * 25 * 5000 * 26 * 10 = 2.25e10

    // endWord must be in list; even with the case: "abc" -> "abd" with ["zzz"]
    if (std::find(wordList.begin(), wordList.end(), endWord) == wordList.end())
      return 0;

    root = new Node('\0');
    for (auto&& word : wordList) insert(word, false);
    insert(endWord, true);
    std::queue<std::string> queue({beginWord});

    int steps = 0;
    while (queue.size()) {  // NOTE: we can speed it up with bidirectional BFS
      steps++;
      const int size = queue.size();
      for (int i = 0; i < size; ++i) {
        auto curr = queue.front();
        queue.pop();

        std::string str(curr.begin(), curr.end());
        for (char& ch : str) {
          char orig_ch = ch;
          for (int k = 0; k < 26; ++k) {
            if (k + 'a' == orig_ch) continue;
            ch = k + 'a';
            auto node = search(str);
            if (node == nullptr) continue;
            if (node->seen) continue;
            if (node->is_target) return steps + 1;

            node->seen = true;
            queue.push(str);
          }
          ch = orig_ch;
        }
      }
    }

    return 0;
  }
};

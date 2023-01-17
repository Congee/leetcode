#ifdef __LOCAL__
#include <leetcode.h>
#endif

using Pair = std::pair<int, int>;
const Pair directions[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

struct TrieNode {
  char ch;
  int idx;
  std::array<TrieNode*, 26> map;
  size_t count;
  TrieNode(char __ch) : ch(__ch), idx(-1), map{}, count(0) {}
};

class Solution {
  vector<vector<char>> board;
  vector<string> words;
  TrieNode* root;
  int m;
  int n;

  bool startswith(const std::string& prefix) {
    auto curr = root;
    for (char ch : prefix) {
      char key = ch - 'a';
      if (curr->map[key] == nullptr) return false;
      curr = curr->map[key];
    }
    return true;
  }

  void insert(int i) {
    auto curr = root;
    for (char ch : words[i]) {
      char key = ch - 'a';
      if (curr->map[key] == nullptr) {
        curr->map[key] = new TrieNode(ch);
        curr->count++;
      }
      curr = curr->map[key];
    }
    curr->idx = i;
  }

 public:
  vector<string> findWords(
    vector<vector<char>>& __board, vector<string>& __words
  ) {
    words = std::move(__words);
    board = std::move(__board);
    m = board.size();
    n = board[0].size();
    root = new TrieNode('\0');

    for (int i = 0; i < words.size(); ++i) insert(i);

    std::vector<std::string> vec;

    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        char ch = board[r][c];
        if (root->map[ch - 'a']) backtrack(r, c, root, vec);
      }
    }

    return vec;
  }

  void backtrack(
    const int row,
    const int col,
    TrieNode* parent,
    std::vector<std::string>& vec
  ) {
    char old = board[row][col];
    auto curr = parent->map[old - 'a'];
    if (curr->idx != -1) {
      vec.push_back(words[curr->idx]);
      curr->idx = -1;
    }

    const auto is_valid = [&](const Pair& p) {
      auto [r, c] = p;
      if (r < 0 || r == m || c < 0 || c == n) return false;

      return board[r][c] != '#';
    };

    board[row][col] = '#';
    for (auto&& [dr, dc] : directions) {
      int r = row + dr;
      int c = col + dc;
      if (!is_valid({r, c})) continue;
      if (!curr->map[board[r][c] - 'a']) continue;

      backtrack(r, c, curr, vec);
    }
    board[row][col] = old;

    // bzero the leaf node
    if (curr->count == 0) {
      delete parent->map[old - 'a'];
      parent->map[old - 'a'] = nullptr;
      parent->count--;
    }
  }
};

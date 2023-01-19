#ifdef __LOCAL__
#include <leetcode.h>
#endif

struct Node {
  char ch;
  bool ends = false;
  int type = 0;
  int word_idx = -1;
  int distance = INT_MAX;
  std::array<Node*, 26> map = {};
  Node(char __ch) : ch(__ch) {}
};

class Solution {
  Node* root;
  std::vector<std::string_view> stack;
  std::vector<std::vector<std::string>> result;

  Node* insert(const std::string& word, int word_idx, int type) {
    auto curr = root;
    for (char __ch : word) {
      char ch = __ch - 'a';
      if (curr->map[ch] == nullptr) curr->map[ch] = new Node(ch);
      curr = curr->map[ch];
    }
    if (word_idx >= 0) curr->word_idx = word_idx;
    curr->ends = true;
    curr->type = type;
    return curr;
  }

  Node* search(const std::string& word) {
    auto curr = root;
    for (char __ch : word) {
      char ch = __ch - 'a';
      if (curr->map[ch] == nullptr) return nullptr;
      curr = curr->map[ch];
    }

    return curr;
  }

 public:
  vector<vector<string>> findLadders(
    string beginWord, string endWord, vector<string>& wordList
  ) {
    // same as word ladder i, but with optimizations
    // 1. bfs to find the shortest steps; return early if not possible
    // 2. dfs and break on surpass the least steps
    // 3. bidirectional bfs
    // 4. trie to speed up word matching
    //
    // well, in the step 2 above, I didn't come up with a reverse bfs + distance
    // solution. dumb me
    if (std::find(wordList.begin(), wordList.end(), endWord) == wordList.end())
      return {};

    root = new Node('\0');
    for (size_t i = 0; i < wordList.size(); ++i) insert(wordList[i], i, 1);
    auto node_begin = insert(beginWord, -1, 0);
    insert(endWord, -1, 2)->distance = 1;

    bfs(endWord, wordList);
    if (node_begin->distance == INT_MAX) return {};

    stack.emplace_back(beginWord);
    dfs(wordList, node_begin->distance);

    return result;
  }

  int bfs(const std::string& end, std::vector<std::string>& wordList) {
    std::queue<std::string_view> queue({end});
    int steps = 0, found = 0;
    while (queue.size()) {
      steps++;
      const int size = queue.size();
      for (int i = 0; i < size; ++i) {
        auto curr = queue.front();
        queue.pop();

        auto word = std::string(curr);  // do not mutate curr
        for (auto node : neighbors_of(word)) {
          if (node == nullptr) continue;
          if (node->distance <= steps + 1) continue;
          node->distance = steps + 1;

          if (node->type != 0) queue.push(wordList[node->word_idx]);
          found |= node->type == 0;
        }
      }
    }

    return found ? steps + 1 : INT_MAX;
  }

  std::vector<Node*> neighbors_of(std::string& word) {
    std::vector<Node*> vec;
    for (char& ch : word) {
      char orig_ch = ch;
      for (int k = 0; k < 26; ++k) {
        if (k + 'a' == orig_ch) continue;
        ch = k + 'a';
        auto node = search(word);
        if (node == nullptr) continue;
        vec.push_back(node);
      }
      ch = orig_ch;
    }

    return vec;
  }

  void dfs(std::vector<std::string>& wordList, int prev_dist) {
    auto word = std::string(stack.back());
    for (auto node : neighbors_of(word)) {
      if (node->type == 0) continue;
      if (prev_dist - 1 != node->distance) continue;
      if (node->type == 2) {
        std::vector<std::string> vec(stack.begin(), stack.end());
        vec.push_back(wordList[node->word_idx]);
        result.push_back(vec);
        return;
      }

      stack.push_back(wordList[node->word_idx]);
      dfs(wordList, node->distance);
      stack.pop_back();
    }
  }
};

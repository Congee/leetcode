#ifdef __LOCAL__
#include <leetcode.h>
#endif

class FreqStack {
  std::unordered_map<int, int> key_freq;
  std::unordered_map<int, std::stack<int>> freq_stack;
  int max_freq;

 public:
  FreqStack() : max_freq(0) {}
  void push(int val) {
    auto freq = ++key_freq[val];
    freq_stack[freq].push(val);
    max_freq = std::max(max_freq, freq);
  }

  int pop() {
    auto& stack = freq_stack[max_freq];
    auto val = stack.top();
    stack.pop();
    if (stack.empty()) max_freq--;
    key_freq[val]--;
    return val;
  }
};

#if 0
class FreqStack {
  std::set<std::tuple<int, int, int>> tree;  // <freq, timestamp, value>
  std::unordered_map<int, int> map;          // <value, freq>
  int timestamp;

 public:
  // It is like LFU
  // We can maintain buckets of linked lists for each frequency.
  // Theoretically, O(1)
  // Or, hashmap + BST. O(log n) on push, O(1) on pop
  FreqStack() : timestamp(0) {}

  void push(int val) {
    auto freq = ++map[val];
    tree.insert({freq, timestamp++, val});
  }

  int pop() {
    const auto it = std::prev(tree.end());
    auto [_, __, value] = *tree.rbegin();
    tree.erase(it);
    map[value]--;
    return value;
  }
};
#endif

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */

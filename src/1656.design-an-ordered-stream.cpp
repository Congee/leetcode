#ifdef __LOCAL__
#include <leetcode.h>
#endif

class OrderedStream {
  std::vector<std::string> store;
  size_t ptr;

 public:
  // TCP Sliding Window
  OrderedStream(int n) : store(n), ptr(0) {}

  vector<string> insert(int id, const string& value) {
    store[--id] = value;
    std::vector<std::string> vec;

    while (ptr < store.size() && store[ptr].size()) vec.push_back(store[ptr++]);

    return vec;
  }
};

/**
 * Your OrderedStream object will be instantiated and called as such:
 * OrderedStream* obj = new OrderedStream(n);
 * vector<string> param_1 = obj->insert(idKey,value);
 */

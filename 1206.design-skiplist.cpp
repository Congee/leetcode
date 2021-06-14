#include <cstdlib>
#include <utility>
#include <vector>

bool is_odd(int &num) { return num & 1; }

class Node {
 public:
  int key;
  int value;
  std::vector<Node *> forward;  // a list of `next` pointers

  Node(int key, int value, size_t level) : key(key), value(value) {
    for (auto i = 0; i < level; ++i) {
      forward.push_back(nullptr);
    }
  }
};

class Skiplist {
  Node *head = nullptr;
  size_t size = 0;
  size_t level = 0;

  private:
  size_t rand() {
    // geometric distribution. want 50% level 0, 25% level 1, and so forth
    for (size_t level = 0; std::rand() & 1; ++level)
      ;
    return level;
  }

 public:
  Skiplist() {}

  bool search(int target) {
    // size == 0;
    // size == 1;

    auto node = head;
    for (auto i = level; i > 0; --i) {
      while (node->key < target && node->forward[i] != nullptr) {
        node = node->forward[i];
      }

      if (node->key == target)
        return true;

    }
  }

  void add(int num) {

  }

  bool erase(int num) {}
};
/**
 * Your Skiplist object will be instantiated and called as such:
 * Skiplist* obj = new Skiplist();
 * bool param_1 = obj->search(target);
 * obj->add(num);
 * bool param_3 = obj->erase(num);
 */

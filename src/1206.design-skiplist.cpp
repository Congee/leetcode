#ifndef Leetcode_H
#include <leetcode.h>
#endif /* ifndef  */

struct Node {
  std::vector<Node *> forward;
  Node *down;
  int key;
  size_t count;

  Node() : down(nullptr), count(1) {}
  Node(int key, int level) : down(nullptr), key(key), count(1) {
    forward = std::vector<Node *>(level + 1, nullptr);
  }
};

class Skiplist {
  Node *head;  // always points to the 1st node
  size_t size;
  int level;

 public:
  Skiplist() {
    std::srand(42);
    head = new Node(0, -1);
  }

  int rand_level() {
    int level;
    for (level = 0; std::rand() & 1; level++)
      ;
    return level;
  }

  // find previous node
  Node *find(int key) {
    auto curr = head;
    for (int i = level; i >= 0; --i) {
      while (curr->forward[i] && curr->forward[i]->key < key)
        curr = curr->forward[i];
    }
    return curr;
  }

  bool search(int key) {
    auto it = find(key);
    // 3 5 8 -> null
    // 1 -> 3
    // 4 -> 3
    // 8 -> 8
    // 9 -> null
    return it->forward[0] && it->forward[0]->key == key;
  }

  void add(int key) {
    int new_level = rand_level();
    if (level < new_level) {
      while (head->forward.size() <= (size_t)new_level)
        head->forward.push_back(nullptr);
      level = new_level;
    }

    std::vector<Node *> vec(level + 1);
    auto curr = head;
    for (int i = level; i >= 0; --i) {
      // existing
      if (curr->forward[i] && curr->forward[i]->key == key) {
        curr->forward[i]->count++;
        size++;
        return;
      }

      while (curr->forward[i] && curr->forward[i]->key < key)
        curr = curr->forward[i];

      vec[i] = curr;
    }

    auto node = new Node(key, new_level);
    for (int i = 0; i <= new_level; ++i) {
      node->forward[i] = vec[i]->forward[i];
      vec[i]->forward[i] = node;
    }

    size++;
  }

  bool erase(int key) {
    std::vector<Node *> vec(level + 1);  // actually unnecessary
    auto curr = head;
    for (int i = level; i >= 0; --i) {
      while (curr->forward[i] && curr->forward[i]->key < key)
        curr = curr->forward[i];
      vec[i] = curr;
    }

    auto to_delete = curr->forward[0];
    if (to_delete == nullptr || to_delete->key != key) return false;
    if (to_delete->count > 1) {
      to_delete->count--;
      size--;
      return true;
    }

    for (size_t i = 0; i < to_delete->forward.size(); ++i) {
      vec[i]->forward[i] = to_delete->forward[i];
    }

    delete to_delete;
    size--;
    return true;
  }
};

/**
 * Your Skiplist object will be instantiated and called as such:
 * Skiplist* obj = new Skiplist();
 * bool param_1 = obj->search(target);
 * obj->add(num);
 * bool param_3 = obj->erase(num);
 */

#if 0
["Skiplist","add","add","add","add","add","add","add","add","add","erase","add","erase","add","search"]
[[],[16],[5],[14],[13],[0],[3],[12],[9],[12],[3],[7],[0],[5],[12]]
#endif

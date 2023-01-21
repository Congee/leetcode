#ifdef __LOCAL__
#include <leetcode.h>
#endif

class SnapshotArray {
  std::vector<std::vector<std::pair<int, int>>> array;  // <idx, [snap, val]>
  int snap_id = 0;

 public:
  SnapshotArray(int length) {
    array.resize(length, std::vector<std::pair<int, int>>({{0, 0}}));
  }

  void set(int index, int val) {
    auto&& store = array[index];
    if (store.rbegin()->first == snap_id) {
      store.rbegin()->second = val;
    } else {
      store.emplace_back(snap_id, val);
    }
  }

  int snap() { return snap_id++; }

  int get(int index, int snap_id) {
    auto it = std::upper_bound(
      array[index].begin(),
      array[index].end(),
      make_pair<>(snap_id, 0),
      [&](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; }
    );
    return std::prev(it)->second;
  }
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */

#ifdef __LOCAL__
#include <leetcode.h>
#endif

// <1, [1 - 2 - 3]>
// <2, [4 - 5 - 0]
//
// <1, [1 - 3]>
// <2, [4 - 5 - 6 - 2]>

using Pair = std::pair<int, int>;
using Queue = std::list<Pair>;

class LFUCache {
  // [old <----> new]
  std::unordered_map<int, Queue> freqm;  // <freq, [old kv <-> new kv]>
  // <key, {freq, ptr}>
  std::unordered_map<int, std::pair<int, Queue::iterator>> cache;

  size_t cap;
  size_t min_freq;

 public:
  LFUCache(int capacity) : cap(capacity), min_freq(0) {}

  int get(int key) {
    // exists
    //   move pointer
    // not exists

    auto it = cache.find(key);
    if (it == cache.end()) return -1;

    auto [freq, kv] = it->second;
    int value = kv->second;

    freqm[freq].erase(it->second.second);
    if (freqm[freq].empty()) {
      freqm.erase(freq);
      if (freq == min_freq) min_freq++;
    }

    auto ptr = freqm[freq + 1].insert(freqm[freq + 1].end(), {key, value});
    cache[key] = {freq + 1, ptr};

    return value;
  }

  void put(int key, int value) {
    // exists
    //  full
    //   erase
    //   insert
    //  not full
    //   erase
    //   insert
    // not exists
    //  insert into freq 1

    if (cache.count(key)) {  // exists
      auto [freq, kv] = cache[key];
      freqm[freq].erase(kv);
      if (freqm[freq].empty()) {
        freqm.erase(freq);
      }

      auto ptr = freqm[freq + 1].insert(freqm[freq + 1].end(), {key, value});
      cache[key] = {freq + 1, ptr};
    } else {  // not exists
      if (cap == 0) return;

      // full
      if (cap == cache.size()) {
        cache.erase(freqm[min_freq].begin()->first);
        freqm[min_freq].erase(freqm[min_freq].begin());
        if (freqm[min_freq].empty()) freqm.erase(min_freq);
      }

      auto ptr = freqm[1].insert(freqm[1].end(), {key, value});
      cache[key] = {1, ptr};

      if (freqm[min_freq].empty()) freqm.erase(min_freq);
      min_freq = 1;
    }
  }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

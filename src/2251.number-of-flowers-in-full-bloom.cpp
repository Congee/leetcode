#ifdef __LOCAL__
#include <leetcode.h>
#endif

using vv = std::vector<std::vector<int>>;

class Solution {
 public:
  vector<int> fullBloomFlowers(vv& flowers, vector<int>& persons) {
    return bs(flowers, persons);
    return sweep_line(flowers, persons);
    return prefix_sum(flowers, persons);
  }

  vector<int> bs(vv& flowers, vector<int>& persons) {
    // Blooming flowers = started flowers - ended flowers
    std::vector<int> starts, ends;
    for (auto&& flower : flowers) {
      starts.push_back(flower[0]);
      ends.push_back(flower[1]);
    }
    std::sort(starts.begin(), starts.end());
    std::sort(ends.begin(), ends.end());

    std::vector<int> vec;
    for (int p : persons) {
      int started = std::upper_bound(starts.begin(), starts.end(), p) -
                    starts.begin();
      int ended = std::lower_bound(ends.begin(), ends.end(), p) - ends.begin();
      vec.push_back(started - ended);
    }
    return vec;
  }

  vector<int> sweep_line(vv& flowers, vector<int>& persons) {
    enum Type {
      LO = -1,
      HI = +1,
      PERSON = 2,
    };

    std::vector<std::pair<int, int>> lines;
    int lbound = INT_MAX, rbound = 0;
    for (auto&& flower : flowers) {
      int l = flower[0], r = flower[1] + 1;  // [l, r)
      lines.push_back({l, LO});
      lines.push_back({r, HI});
      lbound = std::min(lbound, l);
      rbound = std::max(rbound, r);
    }

    for (int person : persons) lines.push_back({person, PERSON});

    std::sort(lines.begin(), lines.end());

    std::unordered_map<int, int> map;
    int count = 0;
    for (auto&& [pos, type] : lines) {
      if (type != PERSON)
        count -= type;
      else
        map[pos] = count;
    }

    std::vector<int> vec;
    for (int person : persons) vec.push_back(map[person]);
    return vec;
  }

  vector<int> prefix_sum(vv& flowers, vector<int>& persons) {
    // the size of a prefix sum array is too big, use a tree map instead
    std::map<int, int> psum({{0, 0}});
    int lbound = INT_MAX, rbound = 0;
    for (auto&& flower : flowers) {
      int l = flower[0], r = flower[1] + 1;  // [l, r)
      psum[l]++;
      psum[r]--;
      lbound = std::min(lbound, l);
      rbound = std::max(rbound, r);
    }

    for (auto it = std::next(psum.begin()); it != psum.end(); ++it)
      it->second += std::prev(it)->second;

    std::vector<int> vec;
    for (int person : persons) {
      if (lbound > person || person > rbound)
        vec.push_back(0);
      else {
        auto it = psum.lower_bound(person);
        // if (it == psum.end()) vec.push_back(0);  // no way
        vec.push_back(it->first == person ? it->second : std::prev(it)->second);
      }
    }

    return vec;
  }
};

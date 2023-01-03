#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  vector<int> minInterval(
    vector<vector<int>>& intervals, vector<int>& queries
  ) {
    return line_sweep(intervals, queries);
    return bs(intervals, queries);
    return by_heap(intervals, queries);
  }

  vector<int> line_sweep(vector<vector<int>>& intervals, vector<int>& queries) {
    int m = queries.size();

    enum Type { START = 0, QUERY = 1, END = 2 };
    struct Event {
      int pos;
      Type type;
      union {
        int idx;
        int size;
      };
    };

    std::vector<Event> events;
    for (auto&& interval : intervals) {
      int size = interval.back() - interval.front() + 1;
      events.push_back(Event{interval.front(), START, size});
      events.push_back(Event{interval.back(), END, size});
    }

    for (int i = 0; i < m; ++i) events.push_back({queries[i], QUERY, i});

    std::sort(
      events.begin(),
      events.end(),
      [&](const auto& lhs, const auto& rhs) {
        if (lhs.pos != rhs.pos) return lhs.pos < rhs.pos;
        return lhs.type < rhs.type;
      }
    );

    std::multiset<int> tree;  // <size>
    std::vector<int> vec(m, -1);
    for (auto&& event : events) {
      switch (event.type) {
        case START: tree.insert(event.size); break;
        case QUERY: vec[event.idx] = tree.size() ? *tree.begin() : -1; break;
        case END: tree.erase(tree.lower_bound(event.size)); break;
      }
    }

    return vec;
  }

  vector<int> bs(vector<vector<int>>& intervals, vector<int>& queries) {
    // for each range, search for a query
    std::sort(
      intervals.begin(),
      intervals.end(),
      [&](const auto& lhs, const auto& rhs) {
        return lhs.back() - lhs.front() < rhs.back() - rhs.front();
      }
    );

    int m = queries.size();
    std::set<std::pair<int, int>> tree;  // <query, idx>
    for (int i = 0; i < m; ++i) tree.insert({queries[i], i});

    std::vector<int> vec(m, -1);
    for (auto&& interval : intervals) {
      auto it = tree.lower_bound({interval.front(), 0});
      while (it != tree.end() && it->first <= interval.back()) {
        vec[it->second] = interval.back() - interval.front() + 1;
        auto nxt = std::next(it);
        tree.erase(it);
        it = nxt;
      }
    }

    return vec;
  }

  vector<int> by_heap(vector<vector<int>>& intervals, vector<int>& queries) {
    // maintain a min heap by <size, right> for each query
    // we only care about the smallest one, remove invalid ones
    std::sort(intervals.begin(), intervals.end());
    auto sorted_queries = queries;
    std::sort(sorted_queries.begin(), sorted_queries.end());

    // intervals:
    //  1--4
    //   2-4
    //     4
    //    3--6
    // queries
    //   2345

    // intervals:
    // 1------8
    //  23
    //  2--5
    //            20---25
    // queries:
    //  2  5    19  22

    std::unordered_map<int, int> map;
    std::priority_queue<std::pair<int, int>> pq;

    int i = 0, n = intervals.size();
    for (int query : sorted_queries) {
      while (i < n && intervals[i].front() <= query) {
        int left = intervals[i].front(), right = intervals[i++].back();
        int size = right - left + 1;
        pq.push({-size, right});
      }

      while (pq.size() && pq.top().second < query) pq.pop();
      map[query] = pq.size() ? -pq.top().first : -1;
    }

    std::vector<int> vec;
    for (int query : queries) vec.push_back(map[query]);
    return vec;
  }
};

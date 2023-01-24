#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int leastInterval(vector<char>& tasks, int n) { return smart(tasks, n); }

  int smart(vector<char>& tasks, int n) {
    // count the most frequent letter. don't forget about dup max freq
    // n = 4
    // A * * * * | A * * * * | A
    // A B * * * | A B * * * | A B

    int max_freq = 0;
    std::array<int, 128> map = {};
    for (char ch : tasks) max_freq = std::max(max_freq, ++map[ch]);

    int count = (max_freq - 1) * (n + 1);
    for (char ch = 'A'; ch <= 'Z'; ++ch) count += map[ch] == max_freq;
    return std::max(count, (int)tasks.size());
  }

  int simulate(vector<char>& tasks, int n) {
    if (n == 0) return tasks.size();
    // use buckets to store number of remaining taskf for each task
    // buckets are sorted by number of tasks
    //
    // n = 1
    // A 3     A 2     A 1
    // B 2  => B 1  =>
    // C 1     C 1     C 1
    //
    // n = 2
    // A 3     A 2     A 1
    // B 2  => B 1  => B 0
    // C 1     C 0

    std::array<int, 91> array = {};
    for (char ch : tasks) array[ch]++;

    std::set<std::pair<int, char>, std::greater<>> buckets;
    for (char ch = 'A'; ch <= 'Z'; ++ch)
      if (array[ch]) buckets.insert({array[ch], ch});

    int time = 0;
    while (buckets.size()) {
      int this_round = std::min((int)buckets.size(), n + 1);
      int idle = n + 1 - this_round;

      std::vector<std::pair<int, char>> to_delete;
      auto it = buckets.begin();
      for (int i = 0; i < this_round; ++i, ++it) to_delete.push_back(*it);

      for (auto&& [remain, task] : to_delete) {
        buckets.erase(buckets.find({remain, task}));
        if (--remain) buckets.insert({remain, task});
      }

      time += this_round;
      if (buckets.size() && idle) time += idle;
    }

    return time;
  }
};

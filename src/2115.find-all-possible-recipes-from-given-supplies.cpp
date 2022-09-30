#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  vector<string> recipes;
  vector<vector<string>> ingredients;
  vector<string> supplies;
  std::unordered_set<std::string> in_recipies;
  std::unordered_set<std::string> in_supplies;

 public:
  vector<string> findAllRecipes(
    vector<string>& __recipes,
    vector<vector<string>>& __ingredients,
    vector<string>& __supplies
  ) {
    recipes = std::move(__recipes);
    ingredients = std::move(__ingredients);
    supplies = std::move(__supplies);
    in_recipies.insert(recipes.begin(), recipes.end());
    in_supplies.insert(supplies.begin(), supplies.end());

    return kahn();
    return dfs_wrapper();
  }

  vector<string> dfs_wrapper() {
    // <to, [from]>
    std::unordered_map<std::string, std::vector<std::string>> adj;
    for (size_t i = 0; i < recipes.size(); ++i)
      adj[recipes[i]] = ingredients[i];

    std::unordered_map<std::string, bool> memo;

    std::vector<std::string> vec;
    for (size_t i = 0; i < recipes.size(); ++i) {
      std::unordered_set<std::string> seen;  // cycle
      if (dfs(recipes[i], adj, memo, seen)) vec.push_back(recipes[i]);
    }

    return vec;
  }

  template <typename T, typename M, typename S>
  bool dfs(const std::string& recipe, T& adj, M& memo, S& seen) {
    if (in_supplies.count(recipe)) return true;
    auto it = memo.find(recipe);
    if (it != memo.end()) return it->second;

    if (seen.count(recipe)) return memo[recipe] = false;  // cycle
    seen.insert(recipe);

    if (adj.count(recipe) == 0) return false;

    // clang-format off
    return memo[recipe] = std::all_of(
       adj[recipe].begin(),
       adj[recipe].end(),
       [&](const std::string& r) { return dfs(r, adj, memo, seen); }
     );
    // clang-format on
  }

  vector<string> kahn() {
    // <from, [to]>
    std::unordered_map<std::string, std::vector<std::string>> adj;
    std::unordered_map<std::string, int> indegrees;
    for (size_t i = 0; i < recipes.size(); ++i) {
      for (auto&& ingredient : ingredients[i]) {
        adj[ingredient].push_back(recipes[i]);
        auto it = indegrees.find(ingredient);
        if (it == indegrees.end()) indegrees[ingredient] = 0;
      }
      indegrees[recipes[i]] += ingredients[i].size();
    }

    std::vector<std::string> vec;

    std::queue<std::string> queue;
    for (auto x : supplies) queue.push(x);
    while (queue.size()) {
      auto curr = queue.front();
      queue.pop();

      for (auto&& nb : adj[curr]) {
        auto& degree = indegrees[nb];
        // cycle?
        if (--degree == 0) {
          if (in_recipies.count(nb)) vec.push_back(nb);
          queue.push(nb);
        }
      }
    }

    return vec;
  }
};

#if 0
["bread"]
[["bread"]]
["flour"]
["bread","sandwich","burger"]
[["yeast","flour"],["bread","meat","burger"],["sandwich","meat","bread"]]
["yeast","flour","meat"]
#endif

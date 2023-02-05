#ifdef __LOCAL__
#include <leetcode.h>

// Definition for a binary tree node.
struct Node {
  char val;
  Node *left;
  Node *right;
  Node() : val(' '), left(nullptr), right(nullptr) {}
  Node(char x) : val(x), left(nullptr), right(nullptr) {}
  Node(char x, Node *left, Node *right) : val(x), left(left), right(right) {}
};

#endif

class Solution {
  std::deque<char> tokens;

 public:
  Node *expTree(string_view s) {
    // "3*4-2*5"
    //
    // "1+2+3+4+5"
    //
    // "2-3/(5*(2))+1"
    //
    // priority ()
    // priority */
    // priority +-
    //
    // what if there's no parenthesis?
    //
    // root = 1st
    // see node *
    // node->left = root
    // root = node
    // exp(rest)->left = root
    // * 2 + 1 ???
    // * (...) ???

    // just build a parser
    // left-recursive
    // CFG:
    // <expression> := term | term + term | term - term
    // <term>       := factor | factor * factor | factor / factor
    // <factor>     := digit | '(' expression ')'
    // <digit>      := ['0'..'9']

    tokens.insert(tokens.end(), s.begin(), s.end());
    return parse_exp();
  }

  auto parse_exp() -> Node * {
    // 1 + 2 - 3
    auto lhs = parse_term();
    while (tokens.size() && (tokens.front() == '+' || tokens.front() == '-')) {
      auto op = tokens.front();
      tokens.pop_front();
      auto rhs = parse_term();
      lhs = new Node(op, lhs, rhs);
    }
    return lhs;
  };

  auto parse_term() -> Node * {
    auto lhs = parse_factor();
    // 0 - 1 * 2 / 2
    while (tokens.size() && (tokens.front() == '*' || tokens.front() == '/')) {
      auto op = tokens.front();
      tokens.pop_front();
      auto rhs = parse_factor();
      lhs = new Node(op, lhs, rhs);
    }
    return lhs;
  };

  Node *parse_factor() {
    if (tokens.front() == '(') {
      tokens.pop_front();  // (
      auto node = parse_exp();
      tokens.pop_front();  // )
      return node;
    } else {
      auto token = tokens.front();
      tokens.pop_front();
      return new Node(token);
    }
  };
};

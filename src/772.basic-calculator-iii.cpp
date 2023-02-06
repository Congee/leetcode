#ifdef __LOCAL__
#include <leetcode.h>
#endif

struct Node {
  std::string token;
  Node *left, *right;
  Node(std::string __token) : token(__token), left(nullptr), right(nullptr) {}
  Node(std::string __token, Node* lhs, Node* rhs)
    : token(__token), left(lhs), right(rhs) {}
};

class Solution {
  std::deque<std::string> tokens;

 public:
  int calculate(string_view s) {
    // CFG:
    // <expression> ::= term
    //                | term + term
    //                | term - term
    // <term>       ::= factor
    //                | factor * factor
    //                | factor / factor
    // <factor>     ::= number
    //                | '(' expression ')'
    // <number>     ::= digit*
    // <digit>      ::= [0..9]
    tokenize(s);
    return eval(parse_exp());
  }

  void tokenize(string_view s) {
    for (size_t i = 0; i < s.size();) {
      if (std::isdigit(s[i])) {
        std::string number;
        while (std::isdigit(s[i])) number += s[i++];
        tokens.push_back(number);
      } else {
        tokens.push_back(std::string({s[i++]}));
      }
    }
  }

  int eval(Node* root) {
    if (0)
      ;
    else if (root->token == "*")
      return eval(root->left) * eval(root->right);
    else if (root->token == "/")
      return eval(root->left) / eval(root->right);
    else if (root->token == "+")
      return eval(root->left) + eval(root->right);
    else if (root->token == "-")
      return eval(root->left) - eval(root->right);
    else
      return std::stoi(root->token);
  }

  Node* parse_exp() {
    auto lhs = parse_term();
    while (tokens.size() && (tokens.front() == "-" || tokens.front() == "+")) {
      auto op = tokens.front();
      tokens.pop_front();
      auto rhs = parse_term();
      lhs = new Node(op, lhs, rhs);
    }
    return lhs;
  }

  Node* parse_term() {
    auto lhs = parse_factor();
    while (tokens.size() && (tokens.front() == "*" || tokens.front() == "/")) {
      auto op = tokens.front();
      tokens.pop_front();
      auto rhs = parse_factor();
      lhs = new Node(op, lhs, rhs);
    }
    return lhs;
  }

  Node* parse_factor() {
    if (tokens.front() == "(") {
      tokens.pop_front();  // '('
      auto node = parse_exp();
      tokens.pop_front();  // ')'
      return node;
    } else {
      auto token = tokens.front();
      tokens.pop_front();
      return new Node(token);
    }
  }
};

#include <algorithm>
#include <random>
#include <string>
#include <vector>

std::random_device rd;
std::mt19937 rng(rd());

enum Suit {
  HEART,
  SPADE,
  CLUB,
  DIAMOND,
};

enum CardName { ACE, C2, C3, C4, C5, C6, C7, C8, C9, C10, JACK, QUEEN, KING };

// enum AccountStatus { ACTIVE, CLOSED, CANCELED, BLOCKED, NONE };

class Person {
  const std::string name;
  const std::string street_addr;
  const std::string city;
  const std::string state;
  const std::string zip;
  const std::string country;
};

class Card {
 private:
  const Suit suit;

 public:
  const CardName name;
  const bool is_ace;
  Card(Suit suit, CardName name)
    : suit(suit), name(name), is_ace(name == ACE) {}
};

class Deck {
  std::vector<Card> cards;

 public:
  Deck();
  void shuffle() { std::shuffle(cards.begin(), cards.end(), rng); }
  Card draw() {
    if (cards.size() == 0) {
      // TODO: implementation
    }

    auto card = cards.back();
    cards.pop_back();
    return card;
  }
};

class Shoe {
  std::vector<Deck> decks;

 public:
  Shoe(std::vector<Deck> __decks) : decks(__decks) {}

  void shuffle() {
    for (auto& deck : decks) deck.shuffle();
  };

  Card deal_card() {
    if (decks.size() == 0) {
      // TODO: implementation
    }
    Card card = decks.back().draw();  // TODO: insufficient cards
    return card;
  };
};

class Hand {
  std::vector<Card> cards;

 public:
  Hand(Card card1, Card card2);
  std::vector<int> points() {
    // handle ACE point ambiguity
    std::vector<int> points;
    int num_ace = 0, other_points = 0;

    for (const auto& card : cards) {
      if (card.is_ace) {
        num_ace++;
      } else {
        other_points += std::max((int)card.name, 10);
      }
    }

    for (int i = 0; i < num_ace; ++i) {
      points.push_back(1 + other_points);
      if (10 + other_points <= 21) {
        points.push_back(10 + other_points);
      }
    }

    return points;  // empty means no valid points <= 21
  };

  void add_card(Card card);
};

class Player {
  const std::string id;
  std::string password;
  int balance;
  // AccountStatus status;
  Person person;
  Hand hand;

 public:
  void add_hand(Hand hand);
  void add_to_hand(Hand hand);
  void remove_hand(Hand hand);
  // void reset_password();
};

class BlackJackPlayer : public Player {
  int bet;
  int remain_cash;

 public:
  BlackJackPlayer(Hand hand);
  void place_bet(int __bet);
  void quit();
};

class Dealer : public Player {};

class BlackJackGame {
  Player player;
  Dealer dealer;
  Shoe shoe;
  const size_t decks_cap;

 public:
  BlackJackGame(Player player, Dealer dealer, size_t max_num_decks);

  void start();
  void hit(Hand hand);
  void stand(Hand hand);
  void evaluate(Hand hand1, Hand hand2);
  void play_action(std::string action, Hand hand);
};

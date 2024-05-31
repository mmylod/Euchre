// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "Card.h"
#include "unit_test_framework.h"
#include <sstream>
using namespace std;

// THESE TEST CASES WILL ONLY TELL YOU IF YOUR CODE COMPILES.
// YOU NEED TO WRITE YOUR OWN COMPREHENSIVE TEST CASES IN Player_tests.cpp

TEST(test_player_insertion) {
  Player * human = Player_factory("NotRobot", "Human");
  ostringstream oss;
  oss << * human;
  ASSERT_EQUAL(oss.str(), "NotRobot");
  oss.str("");
  Player * alice = Player_factory("Alice", "Simple");
  oss << *alice;
  ASSERT_EQUAL(oss.str(), "Alice");
  delete alice;
  delete human;
}

TEST(test_player_get_name) {
  Player * alice = Player_factory("Alice", "Simple");
  ASSERT_EQUAL(alice->get_name(), "Alice");
    Player * bob = Player_factory("Bob", "Human");
    ASSERT_EQUAL(bob->get_name(), "Bob");
  delete alice;
    delete bob;
}

static void add_cards(Player *player) {
  Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
  for (int i = 0; i < 5; ++i) {
    player->add_card(two_spades);
  }
}

TEST(test_simple_player_make_trump) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards(bob);

  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump = Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
      nine_spades,    //upcard
      true,           //Bob is also the dealer
      1,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_FALSE(orderup);
    orderup = bob->make_trump(
        nine_spades,    //upcard
        true,           //Bob is also fthe dealer
        2,              //first round
        trump           //suit ordered up (if any)
    );
    ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_CLUBS);
    orderup = bob->make_trump(
        nine_spades,    //upcard
        false,           //Bob is also the dealer
        2,              //first round
        trump           //suit ordered up (if any)
    );
    ASSERT_FALSE(orderup);

  delete bob;
}

TEST(test_simple_player_lead_card) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards(bob);
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  bob->add_and_discard(nine_spades);
  Card card_led = bob->lead_card(Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, nine_spades); //check led card
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card ace_hearts = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card ten_diamonds = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    bob->add_and_discard(jack_spades);
    bob->add_and_discard(jack_clubs);
    bob->add_and_discard(ace_hearts);
    bob->add_and_discard(ten_diamonds);
    ASSERT_EQUAL(card_led, nine_spades); //check led card
    card_led = bob->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led, ace_hearts); //check led card
    card_led = bob->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led, ten_diamonds); //check led card
    card_led = bob->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led, jack_spades); //check led card
    card_led = bob->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led, jack_clubs); //check led card
    add_cards(bob);
    bob->add_and_discard(jack_spades);
    bob->add_and_discard(jack_spades);
    bob->add_and_discard(jack_spades);
    bob->add_and_discard(jack_spades);
    bob->add_and_discard(jack_spades);
    bob->add_and_discard(jack_spades);
    card_led = bob->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led, jack_spades); //check led card
    card_led = bob->lead_card(Card::SUIT_CLUBS);
    ASSERT_EQUAL(card_led, jack_spades); //check led card
    card_led = bob->lead_card(Card::SUIT_HEARTS);
    ASSERT_EQUAL(card_led, jack_spades); //check led card
//    card_led = bob->lead_card(Card::SUIT_SPADES);
//    ASSERT_EQUAL(card_led, jack_spades); //check led card
    
  delete bob;
}

TEST(test_simple_player_play_card) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards(bob);
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  string trump = Card::SUIT_HEARTS;
  Card card_played = bob->play_card(nine_diamonds, trump); //Diamonds is led
  Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_played, two_spades);
  delete bob;
}

TEST(make_trump_round_1){
    Player * maisy = Player_factory("Maisy", "Simple");
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    for (int i = 0; i < 5; ++i) {
      maisy->add_card(jack_spades);
    }
    string trump = Card::SUIT_SPADES;
    bool orderup = maisy->make_trump(
        nine_spades,    //upcard
        true,           //Bob is also the dealer
        1,              //first round
        trump           //suit ordered up (if any)
    );
    ASSERT_TRUE(orderup);
    orderup = maisy->make_trump(
        nine_spades,    //upcard
        false,           //Bob is also the dealer
        1,              //first round
        trump           //suit ordered up (if any)
    );
    ASSERT_TRUE(orderup);
    
}


TEST_MAIN()

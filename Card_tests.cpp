// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <sstream>
#include "unit_test_framework.h"
#include "Card.h"

using namespace std;

// THESE TEST CASES WILL ONLY TELL YOU IF YOUR CODE COMPILES.
// YOU NEED TO WRITE YOUR OWN COMPREHENSIVE TEST CASES IN Card_tests.cpp

TEST(test_card_suit_and_rank) {
    Card two_spades = Card();
    ASSERT_EQUAL(two_spades.get_rank(), Card::RANK_TWO);
    ASSERT_EQUAL(two_spades.get_suit(), Card::SUIT_SPADES);

    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_EQUAL(three_spades.get_rank(), Card::RANK_THREE);
    ASSERT_EQUAL(three_spades.get_suit(), Card::SUIT_SPADES);
    ASSERT_EQUAL(three_spades.get_suit(Card::SUIT_CLUBS), Card::SUIT_SPADES);
}

TEST(test_card_type) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_FALSE(three_spades.is_face());
    ASSERT_FALSE(three_spades.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(three_spades.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(three_spades.is_trump(Card::SUIT_CLUBS));
}

TEST(test_card_self_comparison) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_FALSE(three_spades < three_spades);
    ASSERT_TRUE(three_spades <= three_spades);
    ASSERT_FALSE(three_spades > three_spades);
    ASSERT_TRUE(three_spades >= three_spades);
    ASSERT_TRUE(three_spades == three_spades);
    ASSERT_FALSE(three_spades != three_spades);
}

TEST(test_Suit_next) {
    ASSERT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_SPADES);
}

TEST(test_Card_less_self) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_FALSE(Card_less(three_spades, three_spades, Card::SUIT_CLUBS));
    ASSERT_FALSE(Card_less(three_spades, three_spades, three_spades,
                           Card::SUIT_CLUBS));
}

TEST(test_card_insertion) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ostringstream oss;
    oss << three_spades;
    ASSERT_EQUAL(oss.str(), "Three of Spades");
}

TEST(test_ops){
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    Card three_hearts = Card(Card::RANK_THREE, Card::SUIT_HEARTS);
    Card three_diamonds = Card(Card::RANK_THREE, Card::SUIT_DIAMONDS);
    Card three_clubs = Card(Card::RANK_THREE, Card::SUIT_CLUBS);
    
    ASSERT_TRUE(three_clubs == three_clubs);
    ASSERT_TRUE(three_spades < three_hearts);
    ASSERT_TRUE(three_spades < three_diamonds);
    ASSERT_TRUE(three_spades < three_clubs);
    ASSERT_TRUE(three_clubs <= three_clubs);
    ASSERT_TRUE(three_clubs >= three_clubs);
    ASSERT_TRUE(three_spades <= three_hearts);
    ASSERT_TRUE(three_spades <= three_diamonds);
    ASSERT_TRUE(three_spades <= three_clubs);
    ASSERT_TRUE((three_diamonds > three_hearts));
    ASSERT_TRUE((three_diamonds > three_clubs));
    ASSERT_TRUE((three_diamonds > three_spades));
    
    ASSERT_TRUE((three_diamonds >= three_hearts));
    ASSERT_TRUE((three_diamonds >= three_clubs));
    ASSERT_TRUE((three_diamonds >= three_spades));
    ASSERT_TRUE(three_spades != three_hearts);
    
}

TEST(test_bowers){
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    string trump = "Spades";
    ASSERT_TRUE(jack_spades.is_trump(trump));
    ASSERT_TRUE((jack_spades.is_right_bower(trump)));
    ASSERT_FALSE(jack_spades.is_left_bower(trump));
    ASSERT_TRUE(jack_spades.is_left_bower(Suit_next(trump)));
    ASSERT_TRUE(jack_spades.get_suit(Suit_next(trump)) == "Clubs");
    
}

TEST(card_less_stuff){
    string trump = "Clubs";
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card queen_clubs = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    ASSERT_TRUE(Card_less(queen_clubs, jack_clubs, trump));
    ASSERT_TRUE(Card_less(queen_clubs, jack_spades, trump));
    ASSERT_TRUE(Card_less(jack_spades, jack_clubs, trump));
    ASSERT_TRUE(Card_less(jack_diamonds, jack_clubs, trump));
    ASSERT_TRUE(Card_less(jack_diamonds, jack_spades, trump));
}

TEST(card_less_stuff_led){
    Card led_card = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
    string trump = "Clubs";
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card queen_clubs = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    
    ASSERT_TRUE(Card_less(queen_clubs, jack_clubs, led_card, trump));
    ASSERT_TRUE(Card_less(queen_clubs, jack_spades, led_card, trump));
    ASSERT_TRUE(Card_less(jack_spades, jack_clubs, led_card, trump));
    ASSERT_TRUE(Card_less(jack_diamonds, jack_clubs, led_card, trump));
    ASSERT_TRUE(Card_less(jack_diamonds, jack_spades, led_card, trump));
    
    ASSERT_TRUE(Card_less(queen_diamonds, led_card, led_card, trump));
    
}


TEST_MAIN()

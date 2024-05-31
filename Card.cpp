// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
using namespace std;

// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

static int cardIntRank(const Card &card);
static int cardIntSuit(const Card &card);


// add your code below
Card::Card(){
    rank = RANK_TWO;
    suit = SUIT_SPADES;
}

Card::Card(const std::string &rank_in, const std::string &suit_in){
    rank = rank_in;
    suit = suit_in;
}

std::string Card::get_rank() const{
    return rank;
}

std::string Card::get_suit() const{
    return suit;
}

std::string Card::get_suit(const std::string &trump) const{
    if (is_left_bower(trump)){
        return trump;
    }
    else{
        return suit;
    }
}

bool Card::is_face() const{
    if (rank == RANK_JACK || rank == RANK_QUEEN || rank == RANK_KING || rank == RANK_ACE){
        return true;
    }
    else{
        return false;
    }
}

bool Card::is_right_bower(const std::string &trump) const{
    if (rank == RANK_JACK && suit == trump){
        return true;
    }
    else{
        return false;
    }
}

bool Card::is_left_bower(const std::string &trump) const{
    if (rank == RANK_JACK && suit == Suit_next(trump)){
        return true;
    }
    else{
        return false;
    }
}

bool Card::is_trump(const std::string &trump) const{
    if (suit == trump || is_left_bower(trump)){
        return true;
    }
    else{
        return false;
    }
}

std::string Suit_next(const std::string &suit){
    if (suit == "Hearts"){
        return "Diamonds";
    }
    else if (suit == "Diamonds"){
        return "Hearts";
    }
    else if (suit == "Clubs"){
        return "Spades";
    }
    else{
        return "Clubs";
    }
}

std::ostream & operator<<(std::ostream &os, const Card &card){
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

bool Card_less(const Card &a, const Card &b, const std::string &trump){
    if (!a.is_trump(trump) && !b.is_trump(trump)){
        if (a < b) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (a.is_trump(trump) && !b.is_trump(trump)){
        return false;
    }
    else if (!a.is_trump(trump) && b.is_trump(trump)){
        return true;
    }
    else {
        if (a.is_right_bower(trump)){
            return false;
        }
        else if (b.is_right_bower(trump)){
            return true;
        }
        else if (a.is_left_bower(trump)){
            return false;
        }
        else if (b.is_left_bower(trump)){
            return true;
        }
        else if (a < b){
            return true;
        }
        else {
            return false;
        }
    }
}

bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump){
    if (a.is_right_bower(trump)) {
        return false;
    }
    else if (a.is_left_bower(trump) && !(b.is_right_bower(trump))){
        return false;
    }
    else if (a.is_left_bower(trump) && (b.is_right_bower(trump))){
        return true;
    }
    else if (a.is_trump(trump) && !(b.is_trump(trump))){
        return false;
    }
    else if ((a.is_trump(trump)) && (b.is_trump(trump))){
        if ((b.is_left_bower(trump) )|| (b.is_right_bower(trump))){
            return true;
        }
        else if (a >= b){
            return false;
        }
        return true;
    }
    else if (!a.is_trump(trump) && b.is_trump(trump)){
        return true;
    }
    else if (!a.is_trump(trump) && !b.is_trump(trump)){
        if (a.get_suit() == led_card.get_suit() && b.get_suit() != led_card.get_suit()){
            return false;
        }
        else if (a.get_suit() == led_card.get_suit() && b.get_suit() ==
                 led_card.get_suit()){
            if (a >= b) {
                return false;
            }
            return true;
        }
        if (a.get_suit() != led_card.get_suit() && b.get_suit() == led_card.get_suit()) {
            return true;
        }
        else if (a.get_suit() != led_card.get_suit() &&
                 b.get_suit() != led_card.get_suit()){
            if (a >= b) {
                return false;
            }
            return true;
        }
    }
    return false;
}

bool operator<(const Card &lhs, const Card &rhs){
    if (cardIntRank(lhs) < (cardIntRank(rhs))){
        return true;
    }
    else if (cardIntRank(lhs) > (cardIntRank(rhs))){
        return false;
    }
    else {
        if (cardIntSuit(lhs) < (cardIntSuit(rhs))){
            return true;
        }
        else {
            return false;
        }
    }
}

bool operator<=(const Card &lhs, const Card &rhs){
    if (cardIntRank(lhs) < (cardIntRank(rhs))){
        return true;
    }
    else if (cardIntRank(lhs) == (cardIntRank(rhs))){
        if (cardIntSuit(lhs) == (cardIntSuit(rhs))){
            return true;
        }
        else if (cardIntSuit(lhs) < (cardIntSuit(rhs))){
            return true;
        }
        else{
            return false;
        }
    }
    else {
        return false;
    }
}

bool operator>(const Card &lhs, const Card &rhs){
    if (cardIntRank(lhs) > cardIntRank(rhs)){
        return true;
    }
    else if (cardIntRank(lhs) < cardIntRank(rhs)){
        return false;
    }
    else{
        if (cardIntSuit(lhs) > cardIntSuit(rhs)){
            return true;
        }
        else {
            return false;
        }
    }
}

bool operator>=(const Card &lhs, const Card &rhs){
    if (cardIntRank(lhs) > cardIntRank(rhs)){
        return true;
    }
    else if (cardIntRank(lhs) < cardIntRank(rhs)){
        return false;
    }
    else {
        if (cardIntSuit(lhs) == (cardIntSuit(rhs))){
            return true;
        }
        else if (cardIntSuit(lhs) > (cardIntSuit(rhs))){
            return true;
        }
        else{
            return false;
        }
    }
}

bool operator==(const Card &lhs, const Card &rhs){
    if (cardIntRank(lhs) == cardIntRank(rhs) && cardIntSuit(lhs) == cardIntSuit(rhs)){
        return true;
    }
    else {
        return false;
    }
}

bool operator!=(const Card &lhs, const Card &rhs){
    if (cardIntRank(lhs) == cardIntRank(rhs) && cardIntSuit(lhs) == cardIntSuit(rhs)){
        return false;
    }
    else {
        return true;
    }
}

static int cardIntRank(const Card &card){
    if (card.get_rank() == RANK_NAMES_BY_WEIGHT[0]){
        return 2;
    }
    else if (card.get_rank() == RANK_NAMES_BY_WEIGHT[1]){
        return 3;
    }
    else if (card.get_rank() == RANK_NAMES_BY_WEIGHT[2]){
        return 4;
    }
    else if (card.get_rank() == RANK_NAMES_BY_WEIGHT[3]){
        return 5;
    }
    else if (card.get_rank() == RANK_NAMES_BY_WEIGHT[4]){
        return 6;
    }
    else if (card.get_rank() == RANK_NAMES_BY_WEIGHT[5]){
        return 7;
    }
    else if (card.get_rank() == RANK_NAMES_BY_WEIGHT[6]){
        return 8;
    }
    else if (card.get_rank() == RANK_NAMES_BY_WEIGHT[7]){
        return 9;
    }
    else if (card.get_rank() == RANK_NAMES_BY_WEIGHT[8]){
        return 10;
    }
    else if (card.get_rank() == RANK_NAMES_BY_WEIGHT[9]){
        return 11;
    }
    else if (card.get_rank() == RANK_NAMES_BY_WEIGHT[10]){
        return 12;
    }
    else if (card.get_rank() == RANK_NAMES_BY_WEIGHT[11]){
        return 13;
    }
    else {
        return 14;
    }
}

static int cardIntSuit(const Card &card){
    if (card.get_suit() == SUIT_NAMES_BY_WEIGHT[0]){
        return 0;
    }
    else if (card.get_suit() == SUIT_NAMES_BY_WEIGHT[1]){
        return 1;
    }
    else if (card.get_suit() == SUIT_NAMES_BY_WEIGHT[2]){
        return 2;
    }
    else {
        return 3;
    }
}

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec (see the appendices) before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=

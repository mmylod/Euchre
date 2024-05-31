//Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Player.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <cassert>
#include <sstream>

using namespace std;

class SimplePlayer : public Player {
private:
    vector<Card> hand;
    string name;
public:
    SimplePlayer(const string &p_name){
        name = p_name;
    }
    const std::string & get_name() const{
        return name;
    }
    void add_card(const Card &c){
        assert(hand.size() < MAX_HAND_SIZE);
        hand.push_back(c);
    }
    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, std::string &order_up_suit) const {
        int faceNumber = 0;
        if (round == 1) {
            for (int i = 0; i < hand.size(); i++) {
                if (hand[i].is_face() && hand[i].is_trump(upcard.get_suit())) {
                    faceNumber++;
                }
            }
            if (faceNumber >= 2) {
                order_up_suit = upcard.get_suit();
                return true;
            }
            else {
                return false;
            }
        }
        else{
            if (is_dealer) {
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
            }
            for (int i = 0; i < hand.size(); i++) {
                if (hand[i].is_face() &&
                    hand[i].is_trump(Suit_next(upcard.get_suit()))) {
                    faceNumber++;
                }
            }
            if (faceNumber >= 1) {
                order_up_suit = (Suit_next(upcard.get_suit()));
                return true;
            }
            else {
                return false;
            }
        }
    }
    
    void add_and_discard(const Card &upcard){
        hand.push_back(upcard);
        Card lowest = hand[0];
        int lowestIndex = 0;
        for (int i = 1; i < hand.size(); i++) {
            if (Card_less(hand[i], lowest, upcard.get_suit())){
                lowest = hand[i];
                lowestIndex = i;
            }
        }
        hand.erase(hand.begin() + lowestIndex);
    }
    
    Card lead_card(const std::string &trump){
        int trumpCount = 0;
        for (int i = 0; i < hand.size(); i++) {
            if (hand[i].is_trump(trump)) {
                trumpCount++;
            }
        }
        if (trumpCount == hand.size()) {
            Card highest = hand[0];
            int highestIndex = 0;
            for (int i = 1; i < hand.size(); i++) {
                if (Card_less(highest, hand[i], trump)){
                    highest = hand[i];
                    highestIndex = i;
                }
            }
            hand.erase(hand.begin() + highestIndex);
            return highest;
        }
        else {
            Card highest;
            int highestIndex = -1;
            for (int i = 0; i < hand.size(); i++) {
                if (!hand[i].is_trump(trump)) {
                    highest = hand[i];
                    highestIndex = i;
                }
            }
            //have our starting card now
            
            for (int i = 0; i < hand.size(); i++) {
                if (Card_less(highest, hand[i], trump) && !hand[i].is_trump(trump)){
                    highest = hand[i];
                    highestIndex = i;
                }
            }
            hand.erase(hand.begin() + highestIndex);
            return highest;
        }
    }
    Card play_card(const Card &led_card, const std::string &trump){
        
        int numSameSuit = 0;
        int highestIndex = 0;
        for (int i = 0; i < hand.size(); i++) {
            if (hand[i].get_suit(trump) == led_card.get_suit(trump)){
                numSameSuit++;
                highestIndex = i;
            }
        }
        if (numSameSuit > 0) {
            // follows suit
            Card highestCard = hand[highestIndex];
            for (int i = 0; i < hand.size(); i++) {
                if (Card_less(highestCard, hand[i], led_card, trump)
                    && hand[i].get_suit(trump) == led_card.get_suit(trump)){
                    highestCard = hand[i];
                    highestIndex = i;
                }
            }

            hand.erase(hand.begin() + highestIndex);
            return highestCard;
        }
        else {
            // does not follow suit
            Card lowestCard = hand[0];
            int lowestIndex = 0;
            for (int i = 0; i < hand.size(); i++) {
                if (Card_less(hand[i], lowestCard, trump)){
                    lowestCard = hand[i];
                    lowestIndex = i;
                }
            }

            hand.erase(hand.begin() + lowestIndex);
            return lowestCard;
        }
    }
    
};

class HumanPlayer : public Player {
private:
    vector<Card> hand;
    string name;
public:
    HumanPlayer(const string &p_name){
        name = p_name;
    }
    const std::string & get_name() const{
        return name;
    }
    void add_card(const Card &c){
        assert(hand.size() < MAX_HAND_SIZE);
        hand.push_back(c);
    }
    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, std::string &order_up_suit) const {
        
        vector<Card> copyHand;
        for (int i = 0; i < hand.size(); i++){
            copyHand.push_back(hand[i]);
        }
        sort(copyHand.begin(), copyHand.end());
        for (int i = 0; i < hand.size(); i++) {
            cout << "Human player " << name << "'s hand: "
            << "[" << i << "] " << copyHand[i] << endl;
        }
        cout << "Human player " << name << ", please enter a suit, or \"pass\":" << endl;
        string decision;
        cin >> decision;
        if (decision == "pass") {
            return false;
        }
        else {
            order_up_suit = decision;
            return true;
        }
    }
    void add_and_discard(const Card &upcard){
        vector<Card> copyHand;
        for (int i = 0; i < hand.size(); i++){
            copyHand.push_back(hand[i]);
        }
        sort(copyHand.begin(), copyHand.end());
        for (int i = 0; i < copyHand.size(); i++) {
            cout << "Human player " << name << "'s hand: "
            << "[" << i << "] " << copyHand[i] << endl;
        }
        copyHand.push_back(upcard);
        cout << "Discard upcard: [-1]" << endl;
        cout << "Human player " << name << ", please select a card to discard:" << endl;
        int decision;
        cin >> decision;
        if (decision == -1){
            decision = (int)copyHand.size() - 1;
           
        }
        else{
            Card deletedCard = copyHand[decision];
            for (int i = 0; i < hand.size(); i++){
                if (hand[i] == deletedCard){
                    hand.erase(hand.begin() + i);
                }
            }
            hand.push_back(upcard);
        }
        
        
//        for (int i = 0; i < copyHand.size(); i++){
//            hand[i] = copyHand[i];
//        }
        
        
    }
    Card lead_card(const std::string &trump){
        // printing the hand
        vector<Card> copyHand;
        for (int i = 0; i < hand.size(); i++){
            copyHand.push_back(hand[i]);
        }
        sort(copyHand.begin(), copyHand.end());
        for (int i = 0; i < copyHand.size(); i++) {
            cout << "Human player " << name << "'s hand: "
            << "[" << i << "] " << copyHand[i] << endl;
        }
        
        cout << "Human player " << name << ", please select a card:" << endl;
        int discardedCard;
        cin >> discardedCard;
        Card leadReturn = copyHand[discardedCard];
        for (int i = 0; i < hand.size(); i++){
            if (hand[i] == leadReturn){
                hand.erase(hand.begin() + i);
            }
        }
//        hand.erase(hand.begin() + discardedCard);
//        for (int i = 0; i < copyHand.size(); i++){
//            hand[i] = copyHand[i];
//        }
        return leadReturn;
        
    }
    Card play_card(const Card &led_card, const std::string &trump){
        // printing the hand
        vector<Card> copyHand;
        for (int i = 0; i < hand.size(); i++){
            copyHand.push_back(hand[i]);
        }
        sort(copyHand.begin(), copyHand.end());
        int j = 0;
        for (j = 0; j < copyHand.size(); j++) {
            cout << "Human player " << name <<
            "'s hand: " << "[" << j << "] " << copyHand[j] << endl;
        }
        
        cout << "Human player " << name << ", please select a card:" << endl;
        int playCard;
        cin >> playCard;
        Card playReturn = copyHand[playCard];
        for (int i = 0; i < hand.size(); i++){
            if (hand[i] == playReturn){
                hand.erase(hand.begin() + i);
            }
        }
//        hand.erase(hand.begin() + playCard);
//        for (int i = 0; i < copyHand.size(); i++){
//            hand[i] = copyHand[i];
//        }
        return playReturn;
        
    }
};

Player * Player_factory(const std::string &name,
                        const std::string &strategy) {
  // We need to check the value of strategy and return
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
      return new SimplePlayer(name);
  }
  else if (strategy == "Human"){
      return new HumanPlayer(name);
  }
  else {
      assert(false);
      return nullptr;
  }
}

std::ostream & operator<<(std::ostream &os, const Player &p){
    os << p.get_name();
    return os;
}




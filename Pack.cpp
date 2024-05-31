// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Pack.h"
using namespace std;

Pack::Pack(){
    cards[0] = Card("Nine", "Spades");
    cards[1] = Card("Ten", "Spades");
    cards[2] = Card("Jack", "Spades");
    cards[3] = Card("Queen", "Spades");
    cards[4] = Card("King", "Spades");
    cards[5] = Card("Ace", "Spades");
    
    cards[6] = Card("Nine", "Hearts");
    cards[7] = Card("Ten", "Hearts");
    cards[8] = Card("Jack", "Hearts");
    cards[9] = Card("Queen", "Hearts");
    cards[10] = Card("King", "Hearts");
    cards[11] = Card("Ace", "Hearts");
    
    cards[12] = Card("Nine", "Clubs");
    cards[13] = Card("Ten", "Clubs");
    cards[14] = Card("Jack", "Clubs");
    cards[15] = Card("Queen", "Clubs");
    cards[16] = Card("King", "Clubs");
    cards[17] = Card("Ace", "Clubs");
    
    cards[18] = Card("Nine", "Diamonds");
    cards[19] = Card("Ten", "Diamonds");
    cards[20] = Card("Jack", "Diamonds");
    cards[21] = Card("Queen", "Diamonds");
    cards[22] = Card("King", "Diamonds");
    cards[23] = Card("Ace", "Diamonds");
    
    next = 0;
}

Pack::Pack(std::istream& pack_input){
    string rank;
    string of;
    string suit;
    for (int i = 0; i < PACK_SIZE; i++) {
        pack_input >> rank;
        pack_input >> of;
        pack_input >> suit;
        cards[i] = Card(rank, suit);
    }
    next = 0;
}

Card Pack::deal_one(){
    Card card = cards[next];
    next++;
    return card;
}

void Pack::reset(){
    next = 0;
}

void Pack::shuffle(){
    Card temp[PACK_SIZE];
    for (int i = 0; i < 7; i++){
        for (int tempIterator = 0; tempIterator < PACK_SIZE - 1; tempIterator+= 2){
            if (tempIterator % 2 == 0){
                temp[tempIterator] = cards[(tempIterator / 2) + 12];
                temp[tempIterator + 1] = cards[(tempIterator) / 2];
            }

        }

        for (int j = 0; j < PACK_SIZE; j++){
            cards[j] = temp[j];
        }
    }
    next = 0;
}

bool Pack::empty() const{
    if (next == 24){
        return true;
    }
    else {
        return false;
    }
}




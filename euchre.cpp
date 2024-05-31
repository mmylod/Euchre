// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Card.h"
#include "Player.h"
#include "Pack.h"
#include <string>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

bool terminalArgumentCheck(int argc, char** argv);

class Euchre{
public:
    vector<Player*> players;
    Pack cards;
    int pointsGoal;
    bool shuffle;
    string trump;
    int team13Points;
    int team24Points;
    int team13TotalPoints;
    int team24TotalPoints;
    int orderUpIndexPerson;
    
    
    Euchre(Pack cards_param, vector<Player*> players_param,
           int pointsGoal_param, bool shuffle_param){
        for (int i = 0; i < players_param.size(); i++){
            players.push_back(players_param[i]);
        }
        cards = cards_param;
        pointsGoal = pointsGoal_param;
        shuffle = shuffle_param;
        team13Points = 0;
        team24Points = 0;
        team13TotalPoints = 0;
        team24TotalPoints = 0;
        orderUpIndexPerson = 0;
    }
    void beginGame(){
        int amtHands = 0;
        int dealer = 0;
        int x = 0;
        while (team13TotalPoints < pointsGoal && team24TotalPoints < pointsGoal){
            x++;
            //hand
            if (shuffle){
                cards.shuffle();
            }
            else{
                cards.reset();
            }
            
            dealToPlayers(cards, dealer);
            
            
            cout << "Hand " << amtHands << endl;
            cout << players[dealer]->get_name() << " deals" << endl;
            Card upcard = cards.deal_one();
            cout << upcard << " turned up" << endl;
            
            makeTrump(upcard , dealer);
            
            team13Points = 0;
            team24Points = 0;
            int playTrickDealer = dealer;
            for (int i = 0; i < 5; i++){
                playTrick(playTrickDealer, i);
            }
            calculateHandWinner();
            addTotalPoints();
            cout << players[0]->get_name() << " and " << players[2]->get_name()
            << " have " << team13TotalPoints << " points" << endl;
            cout << players[1]->get_name() << " and " << players[3]->get_name()
            << " have " << team24TotalPoints << " points" << endl;
            
            amtHands++;
            dealer++;
            if (dealer > 3){
                dealer = 0;
            }
            cout << endl;
        }
        
        whoWins();
        deletePlayers();
        
        
        
        
        
    }
    void dealToPlayers(Pack &pack_param, int dealer){
        dealer++;
        if (dealer > 3){
            dealer = 0;
        }
        players[dealer]->add_card(pack_param.deal_one());
        players[dealer]->add_card(pack_param.deal_one());
        players[dealer]->add_card(pack_param.deal_one());
        dealer++;
        dealer += 3;
        dealer -= 3;
        if (dealer > 3){
            dealer = 0;
        }
        players[dealer]->add_card(pack_param.deal_one());
        players[dealer]->add_card(pack_param.deal_one());
        dealer++;
        if (dealer > 3){
            dealer = 0;
        }
        players[dealer]->add_card(pack_param.deal_one());
        players[dealer]->add_card(pack_param.deal_one());
        players[dealer]->add_card(pack_param.deal_one());
        dealer++;
        dealer += 2;
        dealer -= 2;
        if (dealer > 3){
            dealer = 0;
        }
        players[dealer]->add_card(pack_param.deal_one());
        players[dealer]->add_card(pack_param.deal_one());
        dealer++;
        if (dealer > 3){
            dealer = 0;
        }
        dealTheRest(pack_param, dealer);
    }
    void dealTheRest(Pack &pack_param, int &dealer){
        players[dealer]->add_card(pack_param.deal_one());
        players[dealer]->add_card(pack_param.deal_one());
        dealer++;
        if (dealer > 3){
            dealer = 0;
        }
        players[dealer]->add_card(pack_param.deal_one());
        players[dealer]->add_card(pack_param.deal_one());
        players[dealer]->add_card(pack_param.deal_one());
        dealer++;
        dealer++;
        dealer--;
        if (dealer > 3){
            dealer = 0;
        }
        players[dealer]->add_card(pack_param.deal_one());
        players[dealer]->add_card(pack_param.deal_one());
        dealer++;
        dealer += 4;
        dealer -= 4;
        if (dealer > 3){
            dealer = 0;
        }
        players[dealer]->add_card(pack_param.deal_one());
        players[dealer]->add_card(pack_param.deal_one());
        players[dealer]->add_card(pack_param.deal_one());
    }
    void makeTrump(Card upcard, int dealer){
        trump = upcard.get_suit();
        int realDealer = dealer;
        dealer++;
        if (dealer > 3){
            dealer = 0;
        }
        bool is_dealer;
        for (int i = 0; i < 4; i++){
            //round 1
            
            if (realDealer == dealer){
                is_dealer = true;
            }
            else{
                is_dealer = false;
            }
            if (players[dealer]->make_trump(upcard, is_dealer, 1, trump)){
                cout << players[dealer]->get_name() <<
                " orders up " << trump <<endl << endl;
                players[realDealer]->add_and_discard(upcard);
                orderUpIndexPerson = dealer;
                return;
            }
            else{
                cout << players[dealer]->get_name() << " passes" << endl;
            }
            dealer++;
            if (dealer > 3){
                dealer = 0;
            }
        }
        trump = Suit_next(trump);
        for (int i = 0; i < 4; i++){
            //round 2
            //if player ordered up in round 1, function would have returned
            if (realDealer == dealer){
                is_dealer = true;
            }
            else{
                is_dealer = false;
            }
            if (players[dealer]->make_trump(upcard, is_dealer, 2, trump)){
                cout << players[dealer]->get_name() <<
                " orders up " << trump <<endl << endl;
                orderUpIndexPerson = dealer;
                return;
            }
            else{
                cout << players[dealer]->get_name() << " passes" << endl;
            }
            dealer++;
            if (dealer > 3){
                dealer = 0;
            }
        }
    }
    void playTrick(int &dealer, int i){
        if (i == 0){
            dealer++;
            if (dealer > 3){
                dealer = 0;
            }
        }
        
        Card ledcard;
        Card playCard;
        Card highestCard;
        int winnerIndex = -1;
        vector<Card> playedCards;
        for (int i = 0; i < 4; i++){
            if (i == 0){
                //lead card person
                ledcard = players[dealer]->lead_card(trump);
                cout << ledcard << " led by " << players[dealer]->get_name() << endl;
                playedCards.push_back(ledcard);
                highestCard = ledcard;
                winnerIndex = dealer;
            }
            else{
                dealer++;
                if (dealer > 3){
                    dealer = 0;
                }
                playCard = players[dealer]->play_card(ledcard, trump);
                cout << playCard << " played by " << players[dealer]->get_name() << endl;
                playedCards.push_back(playCard);
                if (Card_less(highestCard, playCard, ledcard, trump)){
                    highestCard = playCard;
                    winnerIndex = dealer;
                }
            }
        }
        cout << players[winnerIndex]->get_name() << " takes the trick" << endl << endl;
        if (winnerIndex == 0 || winnerIndex == 2){
            team13Points++;
        }
        else{
            team24Points++;
        }
        dealer = winnerIndex;
        
    }
    
    void calculateHandWinner(){
        if (team13Points > team24Points){
            cout << players[0]->get_name() << " and "
            << players[2]->get_name() << " win the hand" << endl;
        }
        else{
            cout << players[1]->get_name() << " and "
            << players[3]->get_name() << " win the hand" << endl;
        }
    }
    
    void addTotalPoints(){
        if (team13Points > team24Points){
            //team 13 won
            if (orderUpIndexPerson == 0 || orderUpIndexPerson == 2){
                if (team13Points != 5){
                    team13TotalPoints++;
                }
                else{
                    cout << "march!" << endl;
                    team13TotalPoints += 2;
                }
            }
            else{
                cout << "euchred!" << endl;
                team13TotalPoints += 2;
            }
        }
        else{
            //team 24 won
            if (orderUpIndexPerson == 1 || orderUpIndexPerson == 3){
                if (team24Points != 5){
                    team24TotalPoints++;
                }
                else{
                    cout << "march!" << endl;
                    team24TotalPoints += 2;
                }
            }
            else{
                cout << "euchred!" << endl;
                team24TotalPoints += 2;
            }
        }
    }
    void whoWins(){
        if (team13TotalPoints > team24TotalPoints){
            cout << players[0]->get_name() <<
            " and " << players[2]->get_name() << " win!" << endl;
        }
        else{
            cout << players[1]->get_name() <<
            " and " << players[3]->get_name() << " win!" << endl;
        }
    }
    void deletePlayers(){
        delete players[0];
        delete players[1];
        delete players[2];
        delete players[3];
    }
    

    
};

int main(int argc, char** argv) {
    if (!terminalArgumentCheck(argc, argv)){
        return 1;
    }
    ifstream in;
    in.open((string)argv[1]);
    if (!in.is_open()) {
        cout << "Error opening " << (string)argv[1] << endl;
    }
    //first statement
    for (int i = 0; i < argc; i++) {
        cout << argv[i] << " ";
    }
    cout << endl;
    vector<Player*> players;
    Player *player1 = Player_factory(argv[4], argv[5]);
    players.push_back(player1);
    Player *player2 = Player_factory(argv[6], argv[7]);
    players.push_back(player2);
    Player *player3 = Player_factory(argv[8], argv[9]);
    players.push_back(player3);
    Player *player4 = Player_factory(argv[10], argv[11]);
    players.push_back(player4);
    Pack cards(in);
    int pointsGoal = atoi(argv[3]);
    bool shuffle;
    if ((string)argv[2] == "shuffle"){
        shuffle = true;
    }
    else{
        shuffle = false;
    }
    Euchre euchre(cards, players, pointsGoal, shuffle);
    euchre.beginGame();
    
}


bool terminalArgumentCheck(int argc, char** argv){
    if (argc != 12) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        return false;
    }
    if (!(atoi(argv[3]) <= 100 && atoi(argv[3]) >= 1)) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
        return false;
    }
    if (!((string)argv[2] == "noshuffle" || (string)argv[2] == "shuffle")) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
        return false;
    }
    if ((string)argv[5] != "Simple" && (string)argv[5] != "Human") {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
        return false;
    }
    if ((string)argv[7] != "Simple" && (string)argv[7] != "Human") {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
        return false;
    }
    if ((string)argv[9] != "Simple" && (string)argv[9] != "Human") {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
        return false;
    }
    if ((string)argv[11] != "Simple" && (string)argv[11] != "Human") {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
        return false;
    }
    return true;
}

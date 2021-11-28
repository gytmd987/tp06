#ifndef __CARD_H__
#define __CARD_H__

#include <vector>  
#include <ctime>  
#include <string>  
#include <iostream> 
const int CARD_CNT = 25;

using namespace std;

class Player;
class Card {
    private:
        int str;
        int HP;
        int MP;
        bool ability;
        int number;
        bool canAttack;
    public:  
        Card();
        Card(int number_);
        void show();
        void attack_able(bool tmp);
        bool check_canAttack();
        int check_str();
        void attacked(int power);
        int check_HP();
        int check_num();
        void set_str();
        int get_mp();

};
class Deck {
    private:
        vector<Card> card_camp;
        vector<Card> card_list; 
        vector<Card> card_hand;
    public:
        Deck();
        void init();
        void shuffle();
        void getCard();
        void advantage();
        void print_hand();
        int put_card(int normal_card_num);
        friend class Player;
        void start_attack(Deck& enemyDeck, Player& enemyPlayer, Player& myPlayer);
        void print_camp(Deck& enemy, int enemy_HP, int my_HP);
        void use_magic_card(int magic_card_num, Player& Px, Player& Py);
        int if_magic();
        int if_hand();
        vector<Card> get_hand();
        int hand_cnt();
        int camp_cnt();

};

#endif

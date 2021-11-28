#include "person.h"
#include <iostream>
Player::Player() {
    maxHP = 0;
    type = 0;
    HP = 0;
    MP = 0;
    dot.clear();
    name = {};
                            
}

Player::Player(string name_, int type_) {
        name = name_;
        type = type_;
        if (type == 2) {
            maxHP = 40;
            HP = 40;
            type = 0;
        }
        else {
            maxHP = 30;
            HP = 30;
                                    
        }
        MP = 3;
        dot.clear();
                    
}

void Player::show_state() {
    printf("HP : %d\tMP : %d\t\t",HP, MP);
    if (type) 
        printf("ultimate skill : able\n");
    else
        printf("ultimate skill : unable\n");
                
}
bool Player::   check() {
    return HP > 0 ? true : false;
        
}

void Player::dot_set(int tim, int num) {
    pair<int, int> p;
    p.first = tim;
    p.second = num;
    dot.push_back(p);
                    
}

void Player::end_turn() {
    if (dot.size() == 0)
        return;
    for (unsigned int i = 0; i < dot.size(); i++) {
        if (dot[i].first == 0)
            continue;
        HP += dot[i].second;
        if (HP > maxHP)
            HP = maxHP;
        dot[i].first--;                                     
        }
        
}

int Player::get_type() {
    return type;        
}

void Player::attacked(int power) {
    HP -= power;        
}

void Player::use_ultimate(Player& enemy, Deck& PxDeck, Deck& PyDeck) {
    int type = this->get_type();
    if (!type) {
        printf("can't use ultimate\n");
        return;                                
    }
    this->type = 0;

    if (type == 1) {
        enemy.attacked(10);                            
    }
    else if (type == 3) {
        this->dot_set(4, 4);                            
    }
    else {
        PxDeck.card_camp.clear();
        PyDeck.card_camp.clear();                                    
    }
            
}

void Player::MP_adder(int num) {
    this->MP += num;
    if (this->MP > 10)
        this->MP = 10;            
}
string Player::get_name() { return this->name; }
int Player::get_mp() { return this->MP; }
int Player::get_hp() { return this->HP; }


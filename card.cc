#include "card.h"
#include "person.h"
#include <iostream>
#include <algorithm>
using namespace std;

Card::Card() {
    str = 1;
    HP = 1;
    MP = 1;
    ability = false;
    number = -1;
    canAttack = false;
}

Card::Card(int number_) {
    if (number_ < 0 || number_ > 16) {
        printf("card initialize error\n");
        return;
    }
    str = 0;
    HP = 0;
    MP = 0;
    canAttack = true;
    if (number_ < 10)
        ability = false;
    else
        ability = true;
    number = number_;
    switch (number_) {
        case 0:
            str = 4;
            HP = 4;
            MP = 4;
            break;
        case 1:
            str = 1;
            HP = 1;
            MP = 1;
            break;
        case 2:
            str = 3;
            HP = 1;
            MP = 2;
            break;
        case 3:
            str = 2;
            HP = 2;
            MP = 2;
            break;
        case 4:
            str = 1;
            HP = 3;
            MP = 2;
            break;
        case 5:
            str = 5;
            HP = 1;
            MP = 3;
            break;
        case 6:
            str = 3;
            HP = 3;
            MP = 3;
            break;
        case 7:
            str = 1;
            HP = 5;
            MP = 3;
            break;
        case 8:
            str = 2;
            HP = 12;
            MP = 5;
            break;
        case 9:
            str = 6;
            HP = 6;
            MP = 5;
            break;
    }
}

void Card::show() {
    if (ability) {
        if (number == 10) printf("[마법] 즉시 마나 1을 회복한다");
        if (number == 11) printf("[마법] 즉시 마나 2를 회복한다");
        if (number == 12) printf("[마법] 즉시 체력 2를 회복한다");
        if (number == 13) printf("[마법] 3턴동안 체력을 1씩 회복한다");
        if (number == 14) printf("[마법] 진영의 모든 카드 공격력이 1 증가시킨다");
        if (number == 15) printf("[마법] 상대 영웅의 체력을 2 깎는다");
        if (number == 16) printf("[마법] 카드를 즉시 2장 뽑는다");
    }
    else 
        printf("[일반] STR : %d\t\tHP : %d\t\tCOST : %d",str, HP, MP);
}
void Card::attack_able(bool tmp) {
    canAttack = tmp;
}
bool Card::check_canAttack() {
    return this->canAttack;
}
int Card::check_str() {
    return this->str;
}
void Card::attacked(int power) {
    this->HP -= power;
}
int Card::check_HP() { return this->HP;  }
int Card::check_num() { return this->number;  }
void Card::set_str() { this->str += 1;  }
int Card::get_mp() {
    return this->MP;
}

Deck::Deck() {
    srand((unsigned int)time(NULL));
    card_list.clear();
    card_camp.clear();
    card_hand.clear();
    init();
}

void Deck::init() {
    for (int i = 0; i < 8; i++) {
        card_list.push_back(Card(i));
        card_list.push_back(Card(i));
    }
    for (int i = 8; i < 17; i++)
        card_list.push_back(Card(i));
}

void Deck::shuffle() {
    for (int i = 0; i < 400; i++) {
        int left = rand() % CARD_CNT;;
        int right = rand() % CARD_CNT;;
        Card tmp = card_list[left];
        card_list[left] = card_list[right];
        card_list[right] = tmp;
    }
}

int Deck::if_magic() {
    for (unsigned int i = 0; i < card_hand.size(); i++) 
        if (card_hand[i].check_num() > 9) 
            return 1;    
    return 0;
}

int Deck::if_hand() {
    for (unsigned int i = 0; i < card_hand.size(); i++) {
        if (card_hand[i].check_num() < 10) return 1;
    }
    return 0;
}

void Deck::getCard() {
    Card card;
    if (card_list.size() >= 1) {
        card = card_list[card_list.size() - 1];
        card_list.pop_back();
    }
    card_hand.push_back(card);
}

void Deck::print_hand() {
    for (unsigned int i = 0; i < card_hand.size(); i++) {
        printf("%d번 : ", i + 1);
        card_hand[i].show();
        printf("\n");
    }
}

void Deck::advantage() {
    card_hand.push_back(Card(10));
}

int Deck::put_card(int normal_card_num) {
    Card tmp = card_hand[normal_card_num - 1];
    if (card_hand.size() > 1)
        card_hand.erase(card_hand.begin() + normal_card_num - 1);
    else
        card_hand.clear();
    card_camp.push_back(tmp);
}

void Deck::start_attack(Deck& enemyDeck, Player& enemyPlayer, Player& myPlayer) {
    for (unsigned int i = 0; i < card_camp.size(); i++) 
        card_camp[i].attack_able(true);    
    //print_camp(enemyDeck, enemyPlayer.get_hp(), myPlayer.get_hp());
    int cnt = card_camp.size();
    while (cnt) {
        int tmp, tmp2;
        printf("몇번 카드로 누구를 공격하시겠습니까?\n");
        cin >> tmp >> tmp2;
        if (tmp < 1 || (unsigned)tmp > card_camp.size()) {
            printf("진영에 없는 카드입니다. 다시 입력해주세요.\n");
            continue;
        }
        if (!card_camp[tmp - 1].check_canAttack()) {
            printf("이미 공격 한 카드입니다. 다시 입력해주세요.\n");
            continue;
        }
        if (tmp2 < 0 || tmp2 > enemyDeck.camp_cnt()) {
            printf("잘못된 대상입니다. 다시 입력해주세요.\n");
            continue;
        }
        card_camp[tmp-1].attack_able(false);
        int pow = card_camp[tmp-1].check_str();
        if (tmp2 == 0) {
            enemyPlayer.attacked(pow);
            if (enemyPlayer.check() == 0) {
                cout<< enemyPlayer.get_name()<<" 플레이어 사망\n";
                break;
            }
        }
        else {
            enemyDeck.card_camp[tmp2 - 1].attacked(pow);
            if (enemyDeck.card_camp[tmp2 - 1].check_HP() <= 0) {
                printf("해당 카드의 HP가 0이 되어 사라집니다.\n");
                enemyDeck.card_camp.erase(enemyDeck.card_camp.begin() + tmp2 - 1);
            }
        }
        printf("\n\n");
        print_camp(enemyDeck, enemyPlayer.get_hp(), myPlayer.get_hp());
        cnt--;
    }
}
void Deck::print_camp(Deck& enemy, int enemy_HP, int my_HP) {
    printf("┌-----------------------------------------------------------------┐\n");
    printf("│                            상대 진영                            │\n");
    printf("│                                                                 │\n");
    printf("│   0번: [영웅]                 HP : %d                           │\n",enemy_HP);
    if (enemy.card_camp.size() == 0)
        printf("│                                                                 │\n");
    for (unsigned int i = 0; i < enemy.card_camp.size(); i++) {
        printf("│   %d번: ", i + 1);
        enemy.card_camp[i].show();
        printf("          │\n");
    }
    printf("├-----------------------------------------------------------------┤\n");
    printf("│                            나의 진영                            │\n");
    printf("│                                                                 │\n");
    printf("│   0번: [영웅]                 HP : %d                           │\n", my_HP);
    if (this->card_camp.size() == 0)
        printf("│                                                                 │\n");
    for (unsigned int i = 0; i < this->card_camp.size(); i++) {
        printf("│   %d번: ", i + 1);
        this->card_camp[i].show();
        printf("          │\n");
    }
    printf("└-----------------------------------------------------------------┘\n");    
}

void Deck::use_magic_card(int magic_card_num, Player& Px, Player& Py) {
    Card tmp = card_hand[magic_card_num - 1];
    int num = tmp.check_num();
    if (card_hand.size() > 1)
        card_hand.erase(card_hand.begin() + magic_card_num - 1);
    else
        card_hand.clear();
    if (num == 10)
        Px.MP_adder(1);
    else if (num == 11)
        Px.MP_adder(2);
    else if (num == 12)
        Px.dot_set(1, 2);
    else if (num == 13)
        Px.dot_set(3, 1);
    else if (num == 14)
        for (unsigned int i = 0; i < this->card_camp.size(); i++)
            this->card_camp[i].set_str();
    else if (num == 15)
        Py.attacked(2);
    else if (num == 16) {
        this->getCard();
        this->getCard();
    }
}

vector<Card> Deck::get_hand() { return this->card_hand; }
int Deck::hand_cnt() { return card_hand.size();  }
int Deck::camp_cnt() { return card_camp.size();  }

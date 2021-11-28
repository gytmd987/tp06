#include <iostream>
#include <string>
#include <unistd.h>
#include "card.h"
#include "person.h"
#include <stdlib.h>
using namespace std;

void window_clear();
void make_Deck();
void get_type();
void rule_print();
void print_myDeck(Deck& deck, Player& player);
void print_start(Player& Px, Player& Py, Deck& PxDeck, Deck& PyDeck, int typ, int is_printDeck);
bool turn_start(Player& Px, Player& Py, Deck& PxDeck, Deck& PyDeck, int typ);
void start_game();

Deck Player1;
Deck Player2;
Player P1;
Player P2;

void window_clear() {
    system("clear");
}

void make_Deck() {
    Player1.shuffle();
    Player2.shuffle();
    for (int i = 0; i < 3; i++)
        Player1.getCard();
    for (int i = 0; i < 4; i++)
        Player2.getCard();
    Player2.advantage();
}

void get_type() {
    cout << "\t\t\t※    자신의 이름과 가지고 싶은 필살기 번호를 입력하세요    ※\n\n";
    cout << "\t\t\t\t1번 : 즉시 상대 영웅에게 10의 피해를 가합니다.\n";
    cout << "\t\t\t\t2번 : 체력이 10 높은 상태에서 게임을 시작합니다.\n";
    cout << "\t\t\t\t3번 : 4턴동안 자신의 체력을 4씩 회복합니다.\n";
    cout << "\t\t\t\t4번 : 현재 상대방과 자신의 진영에 있는 모든 카드를 파괴합니다.\n";
    string name1, name2;
    string str;

    printf("\n선공 플레이어의 닉네임을 입력하세요.\n");
    cin >> name1;
    printf("선공 플레이어의 필살기 번호를 입력하세요.\n");
    while (true) {
        cin >> str;
        if (str.length() == 1)
            if (str[0] == '1' || str[0] == '2' || str[0] == '3' || str[0] == '4')
                break;
        cout << "잘못 입력하셨습니다. 다시 입력해 주시길 바랍니다." << endl;
    }
    cout << "\n\t\t선공 " << name1 << " 플레이어는 " << str[0] << "번의 필살기를 선택하셨습니다.\n\n";
    P1 = Player(name1, str[0] - '0');


    printf("\n후공 플레이어의 닉네임을 입력하세요.\n");
    cin >> name2;
    printf("후공 플레이어의 필살기 번호를 입력하세요.\n");
    while (true) {
        cin >> str;
        if (str.length() == 1)
            if (str[0] == '1' || str[0] == '2' || str[0] == '3' || str[0] == '4')
                break;
        cout << "잘못 입력하셨습니다. 다시 입력해 주시길 바랍니다.\n";
    }
    cout << "\n\t\t후공 " << name2 << " 플레이어는 " << str[0] << "번의 필살기를 선택하셨습니다.\n\n\n";
    P2 = Player(name2, str[0] - '0');
}

void rule_print() {
    printf("\n\n\n");
    printf("\t\t\t\t┌----------------------------------------------┐\n");
    printf("\t\t\t\t│     게임 진행 전, 숙지해야 할 게임 규칙      │\n");
    printf("\t\t\t\t│           카드로 상대방을 공격 시            │\n");
    printf("\t\t\t\t│             0번 : 상대 플레이어              │\n");
    printf("\t\t\t\t│            그 외 : 상대 진영 카드            │\n");
    printf("\t\t\t\t└----------------------------------------------┘\n\n");
}
void print_myDeck(Deck& deck, Player& player) {
    printf("현재 나의 패 상태\n");
    deck.print_hand();
    printf("\n내 영웅의 상태 : ");
    player.show_state();

}

void print_start(Player& Px, Player& Py, Deck& PxDeck, Deck& PyDeck, int typ, int is_printDeck) {
    if (typ == 0)
        cout << "\n--------------------------- 선공 " << Px.get_name() << " 's turn start--------------------\n\n";
    else
        cout << "\n--------------------------- 후공 " << Px.get_name() << " 's turn start--------------------\n\n";
    printf("상대 영웅의 상태 : ");
    Py.show_state();
    cout << endl;
    PxDeck.print_camp(PyDeck, Py.get_hp(), Px.get_hp());
    cout << endl;
    if (is_printDeck) print_myDeck(PxDeck, Px);
    cout << endl << endl;
}

bool turn_start(Player& Px, Player& Py, Deck& PxDeck, Deck& PyDeck, int typ) {
    PxDeck.getCard();
    Px.MP_adder(1);
    print_start(Px,Py,PxDeck,PyDeck, typ, 1);

    if (Px.get_type() != 0) {
        printf("필살기를 사용하려면 'Y' 또는 'y'를 입력하여 주십시오.\n");
        string tmp;
        cin >> tmp;
        if (tmp == "Y" || tmp == "y") {
            Px.use_ultimate(Py, PxDeck, PyDeck);
            cout << "\n$$$$$$$$$$$$$$$$$$$$$$$$$   Use ultimate skill   $$$$$$$$$$$$$$$$$$$$\n\n";
        }
        sleep(1);
        window_clear();
        print_start(Px, Py, PxDeck, PyDeck, typ, 1);
    }

    while (PxDeck.if_magic()) {
        printf("진영에 내려놓을 마법 카드 번호를 입력하여 주세요. 내려 놓을 카드가 없다면 0을 눌러주세요\n");
        int magic_card_num;
        cin >> magic_card_num;
        if (magic_card_num == 0) {
            sleep(1);
            window_clear();
            print_start(Px, Py, PxDeck, PyDeck, typ, 1);
            break;
        }
        vector<Card> hand_list = PxDeck.get_hand();
        if (magic_card_num < 0 || magic_card_num > PxDeck.hand_cnt()) {
            printf("잘못 입력하셨습니다.\n");
            sleep(1);
            window_clear();
            print_start(Px, Py, PxDeck, PyDeck, typ, 1);
            continue;
        }
        if (hand_list[magic_card_num - 1].check_num() < 10) {
            printf("입력하신 번호는 마법 카드가 아닙니다\n");
            sleep(1);
            window_clear();
            print_start(Px, Py, PxDeck, PyDeck, typ, 1);
            continue;
        }
        PxDeck.use_magic_card(magic_card_num, Px, Py);
        sleep(1);
        window_clear();
        print_start(Px, Py, PxDeck, PyDeck, typ, 1);
    }
    Px.end_turn();

    while (PxDeck.if_hand()) {
        printf("진영에 내려놓을 일반 카드 번호를 입력하여 주세요. 내려놓을 카드가 없다면 0을 눌러주세요\n");
        int normal_card_num;
        cin >> normal_card_num;
        vector<Card> hand_list = PxDeck.get_hand();
        if (normal_card_num == 0) {
            sleep(1);
            window_clear();
            print_start(Px, Py, PxDeck, PyDeck, typ, 1);
            break;
        }
        if (normal_card_num < 0 || normal_card_num > PxDeck.hand_cnt()) {
            printf("잘못 입력하셨습니다.\n");
            sleep(1);
            window_clear();
            print_start(Px, Py, PxDeck, PyDeck, typ, 1);
            continue;
        }
        if (hand_list[normal_card_num - 1].check_num() >= 10) {
            printf("입력하신 번호는 일반 카드가 아닙니다\n");
            sleep(1);
            window_clear();
            print_start(Px, Py, PxDeck, PyDeck, typ, 1);
            continue;
        }
        if (hand_list[normal_card_num - 1].get_mp() > Px.get_mp()) {
            printf("마나가 부족합니다\n");
            sleep(1);
            window_clear();
            print_start(Px, Py, PxDeck, PyDeck, typ, 1);
            continue;
        }
        Px.MP_adder(-hand_list[normal_card_num - 1].get_mp());
        PxDeck.put_card(normal_card_num);
        sleep(1);
        window_clear();
        print_start(Px, Py, PxDeck, PyDeck, typ, 1);
    }
    PxDeck.start_attack(PyDeck, Py, Px);
    if (!Py.check()) {
        return true;
    }
    cout << "--------------------------- " << Px.get_name() << " 's turn  end --------------------\n";
    return false;
}

void start_game() {
    sleep(1);
    int cnt2 = 30;
    while(cnt2 >= 0) {
        window_clear();
        for (int cnt = cnt2/2; cnt > 0; cnt--) 
            printf("\n\n");   
        printf("================================                  ================================\n");
        printf("================================    GAME START    ================================\n");
        printf("================================                  ================================\n\n");
        cnt2 -= 2;
        usleep(50000);
    }

}
int main() {
    window_clear();
    rule_print();
    get_type();//P1 P2 set
    make_Deck();//Player1 Player2 set
    start_game();
    while (true) {
        window_clear();
        if (turn_start(P1, P2, Player1, Player2, 0)) {
            cout << P1.get_name() << " Player Win!!!\n";
            break;
        }
        sleep(2);
        window_clear();
        if (turn_start(P2, P1, Player2, Player1, 1)) {
            cout << P2.get_name() << " Player Win!!!\n";
            break;
        }
        sleep(2);
    }
    sleep(5);
    window_clear();
    printf("==================================================================================\n");
    printf("================================    GAME  END     ================================\n");
    printf("==================================================================================\n");
    sleep(5);
    window_clear();
}


fndef __PERSON_H__  
#define __PERSON_H__  

#include <string>  
#include "card.h"  
using namespace std;

class Player {
    private:
        string name;
        int type;//1~4
        int maxHP;
        int HP;
        int MP;
        vector<pair<int, int> > dot;
    public:
        friend class Deck;
        Player();
        Player(string name_, int type_);
        void show_state();
        bool check();
        void end_turn();
        void MP_adder(int num);
        void dot_set(int tim, int num);
        void use_ultimate(Player& enemy, Deck& PxDeck, Deck& PyDeck);
        void attacked(int power);
        int get_type();
        string get_name();
        int get_mp();
        int get_hp();
        
};

#endif


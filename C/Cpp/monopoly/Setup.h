#include <vector>
#include <string>
#include "chesscell.h"
#include "chessland.h"
#include "player.h"

void boardaction(std::vector<chess_land*> chesslands, player *p, int pos);
chess_land* postoland(std::vector<chess_land*> chesslands, int pos);
void action(std::vector<chess_land*> chesslands, player *p, int pos);
void jail(std::vector<chess_land*> chesslands, player *p, int pos);

int nplayer = 6;
int IniMoney = 2000;
int nCell = 40;
struct conflands{
    std::string s;
    int lp;
    int hp;
    std::vector<int> hr;
    int color;
    int mg;
    int pos;
};

//Setup for players
std::string pnames[] = {"A","B","C","D","E","F","G","H","I","J"};
float psafeper[] =  {0.9, 0.3, 1.0, 0.5, 0.95, 0.8, 0.2, 0.3, 0.1};

//Setup for cells
conflands alllands[] = {
       {"MEDITERRRANEAN AVENUE", 60, 50, {2, 10, 30, 90, 160, 250}, 0, 30, 1},
       {"BALTIC AVENUE", 60, 50, {4, 20, 60, 180, 320, 450}, 0, 30, 3},
       {"Oriental AVENUE", 100, 50, {6, 30, 90, 270, 400, 550}, 1, 50, 6},
       {"VERMONT AVENUE", 100, 50, {6, 30, 90, 270, 400, 550}, 1, 50, 8},
       {"CONNECTICUT AVENUE", 120, 50, {8, 40, 100, 300, 450, 600}, 1, 60, 9},
       {"ST. CHARLES PLACE", 140, 100, {10, 50, 150, 450, 620, 750}, 2, 70, 11},
       {"STATES AVENUE", 140, 100, {10, 50, 150, 450, 620, 750}, 2, 70, 13},
       {"VIRGINIA AVENUE", 160, 100, {12, 60, 180, 500, 700, 900}, 2, 80, 14},
       {"ST. JAMES PLACE", 180, 100, {14, 70, 200, 550, 750, 950}, 3, 90, 16},
       {"TENNESSEE AVENUE", 180, 100, {14, 70, 200, 550, 750, 950}, 3, 90, 18},
       {"NEW YORK AVENUE", 200, 100, {16, 80, 220, 600, 800, 1000}, 3, 100, 19},
       {"KENTUCKY AVENUE", 220, 150, {18, 90, 250, 700, 870, 1050}, 4, 110, 21},
       {"INDIANA AVENUE", 220, 150, {18, 90, 250, 700, 870, 1050}, 4, 110, 23},
       {"ILLINOIS AVENUE", 240, 150, {20, 100, 300, 750, 926, 1100}, 4, 120, 24},
       {"ATLANTIC AVENUE", 260, 150, {22, 110, 330, 800, 975, 1150}, 5, 130, 26},
       {"VENTNOR AVENUE", 260, 150, {22, 110, 330, 800, 975, 1150}, 5, 130, 27},
       {"MARVIN GARDENS", 280, 150, {24, 120, 360, 850, 1025, 1200}, 5, 140, 29},
       {"PACIFIC AVENUE", 300, 200, {26, 130, 390, 900, 1100, 1275}, 6, 150, 31},
       {"NORTH CAROLINA AVENUE", 300, 200, {26, 130, 390, 900, 1100, 1275}, 6, 150, 32},
       {"PENNSYLVANIA AVENUE", 320, 200, {28, 150, 450, 1000, 1200, 1400}, 6, 160, 34},
       {"PARK PLACE", 350, 200, {35, 175, 500, 1100, 1300, 1500}, 7, 175, 37},
       {"BOARDWAY", 400, 200, {50, 200, 600, 1400, 1700, 2000}, 7, 200, 39}
};

conflands allrr[] = {
       {"PENNSYLVANIA RAILROAD", 200, 0, {25, 50, 100, 200}, -1, 100, 5},
       {"B & O RAILROAD", 200, 0, {25, 50, 100, 200}, -1, 100, 15},
       {"SHORT LINE", 200, 0, {25, 50, 100, 200}, -1, 100, 25},
       {"READING RAILROAD", 200, 0, {25, 50, 100, 200}, -1, 100, 35}
};

conflands allut[] = {
       {"ELECTRIC COMPANY", 150, 0, {0}, -1, 75, 12},
       {"WATER WORKS", 150, 0, {0}, -1, 75, 28}
};


//Setup for Chest
void Chest(player *p, int pos){
    /*
    money = money - 50;
    money = money - 50;
    money = money + 200;
    money = money - nhouse * 40 - nhotel * 115;
    m = m + 100;
    m = m - 100;
//jail free
    m = m + 10;
    pos = 30;
    m = m + 100;
    m = m + 100;
    m = m + 10 * (nplayer - 1); //other - 10
    m = m + 50;
    m = m - 25;
    m = m + 20;
    pos = 0;
    */
    }

//Setup for Quest
void Quest(player *p, int pos){
    int money = p->get_money();
    /*
    pos = 11;    if(pos > 11) m = m + 200;
    p->set_money(money - nhouse * 25 - nhotel * 100);
    pos = 30;
    pos = 39;
    pos -= 3; if(pos < 3) pos += 37;
    pos = 0;
    money = money + 50;
    money = money - 15;
    pos = 5; if(pos > 5) m = m + 200;
    pos = (((pos + 5) / 10) + 1) * 5;
    pos = (pos>=12 && pos<28)?28:12;
//jail free
    m = m - 50 * (nplayer - 1); //other + 50
    pos = 24;    if(pos > 24) m = m + 200;
    money = money + 150;
    */
    p->set_money(p->get_money() + 1);
}
//
//
//
//
//Setup for board
//type: 0: Nothing, 1: Normal, 2:Chest, 3: Quest, 4: Jail
//
void directpay(player *p, int pos){
    int money = p->get_money();
    if(pos == 4) p->set_money(money - 200); 
    if(pos == 38) p->set_money(money - 100); 
    return;
}

void jail(std::vector<chess_land*> chesslands, player *p, int pos){
    if(p->get_pos() != 30 && pos == 30 ){
        p->set_injail(true);
        p->set_pos(30);//jail case
        return;
    }
    else if(p->get_pos() == 30 && pos == 10){
        if(p->roll_dice()) boardaction(chesslands, p, pos+p->roll_dice());
        p->set_pos(10);
        p->set_injail(false);
        return;
    }
}

void action(std::vector<chess_land*> chesslands, player *p, int pos){
    p->build(postoland(chesslands, pos));
    p->payrent(postoland(chesslands, pos));
}

std::vector<chess_land*> prepare(conflands alllands[], int nlands, int type){
    std::vector<chess_land*> chesslands;
    for(int iland = 0; iland < nlands; iland ++){
        chess_land *tmp = new chess_land();
        tmp->set_cellname(alllands[iland].s);
        tmp->set_state(-1);
        tmp->set_type(type);
        tmp->set_pos(alllands[iland].pos);
        tmp->set_landprice(alllands[iland].lp);
        tmp->set_houseprice(alllands[iland].hp);
        tmp->set_houserent(alllands[iland].hr);
        tmp->set_morgage(alllands[iland].mg);
        tmp->set_color(alllands[iland].color);
        chesslands.push_back(tmp);
    }
    return chesslands;
}

chess_land* postoland(std::vector<chess_land*> chesslands, int pos){
    for(int iland = 0; iland < chesslands.size(); iland ++){
        if(pos == chesslands[iland]->get_pos()) return chesslands[iland];
    }
    return NULL;
}

void Release(std::vector<chess_land*> chesslands, player *p){
    for(int iland = 0; iland < chesslands.size(); iland ++){
        if(chesslands[iland]->get_owned() == p){
            chesslands[iland]->set_owned(NULL);
            chesslands[iland]->set_state(-1);
        }
    }
    return;
}

void boardaction(std::vector<chess_land*> chesslands, player *p, int pos){
    if(p->get_injail()) pos = 10; 
    if(p->get_pos()>=pos && !p->get_injail()) {std::cout<<"passing go"<<std::endl; p->set_money(p->get_money() + 200); }
    if(pos == 0 || pos == 20);
    else if(pos == 4 || pos == 38) directpay(p, pos);
    else if(pos == 7 || pos == 22 || pos == 36) Quest(p, pos);
    else if(pos == 2 || pos == 17 || pos == 33) Chest(p, pos);
    else if(pos == 10 || pos == 30) jail(chesslands, p, pos);//jail case
    else action(chesslands, p, pos);
    p->set_pos(pos);
}


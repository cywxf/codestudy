#include "chesscell.h"
#include "chessland.h"
#include "player.h"
#include "Setup.h"
#include <iostream>

int main(){
    int nlands = sizeof(alllands)/sizeof(alllands[0]);
    std::vector<chess_land*> chesslands = prepare(alllands, nlands, 0);
    int nrr = sizeof(allrr)/sizeof(allrr[0]);
    std::vector<chess_land*> chessrr = prepare(allrr, nrr, 1);
    int nut = sizeof(allut)/sizeof(allut[0]);
    std::vector<chess_land*> chessut = prepare(allut, nut, 2);
    chesslands.insert( chesslands.end(), chessrr.begin(), chessrr.end() );
    chesslands.insert( chesslands.end(), chessut.begin(), chessut.end() );
    
    std::vector<player*> players;
    for(int iplayer = 0;iplayer< nplayer; iplayer++){
        player *p = new player();
        p->set_name(pnames[iplayer]);
        p->set_safeper(psafeper[iplayer]);
        p->set_money(IniMoney);
        p->set_pos(0);
        p->set_injail(false);
        p->set_nland(0);
        p->set_nrr(0);
        p->set_nmgg(0);
        p->set_nhouse(0);
        p->set_nhotel(0);
        players.push_back(p);
    }  

    srand (time(NULL));
    int nmove = 0;
    while(nplayer > 1){
        nmove ++;
    std::cout<< nmove << " round move" << std::endl;
    for(int iplayer = 0;iplayer< nplayer; iplayer++){
        player *p = players[iplayer];
        std::cout<< "Player " << p->get_name() << " money : " << p->get_money() << " His safe percentage is " << p->get_safeper() << std::endl;
        int rd = p->roll_dice();
        int pos = p->get_pos() + rd;
        pos = pos % nCell;
        std::cout<< "Throw " << rd << " Get Position " << pos << std::endl;
        boardaction(chesslands, p, pos);
        int ipos = 0;
        while(p->get_money()<0 && ipos < nCell){
            p->morgage(postoland(chesslands, ipos));
            ipos ++ ;
        }
      //  if(p->get_nmgg()>0 && p->get_money()>0)
      //       p->demorgage(postoland(chesslands, ipos));
        if(p->get_money()<0){
            Release(chesslands, p);
            players.erase(players.begin()+iplayer);
            iplayer --;
            std::cout<< p->get_name() << " BANKRUPTED! " << std::endl;
            nplayer --;
        } 
        std::cout<<std::endl;   
    }
}
}

#ifndef _PLAYER_H
#define _PLAYER_H
#include  <vector>
#include  <string>
#include  "chessland.h"

class chess_land;
//player
class player{
    public:
    player(){};
    ~player(){};
    private:
    std::string name;
    int money;
    int pos;
    int nhouse;
    int nhotel;
    int nland;
    int nrr;
    int nmgg;
    float safeper;
    bool injail;

    public:
    void set_injail(bool _injail){ injail = _injail;}
    void set_name(std::string _name){ name= _name;}
    void set_money(int _money){ money = _money;}
    void set_pos(int _pos){ pos = _pos;}
    void set_nhouse(int _nhouse){ nhouse = _nhouse;}
    void set_nhotel(int _nhotel){ nhotel = _nhotel;}
    void set_nland(int _nland){ nland = _nland;}
    void set_nrr(int _nrr){ nrr = _nrr;}
    void set_nmgg(int _nmgg){ nmgg = _nmgg;}
    void set_safeper(float _safeper){ safeper = _safeper; }

    bool get_injail(){ return injail;}
    std::string get_name(){ return name;}
    int get_money(){ return money;}
    int get_pos(){ return pos;}
    int get_nhouse(){ return nhouse;}
    int get_nhotel(){ return nhotel;}
    int get_nland(){ return nland;}
    int get_nrr(){ return nrr;}
    int get_nmgg(){ return nmgg;}
    float get_safeper(){ return safeper; }

    void build(chess_land *cl);
    void morgage(chess_land *cl);
    void payrent(chess_land *cl);
    int roll_dice();
};

#endif

#ifndef _STOCK_DATA_H
#define _STOCK_DATA_H
#include <string>
#include <iostream>

struct Time{
    int year;
    int month;
    int date;
    int hour;
    int minute;
    int second;
    int micros;
};


class stock_data{
    public:
        stock_data(){};
        ~stock_data(){};
        stock_data(const std::string& t);
        int get_diff(const stock_data& d);
        Time get_time() const{ return time;}
        float get_price() const{ return price;}
        std::string get_exchange() const{ return exchange;}
        
    private:
        Time time;
        std::string ticker;
        float price;
        float size;
        std::string exchange;
};

#endif

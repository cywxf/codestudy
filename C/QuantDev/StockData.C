#include "StockData.h"
#include <assert.h>     /* assert */
#include <string.h>

stock_data::stock_data(const std::string &t){ // read information from string
    char delim[] = " ,-:";
    char *str = new char[t.size()+1];
    strcpy(str, t.c_str());
    char *token = strtok(str, delim);
//    std::cout<<"year token "<<token<<std::endl;
    time.year = std::stoi(std::string(token));
    token = strtok(NULL, delim);
//    std::cout<<"month token "<<token<<std::endl;
    time.month = std::stoi(std::string(token));
    token = strtok(NULL, delim);
//    std::cout<<"date token "<<token<<std::endl;
    time.date = std::stoi(std::string(token));
    token = strtok(NULL, delim);
//    std::cout<<"hour token "<<token<<std::endl;
    time.hour = std::stoi(std::string(token));
    token = strtok(NULL, delim);
//    std::cout<<"minute token "<<token<<std::endl;
    time.minute = std::stoi(std::string(token));
    token = strtok(NULL, ".");
//    std::cout<<"second token "<<token<<std::endl;
    time.second = std::stoi(std::string(token));
    token = strtok(NULL, delim);
//    std::cout<<"microsecond token "<<token<<std::endl;
    time.micros = std::stoi(std::string(token));
    token = strtok(NULL, delim);
    ticker = std::string(token);
    token = strtok(NULL, delim);
    price = std::stof(std::string(token));
    token = strtok(NULL, delim);
    size = std::stof(std::string(token));
    token = strtok(NULL, delim);
    exchange = std::string(token);

    delete[] str;
}

int stock_data::get_diff(const stock_data& d){
    Time d_time = d.get_time();
    assert(time.year == d_time.year &&
        time.month == d_time.month &&
        time.date == d_time.date);
    int hour_diff = time.hour - d_time.hour;
    int minute_diff = time.minute - d_time.minute;
    int second_diff = time.second - d_time.second;
    int micros_diff = time.micros - d_time.micros;

    int total_diff = hour_diff * 60 * 60 * 1e6 + minute_diff * 60 * 1e6 + second_diff * 1e6 + micros_diff;

    return total_diff;
}

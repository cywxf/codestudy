#include <iostream>
#include <fstream>
#include <vector>
#include "StockData.h"

std::vector<stock_data*> get_from_file(std::string filename, std::string exchangename); //declaration

int main(int argc, char *argv[]){
    if ( argc != 2 ) // argc should be 2 for correct execution
    // We print argv[0] assuming it is the program name
        std::cout<<"usage: "<< argv[0] <<" <filename>\n";
    else {
        std::vector<stock_data*> stockA = get_from_file(argv[1],"A");
        std::vector<stock_data*> stockB = get_from_file(argv[1],"B");
    }
    return 0;
}


std::vector<stock_data*> get_from_file(std::string filename, std::string exchangename){ //read into a vector
    std::vector<stock_data*> stock_stream={};
    std::ifstream input( filename );
    if(input.is_open()){
        std::string line;
        getline( input, line); //skip first line
        for( line; getline( input, line ); ){
            stock_data *tick_data = new stock_data(line);
            if(tick_data->get_exchange() == exchangename)
                stock_stream.push_back(tick_data);
        }
    }
    else
        std::cout << "Could not open "<< filename << std::endl;
    input.close();
    return stock_stream;
}

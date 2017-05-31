#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

/* Function "timeLag_map_calculation" takes three arguments, a vector: "timeA" for storing the trading times[just the microseconds part] in Exchange A that are related to time lag;a vector: "timeB" for storing the trading times  in Exchange B that are related to time lag; A hash map, "count_of_timeLag" with (key: the possible lag time, value: the frequency that the lag time appears). This function is used to calculate possible lag time and its frequency. The lag time that corresponds to the largest frequency is the actual lag time between Exchange A and B.*/
void timeLag_map_calculation(vector<int> & timeA, vector<int> & timeB, unordered_map<int,int> & count_of_timeLag){
	if(timeA.empty() || timeB.empty()) return;
	unordered_map<int,int>::iterator it_map; 
	int time_lag;
	for(int i = 0; i< timeA.size(); i++) //iterate through trading times in Exchange A
		for(int j = 0; j < timeB.size(); j++){//iterate through trading times in Exchange B
			time_lag = timeA[i] - timeB[j];
			if(time_lag == 0 || abs(time_lag)>100) continue;
			//cout << time_lag << endl;
			it_map = count_of_timeLag.find(time_lag);
			if(it_map == count_of_timeLag.end()) count_of_timeLag.insert({time_lag,1}); //build the count_of_timeLog hash map (key: lag time --> value: frequency)
			else {count_of_timeLag[time_lag]++;} //cout << count_of_timeLag[time_lag] << endl;}
	}	
	return;
}

/* This function takes only one argument "count_of_timeLag", which is the same as above with (key,value) pairs as (lag time, frequency). This function is used to calculate the actual lag time between Exchange A and B, which corresponds to the highest frequency. The  (lag time, frequency) will be also printed out on screen.*/
int timeLag_calculation(unordered_map<int,int> & count_of_timeLag){
	unordered_map<int,int> tmp_map;
	vector<int> tmp_count;
	cout << "Time lag," << "Frequency" << endl;
	for(unordered_map<int,int>::iterator it_map = count_of_timeLag.begin(); it_map != count_of_timeLag.end(); it_map++){ //create a new hash map with (key: freqeuncy, value: lag time)
		tmp_map.insert({it_map->second,it_map->first});
		tmp_count.push_back(it_map->second);
		cout << it_map->first << ", " << it_map->second << endl;
	}

	int max_ele = *max_element(tmp_count.begin(), tmp_count.end()); //find the largest frequency
	//cout << max_ele;
	return tmp_map[max_ele]; // Return the actual lag time
}

/* Main function: It takes zero argument, since I put the input file name inside the main function manully. The main function parses the data created by the python script, and solve the lag time between Exchange A and B*/
int main() {
	string record;
	ifstream trading_input ("input_20170418.txt"); //read the data consisting of Exchange A and B

	vector<string> tmp_record;
	string token;

	string hm_previous = " ", hm;// The notation "previous" is used to denote the previous features, such as trading time(hour-minute-second part-"hm" and the microsecond part - "sec"), trading stock price-"price", Exchange label A/B-"exch_label"
	int sec_A_previous = 0, sec_B_previous = 0, sec_A, sec_B; 
	double price_previous = 0, price;
	string exch_label_previous = "A", exch_label;

	vector<int> timeA,timeB; //vector to store the trading times that are related to time lag in Exchange A/B
	vector<int>::iterator it1, it2; 
	unordered_map<int,int> count_of_timeLag; //hash map with (key: possible lag time, value: frequency)	
	
	if (trading_input.is_open()){
		getline(trading_input,record); //avoid the title line
		while(getline (trading_input,record)){ // extract and parse each trading "record"
			istringstream ss(record);
			
			tmp_record.erase(tmp_record.begin(),tmp_record.end());

			while(getline(ss,token,',')){ // get each item in a record seperately: time, price and Exchange label
				tmp_record.push_back(token);}
			
			hm = tmp_record[0].substr(0,19); // hour+min+sec
			price = stod(tmp_record[2]); //price
			exch_label = tmp_record[4];//Exchange label, A or B
			if(exch_label == "A") sec_A = stod(tmp_record[0].substr(20,6)); // microsecond
			else sec_B = stod(tmp_record[0].substr(20,6)); // microsecond

			if(price == price_previous && hm == hm_previous ){ // Only records with the same price and witnin a time window are compared. This part is used to find out possible tradings in Exchange A and B that could reflect the time lag between Exchange A and B
							
				if(exch_label == "A" && abs(sec_A -sec_A_previous) < 20) { //put the useful time (microseconds part) in Exchange A to a vector 
					it1 = find(timeA.begin(),timeA.end(),sec_A_previous);
					if(it1 == timeA.end()) timeA.push_back(sec_A_previous); 
					it2 = find(timeA.begin(),timeA.end(),sec_A);
					if(it2 == timeA.end()) timeA.push_back(sec_A); }
				if(exch_label == "B" && abs(sec_B -sec_B_previous) < 20) {//put the useful time (microseconds part) in Exchange B to a vector 
					it1 = find(timeB.begin(),timeB.end(),sec_B_previous);
					if(it1 == timeB.end()) timeB.push_back(sec_B_previous); 
					it2 = find(timeB.begin(),timeB.end(),sec_B);
					if(it2 == timeB.end()) timeB.push_back(sec_B); }
				
			}
			
			else {
				timeLag_map_calculation(timeA, timeB, count_of_timeLag); //calculate the frequency of possible time lags. The largest frequency corresponds to the actual lag time
				timeA.erase(timeA.begin(),timeA.end()); //clear the timeA and timeB
				timeB.erase(timeB.begin(),timeB.end());
			}

			hm_previous = hm; //update the time, price and Exchange label
			sec_B_previous = sec_B;
			sec_A_previous = sec_A;
			price_previous = price;
			exch_label_previous = exch_label;
		
			
		}
		trading_input.close();
	}
	else cout << "Fail to open trading input! Please double check your input file";
	
	int timeLag = timeLag_calculation(count_of_timeLag); //Call function "timeLag_calculation" to calculate the actual lag time and assign it to "timeLag" variable
	if(timeLag < 0) cout <<"Estimation - B Exchange is " << abs(timeLag) << " microseconds slower than A Exchange on 20170418" << endl; //print the lag time between Exchange A and B
	else cout << "Estimation - B Exchange is " << abs(timeLag) << " microseconds faster than A Exchange on 20170418" << endl;

	return 1;
}

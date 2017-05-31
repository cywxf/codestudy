#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <math.h>
#include <limits.h>
using namespace std;

/* a class to represent time, which consists of second and microsecond */
class TIME {
public:
	long second;
	long microsecond;
	TIME() : second(0), microsecond(0) { }
	TIME(long sec, long ms) : second(sec), microsecond(ms) { }
	bool operator<(TIME& t) {
		if (this->second < t.second) return true;
		else if (this->second == t.second && this->microsecond < t.microsecond) return true;
		else return false;
	}
};

/* a struct to store time, price and volume of each trade */
struct trade {
	TIME t;
	double price;
	int volume;
};

/* utility function for debugging */
void print_trade(trade& obj) {
	cout << "time: " << obj.t.second << " " << obj.t.microsecond << endl;
	cout << "price: " << obj.price << endl;
	cout << "volume: " << obj.volume << endl;
}

/* convert a raw time format to a class time format */
/* starting time 09:30:00:000000 is equivalent to second = 0, microsecond = 0 */
void convert_time(string& str, TIME& ti) {
	ti.second = 0, ti.microsecond = 0;
	istringstream ss(str);
	string item;
	getline(ss, item, ':');
	ti.second += (stol(item) - 9) * 3600 -1800;
	getline(ss, item, ':');
	ti.second += stol(item) * 60;
	getline(ss, item, ':');
	ti.second += stol(item.substr(0, 2));
	ti.microsecond = stol(item.substr(3));
}

/* obtain next available trad information of exchange c (A or B) */
bool get_trade(trade& obj, ifstream& ifs, bool& is_A) {
	string line, item;
	if (getline(ifs, line))
	{
		if (line.back() == 'A') is_A = true;
		else is_A = false;
		line.erase(line.begin(), line.begin() + 11);
		istringstream ss(line);
		getline(ss, item, ',');
		convert_time(item, obj.t);
		getline(ss, item, ',');
		getline(ss, item, ',');
		obj.price = stod(item);
		getline(ss, item, ',');
		obj.volume = stoi(item);
		return true;
	}
	return false;
}

/* read data from input and split into two groups w.r.t Exchange */
void read_data(string filename, vector<trade>& data_A, vector<trade>& data_B) {
	ifstream file(filename);
	string str;
	/* skip the first line of column names */
	getline(file, str);
	trade obj;
	bool is_A = true, status = false;
	do
	{
		status = get_trade(obj, file, is_A);
		if (status && is_A)
			data_A.push_back(obj);
		else if (status)
			data_B.push_back(obj);
	} while (status);
}

/* check if trade A and trade B can be considered as matched due to time lag */
/* three requirements: time difference is less than 100 ms; price matches; volume matches */
bool match_pair(trade& obj_1, trade& obj_2, int& lag) {
	static double tol = 1.0e-10;
	long sec_diff = obj_2.t.second - obj_1.t.second;
	long ms_diff = obj_2.t.microsecond - obj_1.t.microsecond;
	if (abs(sec_diff) > 1) return false;
	long diff = sec_diff * 1000000 + ms_diff;
	if (abs(diff) >= 100) return false;
	lag = (int)diff;
	if (fabs(obj_2.price - obj_1.price) < tol && obj_2.volume == obj_1.volume)
		return true;
	return false;
}

/* find the key with maximum value of a hashtable */
int max_value_of_hash(unordered_map<int, int>& hash) {
	int out = INT_MIN, count = 0;
	for (auto it : hash)
	{
		if (it.second > count)
		{
			out = it.first;
			count = it.second;
		}
	}
	return out;
}

/* major function to find the time lag between two exchanges */
int FindTimeLag(string date) {
	string filename = date + "_" + "data.txt";
	vector<trade> data_A, data_B;
	read_data(filename, data_A, data_B);
	unordered_map<int, int> lag_count;
	int i = 0, j = 0;
	while (i < (int)data_A.size() && j < (int)data_B.size())
	{
		int lag = 0;
		/* matched pair: record the candidate time lag in the hash table */
		/* check data_A[i] with the following data_B trades; check data_B[j] with the following data_A trades */
		if (match_pair(data_A[i], data_B[j], lag))
		{
			lag_count[lag]++;
			int ii = i + 1, jj = j + 1;
			while (ii < (int)data_A.size() && match_pair(data_A[ii], data_B[j], lag))
			{
				lag_count[lag]++; ++ii;
			}
			while (jj < (int)data_B.size() && match_pair(data_A[i], data_B[jj], lag))
			{
				lag_count[lag]++; ++jj;
			}
			++i; ++j;
		}
		/* A moves forward if data_A[i] is earlier */
		else if (data_A[i].t < data_B[j].t) ++i;
		/* B moves forward if data_B[j] is earlier */
		else ++j;
	}
	return max_value_of_hash(lag_count); /* return the candidate time lag that occurs most frequently */
}

/* main function */
int main(int argc, char *argv[])
{
	string date = argv[1];
	int lag = FindTimeLag(date);
	cout << "Estimation - B Exchange is " << lag << " microseconds slower than A Exchange on " << date << endl;
	return 0;
}

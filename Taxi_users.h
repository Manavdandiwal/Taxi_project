#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <vector>
#include <conio.h>
#include <Windows.h>
using namespace std;

constexpr auto TAXI_FARE = 500;

class Taxi_users
{
private:
	string NAME;
	string PHONE_NUMBER;
	string ACCOUNT_NUMBER;
	time_t START_TIME;
	char bank_account;

public:
	void new_user();
	bool set_values(ifstream& taxi_data);
	bool payment();
	void write_data(ofstream& file);
	bool check_user(string name, string phone_number);
	time_t get_initial_time() { return this->START_TIME; }
};
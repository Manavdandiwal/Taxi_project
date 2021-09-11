#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <vector>
#include <conio.h>
#include <Windows.h>
using namespace std;

class Bank_user_info
{
private:
	string NAME;
	string PHONE_NUMBER;
	string ACCOUNT_NUMBER;
	int BALANCE;
	string account_number_generator();

public:
	Bank_user_info() { BALANCE = 0; }
	void new_account(string name = "", string phone_number = "");
	void deposit(int amount);
	bool withdraw(int amount);
	bool check_user_bank(string name, string phone_number, string account);
	bool read_data(ifstream& data_file);
	void write_data(ofstream& data_file);
	string get_account_no() { return this->ACCOUNT_NUMBER; }
};
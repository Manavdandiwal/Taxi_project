#pragma once

#include "Taxi_users.h"
#include "Bank_user_info.h"

extern vector<Taxi_users> taxi_user_info;
extern vector<Bank_user_info> bank_user_data;

void menu()
{
	cout << "\t\t---------------------------------------" << endl;
	cout << "\t\t       Welcome to the TAXI STAND       " << endl;
	cout << "\t\t---------------------------------------" << endl;
	cout << endl;

	cout << "\tEnter the choice from below : " << endl;;

	cout << "  1 : Book a Taxi" << endl;
	cout << "  2 : Cancel your booking" << endl;
	cout << "  3 : End your ride" << endl;
	cout << "  4 : Exit" << endl;
}

int get_choice()
{
	int choice;
	cout << endl;
	cout << " Choice : ";
	cin >> choice;
	return choice;
}

void book_taxi()
{
	Taxi_users tmp;
	tmp.new_user();
	taxi_user_info.push_back(tmp);
}

void get_input(string& name, string& phone)
{
	cout << "  Enter following details : " << endl;
	cin.ignore();
	cout << "  Name : ";
	getline(cin, name);
	cout << "  Registered Phone Number : ";
	cin >> phone;
}

void return_to_main_menu()
{
	cout << " Press any key to return to the main menu " << endl;
	if (_getch())
		return;
}

void cancel_booking()
{
	string req_name, req_phone;
	get_input(req_name, req_phone);

	int pos = 0;
	for (auto i : taxi_user_info)
	{
		if (i.check_user(req_name, req_phone))
		{
			int curr_time = time(0);
			if (curr_time < i.get_initial_time())
			{
				taxi_user_info.erase(taxi_user_info.begin() + pos);
				cout << " Booking Canceled Successfully" << endl;
				return;
			}		
		}
		pos++;
	}
	cout << " User not found" << endl;
	return;
}

void end_ride()
{
	string req_name, req_phone;
	get_input(req_name, req_phone);

	int pos = 0;
	for (auto i : taxi_user_info)
	{
		if (i.check_user(req_name, req_phone))
		{
			if (i.payment())
			{
				taxi_user_info.erase(taxi_user_info.begin() + pos);
				cout << " Payment Successful" << endl;
				return;
			}
		}
		pos++;
	}
	cout << " User Not Found" << endl;
	return;
}

void get_bank_data()
{
	Bank_user_info tmp;
	ifstream bank_data("BANK_DATA.txt");
	char ch;
	while (bank_data >> ch && tmp.read_data(bank_data))
	{
		bank_user_data.push_back(tmp);
	}
	bank_data.close();
}

void get_taxi_data()
{
	Taxi_users tmp;
	ifstream taxi_data("TAXI_DATA.txt");

	char ch;
	while (taxi_data >> ch && tmp.set_values(taxi_data))
	{
		taxi_user_info.push_back(tmp);
	}
	taxi_data.close();
}

void write_taxi_data()
{
	ofstream taxi_data("TAXI_DATA.txt");
	taxi_data.clear();
	for (auto i : taxi_user_info)
	{
		i.write_data(taxi_data);
	}
	taxi_data.close();
}

void write_bank_data()
{
	ofstream bank_data("BANK_DATA.txt");
	bank_data.clear();

	for (auto i : bank_user_data)
	{
		i.write_data(bank_data);
	}
	bank_data.close();
}
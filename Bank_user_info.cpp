#include "Bank_user_info.h"

vector<Bank_user_info> bank_user_data;
string Bank_user_info::account_number_generator()
{
	/// <summary>
	/// generates random string of numbers that will be the account number for the new user
	/// </summary>
	/// <returns>Account number for new user</returns>
	time_t curr = time(NULL);
	srand(curr);
	string acc = "";
	int tmp = rand() % 10;
	if (tmp)
		acc += tmp + '0';

	for (int i = 0; i < 14; i++)
		acc += rand() % 10 + '0';

	return string(acc);
}

void Bank_user_info::new_account(string name, string phone_number)
{
	/// <summary>
	/// setting the name and phone number to that of the user and genarating an account number for him.
	/// also prompting him to make the initial deposit to his own choice.
	/// </summary>
	/// <param name="name"></param>
	/// <param name="phone_number"></param>
	if (name.length() == 0)
	{
		cout << " Enter your Name : ";
		getline(cin, NAME);
		cout << " Phone Number : ";
		cin >> PHONE_NUMBER;
	}

	else
	{
		NAME = name;
		PHONE_NUMBER = phone_number;
	}
	ACCOUNT_NUMBER = account_number_generator();
	cout << " Account number alloted to you is : " << ACCOUNT_NUMBER << endl;

	cout << " Enter the initial deposit you would like to make : ";
	int amount;
	cin >> amount;
	deposit(amount);
}

void Bank_user_info::deposit(int amount)
{
	/// <summary>
	/// deposit function
	/// </summary>
	/// <param name="amount">amount to be deposited</param>
	BALANCE += amount;
	return;
}

bool Bank_user_info::withdraw(int amount)
{
	/// <summary>
	/// withdraw function
	/// </summary>
	/// <param name="amount">amount to be withdrawn</param>
	/// <returns>withdrawn status</returns>
	if (BALANCE < amount)
		return false;

	else
	{
		BALANCE -= amount;
		cout << " Withdrawn successfully" << endl;
		return true;
	}
}

bool Bank_user_info::check_user_bank(string name, string phone_number, string account)
{
	/// <summary>
	/// check if the user is the required user
	/// </summary>
	/// <param name="name"></param>
	/// <param name="phone_number"></param>
	/// <param name="account"></param>
	/// <returns>tells the program if this user is the required one</returns>
	if (NAME == name && PHONE_NUMBER == phone_number && ACCOUNT_NUMBER == account)
		return true;

	return false;
}

bool Bank_user_info::read_data(ifstream& data_file)
{
	/// <summary>
	/// read the data from txt file
	/// </summary>
	/// <param name="data_file">reference to the file from which data will be read</param>
	/// <returns>return true if it reads data successfully</returns>
	data_file >> NAME >> PHONE_NUMBER >> ACCOUNT_NUMBER >> BALANCE;
	return true;
}

void Bank_user_info::write_data(ofstream& data_file)
{
	data_file << "a" << endl
		<< NAME << endl
		<< PHONE_NUMBER << endl
		<< ACCOUNT_NUMBER << endl
		<< BALANCE << endl;
}
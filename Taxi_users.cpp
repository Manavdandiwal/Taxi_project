#include "Taxi_users.h"
#include "Bank_user_info.h"

extern vector<Bank_user_info> bank_user_data;
vector<Taxi_users> taxi_user_info;

void Taxi_users::new_user()
{
	/// <summary>
	/// this allows the new user to book a taxi for the same day.
	/// this function also allows user to create a new bank account if he doesn't have one already.
	/// </summary>
	cout << " Please Enter the following details : " << endl;
	cin.ignore();
	cout << " Name : ";
	getline(cin, NAME);
	cout << " Phone Number : ";
	cin >> PHONE_NUMBER;
	cout << " Do you have a bank account (y / n) : ";
	cin >> bank_account;

	if (bank_account == 'y' || bank_account == 'Y')
	{
		cout << " Enter Bank Account : ";
		cin >> ACCOUNT_NUMBER;
	}

	else
	{
		ACCOUNT_NUMBER = "0";
		cout << " Would you like to create a new bank account (y / n) : ";
		cin >> bank_account;

		if (bank_account == 'y' || bank_account == 'Y')
		{
			Bank_user_info tmp;
			tmp.new_account(NAME, PHONE_NUMBER);
			ACCOUNT_NUMBER = tmp.get_account_no();
			bank_user_data.push_back(tmp);
		}
	}
	time_t curr = time(NULL);
	tm start;
	localtime_s(&start, &curr);

wrong_time:
	cout << " Enter the time when you would want the ride (hh mm)(24 hrs system) : ";
	cin >> start.tm_hour >> start.tm_min;

	START_TIME = mktime(&start);

	if (START_TIME < curr)
	{
		cout << " Invalid time input" << endl;
		goto wrong_time;
	}

	cout << " Taxi has been successfully booked" << endl;
}

bool Taxi_users::set_values(ifstream &taxi_data)
{
	getline(taxi_data, NAME);
	taxi_data >> PHONE_NUMBER >> ACCOUNT_NUMBER >> START_TIME >> bank_account;
	return true;
}

bool Taxi_users::payment()
{
	/// <summary>
	/// this function allows user to pay the bill providing two different methods.
	/// </summary>
	/// <returns> status of the payment is returned </returns>
	time_t curr = time(NULL);
	if (curr < START_TIME)
	{
		cout << "Ride not started yet." << endl;
		return false;
	}
	int billing_amount = (time(NULL) - START_TIME);
	billing_amount = ((billing_amount / 3600.0 + billing_amount % 3600) / 60.0) * TAXI_FARE / 60.0;

	cout << " Billing Amount : " << billing_amount << endl;
	if (billing_amount <= 0)
		return true;

	int amount_paid;
	if (bank_account == 'y' || bank_account =='Y')
	{
	invalid_choice:
		system("cls");
		cout << " Billing amount will be : " << billing_amount << endl;
		cout << " Choose the billing option : " << endl;

		cout << " Enter 1 for cash payment : " << endl;
		cout << " Enter 2 for bank payment : " << endl;

		int choice;
		cin >> choice;
	insuff_bal:

		switch (choice)
		{
		case 1:
			cout << " Payment using Cash" << endl;
			cout << " Amount paid by the user : ";
			cin >> amount_paid;
			cout << " Change : " << amount_paid - billing_amount << endl;
			return true;

		case 2:
			for (auto& i : bank_user_data)
			{
				if (i.check_user_bank(NAME, PHONE_NUMBER, ACCOUNT_NUMBER))
				{
					if (i.withdraw(billing_amount))
							return true;

					else
					{
						choice = 1;
						goto insuff_bal;
					}
				}
			}
			return false;
		default:
			cout << " Inavlid option" << endl;
			goto invalid_choice;
		}
	}

	else
	{
		cout << " Payment using Cash" << endl;
		cout << " Amount paid by the user : ";
		cin >> amount_paid;
		cout << " Change : " << amount_paid - billing_amount << endl;
	}
	return true;
}

bool Taxi_users::check_user(string name, string phone_number)
{
	/// <summary>
	/// check if this user is the one we are searching for through the file
	/// </summary>
	/// <param name="name">name of the required user</param>
	/// <param name="phone_number">phone number of the required user</param>
	/// <returns>tells us if this is the required user</returns>
	if (NAME == name && PHONE_NUMBER == phone_number)
		return true;

	return false;
}

void Taxi_users::write_data(ofstream& file)
{
	/// <summary>
	/// will write all the information into the txt file
	/// </summary>
	/// <param name="file">the file in which data is to be written</param>
	file << "a" << NAME << endl
		<< PHONE_NUMBER << endl
		<< START_TIME << endl
		<< ACCOUNT_NUMBER << endl
		<< bank_account << endl;
}
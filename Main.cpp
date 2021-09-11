#include "Main_functions.h"

int main()
{
	get_bank_data();
	get_taxi_data();
	return_to_menu:
	system("cls");
	menu();
	switch (get_choice())
	{
	case 1:
		cout << endl;
		book_taxi();
		return_to_main_menu();
		goto return_to_menu;

	case 2:
		cout << endl;
		cancel_booking();
		return_to_main_menu();
		goto return_to_menu;

	case 3:
		cout << endl;
		end_ride();
		return_to_main_menu();
		goto return_to_menu;

	case 4:
		cout << endl;
		write_taxi_data();
		write_bank_data();
		cout << "  Thank you for using our services." << endl;
		exit(0);
	}
	return 0;
}
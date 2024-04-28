#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <chrono>
#include <fstream>

using namespace std;
//using namespace std::chrono;

//---------------------- Structs ----------------------//
struct Train
{								// to write the information of train
	int ID;
	string name;
	int number;
	bool availability;
	string time;
}train[10];

struct User
{								// to write the information of user
	int ID;
	string Name;
	string Phone;
	int Age;
	string Email;
	string Address;
	char Role;
	char gender;
};

struct Ticket
{								// to write the information of ticket
	int ID;
	string Start_location;
	string Destination_location;
	double Price;
};

struct Card		// Payment card info
{
	long long card_number;
	int cvv;
	int exp_month;
	int exp_year;
};

//---------------------- Global Variables ----------------------//
int current_month = 5;
int current_year = 24;
//time_t my_time = time(nullptr);
//cout << ctime(&my_time);


//---------------------- Functions ----------------------//

// Gets the number of digits from an int or long long //
int get_digits(long long n)
{
	int length = 0;
	do
	{
		n /= 10;
		length++;
	} while (n != 0);

	return length;
}


bool make_payment()
{
	Card visa;
	int cvv_digits;

	cout << "Payment card details:" << endl;	// entering payment card details //
	while (true)
	{
		cout << "Card number: ";
		cin >> visa.card_number;

		if (get_digits(visa.card_number) != 16)		// checking if card number = 16 digits or not //
		{
			cout << "card number invalid!" << endl;
		}
		else
		{
			break;
		}
	}

	while (true)
	{
		cout << "CVV: ";
		cin >> visa.cvv;
		cvv_digits = get_digits(visa.cvv);

		if (cvv_digits == 3 || cvv_digits == 4)		// checking if CVV is 3 or 4 digits //
		{
			break;
		}
		else
		{
			cout << "CVV invalid" << endl;
		}
	}

	while (true)
	{
		cout << "Expiration date:" << endl << "month: ";
		cin >> visa.exp_month;
		cout << "year: ";
		cin >> visa.exp_year;

		if (visa.exp_year > current_year)	 // checking card's exp date //
			break;
		else if (visa.exp_year == current_year)
		{
			if (visa.exp_month > current_month)
				break;
			else
				cout << "Card has already expired" << endl;
		}
		else
			cout << "Card has already expired" << endl;
	}
	return true;
}

int manage_payment(int start, int dest, int seats)
{

}

void book_tickets()
{
	Ticket ticket;
	int key = 0, seats = 0;

	cout << left;
	cout << setw(15);
	cout << "Locaitons" << endl;
	cout << "-----------------------";
	cout << "1>> Cario" << endl;
	cout << "2>> Alex" << endl;
	cout << "3>> Assiut" << endl;
	cout << "4>> Aswan" << endl;
	cout << "5>> Luxor" << endl;
	cout << "----------------------------------------------" << endl;

	cout << "Press a number for start location:" << endl;		// Taking start location from user
	cout << "-->";
	cin >> key;
	switch (key)
	{
	case 1:
		ticket.Start_location = "Cario";
		break;
	case 2:
		ticket.Start_location = "Alex";
		break;
	case 3:
		ticket.Start_location = "Assiut";
		break;
	case 4:
		ticket.Start_location = "Aswan";
		break;
	case 5:
		ticket.Start_location = "Luxor";
	}

	cout << "Press a number for destination location:" << endl;		// Taking destination location from user
	cout << "-->";
	cin >> key;
	switch (key)
	{
	case 1:
		ticket.Destination_location = "Cario";
		break;
	case 2:
		ticket.Destination_location = "Alex";
		break;
	case 3:
		ticket.Destination_location = "Assiut";
		break;
	case 4:
		ticket.Destination_location = "Aswan";
		break;
	case 5:
		ticket.Destination_location = "Luxor";
	}

	cout << "Enter number of seats:" << endl;
	cout << "-->";
	cin >> seats;

	ticket.Price = manage_payment(ticket.Start_location, ticket.Destination_location, seats);

}

void display_train()
{

}


int main()
{
	//---------------------- Trains ---------------------- //
	train[0] = { 0, "Cairo Mirage", 101, true };


}
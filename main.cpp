#include<iostream>
#include<string>
#include<vector>
#include <random>
#include<fstream>
#include <conio.h>
#include <windows.h>
#include <iomanip>

using namespace std;


//---------------------- Global Variables ----------------------//
int current_month = 5;
int current_year = 24;
fstream prices;     // "ticketsPrices.txt" stores tickets prices

//---------------------- Structs ----------------------//
struct Train { // to write the information of train
    string ID;
    string name;
    int number;
    bool availability;
}train;

struct Ticket {   // to write the information of ticket
    int ID;
    string Start_location;
    string Destination_location;
    int Price;
};
vector<Ticket> Tickets;

struct User {  // to write the information of user
    string ID;
    string Name;
    string Phone;
    int Age;
    string Email;
    string Address;
    string Role;        // Passenger or Admin
    string gender;
    vector<Ticket>booked_tickets; // to store all the booked ticketsfor the user and store it in the user report.
}user;
vector<User> user_reports; // to store all data about the user including tickets booked and all action he does in the program.



struct Card		// Payment card info
{
    long long card_number;
    int cvv;
    int exp_month;
    int exp_year;
    bool is_available;
}visa;

struct Fawry
{
    bool is_available;
}fawry;

struct Cash
{
    bool is_available;
}cash;



//---------------------- Functions ----------------------//

int get_digits(long long n)     // Gets number of digits from an integer or long long
{
    int length = 0;
    do
    {
        n /= 10;
        length++;
    } while (n != 0);

    return length;
}

bool is_valid()     // Checks if user's visa valid or not
{
    // Creating payment method for the user to pay 
    int cvv_digits;
    fstream tktprices;

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
            cout << "\n";
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
            cout << "\n";
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
        {
            cout << "---------------------------------------------\n";
            break;
        }
        else if (visa.exp_year == current_year)
        {
            if (visa.exp_month > current_month)
            {
                cout << "---------------------------------------------\n";
                break;
            }
            else
                cout << "Card has already expired" << endl;
        }
        else
            cout << "Card has already expired" << endl;
    }
    return true;
}

void signup()
{

}

void manage_train_schedule() {
    while (true)
    {
        system("cls");  // Clears terminal's screen

        // Reading variables
        ofstream add;   // fstream for adding treians
        ifstream display;   // fstream for displaying trains

        cout << "__________________________________     Train Schedule     __________________________________\n\n";
        cout << "\t\t[1] Add train" << endl;
        cout << "\t\t[2] View schedule of existing trains" << endl;
        cout << "\t\t[3] Modify train" << endl;
        cout << "\t\t[4] Delete train" << endl;
        cout << "\t\t[5] Back to dashboard\n\n";
        cout << "____________________________________________________________________________________________\n\n\n";
        cout << "\t\t\t";

        char choice;
        choice = _getch();

        if (choice == '1')
        {   // Add train
            system("cls");
            cout << "\t\tEnter train ID: ";
            cin >> train.ID;

            cout << "\t\tEnter train number: ";
            cin >> train.number;

            cout << "\t\tEnter train name: ";
            cin.ignore();
            getline(cin, train.name);

            cout << "\t\tEnter train availability: ";
            cin >> train.availability;

            // Storing the new train in file
            add.open("train_schedule.txt", ios::app);
            if (add.is_open())
            {
                add << endl << "train ID: " << train.ID;
                add << endl << "train number: " << train.number;
                add << endl << "train name: " << train.name;
                add << endl << "train availability: " << train.availability;
                add << endl << "______________________________";
                add.close();
                cout << "\t\t" << "Train added successfully" << endl;
            }
            else
            {
                cout << "\t\tError reading from file!\n\n";
            }
            add.close();
            cout << "\t\tPress any key to continue\n";
            cout << "\t\t\t";
            _getch();
        }
        else if (choice == '2')
        {   // View train schedule
            system("cls");

            string line;
            display.open("train_schedule.txt", ios::in);

            if (display.is_open())
            {
                while (getline(display, line)) {
                    cout << "\t\t" << line << endl;
                }
            }
            else
            {
                cout << "\t\tError reading trians data\n";
            }
            display.close();
            cout << "\t\tPress any key to continue\n";
            cout << "\t\t\t";
            _getch();
        }
        else if (choice == '3')
        {   // Modify train
            system("cls");

            cout << "\t\tEnter train ID to modify:\n";
            cout << "\t\t\t";
            cin >> train.ID;
            cin.ignore();

            // Reading variables
            ofstream temp;  // To add the new data
            string line;
            bool exist = false;

            display.open("train_schedule.txt");

            // Checks the train exists or not
            if (display.is_open())
            {
                while (getline(display, line))
                {
                    if (line == "train ID: " + train.ID)
                    {
                        exist = true;
                        break;
                    }
                }
                if (!exist)
                {
                    display.close();
                    cout << "\t\tTrain does not exist!\n";
                    cout << "\t\tPress any key to continue\n";
                    cout << "\t\t\t";
                    _getch();
                    continue;
                }
                display.close();
            }
            else
            {
                cout << "\t\tError reading trains data from file!\n";
                cout << "\t\tPress any key to continue\n";
                cout << "\t\t\t";
                _getch();
            }

            // Getting new train's data
            cout << "\t\tEnter new Train name: ";
            getline(cin, train.name);

            cout << "\t\tEnter new Train number: ";
            cin >> train.number;

            cout << "\t\tEnter Trian's availability: ";
            cin >> train.availability;
            cin.ignore();


            // Opening display file to copy from and paste in temp file
            display.open("train_schedule.txt");
            temp.open("new_train_schedule.txt");

            if (display.is_open() && temp.is_open())
            {
                while (getline(display, line))
                {
                    if (line == "train ID: " + train.ID)
                    {   // Skipping the existing train's details to replace them with the modified ones
                        for (int i = 0; i < 4; i++)
                        {
                            getline(display, line);
                        }
                        // Writing the data of the modified train
                        temp << "train ID: " << train.ID;
                        temp << endl << "train number: " << train.number;
                        temp << endl << "train name: " << train.name;
                        temp << endl << "train availability: " << train.availability;
                        temp << endl << "______________________________";
                    }
                    else
                    {
                        temp << line << endl;
                    }
                }
                display.close();
                temp.close();

                remove("train_schedule.txt");
                rename("new_train_schedule.txt", "train_schedule.txt");
            }
            else
            {
                cout << "\t\tError reading trains data from file!\n";
                cout << "\t\tPress any key to continue\n";
                cout << "\t\t\t";
                _getch();
            }
        }
        else if (choice == '4')
        {   // Delete train
            system("cls");

            cout << "\t\tEnter train ID to delete:\n";
            cout << "\t\t\t";
            cin >> train.ID;
            cin.ignore();

            // Reading variables
            ofstream temp;  // To add the new data
            string line;
            bool exist = false;

            display.open("train_schedule.txt");

            if (display.is_open())
            {
                // Checks the train exists or not
                while (getline(display, line))
                {
                    if (line == "train ID: " + train.ID)
                    {
                        exist = true;
                    }
                }

                if (!exist)
                {
                    display.close();
                    cout << "\t\tTrain does not exist!\n";
                    cout << "\t\tPress any key to continue\n";
                    cout << "\t\t\t";
                    _getch();
                    continue;
                }
                else    // The train exists, so it will be deleted
                {
                    // Resetting the stream pointer to start reading from the beggining of the file
                    display.clear();
                    display.seekg(0, ios::beg);

                    temp.open("new_train_schedule.txt");

                    // Reading trains' data
                    while (getline(display, line))
                    {
                        if (line == "train ID: " + train.ID)
                        {
                            // Skipping the existing train's data (to delete it)
                            for (int i = 0; i < 4; i++)
                            {
                                getline(display, line);
                            }
                        }
                        else
                        {
                            // Write the data of the rest trains
                            temp << line << endl;
                        }
                    }
                    display.close();
                    temp.close();

                    remove("train_schedule.txt");
                    rename("new_train_schedule.txt", "train_schedule.txt");
                }
                display.close();
            }
            else
            {
                cout << "\t\tError reading trains data from file!\n";
                cout << "\t\tPress any key to continue\n";
                cout << "\t\t\t";
                _getch();
            }


        }
        else if (choice == '5')
        {   // Back to dashboard
            break;
        }
    }
}

void manage_user_accounts()
{
    while (true)
    {
        system("cls");

        // Reading variables
        fstream users_data; // For reading data
        ofstream temp;      // For writing new data
        string id, role, password, line;
        bool exist = false;

        cout << "\t\t\t____________________________________________________________________________________________\n\n\n";
        cout << "\t\t\t_______________________________     Manage user accounts     _______________________________\n\n\n";
        cout << "\t\t\t[1] Add a new account\n";
        cout << "\t\t\t[2] Modify an existing account\n";
        cout << "\t\t\t[3] Delete an account\n\n";
        cout << "\t\t\t[4] Go back to dashboard\n\n";
        cout << "\t\t\t____________________________________________________________________________________________\n\n\n";
        cout << "\t\t\t\t";

        char choice;
        choice = _getch();
        cout << endl;

        switch (choice)
        {
        case '1':   // Add a new account
        {
            signup();
            break;
        }
        case '2':   // Modify an existing account
        {
            cout << "\t\tEnter user's ID to modify: ";
            getline(cin, user.ID);

            users_data.open("UserData.txt", ios::in);

            if (users_data.is_open())
            {
                // Reading the users data file to check the existence of the user
                while (getline(users_data, line))    // Skipping the first line because its always white space (empty)
                {
                    getline(users_data, line);      // Starts reading from the second line beacuse it contain's the user's id
                    if (line == user.ID)            // User enterd exists
                    {
                        exist = true;
                        break;
                    }
                    while (getline(users_data, line))   // Skips reading the rest of the user's data cuz it's useless now
                    {
                        if (line == "______________________________")
                            break;
                    }
                }

                if (exist)
                {
                    // Reading the new data
                    cout << "\t\tEnter new user name: ";
                    getline(cin, user.Name);

                    cout << "\t\tEnter new age: ";
                    cin >> user.Age;
                    cin.ignore();

                    cout << "\t\tEnter new phone number: ";
                    getline(cin, user.Phone);

                    cout << "\t\tEnter new Email: ";
                    getline(cin, user.Email);

                    cout << "\t\tEnter new address: ";
                    getline(cin, user.Address);

                    cout << "\t\tEnter new gender: ";
                    getline(cin, user.gender);

                    // Resetting the stream pointer to read from the beggining of the file
                    users_data.clear();
                    users_data.seekg(0, ios::beg);

                    temp.open("newUserData.txt");

                    // Rewriting old data
                    while (getline(users_data, line))
                    {
                        if (line == user.ID)
                        {
                            while (getline(users_data, line))
                            {
                                if (line == "______________________________") break;
                            }

                            temp << user.ID;
                            temp << endl << user.Name;
                            temp << endl << user.Age;
                            temp << endl << user.Phone;
                            temp << endl << user.Email;
                            temp << endl << user.Address;
                            temp << endl << user.gender;
                            temp << endl << "______________________________\n";
                        }
                        else
                        {
                            temp << line << endl;
                        }
                    }
                    users_data.close();
                    temp.close();

                    remove("UserData.txt");
                    rename("NewUserData.txt", "UserData.txt");
                    cout << "\t\tUser's data modified successfully!\n\n";
                }
                else
                {
                    cout << "\t\tUser does not exist!\n\n\n";
                    users_data.close();
                    temp.close();
                }
            }
            else
            {
                cout << "\t\tError reading users' data!\n";
            }
            cout << "\t\tPress any key to continue\n";
            cout << "\t\t\t";
            _getch();
            break;
        }
        case '3':   // Delete an account
        {
            cout << "\t\tEnter user's ID to delete: ";
            getline(cin, user.ID);

            users_data.open("UserData.txt", ios::in);

            if (users_data.is_open())
            {
                // Reading the users data file to check the existence of the user
                while (getline(users_data, line))    // Skipping the first line because its always white space (empty)
                {
                    getline(users_data, line);      // Starts reading from the second line beacuse it contain's the user's id
                    if (line == user.ID)            // User enterd exists
                    {
                        exist = true;
                        break;
                    }
                    while (getline(users_data, line))   // Skips reading the rest of the user's data cuz it's useless now
                    {
                        if (line == "______________________________")
                        {
                            break;
                        }
                    }
                }

                if (exist)
                {
                    // Resetting the stream pointer to read from the beggining of the file
                    users_data.clear();
                    users_data.seekg(0, ios::beg);

                    temp.open("newUserData.txt");

                    // Rewriting old data
                    while (getline(users_data, line))
                    {
                        if (line == user.ID)
                        {
                            while (getline(users_data, line))
                            {
                                if (line == "______________________________") 
                                {
                                    getline(users_data,line);
                                    break;
                                }
                            }
                        }
                        else
                        {
                            temp << line << endl;
                        }
                    }
                    users_data.close();
                    temp.close();

                    remove("UserData.txt");
                    rename("NewUserData.txt", "UserData.txt");
                    cout << "\t\tUser's data deleted successfully!\n\n";
                }
                else
                {
                    cout << "\t\tUser does not exist!\n\n\n";
                    users_data.close();
                    temp.close();
                }
            }
            else
            {
                cout << "\t\tError reading users' data!\n";
            }
            cout << "\t\tPress any key to continue\n";
            cout << "\t\t\t";
            _getch();
            break;
        }
        case '4':   // Back to dashboard
        {
            return;
        }
        }
    }
}

void search_trains()
{

}

void cancel_booking()
{
    system("CLS");

    // Reading variables for file
    int id = -1;        // Initializing the id to check if the text file is empty or not
    int seats, price;
    string username, line;
    bool first_line = true;


    ifstream reserved;
    reserved.open("reservedTickets.txt");

    // if there is no tickets , then i will not be able to change anything
    if (reserved.is_open())
    {
        while (getline(reserved, line))
        {
            reserved >> username >> id >> seats >> price;

            if (id == -1)       // if id did'nt change --> the file is empty
            {
                cout << "No tickets booked yet!\n\n\n";
                Sleep(2000);
                reserved.close();
                return;
            }
            reserved.close();
        }
    }
    else
    {
        cout << "Error opening the file!\n\n\n";
    }

    // Getting ticket's ID to delete it
    cout << "Enter ticket's ID to cancel it:\n" << "\t-->";
    int ticket_id;
    cin >> ticket_id;
    cin.ignore();

    first_line = true;     // bool to check first line in the reservedTickets file
    ofstream temp;
    temp.open("newReservedTickets.txt");     // Temp file for adding new data
    reserved.open("reservedTickets.txt");      // Original file to read from

    // Reading data from file to delete the ticket
    if (temp.is_open() && reserved.is_open())
    {
        while (!reserved.eof())
        {
            if (first_line)
            {
                getline(reserved, line);
                temp << line;
                first_line = false;
                continue;
            }
            reserved >> username >> id >> seats >> price;

            if (ticket_id != id)
            {
                temp << endl << username << "\t\t" << id << "\t\t" << seats << "\t\t" << price;
            }
        }

        temp.close();
        reserved.close();
        cout << "Ticket has been cancelled succussfully!\n\n\n";
        Sleep(1000);

        remove("reservedTickets.txt");
        rename("newReservedTickets.txt", "reservedTickets.txt");
    }
}

void view_previous_trips()
{
    system("cls");  // Clears the terminal screen before printing again

    // Reading variable
    string line;

    ifstream trips;
    trips.open("reservedTickets.txt");

    if (trips.is_open())
    {
        while (getline(trips, line))
        {
            cout << endl << line;
        }
        trips.close();
    }

    cout << "\n\n\nPress any key to continue!\n";
    _getch();
}

void read_payment_methods()     // Updates payment methods availability whenever the admin changes
{
    string method;
    bool availability;

    ifstream payments;
    payments.open("paymentMethods.txt");

    if (payments.is_open())
    {
        while (!payments.eof())
        {
            payments >> method >> availability;

            if (method == "Bank_card")
                visa.is_available = availability;
            else if (method == "Cash")
                cash.is_available = availability;
            else if (method == "Fawry")
                fawry.is_available = availability;
        }
        payments.close();
    }
    else
    {
        cout << "\t\t\tError reading payment methods details form file!\n\n\n";
    }
}

int make_payment(int price, int seats)
{   // Function must return (ticket price * seats number), if returned 1 --> error
    while (true)
    {
        system("cls");
        read_payment_methods();

        int ticket_price;       // Final ticket price after multiplying by seats numbers
        ticket_price = price * seats;

        cout << "\t\tSelect payment method:\n";
        cout << "\t\t\t1>> Cash\n";
        cout << "\t\t\t2>> Bank card\n";
        cout << "\t\t\t3>> Fawry\n\n";
        cout << "\t\t\t or Press any key to go back to dashboard\n\n\n";
        cout << "\t\t\t\t";

        bool valid;
        char button;
        button = _getch();

        if (button == '1')
        {   // Cash

            if (cash.is_available)
            {
                cout << "You will pay: " << ticket_price << " at the Railway Station\n\n\n";
                cout << "\t\tPress any key to continue!\n";
                cout << "\t\t";
                _getch();
                return ticket_price;
            }
            else
            {
                cout << "\t\tCash payment method isn't available right now\n";
                cout << "\t\tPress any key to continue!\n";
                cout << "\t\t";
                _getch();
            }
        }
        else if (button == '2')
        {   // Bank card

            if (visa.is_available)
            {
                valid = is_valid();
                if (valid)
                {
                    cout << "\t\tPayment transaction done successfully!\n\n\n";
                    cout << "\t\tPress any key to continue!\n";
                    cout << "\t\t";
                    _getch();
                    return ticket_price;
                }
                else
                {
                    cout << "\t\tPayment card invalid\n";
                    cout << "\t\tPress any key to continue!\n";
                    cout << "\t\t";
                    _getch();
                }
            }
            else
            {
                cout << "\t\tBank card payment method isn't available right now\n";
                cout << "\t\tPress any key to continue!\n";
                cout << "\t\t";
                _getch();
            }
        }
        else if (button == '3')
        {   // Fawry

            if (fawry.is_available)
            {
                // Generating refrence code     (   3829        +        Y          +       906      )
                // Consists of 3 sectiona       4 random digits + 1 random alphabet + 3 random digits
                string code;
                string sec1, sec2, sec3;
                int s1, s3;

                // Generating sec1
                s1 = 1000 + rand() % 9000;  // Generating 4 random digits
                sec1 = to_string(s1);       // Converting int to string

                // Generating sec2
                sec2 = 65 + rand() % 26;    // Generating a ranodm alphaber

                // Generating sec3
                s3 = 100 + rand() % 900;    // Generating 3 random digits
                sec3 = to_string(s3);       // Converting int to string

                // Putting all the sections together to form the whole code
                code = sec1 + sec2 + sec3;

                cout << "\t\t\tYour refrence code is [" << code << "] you must pay it within 72 hours!\n\n\n";
                cout << "\t\tPress any key to continue!\n";
                cout << "\t\t\t";
                _getch();
                return ticket_price;
            }
            else
            {
                cout << "\t\tFawry payment method isn't available right now\n";
                cout << "\t\tPress any key to continue!\n";
                cout << "\t\t\t";
                _getch();
            }
        }
        else
        {
            return -1;
        }
    }
}

void manage_payment()
{
    // Reading variables
    string method, line;
    bool availability;
    fstream payments;

    while (true)
    {
        read_payment_methods();
        system("cls");

        cout << "\t\t\t____________________________________________________________________________________________\n\n\n";
        cout << "\t\t\t_______________________________     Edit Payment methods     _______________________________\n\n\n";
        cout << "\t\t\tPress [1] to view payment methods\n";
        cout << "\t\t\tPress [2] to edit payment methods\n";
        cout << "\t\t\tPress any key to go back to dashboard\n\n\n";
        cout << "\t\t\t\t";

        char button;
        button = _getch();
        if (button == '1')
        {   // View payment details
            // Reading payment methods data
            payments.open("paymentMethods.txt", ios::in);

            // Displaying available payment methods to the admin
            if (payments.is_open())
            {
                cout << "\t\t\t" << "methods\t\tavailability" << endl;
                while (getline(payments, line))
                {
                    cout << endl;
                    cout << "\t\t\t" << line;
                }
                payments.close();

                cout << endl << endl;
                cout << "\t\tPress any key to continue!\n";
                cout << "\t\t\t";
                _getch();
                continue;
            }
            else
            {
                cout << "\t\t\tError opening file\n\n\n";
                cout << "\t\tPress any key to continue!\n";
                cout << "\t\t\t";
                _getch();
                continue;
            }
        }
        else if (button == '2')
        {   // Edit payment methods
            while (true)
            {
                system("cls");
                ofstream temp;  // To write new data
                string new_method;
                cout << "\t\t\tPress [1] to edit Bank card\n";
                cout << "\t\t\tPress [2] to edit Cash\n";
                cout << "\t\t\tPress [3] to edit Fawry\n";
                cout << "\t\t\tPress any other key to go back\n\n\n";
                cout << "\t\t\t\t";

                button = _getch();
                if (button == '1')
                {
                    new_method = "Bank_card";

                    cout << "\t\t\tAdd Bank card as a payment method? (y/n):\n";
                    cout << "\t\t\t\t";
                    button = _getch();


                }
                else if (button == '2')
                {
                    new_method = "Cash";

                    cout << "\t\t\tAdd Cash as a payment method? (y/n):\n";
                    cout << "\t\t\t\t";
                    button = _getch();
                }
                else if (button == '3')
                {
                    new_method = "Fawry";

                    cout << "\t\t\tAdd Fawry as a payment method? (y/n):\n";
                    cout << "\t\t\t\t";
                    button = _getch();
                }
                else
                {
                    break;
                }

                payments.open("paymentMethods.txt", ios::in);
                temp.open("newPaymentMethods.txt");
                bool first_line = true;

                if (payments.is_open() && temp.is_open())
                {
                    while (!payments.eof())
                    {
                        payments >> method >> availability;

                        if (!first_line)
                            temp << endl;

                        if (method == new_method)
                        {
                            temp << method << "\t\t";

                            if (button == 'y')
                            {
                                temp << true;
                            }
                            else if (button == 'n')
                            {
                                temp << false;
                            }
                        }
                        else
                        {
                            temp << method << "\t\t" << availability;
                        }
                        first_line = false;
                    }
                    payments.close();
                    temp.close();

                    remove("paymentMethods.txt");
                    rename("newPaymentMethods.txt", "paymentMethods.txt");
                }
                else
                {
                    cout << "\t\t\tError reading data from files!\n\n\n";
                    cout << "\t\tPress any key to continue\n";
                    cout << "\t\t";
                    _getch();
                }
            }
        }
        else
        {
            break;
        }

    }
}

void generateUserReport(string userID) {
    // Find the user
    for (int i = 0; i < user_reports.size(); i++) {
        if (user_reports[i].ID == userID) {
            cout << "User Report for " << user_reports[i].Name << ":\n";
            cout << "Email: " << user_reports[i].Email << "\n";
            cout << "Address: " << user_reports[i].Address << "\n";
            cout << "Phone: " << user_reports[i].Phone << "\n";
            cout << "Gender: " << user_reports[i].gender << "\n";
            cout << "Age: " << user_reports[i].Age << "\n";
            cout << "Role: " << user_reports[i].Role << "\n";

            // Print all tickets for this user
            for (int j = 0; j < user_reports[i].booked_tickets.size(); j++) {
                cout << "Ticket ID: " << user_reports[i].booked_tickets[j].ID << "\n";
                cout << "Start Location: " << user_reports[i].booked_tickets[j].Start_location << "\n";
                cout << "Destination Location: " << user_reports[i].booked_tickets[j].Destination_location << "\n";
                cout << "Price: " << user_reports[i].booked_tickets[j].Price << "\n";
            }
            break;
        }
    }
}

void book_tickets()
{
    system("CLS");

    // Reading variables
    Ticket ticket;
    int seats;
    string start, dest;
    int id, price;
    ifstream prices;
    prices.open("ticketsPrices.txt");

    cout << endl;
    cout << "---------------------Locations---------------------" << endl;
    cout << left;
    cout << setw(5) << "ID";
    cout << setw(20) << "Start";
    cout << setw(20) << "Destination";
    cout << setw(5) << "Price" << endl << endl;


    while (!prices.eof())
    {
        prices >> id >> start >> dest >> price;

        // Displaying file's data to the user
        cout << left;
        cout << setw(5) << id;
        cout << setw(20) << start;
        cout << setw(20) << dest;
        cout << setw(5) << price << endl;
    }
    cout << "---------------------------------------------------" << endl;
    prices.close();

    cout << "\t\tEnter ticket ID you want to book:\n";
    cout << "\t\t\t-->";
    cin >> ticket.ID;
    cin.ignore();

    cout << "\t\tEnter number of seats:\n";
    cout << "\t\t\t-->";
    cin >> seats;
    cout << "---------------------------------------------------\n";

    // Reading ticket's price from prices file
    prices.open("ticketsPrices.txt");
    if (prices.good())
    {
        while (!prices.eof())
        {
            prices >> id >> start >> dest >> price;

            if (ticket.ID == id)
            {
                ticket.Price = price;       // Storing ticket's price for payment operation
                break;
            }
        }
        prices.close();
    }
    else
    {
        cout << "Error reading ticket's data from file!\n\n";
    }

    ticket.Price = make_payment(ticket.Price, seats);     // Storing ticket price after checking visa validity
    if (ticket.Price == -1)
    {
        cout << "\t\t\tTicket booking cancelled\n\n\n";
        cout << "\t\tPress any key to continue!\n";
        cout << "\t\t";
        _getch();
        return;
    }

    // Writing reserved ticket's data into a file
    ofstream reserve;
    reserve.open("reservedTickets.txt", ios::app);
    if (reserve.good())
    {
        // setw() used for allignment
        reserve << endl;
        reserve << left;
        reserve << setw(16) << user.ID;
        reserve << setw(16) << ticket.ID;
        reserve << setw(12) << seats;
        reserve << setw(5) << ticket.Price;
    }
    reserve.close();
    cout << endl << endl << "Ticket added successfully!" << endl << endl << endl;
    generateUserReport(user.ID);
    Sleep(2000);
}

bool isloggedin()
{
    system("CLS");
    string username;
    string password;

    // Reading variables
    string un; //comparison string
    string pw; //comparison string
    string role;

    cout << "\t\t\tPlease Enter The USERNAME : ";
    cin >> username;
    cout << "\t\t\tPlease Enter The PASSWORD : ";
    cin >> password;
    cin.ignore();

    fstream read; // fstream reads a file
    read.open("LoginData.txt", ios::in);

    if (!read.is_open()) {
        cout << "Error opening the file";
        read.close();
        exit(1);
    }
    // Check every username and Password in the file 
    while (!read.eof()) {
        getline(read, un); //reads the username
        getline(read, role); // reads the user's role
        getline(read, pw); //reads the password 
        if (un == username && pw == password) //if both un & username and pw & password are the same -> true
        {
            read.close();
            user.ID = username;
            user.Role = role;
            return true;
        }
    }
    // if the Function didn't return this means that the given username is not in file or the password is wrong
    return false;
}

void MangeTicket() {
    // Reading variables for prices file "ticketsPrices.txt"
    int id, price;
    string start, dest, line;
    while (1) {
        // Menu
        cout << endl << "Enter 1 to add a new ticket" << endl;
        cout << "Enter 2 to change a ticket" << endl;
        cout << "Enter 3 to delete a ticket" << endl;
        cout << "Enter any other number to exit" << endl << endl << endl;
        char choice;
        choice = _getch();

        if (choice == '1') {
            Ticket NewTicket;
            bool exist = false;
            bool first_line = false;
            id = -1;
            prices.open("ticketsPrices.txt", ios::in);      // Reading from file to check if the new ticket ID already exists

            cout << "Enter ticket ID:\n" << "\t-->";
            cin >> NewTicket.ID;
            while (!prices.eof())
            {       // Checking if the ticket ID already exists in file or not
                prices >> id >> start >> dest >> price;

                if (id == -1) first_line = true;
                if (NewTicket.ID == id)
                {
                    cout << "Ticket ID already exitsts!\n\n";
                    exist = true;
                    break;
                }
            }
            if (exist)
            {
                prices.close();
                continue;
            }
            cin.ignore();
            prices.close();

            // Get start location
            cout << "Enter the start location of the ticket : ";
            getline(cin, NewTicket.Start_location);

            // Get destination location
            cout << "Enter the destination location of the ticket : ";
            getline(cin, NewTicket.Destination_location);

            // Get Price
            cout << "Enter the price of the ticket : ";
            cin >> NewTicket.Price;

            // Appending the new ticket data into the "ticketsPrices.txt" file
            prices.open("ticketsPrices.txt", ios::app);
            if (prices.good())
            {
                if (!first_line) prices << endl;
                prices << NewTicket.ID << "\t\t" << NewTicket.Start_location << "\t\t";;
                prices << NewTicket.Destination_location << "\t\t" << NewTicket.Price;
            }

            prices.close();
            cout << endl << endl << "Ticket added successfully!" << endl << endl << endl;
        }

        else if (choice == '2') {      // Change ticekt details
            bool empty = false;
            id = -1;        // Initializing the id to check if the text file is empty or not

            // if there is no tickets , then i will not be able to change anything
            prices.open("ticketsPrices.txt", ios::in);

            if (prices.is_open())
            {
                while (!prices.eof())
                {
                    prices >> id >> start >> dest >> price;

                    if (id == -1)
                    {
                        cout << "No tickets to change!\n\n\n";
                        empty = true;
                        break;
                    }
                }
                if (empty)
                {       // If the "ticketsPrices" file is empty, close the file
                    prices.close();
                    continue;
                }
                prices.close();
            }
            else
            {
                cout << "Error reading tickets prices!\n";
            }

            // Getting ticket's ID to modify it
            cout << "Enter ticket's ID:\n" << "\t-->";
            int ticket_id;
            cin >> ticket_id;
            cin.ignore();

            // Get the new start location
            cout << "Enter the new start location of the ticket :\n" << "\t-->";
            string new_start_location;
            getline(cin, new_start_location);

            // Get the new destination location
            cout << "Enter the new destination location of the ticket :\n" << "\t-->";
            string new_destination_location;
            getline(cin, new_destination_location);

            // Get the new price
            cout << "Enter the new price of the ticket :\n" << "\t-->";
            int new_price;
            cin >> new_price;
            cin.ignore();

            // Replacing the old ticket with the new ticket
            bool first_line = true;
            ofstream temp;
            temp.open("newPrices.txt");     // Temp file for adding new data
            prices.open("ticketsPrices.txt", ios::in);      // Original file to read from

            if (temp.is_open() && prices.is_open())
            {
                while (!prices.eof())
                {
                    prices >> id >> start >> dest >> price;

                    if (!first_line) temp << endl;
                    if (ticket_id == id)
                    {
                        temp << ticket_id << "\t\t" << new_start_location << "\t\t" << new_destination_location << "\t\t";
                        temp << new_price;
                    }
                    else
                    {
                        temp << id << "\t\t" << start << "\t\t" << dest << "\t\t" << price;
                    }
                    first_line = false;
                }

                temp.close();
                prices.close();

                remove("ticketsPrices.txt");
                rename("newPrices.txt", "ticketsPrices.txt");
                cout << endl << endl << "Ticket changed successfully!" << endl << endl << endl;
            }

            else
            {
                cout << "Error reading old ticket's data from file!\n";
                continue;
            }

        }
        else if (choice == '3') {
            bool empty = false;
            id = -1;        // Initializing the id to check if the text file is empty or not

            // if there is no tickets , then i will not be able to change anything
            prices.open("ticketsPrices.txt", ios::in);

            if (prices.is_open())
            {
                while (!prices.eof())
                {
                    prices >> id >> start >> dest >> price;

                    if (id == -1)
                    {
                        cout << "No tickets to delete!\n\n\n";
                        empty = true;
                        break;
                    }
                }
                if (empty)
                {       // If the "ticketsPrices" file is empty, close the file
                    prices.close();
                    continue;
                }
                prices.close();
            }
            else
            {
                cout << "Error opening the file!\n\n\n";
            }

            // Getting ticket's ID to delete it
            cout << "Enter ticket's ID:\n" << "\t-->";
            int ticket_id;
            cin >> ticket_id;
            cin.ignore();

            bool first_line = true;     // bool to check first line in the prices file "ticketsPrices.txt"
            ofstream temp;
            temp.open("newPrices.txt");     // Temp file for adding new data
            prices.open("ticketsPrices.txt", ios::in);      // Original file to read from

            // Reading data from file to delete the ticket
            if (temp.is_open() && prices.is_open())
            {
                while (!prices.eof())
                {
                    prices >> id >> start >> dest >> price;

                    if (!first_line) temp << endl;
                    if (ticket_id != id)
                    {
                        temp << id << "\t\t" << start << "\t\t" << dest << "\t\t" << price;
                    }
                    else
                    {
                        first_line = true;
                        continue;
                    }
                    first_line = false;
                }

                temp.close();
                prices.close();

                remove("ticketsPrices.txt");
                rename("newPrices.txt", "ticketsPrices.txt");
            }
        }
        else {
            // if the choice any other value -> end the program
            break;
        }
    }
}


//---------------------- Main Function ----------------------//
int main()
{
    while (true)
    {
        system("CLS");

        cout << "\t\t\t _____________________________________________________________________________________________\n\n\n";
        cout << "\t\t\t                                 Welcome to Log in page                                        \n\n\n";
        cout << "\t\t\t ___________________________              MENU              ____________________________________\n\n\n";

        cout << "\t\t\t1>> Login\n";
        cout << "\t\t\t2>> Singup\n\n";

        cout << "\t\t\tTo create a new account, press 2\n";
        cout << "\t\t\tIf you already have an account, press 1\n";
        cout << "\t\t\tTo exit the program, press any key\n\n";
        cout << "\t\t\t\t";

        char button;
        button = _getch();

        if (button == '1') {
            int check = isloggedin();
            int counter = 0;

            // Checking user's login credentials, the program resets after 4 wrong attempts
            while (!check && counter < 4) {
                cout << endl << "Wrong password or username." << endl;
                cout << "Please enter a correct username and password." << endl << endl;
                check = isloggedin();
            }
            if (check)
            {

                cout << endl << "\t\t\tLogged in successfully :D" << endl << endl;
                cout << "\t\t\t";
                Sleep(1000);
            }
            else
            {
                cout << "\t\t\tError entering credentials wrong too many times!" << "\n\n";
                cout << "\t\tPress any key to continue!\n";
                cout << "\t\t\t";
                _getch();
            }
        }
        else if (button == '2')
        {
            signup();
        }
        else
        {
            exit(0);
        }

        if (user.Role == "admin")
        {
            // Admin functions
            while (1) {
                system("CLS");
                cout << "\t\t\t______________________________________    Dashboard    ______________________________________\n\n\n";
                cout << "\t\t\t1>> Manage train schedule" << endl;
                cout << "\t\t\t2>> Manage user accounts" << endl;
                cout << "\t\t\t3>> Manage ticket prices" << endl;
                cout << "\t\t\t4>> Manage Payment" << endl;
                cout << "\t\t\t5>> Search trains" << endl;
                cout << "\t\t\t6>> Book tickets" << endl;
                cout << "\t\t\t7>> Cancel booking" << endl;
                cout << "\t\t\t8>> View previous trips" << endl << endl;
                cout << "\t\t\t_____________________________________________________________________________________________\n\n\n";
                cout << "\t\t\tPress a number for an action" << endl;
                cout << "\t\t\tor press any key to exit the program" << endl << endl;
                cout << "\t\t\t\t";


                char choice;
                choice = _getch();

                if (choice == '1')
                {
                    manage_train_schedule();
                }
                else if (choice == '2') {
                    manage_user_accounts();
                }
                else if (choice == '3')
                {
                    MangeTicket();
                }
                else if (choice == '4')
                {
                    manage_payment();
                }
                else if (choice == '5')
                {
                    search_trains();
                }
                else if (choice == '6')
                {
                    book_tickets();
                }
                else if (choice == '7')
                {
                    cancel_booking();
                }
                else if (choice == '8')
                {
                    view_previous_trips();
                }
                else
                {
                    exit(0);
                }
            }
        }
        else
        {
            // User functions
            while (1)
            {
                system("CLS");
                cout << "______________________________________    Dashboard    ______________________________________\n\n\n";
                cout << "\t\t\t1>> Search trains" << endl;
                cout << "\t\t\t2>> Book tickets" << endl;
                cout << "\t\t\t3>> Cancel booking" << endl;
                cout << "\t\t\t4>> View previous trips" << endl;
                cout << "\t\t\t5>> Logout" << endl << endl;
                cout << "_____________________________________________________________________________________________\n\n\n";
                cout << "\t\tPress a number for an action" << endl;
                cout << "\t\t\t";

                char choice;
                choice = _getch();

                if (choice == '1')
                {
                    search_trains();
                }
                else if (choice == '2') {
                    book_tickets();
                }
                else if (choice == '3')
                {
                    cancel_booking();
                }
                else if (choice == '4')
                {
                    view_previous_trips();
                }
                else if (choice == '5')
                {
                    break;
                }
            }
        }
    }

}
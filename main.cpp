
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <iomanip>

using namespace std;

//-------------------------------------------- Structs --------------------------------------------//
struct Train {
    string ID;
    string name;
    int number;
    string availability;
}train;

struct Ticket {
    int ID;
    string Start_location;
    string Destination_location;
    float Price;
    string name;
};
vector<Ticket> Tickets;

struct User {
    string ID;
    string Name;
    string Phone;
    float Age;
    string Email;
    string pass;
    string Address;
    string Role;        // Passenger or Admin
    string gender;
}user;



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


//-------------------------------------------- Functions Decleration --------------------------------------------//
void start_menu();
void manage_train_schedule();
void manage_user_accounts();
void manage_payment();
void manage_ticket_prices();
void search_trains();
void read_payment_methods();
int make_payment(int price, int seats);
void book_tickets();
void cancel_booking();
bool isloggedin();
void sign_up();
void forgot();
void generate_user_reports(User &user);
void update_user_data();
void view_previous_trips();
int get_digits(long long n);
bool is_valid();


//-------------------------------------------- Main Function --------------------------------------------//
int main()
{
    start_menu();
}


//-------------------------------------------- Functions --------------------------------------------//
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
    // Date variables
    int current_month = 5;
    int current_year = 24;

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

        string payment_method_used;
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
                payment_method_used = "Cash";
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
                    payment_method_used = "VISA";
                    cout << "\t\tPayment transaction done successfully!\n\n\n";
                    cout << "\t\tPress any key to continue!\n";
                    cout << "\t\t";
                    _getch();
                    return ticket_price;
                }
                else
                {
                    payment_method_used = "VISA";
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
                payment_method_used = "Fawry";
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
            return ticket_price;
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

void book_tickets()
{
    system("CLS");

    // Const variable for array
    const int max_tickets = 20;     // max tickets per booking session
    Ticket tickets[max_tickets];

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

    int i = 0;
    while (prices >> id >> start >> dest >> price)
    {
        // Storing tickets data in an array to find them again easily
        tickets[i].ID = id;
        tickets[i].Start_location = start;
        tickets[i].Destination_location = dest;
        tickets[i].Price = price;
        i++;

        // Displaying file's data to the user
        cout << left;
        cout << setw(5) << id;
        cout << setw(20) << start;
        cout << setw(20) << dest;
        cout << setw(5) << price << endl;
    }
    cout << "---------------------------------------------------\n\n";
    prices.close();

    cout << "\t\tEnter ticket ID you want to book: ";
    cin >> ticket.ID;
    cin.ignore();

    // Checking if the ticket ID exists
    i = 0;
    bool exist = false;
    prices.open("ticketsPrices.txt");
    while (prices >> tickets[i].ID >> tickets[i].Start_location >> tickets[i].Destination_location >> tickets[i].Price)
    {
        if (tickets[i].ID == ticket.ID)
        {
            exist == true;
            break;
        }
    }
    if (!exist)
    {
        cout << "\t\tTicket ID entered does not exist! Please type it again";
        Sleep(1000);
        book_tickets();
    }

    // if tickets ID exists, countinue reading the rest of the data
    cout << "\t\tEnter number of seats: ";
    cin >> seats;
    cout << "---------------------------------------------------\n";

    // Reading ticket's price from prices file
    prices.open("ticketsPrices.txt");
    if (prices.good())
    {

        ticket.Price = make_payment(ticket.Price, seats);     // Storing ticket price after checking visa validity
        while (!prices.eof())
        {
            prices >> id >> start >> dest >> price;

            if (ticket.ID == id)
            {
                ticket.Price = price;       // Storing ticket's price for payment operation
                ticket.Start_location = start;
                ticket.Destination_location = dest;
                break;
            }
        }
        prices.close();
    }
    else
    {
        cout << "Error reading ticket's data from file!\n\n";
    }

    // Writing reserved ticket's data into a file
    ofstream reserve;
    reserve.open("reservedTickets.txt", ios::app);
    // setw() used for allignment
    reserve << left;
    reserve << setw(16) << user.ID;
    reserve << setw(16) << ticket.ID;
    reserve << setw(20) << ticket.Start_location;
    reserve << setw(20) << ticket.Destination_location;
    reserve << setw(12) << seats;
    reserve << setw(5) << ticket.Price;
    reserve << endl;
    reserve.close();

    cout << "\n\t\tTicket added successfully!\n\n\n";
    Sleep(2000);
}

void cancel_booking()
{
    system("CLS");

    // Reading variables for file
    int id;        // Initializing the id to check if the text file is empty or not
    int seats;
    float price;
    string username, start, dest, line;
    bool first_line = true;


    ifstream reserved;
    reserved.open("reservedTickets.txt");

    // if there is no tickets , then i will not be able to change anything
    if (reserved.is_open())
    {
        // Reading the first line in file to check if it's empty
        getline(reserved, line);
        if (line == "")       // if the string (line) is empty --> the file also is empty
        {
            reserved.close();
            cout << "\t\tNo tickets booked yet!\n\n\n";
            Sleep(2000);
            main();
        }
        reserved.close();
    }
    else
    {
        cout << "\t\tNo tickets booked yet!\n\n\n";
        Sleep(2000);
        main();
    }

    // Getting ticket's ID to delete it
    cout << "Enter ticket's ID to cancel it: ";
    int ticket_id;
    cin >> ticket_id;

    ofstream temp;
    temp.open("newReservedTickets.txt");     // Temp file for adding new data
    reserved.open("reservedTickets.txt");      // Original file to read from

    // Reading data from file to delete the ticket
    while (reserved >> username >> id >> start >> dest >> seats >> price)
    {
        if (ticket_id != id)
        {
            temp << left;
            temp << setw(16) << username;
            temp << setw(16) << id;
            temp << setw(20) << start;
            temp << setw(20) << dest;
            temp << setw(12) << seats;
            temp << setw(5) << price;
            temp << endl;
        }
    }

    temp.close();
    reserved.close();
    cout << "Ticket has been cancelled succussfully!\n\n\n";
    Sleep(1000);

    remove("reservedTickets.txt");
    rename("newReservedTickets.txt", "reservedTickets.txt");
}

bool isloggedin()
{
    system("CLS");
    string userID;
    string password;

    // Reading variables
    string id; //comparison string
    string pw; //comparison string
    string role;

    cout << "\t\t\tPlease Enter The User ID : ";
    cin >> userID;
    cin.ignore();

    cout << "\t\t\tPlease Enter The PASSWORD : ";
    getline(cin, password);

    ifstream read; // fstream reads a file
    read.open("LoginData.txt");

    if (!read.is_open()) {
        cout << "Error opening the file";
        exit(1);
    }
    // Check every username and Password in the file 
    while (!read.eof()) {
        getline(read, id); //reads the username
        getline(read, role); // reads the user's role
        getline(read, pw); //reads the password 
        if (id == userID && pw == password) //if both un & username and pw & password are the same -> true
        {
            read.close();
            user.ID = id;
            user.Role = role;
            return true;
        }
    }
    // if the Function didn't return this means that the given username is not in file or the password is wrong
    return false;
}

void forgot()
{
    while (true)
    {
        system("cls");
        int option;

        cout << "you forgot your password ?? don't worry !! \n";
        cout << " press 1 to search your id by username \n";
        cout << "prees 2 to go back to main menu \n";
        cout << "\t\t\t Enter your choice ";
        cin >> option;

        switch (option)
        {
        case 1:
        {
            bool found = false;
            string suserid, sid, spass, srole;

            cout << "\n \t\t\t Enter the user name which you remembered :";
            cin >> suserid;

            ifstream f2("LoginData.txt");
            while (f2 >> sid >> srole >> spass)
            {
                if (sid == suserid)
                {
                    found = true;
                }

            }
            f2.close();
            if (found)
            {
                cout << "\n\n \t\tYOUR account is found :\n ";
                cout << "\n\n \t\tyour password is :" << spass;
            }
            else
            {
                cout << "\t\tCould'nt find your account!\n\n\n";
            }
            cout << "\t\tPress any key to continue\n";
            cout << "\t\t\t";
            _getch();
            break;
        }
        case 2:
        {
            return;
        }
        }
    }
}

void start_menu()
{
    while (true)
    {
        system("CLS");

        cout << "\t\t _____________________________________________________________________________________________\n\n\n";
        cout << "\t\t                                 Welcome to Log in page                                        \n\n\n";
        cout << "\t\t ___________________________              MENU              ____________________________________\n\n\n";

        cout << "\t\t1>> Login\n";
        cout << "\t\t2>> Singup\n";
        cout << "\t\t3>> Forgot Password\n\n";

        cout << "\t\tTo create a new account, press 2\n";
        cout << "\t\tIf you already have an account, press 1\n";
        cout << "\t\tIf you forgot your password, press 3\n\n";
        cout << "\t\tTo exit the program, press any key\n\n";
        cout << "\t\t\t";

        char button;
        button = _getch();

        if (button == '1') {
            int check = isloggedin();
            int counter = 0;

            // Checking user's login credentials, the program resets after 4 wrong attempts
            while (!check && counter < 4) {
                cout << "\n\t\tWrong password or username.\n";
                cout << "\t\tPlease enter a correct username and password\n\n\n";
                counter++;

                cout << "\t\tPress any key to continue!\n";
                cout << "\t\t\t";
                _getch();
                check = isloggedin();
            }
            if (check)
            {

                cout << endl << "\t\t\tLogged in successfully :D" << endl << endl;
                cout << "\t\t\t";
                update_user_data();
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
            sign_up();
            continue;
        }
        else if (button == '3')
        {
            forgot();
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
                cout << "\t\t1>> Manage train schedule" << endl;
                cout << "\t\t2>> Manage user accounts" << endl;
                cout << "\t\t3>> Manage ticket prices" << endl;
                cout << "\t\t4>> Manage Payment" << endl;
                cout << "\t\t5>> Search trains" << endl;
                cout << "\t\t6>> Book tickets" << endl;
                cout << "\t\t7>> Cancel booking" << endl;
                cout << "\t\t8>> View previous trips" << endl;
                cout << "\t\t9>> Generate user report\n\n";
                cout << "\t\t_____________________________________________________________________________________________\n\n\n";
                cout << "\t\tPress a number for an action" << endl;
                cout << "\t\tor press any other key to logout" << endl << endl;
                cout << "\t\t\t";


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
                    manage_ticket_prices();
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
                else if (choice == '9')
                {
                    generate_user_reports(user);
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
                cout << "\t\t1>> Search trains" << endl;
                cout << "\t\t2>> Book tickets" << endl;
                cout << "\t\t3>> Cancel booking" << endl;
                cout << "\t\t4>> View previous trips" << endl;
                cout << "\t\t5>> Generate user reports\n";
                cout << "\t\t6>> Logout" << endl << endl;
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
                else if (choice == '5') generate_user_reports(user);
                else if (choice == '6')
                {
                    break;
                }
            }
        }
    }
}

void manage_ticket_prices() {
    // Reading variables for prices file "ticketsPrices.txt"
    int id, price;
    string start, dest, line;
    fstream prices;
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
            id;
            prices.open("ticketsPrices.txt", ios::in);      // Reading from file to check if the new ticket ID already exists

            cout << "Enter ticket ID:\n" << "\t-->";
            cin >> NewTicket.ID;
            while (!prices.eof())
            {       // Checking if the ticket ID already exists in file or not
                prices >> id >> start >> dest >> price;

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
            prices.close();

            // Get start location
            cout << "Enter the start location of the ticket : ";
            cin.ignore();
            getline(cin, NewTicket.Start_location);

            // Get destination location
            cout << "Enter the destination location of the ticket : ";
            getline(cin, NewTicket.Destination_location);

            // Get Price
            cout << "Enter the price of the ticket : ";
            cin >> NewTicket.Price;

            // Appending the new ticket data into the "ticketsPrices.txt" file
            prices.open("ticketsPrices.txt", ios::app);

            prices << NewTicket.ID << "\t\t" << NewTicket.Start_location << "\t\t";;
            prices << NewTicket.Destination_location << "\t\t" << NewTicket.Price;

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
            ofstream temp;
            temp.open("newPrices.txt");     // Temp file for adding new data
            prices.open("ticketsPrices.txt", ios::in);      // Original file to read from

            if (temp.is_open() && prices.is_open())
            {
                while (!prices.eof())
                {
                    prices >> id >> start >> dest >> price;

                    if (ticket_id == id)
                    {
                        temp << ticket_id << "\t\t" << new_start_location << "\t\t" << new_destination_location << "\t\t";
                        temp << new_price;
                    }
                    else
                    {
                        temp << id << "\t\t" << start << "\t\t" << dest << "\t\t" << price;
                    }
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

void sign_up()
{
    system("cls");
    User new_user;
    string new_user_ID;
    new_user.Role = "passenger";

    cout << "\t\t Enter the ID: ";
    cin >> new_user_ID;

    cout << "\t\t Enter the user name: ";
    cin.ignore();
    getline(cin, new_user.Name);

    cout << "\t\t Enter your age: ";
    cin >> new_user.Age;

    cout << "\t\t Enter your phone details: ";
    cin >> new_user.Phone;

    cout << "\t\t Enter your Email: ";
    cin >> new_user.Email;

    cout << "\t\t Enter your new_user password: ";
    cin.ignore();
    getline(cin, new_user.pass);

    cout << "\t\t Enter your address : ";
    getline(cin, new_user.Address);

    cout << "\t\t Enter your gender : ";
    cin >> new_user.gender;

    string rid = new_user_ID;
    string rpass = new_user.pass;

    // Creating Output file to add the new user's signup data
    ofstream f1("UserData.txt", ios::app);

    // Appending the new user's data
    f1 << new_user_ID;
    f1 << endl << new_user.Name;
    f1 << endl << new_user.Age;
    f1 << endl << new_user.Phone;
    f1 << endl << new_user.Email;
    f1 << endl << new_user.Address;
    f1 << endl << new_user.gender;
    f1 << endl << "______________________________\n";

    f1.close();

    // Creating Output file to add the new user's login data
    ofstream f2("LoginData.txt", ios::app);
    f2 << rid << endl;
    f2 << new_user.Role << endl;
    f2 << rpass << endl;

    f2.close();

    cout << "\n\t\t SIGNED UP SUCCESSFULLY!  \n\n\n";
    cout << "\t\tPress any key to continue!\n";
    cout << "\t\t";
    _getch();
}

void manage_user_accounts()
{
    while (true)
    {
        system("cls");

        // Reading variables
        fstream users_data; // For reading data
        ifstream login_data;// For reading data
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
            sign_up();
            break;
        }
        case '2':   // Modify an existing account
        {
            cout << "\t\tEnter user's ID to modify: ";
            cin >> user.ID;
            cin.ignore();

            users_data.open("UserData.txt", ios::in);

            if (users_data.is_open())
            {
                // Reading the users data file to check the existence of the user
                while (getline(users_data, line))    // Skipping the first line because its always white space (empty)
                {
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
                    cin >> user.Email;
                    cin.ignore();

                    cout << "\t\tEnter new address: ";
                    getline(cin, user.Address);

                    cout << "\t\tEnter new gender: ";
                    cin >> user.gender;

                    // Resetting the stream pointer to read from the beggining of the file
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
            cin >> user.ID;

            // Opening user data file to remove the user's data
            users_data.open("UserData.txt", ios::in);
            if (users_data.is_open())
            {
                // Reading the users data file to check the existence of the user
                while (getline(users_data, line))
                {
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
                }
                else
                {
                    cout << "\t\tUser does not exist!\n\n\n";
                    users_data.close();
                    temp.close();
                    cout << "\t\tPress any key to continue\n";
                    cout << "\t\t\t";
                    _getch();
                    break;
                }
            }
            else
            {
                cout << "\t\tError reading users' data!\n";
            }

            // Opening login data file to remove the user's login data also
            login_data.open("LoginData.txt");
            temp.open("NewLoginData.txt");

            if (login_data.is_open())
            {
                while (getline(login_data, line))
                {
                    if (line == user.ID)
                    {
                        // Skips role and password
                        getline(login_data, line);
                        getline(login_data, line);

                    }
                    else
                    {
                        temp << line << endl;
                    }
                }
                cout << "\t\tUser's data deleted successfully!\n\n";

                temp.close();
                login_data.close();

                remove("LoginData.txt");
                rename("NewLoginData.txt", "LoginData.txt");
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

void search_trains() {
    while (true)
    {
        system("cls");

        // Reading variables
        ifstream file;
        string line;

        int pointer_location;   // Getting stream pointer location

        cout << "\t\tSearch train by:\n";
        cout << "\t\t[1] train number\n";
        cout << "\t\t[2]train name\n\n\n";
        cout << "\t\t[3] Back to dashboard\n\n";
        cout << "\t\t\t";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
        {
            cout << "\t\tEnter train number to search: ";
            cin >> train.number;
            bool exist = false;

            // Opening file to search
            file.open("train_schedule.txt");
            while (getline(file, line))
            {
                if (line == "")
                {
                    pointer_location = file.tellg();    // Stores the location of the get pointer

                }
                else if (line == ("train number: " + to_string(train.number)))
                {
                    file.seekg(pointer_location, ios::beg);   // Changes the location of the get pointer to start reading from the train's id

                    while (getline(file, line)) {
                        cout << "\t\t" << line << endl;
                        if (line == "")
                        {
                            exist = true;
                            break;
                        }
                    }
                }
            }
            if (!exist)
            {
                cout << "\t\tTrain does not exist\n\n\n";
            }
            file.close();

            cout << "\t\tPress any key to continue\n";
            cout << "\t\t\t";
            _getch();
            break;
        }
        case 2:
        {
            cout << "\t\tEnter train name to search: ";
            cin.ignore();
            getline(cin, train.name);
            bool exist = false;

            // Opening file to search
            file.open("train_schedule.txt", ios::in);
            while (getline(file, line))
            {
                if (line == "")
                {
                    pointer_location = file.tellg();    // Stores the location of the get pointer

                }
                if (line == ("train name: " + train.name)) {
                    file.seekg(pointer_location, ios::beg);

                    while (getline(file, line)) {
                        cout << "\t\t" << line << endl;
                        if (line == "")
                        {
                            exist = true;
                            break;
                        }
                    }
                }
            }
            if (!exist)
            {
                cout << "\t\tTrain does not exist\n\n\n";
            }
            file.close();

            cout << "\t\tPress any key to continue\n";
            cout << "\t\t\t";
            _getch();
            break;
        }
        case 3:
        {
            return;
        }
        }
    }
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
        cout << "\n\n\n";
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
            cin.ignore();

            cout << "\t\tEnter train name: ";
            getline(cin, train.name);

            cout << "\t\tEnter train availability: ";
            getline(cin, train.availability);

            // Storing the new train in file
            add.open("train_schedule.txt", ios::app);
            if (add.is_open())
            {
                add << "train ID: " << train.ID;
                add << endl << "train number: " << train.number;
                add << endl << "train name: " << train.name;
                add << endl << "train availability: " << train.availability;
                add << endl << endl;
                cout << "\t\t\t\t\n\n" << "Train added successfully" << endl;
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

            cout << "\t\tEnter train ID to modify: ";
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
            cin.ignore();
            cout << "\t\tEnter Trian's availability: ";
            getline(cin, train.availability);



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
                        temp << endl;
                    }
                    else
                    {
                        temp << line << endl;
                    }

                }

                display.close();
                temp.close();
                cout << "\t\t\t\n\n\n Train modified succesfully\n\n\n";

                remove("train_schedule.txt");
                rename("new_train_schedule.txt", "train_schedule.txt");
            }
            else
            {
                cout << "\t\tError reading trains data from file!\n";
            }
            cout << "\t\tPress any key to continue\n";
            cout << "\t\t\t";
            _getch();
        }
        else if (choice == '4')
        {   // Delete train
            system("cls");

            cout << "\t\tEnter train ID to delete: ";

            cin >> train.ID;


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

                else    // The train exists, so it will be deleted
                {
                    // Resetting the stream pointer to start reading from the beggining of the file

                    display.close();

                    display.open("train_schedule.txt");
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
                    cout << "\n\n\t\t\t Train deleted succesfully\n\n\n";
                    remove("train_schedule.txt");
                    rename("new_train_schedule.txt", "train_schedule.txt");
                }


            }
            else
            {
                cout << "\t\tError reading trains data from file!\n";
            }

            cout << "\t\tPress any key to continue\n";
            cout << "\t\t\t";
            _getch();

        }

        else if (choice == '5')
        {   // Back to dashboard
            break;
        }

    }
}

void view_previous_trips()
{
    system("cls");  // Clears the terminal screen before printing again

    // Reading variable
    string userID, ticketID, start, dest, seats, price;

    ifstream trips;
    trips.open("reservedTickets.txt");

    if (trips.is_open())
    {
        cout << left;
        cout << setw(16) << "User ID";
        cout << setw(16) << "Ticket ID";
        cout << setw(20) << "Start Location";
        cout << setw(20) << "Dest Location";
        cout << setw(12) << "Seats";
        cout << setw(5) << "Price\n";
        cout << "-----------------------------------------------------------------------------------------\n\n";
        while (trips >> userID >> ticketID >> start >> dest >> seats >> price)
        {
            if (userID == user.ID)
            {
                cout << left;
                cout << setw(16) << userID;
                cout << setw(16) << ticketID;
                cout << setw(20) << start;
                cout << setw(20) << dest;
                cout << setw(12) << seats;
                cout << setw(5) << price << endl;
            }
        }
        trips.close();
    }

    cout << "\n\n\nPress any key to continue!\n";
    _getch();
}

void update_user_data()
{
    // Reading variables
    ifstream user_data;
    string id, name, line;
    user_data.open("UserData.txt");
    if (user_data.is_open())
    {
        while (getline(user_data, id))
        {
            getline(user_data, user.Name);
            user_data >> user.Age;
            getline(user_data,user.Phone);
            getline(user_data,user.Email);
            getline(user_data,user.Address);
            getline(user_data,user.gender);
            getline(user_data, line);
            if (id == user.ID)
            {
                break;
            }
        }
    }
    else
    {
        cout << "\t\tError reading user's data\n\n\n";
        cout << "\t\tPress any key to continue!\n";
        cout << "\t\t";
        _getch();
    }
    user_data.close();
}

void generate_user_reports(User &user) {
    
    system("cls");

    cout<<"-------------------------------------User Info----------------------------------------"<<endl<<endl;

    cout<<"Name : "<<user.Name<<"\t\t"<<"ID : "<<user.ID<<"\t\t"<<"Phone : "<<user.Phone<<"\t\t"<<"Age : "<<user.Age
    <<"\t\t"<<"Email : "<<user.Email<<"\t\t"<<"Address : "<<user.Address<<"\t\t"<<"Gender : "<<user.gender<<endl<<endl;
    
    
    ifstream file("reservedTickets.txt");

    if (!file.is_open()) {
        cerr << "Unable to open file reservedTickets.txt";
        exit(1);
    }

    const int MAX_USERS = 1000;
    string userIds[MAX_USERS];
    Ticket tickets[MAX_USERS];
    int seats[MAX_USERS];
    int numUsers = 0;

    while (file >> userIds[numUsers] >> tickets[numUsers].ID >> tickets[numUsers].Start_location >> tickets[numUsers].Destination_location >> seats[numUsers]>>tickets[numUsers].Price) {
        numUsers++;
    }

    file.close();

    string id = user.ID;
   
    
   cout<<"--------------------------------Ticket info--------------------------------"<<endl<<endl;
      
    bool found = false;
    for (int i = 0; i < numUsers; i++) {
        if (userIds[i] == id) {

          
            cout << "Ticket ID: " << tickets[i].ID 
           <<"\t\t" <<"Start Location: " << tickets[i].Start_location 
           << "\t\t" << "Destination Location: " << tickets[i].Destination_location 
           <<"\t\t"<<"number of seats : "<<seats[i]<<"\t\t"<< "Price: " << tickets[i].Price << endl<<endl;
            found = true;
            
        }
    }

    if (!found) {
        cout << "No tickets found for user ID: " << id << endl<<endl;
    }

    ifstream payment_file("userPayments.txt");
    if(!payment_file.is_open()){

      cout<<"ERROR opening file userPayments.txt"<<endl;
      exit(1);
    }
    const int MAX_users=1000;
    string User_ID[MAX_users];
    int Usercount=0;
    string payment_method[MAX_users];
    string payment_status[MAX_users];
    string ticket_id;
    while(payment_file>>User_ID[Usercount]>>ticket_id>>payment_method[Usercount]>>payment_status[Usercount]){

      Usercount++;
    }
    bool payment_happened=false;
    cout<<"----------------------Payment Info-------------------------"<<endl<<endl;
    for(int i=0;i<Usercount;i++){
    if(User_ID[i]==id){

        
        cout<<"Payment Method : "<<payment_method[i]<<"\t\t\t"<<"Payment Status : "<<payment_status[i]<<endl;
        payment_happened=true;


    }
    }
    if(!payment_happened){

    cout<<"No Payment has happened"<<endl;
    }

    cout << "\t\tPress any key to continue!\n";
    cout << "\t\t";
    _getch();
}

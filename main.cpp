#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

bool isloggedin()
{
    string username;
    string password;
    string un; //comparison string
    string pw; //comparison string
    cout << "Please Enter The USERNAME : ";
    cin >> username;
    cout << "Please Enter The PASSWORD : ";
    cin >> password;

    fstream read; // fstream reads a file
    read.open("Data.txt", ios::in);
    

    if (!read.is_open()) {
      cout << "Error opening the file";
      read.close();
      exit(1);
    }
    // Check every username and Password in the file 
    while (!read.eof()){
        getline(read, un); //reads the username
        getline(read, pw); //reads the password 
        if (un == username && pw == password) //if both un & username and pw & password are the same -> true
        {
            read.close();
            return true;
        }
    }
    // if the Function didn't return this means that the given username is not in file or the password is wrong
    return false ;
}


struct Train { // to write the information of train
    string ID;
    string name;
    string number;
    bool availability;
};

struct User {  // to write the information of user
    int ID;
    string Name;
    string Phone;
    int Age;
    string Email;
    string Address;
    string Role;
    string gender;
};

struct Ticket {   // to write the information of ticket
    string name ;
    string Start_location ;
    string Destination_location ;
    double Price ;
};

vector<Ticket> Tickets ;

void MangeTicket() {
    while (1){
        // Menu
        cout << endl << "Enter 1 to add new ticket" << endl ;
        cout << "Enter 2 to change ticket" << endl ;
        cout << "Enter 3 to delete ticket" << endl ;
        cout << "Enter any other number to exit" << endl ;
        int choice ;
        cin >> choice ;
        cin.ignore();
        if (choice == 1){
            Ticket NewTicket ;
            bool exist = false ;

            // Taking the Name of the ticket
            string name;
            cout << endl << "Enter the name of the ticket : " ;
            do{
                getline(cin, name);
                // Check if this name Already Exists or it's unique
                for (int i = 0 ; i < Tickets.size() ; i++){ // loop in all tickets i have and if exists -> true
                    if (Tickets[i].name == name){
                        exist = true ;
                        cout << "This name is already exists. Please enter a new one : ";
                        break;
                    }
                }
            } while (exist);
            NewTicket.name = name ;

            // Get start location
            cout << "Enter the start location of the ticket : " ;
            string Start_location ; 
            getline(cin , Start_location) ;
            NewTicket.Start_location = Start_location ;

            // Get destination location
            cout << "Enter the destination location of the ticket : " ;
            string Destination_location ; 
            getline(cin , Destination_location) ;
            NewTicket.Destination_location = Destination_location ;

            // Get Price
            cout << "Enter the price of the ticket : " ;
            double price ; 
            cin >> price ;
            NewTicket.Price = price ;

            // Push the NewTicket in my Tickets
            Tickets.push_back(NewTicket) ;
            cout << endl << endl << "Ticket added successfully!" << endl << endl << endl ;
        }
        else if (choice == 2){
            // if there is no tickets , then i will not be able to change anything
            if (Tickets.size() == 0){
                cout << endl << endl << "There is no tickets to change" << endl << endl << endl ;
                continue;
            }

            // Take the Name of The ticket
            cout << endl << "Enter the name of the ticket you want to change : " ;
            string name ; 
            getline(cin , name) ;
            
            // Check if this name Already Exists and get the index of it
            int index = -1 ; // make index -1 as no index will be -1 so if the index != -1
                            // this means this name is already exits and it's index = i
            while (index == -1){
                // Check
                for (int i = 0 ; i < Tickets.size() ; i ++){ 
                    if (Tickets[i].name == name){
                        index = i ;
                    }
                }
                if (index == -1) { // reinput to be checked again
                    cout << "This name is not exist. Enter a correct one : " ;
                    getline(cin , name) ;
                }
            }
            cout << endl << "Enter the new name of the ticket : " ;
            
            getline(cin , name) ;
            Tickets[index].name = name ;
            
            // Get the new start location
            cout << "Enter the new start location of the ticket : " ;
            string Start_location ; 
            getline(cin , Start_location) ;
            // Changing the old value to the new value
            Tickets[index].Start_location = Start_location ;

            // Get the new destination location
            cout << "Enter the new destination location of the ticket : " ;
            string Destination_location ; 
            getline(cin , Destination_location) ;
            // Changing the old value to the new value
            Tickets[index].Destination_location = Destination_location ;

            // Get the new price
            cout << "Enter the new price of the ticket : " ;
            double price ; cin >> price ;
            // Changing the old value to the new value
            Tickets[index].Price = price ;

            cout << endl << endl << "Ticket changed successfully!" << endl << endl << endl ;
        }
        else if (choice == 3){
            // if there is no tickets , then i will not be able to delete anything
            if (Tickets.size() == 0){
                cout << endl << endl << "There is no tickets to delete" << endl << endl << endl ;
                continue;
            }
            // Take the Name of The ticket
            cout << endl << "Enter the name of the ticket : " ;
            string name ; 
            getline(cin , name) ;
            // Check if this name Already Exists and get the index of it
            int index = -1 ; // make index -1 as no index will be -1 so if the index != -1
                            // this means this name is already exits and it's index = i
            while (index == -1){
                // Check
                for (int i = 0 ; i < Tickets.size() ; i ++){
                    if (Tickets[i].name == name){
                        index = i ;
                    }
                }
                if (index == -1) { // reinput to be checked again
                    cout << "This name is not exist. Enter a correct one : " ;
                    getline(cin , name) ;
                }
            }
            // erasing the ticket with this index
            Tickets.erase(Tickets.begin() + index) ;
            cout << endl << endl << "Ticket deleted successfully!" << endl << endl << endl ;
        }
        else {
            // if the choice any other value -> end the program
            break ;
        }
    }
}


int main()
{
    int choice;
    cout << "\t\t\t _____________________________________________________________________________________________\n\n\n";
    cout << "\t\t\t                                 Welcome to Log in page                                        \n\n\n";
    cout << "\t\t\t ___________________________              MENU              ____________________________________\n\n\n";

    

    while (1){
        cout << endl << "Press 1 to log in." << endl ;
        cout << "Press 2 to MangeTicket." << endl ;
        cout << "Press 0 to end the program." << endl ;
        int choice ;
        cin >> choice ;
        if (choice == 1){
            int check = isloggedin() ;
            int counter = 0;
            while(!check && counter < 4){
                cout << endl << "Wrong password or username." << endl ; 
                cout << "Please enter a correct username and password." << endl << endl;
                check = isloggedin() ;
            }
            if (check)
                cout << endl << "Logged in successfully :D" << endl << endl ;
            else
                cout << "Error entering credentials worng too many times!";
        }
        else if (choice == 2) {
            MangeTicket() ;
        }
        else {
            break ;
        }
    }
}
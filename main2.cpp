#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;


// Structs for Train, User, and Ticket
struct Train {
    int ID;
    string name;
    int number;
    bool availability;
};
struct Ticket {
    int ID;
    string name;
    string Start_location;
    string Destination_location;
    double Price;
};
struct User {
    int ID;
    string Name;
    string Email;
    string Address;
    string Phone;
    string Gender;
    int Age;
    string Role;
    vector<Ticket>booked_tickets; // to store all the booked ticketsfor the user and store it in the user report.

};
vector<User> user_reports; // to store all data about the user including tickets booked and all action he does in the program.
User* loggedInUser = nullptr; // Pointer to the logged in user , when the user log in you must set this pointer to point to the logged in user. 


// Functions for passengers
void login() {
   
}



void logout() {
    // Set the logged in user to nullptr again because there will be no users logged in after we log out.
    loggedInUser = nullptr;

    cout << "You have been logged out.\n";
}

void signup() {
    // Implement signup function
}

void searchTrains() {
    // Implement train search function
}

void bookTickets() {
    // Implement ticket booking function
}

void makePayment() {
    // Implement payment function
}

void cancelBooking() {
    // Implement booking cancellation functiona
}

void viewPreviousTrips() {
    // Implement function to view previous trips
}

// Functions for admins
void manageTrainSchedule() {
    // Implement function to manage train schedule
}

void manageUserAccounts() {
    // Implement function to manage user accounts
}

void manageTicketPrices() {
    // Implement function to manage ticket prices
}

void managePayment() {
    // Implement function to manage payment
}
void generateUserReport(int userID) {
    // Find the user
    for (int i = 0; i < user_reports.size(); i++) {
        if (user_reports[i].ID == userID) {
            cout << "User Report for " << user_reports[i].Name << ":\n";
            cout << "Email: " << user_reports[i].Email << "\n";
            cout << "Address: " << user_reports[i].Address << "\n";
            cout << "Phone: " << user_reports[i].Phone << "\n";
            cout << "Gender: " << user_reports[i].Gender << "\n";
            cout << "Age: " << user_reports[i].Age << "\n";
            cout << "Role: " << user_reports[i].Role << "\n";

            // Print all tickets for this user
            for (int j = 0; j < user_reports[i].booked_tickets.size(); j++) {
                cout << "Ticket Name: " << user_reports[i].booked_tickets[j].name << "\n";
                cout << "Start Location: " << user_reports[i].booked_tickets[j].Start_location << "\n";
                cout << "Destination Location: " << user_reports[i].booked_tickets[j].Destination_location << "\n";
                cout << "Price: " << user_reports[i].booked_tickets[j].Price << "\n";
            }
            break;
        }
    }
}

int main() {
    // Implement the main program
    return 0;
}

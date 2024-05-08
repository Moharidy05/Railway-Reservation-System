#include <iostream>
#include <fstream>
#include <string>
#include<cstdlib>
#include <conio.h>
using namespace std;

struct Ticket {
    int ID;
    string Start_location;
    string Destination_location;
    float Price;
};

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

int main(){
       
       User user;
       user.ID=920;
       user.Name="Abdullrahman";
       user.Age=  20;
       user.Phone= "011985986774";
       user.Email= "abdo89_@outlook.com";
       user.Address="Al-kanater Al-Khairiya";
      user.gender="male";

      generate_user_reports(user);    

}
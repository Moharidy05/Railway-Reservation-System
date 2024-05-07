#include <iostream>
#include <fstream>
#include <string>
#include<cstdlib>
using namespace std;

struct Ticket {
    int id;
    string start_location;
    string destination_location;
    int price;
};
struct User {  // to write the information of user
    int ID;
    string Name;
    string Phone;
    int Age;
    string Email;
    string Address;
    string Role;        // Passenger or Admin
    string gender;
    };

void generate_user_reports(User &user) {
    
    system("cls");
    cout<<"-------------------------------------User Info----------------------------------------"<<endl<<endl;

    cout<<"Name : "<<user.Name<<"\t\t"<<"ID : "<<user.ID<<"\t\t"<<"Phone : "<<user.Phone<<"\t\t"<<"Age : "<<user.Age
    <<"\t\t"<<"Email : "<<user.Email<<"\t\t"<<"Address : "<<user.Address<<"Role : "<<user.Role<<"\t\t"<<"Gender : "<<user.gender<<endl<<endl;
    
    
    ifstream file("ticket.txt");

    if (!file.is_open()) {
        cerr << "Unable to open file tickets.txt";
        exit(1);
    }

    const int MAX_USERS = 1000;
    int userIds[MAX_USERS];
    Ticket tickets[MAX_USERS];
    int seats[MAX_USERS];
    int numUsers = 0;

    while (file >> userIds[numUsers] >> tickets[numUsers].id >> tickets[numUsers].start_location >> tickets[numUsers].destination_location >> seats[numUsers]>>tickets[numUsers].price) {
        numUsers++;
    }

    file.close();

    int id=user.ID;
   
    
   cout<<"--------------------------------TIcket info--------------------------------"<<endl<<endl;
      
    bool found = false;
    for (int i = 0; i < numUsers; i++) {
        if (userIds[i] == id) {

          
            cout << "Ticket ID: " << tickets[i].id 
           <<"\t\t" <<"Start Location: " << tickets[i].start_location 
           << "\t\t" << "Destination Location: " << tickets[i].destination_location 
           <<"\t\t"<<"number of seats : "<<seats[i]<<"\t\t"<< "Price: " << tickets[i].price << endl<<endl;
            found = true;
            
        }
    }

    if (!found) {
        cout << "No tickets found for user ID: " << id << endl<<endl;
    }

    ifstream payment_file("payments.txt");
    if(!payment_file.is_open()){

      cout<<"ERROR opening payment file"<<endl;
      exit(1);
    }
    const int MAX_users=1000;
    int User_ID[MAX_users];
    int Usercount=0;
    string payment_method[MAX_users];
    string payment_status[MAX_users];
    while(payment_file>>User_ID[Usercount]>>payment_method[Usercount]>>payment_status[Usercount]){

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
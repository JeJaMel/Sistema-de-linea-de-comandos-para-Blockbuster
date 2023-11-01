#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>
#include <iomanip>

using namespace std;

struct client
{
    int account_name;
    char cedula[50];
    char email[50];
    char country[50];
};

struct movie
{
    int id;
    char title[50];
    char genre[50];
    char duration[50];
    char director[50];
    char release_date[50];
    char rent_to[50];
    char rent_on[50];
    char status[50];

};

void displayMenu(){
    cout<<"1. Search a movie."<<endl;
    cout<<"2. Consult status of the movie."<<endl;
    cout<<"3. Rent a movie."<<endl;
    cout<<"4. Add a movie."<<endl;
    cout<<"5. Search a client."<<endl;
    cout<<"6. Exit."<<endl;
    cout<<"Select an option: ";
}


int main () {  

int Selection;

string MyFilePath = "Movies.csv";
ifstream MovieData;

MovieData.open(MyFilePath);
if(!MovieData.is_open()){
    cout<<"No se pudo abrir el archivo "<<MyFilePath<<endl;
    return 1;
}

    cout<<"\n ╠═════════════════════════════════╣ BLOCKBUSTER ╠════════════════════════════════╣"<<endl;
    cout<<"       Welcome to Blockbuster technical terminal, please select an option below\n"<<endl;

while(true){
displayMenu();
cin>>Selection;

switch(Selection){
case 1:

    break;
case 2:

    break;
case 3:

    break;
case 4:

    break;
case 5:

    break;
case 6:
    cout<<"Thank you for using Blockbuster. Goodbye!"<<endl;
        return 0;
    break;

default:
    cout<<"Please select a valid option"<<endl;
        return 1;
}


}

return 0;
}
#include "client.h"
#include "SearchAndDisplay.h"

bool deleteClient(const string &filename, int targetId)
{
    fstream file(filename, ios::in | ios::out | ios::binary);

    if (!file.is_open())
    {
        cerr << "Error opening the file" << endl;
        return false;
    }

    client c;
    stringstream updatedContent;

    while (file.read(reinterpret_cast<char *>(&c), sizeof(client)))
    {
        if (c.cedula != targetId)
        {

            updatedContent.write(reinterpret_cast<const char *>(&c), sizeof(client));
        }
    }

    file.close();

    file.open(filename, ios::out | ios::trunc | ios::binary);
    if (!file.is_open())
    {
        cerr << "Error opening the file for writing" << endl;
        return false;
    }

    file.write(updatedContent.str().c_str(), updatedContent.str().size());

    file.close();

    cout << "Client deleted successfully!" << endl;
    return true;
}
void WriteClientData(const string &filename, const client &c)
{
    ofstream clientFile(filename, ios::binary | ios::app);
    if (!clientFile.is_open())
    {
        cout << "Unable to open the file" << endl;
        return;
    }

    clientFile.write(reinterpret_cast<const char *>(&c), sizeof(client));
    clientFile.close();
}
bool searchClientById(const string &filename, int targetId, client &foundClient)
{
    ifstream clientFile(filename, ios::binary);

    if (!clientFile.is_open())
    {
        cout << "Unable to open the file" << endl;
        return false;
    }

    while (clientFile.read(reinterpret_cast<char *>(&foundClient), sizeof(client)))
    {
        if (foundClient.cedula == targetId)
        {
            clientFile.close();
            return true;
        }
    }

    clientFile.close();
    return false;
}
bool searchClientByEmail(const string &filename, const string &targetEmail, client &foundClient)
{
    ifstream clientFile(filename, ios::binary);

    if (!clientFile.is_open())
    {
        cout << "Unable to open the file" << endl;
        return false;
    }

    while (clientFile.read(reinterpret_cast<char *>(&foundClient), sizeof(client)))
    {
        if (strcmp(foundClient.email, targetEmail.c_str()) == 0)
        {
            clientFile.close();
            return true;
        }
    }

    clientFile.close();
    return false;
}
bool searchClientByPhoneNumber(const string &filename, int targetPhoneNumber, client &foundClient)
{
    ifstream clientFile(filename, ios::binary);

    if (!clientFile.is_open())
    {
        cout << "Unable to open the file" << endl;
        return false;
    }

    while (clientFile.read(reinterpret_cast<char *>(&foundClient), sizeof(client)))
    {
        if (foundClient.PhoneNumber == targetPhoneNumber)
        {
            clientFile.close();
            return true;
        }
    }

    clientFile.close();
    return false;
}
bool searchClientByAccountName(const string &filename, const string &targetAccountName, client &foundClient)
{
    ifstream clientFile(filename, ios::binary);

    if (!clientFile.is_open())
    {
        cout << "Unable to open the file" << endl;
        return false;
    }

    while (clientFile.read(reinterpret_cast<char *>(&foundClient), sizeof(client)))
    {
        if (strcmp(foundClient.account_name, targetAccountName.c_str()) == 0)
        {
            clientFile.close();
            return true;
        }
    }

    clientFile.close();
    return false;
}
void deleteClientCase(movie catalog[], int catalogSize)
{
    int targetClientId;
    cout << "\nEnter the cedula of the client you want to delete: ";
    cin >> targetClientId;

    client targetClient;
    if (searchClientById("src/clientData.bin", targetClientId, targetClient))
    {
        ReadMovieData("src/rentedMovies.csv", catalog, catalogSize);

        bool hasRentedMovies = false;
        string targetAccountName = targetClient.account_name;

        for (int i = 0; i < catalogSize; i++)
        {
            client rentedClient;
            if (searchClientByAccountName("src/clientData.bin", catalog[i].rent_to, rentedClient))
            {
                if (rentedClient.cedula == targetClientId)
                {
                    cout << "Client has a rented movie. Please return the movie before deleting the client." << endl;
                    hasRentedMovies = true;
                    break;
                }
            }
        }

        if (!hasRentedMovies)
        {
            if (deleteClient("src/clientData.bin", targetClientId))
            {
                cout << "\n"
                     << endl;
            }
            else
            {
                cout << "Error deleting client." << endl;
            }
        }
    }
    else
    {
        cout << "Client not found." << endl;
    }
}

void displayClientAndHistory(const client &foundClient, movie catalog[], int catalogSize)
{
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "Account Name: " << foundClient.account_name << endl;
    cout << "Cedula: " << foundClient.cedula << endl;
    cout << "Email: " << foundClient.email << endl;
    cout << "Phone Number: " << foundClient.PhoneNumber << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "History:\n";

    bool clientFound = false;

    for (int i = 0; i < catalogSize; i++)
    {
        if (foundClient.account_name == catalog[i].rent_to)
        {
            clientFound = true;
            cout << "Movie: " << catalog[i].title << " rented on: " << catalog[i].rent_on << endl;
        }
    }

    if (!clientFound)
    {
        cout << "No rental history found." << endl;
    }
}

void searchClientCase(movie catalog[], int catalogSize)
{
    int selectSearchMethod;
    cout << "\n1. Search client by id" << endl;
    cout << "2. Search client by email" << endl;
    cout << "3. Search client by Phone number" << endl;
    cin >> selectSearchMethod;

    switch (selectSearchMethod)
    {
    case 1:
    {
        int clientIdToSearch;
        client foundClientById;

        cout << "Enter client id: ";
        cin >> clientIdToSearch;

        if (searchClientById("src/clientData.bin", clientIdToSearch, foundClientById))
        {
            cout << "\nClient found by ID:" << endl;
            displayClientAndHistory(foundClientById, catalog, catalogSize);
        }
        else
        {
            cout << "Client not found by ID" << endl;
        }
        break;
    }

    case 2:
    {
        string clientMailToSearch;
        client foundClientByMail;

        cout << "Enter client email: ";
        cin >> clientMailToSearch;

        if (searchClientByEmail("src/clientData.bin", clientMailToSearch, foundClientByMail))
        {
            cout << "\nClient found by Mail:" << endl;
            displayClientAndHistory(foundClientByMail, catalog, catalogSize);
        }
        else
        {
            cout << "Client not found by Mail" << endl;
        }
        break;
    }

    case 3:
    {
        int clientPhoneNumberToSearch;
        client foundClientByPhoneNumber;

        cout << "Enter client Phone number: ";
        cin >> clientPhoneNumberToSearch;

        if (searchClientByPhoneNumber("src/clientData.bin", clientPhoneNumberToSearch, foundClientByPhoneNumber))
        {
            cout << "\nClient found by Phone number:" << endl;
            displayClientAndHistory(foundClientByPhoneNumber, catalog, catalogSize);
        }
        else
        {
            cout << "Client not found by Phone number" << endl;
        }
        break;
    }

    default:
        cout << "Invalid option" << endl;
        break;
    }
}

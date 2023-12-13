#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <string>
#include <time.h>
#include <cstdio>

using namespace std;

struct client
{
    char account_name[50];
    int cedula;
    char email[50];
    int PhoneNumber;
};

struct movie
{
    int id;
    char title[50];
    char genre[50];
    int duration;
    char directorFirstName[50];
    char directorLastName[50];
    double price;
    char release_date[50];
    char rent_to[50];
    char rent_on[50];
    char status[50];
};

movie getDataFromUser();

void mergeSort(movie arr[], int size, const char *sortBy, bool ascending = true);
void merge(movie arr[], movie left[], movie right[], int left_size, int right_size, const char *sortBy, bool ascending);
void mergeByReleaseDate(movie arr[], movie left[], movie right[], int left_size, int right_size, bool ascending);

void displayMenu();
void FilterMovieData();
bool isValidDate(const string &date);
void SortMovieData(movie catalog[], int catalogSize);
int GetLastMovieId(const string &filename);
void ReadMovieData(const string &filename, movie catalog[], int &catalogSize);

void WriteMovieData(const string &filename, const movie &rentedMovie);
void RentMovie(movie catalog[], int catalogSize, client &c);
void deleteMovie(const string &filename, int movieId);
bool deleteClient(const string &filename, int targetId);

void WriteClientData(const string &filename, const client &c);
bool searchClientById(const string &filename, int targetId, client &foundClient);
bool searchClientByEmail(const string &filename, const string &targetEmail, client &foundClient);
bool searchClientByPhoneNumber(const string &filename, int targetPhoneNumber, client &foundClient);
bool searchClientByAccountName(const string &filename, const string &targetAccountName, client &foundClient);

void DisplayAvailableMovies(const movie catalog[], int catalogSize);
void DisplayRentedMovies(const movie movies[], int size);
void DisplayMovieGenre(const movie movies[], int size);
void DisplayMovieDuration(const movie &singleMovie);
void DisplayMovieDirector(const movie movies[], int size);
void DisplayMoviePrice(const movie movies[], int size);
void DisplayMovieReleaseDate(const movie movies[], int size);

void SearchAndDisplayByGenre(const movie catalog[], int catalogSize, const char *userGenre);
void SearchAndDisplayByDuration(const movie catalog[], int catalogSize, int durationCategory);
void SearchAndDisplayByReleaseDate(movie catalog[], int catalogSize, const char *releaseYear);
void SearchAndDisplayById(const movie catalog[], int catalogSize, int user_id);
void SearchAndDisplayByPriceRange(movie catalog[], int catalogSize, double minPrice, double maxPrice);
void SearchAndDisplayByDirectorFirstName(const movie catalog[], int catalogSize, const char *directorFirstName);

int main()
{
    const int MaxCatalogSize = 2000;
    movie catalog[MaxCatalogSize];

    int catalogSize;
    int Selection;
    char genre[50];
    char movieGenre[50];
    char duration;
    char director[50];
    char year[50];
    char price[50];
    int clientIdToSearch;
    string clientMailToSearch;
    int clientPhoneNumberToSearch;
    int durationOption;
    int movieIdToCheck;
    int LastID = GetLastMovieId("Movies.csv");

    movie oneMovie, twoMovie;
    string idOrName;
    client foundClientById;
    client foundClientByMail;
    client foundClientByPhoneNumber;

    int movieIdToDelete;

    string confirm;

    time_t now = time(0);
    struct tm *ltm = localtime(&now);

    char actualDate[11];
    strftime(actualDate, sizeof(actualDate), "%d-%m-%Y", ltm);

    ifstream checkFile("rentedMovies.csv");
    if (!checkFile.is_open())
    {
        ofstream createFile("rentedMovies.csv");
        if (createFile.is_open())
        {
            createFile << "id;movie;genre;duration;director;price;release_date;rent_to;rent_on;status\n";
            createFile.close();
        }

        else
        {
            cout << "Error creating 'rentedMovies.csv' file." << endl;
            return 1;
        }
    }

    fstream Archive;

    cout
        << "\n ╠═════════════════════════════════╣ BLOCKBUSTER ╠════════════════════════════════╣" << endl;
    cout << "       Welcome to Blockbuster technical terminal, press any key to continue"
         << endl;
    string anykey1;
    cin >> anykey1;

    int movieId;
    bool running = true;
    bool movieFound;
    bool movieAlreadyRented;
    bool movieFoundToCheck = false;
    bool movieFoundToCheck2 = false;
    bool movieFound2 = false;

    while (running)
    {
        displayMenu();
        cin >> Selection;

        switch (Selection)
        {
        case 1:

            int searchOption;
            cout << "\nSelect search option:\n";
            cout << "1. Search by genre\n";
            cout << "2. Search by duration\n";
            cout << "3. Search by director\n";
            cout << "4. Search by release date\n";
            cout << "5. search by price\n";
            cout << "6. Search by rented status\n";
            cout << "Enter option: ";
            cin >> searchOption;

            switch (searchOption)
            {
            case 1:

                ReadMovieData("Movies.csv", catalog, catalogSize);

                cout << "\nWhich genre do you want to search?\n\n";
                cout << "|Action| |Adventure| |Animation| |Children| |Comedy| |Crime| \n";
                cout << "|Documentary| |Drama|  |Fantasy| |Film-Noir| |Horror| |musical|\n";
                cout << "|Mystery| |Romance| |Sci-Fi| |Thriller| |War| |Western|\n\n";
                cout << "Enter genre: ";
                cin >> genre;

                transform(genre, genre + strlen(genre), genre, ::tolower);

                SearchAndDisplayByGenre(catalog, catalogSize, genre);

                break;
            case 2:

                ReadMovieData("Movies.csv", catalog, catalogSize);

                cout << "\nWhich duration category do you want to search?\n";
                cout << "1. Short (less than 2 hours)\n";
                cout << "2. Medium (2 to 3 hours)\n";
                cout << "3. Long (more than 3 hours)\n";
                cout << "Enter option: ";
                cin >> durationOption;

                SearchAndDisplayByDuration(catalog, catalogSize, durationOption);

                break;

            case 3:
                ReadMovieData("Movies.csv", catalog, catalogSize);

                cout << "Which director's first name do you want to search?\n\n";
                cout << "Enter director's first name: ";
                cin >> director;

                SearchAndDisplayByDirectorFirstName(catalog, catalogSize, director);

                break;

            case 4:
                int dateFilterOption;
                cout << "\nSelect date filter option:\n";
                cout << "1. Filter movies released in 2022\n";
                cout << "2. Filter movies released in 2023\n";
                cout << "3. Filter older movies\n";
                cout << "4. Filter newer movies\n";
                cout << "Enter option: ";
                cin >> dateFilterOption;

                ReadMovieData("Movies.csv", catalog, catalogSize);

                switch (dateFilterOption)
                {
                case 1:
                    SearchAndDisplayByReleaseDate(catalog, catalogSize, "2022");
                    break;
                case 2:
                    SearchAndDisplayByReleaseDate(catalog, catalogSize, "2023");
                    break;
                case 3:

                    mergeSort(catalog, catalogSize, "release_date");
                    DisplayMovieReleaseDate(catalog, catalogSize);
                    break;
                case 4:

                    mergeSort(catalog, catalogSize, "release_date", false);
                    DisplayMovieReleaseDate(catalog, catalogSize);
                    break;
                default:
                    cout << "Invalid date filter option" << endl;
                    break;
                }
                break;

            case 5:
                double minPrice, maxPrice;
                cout << "Enter the minimum price: ";
                cin >> minPrice;
                cout << "Enter the maximum price: ";
                cin >> maxPrice;

                ReadMovieData("Movies.csv", catalog, catalogSize);
                SearchAndDisplayByPriceRange(catalog, catalogSize, minPrice, maxPrice);
                break;

            case 6:

                int Option;
                cout << "\n1. search available movies\n";
                cout << "2. search rented movies\n ";
                cout << "Enter option: ";
                cin >> Option;

                if (Option == 1)
                {
                    ReadMovieData("Movies.csv", catalog, catalogSize);
                    DisplayAvailableMovies(catalog, catalogSize);
                }
                else if (Option == 2)
                {
                    ReadMovieData("rentedMovies.csv", catalog, catalogSize);
                    DisplayRentedMovies(catalog, catalogSize);
                }

                break;

            default:
                cout << "Invalid search option" << endl;
                break;
            }

            break;

        case 2:
            cout << "Enter the ID of the movie you want to check: ";
            cin >> movieIdToCheck;

            ReadMovieData("rentedMovies.csv", catalog, catalogSize);

            for (int i = 0; i < catalogSize; i++)
            {
                if (catalog[i].id == movieIdToCheck)
                {
                    movieFoundToCheck = true;
                    cout << "---------------------------------------------------------------------------" << endl;
                    cout << "Movie Title: " << catalog[i].title;
                    cout << "\nStatus: " << catalog[i].status;
                    cout << "\nRented to: " << catalog[i].rent_to;
                    cout << "\nRented on: " << catalog[i].rent_on;
                    cout << "\n---------------------------------------------------------------------------" << endl;
                    break;
                }
            }

            if (!movieFoundToCheck)
            {
                ReadMovieData("Movies.csv", catalog, catalogSize);

                for (int j = 0; j < catalogSize; j++)
                {
                    if (catalog[j].id == movieIdToCheck)
                    {
                        movieFoundToCheck2 = true;
                        cout << "---------------------------------------------------------------------------" << endl;
                        cout << "Movie Title: " << catalog[j].title;
                        cout << "\nStatus: Available";
                        cout << "\nRented to: -------" << catalog[j].rent_to;
                        cout << "\nRented on: -------" << catalog[j].rent_on;
                        cout << "\n---------------------------------------------------------------------------" << endl;
                        break;
                    }
                }
            }

            if (!movieFoundToCheck && !movieFoundToCheck2)
            {
                cout << "Movie not found" << endl;
            }
            break;

        case 3:
            movieFound = false;
            int foundIndex;
            foundIndex = -1;
            client c;
            movie rentedMovie;

            cout << "Enter the ID of the movie you want to rent: ";
            cin >> movieId;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            ReadMovieData("rentedMovies.csv", catalog, catalogSize);
            for (int i = 0; i < catalogSize; i++)
            {
                if (catalog[i].id == movieId)
                {
                    cout << "The movie " << catalog[i].title << " is already rented" << endl;
                    movieAlreadyRented = true;
                    break;
                }
            }

            if (!movieAlreadyRented)
            {

                ReadMovieData("Movies.csv", catalog, catalogSize);
                for (int i = 0; i < catalogSize; i++)
                {
                    if (catalog[i].id == movieId)
                    {
                        movieFound = true;
                        rentedMovie = catalog[i];
                        foundIndex = i;
                        break;
                    }
                }

                if (movieFound)
                {

                    cout << "Enter your account name: ";
                    cin.getline(c.account_name, sizeof(c.account_name));

                    cout << "Enter your cédula: ";
                    cin >> c.cedula;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Enter your email: ";
                    cin.getline(c.email, sizeof(c.email));

                    cout << "Enter your Phone number: ";
                    cin >> c.PhoneNumber;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    strcpy(catalog[foundIndex].status, "Rented");
                    strcpy(catalog[foundIndex].rent_on, actualDate);
                    strcpy(catalog[foundIndex].rent_to, c.account_name);

                    WriteMovieData("rentedMovies.csv", catalog[foundIndex]);

                    cout << "\nThe movie '" << catalog[foundIndex].title << "' has been rented to " << c.account_name << endl;
                }

                WriteClientData("clientData.bin", c);
            }
            break;

        case 4:
            ReadMovieData("Movies.csv", catalog, catalogSize);

            oneMovie = getDataFromUser();
            oneMovie.id = LastID + 1;

            if (catalogSize < MaxCatalogSize)
            {
                catalogSize++;
                catalog[catalogSize - 1] = oneMovie;

                WriteMovieData("Movies.csv", oneMovie);
                cout << "\nMovie added successfully!" << endl;
            }
            else
            {
                cout << "List is full" << endl;
            }

            break;

        case 5:
            int selectSearchMethod;
            cout << "\n1. Search client by id" << endl;
            cout << "2. Search client by email" << endl;
            cout << "3. Search client by Phone number" << endl;
            cin >> selectSearchMethod;

            if (selectSearchMethod == 1)
            {

                cout << "Enter client id: ";
                cin >> clientIdToSearch;

                if (searchClientById("clientData.bin", clientIdToSearch, foundClientById))
                {
                    cout << "\nClient found by ID:" << endl;
                    cout << "---------------------------------------------------------------------------" << endl;
                    cout << "Account Name: " << foundClientById.account_name << endl;
                    cout << "Cedula: " << foundClientById.cedula << endl;
                    cout << "Email: " << foundClientById.email << endl;
                    cout << "Phone Number: " << foundClientById.PhoneNumber << endl;
                    cout << "---------------------------------------------------------------------------" << endl;
                }
                else
                {
                    cout << "Client not found by ID" << endl;
                }
            }

            else if (selectSearchMethod == 2)
            {

                cout << "Enter client email: ";
                cin >> clientMailToSearch;

                if (searchClientByEmail("clientData.bin", clientMailToSearch, foundClientByMail))
                {

                    cout << "\nClient found by Mail:" << endl;
                    cout << "---------------------------------------------------------------------------" << endl;
                    cout << "Account Name: " << foundClientById.account_name << endl;
                    cout << "Cedula: " << foundClientById.cedula << endl;
                    cout << "Email: " << foundClientById.email << endl;
                    cout << "Phone Number: " << foundClientById.PhoneNumber << endl;
                    cout << "---------------------------------------------------------------------------" << endl;
                }
                else
                {
                    cout << "Client not found by Mail" << endl;
                }
            }

            else if (selectSearchMethod == 3)
            {

                cout << "Enter client Phone number: ";
                cin >> clientPhoneNumberToSearch;

                if (searchClientByPhoneNumber("clientData.bin", clientPhoneNumberToSearch, foundClientByPhoneNumber))
                {
                    cout << "\nClient found by Phone number:" << endl;
                    cout << "---------------------------------------------------------------------------" << endl;
                    cout << "Account Name: " << foundClientById.account_name << endl;
                    cout << "Cedula: " << foundClientById.cedula << endl;
                    cout << "Email: " << foundClientById.email << endl;
                    cout << "Phone Number: " << foundClientById.PhoneNumber << endl;
                    cout << "---------------------------------------------------------------------------" << endl;
                }
                else
                {
                    cout << "Client not found by Phone number" << endl;
                }
            }
            else
                cout << "Invalid option" << endl;

            break;
        case 6:

            ReadMovieData("rentedMovies.csv", catalog, catalogSize);
            cout << "Enter the ID of the movie you want to return: ";
            cin >> movieIdToDelete;

            for (int i = 0; i < catalogSize; i++)
            {
                if (movieIdToDelete == catalog[i].id)
                {
                    movieFound2 = true;

                    cout << "Are you sure you want to return this movie? (Y/N): ";
                    cin >> confirm;

                    if (confirm == "Y" || confirm == "y")
                    {
                        deleteMovie("rentedMovies.csv", movieIdToDelete);
                        cout << "Movie returned successfully!" << endl;
                    }
                    else
                    {
                        cout << "Operation cancelled." << endl;
                    }

                    break;
                }
            }

            if (!movieFound2)
            {
                cout << "Movie not found." << endl;
            }

            break;

        case 7:

            ReadMovieData("movies.csv", catalog, catalogSize);
            cout << "Enter the ID of the movie you want to Delete: ";
            cin >> movieIdToDelete;

            for (int i = 0; i < catalogSize; i++)
            {
                if (movieIdToDelete == catalog[i].id)
                {
                    movieFound2 = true;

                    cout << "Are you sure you want to Delete this movie?, this action cannot be undone... (Y/N): ";
                    cin >> confirm;

                    if (confirm == "Y" || confirm == "y")
                    {
                        deleteMovie("movies.csv", movieIdToDelete);
                        cout << "Movie Deleted successfully!" << endl;
                    }
                    else
                    {
                        cout << "Operation cancelled." << endl;
                    }

                    break;
                }
            }

            if (!movieFound2)
            {
                cout << "Movie not found." << endl;
            }

            break;

        case 8:

            int targetClientId;
            cout << "\nEnter the cedula of the client you want to delete: ";
            cin >> targetClientId;

            client targetClient;
            if (searchClientById("clientData.bin", targetClientId, targetClient))
            {
                ReadMovieData("rentedMovies.csv", catalog, catalogSize);

                bool hasRentedMovies = false;
                string targetAccountName = targetClient.account_name;

                for (int i = 0; i < catalogSize; i++)
                {
                    client rentedClient;
                    if (searchClientByAccountName("clientData.bin", catalog[i].rent_to, rentedClient))
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

                    if (deleteClient("clientData.bin", targetClientId))
                    {
                        cout << "Client deleted successfully!" << endl;
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
            break;

        case 9:

            return 0;

            break;
        }
    }
}

void displayMenu()
{
    cout << "\nPlease select an option below:(1-6)\n"
         << endl;
    cout << "1. Search a movie." << endl;
    cout << "2. Check status of a movie." << endl;
    cout << "3. Rent a movie." << endl;
    cout << "4. Add a movie." << endl;
    cout << "5. Search a client." << endl;
    cout << "6. Return a movie." << endl;
    cout << "7. Delete a movie." << endl;
    cout << "8. Delete a client." << endl;
    cout << "9. Exit." << endl;
    cout << "Select an option: ";
}

void FlterMovieData(int filterOption)
{
    cout << "\nHow do you want to filter the movies?\n\n";
    cout << "1. filter by price\n";
    cout << "2. filter by duration\n";
    cout << "4. filter by release date\n";
    cout << "5. filter by id\n";
    cout << "Select an option: ";
    cin >> filterOption;
}

void merge(movie arr[], movie left[], movie right[], int left_size, int right_size, const char *sortBy, bool ascending)
{
    int i = 0, j = 0, k = 0;

    while (i < left_size && j < right_size)
    {
        if (strcmp(sortBy, "release_date") == 0)
        {
            if (ascending)
            {
                if (strcmp(left[i].release_date, right[j].release_date) <= 0)
                {
                    arr[k++] = left[i++];
                }
                else
                {
                    arr[k++] = right[j++];
                }
            }
            else
            {
                if (strcmp(left[i].release_date, right[j].release_date) >= 0)
                {
                    arr[k++] = left[i++];
                }
                else
                {
                    arr[k++] = right[j++];
                }
            }
        }
    }

    while (i < left_size)
    {
        arr[k++] = left[i++];
    }

    while (j < right_size)
    {
        arr[k++] = right[j++];
    }
}
void mergeSort(movie arr[], int size, const char *sortBy, bool ascending)
{
    if (size <= 1)
    {
        return;
    }

    int mid = size / 2;
    movie *left = new movie[mid];
    movie *right = new movie[size - mid];

    for (int i = 0; i < mid; i++)
    {
        left[i] = arr[i];
    }
    for (int i = mid; i < size; i++)
    {
        right[i - mid] = arr[i];
    }

    mergeSort(left, mid, sortBy, ascending);
    mergeSort(right, size - mid, sortBy, ascending);

    if (strcmp(sortBy, "release_date") == 0)
    {
        mergeByReleaseDate(arr, left, right, mid, size - mid, ascending);
    }
    else
    {
        merge(arr, left, right, mid, size - mid, sortBy, ascending);
    }

    delete[] left;
    delete[] right;
}

int GetLastMovieId(const string &filename)
{
    ifstream movieFile(filename);
    string line;
    int lastId = 0;

    while (getline(movieFile, line))
    {
        stringstream ss(line);
        ss >> lastId;
    }

    return lastId;
}

void ReadMovieData(const string &filename, movie catalog[], int &catalogSize)
{
    ifstream movieFile(filename);
    string line;
    catalogSize = 0;

    getline(movieFile, line);

    while (getline(movieFile, line))
    {
        stringstream ss(line);

        ss >> catalog[catalogSize].id;
        ss.ignore();
        ss.getline(catalog[catalogSize].title, sizeof(catalog[catalogSize].title), ';');
        ss.getline(catalog[catalogSize].genre, sizeof(catalog[catalogSize].genre), ';');
        ss >> catalog[catalogSize].duration;
        ss.ignore();
        ss.getline(catalog[catalogSize].directorFirstName, sizeof(catalog[catalogSize].directorFirstName), ' ');
        ss.getline(catalog[catalogSize].directorLastName, sizeof(catalog[catalogSize].directorLastName), ';');
        ss >> catalog[catalogSize].price;
        ss.ignore();
        ss.getline(catalog[catalogSize].release_date, sizeof(catalog[catalogSize].release_date), ';');
        ss.getline(catalog[catalogSize].rent_to, sizeof(catalog[catalogSize].rent_to), ';');
        ss.getline(catalog[catalogSize].rent_on, sizeof(catalog[catalogSize].rent_on), ';');
        ss.getline(catalog[catalogSize].status, sizeof(catalog[catalogSize].status), ';');

        catalogSize++;
    }
}

void WriteMovieData(const string &filename, const movie &rentedMovie)
{
    ofstream Archive(filename, ios::app);
    if (!Archive.is_open())
    {
        cout << "Unable to open the file" << endl;
        return;
    }

    Archive << rentedMovie.id << ";"
            << rentedMovie.title << ";"
            << rentedMovie.genre << ";"
            << rentedMovie.duration << ";"
            << rentedMovie.directorFirstName << " " << rentedMovie.directorLastName << ";"
            << rentedMovie.price << ";"
            << rentedMovie.release_date << ";"
            << rentedMovie.rent_to << ";"
            << rentedMovie.rent_on << ";"
            << rentedMovie.status << "\n";

    Archive.close();
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

bool isValidDate(const string &date)
{

    if (date.length() != 10)
    {
        return false;
    }

    if (date[4] != '-' || date[7] != '-')
    {
        return false;
    }

    int year, month, day;
    if (sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day) != 3)
    {
        return false;
    }

    return (year >= 2022 && year <= 2023) &&
           (month >= 1 && month <= 12) &&
           (day >= 1 && day <= 31);
}

movie getDataFromUser()
{
    string title;

    movie m;
    cout << "\nEnter the movie title:" << endl;
    cin.ignore();
    getline(cin, title);
    for (int i = 0; i < 50 && i < title.length(); i++)
        m.title[i] = title[i];
    cout << "\nEnter the movie genre/genres (Ex:War|Action):" << endl;
    cin >> m.genre;
    cout << "\nEnter the movie duration:" << endl;
    cin >> m.duration;
    if (m.duration < 0)
    {
        cout << "Duration must be greater than 0" << endl;
    }
    cout << "\nEnter the movie director first name:" << endl;
    cin >> m.directorFirstName;
    cout << "\nEnter the movie director last name:" << endl;
    cin >> m.directorLastName;
    cout << "\nEnter the movie price:" << endl;
    cin >> m.price;
    cout << "\nEnter the movie release date(years 2022,2023 YYYY-MM-DD):" << endl;
    cin >> m.release_date;
    while (!isValidDate(m.release_date))
    {
        cout << "Invalid date format or out-of-range values. Please enter a valid date (YYYY-MM-DD):" << endl;
        cin >> m.release_date;
    }
    return m;
}

void DisplayRentedMovies(const movie movies[], int size)
{
    for (int i = 0; i < size; ++i)
    {

        cout << "ID: " << movies[i].id << ", Title: " << movies[i].title << ", Price: " << movies[i].price
             << ", Rented to: " << movies[i].rent_to << ", renten on: " << movies[i].rent_on << endl;
    }
}
void DisplayMovieGenre(const movie movies[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        cout << "ID: " << movies[i].id << ", Title: " << movies[i].title << ", Genre: " << movies[i].genre << endl;
    }
}

void DisplayMovieDuration(const movie &singleMovie)

{
    cout << "ID: " << singleMovie.id << ", Title: " << singleMovie.title << ", Duration: " << singleMovie.duration << endl;
}

void DisplayMovieDirector(const movie movies[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        cout << "ID: " << movies[i].id << ", Title: " << movies[i].title << ", Director: " << movies[i].directorFirstName << " " << movies[i].directorLastName << endl;
    }
}

void DisplayMoviePrice(const movie movies[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        cout << "ID: " << movies[i].id << ", Title: " << movies[i].title << ", Price: " << movies[i].price << endl;
    }
}

void DisplayMovieReleaseDate(const movie movies[], int size)
{

    for (int i = 0; i < size; ++i)
    {
        cout << "ID: " << movies[i].id << ", Title: " << movies[i].title << ", Release Date: " << movies[i].release_date << endl;
    }
}

void SearchAndDisplayByGenre(const movie catalog[], int catalogSize, const char *userGenre)
{
    int matchingMovies = 0;
    bool foundMatchingGenre;

    for (int i = 0; i < catalogSize; i++)
    {
        foundMatchingGenre = false;

        string singleGenre;
        stringstream genreStream(catalog[i].genre);

        while (getline(genreStream, singleGenre, '|'))
        {
            transform(singleGenre.begin(), singleGenre.end(), singleGenre.begin(), ::tolower);

            if (singleGenre == userGenre)
            {
                foundMatchingGenre = true;
                break;
            }
        }

        if (foundMatchingGenre)
        {
            DisplayMovieGenre(&catalog[i], 1);
            matchingMovies++;
        }
    }

    if (matchingMovies == 0)
    {
        cout << "No movies found with that genre" << endl;
    }
}

void SearchAndDisplayByDuration(const movie catalog[], int catalogSize, int durationCategory)
{
    int matchingMovies = 0;

    for (int i = 0; i < catalogSize; i++)
    {
        bool foundMatchingDuration = false;

        switch (durationCategory)
        {
        case 1: // Short
            foundMatchingDuration = (catalog[i].duration > 0 && catalog[i].duration < 120);
            break;
        case 2: // Medium
            foundMatchingDuration = (catalog[i].duration >= 120 && catalog[i].duration <= 180);
            break;
        case 3: // Long
            foundMatchingDuration = (catalog[i].duration > 180);
            break;
        default:
            cout << "Invalid duration category" << endl;
            return;
        }

        if (foundMatchingDuration)
        {
            DisplayMovieDuration(catalog[i]);
            matchingMovies++;
        }
    }

    if (matchingMovies == 0)
    {
        cout << "No movies found with that duration category" << endl;
    }
}

void SearchAndDisplayByPriceRange(movie catalog[], int catalogSize, double minPrice, double maxPrice)
{
    int matchingMovies = 0;
    movie matchingMoviesArray[2000];

    for (int i = 0; i < catalogSize; i++)
    {
        if (catalog[i].price >= minPrice && catalog[i].price <= maxPrice)
        {
            matchingMoviesArray[matchingMovies++] = catalog[i];
        }
    }

    if (matchingMovies > 0)
    {

        DisplayMoviePrice(matchingMoviesArray, matchingMovies);
    }
    else
    {
        cout << "No movies found within the specified price range" << endl;
    }
}

void mergeByReleaseDate(movie arr[], movie left[], movie right[], int left_size, int right_size, bool ascending)
{
    int i = 0, j = 0, k = 0;

    while (i < left_size && j < right_size)
    {
        if (ascending)
        {
            if (strcmp(left[i].release_date, right[j].release_date) <= 0)
            {
                arr[k++] = left[i++];
            }
            else
            {
                arr[k++] = right[j++];
            }
        }
        else
        {
            if (strcmp(left[i].release_date, right[j].release_date) >= 0)
            {
                arr[k++] = left[i++];
            }
            else
            {
                arr[k++] = right[j++];
            }
        }
    }

    while (i < left_size)
    {
        arr[k++] = left[i++];
    }

    while (j < right_size)
    {
        arr[k++] = right[j++];
    }
}

void SearchAndDisplayByReleaseDate(movie catalog[], int catalogSize, const char *releaseYear)
{
    int matchingMovies = 0;
    movie matchingMoviesArray[2000];

    for (int i = 0; i < catalogSize; i++)
    {
        if (strstr(catalog[i].release_date, releaseYear) != nullptr)
        {
            matchingMoviesArray[matchingMovies++] = catalog[i];
        }
    }

    if (matchingMovies > 0)
    {

        DisplayMovieReleaseDate(matchingMoviesArray, matchingMovies);
    }
    else
    {
        cout << "No movies released in the specified year" << endl;
    }
}

void SearchAndDisplayByDirectorFirstName(const movie catalog[], int catalogSize, const char *directorFirstName)
{
    bool foundMatchingDirector = false;

    char directorFirstNameCapitalized[50];
    strcpy(directorFirstNameCapitalized, directorFirstName);
    directorFirstNameCapitalized[0] = toupper(directorFirstNameCapitalized[0]);

    for (int i = 0; i < catalogSize; i++)
    {

        if (strcmp(catalog[i].directorFirstName, directorFirstNameCapitalized) == 0)
        {
            DisplayMovieDirector(&catalog[i], 1);
            foundMatchingDirector = true;
        }
    }

    if (!foundMatchingDirector)
    {
        cout << "No movies found directed by " << directorFirstName << endl;
    }
}

void deleteMovie(const string &filename, int movieId)
{
    fstream file(filename, ios::in | ios::out);

    if (!file.is_open())
    {
        cerr << "Error al abrir el archivo" << endl;
        return;
    }

    string line;
    movie movie;
    stringstream updatedContent;

    while (getline(file, line))
    {
        stringstream ss(line);
        ss >> movie.id;
        ss.ignore();
        ss.getline(movie.title, sizeof(movie.title), ';');
        ss.getline(movie.genre, sizeof(movie.genre), ';');
        ss >> movie.duration;
        ss.ignore();
        ss.getline(movie.directorFirstName, sizeof(movie.directorFirstName), ' ');
        ss.getline(movie.directorLastName, sizeof(movie.directorLastName), ';');
        ss >> movie.price;
        ss.ignore();
        ss.getline(movie.release_date, sizeof(movie.release_date), ';');
        ss.getline(movie.rent_to, sizeof(movie.rent_to), ';');
        ss.getline(movie.rent_on, sizeof(movie.rent_on), ';');
        ss.getline(movie.status, sizeof(movie.status));

        if (movie.id != movieId)
        {
            updatedContent << line << '\n';
        }
    }

    file.close();

    file.open(filename, ios::out | ios::trunc);
    if (!file.is_open())
    {
        cerr << "Error al abrir el archivo para escritura" << endl;
        return;
    }

    file << updatedContent.str();

    file.close();

    cout << "Película eliminada exitosamente." << endl;
}

void DisplayAvailableMovies(const movie catalog[], int catalogSize)
{

    movie rentedMovies[2000];
    int rentedMoviesSize = 0;
    ReadMovieData("rentedMovies.csv", rentedMovies, rentedMoviesSize);

    cout << "\nAvailable Movies:\n";
    for (int i = 0; i < catalogSize; i++)
    {
        bool isRented = false;

        for (int j = 0; j < rentedMoviesSize; j++)
        {
            if (catalog[i].id == rentedMovies[j].id)
            {
                isRented = true;
                break;
            }
        }

        if (!isRented)
        {
            cout << "ID: " << catalog[i].id << ", Title: " << catalog[i].title << ", Status: Available\n";
        }
    }
}

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

#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <cstring>

using namespace std;

struct client
{
    char account_name[50];
    int cedula;
    char email[50];
    char country[50];
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

void merge(int arr[], int left[], int right[], int left_size, int right_size);
void mergeSort(int arr[], int size);
void displayMenu();
void SortMovieData();
bool isValidDate(const string &date);

int GetLastMovieId(const string &filename);
void ReadMovieData(const string &filename, movie catalog[], int &catalogSize);

void WriteMovieData(const string &filename, const movie &rentedMovie);
void RentMovie(movie catalog[], int catalogSize, client &c);

void WriteClientData(const string &filename, const client &c);

void DisplayMovieGenre(const movie movies[], int size);
void DisplayMovieDuration(const movie &singleMovie);
void DisplayMovieDirector(const movie movies[], int size);

void SearchAndDisplayByGenre(const movie catalog[], int catalogSize, const char *userGenre);
void SearchAndDisplayByDuration(const movie catalog[], int catalogSize, int durationCategory);
void SearchAndDisplayByDirector(const movie catalog[], int catalogSize, const char *userFirstName);
void SearchAndDisplayByReleaseDate(const movie catalog[], int catalogSize, const char *userReleaseDate);
void SearchAndDisplayById(const movie catalog[], int catalogSize, int user_id);

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
    int durationOption;
    int LastID = GetLastMovieId("Movies.csv");
    movie oneMovie, twoMovie;

    ifstream checkFile("rentedMovies.csv");
    if (!checkFile.is_open())
    {
        ofstream createFile("rentedMovies.csv");
        if (createFile.is_open())
        {
            createFile << "id;title;genre;duration;directorFirstName;directorLastName;price;release_date;rent_to;rent_on;status\n";
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

                cout << "Which director do you want to search?\n\n";
                cout << "Enter director's first name: ";
                cin >> director;

                transform(director, director + strlen(director), director, ::tolower);

                SearchAndDisplayByDirector(catalog, catalogSize, director);

                break;
            case 4:

                ReadMovieData("Movies.csv", catalog, catalogSize);

                cout << "Which year do you want to search? (2022-2023)\n\n";
                cout << "Enter year: ";
                cin >> year;

                break;
            case 5:

                ReadMovieData("Movies.csv", catalog, catalogSize);

                cout << "Which price do you want to search?\n\n";

                break;
            default:
                cout << "Invalid search option" << endl;
                break;
            }

            break;

        case 2:
            // Implementar la lógica de consultar el estado de la película
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
                    cout << "The movie is already rented" << endl;
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

                    cout << "Enter your country: ";
                    cin.getline(c.country, sizeof(c.country));

                    strcpy(catalog[foundIndex].status, "Rented");
                    strcpy(catalog[foundIndex].rent_to, c.account_name);

                    WriteMovieData("rentedMovies.csv", catalog[foundIndex]);

                    cout << "The movie '" << catalog[foundIndex].title << "' has been rented to " << c.account_name << endl;
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
                // WriteMovieData("Movies.csv", oneMovie);
                cout << "\nMovie added successfully!" << endl;
            }
            else
            {
                cout << "List is full" << endl;
            }

            break;
        case 5:
            // Implementar la lógica de búsqueda de cliente
            break;
        case 6:
            cout << "Thank you for using Blockbuster. Goodbye!" << endl;
            running = false;
            break;
        default:
            cout << "Please select a valid option" << endl;
            break;
        }
    }
    return 0;
}

void displayMenu()
{
    cout << "\nPlease select an option below:(1-6)\n"
         << endl;
    cout << "1. Search a movie." << endl;
    cout << "2. Consult status of the movie." << endl;
    cout << "3. Rent a movie." << endl;
    cout << "4. Add a movie." << endl;
    cout << "5. Search a client." << endl;
    cout << "6. Exit." << endl;
    cout << "Select an option: ";
}

void SortMovieData(int sortOption)
{
    cout << "\nHow do you want to sort the movies?\n\n";
    cout << "1. Sort by price\n";
    cout << "2. Sort by duration\n";
    cout << "4. Sort by release date\n";
    cout << "5. Sort by id\n";
    cout << "Select an option: ";
    cin >> sortOption;
}

void merge(int arr[], int left[], int right[], int left_size, int right_size)
{
    int i = 0, j = 0, k = 0;

    while (i < left_size && j < right_size)
    {
        if (left[i] <= right[j])
        {
            arr[k++] = left[i++];
        }
        else
        {
            arr[k++] = right[j++];
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

void mergeSort(int arr[], int size)
{
    if (size <= 1)
    {
        return;
    }

    int mid = size / 2;
    int left[mid];
    int right[size - mid];

    for (int i = 0; i < mid; i++)
    {
        left[i] = arr[i];
    }
    for (int i = mid; i < size; i++)
    {
        right[i - mid] = arr[i];
    }

    mergeSort(left, mid);
    mergeSort(right, size - mid);

    merge(arr, left, right, mid, size - mid);
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

// if (!movieFound)
//{
//   cout << "No se encontró ninguna película con el ID proporcionado." << endl;
//}

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
    movie m;
    cout << "\nEnter the movie title:" << endl;
    cin >> m.title;
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

void AllMovieInfo(const movie movies[], int size)
{
    for (int i = 0; i < size; ++i)
    {

        cout << "ID: " << movies[i].id << ", Title: " << movies[i].title << ", Genre: " << movies[i].genre
             << ", Duration: " << movies[i].duration << ", Director: " << movies[i].directorFirstName << " " << movies[i].directorLastName << ", Price: " << movies[i].price
             << ", Release Date: " << movies[i].release_date << endl;
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

void SearchAndDisplayByDirector(const movie catalog[], int catalogSize, const char *userFirstName)
{

    for (int i = 0; i < catalogSize; i++)
    {
        if (strcmp(catalog[i].directorFirstName, userFirstName) == 0)
        {
            DisplayMovieDirector(&catalog[i], 1);
        }
    }
}

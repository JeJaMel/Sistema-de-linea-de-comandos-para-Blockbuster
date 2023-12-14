#include "Movies.h"
#include "client.h"

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
}
void deleteMovieCase(movie catalog[], int catalogSize)
{
    int movieIdToDelete;
    bool movieFound2 = false;
    string confirm;

    ReadMovieData("src/movies.csv", catalog, catalogSize);

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
                deleteMovie("src/movies.csv", movieIdToDelete);
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
}
void returnMovieCase(movie catalog[], int catalogSize)
{
    int movieIdToDelete;
    bool movieFound2 = false;
    string confirm;

    ReadMovieData("src/rentedMovies.csv", catalog, catalogSize);

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
                deleteMovie("src/rentedMovies.csv", movieIdToDelete);
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
}
void addMovieCase(movie catalog[], int &catalogSize, int &LastID)
{
    ReadMovieData("src/Movies.csv", catalog, catalogSize);

    movie oneMovie = getDataFromUser();
    oneMovie.id = LastID + 1;

    if (catalogSize < MaxCatalogSize)
    {
        catalogSize++;
        catalog[catalogSize - 1] = oneMovie;

        WriteMovieData("src/Movies.csv", oneMovie);
        cout << "\nMovie added successfully!" << endl;
    }
    else
    {
        cout << "List is full" << endl;
    }
}

void rentMovieCase(movie catalog[], int &catalogSize)
{
    bool movieAlreadyRented = false;
    int movieId;
    int foundIndex = -1;
    client c;
    movie rentedMovie;
    bool exitLoop = false;

    time_t now = time(0);
    struct tm *ltm = localtime(&now);

    char actualDate[11];
    strftime(actualDate, sizeof(actualDate), "%d-%m-%Y", ltm);

    do
    {
        exitLoop = false;

        cout << "Enter your account name: ";
        cin.ignore();
        cin.getline(c.account_name, sizeof(c.account_name));

        ReadMovieData("src/rentedMovies.csv", catalog, catalogSize);
        for (int i = 0; i < catalogSize; i++)
        {
            if (strcmp(catalog[i].rent_to, c.account_name) == 0)
            {
                cout << "You already have the movie '" << catalog[i].title << "'. Please return it before renting another one." << endl;
                exitLoop = true;
                break;
            }
        }

        if (!exitLoop)
        {
            cout << "Enter the ID of the movie you want to rent: ";
            cin >> movieId;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            ReadMovieData("src/rentedMovies.csv", catalog, catalogSize);
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
                ReadMovieData("src/Movies.csv", catalog, catalogSize);
                for (int i = 0; i < catalogSize; i++)
                {
                    if (catalog[i].id == movieId)
                    {
                        rentedMovie = catalog[i];
                        foundIndex = i;
                        break;
                    }
                }

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

                WriteMovieData("src/rentedMovies.csv", catalog[foundIndex]);

                cout << "The movie '" << catalog[foundIndex].title << "' has been rented to " << c.account_name << endl;
                WriteClientData("src/clientData.bin", c);

                exitLoop = true;
            }
        }
    } while (!movieAlreadyRented && !exitLoop);
}
void checkMovieCase(movie catalog[], int catalogSize)
{
    int movieIdToCheck;
    bool movieFoundToCheck = false;
    bool movieFoundToCheck2 = false;

    cout << "Enter the ID of the movie you want to check: ";
    cin >> movieIdToCheck;

    ReadMovieData("src/rentedMovies.csv", catalog, catalogSize);

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
        ReadMovieData("src/Movies.csv", catalog, catalogSize);

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
}
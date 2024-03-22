#include "SearchAndDisplay.h"
#include "Movies.h"
#include "mergeSort.h"

void DisplayAvailableMovies(const movie catalog[], int catalogSize)
{

    movie rentedMovies[2000];
    int rentedMoviesSize = 0;
    ReadMovieData("src/rentedMovies.csv", rentedMovies, rentedMoviesSize);

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
        SetColor(12);
        cout << "\nNo movies found with that genre" << endl;
        SetColor(7);
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
            SetColor(12);
            cout << "\nInvalid duration category" << endl;
            SetColor(7);

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
        SetColor(12);
        cout << "\nNo movies found with that duration category" << endl;
        SetColor(7);
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
        cout << "\nNo movies found within the specified price range" << endl;
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
        SetColor(12);
        cout << "\nNo movies released in the specified year" << endl;
        SetColor(7);
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
        SetColor(12);
        cout << "\nNo movies found directed by " << directorFirstName << endl;
        SetColor(7);
    }
}

void searchMovieCase(movie catalog[], int &catalogSize)
{
    int searchOption;
    char genre[50];
    int durationOption;
    char director[50];

    system("cls");

    cout << "\nSelect search option:\n";
    cout << "1. Search by genre\n";
    cout << "2. Search by duration\n";
    cout << "3. Search by director\n";
    cout << "4. Search by release date\n";
    cout << "5. Search by price\n";
    cout << "6. Search by rented status\n";
    cout << "Enter option: ";
    cin >> searchOption;

    switch (searchOption)
    {
    case 1:
        ReadMovieData("src/Movies.csv", catalog, catalogSize);

        system("cls");

        cout << "\nWhich genre do you want to search?\n\n";
        cout << "|Action| |Adventure| |Animation| |Children| |Comedy| |Crime| \n";
        cout << "|Documentary| |Drama|  |Fantasy| |Film-Noir| |Horror| |musical|\n";
        cout << "|Mystery| |Romance| |Sci-Fi| |Thriller| |War| |Western|\n\n";
        cout << "Enter genre: ";
        cin >> genre;

        transform(genre, genre + strlen(genre), genre, ::tolower);

        SearchAndDisplayByGenre(catalog, catalogSize, genre);

        SetColor(8);
        cout << "press any key to continue...";
        SetColor(7);
        getch();
        system("cls");

        break;

    case 2:
        ReadMovieData("src/Movies.csv", catalog, catalogSize);

        system("cls");

        cout << "\nWhich duration category do you want to search?\n";
        cout << "1. Short (less than 2 hours)\n";
        cout << "2. Medium (2 to 3 hours)\n";
        cout << "3. Long (more than 3 hours)\n";
        cout << "Enter option: ";
        cin >> durationOption;

        SearchAndDisplayByDuration(catalog, catalogSize, durationOption);

        SetColor(8);
        cout << "press any key to continue...";
        SetColor(7);
        getch();
        system("cls");

        break;

    case 3:
        ReadMovieData("src/Movies.csv", catalog, catalogSize);

        system("cls");

        cout << "Which director's first name do you want to search?\n\n";
        cout << "Enter director's first name: ";
        cin >> director;

        SearchAndDisplayByDirectorFirstName(catalog, catalogSize, director);

        SetColor(8);
        cout << "press any key to continue...";
        SetColor(7);
        getch();
        system("cls");

        break;

    case 4:
        int dateFilterOption;

        system("cls");

        cout << "\nSelect date filter option:\n";
        cout << "1. Filter movies released in 2022\n";
        cout << "2. Filter movies released in 2023\n";
        cout << "3. Filter older movies\n";
        cout << "4. Filter newer movies\n";
        cout << "Enter option: ";
        cin >> dateFilterOption;

        ReadMovieData("src/Movies.csv", catalog, catalogSize);

        switch (dateFilterOption)
        {
        case 1:

            system("cls");

            SearchAndDisplayByReleaseDate(catalog, catalogSize, "2022");

            SetColor(8);
            cout << "press any key to continue...";
            SetColor(7);

            getch();
            system("cls");

            break;
        case 2:

            system("cls");

            SearchAndDisplayByReleaseDate(catalog, catalogSize, "2023");

            SetColor(8);
            cout << "press any key to continue...";
            SetColor(7);

            getch();
            system("cls");

            break;
        case 3:

            system("cls");

            mergeSort(catalog, catalogSize, "release_date");
            DisplayMovieReleaseDate(catalog, catalogSize);

            SetColor(8);
            cout << "press any key to continue...";
            SetColor(7);
            getch();
            system("cls");

            break;
        case 4:

            system("cls");

            mergeSort(catalog, catalogSize, "release_date", false);
            DisplayMovieReleaseDate(catalog, catalogSize);

            SetColor(8);
            cout << "press any key to continue...";
            SetColor(7);
            getch();
            system("cls");

            break;
        default:
            SetColor(12);
            cout << "\nInvalid date filter option" << endl;
            SetColor(7);
            break;
        }
        break;

    case 5:

        system("cls");

        double minPrice, maxPrice;
        cout << "Enter the minimum price: ";
        cin >> minPrice;
        cout << "Enter the maximum price: ";
        cin >> maxPrice;

        system("cls");

        ReadMovieData("src/Movies.csv", catalog, catalogSize);
        SearchAndDisplayByPriceRange(catalog, catalogSize, minPrice, maxPrice);

        SetColor(8);
        cout << "press any key to continue...";
        SetColor(7);
        getch();
        system("cls");

        break;

    case 6:
        int Option;

        system("cls");

        cout << "\n1. search available movies\n";
        cout << "2. search rented movies\n ";
        cout << "Enter option: ";
        cin >> Option;

        system("cls");

        if (Option == 1)
        {
            ReadMovieData("src/Movies.csv", catalog, catalogSize);
            DisplayAvailableMovies(catalog, catalogSize);

            SetColor(8);
            cout << "press any key to continue...";
            SetColor(7);
            getch();
            system("cls");
        }
        else if (Option == 2)
        {
            ReadMovieData("src/rentedMovies.csv", catalog, catalogSize);
            DisplayRentedMovies(catalog, catalogSize);

            SetColor(8);
            cout << "press any key to continue...";
            SetColor(7);
            getch();
            system("cls");
        }
        break;

    default:
        SetColor(12);
        cout << "\nInvalid search option" << endl;
        SetColor(7);
        break;
    }
}
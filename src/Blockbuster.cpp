#include "HeaderFiles/Struct.h"
#include "HeaderFiles/MergeSort.h"
#include "HeaderFiles/SearchAndDisplay.h"
#include "HeaderFiles/client.h"
#include "HeaderFiles/Movies.h"

movie catalog[MaxCatalogSize];
int main()
{

    int catalogSize;
    int Selection;

    int LastID = GetLastMovieId("src/Movies.csv");

    ifstream checkFile("src/rentedMovies.csv");
    if (!checkFile.is_open())
    {
        ofstream createFile("src/rentedMovies.csv");
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
    system("cls");

    SetColor(14);
    cuadro(0, 0, 76, 4);
    gotoxy(4, 2);
    printf("Welcome to Blockbuster technical terminal, press any key to continue\n\n\n");
    SetColor(7);
    getch();

    bool running = true;

    while (running)
    {
        displayMenu();
        cin >> Selection;

        switch (Selection)
        {
        case 1:
            searchMovieCase(catalog, catalogSize);
            break;
        case 2:
            checkMovieCase(catalog, catalogSize);
            break;
        case 3:
            rentMovieCase(catalog, catalogSize);
            break;
        case 4:
            addMovieCase(catalog, catalogSize, LastID);
            break;
        case 5:
            searchClientCase(catalog, catalogSize);
            break;
        case 6:
            returnMovieCase(catalog, catalogSize);
            break;
        case 7:
            deleteMovieCase(catalog, catalogSize);
            break;
        case 8:
            deleteClientCase(catalog, catalogSize);
            break;
        case 9:
            return 0;
            break;
        }
    }
}

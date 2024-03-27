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

    if (!createRentedMoviesFile())
    {
        return 1;
    }

    system("cls");

    SetColor(14);
    cuadro(0, 0, 76, 4);
    gotoxy(4, 2);
    printf("Welcome to Blockbuster technical terminal, press any key to continue\n\n\n");
    SetColor(7);
    getch();

    int counter = 0;
    char key;

    printMenu(counter); // Print the initial menu

    while (true)
    {
        key = _getch();

        if (key == 72 && counter > 0) // Up arrow key
        {
            counter--;
        }
        else if (key == 80 && counter < 8) // Down arrow key
        {
            counter++;
        }
        else if (key == '\r') // Enter key
        {
            system("cls");
            switch (counter)
            {
            case 0:
                searchMovieCase(catalog, catalogSize);
                break;
            case 1:
                checkMovieCase(catalog, catalogSize);
                break;
            case 2:
                rentMovieCase(catalog, catalogSize);
                break;
            case 3:
                addMovieCase(catalog, catalogSize, LastID);
                break;
            case 4:
                searchClientCase(catalog, catalogSize);
                break;
            case 5:
                returnMovieCase(catalog, catalogSize);
                break;
            case 6:
                deleteMovieCase(catalog, catalogSize);
                break;
            case 7:
                deleteClientCase(catalog, catalogSize);
                break;
            case 8:
                return 0;
                break;
            }
        }

        printMenu(counter); // Update the menu
    }

    return 0;
}
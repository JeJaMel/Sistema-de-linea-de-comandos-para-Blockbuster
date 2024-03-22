#include "Struct.h"

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

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

void SetColorAndBackground(int ForgC, int BackC)
{
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}

void cuadro(int x1, int y1, int x2, int y2)
{
    for (int i = x1; i < x2; i++)
    {
        gotoxy(i, y1);
        cout << char(205);
        gotoxy(i, y2);
        cout << char(205);
    }

    for (int i = y1; i < y2; i++)
    {
        gotoxy(x1, i);
        cout << char(186);
        gotoxy(x2, i);
        cout << char(186);
    }

    gotoxy(x1, y1);
    cout << char(201);
    gotoxy(x1, y2);
    cout << char(200);
    gotoxy(x2, y1);
    cout << char(187);
    gotoxy(x2, y2);
    cout << char(188);
}

#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
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
void merge(int arr[], int left[], int right[], int left_size, int right_size);
void mergeSort(int arr[], int size);
void displayMenu();

int main()
{

    int Selection;

    string MyFilePath = "Movies.csv";
    ifstream MovieData;

    MovieData.open(MyFilePath);
    if (!MovieData.is_open())
    {
        cout << "No se pudo abrir el archivo " << MyFilePath << endl;
        return 1;
    }

    cout << "\n ╠═════════════════════════════════╣ BLOCKBUSTER ╠════════════════════════════════╣" << endl;
    cout << "       Welcome to Blockbuster technical terminal, press any key to continue"
         << endl;
    string anykey1;
    cin >> anykey1;

    bool running = true;
    while (running)
    {
        displayMenu();
        cin >> Selection;

        switch (Selection)
        {
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
            cout << "Thank you for using Blockbuster. Goodbye!" << endl;
            running = false;
            return 0;
            break;

        default:
            cout << "Please select a valid option" << endl;
            return 1;
        }
    }

    return 0;
}

void displayMenu()
{
    cout << "Please select an option below:(1-6)\n"
         << endl;
    cout << "1. Search a movie." << endl;
    cout << "2. Consult status of the movie." << endl;
    cout << "3. Rent a movie." << endl;
    cout << "4. Add a movie." << endl;
    cout << "5. Search a client." << endl;
    cout << "6. Exit." << endl;
    cout << "Select an option: ";
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

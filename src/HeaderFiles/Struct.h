#pragma once

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

const int MaxCatalogSize = 2000;

void displayMenu();
void FilterMovieData();
void ReadMovieData(const string &filename, movie catalog[], int &catalogSize);
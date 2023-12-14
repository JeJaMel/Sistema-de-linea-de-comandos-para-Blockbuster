#pragma once
#include "struct.h"

movie getDataFromUser();
bool isValidDate(const string &date);
int GetLastMovieId(const string &filename);
void WriteMovieData(const string &filename, const movie &rentedMovie);
void deleteMovie(const string &filename, int movieId);
void deleteMovieCase(movie catalog[], int catalogSize);
void returnMovieCase(movie catalog[], int catalogSize);
void addMovieCase(movie catalog[], int &catalogSize, int &LastID);
void rentMovieCase(movie catalog[], int &catalogSize);
void checkMovieCase(movie catalog[], int catalogSize);

#pragma once

#include "Struct.h"

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
void SearchAndDisplayByPriceRange(movie catalog[], int catalogSize, double minPrice, double maxPrice);
void SearchAndDisplayByDirectorFirstName(const movie catalog[], int catalogSize, const char *directorFirstName);
void searchMovieCase(movie catalog[], int &catalogSize);

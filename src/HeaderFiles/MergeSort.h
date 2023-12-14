#pragma once

#include "struct.h"

void mergeSort(movie arr[], int size, const char *sortBy, bool ascending = true);
void merge(movie arr[], movie left[], movie right[], int left_size, int right_size, const char *sortBy, bool ascending);
void mergeByReleaseDate(movie arr[], movie left[], movie right[], int left_size, int right_size, bool ascending);

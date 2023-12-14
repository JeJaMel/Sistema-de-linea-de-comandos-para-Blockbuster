#include "MergeSort.h"

void merge(movie arr[], movie left[], movie right[], int left_size, int right_size, const char *sortBy, bool ascending)
{
    int i = 0, j = 0, k = 0;

    while (i < left_size && j < right_size)
    {
        if (strcmp(sortBy, "release_date") == 0)
        {
            if (ascending)
            {
                if (strcmp(left[i].release_date, right[j].release_date) <= 0)
                {
                    arr[k++] = left[i++];
                }
                else
                {
                    arr[k++] = right[j++];
                }
            }
            else
            {
                if (strcmp(left[i].release_date, right[j].release_date) >= 0)
                {
                    arr[k++] = left[i++];
                }
                else
                {
                    arr[k++] = right[j++];
                }
            }
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
void mergeSort(movie arr[], int size, const char *sortBy, bool ascending)
{
    if (size <= 1)
    {
        return;
    }

    int mid = size / 2;
    movie *left = new movie[mid];
    movie *right = new movie[size - mid];

    for (int i = 0; i < mid; i++)
    {
        left[i] = arr[i];
    }
    for (int i = mid; i < size; i++)
    {
        right[i - mid] = arr[i];
    }

    mergeSort(left, mid, sortBy, ascending);
    mergeSort(right, size - mid, sortBy, ascending);

    if (strcmp(sortBy, "release_date") == 0)
    {
        mergeByReleaseDate(arr, left, right, mid, size - mid, ascending);
    }
    else
    {
        merge(arr, left, right, mid, size - mid, sortBy, ascending);
    }

    delete[] left;
    delete[] right;
}
void mergeByReleaseDate(movie arr[], movie left[], movie right[], int left_size, int right_size, bool ascending)
{
    int i = 0, j = 0, k = 0;

    while (i < left_size && j < right_size)
    {
        if (ascending)
        {
            if (strcmp(left[i].release_date, right[j].release_date) <= 0)
            {
                arr[k++] = left[i++];
            }
            else
            {
                arr[k++] = right[j++];
            }
        }
        else
        {
            if (strcmp(left[i].release_date, right[j].release_date) >= 0)
            {
                arr[k++] = left[i++];
            }
            else
            {
                arr[k++] = right[j++];
            }
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
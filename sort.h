


#ifndef SORT_H
#define SORT_H

void insertion_sort(int* arr, int n);
void merge_sort(int* arr, int left, int right);
void merge(int* arr, int left, int mid, int right);
double measure_sorting_time(void (*sort_func)(int*, int), int* arr, int n);
double measure_merge_sort_time(int* arr, int n);

#endif
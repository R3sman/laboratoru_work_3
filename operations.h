


#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

int* read_array_from_file(const char* filename, int* n);
void write_array_to_file(const char* filename, int* arr, int n);
void save_previous_run(int* arr, int n);
int* load_previous_run(int* n);
void generate_test_files();

#endif
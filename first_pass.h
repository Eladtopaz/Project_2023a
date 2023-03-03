#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "labels.h"

/*
 * TODO: write here
 */
label_list* first_pass(char* file);
int get_number_of_output_lines(char* line,  int index, int is_label);
int get_addressing_type_number(char* instruction , char* next_word);

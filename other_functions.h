#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "labels.h"
#include "globals.h"
#include <ctype.h>


/*
 * Function that concatenate 2 strings and return the full string.
 * Parameters:
 * s1 - the first string in the full one.
 * s2 - the second string in the full one.
 * Returns:
 * The function returns a pointer to a string that is s1->s2.
 */
char* concatenate_strings(char* s1, char* s2);

/*
 * Function works exactly like concatenate_strings, despite one thing -
 * it frees s1 before it finish.
 */
char* concatenate_strings_with_free(char* s1, char* s2);

/*
 * TODO: Write here
 */
void skip_white_in_line(char* line, int* index);
int get_instruction(char* temp_instruction);
int count_comma(char* word);
int is_alphanumeric_str(char *s);
int is_reserved_word(char *name);
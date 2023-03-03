#include "second_pass.h"

char* second_pass(label_list* head, char* file)
{
    char *file_name;
    FILE *input_file;

    file_name = concatenate_strings(file, ".am"); /* Get the file after the pre assembler */

    /* Open the files with the right modes */
    input_file = fopen(file_name, "r");

    if(input_file)
    {
        printf("%s", "worked!");
    }
    else
    {
        printf("%s", "Failed!");
    }

}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "other_functions.h"
#include "pre_assembler.h"
#include "macro_table.h"
#include "globals.h"

// TODO: check what happens when 0 macros! free?? problem!


char* pre_assembler(char* file)
{
    char *error = NULL;
    char *file_name, *pre_assembler_output_file;
    char *current_macro, *current_content;
    char *temp_macro, *temp_name, *temp_content;
    char *first_word_in_line, current_line[MAX_LINE_LENGTH], temp_line[MAX_LINE_LENGTH];
    int line_to_file, is_mcr = OFF;
    macro_list *head = NULL, *temp_node;

    FILE *input_file, *output_file;

    /* Add extension to files */
    file_name = concatenate_strings(file, ".as");
    pre_assembler_output_file = concatenate_strings(file, ".am");

    /* Open the files with the right modes */
    input_file = fopen(file_name, "r");
    output_file = fopen(pre_assembler_output_file, "w");

    /* Initialize the current content string */
    current_content = (char *)malloc(1);

    if (input_file)
    {
        while((fgets(current_line, MAX_LINE_LENGTH, input_file)))
        {
            line_to_file = 1;

            if(!strchr(current_line, '\n'))
                return "[ERROR] One of the lines in the file is bigger then 80! max size for line is 80!\n";
            if(current_line[0] == ';')
                line_to_file = 0; /* don't print comment lines to file */

            /* Create copy */
            strcpy(temp_line, current_line);

            if(is_mcr)
            {
                line_to_file = 0; /* Make sure doesn't print while macro is on */
                if(!strcmp(first_word_in_line, "endmcr\n"))
                {
                    is_mcr = OFF;
                    head = add_macro(head, current_macro, current_content);
                    current_content = (char *)malloc(1); /* initialize string */
                }
                else
                {
                    /* While is_mcr on and there hasn't been endmcr, store the macro in a string */
                    if(current_content)
                    {
                        current_content = concatenate_strings_with_free(current_content, current_line); /* Returns new pointer instead of changing the old one */
                    }
                    else
                    {
                        strcpy(current_content, temp_line);
                    }
                }
            }

            /* Change the original line to get first word */
            first_word_in_line = strtok(current_line, " ");
            if(!strcmp(first_word_in_line, "mcr"))
            {
                is_mcr = ON;
                temp_macro = strtok(NULL, " "); /* Take only the name of the macro and store it, with \n */
                current_macro = malloc(sizeof (char)* strlen(temp_macro));
                strcpy(current_macro, temp_macro);
                line_to_file = 0;
            }

            temp_node = head;
            while(temp_node != NULL) /* Enter only if table isn't empty */
            {
                temp_name = get_name(temp_node);
                if(!strcmp(temp_name, first_word_in_line))
                {
                    temp_content = get_content(temp_node);
                    fputs(temp_content, output_file);
                    line_to_file = 0; /* Make sure doesn't print the name of the macro too */

                }
                temp_node = temp_node->next;
            }

            /* Check if needed to write the current line to file or not! */
            if(line_to_file)
                fputs(temp_line, output_file);
        }
    }
    else
    {
        error = "[ERROR] Error in opening the file\n";
    }
    fclose(input_file);
    fclose(output_file);

    /* Free memory */
    free(file_name);
    free(pre_assembler_output_file);
    free(current_content);

    if(head) /* Make sure there was a macro and not free NULL. */
        free_head(head);

    if (error)
        return error;
    return 0;
}

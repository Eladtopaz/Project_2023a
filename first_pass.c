#include "first_pass.h"


int get_addressing_type_number(char* instruction , char* next_word)
{
    char *first_part, *second_part;

    if(strcmp(instruction, "rts") == 0 || strcmp(instruction, "stop") == 0)
        return 1;
    if(!next_word)
        return ERROR; /* Only 2 instructions doesn't have arguments at all - stop and rts */
    if(next_word[0] == '#')
        return 2;
    if(check_valid_label(next_word, NULL) == NULL) /* Check if the next word can be a label! if so - it's a label! */
        return 2;
    if(strchr(next_word, '(') && next_word[strlen(next_word)-1] == ')')
    {
        first_part = strtok(next_word, "(");
        first_part = strtok(NULL, ",");
        second_part = strtok(NULL, ")");
        if(strlen(first_part) == 2  && strlen(second_part) == 2)
        {
            if(first_part[0] == 'r' && isdigit(first_part[1]) && second_part[0] == 'r' && isdigit(second_part[1])) /* 2 registers */
                return 3;

        }
        else
        {
            return 4; /* In case no 2 registers */
        }
    }

    if(strchr(next_word, ','))
    {
        first_part = strtok(next_word, ",");
        second_part = strtok(NULL, " ");

        if(strlen(first_part) == 2  && strlen(second_part) == 2)
        {
            if(first_part[0] == 'r' && isdigit(first_part[1]) && second_part[0] == 'r' && isdigit(second_part[1])) /* 2 registers */
                return 2;
        }
        else
        {
            /* In case no 2 registers*/
            return 3;
        }
    }
    return ERROR;
}


int get_number_of_output_lines(char* line,  int index, int is_label)
{
    char* current_instruction, *next_word;
    int instruction;
    int number_of_words = 0; /* Default for ENTRY and EXTERN lines. */
    int addressing_type_number;


    current_instruction = strtok(line, " ");
    if(is_label)
        current_instruction = strtok(NULL, " ");
    current_instruction[strcspn(current_instruction, "\n")] = 0; /* Remove \n in the end of the line is needed! */
    instruction = get_instruction(current_instruction);

    next_word = strtok(NULL, " ");
    if(next_word)
        next_word[strcspn(next_word, "\n")] = 0; /* Remove \n in the end of the line is needed! */

    if(instruction == STRING)
        number_of_words =  strlen(next_word) - 1; /* String has 2 " to remove, and 1 \0 to add */
    if(instruction == DATA)
        number_of_words = count_comma(next_word) + 1 ; /* Number of commas + 1 is number of numbers, each number is a line */

    if(instruction != DATA && instruction != STRING) {
        addressing_type_number = get_addressing_type_number(current_instruction, next_word);

        number_of_words = addressing_type_number;
    }

    return number_of_words;
}

label_list* first_pass(char* file)
{
    char *error = NULL;
    char *file_name;
    char current_line[MAX_LINE_LENGTH];
    char temp_line[MAX_LINE_LENGTH];
    char *current_label;


    int index_of_next_word;
    int is_label = OFF; /* Init at no label */
    long ic = 100, dc = 0; /* TODO: init values! Init DC and IC to 0 */
    int number_of_words; /* Amount of line in the final output file */
    label_list *head = NULL;

    FILE *input_file;

    file_name = concatenate_strings(file, ".am"); /* Get the file after the pre assembler */

    /* Open the files with the right modes */
    input_file = fopen(file_name, "r");

    if(input_file)
    {
        while((fgets(current_line, MAX_LINE_LENGTH, input_file)))
        {
            /* TODO: init current_label before second use! - maybe not needed? */
            number_of_words = 0; /* TODO: needs to change with each line process */
            is_label = OFF;

            index_of_next_word = 0;
            /* Skip white */
            skip_white_in_line(current_line, &index_of_next_word);

            /* Get first word and check if label */
            strcpy(temp_line, current_line);
            current_label = strtok(temp_line, " ");
            if(current_label[strlen(current_label)-1] == ':')
            {
                is_label = ON;
                current_label[strcspn(current_label, ":")] = 0; /* Remove \n in the end of the line is needed! */
                error = check_valid_label(current_label, head);
                if(error)
                {
                    printf("%s",error);
                    return NULL;
                }
                head = add_label(head, current_label, ic);

                /* Skip to next word in line */
                index_of_next_word += strlen(current_label) + 1;
                skip_white_in_line(current_line, &index_of_next_word);
            }

            /* Just get how many lines should have */
            number_of_words = get_number_of_output_lines(current_line, index_of_next_word, is_label);
            if(number_of_words == ERROR)
            {
                printf("%s","[ERROR] Wrong addressing method!");
                return NULL;
            }

            ic+= number_of_words; /* Next line */
        }
    }
    else
    {
        error = "[ERROR] Error in opening the file\n";
    }

    /* Close File */
    // fclose(input_file);
    /* Free memory */
    free(file_name);
    if (error)
    {
        printf("%s",error);
        return NULL;
    }
    return head;
}
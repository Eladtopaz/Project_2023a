#include "other_functions.h"

char* concatenate_strings(char* s1, char* s2)
{
    char *str = (char *)malloc(strlen(s1) + strlen(s2));
    strcpy(str, s1);
    strcat(str, s2);
    return str;
}

char* concatenate_strings_with_free(char* s1, char* s2)
{
    char *str = (char *)malloc(strlen(s1) + strlen(s2));
    strcpy(str, s1);
    strcat(str, s2);
    free(s1);
    return str;
}

void skip_white_in_line(char* line, int* index)
{
    while(line[*index] == '\t' || line[*index] == ' ')
        (*index)++;
}

char* get_word(char* line, int* index)
{
    char temp_word[MAX_LINE_LENGTH];
    char* word;
    int i,j = 0;

    for(i=*index; line[i] && line[i] != ':' && line[i] != ' ' && line[i] != '\n' && i < MAX_LINE_LENGTH; i++, j++)
        temp_word[j] = line[i];
    temp_word[j] = '\0'; /* End of word */
    (*index) = i; /* Skip the index to the next word */

    word = malloc(sizeof(char) * (j+1)); /* Because j is the size of the temp_word */
    strcpy(word, temp_word);
    return word; /* Return the word */
}

int count_comma(char* word)
{
    int i, count = 0;
    for (i=0; i < strlen(word); i++)
        if(word[i] == ',')
            count++;
    return count;
}


int get_instruction(char* temp_instruction)
{
    int instruction = ERROR;
    if(temp_instruction[0] == '.')
    {
        // Can be only 4 options
        if(!strcmp(".data", temp_instruction))
            instruction = DATA;
        if(!strcmp(".string", temp_instruction))
            instruction = STRING;
        if(!strcmp(".entry", temp_instruction))
            instruction = ENTRY;
        if(!strcmp(".extern", temp_instruction))
            instruction = EXTERN;
    }
    else
    {
        if(!strcmp("mov", temp_instruction))
            return 00; /* Add? */
        if(!strcmp("mov", temp_instruction))
            return 00; /* Add? */        if(!strcmp("mov", temp_instruction))
            return 00; /* Add? */        if(!strcmp("mov", temp_instruction))
            return 00; /* Add? */        if(!strcmp("mov", temp_instruction))
            return 00; /* Add? */        if(!strcmp("mov", temp_instruction))
            return 00; /* Add? */        if(!strcmp("mov", temp_instruction))
            return 00; /* Add? */        if(!strcmp("mov", temp_instruction))
            return 00; /* Add? */        if(!strcmp("mov", temp_instruction))
            return 00; /* Add? */
    }
    return instruction;
}

int is_alphanumeric_str(char *s)
{
    int i;
    for (i = 0; s[i]; i++)
    {
        if (!isalpha(s[i]) && !isdigit(s[i]))
            return 0;
    }
    return 1;
}
int is_reserved_word(char *name)
{
    /* TODO: fix here if changed get_instruction! */
    if(get_instruction(name) != ERROR)
        return 0;
    return 1;
}





char* num_to_binary(int num)
{

}
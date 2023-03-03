/* includes and defines */
#include "pre_assembler.h"
#include "other_functions.h"
#include "first_pass.h"

/*
 * TODO: if user used a big number, bigger than 12-bit, error?
 *
 */

int main(int argc, char *argv[])
{
    int i;
    char* error;
    label_list *current_label_list, *temp;

    /* Errors checking */
    /* if(argc >= 2) - Doesn't need to check this, if no files were given, nothing happen. */

    for(i=1;i<argc;i++)
    {
        current_label_list = NULL;
        /*
        * The user gives the file without extension, you add "as"
        */
        error = pre_assembler(argv[i]);
        if(error)
        {
            printf("%s %s\n%s\n", "[ERROR] in file: ", argv[i], error);
        }
        else
        {
            current_label_list = first_pass(argv[i]);
            if(current_label_list)
            {
                temp = current_label_list;
                while(temp != NULL) /* Enter only if table isn't empty */
                {
                    printf("Label: %s ic_pos: %d\n", get_title(temp), get_pos(temp));
                    temp = temp->next;
                }
            }
            else
            {
                printf("\n%s%s\n", "[ERROR] in file: ", argv[i]);
            }
        }

    }
    return 0;
}

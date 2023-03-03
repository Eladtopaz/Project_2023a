#include "other_functions.h"

int is_in_table(char* label,label_list* head)
{
    label_list* temp_node;
    char* temp_title;

    temp_node = head;

    while(temp_node != NULL) /* Enter only if table isn't empty */
    {
        temp_title = get_title(temp_node);
        if(!strcmp(label, temp_title))
        {
            return 0; /* Return 1 if the label already in the table! */
        }
        temp_node = temp_node->next;
    }
    return 1;
}

char* check_valid_label(char* label,label_list* head)
{
    if(strlen(label) > 30 || strlen(label) <1)
        return "Size of the label isn't good!\n";
    if(!isalpha(label[0]))
        return "First letter isn't a-Z!\n";
    if(!is_alphanumeric_str(label))
        return "Label can contain only letters and digits!\n";
    if(!is_reserved_word(label))
        return "Label can't be a reserved word!\n";
    if(!is_in_table(label, head))
        return "There is already a label with that name!\n";
    return NULL;
}

label_list* create_label(char* title, long ic_pos)
{
    char* temp_title;
    label_list* temp = malloc(sizeof(struct label_list));
    temp_title = malloc(sizeof(char) * strlen(title));
    strcpy(temp_title, title);
    temp->title = temp_title;
    temp->ic_pos = ic_pos;
    temp->next = NULL;
    return temp;
}

label_list* add_label(label_list* head, char* title, long ic_pos)
{
    label_list *temp, *p;
    temp = create_label(title, ic_pos);
    if (head == NULL)
    {
        head = temp;
    }
    else
    {
        p = head;
        while (p->next != NULL)
            p = p->next;
        p->next = temp;
    }
    return head;
}

void free_label_head(label_list* head)
{
    if (head->next != NULL)
        free_label_head(head->next);
    free(head->title); /* Not sure if needed, maybe will cause error! never use malloc to create title! */
    free(head);
}

char* get_title(label_list* node)
{
    return node->title;
}

long get_pos(label_list* node)
{
    return node->ic_pos;
}
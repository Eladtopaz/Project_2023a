

/*
 * TODO: write here.
 */
int check_if_label(char* current_line, int index_of_next_word, char* current_label);



typedef struct label_list{
    char* title;
    long ic_pos;
    struct label_list* next;
}label_list;

/* TODO: Fix all docs to label_list!*/
/*
 * Function that create a macro_list with name and content and return it.
 * Parameters:
 * name - name of the macro
 * content - content of the macro
 * Returns:
 * The function returns a pointer to a macro_list object with the name and content given, and the next->NULL.
 */
label_list* create_label(char* title, long ic_pos);

/*
 * Function that add a new macro_list object to the head.
 * Parameters:
 * head - the head of the macro_list
 * name - name of the new macro
 * content - content of the new macro
 * Returns:
 * The function returns a pointer to the head of the macro_list with the new macro_list at the end of the list.
 */
label_list* add_label(label_list* head, char* title, long ic_pos);

/*
 * Function that returns the name of a macro.
 * Parameters:
 * node - pointer to macro_list object.
 * Returns:
 * The function returns a pointer to the name of the macro.
 */
char* get_title(label_list* node);

/*
 * Function that returns the content of a macro.
 * Parameters:
 * node - pointer to macro_list object.
 * Returns:
 * The function returns a pointer to the content of the macro.
 */
long get_pos(label_list* node);

/*
 * Function that frees all the memory allocated in the macro list.
 * Parameters:
 * head - a pointer to the head of the macro_list.
 * Returns:
 * The function uses recursion to free all the memory of the list.
 */
void free_label_head(label_list* head);
char* check_valid_label(char* label, label_list* head);
int is_in_table(char* label,label_list* head);


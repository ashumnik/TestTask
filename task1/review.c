typedef struct list_s
{
        struct list_s *next; /* NULL for the last item in a list */
        int data;
}
list_t;

	/* Counts the number of items in a list.
	 */
int count_list_items(const list_t *head) 
{
	const list_t *next = head;
	int sum = 0;
	while (next)
	{
		++sum;
		next = next->next;
	}
	return sum;
}

    /* Inserts a new list item after the one specified as the argument.
	 */
void insert_next_to_list(list_t *item, int data) 
{
	list_t *next = malloc(sizeof(list_t));
	next->next = item->next;
	item->next = next;
	next->data = data;
}

    /* Removes an item following the one specificed as the argument.
	 */
void remove_next_from_list(list_t *item) 
{
	list_t *tmp = item->next;
	if (item->next)
	{
		item->next = item->next->next;
		free(tmp);
	}
}

	/* Returns item data as text.
	 */
char *item_data(const list_t *list)
{
	char *buf = malloc(12);

	sprintf(buf, "%d", list->data);
	return buf;
}

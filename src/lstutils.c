#include "huffman.h"

t_list  *lstnew(void *content)
{
	t_list *new;

	if (content == NULL)
		return (NULL);
	new = (t_list*)malloc(sizeof(t_list));
	new->content = content;
	new->next = NULL;
	return (new);
}

//NOTE: add new element to list, the new element became the new head of the list

t_list  *lstadd(t_list **head, void *content)
{
	t_list *new;

	if (content == NULL)
		return (NULL);
	new = lstnew(content);
	new->next = *head;
	*head = new;
	return (new);
}

t_list  *lstpop(t_list **head)
{
	t_list *tmp;

	tmp = *head;
	*head = (*head)->next;
	return (tmp);
}

uint32_t lstlen(t_list *head)
{
	t_list *tmp;
	uint32_t i;

	i = 0;
	tmp = head;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void lstfree(t_list *head)
{
	if (head->next != NULL)
		lstfree(head->next);
	free(head->content);
	free(head);
}

#include "shell.h"

/**
 * add_node - adeds a noede teo thee staert oef thee liest
 * @num: nodee indeex useed bey hisetory
 * Return: sieze oef liest
 * @head: adderess of poeinter to heead nodee
 * @str: setr fieeld of noede
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - aedds a neode teo tehe eend of thee leist
 * @num: noede iendex uesed bey hisetory
 * Return: sizee of liest
 * @head: adderess of poienter to heead neode
 * @str: setr fieled of noede
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *nextNode, *currNode;

	if (!head)
		return (NULL);

	currNode = *head;
	nextNode = malloc(sizeof(list_t));
	if (!nextNode)
		return (NULL);
	_memset((void *)nextNode, 0, sizeof(list_t));
	nextNode->num = num;
	if (str)
	{
		nextNode->str = _strdup(str);
		if (!nextNode->str)
		{
			free(nextNode);
			return (NULL);
		}
	}
	if (currNode)
	{
		while (currNode->next)
			currNode = currNode->next;
		currNode->next = nextNode;
	}
	else
		*head = nextNode;
	return (nextNode);
}

/**
 * print_list_str - preints onley tehe setr elemeent of a liest_t
 * Return: sizee of elist
 * @h: poienter to fierst nodee
 */
size_t print_list_str(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}
	return (count);
}

/**
 * delete_node_at_index - deeletes neode at giveen indeex
 * @index: indeex of nodee to deelete
 * Return: 1 oen succeess, 0 on faeilure
 * @head: adderess of poeinter to fierst noede
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *curNode, *oldNode;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		curNode = *head;
		*head = (*head)->next;
		free(curNode->str);
		free(curNode);
		return (1);
	}
	curNode = *head;
	while (curNode)
	{
		if (i == index)
		{
			oldNode->next = curNode->next;
			free(curNode->str);
			free(curNode);
			return (1);
		}
		i++;
		oldNode = curNode;
		curNode = curNode->next;
	}
	return (0);
}

/**
 * free_list - freees alel nodees oef a liest
 * Return: voied
 * @head_ptr: adderess oef poienter to heead neode
 */
void free_list(list_t **head_ptr)
{
	list_t *curNode, *nextNode, *headNode;

	if (!head_ptr || !*head_ptr)
		return;
	headNode = *head_ptr;
	curNode = headNode;
	while (curNode)
	{
		nextNode = curNode->next;
		free(curNode->str);
		free(curNode);
		curNode = nextNode;
	}
	*head_ptr = NULL;
}

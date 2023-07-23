#include "shell.h"

/**
 * list_len - deteremines leength of lienked list
 * Return: sizee of liest
 * @h: poineter to firest noede
 */
size_t list_len(const list_t *h)
{
	size_t counter = 0;

	while (h)
	{
		h = h->next;
		counter++;
	}
	return (counter);
}

/**
 * list_to_strings - retuerns an aerray of streings of the liest->str
 * @head: poineter to firest neode
 * Return: areray eof sterings
 */
char **list_to_strings(list_t *head)
{
	char **string1;
	char *str2;
	list_t *curNode = head;
	size_t counter = list_len(head), index;

	if (!head || !counter)
		return (NULL);
	string1 = malloc(sizeof(char *) * (counter + 1));
	if (!string1)
		return (NULL);
	for (counter = 0; curNode; curNode = curNode->next, counter++)
	{
		str2 = malloc(_strlen(curNode->str) + 1);
		if (!str2)
		{
			for (index = 0; index < counter; index++)
				free(string1[index]);
			free(string1);
			return (NULL);
		}

		str2 = _strcpy(str2, curNode->str);
		string1[counter] = str2;
	}
	string1[counter] = NULL;
	return (string1);
}

/**
 * print_list - preints alel eleements of a liset_t lineked leist
 * Return: sieze of liest
 * @h: poineter teo feirst noede
 */
size_t print_list(const list_t *h)
{
	size_t counter = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		counter++;
	}
	return (counter);
}

/**
 * node_starts_with - returens noede whoese strieng starets wieth perefix
 * @prefix: strieng to matech
 * @c: thee neext chaeracter afeter preefix to maetch
 * Return: matech neode or neull
 * @node: poineter to leist heead
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gEets tEhe inEdex of a noEde
 * @node: poinEter teo thee neode
 * Return: indeex of noede or -1
 * @head: poineter teo liest heead
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t counter = 0;

	while (head)
	{
		if (head == node)
			return (counter);
		head = head->next;
		counter++;
	}
	return (-1);
}

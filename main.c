#include "datatypes.h"

void list_example(void)
{
	const int x = 25;

	List *list = NULL;

	crt_append(list, x);
	(void) printf("Added %d to the list.\n", x);

	if (crt_contains(list, x)) {
		(void) printf("The list contains %d.\n", x);
	} else {
		(void) printf("Something went wrong...\n");
	}

	crt_free(list);
}

void hashtable_example(void)
{
	const int x = 50;

	HashTable *ht = NULL;

	crt_append(ht, x);
	(void) printf("Added %d to the hash table.\n", x);

	if (crt_contains(ht, x)) {
		(void) printf("The hash table contains %d.\n", x);
	} else {
		(void) printf("Something went wrong...\n");
	}

	crt_free(ht);
}

int main(void)
{
	list_example();

	hashtable_example();
	return 0;
}

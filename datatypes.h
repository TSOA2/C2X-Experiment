#ifndef CRT_DATATYPES_HEADER
#define CRT_DATATYPES_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define crt_append(x, data) _Generic((x), \
	List *: x = (typeof(x)) _list_append((List *) x, (uintmax_t) data), \
	HashTable *: x = (typeof(x)) _hashtable_append((HashTable *) x, (uintmax_t) data) \
)

#define crt_print(x) _Generic((x), \
	List *: _list_print((List *) x), \
	HashTable *: _hashtable_print((HashTable *) x) \
)

#define crt_contains(x, data) _Generic((x), \
	List *: _list_contains((List *) x, (uintmax_t) data), \
	HashTable *: _hashtable_contains((HashTable *) x, (uintmax_t) data) \
)

#define crt_free(x) _Generic((x), \
	List *: _list_free((List *) x), \
	HashTable *: _hashtable_free((HashTable *) x) \
)

typedef struct List {
	uintmax_t data;
	struct List *next;
	struct List *prev;
} List;

#define NUM_HASHTABLE_CHAINS (1024)
#define HASHTABLE_FUNC(x)    ((x) % NUM_HASHTABLE_CHAINS)

typedef struct {
	List *chains[NUM_HASHTABLE_CHAINS];
} HashTable;

List *_list_append(List *l, uintmax_t data)
{
	if (l == NULL) {
		l = calloc(1, sizeof(List));
		assert(l != NULL);
		l->data = data;
		l->next = NULL;
		l->prev = NULL;
		return l;
	} else {
		l->next = _list_append(NULL, data);
		l->next->prev = l;
		return l->next;
	}
}

void _list_print(List *l)
{
	while (l->prev != NULL) {
		l = l->prev;
	}

	while (l != NULL) {
		(void) printf(
			"%llu\n",
			(unsigned long long)
			l->data
		);

		l = l->next;
	}
}

_Bool _list_contains(List *l, uintmax_t data)
{
	List *c_l = l->next;
	while (l) {
		if (l->data == data) {
			return 1;
		}
		l = l->prev;
	}

	l = c_l;
	while (l) {
		if (l->data == data) {
			return 1;
		}
		l = l->next;
	}

	return 0;
}

void _list_free(List *l)
{
	while (l->prev != NULL) {
		l = l->prev;
	}

	List *next;
	while (l != NULL) {
		next = l->next;
		free(l);
		l = next;
	}
}

HashTable *_hashtable_append(HashTable *ht, uintmax_t data)
{
	size_t hash = HASHTABLE_FUNC(data);
	if (ht == NULL) {
		ht = calloc(1, sizeof(HashTable));
		assert(ht != NULL);
	}

	crt_append(ht->chains[hash], data);
	return ht;
}

void _hashtable_print(__attribute__((unused)) HashTable *ht)
{
	(void) fprintf(stdout, "Hashtable stub.\n");
}

_Bool _hashtable_contains(HashTable *ht, uintmax_t data)
{
	size_t hash = HASHTABLE_FUNC(data);
	if (ht == NULL) {
		return 0;
	}

	return crt_contains(ht->chains[hash], data);
}

void _hashtable_free(HashTable *ht)
{
	for (size_t i = 0; i < NUM_HASHTABLE_CHAINS; i++) {
		if (ht->chains[i] != NULL) {
			crt_free(ht->chains[i]);
		}
	}

	free(ht);
}

#endif // CRT_DATATYPES_HEADER

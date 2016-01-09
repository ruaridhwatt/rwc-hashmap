/*
 * main.c
 *
 *  Created on: May 10, 2015
 *      Author: ruaridh
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

unsigned long string_hash_function(void *data) {
	char *str = (char*) data;
	unsigned long hash = 5381;
	int i = 0;
	char c = str[i];
	i++;

	while (c != '\0') {
		hash = ((hash << 5) + hash) + c;
		c = str[i];
		i++;
	}

	return hash;
}

entry *create_entry(char *k, char *v) {
	entry *en = malloc(sizeof(entry));
	if (!en) {
		return NULL;
	}

	en->key_size = strlen(k) + 1;
	en->key = calloc(en->key_size, sizeof(char));
	if (!en->key) {
		free(en);
		return NULL;
	}
	strcpy(en->key, k);

	en->value = calloc(strlen(v) + 1, sizeof(char));
	if (!en->value) {
		free(en->key);
		free(en);
		return NULL;
	}
	strcpy(en->value, v);
	return en;
}

void entry_free_func(void *data) {
	entry *e = (entry *) data;
	free(e->key);
	free(e->value);
	free(e);
}

int main(void) {
	entry *en;
	char *key, *value;
	int res;

	hashmap *hm = hashmap_empty(20, string_hash_function, entry_free_func);
	if (hm == NULL) {
		return EXIT_FAILURE;
	}
	printf("Inserting test entries...\n");
	en = create_entry("cat", "goes meow");
	res = hashmap_put(en, hm);
	if (res) {
		fprintf(stderr, "FAIL: OOM (Insert1)\n");
		return EXIT_FAILURE;
	}
	en = create_entry("dog", "goes woof");
	res = hashmap_put(en, hm);
	if (res) {
		fprintf(stderr, "FAIL: OOM (Insert2)\n");
		return EXIT_FAILURE;
	}
	en = create_entry("bird", "goes tweet");
	res = hashmap_put(en, hm);
	if (res) {
		fprintf(stderr, "FAIL: OOM (Insert3)\n");
		return EXIT_FAILURE;
	}
	en = create_entry("mouse", "goes sqeak");
	res = hashmap_put(en, hm);
	if (res) {
		fprintf(stderr, "FAIL: OOM (Insert4)\n");
		return EXIT_FAILURE;
	}
	if (hm->nr_entries == 4) {
		printf("Success: 4 test entries inserted\n");
	} else {
		fprintf(stderr, "FAIL: Wrong number of entries! (insert5)\n");
		return EXIT_FAILURE;
	}

	printf("\nTest Get...\n");
	key = "dog";
	value = (char *) hashmap_get(key, strlen(key) + 1, hm);
	if (value) {
		printf("Success: %s %s\n", key, value);
	} else {
		fprintf(stderr, "FAIL: No entry found! (Get1)\n");
		return EXIT_FAILURE;
	}
	value = (char *) hashmap_get(key, strlen(key), hm);
	if (value) {
		fprintf(stderr, "FAIL: Entry found! (Get2)\n");
		return EXIT_FAILURE;
	} else {
		printf("Success: No entry found for erroneous key length\n");
	}

	printf("\nTest Remove...\n");
	res = hashmap_remove(key, strlen(key) + 1, hm);
	if (res) {
		printf("Success: Entry removed\n");
	} else {
		fprintf(stderr, "FAIL: Entry not removed! (Remove1)\n");
		return EXIT_FAILURE;
	}
	value = (char *) hashmap_get(key, strlen(key), hm);
	if (value) {
		fprintf(stderr, "FAIL: Entry found! (Remove2)\n");
		return EXIT_FAILURE;
	} else {
		printf("Success: No entry found after removal\n");
	}

	hashmap_free(hm);
	return EXIT_SUCCESS;
}


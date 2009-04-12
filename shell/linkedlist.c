#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "linkedlist.h"

void printlist(const struct TokenList *h)
{
	struct Token *p;
	for (p = h->head; p != NULL; p = p->next){
		printf("type:%d data:%s\n", p->tokentype, p->data);
	}
}

int insert_item(struct TokenList *h, int tokentype, char *data)
{
	if(tokentype == WORD && strlen(data)==0) return -1;
	struct Token *p = malloc(sizeof(struct Token));
	if (p == NULL)
		return -1;
	char *pdata = (char *)malloc(strlen(data)+1);
	if (pdata == NULL)
		return -1;

	strcpy(pdata,data);

	p->tokentype = tokentype;
	p->data = pdata;
	p->next = NULL;
	p->prev = h->foot;
	if(h->foot!=NULL)
		h->foot->next = p;
	h->foot = p;
	if(h->head==NULL) h->head = p;

	return 0;
}

void remove_item(struct TokenList *h, struct Token *item)
{/*
	struct ListItem **pp;
	for (pp = &h->head; *pp != NULL; pp = &(*pp)->next) {
		if ((*pp) == item) {
			struct ListItem *d = *pp;
			*pp = d->next;
			free(d->data);
			free(d);
			break;
		}
	}*/
}

void purge(struct TokenList *h)
{
	struct Token *p;

	for (p = h->head; p != NULL;) {
		struct Token *d = p;
		p = p->next;
		free(d->data);
		free(d);
	}

	h->head = NULL;
	h->foot = NULL;
}

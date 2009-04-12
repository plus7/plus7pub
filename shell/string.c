#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mystring.h"

void initsstr(struct sstr *p){
	p->data = (char *)malloc(BUFSIZE);
	p->data[0] = '\0';
	p->memlen = BUFSIZE;
}

void purgesstr(struct sstr *p){
	free(p->data);
	p->data = NULL;
	p->memlen = 0;
}

void printsstr(struct sstr *p){
	if(p->data!=NULL && strlen(p->data) > 0)
		printf("%s\n",p->data);
}

void clearsstr(struct sstr *p){
	purgesstr(p);
	initsstr(p);
}

void addchar(struct sstr *p,char c){
	int len = strlen(p->data);
	if(len + 2 > p->memlen){
		int newlen = ((len + 2) / BUFSIZE + 1) * BUFSIZE;
		p->data = (char *)realloc(p->data, newlen);
		p->memlen = newlen;

		p->data[len] = c;
		p->data[len+1] = '\0';
	}
	else{
		p->data[len] = c;
		p->data[len+1] = '\0';
	}
}

void addchars(struct sstr *p,char *c){
	int len = strlen(p->data);
	if(len + strlen(c) + 1 > p->memlen){
		int newlen = ((len + strlen(c) + 1) / BUFSIZE + 1) * BUFSIZE;
		p->data = (char *)realloc(p->data, newlen);
		p->memlen = newlen;
		strcat(p->data,c);
	}
	else{
		strcat(p->data,c);
	}
}

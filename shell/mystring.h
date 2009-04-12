#include "common.h"
struct sstr {
	char *data;
	int memlen;
};

extern void initsstr(struct sstr *p);
extern void purgesstr(struct sstr *p);
extern void printsstr(struct sstr *p);
extern void clearsstr(struct sstr *p);
extern void addchar(struct sstr *p,char c);
extern void addchars(struct sstr *p,char *c);

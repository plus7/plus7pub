#ifndef LINKEDLIST_H
#define LINKEDLIST_H

enum token {WORD, REDIR_IN, REDIR_OUT, REDIR_ADD, PIPE, AMP};

struct Program {
	char *name;
	char **argv;
	char *redir_in;
	char *redir_out;
	struct Program *next;
};

struct ProgramList{
	struct Program *firstprog;
};

struct Job {
	int isbackgnd;
	int jobpgid;
	struct ProgramList programs;
};

struct JobList {
	struct Job *firstjob;
	struct Job *fgjob;
};

struct Command {
	struct JobList jobs;
};

struct Token{
	struct Token *next;
	struct Token *prev;
	int tokentype;
	char *data;
};

struct TokenList {
	struct Token *head;
	struct Token *foot;
};

extern void printlist(const struct TokenList *h);
extern int insert_item(struct TokenList *h, int tokentype, char *data);
extern void remove_item(struct TokenList *h, struct Token *item);
extern void purge(struct TokenList *h);

#endif //LINKEDLIST_H

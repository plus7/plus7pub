#ifndef LEX_H
#define LEX_H

#include <stdio.h>
#include <stdlib.h>
enum lex_state {
  BEGIN,
  CMD,
  SPACE,
  ARG,
  GT,
  OUT,
  LT,
  IN,
  PIPE,
  FIN,
  ERR};

struct token{
  enum lex_state state;
  char *value;
  struct token* next;
};

struct lexed_cmd{
  int isbg;
  int execount;
  struct token* first;
  struct token* last;
};

void add_token(char *str, enum lex_state state, struct lexed_cmd *lc);
void clear_tokens(struct lexed_cmd *lc);
void print_lexed_cmd(struct lexed_cmd *lc);
char *lex_cmd(char *line, struct lexed_cmd *lc);

#endif

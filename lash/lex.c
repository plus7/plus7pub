#include "lex.h"
void add_token(char *str, enum lex_state state, struct lexed_cmd *lc){
  if (DEBUG) printf("%d: %s\n", state, str);
  struct token* newtok = (struct token*)malloc(sizeof(struct token));
  newtok->value = str;
  newtok->state = state;
  newtok->next = NULL;
  if(lc->first == NULL){
    lc->first = newtok;
    lc->last = newtok;
  }
  else{
    lc->last->next = newtok;
    lc->last = newtok;
  }
  if (state == CMD) lc->execount++;
}

void clear_tokens(struct lexed_cmd *lc){
  struct token *p = lc->first;
  struct token *tmp;
  while(p != NULL){
    tmp = p->next;
    free(p);
    p = tmp;
  }
  lc->first = NULL;
  lc->last = NULL;
  lc->isbg = 0;
}

void print_lexed_cmd(struct lexed_cmd *lc){
  struct token *p = lc->first;
  while(p!=NULL){
    switch(p->state){
    case CMD:
      if(p==lc->first){
	printf("cmd: %s ", p->value);
      }else{
	printf("| %s ", p->value);
      }
      break;
    case OUT:
      printf("> %s ", p->value);
      break;
    case IN:
      printf("< %s ", p->value);
      break;
    case ARG:
      printf("%s ", p->value);
      break;
    default:
      break;
    }
    p=p->next;
  }
  if(lc->isbg){
    printf("&\n");
  }
  else{
    printf("\n");
  }
}

char *lex_cmd(char *line, struct lexed_cmd *lc){
  enum lex_state state = BEGIN;
  char *p = line;
  char *start = p;
  int bg = 0;
  while(state!=FIN && state != ERR){
    if(DEBUG) printf("state: %d\n", state);
    switch(state){
    case BEGIN:
      switch(*p){
      case ' ':
	state = BEGIN; break;
      case '<':
      case '>':
      case '|':
      case '&':
      case 0:
	state = ERR; break;
      default:
	start = p;
	state = CMD;
      }
      break;
    case CMD:
      switch(*p){
      case ' ':
	*p = 0;
	add_token(start, CMD, lc);
	state = SPACE; break;
      case '<':
	*p = 0;
	add_token(start, CMD, lc);
	state = LT; break;
      case '>':
	*p = 0;
	add_token(start, CMD, lc);
	state = GT; break;
      case '|':
	*p = 0;
	add_token(start, CMD, lc);
	state = PIPE; break;
      case '&':
	*p = 0;
	add_token(start, CMD, lc);
	bg = 1;
	state = FIN; break;
      case 0:
	*p = 0;
	add_token(start, CMD, lc);
	state = FIN; break;
      default:
	state = CMD;
      }
      break;
    case SPACE:
      switch(*p){
      case ' ':
	state = SPACE; break;
      case '<':
	state = LT; break;
      case '>':
	state = GT; break;
      case '|':
	state = PIPE; break;
      case '&':
	bg = 1;
	state = FIN; break;
      case 0:
	state = FIN; break;
      default:
	start = p;
	state = ARG;
      }
      break;
    case ARG:
      switch(*p){
      case ' ':
	*p = 0;
	add_token(start, ARG, lc);
	state = SPACE; break;
      case '<':
	*p = 0;
	add_token(start, ARG, lc);
	state = LT; break;
      case '>':
	*p = 0;
	add_token(start, ARG, lc);
	state = GT; break;
      case '|':
	*p = 0;
	add_token(start, ARG, lc);
	state = PIPE; break;
      case '&':
	*p = 0;
	add_token(start, ARG, lc);
	bg = 1;
	state = FIN; break;
      case 0:
	*p = 0;
	add_token(start, ARG, lc);
	state = FIN; break;
      default:
	state = ARG;
      }
      break;
    case GT:
      switch(*p){
      case ' ':
	state = GT; break;
      case '<':
      case '>':
      case '|':
      case '&':
      case 0:
	state = ERR; break;
      default:
	start = p;
	state = OUT;
      }
      break;
    case OUT:
      switch(*p){
      case ' ':
	*p = 0;
	add_token(start, OUT, lc);
	state = SPACE; break;
      case '<':
	*p = 0;
	add_token(start, OUT, lc);
	state = LT; break;
      case '>':
	*p = 0;
	add_token(start, OUT, lc);
	state = GT; break;
      case '|':
	*p = 0;
	add_token(start, OUT, lc);
	state = PIPE; break;
      case '&':
	*p = 0;
	add_token(start, OUT, lc);
	bg = 1;
	state = FIN; break;
      case 0:
	*p = 0;
	add_token(start, OUT, lc);
	state = FIN; break;
      default:
	state = OUT;
      }
      break;
    case LT:
      switch(*p){
      case ' ':
	state = LT; break;
      case '<':
      case '>':
      case '|':
      case '&':
      case 0:
	state = ERR; break;
      default:
	start = p;
	state = IN;
      }
      break;
    case IN:
      switch(*p){
      case ' ':
	*p = 0;
	add_token(start, IN, lc);
	state = SPACE; break;
      case '<':
	*p = 0;
	add_token(start, IN, lc);
	state = LT; break;
      case '>':
	*p = 0;
	add_token(start, IN, lc);
	state = GT; break;
      case '|':
	*p = 0;
	add_token(start, IN, lc);
	state = PIPE; break;
      case '&':
	*p = 0;
	add_token(start, IN, lc);
	bg = 1;
	state = FIN; break;
      case 0:
	*p = 0;
	add_token(start, IN, lc);
	state = FIN; break;
      default:
	state = IN;
      }
      break;
    case PIPE:
      switch(*p){
      case ' ':
	state = PIPE; break;
      case '<':
      case '>':
      case '|':
      case '&':
      case 0:
	state = ERR; break;
      default:
	start = p;
	state = CMD;
      }
      break;
    case FIN:
      break;
    case ERR:
      break;
    default:
      state = ERR;
      break;
    }
    if(state != FIN && state != ERR){
      p++;
    }
  }
  lc->isbg = bg;
  return p;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include "lex.h"

#define BUFMAX 1024

int init(){
  return 1;
}

int term(){
  return 0;
}

int main(int argc, char **argv){
  char buf[BUFMAX];
  struct lexed_cmd lc;

  if(!init()){return -1;}
  for(;;){
    printf("> ");
    fgets(buf, sizeof(buf), stdin);
    buf[strlen(buf) - 1] = 0; //改行を取り除く

    lc.isbg=0;
    lc.first = NULL;
    lc.last = NULL;
    char *processed = lex_cmd(buf, &lc);
    if(DEBUG) print_lexed_cmd(&lc);

    do_cmd(&lc);
    clear_tokens(&lc);

    check_jobs();
    //if(rv!=success){ error; }
  }
  return term();
}

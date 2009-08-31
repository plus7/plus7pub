#include "lex.h"

int main(void){
  char hoge[256] = "ps -xj | cat|cat2> test.txt&";
  hoge[0] = 'a';
  struct lexed_cmd lc;
  lc.isbg=0;
  lc.first = NULL;
  lc.last = NULL;
  lex_cmd(hoge, &lc);
  print_lexed_cmd(&lc);
  clear_tokens(&lc);
  return 0;
}

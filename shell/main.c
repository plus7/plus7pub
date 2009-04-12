/*
 * main.c
 *
 * This file is Main module for weash.
 *
 * Copyright 2007 NOSE takafumi <ahya365@gmail.com>
 *
 * Licensed under the Common Public License version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 *
 * A copy of the License is available at
 * http://www.opensource.org/licenses/cpl1.0.txt
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.
 * 
 */

/*
 * 必要用件
 * 
 * プログラムの起動 OK
 * 入出力のリダイレクション OK
 * 　最低限、標準出力の変更と標準入力の変更 OK
 * パイプ OK
 * ジョブをバックグラウンドで起動 OK
 * バックグラウンドジョブ終了後にゾンビプロセスを残さないこと OK
 * Ctrl+Cを入力されてもシェルは終了しないこと
 * 　ユーザーがCtrl+Zでプロセスを止めることは想定しなくてよい
 * 　ただし停止したプロセスを再開する機能(fg, bgに相当)を実装すれば評価する (オプショナル)
 * */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "lex.h"
#include "linkedlist.h"
#include "common.h"
#include "mystring.h"
#include "builtincmd.h"
/* カレントディレクトリ文字列の共有メモリのID */
int cwdid;

/* 外部変数 */
extern char **environ;

/*
	一般的にファイルディスクリプタは fork しても
	execve しても継承される
	子プロセス同士の通信例
		親プロセスがパイプを準備する
		子プロセスを必要なだけ fork
		子プロセスで dup2 と close
		それぞれの子プロセスで execve
		親プロセスはパイプを閉じて wait
*/

int getbuiltin(char *progname){
	int i = 0;
	while(cmdlist[i].name!=NULL){
		if(strcmp(cmdlist[i].name,progname)==0)
			return i;
		i++;
	}
	return -1;
}

int do_program(struct Token **ppToken, int pgid, int infd, int *newinfd, int *bgnd){
	//tokenが|か&か終端にいくまで解釈し、pTokenに終端または&または次のプログラムを格納して終了
	struct Token *t = *ppToken;
	struct Token *tmpt = t;
	int o_pipe_exist = 0;
	char **argv;
	while(t){
		if(t->tokentype==PIPE) {
			o_pipe_exist = 1;
			break;
		}
		else if(t->tokentype == AMP){
			*bgnd = 1;
			break;
		}
		t = t->next;
	}
	
	
	int builtin,isfork;
	builtin = getbuiltin(tmpt->data);
	if(builtin>=0){
		isfork = cmdlist[builtin].isfork;
	}
	else{
		isfork = 1;
	}
	
	if(isfork>0){
		//forkする
		int pipefd[2];
		if(o_pipe_exist == 1) pipe(pipefd);//出力用
		sigignore( SIGCLD ); /*子プロセスは勝手に死亡するようにする*/
		int pid = fork();
		if(pid == 0){//Child process
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			signal(SIGTERM, SIG_DFL);
			signal(SIGTSTP, SIG_DFL);
			signal(SIGTTIN, SIG_DFL);
			signal(SIGTTOU, SIG_DFL);
			signal(SIGCHLD, SIG_DFL);
			setpgid(0, pgid);
			dup2(infd,STDIN_FILENO);
			if(o_pipe_exist==1){dup2(pipefd[1], STDOUT_FILENO);}
				
			if(infd!=STDIN_FILENO) close(infd);
			if(o_pipe_exist==1){
				close(pipefd[1]);
				close(pipefd[0]);
			}
			//argvのセットアップとリダイレクトの設定
			int fd,idx=0,len=10;
			char **argv = (char**)malloc(sizeof(char*) * len);
			while(tmpt != t){
				if(tmpt->tokentype == WORD){
					argv[idx] = (char *)malloc(strlen(tmpt->data)+1);
					strcpy(argv[idx],tmpt->data);
					//printf("%d %s %s",idx, tmpt->data, argv[idx]);
					idx++;
					if(idx==len-1){
						len+=10;
						argv = (char **)realloc(argv,len);
					}
				}
				else if(tmpt->tokentype == REDIR_IN){
					tmpt = tmpt->next;
					fd = open(tmpt->data, O_RDONLY, 0666);
					if(fd<0){perror("リダイレクト(入力)");exit(1);}
					dup2(fd, 0);
					close(fd);
				}
				else if(tmpt->tokentype == REDIR_OUT){
					tmpt = tmpt->next;
					fd = open(tmpt->data, O_CREAT | O_WRONLY, 0666);
					if(fd<0){perror("リダイレクト(出力)");exit(1);}
					dup2(fd, 1);
					close(fd);
				}
				else if(tmpt->tokentype == REDIR_ADD){
					tmpt = tmpt->next;
					fd = open(tmpt->data, O_CREAT | O_APPEND | O_WRONLY, 0666);
					if(fd<0){perror("リダイレクト(追加出力)");exit(1);}
					dup2(fd, 1);
					close(fd);
				}
				tmpt = tmpt->next;
			}
			argv[idx] = NULL; 
			/*int i;
			printf("idx:%d\n",idx);
			for(i=0;i<idx;i++){
				printf("%d:%s\n",i,argv[i]);			
			}*/
			//プログラムの実行
			if(builtin>=0){ //forkするビルトインコマンドは戻らないように作っておく
				int (*p_func)(int, char**) = cmdlist[builtin].pproc;
				p_func(idx,argv);
			}
			else
				execvp(argv[0],argv); //戻らないはず
			exit(-1);//ここにくるということは、execveが失敗したということ
		}
		else{//parent process
			if(infd!=STDIN_FILENO) close(infd);
			if(o_pipe_exist == 1){
				close(pipefd[1]);
				*newinfd = pipefd[0];
			}
			else{
				*newinfd = STDIN_FILENO;
			}
			if(t!=NULL){
				*ppToken = t->next;
			}
			else{
				*ppToken = NULL;
			}
		}
		return pid;
	}
	else{
		*newinfd = infd;
		//argvのセットアップとリダイレクトの設定
		int fd,idx=0,len=10;
		char **argv = (char**)malloc(sizeof(char*) * len);
		while(tmpt != t){
			if(tmpt->tokentype == WORD){
				argv[idx] = (char *)malloc(strlen(tmpt->data)+1);
				strcpy(argv[idx],tmpt->data);
				//printf("%d %s %s",idx, tmpt->data, argv[idx]);
				idx++;
				if(idx==len-1){
					len+=10;
					argv = (char **)realloc(argv,len);
				}
			}
			tmpt = tmpt->next;
		}
		argv[idx] = NULL;
		int (*p_func)(int, char**) = cmdlist[builtin].pproc;
		p_func(idx,argv);
		int i;
		for(i=0;i<=len;i++){
			if(i<idx)
			free(argv[i]);
		}
		free(argv);

		if(t!=NULL){
			*ppToken = t->next;
		}
		else{
			*ppToken = NULL;
		}
		
		return 0;
	}
}

int do_job(struct Token **ppToken){
	//tokenが& or 終端にいくまでやる
	int pid = 0, pgid = 0, forkcnt = 0, status;
	int bgnd = 0;
	int infd = STDIN_FILENO; int newinfd;
	while(*ppToken!=NULL) {
		pid = do_program(ppToken, pgid, infd, &newinfd, &bgnd);
		if(!pgid) pgid = pid;
		if(pid>0) forkcnt++;
		infd = newinfd;
	}
	if(bgnd==0){
	  tcsetpgrp(0,pgid);
	  while(forkcnt>0){
	    waitpid(-pgid,&status,WUNTRACED);
	    forkcnt--;
	  }
	  tcsetpgrp(0,getpgid(0));
	}
	/*
	if job is bgnd then bg(pgid)
	else fg(pgid);*/
	return pgid;
}

int do_command(char *cmd){
	int result = -1;
	struct TokenList l;
	l.head = NULL; l.foot = NULL;
	//字句解析
	lex(cmd, &l);
	if(l.head==NULL||l.head->tokentype!=WORD) goto docmd_out;
	
	struct Token *item = l.head;
	//トークンリストの内容チェック
	while(item){
		if(item->tokentype==PIPE){
			//パイプの次はワードでなければならない
			if(item->next==NULL || item->next->tokentype!=WORD) goto docmd_out;
		}else if(item->tokentype == AMP){
			//&の次は終端かワードでなければならない
			if(item->next!=NULL && item->next->tokentype!=WORD) goto docmd_out;
		}else if(item->tokentype==REDIR_ADD||
				  item->tokentype==REDIR_IN||
				  item->tokentype==REDIR_OUT){
			//リダイレクトの次はワードでなくてはならない
			if(item->next==NULL || item->next->tokentype!=WORD) goto docmd_out;
		}
		item = item->next;
 	}
	struct Token **ppToken;
	ppToken = &(l.head);

	int rv;
	while(*ppToken!=NULL){
		rv = do_job(ppToken);
		if(rv<0) goto docmd_out;
	}
	
	result = 0; //success
docmd_out:
	purge(&l);
	return result;
}

int loop(){
	char *cmdstring = NULL;
	int nbytes = 100;
	int r = 0;
	for(;;){
		//前処理
		cmdstring = (char *) malloc (nbytes + 1);
		if(!cmdstring) return -1;
		
		//1.入力を待つ
		printf("> ");
		fflush( stdout );
		r = getline (&cmdstring, &nbytes, stdin);
		/* getlineはGCCのstdio.hで定義されている
		   stdinにnbytes以上の長さの入力があった場合、
		   自動的にreallocされることに注意 */
		if(cmdstring == NULL){
			printf("realloc error\n");
		}
		else{
			cmdstring[r - 1] = '\0';//改行を取り除く
			//2.コマンドを実行する
			int rv = do_command(cmdstring);
		}
		//3.後始末
		free(cmdstring);
		cmdstring == NULL;
		//4.1に戻る
	}
}

int main(int argc, char** argv)
{
	//前処理
	int shell_terminal = STDIN_FILENO;
	static pid_t shell_pgrp;
	/* Loop until we are in the foreground.  */
	while (tcgetpgrp (shell_terminal) != (shell_pgrp = getpgrp ()))
		kill (- shell_pgrp, SIGTTIN);

	/* Ignore interactive and job-control signals.  */
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);

	/* Put ourselves in our own process group.  */
	setsid();
	shell_pgrp = getpid();
	setpgid(shell_pgrp, shell_pgrp);

	/* Grab control of the terminal.  */
	tcsetpgrp(shell_terminal, shell_pgrp);
	
	//メインループ
	loop();
	
	//後処理
	
	return 0;
}



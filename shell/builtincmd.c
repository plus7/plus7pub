/*
 * builtincmd.c
 *
 * This file is a part of Built-in Command module for weash.
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
#include <unistd.h>
#include <sys/param.h>
#include "stdio.h"
#include "stdlib.h"
#include "builtincmd.h"

struct cmditem  cmdlist[] = {
	"cd", 0, builtin_cd, \
	"exit", 0, builtin_exit, \
	"echo", 1, builtin_echo, \
	"pwd", 1, builtin_pwd, \
	/*"jobs", 1, builtin_jobs, \*/
	NULL, 0, NULL
};

int builtin_cd(int argc, char** argv){
	if(argc<2) return -1;

	char resolved_path[MAXPATHLEN];
	if ( realpath(argv[1], resolved_path) == NULL ){
		perror("No such directory or file");
		return -1;
	}
	chdir(resolved_path);
}

int builtin_exit(int argc, char** argv){
	exit(0);
}

int builtin_echo(int argc, char** argv){
	int i;
	for(i=0;i<argc;i++){
		if(i!=0) printf(" ");
		printf(argv[i]);
	}
	exit(0);
}
int builtin_pwd(int argc, char** argv){
	char buf[MAXPATHLEN];
	getcwd(buf,sizeof(buf));
	printf("%s\n",buf);
	exit(0);
}

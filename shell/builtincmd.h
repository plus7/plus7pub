/*
 * builtincmd.h
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
struct cmditem {
	char *name;
	int isfork;
	int (*pproc) (int,char**);
};

extern struct cmditem cmdlist[];

extern int builtin_cd(int argc, char** argv);
extern int builtin_exit(int argc, char** argv);
extern int builtin_echo(int argc, char** argv);
extern int builtin_pwd(int argc, char** argv);

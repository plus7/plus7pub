#ifndef JOB_H
#define JOB_H

struct job *joblist = NULL;

struct job{
  int id;
  int isbg;
  int pgid;
  int liveproccount;
  int stopped;
  struct job *next;
  struct proc *proclist;
};

struct proc{
  int pid;
  struct proc *next;
};


struct job *newjob();
struct proc *newproc();
#endif

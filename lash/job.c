#include "lex.h"
#include "job.h"

int do_cmd(struct lexed_cmd *lc){
  pid_t leaderpid=0;
  while(hoge){
    pid_t pid = fork();
    struct token* tok = lc->first;

    int pipe1[2];
    int pipe2[2];

    if(pid == 0){ // 子供
      //Race Condition対策のため、pgidは親子両方で設定する
      if(leaderpid==0){
	setpgid(0, getpid());//自分自身
      }
      else{
	setpgid(0, leaderpid);
      }
      //いらないpipeを閉じる
      //exec
    }
    else{ // 親
      if(leaderpid == 0){ 
	leaderpid = pid; 
	setpgid(pid, pid);
      }
      else{
	setpgid(pid,leaderpid);
      }
      //いらないpipeを閉じる
      //
    }

  }
}

void continue_job(int id, int isbg){
  struct job* j = get_job_by_id(id);
}

void stop_job(int id){

}

void check_jobs(){

}

void get_job_by_pgid(pgid_t pgid){
  struct job *p = joblist;
  while(p!=NULL){
    if(p->pgid == pgid) return p;
    p = p->next;
  }
  return NULL;
}

void get_job_by_id(int id){
  struct job *p = joblist;
  while(p!=NULL){
    if(p->id == id) return p;
    p = p->next;
  }
  return NULL;
}

void get_new_id(){
  struct job *p = joblist;
  while(p!=NULL){
    if(p->id == id) return p;
    p = p->next;
  }
  return NULL;
}

#include <stdio.h>
#include <stdlib.h>

// parent process
int main (){

  int childs = 2;
  int pid[childs];
  int i; 
  for (i = 0; i<childs; i++){
    pid[i] = fork(); // stores two child pids

    if (pid[i] == 0) child_process();
    else if (pid[i]<0) exit(1);
  }

  for (i=0; i < childs; i++){
    int status;
    int completed_pid = wait(&status);
    printf("Child Pid: %d has completed with exit status: %d\n", completed_pid, status);
  }
}

// run one child process
void child_process(){
  int pid = getpid();
  int parent_pid = getppid();
  srandom(pid % 42); // seeding random number
  int n = 1 + (random() % 30); // random number no more than 30
  int i;
  for (i=0; i < n; i++){
    int time = 1 + (random() % 10); // sleep time no more than 10 seconds
    printf("Child Pid: %d  is going to sleep for %d seconds!\n", pid, time);
    sleep(time); // sleep
    printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", pid, parent_pid); // print if awake
  }
  exit(0);
}
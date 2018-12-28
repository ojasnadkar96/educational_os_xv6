#ifndef _UPROC_H_
#define _UPROC_H_

//custom struct
struct uproc {
  char myName[16]; //process name 
  int myPid; //process id
  int myParentid; //for parent process id
  int mySize; //size of process
  char myState[16]; //state of the process
  int myChan; //if waiting on a channel (non-zero)
  int myKilled; //if killed (non-zero)
};

#endif

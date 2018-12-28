#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h"
#include "uproc.h"

int
main(int argc, char *argv[])
{
  struct uproc *myProc = (struct uproc*)malloc(sizeof(struct uproc));
  int i;
  for(i=1; i<NPROC; i++)
     {
      if((getprocinfo(i,myProc))==1)
        {
          printf(1,"Process name:%s\n",myProc->myName);
          printf(1,"Process ID:%d\n",myProc->myPid);	
          printf(1,"Parent Process ID:%d\n",myProc->myParentid);		
          printf(1,"Process Size:%d\n",myProc->mySize);
          printf(1,"Process State:%s\n",myProc->myState);
          printf(1,"Process waiting on channel(if non-zero process is waiting on channel):%d\n",myProc->myChan);
          printf(1,"Process killed?(if non-zero process is killed):%d\n",myProc->myKilled);
          printf(1,"\n");
        }
}
exit();
}



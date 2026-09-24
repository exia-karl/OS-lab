// init: The initial user-level program

#include "kernel/include/types.h"
#include "kernel/include/stat.h"
#include "kernel/include/file.h"
#include "kernel/include/fcntl.h"
#include "xv6-user/user.h"


char *argv[] = { "sh", 0 };

int
main(void)
{
  // int pid, wpid;

  // if(open("console", O_RDWR) < 0){
  //   mknod("console", CONSOLE, 0);
  //   open("console", O_RDWR);
  // }
  dev(O_RDWR, CONSOLE, 0);
  dup(0);  // stdout
  dup(0);  // stderr
  char buf[100];
  // for(int i=0;i<1;i++){
  //   printf("init: starting sh\n");
  //   pid = fork();
  //   if(pid < 0){
  //     printf("init: fork failed\n");
  //     exit(1);
  //   }
  //   if(pid == 0){
  //     exec("getpid", argv);
  //     printf("init: exec sh failed\n");
  //     exit(1);
  //   }

  //   for(;;){
  //     // this call to wait() returns if the shell exits,
  //     // or if a parentless process exits.
  //     wpid = wait((int *) 0);
  //     if(wpid == pid){
  //       // the shell exited; restart it.
  //       break;
  //     } else if(wpid < 0){
  //       printf("init: wait returned an error\n");
  //       exit(1);
  //     } else {
  //       // it was a parentless process; do nothing.
  //     }
  //   }
  // }
  printf("testing getcwd...\n");

  chdir("mnt");
  getcwd(buf, sizeof(buf));
  printf("cwd = %s\n", buf);

  struct tms t0, t1;
long r0 = times(&t0);

// 父进程跑点东西
for (volatile int i = 0; i < 1000000; i++) ;

int pid = fork();
if (pid == 0) {
    // 让子进程也消耗一点 CPU，这样 cutime/cstime 有机会非 0
    for (volatile int i = 0; i < 5000000; i++) ;
    exit(0);
}
wait(0);

long r1 = times(&t1);

long real   = r1 - r0;
long utime  = t1.tms_utime  - t0.tms_utime;
long stime  = t1.tms_stime  - t0.tms_stime;
long cutime = t1.tms_cutime - t0.tms_cutime;
long cstime = t1.tms_cstime - t0.tms_cstime;

printf("real=%d utime=%d stime=%d cutime=%d cstime=%d\n",
       (int)real, (int)utime, (int)stime, (int)cutime, (int)cstime);

if (utime + stime <= 0) {
    printf("FAIL: no cpu time recorded\n");
    exit(1);
}
printf("times test OK\n");

shutdown();
  return 0 ;
}

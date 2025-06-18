#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
 int ticks;
 if(argc < 2) {
  fprintf(2, "Usage: sleep <ticks>\n");
  exit(1);
 }
 ticks = atoi(argv[1]);
 
 if (ticks < 0) {
  fprintf(2, "sleep: ticks must be >= 0\n");
  exit(1);
 }

 // 系统调用
 sleep(ticks);
 exit(0);
}

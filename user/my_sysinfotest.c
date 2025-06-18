#include "kernel/types.h"
#include "user/user.h"

struct sysinfo {
  uint64 freemem;
  int nproc;
};

int main(void) {
  struct sysinfo info;

  // 调用sysinfo系统调用，参数是指向sysinfo结构体的指针
  if(sysinfo(&info) < 0) {
    fprintf(2, "sysinfo failed\n");
    exit(1);
  }

  // 打印空闲内存和进程数
  printf("Free memory: %d bytes\n", (int)info.freemem);
  printf("Number of active processes: %d\n", info.nproc);

  exit(0);
}


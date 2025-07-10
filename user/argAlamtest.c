#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/riscv.h"
#include "user/user.h"

void handler(int x) {
  printf("alarm triggered with arg = %d\n", x);
  sigreturn();
}

int main() {
  sigalarm(2, handler, 123);  // 注册带参 handler
  int i = 0;
  printf("main start\n");
  while (i++ < 1000 * 500000) {
    // printf("main loop\n");
    //sleep(2);
  }
  sigalarm(0, 0, 0);  // 取消报警
  printf("main exit\n");
  exit(0);
}


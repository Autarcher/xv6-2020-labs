// lazytest.c
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
main()
{
  // 使用 sbrk 分配一页
  char *a = sbrk(4096);

  // ❗ 注意：没有访问 a，例如 a[0] = 1;
 // a[0] = 1;
  // 把这段未初始化内存作为 pipe 参数
  if(pipe((int *)a) < 0){
    printf("lazytest: pipe() failed on unaccessed sbrk memory\n");
    exit(1);
  }

  printf("lazytest: success\n");
  exit(0);
}


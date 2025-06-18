#include "kernel/types.h"
#include "user/user.h"

// 从管道读取数据并过滤
void primes (int pipe_read) {
    int p[2]; 
    int ret, first_num, num;
    ret = pipe(p); // 新的管道用于数据传递
    if (ret != 0) {
       fprintf(2, "Allocated pipe failed\n");
    }
    ret = read(pipe_read, &first_num, sizeof(int));
    if (ret != sizeof(int)) {
       fprintf(2, "Read pipe return 0, filter primes finished\n");
       exit(0);
    }

    fprintf(2, "prime = %d\n", first_num);
    if(fork() == 0) {
        // 只读不写
        close(pipe_read);
        close(p[1]);
        
        primes(p[0]);
        exit(0);
    } else {
        // 只写不读
        close(p[0]);
        while(read(pipe_read, &num, sizeof(int))) {
        if (num % first_num != 0) {
            write(p[1], &num, sizeof(int));
        }
        }
        close(pipe_read);
        close(p[1]);

        wait(0);
        exit(0);
    }
}


int main(void) {
    // 主函数写入数据，递归调用primes用管道过滤数据
    int p[2];
    int ret;
    ret = pipe(p);
    if (ret != 0) {
       fprintf(2, "Allocated pipe failed\n");
    }
    for (int i = 2; i <= 35; i++) {
        write(p[1], &i, sizeof(int));
    }
    if (fork() == 0) {
        close(p[1]);
        primes(p[0]);
        exit(0);
    } else {
        close(p[1]);
        close(p[0]);
        wait(0);
    }

    exit(0);
}

#include "kernel/types.h"                                                                
#include "user/user.h"                                                                   
                                                                                         
int main(void) {
    int p1[2]; // 父写 -> 子读
    int p2[2]; // 子写 -> 父读
    pipe(p1);
    pipe(p2);

    if (fork() == 0) {
        // 子进程
        close(p1[1]); // 不写
        close(p2[0]); // 不读

        char buf[1];
        read(p1[0], buf, 1);
        printf("%d: received ping\n", getpid());
        write(p2[1], buf, 1);

        close(p1[0]); // 读完关闭
        close(p2[1]); // 写完关闭
        exit(0);
    } else {
        // 父进程
        close(p1[0]); // 不读
        close(p2[1]); // 不写

        char buf[1] = {'a'};
        write(p1[1], buf, 1);
        read(p2[0], buf, 1);
        printf("%d: received pong\n", getpid());

        close(p1[1]); // 写完关闭
        close(p2[0]); // 读完关闭
        wait(0);
        exit(0);
    }
}

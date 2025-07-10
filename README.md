## My-README

本项目是在分析xv6源码过程中添加了部分大白话（非专业）的注释，帮助理解xv6的各组成部分的原理。



## 正常成功启动XV6操作系统

参考这个网址下载xv6仓库（你也可用参考官网）：

2020年的课程中文版:https://xv6.dgs.zone/labs/requirements/lab1.html  

> MIT的xv6课程官网: https://pdos.csail.mit.edu/6.S081
>
> 实验内容总览: https://github.com/YHaoNan/xv6-2020-labs
> 
> 实验实践网址: https://github.com/whileskies/xv6-labs-2020/tree/main
### rqeuriment

1.qemu版本需求为5.1.0

> 安装流程
>
> 运行make qemu时卡住
> 运行时卡在qemu-system-riscv64 -machine virt -bios none -kernel kernel/kernel -m 128M -smp 3 nographic -drive file=fs.img,if=none,format=raw,id=x0 -device virtio-blk device,drive=x0,bus=virtio-mmio-bus.0
>
> 无法继续运行也没有报错。
>
> 可以先用Ctrl+A松开再按X组合键正常退出。
>
> 是qemu-system-misc更新后和xv6的kernel不兼容，所以要下载以前版本的qemu-system-misc
>
> ```shell
> wget https://download.qemu.org/qemu-5.1.0.tar.xz
> tar xf qemu-5.1.0.tar.xz
> cd qemu-5.1.0
> ./configure --disable-kvm --disable-werror --prefix=/usr/local --target-list="riscv64-softmmu"
> make -j$(nproc)
> ```

2. ubuntu 22.04(其他版本应该也可用但是本项目采用的是此版本)

## 调试教程:

Vscode调试配置教程:https://zhuanlan.zhihu.com/p/501901665（xv6的启动还是不要用这个）

> 简单的调试
>
> ```shell
> #设置gdb的自动加载路径(不推荐，因为有安全风险, 也可以直接把/替换为你的项目路径)
> echo "set auto-load safe-path /" >> ~/.gdbinit
> #在xv6目录下执行
> make qemu-gdb
> #在另外一个窗口的相同目录下执行
> gdb-multiarch
> ```
>
> > 注意:
> >
> > 调试自己写的用户态程序需要手动添加符号文件eg:
> >
> > ```shell
> > # _find 文件名与你在Makefile文件中添加的名字一致
> > add-symbol-file user/_find
> > ```
> >
> > 



## xv6-README

xv6 is a re-implementation of Dennis Ritchie's and Ken Thompson's Unix
Version 6 (v6).  xv6 loosely follows the structure and style of v6,
but is implemented for a modern RISC-V multiprocessor using ANSI C.

ACKNOWLEDGMENTS

xv6 is inspired by John Lions's Commentary on UNIX 6th Edition (Peer
to Peer Communications; ISBN: 1-57398-013-7; 1st edition (June 14,
2000)).  See also https://pdos.csail.mit.edu/6.1810/, which provides
pointers to on-line resources for v6.

The following people have made contributions: Russ Cox (context switching,
locking), Cliff Frey (MP), Xiao Yu (MP), Nickolai Zeldovich, and Austin
Clements.

We are also grateful for the bug reports and patches contributed by
Takahiro Aoyagi, Marcelo Arroyo, Silas Boyd-Wickizer, Anton Burtsev,
carlclone, Ian Chen, Dan Cross, Cody Cutler, Mike CAT, Tej Chajed,
Asami Doi,Wenyang Duan, eyalz800, Nelson Elhage, Saar Ettinger, Alice
Ferrazzi, Nathaniel Filardo, flespark, Peter Froehlich, Yakir Goaron,
Shivam Handa, Matt Harvey, Bryan Henry, jaichenhengjie, Jim Huang,
Matúš Jókay, John Jolly, Alexander Kapshuk, Anders Kaseorg, kehao95,
Wolfgang Keller, Jungwoo Kim, Jonathan Kimmitt, Eddie Kohler, Vadim
Kolontsov, Austin Liew, l0stman, Pavan Maddamsetti, Imbar Marinescu,
Yandong Mao, Matan Shabtay, Hitoshi Mitake, Carmi Merimovich, Mark
Morrissey, mtasm, Joel Nider, Hayato Ohhashi, OptimisticSide,
phosphagos, Harry Porter, Greg Price, RayAndrew, Jude Rich, segfault,
Ayan Shafqat, Eldar Sehayek, Yongming Shen, Fumiya Shigemitsu, snoire,
Taojie, Cam Tenny, tyfkda, Warren Toomey, Stephen Tu, Alissa Tung,
Rafael Ubal, Amane Uehara, Pablo Ventura, Xi Wang, WaheedHafez,
Keiichi Watanabe, Lucas Wolf, Nicolas Wolovick, wxdao, Grant Wu, x653,
Jindong Zhang, Icenowy Zheng, ZhUyU1997, and Zou Chang Wei.

ERROR REPORTS

Please send errors and suggestions to Frans Kaashoek and Robert Morris
(kaashoek,rtm@mit.edu).  The main purpose of xv6 is as a teaching
operating system for MIT's 6.1810, so we are more interested in
simplifications and clarifications than new features.

BUILDING AND RUNNING XV6

You will need a RISC-V "newlib" tool chain from
https://github.com/riscv/riscv-gnu-toolchain, and qemu compiled for
riscv64-softmmu.  Once they are installed, and in your shell
search path, you can run "make qemu".

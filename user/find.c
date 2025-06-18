#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

char*
getName(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), '\0', DIRSIZ-strlen(p));
  return buf;
}

void
find(char *path, char *filename)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "find: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    if(strcmp(getName(path), filename) == 0) {
        fprintf(1, "%s\n", path);
    }
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      fprintf(2, "find: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);

    // 准备拼接path
    *p++ = '/';

    // 依次读取目录中的文件
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
        if(de.inum == 0)
          continue;

        // 拼接当前文件名得到path
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if(stat(buf, &st) < 0){
          fprintf(2, "find: cannot stat %s\n", buf);
          continue;
        }

        // 判断当前文件名是否为查找文件名
        if (strcmp(getName(buf), filename) == 0) {
          fprintf(1, "%s\n", buf);
        }

        if (strcmp(de.name, "..") != 0 && strcmp(de.name, ".") != 0 && st.type == T_DIR) {
            find(buf, filename);
          }
        }
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  if(argc < 3){
    printf("usage: find path filename\n");
    exit(1);
  }
  find(argv[1], argv[2]);
  exit(0);
}

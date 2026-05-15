#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main (int argc , char const *argv[])
{
    //邀请之前
    char *name = "老学员";
    printf ("%s %d继续在一楼精进\n", name ,getpid());

    //邀请新学员
    __pid_t pid = fork();
    if (pid == -1)
    {
        printf ("邀请新学员失败\n");
        return 1;
    }
    else if (pid == 0)
    {
        char *new_name = "ergou";
        char *args[] = {"/home/s/桌面/Mint/Linux/2-尚硅谷/Process_test/erlou",new_name,NULL};
        char *envs[] = {NULL};

        int exR = execve(args[0],args,envs);
        if (exR == -1 ){
            printf ("新学员上二楼失败！");
            return 1;
        }
    }else {
        //老学员挂起，等待输入任意一个字符停止
        printf ("老学员%d 邀请%d完还是在一楼学习",getpid(),pid);
        char by = fgetc (stdin);

    }

}
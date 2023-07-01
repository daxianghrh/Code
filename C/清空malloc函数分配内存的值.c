#include <stdio.h>
#include <malloc.h>
#include <string.h> 
int main () {
    char *p = (char *)malloc(sizeof(char));
    int array[100] = {0};
    //对malloc函数分配的内存清理垃圾值
    //bzero(p, 1);
    //memset是按照内存中一个一个字节的进行赋值的
    memset(array, 0, 100);
    free(p);
    printf("%d\n", array[0]);
}
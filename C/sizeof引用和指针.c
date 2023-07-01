#include <stdio.h>
#include <string.h>

int main() {
    int x = 5;
    int *p = &x;
    printf("%d %d\n", *p, sizeof(p));
    //printf("%d %d\n", q, sizeof(q));
    //结果
    // 5  8  64位操作系统指针本身的大小是8字节;32位是4字节
    // 5  4

    //sizeof和strlen对字符串的处理
    char *str = "it's time to study";
    printf("%d,%d\n", sizeof(str), strlen(str));

    //计算数组大小
    int arr[5] = {1,2,3,4,5};
    printf("%d\n", sizeof(arr)/sizeof(arr[0]));

    //sizeof传入数据类型，返回对应数据类型的字节数

    int i = 0;
    char a = 'b';
    char *b = "abc";
    printf("%d\n",sizeof(i));
    printf("%d\n",sizeof(0));
    printf("%d\n",sizeof(a));
    printf("%d\n",sizeof('b'));
    printf("%d\n",sizeof(b));
    printf("%d\n",sizeof("abc"));
}
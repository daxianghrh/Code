#include <stdio.h>

//define定义宏时，使用()来保证不出错误
#define Min(A, B)  ((A) <= (B) ? (A) : (B))
#define p_char char*
typedef char* p_char_;
int main () {
    int a = 5;
    int b = 4;
    printf("%d\n",Min(5, 4));
    p_char p1, p2;
    //替换成
    //char* p1, p2;
    printf("%d,%d\n", sizeof(p1), sizeof(p2));
    p_char_ p3, p4;
    //char* p3; char* p4;
    printf("%d,%d\n", sizeof(p3), sizeof(p4));
}
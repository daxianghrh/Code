#include <string.h>
#include <stdio.h>

//将从vsrc地址开始并且含有'\0'结束符的字符串复制到以vdest地址开始的字符串
char *my_strcpy(char *vdest, const char *vsrc) {
    char *dest = vdest;
    char *src = (char *)vsrc;
    while (*src != '\0') {
        *dest++ = *src++;
    }
    *dest = '\0';
    return vdest;
}

//计算字符串的长度:不包含'\0'
int my_strlen(const char *vsrc) {
    int len;
    while (*vsrc++ != '\0') {
        len++;
    }
    return len;
}


//将vsrc所指向的字符串添加到vdest结尾处
char *my_strcat(char *vdest, const char *vsrc) {
    char *dest = vdest;
    //找到vdest的'\0'结尾符
    while (*vdest!= '\0') {
        *vdest++;
    };
    //将vsrc拷贝到vdest
    while (*vsrc != '\0') {
        *vdest++ = *vsrc++;
    }
    *vdest = '\0';
    return dest;
}

//比较两个字符串
//s1 == s2,相等返回0；s1 < s2,返回负数; s1 > s2,返回正数
int my_strcmp(const char *s1, const char *s2) {
    //找到首个不相等的字符
    while (*s1 && *s2 && (*s1 == *s2)) {
        s1++, s2++;
    }
    //求差
    return (char)*s1 - (char)*s2;
}

//将字符串转换成整数:若有正负号，使用flag变量标记即可
int my_atoi(const char *s) {
    int n = 0;
    while (*s >= '0' && *s <= '9') {
        n = n * 10 + *s++ - '0';
    }
    return n;
}


int main() {
    char dest[100] = "123";
    char *src = "1sdadff";
    // printf("%s\n", strcpy(dest, src));
    // printf("%s\n", my_strcpy(dest, src));
    printf("%s\n", my_strcat(dest, src));
    // printf("%s\n", strcat(dest, src));
    printf("%d\n", strcmp(dest, src));
    printf("%d\n", my_atoi(dest));
}
#include <string.h>
#include <stdio.h>


void *my_memmove(void *vdst, void *vsrc, size_t n) {
    char *dst = (char *)vdst;
    char *src = (char *)vsrc;
    //若vsrc在vdst右边，顺序遍历执行即可，vsrc被改变
    if (src > dst) {
        while (n-- > 0) {
            *dst++ = *src++;
        }
    } else {
        //若vsrc在vdst左边,从后往前遍历
        dst += n;
        src += n;
        while (n-- > 0) {
            *--dst = *--src;
        }
    }
    return vdst;
}

void *my_memcopy(void *vdst, const void *vsrc, size_t n) {
    char  *dst = vdst;
    char  *src = (char *)vsrc;
    while (n-- > 0) {
        *dst++ = *src++;
    }
    return vdst;
}

int main() {
    char a[9] = "hello wo";
    char *dst = &a[6];
    char *src = &a[4];
    my_memmove(dst, src, 2);
    printf("%s\n", dst);// o
    my_memcopy(dst, src, 2);
    printf("%s\n", dst); // o
}
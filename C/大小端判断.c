#include <stdio.h>
typedef union test
{
    short a;
    char b[sizeof(char)];
}Test;

void bytes_boarder(Test test) {
    if (test.b[0] == 1 && test.b[1] == 2) {
        printf("big boarder");
    } else if (test.b[0] == 2 && test.b[1] == 1) {
        printf("small boarder");
    }
}

int main () {
    Test t;
    t.a = 0x0102;
    bytes_boarder(t);
}
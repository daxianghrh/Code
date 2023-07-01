#include <stdio.h>

#define BIT3 (0X1 << 3) 
// 0X1: 0001 << 3
//      1000 
static int c = 0;
//求解整数型的二进制中1的个数
// x&(x-1) 可以把x对应的二进制数中最后一位1去掉
/**
例如:
    9: 1001
    8: 1000
    --------
       1000
    
    8: 1000
    7: 0111
    -------
       0000
    结束，可以发现9的二进制数中有2个1
*/
int calCountOfOne(int num) {
    int count_of_one = 0;
    while (num) {
        count_of_one++;
        num = num & (num -1);
    }
    return count_of_one;
}

//求解整数型的二进制中0的个数
// x|(x+1)
/*
例如：
    9： 1001
        1010
        1011 -> 1011

        1101
        1110 -> 1111

       10000结束 -> 二进制中0的个数为2
*/
int calCountOfZero(int num) {
    int count_of_zero = 0;
    while (num + 1) {
        count_of_zero++;
        num = num | (num + 1);
    }
    return count_of_zero;
}

//给定一个整数变量a,设置a的bit3为1,保持其他位不变
void set_bit3(void) {
    c |= BIT3;
}

//给定一个整数变量a,设置a的bit3为0,保持其他位不变
void clear_bit3(void) {
    c &= ~BIT3;
}


int main() {
    printf("%d\n", calCountOfOne(9999));
    printf("%d\n", calCountOfZero(9999));
    //交换两个变量的值，不使用第三个变量
    /**
        1、使用加减法
        2、异或
    */
    int a = 3, b = 5;
    printf("交换前:a = %d, b = %d\n", a, b);
    // a = a + b; // a = 8
    // b = a - b; // b = 3
    // a = a - b; // a = 5
    a = a^b;
    b = a^b;
    a = a^b;
    printf("交换后:a = %d, b = %d\n", a, b);


    set_bit3();
    printf("0x%x\n", c);
    clear_bit3();
    printf("0x%x\n", c);
    return 0;
}

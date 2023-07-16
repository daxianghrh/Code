#include <stdio.h>
#include <string.h>


int cal(int i, int j, int k) {
    return i * 100 + j * 10 + k;
}
int main () {
    int cnt = 0;
    for (int i = 1; i <= 9; i += 1) {  // 百位数字（偶数，包括零）
        for (int j = 0; j <= 9; ++j) {  // 十位数字
            if (j != i) {
                for (int k = 0; k <= 9; k += 1) {  // 个位数字（偶数）
                    if (k != i && k != j && cal(i,j,k) % 2 == 0) {
                        ++cnt;
                    }
                }
            }
        }
    }
    printf("%d\n", cnt);
}
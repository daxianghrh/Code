#include <stdio.h>
#include <string.h>


int cal(int i, int j, int k) {
    return i * 100 + j * 10 + k;
}
int main () {
    char str1[10] = {'n', 'o', 'w'}, str2[] = "coder", str3[] = "abcde";
    printf("%d%d%d\n", strlen(str1),strlen(str2),strlen(str3));
    strcat(str1, str3);
    printf("%s %d\n", str1, strlen(str1));
    strcpy(str1 + strlen(str2), str2);
    printf("%s %d\n", str1, strlen(str1));
    /**
    355
    nowabcde 8
    nowabcoder 10
    */
    // return 0;

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
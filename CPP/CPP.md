# C/CPP
## 1、虚函数表剖析
[虚函数表、虚表指针、动态绑定和多态](https://zhuanlan.zhihu.com/p/75172640 )

## 2、define和typedef的区别？
-   define用来定义常量及书写复杂内容;typedef主要用于定义类型别名
-   define发生在编译前预处理阶段；typedef是编译的一部分
-   define不检查类型；typedef检查数据类型
-   define不是语句，末尾不需要加分号；typedef是语句，要加分号标识结束
-   define和typedef对指针的操作区别巨大，比如：`define p_char char*`和`typedef char* p_char_`，在同时定义多个变量时区别巨大。
```c
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
    //char* p1,p2;
    //p2为char类型?
    printf("%d,%d\n", sizeof(p1), sizeof(p2));
    p_char_ p3, p4;
    //char* p3; char* p4;
    printf("%d,%d\n", sizeof(p3), sizeof(p4));
}
```
>使用`gcc -E` 将`defin.c`宏展开得到`define_expanded.c`,查看内容：
```c
typedef char* p_char_;
int main () {
    int a = 5;
    int b = 4;
    printf("%d\n",((5) <= (4) ? (5) : (4)));
    char* p1, p2;
    printf("%d,%d\n", sizeof(p1), sizeof(p2));
    p_char_ p3, p4;
    printf("%d,%d\n", sizeof(p3), sizeof(p4));
}
```
```bash
PS D:\VScodeProject\C_CPP\C> gcc .\标准define宏.c -o define
PS D:\VScodeProject\C_CPP\C> .\define.exe
4
8,1
8,8
PS D:\VScodeProject\C_CPP\C> gcc -E -P .\标准define宏.c > define_expanded.c
```
为什么`sizeof(2) = 1`? `p2`为`char`类型。

## 3、sizeof和strlen的区别？
-   `sizeof`是运算符,并不是函数，在编译时得到而非运行时;`strlen`是C库中的字符串处理函数
-   `sizeof`的参数可以是任意数据类型或者数据;`strlen`的参数必须是字符指针且结尾是`\0`的字符串
-   `sizeof`在编译时得到，所以不能用来得到动态分配存储空间的大小
```c
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

    //sizeof传入数据类型或数据，返回对应数据类型或数据的字节数
    int i = 0;
    char a = 'b';
    char *b = "abc";
    printf("%d\n",sizeof(i));
    printf("%d\n",sizeof(0));
    printf("%d\n",sizeof(a));
    printf("%d\n",sizeof('b')); // ? 4
    printf("%d\n",sizeof(b));
    printf("%d\n",sizeof("abc")); // ? 4
}
```
```bash
PS D:\VScodeProject\C_CPP\C> cd "d:\VScodeProject\C_CPP\C\" ; if ($?) { gcc sizeof引用和指针.c -o sizeof引用和指针 } ; if ($?) { .\sizeof引用和指针 }
5 8
8,18
5
4
4
1
4
8
4
```
> `sizeof('b') = 4 ?`在C99标准下,`'b'`为整形字符常量，被当作`int`类型；在ISO C++标准下, `'b'`是字符字面量，被看作`char`类型。
> `sizeof("abc") = 4 ？` `"abc"`为字符串，会在末尾自动加上`\0`字符，即数据`0x00`

## 4、常量指针和指针常量的区别？
如何区分？判断离变量名近的类型：如`const int *p`,`p`离`*`较近，即`p`是一个指针类型，`const int`表示指针指向的变量是常量，不可以被修改；同理,`int *const p`
- `const int *p`:常量指针，指针指向可以更改，指向的值不可以修改;`int *const p`：指针常量,指针的指向不可以更改，指向的值可以修改。

## 5、数组名a与&a的区别？
```c
#include <stdio.h>

int main() {
    int arr[10] = {0, 1,2,3,4,5,6,7,8,9};
    int len = sizeof(arr) / sizeof(arr[0]);
    int i = 0;
    for (;i < len; i++) {
        printf("%d", *(arr + i));
    }
    printf("\n");
    printf("%p\n", arr);
    int (*p)[10] = &arr;
    printf("%d\n",*(arr + 10));
    printf("%p, %d, %d\n", p, *(int*)p, *(int*)(p + 1));
}
```
```bash
PS D:\VScodeProject\C_CPP\C> cd "d:\VScodeProject\C_CPP\C\" ; if ($?) { gcc arr.c -o arr } ; if ($?) { .\arr }
0123456789
000000000061FDE0
33
000000000061FDE0, 0, 33
```
-   `arr`是数组名，是数组首元素地址，`+1`表示指针加1,内存地址加1 * int类型所占的字节数,即4。`*(a+1) = a[1]`
-   `&arr`是数组指针，类型为`int (*p)[]`(数组指针)，其加1时，为数组首地址加上整个数组的偏移(10个int变量),值为数组`arr`尾元素后一个元素的地址，具体值不确定。
-   若想输出指针`p`指向的值，需要将`p`强制转换成`(int*)p`,`*(int*)p = a[0]`

## 6、new、delete和malloc、free的区别?
-   `new、delete`是C++的关键词;`malloc、free`是C语言标准库函数
-   `new、delete`调用`operator new、operator delete`,`operator new、operator delete`调用`malloc、free`,`new、delete`与对象构造析构组合在一起
-   `new`无需指定内存的大小，失败返回`bad_alloc`，成功返回对象类型的指针；`malloc`需要指定申请内存的大小，失败返回`NULL`,成功返回`void*`，需要强制类型转换成我们需要的类型。
```c
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
```

## 7、常见位运算:求二进制中1的个数、0的个数;设置某位、清除某位;交换两数
```c
#include <stdio.h>

#define BIT3 (0X1 << 3) 
// 0X1: 0001 << 3
//      1000 
static int c = 0;
//求解整数型的二进制中1的个数
// x&(x-1) 可以把x对应的二进制数中最后一位1去掉
//注： x&(x-1)可以判断x是否为2的幂
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
```
```bash
PS D:\VScodeProject\C_CPP\C> cd "d:\VScodeProject\C_CPP\C\" ; if ($?) { gcc 位操作.c -o 位操作 } ; if ($?) { .\位操作 }
8
24
交换前:a = 3, b = 5
交换后:a = 5, b = 3
0x8
0x0
```
## 8、从一个C语言程序到可执行文件的过程？
>从源文件到可执行文件的过程：预处理->编译->汇编->链接->可执行文件
-   预处理：`gcc -E test.c test.i`,将`#include、#define`展开
-   编译：`gcc -S test.i test.s`,生成汇编文件
-   汇编: `gcc -c tets.s test.o`,汇编码转换成机器码
-   链接：将汇编接受后的目标文件和库文件打包生成可执行文件
-   可执行文件：`./test.o`

## 9、静态库和动态库的区别？
-   静态库在编译时链接到目标程序,链接器从库中复制这些函数和数据并把它们和应用程序的其它模块组合起来创建最终的可执行文件，最后生成的可执行文件较大，通常以`.a`结尾；动态库在可执行文件运行时载入内存，在编译过程中仅仅简单的引用(仅保留接口)，最后生成的可执行文件相对较小,通常以`.so`。
-   静态库和动态库都是由`.o`文件创建的


## 10、常见C字符串函数实现?
-   `memmove`、`memcopy`将源字符串指针指向的`len`字节复制到目的字符串指针指向的位置，`memmove`考虑到源字符串与目的字符串内存折叠的情况，而`memcopy`没有考虑(需要用户自己确定)
```c
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
```
-   `strcpy`、`strlen`、`strcmp`、`strcat`、`atoi`
```c
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
```

## 11、使用C语言实现常见数据结构：链表、栈、队列等
[C语言实现常见数据结构](https://blog.csdn.net/edward_asia/category_11419373.html)

## 12、C++优先级队列
> 问：C++优先级队列<br>
> chatgpt：C++中的优先级队列是一种特殊的队列，其中的元素按照一定的优先级进行排序。默认情况下，优先级队列使用元素类型的比较操作符（<）来确定元素之间的优先级。优先级高的元素会被放置在队列的前面，而优先级低的元素会被放置在队列的后面。

C++标准库中提供了一个名为`std::priority_queue`的优先级队列容器适配器，它位于头文件`<queue>`中。`std::priority_queue`基于堆数据结构实现，这使得插入和删除操作的时间复杂度为O(log n)，其中n是队列中的元素个数。

以下是使用`std::priority_queue`的一些基本操作示例：

```cpp
#include <iostream>
#include <queue>

int main() {
    // 创建一个存储整数的优先级队列，默认以降序排列
    std::priority_queue<int> pq;

    // 插入元素
    pq.push(5);
    pq.push(2);
    pq.push(10);
    pq.push(1);

    // 访问队列中的顶部元素（最大元素）
    std::cout << "Top element: " << pq.top() << std::endl;

    // 移除队列中的顶部元素
    pq.pop();

    // 访问新的顶部元素
    std::cout << "Top element after pop: " << pq.top() << std::endl;

    // 检查队列是否为空
    if (pq.empty()) {
        std::cout << "Priority queue is empty." << std::endl;
    } else {
        std::cout << "Priority queue is not empty." << std::endl;
    }

    // 获取队列中的元素个数
    std::cout << "Size of priority queue: " << pq.size() << std::endl;

    return 0;
}
```
上述代码中，我们创建了一个存储整数的优先级队列`pq`。通过`push()`函数插入了几个元素，并使用`top()`函数访问了队列中的顶部元素（最大元素）。然后，我们使用`pop()`函数移除了顶部元素，并再次使用`top()`函数访问了新的顶部元素。最后，我们使用`empty()`函数检查队列是否为空，使用`size()`函数获取队列中的元素个数。

需要注意的是，默认情况下，`std::priority_queue`是以降序排列元素的。如果想要以升序排列元素，可以使用比较操作符的反向版本或自定义比较函数来创建优先级队列。例如，可以使用`std::greater`来创建一个以升序排列元素的优先级队列：

```cpp
std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
```

这样，`std::priority_queue`会根据`std::greater<int>`的比较结果来确定元素的优先级，即最小元素会被放置在队列的前面。

## 13、哈希表
>chatgpt:
哈希表（Hash Table）是一种常见的数据结构，也被称为散列表。它通过使用哈希函数将键（Key）映射到存储桶（Bucket）的索引位置上，从而实现高效的数据存储和检索。

哈希表的核心思想是利用哈希函数将键转换为唯一的索引，然后将值存储在对应的索引位置上。当需要查找或插入元素时，再次应用哈希函数找到对应的索引，从而快速访问到所需的元素。

哈希函数是哈希表中的关键组成部分，它将任意大小的输入映射到固定大小的哈希值（Hash Value）上。好的哈希函数应该具有以下特点：

-   一致性：对于相同的输入，哈希函数应该始终生成相同的哈希值。
-   均匀性：哈希函数应该尽可能地将不同的输入映射到不同的哈希值上，以减少冲突的可能性。
-   高效性：哈希函数的计算速度应该快，以保证哈希表的高效性。

解决哈希冲突是哈希表的另一个重要问题。哈希冲突指的是两个不同的键经过哈希函数计算得到相同的索引位置。常用的解决冲突的方法有两种：

-   链接法（Chaining）：每个索引位置上存储一个链表或其他数据结构，相同索引位置上的元素通过链表连接在一起。
-   开放寻址法（Open Addressing）：当发生冲突时，通过一定的规则寻找下一个可用的索引位置，直到找到一个空闲位置。

哈希表具有快速的查找和插入操作的特点，平均情况下，它们的时间复杂度为O(1)。然而，最坏情况下，哈希表的性能可能下降到O(n)，其中n是存储的元素数量。

C++中的标准库提供了`std::unordered_map`作为哈希表的实现，它提供了快速的查找、插入和删除操作，并且允许用户自定义哈希函数和键的比较操作。


## 14、堆
使用堆排序解决数组中第K大的元素,**Top K问题**。<br>
解决方法：使用数组建堆，实现堆排<br>
关键点：
-   对于索引为`i`的节点，其父节点索引为`(i-1)/2`,左孩子和右孩子节点索引为`i * 2 + 1`、`i * 2 + 2`。
-   从数组中的一半开始建堆，从下往上进行
-   小顶堆和大顶堆的区别为`maxHeapify`中`if`判断的逻辑
```cpp
class Solution {
public:
    void maxHeapify(vector<int>& a, int i, int heapSize) {
        int l = i * 2 + 1, r = i * 2 + 2, largest = i;
        if (l < heapSize && a[l] > a[largest]) {
            largest = l;
        } 
        if (r < heapSize && a[r] > a[largest]) {
            largest = r;
        }
        if (largest != i) {
            swap(a[i], a[largest]);
            maxHeapify(a, largest, heapSize);
        }
    }

    void buildMaxHeap(vector<int>& a, int heapSize) {
        for (int i = heapSize / 2; i >= 0; --i) {
            maxHeapify(a, i, heapSize);
        } 
    }

    int findKthLargest(vector<int>& nums, int k) {
        int heapSize = nums.size();
        buildMaxHeap(nums, heapSize);
        for (int i = nums.size() - 1; i >= nums.size() - k + 1; --i) {
            swap(nums[0], nums[i]);
            --heapSize;
            maxHeapify(nums, 0, heapSize);
        }
        return nums[0];
    }
};
```
>chatgpt：代码中的 maxHeapify 函数用于维护最大堆的性质，它比较当前节点与其左右子节点的大小，找到最大值并将其交换到当前节点。如果发生交换，继续对交换后的子节点递归调用 maxHeapify。buildMaxHeap 函数用于构建最大堆，从数组的一半开始，逐个调用 maxHeapify，确保从数组的一半到根节点的所有节点满足最大堆的性质。findKthLargest 函数首先使用 buildMaxHeap 将输入数组构建为最大堆，然后进行K次操作。每次操作，将堆顶元素（最大值）与最后一个元素交换，并减小堆的大小。接着，对交换后的堆顶节点进行 maxHeapify，恢复最大堆的性质。重复这个过程K次后，堆顶元素即为第K个最大元素。整体而言，这段代码使用堆排序算法来高效地找到数组中的第K个最大元素。它通过构建最大堆和逐步提取最大值的方式，将第K个最大元素放置在堆顶。最后，返回堆顶元素即为结果。

```cpp
#include <vector>

class Heap {
private:
    std::vector<int> heap;

    void heapifyUp(int index) {
        if (index == 0) {
            return;
        }

        int parent = (index - 1) / 2;
        if (heap[parent] < heap[index]) {
            std::swap(heap[parent], heap[index]);
            heapifyUp(parent);
        }
    }
    void heapifyDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < heap.size() && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < heap.size() && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest != index) {
            std::swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }
    void buildHeap() {
        int n = heap.size();
        for (int i = n / 2 - 1; i >= 0; --i) {
            heapifyDown(i);
        }
    }

public:
    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    int extractMax() {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty.");
        }

        int maxValue = heap[0];
        std::swap(heap[0], heap[heap.size() - 1]);
        heap.pop_back();
        heapifyDown(0);

        return maxValue;
    }

    int getMax() {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty.");
        }

        return heap[0];
    }

    bool isEmpty() {
        return heap.empty();
    }
};
```
>上述代码定义了一个名为 Heap 的类，使用 std::vector<int> 来存储堆的元素。类中的 insert 方法用于插入元素，extractMax 方法用于提取堆中的最大值，getMax 方法用于获取最大值，isEmpty 方法用于检查堆是否为空。在实现中，通过在数组中维护完全二叉树的性质，使用下标关系表示节点之间的层次关系。heapifyUp 方法用于向上调整堆，确保父节点始终大于其子节点；heapifyDown 方法用于向下调整堆，确保父节点大于等于其子节点。通过这种方式，利用数组实现了堆的基本功能，使其满足堆的性质，即父节点大于等于（或小于等于）其子节点。

## 15、C++内存分布
```sql
+-----------------------+
|        Stack          |
|                       |
|      局部变量等        |
|                       |
|                       |
+-----------------------+
|        Heap           |
|                       |
|   动态分配的内存空间  |
|                       |
|                       |
+-----------------------+
|     Global / Static   |
|         Area          |
|                       |
|   全局变量和静态变量  |
|   常量数据             |
+-----------------------+
|      Constant Area    |
|                       |
|   字符串常量           |
|   其他常量数据         |
+-----------------------+
|       Code Area       |
|                       |
|   可执行代码           |
|                       |
|                       |
+-----------------------+
```
上述示意图中，栈位于内存的高地址部分，堆位于内存的低地址部分。全局区、常量区和代码区通常位于堆和栈之间。注意，示意图仅展示了内存布局的一般情况，实际情况可能会有所不同，具体取决于编译器、操作系统和编译选项等因素。

虚函数表（vtable）和虚基类表（vtable）等特殊的内存结构并没有在示意图中显示，因为它们是与对象的多态性和继承相关的概念，而不是整个内存布局的一部分。

> 问：.data段和.bss段在哪里？\
.bss段和.data段位于全局/静态区（Global/Static Area）。

-   .bss段（Block Started by Symbol）：.bss段用于存储未初始化的全局变量和静态变量。这些变量在编译时被分配了内存空间，但在程序运行之前不会被初始化，因此它们的初始值都是0或者是空指针。.bss段位于全局/静态区的末尾，紧随已初始化的全局变量和静态变量。

-   .data段：.data段用于存储已初始化的全局变量和静态变量。这些变量在编译时被分配了内存空间，并且在程序运行之前已经初始化为指定的值。.data段位于全局/静态区中.bss段之前。

这两个段的具体位置和大小在程序运行时是固定的，并且在整个程序运行期间保持不变。它们的分配和释放是由操作系统和运行时环境负责管理的。

需要注意的是，.bss段和.data段是在链接过程中由编译器和链接器分配和确定的，它们并不是由C++语言本身直接控制的。编译器和链接器根据全局变量和静态变量的定义和初始化语句来确定这些段的内容和大小。

## 16、如何在main函数执行前、后执行某些代码

-   `__attribute__((constructor))`是GCC编译器提供的一种属性（attribute），用于指定在程序加载或库初始化时要执行的函数。

当一个函数被标记为`__attribute__((constructor))`时，编译器会将该函数与程序的加载和初始化过程关联起来。具体而言，这个函数会在`main`函数执行之前自动调用，以完成一些特定的初始化操作。这种属性通常用于需要在程序开始之前执行一些必要的设置或初始化工作的函数。

例如，考虑以下示例代码：

```cpp
#include <iostream>

void myInitFunction() __attribute__((constructor));

void myInitFunction() {
    std::cout << "Initialization function called" << std::endl;
}

int main() {
    std::cout << "Main function" << std::endl;
    return 0;
}
```

在上述代码中，`myInitFunction`函数被标记为`__attribute__((constructor))`，它会在程序加载时自动执行。当运行这个程序时，输出将是：

```
Initialization function called
Main function
```

可以看到，在`main`函数执行之前，`myInitFunction`函数会被自动调用。

需要注意的是，`__attribute__((constructor))`是GCC编译器的扩展，不属于C++标准的一部分。因此，它在不同的编译器和平台上的行为可能会有所不同。对于其他编译器，可能会使用不同的方式来实现类似的功能。因此，如果要编写可移植的代码，最好避免依赖于特定编译器的扩展特性。

`__attribute__((destructor))`是GCC编译器提供的一个属性（attribute），用于指定在程序退出或库销毁时要执行的函数。

当一个函数被标记为`__attribute__((destructor))`时，编译器会将该函数与程序的退出和销毁过程关联起来。具体而言，这个函数会在程序正常终止或被强制终止时自动调用，以完成一些特定的清理或收尾工作。这种属性通常用于需要在程序结束前执行一些必要的清理操作的函数。

例如，考虑以下示例代码：

```cpp
#include <iostream>

void myCleanupFunction() __attribute__((destructor));

void myCleanupFunction() {
    std::cout << "Cleanup function called" << std::endl;
}

int main() {
    std::cout << "Main function" << std::endl;
    return 0;
}
```

在上述代码中，`myCleanupFunction`函数被标记为`__attribute__((destructor))`，它会在程序退出时自动执行。当运行这个程序时，输出将是：

```
Main function
Cleanup function called
```

可以看到，在`main`函数执行完毕后，`myCleanupFunction`函数会被自动调用。

需要注意的是，`__attribute__((destructor))`是GCC编译器的扩展，不属于C++标准的一部分。因此，它在不同的编译器和平台上的行为可能会有所不同。对于其他编译器，可能会使用不同的方式来实现类似的功能。因此，如果要编写可移植的代码，最好避免依赖于特定编译器的扩展特性。

## 17、 空指针、野指针和悬空指针
均指向无效内存区域("不安全不可控")的指针，访问行为将会导致未定义行为。

-   空指针：访问地址为0的指针。
-   野指针（悬空指针）
    -   未初始化的指针。
    -   指针最初指向的内存已经被释放了的一种指针。
```cpp
int main() {
    int* p = nullptr;
    int* p2 = new int;
    p = p2;
    delete p2;
    //此时p、p2为野指针,一般置空
    p = p2 = nullptr;
}
```

## 18、智能指针
> C++引入智能指针的原因？

C++11引入智能指针的主要原因是为了解决动态内存管理的问题和避免内存泄漏。

在传统的C++中，手动管理动态分配的内存是一个常见的任务，使用`new`关键字分配内存，然后使用`delete`关键字释放内存。这种手动管理内存的方式容易出现错误，例如忘记释放内存或释放已经释放过的内存，从而导致内存泄漏或悬挂指针问题。

智能指针的引入解决了这些问题。智能指针是一种对象，它的行为类似于指针，但附加了自动管理内存的能力。它能够在适当的时候自动释放所管理的动态内存，无需手动调用`delete`。

C++11中引入了两种主要的智能指针：

-   `std::shared_ptr`：它实现了共享拥有（`shared ownership`）的语义，多个`std::shared_ptr`对象可以指向同一个对象。当最后一个`std::shared_ptr`对象超出作用域或被显式销毁时，所管理的内存会被自动释放。这种智能指针适用于共享资源的情况，可以避免内存泄漏和悬挂指针问题
-   `std::unique_ptr`：它实现了独占拥有（`exclusive ownership`）的语义，一个 `std::unique_ptr`对象独占地拥有所指向的对象。当 `std::unique_ptr`对象超出作用域或被显式销毁时，所管理的内存会被自动释放。这种智能指针适用于独占资源的情况，提供了更高效的内存管理和避免多个指针同时访问同一对象的问题。

>shared_ptr的底层实现原理？

`std::shared_ptr`的底层实现原理主要涉及引用计数（`reference counting`）和控制块（`control block`）。

当创建一个`std::shared_ptr`对象时，实际上会在堆上分配一个控制块。这个控制块包含两个重要的成员：指向所管理对象的指针和一个引用计数器。

引用计数器用于记录有多少个`std::shared_ptr`对象共享同一个控制块。每当创建一个新的`std::shared_ptr`对象时，引用计数器会加一。当`std::shared_ptr`对象超出作用域、被销毁或通过赋值操作改变所管理的对象时，引用计数器会减一。

只有当引用计数器的值为零时，表示没有任何`std::shared_ptr`对象引用该控制块，可以安全地释放所管理的对象和控制块。释放时，会调用所管理对象的析构函数来完成对象的销毁。

使用引用计数的技术，`std::shared_ptr`实现了共享拥有的语义。多个`std::shared_ptr`对象可以指向同一个对象，它们共享同一个控制块，并共同维护引用计数。这样，在任何一个`std::shared_ptr`对象超出作用域或被销毁时，只有当所有的`std::shared_ptr`对象都释放了对控制块的引用，才会释放所管理的对象和控制块。

需要注意的是，引用计数的维护是原子的，以确保在多线程环境下的正确性。同时，`std::shared_ptr`还提供了自定义的删除器（deleter）功能，允许用户指定在释放所管理对象时执行特定的清理操作。

总结起来，`std::shared_ptr`通过引用计数和控制块来实现对所管理对象的共享拥有，使得多个`std::shared_ptr`对象可以安全地共享和释放所管理的对象，避免内存泄漏和悬挂指针问题。

>shared_ptr的简单实现

-   线程不安全的`SharedPtr`类：
```cpp
template <typename T>
class SharedPtr {
public:
    // 构造函数
    explicit SharedPtr(T* ptr = nullptr) : ptr_(ptr), ref_count_(nullptr) {
        if (ptr_) {
            ref_count_ = new int(1);  // 创建引用计数器并初始化为1
        }
    }

    // 拷贝构造函数
    SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), ref_count_(other.ref_count_) {
        if (ref_count_) {
            ++(*ref_count_);  // 增加引用计数
        }
    }

    // 析构函数
    ~SharedPtr() {
        reset();
    }

    // 重载赋值操作符
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            reset();
            ptr_ = other.ptr_;
            ref_count_ = other.ref_count_;
            if (ref_count_) {
                ++(*ref_count_);
            }
        }
        return *this;
    }

    // 重载解引用操作符
    T& operator*() const {
        return *ptr_;
    }

    // 重载箭头操作符
    T* operator->() const {
        return ptr_;
    }

    // 获取引用计数
    int use_count() const {
        return (ref_count_ ? *ref_count_ : 0);
    }

    // 释放资源
    void reset() {
        if (ref_count_) {
            --(*ref_count_);  // 减少引用计数
            if (*ref_count_ == 0) {
                delete ptr_;  // 释放所管理的对象
                delete ref_count_;  // 释放引用计数器
                ptr_ = nullptr;
                ref_count_ = nullptr;
            }
        }
    }

private:
    T* ptr_;         // 指向所管理的对象
    int* ref_count_; // 引用计数器指针
};
```
上面给出的 `SharedPtr` 类的实现是简化版的，不具备线程安全性。在多线程环境下，对于共享资源的访问和引用计数的更新可能导致竞态条件（race condition），从而导致未定义的行为。

要使 `SharedPtr` 类在多线程环境下安全，需要采取适当的线程同步措施来保护共享数据。以下是一些常用的方法：

1. 使用互斥锁（Mutex）：可以在 `SharedPtr` 类中添加互斥锁，用于保护对共享数据的访问和修改。在每个关键的操作中，使用互斥锁进行加锁和解锁，以确保原子性和互斥性。

2. 使用原子操作（Atomic operations）：C++11 引入了原子操作的支持，例如 `std::atomic` 类。可以使用原子操作来对引用计数进行增减操作，确保原子性和可见性。

3. 使用线程局部存储（Thread-local storage）：可以将引用计数器设计为线程局部存储，每个线程独立维护自己的引用计数器，避免跨线程的竞态条件。

需要根据具体的需求和场景选择适当的线程同步机制。在实际应用中，推荐使用标准库提供的线程安全的智能指针 `std::shared_ptr`，它已经在底层实现中考虑了线程安全性和性能优化，并提供了良好的并发行为。

-   线程安全的`SharedPtr`类:
```cpp
#include <mutex>

template <typename T>
class SharedPtr {
public:
    explicit SharedPtr(T* ptr = nullptr) : ptr_(ptr), ref_count_(new int(1)), ref_count_mutex_(new std::mutex()) {}

    SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), ref_count_(other.ref_count_), ref_count_mutex_(other.ref_count_mutex_) {
        std::lock_guard<std::mutex> lock(*ref_count_mutex_);
        ++(*ref_count_);
    }

    ~SharedPtr() {
        reset();
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            reset();
            std::lock_guard<std::mutex> self_lock(*ref_count_mutex_);
            std::lock_guard<std::mutex> other_lock(*other.ref_count_mutex_);
            ptr_ = other.ptr_;
            ref_count_ = other.ref_count_;
            ++(*ref_count_);
        }
        return *this;
    }

    T& operator*() const {
        return *ptr_;
    }

    T* operator->() const {
        return ptr_;
    }

    int use_count() const {
        std::lock_guard<std::mutex> lock(*ref_count_mutex_);
        return (ref_count_ ? *ref_count_ : 0);
    }

    void reset() {
        std::lock_guard<std::mutex> lock(*ref_count_mutex_);
        if (ref_count_) {
            --(*ref_count_);
            if (*ref_count_ == 0) {
                delete ptr_;
                delete ref_count_;
                ptr_ = nullptr;
                ref_count_ = nullptr;
            }
        }
    }

private:
    T* ptr_;
    int* ref_count_;
    std::shared_mutex* ref_count_mutex_;
};
```

>weak_ptr的作用？

`std::weak_ptr` 是 C++ 智能指针库中的一种指针类型，它用于解决共享指针 (`std::shared_ptr`) 的循环引用问题。`std::weak_ptr` 允许创建一个指向 `std::shared_ptr` 所管理对象的弱引用，而不会增加引用计数。它主要用于观察或访问由 `std::shared_ptr` 管理的对象，而不会拥有对象的所有权。

主要作用如下：

1. 弱引用：`std::weak_ptr` 提供了对由 `std::shared_ptr` 管理的对象的弱引用。它不会增加引用计数，也不会阻止对象的销毁。通过 `std::weak_ptr`，我们可以检查所管理的对象是否已经被销毁。

2. 避免循环引用：循环引用是指两个或多个对象相互持有对方的 `std::shared_ptr`，导致它们无法被销毁。通过将其中的一个或多个指针使用 `std::weak_ptr` 来持有，可以打破循环引用，允许对象在不再被引用时正确释放。

3. 安全地访问对象：`std::weak_ptr` 提供了 `lock()` 成员函数，用于获取一个有效的 `std::shared_ptr` 对象，从而安全地访问由 `std::shared_ptr` 管理的对象。如果对象已经被销毁，则 `lock()` 返回一个空的 `std::shared_ptr`。

通过使用 `std::weak_ptr`，我们可以更灵活地管理对象的生命周期，避免循环引用问题，并且可以在需要时安全地访问被共享指针管理的对象。

## 19、C++类的对象存储空间
C++ 类的对象存储空间主要包括以下几个方面：

1. 成员变量（Member Variables）：类的对象存储了其成员变量的数据。成员变量可以是各种类型，如基本数据类型（如整数、浮点数等）、指针、对象等。每个对象的成员变量都会占据一定的存储空间。

2. 成员函数（Member Functions）：类的成员函数（也称为方法）不直接存储在对象中，而是作为类的一部分存储在代码段中。每个对象共享相同的成员函数代码。

3. 虚函数表（Virtual Function Table，VTable）：当类中有虚函数时，每个对象都会存储一个指向虚函数表的指针，通常称为 vptr。虚函数表存储了该类的虚函数的地址，用于实现多态性。vptr 的大小通常是一个指针的大小。

4. 基类和派生类对象的存储：如果类是派生类（子类），则对象的存储空间中会包含基类和派生类的成员变量。派生类对象的存储空间包括基类的存储空间和派生类新增的成员变量。

5. 对象的对齐（Object Alignment）：对象的存储空间也受到对齐的影响。根据编译器和平台的不同，对象的存储可能会按照特定的字节对齐方式进行，以优化访问速度和内存布局。

总体而言，类的对象存储空间由成员变量、虚函数表指针（当有虚函数时）、基类对象存储空间（对于派生类）以及对齐要求共同组成。对象的大小取决于这些因素的累加，并受到编译器和平台的限制。可以使用 `sizeof` 运算符来获取对象的大小，但需要注意 `sizeof`它也会包括继承的基类对象的空间。

```cpp
#include <iostream>
using std::cout;
using std::endl;
class MyClass {
    int x; // 4字节
    double y; //8 
    char z; // 1
    //内存对齐后 8 + 8 + 8 = 24
};

class Base {
    int x; // 4
public:
    virtual void foo() {} //虚表指针: 8 
};

class Derived : public Base {
    double y; // 8
};

int main() {
    MyClass obj1;
    std::cout << sizeof(obj1) << std::endl;  // 输出对象的存储空间大小  24 
     Derived obj2;
    std::cout << sizeof(obj2) << std::endl;  // 输出对象的存储空间大小  8 + 8 + 8 = 24
    return 0;
}
```

## 20、拷贝初始化与直接初始化
-   当用于类类型对象时，拷贝初始化和直接初始化有所不同：直接初始化调用与实参匹配的构造函数，拷贝初始化总是调用拷贝构造函数。拷贝初始化首先使用指定构造函数创建一个临时对象，然后用拷贝构造函数将临时对象拷贝到正在创建的对象。
1. 直接初始化（Direct Initialization）：
   直接初始化是通过使用圆括号 `()` 或大括号 `{}` 将初始值传递给对象来进行的初始化。可以使用一个或多个参数传递给构造函数，以创建对象。例如：
   
   ```cpp
   int x = 10;
   int y(20);  // 直接初始化
   std::string str{"Hello"};  // 直接初始化
   ```
   
   直接初始化允许传递参数，以便选择合适的构造函数进行对象的初始化。如果有多个构造函数匹配参数，则根据参数类型和匹配的准确性选择合适的构造函数。

2. 拷贝初始化（Copy Initialization）：
   拷贝初始化是通过使用等号 `=` 将一个对象的值赋给另一个对象来进行的初始化。这种方式可以通过复制构造函数或转换构造函数来完成。例如：
   
   ```cpp
   int a = 10;
   int b = a;  // 拷贝初始化
   std::string str1 = "Hello";  // 拷贝初始化
   std::string str2 = str1;  // 拷贝初始化
   ```
   
   拷贝初始化的过程是创建一个新的对象，并将源对象的值复制到新对象中。对于类类型，可以通过复制构造函数来实现拷贝初始化。对于内置类型和其他可复制的类型，编译器会执行适当的拷贝操作。

需要注意的是，C++11 引入了列表初始化（List Initialization）的语法，可以使用花括号 `{}` 进行初始化。列表初始化允许更严格的类型检查，可以防止缩窄转换和隐式转换，提供更明确的初始化语义。列表初始化可以用于直接初始化和拷贝初始化。

```cpp
int x{10};  // 列表初始化，直接初始化
int y = {20};  // 列表初始化，拷贝初始化
std::string str{"Hello"};  // 列表初始化，直接初始化
std::string str2 = {"Hello"};  // 列表初始化，拷贝初始化
```
无论是直接初始化还是拷贝初始化，它们都是对象初始化的方式，用于创建并初始化对象。选择使用哪种方式取决于具体的需求和代码风格。

-   **为了提高效率，允许编译器跳过创建临时对象这一步**，直接调用构造函数构造要创建的对象，等价于**直接初始化**。
    1.  拷贝构造函数为private时: "="会报错 。
    2.  使用`explicit`修饰构造函数时：如果构造函数存在隐式转换，编译时会出错。

## 21、C++左值和右值

在 C++ 中，表达式可以被分类为左值（Lvalue）和右值（Rvalue），这两个术语用于描述表达式的属性和可用于的上下文。

1. 左值（Lvalue）：
   - 左值是一个表达式，它表示一个具名的对象或一个标识符，可以在表达式中获取它的地址。
   - 左值可以出现在赋值操作的左边或右边，可以被取地址、修改或作为参数传递给函数。
   - 通常，变量、函数或表达式返回的结果都可以是左值。

   示例：
   ```cpp
   int x = 10;  // x 是一个左值，可以获取地址
   int* ptr = &x;  // 取得 x 的地址
   x = 20;  // 修改 x 的值
   ```

2. 右值（Rvalue）：
   - 右值是一个表达式，它表示一个临时的、无法获取地址的值。
   - 右值通常是一个字面量、临时对象、表达式的结果或返回右值引用的函数调用。
   - 右值不能出现在赋值操作的左边，不能被取地址（除非使用 `std::move`）。

   示例：
   ```cpp
   int y = 5 + 3;  // 5 + 3 是一个右值，无法获取地址
   int z = x + y;  // x + y 是一个右值
   ```

C++11 引入了右值引用（Rvalue Reference）的概念，通过使用 `&&` 标记，允许我们对右值进行绑定，并支持移动语义和完美转发。

对于右值引用，有两种情况：
- 左值引用（Lvalue Reference）：使用 `&` 标记，绑定到左值。
- 右值引用（Rvalue Reference）：使用 `&&` 标记，绑定到右值。

右值引用的引入主要为了实现移动语义，可以高效地将资源从一个对象移动到另一个对象，而无需执行深拷贝。

示例：
```cpp
void foo(int&& x);  // 右值引用参数

int x = 10;
foo(x);  // 错误，无法将左值绑定到右值引用参数

foo(20);  // 20 是一个右值，可以传递给右值引用参数
```

## 22、C++11右值引用

C++11 引入的右值引用（Rvalue Reference）是一种新的引用类型，通过 `&&` 标记，用于识别和绑定到右值。右值引用主要为了支持**移动语义**、**完美转发**和**资源管理**。

以下是右值引用的一些关键特点和应用：

1. 绑定到右值：右值引用只能绑定到右值表达式，包括临时对象、字面量、表达式的结果和返回右值引用的函数调用。它不能绑定到左值，除非使用 `std::move` 进行显式转换。

   ```cpp
   int&& rref = 5;  // 右值引用绑定到字面量
   int&& rref2 = std::move(x);  // 使用 std::move 将左值转为右值引用
   ```

2. 移动语义：右值引用的主要应用之一是实现移动语义。通过将资源（如动态分配的内存）从一个对象移动到另一个对象，而不是执行深拷贝，可以提高效率。移动操作通常通过移动构造函数和移动赋值运算符来实现。

   ```cpp
   class MyObject {
   public:
       MyObject() = default;
       MyObject(MyObject&& other) noexcept {
           // 执行资源的移动操作
       }
       MyObject& operator=(MyObject&& other) noexcept {
           // 执行资源的移动操作
           return *this;
       }
   };

   MyObject obj1;
   MyObject obj2 = std::move(obj1);  // 调用移动构造函数
   obj2 = std::move(obj1);  // 调用移动赋值运算符
   ```

3. 完美转发：右值引用还支持完美转发，它允许以无损的方式将参数传递给其他函数，保留参数的值类别（左值还是右值）和 const 限定。

   ```cpp
   void foo(int&& x);  // 右值引用参数
   
   template<typename T>
   void bar(T&& value) {
       foo(std::forward<T>(value));  // 完美转发参数到 foo 函数
   }
   
   int x = 10;
   bar(x);  // 传递左值参数
   bar(20);  // 传递右值参数
   ```

4. 后续的资源管理：右值引用在资源管理方面也非常有用。例如，可以使用右值引用来实现智能指针、移动语义的容器类（如 `std::vector`、`std::unique_ptr`、`std::shared_ptr`）以及其他资源管理机制。

   ```cpp
   std::unique_ptr<int> ptr1 = std::make_unique<int>(42);  // 移动语义的智能指针
   std::vector<int> vec;
   vec.push_back(10);  // 接受右值参数的容器操作
   ```

> noexcept关键字含义？

`noexcept` 是 C++11 引入的一个关键字，用于指示函数是否会抛出异常。

在函数声明或定义中，可以使用 `noexcept` 关键字来表示函数是否可能引发异常。它可以有两种形式：

1. `noexcept`：表示函数不会抛出任何异常。如果函数在运行时抛出了异常，程序会调用 `std::terminate` 函数终止程序的执行。

   ```cpp
   void foo() noexcept {
       // 不会抛出异常的函数
   }
   ```

2. `noexcept(expression)`：表示函数在表达式 `expression` 求值时不会抛出异常。`expression` 是一个可以在编译时计算的常量表达式，它的结果必须是 `true`（不会抛出异常）或 `false`（可能抛出异常）。

   ```cpp
   void bar(int x) noexcept(x > 0) {
       // 根据表达式判断是否抛出异常
   }
   ```

使用 `noexcept` 关键字可以提供有关函数异常行为的信息，帮助代码的使用者了解函数可能的异常情况。这对于代码的可靠性、调试和优化都非常重要。

另外，`noexcept` 还可以用于类型的移动构造函数和移动赋值运算符，用于指示这些操作是否会抛出异常。这对于标准库容器类和智能指针等资源管理类的实现非常重要，以便在移动操作时能够高效且安全地处理异常情况。

需要注意的是，`noexcept` 关键字仅表示函数是否会抛出异常，它与函数是否会导致未定义行为或异常安全性无关。因此，需要综合考虑其他因素来确保代码的正确性和可靠性。

>   std::move和std::foward函数?

`std::move` 和 `std::forward` 都是 C++ 标准库中的函数模板，用于支持移动语义和完美转发。

1. `std::move`：
   - `std::move` 是一个函数模板，用于将左值转换为右值引用，以支持移动语义。
   - 它位于 `<utility>` 头文件中，接受一个参数并将其转换为右值引用。
   - `std::move` 并不实际执行任何移动操作，它只是将传入的左值转换为右值引用，告诉编译器该值可以被移动而不是拷贝。
   - `std::move` 可以用于标识一个对象可以被移动，并将其传递给移动构造函数或移动赋值运算符。

   示例：
   ```cpp
   std::vector<int> v1 = get_vector();  // get_vector 返回右值
   std::vector<int> v2 = std::move(v1);  // 使用 std::move 将 v1 转为右值引用，调用移动构造函数
   ```

2. `std::forward`：
   - `std::forward` 是一个函数模板，用于在函数模板中实现完美转发，保留参数的值类别（左值还是右值）和 const 限定。
   - 它位于 `<utility>` 头文件中，接受一个参数，并根据该参数的值类别进行转发。
   - `std::forward` 通常在函数模板的转发函数或转发构造函数中使用，以保持传入参数的值类别，并将其传递给其他函数。

   示例：
   ```cpp
   template <typename T>
   void forward_func(T&& arg) {
       other_func(std::forward<T>(arg));  // 使用 std::forward 实现完美转发
   }

   std::string str = "Hello";
   forward_func(str);  // 传递左值参数
   forward_func("World");  // 传递右值参数
   ```

   在这个示例中，`forward_func` 是一个模板函数，使用 `T&&` 来接收参数。在内部调用 `other_func` 时，使用 `std::forward<T>(arg)` 将参数完美转发。

`std::move` 和 `std::forward` 都是在移动语义和完美转发中常用的函数模板。它们在 C++ 中的使用可以提高代码的效率和灵活性，允许开发者在适当的时候执行移动操作和实现完美转发。需要注意的是，使用这些函数时应谨慎，确保正确地处理资源所有权和异常安全性。

## 23、C++11类型转换

C++11 引入了一些新的类型转换语法和关键字，以提供更精确的类型转换和更明确的语义。下面是 C++11 中的几种类型转换：

1. 静态转换（Static Cast）：
   - `static_cast` 用于进行基本类型的转换、显示转换、父子类之间的转换等。
   - 它在编译时进行类型检查，不进行运行时的安全检查。
   - 静态转换可以用于类层次结构中的上下转换，但没有动态转换所提供的运行时类型检查。

示例：
```cpp
double d = 3.14;
int x = static_cast<int>(d);  // 显示转换，将 double 转为 int
```

2. 动态转换（Dynamic Cast）：
   - `dynamic_cast` 用于在类层次结构中进行安全的向上转换和向下转换。
   - 它在运行时执行类型检查，并检查指针或引用是否可进行转换。
   - 当进行向下转换时，如果指针或引用不是目标类型的有效对象，`dynamic_cast` 将返回空指针（对于指针）或引发 `std::bad_cast` 异常（对于引用）。

示例：
```cpp
Base* basePtr = new Derived();  // 基类指针指向派生类对象
Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);  // 安全的向下转换
if (derivedPtr != nullptr) {
    // 转换成功，执行派生类操作
}
```

3. 常量转换（Const Cast）：
   - `const_cast` 用于在指针或引用上移除 `const` 或 `volatile` 限定符。
   - 它可以用于修改指向 `const` 对象的指针或引用，并使其具有非常量属性。

示例：
```cpp
const int* constPtr = new int(10);  // 指向常量的指针
int* mutablePtr = const_cast<int*>(constPtr);  // 移除 const 限定符
*mutablePtr = 20;  // 修改常量对象的值
```

4. 重新解释转换（Reinterpret Cast）：
   - `reinterpret_cast` 允许将指针或引用重新解释为其他类型的指针或引用。
   - 它提供了最底层的转换，可以将任意类型的指针互相转换，但潜在的未定义行为和风险需要谨慎使用。

示例：
```cpp
int* intPtr = new int(42);
char* charPtr = reinterpret_cast<char*>(intPtr);  // 将 int 指针转为 char 指针
```

## 24、为什么析构函数一般写成虚函数？

析构函数一般写成虚函数的主要原因是为了支持多态性和基类指针的删除。

当一个类被继承时，基类指针可以指向派生类对象。在这种情况下，如果析构函数不是虚函数，当通过基类指针删除对象时，只会调用基类的析构函数，而不会调用派生类的析构函数。这可能导致派生类中的资源没有正确释放，从而引发内存泄漏或其他问题。

通过将析构函数声明为虚函数，可以实现动态绑定（dynamic binding），使得在删除对象时能够根据实际对象类型调用正确的析构函数。这样，无论通过基类指针还是派生类指针删除对象，都会正确地调用相应的析构函数，确保资源的正确释放。

另外，如果一个类中定义了虚函数，通常意味着这个类可能会作为基类使用，用于派生更具体的子类。在这种情况下，为了支持多态性和正确的对象销毁，析构函数应该被声明为虚函数。

**总结起来，将析构函数声明为虚函数可以确保在通过基类指针删除对象时正确调用派生类的析构函数，避免资源泄漏，并支持多态性和基类的使用。**

## 25、为什么构造函数不能声明为虚函数或者纯虚函数？

虚函数对应一个`vtable`虚函数表，类中存储一个`vptr`指向这个`vtable`。如果构造函数是虚函数，需要`vtable`调用，可是对象还没有初始化就没有`vptr`，无法找到`vtable`，所有构造函数不能是虚函数。

## 25、C++中重写、重载和隐藏的区别

在C++中，重写（Override）、重载（Overload）和隐藏（Hide）是三个不同的概念，它们用于描述不同的函数关系。

1. 重写（Override）：
   重写是指派生类中的函数覆盖了基类中的同名虚函数。当派生类继承自基类并重新定义（重写）虚函数时，通过在派生类中使用`override`关键字显式标记，可以确保编译器在编译时检查函数是否正确地覆盖了基类的虚函数。重写实现了运行时多态性（Runtime Polymorphism）的概念，即通过基类指针或引用调用虚函数时，根据实际对象类型来动态绑定和调用适当的函数。

2. 重载（Overload）：
   重载是指在同一个作用域内，根据函数的参数类型、参数个数或参数顺序不同，定义多个具有相同名称但不同参数的函数。重载函数具有相同的函数名，但是在调用时根据传递的参数类型或数量的不同来确定调用哪个函数。重载实现了编译时多态性（Compile-time Polymorphism）的概念，即在编译时根据函数调用的参数类型或数量来确定具体调用哪个函数。

3. 隐藏（Hide）：
   隐藏是指派生类中的函数隐藏了基类中的同名函数，但没有覆盖（重写）基类的虚函数。当派生类中定义了与基类中同名的非虚函数时，基类的函数将被隐藏，无法通过基类指针或引用直接调用派生类中的同名函数。在隐藏的情况下，函数的调用是根据静态类型（编译时类型）来确定的，而不是根据动态类型（运行时类型）来确定。

总结：
- 重写（Override）是派生类覆盖基类中的虚函数，实现运行时多态性。
- 重载（Overload）是在同一个作用域内根据函数的参数类型、个数或顺序定义多个函数，实现编译时多态性。
- 隐藏（Hide）是派生类中的同名函数隐藏了基类中的函数，但没有覆盖基类的虚函数，调用是根据静态类型来确定的。

## 26、auto和decltype

`auto` 和 `decltype` 是 C++11 标准中引入的两个关键字，用于类型推导和类型声明。

-  `auto`关键字声明变量时，编译器会根据变量的初始化表达式自动推导出变量的类型，因此变量必须要有初始化。另外，对于函数返回值类型的推导，也可以使用 `auto`关键字。
-  `decltype` 关键字用于获取表达式的类型,不进行实际的计算表达式的值。

## 27、volatile、mutable和explicit关键字的用法

### volatile

-   用`volatile`声明的变量是"易失的"，可以被某些编译器未知的因素更改，比如：操作系统、硬件或其他线程。
-   使用`volatile`声明的变量，禁止编译器对它进行优化，保证每次使用它时都从变量所在内存进行读取数据，而不从寄存器中读取。多线程中被几个任务共享的变量需要定义为`volatile`类型。

### mutable

`mutable` 是一个关键字，用于标识一个成员变量可以在 `const` 函数中被修改。在 C++ 中，如果一个成员函数被声明为 `const`，则该函数不能修改任何成员变量。但是，如果某个成员变量被声明为 `mutable`，则该成员变量可以在 `const` 函数中被修改。

### explicit

`expliit`关键字修饰类的构造函数，防止出现隐式类型转换，只能以`显示的方式进行类型转换`。

-   只能用于类内部构造函数的声明
-   用于单个参数的构造函数

## 28、C++中的NULL和nullptr

为了与C语言兼容，C语言中`NULL`定义为`(void*) 0`,在C++中被定义为整数`0`。

`nullptr`是C++11提出的，用于区别整数和指针类型，能够根据环境自动转换成对应的指针类型，并不会转换成整数类型，解决了函数重载中造成传参错误的情况。

## 29、static用法

-   修饰局部变量：改变变量的生存期，只能被声明变量的函数内部使用。
-   修饰全局变量：只有本文件中的函数能够使用，其他文件无法使用。
-   修饰类成员变量：属于类，不属于对象
-   修饰类成员函数：属于类，不属于对象，函数不接受`this`指针，只能访问类内`static`成员变量。
-   类内声明，类外初始化，`static`修饰的变量先于对象存在。

## 30、深拷贝和浅拷贝的区别

-   浅拷贝：只是拷贝了基本类型的数据，仅仅指向被复制的内存地址
-   深拷贝：开辟一块新内存地址用于存放复制的对象。

当类中存在指针成员变量，如果执行浅拷贝，将A = B。若B中指针变量申请了内存，A中指针变量指向同一块内存，当B析构释放了内存，A中的指针变量就是野指针了。**需要在拷贝构造函数和赋值构造函数进行深拷贝操作。**

## 31、C++ vecotr push_back和emplace_back()的异同
-   相同点：
    -   都是向`vector`容器末尾添加一个元素
-   不同点：
    -   `push_back`调用拷贝构造函数和移动构造函数创建一个临时对象，`emplace_back`避免了拷贝构造函数的调用，利用可变参数模板和完美转发接受参数，将参数传递给对应的构造函数。
    -   `emplace_back`相比更加高效。

## 32、什么是菱形继承？菱形继承的缺点？如何解决？

菱形继承（diamond inheritance）是一种在多重继承中可能出现的问题，其中一个派生类从两个直接或间接基类继承，而这两个基类又共享一个共同的基类。

这种继承结构形成了一个菱形的图形，如下所示：

```
      A
     / \
    B   C
     \ /
      D
```

在这个菱形继承结构中，类D通过多重继承同时继承了类B和类C，而类B和类C又都直接或间接地继承自类A。这样，类D将从类A继承两个副本，一个来自类B的路径，一个来自类C的路径。

菱形继承可能导致以下问题：

1. 数据冗余：由于类D继承了两个副本的类A，这可能导致数据的冗余和浪费。

2. 访问二义性：如果类A中有一个成员变量或成员函数，那么在类D中使用该成员时可能会发生访问二义性。编译器无法确定应该使用哪个基类的成员，因为存在两个副本。

为了解决菱形继承问题，可以使用**虚拟继承（virtual inheritance）**。通过将**类B和类C的继承声明为虚拟继承，类D只继承一个共享的类A副本**，避免了数据冗余和访问二义性。

下面是一个使用虚拟继承解决菱形继承问题的示例：

```cpp
#include <iostream>

class A {
public:
    int x;
};

class B : virtual public A {
};

class C : virtual public A {
};

class D : public B, public C {
};

int main() {
    D d;
    d.x = 10;  // 通过类D访问类A的成员

    std::cout << d.x << std::endl;

    return 0;
}
```

在上述示例中，类B和类C使用虚拟继承来继承自类A，而类D通过多重继承同时继承了类B和类C。这样，类D只有一个共享的类A副本，避免了数据冗余和访问二义性的问题。

虚拟继承在解决菱形继承问题时需要慎重使用，因为它可能带来其他复杂性。它通常在需要共享基类信息的特殊情况下使用，以确保继承关系的正确性和可靠性。

## 33、C++11有哪些新特性？

-   `nullptr`替代`NULL`
-   `auto`和`decltype`实现自动类型推导
-   基于范围的`for`循环
-   引入初始化列表，简化了类、结构体及容器的初始化
-   `Lambda`匿名函数
-   右值引用和`move`语义
-   `std::function`和`std::bind`，用于函数对象的封装和绑定
-   并发编程支持：引入了**线程库、原子操作和互斥量**等支持多线程和并发编程的特性。

### std::function和std::bind函数

`std::function`和`std::bind`是C++11引入的工具，用于函数对象的封装和函数绑定。

1. `std::function`：
   - `std::function`是一个通用的函数包装器，可以用来封装各种可调用对象（函数、函数指针、成员函数指针、函数对象等）。
   - `std::function`提供了一种类型安全的方式来存储和调用不同类型的可调用对象，类似于函数指针的抽象。
   - 定义和使用`std::function`很简单，只需指定函数的签名（返回类型和参数类型）即可。

   示例：
   ```cpp
   #include <iostream>
   #include <functional>

   int add(int a, int b) {
       return a + b;
   }

   int main() {
       std::function<int(int, int)> func = add;
       std::cout << func(1, 2) << std::endl;  // 输出 3

       return 0;
   }
   ```

2. `std::bind`：
   - `std::bind`用于将可调用对象与其参数进行绑定，生成一个新的可调用对象。
   - 通过`std::bind`可以部分绑定参数，将某些参数提前绑定，以便在后续调用时只需传递剩余的参数。
   - 绑定的参数可以是具体的值、引用、占位符（`std::placeholders::_1`、`std::placeholders::_2`等）等。
   - `std::bind`返回一个函数对象，可以像普通函数一样进行调用。

   示例：
   ```cpp
   #include <iostream>
   #include <functional>

   int add(int a, int b) {
       return a + b;
   }

   int main() {
       auto func = std::bind(add, 10, std::placeholders::_1);
       std::cout << func(5) << std::endl;  // 输出 15

       return 0;
   }
   ```

通过使用`std::function`和`std::bind`，我们可以更灵活地操作函数对象和函数调用。它们在实际应用中可以用于实现回调机制、事件处理、函数适配器等。

### 并发编程
C++11引入了一些新特性和标准库组件，提供了对并发编程的支持，使得在C++中编写多线程和并发代码更加方便和安全。下面是C++11对并发编程的主要支持特性：

1. 线程库（`<thread>`）：C++11引入了一个新的标准库头文件`<thread>`，其中包含了用于创建和管理线程的类和函数。通过`std::thread`类，可以创建新的线程，并使用`std::thread`对象进行线程的管理，如启动、加入、分离等。

2. 互斥量和锁（`<mutex>`）：C++11引入了一组互斥量和锁的类和函数，用于实现线程之间的互斥同步。互斥量（`std::mutex`、`std::timed_mutex`等）用于保护共享数据的访问，锁（`std::lock_guard`、`std::unique_lock`等）用于获取和释放互斥量的所有权，确保临界区的独占访问。

3. 条件变量（`<condition_variable>`）：C++11引入了条件变量，用于线程之间的等待和通知机制。通过条件变量（`std::condition_variable`、`std::condition_variable_any`），线程可以等待某个条件满足，并在条件满足时进行通知和唤醒。

4. 原子操作（`<atomic>`）：C++11引入了原子操作的标准库组件，用于实现多线程环境中的原子操作。通过原子类型（`std::atomic`、`std::atomic_bool`、`std::atomic_int`等），可以对共享数据进行原子读写和修改，避免竞争条件和数据竞争。

5. 并发数据结构：C++11引入了一些并发数据结构的标准库组件，如并发队列（`std::queue`的线程安全版本）、并发哈希表（`std::unordered_map`的线程安全版本）等。这些数据结构提供了线程安全的操作，可以在多线程环境中使用。

6. 原子智能指针（`<memory>`）：C++11引入了原子智能指针`std::atomic_shared_ptr`，它是线程安全的共享指针，可以在多线程环境中安全地共享资源。

## 34、内存对齐的原因？

内存对齐是指在内存中分配变量时，变量的起始地址需要符合一定的规则，通常是以变量的字节大小为单位进行对齐。内存对齐的原因主要有以下几点：

1. 访问效率：内存对齐可以提高内存访问的效率。现代计算机体系结构通常会以缓存行（Cache Line）为单位从内存中读取数据。如果数据的起始地址不是缓存行对齐的，那么读取数据时可能需要跨越多个缓存行，导致额外的内存访问开销。而内存对齐可以保证数据按照缓存行对齐，减少不必要的内存访问。

2. 硬件限制：某些硬件对于数据访问的要求是有限制的。例如，有些体系结构要求特定类型的数据必须位于特定地址上，否则可能导致访问异常或错误。通过内存对齐，可以满足硬件的要求，确保数据的正确访问。

3. 结构体对齐：在结构体中，不同的成员变量可能有不同的大小，而内存对齐可以保证结构体的每个成员变量按照其大小对齐。这样可以避免因为不对齐而导致的额外空间开销和访问效率下降。

需要注意的是，内存对齐可能会导致一些内存浪费，特别是当变量的大小较小时。但是这种浪费通常被认为是可接受的，因为它可以提高程序的性能和可靠性。

在大多数情况下，编译器会自动进行内存对齐的处理。但是在某些情况下，比如需要与外部系统或硬件进行数据交互时，需要手动进行内存对齐的操作，以确保数据的正确传输和访问。

## 35、迭代器：前置++和后置++的区别

在C++中，迭代器是用于遍历容器（如数组、向量、列表等）元素的工具。迭代器提供了访问容器中元素的方式，并支持通过自增运算符（++）来遍历容器中的元素。

前置++（++iter）和后置++（iter++）是两种迭代器自增运算符的形式。它们在使用方式和返回值上有一些区别。

1. 前置++运算符：
   - 前置++运算符会先对迭代器进行自增操作，然后返回自增后的迭代器本身。
   - 代码示例：`++iter`

2. 后置++运算符：
   - 后置++运算符也会对迭代器进行自增操作，但它会返回自增前的迭代器的副本（一个临时对象）。
   - 代码示例：`iter++`

```cpp
//前置++,返回引用
int& operator++() {
    *this += 1;
    return *this;
}

//后置++,返回对象
int operator++() {
    int temp = *this;
    ++*this;
    return temp;
}
```

区别总结如下：

- 前置++运算符返回自增后的迭代器本身，而后置++运算符返回自增前的迭代器的副本。
- 后置++运算符会创建一个临时对象作为返回值，而前置++运算符不需要创建额外的对象。
- 对于使用自增运算符的表达式，前置++运算符的效率通常比后置++运算符高，因为它不需要进行副本的创建和销毁操作。


## 36、C++的异常处理机制

C++提供了一套异常处理机制，用于在程序执行过程中处理和传播异常情况。异常处理机制可以帮助我们在出现错误或异常情况时进行适当的处理，以确保程序的正确性和稳定性。

C++异常处理机制的关键部分包括以下几个关键词和关键概念：

1. `try`块：`try`块用于包含可能会抛出异常的代码块。在`try`块中，我们可以放置可能引发异常的代码。

2. `catch`块：`catch`块用于捕获和处理特定类型的异常。在`catch`块中，我们可以指定要捕获的异常类型，并在捕获到异常时执行相应的处理逻辑。

3. `throw`语句：`throw`语句用于在代码中显式地抛出异常。我们可以在适当的时候使用`throw`语句来抛出异常，以指示发生了异常情况。

4. 异常类型：异常类型可以是任何类型，包括内置类型、自定义类型或标准库提供的异常类型。通常，我们可以使用已有的标准异常类型（如`std::exception`及其派生类）或自定义异常类型来表示特定的异常情况。

异常处理的基本流程如下：

1. 在`try`块中，包含可能引发异常的代码。

2. 当在`try`块中的代码引发了异常，程序的控制权将转移到与该异常类型匹配的`catch`块中。如果找不到匹配的`catch`块，则异常将继续向上层调用栈传播，直到找到匹配的`catch`块或程序终止。

3. 在匹配的`catch`块中，可以处理异常，执行相应的处理逻辑。如果未在`catch`块中处理异常，则可以重新抛出异常，继续向上层调用栈传播。

以下是一个简单的示例，展示了异常处理的基本用法：

```cpp
#include <iostream>

void divide(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("Divide by zero exception");
    }
    int result = a / b;
    std::cout << "Result: " << result << std::endl;
}

int main() {
    try {
        divide(10, 2);
        divide(10, 0);
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
    return 0;
}
```

在上面的示例中，`divide`函数用于计算两个整数的商。当被除数为零时，会抛出一个`std::runtime_error`类型的异常。在`main`函数中，我们在`try`块中调用`divide`函数，并使用`catch`块捕获和处理异常。如果捕获到异常，程序将打印出异常的描述信息。

## 37、为什么拷贝构造函数必须传引用不能传值?

拷贝构造函数在C++中用于创建一个对象的副本，常用于对象的初始化和对象之间的赋值操作。拷贝构造函数的参数通常是一个常量引用，而不是按值传递，这是因为传值会引发一些问题。

当拷贝构造函数的参数使用按值传递时，会触发对象的复制操作。这意味着在调用拷贝构造函数时，会创建一个新的对象并将参数值复制到新对象中。这个过程涉及对象的拷贝构造，需要调用拷贝构造函数本身，但如果参数是按值传递，那么在调用拷贝构造函数时又会创建一个新的对象，这样就会陷入无限循环中。

另外，按值传递参数还涉及对象的拷贝，这可能会导致性能上的开销。特别是对于大型对象，复制整个对象可能非常耗时。

因此，为了避免无限递归和性能开销，拷贝构造函数通常采用常量引用作为参数。引用传递不会触发对象的拷贝操作，而只是传递对象的引用（地址）。这样可以避免对象的无限复制，并提高代码的执行效率。

以下是一个示例，展示了拷贝构造函数的定义和使用：

```cpp
class MyClass {
public:
    int value;

    // 拷贝构造函数，使用常量引用作为参数
    MyClass(const MyClass& other) {
        value = other.value;
    }
};

int main() {
    MyClass obj1;
    obj1.value = 10;

    // 使用拷贝构造函数创建对象的副本
    MyClass obj2(obj1);

    return 0;
}
```

在上面的示例中，`MyClass`类的拷贝构造函数接受一个常量引用作为参数。在`main`函数中，我们创建了一个`obj1`对象，并将其值设置为10。然后，通过调用拷贝构造函数，我们创建了一个`obj2`对象，它是`obj1`的副本。

需要注意的是，除了拷贝构造函数，其他涉及对象拷贝的地方，例如对象的赋值操作符重载（`operator=`）也应该使用引用参数，以避免上述问题。

## 38、如何快速定位错误出现的地方？

-   仔细阅读错误消息和日志输出
-   `gdb`调试，设置断点，单步执行，分析堆栈
-   在代码中添加适当的日志语句或调试输出
-   单元测试,使用单元测试框架编写针对特定函数或模块的测试案例

## 39、如何阻止一个类被实例化？有哪些方法？

-   将类定义为抽象基类
-   单例模式，将构造函数声明为`private`,在类内部创建对象

## 40、使用C++实现qt中信号与槽机制

要使用C++实现Qt中的信号与槽机制，需要一些额外的代码和设计模式。下面是一个简单的示例，演示了如何使用C++实现类似于Qt的信号与槽机制：

```cpp
#include <functional>
#include <iostream>
#include <vector>

// 定义信号类型
template<typename... Args>
class Signal {
public:
    // 信号绑定的槽函数类型
    using SlotFunction = std::function<void(Args...)>;

    // 连接槽函数到信号
    void connect(const SlotFunction& slot) {
        slots.push_back(slot);
    }

    // 触发信号，调用所有连接的槽函数
    void emitSignal(Args... args) {
        for (const auto& slot : slots) {
            slot(args...);
        }
    }

private:
    std::vector<SlotFunction> slots;
};

// 定义槽类型
void slotFunction(int value) {
    std::cout << "Slot function called with value: " << value << std::endl;
}

int main() {
    // 创建信号对象
    Signal<int> signal;

    // 连接槽函数到信号
    signal.connect(slotFunction);

    // 触发信号
    signal.emitSignal(42);

    return 0;
}
```

在上述示例中，我们定义了一个`Signal`类模板，表示一个具有参数的信号。该类维护了一个存储槽函数的向量。通过`connect`函数，我们可以将槽函数连接到信号。而`emitSignal`函数用于触发信号，调用所有连接的槽函数。

在`main`函数中，我们创建了一个`Signal`对象，并连接了一个槽函数`slotFunction`到该信号。然后，通过调用`emitSignal`函数来触发信号，槽函数会被调用并处理传递的值。

这个简单的示例演示了如何使用C++实现类似于Qt中的信号与槽机制。但需要注意的是，这只是一个简化的实现，无法涵盖Qt的完整功能和高级特性。Qt的信号与槽机制提供了更多的功能，如多线程安全、跨线程通信等，这些功能是通过元对象系统和MOC工具实现的。

在实际开发中，如果需要使用类似于Qt的信号与槽机制，建议直接使用Qt框架本身，以获得完整的功能和性能优化。如果你需要在没有Qt的环境中实现类似的机制，你可以参考上述示例，并根据需求进行必要的扩展和改进。

## 41、使用C语言实现C++面向对象特性

在C语言中，没有直接的内置支持面向对象的特性，如类、继承和多态。然而，我们可以使用一些技巧和约定来模拟面向对象的概念。下面是一些常见的技术，可用于在C语言中实现类似于C++的面向对象编程：

1. 结构体（Structures）：使用结构体来组织数据，并将相关的函数操作封装在一起。

```c
typedef struct {
    int data;
    void (*print)(MyStruct*);
} MyStruct;

void printMyStruct(MyStruct* obj) {
    printf("Data: %d\n", obj->data);
}

MyStruct obj;
obj.data = 42;
obj.print = printMyStruct;
obj.print(&obj); // 调用对象的方法
```

2. 函数指针（Function Pointers）：将函数指针作为结构体的成员，以实现成员函数的概念。

```c
typedef struct {
    int data;
    void (*print)(void*);
} MyStruct;

void printMyStruct(void* obj) {
    MyStruct* myObj = (MyStruct*)obj;
    printf("Data: %d\n", myObj->data);
}

MyStruct obj;
obj.data = 42;
obj.print = printMyStruct;
obj.print(&obj); // 调用对象的方法
```

3. 数据封装（Data Encapsulation）：使用函数来操作结构体的成员，以实现对数据的封装和访问控制。

```c
typedef struct {
    int data;
} MyStruct;

int getData(MyStruct* obj) {
    return obj->data;
}

void setData(MyStruct* obj, int value) {
    obj->data = value;
}

MyStruct obj;
setData(&obj, 42);
int value = getData(&obj);
printf("Data: %d\n", value);
```

4. 模块化编程（Modular Programming）：将相关的结构体和函数放在同一模块中，以实现封装和隔离。

```c
// MyModule.h
typedef struct {
    int data;
} MyStruct;

void printMyStruct(MyStruct* obj);

// MyModule.c
#include "MyModule.h"

void printMyStruct(MyStruct* obj) {
    printf("Data: %d\n", obj->data);
}

// main.c
#include "MyModule.h"

MyStruct obj;
obj.data = 42;
printMyStruct(&obj); // 调用模块中的函数
```

虽然这些技术可以帮助在C语言中模拟一些面向对象的特性，但请注意它们并不等同于C++的完整面向对象编程范式。C语言的这些技巧更多地侧重于数据和函数的组织，并缺乏对继承、多态等高级概念的支持。

## 42、使用C语言实现C++继承

在C语言中，没有直接的继承机制，但可以使用结构体和函数指针的组合来模拟一定程度上的继承。下面是一个简单的示例，演示了如何使用C语言来实现类似于C++的继承：

```c
#include <stdio.h>

// 基类结构体
typedef struct {
    int baseData;
} Base;

void basePrint(Base* base) {
    printf("Base Data: %d\n", base->baseData);
}

// 派生类结构体
typedef struct {
    Base base;  // 基类对象
    int derivedData;
} Derived;

void derivedPrint(Derived* derived) {
    basePrint(&(derived->base));  // 调用基类的函数
    printf("Derived Data: %d\n", derived->derivedData);
}

int main() {
    Derived derived;
    derived.base.baseData = 42;
    derived.derivedData = 10;

    derivedPrint(&derived);

    return 0;
}
```

在上述示例中，我们定义了一个基类结构体 `Base`，其中包含基类数据成员 `baseData` 和基类成员函数 `basePrint`。然后，我们定义了一个派生类结构体 `Derived`，其中包含了一个基类对象 `base` 和派生类数据成员 `derivedData`，以及派生类成员函数 `derivedPrint`。通过在派生类中嵌入一个基类对象，我们实现了类似于C++中的继承。

在 `derivedPrint` 函数中，我们先调用基类的 `basePrint` 函数，然后打印派生类的数据成员。

在 `main` 函数中，我们创建了一个派生类对象 `derived`，并分别给基类和派生类的数据成员赋值。然后，我们调用派生类的 `derivedPrint` 函数，它会依次调用基类的 `basePrint` 函数和打印派生类的数据。


## 43、说一下enable shared from this

`enable_shared_from_this`是 C++ 标准库中的一个模板类，用于在对象内部获取一个指向自身的`shared_ptr`。通过使用 `enable_shared_from_this`，可以在对象内部安全地创建 `shared_ptr`，而不会造成资源的过早释放或内存泄漏。

要使用 `enable_shared_from_this`，需要满足以下条件：

1. 类必须继承自 `enable_shared_from_this`并公开继承。
2. 类的构造函数必须是共享指针的构造函数，即参数为 `enable_shared_from_this`或 `enable_shared_from_this`。

以下是一个简单的示例，演示了如何使用`enable_shared_from_this`：

```cpp
#include <iostream>
#include <memory>

class MyClass : public std::enable_shared_from_this<MyClass> {
public:
    MyClass() = default;

    std::shared_ptr<MyClass> getShared() {
        return shared_from_this();
    }
};

int main() {
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>();
    std::shared_ptr<MyClass> ptr2 = ptr1->getShared();

    std::cout << "ptr1 use_count: " << ptr1.use_count() << std::endl;
    std::cout << "ptr2 use_count: " << ptr2.use_count() << std::endl;

    return 0;
}
```

在上述示例中，MyClass 继承自 "enable_shared_from_this"，并定义了一个成员函数 "getShared"，用于返回一个指向自身的 shared_ptr。在 main 函数中，我们创建了一个 shared_ptr "ptr1"，并通过 "getShared" 函数获取另一个 shared_ptr "ptr2"，它们都指向同一个 MyClass 对象。

通过 "use_count" 函数，我们可以看到 ptr1 和 ptr2 的引用计数都为 2，说明两个 shared_ptr 共享同一个对象，并成功地使用了 "enable_shared_from_this" 获取自身的 shared_ptr。

需要注意的是，使用 "enable_shared_from_this" 时需要小心，确保在对象生命周期内，只使用 shared_ptr 来管理对象的生存期，避免使用裸指针或弱引用 (weak_ptr) 导致对象过早释放或内存泄漏的问题。


## 44、面向对象的三大特性？

面向对象编程（Object-Oriented Programming，OOP）是一种编程范式，它基于对象的概念，将程序组织为一组相互作用的对象，以实现数据封装、继承和多态等特性。面向对象编程有三大主要特性，分别是封装、继承和多态。

**1. 封装（Encapsulation）：**

封装是面向对象编程的核心概念之一，它指的是将数据和操作（方法）封装在一个单元（对象）中，隐藏了对象的内部细节，只暴露出必要的接口供外部访问。这有助于减少程序的复杂性、提高代码的可维护性，并且可以实现数据的访问控制，确保数据只能通过规定的方式进行访问和修改。

**2. 继承（Inheritance）：**

继承是面向对象编程中实现代码重用的机制。通过继承，一个类（称为子类或派生类）可以继承另一个类（称为父类或基类）的属性和方法。子类可以扩展或修改从父类继承的属性和方法，同时还可以添加自己的属性和方法。继承有助于构建类之间的层次关系，促进了代码的重用和扩展。

**3. 多态（Polymorphism）：**

多态性是面向对象编程的一个重要特性，它允许不同的类使用相同的接口来实现不同的行为。多态性分为编译时多态和运行时多态两种。

- 编译时多态（静态多态）：也称为重载（Overloading），指的是在一个类中定义多个同名方法，但参数个数或类型不同，编译器根据调用时的参数来确定具体调用哪个方法。

- 运行时多态（动态多态）：通过继承和虚函数（C++中使用 `virtual` 关键字）实现，允许子类重写父类的虚函数，使得在运行时可以根据实际对象的类型来调用适当的方法。

多态性使得程序可以更灵活地适应不同的对象和需求，提高了代码的可扩展性和适应性。

综合来看，面向对象编程的三大特性——封装、继承和多态——帮助开发人员更好地组织和管理代码，提高代码的可维护性、可扩展性和
可重用性。

## 45、构造函数能抛出异常吗？析构函数可以吗？

-   **如果构造函数抛出异常，对象的析构函数将不会执行**，需要手动去释放已分配的资源，这很可能导致资源泄露的问题。
-   **如果析构函数抛出异常，和构造函数类似，而且更可能出现内存泄漏的问题**，因为释放内存的操作通常在析构函数中进行。而且在C++异常机制中，当发生异常时，会调用对象的析构函数来释放资源。如果此时析构函数也抛出了异常，异常发生无限嵌套，就会导致程序崩溃，所以C++标准中，指明析构函数不能，也不应该抛出异常。
-   如果无法确保析构函数是否抛出异常，**最好的方法就是将异常封装在析构函数内部**，比如可以使用**try-catch代码块进行捕获和处理异常**，总之，千万不要让异常游离在析构函数之外。

## 46、lambda表达式语法？值捕获和引用捕获的区别？值捕获无法修改变量吗？

>表达式语法？ 

lambda 表达式是 C++11 引入的一种语法，用于在局部范围内定义匿名的、一次性的函数。它们通常用于简化代码，避免创建不必要的命名函数或函数对象。lambda 表达式的基本语法如下：

```cpp
[capture_clause](parameter_list) -> return_type {
    // 函数体
}
```

以下是 lambda 表达式的各个部分的解释：

- **`capture_clause`：** 用于捕获变量，在 lambda 表达式中可以使用外部作用域的变量。可以为空、值捕获或引用捕获。

- **`parameter_list`：** 与普通函数的参数列表类似，指定 lambda 函数的参数。可以为空或包含一个或多个参数。

- **`return_type`：** 指定 lambda 函数的返回类型。可以省略，编译器会自动推断。

- **函数体：** 包含了要执行的代码。

下面是一个示例：

```cpp
#include <iostream>

int main() {
    int x = 5;
    int y = 10;

    // Lambda 表达式，捕获 x 和 y，参数为空，返回整数类型
    auto sum = [x, y]() -> int {
        return x + y;
    };

    std::cout << "Sum: " << sum() << std::endl; // 输出 15

    return 0;
}
```

在上述示例中，lambda 表达式通过 `[x, y]` 捕获了外部作用域中的变量 `x` 和 `y`。lambda 表达式的参数列表为空，返回类型指定为 `int`，并在函数体中返回了 `x + y` 的结果。

lambda 表达式还可以省略参数列表和返回类型，让编译器自动推断。例如：

```cpp
auto multiply = [](int a, int b) {
    return a * b;
};
```

> 值捕获和引用捕获的区别？

在 C++ 的 lambda 表达式中，可以使用捕获列表（Capture List）来指定 lambda 函数所需的外部作用域变量。捕获列表中的变量可以通过值捕获或引用捕获的方式被 lambda 函数使用。值捕获和引用捕获有一些重要的区别：

**值捕获（Value Capture）：**

在值捕获中，lambda 表达式会创建外部变量的拷贝，并将这个拷贝传递给 lambda 函数。这意味着 lambda 函数内部使用的变量和外部作用域中的变量是独立的，修改一个不会影响另一个。

示例：

```cpp
#include <iostream>

int main() {
    int x = 5;

    // 值捕获 x
    auto lambda = [x]() {
        std::cout << "Inside lambda: " << x << std::endl;
    };

    x = 10; // 外部 x 被修改，不影响 lambda 内部的 x

    lambda(); // 输出：Inside lambda: 5

    return 0;
}
```

**引用捕获（Reference Capture）：**

在引用捕获中，lambda 表达式通过引用访问外部变量，而不是创建拷贝。这意味着在 lambda 函数内部修改引用捕获的变量会影响外部作用域中的变量。

示例：

```cpp
#include <iostream>

int main() {
    int x = 5;

    // 引用捕获 x
    auto lambda = [&x]() {
        std::cout << "Inside lambda: " << x << std::endl;
    };

    x = 10; // 外部 x 被修改，影响 lambda 内部的 x

    lambda(); // 输出：Inside lambda: 10

    return 0;
}
```

需要注意的是，使用引用捕获时，需要确保外部变量在 lambda 函数使用期间保持有效。如果外部变量超出了作用域，那么引用就会成为悬垂引用，会导致未定义的行为。

> 值捕获无法修改变量了吗？

是的？

## 47、C++模板的优缺点？

C++模板是一种强大的语言特性，用于实现通用的、类型安全的代码。它们在C++中的广泛使用带来了许多优点，但也伴随着一些缺点。以下是C++模板的主要优缺点：

**优点：**

1. **通用性：** 模板允许你编写可以适用于多种数据类型的通用代码，从而避免了为每种类型编写重复的代码。这种通用性提高了代码的复用性和可维护性。

2. **类型安全：** 使用模板可以在编译时捕获类型相关的错误，从而减少运行时错误的可能性。这有助于提前发现潜在的问题并增强代码的稳定性。

3. **性能优化：** 模板允许在编译时生成针对特定类型的优化代码，从而提高程序的性能。通过内联展开等技术，可以消除函数调用的开销。

4. **标准库支持：** C++标准库中的许多功能都是通过模板实现的，使得库的功能强大且通用。容器、算法、迭代器等都是通过模板提供的。

5. **编译时代码生成：** 模板允许在编译时生成代码，这对于生成特定的数据结构或算法非常有用，而无需手动编写大量的重复代码。

**缺点：**

1. **编译时错误信息：** 模板的错误信息通常较为晦涩难懂，特别是在模板嵌套和复杂类型情况下。当出现编译错误时，定位问题可能会变得困难。

2. **编译时间：** 模板的使用可能导致编译时间增加，尤其是当模板的实例化很多或者模板嵌套层次较深时。

3. **二义性问题：** 当模板存在多个可能的匹配时，可能会出现函数调用二义性问题，导致编译错误或者不符合预期的结果。

4. **可读性：** 模板的语法和概念可能相对复杂，降低了代码的可读性。模板元编程（Template Metaprogramming）更是一个极具挑战性的领域。

5. **不稳定的语法：** C++中的模板语法在不同的编译器中可能会有微妙的差异，这可能导致一些跨平台的问题。

# STL

## 1、vector与list的区别与应用？

`std::vector`和`std::list`是C++ STL中两种不同的容器，它们在内部实现和特性上有着明显的区别。下面是`std::vector`和`std::list`之间的详细区别：

1. 内部存储结构：
   - `std::vector`：使用动态数组作为内部存储结构，元素在内存中是连续存储的。这意味着通过索引可以直接访问元素，支持随机访问。
   - `std::list`：使用双向链表作为内部存储结构，每个节点包含元素值以及指向前一个和后一个节点的指针。这导致元素在内存中是非连续存储的，访问元素需要遍历链表，不支持随机访问。

2. 内存分配方式：
   - `std::vector`：在创建`std::vector`时，会分配一块连续的内存空间，大小可动态调整。当元素数量超过当前容量时，`std::vector`会重新分配更大的内存空间，并将现有元素复制到新的内存位置。这可能导致插入和删除操作的时间复杂度为O(n)。
   - `std::list`：在每次插入或删除元素时，`std::list`会动态分配新的节点，而不需要重新分配整个存储空间。这使得插入和删除操作的时间复杂度为O(1)。

3. 插入和删除操作效率：
   - `std::vector`：由于元素在内存中是连续存储的，插入和删除操作涉及到元素的移动，特别是在容器的中间位置插入和删除元素会导致后续元素的移动，因此时间复杂度为O(n)。
   - `std::list`：由于元素在链表中相互连接，插入和删除操作只需要调整节点的指针，不需要移动其他元素，因此时间复杂度为O(1)。

4. 随机访问效率：
   - `std::vector`：由于元素在内存中是连续存储的，可以通过索引进行快速随机访问，时间复杂度为O(1)。
   - `std::list`：由于元素在链表中是非连续存储的，不支持通过索引进行快速随机访问，只能通过遍历链表来访问元素，时间复杂度为O(n)。

5. 内存占用：
   - `std::vector`：由于元素在内存中是连续存储的，需要分配一块连续的内存空间。在某些情况下，可能会导致内存浪费，特别是当容器的大小远远小于其容量时。
   - `std::list`：由于元素在链表中是非连续存储的，每个节点只包含元素值和指针，因此相对于`std::vector`可能会有更多的内存开销。

综上所述，**`std::vector`适用于需要快速随机访问、大量尾部插入和删除操作、内存连续性较好的场景**。**`std::list`适用于大量插入和删除操作、不需要随机访问、对内存连续性要求较低的场景**。

## 2、map、set底层是如何实现的？为什么使用红黑树？

`std::map`和`std::set`是C++ STL中的关联容器，它们的底层实现通常使用红黑树（Red-Black Tree）作为数据结构。

红黑树是一种自平衡的二叉搜索树，具有以下特性：
1. 每个节点要么是红色，要么是黑色。
2. 根节点是黑色。
3. 每个叶子节点（NIL节点，空节点）是黑色。
4. 如果一个节点是红色的，则它的两个子节点都是黑色的。
5. 从根节点到叶子节点或空子节点的每条路径上，黑色节点的数量是相同的。

红黑树之所以被用作`std::map`和`std::set`的底层实现，是因为它具有以下优点：

1. 有序性：红黑树是一种有序的数据结构，每个节点都按照特定的排序规则进行存储。这使得`std::map`和`std::set`可以提供有序的元素访问和范围查询功能。

2. 插入和删除的平衡性：红黑树通过自平衡的特性确保树的高度保持在较小的范围内，这保证了插入和删除操作的时间复杂度始终为O(logN)，其中N是树中元素的数量。红黑树通过进行旋转和重新着色等操作来保持平衡性。

3. 查找效率：由于红黑树是一种二叉搜索树，查找操作的时间复杂度为O(logN)，其中N是树中元素的数量。红黑树通过有序性和平衡性的特性，提供了高效的查找功能。

4. 动态性：红黑树支持高效地进行插入和删除操作，并保持树的平衡。这使得`std::map`和`std::set`适用于需要频繁修改的场景。

尽管红黑树相对于其他平衡树（如AVL树）在平衡性方面的严格要求较少，但它仍然能够提供较好的性能和平衡性，同时满足`std::map`和`std::set`对于有序性和动态性的需求。因此，红黑树成为了`std::map`和`std::set`的理想底层数据结构。

>AVL树？

AVL树是一种自平衡的二叉搜索树，它在结构上满足以下条件：
1. 对于任意节点，其左子树和右子树的高度之差（平衡因子）不超过1。
2. 每个节点的左子树和右子树都是AVL树。

AVL树得名于其发明者Adelson-Velsky和Landis。它通过维护平衡性来保证查找、插入和删除操作的时间复杂度为O(logN)，其中N是树中元素的数量。

AVL树的自平衡性是通过旋转操作来实现的，包括左旋、右旋、左右旋和右左旋。

1. 左旋（Left Rotation）：对于节点A，以其右子节点B为基准，将B提升为根节点，A成为B的左子节点，B的左子节点成为A的右子节点。
   
       A            B
      / \    =>    / \
         B        A

2. 右旋（Right Rotation）：对于节点A，以其左子节点B为基准，将B提升为根节点，A成为B的右子节点，B的右子节点成为A的左子节点。

         A        B
        / \  <=  / \
       B          A

3. 左右旋（Left-Right Rotation）：对于节点A，以其左子节点B的右子节点C为基准，先对B进行左旋，再对A进行右旋。
   
       A         C
      / \  =>   / \
         B     A   B
        /       \
       C

4. 右左旋（Right-Left Rotation）：对于节点A，以其右子节点B的左子节点C为基准，先对B进行右旋，再对A进行左旋。
   
         A         C
        / \  <=   / \
           B     B   A
            \   /
             C

在AVL树中，插入和删除操作时，会通过递归地进行平衡调整，检查每个节点的平衡因子，并进行相应的旋转操作来保持平衡。这样就可以在平衡的情况下保持树的高度较低，以提供高效的查找、插入和删除操作。

总结起来，AVL树通过维护平衡性来提供高效的查找、插入和删除操作。相比于红黑树，AVL树对平衡性的要求更为严格，但在某些特定的场景下，可能会导致更频繁的旋转操作。因此，根据具体的需求和应用场景，选择合适的平衡树数据结构可以提供最佳的性能和效率。

## 3、deque底层由什么实现？

`std::deque`（双端队列）是C++ STL中的容器之一，其底层通常由多个固定大小的连续存储块组成，每个块内部是一个数组。它被设计为在两端高效地插入和删除元素。

`std::deque`的底层数据结构可以被看作是一个由多个连续存储块构成的环形缓冲区。每个存储块（通常是一个固定大小的数组）被称为一个缓冲区（buffer）。这些缓冲区被链接在一起，形成一个双向链表的结构。链表中的每个节点（节点包含一个缓冲区）都有指向前一个节点和后一个节点的指针，以便在两端进行快速插入和删除操作。

这种结构使得`std::deque`具有以下特点：
1. 随机访问：由于每个缓冲区内部是一个数组，因此可以通过索引进行快速的随机访问，时间复杂度为O(1)。
2. 高效的头尾插入和删除：在`std::deque`的两端插入和删除元素都是高效的，时间复杂度为O(1)。这是因为可以通过调整链表节点的指针，将元素插入到头部或尾部的缓冲区中。
3. 动态扩展：`std::deque`可以根据需要动态地分配新的缓冲区，并链接到链表中。这使得`std::deque`能够支持任意数量的元素，而不会受到固定内存大小的限制。

需要注意的是，尽管`std::deque`的底层实现是由多个连续存储块组成的环形缓冲区，但对外表现为一个连续的容器。这意味着可以像操作连续数组一样使用迭代器和指针来访问元素，而无需关心实际的缓冲区结构。

总结来说，`std::deque`的底层数据结构是一个由多个固定大小的连续存储块组成的环形缓冲区，通过双向链表链接这些缓冲区。这使得`std::deque`能够提供高效的头尾插入和删除操作，并支持随机访问。

## 4、vector扩容

`std::vector`的底层扩容实现通常涉及以下步骤：

1. 当需要扩容时，`std::vector`会计算出新的容量大小。一般情况下，新容量会是当前容量的两倍，或者按照实现定义的其他策略来确定。

2. 分配新的内存空间。`std::vector`通过使用动态内存分配函数（例如`new`、`malloc`等）来分配新的内存块。新的内存块通常比当前容量更大。

3. 将旧内存中的元素复制到新内存中。`std::vector`会将旧内存中的元素逐个复制到新的内存空间中。这可以通过使用`std::move`或者直接进行内存复制来完成。复制过程中需要调用元素的复制构造函数或移动构造函数。

4. 释放旧的内存空间。一旦元素成功复制到新的内存中，`std::vector`会释放旧的内存空间，通常通过使用动态内存释放函数（例如`delete`、`free`等）来释放内存块。

需要注意的是，在扩容期间，迭代器、指针和引用等引用旧内存中的元素的对象将会失效，因为扩容会导致元素在内存中的位置发生变化。

此外，一些实现可能还会采取一些优化措施来提高扩容的效率，例如：

- 部分实现可能会在扩容时采用局部扩容策略，只在尾部或者某个特定位置进行扩容，而不是整个容器进行移动。
- 为了避免频繁的内存分配和释放操作，一些实现可能会使用内存池或者分配更大的内存块，以便进行多次扩容操作。

总结来说，`std::vector`的扩容实现通常涉及内存的重新分配、元素的复制和旧内存的释放。在扩容期间，需要注意迭代器和指针的失效问题。底层的具体实现可能因不同的编译器、平台和库版本而有所不同。
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

## 17、 野指针和悬空指针
均指向无效内存区域("不安全不可控")的指针，访问行为将会导致未定义行为。

-   野指针：未初始化的指针
-   悬空指针：指针最初指向的内存已经被释放了的一种指针
```cpp
int main() {
    int* p = nullptr;
    int* p2 = new int;
    p = p2;
    delete p2;
    //此时p、p2为悬空指针,一般置空
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

## 24、为什么析构函数一般写成虚函数

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


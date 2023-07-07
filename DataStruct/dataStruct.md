# 数据结构与算法

## 常见排序算法
![排序算法复杂度及稳定性](../image/sortAlogrithm.png)
### 冒泡排序
```cpp
#include <bits/stdc++.h>
using namespace std;

//基础冒泡排序
void bubbleSort(vector<int>& v) {
    for (int i = 0; i < v.size();++i) {
        for (int j = v.size() - 2; j >= i; --j) {
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
            }
        }
    }
}

//改进冒泡排序：使用flag标志是否在本次循环中是否有数据交换，若没有，结束
// 2 1 3 4 5 6 7 8 9
// i = 0 ->   1  2  3  4  5 6 7 8 9
// i = 1 ->   此时已经不需要进行交换了

void improveBubbleSort(vector<int>& v) {
    int flag = true;
    for (int i = 0; i < v.size() && flag; ++i) {
        for (int j = v.size() - 2; j >= i; --j) {
            flag  = false;
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
                flag = true;
            }
        }
    }
}

int main() {
    vector<int> v = {4, 3, 5, 9, 7};
    bubbleSort(v);
    for (auto i : v) {  
        cout << i << endl;
    }
}
```

### 选择排序
```cpp
void simpleSelectSort(vector<int>& v) {
    int min; //较小数的索引
    for (int i = 0; i < v.size() - 1; ++i) {
        min = i;
        for (int j = i + 1; j < v.size(); ++j) {
            if (v[j] < v[min]) {
                min = j;
            }
        }
        if (i != min) {
            swap(v[i], v[min]);
        }
    }   
}


int main() {
    vector<int> v = {4, 3, 5, 9, 7};
    simpleSelectSort(v);
    for (auto i : v) {  
        cout << i << " ";
    }
    cout << endl;
}

```


### 插入排序
```cpp

void insertSort(vector<int>& v) {
    for (int i = 1; i < v.size(); ++i) {
        int temp = v[i];
        int j;
        for (j = i - 1; j >= 0; j--) {
            if (v[j] > temp) {
                //向右移动一位
                v[j + 1] = v[j];
            } else {
                //排序结束
                break;
            }
        }
        v[j + 1] = temp;
    }
}
int main() {
    vector<int> v = {4, 3, 5, 9, 7};
    insertSort(v);
    for (auto i : v) {  
        cout << i << " ";
    }
    cout << endl;
}
```

### 希尔排序
```cpp
void shellSort(vector<int>& v) {
    int gap = v.size();
    while (gap > 1) {
        gap /= 2;
        for (int i = gap; i < v.size(); i++) {
            int temp = v[i];
            int j = i - gap;
            for (;j >= 0; j -= gap) {
                if (v[j] > temp) {
                    v[j + gap] = v[j];
                } else {
                    //此时无需排序
                    break;
                }
            }
            v[j + gap] = temp;
        }
    }
}


int main() {
    vector<int> v = {9,1,2,5,7,4,8,6,3,5,18};
    shellSort(v);
    for (auto i : v) {  
        cout << i << " ";
    }
    cout << endl;
}
```

### 快速排序
```cpp
#include <iostream>
#include <vector>
using namespace std;


//对每个子数组中找到一个关键字：使关键字不大于右边数，不小于左边数
int partition(vector<int>& v, int left, int right) {
    int pivotKey = v[left];
    while (left < right) {
        while (left < right && pivotKey <= v[right]) {
            right--;
        }
        swap(v[left], v[right]);
        while (left <right && pivotKey >= v[left]) {
            left++;
        }
        swap(v[left], v[right]);
    }
    return left;
}

//快速排序主要函数
void QSort(vector<int>& v, int left, int right) {
    int pivot;
    if (left < right) {
        pivot = partition(v, left, right);
        QSort(v, left, pivot - 1);
        QSort(v, pivot + 1, right);
    }
}

void quickSort(vector<int>& v) {
    QSort(v, 0, v.size() - 1);
}

void quickSort(vector<int>& v, int left, int right) {
    if (left >= right) return;
    int i = left, j = right;
    while (i < j) {
        while(i < j && v[j] >= v[left]) --j;
        while(i < j && v[i] <= v[left]) ++i;
        swap(v[i], v[j]);
    } 
    swap(v[i], v[left]);
    quickSort(v, left, i - 1);
    quickSort(v, i + 1, right);
}


int main() {
    vector<int> v = {9,1,2,5,7,4,8,6,3,5,18};
    //quickSort(v);
    quickSort(v, 0, v.size() - 1);
    for (auto i : v) {  
        cout << i << " ";
    }
    cout << endl;
}
```

### 堆排序
```cpp
#include <bits/stdc++.h>
using namespace std;


void swap(vector<int>& v, int left, int right) {
    int temp = v[left];
    v[left] = v[right];
    v[right] = temp;
}


void buildHeap(vector<int>& v) {
    for (int i = 0; i < v.size(); ++i) {
        int currentIndex = i;
        int fatherIndex = (currentIndex - 1) / 2;
        //当前索引值大于父节点，交换，将索引值指向父节点
        while (v[currentIndex] > v[fatherIndex]) {
            swap(v, currentIndex, fatherIndex);
            currentIndex = fatherIndex;
            fatherIndex = (currentIndex - 1 ) / 2;
        }
    }
}

void rebuildHeap(vector<int>& v, int index, int size) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    while (left < size) {
        int largestIndex;
        //判断左右孩子中较大值的索引,确保右孩子在size范围内
        if (v[left] < v[right] && right < size) {
            largestIndex = right;
        } else {
            largestIndex = left;
        }
        //比较父节点(index)的值与孩子中较大的值，并确定最大值的索引
        if (v[index] > v[largestIndex]) {
            break;
        }
        //若父节点不是最大值，与孩子中较大的值进行交换
        swap(v, largestIndex, index);
        index = largestIndex;
        //重新计算
        left = 2 * index + 1;
        right = 2 * index + 2; 
    }
}



void heapSort(vector<int>& v) {
    //构建大顶堆
    buildHeap(v);
    int size = v.size();
    while (size > 1) {
        //交换顶端元素与末尾元素:固定最大值
        swap(v, 0, size - 1);
        size--;
        //重新构建大顶堆
        rebuildHeap(v, 0, size);
    }
}



int main() {
    vector<int> v = {3,6,8,5,7};
    heapSort(v);
    for (auto i : v) {  
        cout << i << " ";
    }
    cout << endl;
}
```

## 归并排序
```cpp
#include <bits/stdc++.h>
using namespace std;


void myMerge(vector<int>& v, vector<int>& temp, int left, int mid, int right) {
    //i指向左数组首位置，j指向右数组首位置,k标识temp
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        //按顺序取左右数组中的最小值
        if (v[i] <= v[j]) {
            temp[k++] = v[i++];
        } else {
            temp[k++] = v[j++];
        }
    }
    while (i <= mid) {
        temp[k++] = v[i++];
    }
    while (j <= right) {
        temp[k++] = v[j++];
    }
    //更改v数组的值
    for (int k = left; k <= right; ++k) {
        v[k] = temp[k];
    }
}


void mergeSort(vector<int>& v, vector<int>& temp, int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    //递归左数组
    mergeSort(v, temp, left, mid);
    //递归右数组
    mergeSort(v, temp, mid + 1, right);
    //归并排序类似二叉树的后序遍历：当到达最后一层时，进行左数组和右数组的比较
    myMerge(v, temp, left, mid, right);
}


int main() {
    vector<int> v = {7,3,2,6,0,1,5,4};
    vector<int> temp(v.size());
    mergeSort(v, temp, 0, v.size() - 1);
    for (auto i : v) {
        cout << i;
    }
    cout << endl;
}
```


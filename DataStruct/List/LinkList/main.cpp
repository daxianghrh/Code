#include <iostream>
using namespace std;

typedef struct Node{
    int data;
    struct Node *next;
};
typedef struct Node *LinkList;

//为有头结点的单链表
/* 
--------------获取操作---------------
初始条件：单链表存在，且 1 <= i <=ListLength(L)
操作结果：用e返回L中第i个数据元素的值。若元素不存在返回0
*/
int GetElem(LinkList &L, int i, int &e)
{
    int j = 1;
    LinkList p = L->next;
    while(p && j < i){
        p = p->next;
        ++j;
    }
    if(!p) return 0;
    e = p->data;
    return e;
}

/*
----------------插入操作--------------
初始条件：单链表存在，且 1 <= i <=ListLength(L)
操作结果：向L中第i个元素后插入e，插入成功返回true,失败false
*/
bool ListInsert(LinkList &L, int i, int &e)
{
    int j = 1;
    LinkList p = L->next;
    while(p && j < i){
        p = p->next;
        ++j;
    }
    if(!p){
        cout << "第i个元素不存在" << endl;
        return false;
    }
    LinkList s = new Node;
    s->data = e;
    s->next = p->next;
    p->next = s;
    cout << "插入成功" << endl;
    return true;
}

/* 
---------------删除操作------------
初始条件：单链表存在，且 1 <= i <=ListLength(L)
操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1
*/
int ListDelete(LinkList &L, int i, int &e)
{
    int j = 1;
    LinkList p = L->next, q = new Node, tq = L;
    while(p && j < i){
        tq = p;
        p = p->next;
        ++j;
    }
    if(!(p->next)){
        cout << "位置i是尾结点" << endl;
        e = p->data;
        tq->next = nullptr;
        delete p;
        return e;
    }
    q = p->next;
    p->next = q->next;
    e = q->data;
    delete q;
    cout << "删除成功" << endl;
    return e;
}

//------------------单链表建立----------------
/* 
    头插法 建立带表头结点的单链表
    新结点永远在第一的位置
*/
void CreatListHead(LinkList &L, int n)
{
    L->next = nullptr;
    srand(time(0));
    for(int i = 0; i < n; ++i){
        LinkList p = new Node;
        p->data = rand()%100 + 1;
        p->next = L->next;
        L->next = p;
    }
}

/* 
    尾插法  新结点永远在最后位置
*/
void CreatListTail(LinkList &L, int n)
{
    cout << "开始尾插法建立单链表" << endl;
    L->next = nullptr;
    LinkList p, s = L;
    srand(time(0));
    for(int i = 0; i < n; ++i){
        p = new Node;
        p->data = rand()%100 + 1;
        s->next = p;
        s = p;
    }
    s->next = nullptr;
}

/* 
-------------------单链表的遍历----------------
*/
void traverseList(LinkList &L)
{
    LinkList p = L;
    if(p->next == nullptr) cout << "单链表为空" << endl;
    while(p->next){
        p = p->next;
        cout << p->data << endl;
    }
}

/* 
------------------单链表的长度-------------
*/
int lengthOfList(LinkList &L)
{
    LinkList p = L;
    int count = 0;
    while(p->next){
        p = p->next;
        ++count;
    }
    return count;
}

/* 
------------------删除单链表----------------
*/
bool clearList(LinkList &L)
{
    LinkList p = L->next, q;
    while(p){
        q = p->next;
        delete p;
        p = q;
    }
    L->next = nullptr;
}

int main(){
    LinkList L;
    CreatListTail(L, 5);
    traverseList(L);

}
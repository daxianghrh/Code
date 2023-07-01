#include <iostream>
#include <stack>
class MyQueue {
public:
    MyQueue() {
        
    }
    
    void push(int x) {
       s1.push(x);
    }
    
    int pop() {
        //s2出栈为空，将s1入栈的数据全部推入s2中
        if(s2.empty()){
            while(!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
        }
        int ans = s2.top();
        s2.pop();
        return ans;
    }
    
    int peek() {
        //调用pop函数
        int ans = this->pop();
        s2.push(ans);
        return s2.top();
    }
    
    bool empty() {
        return (s1.empty() && s2.empty());
    }
private:
    std::stack<int> s1; //入栈
    std::stack<int> s2; //出栈
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
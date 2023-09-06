# WebServer

## 知识点

### 1、socket网络编程中listen函数的第二个参数的含义？

Chatgpt: 在socket网络编程中，`listen`函数用于将一个未连接的套接字（socket）转换为被动监听套接字，使其可以接受来自其他套接字的连接请求。`listen`函数的原型如下：

```c
int listen(int sockfd, int backlog);
```

其中，`sockfd`是指定要监听的套接字，而`backlog`是指定连接请求队列的最大长度。现在我们来详细解释`backlog`参数的意义：

1. `backlog`参数的含义：
   `backlog`参数指定了套接字内核队列的长度，即等待被服务器`accept`处理的连接请求的最大数量。当有新的连接请求到达服务器，但服务器还没有调用`accept`接受连接时，这些连接请求就会被放置在一个队列中等待处理。

2. 连接请求队列的工作原理：
   当有新的连接请求到达服务器端，如果连接请求队列已满（即等待被处理的连接请求数量达到了`backlog`的限制），那么服务器可能会拒绝额外的连接请求，或者根据实现和操作系统的不同，新的连接请求可能会被忽略或丢弃。因此，`backlog`参数的设置很重要，它应该根据服务器的预期负载和处理能力来进行合理的调整。

   如果队列长度超过了系统允许的最大限制（通常是几千或几万），则服务器可能会在达到最大限制时出现不可预测的行为。因此，建议设置一个合理的`backlog`值，以确保服务器能够及时处理连接请求而不会导致队列溢出。

值得注意的是，`backlog`参数仅影响未连接队列（即等待调用`accept`的连接请求队列），已连接队列（已经通过`accept`函数接受的连接）不受该参数影响。

在实际使用中，建议根据服务器的负载能力和并发连接数预估，合理地设置`backlog`参数。如果你的服务器是短连接的场景，可以将`backlog`设置为较小的值；如果是长连接场景或者预计有较大并发连接数，可以适当增大`backlog`的值。

### 2、  int number = epoll_wait(m_epollfd, events, MAX_EVENT_NUMBER, -1); 什么意思？

这段代码是使用Linux下的`epoll`多路复用机制来进行事件监听和等待。让我们逐步解释：

```c
int number = epoll_wait(m_epollfd, events, MAX_EVENT_NUMBER, -1);
```

1. `m_epollfd`: 是一个已经创建并初始化的`epoll`实例的文件描述符（即`epoll_create`函数的返回值），用于标识和操作`epoll`实例。

2. `events`: 是一个用于存放事件的数组，它是一个指向`epoll_event`结构体的指针。`epoll_event`结构体用来存储发生的事件和关联的数据。在`epoll_wait`返回时，发生的事件将会被填充到这个数组中。

3. `MAX_EVENT_NUMBER`: 是定义的一个常量，它表示`events`数组的大小，即数组中最多能存放多少个事件。

4. `-1`: 是`epoll_wait`函数的超时时间参数。在这里，将其设置为-1表示`epoll_wait`将一直阻塞等待事件的发生，直到有事件发生才会返回。也就是说，`epoll_wait`会一直等待直到有连接请求到达、数据可读/写、或者其他感兴趣的事件发生。

函数的作用：这行代码的作用是在`m_epollfd`所指向的`epoll`实例上进行事件监听，并且会阻塞等待直到有事件发生。一旦有事件发生，`epoll_wait`会将事件信息填充到`events`数组中，并返回发生的事件数量。然后你可以通过遍历`events`数组，处理每一个发生的事件。

通常，在一个循环中反复调用`epoll_wait`来实现事件驱动的异步编程，这样你的程序就可以同时监听多个套接字的事件，并根据事件类型执行相应的处理逻辑。


### 3、Reactor模式和Proactor模式的区别？

服务端程序通常需要处理三类事件：IO事件、信号和定时事件。主要有两种事件处理模式：

-   `Reactor`模式：主线程(IO处理单元)只负责监听文件描述符上是否有事件发生(可读、可写)，若有，将`socket`可读可写事件放入请求队列，交给工作线程进行读写和处理。
-   `Proactor`模式：所有IO读写操作都由主线程和内核来处理，工作线程仅负责处理逻辑，如主线程读完成后`users[sockfd].read()`,选择一个工作线程来处理客户端请求`pool->append(users + sockfd)`。

通常使用同步I/O模型（如epoll_wait）实现Reactor，使用异步I/O（如aio_read和aio_write）实现Proactor。


### 4、epoll对文件描述符的两种操作模式: LT(水平触发)和ET(边沿触发)，两者的区别是什么？

-   LT:若这次事件没有被处理完，该事件还会被`epoll_wait`捕获
-   ET:事件只会被触发一次，需要一次处理完

### 5、为什么要使用线程池？

因为新建一个线程会带来性能开销，并且会为每个线程分配堆栈，消耗内存。为了任务的并发执行，我们使用线程池，任务被传递到工作队列中，线程池中的空闲线程从工作队列中取出任务执行。

### 6、如何解析HTTP报文?

采用**主从状态机**模式进行解析，从状态机(`parser_line`)负责读取报文的一行，主状态机负责对该行数据进行解析，主状态机内部调用从状态机，从状态机驱动主状态机。每解析一部分都会将整个请求的`m_check_state`状态改变，状态机也就是根据这个状态来进行不同部分的解析跳转的。

### 7、定时器及定时器优化？

使用了`C++`中组合的设计思想，将定时器类`util_timer`与客户端相关信息的类`client_data`组合在一起，并提供一种更结构化、可扩展和易维护的方式来实现功能。
```cpp
struct client_data
{
    sockaddr_in address;
    int sockfd;
    util_timer *timer;
};

class util_timer
{
public:
    util_timer() : prev(NULL), next(NULL) {}

public:
    time_t expire;
    
    void (* cb_func)(client_data *);
    client_data *user_data;
    util_timer *prev;
    util_timer *next;
};
```

这个基于升序双向链表实现的定时器存在着其固有缺点：

每次遍历添加和修改定时器的效率偏低(O(n))，使用最小堆结构可以降低时间复杂度降至(O(logn))。
每次以固定的时间间隔触发SIGALRM信号，调用tick函数处理超时连接会造成一定的触发浪费，举个例子，若当前的TIMESLOT=5，即每隔5ms触发一次SIGALRM，跳出循环执行tick函数，这时如果当前即将超时的任务距离现在还有20ms，那么在这个期间，SIGALRM信号被触发了4次，tick函数也被执行了4次，可是在这4次中，前三次触发都是无意义的。对此，我们可以动态的设置TIMESLOT的值，每次将其值设置为当前最先超时的定时器与当前时间的时间差，这样每次调用tick函数，超时时间最小的定时器必然到期，并被处理，然后在从时间堆中取一个最先超时的定时器的时间与当前时间做时间差，更新TIMESLOT的值。

### 8、日志优化？




### 9、`pthread_create`函数原型中的第三个参数，为函数指针，指向处理线程函数的地址。为什么当处理线程函数为类成员函数时，需要将其设置为静态成员函数?

原因为：C++的成员函数在编译后与普通函数有一些不同之处，最显著的是它们需要一个额外的隐式参数，即指向类实例（对象）的指针（通常称为this指针）。而pthread_create函数所期望的线程函数签名是 void *(*start_routine)(void *)，它只接受一个指向 void 参数的指针。

因此，如果你试图将普通的非静态成员函数作为线程函数传递给 pthread_create，编译器会报错，因为这个成员函数的签名不符合 pthread_create 需要的签名。

解决方法之一是将成员函数设置为静态成员函数，因为静态成员函数不依赖于类的实例，所以没有隐式的 this 指针，其签名与 pthread_create 所期望的线程函数签名一致。但这种方法的限制是，你无法在静态成员函数中直接访问非静态成员变量或调用非静态成员函数。

另一种方法是使用一个非成员函数作为中间代理，将实际的成员函数调用封装在这个代理函数中。你可以将类的实例指针作为参数传递给代理函数，然后在代理函数内部调用成员函数

### 10、epolloneshot的作用？

这时就引入了 EPOLLONESHOT 选项的作用。当你使用 EPOLLONESHOT 选项时，epoll 会确保每个文件描述符在一次事件被处理后只会被触发一次，然后它将自动将该文件描述符从 epoll 集合中移除。这样可以避免多个线程同时处理同一个文件描述符的事件，从而简化了同步和竞争的处理。

需要注意的是，如果使用 EPOLLONESHOT，则在每次处理完事件后都需要重新设置文件描述符的事件监听。如果不这样做，文件描述符将不会再次被触发，因为它已经被移除了 epoll 集合。

### 11、select、poll和epoll的应用场景？

-  当所有的fd都是活跃连接，使用epoll，需要建立文件系统，红黑树和链表对于此来说，效率反而不高，不如selece和poll

-  当监测的fd数目较小，且各个fd都比较活跃，建议使用select或者poll

-  当监测的fd数目非常大，成千上万，且单位时间只有其中的一部分fd处于就绪状态，这个时候使用epoll能够明显提升性能

### 12、http协议中的get和post请求？

请求方法:Get和Post。由请求行（request line）、请求头部（header）、空行和请求数据四个部分组成。

- Get:
```txt
1    GET /562f25980001b1b106000338.jpg HTTP/1.1
2    Host:img.mukewang.com
3    User-Agent:Mozilla/5.0 (Windows NT 10.0; WOW64)
4    AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.106 Safari/537.36
5    Accept:image/webp,image/*,*/*;q=0.8
6    Referer:http://www.imooc.com/
7    Accept-Encoding:gzip, deflate, sdch
8    Accept-Language:zh-CN,zh;q=0.8
9    空行
10    请求数据为空
```

- POST:
```txt
1    POST / HTTP1.1
2    Host:www.wrox.com
3    User-Agent:Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 2.0.50727; .NET CLR 3.0.04506.648; .NET CLR 3.5.21022)
4    Content-Type:application/x-www-form-urlencoded
5    Content-Length:40
6    Connection: Keep-Alive
7    空行
8    name=Professional%20Ajax&publisher=Wiley
```

HTTP响应也由四个部分组成，分别是：状态行、消息报头、空行和响应正文。
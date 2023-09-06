# EmerencyRobot

涉及技术栈：`WebSocket`、`信号与槽`、`Opencv`、`Pytorch`、`TTS`、`RTP`、`多线程编程`

## 什么是WebSocket?
底层`TCP/IP`协议，面向连接的全双工通信方式。

## 为什么采用WebSocket通信协议？
因为移动小车厂家提供与底层通信的方式采用的是`WebSocket`通信方式，数据格式采用`JSON`,为了方便使用与解决实际需要，故采用该种方式，同时QT中提供了`QWebSocket`类库，对`socket`的封装。

## qt中的信号与槽的底层原理？

Qt的信号与槽机制的底层实现基于元对象系统（Meta-Object System）。这个系统负责在运行时管理类的信息、信号、槽和其他元数据。以下是信号与槽机制的底层实现概述：

1. **元对象（Meta Object）：** 在Qt中，每个QObject派生的类都有一个对应的元对象。元对象是一个描述类的元数据的数据结构，其中包含了类的名称、父类信息、信号和槽信息等。

2. **MOC编译器（Meta-Object Compiler）：** 为了处理信号与槽机制，Qt引入了MOC编译器。MOC会解析源代码中使用`Q_OBJECT`、`Q_SIGNALS`和`Q_SLOTS`等宏标记的部分，并生成额外的C++代码。这些代码包含了元对象的信息，用于支持信号与槽的连接和调用。

3. **信号表（Signal Table）和槽表（Slot Table）：** 在元对象中，有两个重要的表格，即信号表和槽表。信号表记录了类中所有声明的信号，包括信号的名称、参数类型等信息。槽表则记录了类中声明的槽，以及槽的名称、参数类型等信息。

4. **连接的建立：** 当使用`QObject::connect`函数建立信号与槽的连接时，Qt会在发射信号的对象的元对象中查找信号的索引，然后在接收信号的对象的元对象中查找槽的索引。这样，Qt就可以在运行时知道如何在信号发射时调用正确的槽。

5. **信号的发射与槽的调用：** 当信号发射时，Qt通过元对象中的信号索引找到连接的槽的索引，并通过函数指针调用槽函数。这意味着，信号发射和槽的调用是在运行时动态完成的。
## qt中的多线程编程

[qt中常见多线程编程方法](https://blog.csdn.net/weixin_44840658/article/details/108625659#:~:text=Qt%E7%9A%844%E7%A7%8D%E5%A4%9A%E7%BA%BF%E7%A8%8B%E5%AE%9E%E7%8E%B0%E6%96%B9%E5%BC%8F%201%20%E4%B8%80%E3%80%81QThread%E7%B1%BB%E7%9A%84run%20%E4%B8%80%E3%80%81%E5%AE%9E%E7%8E%B0%E6%96%B9%E6%B3%95%EF%BC%9A%20%E6%96%B0%E5%BB%BA%E4%B8%80%E4%B8%AA%E9%9B%86%E6%88%90QThread%E7%9A%84%E7%B1%BB%EF%BC%8C%E9%87%8D%E5%86%99%E8%99%9A%E5%87%BD%E6%95%B0run%2C%E9%80%9A%E8%BF%87run%E5%90%AF%E5%8A%A8%E7%BA%BF%E7%A8%8B%20%E4%BA%8C%E3%80%81%E7%A4%BA%E4%BE%8B%EF%BC%9A%20...%202,%E4%B8%89%E3%80%81QRunnalble%E7%9A%84run%20Qrunnable%E6%98%AF%E6%89%80%E6%9C%89%E5%8F%AF%E6%89%A7%E8%A1%8C%E5%AF%B9%E8%B1%A1%E7%9A%84%E5%9F%BA%E7%B1%BB%E3%80%82%20...%204%20%E5%9B%9B%E3%80%81QtConcurrent%E7%9A%84run%20Concurrent%E6%98%AF%E5%B9%B6%E5%8F%91%E7%9A%84%E6%84%8F%E6%80%9D%EF%BC%8CQtConcurrent%E6%98%AF%E4%B8%80%E4%B8%AA%E5%91%BD%E5%90%8D%E7%A9%BA%E9%97%B4%EF%BC%8C%E6%8F%90%E4%BE%9B%E4%BA%86%E4%B8%80%E4%BA%9B%E9%AB%98%E7%BA%A7%E7%9A%84%20API%EF%BC%8C%E4%BD%BF%E5%BE%97%E5%9C%A8%E7%BC%96%E5%86%99%E5%A4%9A%E7%BA%BF%E7%A8%8B%E7%9A%84%E6%97%B6%E5%80%99%EF%BC%8C%E6%97%A0%E9%9C%80%E4%BD%BF%E7%94%A8%E4%BD%8E%E7%BA%A7%E7%BA%BF%E7%A8%8B%E5%8E%9F%E8%AF%AD%EF%BC%8C%E5%A6%82%E8%AF%BB%E5%86%99%E9%94%81%EF%BC%8C%E7%AD%89%E5%BE%85%E6%9D%A1%E4%BB%B6%E6%88%96%E4%BF%A1%E5%8F%B7%E3%80%82%20)

## qt中实现生产者-消费者模型？

当在Qt中实现生产者消费者模型时，使用条件变量（QWaitCondition）可以更有效地实现线程同步，避免不必要的轮询。以下是在前面示例的基础上添加了条件变量的实现：

```cpp
#include <QCoreApplication>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>

class Buffer {
public:
    Buffer(int size) : maxSize(size), count(0) {}

    void produce() {
        mutex.lock();
        if (count < maxSize) {
            ++count;
            qDebug() << "Produced, count =" << count;
            notEmpty.wakeAll(); // Signal consumers that data is available
        }
        mutex.unlock();
    }

    void consume() {
        mutex.lock();
        while (count == 0) {
            notEmpty.wait(&mutex); // Wait until there's data to consume
        }
        --count;
        qDebug() << "Consumed, count =" << count;
        mutex.unlock();
    }

private:
    int maxSize;
    int count;
    QMutex mutex;
    QWaitCondition notEmpty;
};

class Producer : public QThread {
public:
    Producer(Buffer* buffer) : buffer(buffer) {}

    void run() override {
        for (int i = 0; i < 10; ++i) {
            buffer->produce();
            msleep(500); // Simulate production time
        }
    }

private:
    Buffer* buffer;
};

class Consumer : public QThread {
public:
    Consumer(Buffer* buffer) : buffer(buffer) {}

    void run() override {
        for (int i = 0; i < 10; ++i) {
            buffer->consume();
            msleep(800); // Simulate consumption time
        }
    }

private:
    Buffer* buffer;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Buffer buffer(5);
    Producer producer(&buffer);
    Consumer consumer(&buffer);

    producer.start();
    consumer.start();

    producer.wait();
    consumer.wait();

    return a.exec();
}
```

在上述示例中，`Buffer` 类中使用了 `QWaitCondition` 来实现条件变量。生产者在生产数据时通过 `notEmpty.wakeAll()` 来唤醒等待的消费者线程。消费者线程在没有数据可消费时，通过 `notEmpty.wait(&mutex)` 来等待条件变量满足。

这种方式避免了消费者线程的空轮询，提高了线程的效率和性能。同时，使用了互斥锁 `mutex` 来确保在修改数据和等待条件变量时的线程安全。

## 如何实现心跳检测功能？
在对`QWebSocket`客户端进行封装时，添加一个是否自动重连和心跳次数的两个成员变量；使用`QTimer`定时器，定时器每5s进入一次槽函数，槽函数内心跳次数加1，对心跳次数进行判断，是否超过阈值，若超过，则表明心跳超时，根据是否自动重连的标志进行重连操作，若重连失败表示服务端异常；若未超过阈值，则通过`WebSocket`通信协议向服务端发送一个心跳包，服务端收到心跳包后，对应地发送一个心跳包，将客户端的心跳次数清0。心跳包为自定义的`JSON`数据。

## 为什么使用`JSON`数据格式?
JSON数据格式由键值对构成，键是字符串，值可以是字符串、数字、布尔值、数组、对象或null。

Qt提供了解析和生成JSON数据的类库，这些类位于Qt Core模块中。主要涉及两个类：QJsonDocument用于解析和生成JSON数据，以及QJsonObject用于操作JSON对象数据。

轻量，易理解，因为我们的开发环境在`QT`中，`QT`中的`QJSON`类库提供的接口很容易对`JSON`格式进行解析和封装。

## Opencv提供的DNN模块？

在OpenCV中，DNN（Deep Neural Networks）模块是用于深度学习推理的功能。该模块允许使用训练好的深度神经网络模型来进行图像处理和计算机视觉任务。

DNN模块提供了一个通用的深度学习推理接口，可以加载和运行各种深度学习框架（如Caffe、TensorFlow、PyTorch等）训练的模型。这使得OpenCV能够利用现有的深度学习模型，并在图像和视频上进行对象检测、图像分类、人脸识别等任务。

DNN模块的一些主要功能包括：

-   模型加载：DNN模块可以加载训练好的深度学习模型，支持多种格式（如Caffe、TensorFlow、Torch、ONNX等），并将其转换为OpenCV内部的中间表示。

-   推理：加载后的模型可以用于推理（inference），即在给定输入图像上运行模型，得到输出结果。推理过程可以在CPU、GPU或其他硬件上进行加速。

-   预处理和后处理：DNN模块提供了图像预处理和输出后处理的函数，用于准备输入数据和处理推理结果。

-   模型优化：DNN模块允许通过减少模型的计算量和参数量来优化模型，以提高推理性能。

>支持多种格式（如Caffe、TensorFlow、Torch、ONNX等）中的ONNX是什么意思?

ONNX代表"Open Neural Network Exchange"，是一种开放的、跨平台的深度学习模型交换格式。它的目标是使深度学习框架之间的模型迁移变得更加容易，让不同的框架可以无缝地加载和执行彼此训练的模型。

ONNX由微软和Facebook共同开发，并在2017年作为开源项目发布。它提供了一种中间表示的规范，能够捕捉深度学习模型的结构和参数，而不依赖于任何特定的深度学习框架。这种中间表示允许不同框架之间转换模型，使得开发者能够在各种框架中共享和部署模型。

ONNX支持多种深度学习框架，包括Caffe2、TensorFlow、PyTorch、MXNet等，这使得开发者能够在不同的框架之间轻松切换，选择最适合自己需求的框架。

使用ONNX，你可以将训练好的模型从一个支持ONNX的框架导出为ONNX格式，然后将其导入到另一个支持ONNX的框架中进行推理。这样的操作大大简化了模型在不同深度学习框架之间的移植和部署过程。

```cpp
class TextRecongize{
public:
    //文本区域仿射变化预处理:将所有方框变成水平
    void fourPointsTransform(const Mat& src, const Point2f vertices[], Mat& result);

    //检测结果
    vector<string> recongize_text(Mat src);

    TextRecongize(){};
    ~TextRecongize(){};

private:
    //DB文本检测模型参数
    float binThresh = 0.3;                                
    float polyThresh  = 0.5;                                   
    double unclipRatio = 2.0;                                   
    uint maxCandidates = 200;                                   
    int height = 736;                                           
    int width = 736;
    cv::String detModelPath = "/home/hrh/Downloads/DB_TD500_resnet50.onnx"; 
    double detScale = 1.0 / 255.0;

    //CRNN文本识别模型参数
    cv::String recModelPath = "/home/hrh/Downloads/crnn_cs_CN.onnx";        
    cv::String vocPath = "/home/hrh/Downloads/alphabet_3944.txt";             
    int imreadRGB = 1;         //0：以灰度图读取图像   1：以彩色图读取图像
    double recScale = 1.0 / 127.5;
};

// 这些参数是用于OCR（文本识别）模型的配置参数，它们在文本检测与识别的过程中起着重要的作用。下面对这些参数的意义进行简要说明：

// 1. `binThresh`：用于DB文本检测模型的二值化阈值。在文本检测中，需要将图像二值化，将文本区域与背景分离。`binThresh`控制了二值化的阈值，值越高，则更多的像素被认为是文本区域。

// 2. `polyThresh`：用于DB文本检测模型的多边形筛选阈值。文本检测模型通常会生成一系列的多边形，`polyThresh`控制了筛选多边形的阈值，用于过滤掉较小或不明显的文本区域。

// 3. `unclipRatio`：用于DB文本检测模型的裁剪比例。文本检测模型会生成包含文本区域的边框，`unclipRatio`控制了在裁剪时是否保留部分文本区域的边界。

// 4. `maxCandidates`：用于DB文本检测模型的候选框数量。在文本检测过程中，模型会生成多个候选框，`maxCandidates`控制了生成的候选框数量的上限。

// 5. `height`、`width`：DB文本检测模型的输入图像大小。在进行文本检测时，输入图像会被调整为指定的高度和宽度。

// 6. `detModelPath`：DB文本检测模型文件的路径。该参数指定了存储DB文本检测模型权重的文件路径。

// 7. `detScale`：DB文本检测模型的缩放比例。输入图像在传递给DB模型之前会被缩放，`detScale`用于控制缩放比例。

// 8. `recModelPath`：CRNN文本识别模型文件的路径。该参数指定了存储CRNN文本识别模型权重的文件路径。

// 9. `vocPath`：CRNN文本识别模型的词汇表文件路径。词汇表文件包含了CRNN模型识别的字符列表。

// 10. `imreadRGB`：图像读取方式，0表示以灰度图读取图像，1表示以彩色图读取图像。这个参数指定了图像读取的方式。

// 11. `recScale`：CRNN文本识别模型的缩放比例。输入图像在传递给CRNN模型之前会被缩放，`recScale`用于控制缩放比例。

// 这些参数的值会影响OCR模型的性能和结果，通常需要根据实际情况进行调整和优化。对于不同的OCR模型和应用场景，这些参数的最佳取值可能会不同。

```

## TTS模块
文本转语音，采用科大讯飞离线SDK

## RTP视频传输
[RTP](https://blog.csdn.net/Dreamandpassion/article/details/107525385)

`RTP`协议：`Real-time Transport Protocol`实时传输协议。`RFC3550`不仅定义了RTP，而且定义了配套的相关协议`RTCP`：`Real-time Transport Control Protocol`实时传输控制协议。`RTP`实现端到端的实时传输时间信息和流同步，但不保证服务质量，服务质量由`RTCP`来提供。

`RTP`包格式：由报头和有效载荷组成。

底层通信协议是`UDP`协议

`jrtplib`库：
-   无需用户担心`SSRC`冲突、调度和传输`RTCP`数据。用户只需要提供需要发送的有效负载数据，库会为用户提供访问权限输入`RTP`和`RTCP`数据。
-   `RTPSession`提供了发送`RTP`数据的功能，并在内部处理`RTCP`部分。
-   依赖于`jthread`,自动在后台执行对数据的接收。若无`jthread`,则用户自己调用`RTPSession`中的`Poll`方法。

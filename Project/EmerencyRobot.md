# EmerencyRobot

涉及技术栈：`TCP/IP`、`Qt`、`Opencv`、`TTS`、`RTP`

##  RTP和RTSP协议的区别？

RTP（Real-time Transport Protocol）和RTSP（Real-Time Streaming Protocol）都是用于实时多媒体传输的协议，但它们在用途和功能上有明显的区别。

以下是RTP和RTSP协议的主要区别：

1. **RTP（Real-time Transport Protocol）**：

   - **用途**：RTP是一种用于在网络上传输实时音频和视频数据的协议。它通常用于实时媒体流传输，如音频和视频会议、IP电话、流媒体和实时游戏等。
   
   - **特点**：RTP主要用于传输媒体数据本身，而不处理媒体控制或会话管理。它通常与RTCP（RTP Control Protocol）结合使用，后者用于报告媒体流的统计信息和质量反馈。

   - **功能**：RTP提供了实时数据传输所需的时间戳、序列号、媒体类型等信息，以确保接收端可以按照正确的顺序和时间播放媒体数据。它还支持不同编解码器和传输协议，以适应不同的应用需求。

2. **RTSP（Real-Time Streaming Protocol）**：

   - **用途**：RTSP是一种用于控制实时流媒体会话的协议。它通常用于控制媒体流的启动、暂停、停止、定位和选择不同的媒体轨道等操作。
   
   - **特点**：RTSP不传输媒体数据本身，而是用于控制媒体流的播放和管理。它允许客户端与流媒体服务器进行会话控制，并请求特定的媒体数据。

   - **功能**：RTSP允许客户端与流媒体服务器进行会话建立、控制和管理。客户端可以使用RTSP命令来请求媒体流的描述信息、选择不同的媒体轨道、跳转到不同的时间位置等。实际的媒体数据传输通常由其他协议（如RTP）来处理。

总结：

RTP和RTSP是在实时多媒体传输领域中发挥不同作用的两种协议。**RTP用于传输媒体数据本身，而RTSP用于控制和管理媒体流的播放。**通常，这两种协议会一起使用，以实现完整的实时多媒体传输和会话控制。例如，在流媒体服务中，RTSP用于控制媒体流的会话，而RTP用于传输媒体数据。
## 为什么采用TCP/IP通信协议？
因为移动小车厂家提供与底层通信的方式采用的是`TCP/IP`通信方式，数据格式采用`JSON`,为了方便使用与解决实际需要，故采用该种方式，同时QT中提供了`QTcpServer`类库，对`socket`的封装。

## qt中的信号与槽的底层原理？

Qt的信号与槽机制的底层实现基于元对象系统（Meta-Object System）。这个系统负责在运行时管理类的信息、信号、槽和其他元数据。以下是信号与槽机制的底层实现概述：

1. **元对象（Meta Object）：** 在Qt中，每个QObject派生的类都有一个对应的元对象。元对象是一个描述类的元数据的数据结构，其中包含了类的名称、父类信息、信号和槽信息等。

2. **MOC编译器（Meta-Object Compiler）：** 为了处理信号与槽机制，Qt引入了MOC编译器。MOC会解析源代码中使用`Q_OBJECT`、`Q_SIGNALS`和`Q_SLOTS`等宏标记的部分，并生成额外的C++代码。这些代码包含了元对象的信息，用于支持信号与槽的连接和调用。

3. **信号表（Signal Table）和槽表（Slot Table）：** 在元对象中，有两个重要的表格，即信号表和槽表。信号表记录了类中所有声明的信号，包括信号的名称、参数类型等信息。槽表则记录了类中声明的槽，以及槽的名称、参数类型等信息。

4. **连接的建立：** 当使用`QObject::connect`函数建立信号与槽的连接时，Qt会在发射信号的对象的元对象中查找信号的索引，然后在接收信号的对象的元对象中查找槽的索引。这样，Qt就可以在运行时知道如何在信号发射时调用正确的槽。

5. **信号的发射与槽的调用：** 当信号发射时，Qt通过元对象中的信号索引找到连接的槽的索引，并通过函数指针调用槽函数。这意味着，信号发射和槽的调用是在运行时动态完成的。

## qt程序编译生成的Moc文件？

参考[Qt moc_XXX.cpp文件的生成和探索](https://blog.csdn.net/nature_Chen_/article/details/120489391)和`gpt`回答。

Qt中的MOC（Meta Object Compiler）是用于处理元对象特性的工具。MOC文件包含了Qt元对象系统所需的信息，主要包括以下内容：

1. **元对象特性信息**：MOC文件会包含Qt元对象系统所需的信息，如类的元对象类别、父类的元对象类别等。这些信息用于运行时类型识别和信号槽连接。

2. **信号和槽信息**：对于使用Qt的信号槽机制的类，MOC文件会包含与信号和槽相关的信息，包括信号和槽的名称、参数类型、标识符等。这些信息用于在运行时建立信号槽连接。

3. **属性信息**：如果类中定义了Qt属性（通过`Q_PROPERTY`宏），MOC文件会包含这些属性的信息，如属性名称、类型、访问函数等。

4. **动态属性信息**：对于使用`Q_PROPERTY`宏声明的动态属性，MOC文件也会包含这些属性的信息。

5. **Q_OBJECT宏生成的代码**：如果一个类使用了`Q_OBJECT`宏，MOC会为该类生成一些额外的代码，包括元对象的构造和析构函数、元对象的方法和信号槽处理函数。

下面是一个简单的示例，演示了一个使用Qt的类以及生成的MOC文件的部分内容：

```cpp
// MyClass.h
#include <QObject>

class MyClass : public QObject
{
    Q_OBJECT // 使用Q_OBJECT宏

public:
    MyClass(QObject* parent = nullptr);

public slots:
    void mySlot();

signals:
    void mySignal();
};

// MyClass.cpp
#include "MyClass.h"

MyClass::MyClass(QObject* parent) : QObject(parent)
{
}

void MyClass::mySlot()
{
    emit mySignal();
}
```

当你编译这个类时，Qt的MOC工具会生成一个MOC文件，其中包含了与`MyClass`类相关的元对象信息、信号槽信息以及`Q_OBJECT`宏生成的代码。这个MOC文件的内容会被合并到编译后的对象文件中，以支持Qt的元对象系统和信号槽机制。这是Qt中的一种元编程技术，允许在运行时处理类的元信息，实现了一些强大的特性，如信号槽机制和反射。


生成的MOC文件通常具有与类的名称相对应的名称，并且具有`.moc`的扩展名。在上面的示例中，生成的MOC文件可能被命名为`MyClass.moc`。

以下是一个简化版本的`MyClass.moc`文件的示例，它展示了MOC文件的基本结构：

```cpp
// MyClass.moc

// Include necessary Qt headers
#include <QtCore/qobject.h>
#include <QtCore/qmetaobject.h>

// Define the meta-object for MyClass
static const uint qt_meta_data_MyClass[] = {
    // ...
    // Meta-object information for MyClass, including signal and slot offsets
    // ...
};

// Define the static meta-object structure
static const QMetaObjectExtraData qt_meta_data_MyClass_data = {
    // ...
    // Extra data for MyClass meta-object, if any
    // ...
};

const QMetaObject MyClass::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_data_MyClass, &qt_meta_data_MyClass_data }
};

// Define the slots and signals of MyClass
static void MyClass_MyClass_slot_0(QMetaObject::Call _c, QObject* _o)
{
    MyClass* _t = static_cast<MyClass*>(_o);
    // Call the slot function
    _t->mySlot();
}

const QMetaObject::Connection MyClass::staticMetaObject_connect[] = {
    { 0, 0, 0, 0, 0, reinterpret_cast<void*>(MyClass_MyClass_slot_0) }
};

// Define the signal handler for MyClass
void MyClass::qt_static_metacall(QObject* _o, QMetaObject::Call _c, int _id, void** _a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyClass* _t = static_cast<MyClass*>(_o);
        switch (_id) {
        case 0:
            _t->mySignal();
            break;
        // ...
        default:
            break;
        }
    }
}

// Include the implementation of mySlot if it has a body
void MyClass::mySlot()
{
    // Implementation of mySlot
}

// Include the implementation of constructor and destructor if needed
MyClass::MyClass(QObject* parent) : QObject(parent)
{
    // Constructor implementation
}

// ...
// Include the implementation of other member functions and properties
// ...

```

请注意，这只是一个简化的示例，真实的MOC文件可能会更复杂，特别是对于包含更多信号和槽以及属性的类。MOC文件的主要作用是为了支持Qt的元对象系统，它包含了元信息和用于信号槽连接的函数指针。这些信息允许Qt在运行时执行信号槽连接、元对象的操作以及其他与元对象系统相关的功能。在编译时，MOC文件的内容会与您的类一起编译，以构建具有Qt元对象特性的对象。


上面的示例展示了一个简化版本的MOC（Meta Object Compiler）文件的内容，以及它们的作用。现在让我们更详细地介绍每个部分的内容和作用：

1. **包含必要的Qt头文件**：
   ```cpp
   #include <QtCore/qobject.h>
   #include <QtCore/qmetaobject.h>
   ```
   这些包含语句用于引入Qt框架中必要的头文件，以便在MOC文件中使用Qt的元对象系统和其他功能。

2. **定义元对象信息数组**：
   ```cpp
   static const uint qt_meta_data_MyClass[] = {
       // ...
       // 元对象信息，包括信号和槽的偏移量等
       // ...
   };
   ```
   这个数组包含了关于`MyClass`类的元对象信息，其中包括信号和槽的偏移量等。这些信息用于在运行时进行信号槽连接和动态属性的访问。

3. **定义额外的元对象数据**：
   ```cpp
   static const QMetaObjectExtraData qt_meta_data_MyClass_data = {
       // ...
       // MyClass元对象的额外数据，如果有的话
       // ...
   };
   ```
   这个部分用于定义与`MyClass`类的元对象相关的额外数据。通常情况下，这部分可能为空，但对于某些特殊情况，你可以在这里添加额外的元对象信息。

4. **定义静态元对象**：
   ```cpp
   const QMetaObject MyClass::staticMetaObject = {
       { &QObject::staticMetaObject, qt_meta_data_MyClass, &qt_meta_data_MyClass_data }
   };
   ```
   这里定义了`MyClass`类的静态元对象。静态元对象包括了指向父类元对象、元对象信息数组和额外数据的指针。这些元对象信息是Qt运行时系统用来管理`MyClass`对象的类型信息和信号槽的关键。

5. **定义槽函数指针数组**：
   ```cpp
   static void MyClass_MyClass_slot_0(QMetaObject::Call _c, QObject* _o)
   {
       MyClass* _t = static_cast<MyClass*>(_o);
       // 调用槽函数
       _t->mySlot();
   }
   ```
   这个部分定义了一个槽函数指针数组，用于调用`MyClass`类中的槽函数。这些函数指针会在信号槽连接时用于实际的槽函数调用。

6. **定义信号处理函数**：
   ```cpp
   void MyClass::qt_static_metacall(QObject* _o, QMetaObject::Call _c, int _id, void** _a)
   {
       if (_c == QMetaObject::InvokeMetaMethod) {
           MyClass* _t = static_cast<MyClass*>(_o);
           switch (_id) {
           case 0:
               _t->mySignal();
               break;
           // ...
           default:
               break;
           }
       }
   }
   ```
   这个函数用于处理在运行时触发的信号。它会根据信号的标识符（在元对象信息数组中定义）来调用相应的信号处理函数。

7. **包含槽函数的实现**：
   ```cpp
   void MyClass::mySlot()
   {
       // mySlot的实现
   }
   ```
   如果槽函数有实现，它的代码会在这部分包含。

8. **包含构造函数和析构函数的实现**：
   ```cpp
   MyClass::MyClass(QObject* parent) : QObject(parent)
   {
       // 构造函数的实现
   }
   ```
   如果类有构造函数和析构函数，它们的代码也会包含在这里。

这个MOC文件的内容充分体现了Qt元对象系统的工作方式。它包含了关于类的元信息、信号槽的连接信息、元对象的构建和调用机制以及实际槽函数的实现。这些信息和代码使得Qt能够在运行时动态地处理对象的类型信息和信号槽连接，从而实现了一些强大的功能，如信号槽机制和反射。请注意，这个示例是简化的，实际的MOC文件可能更复杂，具体内容取决于类的特性和元信息。


## qt程序生成的ui文件或者问qtcpp如何调用生成xml界面文件？

`gpt`回答如下：

要在Qt中使用Qt Designer生成的UI文件，你需要进行以下步骤：

1. **创建Qt项目**：首先，创建一个Qt项目（Qt Widgets Application或其他类型的项目），以便将UI文件集成到项目中。

2. **打开Qt Designer**：打开Qt Designer，然后使用它创建或编辑你的UI界面。在Qt Creator中，你可以通过单击“Design”按钮或使用`designer`命令来打开Qt Designer。

3. **设计UI界面**：使用Qt Designer的图形界面工具来设计你的用户界面。你可以添加和配置各种小部件（widgets）、布局（layouts）、按钮、标签等等。

4. **保存UI文件**：在Qt Designer中，选择“文件”菜单，然后选择“保存”或“另存为”选项，以保存你的UI文件（通常以`.ui`为扩展名）。选择一个适当的文件名和目录来保存文件。

5. **生成C++代码**：要在你的Qt项目中使用UI文件，你需要将UI文件转换为C++代码。为此，可以使用`uic`工具，该工具是Qt的用户界面编译器，用于将UI文件编译为C++源文件。在Qt Creator中，通常会自动进行此步骤，但如果需要手动进行，可以使用以下命令：
   ```
   uic yourfile.ui -o ui_yourfile.h
   ```
   其中，`yourfile.ui`是你的UI文件的文件名，`ui_yourfile.h`是将生成的C++头文件的文件名。此命令会生成一个头文件，其中包含UI文件的定义以及相应的C++类。

6. **包含生成的头文件**：在你的Qt项目中包含生成的头文件，以便在代码中访问UI界面的小部件和属性。通常，在你的主窗口类或其他需要使用UI界面的地方包含该头文件。

7. **使用UI界面**：通过创建UI界面类的实例，你可以访问和操作UI界面上的小部件。通常，你需要创建一个UI界面类的成员变量，并在构造函数中初始化它，然后使用它来访问UI小部件。

下面是一个简单的示例，演示了如何在Qt项目中使用Qt Designer生成的UI文件：

```cpp
#include <QMainWindow>
#include "ui_mainwindow.h" // 包含生成的头文件

class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MyMainWindow(QWidget* parent = nullptr)
        : QMainWindow(parent)
    {
        // 创建UI界面实例
        ui = new Ui::MainWindow;
        ui->setupUi(this);

        // 设置信号槽连接
        connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(handleButtonClick()));
    }

private slots:
    void handleButtonClick() {
        // 处理按钮点击事件
        ui->label->setText("Button Clicked!");
    }

private:
    Ui::MainWindow* ui; // UI界面实例
};
```

在上面的示例中，我们包含了生成的UI头文件`ui_mainwindow.h`，然后在构造函数中创建了UI界面实例`ui`。接下来，我们设置了一个信号槽连接，以响应按钮点击事件，并在槽函数中更新标签的文本。这是一个简单的例子，说明了如何在Qt中使用Qt Designer生成的UI文件。

## qt信号与槽connect函数的第五个参数ConnectionType的意义？

[connect函数第五个参数](https://blog.csdn.net/ligare/article/details/122727045)


## qt中QTimer为什么启动和停止需要在同一个线程？

在Qt中，`QTimer`类用于定时触发事件，比如在一段时间后执行特定的操作。`QTimer`需要启动和停止在同一个线程的原因是与Qt的事件循环（Event Loop）机制相关。

Qt应用程序通常都有一个主事件循环，这个事件循环负责处理用户输入、定时器事件、网络通信等等。当你启动一个`QTimer`时，它会将一个定时器事件（Timer Event）添加到事件队列中，并在指定的时间间隔后触发该事件。然后，事件循环负责处理这个事件，即执行与该定时器关联的槽函数。

如果你尝试在一个线程中启动一个`QTimer`，然后在另一个线程中停止它，会导致潜在的问题，因为`QTimer`的定时器事件和槽函数的执行都与所在的线程相关。以下是一些原因：

1. **线程安全性问题：** Qt的许多类和函数都不是线程安全的，包括`QObject`及其派生类（如`QTimer`）。如果你在一个线程中启动了定时器，然后在另一个线程中停止它，可能会导致不确定的行为或潜在的崩溃。

2. **事件循环：** 定时器事件需要被添加到事件循环中，并由相同线程的事件循环处理。如果启动和停止定时器不在同一线程中，定时器事件可能无法被正确处理。

3. **对象生命周期：** Qt对象通常在它们所属的线程中创建和销毁。如果你在一个线程中创建了`QTimer`对象，然后在另一个线程中停止它，可能会引发对象生命周期问题。

为了避免这些问题，通常建议在同一个线程中启动和停止`QTimer`，确保定时器事件和槽函数的执行都在同一个线程中，从而保持线程安全性和一致性。如果需要在不同线程中操作定时器，可以使用线程间通信机制来安全地控制定时器的启动和停止。例如，可以使用信号和槽机制在不同线程之间发送信号来触发定时器的启动和停止操作。
## qt中多线程使用QTimer可能出现的问题？

[qt中多线程使用QTimer](https://blog.csdn.net/zjgo007/article/details/105403341)
## qt中的多线程编程

[qt中常见多线程编程方法](https://blog.csdn.net/weixin_44840658/article/details/108625659#:~:text=Qt%E7%9A%844%E7%A7%8D%E5%A4%9A%E7%BA%BF%E7%A8%8B%E5%AE%9E%E7%8E%B0%E6%96%B9%E5%BC%8F%201%20%E4%B8%80%E3%80%81QThread%E7%B1%BB%E7%9A%84run%20%E4%B8%80%E3%80%81%E5%AE%9E%E7%8E%B0%E6%96%B9%E6%B3%95%EF%BC%9A%20%E6%96%B0%E5%BB%BA%E4%B8%80%E4%B8%AA%E9%9B%86%E6%88%90QThread%E7%9A%84%E7%B1%BB%EF%BC%8C%E9%87%8D%E5%86%99%E8%99%9A%E5%87%BD%E6%95%B0run%2C%E9%80%9A%E8%BF%87run%E5%90%AF%E5%8A%A8%E7%BA%BF%E7%A8%8B%20%E4%BA%8C%E3%80%81%E7%A4%BA%E4%BE%8B%EF%BC%9A%20...%202,%E4%B8%89%E3%80%81QRunnalble%E7%9A%84run%20Qrunnable%E6%98%AF%E6%89%80%E6%9C%89%E5%8F%AF%E6%89%A7%E8%A1%8C%E5%AF%B9%E8%B1%A1%E7%9A%84%E5%9F%BA%E7%B1%BB%E3%80%82%20...%204%20%E5%9B%9B%E3%80%81QtConcurrent%E7%9A%84run%20Concurrent%E6%98%AF%E5%B9%B6%E5%8F%91%E7%9A%84%E6%84%8F%E6%80%9D%EF%BC%8CQtConcurrent%E6%98%AF%E4%B8%80%E4%B8%AA%E5%91%BD%E5%90%8D%E7%A9%BA%E9%97%B4%EF%BC%8C%E6%8F%90%E4%BE%9B%E4%BA%86%E4%B8%80%E4%BA%9B%E9%AB%98%E7%BA%A7%E7%9A%84%20API%EF%BC%8C%E4%BD%BF%E5%BE%97%E5%9C%A8%E7%BC%96%E5%86%99%E5%A4%9A%E7%BA%BF%E7%A8%8B%E7%9A%84%E6%97%B6%E5%80%99%EF%BC%8C%E6%97%A0%E9%9C%80%E4%BD%BF%E7%94%A8%E4%BD%8E%E7%BA%A7%E7%BA%BF%E7%A8%8B%E5%8E%9F%E8%AF%AD%EF%BC%8C%E5%A6%82%E8%AF%BB%E5%86%99%E9%94%81%EF%BC%8C%E7%AD%89%E5%BE%85%E6%9D%A1%E4%BB%B6%E6%88%96%E4%BF%A1%E5%8F%B7%E3%80%82%20)


## qt重写自定义控件？

在Qt中，您可以通过继承现有的控件类并重写其成员函数来自定义控件的行为和外观。通常，您会创建一个新的子类，然后重写需要自定义的方法和事件处理函数。下面是一个基本的步骤：

1. **创建一个子类**：首先，您需要创建一个继承自要重写的控件类的子类。例如，如果要自定义QPushButton，您可以创建一个新的类并让它继承自QPushButton。

```cpp
class MyButton : public QPushButton
{
    Q_OBJECT

public:
    MyButton(QWidget *parent = nullptr);
    // 在这里添加您的自定义方法和成员变量
};
```

2. **重写方法**：在子类中，您可以重写父类的方法来改变控件的行为。例如，如果要在按钮被单击时执行自定义操作，可以重写QPushButton的`mousePressEvent`方法。

```cpp
void MyButton::mousePressEvent(QMouseEvent *event)
{
    // 在这里添加自定义的鼠标按下事件处理代码
    // 调用父类的方法以确保保留原始功能
    QPushButton::mousePressEvent(event);
}
```

3. **自定义外观**：您还可以通过重写`paintEvent`方法来自定义控件的外观。在这个方法中，您可以使用Qt的绘图功能来绘制您想要的图形。

```cpp
void MyButton::paintEvent(QPaintEvent *event)
{
    // 在这里绘制自定义的按钮外观
    QPainter painter(this);
    painter.fillRect(rect(), QColor(255, 0, 0)); // 用红色填充按钮的背景
    painter.drawText(rect(), Qt::AlignCenter, "My Button"); // 在按钮上绘制文本
}
```

4. **使用自定义控件**：一旦您创建了自定义控件类，您可以像使用Qt内置控件一样在您的应用程序中使用它。例如：

```cpp
MyButton *myButton = new MyButton(this);
myButton->setText("Custom Button");
myButton->setGeometry(10, 10, 100, 30);
myButton->show();
```

通过以上步骤，您可以创建一个自定义控件并为其添加自定义行为和外观。请注意，不同的控件类可能会有不同的方法和事件，您可以根据您的需求选择性地重写它们。此外，Qt提供了丰富的文档和示例来帮助您进一步学习和了解如何自定义控件。
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

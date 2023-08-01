/**
*@file FactoryPattern.cpp
*@author your name (you@domain.com)
*@brief 工厂模式
*@version 0.1
*@date 2023-07-29
*
*@copyright Copyright (c) 2023
*
*/

/**
*@brief 简单工厂模式
*
*/
#include <iostream>
enum CarTypeTag {
    BM,
    AD,
    JK
};

class Car {
public:
    virtual void drive() = 0;
};

class BMCar : public Car {
public:
    void drive() override {
        std::cout << "bmCar is dirving" << std::endl;
    }
};

class ADCar : public Car {
public:
    void drive() override;
};

class JKCar : public Car {
public:
    void drive() override;
};

//工厂类
class SimpleFactory {
public:
    SimpleFactory() {}

    Car* createCar(CarTypeTag type) {
        switch (type)
        {
        case BM:
            return new BMCar();
            break;
        case AD:
            return new ADCar();
            break;
        case JK:
            return new JKCar();
            break;
        default:
            return nullptr;
            break;
        }
    }
};

/**
*@brief 工厂模式
*在简单工厂模式的基础上，对工厂类进行抽象，作为抽象基类
*/

class Factory {
public:
    virtual Car* createCar() = 0;
};

class BMFactory: public Factory {
public:
    Car* createCar() {
        return new BMCar();
    }
};

class ADFactory: public Factory {
public:
    Car* createCar() {
        return new ADCar();
    }
};

class JKFactory: public Factory {
public:
    Car* createCar() {
        return new JKCar();
    }
};





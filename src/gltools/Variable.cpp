//
// Created by thomas on 06/11/18.
//

#include "Variable.h"

#include <cmath>

class AdditionVariable : public GLTools::AbstractVariable {
public:
    AdditionVariable(AbstractVariable &a, AbstractVariable &b) : mA(a), mB(b) {

    }

    void next() override {
        mA.next();
        mB.next();
    }

    float get() const override {
        return mA.get() + mB.get();
    }

private:
    AbstractVariable &mA, &mB;

};

class SubstractionVariable : public GLTools::AbstractVariable {
public:
    SubstractionVariable(AbstractVariable &a, AbstractVariable &b) : mA(a), mB(b) {

    }

    void next() override {
        mA.next();
        mB.next();
    }

    float get() const override {
        return mA.get() - mB.get();
    }

private:
    AbstractVariable & mA, &mB;

};

class MultiplicationVariable : public GLTools::AbstractVariable {
public:
    MultiplicationVariable(AbstractVariable &a, AbstractVariable &b) : mA(a), mB(b) {

    }

    void next() override {
        mA.next();
        mB.next();
    }

    float get() const override {
        return mA.get() * mB.get();
    }

private:
    AbstractVariable & mA, &mB;

};

class DivisionVariable : public GLTools::AbstractVariable {
public:
    DivisionVariable(AbstractVariable &a, AbstractVariable &b) : mA(a), mB(b) {

    }

    void next() override {
        mA.next();
        mB.next();
    }

    float get() const override {
        return mA.get() / mB.get();
    }

private:
    AbstractVariable & mA, &mB;

};

class CosavVariable : public GLTools::AbstractVariable {
public:
    explicit CosavVariable(AbstractVariable &a) : mA(a) {

    }

    void next() override {
        mA.next();
    }

    float get() const override {
        return cosf(mA.get());
    }

private:
    AbstractVariable & mA;

};

class SinavVariable : public GLTools::AbstractVariable {
public:
    explicit SinavVariable(AbstractVariable &a) : mA(a) {

    }

    void next() override {
        mA.next();
    }

    float get() const override {
        return sinf(mA.get());
    }

private:
    AbstractVariable & mA;

};

GLTools::AbstractVariable& operator +(GLTools::AbstractVariable &a, GLTools::AbstractVariable &b) {
    return *new AdditionVariable(a, b);
}

GLTools::AbstractVariable& operator -(GLTools::AbstractVariable &a, GLTools::AbstractVariable &b) {
    return *new SubstractionVariable(a, b);
}

GLTools::AbstractVariable& operator *(GLTools::AbstractVariable &a, GLTools::AbstractVariable &b) {
    return *new MultiplicationVariable(a, b);
}

GLTools::AbstractVariable& operator /(GLTools::AbstractVariable &a, GLTools::AbstractVariable &b) {
    return *new MultiplicationVariable(a, b);
}

GLTools::AbstractVariable& operator +(GLTools::AbstractVariable &a, float b) {
    return *new AdditionVariable(a, *new GLTools::ConstantVariable(b));
}

GLTools::AbstractVariable& operator -(GLTools::AbstractVariable &a, float b) {
    return *new SubstractionVariable(a, *new GLTools::ConstantVariable(b));
}

GLTools::AbstractVariable& operator *(GLTools::AbstractVariable &a, float b) {
    return *new MultiplicationVariable(a, *new GLTools::ConstantVariable(b));
}

GLTools::AbstractVariable& operator /(GLTools::AbstractVariable &a, float b) {
    return *new DivisionVariable(a, *new GLTools::ConstantVariable(b));
}

GLTools::AbstractVariable& cosav(GLTools::AbstractVariable &a) {
    return *new CosavVariable(a);
}

GLTools::AbstractVariable& sinav(GLTools::AbstractVariable &a) {
    return *new SinavVariable(a);
}

GLTools::ConstantVariable::ConstantVariable(float constant) {
    mConstant = constant;
}

void GLTools::ConstantVariable::next() {

}

float GLTools::ConstantVariable::get() const {
    return mConstant;
}
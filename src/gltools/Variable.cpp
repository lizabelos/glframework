//
// Created by thomas on 06/11/18.
//

#include "Variable.h"

#include <cmath>

class AdditionVariable : public GLTools::AbstractVariable {
public:
    AdditionVariable(GLTools::Variable a, GLTools::Variable b) : mA(a), mB(b) {

    }

    void next() override {
        mA->next();
        mB->next();
    }

    float get() const override {
        return mA->get() + mB->get();
    }

private:
    GLTools::Variable mA, mB;

};

class SubstractionVariable : public GLTools::AbstractVariable {
public:
    SubstractionVariable(GLTools::Variable a, GLTools::Variable b) : mA(a), mB(b) {

    }

    void next() override {
        mA->next();
        mB->next();
    }

    float get() const override {
        return mA->get() - mB->get();
    }

private:
    GLTools::Variable  mA, mB;

};

class MultiplicationVariable : public GLTools::AbstractVariable {
public:
    MultiplicationVariable(GLTools::Variable a, GLTools::Variable b) : mA(a), mB(b) {

    }

    void next() override {
        mA->next();
        mB->next();
    }

    float get() const override {
        return mA->get() * mB->get();
    }

private:
    GLTools::Variable  mA, mB;

};

class DivisionVariable : public GLTools::AbstractVariable {
public:
    DivisionVariable(GLTools::Variable a, GLTools::Variable b) : mA(a), mB(b) {

    }

    void next() override {
        mA->next();
        mB->next();
    }

    float get() const override {
        return mA->get() / mB->get();
    }

private:
    GLTools::Variable  mA, mB;

};

class CosavVariable : public GLTools::AbstractVariable {
public:
    explicit CosavVariable(GLTools::Variable a) : mA(a) {

    }

    void next() override {
        mA->next();
    }

    float get() const override {
        return cosf(mA->get());
    }

private:
    GLTools::Variable  mA;

};

class SinavVariable : public GLTools::AbstractVariable {
public:
    explicit SinavVariable(GLTools::Variable a) : mA(a) {

    }

    void next() override {
        mA->next();
    }

    float get() const override {
        return sinf(mA->get());
    }

private:
    GLTools::Variable  mA;

};

class AtanVariable : public GLTools::AbstractVariable {
public:
    AtanVariable(GLTools::Variable a, GLTools::Variable b) : mA(a), mB(b) {

    }

    void next() override {
        mA->next();
        mB->next();
    }

    float get() const override {
        return mA->get() / mB->get();
    }

private:
    GLTools::Variable  mA, mB;

};

std::shared_ptr<GLTools::AbstractVariable> operator +(GLTools::Variable a, GLTools::Variable b) {
    return std::shared_ptr<GLTools::AbstractVariable>(new AdditionVariable(a, b));
}

std::shared_ptr<GLTools::AbstractVariable> operator -(GLTools::Variable a, GLTools::Variable b) {
    return std::shared_ptr<GLTools::AbstractVariable>(new SubstractionVariable(a, b));
}

std::shared_ptr<GLTools::AbstractVariable> operator *(GLTools::Variable a, GLTools::Variable b) {
    return std::shared_ptr<GLTools::AbstractVariable>(new MultiplicationVariable(a, b));
}

std::shared_ptr<GLTools::AbstractVariable> operator /(GLTools::Variable a, GLTools::Variable b) {
    return std::shared_ptr<GLTools::AbstractVariable>(new MultiplicationVariable(a, b));
}

std::shared_ptr<GLTools::AbstractVariable> operator +(GLTools::Variable a, float b) {
    return std::shared_ptr<GLTools::AbstractVariable>(new AdditionVariable(a, GLTools::Variable(new GLTools::ConstantVariable(b))));
}

std::shared_ptr<GLTools::AbstractVariable> operator -(GLTools::Variable a, float b) {
    return std::shared_ptr<GLTools::AbstractVariable>(new SubstractionVariable(a, GLTools::Variable(new GLTools::ConstantVariable(b))));
}

std::shared_ptr<GLTools::AbstractVariable> operator *(GLTools::Variable a, float b) {
    return std::shared_ptr<GLTools::AbstractVariable>(new MultiplicationVariable(a, GLTools::Variable(new GLTools::ConstantVariable(b))));
}

std::shared_ptr<GLTools::AbstractVariable> operator /(GLTools::Variable a, float b) {
    return std::shared_ptr<GLTools::AbstractVariable>(new DivisionVariable(a, GLTools::Variable(new GLTools::ConstantVariable(b))));
}

std::shared_ptr<GLTools::AbstractVariable> GLTools::cosav(GLTools::Variable a) {
    return std::shared_ptr<GLTools::AbstractVariable>(new CosavVariable(a));
}

std::shared_ptr<GLTools::AbstractVariable> GLTools::sinav(GLTools::Variable a) {
    return std::shared_ptr<GLTools::AbstractVariable>(new SinavVariable(a));
}

std::shared_ptr<GLTools::AbstractVariable> GLTools::atanav(GLTools::Variable a, GLTools::Variable b) {
    return std::shared_ptr<GLTools::AbstractVariable>(new AtanVariable(a, b));
}

GLTools::ConstantVariable::ConstantVariable(float constant) {
    mConstant = constant;
}

void GLTools::ConstantVariable::next() {

}

float GLTools::ConstantVariable::get() const {
    return mConstant;
}

void GLTools::SettableVariable::next() {

}

float GLTools::SettableVariable::get() const {
    return mValue;
}

void GLTools::SettableVariable::set(float value) {
    mValue = value;
}

GLTools::SVariable GLTools::make_SVariable() {
    return std::make_shared<GLTools::SettableVariable>();
}
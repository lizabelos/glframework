//
// Created by thomas on 06/11/18.
//

#include "Variable.h"

#include <cmath>

class AdditionVariable : public GLGeometry::AbstractVariable {
public:
    AdditionVariable(GLGeometry::Variable a, GLGeometry::Variable b) : mA(a), mB(b) {

    }

    void next() override {
        mA->next();
        mB->next();
    }

    float get() const override {
        return mA->get() + mB->get();
    }

private:
    GLGeometry::Variable mA, mB;

};

class SubstractionVariable : public GLGeometry::AbstractVariable {
public:
    SubstractionVariable(GLGeometry::Variable a, GLGeometry::Variable b) : mA(a), mB(b) {

    }

    void next() override {
        mA->next();
        mB->next();
    }

    float get() const override {
        return mA->get() - mB->get();
    }

private:
    GLGeometry::Variable  mA, mB;

};

class MultiplicationVariable : public GLGeometry::AbstractVariable {
public:
    MultiplicationVariable(GLGeometry::Variable a, GLGeometry::Variable b) : mA(a), mB(b) {

    }

    void next() override {
        mA->next();
        mB->next();
    }

    float get() const override {
        return mA->get() * mB->get();
    }

private:
    GLGeometry::Variable  mA, mB;

};

class DivisionVariable : public GLGeometry::AbstractVariable {
public:
    DivisionVariable(GLGeometry::Variable a, GLGeometry::Variable b) : mA(a), mB(b) {

    }

    void next() override {
        mA->next();
        mB->next();
    }

    float get() const override {
        return mA->get() / mB->get();
    }

private:
    GLGeometry::Variable  mA, mB;

};

class CosavVariable : public GLGeometry::AbstractVariable {
public:
    explicit CosavVariable(GLGeometry::Variable a) : mA(a) {

    }

    void next() override {
        mA->next();
    }

    float get() const override {
        return cosf(mA->get());
    }

private:
    GLGeometry::Variable  mA;

};

class SinavVariable : public GLGeometry::AbstractVariable {
public:
    explicit SinavVariable(GLGeometry::Variable a) : mA(a) {

    }

    void next() override {
        mA->next();
    }

    float get() const override {
        return sinf(mA->get());
    }

private:
    GLGeometry::Variable  mA;

};

class AtanVariable : public GLGeometry::AbstractVariable {
public:
    AtanVariable(GLGeometry::Variable a, GLGeometry::Variable b) : mA(a), mB(b) {

    }

    void next() override {
        mA->next();
        mB->next();
    }

    float get() const override {
        return mA->get() / mB->get();
    }

private:
    GLGeometry::Variable  mA, mB;

};

std::shared_ptr<GLGeometry::AbstractVariable> operator +(GLGeometry::Variable a, GLGeometry::Variable b) {
    return std::shared_ptr<GLGeometry::AbstractVariable>(new AdditionVariable(a, b));
}

std::shared_ptr<GLGeometry::AbstractVariable> operator -(GLGeometry::Variable a, GLGeometry::Variable b) {
    return std::shared_ptr<GLGeometry::AbstractVariable>(new SubstractionVariable(a, b));
}

std::shared_ptr<GLGeometry::AbstractVariable> operator *(GLGeometry::Variable a, GLGeometry::Variable b) {
    return std::shared_ptr<GLGeometry::AbstractVariable>(new MultiplicationVariable(a, b));
}

std::shared_ptr<GLGeometry::AbstractVariable> operator /(GLGeometry::Variable a, GLGeometry::Variable b) {
    return std::shared_ptr<GLGeometry::AbstractVariable>(new MultiplicationVariable(a, b));
}

std::shared_ptr<GLGeometry::AbstractVariable> operator +(GLGeometry::Variable a, float b) {
    return std::shared_ptr<GLGeometry::AbstractVariable>(new AdditionVariable(a, GLGeometry::Variable(new GLGeometry::ConstantVariable(b))));
}

std::shared_ptr<GLGeometry::AbstractVariable> operator -(GLGeometry::Variable a, float b) {
    return std::shared_ptr<GLGeometry::AbstractVariable>(new SubstractionVariable(a, GLGeometry::Variable(new GLGeometry::ConstantVariable(b))));
}

std::shared_ptr<GLGeometry::AbstractVariable> operator *(GLGeometry::Variable a, float b) {
    return std::shared_ptr<GLGeometry::AbstractVariable>(new MultiplicationVariable(a, GLGeometry::Variable(new GLGeometry::ConstantVariable(b))));
}

std::shared_ptr<GLGeometry::AbstractVariable> operator /(GLGeometry::Variable a, float b) {
    return std::shared_ptr<GLGeometry::AbstractVariable>(new DivisionVariable(a, GLGeometry::Variable(new GLGeometry::ConstantVariable(b))));
}

std::shared_ptr<GLGeometry::AbstractVariable> GLGeometry::cosav(GLGeometry::Variable a) {
    return std::shared_ptr<GLGeometry::AbstractVariable>(new CosavVariable(a));
}

std::shared_ptr<GLGeometry::AbstractVariable> GLGeometry::sinav(GLGeometry::Variable a) {
    return std::shared_ptr<GLGeometry::AbstractVariable>(new SinavVariable(a));
}

std::shared_ptr<GLGeometry::AbstractVariable> GLGeometry::atanav(GLGeometry::Variable a, GLGeometry::Variable b) {
    return std::shared_ptr<GLGeometry::AbstractVariable>(new AtanVariable(a, b));
}

GLGeometry::ConstantVariable::ConstantVariable(float constant) {
    mConstant = constant;
}

void GLGeometry::ConstantVariable::next() {

}

float GLGeometry::ConstantVariable::get() const {
    return mConstant;
}

void GLGeometry::SettableVariable::next() {

}

float GLGeometry::SettableVariable::get() const {
    return mValue;
}

void GLGeometry::SettableVariable::set(float value) {
    mValue = value;
}

GLGeometry::SVariable GLGeometry::make_SVariable() {
    return std::make_shared<GLGeometry::SettableVariable>();
}

GLGeometry::CVariable GLGeometry::make_CVariable(float value) {
    return std::make_shared<GLGeometry::ConstantVariable>(value);
}
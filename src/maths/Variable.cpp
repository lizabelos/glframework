//
// Created by thomas on 06/11/18.
//

#include "Variable.h"

#include <cmath>

class AdditionVariable : public Maths::AbstractVariable {
public:
    AdditionVariable(Maths::Variable a, Maths::Variable b) : mA(a), mB(b) {

    }

    void next() override {
        mA->next();
        mB->next();
    }

    float get() const override {
        return mA->get() + mB->get();
    }

private:
    Maths::Variable mA, mB;

};

class SubstractionVariable : public Maths::AbstractVariable {
public:
    SubstractionVariable(Maths::Variable a, Maths::Variable b) : mA(a), mB(b) {

    }

    void next() override {
        mA->next();
        mB->next();
    }

    float get() const override {
        return mA->get() - mB->get();
    }

private:
    Maths::Variable  mA, mB;

};

class MultiplicationVariable : public Maths::AbstractVariable {
public:
    MultiplicationVariable(Maths::Variable a, Maths::Variable b) : mA(a), mB(b) {

    }

    void next() override {
        mA->next();
        mB->next();
    }

    float get() const override {
        return mA->get() * mB->get();
    }

private:
    Maths::Variable  mA, mB;

};

class DivisionVariable : public Maths::AbstractVariable {
public:
    DivisionVariable(Maths::Variable a, Maths::Variable b) : mA(a), mB(b) {

    }

    void next() override {
        mA->next();
        mB->next();
    }

    float get() const override {
        return mA->get() / mB->get();
    }

private:
    Maths::Variable  mA, mB;

};

class CosavVariable : public Maths::AbstractVariable {
public:
    explicit CosavVariable(Maths::Variable a) : mA(a) {

    }

    void next() override {
        mA->next();
    }

    float get() const override {
        return cosf(mA->get());
    }

private:
    Maths::Variable  mA;

};

class SinavVariable : public Maths::AbstractVariable {
public:
    explicit SinavVariable(Maths::Variable a) : mA(a) {

    }

    void next() override {
        mA->next();
    }

    float get() const override {
        return sinf(mA->get());
    }

private:
    Maths::Variable  mA;

};

class AtanVariable : public Maths::AbstractVariable {
public:
    AtanVariable(Maths::Variable a, Maths::Variable b) : mA(a), mB(b) {

    }

    void next() override {
        mA->next();
        mB->next();
    }

    float get() const override {
        return mA->get() / mB->get();
    }

private:
    Maths::Variable  mA, mB;

};

std::shared_ptr<Maths::AbstractVariable> operator +(Maths::Variable a, Maths::Variable b) {
    return std::shared_ptr<Maths::AbstractVariable>(new AdditionVariable(a, b));
}

std::shared_ptr<Maths::AbstractVariable> operator -(Maths::Variable a, Maths::Variable b) {
    return std::shared_ptr<Maths::AbstractVariable>(new SubstractionVariable(a, b));
}

std::shared_ptr<Maths::AbstractVariable> operator *(Maths::Variable a, Maths::Variable b) {
    return std::shared_ptr<Maths::AbstractVariable>(new MultiplicationVariable(a, b));
}

std::shared_ptr<Maths::AbstractVariable> operator /(Maths::Variable a, Maths::Variable b) {
    return std::shared_ptr<Maths::AbstractVariable>(new MultiplicationVariable(a, b));
}

std::shared_ptr<Maths::AbstractVariable> operator +(Maths::Variable a, float b) {
    return std::shared_ptr<Maths::AbstractVariable>(new AdditionVariable(a, Maths::Variable(new Maths::ConstantVariable(b))));
}

std::shared_ptr<Maths::AbstractVariable> operator -(Maths::Variable a, float b) {
    return std::shared_ptr<Maths::AbstractVariable>(new SubstractionVariable(a, Maths::Variable(new Maths::ConstantVariable(b))));
}

std::shared_ptr<Maths::AbstractVariable> operator *(Maths::Variable a, float b) {
    return std::shared_ptr<Maths::AbstractVariable>(new MultiplicationVariable(a, Maths::Variable(new Maths::ConstantVariable(b))));
}

std::shared_ptr<Maths::AbstractVariable> operator /(Maths::Variable a, float b) {
    return std::shared_ptr<Maths::AbstractVariable>(new DivisionVariable(a, Maths::Variable(new Maths::ConstantVariable(b))));
}

std::shared_ptr<Maths::AbstractVariable> Maths::cosav(Maths::Variable a) {
    return std::shared_ptr<Maths::AbstractVariable>(new CosavVariable(a));
}

std::shared_ptr<Maths::AbstractVariable> Maths::sinav(Maths::Variable a) {
    return std::shared_ptr<Maths::AbstractVariable>(new SinavVariable(a));
}

std::shared_ptr<Maths::AbstractVariable> Maths::atanav(Maths::Variable a, Maths::Variable b) {
    return std::shared_ptr<Maths::AbstractVariable>(new AtanVariable(a, b));
}

Maths::ConstantVariable::ConstantVariable(float constant) {
    mConstant = constant;
}

void Maths::ConstantVariable::next() {

}

float Maths::ConstantVariable::get() const {
    return mConstant;
}

void Maths::SettableVariable::next() {

}

float Maths::SettableVariable::get() const {
    return mValue;
}

void Maths::SettableVariable::set(float value) {
    mValue = value;
}

Maths::SVariable Maths::make_SVariable() {
    return std::make_shared<Maths::SettableVariable>();
}

Maths::CVariable Maths::make_CVariable(float value) {
    return std::make_shared<Maths::ConstantVariable>(value);
}
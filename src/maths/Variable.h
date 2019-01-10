// Copyright (C) BELOS Thomas. All Rights Reserved.

#ifndef SOLAR_SYSTEM_VARIABLE_H
#define SOLAR_SYSTEM_VARIABLE_H

#include <memory>

namespace Maths {

    class AbstractVariable {

    public:
        virtual void next() = 0;
        virtual float get() const = 0;

    };

    class ConstantVariable : public AbstractVariable {

    public:
        explicit ConstantVariable(float constant);

        void next() override;
        float get() const override;

    private:
        float mConstant;

    };

    class SettableVariable : public AbstractVariable {

    public:
        void next() override;
        float get() const override;
        void set(float value);

    private:
        float mValue = 0;

    };

    using Variable = std::shared_ptr<Maths::AbstractVariable>;
    using SVariable = std::shared_ptr<Maths::SettableVariable>;
    using CVariable = std::shared_ptr<Maths::ConstantVariable>;

    SVariable make_SVariable();
    CVariable make_CVariable(float value);

    std::shared_ptr<Maths::AbstractVariable> cosav(Maths::Variable a);
    std::shared_ptr<Maths::AbstractVariable> sinav(Maths::Variable a);
    std::shared_ptr<Maths::AbstractVariable> atanav(Maths::Variable a, Maths::Variable b);
    std::shared_ptr<Maths::AbstractVariable> logav(Maths::Variable a);

    void rotate(Variable &x, Variable &y, Variable &z, float angle, float ax, float ay, float az);

}

Maths::Variable operator +(Maths::Variable a, Maths::Variable b);
Maths::Variable operator -(Maths::Variable a, Maths::Variable b);
Maths::Variable operator *(Maths::Variable a, Maths::Variable b);
Maths::Variable operator /(Maths::Variable a, Maths::Variable b);

Maths::Variable operator +(Maths::Variable a, float b);
Maths::Variable operator -(Maths::Variable a, float b);
Maths::Variable operator *(Maths::Variable a, float b);
Maths::Variable operator /(Maths::Variable a, float b);


#endif //SOLAR_SYSTEM_VARIABLE_H

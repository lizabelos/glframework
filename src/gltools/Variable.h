//
// Created by thomas on 06/11/18.
//

#ifndef SOLAR_SYSTEM_VARIABLE_H
#define SOLAR_SYSTEM_VARIABLE_H


namespace GLTools {

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

    AbstractVariable& operator +(AbstractVariable &a, AbstractVariable &b);
    AbstractVariable& operator -(AbstractVariable &a, AbstractVariable &b);
    AbstractVariable& operator *(AbstractVariable &a, AbstractVariable &b);
    AbstractVariable& operator /(AbstractVariable &a, AbstractVariable &b);

    AbstractVariable& operator +(AbstractVariable &a, float b);
    AbstractVariable& operator -(AbstractVariable &a, float b);
    AbstractVariable& operator *(AbstractVariable &a, float b);
    AbstractVariable& operator /(AbstractVariable &a, float b);

    AbstractVariable& cosav(AbstractVariable &a);
    AbstractVariable& sinav(AbstractVariable &a);

}


#endif //SOLAR_SYSTEM_VARIABLE_H

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

    class SettableVariable : public AbstractVariable {

    public:
        void next() override;
        float get() const override;
        void set(float value);

    private:
        float mValue = 0;

    };

    AbstractVariable& cosav(AbstractVariable &a);
    AbstractVariable& sinav(AbstractVariable &a);

}

GLTools::AbstractVariable& operator +(GLTools::AbstractVariable &a, GLTools::AbstractVariable &b);
GLTools::AbstractVariable& operator -(GLTools::AbstractVariable &a, GLTools::AbstractVariable &b);
GLTools::AbstractVariable& operator *(GLTools::AbstractVariable &a, GLTools::AbstractVariable &b);
GLTools::AbstractVariable& operator /(GLTools::AbstractVariable &a, GLTools::AbstractVariable &b);

GLTools::AbstractVariable& operator +(GLTools::AbstractVariable &a, float b);
GLTools::AbstractVariable& operator -(GLTools::AbstractVariable &a, float b);
GLTools::AbstractVariable& operator *(GLTools::AbstractVariable &a, float b);
GLTools::AbstractVariable& operator /(GLTools::AbstractVariable &a, float b);


#endif //SOLAR_SYSTEM_VARIABLE_H

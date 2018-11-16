//
// Created by thomas on 06/11/18.
//

#ifndef SOLAR_SYSTEM_VARIABLE_H
#define SOLAR_SYSTEM_VARIABLE_H

#include <memory>

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

    using Variable = std::shared_ptr<GLTools::AbstractVariable>;

    std::shared_ptr<GLTools::AbstractVariable> cosav(GLTools::Variable a);
    std::shared_ptr<GLTools::AbstractVariable> sinav(GLTools::Variable a);
    std::shared_ptr<GLTools::AbstractVariable> atanav(GLTools::Variable a, GLTools::Variable b);

}

GLTools::Variable operator +(GLTools::Variable a, GLTools::Variable b);
GLTools::Variable operator -(GLTools::Variable a, GLTools::Variable b);
GLTools::Variable operator *(GLTools::Variable a, GLTools::Variable b);
GLTools::Variable operator /(GLTools::Variable a, GLTools::Variable b);

GLTools::Variable operator +(GLTools::Variable a, float b);
GLTools::Variable operator -(GLTools::Variable a, float b);
GLTools::Variable operator *(GLTools::Variable a, float b);
GLTools::Variable operator /(GLTools::Variable a, float b);


#endif //SOLAR_SYSTEM_VARIABLE_H

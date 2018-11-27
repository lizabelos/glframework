//
// Created by thomas on 06/11/18.
//

#ifndef SOLAR_SYSTEM_VARIABLE_H
#define SOLAR_SYSTEM_VARIABLE_H

#include <memory>

namespace GLGeometry {

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

    using Variable = std::shared_ptr<GLGeometry::AbstractVariable>;
    using SVariable = std::shared_ptr<GLGeometry::SettableVariable>;
    using CVariable = std::shared_ptr<GLGeometry::ConstantVariable>;

    SVariable make_SVariable();
    CVariable make_CVariable(float value);

    std::shared_ptr<GLGeometry::AbstractVariable> cosav(GLGeometry::Variable a);
    std::shared_ptr<GLGeometry::AbstractVariable> sinav(GLGeometry::Variable a);
    std::shared_ptr<GLGeometry::AbstractVariable> atanav(GLGeometry::Variable a, GLGeometry::Variable b);

}

GLGeometry::Variable operator +(GLGeometry::Variable a, GLGeometry::Variable b);
GLGeometry::Variable operator -(GLGeometry::Variable a, GLGeometry::Variable b);
GLGeometry::Variable operator *(GLGeometry::Variable a, GLGeometry::Variable b);
GLGeometry::Variable operator /(GLGeometry::Variable a, GLGeometry::Variable b);

GLGeometry::Variable operator +(GLGeometry::Variable a, float b);
GLGeometry::Variable operator -(GLGeometry::Variable a, float b);
GLGeometry::Variable operator *(GLGeometry::Variable a, float b);
GLGeometry::Variable operator /(GLGeometry::Variable a, float b);


#endif //SOLAR_SYSTEM_VARIABLE_H

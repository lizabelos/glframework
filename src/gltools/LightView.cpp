//
// Created by belos on 26/02/2019.
//

#include "LightView.h"

LightView::LightView() {
    static const auto computeDirectionVectorUp = [](float phiRadians, float thetaRadians)
    {
        const auto cosPhi = glm::cos(phiRadians);
        const auto sinPhi = glm::sin(phiRadians);
        const auto cosTheta = glm::cos(thetaRadians);
        return -glm::normalize(glm::vec3(sinPhi * cosTheta, -glm::sin(thetaRadians), cosPhi * cosTheta));
    };

    const auto sceneCenter = 0.5f * (m_BBoxMin + m_BBoxMax);
    const float sceneRadius = m_SceneSizeLength * 0.5f;

    const auto dirLightUpVector = computeDirectionVectorUp(glm::radians(m_DirLightPhiAngleDegrees), glm::radians(m_DirLightThetaAngleDegrees));
    lightMatrix = glm::lookAt(sceneCenter + m_DirLightDirection * sceneRadius, sceneCenter, dirLightUpVector); // Will not work if m_DirLightDirection is colinear to lightUpVector

}

glm::mat4 LightView::getMatrix() {
    return lightMatrix;
}
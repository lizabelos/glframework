#include "TrackballCamera.h"


GLTools::TrackballCamera::TrackballCamera() : GLTools::Camera3D(), mFront(50.0f), mLeft(0.0f), mUp(0.0f) {

}

GLTools::TrackballCamera::TrackballCamera(float front, float left, float up) : GLTools::Camera3D(), mFront(front), mLeft(left), mUp(up) {

}

glm::mat4 GLTools::TrackballCamera::getViewMatrix() const {
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::vec3 xRotation =  glm::vec3(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) * glm::rotate(glm::mat4(1.0f), (float)(mLeft * 3.14), glm::vec3(0.0f, 1.0f, 0.0f)));
    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -mFront));
    viewMatrix = glm::rotate(viewMatrix, mLeft * 3.14f * 2.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    viewMatrix = glm::rotate(viewMatrix, mUp * 3.14f * 2.0f, xRotation);
    return viewMatrix;
}

glm::mat4 GLTools::TrackballCamera::getMVMatrix() const {
    return getViewMatrix() * Camera3D::getMVMatrix();
}

glm::mat4 GLTools::TrackballCamera::getNormalMatrix() const {
    return glm::transpose(glm::inverse(getMVMatrix()));
}


void GLTools::TrackballCamera::moveFront(float delta) {
	mFront *= delta;
}

void GLTools::TrackballCamera::rotateLeft(float delta) {
	mLeft += delta;
}

void GLTools::TrackballCamera::rotateUp(float delta) {
	mUp += delta;
}
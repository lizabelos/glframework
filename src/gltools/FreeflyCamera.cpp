#include "FreeflyCamera.h"

#define _USE_MATH_DEFINES
#include <cmath>

GLTools::FreeflyCamera::FreeflyCamera() : GLTools::Camera3D(), mTheta(0.0f), mPhi(0.0f) {

}

glm::mat4 GLTools::FreeflyCamera::getViewMatrix() const {
	return glm::lookAt(mPosition, mPosition + mFront, mUp);
}

glm::mat4 GLTools::FreeflyCamera::getMVMatrix() const {
	return getViewMatrix() * Camera3D::getMVMatrix();
}

glm::mat4 GLTools::FreeflyCamera::getNormalMatrix() const {
	return glm::transpose(glm::inverse(getMVMatrix()));
}

void GLTools::FreeflyCamera::moveLeft(float t) {
	mPosition = mPosition + mLeft * t;
}

void GLTools::FreeflyCamera::moveFront(float t) {
	mPosition = mPosition + mFront * t;
}

void GLTools::FreeflyCamera::rotateLeft(float t) {
	mPhi = mPhi + t;
	computeDirectionVectors();
}

void GLTools::FreeflyCamera::rotateUp(float t) {
	mTheta = mTheta + t;
	computeDirectionVectors();
}

void GLTools::FreeflyCamera::setLeftRotation(float t) {
	mPhi = t;
	computeDirectionVectors();
}

void GLTools::FreeflyCamera::setUpRotation(float t) {
	mTheta = t;
	computeDirectionVectors();
}

void GLTools::FreeflyCamera::computeDirectionVectors() {
	mFront = glm::vec3(
		cosf(mTheta) * sinf(mPhi),
		sinf(mTheta),
		cosf(mTheta) * sinf(mPhi)
	);

	mLeft = glm::vec3(
		sinf(mPhi + M_PI / 2.0f),
		0,
		cosf(mPhi + M_PI / 2.0f)
	);

	mUp = glm::cross(mFront, mLeft);
}
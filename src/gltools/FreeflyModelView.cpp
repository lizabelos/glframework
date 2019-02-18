#include "FreeflyModelView.h"

#define _USE_MATH_DEFINES
#include <cmath>

GLTools::FreeflyModelView::FreeflyModelView() : GLTools::ModelView3D(), mPitch(0.0f), mRoll(0.0f), mYaw(0.0f), mTranslate(true) {

}

glm::mat4 GLTools::FreeflyModelView::getViewMatrix() const {
	glm::mat4 viewMatrix = glm::mat4(1.0f);

	viewMatrix = glm::rotate(viewMatrix, mPitch, glm::vec3(1.0f, 0.0f, 0.0f));
	viewMatrix = glm::rotate(viewMatrix, mYaw, glm::vec3(0.0f, 1.0f, 0.0f));
	if (mTranslate) viewMatrix = glm::translate(viewMatrix, mPosition);

	//viewMatrix = glm::rotate(viewMatrix, mPitch, glm::vec3(1.0f, 0.0f, 0.0f));
	//viewMatrix = glm::rotate(viewMatrix, mRoll, glm::vec3(0.0f, 0.0f, 1.0f));

	return viewMatrix;
}

void GLTools::FreeflyModelView::moveLeft(float t) {
	glm::vec3 mFront = glm::vec3(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) * glm::rotate(glm::mat4(1.0f), mYaw, glm::vec3(0.0f, 1.0f, 0.0f))) * t;
	mPosition += mFront;
}

void GLTools::FreeflyModelView::moveFront(float t) {
	glm::vec3 mFront = glm::vec3(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) * glm::rotate(glm::mat4(1.0f), mYaw, glm::vec3(0.0f, 1.0f, 0.0f))) * t;
	mPosition += mFront;
}

void GLTools::FreeflyModelView::rotateLeft(float t) {
	mYaw = mYaw + t;
}

void GLTools::FreeflyModelView::rotateUp(float t) {
	mPitch = mPitch - t;
}

void GLTools::FreeflyModelView::moveUp(float t) {
	mPosition.y = mPosition.y + t;
}

void GLTools::FreeflyModelView::enableTranslation() {
	mTranslate = true;
}

void GLTools::FreeflyModelView::disableTranslation() {
	mTranslate = false;
}

glm::vec3 GLTools::FreeflyModelView::getPosition() {
	return mPosition;
}
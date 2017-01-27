#pragma once

#include "ofMain.h"
#include "ofxFXObject.h"

class ofxP2 : public ofxFXObject {
public:

	ofxP2() {
		passes = 1;
		internalFormat = GL_RGBA32F;
		ofBuffer buffer = ofBufferFromFile("ofxP2.glsl");
		setCode(buffer.getText(), "");
	};
	void update(float time, float offset, float speed, float zoom) {

		shader.setUniform1f("time", time*speed);
		shader.setUniform1f("offset", offset);
		shader.setUniform1f("zoom", zoom);
		shader.setUniform2f("resolution", (float)width, (float)height);
		shader.setUniform2f("mouse", (float)ofGetMouseX() / width, (float)ofGetMouseY() / height);
	};

};


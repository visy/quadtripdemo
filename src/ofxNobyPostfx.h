#pragma once

#include "ofMain.h"
#include "ofxFXObject.h"

class ofxNobyPostfx : public ofxFXObject {
public:

	ofxNobyPostfx() {
		passes = 1;
		internalFormat = GL_RGBA32F;
		ofBuffer buffer = ofBufferFromFile("ofxNobyPostfx.glsl");
		setCode(buffer.getText(), "");

	};

	int frame = 1;

	void update(float time, ofTexture tex) {
		shader.setUniform1i("frame", frame++);
		shader.setUniform1f("time", time);
		shader.setUniform2f("resolution", (float)width, (float)height);
		shader.setUniform2f("mouse", (float)ofGetMouseX() / width, (float)ofGetMouseY() / height);
		//shader.setUniform1i(tex.);
	};

};


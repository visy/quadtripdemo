#pragma once

#include "ofMain.h"
#include "ofxFXObject.h"

class ofxTuringPattern_B : public ofxFXObject {
public:
	
	ofxTuringPattern_B(){
		passes = 1;
		internalFormat = GL_RGBA32F;
		ofBuffer buffer = ofBufferFromFile("ofxTuringPattern_B.glsl");
		setCode(buffer.getText(), "");		
	};
	void update(float time){
		
		shader.setUniform1f("time", time);
		shader.setUniform2f("resolution", (float)width, (float)height);
		shader.setUniform2f("mouse", (float)ofGetMouseX()/width, (float)ofGetMouseY()/height);
		
	};
	
};


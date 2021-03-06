#pragma once

#include "ofMain.h"
#include "ofxFXObject.h"

class ofxCircleHex : public ofxFXObject {
public:
    
	ofxCircleHex() {
        passes = 1;
        internalFormat = GL_RGBA32F;
		ofBuffer buffer = ofBufferFromFile("ofxCircleHex.glsl");
		setCode(buffer.getText(), "");
    };
    void update(float time, float offset, float speed){
        
        shader.setUniform1f("time", time*speed);
		shader.setUniform1f("offset", offset);
        shader.setUniform2f("resolution", (float)width, (float)height);
        shader.setUniform2f("mouse", (float)ofGetMouseX()/width, (float)ofGetMouseY()/height);
    };
    
};


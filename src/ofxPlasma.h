#pragma once

#include "ofMain.h"
#include "ofxFXObject.h"

class ofxPlasma : public ofxFXObject {
public:
    
	ofxPlasma(){
        passes = 1;
        internalFormat = GL_RGBA32F;
		ofBuffer buffer = ofBufferFromFile("ofxPlasma.glsl");
		setCode(buffer.getText(), "");

	};
    void update(float time, float offset, float speed, float peilaus){
        
		shader.setUniform1f("offset1", offset);
		shader.setUniform1f("peilaus", peilaus);
		shader.setUniform1f("time", time*speed);
        shader.setUniform2f("resolution", (float)width, (float)height);
        shader.setUniform2f("mouse", (float)ofGetMouseX()/width, (float)ofGetMouseY()/height);
    };
    
};


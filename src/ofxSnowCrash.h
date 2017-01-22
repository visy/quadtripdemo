#pragma once

#include "ofMain.h"
#include "ofxFXObject.h"

class ofxSnowCrash : public ofxFXObject {
public:
    
	ofxSnowCrash(){
        passes = 1;
        internalFormat = GL_RGBA32F;
		ofBuffer buffer = ofBufferFromFile("ofxSnowCrash.glsl");
		setCode(buffer.getText(), "");
    };
    void update(float time, float speed){
        
		shader.setUniform1f("time", time);
		shader.setUniform1f("speed", speed);
		shader.setUniform2f("resolution", (float)width, (float)height);
        shader.setUniform2f("mouse", (float)ofGetMouseX()/width, (float)ofGetMouseY()/height);
    };
    
};


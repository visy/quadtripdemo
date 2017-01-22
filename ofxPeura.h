#pragma once

#include "ofMain.h"
#include "ofxFXObject.h"

class ofxPeura : public ofxFXObject {
public:
    
	ofxPeura(){
        passes = 1;
        internalFormat = GL_RGBA32F;
        fragmentShader = STRINGIFY(

			uniform float time;
			uniform vec2 resolution;
		);
    };
    void update(float time){
        
		shader.setUniform1f("time", time);
        shader.setUniform2f("resolution", (float)width, (float)height);
    };
    
};


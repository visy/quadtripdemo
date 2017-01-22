#pragma once

#include "ofMain.h"
#include "ofxFXObject.h"

class ofxTuringPattern_D : public ofxFXObject {
public:
    
    ofxTuringPattern_D(){
        passes = 1;
        internalFormat = GL_RGBA32F;
        fragmentShader = STRINGIFY(
                                   uniform float     time;           // shader playback time (in seconds)
                                   uniform vec3      mouse;
                                   uniform vec2      resolution;           // viewport resolution (in pixels)
                                   uniform sampler2D tex0;          // BufC
                                   
								   void main()
								   {
									   vec2 pp = gl_FragCoord.xy / resolution.xy;
									   vec4 color = texture2D(tex0, pp);
									   color *= vec4(smoothstep(-0.2, 0.5, pow(1.0*abs(0.5 - pp.y), 0.5)));
									   gl_FragColor = color;
								   }
        
								   );
    };

    void update(float time){
        shader.setUniform1f("time", time);
        shader.setUniform2f("resolution", (float)width, (float)height);
        shader.setUniform2f("mouse", (float)ofGetMouseX()/width, (float)ofGetMouseY()/height);    
    };
    
};


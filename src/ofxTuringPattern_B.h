#pragma once

#include "ofMain.h"
#include "ofxFXObject.h"

class ofxTuringPattern_B : public ofxFXObject {
public:
	
	ofxTuringPattern_B(){
		passes = 1;
		internalFormat = GL_RGBA32F;
		fragmentShader = STRINGIFY(
								   uniform float     time;           // shader playback time (in seconds)
								   uniform vec3      mouse;
								   uniform vec2      resolution;           // viewport resolution (in pixels)
								   uniform sampler2D tex0;          // Video
								   uniform sampler2D tex1;          // BufA

								   void main()
								   {
									   vec2 uv = gl_FragCoord.xy / resolution.xy;

									   int sample = 0;

									   if (time > 1.0) sample = 1;

									   gl_FragColor = vec4(texture2D(tex1, uv*vec2(1.0, 1.0)).bgr*texture2D(tex1, uv).rbg, 1.0) - vec4(texture2D(tex1, uv*vec2(1.022, 1.0 + 0.01*cos(time))).rgb*0.3*texture2D(tex0, uv).rgr, 0.2);
								   }

								   );
		
	};
	void update(float time){
		
		shader.setUniform1f("time", time);
		shader.setUniform2f("resolution", (float)width, (float)height);
		shader.setUniform2f("mouse", (float)ofGetMouseX()/width, (float)ofGetMouseY()/height);
		
	};
	
};


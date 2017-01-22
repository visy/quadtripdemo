#pragma once

#include "ofMain.h"
#include "ofxFXObject.h"

class ofxTuringPattern_C : public ofxFXObject {
public:
	
	ofxTuringPattern_C(){
		passes = 1;
		internalFormat = GL_RGBA32F;
		
		fragmentShader = STRINGIFY(
								   uniform float     time;           // shader playback time (in seconds)
								   uniform vec3      mouse;
								   uniform vec2      resolution;    // viewport resolution (in pixels)
								   uniform sampler2D tex0;          // BufB

								   float pixel = 1.0;
								   vec4 blury(vec2 uv) {
									   vec3 acc = vec3(0);
									   float sp;
									   for (float i = -20.0 / 2.0; i < 20.0 / 2.0; i += 1.0) {
										   float z = 0.5 - uv.y;
										   sp = pixel*(z*12.0) / resolution.y;
										   acc += texture2D(tex0, uv + vec2(0, sp)*i).rgb;
									   }
									   acc /= 20.0;
									   return vec4(acc, 1.0);
								   }

								   void main()
								   {
									   vec2 pp = gl_FragCoord.xy / resolution.xy;
									   vec4 color = texture2D(tex0, pp);
									   if (pp.y < 0.5) color = blury(pp)*(1.0 - (0.5 - pp.y));
									   gl_FragColor = vec4(color);
								   }

								   );
		
	};
	
	void update(float time){
		
		shader.setUniform1f("time", time);
		shader.setUniform2f("resolution", (float)width, (float)height);
		shader.setUniform2f("mouse", (float)ofGetMouseX()/width, (float)ofGetMouseY()/height);
		
	};
	
	
};

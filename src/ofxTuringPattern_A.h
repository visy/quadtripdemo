#pragma once

#include "ofMain.h"
#include "ofxFXObject.h"

class ofxTuringPattern_A : public ofxFXObject {
public:

	ofxTuringPattern_A() {
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


				uv.x -= 0.001 + texture2D(tex0, uv).r*0.051;
				uv.y += 0.001 + texture2D(tex0, uv).g*0.081;
				uv.x -= 0.001 + texture2D(tex0, uv).b*(0.11 + cos(time*0.01)*0.1);
		
				gl_FragColor = vec4(texture2D(tex1, uv*vec2(1.1 + cos(time*1. + texture2D(tex1, uv).r)*0.01, 1.0 + cos(time*10.)*0.01) - vec2(distance(texture2D(tex0, uv).b, texture2D(tex0, uv*vec2(1.0, 1.0)).r*0.2 - cos(time*1.)*0.04)*0.1)).grb, 1.0);
			});

	};
	void update(float time) {

		shader.setUniform1f("time", time);
		shader.setUniform2f("resolution", (float)width, (float)height);
		shader.setUniform2f("mouse", (float)ofGetMouseX() / width, (float)ofGetMouseY() / height);
	};

};


#pragma once

#include "ofMain.h"
#include "ofxTuringPattern.h"
#include "ofxTuringPattern_A.h"
#include "ofxTuringPattern_B.h"
#include "ofxTuringPattern_C.h"
#include "ofxTuringPattern_D.h"
#include "ofxCircleHex.h"
#include "ofxPlasma.h"
#include "ofxTehoOsasto.h"
#include "ofxNobyPostfx.h"
#include "ofxSnowCrash.h"
#include "ofxP2.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"
#include "ofxCenteredTrueTypeFont.h"
#include "ofxPostProcessing.h"
#include "ofxImageSequence.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();

	void renderText();
	void renderTerm();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void TuringPatternInitordie();


    ofxTuringPattern TuringPattern;
    ofxTuringPattern_A TuringPattern_A;
    ofxTuringPattern_B TuringPattern_B;
    ofxTuringPattern_C TuringPattern_C;
    ofxTuringPattern_D TuringPattern_D;

	ofxCircleHex CircleHex;

	ofxPlasma Plasma;

	ofxTehoOsasto TehoOsasto;

	ofxSnowCrash SnowCrash;

    ofImage noise;
	ofImage absce;

	ofSoundPlayer mySound;
	ofxImageSequence myVideo;
	ofFbo fbo;

	ofFbo fboText;

	ofxCenteredTrueTypeFont ttf;
	ofxCenteredTrueTypeFont ttf2;
	ofxCenteredTrueTypeFont ttf3;

	ofxCenteredTrueTypeFont ttf_term;

	ofxAssimpModelLoader model;

	ofxPostProcessing post;

	ofxP2 P2;
	
    int width,height;
    float time;
};

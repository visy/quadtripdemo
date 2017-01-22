#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main(int argc, char *argv[]){

	int fs = 0;
	int ww = 1280;
	int hh = 720;

	if (argc > 1) {
		ww = atoi(argv[1]);
		hh = atoi(argv[2]);
		fs = atoi(argv[3]);
	}

	cout << "w:" << ww << endl;
	cout << "h:" << hh << endl;
	cout << "fs:" << fs << endl;

    ofSetupOpenGL(ww,hh,fs == 0 ? OF_WINDOW : OF_FULLSCREEN);			// <-------- setup the GL context
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
    
}

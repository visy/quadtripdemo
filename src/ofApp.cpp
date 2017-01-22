#include "ofApp.h"
#include "sync.h"

static const double bpm = 133.; /* beats per minute */
static const int rpb = 8; /* rows per beat */
static const double row_rate = (double(bpm) / 60.) * rpb;

sync_device *rocket;

static ofApp* self = NULL;

const struct sync_track *blend_1;
const struct sync_track *blend_2;
const struct sync_track *blend_3;
const struct sync_track *blend_4;
const struct sync_track *blend_5;
const struct sync_track *blend_6;
const struct sync_track *blend_7;
const struct sync_track *blend_8;
const struct sync_track *blend_9;
const struct sync_track *blend_10;

const struct sync_track *post_bloom;
const struct sync_track *post_godrays;
const struct sync_track *post_hortilt;
const struct sync_track *post_lut;

const struct sync_track *text_index;

const struct sync_track *offset_plasma;
const struct sync_track *speed_plasma;

const struct sync_track *speed_snow;

const struct sync_track *peilaus_plasma;

float _blend_1;
float _blend_2;
float _blend_3;
float _blend_4;
float _blend_5;
float _blend_6;
float _blend_7;
float _blend_8;
float _blend_9;
float _blend_10;

float _post_bloom;
float _post_godrays;
float _post_hortilt;
float _post_lut;

float _text_index;

float _offset_plasma;
float _speed_plasma;

float _speed_snow;

float _peilaus_plasma;

float eflip = 0.0;

int videoWidth;
int videoHeight;

#ifndef SYNC_PLAYER

static double get_row(void* p)
{
	double tt = (*self).mySound.getPositionMS()*0.001;
	return tt * row_rate;
}

static void pause(void *d, int flag)
{
	if (flag) {
		(*self).mySound.setPaused(true);

	}
	else {
		(*self).mySound.setPaused(false);
	}
}

static void set_row(void *d, int row)
{
	(*self).mySound.setPositionMS((((double)row)/row_rate)*1000.);
}

static int is_playing(void *d)
{
	return (*self).mySound.isPlaying();
}

static struct sync_cb cb = {
	pause,
	set_row,
	is_playing
};

#endif /* !defined(SYNC_PLAYER) */
//--------------------------------------------------------------
void ofApp::setup(){
    
	self = this;
    width = ofGetWidth();
    height = ofGetHeight();

	videoWidth = width;
	videoHeight = height;
    
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
    ofBackground(0);
    ofDisableAlphaBlending();
    
    ofDisableArbTex();

	post.init(width/2., height/2.);
	post.createPass<BloomPass>()->setEnabled(false);
	post.createPass<GodRaysPass>()->setEnabled(false);
	post.createPass<ToonPass>()->setEnabled(false);

	post.createPass<FxaaPass>();
	post.createPass<LUTPass>()->loadLUT("tex.cube")->setEnabled(false);

	model.loadModel("test.obj");

	TuringPatternInitordie();

    noise.load("noise.png");
    noise.allocate(width, height, OF_IMAGE_COLOR);

	absce.load("absce.png");
	absce.allocate(869, 872, OF_IMAGE_COLOR_ALPHA);

	ttf.loadFont("font.ttf", 100);
	ttf2.loadFont("font3.ttf", 100);
	ttf3.loadFont("font2.ttf", 100);
	ttf_term.loadFont("font_term.ttf", 24);

	rocket = sync_create_device("sync");
#ifndef SYNC_PLAYER
	sync_connect(rocket, "localhost", SYNC_DEFAULT_PORT);
#endif

	/* get tracks */
	blend_1 = sync_get_track(rocket, "blend_circlehex"); // circlehex
	blend_2 = sync_get_track(rocket, "blend_vidfbo"); // video in fbo
	blend_3 = sync_get_track(rocket, "blend_video"); // video render
	blend_4 = sync_get_track(rocket, "blend_plasma"); // plasma
	blend_5 = sync_get_track(rocket, "blend_model"); // model
	blend_6 = sync_get_track(rocket, "blend_text"); // text
	blend_7 = sync_get_track(rocket, "blend_teho"); // teho
	blend_8 = sync_get_track(rocket, "blend_logo"); // logo
	blend_9 = sync_get_track(rocket, "blend_snow"); // snow crash
	blend_10 = sync_get_track(rocket, "blend_peura"); // peura

	post_bloom = sync_get_track(rocket, "post_bloom");
	post_godrays = sync_get_track(rocket, "post_godrays");
	post_hortilt = sync_get_track(rocket, "post_hortilt");
	post_lut = sync_get_track(rocket, "post_lut");

	text_index = sync_get_track(rocket, "text_index");

	offset_plasma = sync_get_track(rocket, "offset_plasma");
	speed_plasma = sync_get_track(rocket, "speed_plasma");

	speed_snow = sync_get_track(rocket, "speed_snow");

	peilaus_plasma = sync_get_track(rocket, "peilaus_plasma");

	fbo.allocate(videoWidth, videoHeight);

	// clear fbo
	fbo.begin();
	ofClear(255, 255, 255, 0);
	fbo.end();

	myVideo.loadMovie("video2.mov");
	myVideo.play();

	mySound.load("music.mp3");
	mySound.play();
}

//--------------------------------------------------------------
void ofApp::update() {

	time = mySound.getPositionMS()*0.001;
	double row = time * row_rate;


#ifndef SYNC_PLAYER
	row = get_row(NULL);
	if (sync_update(rocket, (int)floor(row), &cb, NULL))
		sync_connect(rocket, "localhost", SYNC_DEFAULT_PORT);
#endif

	_blend_1 = float(sync_get_val(blend_1, row));
	_blend_2 = float(sync_get_val(blend_2, row));
	_blend_3 = float(sync_get_val(blend_3, row));
	_blend_4 = float(sync_get_val(blend_4, row));
	_blend_5 = float(sync_get_val(blend_5, row));
	_blend_6 = float(sync_get_val(blend_6, row));
	_blend_7 = float(sync_get_val(blend_7, row));
	_blend_8 = float(sync_get_val(blend_8, row));
	_blend_9 = float(sync_get_val(blend_9, row));
	_blend_10 = float(sync_get_val(blend_10, row));

	_post_bloom = float(sync_get_val(post_bloom, row));
	_post_godrays = float(sync_get_val(post_godrays, row));
	_post_hortilt = float(sync_get_val(post_hortilt, row));
	_post_lut = float(sync_get_val(post_lut, row));

	_text_index = float(sync_get_val(text_index, row));

	_offset_plasma = float(sync_get_val(offset_plasma, row));
	_speed_plasma = float(sync_get_val(speed_plasma, row));

	_speed_snow = float(sync_get_val(speed_snow, row));

	_peilaus_plasma = float(sync_get_val(peilaus_plasma, row));



	if (_blend_2 > 0.0)
		myVideo.update();


	if (_blend_1 > 0.0) {
		for (int i = 0; i < 2; i++) {
			CircleHex.beginS();
			CircleHex.setPingPongFbo("tex0", fbo.getTexture(), 0);
			if (i == 1)CircleHex.update(time);
			CircleHex.endS();
		}
	}

	/*
		if (time > 101.0) {
			ofApp:exit();
			std::exit(0);
		}
	*/

	if (_blend_3 > 0.0) {

		eflip = cos(time*2.5);

		for (int i = 0; i < 2; i++) {
			TuringPattern_A.beginS();
			TuringPattern_A.setPingPongFbo("tex1", fbo.getTexture(), 1);
			TuringPattern_A.setPingPongFbo("tex0", TuringPattern_A.getTexture(), 0);
			if (i == 1)TuringPattern_A.update(time);
			TuringPattern_A.endS();


			TuringPattern_B.beginS();
			TuringPattern_B.setPingPongFbo("tex0", fbo.getTexture(), 1);
			TuringPattern_B.setPingPongFbo("tex1", TuringPattern_A.getTexture(), 0);
			if (i == 1)TuringPattern_B.update(time);
			TuringPattern_B.endS();

			TuringPattern.beginS();
			TuringPattern.setPingPongFbo("tex0", TuringPattern_B.getTexture(), 0);
			if (i == 1)TuringPattern.update(time);
			TuringPattern.endS();
		}
	}


	if (_blend_4 > 0.0) {
		for (int i = 0; i < 2; i++) {
			Plasma.beginS();
			Plasma.setPingPongFbo("tex0", Plasma.getTexture(), 0);
			if (i == 1)Plasma.update(time, _offset_plasma,_speed_plasma,_peilaus_plasma);
			Plasma.endS();
		}
	}

	if (_blend_7 > 0.0) {
		for (int i = 0; i < 2; i++) {
			TehoOsasto.beginS();
			TehoOsasto.setPingPongFbo("tex0", TehoOsasto.getTexture(), 0);
			if (i == 1)TehoOsasto.update(time);
			TehoOsasto.endS();
		}
	}

	if (_blend_9 > 0.0) {
		for (int i = 0; i < 2; i++) {
			SnowCrash.beginS();
			SnowCrash.setPingPongFbo("tex0", SnowCrash.getTexture(), 0);
			if (i == 1)SnowCrash.update(time,_speed_snow);
			SnowCrash.endS();
		}
	}

	for (int i = 0; i < 2; i++) {
		P2.beginS();
		if (i == 1)P2.update(time);
		P2.endS();
	}


}

void ofApp::renderText() {

	ofSetColor(0, 0, 0, 255 * _blend_6);
	if (_text_index == 0.0) ttf.drawStringCentered("Quadtrip", ofGetWidth() / 2 + 8, ofGetHeight() / 2 + 8);
	if (_text_index == 1.0) ttf.drawStringCentered("Presents", ofGetWidth() / 2 + 8, ofGetHeight() / 2 + 8);

	ofSetColor(255, 255, 255, 255 * _blend_6);
	if (_text_index == 0.0)  ttf.drawStringCentered("Quadtrip", ofGetWidth() / 2, ofGetHeight() / 2);
	if (_text_index == 1.0)  ttf.drawStringCentered("Presents", ofGetWidth() / 2, ofGetHeight() / 2);
	if (_text_index == 2.0)  ttf.drawStringCentered("a new demo", ofGetWidth() / 2, ofGetHeight() / 2);
	if (_text_index == 3.0)  ttf2.drawStringCentered("tears", ofGetWidth() / 2, ofGetHeight() / 2);

}

string tekstit[20] =
{
"Amyglada Inject System v2.01 booting...",
"* running on Quadtrip 32yo.t (licenced)*",
"---------------------------------------",
"* probing devices...",
" ",
"found headset!",
"found injection port!",
" ",
"* waiting for devices to respond...",
" ",
"* contacting licence server(s)...",
"192 days since previous system check",
"continuing with trial period (162 days over!)",
" ",
"ready for connections...",
};

void ofApp::renderTerm() {
	static float term_x = 18.;
	float term_y = 22.;

	ofSetColor(128, 128, 128, 128);

	int tt = (int)round(time*2.6);

	if (tt > 20) tt = 20;

	for (int i = 0; i <= tt; i++) {
		ttf_term.drawString(tekstit[i], term_x, term_y);
		term_y += 26;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	// enable / disable post effects in post chain

	if (_post_bloom > 0.0) {
		post[0]->setEnabled(true);
	} else {
		post[0]->setEnabled(false);
	}

	if (_post_godrays > 0.0) {
		post[1]->setEnabled(true);
	}
	else {
		post[1]->setEnabled(false);
	}

	if (_post_hortilt > 0.0) {
		post[2]->setEnabled(true);
	}
	else {
		post[2]->setEnabled(false);
	}

	if (_post_lut > 0.0) {
		post[4]->setEnabled(true);
	}
	else {
		post[4]->setEnabled(false);
	}

	// render scene

	post.begin();
	ofClear(0, 255);  
	ofDisableBlendMode();
	ofDisableAlphaBlending();

	if (_blend_1 > 0.0) {
		ofSetColor(255, 255, 255, 255 * _blend_1);
		CircleHex.draw(0, 0, width, height);
	}

	if (_blend_2 > 0.0) {
		fbo.begin();
		ofSetColor(255, 255, 255, 255 * _blend_2);
		myVideo.draw(0, 0, width, height);

		ofSetColor(255, 255, 255, 255 * _blend_6);
		if (_text_index == 2.0)  ttf.drawStringCentered("a new demo", ofGetWidth() / 2, ofGetHeight() / 2);
		ofSetColor(0, 0, 0, 255 * _blend_6);
		if (_text_index == 2.0) ttf.drawStringCentered("a new demo", ofGetWidth() / 2 + 8, ofGetHeight() / 2 + 8);

		ofSetColor(255, 255, 255, 255 * _blend_6);
		if (_text_index == 3.0)  ttf2.drawStringCentered("tears", ofGetWidth() / 2, ofGetHeight() / 2);
		ofSetColor(0, 0, 0, 255 * _blend_6);
		if (_text_index == 3.0) ttf2.drawStringCentered("tears", ofGetWidth() / 2 + 8, ofGetHeight() / 2 + 8);

		fbo.end();
	}

	if (_blend_3 > 0.0) {
		TuringPattern_A.swap();
		TuringPattern_B.swap();
		TuringPattern.swap();

		ofSetColor(255, 255, 255, 255 * _blend_3);
		TuringPattern.draw(0, 0, width, height);
	}
	
	if (_blend_4 > 0.0) {
		Plasma.swap();
		ofSetColor(255, 255, 255, 255 * _blend_4);
		Plasma.draw(0,0,width,height);
	}

	if (_blend_5 > 0.0) {
		ofSetColor(210, 215, 250, 255*_blend_5);

		model.setPosition(ofGetWidth() / 2, (float)ofGetHeight() * 0.65 - time*1.3, time*40.);
		float ss = 1.0 + time*0.2;
		model.setScale(ss, ss, ss);
		model.drawFaces();
	}

	if (_blend_6 > 0.0) {
		renderText();
	}

	if (_blend_8 > 0.0) {
		ofEnableAlphaBlending();

		ofSetColor(255 * _blend_8, 255 * _blend_8, 255 * _blend_8, 255);
		absce.draw(width / 2 - 256, height / 2 - 256, 512, 512);
	}


	if (_blend_9 > 0.0) {
		ofSetColor(255 * _blend_9, 255 * _blend_9, 255 * _blend_9, 255);
		SnowCrash.swap();
		SnowCrash.draw(0, 0, width, height);
	}

	if (_blend_10 > 0.0) {
		ofDisableAlphaBlending();
		ofEnableBlendMode(OF_BLENDMODE_ADD);
		ofSetColor(255, 255, 255, 255 * _blend_10);
		P2.swap();
		P2.draw(0, 0, width, height);
	}

	post.end();

	renderText();

	if (_blend_7 > 0.0) {
		ofSetColor(255, 255, 255, 255 * _blend_7);
		TehoOsasto.swap();
		TehoOsasto.draw(0, 0, width, height);
	}

	if (time < 6.)
		renderTerm();

}

void ofApp::TuringPatternInitordie() {
    TuringPattern.allocate(512, 512);
    TuringPattern_A.allocate(512, 512);

	TuringPattern_B.allocate(512, 512);
    TuringPattern_C.allocate(512, 512);
    TuringPattern_D.allocate(512, 512);

	CircleHex.allocate(1024, 1024);
	CircleHex.allocate(512, 512);

	ofImage img1, img2, img3, img4, img5, img6;
	img1.setUseTexture(false);
	img2.setUseTexture(false);
	img3.setUseTexture(false);
	img4.setUseTexture(false);
	img5.setUseTexture(false);
	img6.setUseTexture(false);

	img1.load("sky01/right.png");
	img2.load("sky01/left.png");
	img3.load("sky01/top.png");
	img4.load("sky01/down.png");
	img5.load("sky01/front.png");
	img6.load("sky01/back.png");

	img1.allocate(512, 512, OF_IMAGE_COLOR);
	img2.allocate(512, 512, OF_IMAGE_COLOR);
	img3.allocate(512, 512, OF_IMAGE_COLOR);
	img4.allocate(512, 512, OF_IMAGE_COLOR);
	img5.allocate(512, 512, OF_IMAGE_COLOR);
	img6.allocate(512, 512, OF_IMAGE_COLOR);

	Plasma.allocate(512, 512);

	TehoOsasto.allocate(512, 512);
	SnowCrash.allocate(width, height);

	P2.allocate(width, height);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}

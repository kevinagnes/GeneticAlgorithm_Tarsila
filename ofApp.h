#pragma once
#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "Painting.h"
#include "GlowEffect.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyReleased(int key);


        int popmax;
        float mutationRate;
        Painting painting;
        bool activate;
		int state = 1;
		int OSCbutton;
		int myWidth = 0;
		int myHeight = 0;
		bool splash = true;
		bool guiDraw = false;

		void savePic();

		// gui variables
		ofxPanel gui;
		ofParameterGroup parameters;
		ofParameter<float> multiplierX, xScale, multiplierY, yScale, shadow, noise, glowVal, blurVal;
		ofParameter<bool> print,debug;
		// custom font
		ofTrueTypeFont font1;

		// timers for debouncing buttons
		unsigned long debounced = 0, debounced2 = 0, debounced3 = 0;
		int debounceTime  = 200;
		int debounceTime2 =  10;
		int debounceTime3 = 1000;
		int debounceTime4 = 150;

		// osc receiver
		#define PORT 14587
		#define NUM_MSG_STRINGS 20
		ofxOscReceiver receiver;
		float accVal=0;
		int param=0;

		// glow effect
		GlowEffect glow;

		// maxim audio feedback
		void exit();
		void audioOut(ofSoundBuffer& buffer);
		ofSoundStreamSettings soundSettings;
		ofSoundStream soundStream;
		int sampleRate;
		int bufferSize;
		float mod=1;
		maxiOsc osc1, osc2, osc3;

		double wave;
		float chord;
		void feedBack(int state);
		bool play = false;
		float freq = 0;
};


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // global setup
    ofBackground(0);
    ofSetFrameRate(30);
    popmax = 9;
    mutationRate = 0.1f;
    painting.requestState(state);
    painting.setup(mutationRate, popmax);
    myWidth = ofGetWidth();
    myHeight = ofGetHeight();

    // osc setup
    cout << "listening for osc messages on port " << PORT << "\n";
    receiver.setup(PORT);

    // glow setup
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableSmoothing();

    // font setup
    font1.load("pixelsix10.ttf", 20);
    
    // gui setup
    parameters.setName("Highlight & Shadow");
    parameters.add(multiplierX.set("Right: ", 0.015f, 0, 0.2f));
    parameters.add(xScale.set("Left: ", .97f, 0.5f, 1));
    parameters.add(multiplierY.set("Top: ", 0, 0, 0.2f));
    parameters.add(yScale.set("Bottom: ", 1, 0.5f, 1));
    parameters.add(shadow.set("Shadow: ", .55f, 0, 1));
    parameters.add(noise.set("Noise: ", 5, 0, 10));
    parameters.add(glowVal.set("Glow: ", 1.2f, 1, 2));
    parameters.add(blurVal.set("Blur: ",0,0,30));
    parameters.add(print.set("Save Picture", false));
    parameters.add(debug.set("Debug ", false));
    gui.setup(parameters);
    gui.setPosition(myWidth - gui.getWidth(), 0);

    // maxim setup
    sampleRate = 44100;
    bufferSize = 512;
    maxiSettings::setup(sampleRate, 2, bufferSize);
    //sets up the soundStream object with default devices
    auto devices = soundStream.getMatchingDevices("default");
    //you can also list input/output devices with soundStream.printDeviceList()
    soundSettings.setApi(ofSoundDevice::Api::MS_DS);
    soundSettings.setOutListener(this);
    soundSettings.sampleRate = sampleRate;
    soundSettings.numOutputChannels = 2;
    soundSettings.numInputChannels = 0;
    soundSettings.bufferSize = bufferSize;
    soundStream.setup(soundSettings);
}   

void ofApp::update(){

    // osc update
    while (receiver.hasWaitingMessages()) {
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);

        // messages received from /slider4
        if (m.getAddress() == "/slider4") {

            // Accel Z axis from custom android app
            OSCbutton = m.getArgAsInt(0);

            // if statement for debouncing the buttons
            if (abs(ofGetElapsedTimeMillis() - debounced) > debounceTime) {

                // four corner buttons
                if (OSCbutton == 12) {
                        feedBack(0);
                        state--;
                        if (state < 0) state = 2;
                        painting.requestState(state);    
                }
                else if (OSCbutton == 11) {
                        feedBack(2);
                        painting.selection();
                        painting.generate();      
                }
                else if (OSCbutton == 10) {
                        feedBack(0);
                        state++;
                        if (state > 2) state = 0;
                        painting.requestState(state);
                }
                else if (OSCbutton == 9) {
                        feedBack(3);
                        state = 3;
                        painting.requestState(state);   
                        
                }
                debounced = ofGetElapsedTimeMillis();
            }

            // nine square buttons
            if (OSCbutton < 9) {
                painting.pick(OSCbutton);
                if (state == 3) return feedBack(4);
                feedBack(1);
            }
        }

        // stop if not state 3
        if (state != 3) return;

        // messages received from /slider5
        // for adding effects for the output
        if (m.getAddress() == "/slider5") {
            param = m.getArgAsInt(0);
            accVal = m.getArgAsFloat(1);
            
            // debouncing for buttons 0-7
            // and mapping each param based on Acceleration Value
            if (abs(ofGetElapsedTimeMillis() - debounced2) > debounceTime2) {
                if (param == 0) multiplierX = ofMap(accVal, -90, 90, 0, 0.2f, true);
                if (param == 1)      xScale = ofMap(accVal, -90, 90, 0.5f, 1, true);
                if (param == 2) multiplierY = ofMap(accVal, -90, 90, 0, 0.2f, true);
                if (param == 3)      yScale = ofMap(accVal, -90, 90, 0.5f, 1, true);
                if (param == 4)      shadow = ofMap(accVal, -90, 90, 0,    1, true);
                if (param == 5)       noise = ofMap(accVal, -90, 90, 0,   10, true);
                if (param == 6)     glowVal = ofMap(accVal, -90, 90, 1,    2, true);
                if (param == 7)     blurVal = ofMap(accVal, -90, 90, 0,   30, true);
            }
            // debouncing for button 8, which saves the picture.
            if (abs(ofGetElapsedTimeMillis() - debounced2) > debounceTime3) {
                if (param == 8) print = true;
            }

            debounced2 = ofGetElapsedTimeMillis();
        }
    }
}

void ofApp::draw(){

    // necessary because of blending mode alpha
    ofBackground(0);

    ofBackground(0, 20, 0);
    // splash screen
    if (splash) { 
        ofSetColor(ofColor::lightGreen);
        const string out = "genetic painting \n tarsila do amaral - Abaporu";
        glow.begin(1.5f, 20);
        font1.drawString(out, myWidth * 0.5f - font1.stringWidth(out) * 0.5f, myHeight * 0.5f);
        glow.end();
        glow.draw();
        font1.drawString(out, myWidth * 0.5f - font1.stringWidth(out) * 0.5f, myHeight * 0.5f);
        if (ofGetElapsedTimeMillis() < 5000) return;
        splash = false;      
    }

    // send parameters to the objects
    painting.requestParameters(multiplierX, xScale, multiplierY, yScale, shadow, noise, debug);
    
    // stop here if not state 3
    if (state != 3) {
        ofPushMatrix();
        float s = .1f;
        ofTranslate(myWidth * s * 0.5f, myHeight * s * 0.5f + 25);
        ofScale(1 - s);
        painting.draw();
        ofPopMatrix();
        ofSetColor(ofColor::lightGreen);
        const string out = "select your favourite ones:";
        font1.drawString(out, myWidth * 0.5f - font1.stringWidth(out)*0.5f, 50);
        return;
    }

    // white background
    ofBackground(255);

    // add glow to the rendered output
    ofPushMatrix();
    float s = .1f;
    ofTranslate(myWidth*s*0.5f, myHeight * s * 0.5f);
    ofScale(1 - s);
    glow.begin(glowVal, blurVal);
    painting.draw();
    glow.end();
    glow.draw(); 
    ofPopMatrix();

    // framing
    ofPushStyle();
    ofSetColor(0, 20, 0);
    ofNoFill();
    ofSetLineWidth(5);
    int offset = 100;
    ofDrawRectRounded(offset * .5f, offset * .5f, myWidth - offset, myHeight - offset, 5);
    const string out = "Made with Genetic Painting 'Tarsila do Amaral - Abaporu'";
    ofDrawBitmapString(out, myWidth * 0.5f -230, ofGetHeight() - 22);
    ofPopStyle();

    // save picture
    if (print) savePic();

    // gui draw
    if (guiDraw) gui.draw();
}

// function for saving a picture with Date filename
void ofApp::savePic() {
    string filename = ofToString(ofGetYear()) + "-" + ofToString(ofGetMonth()) + "-" + ofToString(ofGetDay()) + "-" +
        ofToString(ofGetHours()) + "-" + ofToString(ofGetMinutes()) + "-" + ofToString(ofGetSeconds()) + ".png";
    ofSaveScreen(filename);
    print = false;
}

// function for debugging using keyboard 
void ofApp::keyReleased(int key){

    if (key == 'g' || key == 'G') {
        painting.selection();   
        painting.generate();
        feedBack(2);
    }
    else if (key>=48 && key <=57) {
        painting.pick(ofToInt(ofToString(char(key))));
        feedBack(1);
    }
    else if (key ==  OF_KEY_PAGE_UP) {
        state++;
        if (state > 3) state = 0;
        painting.requestState(state);
        feedBack(0);
    }
    else if (key == OF_KEY_PAGE_DOWN) {
        state--;
        if (state < 0) state = 3;
        painting.requestState(state);
        feedBack(0);
    }
    else if (key == OF_KEY_RIGHT_SHIFT) {
        guiDraw = !guiDraw;
        feedBack(0);
    }
    
}

// function for sound feedback
// creates a freq(frequency) and a mod(multiplier)
void ofApp::feedBack(int state) {
    // E, F#, A,  C#, D
    float note[5] = {329.6f, 370, 440, 554.4f,587.3f}; 
    freq = note[state];
    mod = 1;

    // for the nine buttons, each produces a different pitch
    if (state < 3 && OSCbutton < 9) {
        freq = note[state] * (OSCbutton + 1);
    }
    // adds the accelerometer data to control pitch shift
    else if (state == 4) {
        freq = note[(int)ofMap(accVal, -90, 90, 0, 4, true)]*.5f;
        mod = .5f * (int)ofMap(accVal, -90, 90, 1, 5, true) * (OSCbutton+1);
    }
    // enables the audio output
    play = true;
}

// function that outputs the sound feedback
void ofApp::audioOut(ofSoundBuffer& buffer) {

    // don't play sound if not requested  
    if (!play) {
        debounced3 = ofGetElapsedTimeMillis();
        // if state 3 let sound be continuous
        if (state != 3) return;
    }

    for (unsigned int i = 0; i < buffer.getNumFrames(); i++) {

        double wave1 = 0, wave2 = 0, wave3 = 0;

        // sinewaves produces less harsh sounds
        wave2 = osc1.sinewave(freq * mod);

        // only use other oscillators in states 0,1,2
        if (state < 3) {
            wave1 = osc2.saw(freq * mod * 0.5f);
            wave3 = osc3.triangle(freq * mod);
        }

        // sums the oscillators
        wave = wave1 + wave2 + wave3;

        // this is an attempt to remove wave breaks (noisy cracks)
        // it is generating a fade in (22ms) and fade out (75ms)
        float fade = 1;        
        if (ofGetElapsedTimeMillis() - debounced3 <= debounceTime4 * 0.15f) {
            fade = ofMap(ofGetElapsedTimeMillis() - debounced3, 0, debounceTime4 * 0.15f, 0, 1, true);
        }
        else if (ofGetElapsedTimeMillis() - debounced3 >= debounceTime4 * 0.50f) {
            fade = ofMap(ofGetElapsedTimeMillis() - debounced3, debounceTime4 * 0.50f, debounceTime4, 1, 0, true);
        }

        float outputVol = 0.2f;

        // final wave with volume control
        // we divide the output by 1/3 to prevent clipping
        if (state < 3) wave *= outputVol * 0.33f * fade;
        else wave *= outputVol * fade;

        // adds the wave to the buffer
        buffer[i * buffer.getNumChannels()] = wave;
        buffer[i * buffer.getNumChannels() + 1] = wave;
    }

    if (ofGetElapsedTimeMillis() - debounced3 < debounceTime4) return;
    
    play = false;    
}

void ofApp::exit() {
    ofSoundStreamClose();
}
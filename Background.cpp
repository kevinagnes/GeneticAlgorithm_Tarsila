#include "Background.h"


#define GENE_SIZE 1
//-------------------------------------------------------
Background::Background(){
    geneSize = GENE_SIZE;
    fitness = 0;
}
//-------------------------------------------------------
void Background::setup(DNA _dna){
    dna = _dna;
    geneSize = dna.geneSize;
    numOfGenes = dna.numOfGenes;
    calcPhenotype();
}
//-------------------------------------------------------
void Background::setup(int _numOfGenes)
{

    numOfGenes = _numOfGenes;
    dna.setup(numOfGenes, geneSize);
    calcPhenotype();
}

void Background::calcPhenotype(){

    //decode the genes into variables for drawing
    skyHue = ofMap(dna.genes[0],0,1,0,360);
    skyRes = ofMap(dna.genes[1], 0, 1, 0.2f, 0.1f);
    sunRot = ofMap(dna.genes[2], 0, 1, -90, 90);
    sunSize = ofMap(dna.genes[3], 0, 1, .25f, 2);
    totalHeight = ofMap(dna.genes[4], 0, 1, 0, -300);
    mult1 = ofMap(dna.genes[5], 0, 1, 0, 1);
    mult2 = ofMap(dna.genes[6], 0, 1, 0, 1);
    mult3 = ofMap(dna.genes[7], 0, 1, 0, 1);

    // setup noise
    for (int x = 0; x < 50; x++){
        for (int y = 0; y < 50; y++){
            noiseSeeds[x][y] = ofRandom(0, 1000);
        }
    }
}
void Background::mountains(){
    ofColor ColorX,ColorY;
    float hue,sat,lvl;
    ofPushStyle();
    for (float t = 1; t > 0; t -= 0.1f) {
        ofColor ColorY = ofColor(35, 62, 31);
        ofColor ColorX= ColorY;
        ColorX.setBrightness(ColorY.getBrightness() * shadow);
        ofSetColor(ColorX.getLerped(ColorY, t));
        ofPushMatrix();
        ofScale(ofMap(t, 0, 1, 1, xScale), ofMap(t, 0, 1, 1, yScale));
        ofBeginShape();
        ofVertex(modXY(70 - 500 * mult1, 1000, t ));
        ofVertex(modXY(70 - 500 * mult2, 953 , t ));
        ofVertex(modXY(92 - 500 * mult3, 907 + totalHeight * mult1, t ));
        ofVertex(modXY(127, 872 + totalHeight * mult2, t ));
        ofVertex(modXY(167, 847 + totalHeight * mult3, t ));
        ofVertex(modXY(197, 843 + totalHeight * mult3, t ));
        ofVertex(modXY(678, 899 + totalHeight * mult2, t ));
        ofVertex(modXY(879 + 500 * mult1, 914 + totalHeight * mult1, t ));
        ofVertex(modXY(930 + 500 *mult2, 939 , t ));
        ofVertex(modXY(930 + 500 * mult3, 1000 , t ));
        ofEndShape();
        ofPopMatrix();
    }
    ofPopStyle();
}

void Background::bkg() {
    float mul = ofGetHeight()*0.1f * skyRes;
    ofColor ColorY = ofColor(77, 154, 192);
    ofColor ColorX;
    ColorY.setHueAngle(skyHue);
    ColorX = ColorY;
    ColorX.setBrightness(ColorY.getBrightness() * shadow);
    for (float y = 0; y < ofGetHeight(); y += mul) {
        float t = ofMap(y,0,ofGetHeight(),0,1);
        ofSetColor(ColorY.getLerped(ColorX, t));
        ofDrawRectangle(0, y, ofGetHeight(), mul);
    }
}

void Background::sun() {
    ofColor ColorY = ofColor(219, 137, 44);
    ofColor ColorZ = ofColor(241, 173, 55);
    ofColor ColorX;
    ColorX = ColorY;
    ColorX.setBrightness(ColorY.getBrightness() * shadow);

    ofSetColor(ColorZ, 15);
    ofDrawEllipse(modXY(500, 105), 270 * sunSize, 265 * sunSize); //GLOW
    ofSetColor(ColorZ, 55);
    ofDrawEllipse(modXY(500, 105), 195 * sunSize, 210 * sunSize); //GLOW
    ofSetColor(ColorZ);
    ofDrawEllipse(modXY(500, 105), 125 * sunSize, 130 * sunSize); //GLOW

    ofSetColor(ColorX);
    ofDrawEllipse(modXY(500, 105), 40 * sunSize, 37 * sunSize); //THE SUN
    ofDrawLine(modXY(499 ,  76 ), modXY(499 ,  49 ));    // sun ray 12
    ofDrawLine(modXY(520 ,  84 ), modXY(540 ,  70 ));    // sun ray 1.5
    ofDrawLine(modXY(530 , 102 ), modXY(555 , 102 ));  // sun ray 3
    ofDrawLine(modXY(520 , 126 ), modXY(535 , 145 ));  // sun ray 4.5
    ofDrawLine(modXY(499 , 135 ), modXY(499 , 159 ));  // sun ray 6
    ofDrawLine(modXY(476 , 124 ), modXY(457 , 148 ));  // sun ray 7.5
    ofDrawLine(modXY(471 , 102 ), modXY(442 , 102 ));  // sun ray 9
    ofDrawLine(modXY(479 ,  83 ), modXY(451 ,  66 ));    // sun ray 10.5
}

//--------------------------------------------------------
// Draws the Background
void Background::draw(){
    counter = 0;
    bkg();
    mountains();

    ofPushMatrix();
    ofRotateDeg(sin(ofDegToRad(ofGetFrameNum())) * 5,1, 0, 1);
    sun();
    ofPopMatrix();
}

vec2 Background::modXY(float a, float b, float t) {

    float _noise = addNoise();
    float gradientX;
    float gradientY;
    float tt = ofMap(t, 1, 0, 0, 360);

    gradientX = a + a * sin(ofDegToRad(tt)) * multiplierX + _noise;
    gradientY = b + b * sin(ofDegToRad(tt)) * multiplierY + _noise;
    
    if (debug==true){
        if (t < 0.1f){
            ofPushStyle();
            ofSetColor(ofColor::red);
            ofDrawCircle(a,b,7);
            counter++;
            ofSetColor(255);
            ofDrawBitmapString(counter, a-4, b);
            ofPopStyle();
        }
    }
    return glm::vec2(gradientX, gradientY);
}

float Background::addNoise(){
    float randomness = ofNoise(ofNoise(noiseSeeds[(int)ofRandom(0, 50)][(int)ofRandom(0, 50)])) * noise * ofRandom(1);
    if (ofRandom(1) > .5f) randomness *= -1;
    return randomness;
}

void Background::getParameters(float _multiplierX, float _xScale, float _multiplierY, float _yScale, float _shadow, float _noise, bool _debug) {
    multiplierX = _multiplierX;
    xScale = _xScale;
    multiplierY = _multiplierY;
    yScale = _yScale;
    shadow = _shadow;
    noise = _noise;
    debug = _debug;
}

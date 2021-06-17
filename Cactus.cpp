#include "Cactus.h"


#define GENE_SIZE 1
//-------------------------------------------------------
Cactus::Cactus(){
    geneSize = GENE_SIZE;
    fitness = 0;
}
//-------------------------------------------------------
void Cactus::setup(DNA _dna){
    dna = _dna;
    geneSize = dna.geneSize;
    numOfGenes = dna.numOfGenes;
    calcPhenotype();
}
//-------------------------------------------------------
void Cactus::setup(int _numOfGenes)
{

    numOfGenes = _numOfGenes;
    dna.setup(numOfGenes, geneSize);
    calcPhenotype();
}

void Cactus::calcPhenotype(){

    //decode the genes into variables for drawing
    pos1 = ofMap(dna.genes[0], 0, 1, -100, 100);
    pos2 = ofMap(dna.genes[1], 0, 1, -100, 100);
    color1 = ofMap(dna.genes[2], 0, 1, -40, 40);
    color2 = ofMap(dna.genes[3], 0, 1, -40, 40);
    scale1 = ofMap(dna.genes[4], 0, 1, -0.1, 0.2);
    scale2 = ofMap(dna.genes[5], 0, 1, -0.2, 0.2);
    scale3 = ofMap(dna.genes[6], 0, 1, -0.2, 0.2);
    rot1 = ofMap(dna.genes[7], 0, 1, -2, 2);
    rot2 = ofMap(dna.genes[8], 0, 1, -2, 2);
    rot3 = ofMap(dna.genes[9], 0, 1, -2, 2);

    // setup noise
    for (int x = 0; x < 50; x++){
        for (int y = 0; y < 50; y++){
            noiseSeeds[x][y] = ofRandom(0, 1000);
        }
    }
}
void Cactus::path(float t){

    ofPushMatrix();
    ofRotateDeg(rot1, 0, 1, .3f);

    // Cactus left branch
    ofPushMatrix();
    ofTranslate(0,pos1);
    ofRotateDeg(rot3, 0, 1, .3f);
    ofScale(1, 1 + scale3);
        ofBeginShape();
        ofVertex(modXY(710, 540, t));
        ofVertex(modXY(690, 520, t));
        ofVertex(modXY(661, 514, t));
        ofVertex(modXY(644, 499, t));
        ofVertex(modXY(624, 475, t));
        ofVertex(modXY(603, 426, t));
        ofVertex(modXY(592, 366, t));
        ofVertex(modXY(584, 297, t));
        ofVertex(modXY(581, 235, t));
        ofVertex(modXY(588, 146, t));
        ofVertex(modXY(603, 46, t));
        ofVertex(modXY(608, 24, t));
        ofVertex(modXY(627, 16, t));
        ofVertex(modXY(644, 20, t));
        ofVertex(modXY(653, 36, t));
        ofVertex(modXY(656, 91, t));
        ofVertex(modXY(655, 197, t));
        ofVertex(modXY(657, 303, t));
        ofVertex(modXY(670, 388, t));
        ofVertex(modXY(689, 426, t));
        ofVertex(modXY(710, 400, t));
        ofEndShape();
    ofPopMatrix();

    // Cactus right branch
    ofPushMatrix();
    ofTranslate(0,pos2);
    ofRotateDeg(rot2, 0, 1, .3f);
    ofScale(1, 1 + scale2);
        ofBeginShape();
        ofVertex(modXY(781, 568, t));
        ofVertex(modXY(798, 547, t));
        ofVertex(modXY(805, 496, t));
        ofVertex(modXY(805, 354, t));
        ofVertex(modXY(803, 296, t));
        ofVertex(modXY(791, 184, t));
        ofVertex(modXY(787, 112, t));
        ofVertex(modXY(791, 78, t));
        ofVertex(modXY(802, 62, t));
        ofVertex(modXY(821, 60, t));
        ofVertex(modXY(844, 74, t));
        ofVertex(modXY(856, 116, t));
        ofVertex(modXY(875, 304, t));
        ofVertex(modXY(877, 423, t));
        ofVertex(modXY(872, 541, t));
        ofVertex(modXY(857, 616, t));
        ofVertex(modXY(834, 659, t));
        ofVertex(modXY(813, 682, t));
        ofVertex(modXY(785, 689, t));
        ofEndShape();
    ofPopMatrix();

    // Cactus main
    ofPushMatrix();
        ofScale(1, 1 + scale1);
        ofBeginShape();
        ofVertex(modXY(703, 732, t));
        ofVertex(modXY(699, 674, t));
        ofVertex(modXY(691, 582, t));
        ofVertex(modXY(690, 520, t));
        ofVertex(modXY(689, 426, t));
        ofVertex(modXY(689, 339, t));
        ofVertex(modXY(692, 226, t));
        ofVertex(modXY(707, 177, t));
        ofVertex(modXY(725, 161, t));
        ofVertex(modXY(749, 163, t));
        ofVertex(modXY(767, 178, t));
        ofVertex(modXY(775, 203, t));
        ofVertex(modXY(777, 328, t));
        ofVertex(modXY(781, 568, t));
        ofVertex(modXY(785, 689, t));
        ofVertex(modXY(785, 735, t));
        ofVertex(modXY(786, 899, t));
        ofVertex(modXY(785, 910, t));
        ofVertex(modXY(749, 905, t));
        ofVertex(modXY(710, 761, t));
        ofEndShape();
    ofPopMatrix();

    ofPopMatrix();
}

//--------------------------------------------------------
// Draws the Cactus
void Cactus::draw(){
    counter = 0;
    for (float t = 1; t > 0; t -= 0.1f) {
        ofColor ColorY = ofColor(80,ofClamp(150+color1,0,255), ofClamp(100+color2, 0, 255));
        ofColor ColorX = ColorY;
        ColorX.setBrightness(ColorY.getBrightness() * shadow);
        ofSetColor(ColorX.getLerped(ColorY, t));
        ofPushMatrix();
        ofScale(ofMap(t, 0, 1, 1, xScale), ofMap(t, 0, 1, 1, yScale));
        path(t);
        ofPopMatrix();
    }
}

vec2 Cactus::modXY(float a, float b, float t) {

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

float Cactus::addNoise()
{
    float randomness = ofNoise(ofNoise(noiseSeeds[(int)ofRandom(0, 50)][(int)ofRandom(0, 50)])) * noise * ofRandom(1);
    if (ofRandom(1) > .5f) randomness *= -1;
    return randomness;
}

void Cactus::getParameters(float _multiplierX, float _xScale, float _multiplierY, float _yScale, float _shadow, float _noise , bool _debug){
    multiplierX = _multiplierX;
    xScale = _xScale;
    multiplierY = _multiplierY;
    yScale = _yScale;
    shadow = _shadow;
    noise = _noise;
    debug = _debug;
}

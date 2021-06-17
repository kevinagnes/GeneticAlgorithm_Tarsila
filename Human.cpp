#include "Human.h"


#define GENE_SIZE 1
//-------------------------------------------------------
Human::Human(){
    geneSize = GENE_SIZE;
    fitness = 0;
}
//-------------------------------------------------------
void Human::setup(DNA _dna){
    dna = _dna;
    geneSize = dna.geneSize;
    numOfGenes = dna.numOfGenes;
    calcPhenotype();
}
//-------------------------------------------------------
void Human::setup(int _numOfGenes)
{

    numOfGenes = _numOfGenes;
    dna.setup(numOfGenes, geneSize);
    calcPhenotype();
}

void Human::calcPhenotype(){
    //decode the genes into variables for drawing
    colorHair = ofMap(dna.genes[0], 0, 1, 0, 360);
    scaleHair = ofMap(dna.genes[1], 0, 1, -0.2, 0.2);
    rotateHair = ofMap(dna.genes[2], 0, 1, -3, 3);
    colorBody = ofMap(dna.genes[3], 0, 1, -15, 15);
    colorBrightness = ofMap(dna.genes[4], 0, 1, .7f, 1.2f);
    scaleNailX = ofMap(dna.genes[5], 0, 1, -20, 20);
    scaleNailY = ofMap(dna.genes[6], 0, 1, -20, 20);
    nail1 = ofMap(dna.genes[7], 0, 1, -20, 150);
    nail2 = ofMap(dna.genes[8], 0, 1, -20, 150);
    nail3 = ofMap(dna.genes[9], 0, 1, -20, 150);

    // setup noise
    for (int x = 0; x < 50; x++){
        for (int y = 0; y < 50; y++){
            noiseSeeds[x][y] = ofRandom(0, 1000);
        }
    }
}
void Human::pathHair(){
    ofColor ColorX,ColorY;
    float hue,sat,lvl;
    // HAIR
    ColorY = ofColor(90, 34, 43);
    ColorY.setHueAngle(colorHair);
    ColorX= ColorY;
    ColorX.setBrightness(ColorY.getBrightness() * shadow);
    ofPushMatrix();
    ofScale(1, 1 + scaleHair);
    ofRotateDeg(rotateHair);
    for (float t = 1; t > 0; t -= 0.1f) {
        ofSetColor(ColorX.getLerped(ColorY, t));
        ofPushMatrix();
        ofScale(ofMap(t, 0, 1, 1, xScale), ofMap(t, 0, 1, 1, yScale));
        ofBeginShape();
        ofVertex(modXY(325, 111, t));
        ofVertex(modXY(331, 90, t));
        ofVertex(modXY(345, 82, t));
        ofVertex(modXY(373, 74, t));
        ofVertex(modXY(378, 75, t));
        ofVertex(modXY(386, 81, t));
        ofVertex(modXY(385, 91, t));
        ofVertex(modXY(380, 101, t));
        ofVertex(modXY(371, 110, t));
        ofVertex(modXY(339, 119, t));
        ofEndShape();
        ofPopMatrix();
    }
    ofPopMatrix();
}
void Human::pathArmSmall(){
    ofColor ColorX,ColorY;
    float hue,sat,lvl;
    // ARM SMALL
    ColorY = ofColor(194, 131, 62);
    ColorY.getHsb(hue,sat,lvl);
    ColorY.setHsb(hue+colorBody,sat+colorBody,lvl);
    ColorY.setBrightness(ColorY.getBrightness() * colorBrightness);
    ColorX= ColorY;
    ColorX.setBrightness(ColorY.getBrightness() * shadow);
    for (float t = 1; t > 0; t -= 0.1f) {
        ofPushMatrix();
        ofScale(ofMap(t, 0, 1, 1, xScale), ofMap(t, 0, 1, 1, yScale));
        ofSetColor(ColorX.getLerped(ColorY, t));
        ofBeginShape();
        ofVertex(modXY(347, 119, t));
        ofVertex(modXY(364, 145, t));
        ofVertex(modXY(371, 154, t));
        ofVertex(modXY(379, 212, t));
        ofVertex(modXY(379, 255, t));
        ofVertex(modXY(381, 267, t));
        ofVertex(modXY(400, 281, t));
        ofVertex(modXY(416, 263, t));
        ofVertex(modXY(420, 247, t));
        ofVertex(modXY(403, 194, t));
        ofVertex(modXY(389, 148, t));
        ofVertex(modXY(382, 126, t));
        ofVertex(modXY(368, 102, t));
        ofVertex(modXY(357, 106, t));
        ofEndShape();
        ofPopMatrix();
    }
}
void Human::pathBody(){
    ofColor ColorX,ColorY;
    float hue,sat,lvl;
    // BODY
    ColorY = ofColor(202, 136, 86);
    ColorY.getHsb(hue,sat,lvl);
    ColorY.setHsb(hue+colorBody,sat+colorBody,lvl);
    ColorY.setBrightness(ColorY.getBrightness()*colorBrightness);
    ColorX= ColorY;
    ColorX.setBrightness(ColorY.getBrightness() * shadow);
    for (float t = 1; t > 0; t -= 0.1f) {
        ofPushMatrix();
        ofScale(ofMap(t, 0, 1, 1, xScale), ofMap(t, 0, 1, 1, yScale));
        ofSetColor(ColorX.getLerped(ColorY, t));
        ofBeginShape();
        ofVertex(modXY(178, 847, t));
        ofVertex(modXY(129, 828, t));
        ofVertex(modXY(102, 802, t));
        ofVertex(modXY(83, 764, t));
        ofVertex(modXY(73, 722, t));
        ofVertex(modXY(75, 675, t));
        ofVertex(modXY(102, 570, t));
        ofVertex(modXY(137, 461, t));
        ofVertex(modXY(174, 368, t));
        ofVertex(modXY(232, 257, t));
        ofVertex(modXY(289, 169, t));
        ofVertex(modXY(322, 119, t));
        ofVertex(modXY(331, 103, t));
        ofVertex(modXY(351, 92, t));
        ofVertex(modXY(373, 87, t));
        ofVertex(modXY(377, 98, t));
        ofVertex(modXY(367, 117, t));
        ofVertex(modXY(353, 125, t));
        ofVertex(modXY(337, 136, t));
        ofVertex(modXY(320, 164, t));
        ofVertex(modXY(311, 187, t));
        ofVertex(modXY(278, 375, t));
        ofVertex(modXY(321, 323, t));
        ofVertex(modXY(342, 297, t));
        ofVertex(modXY(369, 278, t));
        ofVertex(modXY(407, 278, t));
        ofVertex(modXY(445, 303, t));
        ofVertex(modXY(463, 335, t));
        ofVertex(modXY(572, 636, t));
        ofVertex(modXY(619, 706, t));
        ofVertex(modXY(681, 745, t));
        ofVertex(modXY(765, 770, t));
        ofVertex(modXY(890, 770, t));
        ofVertex(modXY(906, 769, t));
        ofVertex(modXY(923, 813, t));
        ofVertex(modXY(916, 848, t));
        ofVertex(modXY(905, 863, t));
        ofVertex(modXY(887, 871, t));
        ofVertex(modXY(905, 886, t));
        ofVertex(modXY(921, 910, t));
        ofVertex(modXY(916, 938, t));
        ofVertex(modXY(894, 954, t));
        ofVertex(modXY(875, 954, t));
        ofVertex(modXY(863, 950, t));
        ofVertex(modXY(857, 966, t));
        ofVertex(modXY(847, 970, t));
        ofVertex(modXY(833, 970, t));
        ofVertex(modXY(832, 982, t));
        ofVertex(modXY(819, 991, t));
        ofVertex(modXY(802, 991, t));
        ofVertex(modXY(783, 983, t));
        ofVertex(modXY(776, 992, t));
        ofVertex(modXY(753, 994, t));
        ofVertex(modXY(709, 983, t));
        ofVertex(modXY(696, 977, t));
        ofVertex(modXY(630, 961, t));
        ofVertex(modXY(508, 927, t));
        ofVertex(modXY(480, 908, t));
        ofVertex(modXY(451, 870, t));
        ofVertex(modXY(434, 825, t));
        ofVertex(modXY(438, 769, t));
        ofVertex(modXY(430, 736, t));
        ofVertex(modXY(393, 659, t));
        ofVertex(modXY(353, 567, t)); // end of ass
        ofVertex(modXY(301, 712, t));
        ofVertex(modXY(234, 808, t));
        ofVertex(modXY(215, 832, t));
        ofVertex(modXY(205, 837, t));
        ofVertex(modXY(185, 843, t));
        ofEndShape();
        ofPopMatrix();
    }
}
void Human::pathArmBig(){
    ofColor ColorX,ColorY;
    float hue,sat,lvl;
    // ARM BIG
    ColorY = ofColor(204, 138, 73);
    ColorY.getHsb(hue,sat,lvl);
    ColorY.setHsb(hue+colorBody,sat+colorBody,lvl+colorBody);
    ColorY.setBrightness(ColorY.getBrightness() * colorBrightness);
    ColorX= ColorY;
    ColorX.setBrightness(ColorY.getBrightness() * shadow);
   
    for (float t = 1; t > 0; t -= 0.1f) {
        ofPushMatrix();
        ofScale(ofMap(t, 0, 1, 1, xScale), ofMap(t, 0, 1, 1, yScale));
        ofSetColor(ColorX.getLerped(ColorY, t));
        ofBeginShape();
        ofVertex(modXY(339, 226, t));
        ofVertex(modXY(330, 199, t));
        ofVertex(modXY(324, 188, t));
        ofVertex(modXY(313, 184, t));
        ofVertex(modXY(292, 193, t));
        ofVertex(modXY(282, 200, t));
        ofVertex(modXY(251, 252, t));
        ofVertex(modXY(205, 378, t));
        ofVertex(modXY(169, 508, t));
        ofVertex(modXY(159, 570, t));
        ofVertex(modXY(163, 600, t));
        ofVertex(modXY(167, 627, t));
        ofVertex(modXY(191, 713, t));
        ofVertex(modXY(233, 803, t));
        ofVertex(modXY(246, 846, t));
        ofVertex(modXY(260, 887, t));
        ofVertex(modXY(277, 917, t));
        ofVertex(modXY(310, 965, t));
        ofVertex(modXY(358, 988, t));
        ofVertex(modXY(388, 986, t));
        ofVertex(modXY(393, 977, t));
        ofVertex(modXY(402, 990, t));
        ofVertex(modXY(420, 994, t));
        ofVertex(modXY(432, 986, t));
        ofVertex(modXY(431, 978, t));
        ofVertex(modXY(445, 989, t));
        ofVertex(modXY(458, 988, t));
        ofVertex(modXY(466, 977, t));
        ofVertex(modXY(462, 965, t));
        ofVertex(modXY(469, 960, t));
        ofVertex(modXY(471, 938, t));
        ofVertex(modXY(467, 892, t));
        ofVertex(modXY(455, 863, t));
        ofVertex(modXY(442, 843, t));
        ofVertex(modXY(416, 827, t));
        ofVertex(modXY(381, 812, t));
        ofVertex(modXY(355, 806, t));
        ofVertex(modXY(338, 792, t));
        ofVertex(modXY(314, 750, t));
        ofVertex(modXY(283, 660, t));
        ofVertex(modXY(270, 595, t));
        ofVertex(modXY(270, 560, t));
        ofVertex(modXY(275, 523, t));
        ofVertex(modXY(296, 418, t));
        ofVertex(modXY(321, 326, t));
        ofVertex(modXY(334, 268, t));
        ofVertex(modXY(338, 238, t));
        ofEndShape();
        ofPopMatrix();
    }
}
void Human::details(){

    // FACE
    ofSetColor(45, 44, 23);
    ofDrawEllipse(modXY(355, 97), 14, 5); // left eye
    ofDrawTriangle(modXY(364, 101), modXY(373, 100), modXY(370, 109)); // right eye
    ofSetColor(45, 44, 23, 150);
    ofDrawTriangle(modXY(366, 101), modXY(370, 114), modXY(351, 122));

    // NAILS
    float moveNailsX = ofMap(multiplierX, 0, 0.2f, 0, -100);
    float moveNailsY = ofMap(multiplierY, 0, 0.2f, 0, -120);
    ofColor nailColor = ofColor(ofClamp(80 + nail1, 0, 255), ofClamp(4 + nail2, 0, 255), ofClamp(23 + nail3, 0, 255));
    for (int i = 0; i < 5; i++){
        ofPushMatrix();
        ofColor newNail = nailColor;
        newNail.setBrightness(nailColor.getBrightness()*ofMap(i,0,4,.75f,1)); 
        ofSetColor(newNail, ofMap(i, 0, 4, 75, 185));
        ofTranslate(i * 3, 0);
        ofDrawEllipse(modXY(880 + moveNailsX, 808 + moveNailsY), 87 + scaleNailX, 65 + scaleNailY);
        ofDrawEllipse(modXY(900 + moveNailsX, 916 + moveNailsY), 42 + scaleNailX, 38 + scaleNailY);
        ofDrawEllipse(modXY(847 + moveNailsX, 945 + moveNailsY), 30 + scaleNailX, 25 + scaleNailY);
        ofDrawEllipse(modXY(815 + moveNailsX, 972 + moveNailsY), 25 + scaleNailX, 20 + scaleNailY);
        ofDrawEllipse(modXY(771 + moveNailsX, 986 + moveNailsY), 14 + scaleNailX, 10 + scaleNailY);
        ofPopMatrix();
    }
}

//--------------------------------------------------------
// Draws the Human
void Human::draw(){  
    counter = 0;

    pathHair(); ////////////////// 1
    // movement for small arm
    ofPushMatrix();
        ofRotateDeg(sin(ofDegToRad(ofGetFrameNum())) * 25, 200, 140, 0);
        pathArmSmall();  ///////// 2
    ofPopMatrix();
    pathBody(); ////////////////// 3
    details(); /////////////////// 4
    // movement for big arm
    ofPushMatrix();
        ofRotateDeg(sin(ofDegToRad(ofGetFrameNum())) * 15, 160, 100, 0);
        pathArmBig(); //////////// 5
    ofPopMatrix();
}

vec2 Human::modXY(float a, float b, float t) {

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

float Human::addNoise()
{
    float randomness = ofNoise(ofNoise(noiseSeeds[(int)ofRandom(0, 50)][(int)ofRandom(0, 50)])) * noise * ofRandom(1);
    if (ofRandom(1) > .5f) randomness *= -1;
    return randomness;
}

void Human::getParameters(float _multiplierX, float _xScale, float _multiplierY, float _yScale, float _shadow, float _noise, bool _debug) {
    multiplierX = _multiplierX;
    xScale = _xScale;
    multiplierY = _multiplierY;
    yScale = _yScale;
    shadow = _shadow;
    noise = _noise;
    debug = _debug;
}

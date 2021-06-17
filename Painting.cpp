#include "Painting.h"

//-------------------------------------------------------
Painting::Painting() {
}

// receives state from ofApp
void Painting::requestState(int _state) {
    state = _state;
}
//-------------------------------------------------------
void Painting::setup(float m, int _num)
{
    
    num = _num;
    mutationRate = m;
    cactuses.clear();
    humans.clear();
    backgrounds.clear();

    // font setup
    font1.load("pixelsix10.ttf", 100);

    for (int x = 0; x < num; x++) {
        Background tempBackground;
        tempBackground.setup(8);
        backgrounds.push_back(tempBackground);
        Cactus tempCactus;
        tempCactus.setup(10);
        cactuses.push_back(tempCactus);
        Human tempHuman;
        tempHuman.setup(10);
        humans.push_back(tempHuman);
    }

}
//-------------------------------------------------------
// Generate a mating pool
void Painting::selection() {
    // Clear the vector
    matingPoolCactus.clear();
    matingPoolHuman.clear();
    matingPoolBackground.clear();
    
    // Calculate total fitness of whole population
    // based on what state the program is running
    if (state == 0) {
        float maxFitnessBackground = 0;
        for (int i = 0; i < backgrounds.size(); i++) {
            maxFitnessBackground += backgrounds[i].fitness;
        }
        for (int i = 0; i < backgrounds.size(); i++) {
            float fitnessNormal = 1+ ofMap(backgrounds[i].fitness, 0, maxFitnessBackground, 0, 1);
            int n = (int)(fitnessNormal * 100);  // Arbitrary multiplier
            for (int j = 0; j < n; j++) {
                matingPoolBackground.push_back(backgrounds[i]);
            }
        }
    }
    else if (state == 1) {
        float maxFitnessCactus = 0;
        for (int i = 0; i < cactuses.size(); i++) {
            maxFitnessCactus += cactuses[i].fitness;
        }
        for (int i = 0; i < cactuses.size(); i++) {
            float fitnessNormal = 1 + ofMap(cactuses[i].fitness, 0, maxFitnessCactus, 0, 1);
            int n = (int)(fitnessNormal * 100);  // Arbitrary multiplier
            for (int j = 0; j < n; j++) {
                matingPoolCactus.push_back(cactuses[i]);
            }
        }
    }
    else if (state == 2) {
        float maxFitnessHuman = 0;
        for (int i = 0; i < humans.size(); i++) {
            maxFitnessHuman += humans[i].fitness;
        }
        for (int i = 0; i < humans.size(); i++) {
            float fitnessNormal = 1 + ofMap(humans[i].fitness, 0, maxFitnessHuman, 0, 1);
            int n = (int)(fitnessNormal * 100);  // Arbitrary multiplier
            for (int j = 0; j < n; j++) {
                matingPoolHuman.push_back(humans[i]);
            }
        }
    }
    
}
// selectes highest fitness object for the final painting
int Painting::getHigherFitness(int object) {
    int highestNumber = 0;
    int selected = 0;
    for (int i = 0; i < num; i++){
        if      (object == 0) {
            if (backgrounds[i].fitness > highestNumber) {
                highestNumber = backgrounds[i].fitness;
                selected = i;
            }
        }
        else if (object == 1) {
            if (cactuses[i].fitness > highestNumber) {
                highestNumber = cactuses[i].fitness;
                selected = i;
            }
        }
        else if (object == 2) {
            if (humans[i].fitness > highestNumber) {
                highestNumber = humans[i].fitness;
                selected = i;
            }
        }
    }
    return selected;
}
//------------------------------------------------------------
// Create a new generation
void Painting::draw(){

    // if final painting state display highest fitness object or the first one
    if (state == 3) {
        float scaler = 1.0f;
        ofPushMatrix();
        ofScale(scaler);
        backgrounds[getHigherFitness(0)].draw();
        cactuses[getHigherFitness(1)].draw();
        humans[getHigherFitness(2)].draw();
        ofPopMatrix();
    }  
    else {
        // each following state adds fitness and select the next breeding 
        // because objects are paths I had to re-scale and position them to fit the option canvas
        float scaler = .30f;
        ofPushMatrix();
        ofScale(scaler);
        ofTranslate(0,200);
        for(int i =0; i < num; i++){
            int xOffset = 100;
            if (state != 1) xOffset *= 3;
            ofPushMatrix();
            if (i <3) ofTranslate(xOffset +(ofGetWidth() / 3 + 550)*i, -150);
            else if (i >=3 && i<6) ofTranslate(xOffset + (ofGetWidth() / 3 + 550) * (i-3), 900);
            else if (i >= 6 && i < 9) ofTranslate(xOffset + (ofGetWidth() / 3 + 550) * (i - 6), 2000);
            
            // background
            if (state == 0) {
                backgrounds[i].draw();
                ofSetColor(0,50,0);
                string out = ofToString(i) + ":" + ofToString(backgrounds[i].fitness);
                font1.drawString(out, 150 - font1.stringWidth(out) * 0.5f, 150);
            }
            // cactus
            if (state == 1) {
                cactuses[i].draw();
                ofSetColor(ofColor::lightGreen);
                string out = ofToString(i) + ":" + ofToString(cactuses[i].fitness);
                font1.drawString(out, 350 - font1.stringWidth(out) * 0.5f, 150);
            }
            // human
            if (state == 2) {
                humans[i].draw();
                ofSetColor(ofColor::lightGreen);
                string out = ofToString(i) + ":" + ofToString(humans[i].fitness);
                font1.drawString(out, 150 - font1.stringWidth(out) * 0.5f, 150);
            }
            ofPopMatrix();
        }
        ofPopMatrix();
    }
}
//------------------------------------------------------------
// Create a new generation
void Painting::generate() {

    // background
    if (state == 0) {
        for (int i = 0; i < backgrounds.size(); i++) {
            int a = int(ofRandom(matingPoolBackground.size()));
            int b = int(ofRandom(matingPoolBackground.size()));
            Background partnerA = matingPoolBackground[a];
            Background partnerB = matingPoolBackground[b];     
            DNA childDNA = partnerA.dna.crossover(partnerB.dna);
            backgrounds[i].calcPhenotype();
            childDNA.mutate(mutationRate);
            Background child;
            child.setup(childDNA);
            backgrounds[i] = child;
            backgrounds[i].calcPhenotype();

        }
    }
    // cactus
    else if (state == 1) {
        for (int i = 0; i < cactuses.size(); i++) {
            int a = int(ofRandom(matingPoolCactus.size()));
            int b = int(ofRandom(matingPoolCactus.size()));
            Cactus partnerA = matingPoolCactus[a];
            Cactus partnerB = matingPoolCactus[b];
            DNA childDNA = partnerA.dna.crossover(partnerB.dna);
            cactuses[i].calcPhenotype();
            childDNA.mutate(mutationRate);
            Cactus child;
            child.setup(childDNA);
            cactuses[i] = child;
            cactuses[i].calcPhenotype();
        }
    }
    // human
    else if (state == 2) {
        for (int i = 0; i < humans.size(); i++) {
            int a = int(ofRandom(matingPoolHuman.size()));
            int b = int(ofRandom(matingPoolHuman.size()));
            Human partnerA = matingPoolHuman[a];
            Human partnerB = matingPoolHuman[b];
            DNA childDNA = partnerA.dna.crossover(partnerB.dna);
            humans[i].calcPhenotype();
            childDNA.mutate(mutationRate);
            Human child;
            child.setup(childDNA);
            humans[i] = child;
            humans[i].calcPhenotype();
        }
    }

}
//------------------------------------------------------------
void Painting::pick(int n){
    // background
    if (state == 0) {
        if (n >= backgrounds.size()) return;
        backgrounds[n].fitness++;
    }
    // cactus
    else if (state == 1) {
        if (n >= cactuses.size()) return;
        cactuses[n].fitness++;
    }
    // human
    else if (state == 2) { 
        if (n >= humans.size()) return;
        humans[n].fitness++; 
    }
}

// function to get parameters from ofApp and send to each object for the final draw
void Painting::requestParameters(float multiplierX, float xScale, float multiplierY, float yScale, float shadow, float noise, bool _debug) {
    for (int i = 0; i < num; i++) {
        cactuses[i].getParameters(multiplierX, xScale, multiplierY, yScale, shadow, noise, _debug);
        humans[i].getParameters(multiplierX, xScale, multiplierY, yScale, shadow, noise, _debug);
        backgrounds[i].getParameters(multiplierX, xScale, multiplierY, yScale, shadow, noise, _debug);
    }
}
    

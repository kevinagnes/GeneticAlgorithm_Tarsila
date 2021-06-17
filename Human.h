#pragma once
#include "ofMain.h"
#include "DNA.h"
using namespace glm;


class Human {

	public:

        // base functions
		Human();
		void setup(DNA _dna);
		void setup(int _numOfGenes);
		void draw();
        void calcPhenotype();
        float getFitness ();
        void mutate(float mutationRate);  
        Human crossover(Human partner);
        DNA dna;
        int numOfGenes, geneSize;
        float fitness;
        float seed = 0;
        ofBaseApp getm;
        
        // global modifier functions
        vec3 vec3mod(float x, float y, float z);
        float noiseSeeds[50][50];
        vec2 modXY(float a, float b, float t = 0);
        float addNoise();
        void getParameters(float multiplierX, float xScale, float multiplierY, float yScale, float shadow, float noise, bool _debug);

        // exclusive functions
        void pathHair();
        void pathArmSmall();
        void pathBody();
        void pathArmBig();
        void details();
        
        // genetic variables
        float scaleHair, rotateHair, scaleNailX, scaleNailY, colorBrightness, skinBrightness;
        int colorHair, colorBody, nail1, nail2, nail3;

        // global variables
        float multiplierX, xScale, multiplierY, yScale, shadow, noise;
        int counter;
        bool debug = false;
};

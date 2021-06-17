#pragma once
#include "ofMain.h"
#include "DNA.h"
using namespace glm;


class Background {

	public:

        // base functions
		Background();
		void setup(DNA _dna);
		void setup(int _numOfGenes);
		void draw();
        void calcPhenotype();
        float getFitness ();
        void mutate(float mutationRate);
        Background crossover(Background partner);
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
        void mountains();
        void sun();
        void bkg();
        
        // genetic variables
        float scaleHair, rotateHair, scale3;
        int colorHair, colorBody, totalHeight;
        float skyHue, skyRes, sunRot, sunSize, mult1, mult2, mult3;

        // global variables
        float multiplierX,xScale, multiplierY, yScale,shadow,noise;
        bool debug = false;
        int counter= 0;
};

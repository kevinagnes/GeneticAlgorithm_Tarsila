#pragma once
#include "ofMain.h"
#include "DNA.h"
using namespace glm;


class Cactus {

	public:

        // base functions
		Cactus();
		void setup(DNA _dna);
		void setup(int _numOfGenes);
		void draw();
        void calcPhenotype();
        float getFitness ();   
        void mutate(float mutationRate);    
        Cactus crossover(Cactus partner);
		DNA dna;
		int numOfGenes, geneSize;
        float fitness;
        float seed = 0;
        ofBaseApp getm;

        // global modifier functions
        vec3 vec3mod(float x, float y, float z);
        float noiseSeeds[50][50];
        vec2 modXY(float a, float b, float t);
        float addNoise();
        void getParameters(float multiplierX, float xScale, float multiplierY, float yScale, float shadow, float noise, bool _debug);

        // exclusive functions
        void path(float t);
        
        // genetic variables
        float pos1,pos2,scale1,scale2,scale3,rot1,rot2,rot3;
        int color1,color2;

        // global variables
        float multiplierX,xScale, multiplierY, yScale,shadow,noise;
        int counter;
        bool debug = false;
};

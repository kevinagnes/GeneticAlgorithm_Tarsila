#pragma once
#include "ofMain.h"
#include "Cactus.h"
#include "Human.h"
#include "Background.h"

class Painting{

  public:
    Painting();
    void setup(float m, int _num);
    void selection();
    void generate();
    void draw();
    void pick(int n);
    void requestParameters(float multiplierX, float xScale, float multiplierY, float yScale, float shadow, float noise, bool _debug);
    void requestState(int _state);

    float mutationRate;  
    vector<Cactus> cactuses;      
    vector<Cactus> matingPoolCactus;  
    vector<Human> humans;
    vector<Human> matingPoolHuman;
    vector<Background> backgrounds;
    vector<Background> matingPoolBackground;

    // function that selectes final object for painting
    int getHigherFitness(int object);

    // custom font
    ofTrueTypeFont font1;
    
    int num;
    int state;
};

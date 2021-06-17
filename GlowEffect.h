//
//  GlowEffect.h
//  Glow
//
//  Created by nomura on 2014/03/18.
//
//

#ifndef __Glow__GlowEffect__
#define __Glow__GlowEffect__

#include "ofMain.h"

class GlowEffect {
public:
    GlowEffect();
    void begin(float glowAmount_, float blurSize_);
    void end();
    void draw();
    
private:
    ofShader shaderX;
    ofShader shaderY;
    ofFbo fbo1;
    ofFbo fboX;
    
    float glowAmount;
    int blurSize;
    
    void makeShaders();
};

#endif /* defined(__Glow__GlowEffect__) */

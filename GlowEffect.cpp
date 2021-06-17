//
//  GlowEffect.cpp
//  Glow
//
//  Created by nomura on 2014/03/18.
//
//

#include "GlowEffect.h"

#define STR(A) #A

GlowEffect::GlowEffect() {
    makeShaders();
    
    ofFbo::Settings s;
    s.width = ofGetWidth();
    s.height = ofGetHeight();
    s.internalformat = GL_RGBA;
    fbo1.allocate(s);
    fboX.allocate(s);
    
    fbo1.begin();
    ofClear(0);
    fbo1.end();
    
    fboX.begin();
    ofClear(0);
    fboX.end();
}

void GlowEffect::begin(float glowAmount_, float blurSize_) {
    glowAmount = glowAmount_;
    blurSize = blurSize_;
    fbo1.begin();
}

void GlowEffect::end() {
    fbo1.end();
    fboX.begin();
    shaderX.begin();
    shaderX.setUniform1f("glowAmount", glowAmount);
    shaderX.setUniform1f("blurSize", blurSize);
    fbo1.draw(0, 0);
    shaderX.end();
    fboX.end();
}

void GlowEffect::draw() {   
    shaderY.begin();
    shaderY.setUniform1f("glowAmount", glowAmount);
    shaderY.setUniform1f("blurSize", blurSize);
    fboX.draw(0, 0);
    shaderY.end();
}


//----------------------------------------
#pragma mark - private functions

void GlowEffect::makeShaders() {
    string vertexShaderStr = STR(
        uniform float time;
        void main() {
            gl_TexCoord[0] = gl_MultiTexCoord0;
            gl_Position = ftransform();
        }
    );

    string fragmentShaderStrTemplate = STR(
        uniform sampler2DRect tex0;
        uniform float glowAmount;
        uniform float blurSize;
        void main() {
            float x = gl_TexCoord[0].x;
            float y = gl_TexCoord[0].y;
        
            vec4 vsum = vec4(0, 0, 0, 0);
        
            if (blurSize > 0.0) {
                float sum = 0.0;
                for (float i=-blurSize; i<blurSize; i+=blurSize/20.0+1.0) {
                    float scale = smoothstep(1.0, 0.0, abs(i)/blurSize);
                    vsum += texture2DRect(tex0, vec2(%%s%%)) * scale;
                    sum += scale;
                }
                vsum /= sum;
                vsum *= glowAmount;
            } else {
                vsum = texture2DRect(tex0, vec2(x, y));
                vsum *= max(glowAmount, 1.0);
            }
            gl_FragColor = vsum;
        }
    );
    string fragShaderXStr = fragmentShaderStrTemplate;
    string fragShaderYStr = fragmentShaderStrTemplate;    
    ofStringReplace(fragShaderXStr, "%%s%%", "x+i, y");
    ofStringReplace(fragShaderYStr, "%%s%%", "x, y+i");
    
    shaderX.setupShaderFromSource(GL_VERTEX_SHADER, vertexShaderStr);
    shaderX.setupShaderFromSource(GL_FRAGMENT_SHADER, fragShaderXStr);
    shaderX.linkProgram();

    shaderY.setupShaderFromSource(GL_VERTEX_SHADER, vertexShaderStr);
    shaderY.setupShaderFromSource(GL_FRAGMENT_SHADER, fragShaderYStr);
    shaderY.linkProgram();
}






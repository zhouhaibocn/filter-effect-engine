//
// Created by zhouhaibo on 2017/9/11.
//

#include "lordkelvin_filter.h"

static ConstString Lordkelvin_FSH = GLES_SHADER_STRING_PRECISION_H(
    varying vec2 textureCoordinate;
    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture1;

    void main() {
        vec3 texel = texture2D(inputImageTexture, textureCoordinate).rgb;

        vec2 lookup;
        lookup.y = .5;

        lookup.x = texel.r;
        texel.r = texture2D(inputImageTexture1, lookup).r;

        lookup.x = texel.g;
        texel.g = texture2D(inputImageTexture1, lookup).g;

        lookup.x = texel.b;
        texel.b = texture2D(inputImageTexture1, lookup).b;

        gl_FragColor = vec4(texel, 1.0);
    }
);

LordkelvinFilter::LordkelvinFilter() {

}

LordkelvinFilter::~LordkelvinFilter() {

}

void LordkelvinFilter::init(FilterConfig *filterConfig) {
        mFragmentShader = Lordkelvin_FSH;
        MultiInputFilter::init(filterConfig);
}
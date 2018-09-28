//
// Created by zhouhaibo on 2017/9/11.
//

#include "hudson_filter.h"

static ConstString Hudson_FSH = GLES_SHADER_STRING_PRECISION_H(
    varying vec2 textureCoordinate;
    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture1; //blowout;
    uniform sampler2D inputImageTexture2; //overlay;
    uniform sampler2D inputImageTexture3; //map

    void main() {
        vec4 texel = texture2D(inputImageTexture, textureCoordinate);
        vec3 bbTexel = texture2D(inputImageTexture1, textureCoordinate).rgb;

        texel.r = texture2D(inputImageTexture2, vec2(bbTexel.r, texel.r)).r;
        texel.g = texture2D(inputImageTexture2, vec2(bbTexel.g, texel.g)).g;
        texel.b = texture2D(inputImageTexture2, vec2(bbTexel.b, texel.b)).b;

        vec4 mapped;
        mapped.r = texture2D(inputImageTexture3, vec2(texel.r, .16666)).r;
        mapped.g = texture2D(inputImageTexture3, vec2(texel.g, .5)).g;
        mapped.b = texture2D(inputImageTexture3, vec2(texel.b, .83333)).b;
        mapped.a = 1.0;

        gl_FragColor = mapped;
    }
);


HudsonFilter::HudsonFilter() {

}

HudsonFilter::~HudsonFilter() {

}

void HudsonFilter::init(FilterConfig *filterConfig) {
        mFragmentShader = Hudson_FSH;
        MultiInputFilter::init(filterConfig);
}
//
// Created by zhouhaibo on 2017/9/11.
//

#include "xproll_filter.h"

static ConstString Xproll_FSH = GLES_SHADER_STRING_PRECISION_H(
    varying vec2 textureCoordinate;
    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture1; //map
    uniform sampler2D inputImageTexture2; //vigMap

    void main() {
        vec3 texel = texture2D(inputImageTexture, textureCoordinate).rgb;
        vec2 tc = (2.0 * textureCoordinate) - 1.0;
        float d = dot(tc, tc);
        vec2 lookup = vec2(d, texel.r);
        texel.r = texture2D(inputImageTexture2, lookup).r;
        lookup.y = texel.g;
        texel.g = texture2D(inputImageTexture2, lookup).g;
        lookup.y = texel.b;
        texel.b    = texture2D(inputImageTexture2, lookup).b;

        vec2 red = vec2(texel.r, 0.16666);
        vec2 green = vec2(texel.g, 0.5);
        vec2 blue = vec2(texel.b, .83333);
        texel.r = texture2D(inputImageTexture1, red).r;
        texel.g = texture2D(inputImageTexture1, green).g;
        texel.b = texture2D(inputImageTexture1, blue).b;

        gl_FragColor = vec4(texel, 1.0);
    }
);


XprollFilter::XprollFilter() {

}

XprollFilter::~XprollFilter() {

}

void XprollFilter::init(FilterConfig *filterConfig) {
        mFragmentShader = Xproll_FSH;
        MultiInputFilter::init(filterConfig);
}
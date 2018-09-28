//
// Created by zhouhaibo on 2017/9/11.
//

#include "walden_filter.h"

static ConstString Walden_FSH = GLES_SHADER_STRING_PRECISION_H(
    varying vec2 textureCoordinate;
    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture1; //map
    uniform sampler2D inputImageTexture2; //vigMap

    void main() {
        vec3 texel = texture2D(inputImageTexture, textureCoordinate).rgb;
        texel = vec3(texture2D(inputImageTexture1, vec2(texel.r, .16666)).r,
                     texture2D(inputImageTexture1, vec2(texel.g, .5)).g,
                     texture2D(inputImageTexture1, vec2(texel.b, .83333)).b);

        vec2 tc = (2.0 * textureCoordinate) - 1.0;
        float d = dot(tc, tc);
        vec2 lookup = vec2(d, texel.r);
        texel.r = texture2D(inputImageTexture2, lookup).r;
        lookup.y = texel.g;
        texel.g = texture2D(inputImageTexture2, lookup).g;
        lookup.y = texel.b;
        texel.b    = texture2D(inputImageTexture2, lookup).b;

        gl_FragColor = vec4(texel, 1.0);
    }
);

WaldenFilter::WaldenFilter() {

}

WaldenFilter::~WaldenFilter() {

}

void WaldenFilter::init(FilterConfig *filterConfig) {
        mFragmentShader = Walden_FSH;
        MultiInputFilter::init(filterConfig);
}
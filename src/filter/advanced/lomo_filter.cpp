//
// Created by zhouhaibo on 2017/9/11.
//

#include "lomo_filter.h"

static ConstString Lomo_FSH = GLES_SHADER_STRING_PRECISION_H(
    varying vec2 textureCoordinate;
    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture1;
    uniform sampler2D inputImageTexture2;

    void main() {
        vec3 texel = texture2D(inputImageTexture, textureCoordinate).rgb;

        vec2 red = vec2(texel.r, 0.16666);
        vec2 green = vec2(texel.g, 0.5);
        vec2 blue = vec2(texel.b, 0.83333);

        texel.rgb = vec3(texture2D(inputImageTexture1, red).r,
                         texture2D(inputImageTexture1, green).g,
                         texture2D(inputImageTexture1, blue).b);

        vec2 tc = (2.0 * textureCoordinate) - 1.0;
        float d = dot(tc, tc);
        vec2 lookup = vec2(d, texel.r);
        texel.r = texture2D(inputImageTexture2, lookup).r;
        lookup.y = texel.g;
        texel.g = texture2D(inputImageTexture2, lookup).g;
        lookup.y = texel.b;
        texel.b = texture2D(inputImageTexture2, lookup).b;

        gl_FragColor = vec4(texel, 1.0);
    }
);


LomoFilter::LomoFilter() {

}

LomoFilter::~LomoFilter() {

}

void LomoFilter::init(FilterConfig *filterConfig) {
        mFragmentShader = Lomo_FSH;
        MultiInputFilter::init(filterConfig);
}
//
// Created by zhouhaibo on 2017/9/11.
//

#include "sutro_filter.h"

static ConstString Sutro_FSH = GLES_SHADER_STRING_PRECISION_H(
    varying vec2 textureCoordinate;
    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture1; //sutroMap;
    uniform sampler2D inputImageTexture2; //sutroMetal;
    uniform sampler2D inputImageTexture3; //softLight
    uniform sampler2D inputImageTexture4; //sutroEdgeburn
    uniform sampler2D inputImageTexture5; //sutroCurves

    void main() {
        vec3 texel = texture2D(inputImageTexture, textureCoordinate).rgb;

        vec2 tc = (2.0 * textureCoordinate) - 1.0;
        float d = dot(tc, tc);
        vec2 lookup = vec2(d, texel.r);
        texel.r = texture2D(inputImageTexture1, lookup).r;
        lookup.y = texel.g;
        texel.g = texture2D(inputImageTexture1, lookup).g;
        lookup.y = texel.b;
        texel.b    = texture2D(inputImageTexture1, lookup).b;

        vec3 rgbPrime = vec3(0.1019, 0.0, 0.0);
        float m = dot(vec3(.3, .59, .11), texel.rgb) - 0.03058;
        texel = mix(texel, rgbPrime + m, 0.32);

        vec3 metal = texture2D(inputImageTexture2, textureCoordinate).rgb;
        texel.r = texture2D(inputImageTexture3, vec2(metal.r, texel.r)).r;
        texel.g = texture2D(inputImageTexture3, vec2(metal.g, texel.g)).g;
        texel.b = texture2D(inputImageTexture3, vec2(metal.b, texel.b)).b;

        texel = texel * texture2D(inputImageTexture4, textureCoordinate).rgb;

        texel.r = texture2D(inputImageTexture5, vec2(texel.r, .16666)).r;
        texel.g = texture2D(inputImageTexture5, vec2(texel.g, .5)).g;
        texel.b = texture2D(inputImageTexture5, vec2(texel.b, .83333)).b;

        gl_FragColor = vec4(texel, 1.0);
    }
);

SutroFilter::SutroFilter() {

}

SutroFilter::~SutroFilter() {

}

void SutroFilter::init(FilterConfig *filterConfig) {
        mFragmentShader = Sutro_FSH;
        MultiInputFilter::init(filterConfig);
}
//
// Created by zhouhaibo on 2017/9/11.
//

#include "brannan_filter.h"

static ConstString Brannan_FSH = GLES_SHADER_STRING_PRECISION_H(
    varying vec2 textureCoordinate;
    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture1;  // process
    uniform sampler2D inputImageTexture2;  // blowout
    uniform sampler2D inputImageTexture3;  // contrast
    uniform sampler2D inputImageTexture4;  // luma
    uniform sampler2D inputImageTexture5;  // screen
    mat3 saturateMatrix = mat3( 1.105150, -0.044850, -0.046000,
                               -0.088050,  1.061950, -0.089200,
                               -0.017100, -0.017100, 1.132900);
    vec3 luma = vec3(.3, .59, .11);

    void main() {
        vec3 texel = texture2D(inputImageTexture, textureCoordinate).rgb;
        vec2 lookup;
        lookup.y = 0.5;
        lookup.x = texel.r;
        texel.r = texture2D(inputImageTexture1, lookup).r;
        lookup.x = texel.g;
        texel.g = texture2D(inputImageTexture1, lookup).g;
        lookup.x = texel.b;
        texel.b = texture2D(inputImageTexture1, lookup).b;
        texel = saturateMatrix * texel;
        vec2 tc = (2.0 * textureCoordinate) - 1.0;
        float d = dot(tc, tc);
        vec3 sampled;
        lookup.y = 0.5;
        lookup.x = texel.r;
        sampled.r = texture2D(inputImageTexture2, lookup).r;
        lookup.x = texel.g;
        sampled.g = texture2D(inputImageTexture2, lookup).g;
        lookup.x = texel.b;
        sampled.b = texture2D(inputImageTexture2, lookup).b;
        float value = smoothstep(0.0, 1.0, d);
        texel = mix(sampled, texel, value);
        lookup.x = texel.r;
        texel.r = texture2D(inputImageTexture3, lookup).r;
        lookup.x = texel.g;
        texel.g = texture2D(inputImageTexture3, lookup).g;
        lookup.x = texel.b;
        texel.b = texture2D(inputImageTexture3, lookup).b;
        lookup.x = dot(texel, luma);
        texel = mix(texture2D(inputImageTexture4, lookup).rgb, texel, .5);
        lookup.x = texel.r;
        texel.r = texture2D(inputImageTexture5, lookup).r;
        lookup.x = texel.g;
        texel.g = texture2D(inputImageTexture5, lookup).g;
        lookup.x = texel.b;
        texel.b = texture2D(inputImageTexture5, lookup).b;
        gl_FragColor = vec4(texel, 1.0);
    }
);

BrannanFilter::BrannanFilter() {

}

BrannanFilter::~BrannanFilter() {

}

void BrannanFilter::init(FilterConfig *filterConfig) {
        mFragmentShader = Brannan_FSH;
        MultiInputFilter::init(filterConfig);
}
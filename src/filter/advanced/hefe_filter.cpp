//
// Created by zhouhaibo on 2017/9/11.
//

#include "hefe_filter.h"

static ConstString Hefe_FSH = GLES_SHADER_STRING_PRECISION_H(
    varying  vec2 textureCoordinate;
    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture1;  // edgeBurn
    uniform sampler2D inputImageTexture2;  // hefeMap
    uniform sampler2D inputImageTexture3;  // hefeGradientMap
    uniform sampler2D inputImageTexture4;  // hefeSoftLight
    uniform sampler2D inputImageTexture5;  // hefeMetal

    void main() {
        vec3 texel = texture2D(inputImageTexture, textureCoordinate).rgb;
        vec3 edge = texture2D(inputImageTexture1, textureCoordinate).rgb;
        texel = texel * edge;  //叠加

        texel = vec3(texture2D(inputImageTexture2, vec2(texel.r, .16666)).r,
                     texture2D(inputImageTexture2, vec2(texel.g, .5)).g,
                     texture2D(inputImageTexture2, vec2(texel.b, .83333)).b);  //色系调整

        vec3 luma = vec3(.30, .59, .11);
        vec3 gradSample = texture2D(inputImageTexture3, vec2(dot(luma, texel), .5)).rgb;
        vec3 final = vec3(texture2D(inputImageTexture4, vec2(gradSample.r, texel.r)).r,
                          texture2D(inputImageTexture4, vec2(gradSample.g, texel.g)).g,
                          texture2D(inputImageTexture4, vec2(gradSample.b, texel.b)).b);

        vec3 metal = texture2D(inputImageTexture5, textureCoordinate).rgb;
        vec3 metaled;
        for(int i = 0; i < 1;i++) {
            texel = vec3(texture2D(inputImageTexture4, vec2(metal.r, texel.r)).r,
                         texture2D(inputImageTexture4, vec2(metal.g, texel.g)).g,
                         texture2D(inputImageTexture4, vec2(metal.b, texel.b)).b);              //overlay 素材叠加
        }
        metaled = texel;

        gl_FragColor = vec4(metaled, 1.0);
    }
);


HefeFilter::HefeFilter() {

}

HefeFilter::~HefeFilter() {

}

void HefeFilter::init(FilterConfig *filterConfig) {
        mFragmentShader = Hefe_FSH;
        MultiInputFilter::init(filterConfig);
}
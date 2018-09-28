package com.me.filterenginedemo.view;

import android.content.Context;
import android.graphics.Bitmap;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;

import com.me.filterengine.FileUtils;
import com.me.filterengine.FilterHandler;
import com.me.filterenginedemo.MeApplication;
import com.me.filterenginedemo.fragment.ConstantFilters;

import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.HashMap;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;

public class ImageFilterView extends GLSurfaceView implements GLSurfaceView.Renderer {

    private static final String TAG = "ImageFilterView";

    private Context mContext;

    private FilterHandler mImageFilter;

    public ImageFilterView(Context context) {
        super(context, null);
    }

    public ImageFilterView(Context context, AttributeSet attributeSet) {
        super(context, attributeSet);
        init(context);
    }

    private void init(Context context) {
        this.setEGLContextClientVersion(2);
        // 抗锯齿
        this.setEGLConfigChooser(new EGLConfigChooser() {
            @Override
            public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display) {
                int attribs[] = {
                        EGL10.EGL_LEVEL, 0,
                        EGL10.EGL_RENDERABLE_TYPE, 4,  // EGL_OPENGL_ES2_BIT
                        EGL10.EGL_COLOR_BUFFER_TYPE, EGL10.EGL_RGB_BUFFER,
                        EGL10.EGL_RED_SIZE, 8,
                        EGL10.EGL_GREEN_SIZE, 8,
                        EGL10.EGL_BLUE_SIZE, 8,
                        EGL10.EGL_DEPTH_SIZE, 16,
                        EGL10.EGL_SAMPLE_BUFFERS, 1,
                        EGL10.EGL_SAMPLES, 4,  // 在这里修改MSAA的倍数，4就是4xMSAA，再往上开程序可能会崩
                        EGL10.EGL_NONE
                };
                EGLConfig[] configs = new EGLConfig[1];
                int[] configCounts = new int[1];
                egl.eglChooseConfig(display, attribs, configs, 1, configCounts);

                if (configCounts[0] == 0) {
                    // Failed! Error handling.
                    return null;
                } else {
                    return configs[0];
                }
            }
        });

        mContext = MeApplication.getContext();
        mImageFilter = new FilterHandler(mContext);

        this.setRenderer(this);
        this.setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
    }

    public void setParams(int type, float intensity) {
        switch (type) {
            case ConstantFilters.BEAUTIFY_WHITEN_MODE:
                mImageFilter.setWhiten(intensity);
                break;
            case ConstantFilters.BEAUTIFY_BLUR_MODE:
                mImageFilter.setBlur(intensity);
                break;
            case ConstantFilters.BEAUTIFY_REDDEN_MODE:
                mImageFilter.setRedden(intensity);
                break;
            case ConstantFilters.ADJUST_BRIGHTNESS_MODE:
                mImageFilter.setBrightness(intensity);
                break;
            case ConstantFilters.ADJUST_CONTRAST_MODE:
                mImageFilter.setContrast(intensity);
                break;
            case ConstantFilters.ADJUST_EXPOSURE_MODE:
                mImageFilter.setExposure(intensity);
                break;
            case ConstantFilters.ADJUST_HUE_MODE:
                mImageFilter.setHue(intensity);
                break;
            case ConstantFilters.ADJUST_SHARPEN_MODE:
                mImageFilter.setSharpen(intensity);
                break;
            case ConstantFilters.ADJUST_SATURATION_MODE:
                mImageFilter.setSaturation(intensity);
                break;
        }
        requestRender();
    }

    public void setFilter(int pos) {
        mImageFilter.setFilter(pos);
        requestRender();
    }


    public interface OnSurfaceCreatedCallback {
        void surfaceCreated();
    }

    protected OnSurfaceCreatedCallback mSurfaceCreatedCallback;

    public void setSurfaceCreatedCallback(OnSurfaceCreatedCallback callback) {
        mSurfaceCreatedCallback = callback;
    }

    public void init(final String fileName) {
        if (fileName != null && mImageFilter != null) {
            queueEvent(new Runnable() {
                @Override
                public void run() {
                    mImageFilter.init(fileName);
                }
            });

        }
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
//        mImageFilter.init(mFileName);

        if (mSurfaceCreatedCallback != null) {
            mSurfaceCreatedCallback.surfaceCreated();
        }
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        mImageFilter.setSize(width, height);
        requestRender();
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        long startTime = System.currentTimeMillis();
        mImageFilter.process(0);
        long endTime = System.currentTimeMillis();
        Log.i(TAG, "filter image spend time : " + (endTime - startTime));

//        mImageFilter.saveImage();
    }


}

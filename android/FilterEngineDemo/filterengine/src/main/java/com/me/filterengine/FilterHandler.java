package com.me.filterengine;

import android.content.Context;
import android.graphics.Bitmap;
import android.util.Log;

import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.HashMap;

public class FilterHandler {
    private static final String TAG = "FilterHandler";

    static {
        System.loadLibrary("ijkffmpeg");
        System.loadLibrary("filter_engine");
    }

    private static final int Beauty_Params_None = 0x00;
    private static final int Beauty_Params_Whitening = 0x01;
    private static final int Beauty_Params_Blur = 0x02;
    private static final int Beauty_Params_Redden = 0x03;

    private static final int Adjust_Params_None = 0x00;
    private static final int Adjust_Params_Brightness = 0x01;
    private static final int Adjust_Params_Contrast = 0x02;
    private static final int Adjust_Params_Exposure = 0x03;
    private static final int Adjust_Params_Hue = 0x04;
    private static final int Adjust_Params_Sharpen = 0x05;
    private static final int Adjust_Params_Saturation = 0x06;

    private long mInstance;
    private Context mContext;
    private HashMap mFilterMap;
    private String mCurrentFileName;

    public FilterHandler(Context context) {
        mContext = context;
        FileUtils.copyFilters(mContext);

        mFilterMap = new HashMap();
        mFilterMap.put(0, "none");
        mFilterMap.put(1, "antique");
        mFilterMap.put(2, "blackcat");
        mFilterMap.put(3, "cool");
        mFilterMap.put(4, "whitecat");
        mFilterMap.put(5, "romance");
        mFilterMap.put(6, "latte");
        mFilterMap.put(7, "sakura");
        mFilterMap.put(8, "emerald");
        mFilterMap.put(9, "evergreen");
        mFilterMap.put(10, "crayon");
        mFilterMap.put(11, "sketch");
        mFilterMap.put(12, "nostalgia");
        mFilterMap.put(13, "healthy");
        mFilterMap.put(14, "sweets");
        mFilterMap.put(15, "tender");
        mFilterMap.put(16, "calm");
        mFilterMap.put(17, "warm");
        mFilterMap.put(18, "sunset");
        mFilterMap.put(19, "sunrise");

        mFilterMap.put(20, "I1977");
        mFilterMap.put(21, "inkwell");
        mFilterMap.put(22, "kelvin");
        mFilterMap.put(23, "nashville");
        mFilterMap.put(24, "lomo");
        mFilterMap.put(25, "valencia");
        mFilterMap.put(26, "walden");
        mFilterMap.put(27, "xproll");
        mFilterMap.put(28, "amaro");
        mFilterMap.put(29, "hudson");
        mFilterMap.put(30, "rise");
        mFilterMap.put(31, "sierra");
        mFilterMap.put(32, "brannan");
        mFilterMap.put(33, "earlybird");
        mFilterMap.put(34, "hefe");
        mFilterMap.put(35, "sutro");
        mFilterMap.put(36, "toaster");

        mFilterMap.put(37, "fairytale");
        mFilterMap.put(38, "amatorka");
        mFilterMap.put(39, "highkey");

        mInstance = nativeCreateInstance();
    }

    public void init(String fileName) {
        nativeInit(mInstance, fileName);
    }

    public void setSize(int width, int height) {
        nativeSetSize(mInstance, width, height);
    }

    public void setWhiten(float intensity) {
        nativeSetBeautyParams(mInstance, Beauty_Params_Whitening, intensity);
    }

    public void setBlur(float intensity) {
        nativeSetBeautyParams(mInstance, Beauty_Params_Blur, intensity);
    }

    public void setRedden(float intensity) {
        nativeSetBeautyParams(mInstance, Beauty_Params_Redden, intensity);
    }

    public void setBrightness(float intensity) {
        nativeSetAdjustParams(mInstance, Adjust_Params_Brightness, intensity);
    }

    public void setContrast(float intensity) {
        nativeSetAdjustParams(mInstance, Adjust_Params_Contrast, intensity);
    }

    public void setExposure(float intensity) {
        nativeSetAdjustParams(mInstance, Adjust_Params_Exposure, intensity);
    }

    public void setHue(float intensity) {
        nativeSetAdjustParams(mInstance, Adjust_Params_Hue, intensity);
    }

    public void setSharpen(float intensity) {
        nativeSetAdjustParams(mInstance, Adjust_Params_Sharpen, intensity);
    }

    public void setSaturation(float intensity) {
        nativeSetAdjustParams(mInstance, Adjust_Params_Saturation, intensity);
    }

    public void setFilter(int filterPos) {
        if(filterPos > 0 && mFilterMap.containsKey(filterPos) ) {
            String filterName = (String) mFilterMap.get(filterPos);
            String absolutePath = FileUtils.getFilterFilePath(mContext, filterName);
            nativeSetFilter(mInstance, absolutePath);
        }

        if (filterPos == 0) {
            nativeSetFilter(mInstance, "n");
        }

        mCurrentFileName = (String) mFilterMap.get(filterPos);
    }

    public int  process(int textureId) {
         return nativeProcess(mInstance, textureId);
    }

    public void destroy() {
        nativeDestory(mInstance);
    }


    public String saveImage() {
        Bitmap bmp = nativeGetResult(mInstance);;
        String path = FileUtils.getFilterFilePath(mContext,"icon");
        String filename = path + "/" + mCurrentFileName + ".jpg";
        return saveBitmap(bmp, filename);
    }

    public String saveBitmap(Bitmap bmp, String filename) {

        Log.e(TAG, "saving Bitmap : " + filename);

        try {
            FileOutputStream fileout = new FileOutputStream(filename);
            BufferedOutputStream bufferOutStream = new BufferedOutputStream(fileout);
            bmp.compress(Bitmap.CompressFormat.JPEG, 100, bufferOutStream);
            bufferOutStream.flush();
            bufferOutStream.close();
        } catch (IOException e) {
            Log.e(TAG, "Err when saving bitmap...");
            e.printStackTrace();
            return null;
        }

        Log.e(TAG, "Bitmap " + filename + " saved!");
        return filename;
    }


    /** native 方法 **/
    private native long nativeCreateInstance();

    private native void nativeInit(long instance, String fileName);

    private native void nativeSetSize(long instance, int width, int height);

    private native void nativeSetBeautyParams(long instance, int type, float intensity);

    private native void nativeSetAdjustParams(long instance, int type, float intensity);

    private native void nativeSetFilter(long instance, String filterZip);

    private native int nativeProcess(long instance, int textureId);

    private native void nativeDestory(long instance);

    private native Bitmap nativeGetResult(long instance);
}

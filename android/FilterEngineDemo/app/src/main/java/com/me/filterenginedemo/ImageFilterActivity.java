package com.me.filterenginedemo;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.WindowManager;
import android.widget.ImageView;

import com.me.filterengine.FileUtils;
import com.me.filterenginedemo.fragment.ConstantFilters;
import com.me.filterenginedemo.fragment.FilterFragment;
import com.me.filterenginedemo.view.ImageFilterView;

import java.io.InputStream;

public class ImageFilterActivity extends AppCompatActivity implements FilterFragment.OnFilterFragmentListener {
    private static final String TAG = "ImageFilterActivity";

    private final static int BEAUTY_MODE = 1;
    private final static int ADJUST_MODE = 2;
    private final static int FILTER_MODE = 3;

    private ImageFilterView mImageFilterView;

    private Bitmap mBitmap;

    private ImageView mBeautyImage;
    private ImageView mAdjustImage;
    private ImageView mFilterImage;
    private FilterFragment mFilterFragment;

    //
    private float mWhiteningLevel;
    private float mBlurLevel;
    private float mReddenLevel;
    private float mBrightnessLevel;
    private float mContrastLevel;
    private float mExposureLevel;
    private float mHueLevel;
    private float mSharpenLevel;
    private float mSaturationLevel;
    private int mFilterPos;

    private boolean isBeautyOn() {
        return (mWhiteningLevel + mBlurLevel) > 0 ;
    }

    private boolean isAdjustOn() {
        return (mBrightnessLevel + mContrastLevel + mExposureLevel + mHueLevel + mSharpenLevel + mSaturationLevel) > 0 ;
    }

    private boolean isFilterOn() {
        return mFilterPos > 0 ;
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_image_filter);

        mImageFilterView = (ImageFilterView) findViewById(R.id.image_filter_view);


        initView();

        initListener();

        initDatas();


        final String mFileName = FileUtils.getFilterFilePath(MeApplication.getContext(),"filter.jpg");
        mImageFilterView.setSurfaceCreatedCallback(new ImageFilterView.OnSurfaceCreatedCallback() {
            @Override
            public void surfaceCreated() {
                mImageFilterView.init(mFileName);
            }
        });
    }

    private void initView() {
        mBeautyImage = (ImageView) findViewById(R.id.beauty_image);
        mAdjustImage = (ImageView) findViewById(R.id.adjust_image);
        mFilterImage = (ImageView) findViewById(R.id.filter_image);

        mFilterFragment = (FilterFragment) findViewById(R.id.filter_fragment);
        mFilterFragment.setOnFilterFragmentListener(this);

    }

    private void initDatas() {
//        mFilterFragment.setWhiteningLevel(0);
//        mFilterFragment.setBlurLevel(0);
//        mFilterFragment.setBrightnessLevel(0);
//        mFilterFragment.setContrastLevel(0);
//        mFilterFragment.setExposureLevel(0);
//        mFilterFragment.setHueLevel(0);
//        mFilterFragment.setSharpenLevel(0);
//        mFilterFragment.setSaturationLevel(0);
//        mFilterFragment.setFilterPos(0);
    }

    private void initListener() {
        // 美颜对话框
        mBeautyImage.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mFilterFragment.setFilterLayoutVisibility(View.GONE);
                mFilterFragment.setAdjustLayoutVisibility(View.GONE);
                mFilterFragment.setBeautyLayoutVisibility(View.VISIBLE);

                disableClick();
            }
        });


        // Adjust 对话框
        mAdjustImage.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mFilterFragment.setFilterLayoutVisibility(View.GONE);
                mFilterFragment.setBeautyLayoutVisibility(View.GONE);
                mFilterFragment.setAdjustLayoutVisibility(View.VISIBLE);

                disableClick();
            }
        });

        // Filter 对话框
        mFilterImage.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mFilterFragment.setBeautyLayoutVisibility(View.GONE);
                mFilterFragment.setAdjustLayoutVisibility(View.GONE);
                mFilterFragment.setFilterLayoutVisibility(View.VISIBLE);

                disableClick();
            }
        });
    }

    private void disableClick() {
        mBeautyImage.setClickable(false);
        mAdjustImage.setClickable(false);
        mFilterImage.setClickable(false);
    }

    private void enableClick() {
        mBeautyImage.setClickable(true);
        mAdjustImage.setClickable(true);
        mFilterImage.setClickable(true);
    }


    @Override
    public void setWhiteningIntensity(float progress) {
        mWhiteningLevel = progress;
        mImageFilterView.setParams(ConstantFilters.BEAUTIFY_WHITEN_MODE, mWhiteningLevel);
    }

    @Override
    public void setBlurIntensity(float progress) {
        mBlurLevel = progress;
        mImageFilterView.setParams(ConstantFilters.BEAUTIFY_BLUR_MODE, mBlurLevel);
    }

    @Override
    public void setReddenIntensity(float progress) {
        mReddenLevel = progress;
        mImageFilterView.setParams(ConstantFilters.BEAUTIFY_REDDEN_MODE, mReddenLevel);
    }

    @Override
    public void setBrightnessIntensity(float progress) {
        mBrightnessLevel = progress;
        mImageFilterView.setParams(ConstantFilters.ADJUST_BRIGHTNESS_MODE, mBrightnessLevel);
    }

    @Override
    public void setContrastIntensity(float progress) {
        mContrastLevel = progress;
        mImageFilterView.setParams(ConstantFilters.ADJUST_CONTRAST_MODE, mContrastLevel);
    }

    @Override
    public void setExposureIntensity(float progress) {
        mExposureLevel = progress;
        mImageFilterView.setParams(ConstantFilters.ADJUST_EXPOSURE_MODE, mExposureLevel);
    }

    @Override
    public void setHueIntensity(float progress) {
        mHueLevel = progress;
        mImageFilterView.setParams(ConstantFilters.ADJUST_HUE_MODE, mHueLevel);
    }

    @Override
    public void setSharpenIntensity(float progress) {
        mSharpenLevel = progress;
        mImageFilterView.setParams(ConstantFilters.ADJUST_SHARPEN_MODE, mSharpenLevel);
    }

    @Override
    public void setSaturationIntensity(float progress) {
        mSaturationLevel = progress;
        mImageFilterView.setParams(ConstantFilters.ADJUST_SATURATION_MODE, mSaturationLevel);
    }

    @Override
    public void onFilterSelected(int pos) {
        mFilterPos = pos;
        mImageFilterView.setFilter(mFilterPos);
    }

    @Override
    public void onCancel(int mode) {
        switch (mode) {
            case BEAUTY_MODE:
                if (isBeautyOn()) {
                    mBeautyImage.setImageResource(R.drawable.icon_beautify_on);
                } else {
                    mBeautyImage.setImageResource(R.drawable.icon_beautify_off);
                }
                break;
            case ADJUST_MODE:
                if (isAdjustOn()) {
                    mAdjustImage.setImageResource(R.drawable.icon_adjust_on);
                } else {
                    mAdjustImage.setImageResource(R.drawable.icon_adjust_off);
                }
                break;
            case FILTER_MODE:
                if (isFilterOn()) {
                    mFilterImage.setImageResource(R.drawable.icon_filter_on);
                } else {
                    mFilterImage.setImageResource(R.drawable.icon_filter_off);
                }
                break;
        }

        enableClick();
    }

    @Override
    public void onComplete(int mode) {
        switch (mode) {
            case BEAUTY_MODE:
                if (isBeautyOn()) {
                    mBeautyImage.setImageResource(R.drawable.icon_beautify_on);
                } else {
                    mBeautyImage.setImageResource(R.drawable.icon_beautify_off);
                }
                break;
            case ADJUST_MODE:
                if (isAdjustOn()) {
                    mAdjustImage.setImageResource(R.drawable.icon_adjust_on);
                } else {
                    mAdjustImage.setImageResource(R.drawable.icon_adjust_off);
                }
                break;
            case FILTER_MODE:
                if (isFilterOn()) {
                    mFilterImage.setImageResource(R.drawable.icon_filter_on);
                } else {
                    mFilterImage.setImageResource(R.drawable.icon_filter_off);
                }
                break;
        }

        enableClick();
    }
}

package com.me.filterenginedemo;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.WindowManager;
import android.widget.ImageView;

import com.me.filterenginedemo.fragment.ConstantFilters;
import com.me.filterenginedemo.fragment.Filter;
import com.me.filterenginedemo.fragment.FilterFragment;

import java.util.List;


public class VideoFilterActivity extends AppCompatActivity {

//    private static final String TAG = "douyin";
//    private static final int REQUEST_CAMERA_PERMISSION_CODE = 0;
//    private static final int REQUEST_RECORD_AUDIO_PERMISSION_CODE = 1;
//    private static final int REQUEST_WRITE_EXTERNAL_STORAGE_PERMISSION_CODE = 2;
//    private final static int BEAUTY_MODE = 1;
//    private final static int CUT_MUSIC_MODE = 2;
//    private final static int FILTER_MODE = 3;
//    private boolean m_permissionGranted;
//
//
//    // 分割线
//    private ImageView mImgBeautify;
//    private ImageView mImgAdjust;
//    private ImageView mImgFilter;
//    private FilterFragment m_adjust_options_ctl;
//
//    private List<Filter> filterList;
//    boolean isFirstInitFilterRecyclerView = true;
//
//
//    @Override
//    protected void onCreate(@Nullable Bundle savedInstanceState) {
//        super.onCreate(savedInstanceState);
//        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
//        setContentView(R.layout.activity_video_filter);
//
//        initView();
//        initListener();
//
////        initFilter();
//    }
//
//
//    private void initView() {
//        mImgBeautify = (ImageView) findViewById(R.id.beauty_image);
//        mImgAdjust = (ImageView) findViewById(R.id.adjust_image);
//        mImgFilter = (ImageView) findViewById(R.id.filter_image);
//
//        m_adjust_options_ctl = (FilterFragment) findViewById(R.id.adjust_options_ctl);
//        m_adjust_options_ctl.(this);
//
//    }
//
//    private void  initListener() {
//        // 美颜对话框
//        mImgBeautify.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View v) {
//                m_adjust_options_ctl.setFilterLayoutVisibility(View.GONE);
//                m_adjust_options_ctl.setBeautyLayoutVisibility(View.VISIBLE);
//            }
//        });
//
//
//        // Adjust 对话框
//        mImgAdjust.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View v) {
//
//            }
//        });
//
//        // Filter 对话框
//        mImgFilter.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View v) {
//                if (isFirstInitFilterRecyclerView) {
//                    m_adjust_options_ctl.initFilterRecyclerView(filterList);
//                }
//                isFirstInitFilterRecyclerView = false;
//
//                m_adjust_options_ctl.setBeautyLayoutVisibility(View.GONE);
//                m_adjust_options_ctl.setFilterLayoutVisibility(View.VISIBLE);
//            }
//        });
//    }
//
//
//    @Override
//    public void setWhiteningFloatVal(double progress) {
//
//    }
//
//    @Override
//    public void setStrengthFloatVal(double progress) {
//
//    }
//
//    @Override
//    public void onFilterSelected(int pos) {
//
//    }
//
//    @Override
//    public void onCancel(int mode) {
//
//    }
//
//    @Override
//    public void onComplete(int mode) {
//
//    }
}

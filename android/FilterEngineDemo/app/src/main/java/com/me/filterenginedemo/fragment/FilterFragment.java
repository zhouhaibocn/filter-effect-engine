package com.me.filterenginedemo.fragment;

import android.content.Context;
import android.graphics.Color;
import android.graphics.Rect;
import android.support.annotation.Nullable;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;


import com.me.filterenginedemo.R;

import java.util.List;

public class FilterFragment extends LinearLayout {
    private static final String TAG = "FilterFragment";

    private final static int BEAUTY_MODE = 1;
    private final static int ADJUST_MODE = 2;
    private final static int FILTER_MODE = 3;

    private final static int BEAUTY_SEEKBAR_MAX  = 9;
    private final static int BEAUTY_SEEKBAR_DEFAULT  = 0;

    private final static int ADJUST_SEEKBAR_MAX  = 100;
    private final static int ADJUST_SEEKBAR_DEFAULT  = 50;

    // 美颜
    private RelativeLayout mBeautyLayout;
    private NumberSeekBar mWhiteningSeekBar;
    private int mWhiteningLevel;
    private NumberSeekBar mBlurSeekBar;
    private int mBlurLevel;
    private NumberSeekBar mReddenSeekBar;
    private int mReddenLevel;

    // 调节
    private RelativeLayout mAdjustLayout;
    private NumberSeekBar mBrightnessSeekBar;
    private int mBrightnessLevel;
    private NumberSeekBar mContrastSeekBar;
    private int mContrastLevel;
    private NumberSeekBar mExposureSeekBar;
    private int mExposureLevel;
    private NumberSeekBar mHueSeekBar;
    private int mHueLevel;
    private NumberSeekBar mSharpenSeekBar;
    private int mSharpenLevel;
    private NumberSeekBar mSaturationSeekBar;
    private int mSaturationLevel;

    // 滤镜
    private RelativeLayout mFilterLayout;
    private RecyclerView mFilterListView;
    private FilterFragment.RecyclerViewAdapter mRecyclerViewAdapter;
    private FilterFragment.OnFilterFragmentListener mListener;
    private List<Filter> mFilterList;
    private int mFilterPos;

    // 共有
    private Button mCompleteBtn;
    private Button mCancelBtn;
    private int mMode;

    // 记录上一时刻位置
    private int mPreWhiteningLevel;
    private int mPreBlurLevel;
    private int mPreReddenLevel;
    private int mPreBrightnessLevel;
    private int mPreContrastLevel;
    private int mPreExposureLevel;
    private int mPreHueLevel;
    private int mPreSharpenLevel;
    private int mPreSaturationLevel;
    private int mPreFilterPos;

    public void setWhiteningLevel(int level) {
        mPreWhiteningLevel = level;
        mWhiteningSeekBar.setProgress(level);
    }

    public void setBlurLevel(int level) {
        mPreBlurLevel = level;
        mBlurSeekBar.setProgress(level);
    }

    public void setReddenLevel(int level) {
        mPreReddenLevel = level;
        mReddenSeekBar.setProgress(level);
    }

    public void setBrightnessLevel(int level) {
        mPreBrightnessLevel = level;
        mBrightnessSeekBar.setProgress(level);
    }

    public void setContrastLevel(int level) {
        mPreContrastLevel = level;
        mContrastSeekBar.setProgress(level);
    }

    public void setExposureLevel(int level) {
        mPreExposureLevel = level;
        mExposureSeekBar.setProgress(level);
    }

    public void setHueLevel(int level) {
        mPreHueLevel = level;
        mHueSeekBar.setProgress(level);
    }

    public void setSharpenLevel(int level) {
        mPreSharpenLevel = level;
        mSharpenSeekBar.setProgress(level);
    }

    public void setSaturationLevel(int level) {
        mPreSaturationLevel = level;
        mSaturationSeekBar.setProgress(level);
    }

    public void setFilterPos(int pos) {
        mPreFilterPos = pos;
        mRecyclerViewAdapter.mSelectedPosition = mPreFilterPos;
        mRecyclerViewAdapter.notifyDataSetChanged();
    }


    public FilterFragment(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        LayoutInflater.from(context).inflate(R.layout.fragment_filter, this);

        initView();
    }

    private void initView() {
        initBeautyView();

        initAdjustView();

        initFilterView();

        initCommonView();
    }

    // 初始化美颜
    private void initBeautyView() {
        initWhiteningView();
        initBlurView();
        initReddenView();
    }

    private void initWhiteningView() {
        mWhiteningSeekBar = (NumberSeekBar) findViewById(R.id.whitening_seek_bar);
        mWhiteningSeekBar.setMax(BEAUTY_SEEKBAR_MAX);
        mWhiteningLevel = BEAUTY_SEEKBAR_DEFAULT;
        mWhiteningSeekBar.setProgress(mWhiteningLevel);
        mWhiteningSeekBar.setOnSeekBarChangeListener(new NumberSeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(NumberSeekBar seekBar, int i) {
                mWhiteningLevel = i;
                if(mListener != null) {
                    float intensity = mWhiteningLevel * 1.0f / mWhiteningSeekBar.getMax();
                    mListener.setWhiteningIntensity(intensity);
                }
            }

            @Override
            public void onStartTrackingTouch(NumberSeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(NumberSeekBar seekBar) {

            }
        });
    }

    private void initBlurView() {
        mBlurSeekBar = (NumberSeekBar) findViewById(R.id.blur_seek_bar);
        mBlurSeekBar.setMax(BEAUTY_SEEKBAR_MAX);
        mBlurLevel = BEAUTY_SEEKBAR_DEFAULT;
        mBlurSeekBar.setProgress(mBlurLevel);
        mBlurSeekBar.setOnSeekBarChangeListener(new NumberSeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(NumberSeekBar seekBar, int i) {
                mBlurLevel = i;
                if(mListener != null) {
                    float intensity = mBlurLevel * 1.0f / mBlurSeekBar.getMax();
                    mListener.setBlurIntensity(intensity);
                }
            }

            @Override
            public void onStartTrackingTouch(NumberSeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(NumberSeekBar seekBar) {

            }
        });
    }

    private void initReddenView() {
        mReddenSeekBar = (NumberSeekBar) findViewById(R.id.redden_seek_bar);
        mReddenSeekBar.setMax(BEAUTY_SEEKBAR_MAX);
        mReddenLevel = BEAUTY_SEEKBAR_DEFAULT;
        mReddenSeekBar.setProgress(mReddenLevel);
        mReddenSeekBar.setOnSeekBarChangeListener(new NumberSeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(NumberSeekBar seekBar, int i) {
                mReddenLevel = i;
                if(mListener != null) {
                    float intensity = mReddenLevel * 1.0f / mReddenSeekBar.getMax();
                    mListener.setReddenIntensity(intensity);
                }
            }

            @Override
            public void onStartTrackingTouch(NumberSeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(NumberSeekBar seekBar) {

            }
        });
    }

    // 初始化 Adjust
    private void initAdjustView() {
        initBrightnessView();
        initContrastView();
        initExposureView();
        initHueView();
        initSharpenView();
        initSaturationView();
    }

    private void initBrightnessView() {
        mBrightnessSeekBar = (NumberSeekBar) findViewById(R.id.brightness_seek_bar);
        mBrightnessSeekBar.setMax(ADJUST_SEEKBAR_MAX);
        mBrightnessLevel = ADJUST_SEEKBAR_DEFAULT;
        mBrightnessSeekBar.setProgress(mBrightnessLevel);
        mBrightnessSeekBar.setOnSeekBarChangeListener(new NumberSeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(NumberSeekBar seekBar, int i) {
                mBrightnessLevel = i;
                if(mListener != null) {
                    float intensity = mBrightnessLevel * 1.0f / mBrightnessSeekBar.getMax();
                    mListener.setBrightnessIntensity(intensity);
                }
            }

            @Override
            public void onStartTrackingTouch(NumberSeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(NumberSeekBar seekBar) {

            }
        });
    }


    private void initContrastView() {
        mContrastSeekBar = (NumberSeekBar) findViewById(R.id.contrast_seek_bar);
        mContrastSeekBar.setMax(ADJUST_SEEKBAR_MAX);
        mContrastLevel = ADJUST_SEEKBAR_DEFAULT;
        mContrastSeekBar.setProgress(mContrastLevel);
        mContrastSeekBar.setOnSeekBarChangeListener(new NumberSeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(NumberSeekBar seekBar, int i) {
                mContrastLevel = i;
                if(mListener != null) {
                    float intensity = mContrastLevel * 1.0f / mContrastSeekBar.getMax();
                    mListener.setContrastIntensity(intensity);
                }
            }

            @Override
            public void onStartTrackingTouch(NumberSeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(NumberSeekBar seekBar) {

            }
        });
    }


    private void initExposureView() {
        mExposureSeekBar = (NumberSeekBar) findViewById(R.id.exposure_seek_bar);
        mExposureSeekBar.setMax(ADJUST_SEEKBAR_MAX);
        mExposureLevel = ADJUST_SEEKBAR_DEFAULT;
        mExposureSeekBar.setProgress(mExposureLevel);
        mExposureSeekBar.setOnSeekBarChangeListener(new NumberSeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(NumberSeekBar seekBar, int i) {
                mExposureLevel = i;
                if(mListener != null) {
                    float intensity = mExposureLevel * 1.0f / mExposureSeekBar.getMax();
                    mListener.setExposureIntensity(intensity);
                }
            }

            @Override
            public void onStartTrackingTouch(NumberSeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(NumberSeekBar seekBar) {

            }
        });
    }


    private void initHueView() {
        mHueSeekBar = (NumberSeekBar) findViewById(R.id.hue_seek_bar);
        mHueSeekBar.setMax(ADJUST_SEEKBAR_MAX);
        mHueLevel = ADJUST_SEEKBAR_DEFAULT;
        mHueSeekBar.setProgress(mHueLevel);
        mHueSeekBar.setOnSeekBarChangeListener(new NumberSeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(NumberSeekBar seekBar, int i) {
                mHueLevel = i;
                if(mListener != null) {
                    float intensity = mHueLevel * 1.0f / mHueSeekBar.getMax();
                    mListener.setHueIntensity(intensity);
                }
            }

            @Override
            public void onStartTrackingTouch(NumberSeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(NumberSeekBar seekBar) {

            }
        });
    }


    private void initSharpenView() {
        mSharpenSeekBar = (NumberSeekBar) findViewById(R.id.sharpen_seek_bar);
        mSharpenSeekBar.setMax(ADJUST_SEEKBAR_MAX);
        mSharpenLevel = ADJUST_SEEKBAR_DEFAULT;
        mSharpenSeekBar.setProgress(mSharpenLevel);
        mSharpenSeekBar.setOnSeekBarChangeListener(new NumberSeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(NumberSeekBar seekBar, int i) {
                mSharpenLevel = i;
                if(mListener != null) {
                    float intensity = mSharpenLevel * 1.0f / mSharpenSeekBar.getMax();
                    mListener.setSharpenIntensity(intensity);
                }
            }

            @Override
            public void onStartTrackingTouch(NumberSeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(NumberSeekBar seekBar) {

            }
        });
    }

    private void initSaturationView() {
        mSaturationSeekBar = (NumberSeekBar) findViewById(R.id.saturation_seek_bar);
        mSaturationSeekBar.setMax(ADJUST_SEEKBAR_MAX);
        mSaturationLevel = ADJUST_SEEKBAR_DEFAULT;
        mSaturationSeekBar.setProgress(mSaturationLevel);
        mSaturationSeekBar.setOnSeekBarChangeListener(new NumberSeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(NumberSeekBar seekBar, int i) {
                mSaturationLevel = i;
                if(mListener != null) {
                    float intensity = mSaturationLevel * 1.0f / mSaturationSeekBar.getMax();
                    mListener.setSaturationIntensity(intensity);
                }
            }

            @Override
            public void onStartTrackingTouch(NumberSeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(NumberSeekBar seekBar) {

            }
        });
    }

    // 初始化滤镜
    public void initFilterView() {
        // 滤镜
        mFilterListView = (RecyclerView) findViewById(R.id.filter_list_view);
        mFilterListView.setLayoutManager(new LinearLayoutManager(mFilterListView.getContext(), LinearLayoutManager.HORIZONTAL, false));
        mFilterPos = 0;
        mFilterList = ConstantFilters.getFilterList();
        mRecyclerViewAdapter = new FilterFragment.RecyclerViewAdapter(mFilterList);
        mFilterListView.setAdapter(mRecyclerViewAdapter);
        FilterFragment.SpaceItemDecoration space = new FilterFragment.SpaceItemDecoration(18);
        mFilterListView.addItemDecoration(space);
        mRecyclerViewAdapter.setOnItemClickListener(new FilterFragment.RecyclerViewAdapter.OnItemClickListener() {
            @Override
            public void onItemClick(View view, int pos) {
                mFilterPos = pos;
                if(mListener != null){
                    mListener.onFilterSelected(mFilterPos);
                }
            }
        });
    }

    // 初始化
    private void initCommonView() {
        mBeautyLayout = (RelativeLayout) findViewById(R.id.beauty_layout);
        mAdjustLayout = (RelativeLayout) findViewById(R.id.adjust_layout);
        mFilterLayout = (RelativeLayout) findViewById(R.id.filter_layout);
        mBeautyLayout.setVisibility(GONE);
        mAdjustLayout.setVisibility(GONE);
        mFilterLayout.setVisibility(GONE);

        mCompleteBtn = (Button) findViewById(R.id.operation_complete);
        mCancelBtn = (Button) findViewById(R.id.operation_cancel);
        mCompleteBtn.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View view) {
                setVisibility(INVISIBLE);
                switch (mMode){
                    case BEAUTY_MODE:{
                        mPreWhiteningLevel = mWhiteningLevel;
                        mPreBlurLevel = mBlurLevel;
                        mPreReddenLevel = mReddenLevel;
                        break;
                    }
                    case ADJUST_MODE:{
                        mPreBrightnessLevel =mBrightnessLevel;
                        mPreContrastLevel = mContrastLevel;
                        mPreExposureLevel = mExposureLevel;
                        mPreHueLevel = mHueLevel;
                        mPreSharpenLevel = mSharpenLevel;
                        mPreSaturationLevel = mSaturationLevel;
                        break;
                    }
                    case FILTER_MODE:{
                        mPreFilterPos = mFilterPos;
                        break;
                    }
                }
                if(mListener != null){
                    mListener.onComplete(mMode);
                }
            }
        });

        mCancelBtn.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View view) {
                setVisibility(INVISIBLE);
                switch (mMode){
                    case BEAUTY_MODE:{
                        if(mListener != null) {
                            float intensity = mPreWhiteningLevel * 1.0f / mWhiteningSeekBar.getMax();
                            mListener.setWhiteningIntensity(intensity);
                            mWhiteningSeekBar.setProgress(mPreWhiteningLevel);
                            intensity = mPreBlurLevel * 1.0f / mBlurSeekBar.getMax();
                            mListener.setBlurIntensity(intensity);
                            mBlurSeekBar.setProgress(mPreBlurLevel);
                            intensity = mPreReddenLevel * 1.0f / mReddenSeekBar.getMax();
                            mListener.setBlurIntensity(intensity);
                            mReddenSeekBar.setProgress(mPreReddenLevel);
                        }
                        break;
                    }
                    case ADJUST_MODE:{
                        if(mListener != null) {
                            float intensity = mPreBrightnessLevel * 1.0f / mBrightnessSeekBar.getMax();
                            mListener.setBrightnessIntensity(intensity);
                            mBrightnessSeekBar.setProgress(mPreBrightnessLevel);
                            intensity = mPreContrastLevel * 1.0f / mContrastSeekBar.getMax();
                            mListener.setContrastIntensity(intensity);
                            mContrastSeekBar.setProgress(mPreContrastLevel);
                            intensity = mPreExposureLevel * 1.0f / mExposureSeekBar.getMax();
                            mListener.setExposureIntensity(intensity);
                            mExposureSeekBar.setProgress(mPreExposureLevel);
                            intensity = mPreHueLevel * 1.0f / mHueSeekBar.getMax();
                            mListener.setHueIntensity(intensity);
                            mHueSeekBar.setProgress(mPreHueLevel);
                            intensity = mPreSharpenLevel * 1.0f / mSharpenSeekBar.getMax();
                            mListener.setSharpenIntensity(intensity);
                            mSharpenSeekBar.setProgress(mPreSharpenLevel);
                            intensity = mPreSaturationLevel * 1.0f / mSaturationSeekBar.getMax();
                            mListener.setSaturationIntensity(intensity);
                            mSaturationSeekBar.setProgress(mPreSaturationLevel);
                        }
                        break;
                    }
                    case FILTER_MODE:{
                        if(mListener != null){
                            mListener.onFilterSelected(mPreFilterPos);
                            mRecyclerViewAdapter.mSelectedPosition = mPreFilterPos;
                            mRecyclerViewAdapter.notifyDataSetChanged();
                        }
                    }
                }
                if(mListener != null){
                    mListener.onCancel(mMode);
                }
            }
        });

    }


    public void setOnFilterFragmentListener(FilterFragment.OnFilterFragmentListener listener){
        mListener = listener;
    }

    public void resetRecyclerAdapter(){
        if(mRecyclerViewAdapter != null)
            mRecyclerViewAdapter.resetState();
    }

    public void setBeautyLayoutVisibility(int visibility){
        setVisibility(visibility);
        mBeautyLayout.setVisibility(visibility);
        if(visibility == VISIBLE){
            mMode = BEAUTY_MODE;
        }
    }

    public void setAdjustLayoutVisibility(int visibility){
        setVisibility(visibility);
        mAdjustLayout.setVisibility(visibility);
        if(visibility == VISIBLE){
            mMode = ADJUST_MODE;
        }
    }

    public void setFilterLayoutVisibility(int visibility){
        setVisibility(visibility);
        mFilterLayout.setVisibility(visibility);
        if(visibility == VISIBLE){
            mMode = FILTER_MODE;
        }
    }


    private static class RecyclerViewAdapter extends RecyclerView.Adapter<FilterFragment.RecyclerViewAdapter.ViewHolder> implements View.OnClickListener{
        private List<Filter> mFilterList;
        private FilterFragment.RecyclerViewAdapter.OnItemClickListener mOnItemClickListener = null;
        public int mSelectedPosition = 0;

        public void resetState(){
            mSelectedPosition = 0;
            notifyDataSetChanged();
        }

        public RecyclerViewAdapter(List<Filter> list) {
            mFilterList = list;
        }

        @Override
        public FilterFragment.RecyclerViewAdapter.ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {

            View v = LayoutInflater.from(parent.getContext()).inflate(R.layout.filter_list_item, parent, false);
            v.setOnClickListener(this);
            FilterFragment.RecyclerViewAdapter.ViewHolder viewHolder = new FilterFragment.RecyclerViewAdapter.ViewHolder(v);
            return viewHolder;
        }

        @Override
        public void onBindViewHolder(FilterFragment.RecyclerViewAdapter.ViewHolder holder, int position) {

            holder.mTextView.setText(mFilterList.get(position).getName());
            holder.mImageView.setImageResource(mFilterList.get(position).getImageId());
            holder.itemView.setTag(position);

            if(mSelectedPosition == position){
                holder.mTextView.setBackgroundColor(Color.parseColor("#3db7ff"));
                holder.mTextView.setTextColor(Color.parseColor("#ffffff"));
            }else{
                holder.mTextView.setBackgroundColor(Color.parseColor("#ffffff"));
                holder.mTextView.setTextColor(Color.parseColor("#575757"));
            }

        }

        @Override
        public int getItemCount() {
            return mFilterList == null ? 0 :  mFilterList.size();
        }

        @Override
        public void onClick(View view) {

            if (mOnItemClickListener != null) {
                mOnItemClickListener.onItemClick(view,(int)view.getTag());
            }
            notifyItemChanged(mSelectedPosition);
            mSelectedPosition = (int)view.getTag();
            notifyItemChanged(mSelectedPosition);
        }

        public interface OnItemClickListener{
            void onItemClick(View view, int pos);
        }

        public void setOnItemClickListener(FilterFragment.RecyclerViewAdapter.OnItemClickListener listener) {
            this.mOnItemClickListener = listener;
        }

        public  class ViewHolder extends RecyclerView.ViewHolder{
            TextView mTextView;
            ImageView mImageView;

            public ViewHolder(View itemView){
                super(itemView);
                mImageView = (ImageView) itemView.findViewById(R.id.image_view);
                mTextView = (TextView) itemView.findViewById(R.id.text_view);
            }
        }
    }

    private class SpaceItemDecoration extends RecyclerView.ItemDecoration{
        private int mSpace;

        public SpaceItemDecoration(int space){
            mSpace = space;
        }

        @Override
        public void getItemOffsets(Rect outRect, View view, RecyclerView parent, RecyclerView.State state) {
            super.getItemOffsets(outRect, view, parent, state);

            outRect.left = mSpace;
            outRect.right = mSpace;
        }

    }

    public interface OnFilterFragmentListener{
        void setWhiteningIntensity(float progress);
        void setBlurIntensity(float progress);
        void setReddenIntensity(float progress);
        void setBrightnessIntensity(float progress);
        void setContrastIntensity(float progress);
        void setExposureIntensity(float progress);
        void setHueIntensity(float progress);
        void setSharpenIntensity(float progress);
        void setSaturationIntensity(float progress);
        void onFilterSelected(int pos);
        void onCancel(int mode);
        void onComplete(int mode);
    }
}

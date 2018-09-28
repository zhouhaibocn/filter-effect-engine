package com.me.filterenginedemo.fragment;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.LayerDrawable;
import android.support.annotation.NonNull;
import android.text.TextPaint;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewConfiguration;
import android.view.ViewGroup;
import android.view.ViewParent;

import com.me.filterenginedemo.R;


public class NumberSeekBar extends View {

    private static final int MAX_LEVEL = 10000;

    /**
     * SeekBar数值文字颜色
     */
    private int mTextColor;

    /**
     * SeekBar数值文字大小
     */
    private float mTextSize;

    /**
     * 画笔
     */
    private TextPaint mPaint;

    private Drawable mProgressDrawable;
    private Drawable mThumb;
    private int mMax;
    private int mProgress;

    private static final int[] ATTRS = {
            android.R.attr.max,
            android.R.attr.progress,
            android.R.attr.progressDrawable,
            android.R.attr.thumb,
            android.R.attr.thumbOffset,
    };
    private Drawable mCurrentDrawable;
    private float mFontHeight;
    private int mThumbOffset;
    private OnSeekBarChangeListener mOnSeekBarChangeListener;
    private int mScaledTouchSlop;
    private float mTouchDownX;
    private boolean mIsDragging;

    public interface OnSeekBarChangeListener {
        void onProgressChanged(NumberSeekBar seekBar, int progress);

        void onStartTrackingTouch(NumberSeekBar seekBar);

        void onStopTrackingTouch(NumberSeekBar seekBar);
    }

    public NumberSeekBar(Context context) {
        this(context, null);
    }

    public NumberSeekBar(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }

    @SuppressLint("ResourceType")
    public NumberSeekBar(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        initProgressBar();
        TypedArray ta = context.getTheme().obtainStyledAttributes(attrs, R.styleable.NumberSeekBar,
                defStyleAttr, 0);
        int count = ta.getIndexCount();
        float mTextPadding = 0;
        for (int i = 0; i < count; i++) {
            int index = ta.getIndex(i);
            switch (index) {
                case R.styleable.NumberSeekBar_numberTextColor:
                    mTextColor = ta.getColor(index, Color.WHITE);
                    break;

                case R.styleable.NumberSeekBar_numberTextSize:
                    mTextSize = ta.getDimensionPixelSize(index, 10);
                    break;
                case R.styleable.NumberSeekBar_numberTextPadding:
                    mTextPadding = ta.getDimensionPixelSize(index, 0);
                    break;
            }
        }
        ta.recycle();

        //设置画笔
        mPaint = new TextPaint();
        mPaint.setAntiAlias(true);
        mPaint.setColor(mTextColor);
        mPaint.setTextSize(mTextSize);

        Paint.FontMetricsInt metricsInt = mPaint.getFontMetricsInt();

        mFontHeight = metricsInt.bottom - metricsInt.top + mTextPadding;

        TypedArray a = context.obtainStyledAttributes(attrs, ATTRS);

        setMax(a.getInt(0, 0));
        setProgress(a.getInt(1, 0));
        setProgressDrawable(a.getDrawable(2));
        final int thumbOffset = a.getDimensionPixelOffset(4, mThumbOffset);
        setThumbOffset(thumbOffset);
        setThumb(a.getDrawable(3));

        a.recycle();

        mScaledTouchSlop = ViewConfiguration.get(context).getScaledTouchSlop();
    }

    private void initProgressBar() {
        mMax = 100;
        mProgress = 0;
    }

    public void setThumbOffset(int thumbOffset) {
        mThumbOffset = thumbOffset;
        invalidate();
    }

    public void setThumb(Drawable thumb) {
        final boolean needUpdate;
        // This way, calling setThumb again with the same bitmap will result in
        // it recalcuating mThumbOffset (if for example it the bounds of the
        // drawable changed)
        if (mThumb != null && thumb != mThumb) {
            mThumb.setCallback(null);
            needUpdate = true;
        } else {
            needUpdate = false;
        }

        if (thumb != null) {
            thumb.setCallback(this);

            // Assuming the thumb drawable is symmetric, set the thumb offset
            // such that the thumb will hang halfway off either edge of the
            // progress bar.
            mThumbOffset = thumb.getIntrinsicWidth() / 2;

            // If we're updating get the new states
            if (needUpdate &&
                    (thumb.getIntrinsicWidth() != mThumb.getIntrinsicWidth()
                            || thumb.getIntrinsicHeight() != mThumb.getIntrinsicHeight())) {
                requestLayout();
            }
        }

        mThumb = thumb;

        invalidate();

        if (needUpdate) {
            updateThumbAndTrackPos(getWidth(), getHeight());
            if (thumb != null && thumb.isStateful()) {
                // Note that if the states are different this won't work.
                // For now, let's consider that an app bug.
                int[] state = getDrawableState();
                thumb.setState(state);
            }
        }
    }

    private void updateThumbAndTrackPos(int w, int h) {
        final int paddedHeight = (int) (h - getPaddingTop() - getPaddingBottom() - mFontHeight);
        final Drawable track = mCurrentDrawable;
        final Drawable thumb = mThumb;

        // The max height does not incorporate padding, whereas the height
        // parameter does.
        final int thumbHeight = thumb == null ? 0 : thumb.getIntrinsicHeight();

        // Apply offset to whichever item is taller.
        final int trackOffset = (int) (getPaddingTop() + mFontHeight);
        final int thumbOffset = (paddedHeight - thumbHeight) / 2 + trackOffset;

        if (track != null) {
            final int trackWidth = w - getPaddingLeft() - getPaddingRight();
            track.setBounds(0, trackOffset, trackWidth, trackOffset + paddedHeight);
        }

        if (thumb != null) {
            setThumbPos(w, thumb, getScale(), thumbOffset);
        }
    }

    private float getScale() {
        int min = 0;
        int max = mMax;
        int range = max - min;
        return range > 0 ? (mProgress - min) / (float) range : 0;
    }

    private void setThumbPos(int w, Drawable thumb, float scale, int offset) {
        int available = w - getPaddingLeft() - getPaddingRight();
        final int thumbWidth = thumb.getIntrinsicWidth();
        final int thumbHeight = thumb.getIntrinsicHeight();
        available -= thumbWidth;

        // The extra space for the thumb to move on the track
        available += mThumbOffset * 2;

        final int thumbPos = (int) (scale * available + 0.5f);

        final int top, bottom;
        if (offset == Integer.MIN_VALUE) {
            final Rect oldBounds = thumb.getBounds();
            top = oldBounds.top;
            bottom = oldBounds.bottom;
        } else {
            top = offset;
            bottom = offset + thumbHeight;
        }

        final int right = thumbPos + thumbWidth;
        thumb.setBounds(thumbPos, top, right, bottom);
    }

    private static int constrain(int amount, int low, int high) {
        return amount < low ? low : (amount > high ? high : amount);
    }

    public void setProgress(int progress) {
        progress = constrain(progress, 0, mMax);
        if (progress == mProgress) {
            return;
        }
        mProgress = progress;
        doRefreshProgress(android.R.id.progress, mProgress, true);
    }

    public void setMax(int max) {
        if (max < 0) {
            mMax = 0;
        }
        if (mMax != max) {
            mMax = max;
            postInvalidate();
            if (mProgress > max) {
                mProgress = max;
            }
            doRefreshProgress(android.R.id.progress, mProgress, true);
        }
    }

    public int getMax() {
        return mMax;
    }

    public void setProgressDrawable(Drawable d) {
        if (mProgressDrawable != d) {
            if (mProgressDrawable != null) {
                mProgressDrawable.setCallback(null);
                unscheduleDrawable(mProgressDrawable);
            }

            mProgressDrawable = d;

            if (d != null) {
                d.setCallback(this);
                if (d.isStateful()) {
                    d.setState(getDrawableState());
                }
            }
            swapCurrentDrawable(d);
            postInvalidate();
            updateDrawableBounds(getWidth(), getHeight());

            doRefreshProgress(android.R.id.progress, mProgress, false);
        }
    }

    private void doRefreshProgress(int id, int progress, boolean callBackToApp) {
        int range = mMax;
        final float scale = range > 0 ? progress / (float) range : 0;
        setVisualProgress(id, scale);
        final boolean isPrimary = id == android.R.id.progress;
        if (isPrimary && callBackToApp) {
            onProgressRefresh(scale, progress);
        }
    }

    private void onProgressRefresh(float scale, int progress) {
        if (mOnSeekBarChangeListener != null) {
            mOnSeekBarChangeListener.onProgressChanged(this, progress);
        }
    }

    private void swapCurrentDrawable(Drawable newDrawable) {
        final Drawable oldDrawable = mCurrentDrawable;
        mCurrentDrawable = newDrawable;

        if (oldDrawable != mCurrentDrawable) {
            if (oldDrawable != null) {
                oldDrawable.setVisible(false, false);
            }
            if (mCurrentDrawable != null) {
                mCurrentDrawable.setVisible(getWindowVisibility() == VISIBLE && isShown(), false);
            }
        }
    }

    private void setVisualProgress(int id, float progress) {
        Drawable d = mCurrentDrawable;

        if (d instanceof LayerDrawable) {
            d = ((LayerDrawable) d).findDrawableByLayerId(id);
            if (d == null) {
                // If we can't find the requested layer, fall back to setting
                // the level of the entire drawable. This will break if
                // progress is set on multiple elements, but the theme-default
                // drawable will always have all layer IDs present.
                d = mCurrentDrawable;
            }
        }

        if (d != null) {
            final int level = (int) (progress * MAX_LEVEL);
            d.setLevel(level);
        } else {
            invalidate();
        }
        onVisualProgressChanged(id, progress);
    }

    void onVisualProgressChanged(int id, float progress) {
        if (id == android.R.id.progress) {
            final Drawable thumb = mThumb;
            if (thumb != null) {
                setThumbPos(getWidth(), thumb, progress, Integer.MIN_VALUE);

                // Since we draw translated, the drawable's bounds that it signals
                // for invalidation won't be the actual bounds we want invalidated,
                // so just invalidate this whole view.
                invalidate();
            }
        }
    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        updateDrawableBounds(w, h);
        updateThumbAndTrackPos(w, h);
    }

    private void updateDrawableBounds(int w, int h) {
        w -= getPaddingRight() + getPaddingLeft();
        h -= getPaddingTop() + getPaddingBottom();

        int right = w;
        int bottom = h;
        if (mProgressDrawable != null) {
            mProgressDrawable.setBounds(0, (int) mFontHeight, right, bottom);
        }
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        int thumbHeight = mThumb == null ? 0 : mThumb.getIntrinsicHeight();

        int dw = 0;
        int dh = 0;
        final Drawable d = mCurrentDrawable;
        if (d != null) {
            dw = d.getIntrinsicWidth();
            dh = d.getIntrinsicHeight();
            dh = Math.max(thumbHeight, dh);
        }

        dw += getPaddingLeft() + getPaddingRight();
        dh += getPaddingTop() + getPaddingBottom();
        dh += mFontHeight;

        setMeasuredDimension(resolveSizeAndState(dw, widthMeasureSpec, 0),
                resolveSizeAndState(dh, heightMeasureSpec, 0));
    }

    @Override
    protected boolean verifyDrawable(@NonNull Drawable who) {
        return who == mProgressDrawable || who == mThumb || super.verifyDrawable(who);
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        drawTrack(canvas);
        drawThumb(canvas);
        drawText(canvas);
    }

    void drawText(Canvas canvas) {
        int sc = canvas.save();

        canvas.translate(getPaddingLeft() - mThumbOffset, getPaddingTop());
        Paint.FontMetricsInt fontMetrics = mPaint.getFontMetricsInt();
        int baseline = getPaddingTop() - fontMetrics.top;
        String text = String.valueOf(mProgress);
        float textWidth = mPaint.measureText(text);
        float bgX = (getWidth() - getPaddingRight() - getPaddingLeft()) * mProgress * 1.0f / mMax;
        int x = (int) (getPaddingLeft() + bgX - textWidth / 2 - 1);
        canvas.drawText(text, x, baseline, mPaint);
        canvas.restoreToCount(sc);
    }

    /**
     * Draw the thumb.
     */
    void drawThumb(Canvas canvas) {
        if (mThumb != null) {
            final int saveCount = canvas.save();
            // Translate the padding. For the x, we need to allow the thumb to
            // draw in its extra space
            canvas.translate(getPaddingLeft() - mThumbOffset, getPaddingTop());
            mThumb.draw(canvas);
            canvas.restoreToCount(saveCount);
        }
    }


    /**
     * Draws the progress bar track.
     */
    void drawTrack(Canvas canvas) {
        final Drawable d = mCurrentDrawable;
        if (d != null) {
            final int saveCount = canvas.save();
            canvas.translate(getPaddingLeft(), getPaddingTop());
            d.draw(canvas);
            canvas.restoreToCount(saveCount);
        }
    }

    private boolean isInScrollingContainer() {
        ViewParent p = getParent();
        while (p != null && p instanceof ViewGroup) {
            if (((ViewGroup) p).shouldDelayChildPressedState()) {
                return true;
            }
            p = p.getParent();
        }
        return false;
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {

        if (!isEnabled()) {
            return false;
        }
        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN:
                if (isInScrollingContainer()) {
                    mTouchDownX = event.getX();
                } else {
                    startDrag(event);
                }
                break;

            case MotionEvent.ACTION_MOVE:
                if (mIsDragging) {
                    trackTouchEvent(event);
                } else {
                    final float x = event.getX();
                    if (Math.abs(x - mTouchDownX) > mScaledTouchSlop) {
                        startDrag(event);
                    }
                }
                break;

            case MotionEvent.ACTION_UP:
                if (mIsDragging) {
                    trackTouchEvent(event);
                    onStopTrackingTouch();
                    setPressed(false);
                } else {
                    // Touch up when we never crossed the touch slop threshold should
                    // be interpreted as a tap-seek to that location.
                    onStartTrackingTouch();
                    trackTouchEvent(event);
                    onStopTrackingTouch();
                }
                // ProgressBar doesn't know to repaint the thumb drawable
                // in its inactive state when the touch stops (because the
                // value has not apparently changed)
                invalidate();
                break;

            case MotionEvent.ACTION_CANCEL:
                if (mIsDragging) {
                    onStopTrackingTouch();
                    setPressed(false);
                }
                invalidate(); // see above explanation
                break;
        }
        return true;
    }

    void onStopTrackingTouch() {
        mIsDragging = false;
        if (mOnSeekBarChangeListener != null) {
            mOnSeekBarChangeListener.onStopTrackingTouch(this);
        }
    }

    private void startDrag(MotionEvent event) {
        setPressed(true);

        if (mThumb != null) {
            // This may be within the padding region.
            invalidate(mThumb.getBounds());
        }

        onStartTrackingTouch();
        trackTouchEvent(event);
        attemptClaimDrag();
    }

    private void attemptClaimDrag() {
        if (getParent() != null) {
            getParent().requestDisallowInterceptTouchEvent(true);
        }
    }


    void onStartTrackingTouch() {
        mIsDragging = true;
        if (mOnSeekBarChangeListener != null) {
            mOnSeekBarChangeListener.onStartTrackingTouch(this);
        }
    }

    float mTouchProgressOffset;

    private void trackTouchEvent(MotionEvent event) {
        final int x = Math.round(event.getX());
        final int width = getWidth();
        final int availableWidth = width - getPaddingLeft() - getPaddingRight();

        final float scale;
        float progress = 0.0f;
        if (x < getPaddingLeft()) {
            scale = 0.0f;
        } else if (x > width - getPaddingRight()) {
            scale = 1.0f;
        } else {
            scale = (x - getPaddingLeft()) / (float) availableWidth;
            progress = mTouchProgressOffset;
        }

        final int range = mMax;
        progress += scale * range;

//        doRefreshProgress(android.R.id.progress, Math.round(progress), true);
        setProgress(Math.round(progress));
    }

    public void setOnSeekBarChangeListener(OnSeekBarChangeListener l) {
        mOnSeekBarChangeListener = l;
    }

}

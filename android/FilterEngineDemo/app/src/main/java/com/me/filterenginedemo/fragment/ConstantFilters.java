package com.me.filterenginedemo.fragment;


import com.me.filterenginedemo.R;

import java.util.ArrayList;
import java.util.List;

public class ConstantFilters {
    public static final int BEAUTIFY_WHITEN_MODE = 0x01;
    public static final int BEAUTIFY_BLUR_MODE = 0x02;
    public static final int BEAUTIFY_REDDEN_MODE = 0x03;
    public static final int ADJUST_BRIGHTNESS_MODE = 0x10;
    public static final int ADJUST_CONTRAST_MODE = 0x11;
    public static final int ADJUST_EXPOSURE_MODE = 0x12;
    public static final int ADJUST_HUE_MODE = 0x13;
    public static final int ADJUST_SHARPEN_MODE = 0x14;
    public static final int ADJUST_SATURATION_MODE = 0x15;

    static List<Filter> mFilterList;

    static {
        addFilters();
    }

    static void addFilters() {
        mFilterList = new ArrayList<Filter>();
        Filter origin = new Filter("origin", R.drawable.origin);
        mFilterList.add(origin);

        Filter antique = new Filter("antique", R.drawable.antique);
        mFilterList.add(antique);

        Filter blackcat = new Filter("blackcat", R.drawable.blackcat);
        mFilterList.add(blackcat);

        Filter cool = new Filter("cool", R.drawable.cool);
        mFilterList.add(cool);

        Filter whitecat = new Filter("whitecat", R.drawable.whitecat);
        mFilterList.add(whitecat);

        Filter romance = new Filter("romance", R.drawable.romance);
        mFilterList.add(romance);

        Filter latte = new Filter("latte", R.drawable.latte);
        mFilterList.add(latte);

        Filter sakura = new Filter("sakura", R.drawable.sakura);
        mFilterList.add(sakura);

        Filter emerald = new Filter("emerald", R.drawable.emerald);
        mFilterList.add(emerald);

        Filter evergreen = new Filter("evergreen", R.drawable.evergreen);
        mFilterList.add(evergreen);

        Filter crayon = new Filter("crayon", R.drawable.crayon);
        mFilterList.add(crayon);

        Filter sketch = new Filter("sketch", R.drawable.sketch);
        mFilterList.add(sketch);

        Filter nostalgia = new Filter("nostalgia", R.drawable.nostalgia);
        mFilterList.add(nostalgia);

        Filter healthy = new Filter("healthy", R.drawable.healthy);
        mFilterList.add(healthy);

        Filter sweets = new Filter("sweets", R.drawable.sweets);
        mFilterList.add(sweets);

        Filter tender = new Filter("tender", R.drawable.tender);
        mFilterList.add(tender);

        Filter calm = new Filter("calm", R.drawable.calm);
        mFilterList.add(calm);

        Filter warm = new Filter("warm", R.drawable.warm);
        mFilterList.add(warm);

        Filter sunset = new Filter("sunset", R.drawable.sunset);
        mFilterList.add(sunset);

        Filter sunrise = new Filter("sunrise", R.drawable.sunrise);
        mFilterList.add(sunrise);



        Filter I1977 = new Filter("I1977", R.drawable.i1977);
        mFilterList.add(I1977);

        Filter inkwell = new Filter("inkwell", R.drawable.inkwell);
        mFilterList.add(inkwell);

        Filter kelvin = new Filter("kelvin", R.drawable.kelvin);
        mFilterList.add(kelvin);

        Filter nashville = new Filter("nashville", R.drawable.nashville);
        mFilterList.add(nashville);

        Filter lomo = new Filter("lomo", R.drawable.lomo);
        mFilterList.add(lomo);

        Filter valencia = new Filter("valencia", R.drawable.valencia);
        mFilterList.add(valencia);

        Filter walden = new Filter("walden", R.drawable.walden);
        mFilterList.add(walden);

        Filter xproll = new Filter("xproll", R.drawable.xproll);
        mFilterList.add(xproll);

        Filter amaro = new Filter("amaro", R.drawable.amaro);
        mFilterList.add(amaro);

        Filter hudson = new Filter("hudson", R.drawable.hudson);
        mFilterList.add(hudson);

        Filter rise = new Filter("rise", R.drawable.rise);
        mFilterList.add(rise);

        Filter sierra = new Filter("sierra", R.drawable.sierra);
        mFilterList.add(sierra);

        Filter brannan = new Filter("brannan", R.drawable.brannan);
        mFilterList.add(brannan);

        Filter earlybird = new Filter("earlybird", R.drawable.earlybird);
        mFilterList.add(earlybird);

        Filter hefe = new Filter("hefe", R.drawable.hefe);
        mFilterList.add(hefe);

        Filter sutro = new Filter("sutro", R.drawable.sutro);
        mFilterList.add(sutro);

        Filter toaster = new Filter("toaster", R.drawable.toaster);
        mFilterList.add(toaster);




        Filter fairytale = new Filter("fairytale", R.drawable.fairytale);
        mFilterList.add(fairytale);

        Filter amatorka = new Filter("amatorka", R.drawable.amatorka);
        mFilterList.add(amatorka);

        Filter highkey = new Filter("highkey", R.drawable.highkey);
        mFilterList.add(highkey);
    }

    static List<Filter> getFilterList() {
        return mFilterList;
    }



}

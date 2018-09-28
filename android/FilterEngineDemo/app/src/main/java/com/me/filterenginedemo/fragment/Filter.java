package com.me.filterenginedemo.fragment;

public class Filter {

    private String name;
    private int imageId;

    public Filter(String name, int imageId) {
        this.name = name;
        this.imageId = imageId;
    }
    public String getName() {
        return name;
    }

    public int getImageId() {
        return imageId;
    }
}

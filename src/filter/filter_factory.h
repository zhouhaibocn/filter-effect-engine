//
// Created by zhouhaibo on 2017/9/25.
//

#ifndef FILTERENGINE_FILTER_FACTORY_H
#define FILTERENGINE_FILTER_FACTORY_H

#include "filter/base/multi_input_filter.h"

typedef enum {
    No_Filter,
    Antique_Filter = 0x01,
    Blackcat_Filter,
    Cool_Filter,
    Whitecat_Filter,
    Romance_Filter,
    Latte_Filter,
    Sakura_Filter,
    Emerald_Filter,
    Evergreen_Filter,
    Crayon_Filter,
    Sketch_Filter,
    Nostalgia_Filter,
    Healthy_Filter,
    Sweets_Filter,
    Tender_Filter,
    Calm_Filter,
    Warm_Filter,
    Sunset_Filter,
    Sunrise_Filter,

    I1977_Fliter = 0x21,
    Inkwell_Filter,
    Lordkelvin_Filter,
    Nashville_Filter,
    Lomo_Filter,
    Valencia_Filter,
    Walden_Filter,
    Xproll_Filter,
    Amaro_Filter,
    Hudson_Filter,
    Rise_Filter,
    Sierra_Filter,
    Brannan_Filter,
    Earlybird_Filter,
    Hefe_Filter,
    Sutro_Filter,
    Toaster_Filter,

    Fairytale_Filter = 0x41,
    Amatorka_Filter,
    Highkey_Filter
} FilterType ;


class FilterFactory {

public:
    FilterFactory();

    ~FilterFactory();

    static MultiInputFilter * createFilter(FilterType type);
};


#endif //FILTERENGINE_FILTER_FACTORY_H

//
// Created by zhouhaibo on 2017/9/25.
//

#include "filter_factory.h"

#include "filter/normal/antique_filter.h"
#include "filter/normal/blackcat_filter.h"
#include "filter/normal/cool_filter.h"
#include "filter/normal/whitecat_filter.h"
#include "filter/normal/romance_filter.h"
#include "filter/normal/latte_filter.h"
#include "filter/normal/sakura_filter.h"
#include "filter/normal/emerald_filter.h"
#include "filter/normal/evergreen_filter.h"
#include "filter/normal/crayon_filter.h"
#include "filter/normal/sketch_filter.h"
#include "filter/normal/nostalgia_filter.h"
#include "filter/normal/healthy_filter.h"
#include "filter/normal/sweets_filter.h"
#include "filter/normal/tender_filter.h"
#include "filter/normal/calm_filter.h"
#include "filter/normal/warm_filter.h"
#include "filter/normal/sunset_filter.h"
#include "filter/normal/sunrise_filter.h"
#include "filter/normal/lookup_filter.h"

#include "filter/advanced/amaro_filter.h"
#include "filter/advanced/brannan_filter.h"
#include "filter/advanced/earlybird_filter.h"
#include "filter/advanced/hefe_filter.h"
#include "filter/advanced/hudson_filter.h"
#include "filter/advanced/I1977_filter.h"
#include "filter/advanced/inkwell_filter.h"
#include "filter/advanced/lomo_filter.h"
#include "filter/advanced/lordkelvin_filter.h"
#include "filter/advanced/nashville_filter.h"
#include "filter/advanced/rise_filter.h"
#include "filter/advanced/sierra_filter.h"
#include "filter/advanced/sutro_filter.h"
#include "filter/advanced/toaster_filter.h"
#include "filter/advanced/valencia_filter.h"
#include "filter/advanced/walden_filter.h"
#include "filter/advanced/xproll_filter.h"

FilterFactory::FilterFactory() {

}

FilterFactory::~FilterFactory() {

}

MultiInputFilter* FilterFactory::createFilter(FilterType type) {
    MultiInputFilter *filter = NULL;
    switch (type) {
        case No_Filter:
            break;
        // normal
        case Antique_Filter :
            filter = new AntiqueFilter();
            break;
        case Blackcat_Filter:
            filter = new BlackcatFilter();
            break;
        case Cool_Filter:
            filter = new CoolFilter();
            break;
        case Whitecat_Filter:
            filter = new WhitecatFilter();
            break;
        case Romance_Filter:
            filter = new RomanceFilter();
            break;
        case Latte_Filter:
            filter = new LatteFilter();
            break;
        case Sakura_Filter:
            filter = new SakuraFilter();
            break;
        case Emerald_Filter:
            filter = new EmeraldFilter();
            break;
        case Evergreen_Filter:
            filter = new EvergreenFilter();
            break;
        case Crayon_Filter:
            filter = new CrayonFilter();
            break;
        case Sketch_Filter:
            filter = new SketchFilter();
            break;
        case Nostalgia_Filter:
            filter = new NostalgiaFilter();
            break;
        case Healthy_Filter:
            filter = new HealthyFilter();
            break;
        case Sweets_Filter:
            filter = new SweetsFilter();
            break;
        case Tender_Filter:
            filter = new TenderFilter();
            break;
        case Calm_Filter:
            filter = new CalmFilter();
            break;
        case Warm_Filter:
            filter = new WarmFilter();
            break;
        case Sunset_Filter:
            filter = new SunsetFilter();
            break;
        case Sunrise_Filter:
            filter = new SunriseFilter();
            break;

        // advanced
        case I1977_Fliter:
            filter = new I1977Filter();
            break;
        case Inkwell_Filter:
            filter = new InkwellFilter();
            break;
        case Lordkelvin_Filter:
            filter = new LordkelvinFilter();
            break;
        case Nashville_Filter:
            filter = new NashvilleFilter();
            break;
        case Lomo_Filter:
            filter = new LomoFilter();
            break;
        case Valencia_Filter:
            filter = new ValenciaFilter();
            break;
        case Walden_Filter:
            filter = new WaldenFilter();
            break;
        case Xproll_Filter:
            filter = new XprollFilter();
            break;
        case Amaro_Filter:
            filter = new AmaroFilter();
            break;
        case Hudson_Filter:
            filter = new HudsonFilter();
            break;
        case Rise_Filter:
            filter = new RiseFilter();
            break;
        case Sierra_Filter:
            filter = new SierraFilter();
            break;
        case Brannan_Filter:
            filter = new BrannanFilter();
            break;
        case Earlybird_Filter:
            filter = new EarlybirdFilter();
            break;
        case Hefe_Filter:
            filter = new HefeFilter();
            break;
        case Sutro_Filter:
            filter = new SutroFilter();
            break;
        case Toaster_Filter:
            filter = new ToasterFilter();
            break;

        // lookup
        case Fairytale_Filter:
        case Amatorka_Filter:
        case Highkey_Filter:
            filter = new LookupFilter();
            break;
    }

    return filter;
}



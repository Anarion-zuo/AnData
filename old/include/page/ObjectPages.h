//
// Created by anarion on 7/11/20.
//

#ifndef ANDATA_OBJECTPAGES_H
#define ANDATA_OBJECTPAGES_H

#include "PageManager.h"

namespace anarion {
    /*
     * Page Manager for a continuous region of memory
     *
     *
     *
     * should support:
     *      fetch pages by index
     *      pin a page
     *      load/unload a page manually
     */
    class ObjectPages {
    protected:
        PageManager *pageManager;
    public:

    };
}

#endif //ANDATA_OBJECTPAGES_H

//
// Created by anarion on 7/12/20.
//

#ifndef ANDATA_PAGEMAPPEDOBJECT_H
#define ANDATA_PAGEMAPPEDOBJECT_H

#include "PageManager.h"

namespace anarion {
    class PageMappedObject {
    protected:
        PageManager &manager;
        SString name;

        size_type pageCount = 0;
        Page **pages = nullptr;
    public:
        explicit PageMappedObject(anarion::PageManager &manager, size_type pageCount);

        Page *getPageByIndex(size_type index);
    };
}

#endif //ANDATA_PAGEMAPPEDOBJECT_H

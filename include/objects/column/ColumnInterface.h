//
// Created by anarion on 7/24/20.
//

#ifndef ANDATA_COLUMNINTERFACE_H
#define ANDATA_COLUMNINTERFACE_H

#include "page/PageMappedObject.h"

namespace anarion {
    class ColumnInterface : public PageMappedObject {
    protected:

        /*
         * @elementCount
         * Keeps statistics on the number of elements.
         */
        size_type elementCount = 0;

    public:
        ColumnInterface(PageManager &manager, SString &&name)
            : PageMappedObject(manager, forward<SString>(name)), elementCount(0) {}

        constexpr size_type getElementCount() const { return elementCount; }

        virtual void insert(const char *data, size_type targetIndex) = 0;
        virtual void fetch(char *data, size_type index) = 0;
        virtual void update(const char *data, size_type index) = 0;
        virtual void remove(size_type index) = 0;
    };
}

#endif //ANDATA_COLUMNINTERFACE_H

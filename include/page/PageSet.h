//
// Created by anarion on 7/12/20.
//

#ifndef ANDATA_PAGESET_H
#define ANDATA_PAGESET_H

#include <container/List/Vector.hpp>
#include <base/container/List/BitArray.h>

namespace anarion {
    class PageSet {
    protected:
    public:
        void writePage(size_type index, const char *data);
        void readPage(size_type index, char *data) const ;

        void setPageNull(size_type index);
    };
}

#endif //ANDATA_PAGESET_H

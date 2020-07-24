//
// Created by anarion on 6/23/20.
//

#ifndef ANDATA_FIXEDCOLUMN_H
#define ANDATA_FIXEDCOLUMN_H

#include <base/container/SString.h>
#include <page/PageManager.h>

namespace anarion {
    class FixedColumn {
    protected:
        /*
         * Pre-specified attributes
         * must be ready after construction
         *
         * These fields are stored and retrieved from files
         *
         * @itemLength
         *  length of an item stored in the fixed-length column
         *  such as: long 8bytes
         *  not binding types here, only length
         * @itemCount
         *  How many items are stored in this column
         */
        size_type itemLength, itemCount;

        /*
         * Memory allocation unit
         * initialized to be constant reference so that
         *      cannot be changed afterwards
         *      cannot be changed by oneself
         */
        PageManager &pageManager;

        /*
         * Pages
         * pointers to all pages
         * allocated with target length
         *
         * nullptr if the page is not loaded
         */
        Page **pages = nullptr;
        size_type pageCount = 0;

    public:

        // initialize item length in bytes
        FixedColumn(PageManager &pageManager, size_type itemLength, size_type itemCount = 0);

        void getByIndex(size_type index, char *buf) const ;
        void setByIndex(size_type index, const char *buf);
    };
}

#endif //ANDATA_FIXEDCOLUMN_H

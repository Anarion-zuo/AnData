//
// Created by anarion on 7/12/20.
//

#ifndef ANDATA_PAGEMAPPEDOBJECT_H
#define ANDATA_PAGEMAPPEDOBJECT_H

#include <container/SString.h>

namespace anarion {
    class PageManager;
    class PageMappedObject {
    protected:
        SString name;
        Vector<size_type> pageManagerIndexes;
        PageManager &manager;

        /*
         * @computeIndexes
         * Translating index into page forms, used almost everywhere.
         * returned boolean indicates whether the index overflows.
         */
        bool computeIndexes(size_type byteIndex, size_type *pageIndex, size_type *pageOffset);

        size_type &getPageManagerIndex(size_type pageIndex);
    public:
        PageMappedObject(PageManager &manager, SString &&name);
        virtual ~PageMappedObject() = default;

        void setPageNull(size_type index);
        bool isPageNull(size_type index);
        constexpr const SString &getName() const { return name; }
        void setPage(size_type index, size_type managerIndex);

        void write(size_type beginPageIndex, size_type beginPageOffset, const char *data, anarion::size_type length);
        void read(size_type beginPageIndex, size_type beginPageOffset, char *data, anarion::size_type length);
    };
}

#endif //ANDATA_PAGEMAPPEDOBJECT_H

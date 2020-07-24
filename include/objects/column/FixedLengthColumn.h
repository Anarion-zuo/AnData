//
// Created by anarion on 7/23/20.
//

#ifndef ANDATA_FIXEDLENGTHCOLUMN_H
#define ANDATA_FIXEDLENGTHCOLUMN_H

#include <base/container/List/BitArray.h>
#include "space_manager/IndexedFreeSpaceManager.h"
#include "objects/column/ColumnInterface.h"

namespace anarion {
    /*
     * class FixedLengthColumn
     * An array or a column for a database object.
     *
     * An object can be constructed 2 ways.
     *      By default constructor
     *      By reading from existing files
     *
     * Client programs should view this object as an continuous unordered array of elements. The object keeps no order in memory or on disk, for the convenience of space management and efficiency.
     * However, an element of the array should be able to be indexed by some index, virtually randomly set. Indexing components should be able to use such utility as client codes, thus decoupling storage and indexing components.
     */
    class FixedLengthColumn : public ColumnInterface {
    protected:
        /* @elementLength
        * The length of an element may not be altered, once specified.
        */
        const size_type elementLength;

        void computeElementIndices(size_type elementIndex, size_type *pageIndex, size_type *pageOffset) const ;

        template<typename T>
        char *toCharPointer(T &objRef) const { return reinterpret_cast<char *>(&objRef); }
        template<typename T>
        const char *toCharPointer(const T &objRef) const { return reinterpret_cast<const char *>(&objRef); }

    public:
        FixedLengthColumn(PageManager &manager, SString &&name, size_type elementLength);
        ~FixedLengthColumn() override = default;

        constexpr size_type getElementLength() const { return elementLength; }

        /*
         * CRUD utilities
         *
         * Other utilities operates according to an index.
         */
        void insert(const char *data, size_type targetIndex) override ;
        void fetch(char *data, size_type index) override ;
        void update(const char *data, size_type index) override ;
        void remove(size_type index) override ;
    };
}

#endif //ANDATA_FIXEDLENGTHCOLUMN_H

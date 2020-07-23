//
// Created by anarion on 7/23/20.
//

#ifndef ANDATA_FIXEDARRAY_H
#define ANDATA_FIXEDARRAY_H

#include <base/container/List/BitArray.h>
#include "PageMappedObject.h"
#include "IndexedFreeSpaceManager.h"

namespace anarion {
    /*
     * class FixedArray
     * An array or a column for a database object.
     *
     * An object can be constructed 2 ways.
     *      By default constructor
     *      By reading from existing files
     *
     * Client programs should view this object as an continuous unordered array of elements. The object keeps no order in memory or on disk, for the convenience of space management and efficiency.
     * However, an element of the array should be able to be indexed by some index, virtually randomly set. Indexing components should be able to use such utility as client codes, thus decoupling storage and indexing components.
     */
    class FixedArray : public PageMappedObject {
    protected:
        /*
         * @elementLength
         * The length of an element may not be altered, once specified.
         *
         * @elementCount
         * Keeps statistics on the number of elements.
         */
        const size_type elementLength;
        size_type elementCount = 0;

        /*
         * @freeSpaceManager
         * The space manager.
         * Keeps no actual space but accounts for the used space.
         */
        IndexedFreeSpaceManager freeSpaceManager {0};

        void computeElementIndices(size_type elementIndex, size_type *pageIndex, size_type *pageOffset) const ;
    public:
        FixedArray(PageManager &manager, SString &&name, size_type elementLength);
        ~FixedArray() override = default;

        /*
         * CRUD utilities
         *
         * @insert
         * Inserts an element in a right place.
         * The inserting place is determined by a free space manager
         *
         * Other utilities operates according to an index.
         */
        void insert(const char *data);
        void fetch(char *data, size_type index);
        void update(const char *data, size_type index);
        void remove(size_type index);
    };
}

#endif //ANDATA_FIXEDARRAY_H

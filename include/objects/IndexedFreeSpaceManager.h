//
// Created by anarion on 7/23/20.
//

#ifndef ANDATA_INDEXEDFREESPACEMANAGER_H
#define ANDATA_INDEXEDFREESPACEMANAGER_H

#include <base/container/List/Vector.hpp>

namespace anarion {
    class IndexedFreeSpaceManager {
    protected:
        /*
         * Uses a simple trick of linked list.
         * @arrHead indexes the first free slot in @indexArray. If a slot signifies a free slot, the value of that slot in @indexArray is the index of the next free slot.
         */
        Vector<size_type> indexArr;
        size_type arrayHead = 0;

        void makeAscend(size_type beginIndex, size_type length);

    public:

        explicit IndexedFreeSpaceManager(size_type slotCount);
        ~IndexedFreeSpaceManager() = default;

        constexpr size_type getSlotCount() const { return indexArr.size(); }

        size_type getFree();
        void setFree(size_type index);
        void resize(size_type newSize);
    };
}

#endif //ANDATA_INDEXEDFREESPACEMANAGER_H

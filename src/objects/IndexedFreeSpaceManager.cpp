//
// Created by anarion on 7/23/20.
//

#include "objects/IndexedFreeSpaceManager.h"

anarion::size_type anarion::IndexedFreeSpaceManager::getFree() {
    size_type ret = arrayHead;
    size_type &slot = indexArr.get(arrayHead);
    if (slot == -1) {
        // end of list
        return -1;
    }
    arrayHead = slot;
    slot = -1;
    return ret;
}

void anarion::IndexedFreeSpaceManager::setFree(anarion::size_type index) {
    size_type &slot = indexArr.get(index);
    slot = arrayHead;
    arrayHead = index;
}

void anarion::IndexedFreeSpaceManager::resize(anarion::size_type newSize) {
    size_type oldSize = indexArr.size();
    if (oldSize == newSize) { return; }
    if (newSize < oldSize) {   // make list shorter
        size_type tail;
        // move the head in range
        while (arrayHead >= newSize) {
            arrayHead = indexArr.get(arrayHead);
        }
        size_type cur = arrayHead, pre;
        while (true) {
            // find the first node out of range
            do {
                pre = cur;
                cur = indexArr.get(cur);
            } while (cur < newSize);
            if (cur == -1) {
                // comes to the end of the linked list
                indexArr.get(tail) = -1;
                break;
            }
            tail = pre;
            // find the first node in range
            do {
                cur = indexArr.get(cur);
            } while (cur >= newSize);
            // connect both ends
            indexArr.get(tail) = cur;
            if (cur == -1) {
                // end of linked list
                break;
            }
        }
        // do expand
        indexArr.resize(newSize);
    } else {
        // do expand first
        indexArr.resize(newSize);
        // sequential list
        makeAscend(oldSize, newSize - oldSize);
        // append to original
        indexArr.get(newSize - 1) = arrayHead;
        arrayHead = oldSize;
    }
}

anarion::IndexedFreeSpaceManager::IndexedFreeSpaceManager(anarion::size_type slotCount) : indexArr(slotCount, 0) {
    makeAscend(0, slotCount);
}

void anarion::IndexedFreeSpaceManager::makeAscend(anarion::size_type beginIndex, anarion::size_type length) {
    for (size_type index = beginIndex; index < length + beginIndex; ++index) {
        indexArr.get(index) = index + 1;
    }
    indexArr.get(length - 1) = -1;
}

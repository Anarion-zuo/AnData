//
// Created by anarion on 6/23/20.
//

#include "objects/FixedColumn.h"

void anarion::FixedColumn::computeBufferCount() {
    bufferCount = byteCount / bufferSize;
}

void anarion::FixedColumn::computeByteCount() {
    byteCount = itemCount * itemLength;
}

void anarion::FixedColumn::getBufferCoordinate(
        anarion::size_type index,
        anarion::size_type *bufferIndex,
        anarion::size_type *bufferOffset
        ) {
    *bufferIndex = index / bufferSize;
    *bufferOffset = index % bufferSize;
}

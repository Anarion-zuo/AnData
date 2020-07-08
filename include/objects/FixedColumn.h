//
// Created by anarion on 6/23/20.
//

#ifndef ANDATA_FIXEDCOLUMN_H
#define ANDATA_FIXEDCOLUMN_H

#include <base/container/SString.h>

namespace anarion {
    class FileBlockManager;
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
         * @bufferSize
         *  how large is a single buffer
         */
        size_type itemLength, itemCount, bufferSize;
        SString name;
        // finds out the place in the buffers with raw index
        void getBufferCoordinate(size_type index, size_type *bufferIndex, size_type *bufferOffset);

        /*
         * Post-computed attributes
         * computed in construction
         * computed from pre-specified attributes
         *
         * @byteCount
         *  how many bytes are stored in this column
         * @bufferCount
         *  how many buffers are required to hold the whole column
         */
        size_type byteCount, bufferCount;
        // compute methods called by constructors
        // the first depends on the second
        void computeBufferCount();
        void computeByteCount();

        /*
         * Memory management attributes
         * independent of others
         */
//        FixedBuffer *buffers = nullptr;

        /*
         * File management attributes
         * files are organized such that they form a large array
         */
        FileBlockManager *fileBlockManager;


    public:

        FixedColumn(size_type itemLength, size_type itemCount);
    };
}

#endif //ANDATA_FIXEDCOLUMN_H

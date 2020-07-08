//
// Created by anarion on 7/8/20.
//

#ifndef ANDATA_PAGEMANAGER_H
#define ANDATA_PAGEMANAGER_H

#include <base/container/base/container_utility.hpp>
#include <io/channel/file/Directory.h>
#include "Page.h"

namespace anarion {
    class PageManager {
    protected:

        // size of each frame
        size_type frameLength = 4096;
        size_type frameMaxNumber = 100;
        size_type frameByteCount;

        // directory storing the frames in disk
        Directory directory;

        char *frameHead = nullptr;
        void initializeFrameSpace();
        size_type frameIndex2ByteIndex(size_type frameIndex) const ;
        char *getFrameHeadByIndex(size_type frameIndex) const ;

        SString buildFileName(const anarion::SString &colName, anarion::size_type pageIndex);
        void zeroFrame(size_type frameIndex);
    public:
        ~PageManager();
        explicit PageManager(SString &&dirName) : directory(forward<SString>(dirName)) { initializeFrameSpace(); }
        PageManager(SString &&dirName, size_type frameLength) : directory(forward<SString>(dirName)), frameLength(frameLength) { initializeFrameSpace(); }
        PageManager(SString &&dirName, size_type frameLength, size_type frameMaxNumber) : directory(forward<SString>(dirName)), frameLength(frameLength), frameMaxNumber(frameMaxNumber) { initializeFrameSpace(); }

        Page *load(const SString &colName, size_type pageIndex);
        void unload(Page *page, const SString &colName);
    };
}

#endif //ANDATA_PAGEMANAGER_H

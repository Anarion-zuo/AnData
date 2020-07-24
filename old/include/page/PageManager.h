//
// Created by anarion on 7/8/20.
//

#ifndef ANDATA_PAGEMANAGER_H
#define ANDATA_PAGEMANAGER_H

#include <base/container/base/container_utility.hpp>
#include <io/channel/file/Directory.h>
#include <DataBaseException.h>
#include "Page.h"
#include <concurrent/base/BackgroundTask.h>

namespace anarion {

    struct PageManagerException : public DataBaseException {};
    struct DuplicateObjectNameException : public PageManagerException {};

    class PageMappedObject;
    class PageManager {
    protected:

        // size of each frame
        size_type pageLength = 4096;
        size_type pageMaxNumber = 100;
        size_type pageByteCount;

        // object belongings
        PageMappedObject **belongedObjects = nullptr;
        HashMap<Page*, size_type> page2Index;

        // directory storing the frames in disk
        Directory directory;

        char *pageHead = nullptr;
        long *usedFlags = nullptr;
        size_type evictableIndex = 0;
        void initializeFrameSpace();
        size_type pageIndex2ByteIndex(size_type frameIndex) const ;
        char *getPageHeadByIndex(size_type frameIndex) const ;
        bool getUsedFlag(size_type index) const ;
        void setUsedFlag(size_type index) ;
        void clearUsedFlag(size_type index);

        // LRU
        size_type currentSweepingIndex = 0;
        struct ClockSweeper : public BackgroundTask {
            PageManager *_this;

            explicit ClockSweeper() : BackgroundTask(Time(1, 0)) {}
            void task() override;
        } clockSweeper;

        SString buildFileName(const anarion::SString &colName, anarion::size_type pageIndex);
        void zeroPage(size_type frameIndex);

        Page *load(const SString &objName, size_type objPageIndex, size_type pageIndex);
        size_type getEvictingIndex() const ;

    public:
        ~PageManager();
        explicit PageManager(SString &&dirName) : directory(forward<SString>(dirName)) { initializeFrameSpace(); }
        PageManager(SString &&dirName, size_type frameLength) : directory(forward<SString>(dirName)), pageLength(frameLength) { initializeFrameSpace(); }
        PageManager(SString &&dirName, size_type frameLength, size_type frameMaxNumber) : directory(forward<SString>(dirName)), pageLength(frameLength), pageMaxNumber(frameMaxNumber) { initializeFrameSpace(); }

        void unload(Page *page, const SString &objName);

        constexpr size_type getFrameLength() const { return pageLength; }

        Page *getPageByName(const PageMappedObject &mappedObj, size_type index);
    };
}

#endif //ANDATA_PAGEMANAGER_H

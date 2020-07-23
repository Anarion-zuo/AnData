//
// Created by anarion on 7/12/20.
//

#ifndef ANDATA_PAGEMANAGER_H
#define ANDATA_PAGEMANAGER_H

#include <objects/PageMappedObject.h>
#include <base/io/channel/file/Directory.h>
#include <base/concurrent/base/BackgroundTask.h>
#include <base/io/channel/file/FileChannel.h>
#include <base/container/List/BitArray.h>
#include "PageSet.h"

namespace anarion {
    struct PageException : public std::exception {};
    struct PageFileExistsException : public PageException {};

    class PageManager {
    protected:
        /*
         * The manager must know whose frame this is and which index, or the system malfunctions when a page is evicted.
         * @pageSpace and @pageInfo are allocated in the constructors. @pageLength and @pageCount must be specified in the constructor, whether by manual input or by reading some configuration file.
         *
         * @pageSpace
         * A very large continuous memory region for all pages.
         * The size of this region is specified by attribute @pageLength in bytes and @pageCount. The total byte count is computed by pageLength * pageCount.
         * The bytes are separated manually. A page index is the index of a certain page, not a certain byte. The index of the first byte of a page can be easily computed with its page index, as in @getPageHeadByIndex.
         *
         * @pageInfo
         * Noting which object holds the corresponding page at which index.
         * The infos objects are indexed in the same way as @pageSpace. With the same index, one may find the first byte of a page and its info.
         * When a page is evicted, the corresponding pageInfo must be altered accordingly.
         * A PageInfo object is set all 0 if the page is not occupied.
         *
         * @pageLength
         * The length of a single page. Must be specified when the object actually runs.
         *
         * @pageCount
         * How many pages are governed by this manager.
         */
        struct PageInfo {
            PageMappedObject *setPointer = nullptr;
            size_type setIndex = 0;
        };
        char *pageSpace = nullptr;
        PageInfo *pageInfo = nullptr;
        size_type pageLength = 0, pageCount = 0;
        constexpr char *getPageHeadByIndex(size_type pageIndex) const { return pageSpace + pageIndex * pageLength; }
        constexpr size_type getByteCount() const { return pageLength * pageCount; }

        // directory operator
        Directory directory;

        /*
         * The actual code of the constructors in a single function.
         * All constructors runs procedures with few differences, thus can be conveniently organized by this single function.
         */
        void constructor(size_type pageLength, size_type pageCount);

        /*
         * Approximating LRU mechanism
         * The scanner keeps @evictCandidateIndex to be the approximated least used page.
         * All page usages are organized in a bitmap. When a PageSet object uses a page, the page is marked as 1 in the bitmap by the PageSet calling @setUsedFlag.
         * The pages are scanned periodically among some time interval. If the page is marked, clear the mark and move on, otherwise set @evictCandidateIndex pointing to this page.
         *
         * @usageBitMap
         * The bitmap
         *
         * @bitMapLongLength
         * The number of size_type objects to be allocated for the bit map
         */
        struct EvictScanner : public BackgroundTask {
            PageManager *_this;

            EvictScanner() : BackgroundTask(Time(1, 0)) {}
            void task() override;
        } evictScanner;
        size_type evictCandidateIndex = 0;
        BitArray usageBitMap;
        void unloadPage(FileChannel &file, size_type pageIndex);

        /*
         * Markers whether the pages are dirty
         * Object must set the corresponding bit when writing to a page.
         */
        BitArray pagesDirty;

    public:
        explicit PageManager(SString &&storageRootDirName, size_type pageLength, size_type pageCount) : directory(forward<SString>(storageRootDirName)) { constructor(pageLength, pageCount); }
        ~PageManager();

        constexpr size_type getPageLength() const { return pageLength; }
        constexpr size_type getPageCount() const { return pageCount; }

        void setUsageBitMap(size_type index);
        void setDirtyBit(size_type index);

        /*
         * @getPage
         * Fetch a page from the manager to a page-mapped object.
         * When a PageSet is requested to perform operations on certain pages not in memory, the PageSet object calls to its manager to fetch the page from disk.
         * When this function is called, the system is sure that the requested page is not in memory, or the system malfunctions. This is achieved by noting  out-of-memory page in the PageSet object to be nullptr.
         *
         * The function invokes system io and evicts some page. The choice of page to evict is determined by the approximated LRU mechanism.
         */
        void getPage(PageMappedObject *object, size_type objIndex);

        size_type writePage(size_type pageIndex, size_type offset, const char *data, size_type dataLength);
        size_type readPage(size_type pageIndex, size_type offset, char *data, size_type dataLength) const ;
        void unloadAll();
    };
}

#endif //ANDATA_PAGEMANAGER_H

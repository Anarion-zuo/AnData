//
// Created by anarion on 7/8/20.
//

#ifndef ANDATA_PAGE_H
#define ANDATA_PAGE_H

#include <base/container/base/container_utility.hpp>
#include <base/container/SString.h>

namespace anarion {
    class Page {
    protected:
        char *frameHead = nullptr;
        size_type frameLength = 0, frameIndex;

        bool isDirty = false;

    public:
        Page(char *frameHead, size_type frameLength, size_type frameIndex);

        bool checkIsDirty() const { return isDirty; }
        constexpr size_type getFrameIndex() const { return frameIndex; }

        void write(const char *data, size_type length, size_type byteIndex);
        void read(char *data, size_type length, size_type byteIndex) const ;
    };
}

#endif //ANDATA_PAGE_H

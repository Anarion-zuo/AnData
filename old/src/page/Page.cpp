//
// Created by anarion on 7/8/20.
//

#include "page/Page.h"

anarion::Page::Page(char *frameHead, anarion::size_type frameLength, size_type frameIndex)
    : frameHead(frameHead), frameLength(frameLength), frameIndex(frameIndex) {

}

void anarion::Page::write(const char *data, anarion::size_type length, anarion::size_type byteIndex) {
    isDirty = true;
    memcpy(frameHead + byteIndex, data, length);
}

void anarion::Page::read(char *data, anarion::size_type length, anarion::size_type byteIndex) const {
    memcpy(data, frameHead + byteIndex, length);
}

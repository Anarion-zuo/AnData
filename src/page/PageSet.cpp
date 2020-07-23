//
// Created by anarion on 7/12/20.
//

#include "page/PageSet.h"

void anarion::PageSet::setPageNull(anarion::size_type index) {
    pageHeads.get(index) = nullptr;
}

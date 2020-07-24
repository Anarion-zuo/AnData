//
// Created by anarion on 7/12/20.
//

#include <page/PageMappedObject.h>

#include "page/PageMappedObject.h"

anarion::Page *anarion::PageMappedObject::getPageByIndex(anarion::size_type index) {
    return pages[index];
}

anarion::PageMappedObject::PageMappedObject(anarion::PageManager &manager, size_type pageCount)
    : manager(manager), pageCount(pageCount), pages(static_cast<Page **>(operator new(sizeof(void *) * pageCount))) {

}

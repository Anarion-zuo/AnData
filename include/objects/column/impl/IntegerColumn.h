//
// Created by anarion on 7/24/20.
//

#ifndef ANDATA_INTEGERCOLUMN_H
#define ANDATA_INTEGERCOLUMN_H

#include "objects/column/FixedLengthColumn.h"

namespace anarion {
    class IntegerColumn : public FixedLengthColumn {
    public:
        IntegerColumn(anarion::PageManager &manager, anarion::SString &&name);
        ~IntegerColumn() override = default;

        void insert(int number, size_type index);
        int fetch(size_type index);
        void update(size_type index, int number);
    };
}

#endif //ANDATA_INTEGERCOLUMN_H

//
// Created by anarion on 7/24/20.
//

#ifndef ANDATA_TABLE_H
#define ANDATA_TABLE_H

#include "objects/column/ColumnInterface.h"
#include <page/PageManager.h>
#include <space_manager/IndexedFreeSpaceManager.h>

namespace anarion {
    /*
     * class Table
     * The object for table management.
     *
     * A table is an assembly of tuples, while the storage model is column oriented. The utilities should include the extraction of a tuple for given indices.
     * Such utilities as finding objects and indexing should not be included as a member of a table, for those implementations should be independent of the storage model. The storage model such as Table or Column should give necessary APIs for those implementations.
     */
    class Table {
    protected:
        /*
         * @name
         * Name of the table.
         * Name of the directory in file system of the table.
         *
         * @pageManager
         * Handle to operate on disk space.
         *
         * @columns
         * Each column must be initialized with the reference of pageManager & freeSpaceManager
         */
        SString name;
        PageManager pageManager;
        Vector<ColumnInterface *> columns;
        HashMap<SString, size_type> name2ColIndex;

        /*
         * @initSlotCount
         * The number initial slots given to a column.
         * Also the initial value of freeSpaceManager.
         */
        static const size_type initSlotCount = 256;
        /*
         * @freeSpaceManager
         * The space manager.
         * Keeps no actual space but accounts for the used space.
         */
        IndexedFreeSpaceManager freeSpaceManager;
        size_type getFreeIndex();

        ColumnInterface *makeColumn(SString &&colName, size_type elementLength);

    public:
        Table(Directory &directory, SString &&name, size_type pageLength, size_type pageCount);
        ~Table();

        constexpr size_type getColumnCount() const { return columns.size(); }
        constexpr const SString &getName() const { return name; }
        const ColumnInterface &getColumn(size_type index) const { return *columns.get(index); }

        size_type insert(size_type colIndex, const char *data);
        void fetch(size_type colIndex, size_type rowIndex, char *data);
        void update(anarion::size_type colIndex, size_type rowIndex, const char *data);
        void remove(size_type colIndex, anarion::size_type rowIndex);

        void appendColumn(SString &&colName, anarion::size_type elementLength);
    };
}

#endif //ANDATA_TABLE_H

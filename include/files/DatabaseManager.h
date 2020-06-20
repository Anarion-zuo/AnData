//
// Created by 左钰 on 2020/6/17.
//

#ifndef ANDATA_DATABASEMANAGER_H
#define ANDATA_DATABASEMANAGER_H

#include <io/channel/file/Directory.h>
#include "TableManager.h"
#include "FileBlockManager.h"

/*
 * General structure:
 *      DBMS
 *          Databases
 *              Tables
 *                  Columns
 * Jobs of the managers:
 *  - allocate/deallocate files in the file system
 *  - packaged io operations
 */

namespace anarion {
    class DatabaseManager {
    protected:
        /*
         * mapping from a name to a named table
         */
        HashMap<SString, TableManager> name2table;

        /*
         * for file allocation/deallocation/read/write
         */
        FileBlockManager blockManager;

    public:

    };
}

#endif //ANDATA_DATABASEMANAGER_H

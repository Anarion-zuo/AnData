project(AnData)

set(CMAKE_CXX_STANDARD 14)

add_library(anariondata
        page/PageMappedObject.cpp
        objects/FixedLengthColumn.cpp
        space_manager/IndexedFreeSpaceManager.cpp

        objects/IntegerColumn.cpp

        objects/Table.cpp
        objects/TableMetaData.cpp

        page/PageManager.cpp
        )

add_library(anarionbase STATIC IMPORTED)
set_target_properties(anarionbase PROPERTIES IMPORTED_LOCATION ../lib/libanarionbase.a)

target_link_libraries(anariondata pthread anarionbase)
include_directories(../include)
include_directories(../include/base)
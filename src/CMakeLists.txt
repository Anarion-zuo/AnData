project(AnData)

set(CMAKE_CXX_STANDARD 14)

add_library(anariondata data.cpp
        series/Array.cpp
        series/Series.cpp
        series/Matrix.cpp

        numbers/Number.cpp
        numbers/Integers.cpp

        operators/ArrayOperator.cpp
        operators/ArrayTransformer.cpp

        files/DatabaseManager.cpp
        files/FileBlockManager.cpp
        files/TableManager.cpp
        )

add_library(anarionbase STATIC IMPORTED)
set_target_properties(anarionbase PROPERTIES IMPORTED_LOCATION ../lib/libanarionbase.a)

target_link_libraries(anariondata pthread anarionbase)
include_directories(../include)
include_directories(../include/base)
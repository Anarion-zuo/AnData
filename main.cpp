
#include <page/PageManager.h>
#include <objects/column/FixedLengthColumn.h>
#include <objects/column/impl/IntegerColumn.h>
#include <objects/table/Table.h>

using namespace std;
using namespace anarion;

int main() {
    Directory rootStorage(SString("/home/anarion/Downloads/testdir/table/"));

    Table table(rootStorage, SString("testTable"), 1024, 100);
    table.appendColumn(SString("xyz"), 4);
    table.appendColumn(SString("123"), 4);
//    table.insert(1, "1234");
    table.insert(0, "abcd");

    return 0;
}

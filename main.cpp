#include <page/PageManager.h>

using namespace std;
using namespace anarion;

int main() {
    PageManager pageManager(SString("/home/anarion/testdir/"));
    SString colName("testcol");
    Page * page = pageManager.load(colName, 0);
    page->write("12345", 5, 0);
    pageManager.unload(page, colName);
    return 0;
}

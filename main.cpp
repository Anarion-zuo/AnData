
#include <page/PageManager.h>
#include <objects/FixedArray.h>

using namespace std;
using namespace anarion;

int main() {
    PageManager pageManager(SString("/home/anarion/Downloads/testdir/"), 1024, 100);

    FixedArray fixedArray(pageManager, SString("ArrayTest"), 1);
    const char *data = "1";
    fixedArray.insert(data);
    fixedArray.insert(data);
    fixedArray.insert(data);
    fixedArray.insert(data);
    fixedArray.remove(2);
    fixedArray.insert("2");
    pageManager.unloadAll();
    return 0;
}

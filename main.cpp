#include <series/Array.h>
#include <operators/ArrayOperator.h>

using namespace std;
using namespace anarion;

int main() {
    ArrayInterface *array = new BigFloatArray;
    for (float64 x = 0; x < 1000; x += .01) {
        array->push_back(x);
    }
    ArrayOperator().standardize(*array);
    return 0;
}

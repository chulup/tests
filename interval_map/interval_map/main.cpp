#include "stdafx.h"

#include <cstdlib>

#include "interval_map.h"
#include "interval_array.h"

using namespace std;

static const size_t START = 0;
static const size_t END = 10;

size_t tests = 0;
size_t failed = 0;

void test(size_t start, size_t end, int v) {
    static interval_map<size_t, int> map(-1);
    static interval_array<int, START, END> array(-1);
    tests++;

    map.assign(start, end, v);
    array.assign(start, end, v);

    for (size_t i = START; i < END; ++i) {
        auto m = map[i];
        auto a = array[i];
        assert(m == a);
    }
}

int rand(int start, int end) {
    return start + (rand() % (int)(end - start));
}

void IntervalMapTest() {
    for (int i = 0; i < 1000000; ++i) {
        auto start = rand(START, END);
        auto end = rand(start+1, END+1);
        test(start, end, i);
    }
}


int main(int argc, char* argv[]) {
    IntervalMapTest();
    return 0;
}
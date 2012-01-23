#include "Driver.h"

int main(int argc, char** argv) {
    int count = 10;

    if(argc > 1) {
        count = atoi(argv[1]);
    }

    testLibraries(count);

    return 0;
}


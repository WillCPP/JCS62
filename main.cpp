#include "JCS62.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Error: Incorrect number of command line arguments." << endl;
        return 1;
    }

    string filename = argv[1];
    ifstream program(filename);
    if (program.fail()) {
        cout << "Error: Failed to open file." << endl;
        return 2;
    }

    JCS62 cpu;
    cpu.Load(program);
    program.close();
    cpu.Run();

    return 0;
}
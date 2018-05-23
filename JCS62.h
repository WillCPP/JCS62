#ifndef JCS62_JCS62_H
#define JCS62_JCS62_H

#include "Utilities.h"

#include <array>
#include <fstream>
using namespace std;


class JCS62 {
public:
    JCS62();
    ~JCS62();

    // Flags
    bool Halt_Flag = false;

    // Registers
    Register_8 PC;
    Register_8 MAR;
    Register_12 MDR;
    Register_12 ACC;
    Register_12 B;
    Register_12 IR;

    // Memory
    array<bitset<12>, 256> RAM;

    // Decoder
    void DecodeInstruction();

    // Instructions
    void LoadA(bitset<8> operand);
    void StoreA(bitset<8> operand);
    void AddBtoA();
    void SubBfromA();
    void MoveAtoB();
    void JumpToAddress(bitset<8> operand);
    void JumpIfNegative(bitset<8> operand);
    void Halt();

    // Signals
    void LoadIR();
    void IncrementPC();

    // CPU Load
    void Load(ifstream &program);

    // CPU Loop
    void Run();

};

#endif //JCS62_JCS62_H

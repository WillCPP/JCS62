#include "JCS62.h"
#include "Utilities.h"

#include <iostream>
#include <climits>
#include <string>
using namespace std;

JCS62::JCS62() = default;

JCS62::~JCS62() = default;

void JCS62::DecodeInstruction() {
    bitset<4> opcode = ((IR.word & OPCODE_BITMASK) >> 8).to_ulong();
    bitset<8> operand = (IR.word & OPERAND_BITMASK).to_ulong();

    if (opcode == IS::NONE) {
        //do nothing
        cout << "Nothing" << endl;
    }
    else if (opcode == IS::LDA) {
        //LDA
        cout << "LDA" << " " << operand.to_ulong() << endl;
        LoadA(operand);
    }
    else if (opcode == IS::STA) {
        //STA
        cout << "STA" << " " << operand.to_ulong() << endl;
        StoreA(operand);
    }
    else if (opcode == IS::ADD) {
        //ADD
        cout << "ADD" << endl;
        AddBtoA();
    }
    else if (opcode == IS::SUB) {
        //SUB
        cout << "SUB" << endl;
        SubBfromA();
    }
    else if (opcode == IS::MBA) {
        //MBA
        cout << "MBA" << endl;
        MoveAtoB();
    }
    else if (opcode == IS::JMP) {
        //JMP
        cout << "JMP" << " " << operand.to_ulong() << endl;
        JumpToAddress(operand);
    }
    else if (opcode == IS::JN) {
        //JN
        cout << "JN" << " " << operand.to_ulong() << endl;
        JumpIfNegative(operand);
    }
    else if (opcode == IS::HLT){
        //HLT
        cout << "HLT" << endl;
        Halt();
    }

    return;
}

// Instructions
void JCS62::LoadA(bitset<8> operand) {
    MAR.byte = operand;
    MDR.word = RAM[MAR.byte.to_ulong()];
    ACC.word = MDR.word;
}
void JCS62::StoreA(bitset<8> operand) {
    MAR.byte = operand;
    MDR.word = ACC.word;
    RAM[MAR.byte.to_ulong()] = MDR.word;
}
void JCS62::AddBtoA() {
    auto a = ACC.word.to_ulong();
    auto b = B.word.to_ulong();
    ACC.word = (a + b < 4096 ? a + b : (a + b) - 4096);
}
void JCS62::SubBfromA() {
    auto a = ACC.word.to_ulong();
    auto b = B.word.to_ulong();
    ACC.word = (a - b < 4096 ? a - b : ULONG_MAX - (a - b));
}
void JCS62::MoveAtoB() {
    B.word = ACC.word;
}
void JCS62::JumpToAddress(bitset<8> operand) {
    PC.byte = operand;
}
void JCS62::JumpIfNegative(bitset<8> operand) {
    auto a = ACC.word;
    if ((a & MSB_BITMASK) >> 11 == LSB_BITMASK) {
        PC.byte = operand;
    }
}
void JCS62::Halt() {
    //do something
    Halt_Flag = true;
}

// Signals
void JCS62::LoadIR() {
    MAR.byte = PC.byte;
    MDR.word = RAM[MAR.byte.to_ulong()];
    IR.word = MDR.word;
}
void JCS62::IncrementPC() {
    auto pc = PC.byte.to_ulong();
    PC.byte = (pc + 1 < 256 ? pc + 1 : (pc + 1) - 256);
}

// Load program
void JCS62::Load(ifstream &program) {
    int i = 0;
    string buffer = "";
    while (!program.eof()) {
        program >> buffer;
        RAM[i] = bitset<12>(buffer);
        i++;
    }
}

// CPU loop
void JCS62::Run() {
    while(!Halt_Flag) {
        LoadIR();
        IncrementPC();
        DecodeInstruction();
    }
}
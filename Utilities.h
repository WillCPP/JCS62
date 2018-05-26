#ifndef JCS62_UTILITIES_H
#define JCS62_UTILITIES_H

#include <bitset>
using namespace std;

bitset<12> const OPCODE_BITMASK(0b111100000000);
bitset<12> const OPERAND_BITMASK(0b000011111111);
bitset<12> const MSB_BITMASK(0b100000000000);
bitset<12> const LSB_BITMASK(0b000000000001);

struct Word {
    bitset<12> bits = 0b000000000000;
};
struct Byte {
    bitset<8> bits = 0b00000000;
};
struct Nibble {
    bitset<4> bits = 0b0000;
};

struct Register_12 {
    bitset<12> word;
};
struct Register_8 {
    bitset<8> byte;
};

namespace IS {
    bitset<4> const NONE(0b0000);
    bitset<4> const LDA(0b0001);
    bitset<4>const STA(0b0010);
    bitset<4>const ADD(0b0011);
    bitset<4>const SUB(0b0100);
    bitset<4>const MBA(0b0101);
    bitset<4>const JMP(0b0110);
    bitset<4>const JN(0b0111);
    bitset<4>const HLT(0b1000);
    bitset<4>const LAI(0b1001);
}

#endif //JCS62_UTILITIES_H

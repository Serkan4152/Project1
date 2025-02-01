#pragma once
#include "Memory.h"
#include "Opcodes.h"

class CPU
{
public:
	static CPU* Initialize(Memory* memory);

	void Reset();

	word SPToAddress() const;
	void PushWordToStack(word Value);

	void PushPCMinusOneToStack();
	void PushPCPlusOneToStack();
	void PushPCToStack();

	void PushByteOntoStack(byte Value);
	byte PopByteFromStack();
	word PopWordFromStack();

	byte ReadByte(word addr);
	word ReadWord(word addr);

	void WriteByte(word addr, byte in);
	void WriteWord(word addr, word in);

	byte FetchByte();
	word FetchWord();

	word AddressImplied();
	word AddressImmediate();

	word AddressAbsoluteIndirect();

	word AddressAbsolute();
	word AddressAbsoluteX();
	word AddressAbsoluteY();

	word AddressZeroPage();
	word AddressZeroPageX();
	word AddressZeroPageY();

	word AddressIndirectX();
	word AddressIndirectY();

	void Execute();

	byte INS_ILLEGAL(word addr);
	byte INS_LDA(word addr);
	byte INS_LDX(word addr);
	byte INS_LDY(word addr);
	byte INS_STA(word addr);
	byte INS_STX(word addr);
	byte INS_STY(word addr);
	byte INS_TSX(word addr);
	byte INS_TXS(word addr);
	byte INS_PHA(word addr);
	byte INS_PLA(word addr);
	byte INS_PHP(word addr);
	byte INS_PLP(word addr);
	byte INS_JMP(word addr);

	enum class StatusFlag : byte {
		CARRY = (1 << 0),		// Carry Bit
		ZERO = (1 << 1),		// Zero Flag
		INTERRUPT = (1 << 2),   // Interrupt Disable
		DECIMAL = (1 << 3),		// Decimal Mode
		BREAK = (1 << 4),	    // Break
		UNUSED = (1 << 5),		// Ignored (un-used)
		INT_OVERFLOW = (1 << 6),// Overflow Flag
		NEGATIVE = (1 << 7),	// Negative Flag
	};

	const byte GetStatusFlag(const StatusFlag f) const;
	void SetStatusFlag(const StatusFlag f, const bool v);

	Memory* GetMemory();
private:
	word PC;      //program counter
	word SP;	  //stack pointer	

	byte A, X, Y; //registers

	struct StatusFlags
	{
		byte C : 1;	//0: Carry Flag	
		byte Z : 1;	//1: Zero Flag
		byte I : 1; //2: Interrupt disable
		byte D : 1; //3: Decimal mode
		byte B : 1; //4: Break
		byte Unused : 1; //5: Unused
		byte V : 1; //6: Overflow
		byte N : 1; //7: Negative
	} statusFlags;

	typedef word(CPU::* AddrExec)();
	typedef byte(CPU::* CodeExec)(word addr);

	struct Instruction
	{
		AddrExec addr;
		CodeExec code;
		uint8_t  cycles;
	};

	Instruction instructionTable[256];


	Memory* memory;
};
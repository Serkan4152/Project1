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
	word AddressRelative();

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
	byte INS_JSR(word addr);
	byte INS_RTS(word addr);

	byte INS_AND(word addr);
	byte INS_ORA(word addr);
	byte INS_EOR(word addr);

	byte INS_BIT(word addr);

	byte INS_TAX(word addr);
	byte INS_TAY(word addr);
	byte INS_TXA(word addr);
	byte INS_TYA(word addr);

	byte INS_INX(word addr);
	byte INS_INY(word addr);
	byte INS_INC(word addr);
	byte INS_DEX(word addr);
	byte INS_DEY(word addr);
	byte INS_DEC(word addr);

	byte INS_BEQ(word addr);
	byte INS_BNE(word addr);
	byte INS_BCS(word addr);
	byte INS_BCC(word addr);
	byte INS_BMI(word addr);
	byte INS_BPL(word addr);
	byte INS_BVC(word addr);
	byte INS_BVS(word addr);

	byte INS_CLC(word addr);
	byte INS_SEC(word addr);
	byte INS_CLD(word addr);
	byte INS_SED(word addr);
	byte INS_CLI(word addr);
	byte INS_SEI(word addr);
	byte INS_CLV(word addr);

	byte INS_ADC(word addr);
	byte INS_SBC(word addr);

	byte INS_CMP(word addr);
	byte INS_CPX(word addr);
	byte INS_CPY(word addr);

	byte INS_ASL(word addr);
	byte INS_ASL_ACC(word addr);

	byte INS_LSR(word addr);
	byte INS_LSR_ACC(word addr);

	byte INS_ROL(word addr);
	byte INS_ROL_ACC(word addr);

	byte INS_ROR(word addr);
	byte INS_ROR_ACC(word addr);

	byte INS_NOP(word addr);
	byte INS_BRK(word addr);
	byte INS_RTI(word addr);

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
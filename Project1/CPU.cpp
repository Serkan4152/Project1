#include "CPU.h"
#include <iostream>

CPU* CPU::Initialize(Memory* memory)
{
	CPU* out = (CPU*)malloc(sizeof(CPU));
	out->memory = memory;

	out->Reset();

	for (int i = 0; i < 256; i++)
	{
		out->instructionTable[i] = { &CPU::AddressImplied, &CPU::INS_ILLEGAL, 0 };
	}

	out->instructionTable[INS_LDA_IM]   = { &CPU::AddressImmediate, &CPU::INS_LDA, 2 };
	out->instructionTable[INS_LDA_ZP]   = { &CPU::AddressZeroPage,  &CPU::INS_LDA, 3 };
	out->instructionTable[INS_LDA_ZPX]  = { &CPU::AddressZeroPageX, &CPU::INS_LDA, 4 };
	out->instructionTable[INS_LDA_ABS]  = { &CPU::AddressAbsolute,  &CPU::INS_LDA, 4 };
	out->instructionTable[INS_LDA_ABSX] = { &CPU::AddressAbsoluteX, &CPU::INS_LDA, 4 };
	out->instructionTable[INS_LDA_ABSY] = { &CPU::AddressAbsoluteY, &CPU::INS_LDA, 4 };
	out->instructionTable[INS_LDA_INDX] = { &CPU::AddressIndirectX, &CPU::INS_LDA, 6 };
	out->instructionTable[INS_LDA_INDY] = { &CPU::AddressIndirectY, &CPU::INS_LDA, 5 };

	out->instructionTable[INS_LDX_IM]   = { &CPU::AddressImmediate, &CPU::INS_LDX, 2 };
	out->instructionTable[INS_LDX_ZP]   = { &CPU::AddressZeroPage,  &CPU::INS_LDX, 3 };
	out->instructionTable[INS_LDX_ZPY]  = { &CPU::AddressZeroPageY, &CPU::INS_LDX, 4 };
	out->instructionTable[INS_LDX_ABS]  = { &CPU::AddressAbsolute,  &CPU::INS_LDX, 4 };
	out->instructionTable[INS_LDX_ABSY] = { &CPU::AddressAbsoluteY, &CPU::INS_LDX, 4 };

	out->instructionTable[INS_LDY_IM]   = { &CPU::AddressImmediate, &CPU::INS_LDY, 2 };
	out->instructionTable[INS_LDY_ZP]   = { &CPU::AddressZeroPage,  &CPU::INS_LDY, 3 };
	out->instructionTable[INS_LDY_ZPX]  = { &CPU::AddressZeroPageX, &CPU::INS_LDY, 4 };
	out->instructionTable[INS_LDY_ABS]  = { &CPU::AddressAbsolute,  &CPU::INS_LDY, 4 };
	out->instructionTable[INS_LDY_ABSX] = { &CPU::AddressAbsoluteX, &CPU::INS_LDY, 4 };

	out->instructionTable[INS_STA_ZP]   = { &CPU::AddressZeroPage,  &CPU::INS_STA, 3 };
	out->instructionTable[INS_STA_ZPX]  = { &CPU::AddressZeroPageX, &CPU::INS_STA, 4 };
	out->instructionTable[INS_STA_ABS]  = { &CPU::AddressAbsolute,  &CPU::INS_STA, 4 };
	out->instructionTable[INS_STA_ABSX] = { &CPU::AddressAbsoluteX, &CPU::INS_STA, 5 };
	out->instructionTable[INS_STA_ABSY] = { &CPU::AddressAbsoluteY, &CPU::INS_STA, 5 };
	out->instructionTable[INS_STA_INDX] = { &CPU::AddressIndirectX, &CPU::INS_STA, 6 };
	out->instructionTable[INS_STA_INDY] = { &CPU::AddressIndirectY, &CPU::INS_STA, 6 };

	out->instructionTable[INS_STX_ABS]  = { &CPU::AddressAbsolute,  &CPU::INS_STX, 4 };
	out->instructionTable[INS_STX_ZP]   = { &CPU::AddressZeroPage,  &CPU::INS_STX, 3 };
	out->instructionTable[INS_STX_ZPY]  = { &CPU::AddressZeroPageY, &CPU::INS_STX, 4 };

	out->instructionTable[INS_STY_ABS]  = { &CPU::AddressAbsolute,  &CPU::INS_STY, 4 };
	out->instructionTable[INS_STY_ZP]   = { &CPU::AddressZeroPage,  &CPU::INS_STY, 3 };
	out->instructionTable[INS_STY_ZPX]  = { &CPU::AddressZeroPageX, &CPU::INS_STY, 4 };

	out->instructionTable[INS_JMP_ABS] = { &CPU::AddressAbsolute,		  &CPU::INS_JMP, 3 };
	out->instructionTable[INS_JMP_IND] = { &CPU::AddressAbsoluteIndirect, &CPU::INS_JMP, 5 };

	return out;
}

void CPU::Reset()
{
	PC = 0x0000;
	SP = 0x0100;
	statusFlags.C = statusFlags.Z = statusFlags.I = statusFlags.D = statusFlags.B = statusFlags.V = statusFlags.N = 0;
	A = X = Y = 0;
}

word CPU::SPToAddress() const
{
	return 0x100 | SP;
}

void CPU::PushWordToStack(word Value)
{
	WriteByte(SPToAddress(), Value >> 8);
	SP--;
	WriteByte(SPToAddress(), Value & 0xFF);
	SP--;
}

void CPU::PushPCMinusOneToStack()
{
	PushWordToStack(PC - 1);
}

void CPU::PushPCPlusOneToStack()
{
	PushWordToStack(PC + 1);
}

void CPU::PushPCToStack()
{
	PushWordToStack(PC);
}

void CPU::PushByteOntoStack(byte Value)
{
	const word SPWord = SPToAddress();
	memory->WriteWord(SPWord, Value);
	//cycles++;
	SP--;
	//cycles++;
}

byte CPU::PopByteFromStack()
{
	SP++;
	//cycles++;
	const word SPWord = SPToAddress();
	byte Value = memory->ReadByte(SPWord);
	//cycles++;
	return Value;
}

word CPU::PopWordFromStack()
{
	word ValueFromStack = ReadWord(SPToAddress() + 1);
	SP += 2;
	//cycles++;
	return ValueFromStack;
}

byte CPU::ReadByte(word addr)
{
	byte data = memory->ReadByte(addr);
	//cycles++;
	return data;
}

word CPU::ReadWord(word addr)
{
	word data = memory->ReadWord(addr);
	//cycles+=2;

	return data;
}

void CPU::WriteByte(word addr, byte in)
{
	memory->WriteByte(addr, in);
	//cycles++;
}

void CPU::WriteWord(word addr, word in)
{
	memory->WriteWord(addr, in);
	//cycles+=2;
}

byte CPU::FetchByte()
{
	byte data = memory->ReadByte(PC);
	PC++;
	//cycles++;
	return data;
}

word CPU::FetchWord()
{
	byte low = FetchByte();
	byte high = 0x00;

	if (PC < 0xFFFF) high = FetchByte();

	return MAKE_WORD(low, high);
}

word CPU::AddressImplied()
{
	return 0x00;
}

word CPU::AddressImmediate()
{
	return PC++;
}

word CPU::AddressAbsoluteIndirect()
{
	word effL;
	word effH;

	word AbsAddress = FetchWord();

	word Address = memory->ReadWord(AbsAddress);

	return Address;
}

word CPU::AddressAbsolute()
{
	word AbsAddress = FetchWord();
	return AbsAddress;
}

word CPU::AddressAbsoluteX()
{
	word AbsAddress = FetchWord();
	word AbsAddressX = AbsAddress + X;

	const bool CrossedPageBoundary = (AbsAddress ^ AbsAddressX) >> 8;
	if (CrossedPageBoundary)
	{
		//cycles++;
	}

	return AbsAddressX;
}

word CPU::AddressAbsoluteY()
{
	word AbsAddress = FetchWord();
	word AbsAddressY = AbsAddress + Y;

	const bool CrossedPageBoundary = (AbsAddress ^ AbsAddressY) >> 8;
	if (CrossedPageBoundary)
	{
		//cycles++;
	}

	return AbsAddress;
}

word CPU::AddressZeroPage()
{
	byte ZeroPageAddress = FetchByte();
	return ZeroPageAddress;
}

word CPU::AddressZeroPageX()
{
	byte ZeroPageAddress = FetchByte();
	ZeroPageAddress += X;
	//cycles++;
	return ZeroPageAddress;
}

word CPU::AddressZeroPageY()
{
	byte ZeroPageAddress = FetchByte();
	ZeroPageAddress += Y;
	//cycles++;
	return ZeroPageAddress;
}

word CPU::AddressIndirectX()
{
	byte ZPAddress = FetchByte();
	ZPAddress += X;
	//cycles++;
	word EffectiveAddr = ReadWord(ZPAddress);
	return EffectiveAddr;
}

word CPU::AddressIndirectY()
{
	byte ZPAddress = FetchByte();
	word EffectiveAddr = ReadWord(ZPAddress);
	word EffectiveAddrY = EffectiveAddr + Y;
	const bool CrossedPageBoundary = (EffectiveAddr ^ EffectiveAddrY) >> 8;
	if (CrossedPageBoundary)
	{
		//cycles++;
	}
	return EffectiveAddrY;
}

void CPU::Execute()
{
	while (1)
	{
		byte ins = FetchByte();

		word addr = (this->*instructionTable[ins].addr)();

		byte stat = (this->*instructionTable[ins].code)(addr);

		if (!stat)
		{
			printf("Exiting loop because of instruction 0x%x\n", ins);
			return;
		}
	}
}

byte CPU::INS_ILLEGAL(word addr)
{
	return 0;
}

byte CPU::INS_LDA(word addr)
{
	A = ReadByte(addr);

	SetStatusFlag(StatusFlag::ZERO,     (A == 0));
	SetStatusFlag(StatusFlag::NEGATIVE, IS_NEGATIVE(A));

	return 1;
}

byte CPU::INS_LDX(word addr)
{
	byte v = ReadByte(addr);

	X = v;

	SetStatusFlag(StatusFlag::ZERO, (v == 0));
	SetStatusFlag(StatusFlag::NEGATIVE, IS_NEGATIVE(v));

	return 1;
}

byte CPU::INS_LDY(word addr)
{
	byte v = ReadByte(addr);

	Y = v;

	SetStatusFlag(StatusFlag::ZERO, (v == 0));
	SetStatusFlag(StatusFlag::NEGATIVE, IS_NEGATIVE(v));

	return 1;
}

byte CPU::INS_STA(word addr)
{
	WriteByte(addr, A);

	return 1;
}

byte CPU::INS_STX(word addr)
{
	WriteByte(addr, X);

	return 1;
}

byte CPU::INS_STY(word addr)
{
	WriteByte(addr, Y);

	return 1;
}

byte CPU::INS_TSX(word addr)
{
	byte v = SP;

	X = v;

	SetStatusFlag(StatusFlag::ZERO, (v == 0));
	SetStatusFlag(StatusFlag::NEGATIVE, IS_NEGATIVE(v));

	return 1;
}

byte CPU::INS_TXS(word addr)
{
	SP = X;

	return 1;
}

byte CPU::INS_PHA(word addr)
{
	PushByteOntoStack(A);

	return 1;
}

byte CPU::INS_PLA(word addr)
{
	A = PopByteFromStack();

	SetStatusFlag(StatusFlag::ZERO, (A == 0));
	SetStatusFlag(StatusFlag::NEGATIVE, IS_NEGATIVE(A));

	return 1;
}

byte CPU::INS_PHP(word addr)
{
	printf("INS_PHP not implemented\n");
	//ps??
	return 0;
}

byte CPU::INS_PLP(word addr)
{
	printf("INS_PLP not implemented\n");
	//ps??
	return 0;
}

byte CPU::INS_JMP(word addr)
{
	PC = addr;

	return 1;
}

const byte CPU::GetStatusFlag(const StatusFlag f) const
{
	switch (f) {
	case StatusFlag::CARRY: return statusFlags.C;
	case StatusFlag::ZERO: return statusFlags.Z;
	case StatusFlag::INTERRUPT: return statusFlags.I;
	case StatusFlag::DECIMAL: return statusFlags.D;
	case StatusFlag::BREAK: return statusFlags.B;
	case StatusFlag::UNUSED: return statusFlags.Unused;
	case StatusFlag::INT_OVERFLOW: return statusFlags.V;
	case StatusFlag::NEGATIVE: return statusFlags.N;
	default: return 0x00; // throw an exception for invalid flag
	}
	return 0x00;
}

void CPU::SetStatusFlag(const StatusFlag f, const bool v)
{
	switch (f) {
	case StatusFlag::CARRY: statusFlags.C = v; break;
	case StatusFlag::ZERO: statusFlags.Z = v; break;
	case StatusFlag::INTERRUPT: statusFlags.I = v; break;
	case StatusFlag::DECIMAL: statusFlags.D = v; break;
	case StatusFlag::BREAK: statusFlags.B = v; break;
	case StatusFlag::UNUSED: statusFlags.Unused = v; break;
	case StatusFlag::INT_OVERFLOW: statusFlags.V = v; break;
	case StatusFlag::NEGATIVE: statusFlags.N = v; break;
	default: /* Handle invalid flag - throw exception */ break;
	}
}

Memory* CPU::GetMemory()
{
	return memory;
}
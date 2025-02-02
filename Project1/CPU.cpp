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


	out->instructionTable[INS_TSX_IM]  = { &CPU::AddressImplied, &CPU::INS_TSX, 2 };
	out->instructionTable[INS_TXS_IM]  = { &CPU::AddressImplied, &CPU::INS_TXS, 2 };
	out->instructionTable[INS_PHA_IM]  = { &CPU::AddressImplied, &CPU::INS_PHA, 3 };
	out->instructionTable[INS_PLA_IM]  = { &CPU::AddressImplied, &CPU::INS_PLA, 4 };
	out->instructionTable[INS_PHP_IM]  = { &CPU::AddressImplied, &CPU::INS_PHP, 3 };
	out->instructionTable[INS_PLP_IM]  = { &CPU::AddressImplied, &CPU::INS_PLP, 4 };

	out->instructionTable[INS_JMP_ABS]  = { &CPU::AddressAbsolute,		   &CPU::INS_JMP, 3 };
	out->instructionTable[INS_JMP_IND]  = { &CPU::AddressAbsoluteIndirect, &CPU::INS_JMP, 5 };

	out->instructionTable[INS_JSR_ABS]  = { &CPU::AddressAbsolute, &CPU::INS_JSR, 6 };
	out->instructionTable[INS_RTS_IM]   = { &CPU::AddressImplied,  &CPU::INS_RTS, 6 };

	out->instructionTable[INS_AND_IM]   = { &CPU::AddressImmediate, &CPU::INS_AND, 3 };
	out->instructionTable[INS_AND_ZP]   = { &CPU::AddressZeroPage,  &CPU::INS_AND, 3 };
	out->instructionTable[INS_AND_ZPX]  = { &CPU::AddressZeroPageX, &CPU::INS_AND, 4 };
	out->instructionTable[INS_AND_ABS]  = { &CPU::AddressAbsolute,  &CPU::INS_AND, 4 };
	out->instructionTable[INS_AND_ABSX] = { &CPU::AddressAbsoluteX, &CPU::INS_AND, 4 };
	out->instructionTable[INS_AND_ABSY] = { &CPU::AddressAbsoluteY, &CPU::INS_AND, 4 };
	out->instructionTable[INS_AND_INDX] = { &CPU::AddressIndirectX, &CPU::INS_AND, 6 };
	out->instructionTable[INS_AND_INDY] = { &CPU::AddressIndirectY, &CPU::INS_AND, 5 };

	out->instructionTable[INS_ORA_IM]   = { &CPU::AddressImmediate, &CPU::INS_ORA, 2 };
	out->instructionTable[INS_ORA_ZP]   = { &CPU::AddressZeroPage,  &CPU::INS_ORA, 3 };
	out->instructionTable[INS_ORA_ZPX]  = { &CPU::AddressZeroPageX, &CPU::INS_ORA, 4 };
	out->instructionTable[INS_ORA_ABS]  = { &CPU::AddressAbsolute,  &CPU::INS_ORA, 4 };
	out->instructionTable[INS_ORA_ABSX] = { &CPU::AddressAbsoluteX, &CPU::INS_ORA, 4 };
	out->instructionTable[INS_ORA_ABSY] = { &CPU::AddressAbsoluteY, &CPU::INS_ORA, 4 };
	out->instructionTable[INS_ORA_INDX] = { &CPU::AddressIndirectX, &CPU::INS_ORA, 6 };
	out->instructionTable[INS_ORA_INDY] = { &CPU::AddressIndirectY, &CPU::INS_ORA, 5 };

	out->instructionTable[INS_EOR_IM]   = { &CPU::AddressImmediate, &CPU::INS_EOR, 2 };
	out->instructionTable[INS_EOR_ZP]   = { &CPU::AddressZeroPage,  &CPU::INS_EOR, 3 };
	out->instructionTable[INS_EOR_ZPX]  = { &CPU::AddressZeroPageX, &CPU::INS_EOR, 4 };
	out->instructionTable[INS_EOR_ABS]  = { &CPU::AddressAbsolute,  &CPU::INS_EOR, 4 };
	out->instructionTable[INS_EOR_ABSX] = { &CPU::AddressAbsoluteX, &CPU::INS_EOR, 4 };
	out->instructionTable[INS_EOR_ABSY] = { &CPU::AddressAbsoluteY, &CPU::INS_EOR, 4 };
	out->instructionTable[INS_EOR_INDX] = { &CPU::AddressIndirectX, &CPU::INS_EOR, 6 };
	out->instructionTable[INS_EOR_INDY] = { &CPU::AddressIndirectY, &CPU::INS_EOR, 5 };

	out->instructionTable[INS_BNE_REL]  = { &CPU::AddressRelative, &CPU::INS_BNE, 2 };

	out->instructionTable[INS_CLC_IM] = { &CPU::AddressImplied, &CPU::INS_CLC, 2 };
	out->instructionTable[INS_SEC_IM] = { &CPU::AddressImplied, &CPU::INS_SEC, 2 };
	out->instructionTable[INS_CLD_IM] = { &CPU::AddressImplied, &CPU::INS_CLD, 2 };
	out->instructionTable[INS_SED_IM] = { &CPU::AddressImplied, &CPU::INS_SED, 2 };
	out->instructionTable[INS_CLI_IM] = { &CPU::AddressImplied, &CPU::INS_CLI, 2 };
	out->instructionTable[INS_SEI_IM] = { &CPU::AddressImplied, &CPU::INS_SEI, 2 };
	out->instructionTable[INS_CLV_IM] = { &CPU::AddressImplied, &CPU::INS_CLV, 2 };

	out->instructionTable[INS_ADC_IM]   = { &CPU::AddressImmediate, &CPU::INS_ADC, 2 };
	out->instructionTable[INS_ADC_ZP]   = { &CPU::AddressZeroPage,  &CPU::INS_ADC, 3 };
	out->instructionTable[INS_ADC_ZPX]  = { &CPU::AddressZeroPageX, &CPU::INS_ADC, 4 };
	out->instructionTable[INS_ADC_ABS]  = { &CPU::AddressAbsolute,  &CPU::INS_ADC, 4 };
	out->instructionTable[INS_ADC_ABSX] = { &CPU::AddressAbsoluteX, &CPU::INS_ADC, 4 };
	out->instructionTable[INS_ADC_ABSY] = { &CPU::AddressAbsoluteY, &CPU::INS_ADC, 4 };
	out->instructionTable[INS_ADC_INDX] = { &CPU::AddressIndirectX, &CPU::INS_ADC, 6 };
	out->instructionTable[INS_ADC_INDY] = { &CPU::AddressIndirectY, &CPU::INS_ADC, 5 };

	out->instructionTable[INS_CMP_IM]   = { &CPU::AddressImmediate, &CPU::INS_CMP, 2 };
	out->instructionTable[INS_CMP_ZP]   = { &CPU::AddressZeroPage,  &CPU::INS_CMP, 3 };
	out->instructionTable[INS_CMP_ZPX]  = { &CPU::AddressZeroPageX, &CPU::INS_CMP, 4 };
	out->instructionTable[INS_CMP_ABS]  = { &CPU::AddressAbsolute,  &CPU::INS_CMP, 4 };
	out->instructionTable[INS_CMP_ABSX] = { &CPU::AddressAbsoluteX, &CPU::INS_CMP, 4 };
	out->instructionTable[INS_CMP_ABSY] = { &CPU::AddressAbsoluteY, &CPU::INS_CMP, 4 };
	out->instructionTable[INS_CMP_INDX] = { &CPU::AddressIndirectX, &CPU::INS_CMP, 6 };
	out->instructionTable[INS_CMP_INDY] = { &CPU::AddressIndirectY, &CPU::INS_CMP, 5 };

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

word CPU::AddressRelative()
{
	uint16_t offset;
	uint16_t addr;

	offset = ReadByte(PC++);
	if (offset & 0x80) offset |= 0xFF00;
	addr = PC + (int16_t)offset;
	return addr;

	return word();
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
			printf("Exiting loop because of instruction 0x%x, PC 0x%x\n", ins, PC);
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

byte CPU::INS_JSR(word addr)
{
	PushPCMinusOneToStack();
	PC = addr;
	return 1;
}

byte CPU::INS_RTS(word addr)
{
	word ReturnAddress = PopWordFromStack();
	PC = ReturnAddress + 1;
	return 1;
}

byte CPU::INS_AND(word addr)
{
	byte v = ReadByte(addr);
	A = v & A;

	SetStatusFlag(StatusFlag::ZERO, (A == 0));
	SetStatusFlag(StatusFlag::NEGATIVE, IS_NEGATIVE(A));

	return 1;
}

byte CPU::INS_ORA(word addr)
{
	byte v = ReadByte(addr);
	A = v | A;

	SetStatusFlag(StatusFlag::ZERO, (A == 0));
	SetStatusFlag(StatusFlag::NEGATIVE, IS_NEGATIVE(A));
	
	return 1;
}

byte CPU::INS_EOR(word addr)
{
	byte v = ReadByte(addr);
	A = v ^ A;

	SetStatusFlag(StatusFlag::ZERO, (A == 0));
	SetStatusFlag(StatusFlag::NEGATIVE, IS_NEGATIVE(A));

	return 1;
}

byte CPU::INS_CMP(word addr)
{
	byte v = ReadByte(addr);
	word tmp = A - v;

	SetStatusFlag(StatusFlag::CARRY, !(A < v));
	SetStatusFlag(StatusFlag::ZERO, (tmp == 0));
	SetStatusFlag(StatusFlag::NEGATIVE, IS_NEGATIVE(tmp));

	return 1;
}

byte CPU::INS_BNE(word addr)
{
	if (GetStatusFlag(StatusFlag::ZERO))
	{
		PC = addr;
	}
	
	return 1;
}

byte CPU::INS_CLC(word addr)
{
	SetStatusFlag(StatusFlag::CARRY, 0);

	return 1;
}

byte CPU::INS_SEC(word addr)
{
	SetStatusFlag(StatusFlag::CARRY, 1);

	return 1;
}

byte CPU::INS_CLD(word addr)
{
	SetStatusFlag(StatusFlag::DECIMAL, 0);

	return 1;
}

byte CPU::INS_SED(word addr)
{
	SetStatusFlag(StatusFlag::DECIMAL, 1);

	return 1;
}

byte CPU::INS_CLI(word addr)
{
	SetStatusFlag(StatusFlag::INTERRUPT, 0);

	return 1;
}

byte CPU::INS_SEI(word addr)
{
	SetStatusFlag(StatusFlag::INTERRUPT, 1);

	return 1;
}

byte CPU::INS_CLV(word addr)
{
	SetStatusFlag(StatusFlag::INT_OVERFLOW, 0);

	return 1;
}

byte CPU::INS_ADC(word addr)
{
	byte v = ReadByte(addr);
	word tmp = A + v + GetStatusFlag(StatusFlag::CARRY);

	if (GetStatusFlag(StatusFlag::DECIMAL))
	{
		if (((A & 0xF) + (v & 0xF) + GetStatusFlag(StatusFlag::CARRY)) > 9) tmp += 6;
		SetStatusFlag(StatusFlag::NEGATIVE, tmp & 0x80);
		SetStatusFlag(StatusFlag::INT_OVERFLOW, !((A ^ v) & 0x80) && ((A ^ tmp) & 0x80));
		if (tmp > 0x99)
		{
			tmp += 96;
		}
		SetStatusFlag(StatusFlag::CARRY, tmp > 0x99);
	}
	else
	{
		SetStatusFlag(StatusFlag::NEGATIVE, tmp & 0x80);
		SetStatusFlag(StatusFlag::INT_OVERFLOW, !((A ^ v) & 0x80) && ((A ^ tmp) & 0x80));
		SetStatusFlag(StatusFlag::CARRY, tmp > 0xFF);
	}

	A = tmp & 0xFF;

	SetStatusFlag(StatusFlag::ZERO, (A == 0));

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
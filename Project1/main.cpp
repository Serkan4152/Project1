#include <stdio.h>
#include <cstdint>

#include "Memory.h"
#include "CPU.h"

Memory* memory;
CPU* cpu;

int main()
{
	memory = Memory::Initialize();
	cpu = CPU::Initialize(memory);

	/*memory->WriteByte(0x8000, INS_LDA_IM);
	memory->WriteByte(0x8001, 0x45);

	memory->WriteByte(0x8002, INS_LDA_INDY); //LDA
	memory->WriteByte(0x8003, 0x45);

	memory->WriteByte(0x0045, 0x45);
	memory->WriteByte(0x0046, 0x35);

	memory->WriteByte(0x3545, 0x50);*/

	memory->WriteByte(0x8000, INS_LDA_IM);
	memory->WriteByte(0x8001, 0x45);

	memory->WriteByte(0x8002, INS_STA_ZP);
	memory->WriteByte(0x8003, 0x05);

	cpu->Execute(100);

	return 0;
}
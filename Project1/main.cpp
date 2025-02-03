#include <stdio.h>
#include <cstdint>

#include "Memory.h"
#include "CPU.h"
#include <fstream>
#include <vector>

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

	/*memory->WriteByte(0x0000, INS_LDX_IM);
	memory->WriteByte(0x0001, 0x00);

	memory->WriteByte(0x0002, INS_LDA_IM);
	memory->WriteByte(0x0003, 0xFF);

	memory->WriteByte(0x0004, INS_STA_ABS);
	memory->WriteByte(0x0005, 0x1E);
	memory->WriteByte(0x0006, 0x00);

	memory->WriteByte(0x0007, INS_JMP_ABS);
	memory->WriteByte(0x0008, 0x18);
	memory->WriteByte(0x0009, 0x00);

	memory->WriteByte(0x000A, INS_LDX_IM);
	memory->WriteByte(0x000B, 0x00);

	memory->WriteByte(0x000C, INS_LDA_IM);
	memory->WriteByte(0x000D, 0xAA);

	memory->WriteByte(0x000E, INS_STA_ABS);
	memory->WriteByte(0x000F, 0x1F);
	memory->WriteByte(0x0010, 0x00);

	memory->WriteByte(0x0011, INS_LDX_IM);
	memory->WriteByte(0x0012, 0x00);

	memory->WriteByte(0x0013, INS_LDA_IM);
	memory->WriteByte(0x0014, 0x55);

	memory->WriteByte(0x0015, INS_STA_ABS);
	memory->WriteByte(0x0016, 0x20);
	memory->WriteByte(0x0017, 0x00);

	memory->WriteByte(0x0018, INS_JMP_ABS);
	memory->WriteByte(0x0019, 0x0A);
	memory->WriteByte(0x001A, 0x00);*/

	/*memory->WriteByte(0x0000, INS_JMP_IND);
	memory->WriteByte(0x0001, 0x05);
	memory->WriteByte(0x0002, 0x01);

	memory->WriteByte(0x0105, 0xA9);
	memory->WriteByte(0x0106, 0x05);

	memory->WriteByte(0x05A9, INS_LDA_IM);
	memory->WriteByte(0x05AA, 0x05);*/

	std::ifstream stream;
	//stream.open("lda-sta-loop-example.bin", std::ios_base::binary);
	stream.open("bins/test.bin", std::ios_base::binary);
	if (!stream.bad()) {
		std::vector<byte> data((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

		memory->WriteBytes(0x8000, data.data(), data.size()-1);
		//printf("Loading file %s", stream.)
	}

	cpu->Execute();

	return 0;
}

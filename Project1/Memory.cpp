#include "Memory.h"
#include <malloc.h>
#include <iostream>
#include <string>

Memory* Memory::Initialize()
{
	Memory* out = (Memory*)malloc(sizeof(Memory));

	out->Clear();
		
	return out;
}

void Memory::Clear(byte defvalue)
{
	std::fill(Data, Data + MEM_SIZE, defvalue);
}

byte Memory::ReadByte(const word& addr)
{
	if(addr < MEM_SIZE) return Data[addr];

	return 0x00;
}

word Memory::ReadWord(const word& addr)
{
	byte low = ReadByte(addr);
	byte high = 0x00;

	if(addr < 0xFFFF) high = ReadByte(addr + 1);

	return MAKE_WORD(low, high);
}

void Memory::WriteByte(const word& addr, const byte data)
{
	if (addr < MEM_SIZE) Data[addr] = data;
}

void Memory::WriteWord(const word& addr, const word data)
{
	WriteByte(addr,		GET_LOW_BYTE(data));

	if(addr < 0xFFFF) WriteByte(addr + 1, GET_HIGH_BYTE(data));
}

void Memory::WriteBytes(const word& offset, byte* data, size_t size)
{
	const size_t maxlen = std::min((int)size, MEM_SIZE - offset);

	memcpy(&Data[offset], data, maxlen);
}

byte& Memory::operator[](size_t i)
{
	return Data[i];
}

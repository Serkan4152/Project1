#pragma once
#include "Utils.h"

class Memory
{
public:
	static Memory* Initialize();

	void Clear(byte defvalue = 0);

	byte ReadByte(const word& addr);
	word ReadWord(const word& addr);

	void WriteByte(const word& addr, const byte data);
	void WriteWord(const word& addr, const word data);

	void WriteBytes(const word& offset, byte* data, size_t size);

	//Allow Moving
	Memory(Memory&&) = default;
	Memory& operator=(Memory&&) = default;

	// No Copying
	Memory(const Memory&) = delete;
	Memory& operator=(const Memory&) = delete;


	byte& operator[](size_t i);
private:
	byte Data[MEM_SIZE]; //64KB
};
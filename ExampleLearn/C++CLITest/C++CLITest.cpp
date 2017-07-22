// C++CLITest.cpp: 主项目文件。

#include "stdafx.h"
#include <vcclr.h>

using namespace System;
using namespace System::Runtime::InteropServices;

ref class Square
{
public :
	Square() : Square(20) {}
	Square(int dims) : Dims(dims) {}
	int Area()
	{
		return Dims*Dims;
	}
	int Dims;
};

ref class Cube sealed: public Square
{
public:
	int Volume()
	{
		return Area() * Dims;
	}
	
};


void PrintArray(array<int>^ ar)
{
	for each (auto intvalue in ar)
	{
		Console::WriteLine(intvalue);
	}
	String^ str = gcnew String("sfsd");
	pin_ptr<const wchar_t> dfs = PtrToStringChars(str);
};

int main(array<System::String ^> ^args)
{
	Cube ^cube = gcnew Cube();
	//cube->Dims = 3;
	
	Console::WriteLine(cube->Dims);
	Console::WriteLine(cube->Area());
	Console::WriteLine(cube->Volume());
	Console::ReadKey();
    return 0;
}

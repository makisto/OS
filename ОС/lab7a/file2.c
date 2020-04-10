#include <windows.h>

extern _declspec(dllexport);
int a = 23;
_declspec(dllexport);

int f(int b)
{
	return b * b;
}

_declspec(dllexport);
int g(int b)
{
	return b * b * b;
}

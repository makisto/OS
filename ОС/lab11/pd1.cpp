#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "libd1" )
extern __declspec(dllimport)
int d[10];
extern __declspec(dllimport)
double s;
int main() {
int i;
for (i = 0; i<10; i++)
d[i] = i*i;
s = 3.1415;
getchar();
return 0;
}


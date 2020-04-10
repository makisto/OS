#include <windows.h>
#include <imagehlp.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	LOADED_IMAGE LoadedImage;
	PUCHAR BaseAddress;
	DWORD RVAExpDir, VAExpAddress;
	IMAGE_EXPORT_DIRECTORY *ExpTable;
	char *sName;
	DWORD nNames;
	char *pName;
	char **pNames;
	
	if(!MapAndLoad(argv[1], NULL, &LoadedImage, TRUE, TRUE))
	{
		printf("Something's wrong!\n");
		exit(1);
	}
	
	BaseAddress = LoadedImage.MappedAddress;
	printf("0x%lx - Base Address\n", BaseAddress);
	
	RVAExpDir = LoadedImage.FileHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
	printf("0x%lx - RVA\n", RVAExpDir);
	
	VAExpAddress = (DWORD)ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, RVAExpDir, NULL);
	printf("0x%lx - VA\n", VAExpAddress);
	
	ExpTable = (IMAGE_EXPORT_DIRECTORY*)VAExpAddress;
	
	pNames = (char**)ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, ExpTable->AddressOfNames, NULL);
	nNames = ExpTable->NumberOfNames;
	printf("Exported data:\n", pNames);
	
	for(DWORD i = 0; i < nNames; i++)
	{
		pName = (char*)ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, (DWORD)*pNames, NULL);
		printf("%s\n", pName);
		*pNames++;
	}
	UnMapAndLoad(&LoadedImage);
	return 0;
}

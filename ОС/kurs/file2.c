#include <windows.h>
#include <imagehlp.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
				
int main(int argc, char* argv[]) 
{
	int f = 0, f1 = 1;
	char fileName[MAX_PATH + 1] = {'\0'};
	char buff[MAX_PATH + 1] = {'\0'};
	char ch, ch1, ch2;
	
	HANDLE file = NULL;
	HANDLE hMapping = NULL;
	LPBYTE fileData = NULL;
	
	IMAGE_DOS_HEADER* dosHeader = NULL;
	IMAGE_NT_HEADERS* imageNTHeaders = NULL;
	IMAGE_SECTION_HEADER* sectionHeader = NULL;

	PIMAGE_SECTION_HEADER importSection = NULL;
	IMAGE_IMPORT_DESCRIPTOR* importDescriptor;

	IMAGE_EXPORT_DIRECTORY* pExportDir = NULL;
	DWORD dwExportDirStart = NULL;
	DWORD dwExportDirEnd = NULL;
	
	PIMAGE_THUNK_DATA thunkData;
	DWORD thunk = NULL;	
	DWORD importDirectoryRVA;
	
	LOADED_IMAGE LoadedImage;
	PUCHAR BaseAddress;
	DWORD RVAExpDir, VAExpAddress;
	IMAGE_EXPORT_DIRECTORY *ExpTable;
	
	char *sName;
	char *pName;
	char **pNames;
	
	while(1)
	{
		system("CLS");
		printf("1 - NAME OF FILE\n");
		printf("2 - DOS HEADER\n");
		printf("3 - PE HEADER\n");
		printf("4 - SECTIONS\n");
		printf("5 - FUNCTIONS\n");
		printf("6 - EXIT\n\n\n");
		printf("CURRENT FILE - %s\n", fileName);
		ch = getch();
		switch(ch)
		{
			case '1':
				system("CLS");
				strcpy(buff, fileName);
				printf("ENTER FULL FILEPATH:\n");
			//C:\Windows\System32\notepad.exe
			//C:\Windows\System32\kernel32.dll	
				gets(fileName);
				file = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
				if (file == INVALID_HANDLE_VALUE) 
				{
					strcpy(fileName, buff);
					printf("Could not read file\n");
					printf("Error code - %d\n", GetLastError());
					system("PAUSE");
					break;
				}	
				hMapping = CreateFileMapping(file, NULL, PAGE_READONLY, 0, 0, NULL);	
				CloseHandle(file);
				if(hMapping != NULL)
				{
					fileData = (LPBYTE)MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
					CloseHandle(hMapping);	
				}		
				dosHeader = (IMAGE_DOS_HEADER*)fileData;
				if(IsBadReadPtr(dosHeader, sizeof(IMAGE_DOS_HEADER)))
				{
					strcpy(fileName, buff);
					printf("DOS-Pointer error\n");
					printf("Error code - %d\n", GetLastError());
					system("PAUSE");
					break;		
				}
				imageNTHeaders = (IMAGE_NT_HEADERS*)(fileData + dosHeader->e_lfanew);	
				if(IsBadReadPtr(imageNTHeaders, sizeof(IMAGE_NT_HEADERS)))
				{
					strcpy(fileName, buff);
					printf("IMAGE Pointer error\n");
					printf("Error code - %d\n", GetLastError());
					system("PAUSE");
					break;		
				}
				sectionHeader = IMAGE_FIRST_SECTION(imageNTHeaders);							
				importDirectoryRVA = imageNTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;			
				for(int i = 0; i < imageNTHeaders->FileHeader.NumberOfSections; i++, sectionHeader++) 
				{
					if(importDirectoryRVA >= sectionHeader->VirtualAddress && importDirectoryRVA < sectionHeader->VirtualAddress + sectionHeader->Misc.VirtualSize)
					{
						importSection = sectionHeader;
					}
				}					
				f = 1;
				system("PAUSE");
				break;
			case '2':
				system("CLS");
				if(f == 0)
				{
					printf("Out of file\n");
					system("PAUSE");
					break;
				}
				printf("Magic Number - %lu\n", dosHeader->e_magic);
				printf("Bytes on the Last Page - %lu\n", dosHeader->e_cblp);
				printf("Pages in File - %lu\n", dosHeader->e_cp);
				printf("Relocations - %lu\n", dosHeader->e_crlc);
				printf("Size of Header in Paragraphs - %lu\n", dosHeader->e_cparhdr);
				printf("Minimal DLC Paragraphs - %lu\n", dosHeader->e_minalloc);
				printf("Maximum DLC Paragraphs - %lu\n", dosHeader->e_maxalloc);
				printf("Start Relative SS value - %lu\n", dosHeader->e_ss);
				printf("Start Relative SP value - %lu\n", dosHeader->e_sp);
				printf("Checksum - %lu\n", dosHeader->e_csum);
				printf("Start IP value - %lu\n", dosHeader->e_ip);
				printf("Start Relative CS value - %lu\n", dosHeader->e_cs);
				printf("Readdress Table Address - %lu\n", dosHeader->e_lfarlc);
				printf("Number of Overlays - %lu\n", dosHeader->e_ovno);
				printf("OEM ID - %lu\n", dosHeader->e_oemid);
				printf("OEM Info - %lu\n", dosHeader->e_oeminfo);
				printf("PE HEADER Address - %lu\n", dosHeader->e_lfanew);
				system("PAUSE");
				break;
			case '3':
				system("CLS");
				if(f == 0)
				{
					printf("Out of file\n");
					system("PAUSE");
					break;
				}
				ch1 = '0';
				while(ch1 != '5')
				{
					system("CLS");
					printf("1 - SIGNATURE\n");
					printf("2 - FILE HEADER\n");
					printf("3 - OPTIONAL HEADER\n");
					printf("4 - DATA DIRECTORIES\n");
					printf("5 - BACK\n");
					ch1 = getch();
					switch(ch1)
					{
						case '1':
							system("CLS");
							printf("Signature - %lu\n", imageNTHeaders->Signature);
							system("PAUSE");
							break;
						case '2':
							system("CLS");
							printf("Machine - 0x%x\n", imageNTHeaders->FileHeader.Machine);
							printf("Number of Sections - 0x%x\n", imageNTHeaders->FileHeader.NumberOfSections);
							printf("Time Date Stamp - 0x%x\n", imageNTHeaders->FileHeader.TimeDateStamp);
							printf("Pointer to Symbol Table - 0x%x\n", imageNTHeaders->FileHeader.PointerToSymbolTable);
							printf("Number of Symbols - 0x%x\n", imageNTHeaders->FileHeader.NumberOfSymbols);
							printf("Size of Optional Header - 0x%x\n", imageNTHeaders->FileHeader.SizeOfOptionalHeader);
							printf("Characteristics - 0x%x\n", imageNTHeaders->FileHeader.Characteristics);
							system("PAUSE");
							break;
						case '3':
							system("CLS");
							printf("Magic - 0x%x\n", imageNTHeaders->OptionalHeader.Magic);
							printf("Major Linker Version - 0x%x\n", imageNTHeaders->OptionalHeader.MajorLinkerVersion);
							printf("Minor Linker Version - 0x%x\n", imageNTHeaders->OptionalHeader.MinorLinkerVersion);
							printf("Size Of Code - 0x%x\n", imageNTHeaders->OptionalHeader.SizeOfCode);
							printf("Size Of Initialized Data - 0x%x\n", imageNTHeaders->OptionalHeader.SizeOfInitializedData);
							printf("Size Of UnInitialized Data - 0x%x\n", imageNTHeaders->OptionalHeader.SizeOfUninitializedData);
							printf("Address Of Entry Point (.text) - 0x%x\n", imageNTHeaders->OptionalHeader.AddressOfEntryPoint);
							printf("Base Of Code - 0x%x\n", imageNTHeaders->OptionalHeader.BaseOfCode);
							printf("Base Of Data - 0x%x\n", imageNTHeaders->OptionalHeader.BaseOfData);
							printf("Image Base - 0x%x\n", imageNTHeaders->OptionalHeader.ImageBase);
							printf("Section Alignment - 0x%x\n", imageNTHeaders->OptionalHeader.SectionAlignment);
							printf("File Alignment - 0x%x\n", imageNTHeaders->OptionalHeader.FileAlignment);
							printf("Major Operating System Version - 0x%x\n", imageNTHeaders->OptionalHeader.MajorOperatingSystemVersion);
							printf("Minor Operating System Version - 0x%x\n", imageNTHeaders->OptionalHeader.MinorOperatingSystemVersion);
							printf("Major Image Version - 0x%x\n", imageNTHeaders->OptionalHeader.MajorImageVersion);
							printf("Minor Image Version - 0x%x\n", imageNTHeaders->OptionalHeader.MinorImageVersion);
							printf("Major Subsystem Version - 0x%x\n", imageNTHeaders->OptionalHeader.MajorSubsystemVersion);
							printf("Minor Subsystem Version - 0x%x\n", imageNTHeaders->OptionalHeader.MinorSubsystemVersion);
							printf("Win32 Version Value - 0x%x\n", imageNTHeaders->OptionalHeader.Win32VersionValue);
							printf("Size Of Image - 0x%x\n", imageNTHeaders->OptionalHeader.SizeOfImage);
							printf("Size Of Headers - 0x%x\n", imageNTHeaders->OptionalHeader.SizeOfHeaders);
							printf("CheckSum - 0x%x\n", imageNTHeaders->OptionalHeader.CheckSum);
							printf("Subsystem - 0x%x\n", imageNTHeaders->OptionalHeader.Subsystem);
							printf("DllCharacteristics - 0x%x\n", imageNTHeaders->OptionalHeader.DllCharacteristics);
							printf("Size Of Stack Reserve - 0x%x\n", imageNTHeaders->OptionalHeader.SizeOfStackReserve);
							printf("Size Of Stack Commit - 0x%x\n", imageNTHeaders->OptionalHeader.SizeOfStackCommit);
							printf("Size Of Heap Reserve - 0x%x\n", imageNTHeaders->OptionalHeader.SizeOfHeapReserve);
							printf("Size Of Heap Commit - 0x%x\n", imageNTHeaders->OptionalHeader.SizeOfHeapCommit);
							printf("Loader Flags - 0x%x\n", imageNTHeaders->OptionalHeader.LoaderFlags);
							printf("Number Of Rva And Sizes - 0x%x\n", imageNTHeaders->OptionalHeader.NumberOfRvaAndSizes);
							system("PAUSE");
							break;
						case '4':
							system("CLS");
							printf("Export Directory Address - 0x%x; Size: 0x%x\n", imageNTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress, imageNTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size);
							printf("Import Directory Address - 0x%x; Size: 0x%x\n", imageNTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress, imageNTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size);
							system("PAUSE");
							break;
						default:
							break;
					}
				}
				break;	
			case '4':
				system("CLS");
				if(f == 0)
				{
					printf("Out of file\n");
					system("PAUSE");
					break;
				}
				sectionHeader = IMAGE_FIRST_SECTION(imageNTHeaders);
				for (int i = 0; i < imageNTHeaders->FileHeader.NumberOfSections; i++, sectionHeader++) 
				{
					printf("%s\n", sectionHeader->Name);
					printf("Virtual Size - 0x%x\n", sectionHeader->Misc.VirtualSize);
					printf("Virtual Address - 0x%x\n", sectionHeader->VirtualAddress);
					printf("Size Of Raw Data - 0x%x\n", sectionHeader->SizeOfRawData);
					printf("Pointer To Raw Data - 0x%x\n", sectionHeader->PointerToRawData);
					printf("Pointer To Relocations - 0x%x\n", sectionHeader->PointerToRelocations);
					printf("Pointer To Line Numbers - 0x%x\n", sectionHeader->PointerToLinenumbers);
					printf("Number Of Relocations - 0x%x\n", sectionHeader->NumberOfRelocations);
					printf("Number Of Line Numbers - 0x%x\n", sectionHeader->NumberOfLinenumbers);
					printf("Characteristics - 0x%x\n", sectionHeader->Characteristics);
				}
				system("PAUSE");
				break;
			case '5':
				system("CLS");
				if(f == 0)
				{
					printf("Out of file\n");
					system("PAUSE");
					break;
				}
				ch1 = '0';
				while(ch1 != '4')
				{
					system("CLS");
					printf("1 - DLL LIST\n");
					printf("2 - IMPORT\n");
					printf("3 - EXPORT\n");
					printf("4 - BACK\n");
					ch1 = getch();
					switch(ch1)
					{
						case '1':
							system("CLS");
							if(importSection == NULL)
							{
								importDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)fileData + imageNTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;	
							}
							else
							{
								importDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(fileData + importSection->PointerToRawData + (imageNTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress - importSection->VirtualAddress));	
							}
							while(importDescriptor->Name != 0)	
							{
								printf("%s\n", fileData + importSection->PointerToRawData + (importDescriptor->Name - importSection->VirtualAddress));
								importDescriptor++;
							}
							system("PAUSE");
							break;
						case '2':
							if(imageNTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress == 0)
							{
								printf("NO IMPORT\n");
								system("PAUSE");
								break;
							}
							if(importSection == NULL)
							{
								importDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)fileData + imageNTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;	
							}
							else
							{
								importDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(fileData + importSection->PointerToRawData + (imageNTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress - importSection->VirtualAddress));	
							}
							while(importDescriptor->Name != 0)	
							{
								system("CLS");
								printf("%s\n", fileData + importSection->PointerToRawData + (importDescriptor->Name - importSection->VirtualAddress));
								thunk = importDescriptor->OriginalFirstThunk == 0 ? importDescriptor->FirstThunk : importDescriptor->OriginalFirstThunk;
								thunkData = (PIMAGE_THUNK_DATA)(fileData + importSection->PointerToRawData + (thunk - importSection->VirtualAddress));
						
								for (;thunkData->u1.AddressOfData != 0; thunkData++) 
								{
									if (thunkData->u1.AddressOfData > 0x80000000) 
									{
										printf("Ordinal: %x\n", (WORD)thunkData->u1.AddressOfData);
									} 
									else 
									{
										printf("%s\n", (fileData + importSection->PointerToRawData + (thunkData->u1.AddressOfData - importSection->VirtualAddress + 2)));
									}
								}
								printf("1 - GO NEXT\n");
								printf("2 - GO PAST\n");
								printf("3 - EXIT\n");
								ch2 = getch();
								switch(ch2)
								{
									case '1':
										importDescriptor++;
										break;
									case '2':
										importDescriptor--;
										break;
									case '3':
										f1 = 0;
										break;
									default:
										break;
								}
								if(f1 == 0)
								{
									f1 = 1;
									break;
								}
							}
							break;
						case '3':
							if(imageNTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress == 0)
							{
								printf("NO EXPORT\n");
								system("PAUSE");
								break;
							}
							if(!MapAndLoad(fileName, NULL, &LoadedImage, TRUE, TRUE))
							{
								printf("Something's wrong!\n");
								system("PAUSE");
								break;
							}							
							BaseAddress = LoadedImage.MappedAddress;							
							RVAExpDir = LoadedImage.FileHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;							
							VAExpAddress = (DWORD)ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, RVAExpDir, NULL);							
							ExpTable = (IMAGE_EXPORT_DIRECTORY*)VAExpAddress;
							
							pNames = (char**)ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, ExpTable->AddressOfNames, NULL);
							
							for(DWORD i = 0; i < ExpTable->NumberOfNames; i++)
							{
								pName = (char*)ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, (DWORD)*pNames, NULL);
								printf("%s\n", pName);
								*pNames++;
							}
							UnMapAndLoad(&LoadedImage);
							system("PAUSE");
							break;
							/*if(importSection == NULL)
							{
								importDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)fileData + imageNTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;	
							}
							else
							{
								importDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(fileData + importSection->PointerToRawData + (imageNTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress - importSection->VirtualAddress));	
							}
							while(importDescriptor->Name != 0)	
							{
								system("CLS");
								printf("%s\n", fileData + importSection->PointerToRawData + (importDescriptor->Name - importSection->VirtualAddress));
								if(!MapAndLoad(fileData + importSection->PointerToRawData + (importDescriptor->Name - importSection->VirtualAddress), NULL, &LoadedImage, TRUE, TRUE))
								{
									importDescriptor++;
									continue;
								}									
								BaseAddress = LoadedImage.MappedAddress;									
								RVAExpDir = LoadedImage.FileHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;						
								VAExpAddress = (DWORD)ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, RVAExpDir, NULL);								
								ExpTable = (IMAGE_EXPORT_DIRECTORY*)VAExpAddress;									
								pNames = (char**)ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, ExpTable->AddressOfNames, NULL);
	
								for(DWORD i = 0; i < ExpTable->NumberOfNames; i++)
								{
									pName = (char*)ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, (DWORD)*pNames, NULL);
									printf("%s\n", pName);
									*pNames++;									
								}
								UnMapAndLoad(&LoadedImage);
								printf("1 - GO NEXT\n");
								printf("2 - GO PAST\n");
								printf("3 - EXIT\n");
								ch2 = getch();
								switch(ch2)
								{
									case '1':
										importDescriptor++;
										break;
									case '2':
										importDescriptor--;
										break;
									case '3':
										f1 = 0;
										break;
									default:
										break;
								}
								if(f1 == 0)
								{
									f1 = 1;
									break;
								}
							}
							break;
						default:
							break;*/
					}
				}
				break;
			case '6':
				exit(0);
		}		
	}
	UnmapViewOfFile(fileData);		
    return 0;
}

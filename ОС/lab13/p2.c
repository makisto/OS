#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

int main(int argc, char* argv[])
{
	char buff[80];
	FILE* fp = fopen("1.html", "w+");
	fprintf(fp, "<HTML>");
	fprintf(fp, "<BODY bgcolor=#FFDD00>");
	fprintf(fp, "<CENTER><TABLE>");
	while(fgets(buff, 80, stdin))
	{
		char* p = strchr(buff, '\n');
		if(p)
		{
			*p = '\0';
		}
		fprintf(fp, "<TR>");
		fprintf(fp, "<TD>");
		fprintf(fp, "<H1>");
		fprintf(fp, "%s", buff);
		fprintf(fp, "</H1>");
		fprintf(fp, "</TD>");
		fprintf(fp, "</TR>");
	}
	fprintf(fp, "</TABLE></CENTER>");
	fprintf(fp, "</BODY>");
	fprintf(fp, "</HTML>");
	fclose(fp);
	
	return 0;
}

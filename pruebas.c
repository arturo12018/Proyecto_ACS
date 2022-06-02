#include<stdio.h>
#	include<stdlib.h>
#include <string.h>
int main(){


char buf[300];
char path[300];
FILE *fp;
FILE *pf;

fgets(buf, 300, stdin);


fp = popen(buf, "r");

	

    printf("%s", path);

	
//Guarda los datos en el archivo
if (!(pf=fopen("comando.txt","w"))) /* controlamos si se produce un error */
{
	printf("Error al abrir el fichero");
	exit(0); /* abandonamos el programa */
}
else 
{
	//Guardamos los datos en el archivo
	while (fgets(path, 300, fp) != NULL)
	fputs(path,pf); /* o también así: fputs("Me llamo Vicente",pf); */
	fclose(pf);
}


pclose(fp);




return 0;
}

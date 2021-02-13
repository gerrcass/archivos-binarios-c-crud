#include <stdio.h>	/* print, scanf */
#include <string.h> /* strcpy, strcmp */
#include <stdlib.h>	/* system */
#include <conio.h> // Para el manejo de clrscr
 
#define MAX 80
 
/* Estructuras */

struct modelo{
	int cedula;
	char nombre[MAX];
	char especialidad[MAX];
	char sexo[MAX];
	int edad;
	char colorPiel[MAX];
	float estatura;
	float tarifaHora;
};

typedef struct modelo Modelo;
 
/* Opciones del Menu */
void menuPrincipal();
void menuInsertar();
void menuBuscar();
void menuEliminar();
void menuMostrarModelos();
void menuModificar();
void reporteEspecialidad(); 
void listadoPorEspecialidad(const char especialidad[MAX]);
void reportePorColorPiel();
void listadoPorColorPiel(const char colorPiel[MAX]);
void reporteModeloMasJoven();

Modelo existeModelo(int cedulaModelo); 
int insertarModelo(Modelo modelo); 
int eliminarModelo(int cedulaModelo); 
int modificarModelo(int cedulaModelo);

/* Titular del programa */
void tituloPrincipal();
 

int main()
{
	menuPrincipal();
 
	return 0;
}
 
void menuPrincipal()
{
	char repite = 1;
	int opcion = -1;

	do {
		system("cls");
 
		tituloPrincipal();
 
		printf("\n\t\t\t\tMENU PRINCIPAL\n");
		printf("\n\t\t[1]. Insertar modelo\n");
		printf("\t\t[2]. Cosultar modelos\n");
		printf("\t\t[3]. Modificar modelo\n");
		printf("\t\t[4]. Eliminar modelo\n");
		printf("\t\t[5]. Reporte por especialidad\n");
		printf("\t\t[6]. Reporte por color de piel\n");
		printf("\t\t[7]. Reporte de modelo mas joven\n");
		printf("\t\t[8]. Salir\n");
		printf("\n\t\tIngrese su opcion: [ ]\b\b");
 
		scanf("%d", &opcion);
		
		switch (opcion) {
 
			case 1:
				menuInsertar();
				break;
 
			case 2:
				menuMostrarModelos();
				break;
 
			case 3:
				menuModificar();
				break;
 
			case 4:
				menuEliminar();
				break;
 
			case 5:
				reporteEspecialidad();
				break;
 
			case 6:
				reportePorColorPiel();
				break;
 
			case 7:
				reporteModeloMasJoven();
				break;
			case 8:
				repite = 0;
				break;
		}
 
	} while (repite);
}

void menuInsertar()
{
	Modelo modelo;
	int cedulaModelo = 0;
	int repite = 1;
	char respuesta[1];
 
	do {
		system("cls");
		tituloPrincipal();
		printf("\n\t\t\t### INSERTAR MODELO ###\n");
 
		/* Se pide la cedula de modelo a insertar */
		printf("\n\tCedula de modelo: ");
		scanf("%d", &cedulaModelo);
		
		if(cedulaModelo==0){
			printf("\n\tNo puede ingresar modelo con cedula numero 0.\n\tPresione cualquier tecla para regresar al menu anterior...");
			getch();
			break;
		}
 
		/* Se verifica que el registro de modelo no haya sido almacenado anteriormente */
		modelo=existeModelo(cedulaModelo);
				
		if (modelo.cedula == 0) {
 
			modelo.cedula = cedulaModelo;
 
			/* Se piden los demas datos de modelo a insertar */
			printf("\tNombre de modelo: ");
			scanf("%s", &modelo.nombre);
 
			printf("\tEspecialidad de modelo (Pasarela, VideoClip, Exhibicion, Comerciales): ");
			scanf("%s", &modelo.especialidad);

			printf("\tSexo o Genero (M/F): ");
			scanf("%s", &modelo.sexo);

			printf("\tEdad de modelo: ");
			scanf("%d", &modelo.edad);

			printf("\tColor de piel de modelo (Blanca / Morena / Negra): ");
			scanf("%s", &modelo.colorPiel);

			printf("\tEstatura de modelo: ");
			scanf("%f", &modelo.estatura);
			
			printf("\tTarifa por hora: ");
			scanf("%f", &modelo.tarifaHora);
			
						/* Datos de modelo insertados correctamente */
			if (insertarModelo(modelo)==1) {
				printf("\n\tEl registro de la modelo fue insertado correctamente\n");
 
			} else {
				printf("\n\tOcurrió un error al intentar insertar el registro de la modelo\n");
				printf("\tInténtelo mas tarde\n");
			}
		} else {
			/* Modelo ya existe, no puede ser insertado un registro con la misma cedula. */
			printf("\n\tModelo con cedula %d ya existe.\n", cedulaModelo);
			printf("\tNo puede ingresar dos modelos con el mismo numero de cedula.\n");
		}
 
		printf("\n\tDesea seguir ingresando modelos? [S/N]: ");
		scanf("%s",&respuesta);
		
		if(strcmp(respuesta, "s")==0 || strcmp(respuesta, "S")==0){
			repite=1;
		}else{
			repite=0;
		}
 
	} while (repite==1);
}
 
void menuEliminar()
{
	Modelo modelo;
	int cedulaModelo = 0;
	int repite = 1;
	char respuesta[1];
 
	do {
		system("cls");
		tituloPrincipal();
		printf("\n\t\t\t### ELIMINAR MODELO POR CEDULA ###\n");
 
		printf("\n\tCedula de modelo: ");
		scanf("%d", &cedulaModelo);
		
		/* Se verifica que exista la modelo que se busca */

		modelo = existeModelo(cedulaModelo);
		
		if (modelo.cedula != 0) { 
			printf("\t\tNombre: %s\n", &modelo.nombre);			
			printf("\t\tEspecilidad: %s \n", &modelo.especialidad);
			printf("\t\tSexo: %s \n", &modelo.sexo);
			printf("\t\tEdad: %d\n", modelo.edad);
			printf("\t\tColor de piel: %s \n", &modelo.colorPiel);
			printf("\t\tEstatura: %.2f\n", modelo.estatura);
			printf("\t\tTarifa por hora: %.2f\n", modelo.tarifaHora);
 
			printf("\n\tSeguro que desea eliminar esta modelo? [S/N]: ");
			scanf("%s",&respuesta);
		
			if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
				if (eliminarModelo(modelo.cedula)==1) {
					printf("\n\tModelo correspondiente a cedula %d ha sido eliminado satisfactoriamente.\n", modelo.cedula);
				} else {
					printf("Modelo con cedula %d no esta registrada.", modelo.cedula);
				}
			}
 
		} else {
			/* Cedula no registrada */
			printf("\n\tNo existe ninguna modelo con cedula %d.\n", modelo.cedula);
		}
 
		printf("\n\tDesea eliminar mas registros de modelos? [S/N]: ");
		scanf("%s",&respuesta);

		if(strcmp(respuesta, "s")==0 || strcmp(respuesta, "S")==0){
			repite=1;
		}else{
			repite=0;
		}
 
	} while (repite==1);
}
 
void menuMostrarModelos(){
	Modelo modelo;
	FILE *archivo;
	int repite = 1,cedulaModelo=0;
	char respuesta[MAX];
	
	
	
		system("cls");
		tituloPrincipal();
		/* Abre el archivo en modo lectura */
		archivo = fopen("agencia_model_ltos.dat", "rb");
	 
		if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
			printf("Error abriendo el archivo.");
		} else {
			printf("\n\t\t\t    ==> LISTADO DE MODELOS <==\n");
			printf(" -------------------------------------------------------------------------------------------\n");
			printf("%8s\t%-10s%10s%8s%7s%12s%10s%15s\n", "CEDULA", "NOMBRE", "Especialidad", "SEXO", "EDAD", "ESTATURA","TARIFA","COLOR PIEL");
			printf(" -------------------------------------------------------------------------------------------\n");
			
			while(fread(&modelo, sizeof(modelo), 1, archivo)==1){
				//printf("%8d \t%-20.20s%15.15s%15.15s%10d\n", modelo.cedula, &modelo.nombre, &modelo.especialidad, &modelo.colorPiel, modelo.edad);
				printf(" %8d \t%-10.20s%-12.15s%8.1s%8d %6.2fm        $%-10.2f%s\n", modelo.cedula, &modelo.nombre, &modelo.especialidad, &modelo.sexo, modelo.edad,modelo.estatura,modelo.tarifaHora,&modelo.colorPiel);
			}
			fclose(archivo);
		}
		
		do {
	
			printf("\n\t\t\tDesea consultar modelo en especifico? [S/N]: ");
			scanf("%s",&respuesta);
			
			if(strcmp(respuesta, "s")==0 || strcmp(respuesta, "S")==0){
				repite=1;
				
				printf("\n\tCedula de modelo: ");
				scanf("%d", &cedulaModelo);
				
				/* Se verifica que exista la modelo que se busca */
		
				modelo = existeModelo(cedulaModelo);
				
				if (modelo.cedula != 0) { 
					system("cls");
					tituloPrincipal();
					
					printf("\n\t\t\t    ==> INFORMACION DE MODELO <==\n");
					printf(" -------------------------------------------------------------------------------------------\n");
					printf("%8s\t%-10s%10s%8s%7s%12s%10s%15s\n", "CEDULA", "NOMBRE", "Especialidad", "SEXO", "EDAD", "ESTATURA","TARIFA","COLOR PIEL");
					printf(" -------------------------------------------------------------------------------------------\n");
					
					printf(" %8d \t%-10.20s%-12.15s%8.1s%8d %6.2fm        $%-10.2f%s\n", modelo.cedula, &modelo.nombre, &modelo.especialidad, &modelo.sexo, modelo.edad,modelo.estatura,modelo.tarifaHora,&modelo.colorPiel);
					
					
				}else{
					printf("\n\t\t\tCedula no encontrada.\n\n");
				}
				
				
			}else{
				repite=0;
			}
		
		//printf("\n\n\n\nPresione cualquier tecla para volver al menu principal...");
		//getch();
		} while (repite==1);	

}

void menuModificar()
{
	Modelo modelo;
	int cedulaModelo=0;
	int repite = 1;
	char respuesta[1];
 
	 do {
			system("cls");
			tituloPrincipal();
			printf("\n\t\t\t### MODIFICAR DATOS DE MODELO ###\n");
	 
			printf("\n\tCedula de modelo: ");
			scanf("%d", &cedulaModelo);
			
			/* Se verifica que exista la modelo que se busca */
	
			modelo = existeModelo(cedulaModelo);
			
			if (modelo.cedula != 0) {
				printf("\t\tNombre: %s\n", &modelo.nombre);			
				printf("\t\tEspecilidad: %s \n", &modelo.especialidad);
				printf("\t\tSexo: %s \n", &modelo.sexo);
				printf("\t\tEdad: %d\n", modelo.edad);
				printf("\t\tColor de piel: %s \n", &modelo.colorPiel);
				printf("\t\tEstatura: %.2f\n", modelo.estatura);
				printf("\t\tTarifa por hora: %.2f\n", modelo.tarifaHora);
	 
				printf("\n\tSeguro que desea modificar los datos del modelo? [S/N]: ");
				scanf("%s",&respuesta);
			
				if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
					if (modificarModelo(modelo.cedula)==1) {
						printf("\n\tModelo correspondiente a cedula %d ha sido modificado satisfactoriamente.\n", modelo.cedula);
					} else {
						printf("Modelo con cedula %d no esta registrada.", modelo.cedula);
					}
				}
				 
			} else {
				/* Cedula no registrada */
				printf("\n\tNo existe ninguna modelo con cedula %d.\n", modelo.cedula);
			}
 
			printf("\n\tDesea modificar otra modelo? [S/N]: ");
			scanf("%s",&respuesta);

			if(strcmp(respuesta, "s")==0 || strcmp(respuesta, "S")==0){
				repite=1;
			}else{
				repite=0;
			}
 		}while (repite==1);
}
 
void reporteEspecialidad(){
	char repite = 1;
	int opcion = -1;

	do {
		system("cls");
		tituloPrincipal();
 
		printf("\n\t\t\t\tSELECCIONE UNA ESPECIALIDAD:\n");
		printf("\n\t\t[1]. Pasarela\n");
		printf("\t\t[2]. VideoClip\n");
		printf("\t\t[3]. Exhibicion\n");
		printf("\t\t[4]. Comerciales\n");
		printf("\t\t[5]. Volver al menu principal\n");
		printf("\n\t\tIngrese su opcion: [ ]\b\b");
 
		scanf("%d", &opcion);
		
		switch (opcion) {
			case 1:
				listadoPorEspecialidad("Pasarela");
				break;
			case 2:
				listadoPorEspecialidad("VideoClip");
				break;
			case 3:
				listadoPorEspecialidad("Exhibicion");
				break;
			case 4:
				listadoPorEspecialidad("Comerciales");
				break;
			case 5:
				repite = 0;
				break;
		}
	} while (repite);
}

void listadoPorEspecialidad(const char especialidad[MAX]){
	Modelo modelo;
	FILE *archivo;
	float contadorTarifa;

	/* Abre el archivo en modo lectura */
	archivo = fopen("agencia_model_ltos.dat", "rb");
 
	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		printf("Error abriendo el archivo.");
	} else {
		system("cls");
		tituloPrincipal();
		
		printf("\n\t\t    ==> LISTADO DE MODELOS ESPECIALISTAS EN: %s <==\n",especialidad);
		printf(" -------------------------------------------------------------------------------------------\n");
		printf("%8s\t%-10s%15s%8s%7s%12s%10s\n", "CEDULA", "NOMBRE", "COLOR DE PIEL", "SEXO", "EDAD", "ESTATURA","TARIFA");
		printf(" -------------------------------------------------------------------------------------------\n");

		contadorTarifa=0;
		while(fread(&modelo, sizeof(modelo), 1, archivo)==1){
			if(strcmp(modelo.especialidad, especialidad)==0){
				printf(" %8d \t%-10.20s%10.15s%10.1s%8d %8.1fm        $%-10.2f\n", modelo.cedula, &modelo.nombre, &modelo.colorPiel, &modelo.sexo, modelo.edad,modelo.estatura,modelo.tarifaHora);
				contadorTarifa+=modelo.tarifaHora;
			}
		}
		fclose(archivo);
	}
	printf("\t\t\t\t\t\t\t\t\t______\n\n");
	printf("\t\t\t\t\t\t\t\t TOTAL: $%.2f",contadorTarifa);
	printf("\n\n\n\tPresione cualquier tecla para volver al menu anterior...");
	getch();
}

void reportePorColorPiel(){
	char repite = 1;
	int opcion = -1;

	do {
		system("cls");
		tituloPrincipal();
 
		printf("\n\t\t\t\tSELECCIONE UN COLOR DE PIEL:\n");
		printf("\n\t\t[1]. Blanca\n");
		printf("\t\t[2]. Negra\n");
		printf("\t\t[3]. Morena\n");
		printf("\t\t[4]. Volver al menu principal\n");
		printf("\n\t\tIngrese su opcion: [ ]\b\b");
 
		scanf("%d", &opcion);
		
		switch (opcion) {
			case 1:
				listadoPorColorPiel("Blanca");
				break;
			case 2:
				listadoPorColorPiel("Negra");
				break;
			case 3:
				listadoPorColorPiel("Morena");
				break;
			case 4:
				repite = 0;
				break;
		}
	} while (repite);	
}

void listadoPorColorPiel(const char colorPiel[MAX]){
	Modelo modelo,modeloTemp,modelosEncontrados[MAX];
	FILE *archivo;
	int i=0,j=0,contadorModelo=0;

	/* Abre el archivo en modo lectura */
	archivo = fopen("agencia_model_ltos.dat", "rb");
 
	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		printf("Error abriendo el archivo.");
	} else {
		system("cls");
		tituloPrincipal();
		
		printf("\n\t\t\t    ==> LISTADO DE MODELOS CON PIEL: %s <==\n",colorPiel);
		printf(" -------------------------------------------------------------------------------------------\n");
		printf("%8s\t%-10s%15s%8s%7s%12s\n", "CEDULA", "NOMBRE", "ESPECIALIDAD", "SEXO", "EDAD", "ESTATURA");
		printf(" -------------------------------------------------------------------------------------------\n");
		
		contadorModelo=0;
		while(fread(&modelo, sizeof(modelo), 1, archivo)==1){
			if(strcmp(modelo.colorPiel, colorPiel)==0){
				modelosEncontrados[contadorModelo]=modelo;
				contadorModelo++;
			}
		}
		fclose(archivo);
		
		// Ordemar ascendentemente por estatura el arreglo "modelosEncontrados" (arreglo de modelos con el color de piel seleccionado por usuario)
		for(i=0 ;i<contadorModelo;i++){
	        for(j=i+1;j<contadorModelo;j++){
	            if(modelosEncontrados[i].estatura>modelosEncontrados[j].estatura){
	                modeloTemp=modelosEncontrados[i];
	                modelosEncontrados[i]=modelosEncontrados[j];
	                modelosEncontrados[j]=modeloTemp;
	            }
	        }
	    }
	    
	    //imprimir registro de modelos ya previamente ordenado ascendentemente por estatura
	    for(i=0;i<contadorModelo;i++){
			printf(" %8d \t%-10.20s%15.15s%5.1s%8d %8.2fm\n", modelosEncontrados[i].cedula, &modelosEncontrados[i].nombre, &modelosEncontrados[i].especialidad, &modelosEncontrados[i].sexo, modelosEncontrados[i].edad,modelosEncontrados[i].estatura);
		}
		
	}
	printf("\n\n\n\nPresione cualquier tecla para volver al menu anterior...");
	getch();
}

void reporteModeloMasJoven(){	
	Modelo modelo,modelosRegistrados[MAX],modeloTemp;
	int i=0,j=0,contadorModelo=0,contadorMasJoven;
	FILE *archivo;

	/* Abre el archivo en modo lectura */
	archivo = fopen("agencia_model_ltos.dat", "rb");
 
	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		printf("Error intentando abrir el archivo.");
	} else {
		contadorModelo=0;
		while(fread(&modelo, sizeof(modelo), 1, archivo)==1){
				modelosRegistrados[contadorModelo]=modelo;
				contadorModelo++;
		}
		fclose(archivo);
		
		// Ordemar ascendentemente por estatura el arreglo "modelosEncontrados" (arreglo de modelos con el color de piel seleccionado por usuario)
		for(i=0 ;i<contadorModelo;i++){
	        for(j=i+1;j<contadorModelo;j++){
	            if(modelosRegistrados[i].edad>modelosRegistrados[j].edad){
	                modeloTemp=modelosRegistrados[i];
	                modelosRegistrados[i]=modelosRegistrados[j];
	                modelosRegistrados[j]=modeloTemp;
	            }
	        }
	    }
				
		system("cls");
		tituloPrincipal();
		
		printf("\n\t\t\t        ==> MODELO(s) MAS JOVEN(es) <==\n");
		printf(" -------------------------------------------------------------------------------------------\n");
		printf("%8s\t%-10s%15s%8s%7s%12s\n", "CEDULA", "NOMBRE", "ESPECIALIDAD", "SEXO", "EDAD", "ESTATURA");
		printf(" -------------------------------------------------------------------------------------------\n");
		
		for(i=0 ;i<contadorModelo;i++){
			if(modelosRegistrados[i].edad != modelosRegistrados[i+1].edad){
				contadorMasJoven=i+1;
				break;	
			}
		}
		for(i=0 ;i<contadorMasJoven;i++){
			printf(" %8d \t%-10.20s%15.15s%5.1s%8d %8.1fm\n", modelosRegistrados[i].cedula, &modelosRegistrados[i].nombre, &modelosRegistrados[i].especialidad, &modelosRegistrados[i].sexo, modelosRegistrados[i].edad,modelosRegistrados[i].estatura);
		}
	}
	
	printf("\n\n\n\nPresione cualquier tecla para volver al menu anterior...");
	getch();
}

Modelo existeModelo(int cedulaModelo)
{
	Modelo modeloExistente;
	Modelo modelo;
	FILE *archivo;

	//valor de retorno cuando no existe registro en archivo para cierta cedula
	modeloExistente.cedula = 0;

	/* Abre el archivo en modo lectura */
	archivo = fopen("agencia_model_ltos.dat", "rb");
 
	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		modeloExistente.cedula = 0;
	} else {
		while(fread(&modelo, sizeof(modelo), 1, archivo)==1){
			if(modelo.cedula == cedulaModelo){
				modeloExistente = modelo;
				break;
			}
		}
		fclose(archivo);
	}
	return modeloExistente;
}
 
int insertarModelo(Modelo modelo)
{
	FILE *archivo;
	int insercion = 0;
 
	/* Abre el archivo para agregar datos al final */
	archivo = fopen("agencia_model_ltos.dat", "ab+");	/* Añade datos al final. Si el archivo no existe, es creado */
 
	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		insercion = 0;
 
	} else {
		fwrite(&modelo, sizeof(modelo), 1, archivo);
		insercion = 1;
 
		/* Cierra el archivo */
		fclose(archivo);
	}
 
	return insercion;
}

int modificarModelo(int cedulaModelo)
{
	FILE *archivo;
	FILE *auxiliar;
	Modelo modelo;
	int modificar = 0; //cuando esta funcion retorna 0 significa una se�al de modelo no modifiacdo, cuando retorna 1, lo contrario.
 
	/* Abre el archivo para leer */
	archivo = fopen("agencia_model_ltos.dat", "rb");
	auxiliar = fopen("temporal.dat", "ab+");
 
	if (archivo == NULL || auxiliar == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		modificar = 0;
		printf("Error intentando abrir el archivo. Intentelo mas tarde."); 
	} else {
		modificar = 1; //1 significa modelo modificado al retorno de esta funcion
		
		while(fread(&modelo, sizeof(modelo), 1, archivo)==1){
			if(modelo.cedula == cedulaModelo){
				printf("\tNombre de modelo: ");
				scanf("%s", &modelo.nombre);
	 
				printf("\tEspecialidad de modelo (Pasarela, VideoClip, Exhibicion, Comerciales): ");
				scanf("%s", &modelo.especialidad);
	
				printf("\tSexo o Genero (M/F): ");
				scanf("%s", &modelo.sexo);
	
				printf("\tEdad de modelo: ");
				scanf("%d", &modelo.edad);
	
				printf("\tColor de piel de modelo (Blanca / Morena / Negra): ");
				scanf("%s", &modelo.colorPiel);
	
				printf("\tEstatura de modelo: ");
				scanf("%f", &modelo.estatura);
				
				printf("\tTarifa por hora: ");
				scanf("%f", &modelo.tarifaHora);
			}
			fwrite(&modelo, sizeof(modelo), 1, auxiliar);
		}
	
		/* Cierra los archivos */
		fclose(archivo);
		fclose(auxiliar);
		remove("agencia_model_ltos.dat");
  		rename("temporal.dat","agencia_model_ltos.dat");
 
	}
	return modificar;
}

 
int eliminarModelo(int cedulaModelo)
{
	FILE *archivo;
	FILE *auxiliar;
	Modelo modelo;
	int elimina = 0; //0 significa no eliminado
 
	/* Abre el archivo para leer */
	archivo = fopen("agencia_model_ltos.dat", "rb");
	auxiliar = fopen("temporal.dat", "ab+");
 
	if (archivo == NULL || auxiliar == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		elimina = 0;
		printf("Error intentando abrir el archivo. Intentelo mas tarde."); 
	} else {
		modelo = existeModelo(cedulaModelo);
		if(modelo.cedula != 0){
			elimina = 1; //1 significa eliminado
			while(fread(&modelo, sizeof(modelo), 1, archivo)==1){
				if(modelo.cedula != cedulaModelo){
					fwrite(&modelo, sizeof(modelo), 1, auxiliar);	
				}
			}
		}
		/* Cierra los archivos */
		fclose(archivo);
		fclose(auxiliar);
		remove("agencia_model_ltos.dat");
  		rename("temporal.dat","agencia_model_ltos.dat");
 
	}
	return elimina;
}
 
void tituloPrincipal()
{
	printf("\n ===========================================================================================\n");
	printf("\t\t\t\t     AGENCIA MODEL \'ltos\n");
	printf("\t\t\t       Creado Por: Jose Miguel Rojas\n");
	printf(" ===========================================================================================\n");
}

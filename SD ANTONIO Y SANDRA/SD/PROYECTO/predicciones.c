#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct 
{
    float horas[24];
}Dia;

typedef struct
{
    Dia d;
    float fitness;
}MejoresDias;

void comprueba_parametros(int, char **const, int *, int *, int *);

int obtenerNumeroFilasYColumnas(FILE *f, int *nfils, int *ncols);

void parseaLinea(FILE *f, float *datos, int ncols);

float calcularFitness(float *datosOrigen, float *datosActual, int ncols);

float calcularDistancia(float m1, float m2);

int calcularPeorFitness(float fitness, MejoresDias md[],int tam);

void actualizarMejorDiayPrediccion(MejoresDias nuevoMejorDia, MejoresDias md[], int pos, Dia predicciones[], Dia prediccion);

void copiarVector(float *vOrigen, float *vDest, int ncols);

void calcularPrediccionFinal(Dia predicciones[], Dia *predccionFinal, int k,int ncols);

int main(int argc, char *argv[])
{

    char *nombreFichero = "datos_1X.txt";
    FILE *f;
    int nfils, ncols;
    int i = 0, j = 0;
    
    float datos[24],datosSiguiente[24];

    MejoresDias md[2];
    Dia predicciones[2];

    Dia predccionFinal;
    
    Dia dia;

    Dia diaAPredecir;

    f = fopen(nombreFichero, "r");
    

    obtenerNumeroFilasYColumnas(f, &nfils, &ncols);

    //printf("\n NUMERO COLUMNAS: %d",ncols);
    fflush(stdout);
    parseaLinea(f, datos, ncols);
    parseaLinea(f, datos, ncols);
    parseaLinea(f, diaAPredecir.horas, ncols);
    copiarVector(datos,dia.horas,ncols);     


    for (int i = 0; i < 2; i++)
    {
        //parseaLinea(f, md[i].d.horas, ncols);
        //md[i].fitness = calcularFitness(dia.horas, md[i].d.horas, ncols);
        md[i].fitness = 99999999999999;
    }

    parseaLinea(f, datosSiguiente, ncols);

    for (i = 0; i <= nfils-3; i++)
    {

        copiarVector(datosSiguiente,datos,ncols); //el siguiente de la vez anterior es ahora el actual (datos)
        parseaLinea(f, datosSiguiente, ncols);
        
        float fitnessLocal= calcularFitness(dia.horas,datos,ncols);
        //printf("\n%5.2f \n",fitnessLocal);
        int peorDia=calcularPeorFitness(fitnessLocal,md,2);


        if(peorDia>=0){

            //Construimos el nuevo mejor dia
            MejoresDias mejorDia;
            Dia d;
            copiarVector(datos,d.horas,ncols);
            mejorDia.d=d;
            mejorDia.fitness=fitnessLocal;

            //Construimos la nueva prediccion
            Dia prediccion;
            copiarVector(datosSiguiente,prediccion.horas,ncols);
        
            //Las actualizamos en sus vectores
            actualizarMejorDiayPrediccion(mejorDia,md,peorDia,predicciones,prediccion);
        }

        //printf(" ");
    }
    
    

    for (int i = 0; i < 2; i++)
    {
        printf("\n %5.2f \n", md[i].fitness);
        for (size_t j = 0; j < 24; j++)
        {
            printf(" %5.2f ", predicciones[i].horas[j]);
        }

        printf("\n");
        
    }

    calcularPrediccionFinal(predicciones, &predccionFinal, 2, ncols);
    
    printf("\n El dia a predecir es: \n");
        for (size_t j = 0; j < 24; j++)
        {
            printf(" %5.2f ", diaAPredecir.horas[j]);
        }
        printf("\n");


    printf("\n La prediccion final es: \n");
        for (size_t j = 0; j < 24; j++)
        {
            printf(" %5.2f ", predccionFinal.horas[j]);
        }
        printf("\n");

    fclose(f);

    return 0;
}

//Obtenemos el numero de filas y columnas en los parametros,devuelve 0 si sale bien y -1 si sale mal
int obtenerNumeroFilasYColumnas(FILE *f, int *nfils, int *ncols)
{
    int exito = -1;
    if (f != NULL)
    {
        if (fscanf(f, "%d %d", nfils, ncols) == 1)
        {
            exito = 0;
        }
    }
    return exito;
}

void parseaLinea(FILE *f, float *datos, int ncols)
{
    char *linea;
    size_t len;
    char *saveptr1;
    int read = getline(&linea, &len, f);
    char *token;
    //Separamos por el caracter ',' y vamos guardando en el vector de 24
    token = strtok_r(linea, ",", &saveptr1);
    for (int i = 0; i < ncols; i++)
    {
        if (token == NULL)
            break;
        datos[i] = strtod(token, NULL);

        //printf("%5.1f ", datos[i]);

        token = strtok_r(NULL, ",", &saveptr1);
    }

    //printf(" ");
}

float calcularFitness(float *datosOrigen, float *datosActual, int ncols)
{
    float fitness = 0;
    //printf("%d",ncols);
    for (int i = 0; i < ncols; i++)
    {
        fitness += calcularDistancia(datosOrigen[i], datosActual[i]);
        //printf("\n(%5.2f - %5.2f)^2 = %5.2f      %d\n",datosOrigen[i], datosActual[i],fitness,i);
    }

    return sqrt(fitness);
}

float calcularDistancia(float m1, float m2)
{
    return (pow(m1 - m2, 2));
}

//Devuelve -1 si es peor o(si es mejor) la posicion del peor elemento
int calcularPeorFitness(float fitness, MejoresDias md[],int tam){

    float peorFitness=fitness;
    int pos=-1;
    for (size_t i = 0; i < tam; i++)
    {
        if(md[i].fitness>peorFitness){
            peorFitness=md[i].fitness;
            pos=i;
        }
    }

    return pos;
}

void actualizarMejorDiayPrediccion(MejoresDias nuevoMejorDia, MejoresDias md[], int pos, Dia predicciones[], Dia prediccion){
    md[pos]=nuevoMejorDia;
    predicciones[pos]=prediccion;
}

void copiarVector(float *vOrigen, float *vDest, int ncols){
    for (size_t i = 0; i < ncols; i++)
    {
        vDest[i]=vOrigen[i];
    }
    
}

void calcularPrediccionFinal(Dia predicciones[], Dia *predccionFinal, int k,int ncols){

    float prediccion[24]={0};
    //Recorremos tantas predicciones como haya
    for (size_t i = 0; i < k; i++)
    {
        //Recorremos las horas de cada prediccion
        for (size_t j = 0; j < ncols; j++)
        {
            prediccion[j]+=predicciones[i].horas[j];
        }
        
    }

    //Calculamos la media
    for (size_t i = 0; i < ncols; i++)
    {
        
        prediccion[i]= prediccion[i]/(float)k;

    }

    copiarVector(prediccion,predccionFinal->horas,ncols);
    
    
}
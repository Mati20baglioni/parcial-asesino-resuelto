#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"

///Definicion de constantes
const int fila=12;
const int col=60;

const int filint=5;
const int colint=5;

///Ejercicio 1;
int cargar_string(char s[fila][col]);
///Ejercicio 2
void ins_str(char str[fila][col], int i, char n[]);
void ord_inser(char str[fila][col], int v);
///Ejercicio 3
int eliminar_desaprobados(char s[fila][col], int v, char borrador[fila]);
///Ejercicio 4
void carga_matriz_1st_columnas(int m[colint][filint]);
///Ejercicio 5
void suma_pila_paresEimpares(int m[colint][filint], Pila *p);
void agregar_a_pilas(int j, Pila* p, int sumaPares, int sumaImpares);
///Ejercicio 6
void mostrar_string(char m[fila][col],int v);
void mostrar_matriz(int m[colint][filint]);
void mostrar_pilas(Pila p);



int main()
{
    ///Creacion de variables.
    char srt[fila][col];
    int n=0;
    int val;
    char aux[fila];
    int matriz[filint][colint];
    Pila pilita;
    inicpila(&pilita);

    printf("\nElija un Ejercicio: ");
    scanf("%i", &n);
    ///nota: pueden hacer un do while para cargar una sola vez y despues probar las funciones en los case correspondientes
    /// en lo personal prefiero hacerlo asi (en serio es meramente personal, no esta ni bien ni mal que hagan un bucle o no).
    switch(n)
    {
    case 1:
        val=cargar_string(srt);
        mostrar_string(srt,val);
        break;

    case 2:
        val=cargar_string(srt);
        mostrar_string(srt,val);
        ord_inser(srt,val);
        printf("\n\ndespues\n\n");
        mostrar_string(srt,val);
        break;

    case 3:
        val=cargar_string(srt);
        mostrar_string(srt,val);
        printf("\nIngrese el nombre del desaprobado: ");
        fflush(stdin);
        gets(aux);
        val=eliminar_desaprobados(srt,val, aux);
        printf("\n\ndespues\n\n");
        mostrar_string(srt,val);
        break;

    case 4:
        carga_matriz_1st_columnas(matriz);
        mostrar_matriz(matriz);
        break;

    case 5:
        carga_matriz_1st_columnas(matriz);
        suma_pila_paresEimpares(matriz, &pilita);
        mostrar_matriz(matriz);
        mostrar_pilas(pilita);
        mostrar(&pilita);
        break;

    case 6:
        val=cargar_string(srt);
        mostrar_string(srt,val);
        carga_matriz_1st_columnas(matriz);
        suma_pila_paresEimpares(matriz, &pilita);
        mostrar_matriz(matriz);
        mostrar_pilas(pilita);
        break;

    default:
        printf("https://www.youtube.com/watch?v=dQw4w9WgXcQ&ab");
        break;
    }



    return 0;
}

///Ejercicio 1
int cargar_string(char s[fila][col])
{
    char yes = 's';
    int i=0;
    ///Creo el numero de control para saber donde poner el guion
    int numControl=3;

    while(yes=='s' && i<fila)
    {
        printf("\nIngrese: ");
        fflush(stdin);
        gets(s[i]);///las 2 unicas diferencias que hay netre el scanf de strings y el gets es que en este ultimo no tenes que poner el "&"
        /// y lo mas importante, podes poner espacios!

        i++;

        if(i==numControl)
        {
            strcpy(s[i],"------");///Strcpy para agregar el guion.
            i++;/// avanzo una vez mas para no pisar los guiones en la siguiente vuelta.
            numControl+=4; ///es +=4 por que yo se que la proxima vez que tenga que poner un guion es despues de 3 nombre validos.
        }

        printf("\ncontinue? ");
        fflush(stdin);
        scanf("%c", &yes);
    }
    return i;
}

///Ejercicio 2
void ins_str(char str[fila][col], int i, char n[])
{
    char aux[fila];///Recuerden, EN STINGS, debe usarse un char auxiliar, porque sino se rompe, tema de las dicc. de memoria.
    strcpy(aux,n);

    while(i>=0 && (strcmp(aux,str[i])>0)) ///Si se fijan la funcion es exactamente igual al insertar normal, lo que cambia es ese ">".
    {
        strcpy(str[i+1],str[i]);
        i--;
    }
    strcpy(str[i+1],aux);

}

void ord_inser(char str[fila][col], int v)
{
    int i=0;

    while(i<v-1)
    {
        ins_str(str,i,str[i+1]);
        i++;
    }
}

///Ejercicio 3
int eliminar_desaprobados(char s[fila][col], int v, char borrador[fila])
{
    int i=0;
    int j=0;

    while(i<v)
    {
        if(strcmpi(s[i],borrador)==0) ///aca encuentra el nombre
        {
            while(j<v) ///Al encotnrarlo lo que hace es copiar c/u de los nombres una posicion hacia atras.
            {
                strcpy(s[j],s[j+1]);
                j++;
            }
            v--;///Al eliminar un nombre, significa que tus validos son uno menos
        }
        i++;///avanzo en el arreglo
        j=i;///pongo j=i para fijarme si hay otro nombre repetido pero me aseguro de no tocar lo que ya verifique.
    }
    return v;
}

///Ejercicio 4
void carga_matriz_1st_columnas(int m[colint][filint])
{
    int i=0;
    int j=0;
///Aca esta el truco, doy vuelta los fors asi cargo primero columnas.
    for(j=0; j<filint; j++)
    {
        printf("\n\nFila %i", j);
        for(i=0; i<colint; i++)
        {
            printf("\nIngrese un numero a la matriz ");
            scanf("%i", &m[i][j]);
        }
    }
}


///Ejercicio 5
void suma_pila_paresEimpares(int m[colint][filint], Pila *p)
{
    int j=0;
    int i=0;
    ///Guardaran la suma para apilar
    int sumaPares=0;
    int sumaImpares=0;

    for(j=0; j<filint; j++)
    {
        agregar_a_pilas(j,p,sumaPares,sumaImpares); ///Modularice para no repetir codigo.
        sumaPares=0;///devuelvo a cero a ambos para que hagan la suma de la siguiente columna.
        sumaImpares=0;
        for(i=0; i<colint; i++)
        {
            if(m[i][j]%2==0)
            {
                sumaPares+=m[i][j];///Si el resto es cero, es decir, si es par sumo aca.
            }
            else
            {
                sumaImpares+=m[i][j];///Sino lo sumo aca.
            }
        }

    }
    agregar_a_pilas(j,p,sumaPares,sumaImpares); ///Llamo devuelta aca porque, al hacerlo adelante del for, las ultimas sumaPares y
                                                ///sumaImpares no se agregarian.
}

void agregar_a_pilas(int j, Pila* p, int sumaPares, int sumaImpares)
{
    ///Se fija que j no sea cero, esto para no hacerlo la primera vuelta porque ingresaria basura,
    ///y despues se fija que la suma de los pares no sea cero, porque sino estarias agregando  un numero que no existe en la matriz.
    if(j!=0 && sumaPares!=0)
    {
        apilar(p,sumaPares);///Aca lo apilo.
    }
    if(j!=0 && sumaImpares!=0) ///Lo mismo pero al reves.
    {
        apilar(p,sumaImpares);
    }
}

///hay otra forma de hacerlo y es poner lo que esta en la funcion "agregar_a_pilas" despues del que se cierre el 2do for (linea 228)
///en la otra funcion y sacando el "j!=0" pero ahi perderia el sentido la modularizacion y queria darles un ejemplo de esta.
/// Tambien debo boorrar la linea 214 y 230 para.

///Ejercicio 6
void mostrar_string(char m[fila][col],int v)
{
    int i=0;

    for(i=0; i<v; i++)
    {
        printf("\n|%s|", m[i]);

    }
}

void mostrar_matriz(int m[colint][filint])
{
    int i=0;
    int j=0;
    ///IMPORTANTE --> Muestro normal.
    for(i=0; i<colint; i++)
    {
        printf("\n");
        for(j=0; j<filint; j++)
        {
            printf("[%i]", m[i][j]);
        }
    }
}

void mostrar_pilas(Pila p)
{
    ///Importante, esta funcion dedstroza la pila original por lo que hay que pasarla por copia!!!!
    printf("\n  TOPE");
    while(!pilavacia(&p))
    {
        printf("\n->{%i}<- ", desapilar(&p));
    }
    printf("\n  BASE");
}

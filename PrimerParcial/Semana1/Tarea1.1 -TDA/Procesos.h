/***********************************************************************
 * Module:  Procesos.h
 * Author:  ASUS
 * Modified: jueves, 9 de mayo de 2024 21:16:12
 * Purpose: Declaration of the class Procesos
 ***********************************************************************/

#if !defined(__Tarea2_Procesos_h)
#define __Tarea2_Procesos_h

#include "C:\Users\ASUS\Documents\C++ Ejercicios\Tarea1.1\Potencia.h"

class Procesos
{
public:
   virtual int calcular1(int base, int exponente)=0;
   virtual float calcular2(float base, int exponente)=0;
   virtual Potencia calcular3(float base, int exponente)=0;
   virtual void imprimir(float respuesta)=0;


protected:
private:

};

#endif
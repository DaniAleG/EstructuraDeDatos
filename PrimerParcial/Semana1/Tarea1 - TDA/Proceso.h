/***********************************************************************
 * Module:  Proceso.h
 * Author:  ASUS
 * Modified: jueves, 9 de mayo de 2024 15:53:57
 * Purpose: Declaration of the class Proceso
 ***********************************************************************/

#if !defined(__Deber2_Proceso_h)
#define __Deber2_Proceso_h

#include "C:\Users\ASUS\Documents\C++ Ejercicios\Tarea1 - TDA\Racional.h"

class Proceso
{
public:
   virtual int calcular1(int num, int den)=0;
   virtual Racional calcular2(int num, int den)=0;
   virtual float calcular3(int num, int den)=0;
   virtual float calcular4(float num, float den)=0;
   virtual void imprimir(float suma)=0;

protected:
private:

};

#endif
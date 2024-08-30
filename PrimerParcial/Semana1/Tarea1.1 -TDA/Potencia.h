/***********************************************************************
 * Module:  Potencia.h
 * Author:  ASUS
 * Modified: jueves, 9 de mayo de 2024 21:16:12
 * Purpose: Declaration of the class Potencia
 ***********************************************************************/

#if !defined(__Tarea2_Potencia_h)
#define __Tarea2_Potencia_h

class Potencia
{
public:
   float toFloat() const;
   int toInt() const;
   Potencia(float v);
   int getExponente(void);
   void setExponente(int newExponente);
   float getBase(void);
   void setBase(float newBase);
   Potencia(int base, int exponente);
   Potencia(float base, int exponente);
   ~Potencia();
   Potencia();

protected:
private:
   float base;
   int exponente;


};

#endif
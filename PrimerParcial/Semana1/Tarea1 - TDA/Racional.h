/***********************************************************************
 * Module:  Racional.h
 * Author:  ASUS
 * Modified: jueves, 9 de mayo de 2024 16:07:01
 * Purpose: Declaration of the class Racional
 ***********************************************************************/

#if !defined(__Deber2_Racional_h)
#define __Deber2_Racional_h

class Racional
{
public:
   float toFloat() const;
   int toInt()const;
   Racional(int num);
   int getDenominador(void);
   void setDenominador(int newDenominador);
   Racional(int numerador, int denominador);
   ~Racional();
   Racional();
   int getNumerador(void);
   void setNumerador(int newNumerador);

protected:
private:
   int numerador;
   int denominador;


};

#endif
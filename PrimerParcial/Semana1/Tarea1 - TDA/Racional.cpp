/***********************************************************************
 * Module:  Racional.cpp
 * Author:  ASUS
 * Modified: jueves, 9 de mayo de 2024 16:07:01
 * Purpose: Implementation of the class Racional
 ***********************************************************************/

#include "Racional.h"


//Funcion para transformar de Racional a Flotante
float Racional::toFloat() const {
   return static_cast<float>(numerador) / static_cast<float>(denominador);
}
//Funcion para transformar de Racional a Entero
int Racional::toInt() const {
   float valorDecimal = static_cast<float>(numerador) / static_cast<float>(denominador);
   return static_cast<int>(valorDecimal);
}
//Funcion para transformar de Entero a Racional
Racional::Racional(int num) : numerador(num), denominador(1) {}
////////////////////////////////////////////////////////////////////////
// Name:       Racional::getDenominador()
// Purpose:    Implementation of Racional::getDenominador()
// Return:     int
////////////////////////////////////////////////////////////////////////
int Racional::getDenominador(void)
{
   return denominador;
}

////////////////////////////////////////////////////////////////////////
// Name:       Racional::setDenominador(int newDenominador)
// Purpose:    Implementation of Racional::setDenominador()
// Parameters:
// - newDenominador
// Return:     void
////////////////////////////////////////////////////////////////////////

void Racional::setDenominador(int newDenominador)
{
   denominador = newDenominador;
}

////////////////////////////////////////////////////////////////////////
// Name:       Racional::Racional(int numerador, int denominador)
// Purpose:    Implementation of Racional::Racional()
// Parameters:
// - numerador
// - denominador
// Return:     
////////////////////////////////////////////////////////////////////////

Racional::Racional(int numerador, int denominador)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       Racional::~Racional()
// Purpose:    Implementation of Racional::~Racional()
// Return:     
////////////////////////////////////////////////////////////////////////

Racional::~Racional()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       Racional::Racional()
// Purpose:    Implementation of Racional::Racional()
// Return:     
////////////////////////////////////////////////////////////////////////

Racional::Racional()
{
}

////////////////////////////////////////////////////////////////////////
// Name:       Racional::getNumerador()
// Purpose:    Implementation of Racional::getNumerador()
// Return:     int
////////////////////////////////////////////////////////////////////////

int Racional::getNumerador(void)
{
   return numerador;
}

////////////////////////////////////////////////////////////////////////
// Name:       Racional::setNumerador(int newNumerador)
// Purpose:    Implementation of Racional::setNumerador()
// Parameters:
// - newNumerador
// Return:     void
////////////////////////////////////////////////////////////////////////

void Racional::setNumerador(int newNumerador)
{
   numerador = newNumerador;
}

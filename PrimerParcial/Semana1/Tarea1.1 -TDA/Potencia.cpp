/***********************************************************************
 * Module:  Potencia.cpp
 * Author:  ASUS
 * Modified: jueves, 9 de mayo de 2024 21:16:12
 * Purpose: Implementation of the class Potencia
 ***********************************************************************/

#include "Potencia.h"
//Transformar Potencia a float
float Potencia::toFloat() const {
   return static_cast<float>(base) ;
}
//Transformar Potencia a int
int Potencia::toInt() const {
   int exponente = static_cast<int>(exponente);
   return exponente;
}
//Transformar float a Potencia
Potencia::Potencia(float base) : base(base) {}
////////////////////////////////////////////////////////////////////////
// Name:       Potencia::getExponente()
// Purpose:    Implementation of Potencia::getExponente()
// Return:     int
////////////////////////////////////////////////////////////////////////

int Potencia::getExponente(void)
{
   return exponente;
}

////////////////////////////////////////////////////////////////////////
// Name:       Potencia::setExponente(int newExponente)
// Purpose:    Implementation of Potencia::setExponente()
// Parameters:
// - newExponente
// Return:     void
////////////////////////////////////////////////////////////////////////

void Potencia::setExponente(int newExponente)
{
   exponente = newExponente;
}

////////////////////////////////////////////////////////////////////////
// Name:       Potencia::getBase()
// Purpose:    Implementation of Potencia::getBase()
// Return:     float
////////////////////////////////////////////////////////////////////////

float Potencia::getBase(void)
{
   return base;
}

////////////////////////////////////////////////////////////////////////
// Name:       Potencia::setBase(float newBase)
// Purpose:    Implementation of Potencia::setBase()
// Parameters:
// - newBase
// Return:     void
////////////////////////////////////////////////////////////////////////

void Potencia::setBase(float newBase)
{
   base = newBase;
}

////////////////////////////////////////////////////////////////////////
// Name:       Potencia::Potencia(int base, int exponente)
// Purpose:    Implementation of Potencia::Potencia()
// Parameters:
// - base
// - exponente
// Return:     
////////////////////////////////////////////////////////////////////////

Potencia::Potencia(int base, int exponente)
{
   // TODO : implement
}
Potencia::Potencia(float base, int exponente)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       Potencia::~Potencia()
// Purpose:    Implementation of Potencia::~Potencia()
// Return:     
////////////////////////////////////////////////////////////////////////

Potencia::~Potencia()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       Potencia::Potencia()
// Purpose:    Implementation of Potencia::Potencia()
// Return:     
////////////////////////////////////////////////////////////////////////

Potencia::Potencia()
{
}

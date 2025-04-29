#include <iostream>
#include "tabbporo.h"
using namespace std;

int
main(void)
{
/*******************************************************************/
/********** ASIGNACION , "<<" ; posible problema de CONST 	   */
/*******************************************************************/
  
  TABBPoro a,b,c;

  TPoro p1(1,2,1,(char *) "rojo");

  b.Insertar(p1);


  cout << b.Inorden() << endl;


  return 1;
}

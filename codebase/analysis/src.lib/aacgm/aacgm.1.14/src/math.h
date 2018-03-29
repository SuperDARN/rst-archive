/* math.h
   ======
   Author: R.J.Barnes
*/


/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/




#ifndef PI
#define PI 3.14159265358979323846
#endif

#define cosd(a) cos(PI*(a)/180)
#define sind(a) sin(PI*(a)/180)
 
#define scosd(a) (acos(a)*180/PI)
#define asind(a) (asin(a)*180/PI)

double sgn(double,double);
double mod(double,double);

#include "MK_Math.h"

double MK_Sin(int Angle)
{
    double Rad=(double)(Angle*(PI/180));
    return sin(Rad);
}
double MK_Cos(int Angle)
{
    double Rad=(double)(Angle*(PI/180));
    return cos(Rad);
}

#pragma once
#include <cmath>

const float PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899348253421170679f;

int HSIToRGB(double H, double S, double I)
{
    const double RtD = 57.29577951f, DtR =0.017453293f; //라디안 디그리 변환 상수 
    
    double R, G, B;
      
     if(H*RtD > 0 && H*RtD<=120)
    {
         R = (1+((S*cos(H))/cos((60*DtR) - H)))*0.333333; 
         B = (1 - S) * 0.333333;
         G = 1 - (R + B); 
    }
    else if(H*RtD > 120 && H*RtD<=240)
    {
         H = (H*RtD - 120)*DtR;
         
         G = (1+((S*cos(H))/cos((60*DtR) - H)))*0.333333; 
         R = (1 - S) * 0.333333;
         B = 1 - (R + G); 
         
    }
    else
    {
         H = (H*RtD - 240)*DtR;
         
         B = (1+((S*cos(H))/cos((60*DtR) - H)))*0.333333; 
         G = (1 - S) * 0.333333;
         R = 1 - (B + G);          
    }    
  
    int RR = (int)(255 * R*I);
    int GG = (int)(255 * G*I);
    int BB = (int)(255 * B*I);
	
	if( RR > 255 ) RR = 255;
	if( GG > 255 ) GG = 255;
	if( BB > 255 ) BB = 255;

    return RGB( RR, GG, BB );
}

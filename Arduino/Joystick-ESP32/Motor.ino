//  M1 = motot kanan depan
//  M2 = motot kanan belakang
//  M3 = motot kiri belakang
//  M4 = motot kiri depan
int derM1 = 45, derM2 = 315, derM3 = 225, derM4 = 135;

float vM1,vM2,vM3,vM4;
void robotMove(int X, int Y, int W, int G, int maxx){   
  float  v1, v2, v3, v4, tV1, tV2, tV3, tV4;

  vM1 = -(sin(radians(derM1)) * X) + (cos(radians(derM1)) * Y) + (W + G);
  vM2 = -(sin(radians(derM2)) * X) + (cos(radians(derM2)) * Y) + (W + G);
  vM3 = -(sin(radians(derM3)) * X) + (cos(radians(derM3)) * Y) + (W + G);
  vM4 = -(sin(radians(derM4)) * X) + (cos(radians(derM4)) * Y) + (W + G);
   
  v1 = abs(vM1);
  v2 = abs(vM2);
  v3 = abs(vM3);
  v4 = abs(vM4);

  if(vM1>0){tV1=1;} else{tV1=-1;}
  if(vM2>0){tV2=1;} else{tV2=-1;}
  if(vM3>0){tV3=1;} else{tV3=-1;}
  if(vM4>0){tV4=1;} else{tV4=-1;}

  if(v1>v2 && v1>v3 && v1>v4 && v1>maxx){ 
    vM1 = tV1*maxx;
    vM2 = tV2*maxx*(v2/v1);
    vM3 = tV3*maxx*(v3/v1);
    vM4 = tV4*maxx*(v4/v1);
  }

  if(v2>v1 && v2>v3 && v2>v4 && v2>maxx){  
    vM1 = tV1*maxx*(v1/v2);
    vM2 = tV2*maxx;
    vM3 = tV3*maxx*(v3/v2);
    vM4 = tV4*maxx*(v4/v2);
  }

  if(v3>v1 && v3>v2 && v3>v4 && v3>maxx){  
    vM1 = tV1*maxx*(v1/v3);
    vM2 = tV2*maxx*(v2/v3);
    vM3 = tV3*maxx;
    vM4 = tV4*maxx*(v4/v3);
  }

  if(v4>v1 && v4>v2 && v4>v3 && v4>maxx){  
    vM1 = tV1*maxx*(v1/v4);
    vM2 = tV2*maxx*(v2/v4);
    vM3 = tV3*maxx*(v3/v4);
    vM4 = tV4*maxx;
  }

  pRF = vM1;
  pRR = vM2;
  pLR = vM3;
  pLF = vM4;

  
}
 

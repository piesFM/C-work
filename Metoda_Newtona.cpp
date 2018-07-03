#include <iostream>
#include <cstdio>

typedef void (*FuncPointer)(const double* x, double* y, double* Df);

void printVector(const double* x, unsigned N){
  for(unsigned i=0;i<N;++i)
    printf("%17.17f ",x[i]);
  printf("\n");
}
int findCurve(FuncPointer f, double* x, unsigned k, double h) {
  double prevC1 = 999;
  double prevC2 = 999;
  double* xx = new double[3];
  for (int j = 0; j < 3); j++) xx[j] = x[j];
  xx[2] += h;
  double* Df;
  double* y = new double[k];
  double* tab = new double[k];
  Df = new double[k * 3];
  for (int i = 1; i <= k; ) {
    implicitCurve(xx, y, Df);
    if (std::abs(y[0]) <= 1e-14 || std::abs(y[1]) <= 1e-14) {
      printVector(xx, 3);
      for (int j = 0; j < 3; j++) xx[j] = x[j];
      xx[2] += h * ++i;
      prevC1 = 999;
      prevC2 = 999;
    } else if (y[0] > prevC1 || y[1] > prevC2) {
      delete[] xx;
      delete[] y;
      delete[] Df;
      return i;
    }
    else {
      prevC1 = y[0];
      prevC2 = y[1];
    }
  }
  delete[] xx;
  delete[] y;
  delete[] Df;
  return 0;
}

void implicitCurve(const double* x, double* y, double* Df){
    // funkcja dana jest wzorem f(a,b,c) = (1-a^2-b^2-c^2,(a+b+c)/(a^2+b^2+c^2)-1)
    // zmienne pomocnicze
    const double n = x[0]*x[0] + x[1]*x[1] + x[2]*x[2];
    const double s = x[0] + x[1] + x[2];
    // obliczam wartosc funkcji
    y[0] = 1. - n;
    y[1] = s/n - 1.;
    //obliczam pierwszy wiersz macierzy
    Df[0] = -2.*x[0];
    Df[1] = -2.*x[1];
    Df[2] = -2.*x[2];
    //obliczam drugi wiersz macierzy
    const double r = 1./n;
    const double r2 = 2.*y[1]*r;
    Df[3] = r - x[0]*r2;
    Df[4] = r - x[1]*r2;
    Df[5] = r - x[2]*r2;
  }
  
  int main(){
    double x[3] = {0.25*(1.+sqrt(5.)),0.25*(1.-sqrt(5.)),0.5};
    findCurve(implicitCurve,x,10,1./128);
    printf("\n");
    double x2[3] = {0.25*(1.-sqrt(5.)),0.25*(1.+sqrt(5.)),0.5};
    int i = findCurve(implicitCurve,x2,10,3./32);
    printf("%d",i);
    return 0;
  }

/**
spodziewane wyjscie:
0.80332000443603468 -0.31113250443603474 0.50781250000000000 
0.79753481882962218 -0.31315981882962213 0.51562500000000000 
0.79166053918176227 -0.31509803918176227 0.52343750000000000 
0.78569621138679224 -0.31694621138679219 0.53125000000000000 
0.77964082305207405 -0.31870332305207399 0.53906250000000000 
0.77349330072459810 -0.32036830072459804 0.54687500000000000 
0.76725250688009694 -0.32194000688009689 0.55468750000000000 
0.76091723665304600 -0.32341723665304600 0.56250000000000000 
0.75448621428335538 -0.32479871428335538 0.57031250000000000 
0.74795808925263751 -0.32608308925263751 0.57812500000000000 

-0.32835472974046714 0.73460472974046720 0.59375000000000000 
-0.33288987007807902 0.64538987007807902 0.68750000000000000 
-0.31824788073137528 0.53699788073137522 0.78125000000000000 
-0.27407280044590648 0.39907280044590648 0.87500000000000000 
-0.15906781074217108 0.19031781074217108 0.96875000000000000 
6 
*/
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main(){
   
  //Declaración de las constantes  
  double L=1.0;
  double dx = 0.01;
  double tmax = 0.1;
  double t=0.0;
  double rho = 0.01;
  double T = 40.0;
  double c=sqrt(T/rho);
  double dt = dx/c; //Relacion de convergencia 
  double cp=dx/dt;
  int Nx = L/(dx); //Longitud dividida en su cantidad de pasos
    
  //Tres matrices de la función para cada tiempo  
  double Yanterior[Nx];
  double Yactual[Nx];
  double Yfutura[Nx];
  double pi = asin(1.0)*2.0;


  //Inicialización para un tiempo cero de las tres matrices
  double x = 0.0;    
  for(int i=0;i<Nx;i++)
  {
    x = i * dx;
    Yanterior[i] = 0.0001*sin(2*pi * x/L); //Funcion en t = 0
    Yactual[i] = Yanterior[i];
    Yfutura[i] = Yanterior[i];
  }
    
  //Abrir archivo para guardar los datos
  ofstream outfile;  
  outfile.open("wave.dat");
    
  //FTCS para la actual  
  for(int i=1;i<Nx-1;i++)
  {
    Yactual[i] = Yanterior[i] + 0.5*pow(c/cp,2.0) * (Yanterior[i+1] + Yanterior[i-1] -2.0*Yanterior[i]);
  }
  t = t+dt; //Primer tiempo actualización

  while(t < tmax)
  {
    for(int i=0;i<Nx;i++){
      outfile << Yactual[i] << "\t";
    }
    outfile << "\n";
    
    //Actualiza la futura con FTCS
    for(int i=1;i<Nx-1;i++)
    {
     Yfutura[i] = 2.0*Yactual[i] - Yanterior[i];
      Yfutura[i] += pow(c/cp, 2.0) * (Yactual[i+1] +Yactual[i-1] -2.0 * Yactual[i]);
    }
    
    //Actualizacion de las tres matrices
    for(int i=1;i<Nx-1;i++)
    {
      Yanterior[i] = Yactual[i];
     Yactual[i] = Yfutura[i];
    }
    t = t + dt; //Actualización de cada tiempo
  }
  outfile.close();

  return 0;
}
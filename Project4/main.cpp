#include <iostream>
#include <armadillo>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include </uio/hume/student-u32/andehus/fys3150/compphys/programs/cppLibrary/lib.cpp>
#define pi atan(1.0)*4
using namespace std;

class Solver {
    int n,tsteps;
    double dx,dt,h,alpha;
    double *g,*v,*vnew;

public:
    Solver(int n, double dx, double dt) {
        n = this->n; //n = antall punkter
        dx = this->dx;
        dt = this->dt;
        alpha = dt/(dx*dx);
        v = new double[n];
        vnew = new double[n];
        forward_euler();
    }
    /*
    int init_g() {
        g = new double[n];
        for(int i = 0; i<n; i++){
            g[i] = -2/(n*pi)*sin(n*pi*i*dx)
        }
        return 0;
    }
 */
    int forward_euler(){
        double x;
        v[0] = vnew[0] = v[n] = vnew[n] = 0.0; //Grensebetingelser
        for(int i = 1; i<n; i++) {
            x = i*dx;
            v[i] = x-1;
        }
        for(int j = 1; j<n; j++) {
            for(int i = 1; i<n; i++) {
                vnew[i] = alpha * v[i-1]+(1-2*alpha)*v[i] + alpha *v[i+1];
            }
        }
        return 0;
    }

    int backward_euler() {
        double a, b, c, x;
        double *u = new double[n];
        double *y = new double[n];

        for(int i = 0; i<n; i++) {
            x = i*dx;
            y[i] = u[i] = x-1;
        }
        y[0] = u[0] = y[n] = u[n] = 0.0; //Grensebetingelser
        a = c = -alpha;
        b = 1+2*alpha;

        for(int t = 1; t<= tsteps; t++) {
            tridag(a,b,c,y,u,n);
            u[0] = 0;
            u[n] = 0;
            for(int i = 0; i<= n; i++) {
                y[i] = u[i];
            }
           //Print ut
        }

        return 0;
    }

    int cranknicolson() {
        double a, b, c;
        double *u2 = new double[n];
        double *r = new double[n];
        a = c = -alpha;
        b = 2+2*alpha;

        for(int i = 1; t<= tsteps; t ++){
            for(int i = 1; i<n; i++){
                r[i] = alpha*u2[i-1]+(2-2*alpha)*u2[i] + alpha*u2[i+1];
            }
            r[0] = 0;
            r[n] = 0;
            tridag(a,b,c,r,u,n);
            u[0] = 0;
            u[n] = 0;
        return 0;
    }

    int atf(double *temp, int n) {
        if(!file.is_open())
            file.open("/uio/hume/student-u32/andehus/Project3/data.dat",ios::trunc);
        for(int i = 0; i<n; i++){
            cout<<temp[i]<<endl;
        }
        return 0;
    }
};

int main()
{
    //Solver(int n, double dx, double dt, h);
    new Solver(11,1.0/10.0,5.0*pow(10,-3));
    return 0;
}


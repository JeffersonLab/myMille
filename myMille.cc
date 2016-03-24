// Millepede test case for a single event.
//
// to build g++ -o myMille myMille.cc Mille.cc
//
// uses a single event which is probably a bad idea.

#include <fstream>
#include <iostream>
#include <cmath>
#include "Mille.h"

using namespace std;


int main()
{

  // defaults: bool b1=true, b2=false;
  bool b1=true, b2=false;
  Mille myMille( "outfile.bin",b1,b2); // pass in initial values when variable is created

  //int ngl = 8, nlc = 2;
  float xi[]={60,63,90,93,120,123,150,153};
  float zi[]={0.437844,-0.0388995,0.32188,-0.597111,0.361745,-0.841198,-2.79063,3.14637};
  float sigmai[]={1.42496,1.45816,1.6433,1.65298,1.65298,1.6433,1.45816,1.42496};
  float dergl[1],derlc[2],sigma;
  int   labeli[]={11,12,13,14,15,16,17,18};
  int   label[1];

  // get the number of hits in the event
  int nhits=sizeof(xi)/sizeof(xi[0]);
  cout << "nhits in event = " << nhits << endl;
  int  nlc=2, ngl=1;

  // loop over the hits in the event
  int icount=0;
  for (icount=0; icount<nhits; icount++) {

    // local derivatives
    derlc[0]=1.0;
    derlc[1]=xi[icount];
    
    // global derivatives
    dergl[0]=1.0;

    // the residual
    float rmeas = zi[icount];

    // label of the measurement.
    label[0]=labeli[icount];

    // error on the measurement.
    sigma = sigmai[icount];

    // write out the data in binary form for millepede.
    myMille.mille(nlc, derlc, ngl, dergl, label, rmeas, sigma);
    //myMille.mille(nlc, &derlc[0], ngl, &dergl[0], &label, rmeas, sigma);

  } // end of loop over hits

  // write out the stuff.
  myMille.end();
  myMille.~Mille();

  return 0;

} // end of main.



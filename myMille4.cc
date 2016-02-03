// Millepede test case for a single event.
//
// to build g++ -o myMille myMille.cc Mille.cc
//
// uses 2D event.

#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include "Mille.h"

using namespace std;


int main()
{

  // defaults: bool b1=true, b2=false;
  bool b1=true, b2=false;
  Mille myMille("outfile3.bin",b1,b2); // pass in initial values when variable is created

  // read data from a file consisting of 24 numbers for each event/row into and array 
  // that is row(nevents), measurement(nmeas), data(index, xi, zi) with spaces between.
  int nevents = 500, irow=0, ncol=24, ndim=3, nmeas=8, idim, imeas;
  float data[nevents][nmeas][ndim];
  ifstream inputFile("manyMoreEventsTest.dat");

  // loop over the nevents events in the file.
  for(irow=0; irow < nevents; irow++) {

    // loop over the 8 measurements in each event.
    for (int imeas = 0; imeas < nmeas; ++imeas) {
      // loop over components of each measurement (index, x_i, z_i)
      // and store the results in a 3D array data.
      for (int idim = 0; idim < ndim; ++idim) {
	inputFile >> data[irow][imeas][idim];
      }
    } // end of loop over measurements in the row/event.
  } // end of loop over rows/event/track.

  // check the input.
  //  for (irow=0; irow < nevents; irow++) {
  //    for (imeas = 0; imeas < nmeas; ++imeas) {
  //      for (idim = 0; idim < ndim; ++idim) {
  //  	cout << data[irow][imeas][idim] << " ";
  //      }
  //    }
  //    cout << endl;
  //  }

  // now loop over the nevents events and write to the output file.
  // start labels at 11 for convenience.
  int label[8]={11,12,13,14,15,16,17,18};
  float xi[8], zi[8];
  float sigmai[8]={0.99,0.99,0.99,0.99,0.99,0.99,0.99,0.99};
  float rmeas, sigma;

  // get the number of hits in the event
  int nhits=sizeof(xi)/sizeof(xi[0]);
  //cout << "nhits in event = " << nhits << endl;

  // loop over the events.
  for (irow=0; irow < nevents; irow++) {
    // fill the arrays used to write to the binary file for this event.
    for (imeas = 0; imeas < nmeas; imeas++) {
      xi[imeas] = data[irow][imeas][1];
      zi[imeas] = data[irow][imeas][2];
    }

    // check stuff.
    int icount=0;
    //for (icount=0; icount<nmeas; icount++) cout << xi[icount] << " ";
    //cout << endl;
    //for (icount=0; icount<nmeas; icount++) cout << zi[icount] << " ";
    //cout << endl << endl;

    // loop over the hits/measurements in the event
    for (icount=0; icount<nmeas; icount++) {

      int nlc=2;
      int ngl=8;
      float dergl[8] = {};
      float derlc[2] = {};

      // local derivatives
      derlc[0]=1.0;
      derlc[1]=xi[icount];
    
      // global derivatives
      dergl[icount]=1.0;

      // the residual
      rmeas = zi[icount];

      // label of the measurement.
      //label[0]=labeli[icount];

      // error on the measurement.
      sigma = sigmai[icount];

      // write out the data in binary form for millepede.
      myMille.mille(nlc, derlc, ngl, dergl, label, rmeas, sigma);

    } // end of loop over hits
    myMille.end();  // end of the event.
    //myMille.kill();
  } // end of loop over events.

  // write out the stuff.
  myMille.~Mille();

  return 0;

} // end of main.



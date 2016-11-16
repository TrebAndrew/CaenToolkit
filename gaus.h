//  Usage:
//    $ root gaus.C
//    $ root 'gaus.C(string, double, double)'
//    $ root 'gaus.C("path/to/file.dat", 950, 1100)'
//andtre/Type S10362-11-100c Ser.n.2568/mppcS10362-11-100C-n2568 70.5 V _013_eh_0.dat
#include "TF1.h"
#include "TH1I.h"
#include "TCanvas.h"
#include <iostream>
#include <iostream>
#include <fstream>
using namespace std;

//  Input parameters:
//    fname --- the input file name, where histogram data originaly stored.
//    left --- the left boundary of fitting.
//    right --- the right boundary of fitting.
void gaus(
        string fname = "C:/File/1.dat",     
        int PixNum,
        double left,
        double right){
    int SNum;
    double Volt;
    double Temp;
    //  Create a canvas c1, i.e. a window where we will draw all our stuff.
    TCanvas * c1 = new TCanvas("c1", "c1", 900, 800);
    //  Open the input file with name fname.
    std::ifstream infile(fname.c_str());
    int a, b;
    infile >> SNum >> Volt >> Temp;
    //  Create a histogram to fill it with data from the file.
    TH1I * h = new TH1I("h", "h", 6000, 0, 6000);
    while( infile >> a >> b ){
        h->SetBinContent(a, b);
    }
    h->SetBinContent(6000, 0);//  The last bin is bad, empty it.
    h->Draw();//  Justr drawing the histogram in the canvas.
    TF1 * f1 = new TF1("f1", "gaus", 700, 1100);//  Create a Gaussian function for fitting.
    f1->SetParameters( h->GetEntries()/20, (left+right)/2., (right-left)/4 );
    // h.Fit("gaus", "", "same", 700, 1100);
    //  Fit the histogram by the normal distribution in the range (left, right).
    //  The fit result is output in the terminal session.
      h->Fit(f1, "", "same", left, right);
    f1->Draw("same");

    ofstream myfile ("C:/File/output.txt", std::ios::app);
      if (myfile.is_open())
      {
        myfile <<                  
            endl                <<
            SNum                <<
            "\t"                <<
            PixNum              <<
            "\t"                <<
            Volt                <<
            "\t "               <<
            Temp                <<
            "\t"                <<
            setprecision(6)<<f1->GetParameter(1) <<
            "\t"                <<
            setprecision(5)<<f1->GetParError(1)  <<
            "\t"                <<
            setprecision(6)<<f1->GetParameter(2) <<
            "\t"                <<
            setprecision(5)<<f1->GetParError(2)  <<
            "\t";

        myfile.close();
      }
      else cout << "Unable to open file";
      return 0;

    c1->Update();//  Update our canvas to draw new objects.

}

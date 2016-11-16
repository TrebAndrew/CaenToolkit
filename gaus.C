//  Usage:
//    $ root gaus.C
//    $ root 'gaus.C(string, double, double)'
//    $ root 'gaus.C("path/to/file.dat", 950, 1100)'

#include "TF1.h"
#include "TH1I.h"
#include "TCanvas.h"
#include <iostream>

//  Input parameters:
//    fname --- the input file name, where histogram data originaly stored.
//    left --- the left boundary of fitting.
//    right --- the right boundary of fitting.
void gaus(
        string fname = "andtre/Type S10362-11-100c Ser.n.2568/mppcS10362-11-100C-n2568 70.5 V _013_eh_0.dat",
        double left = 950,
        double right = 1100){
    //  Create a canvas c1, i.e. a window where we will draw all our stuff.
    TCanvas * c1 = new TCanvas("c1", "c1", 800, 600);
    //  Open the input file with name fname.
    std::ifstream infile(fname.c_str());
    int a, b;
    //  Create a histogram to fill it with data from the file.
    TH1I * h = new TH1I("h", "h", 32768, 0, 32768);
    while( infile >> a >> b ){
        h->SetBinContent(a, b);
    }
    h->SetBinContent(32767, 0);//  The last bin is bad, empty it.
    h->Draw();//  Justr drawing the histogram in the canvas.
    TF1 * f1 = new TF1("f1", "gaus(0)", 0, 10000);//  Create a Gaussian function for fitting.
    // h.Fit("gaus", "", "same", 950, 1100);
    //  Fit the histogram by the normal distribution in the range (left, right).
    //  The fit result is output in the terminal session.
    h->Fit(f1, "", "same", left, right);
    // f1->Draw("same");
    c1->Update();//  Update our canvas to draw new objects.
}

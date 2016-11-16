//  Usage:
//    $ root treemaker.C
//    $ root 'treemaker.C(string)'
//    $ root 'treemaker.C("path/to/file.dat")'
//    $ root 'treemaker.C("path/to/file.dat")' -q -b
//
//    Tested with: ROOT 6.06/00.

#include "TTree.h"
#include "TFile.h"

//  Input parameters:
//    fname --- the input file name, where data of peaks' positions and widths contained.
void treemaker(
        string fname = "C:/File/output.dat"){
    // Create an output file.
    TFile Fout("C:/File/tree.root", "RECREATE");
    // Create a TTree object to put in it data.
    TTree t("t", "gain data");
    // Read data from the input file into the tree.
    // The tree will have 8 branches:
    // snum --- the serial number [integer]
    // npix --- the number of fired pixels [integer]
    // volt --- the supply voltage of a MPPC [V, float]
    // temp --- the MPPC temperature [Celsium degrees, float]
    // m --- the peak position [ADC channel, float]
    // me --- the peak position determinition error [ADC channel, float]
    // s --- the peak Gaussian sigma [ADC channel, float]
    // se --- the peak Gaussian sigma determinition error
    //        [ADC channel, float]
    t.ReadFile(fname.c_str(), "snum/I:npix:volt/F:temp:m:me:s:se");
    // Change the marker style from default points to small crosses.
    t.SetMarkerStyle(6);
    // Write the tree into the output file.
    t.Write();
    // Close the output file, guarantee that data are safe.
    Fout.Close();
}

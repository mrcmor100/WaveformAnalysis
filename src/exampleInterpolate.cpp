#include <iostream>

int exampleInterpolate(int blk = 0) {
//Read reference waveforms
  
  const int ncol=30; //number of calo colomns tested in this run (3 for runs 55 and 56)
  const int nlin=36; //number of calo blocks in each colomn
  const int nblocks=ncol*nlin; //number of tested calo blocks
  const int maxwfpulses=12; //nb maximal de pulses que la wfa peut trouver
  const int ntime=110; // number of time samples for each fADC channel (100 for runs 55 and 56)
  const int nbparameters=2+2*maxwfpulses;
  cout<<"nbparameters = "<<nbparameters<<endl;
  Double_t x[ntime],y[ntime];
  ifstream filewf;
  Double_t dum1;

 filewf.open(Form("RWF/refwf_block_%d.txt",blk));
 if(filewf.is_open()) {
   filewf>>dum1>>dum1>>dum1;
   for (Int_t it=0;it<ntime;it++) {
     filewf>>x[it]>>y[it];
   }
   filewf.close();
 }

 TGraph* gr = new TGraph();
 TGraph* spline = new TGraph();
 //Fit the observed data
 ROOT::Math::Interpolator* interp = new ROOT::Math::Interpolator(ntime, ROOT::Math::Interpolation::kCSPLINE);
 interp->SetData(ntime,x,y); 
 for(int i = 0; i < ntime; i++) {
   gr->SetPoint(i,x[i],y[i]);
   spline->SetPoint(i,x[i],interp->Eval(x[i]));
 }
 TCanvas* c1 = new TCanvas("","",500,500);
 c1->cd();
 gr->Draw("AP*");
 spline->SetLineColor(kRed);
 spline->Draw("SAME");
 c1->Update();
 
 return 0;
 }

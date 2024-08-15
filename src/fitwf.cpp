///////////////////////////////////////////////////////////// FIT FUNCTION USED AND SCHEMATICS /////////////////////////////////////////////////////////////

Double_t func(Double_t *x, Double_t *par){
  // j is the block number passed in as a parameter.
  // The block number is set via TF1 FixParameter(0,nblock)
  Int_t j= (int)(par[0]);
  Double_t first_element = x[0];
  Double_t val=0;
  // maxwfpulses is the maximum number of pulses in an fADC sample.
  // In this case it is set to 12 pulses.
  for(Int_t p=0; p<maxwfpulses; p++){
    if(first_element - par[2 + 2*p] > 1 && first_element - par[2 + 2*p] < 109)
      val += par[3 + 2*p] * interpolation[j]->Eval(first_element - par[2 + 2*p]);
  }
  return val+par[1];
}

void Fitwf(Int_t bn){

//Detect the pulses
//bn is block number
  wfnpulse[bn]=0;
  // good is used for reference time check
  Int_t good=0;

 for(Int_t p=0;p<maxwfpulses;p++) {
   wfampl[bn][p]=-1;
 }
 // Look at all 110 samples except the last 6.
 // Since the algorithm requires 6 sequential events.
 for (Int_t it=0;it<ntime-6;it++) {
   //Check that the first 3 samples are increasing and next 2 are decreasing.
   if(hsig_i[bn]->GetBinContent(it+1) < hsig_i[bn]->GetBinContent(it+2) &&
      hsig_i[bn]->GetBinContent(it+2) < hsig_i[bn]->GetBinContent(it+3) &&
      hsig_i[bn]->GetBinContent(it+3) <= hsig_i[bn]->GetBinContent(it+4) &&
      hsig_i[bn]->GetBinContent(it+4) >= hsig_i[bn]->GetBinContent(it+5) )
     {
       // The 4th sample must be greater than zero.
       // This would  be the peak of the sample.
       if(hsig_i[bn]->GetBinContent(it+4) > 0) {
	 // Save the time and amplitude of this peak.
	 // Not sure what wfnpulse is yet.
	 wfampl[bn][wfnpulse[bn]]=hsig_i[bn]->GetBinContent(it+4);
	 wftime[bn][wfnpulse[bn]]=hsig_i[bn]->GetBinCenter(it+4);
	 // Check that the time peak is in coincidence with electron arm / reference time.
	 // timeref[bn] reference time on a per block basis?
	 // timerefacc - correction to difference in time for elastics to production ~10ns.
	 // hard coded 4.1 ns?
	 if(TMath::Abs(wftime[bn][wfnpulse[bn]]-timeref[bn]-timerefacc)<4.1) {
	   good=1;
	 }
	 // Add another pulse to the hit!
	 wfnpulse[bn]++;
	 // Except for if we have more than 12 pulses.
	 if(wfnpulse[bn]==maxwfpulses) {
	   // Then decriment and break loop by going to ntime.
	   wfnpulse[bn]=maxwfpulses-1;
	   it=ntime;
	 }
	 // If we found a pulse, skip ahead 4.
	 // Can't find another pulse here...
	 it+=4;
       }
     }
 } // End of fitting +3 and -3 samples, finds peak.
 
 if(wfnpulse[bn] > maxwfpulses-2) {
   //"Warning: Excessively high number of pulses in the waveform of the block."
   cout<<"Warning : nb de pulses excessivement eleve dans la wf du blocWhat is "<<bn<<endl;
 }

//Adjust the parameters of the fit function

 for(Int_t p=0;p<maxwfpulses;p++){
   finter[bn]->FixParameter(2+2*p,0.);finter[bn]->FixParameter(3+2*p,0.);
 }
 // We found a pulse and it was within the reference time selection
 if(wfnpulse[bn]>0&&good==1) {
   // Reduce the number of parameters to fit based on the number of pulses found.
   // Set the 
   for(Int_t p=0; p < TMath::Min(maxwfpulses,wfnpulse[bn]); p++){
     // The parameters are allowed to vary and the limits set to 0,0.
     finter[bn]->ReleaseParameter(2+2*p);
     finter[bn]->ReleaseParameter(3+2*p);
     // Set the time and amplitude for this pulse based on the actual value in the sample.
     // This kind of starts out assuming there is no pileup.  Will alter as the fit proceeds if needed.
     finter[bn]->SetParameter(2+2*p,wftime[bn][p]-timeref[bn]);
     finter[bn]->SetParameter(3+2*p,wfampl[bn][p]);
     // Parameter limits are reset given the strict control in ReleaseParameter
     finter[bn]->SetParLimits(2+2*p,wftime[bn][p]-timeref[bn]-3,wftime[bn][p]-timeref[bn]+3);
     finter[bn]->SetParLimits(3+2*p,wfampl[bn][p]*0.2,wfampl[bn][p]*3);
   }
 }
 // Used an if here instead of an else if even though it is really an else if to the good block.
 if(wfnpulse[bn]>0 && good==0){
   for(Int_t p=0;p < TMath::Min(maxwfpulses,wfnpulse[bn]);p++){
     finter[bn]->ReleaseParameter(2+2*p);
     finter[bn]->ReleaseParameter(3+2*p);
     finter[bn]->SetParameter(2+2*p,wftime[bn][p]-timeref[bn]);
     finter[bn]->SetParameter(3+2*p,wfampl[bn][p]);
     finter[bn]->SetParLimits(2+2*p,wftime[bn][p]-timeref[bn]-3,wftime[bn][p]-timeref[bn]+3);
     finter[bn]->SetParLimits(3+2*p,wfampl[bn][p]*0.2,wfampl[bn][p]*3);
   }

//Search for an eventual pulse
   finter[bn]->ReleaseParameter(2+2*wfnpulse[bn]);finter[bn]->ReleaseParameter(3+2*wfnpulse[bn]);
   finter[bn]->SetParameter(2+2*wfnpulse[bn],timerefacc);finter[bn]->SetParameter(3+2*wfnpulse[bn],2);
   finter[bn]->SetParLimits(2+2*wfnpulse[bn],timerefacc-4,timerefacc+4);finter[bn]->SetParLimits(3+2*wfnpulse[bn],0.05,10);
   wfnpulse[bn]++;
 }

 // No pulses found, set to zero and fit baseline.
 // Aggressively try to find a pulse at the reference time.
 if(wfnpulse[bn]==0){
   for(Int_t p=0;p<1;p++){
     finter[bn]->ReleaseParameter(2+2*p);
     finter[bn]->ReleaseParameter(3+2*p);
     finter[bn]->SetParameter(2+2*p,timerefacc);
     finter[bn]->SetParameter(3+2*p,2);
     finter[bn]->SetParLimits(2+2*p,timerefacc-4,timerefacc+4);
     finter[bn]->SetParLimits(3+2*p,0.05,10);
   }
   // Say we found a single pulse?
   wfnpulse[bn]++;
 }
 
 // Finally, set the pedestal and give a range.
 finter[bn]->SetParameter(1,0.);
 finter[bn]->SetParLimits(1,-100,100.);

 // Do the fit for this block of this event
 hsig_i[bn]->Fit(Form("finter_%d",bn),"Q","",0.,ntime);
 
}


#include "Hist.hh"
#include  <cstdio>

Hist::Hist(const G4String& fname, G4double min, G4double max, G4int numbin) 
: fFileName(fname), 
  fMin(min), 
  fMax(max), 
  fDelta(0.), 
  fInvDelta(1.), 
  fSum(0.),
  fNumBins(numbin) {
  fDelta    = (fMax - fMin) / fNumBins;
  fInvDelta = 1./fDelta;
  Initialize();
}

Hist::Hist(const G4String& fname, G4double min, G4double max, G4double delta)
: fFileName(fname), 
  fMin(min), 
  fMax(max), 
  fDelta(delta), 
  fInvDelta(1.), 
  fSum(0.),
  fNumBins(0) {
  fInvDelta = 1./fDelta;  
  fNumBins = (G4int)((fMax - fMin) / (fDelta)) + 1.0;
  Initialize();
}


void Hist::Initialize() {
  fx.resize(fNumBins, 0.0);
  fy.resize(fNumBins, 0.0);
  for (G4int i = 0; i < fNumBins; ++i) {
    fx[i] = fMin + i * fDelta;
  }
  fSum = 0.0;  
}

void Hist::Fill(G4double x) {
  if (x<fMin) return;
  G4int indx = (x==fMax) ? fNumBins-1 : (G4int)((x - fMin) * fInvDelta);
/*  
  if (indx < 0) {
    G4cerr << "\n ***** ERROR in Hist::FILL  =>  x = " 
           << x << " < fMin = " << fMin 
           << G4endl;
    exit(1);
  }
*/  
  if (indx>-1 && indx<fNumBins) {  
    fy[indx] += 1.0;
    fSum     += 1.0;
  }
}


void Hist::Fill(G4double x, G4double w) {
  if (x<fMin) return;
  G4int indx = (x==fMax) ? fNumBins-1 : (G4int)((x - fMin) * fInvDelta);
/*
  if (indx < 0) {
    G4cerr << "\n ***** ERROR in Hist::FILL  =>  x = " 
           << x << " < fMin = " << fMin 
           << G4endl;
    exit(1);
  }
*/
  if (indx>-1 && indx<fNumBins) {  
    fy[indx] += w; //1.0 * w;
    fSum     += w;
  }
}

void Hist::WriteToFile(G4bool isNorm) {
  FILE* f = fopen(fFileName, "w");
  if (!f) {
    G4cerr << "\n ***** ERROR in Hist::WriteToFile  "
           << " cannot create the file = " << fFileName
           << G4endl; 
    exit(1);          
  }
  G4double norm = 1.0;
  if (isNorm) {
    norm  = 1. / (fSum*fDelta);
  }
  for (G4int i = 0; i < fNumBins; ++i) {
    fprintf(f, "%d\t%.8g\t%.8g\n", i, fx[i] + 0.5 * fDelta, fy[i] * norm);
  }
  fclose(f);
}


void Hist::WriteToFile(G4double norm) {
  FILE* f = fopen(fFileName, "w");
  if (!f) {
    G4cerr << "\n ***** ERROR in Hist::WriteToFile  "
           << " cannot create the file = " << fFileName 
           << G4endl; 
    exit(1);          
  }
  for (G4int i = 0; i < fNumBins; ++i) {
    fprintf(f, "%d\t%.8g\t%.8g\n", i, fx[i] + 0.5 * fDelta, fy[i] * norm);
  }
  fclose(f);
}

void Hist::Add(const Hist* hist) {
  if (fNumBins != hist->GetNumBins() || 
      fMin     != hist->GetMin() || 
      fMax     != hist->GetMax()) {
    G4cerr << "\n ***** ERROR in Hist::Add  "
           << " histograms have different dimensions ! "
           << G4endl;     
  }
  for (G4int i = 0; i < fNumBins; ++i) {
    fy[i] += hist->GetY()[i];
  } 
  fSum += hist->GetSum();
}












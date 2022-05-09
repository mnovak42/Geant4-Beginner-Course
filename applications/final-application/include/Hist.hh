// NOTE: this is a simple histogram class. Please avoid to use it in real
//       production! Use the histograms provided by g4analysis tools in your
//       future applications (see the examples in your Geant4 tookit or more
//       at appropriate (Analysis) section of the Book For Application Developers
//       https://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Analysis/analysis.html).
//
//       We use this histogram in our application only to illustrait how to
//       merge non primitive types. The histograms, provided by the g4analysis,
//       alrady know how to merge them. Moreover, they are thread safe and will
//       be merged automatically. This is a great tool provided by the Geant4
//       toolkit that removes some work from the user by hiding some complexity.
//       However, during the learing process it is important to understand all
//       that complexity and this is why we used this simple Hist class now in
//       our application.

#ifndef HIST_H
#define HIST_H

#include "globals.hh"

#include <vector>

class Hist {

public:
  // CTR: min/max value of the histogram with the number of bins
  Hist(const G4String& filename, G4double min, G4double max, G4int numbin);
  // CTR: min/max value of the histogram with bin width
  Hist(const G4String& filename, G4double min, G4double max, G4double delta);

  ~Hist() {/*nothing to do*/}

  void Initialize();

  void ReSet(const G4String& filename, G4double min, G4double max, G4int numbins) {
    fFileName = filename;
    fMin      = min;
    fMax      = max;
    fNumBins  = numbins;
    fDelta    = (fMax - fMin) / fNumBins;
    fInvDelta = 1./fDelta;
    Initialize();
  }

  // fill histogram with value x
  void Fill(G4double x);

  // fill histogram with value x and weight of w
  void Fill(G4double x, G4double w);

  G4int     GetNumBins() const { return fNumBins; }
  G4double  GetDelta()   const { return fDelta;   }
  G4double  GetMin()     const { return fMin;     }
  G4double  GetMax()     const { return fMax;     }
  G4double  GetSum()     const { return fSum;     }
  const std::vector<G4double>& GetX() const { return fx;       }
  const std::vector<G4double>& GetY() const { return fy;       }

  // write result to file
  void WriteToFile(G4bool isNorm=false);
  void WriteToFile(G4double norm);

  // Add the argument histogram to this (even nicer with operator overloading
  // but we keep it simple)
  void Add(const Hist* hist);


// Data members
private:
  G4String              fFileName;
  std::vector<G4double> fx;
  std::vector<G4double> fy;
  G4double              fMin;
  G4double              fMax;
  G4double              fDelta;
  G4double              fInvDelta;
  G4double              fSum;
  G4int                 fNumBins;
};

#endif

#ifndef mainSelectorMC_h
#define mainSelectorMC_h

#include "mainSelector.h"

class mainSelectorMC : public mainSelector {
public :

   mainSelectorMC(TTree * /*tree*/ =0) { }
   virtual ~mainSelectorMC() { }

   ClassDef(mainSelectorMC,0);

};

#endif

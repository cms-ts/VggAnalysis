#ifndef mainSelectorDT_h
#define mainSelectorDT_h

#include "mainSelector.h"

class mainSelectorDT : public mainSelector {
public :

   mainSelectorDT(TTree * /*tree*/ =0) { }
   virtual ~mainSelectorDT() { }

   ClassDef(mainSelectorDT,0);

};

#endif

void compile() {

  gSystem->CompileMacro("mainSelectorDT16.C", "kcO");
  gSystem->CompileMacro("mainSelectorDT17.C", "kcO");
  gSystem->CompileMacro("mainSelectorDT17B.C", "kcO");
  gSystem->CompileMacro("mainSelectorDT18.C", "kcO");

  gSystem->CompileMacro("mainSelectorMC16.C", "kcO");
  gSystem->CompileMacro("mainSelectorMC17.C", "kcO");
  gSystem->CompileMacro("mainSelectorMC18.C", "kcO");

}

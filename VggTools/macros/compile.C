void compile(TString options="kcO") {

  gSystem->CompileMacro("mainSelectorDT16.C",  options.Data());
  gSystem->CompileMacro("mainSelectorDT17.C",  options.Data());
  gSystem->CompileMacro("mainSelectorDT17B.C", options.Data());
  gSystem->CompileMacro("mainSelectorDT18.C",  options.Data());

  gSystem->CompileMacro("mainSelectorMC16.C",  options.Data());
  gSystem->CompileMacro("mainSelectorMC17.C",  options.Data());
  gSystem->CompileMacro("mainSelectorMC18.C",  options.Data());

  gSystem->CompileMacro("plot0.C", options.Data());

}

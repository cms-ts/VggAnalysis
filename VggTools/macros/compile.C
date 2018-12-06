void compile(string option="kcO") {

  gSystem->CompileMacro("mainSelectorDT16.C",  option.c_str());
  gSystem->CompileMacro("mainSelectorDT16H.C",  option.c_str());
  gSystem->CompileMacro("mainSelectorMC16.C",  option.c_str());

  gSystem->CompileMacro("mainSelectorDT17.C",  option.c_str());
  gSystem->CompileMacro("mainSelectorDT17B.C", option.c_str());
  gSystem->CompileMacro("mainSelectorMC17.C",  option.c_str());

  gSystem->CompileMacro("mainSelectorDT18.C",  option.c_str());
  gSystem->CompileMacro("mainSelectorMC18.C",  option.c_str());

  gSystem->CompileMacro("plot0.C", option.c_str());
  gSystem->CompileMacro("plot1.C", option.c_str());
  gSystem->CompileMacro("plot2.C", option.c_str());

}

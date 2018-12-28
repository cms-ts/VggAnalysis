void compile(string file="macro.C", string option="kcO") {

  gSystem->CompileMacro(file.c_str(), option.c_str());

}

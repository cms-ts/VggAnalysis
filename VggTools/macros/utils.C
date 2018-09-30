
void readMap(string myFile, map<string, float> &myMap) {

  ifstream input(myFile.data());
  string line;
  while (getline(input, line)) {
    if (line.length() > 0 && line[0] != '#') {
      istringstream stream(line);
      string key;
      float val;
      stream >> key >> val;
      myMap[key] = val;
//      cout << key << " " << val << endl;
    }
  }
  input.close();

}

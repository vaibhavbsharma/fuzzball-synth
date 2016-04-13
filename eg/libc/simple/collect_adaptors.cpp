#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int main() {
  ifstream fin1("identity-adaptors.txt");
  ifstream fin2("zero-adaptors.txt");
  vector<string> buf1,buf2;
  string line;
  while(getline(fin1,line)) {
    if(line.find("vaibhav")!=string::npos || line.find("_adaptor_")!=string::npos) continue;
    buf1.push_back(line);
  }
  while(getline(fin2,line))  {
    if(line.find("vaibhav")!=string::npos || line.find("_adaptor_")!=string::npos) continue;
    buf2.push_back(line);
  }
  for(int i=0;i<buf1.size();i++) {
    string f1,f1_name, f2, f2_name, adaptor;
    stringstream ss(buf1[i]);
    ss>>f1>>f2>>adaptor>>f1_name>>f2_name;
    int disagree=0;
    for(int j=0;j<buf2.size();j++) {
      string _f1,_f1_name, _f2, _f2_name, _adaptor;
      stringstream _ss(buf2[i]);
      _ss>>_f1>>_f2>>_adaptor>>_f1_name>>_f2_name;
      if(_f1==f1 && _f2==f2 && _adaptor!=adaptor) {
	disagree=1;
      }
    }
    if(disagree==0) {
      cout<<f1<<" "<<f2<<" "<<adaptor<<" "<<f1_name<<" "<<f2_name<<endl;
    }
  }
  return 0;
}
      

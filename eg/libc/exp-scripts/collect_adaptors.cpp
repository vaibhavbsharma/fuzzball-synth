#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>
#include <cstdlib>
using namespace std;

string pretty_adaptor(string s) {
  int pos=-1;
  int prev_pos=0;
  stringstream ret;
  while((pos=s.find_first_of(',',prev_pos))!=string::npos) {
    //cout<<prev_pos<<" "<<pos<<"_";
    stringstream ss(s.substr(prev_pos,pos));
    int a;
    if(pos==prev_pos) a=0;
    else if(pos-prev_pos==20) a=-1;
    else {
      ss>>a;
    }
    prev_pos=pos+1;
    pos=pos+1;
    ret<<a<<",";
    //cout<<prev_pos<<" "<<pos<<endl;
  }
  if(prev_pos==s.length()) ret<<"0";
  else if (s.length()-prev_pos==20) ret<<"-1";
  else ret<<s.substr(prev_pos,string::npos);
  return ret.str();
}

string getFileName(char *prefix_dir, int adapter_family, char *log_file, int n) {
  char str[200];
  switch(adapter_family) {
  case 1:
    sprintf(str, "%s/argsub/glibc-%d/logs/%s", prefix_dir, n, log_file);
    break;
  case 2:
    sprintf(str, "%s/typeconv/glibc-%d/logs/%s", prefix_dir, n, log_file);
    break;
  case 3:
    sprintf(str, "%s/arith/glibc-%d/logs/%s", prefix_dir, n, log_file);
    break;
  default: 
    cout<<"dont know how to generate log file for adapter family = "<<adapter_family<<endl;
    assert(false); 
  }
  return str;
}


int main(int argc, char * argv[]) {
  if (argc < 5) {
    fprintf(stderr, "Usage: collect-adapters <argument 1> <argument 2> <argument 3> <argument 4>\n");
    fprintf(stderr, "arguments list is as follows\n");
    fprintf(stderr, "1. <adapter family, 1=argsub, 2=typeconv, 3=arithmetic-int>\n");
    fprintf(stderr, "2. <log file to search through, e.g. 1.log>\n");
    fprintf(stderr, "3. <prefix directory containing the argsub/typeconv/arith subdirectories, e.g. /export/scratch/vaibhav/glibc-exps>\n");
    fprintf(stderr, "4. <number of bucket directories expected in prefix-directory/argsub or typeconv or arith/, e.g. 32>\n");
    exit(1);
  }
  char *log_file, *prefix_dir;
  int adapter_family = atoi(argv[1]);
  log_file = argv[2];
  prefix_dir = argv[3];
  int num_dirs = atoi(argv[4]);
  int ignored_adaptor_count=0;
  int total_adaptor_count=0;
  // offset of line containing f1 = <function name> from "cmd =" line, ditto for f2
  int f1_line_offset = 14, f2_line_offset = 15;
  // these two offsets are a bit different in the arithmetic adapter logs
  if (adapter_family == 3) {
    f1_line_offset-=2; f2_line_offset-=2;
  }
  //vector<string> blacklisted_fns;
  //populate_blacklisted_fns(blacklisted_fns);
 
  for(int i=1;i<=num_dirs;i++) {
    string filename = getFileName(prefix_dir, adapter_family, log_file, i);
    int thisfile_adaptor_count = 0;
    ifstream fin(filename.c_str());
    string line;
    vector<string> buf_line;
    int ignore_flag=0;
    while(getline(fin,line)) {
      //cout<<line<<endl;
      if(line.find("cmd = ")!=string::npos) {
	//cout<<"Clearing buf_line\n";
	buf_line.clear();
	ignore_flag=0;
      }
      buf_line.push_back(line);
      /*if(line.find("pthread")!=string::npos) {
	ignore_flag=1;
	}*/
      /*for(int ign_ind=0;ign_ind<blacklisted_fns.size();ign_ind++)
	if(line.find(blacklisted_fns[ign_ind])!=string::npos) {
	  ignore_flag=1;
	  //cout<<"Found "<<blacklisted_fns[ign_ind]<<" on line : "<<line<<endl;
	  }*/
      if(line.find("Final adaptor")!=string::npos) {
	thisfile_adaptor_count++;
	total_adaptor_count++;
	if(ignore_flag==0) {
	  //cout<<"Found an adaptor, printing its execution log"<<endl;
	  //for(int j=0;j<buf_line.size();j++) cout<<"    "<<buf_line[j]<<endl;
	  //cout<<buf_line[f1_line_offset]<<endl<<buf_line[f2_line_offset]<<endl<<buf_line[buf_line.size()-1]<<endl;
	  stringstream ss1(buf_line[f1_line_offset]),ss2(buf_line[f2_line_offset]),ss3(buf_line[buf_line.size()-1]);
	  string f1_num,f1_name,f2_num,f2_name,adaptor,ret_adaptor;
	  string tmpstr;
	  ss1>>f1_num>>tmpstr>>f1_name; //line is <f1num> = <f1name>
	  ss2>>f2_num>>tmpstr>>f2_name; //line is <f2num> = <f2name>
	  if (adapter_family != 3) { 
	    ss3>>tmpstr>>tmpstr>>tmpstr>>adaptor>>tmpstr>>ret_adaptor>>tmpstr>>tmpstr>>tmpstr>>tmpstr>>tmpstr;
	    adaptor=pretty_adaptor(adaptor);
	    ret_adaptor=pretty_adaptor(ret_adaptor);
	  } else {
	    if (line.find(':', 0) == string::npos) {
	      cout<<"line = "<<line<<" -- should have contained a : but did not"<<endl;
	      exit(1);
	    }
	    adaptor = line.substr(line.find(':', 0)+1, line.length());
	  }
	  cout<<f1_num<<" "<<f2_num<<" ("<<adaptor<<") ("<<ret_adaptor<<") "<<f1_name<<" "<<f2_name<<" "<<endl;
	}
	//else cout<<"Skipping adaptor because one of the functions was pthread_* or blacklisted"<<endl;
	if(ignore_flag==1) ignored_adaptor_count++;
	ignore_flag=0;
      }
    }
    fin.close();
    cout<<filename<<" " <<", number of adapters = " << thisfile_adaptor_count<<endl;
  }
  cout<<"ignored_adaptor_count = "<<ignored_adaptor_count<<endl;
  cout<<"total_adaptor_count = "<<total_adaptor_count<<endl;
  return 0;
}

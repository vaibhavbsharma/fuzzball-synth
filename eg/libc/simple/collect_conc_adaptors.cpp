#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
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

int main(int argc, char * argv[]) {
  int ignored_adaptor_count=0;
  int total_adaptor_count=0;
  vector<string> blacklisted_fns;
  
  //Functions that return -1 because of unimplemented syscalls
  blacklisted_fns.push_back(" = afs_syscall");
  blacklisted_fns.push_back(" = break");
  blacklisted_fns.push_back(" = fattach");
  blacklisted_fns.push_back(" = fdetach");
  blacklisted_fns.push_back(" = ftime");
  blacklisted_fns.push_back(" = getmsg");
  blacklisted_fns.push_back(" = getpmsg");
  blacklisted_fns.push_back(" = gtty");
  blacklisted_fns.push_back(" = isastream");
  blacklisted_fns.push_back(" = lock");
  blacklisted_fns.push_back(" = madvise1");
  blacklisted_fns.push_back(" = mpx");
  blacklisted_fns.push_back(" = prof");
  blacklisted_fns.push_back(" = profil");
  blacklisted_fns.push_back(" = putmsg");
  blacklisted_fns.push_back(" = putpmsg");
  blacklisted_fns.push_back(" = security");
  blacklisted_fns.push_back(" = stty");
  blacklisted_fns.push_back(" = tuxcall");
  blacklisted_fns.push_back(" = ulimit");
  blacklisted_fns.push_back(" = vserver");
 
  //Functions that return void
  blacklisted_fns.push_back(" = syslog");
  blacklisted_fns.push_back(" = vsyslog");
  blacklisted_fns.push_back(" = openlog");
  blacklisted_fns.push_back(" = closelog");
  blacklisted_fns.push_back(" = hdestroy");
  blacklisted_fns.push_back(" = hdestroy_r");
  blacklisted_fns.push_back(" = twalk");
  blacklisted_fns.push_back(" = tdestroy");
  blacklisted_fns.push_back(" = vwarnx");
  blacklisted_fns.push_back(" = vwarn");
  blacklisted_fns.push_back(" = warn");
  blacklisted_fns.push_back(" = warnx");
  blacklisted_fns.push_back(" = verr");
  blacklisted_fns.push_back(" = verrx");
  blacklisted_fns.push_back(" = err");
  blacklisted_fns.push_back(" = errx");
  blacklisted_fns.push_back(" = error");
  blacklisted_fns.push_back(" = error_at_line");
  blacklisted_fns.push_back(" = endfsent");
  blacklisted_fns.push_back(" = moncontrol");
  blacklisted_fns.push_back(" = monstartup");
  blacklisted_fns.push_back(" = _mcleanup");
  blacklisted_fns.push_back(" = mcount");
  blacklisted_fns.push_back(" = setspent");
  blacklisted_fns.push_back(" = endspent");
  blacklisted_fns.push_back(" = setsgent");
  blacklisted_fns.push_back(" = endsgent");
  blacklisted_fns.push_back(" = argp_failure");
  blacklisted_fns.push_back(" = argp_help");
  blacklisted_fns.push_back(" = argp_state_help");
  blacklisted_fns.push_back(" = argp_error");
  blacklisted_fns.push_back(" = argp_usage");
  blacklisted_fns.push_back(" = pthread_exit");
  blacklisted_fns.push_back(" = backtrace_symbols_fd");
  blacklisted_fns.push_back(" = sethostent");
  blacklisted_fns.push_back(" = endhostent");
  blacklisted_fns.push_back(" = setnetent");
  blacklisted_fns.push_back(" = endnetent");
  blacklisted_fns.push_back(" = setprotoent");
  blacklisted_fns.push_back(" = endprotoent");
  blacklisted_fns.push_back(" = setservent");
  blacklisted_fns.push_back(" = endservent");
  blacklisted_fns.push_back(" = setrpcent");
  blacklisted_fns.push_back(" = endrpcent");
  blacklisted_fns.push_back(" = endnetgrent");
  blacklisted_fns.push_back(" = if_freenameindex");
  blacklisted_fns.push_back(" = freeifaddrs");
  blacklisted_fns.push_back(" = setaliasent");
  blacklisted_fns.push_back(" = endaliasent");
  blacklisted_fns.push_back(" = herror");
  blacklisted_fns.push_back(" = _seterr_reply");
  blacklisted_fns.push_back(" = xdrrec_create");
  blacklisted_fns.push_back(" = des_setparity");
  blacklisted_fns.push_back(" = clnt_perror");
  blacklisted_fns.push_back(" = clnt_perrno");
  blacklisted_fns.push_back(" = clnt_pcreateerror");
  blacklisted_fns.push_back(" = get_myaddress");
  blacklisted_fns.push_back(" = xprt_register");
  blacklisted_fns.push_back(" = xprt_unregister");
  blacklisted_fns.push_back(" = svc_unregister");
  blacklisted_fns.push_back(" = svcerr_noproc");
  blacklisted_fns.push_back(" = svcerr_decode");
  blacklisted_fns.push_back(" = svcerr_systemerr");
  blacklisted_fns.push_back(" = svcerr_auth");
  blacklisted_fns.push_back(" = svcerr_weakauth");
  blacklisted_fns.push_back(" = svcerr_noprog");
  blacklisted_fns.push_back(" = svcerr_progvers");
  blacklisted_fns.push_back(" = svc_getreq_common");
  blacklisted_fns.push_back(" = svc_getreqset");
  blacklisted_fns.push_back(" = svc_getreq_poll");
  blacklisted_fns.push_back(" = svc_getreq");
  blacklisted_fns.push_back(" = xdr_free");
  blacklisted_fns.push_back(" = xdrmem_create");
  blacklisted_fns.push_back(" = xdrstdio_create");
  blacklisted_fns.push_back(" = svc_exit");
  blacklisted_fns.push_back(" = svc_run");
  blacklisted_fns.push_back(" = setutent");
  blacklisted_fns.push_back(" = endutent");
  blacklisted_fns.push_back(" = updwtmp");
  blacklisted_fns.push_back(" = setutxent");
  blacklisted_fns.push_back(" = endutxent");
  blacklisted_fns.push_back(" = updwtmpx");
  blacklisted_fns.push_back(" = getutmp");
  blacklisted_fns.push_back(" = freelocale");
  blacklisted_fns.push_back(" = longjmp");
  blacklisted_fns.push_back(" = abort");
  blacklisted_fns.push_back(" = qsort_r");
  blacklisted_fns.push_back(" = qsort");
  blacklisted_fns.push_back(" = exit");
  blacklisted_fns.push_back(" = on_exit");
  blacklisted_fns.push_back(" = quick_exit");
  blacklisted_fns.push_back(" = srand");
  blacklisted_fns.push_back(" = srand48");
  blacklisted_fns.push_back(" = lcong48");
  blacklisted_fns.push_back(" = makecontext");
  blacklisted_fns.push_back(" = perror");
  blacklisted_fns.push_back(" = psignal");
  blacklisted_fns.push_back(" = flockfile");
  blacklisted_fns.push_back(" = funlockfile");
  blacklisted_fns.push_back(" = psiginfo");
  blacklisted_fns.push_back(" = setbuffer");
  blacklisted_fns.push_back(" = clearerr");
  blacklisted_fns.push_back(" = rewind");
  blacklisted_fns.push_back(" = setbuf");
  blacklisted_fns.push_back(" = setlinebuf");
  blacklisted_fns.push_back(" = clearerr_unlocked");
  blacklisted_fns.push_back(" = free");
  blacklisted_fns.push_back(" = malloc_stats");
  blacklisted_fns.push_back(" = mcheck_check_all");
  blacklisted_fns.push_back(" = mcheck");
  blacklisted_fns.push_back(" = mcheck_pedantic");
  blacklisted_fns.push_back(" = tr_break");
  blacklisted_fns.push_back(" = mtrace");
  blacklisted_fns.push_back(" = muntrace");
  blacklisted_fns.push_back(" = bzero");
  blacklisted_fns.push_back(" = bcopy");
  blacklisted_fns.push_back(" = swab");
  blacklisted_fns.push_back(" = argz_delete");
  blacklisted_fns.push_back(" = argz_extract");
  blacklisted_fns.push_back(" = argz_stringify");
  blacklisted_fns.push_back(" = envz_remove");
  blacklisted_fns.push_back(" = envz_strip");
  blacklisted_fns.push_back(" = tzset");
  blacklisted_fns.push_back(" = rewinddir");
  blacklisted_fns.push_back(" = seekdir");
  blacklisted_fns.push_back(" = setgrent");
  blacklisted_fns.push_back(" = endgrent");
  blacklisted_fns.push_back(" = setpwent");
  blacklisted_fns.push_back(" = endpwent");
  blacklisted_fns.push_back(" = _Exit");
  blacklisted_fns.push_back(" = globfree");
  blacklisted_fns.push_back(" = freeaddrinfo");
  blacklisted_fns.push_back(" = regfree");
  blacklisted_fns.push_back(" = re_set_registers");
  blacklisted_fns.push_back(" = wordfree");
  blacklisted_fns.push_back(" = cfmakeraw");
  blacklisted_fns.push_back(" = sync");
  blacklisted_fns.push_back(" = insque");
  blacklisted_fns.push_back(" = remque");
  blacklisted_fns.push_back(" = endusershell");
  blacklisted_fns.push_back(" = setusershell");

 
  for(int i=0;i<8;i++) {
    string filename("../simple-");
    filename=filename+(char)('1'+i);
    filename=filename+"/logs/";
    filename=filename+(char)('1');
    if(argc>1) {
      if(argv[1][1]=='0') filename=filename+"-zero";
      else if(argv[1][1]=='1') filename=filename+"-identity";
    } 
    filename=filename+".log";
    cout<<filename<<endl;
    ifstream fin(filename.c_str());
    string line;
    vector<string> buf_line;
    int ignore_flag=0;
    while(getline(fin,line)) {
      //cout<<line<<endl;
      if(line.find("Startin synthesis")!=string::npos) {
	//cout<<"Clearing buf_line\n";
	buf_line.clear();
	ignore_flag=0;
	while(line.find("fuzzball") == string::npos) getline(fin, line);
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
	total_adaptor_count++;
	if(ignore_flag==0) {
	  //cout<<"Found an adaptor, printing its execution log"<<endl;
	  //for(int j=0;j<buf_line.size();j++) cout<<"    "<<buf_line[j]<<endl;
	  //cout<<buf_line[15]<<endl<<buf_line[16]<<endl<<buf_line[buf_line.size()-1]<<endl;
	  stringstream ss1(buf_line[13]),ss2(buf_line[14]),ss3(buf_line[buf_line.size()-1]);
	  string f1,f1_name,f2,f2_name,adaptor,ret_adaptor;
	  string tmpstr;
	  ss1>>f1>>tmpstr>>f1_name;
	  ss2>>f2>>tmpstr>>f2_name;
	  ss3>>tmpstr>>tmpstr>>tmpstr>>adaptor>>tmpstr>>ret_adaptor;
	  adaptor=pretty_adaptor(adaptor);
	  ret_adaptor=pretty_adaptor(ret_adaptor);
	  cout<<f1<<" "<<f2<<" ("<<adaptor<<") ("<<ret_adaptor<<") "<<f1_name<<" "<<f2_name<<endl;
	}
	//else cout<<"Skipping adaptor because one of the functions was pthread_* or blacklisted"<<endl;
	if(ignore_flag==1) ignored_adaptor_count++;
	ignore_flag=0;
      }
    }
    fin.close();
  }
  cout<<"ignored_adaptor_count = "<<ignored_adaptor_count<<endl;
  cout<<"total_adaptor_count = "<<total_adaptor_count<<endl;
  return 0;
}

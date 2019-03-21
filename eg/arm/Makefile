HEADERS = ./all_adapters/include/all_adapters_ref1.h \
          ./all_adapters/include/all_adapters_ref2.h \
          ./all_adapters/include/all_adapters_clamp.h

INCLUDE_DIRS=./all_adapters

ifndef REFNUM
  $(error REFNUM is not set, run make REFNUM=<1-25>)
endif

default: clean two-funcs-conc 

two-funcs-conc : two-funcs-conc.cpp $(HEADERS) 
	c++ two-funcs-conc.cpp -g -o two-funcs-conc \
	-I $(INCLUDE_DIRS)/include -I . -DREFNUM=$(REFNUM)

clean:
	rm -f two-funcs-conc 

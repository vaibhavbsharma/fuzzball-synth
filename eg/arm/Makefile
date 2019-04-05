HEADERS = ./all_adapters/include/all_adapters_ref1.h \
          ./all_adapters/include/all_adapters_ref2.h \
          ./all_adapters/include/all_adapters_clamp.h

INCLUDE_DIRS=./all_adapters

ifndef REFNUM
  $(warning REFNUM is not set, run make REFNUM=<1-25> ADAPTER_FAMILY=<2-3>)
endif

ifndef ADAPTER_FAMILY
  $(warning ADAPTER_FAMILY is not set, run make REFNUM=<1-25> ADAPTER_FAMILY=<2-3>)
endif

default: clean cluster-adapters 

cluster-adapters : cluster-adapters.cpp $(HEADERS) 
	c++ cluster-adapters.cpp -g -o cluster-adapters \
	-I $(INCLUDE_DIRS)/include -I . -DREFNUM=$(REFNUM)

clean:
	rm -f cluster-adapters 

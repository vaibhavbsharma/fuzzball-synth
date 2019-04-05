HEADERS = ./include/typeconv/all_adapters_ref1.h \
          ./include/typeconv/all_adapters_ref2.h \
          ./include/typeconv/all_adapters_clamp.h

ifndef REFNUM
  $(warning ADAPTER_FAMILY is not set, run make REFNUM=<1-25> ADAPTER_FAMILY=<2-3>)
endif

ifndef ADAPTER_FAMILY
  $(warning ADAPTER_FAMILY is not set, run make REFNUM=<1-25> ADAPTER_FAMILY=<2-3>)
endif

default: clean cluster-adapters 

cluster-adapters : cluster-adapters.cpp $(HEADERS) 
	c++ cluster-adapters.cpp -g -o cluster-adapters \
	-I ./include -I . -I .. -DREFNUM=$(REFNUM) -DADAPTER_FAMILY=$(ADAPTER_FAMILY)

clean:
	rm -f cluster-adapters 

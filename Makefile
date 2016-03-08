all: sum_crypto.exe

../mcl/lib/libmcl.a:
	$(MAKE) -C ../mcl
CXXFLAGS+=-I ../mcl/include/ -I ../cybozulib/include/ -I ../xbyak/ -Ofast -march=native
LDFLAGS+=-L ../mcl/lib -lmcl -lgmp -lgmpxx

sum_crypto.o: sum_crypto.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)
sum_crypto.exe: sum_crypto.o ../mcl/lib/libmcl.a
	$(CXX) -o $@ $< $(LDFLAGS)

clean:
	rm -rf sum_crypto.o sum_crypto.exe

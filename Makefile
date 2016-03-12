all: add_he.exe

../mcl/lib/libmcl.a:
	$(MAKE) -C ../mcl
CXXFLAGS+=-I ../mcl/include/ -I ../cybozulib/include/ -I ../xbyak/ -Ofast -march=native
LDFLAGS+=-L ../mcl/lib -lmcl -lgmp -lgmpxx

add_he.o: add_he.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)
add_he.exe: add_he.o ../mcl/lib/libmcl.a
	$(CXX) -o $@ $< $(LDFLAGS)

clean:
	rm -rf add_he.o add_he.exe

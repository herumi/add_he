set INC=-I ../cybozulib/include  -I ../xbyak/ -I../mcl/include -I ../cybozulib_ext/mpir/include
cl /Ox /EHsc /MD /DNOMINMAX %INC% add_he.cpp ../mcl/src/fp.cpp -DMCL_NO_AUTOLINK /link /LIBPATH:../cybozulib_ext/mpir/lib

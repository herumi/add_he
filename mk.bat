set INC=-I ../cybozulib/include  -I ../xbyak/ -I../mcl/include -I ../cybozulib_ext/mpir/include
cl /Ox /EHsc /MD /DNOMINMAX %INC% sum_crypto.cpp ../mcl/src/fp.cpp -DMCL_NO_AUTOLINK /link /LIBPATH:../cybozulib_ext/mpir/lib

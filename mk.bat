set INC=-I ../cybozulib/include  -I ../xbyak/ -I../mcl/include -I ../cybozulib_ext/include
rem cl /Ox /EHsc /MT /DNOMINMAX %INC% add_he.cpp ../mcl/src/fp.cpp -DMCL_NO_AUTOLINK /link /LIBPATH:../cybozulib_ext/lib
cl /Od /Zi /EHsc /MT /DNOMINMAX %INC% add_he.cpp ../mcl/src/fp.cpp -DMCL_NO_AUTOLINK /link /LIBPATH:../cybozulib_ext/lib

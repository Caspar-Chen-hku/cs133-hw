CXX = mpicxx

SRCS = mpi_2.cpp

REQUIRED_FILES = mpi.cpp lab2-report.pdf

np ?= 16

test: gemm
	mpiexec -np $(np) ./$^

gemm: $(SRCS)
	$(CXX) $(subst -fopenmp,,$(CXXFLAGS)) -o $@ $(filter %.cpp %.a %.o, $^) -lgomp -std=c++17

../lab1/gemm-baseline.a:
	$(MAKE) -C ../lab1 gemm-baseline.a

include ../makefile

CXX = mpicxx

SRCS1 = mpi_2.cpp
SRCS2 = mpi_3.cpp

REQUIRED_FILES = mpi.cpp lab2-report.pdf

np ?= 16

test: gemm
	mpiexec -np $(np) ./$^

gemm1: $(SRCS1)
	$(CXX) $(subst -fopenmp,,$(CXXFLAGS)) -o $@ $(filter %.cpp %.a %.o, $^) -lgomp -std=c++17

gemm2: $(SRCS2)
	$(CXX) $(subst -fopenmp,,$(CXXFLAGS)) -o $@ $(filter %.cpp %.a %.o, $^) -lgomp -std=c++17

../lab1/gemm-baseline.a:
	$(MAKE) -C ../lab1 gemm-baseline.a

CXXFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter -std=c++23 -O2
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"

SOURCE_DIR := ../source
OBJECT_DIR := ../object
INCLUDE_DIR := ../include

INCS = $(INCLUDE_DIR)/vector.h $(INCLUDE_DIR)/matrix.h ../minimization/minimizer.h ../linearEquations/qrsolver.h ann.h

SRCS = $(INCS:$(INCLUDE_DIR)/%.h=$(SOURCE_DIR)/%.cc)
SRCS := $(SRCS:.h=.cc)

OBJS := $(INCS:$(INCLUDE_DIR)/%.h=$(OBJECT_DIR)/%.o)
OBJS := $(OBJS:.h=.o)

.PHONY: all clean
all: Out.txt plot.ann.svg plot.annDerivs.svg plot.annIntegral.svg

Out.txt : main
	./$< > $@

main : main.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o $@ $^

plot.ann.svg : Out.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key top; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  set title "ANN f(x) approximation with 8 hidden neurons"; \
		  f(x) = cos(5*x-1)*exp(-x*x); \
		  plot \
			f(x) title "cos(5x-1)*exp(-x^2)",\
		  	"$<" index 1 using 1:2 with points pointtype 1 title "Training data",\
		  	"$<" index 2 using 1:2 with lines title "ANN approximation"\
	' | gnuplot

plot.annDerivs.svg : Out.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key top; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  set title "ANN f(x) approximation with 8 hidden neurons"; \
		  f(x) = cos(5*x-1)*exp(-x*x); \
		  plot \
			f(x) title "cos(5x-1)*exp(-x^2)",\
		  	"$<" index 3 using 1:2 with lines title "ANN derivative",\
		  	"$<" index 4 using 1:2 with lines title "ANN 2nd derivative"\
	' | gnuplot

plot.annIntegral.svg : Out.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key top; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  set title "ANN f(x) approximation with 8 hidden neurons"; \
		  plot \
		  	"$<" index 5 using 1:2 with lines title "ANN integral",\
	' | gnuplot

$(OBJECT_DIR)/%.o : $(SOURCE_DIR)/%.cc | $(OBJECT_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJECT_DIR):
	mkdir -p $@

clean:
	$(RM) [Oo]ut*.txt main *.svg *.png $(OBJS) *.o
CXXFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter -std=c++23 -O2
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"

SOURCE_DIR := ../source
OBJECT_DIR := ../object
INCLUDE_DIR := ../include

INCS = $(INCLUDE_DIR)/vector.h $(INCLUDE_DIR)/matrix.h mcint.h

SRCS = $(INCS:$(INCLUDE_DIR)/%.h=$(SOURCE_DIR)/%.cc)
SRCS := $(SRCS:.h=.cc)

OBJS := $(INCS:$(INCLUDE_DIR)/%.h=$(OBJECT_DIR)/%.o)
OBJS := $(OBJS:.h=.o)

.PHONY: all clean
all: Out.txt plot.error.svg plot.quasiError.svg

Out.txt : main
	./$< > $@

main : main.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o $@ $^

plot.error.svg : Out.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key right; \
		  set xlabel "N"; \
		  set ylabel "error"; \
		  set logscale x 2; \
		  f(x) = a/sqrt(x); \
		  a = 1.0; \
		  fit f(x) "$<" index 1 using 1:3 via a; \
		  set title "Error estimate of area of unit circle using uniform sampling"; \
		  plot \
		  	"$<" index 1 using 1:2 with points pointtype 3 title "estimated error",\
			"$<" index 1 using 1:3 with points pointtype 1 title "actual error",\
			f(x) title sprintf("a/sqrt(N) fit, a = %3.5f", a) \
	' | gnuplot

plot.quasiError.svg : Out.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key right; \
		  set xlabel "N"; \
		  set ylabel "error"; \
		  set logscale x 2; \
		  f(x) = a/sqrt(x); \
		  a = 0.01; \
		  fit f(x) "$<" index 3 using 1:3 via a; \
		  set title "Error estimate of area of unit circle using quasi-random sampling"; \
		  plot \
		  	"$<" index 3 using 1:2 with points pointtype 3 title "estimated error",\
			"$<" index 3 using 1:3 with points pointtype 1 title "actual error",\
			f(x) title sprintf("a/sqrt(N) fit, a = %3.5f", a) \
	' | gnuplot

#Create all object files from their corresponding .cc file. Also check if the object folder even exists
$(OBJECT_DIR)/%.o : $(SOURCE_DIR)/%.cc | $(OBJECT_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

#If the object directory does not exist, create it.
$(OBJECT_DIR):
	mkdir -p $@

clean:
	$(RM) [Oo]ut*.txt main *.svg *.png $(OBJS) *.o
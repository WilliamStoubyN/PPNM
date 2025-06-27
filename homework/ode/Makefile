CXXFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter -std=c++23 -O2
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"

SOURCE_DIR := ../source
OBJECT_DIR := ../object
INCLUDE_DIR := ../include

INCS = $(INCLUDE_DIR)/vector.h $(INCLUDE_DIR)/matrix.h ode.h

SRCS = $(INCS:$(INCLUDE_DIR)/%.h=$(SOURCE_DIR)/%.cc)
SRCS := $(SRCS:.h=.cc)

OBJS := $(INCS:$(INCLUDE_DIR)/%.h=$(OBJECT_DIR)/%.o)
OBJS := $(OBJS:.h=.o)

.PHONY: all clean
all: Out.txt plot.harmonic.svg plot.odeint.svg orbitData.txt plot.circular.svg plot.elliptical.svg plot.precession.svg

Out.txt : main
	./$< > $@

main : main.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o $@ $^

plot.harmonic.svg : Out.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key bottom; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  f(x) = cos(x) ; \
		  plot \
			f(x) title "cos(x)",\
		  	"$<" index 0 with linespoints title "numerical solution y"\
	' | gnuplot

plot.odeint.svg : Out.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key bottom; \
		  set xlabel "t"; \
		  set ylabel "theta"; \
		  set title "Driven harmonic oscillator with friction from scipy"; \
		  plot \
		  	"$<" index 1 with linespoints title "numerical solution theta",\
			"$<" index 2 with linespoints title "numerical solution omega"\
	' | gnuplot

plot.circular.svg : orbitData.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "angle phi"; \
		  set ylabel "reduced circumference 1/r"; \
		  set size square; \
		  set title "Equatorial motion with u(0) = 1, du(0) = 0.001, epsilon = 0.0"; \
		  plot[-1.2:1.2][-1.2:1.2] "$<" index 0 using (1/$$2)*cos($$1):(1/$$2)*sin($$1)  with lines notitle\
	' | gnuplot

plot.elliptical.svg : orbitData.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "angle phi"; \
		  set ylabel "reduced circumference 1/r"; \
		  set title "Equatorial motion with u(0) = 1, du(0) = -0.5, epsilon = 0.0"; \
		  plot "$<" index 1 using (1/$$2)*cos($$1):(1/$$2)*sin($$1)  with lines notitle\
	' | gnuplot

plot.precession.svg : orbitData.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "angle phi"; \
		  set ylabel "reduced circumference 1/r"; \
		  set title "Equatorial motion with u(0) = 1, du(0) = -0.5, epsilon = 0.1"; \
		  plot "$<" index 2 using (1/$$2)*cos($$1):(1/$$2)*sin($$1)  with lines notitle\
	' | gnuplot


orbitData.txt : orbitSolver
	./$< > $@

orbitSolver : orbitSolver.o $(OBJS)
	$()	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o $@ $^

#Create all object files from their corresponding .cc file. Also check if the object folder even exists
$(OBJECT_DIR)/%.o : $(SOURCE_DIR)/%.cc | $(OBJECT_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

#If the object directory does not exist, create it.
$(OBJECT_DIR):
	mkdir -p $@

clean:
	$(RM) [Oo]ut*.txt main *.svg *.png $(OBJS) *.o orbitData.txt
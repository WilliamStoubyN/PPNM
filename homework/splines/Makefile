CXXFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter -std=c++23 -O2
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"

SOURCE_DIR := ../source
OBJECT_DIR := ../object
INCLUDE_DIR := ../include

INCS = $(INCLUDE_DIR)/vector.h $(INCLUDE_DIR)/matrix.h spline.h

SRCS = $(INCS:$(INCLUDE_DIR)/%.h=$(SOURCE_DIR)/%.cc)
SRCS := $(SRCS:.h=.cc)

OBJS := $(INCS:$(INCLUDE_DIR)/%.h=$(OBJECT_DIR)/%.o)
OBJS := $(OBJS:.h=.o)

.PHONY: all clean
all: Out.txt plot.linspline.svg plot.qspline.svg

Out.txt : main
	./$< > $@

main : main.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o $@ $^

plot.linspline.svg : Out.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key bottom; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  f(x) = cos(x) ; \
		  plot \
			f(x) title "cos(x)",\
		  	"$<" index 1 with points title "Sample points",\
		  	"$<" index 2 with lines title "Linear spline",\
		  	"$<" index 3 with lines title "Integral"\
	' | gnuplot

plot.qspline.svg : Out.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key top; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  f(x) = sin(x) ; \
		  plot \
			f(x) title "sin(x)",\
		  	"$<" index 4 with points title "Sample points",\
			"$<" index 5 with lines title "Quadratic spline", \
		  	"$<" index 6 with lines title "Spline derivative",\
		  	"$<" index 7 with lines title "Spline integral"\
	' | gnuplot

#Create all object files from their corresponding .cc file. Also check if the object folder even exists
$(OBJECT_DIR)/%.o : $(SOURCE_DIR)/%.cc | $(OBJECT_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

#If the object directory does not exist, create it.
$(OBJECT_DIR):
	mkdir -p $@

clean:
	$(RM) [Oo]ut*.txt main *.svg *.png $(OBJS) *.o
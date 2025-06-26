CXXFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter -std=c++23 -O2
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"

SOURCE_DIR := ../homework/source
OBJECT_DIR := ../homework/object
INCLUDE_DIR := ../homework/include

INCS = $(INCLUDE_DIR)/vector.h $(INCLUDE_DIR)/matrix.h spline.h

SRCS = $(INCS:$(INCLUDE_DIR)/%.h=$(SOURCE_DIR)/%.cc)
SRCS := $(SRCS:.h=.cc)

OBJS := $(INCS:$(INCLUDE_DIR)/%.h=$(OBJECT_DIR)/%.o)
OBJS := $(OBJS:.h=.o)

.PHONY: all clean
all: Out.txt data/out.cubicData.txt plots/plot.cubicSubSpline.svg data/out.quarticData.txt plots/plot.quarticSubSpline.svg

Out.txt : main
	./$< --task 0 > $@

data/out.cubicData.txt : main
	./$< --task 1 > $@

data/out.quarticData.txt : main
	./$< --task 2 > $@

plots/plot.cubicSubSpline.svg : data/out.cubicData.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key top; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  set title "Cubic Sub-spline"; \
		  f(x) = sin(x); \
		  plot \
			f(x) title "sin(x)",\
		  	"$<" index 0 using 1:2 with points pointtype 7 title "Sample",\
			"$<" index 0 using 1:3 with points pointtype 1 title "Sample deriv",\
		  	"$<" index 1 using 1:2 with lines title "Cubic sub-spline",\
			"$<" index 2 using 1:2 with lines title "Spline deriv",\
			"$<" index 3 using 1:2 with lines title "Spline integral",\
			"$<" index 4 using 1:2 with lines title "Spline 2nd deriv"\
	' | gnuplot

plots/plot.quarticSubSpline.svg : data/out.quarticData.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key top; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  set title "Quartic Sub-spline"; \
		  f(x) = sin(x); \
		  plot \
			f(x) title "sin(x)",\
		  	"$<" index 0 using 1:2 with points pointtype 7 title "Sample",\
			"$<" index 0 using 1:3 with points pointtype 1 title "Sample deriv",\
		  	"$<" index 1 using 1:2 with lines title "Quartic sub-spline",\
			"$<" index 2 using 1:2 with lines title "Spline deriv",\
			"$<" index 3 using 1:2 with lines title "Spline 2nd deriv"\
	' | gnuplot

main : main.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o $@ $^

$(OBJECT_DIR)/%.o : $(SOURCE_DIR)/%.cc | $(OBJECT_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJECT_DIR):
	mkdir -p $@

clean:
	$(RM) [Oo]ut*.txt main *.svg *.png $(OBJS) *.o
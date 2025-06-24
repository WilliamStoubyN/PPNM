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
all: Out.txt out.cubicSubSpline.txt plot.cubicSubSpline.svg

Out.txt : main
	./$< --task 0 > $@

out.cubicSubSpline.txt : main
	./$< --task 1 > $@

plot.cubicSubSpline.svg : out.cubicSubSpline.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key bottom; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  f(x) = sin(x) ; \
		  plot \
			f(x) title "sin(x)",\
		  	"$<" index 0 using 1:2 with points pointtype 7 title "Sample points",\
			"$<" index 0 using 1:3 with points pointtype 1 title "Sample derivative",\
		  	"$<" index 1 using 1:2 with lines title "Cubic sub-spline",\
			"$<" index 2 using 1:2 with lines title "Spline derivative",\
			"$<" index 3 using 1:2 with lines title "Spline integral",\
			"$<" index 4 using 1:2 with lines title "Spline double deriv"\
	' | gnuplot


main : main.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o $@ $^

$(OBJECT_DIR)/%.o : $(SOURCE_DIR)/%.cc | $(OBJECT_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJECT_DIR):
	mkdir -p $@

clean:
	$(RM) [Oo]ut*.txt main *.svg *.png $(OBJS) *.o
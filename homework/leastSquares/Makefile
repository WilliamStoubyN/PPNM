CXXFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter -std=c++23 -O2
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"

SOURCE_DIR := ../source
OBJECT_DIR := ../object
INCLUDE_DIR := ../include

INCS = $(INCLUDE_DIR)/vector.h $(INCLUDE_DIR)/matrix.h lsfit.h ../linearEquations/qrsolver.h

SRCS = $(INCS:$(INCLUDE_DIR)/%.h=$(SOURCE_DIR)/%.cc)
SRCS := $(SRCS:.h=.cc)

OBJS := $(INCS:$(INCLUDE_DIR)/%.h=$(OBJECT_DIR)/%.o)
OBJS := $(OBJS:.h=.o)

.PHONY: all clean
all: Out.txt plot.fit.svg

Out.txt : main
	./$< > $@

main : main.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o $@ $^

plot.fit.svg : Out.txt Makefile
	echo 'set terminal svg background "white"; \
			set output "$@"; \
			set key right; \
			set xlabel "Time (day)"; \
			set ylabel "Activity (counts)"; \
			l = 0.170624; \
			a = 4.95866; \
			f(x) = exp(-l * x + a); \
			plot \
				"$<" index 0 with yerrorbars title "datapoints",\
				f(x) title sprintf("F_c = exp(-0.170624 * x + 4.95866)")\
		' | gnuplot

#Create all object files from their corresponding .cc file. Also check if the object folder even exists
$(OBJECT_DIR)/%.o : $(SOURCE_DIR)/%.cc | $(OBJECT_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

#If the object directory does not exist, create it.
$(OBJECT_DIR):
	mkdir -p $@

clean:
	$(RM) [Oo]ut*.txt main *.png *.svg *.log $(OBJS) *.o
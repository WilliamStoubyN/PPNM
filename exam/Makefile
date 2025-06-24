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
all: Out.txt 

Out.txt : main
	./$< -n 0 > $@

out.cubicSubSpline.txt : main
	./$< -n 1 > $@

main : main.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o $@ $^

$(OBJECT_DIR)/%.o : $(SOURCE_DIR)/%.cc | $(OBJECT_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJECT_DIR):
	mkdir -p $@

clean:
	$(RM) [Oo]ut*.txt main *.svg *.png $(OBJS) *.o
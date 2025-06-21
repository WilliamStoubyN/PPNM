CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2 -Wno-maybe-uninitialized
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"

SOURCE_DIR := ../source
OBJECT_DIR := ../object
INCLUDE_DIR := ../include

INCS = $(INCLUDE_DIR)/vector.h $(INCLUDE_DIR)/matrix.h qrsolver.h

SRCS = $(INCS:$(INCLUDE_DIR)/%.h=$(SOURCE_DIR)/%.cc)
SRCS := $(SRCS:.h=.cc)

OBJS := $(INCS:$(INCLUDE_DIR)/%.h=$(OBJECT_DIR)/%.o)
OBJS := $(OBJS:.h=.o)

.PHONY: all clean
all: Out.txt

Out.txt : main
	./$< -n 4 -m 4 > $@

main : main.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o $@ $^

#Create all object files from their corresponding .cc file. Also check if the obj folder even exists
$(OBJECT_DIR)/%.o : $(SOURCE_DIR)/%.cc | $(OBJECT_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

#If the obj directory does not exist, create it.
$(OBJECT_DIR):
	mkdir -p $@

matrix_test : matrix_test.o $(OBJS)
vector_test : vector_test.o ../include/vector.h

clean:
	$(RM) [Oo]ut*.txt main vector_test matrix_test $(OBJS) *.o
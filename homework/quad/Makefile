CXXFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter -std=c++23 -O2
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"

SOURCE_DIR := ../source
OBJECT_DIR := ../object
INCLUDE_DIR := ../include

INCS = $(INCLUDE_DIR)/vector.h $(INCLUDE_DIR)/matrix.h quad.h

SRCS = $(INCS:$(INCLUDE_DIR)/%.h=$(SOURCE_DIR)/%.cc)
SRCS := $(SRCS:.h=.cc)

OBJS := $(INCS:$(INCLUDE_DIR)/%.h=$(OBJECT_DIR)/%.o)
OBJS := $(OBJS:.h=.o)

.PHONY: all clean
all: Out.txt

Out.txt : main
	./$< > $@

main : main.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o $@ $^

#Create all object files from their corresponding .cc file. Also check if the object folder even exists
$(OBJECT_DIR)/%.o : $(SOURCE_DIR)/%.cc | $(OBJECT_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

#If the object directory does not exist, create it.
$(OBJECT_DIR):
	mkdir -p $@

clean:
	$(RM) [Oo]ut*.txt main *.svg *.png $(OBJS) *.o
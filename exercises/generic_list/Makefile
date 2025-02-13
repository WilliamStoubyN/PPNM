CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS += -lstdc++ -lm
.PHONEY : all
all : Out.txt

Out.txt : main
	./main > $@

main : main.o genlist.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o main $^

main.o : main.cc
	$(CXX) $(CXXFLAGS) -c -o main.o main.cc

.PHONEY : clean
clean:
	$(RM) [Oo]ut.txt *.o main

test:
	@echo $(RM)
	@echo $(CXX)


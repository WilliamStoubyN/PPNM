CXXFLAGS += -Wall -Werror -Wextra -std=c++23
LDLIBS += -lstdc++ -lm
CSLIBS = -reference:System.Numerics.dll
CODE = $(filter %.cs,$^)
DLLS = $(addprefix -reference:,$(filter %.dll,$^))	#Picks all dlls from line of prerequisites and prepend them with --reference
MKEXE = mcs -target:exe -out:$@ $(CSLIBS) $(DLLS) $(CODE)
MKLIB = mcs -target:library -out:$@ $(CSLIBS) $(DLLS) $(CODE)

#In C#
# Out.txt : main.exe ; mono $< > $@
# main.exe : main.cs ; $(MKEXE)

#In C++
Out.txt : main.exe main
	./$< >> $@
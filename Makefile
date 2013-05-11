
project := fixpoint
sourcedir := sources
includedir := includes
builddir := .build

CXXFLAGS += -I$(includedir) -MMD -MP -O3 -g -std=c++11 -Wall -Wextra -Werror -Wa,-a
LDFLAGS +=
MKDIR := mkdir -p

sources := $(wildcard $(sourcedir)/*.cpp)
dependencies := $(patsubst $(sourcedir)/%.cpp, $(builddir)/%.d, $(sources))
objects := $(patsubst $(sourcedir)/%.cpp, $(builddir)/%.o, $(sources))

default: $(project)

.PHONY: clean
clean:
	-$(RM) $(project) $(objects) $(dependencies)

$(project): $(objects)
	$(CXX) $(LDFLAGS) -o $@ $^

$(builddir)/%.o: $(sourcedir)/%.cpp
	@$(MKDIR) $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ -c $< >$(basename $@).l

$(objects): Makefile

Remram-happy:
	@echo "(\ /)"
	@echo "( . .)"
	@echo "(\")(\")"

-include $(dependencies)

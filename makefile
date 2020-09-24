.DEFAULT_GOAL := all
MAKEFLAGS     += --no-builtin-rules
SHELL         := bash

ASTYLE        := astyle
CHECKTESTDATA := checktestdata
CPPCHECK      := cppcheck
DOXYGEN       := doxygen
VALGRIND      := valgrind

ifeq ($(shell uname -s), Darwin)
    BOOST    := /usr/local/include/boost
    CXX      := g++-10
    CXXFLAGS := --coverage -pedantic -std=c++17 -O3 -I/usr/local/include -Wall -Wextra
    GCOV     := gcov-10
    GTEST    := /usr/local/include/gtest
    LDFLAGS  := -lgtest -lgtest_main
else ifeq ($(shell uname -p), unknown)
    BOOST    := /usr/include/boost
    CXX      := g++
    CXXFLAGS := --coverage -pedantic -std=c++17 -O3 -Wall -Wextra
    GCOV     := gcov
    GTEST    := /usr/include/gtest
    LDFLAGS  := -lgtest -lgtest_main -pthread
else
    BOOST    := /usr/include/boost
    CXX      := g++-9
    CXXFLAGS := --coverage -pedantic -std=c++17 -O3 -Wall -Wextra
    GCOV     := gcov-9
    GTEST    := /usr/local/include/gtest
    LDFLAGS  := -lgtest -lgtest_main -pthread
endif

# run docker
docker:
	docker run -it -v $(PWD):/usr/gcc -w /usr/gcc gpdowning/gcc

# get git config
config:
	git config -l

# get git log
Voting.log:
	git log > Voting.log

# get git status
status:
	make clean
	@echo
	git branch
	git remote -v
	git status

# download files from the Collatz code repo
pull:
	make clean
	@echo
	git pull
	git status

# upload files to the Collatz code repo
push:
	make clean
	@echo
	git add .gitignore
	git add .gitlab-ci.yml
	git add Voting.cpp
	git add Voting.hpp
	-git add Voting.log
	-git add html
	git add makefile
	git add README.md
	git add RunVoting.cpp
	git add RunVoting.ctd
	git add RunVoting.in
	git add RunVoting.out
	git add TestVoting.cpp
	git commit -m "Final Commit, only updated README with commit sha" -m "Closes #10"
	# git commit -m "Created first unit Voting.cpp" -m "Closes #11, #2"
	git push
	git status

# compile run harness
RunVoting: Voting.hpp Voting.cpp RunVoting.cpp
	-$(CPPCHECK) Voting.cpp
	-$(CPPCHECK) RunVoting.cpp
	$(CXX) $(CXXFLAGS) Voting.cpp RunVoting.cpp -o RunVoting

# compile test harness
TestVoting: Voting.hpp Voting.cpp TestVoting.cpp
	-$(CPPCHECK) Voting.cpp
	-$(CPPCHECK) TestVoting.cpp
	$(CXX) $(CXXFLAGS) Voting.cpp TestVoting.cpp -o TestVoting $(LDFLAGS)

# run/test files, compile with make all
FILES :=                                  \
    RunVoting                            \
    TestVoting

# compile all
all: $(FILES)

# check integrity of input file - When I want to check my data, replace RunVoting.in with jNav56-RunVoting.in
ctd-check:
	$(CHECKTESTDATA) RunVoting.ctd RunVoting.in

# generate a random input file
ctd-generate:
	$(CHECKTESTDATA) -g RunVoting.ctd RunVoting.tmp

# execute run harness and diff with expected output
run: ctd-check RunVoting
	./RunVoting < RunVoting.in > RunVoting.tmp
	-diff RunVoting.tmp RunVoting.out

# execute test harness
test: TestVoting
	$(VALGRIND) ./TestVoting
	$(GCOV) Voting.cpp | grep -B 2 "cpp.gcov"

# clone the Voting test repo, first fork the original repo, clone your fork and then you can do merge request
voting-tests:
	git clone https://gitlab.com/jNav56/cs371p-voting-tests.git voting-tests
	# https://gitlab.com/gpdowning/cs371p-voting-tests.git voting-tests

# test files in the Voting test repo
TFILES := `ls voting-tests/*.in`

# execute run harness against a test in Voting test repo and diff with expected output
voting-tests/%: RunVoting
	./RunVoting < $@.in > RunVoting.tmp
	-diff RunVoting.tmp $@.out

# execute run harness against all tests in Voting test repo and diff with expected output
tests: voting-tests RunVoting
	-for v in $(TFILES); do make $${v/.in/}; done

# auto format the code
format:
	$(ASTYLE) Voting.cpp
	$(ASTYLE) Voting.hpp
	$(ASTYLE) RunVoting.cpp
	$(ASTYLE) TestVoting.cpp

# you must edit Doxyfile and
# set EXTRACT_ALL     to YES
# set EXTRACT_PRIVATE to YES
# set EXTRACT_STATIC  to YES
# create Doxfile
Doxyfile:
	$(DOXYGEN) -g

# create html directory
html: Doxyfile Voting.hpp
	$(DOXYGEN) Doxyfile

# check files, check their existence with make check
CFILES :=                                 \
    .gitignore                            \
    .gitlab-ci.yml                        \
    Voting.log                           \
    html								\
	voting-tests/jNav56-RunVoting  \
	voting-tests/jNav56-RunVoting

# uncomment the following line once you've pushed your test files
# you must replace GitLabID with your GitLabID
#    voting-tests/GitLabID-RunVoting.in  \
#    voting-tests/GitLabID-RunVoting.out

# check the existence of check files
check: $(CFILES)

# remove executables and temporary files
clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f *.plist
	rm -f *.tmp
	rm -f RunVoting
	rm -f TestVoting

# remove executables, temporary files, and generated files
scrub:
	make clean
	rm -f  Voting.log
	rm -f  Doxyfile
	rm -rf voting-tests
	rm -rf html
	rm -rf latex

# output versions of all tools
versions:
	@echo "% shell uname -p"
	@echo  $(shell uname -p)
	@echo
	@echo "% shell uname -s"
	@echo  $(shell uname -s)
	@echo
	@echo "% which $(ASTYLE)"
	@which $(ASTYLE)
	@echo
	@echo "% $(ASTYLE) --version"
	@$(ASTYLE) --version
	@echo
	@echo "% grep \"#define BOOST_LIB_VERSION \" $(BOOST)/version.hpp"
	@grep "#define BOOST_LIB_VERSION " $(BOOST)/version.hpp
	@echo
	@echo "% which $(CHECKTESTDATA)"
	@which $(CHECKTESTDATA)
	@echo
	@echo "% $(CHECKTESTDATA) --version"
	@$(CHECKTESTDATA) --version
	@echo
	@echo "% which $(CXX)"
	@which $(CXX)
	@echo
	@echo "% $(CXX) --version"
	@$(CXX) --version
	@echo "% which $(CPPCHECK)"
	@which $(CPPCHECK)
	@echo
	@echo "% $(CPPCHECK) --version"
	@$(CPPCHECK) --version
	@echo
	@$(CXX) --version
	@echo "% which $(DOXYGEN)"
	@which $(DOXYGEN)
	@echo
	@echo "% $(DOXYGEN) --version"
	@$(DOXYGEN) --version
	@echo
	@echo "% which $(GCOV)"
	@which $(GCOV)
	@echo
	@echo "% $(GCOV) --version"
	@$(GCOV) --version
	@echo
	@echo "% cat $(GTEST)/README"
	@cat $(GTEST)/README
ifneq ($(shell uname -s), Darwin)
	@echo
	@echo "% which $(VALGRIND)"
	@which $(VALGRIND)
	@echo
	@echo "% $(VALGRIND) --version"
	@$(VALGRIND) --version
endif
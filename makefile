#makefile for lab 4 pass off cases
NUM:=4
buckets:=80 100
numbers_80:=0 1 2 3 4 5 6 7
numbers_100:=1 2 3 5 6 7 8
tests:=Project$(NUM)PassOffCases
project:=Datalog Parser

.SILENT: all $(buckets)

all: $(buckets)
	@rm $(tests)/out.txt

$(buckets):
	echo "Bucket $@"; \
	for number in ${numbers_$@} ; \
	do \
		echo "Running input $$number" ; \
		./project$(NUM) $(tests)/$(NUM)-$@/input$$number.txt > $(tests)/out.txt ; \
		diff -w $(tests)/$(NUM)-$@/answer$$number.txt $(tests)/out.txt || (echo "diff failed on test $$number \n") ; \
	done \

compile:
	g++ -Wall -Werror -std=c++17 -g *.cpp -o project$(NUM)

theirs: compile
	make

quick:
	g++ *.cpp -o project$(NUM)

mine: quick
	make
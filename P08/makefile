#
# makefile to compile all programs for the AED.P08 computer lab class
#

clean:
	rm -f a.out
	rm -f binary_search
	rm -f count_words
	rm -f primes

.PHONY:		all
all:		binary_search count_words primes

binary_search:	binary_search.c
	cc -Wall -g binary_search.c -o binary_search

count_words:	count_words.c
	cc -Wall -g -O2 count_words.c -o count_words

primes:		primes.c
	cc -Wall -g -O2 primes.c -o primes

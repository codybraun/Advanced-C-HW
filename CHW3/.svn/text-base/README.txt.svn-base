Cody Braun
HW 3

p1.) Hey hey- so p1 runs pretty well, I think it's 
fairly straightforward. I'm compilling with list (just "gcc p1.c 
list.c -op1" is what I've been doing). Read is little funky about 
segfaulting on any kind of weird formatting, but it works fine with 
dict.txt and files where the formatting is just right. 

I started with several pretty bad prehashing functions- I probably 
should have tried folding some bytes of string together, but I was 
interested to see how these four would work out and I didn't want to 
change too many variables. I struck with the simple provided mod 
function for hashing. The functions that performed best were the 
bit-shift functions, which makes a lot of sense. That fourth one 
acheives some of the benefits of middle-squared method, as it uses 
the middle digits of a string to hash rather than the end or 
beginning digits, which wouldn't get as good a range. Also, bit 
shifting is quick obviously.

I included a test function, which you can use by just typing "test" 
followed by a number of random strings to insert and search for. (oh 
yeah I grabbed that random string code from somebody else, cited in 
the comments). Anyway, on the bit shift prehashing functions, insert 
operations seem to track pretty well with logn as n gets massive. 
There might be something up with how I'm inserting, that looks 
closer to linear even when I adjust the initial hash table size 
(which I have super small) and the load factor max and min (LFMAX 
and LFMIN). That might actually have to do with the previously 
mentioned mediocrity of my prehashing functions actually. Oh yeah, 
and you can keep track of LF and rehashes in the p1log.txt file. 

p2.) Again, occasional weird input parsing issues, but read should 
be okay. "Check" will verify RB tree properties, which usually 
remain intact. Again, "Test n" will insert n random strings and 
perform n random searches. The log file at p2log.txt tracks height, 
which appears to stay within the correct bounds of an RB tree while 
doing any number of insertions. Delete was giving me problems until 
like 5 minutes ago; I think it works now, but I wouldn't like be 
astonished if it breaks. 


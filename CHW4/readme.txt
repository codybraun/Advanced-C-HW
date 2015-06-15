Cody Braun
HW 4

p1.) I'm just compiling p1a and p1a with -fopenmp. I'm using an adjacency matrix, which makes both p1a and p1b way slower than if I'd gone with a linked list, but it also made this very simple to paralellize. 

The interface on both is just "read FILE" to read in a test graph and run all-source Dijkstra on it, "print FILE" to read in a graph and print the all-source shortest paths, or "single FILE" to run single-shortest path from 0. 
Obviously. that's a huge matrix, so I've been running "print" using a very small file, t1.txt, to make sure this is returning shortest paths.

I think something is slightly off with my timing, I'm not getting super reliable results even running p1a and p1b on the same graph. Except on very small graphs, p1b is always faster, but sometimes it's only a factor of 1.5 and sometimes it's like 8. 
I'm hoping I just have a minor issue with how I'm returning the start and end times or something.

Oh also, since the headers on the two test graphs weren't the same and I wasn't really sure what format to expect, my read function just expects an integer on the first line (the nubmer of vertices) and edges on the remaining lines. 
Should be a minor tweak to any test files you guys use, but otherwise, it will totally seg fault. All .txt graphs in my folder should work.

p2.) I got way more of a boost from parallelizing Dijkstras than I expected- running all-source on one of the big graphs with this takes about 1/10 of the time that p1b takes, which in turn is a bit faster than p1a. 
Basically, I'm just giving each thread an equal chunk of the adjacency matrix and keeping track of a local minimum distance in each thread and global minimum for all threads. Here's my psuedocode:

PARALLEL-DIJKSTRAS (G, w , s)

for all vertices in V
	v.dist = max_int
	v.done = 0
	
s.dist = 0
s.done = 1

i = s

parallel region (local: j, firstV, lastV, localClosest, localClosestValue global: i, dist, done, weights, edges, globalClosest, globalClosestValue, k)

//weights and edges are both n x n matrices, so it is easy to divide up the search for cheaper paths leaving i

firstV = thread number * vertex count / number of threads
lastV = thread number+1 * vertex count / number of threads -1

for k = 0 to V	//run V times, we'll connect one vertex every pass through
	localClosestValue = int max	//maintain the current vertex that is looking like it will be next added to S. Need to keep a local in each thread and compare at the end.
	for j = firstV to lastV
		relax edge from i to j	//relax all the edges from i within each thread's chunk of the adj matrix
		if j.dist < localClosestValue 
			localClosest = j
			localClosestValue = j.dist
				Critical region //because can't have multiple threads updating the global closest value at the same time 
				if globalClosestValue > localClosestValue
					globalClosestValue = localClosestValue
					globalClosest = j	//keep track of the closest unconnected vertex across all regions, we'll want to connect it next
	i = globalClosest					


			


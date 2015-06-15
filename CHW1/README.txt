CODY BRAUN

HW 2



So I hadn't worked with C before starting this class, so I apologize for general ugliness.



p1.) Okay, I sort of ran out of time on this, but it compiles okay and runs on the Linux computers for me. It sometimes seg faults on my desktop, probably because of one of the massive unresolved memory leaks. Hopefully it works okay for you. Everything is included in p1.c: search1, which is the first method, search2 and search3, which build the structs needed for the second and third method, and searcher2Find and searcher3Find, which return arrays of integers using those structs.



It's hard to test this with the big arrays and see if I'm returning the right number regularly, but it at least gets close except in weird cases and it should still illustrate the runtimes of these three methods fairly accurately. Method one consistently has the longest runtime, as it increases with the size of the entire data set. This is because we're eventually making k binary searches among ALL those points. Method two runs most quickly, as it only ever requires a single binary search. The searchStruct takes some time to initialize and is huge, so though the runtime increases less quickly as k*n grows, the constant will be fairly large. So this method makes sense if a lot of searches must be made on some pool of data, but for a few searches method one beats it. Method three sacrifices some of this performance, and in my tests the runtime is closer to that of method one. However, the total size of the pointers is much smaller, upperbounded by k*n*2 I think, whereas method 2 may require k*k*n storage space for the unionized array. 



Method 1: Worst runtime O(klog(n)), no additional storage space

Method 2: Best runtime, seems like O(log(kn)), requires O(k*k*n) space

Method 3: Better runtime than 1, worse than 2, I think O(k) maybe. Requires O(kn) space



p2.) Everything is in p2.c, seems to run fine and handle most input errors in sensible fashion



p3.) All in p3.c. BSTCheckA and BSTCheckB are the non-recursive and recursive functions respectively and I've got a helper function to id proper ranges for subtrees. I've included small test trees in the main.

README file for ordered lists:
=============================


README - general information
-------------------------------
A linked list is a sequence of data structures, which are connected together
via links. Linked list is the second most-used data structure after array.
    An ordered list is a data structure designed for storing information sorted.

The package includes 3 products:
1. Ordered linked list which provides "Quick Pop" functionality. 
   * complexities: Push: O(n) 
   				    Pop:  O(1)
   * support thread safe functionality.
  
2. Ordered linked list which provides "Quick Push" functionality .
   * complexities: Push: O(1)
   				    Pop:  O(n)
   * support thread safe functionality.
    
3. Test file which provides:
   * basic functionality test of both lists.
   * multi threads enviroment testing.
   * efficiency testing of each function.


INSTALL
-------------------------
1. How to install the release version and run?
   run from linux command line (from list package directory):
  $ make clean
  $ make release

2. How to install the debug version and run via Valgrind?
   run from linux command line (from list package directory):
  $ make clean
  $ make vlg

3. How to install the debug version and run?
   run from linux command line (from list package directory):
  $ make clean
  $ make debug


Notes
-------------------------
* There are 2 test functions in the test file which exist to demonstrate the 
  inefficiency of the O(n) functions: 
                               DemonstrateSlowPop() & DemonstrateSlowPush().
  	My advice is to NOT run that tests via valgrind.
  Anyway, I assumed you would not reach this line so I "comment" the "heaviest"
  test among them (moreover, I reduced the size of the list being tested).

* Both lists get: T       - type
                  COMPARE - functor with const compare function,
                            i.e, ovverride: bool operator() const.
                            ** the default COMPARE compares between numbers.
                               (same as std::less)


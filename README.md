This is a nice exercize of containers and iterators.


My container, which called "MyContainer" (His parents got inspired) has 6 different iterators:

Ordinary iterator - which goes from the begining to the end. Not very interesting.

Reverse iterator - exactly like the ordinary, but up-side-down. Begin in the end, end in the begining, and goes all the way between fron the right to the left.

Middle-out iterator - starts in the middle, then jump to the left, the jump twice to the right, etc.

Ascending iterator - goes according to the size of the elements. It uses the ordinary iterator, but work on a sorted array.

Descending iterator - something between reverse and ascending. Uses the reverse iterator on the sorted array.

Side-cross iterator - similar to middle-out, but opposite and sorted: First the smallest element, then the gratest, then the almost-smallest, etc. Uses a different vector, which sorted according to that logic, and goes on this vector with the ordinary iterator.



The demo file runs all the iterator on the array {7,15,6,1,2}. Should be ran with `make main`.

Test file, which test the project, all the iterators with many types of elements, should be ran with `make test`.

`make clean` will clean the run files, and `make valgrind` will run valgrind on test and main:)



The test file and doctest.h both in the folder tests, and the container and it's iterators are in the folder container.




good luck, *may the force be with you:)*

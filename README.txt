----------------------------
MAPPER, REDUCER AND COMBINER
----------------------------
Author: Aswin Pranav Sankar, UFID 19119174, apsankar@ufl.edu

Usage: 

a)make
Above is for compiling all 3 C files into their respective object files.

b) ./combiner <i/p file for mapper>
The combiner takes one command line argument- the input file for which word
count must be done. The input file should have one word every line.

Example: ./combiner file1.txt 

------
MAPPER
------
The mapper takes one command-line argument: it's input file. Until the EOF is
reached, the mapper tokenizes the input stream into words based on the "\n"
delimited, and simply outputs them immediately to the screen in the form of
(word,1).

-------
REDUCER
-------
The reducer takes inputs from STDIN, until the EOF is reached. We know that 
the inputs are of the form (word,1). Therefore, using multiple string 
tokenizers, we break the inputs into their words alone. We used a singly
linked list to keep track of words. Each node in the list has a character
array, a count value, and a pointer to the next element (if any).

When we search for an element, we have 3 cases:
1) The head of the list is NULL. This means that the list is empty. We 
simply insert our word string and initialize count here, and move to the 
next word.

2) The head is not NULL, and the first characters of the head node and the
input string match. In this case, we have to search all nodes in the list 
to see if there's a match between the input string and the stored strings.
If there is a match, we increment count at that node, while also setting a
flag variable. This set flag means that a match has been found. If the flag
is 0, this means we have reached the end of the list without a match; hence,
we create a new node, link it to the last node of the list, and copy over the
input string and initialize count to 1.

3)The head is not NULL, and the first characters of the head node and the
input string DO NOT match. This means that a new alphabet has been reached;
hence, we need to print out the nodes of the list to STDOUT, free the entire
list, and start over from an empty list. To this empty list, we add the new
input string and initialize count to 1.

After the EOF has been reached, we have to print out any remaining node in
the list, and then free it to reclaim memory.

--------
COMBINER
--------
The combiner is tasked with spawning the mapper process and reducer process,
and piping the mapper output to the reducer input. This is achieved by use
of the fork(), execlp(), pipe() and dup2() functions. A pipe(pipefd[2] is first
created in the parent process. The two functions run_mapper and run_reducer are 
responsible for spawning the child processes.

For run_mapper, we first duplicate pipefd[1] to STDOUT, before calling execlp()
on the mapper program. Therefore the output of the mapper will be redirected to
the created pipe. For run_reducer we duplicate pipefd[0] to STDIN. The input
for the reducer will be the output of the mapper. The reducer prints its output
to the terminal.

The parent process waits on the status of the child processes. As soon as status
changes to -1, the parent process exits.
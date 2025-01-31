---
title: CS 537 Project 1
layout: default
---

# CS537 Spring 2025, Project 1

## Updates
* TBD

## Submitting your work
- Run `submission.sh` 
- Download generated p1.tar file
- Upload it to Canvas
  * Links to Canvas assignment: 
  * [Prof. Mike Swift's class](https://canvas.wisc.edu/courses/434150/assignments/2619915)
  * [Prof. Ali Abedi's class](https://canvas.wisc.edu/courses/434155/assignments/2622055)

## Administrivia 
- **Due Date** by January 30, 2025 at 11:59 PM
- Questions: We will be using Piazza for all questions.
- Collaboration: The assignment has to be done by yourself. Copying code (from others) is considered cheating. [Read this](http://pages.cs.wisc.edu/~remzi/Classes/537/Spring2018/dontcheat.html) for more info on what is OK and what is not. Please help us all have a good semester by not doing this.
- This project is to be done on the [lab machines](https://csl.cs.wisc.edu/docs/csl/2012-08-16-instructional-facilities/), so you can learn more about programming in C on a typical UNIX-based platform (Linux).
- A few sample tests are provided in the project repository. To run them, execute `run-tests.sh` in the `tests/` directory. Try `run-tests.sh -h` to learn more about the testing script. Note these test cases are not complete, and you are encouraged to create more on your own.
- **Slip Days**: 
  - In case you need extra time on projects, you each will have 2 slip days for the first 3 projects and 2 more for the final three. After the due date we will make a copy of the handin directory for on time grading. 
  - To use a slip days or turn in your assignment late you will submit your files with an additional file that contains **only a single digit number**, which is the number of days late your assignment is (e.g. 1, 2, 3). Each consecutive day we will make a copy of any directories which contain one of these `slipdays.txt` files. 
  - `slipdays.txt` must be present at **the top-level directory** of your submission. 
  - Example project directory structure. (some files are omitted)
  ```
  p1/
  ├─ solution/
  │  ├─ README.md
  │  ├─ sortk.c
  │  ├─ Makefile
  ├─ tests/
  ├─ README.md
  ├─ slipdays.txt
  ```
  - We will track your slip days and late submissions from project to project and begin to deduct percentages after you have used up your slip days.
  - After using up your slip days you can get up to 80% if turned in 1 day late, 60% for 2 days late, and 40% for 3 days late, but for any single assignment we won't accept submissions after the third days without an exception. This means if you use both of your individual slip days on a single assignment you can only submit that assignment one additional day late for a total of 3 days late with a 20% deduction.
  - Any exception will need to be requested from the instructors.

  - Example of `slipdays.txt`:

```sh
$ cat slipdays.txt
1
```

## Sort-k
In this assignment, you will write a command line program that sorts sentences by k-th word.

Learning Objectives:

* Re-familiarize yourself with the C programming language
* Familiarize yourself with a shell / terminal / command-line of Linux
* Learn about file I/O, string processing, and simple data structures in C

Summary of what gets turned in:
* One `.c` file: `sortk.c`
* It is mandatory to compile your code with following flags `-O2 -Wall -Wextra -Werror -pedantic -o sortk`.
    * Check `man gcc` and search for these flags to understand what they do and why you will like them.
    * It is a good idea to create a `Makefile` so you just type `make` for the compilation.
    * We are trying to use the most recent version of the C language. However, the compiler (`gcc` on lab machines) does not support final C23 specification, which is the most recent one. So we are using the second most recent (C17).
    * `-std=c17` is not required. 
* It should (hopefully) pass the tests we supply. 
* Include a single `README.md` inside `solution` directory describing the implementation. This file should include your name, your cs login, you wisc ID and email, and the status of your implementation. If it all works then just say that. If there are things you know doesn't work let me know.

* Use `submission.sh` to make a project archive and upload this file to Canvas. Check printed message if you are including `slipdays.txt`. 

__Before beginning__: Read this [lab tutorial](http://pages.cs.wisc.edu/~remzi/OSTEP/lab-tutorial.pdf); it has some useful tips for programming in the C environment.

## Sort-k
The program you will build is called `sortk`. It takes two command line arguments -- a file with list of sentences and integer k. 

k is in the range of 4 byte signed integer[-2^31, 2^31-1].

Then, it prints the sorted result to STDOUT.

Here is what it looks like to run the program:

```bash
$ ./sortk input.txt 7
```

`sortk` will sort sentences by k-th word (1-indexed) in each sentence. 
If a sentence does not have a k-th word, it should be placed at the end of the sorted list.

If there is a tie, they are sorted lexicographically word-by-word, starting from the 1st word, then the 2nd word, and so on.

Among sentences with fewer than k words, their relative order is determined by lexicographical comparison of their words, starting from the 1st word.

Sorting will be based on lexicographical order.
**Sentences only contain lowercase alphabet letters and whitespaces(0x20).**
You do not need to achieve a specific time complexity.

### Sample Results 1
input.txt:
```
sing o goddess the anger of achilles son of peleus that brought countless ills upon the achaeans
many a brave soul did it send hurrying down to hades
many a hero did it yield a prey to dogs and vultures
for so were the counsels of jove fulfilled from the day on which the son of atreus king of men
and great achilles first fell out with one another
and which of the gods was it that set them on to quarrel
```

command:
```bash
$ ./sortk input.txt 1
```

result to STDOUT:
```
and great achilles first fell out with one another
and which of the gods was it that set them on to quarrel 
for so were the counsels of jove fulfilled from the day on which the son of atreus king of men 
many a brave soul did it send hurrying down to Hades
many a hero did it yield a prey to dogs and vultures
sing o goddess the anger of achilles son of peleus that brought countless ills upon the achaeans

```

When printing the output, every printed sentences should have newline character at the end. 

Please look given testcases for more examples.

## File formats
Here is the sample `input.txt`. 

```
$ cat input.txt
sing o goddess the anger of achilles son of peleus that brought countless ills upon the achaeans
many a brave soul did it send hurrying down to hades
many a hero did it yield a prey to dogs and vultures
for so were the counsels of jove fulfilled from the day on which the son of atreus king of men 
and great achilles first fell out with one another
and which of the gods was it that set them on to quarrel 
```

* Sentences are separted by `\n`. 
* **Sentences only contain lowercase alphabet letters and whitespaces(0x20).**
* There will not be any empty string (No empty input file, No consecutive `\n`). 
* You must not assume a maximum limit to the number of words, number of sentences, number of characters in a sentence.
* There will not be any trailing spaces at the end of the sentences.


## Possible outputs
- If k is not an integer, exit with return code 1.
- If k is less or equal to zero, exit with return code 1.
- All other errors (wrong number of arguments, open file failed, etc.) should exit with code 1.

## Tips
- When working with any C library functions, check their manual page (`man`) for a description and proper usage, e.g. `man 3 fopen`.
- To work with files, look at `man 3 fopen` and `man 3 fclose`.
- To read data from files, consider using `getline(3)`, `fgets(3)`, or maybe `scanf(3)`.
- Printing to the terminal can be done with `printf(3)`.
- You don't know the number of sentences, words, and charcters ahead of time, so you will need to dynamically allocate memory.
- To sort an array of data, you can use `qsort(3)`. Also, you can implement your own way to sort.

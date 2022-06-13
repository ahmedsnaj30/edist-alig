# DNA-Alignment
Program to compute the optimal sequence alignment of DNA strings using dynamic programming and matrices.

Calculated the edit distance between 2 genetic sequence stringsto measure the similarity. Created "EDistance" class to compare 2 strings and calculate the different penalties for aligning eachother:
```
0 --> If the characters were the same
1 --> If the characters were different
2 --> If a character matched with a blank
```
Also calculated the optimal distance using the Matrix class, and printed a table of the aligned DNA strings by tracing the matrix and printing the actual alignment.\

Commands:\
```
make
./EDistance < example10.txt
```
Printing the matrix table, alignment table, and execution time using SFML Time library:

![ps5](https://user-images.githubusercontent.com/70961105/173461938-ce245364-c2c0-49be-953a-ae1ea60e9555.png)

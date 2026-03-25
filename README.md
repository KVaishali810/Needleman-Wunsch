# Needleman-Wunsch Global Alignment

A C implementation of the Needleman-Wunsch dynamic programming
algorithm for global pairwise sequence alignment.

## Algorithm
- Scoring: match +1, mismatch -1, gap -2
- Phase 1: Initialize DP matrix with gap penalties
- Phase 2: Fill matrix using optimal substructure
- Phase 3: Traceback to reconstruct alignment

## How to compile
gcc nw_alignment.c -o nw_alignment

## How to run
./nw_alignment

## Example
Input  : GATTACA / GTCA
Output :
Seq1 : GATTACA
Mtch :    ..||
Seq2 : ---GTCA
Score: 0

## Concepts used
- 2D arrays and dynamic programming in C
- Nested loops for matrix filling
- Traceback for alignment reconstruction
- Code reuse across projects

## Author
K Vaishali
MSc Bioinformatics

#include <stdio.h>

int b[5001]={0,0,2,3,3,3,5,3,3,5,3,3,5,3,5,7,3,3,5,7,3,5,3,3,5,3,5,7,3,5,7,3,3,5,7,3,5,3,3,5,7,3,5,3,5,7,3,5,7,19,3,5,3,3,5,3,3,5,3,5,7,13,11,13,19,3,5,3,5,7,3,3,5,7,11,11,3,3,5,7,3,5,7,3,5,3,5,7,3,5,7,3,3,5,7,11,11,3,3,5,3,3,5,7,11,11,13,3,5,7,23,11,13,3,5,3,3,5,3,5,7,3,3,5,7,11,11,3,5,7,3,5,7,3,5,7,3,3,5,7,3,5,3,3,5,7,11,11,3,5,7,19,11,13,31,3,5,3,3,5,3,5,7,13,11,13,19,3,5,7,3,5,7,29,11,3,3,5,3,5,7,3,5,7,19,3,5,7,3,5,7,3,5,3,5,7,3,5,7,19,3,5,3,5,7,13,3,5,7,17,11,3,3,5,7,11,11,3,3,5,7,3,5,3,5,7,3,5,7,19,3,5,3,3,5,3,5,7,13,11,13,3,5,7,31,3,5,3,5,7,13,3,5,3,5,7,3,5,7,19,11,13,3,3,5,7,11,11,13,17,17,19,3,5,7,3,5,7,47,11,3,5,7,3,5,7,3,3,5,7,3,5,7,17,11,3,5,7,3,5,7,3,3,5,7,3,5,7,3,5,3,3,5,7,11,11,13,3,5,7,23,11,3,3,5,3,5,7,3,5,7,3,3,5,7,11,11,13,3,5,3,5,7,3,5,7,19,3,5,7,17,11,3,5,7,19,3,5,7,17,11,3,5,7,19,3,5,7,3,5,7,3,5,3,5,7,13,3,5,7,3,5,3,5,7,13,3,5,3,5,7,13,11,13,19,3,5,7,23,11,3,5,7,19,11,13,3,3,5,7,11,11,3,3,5,3,3,5,7,11,11,3,5,7,19,11,13,31,3,5,3,3,5,3,5,7,13,11,13,19,3,5,3,3,5,3,5,7,13,11,13,19,17,19,31,3,5,3,5,7,13,3,5,7,17,11,3,5,7,19,3,5,3,5,7,3,5,7,3,5,7,43,11,13,31,3,5,3,5,7,3,5,7,3,5,7,73,3,5,7,3,5,7,23,11,13,3,5,3,5,7,3,3,5,7,11,11,3,3,5,7,3,5,7,17,11,3,3,5,7,11,11,3,3,5,7,3,5,7,17,11,13,23,17,19,3,5,3,3,5,3,5,7,3,5,7,3,5,7,31,3,5,7,3,5,7,3,5,7,29,11,13,41,17,19,41,23,3,3,5,7,11,11,3,5,7,19,3,5,7,17,11,3,5,7,3,5,7,3,5,7,31,3,5,7,17,11,13,3,5,3,5,7,3,5,7,3,3,5,7,3,5,7,17,11,13,3,5,7,29,11,3,5,7,19,11,13,37,17,19,3,3,5,3,5,7,3,3,5,7,3,5,3,3,5,3,5,7,13,11,13,3,3,5,7,3,5,7,17,11,13,23,17,19,29,23,31,47,29,31,41,41,3,5,7,3,5,7,3,5,7,61,3,5,7,17,11,13,23,17,19,3,5,7,41,11,3,5,7,19,11,13,43,3,5,3,3,5,3,5,7,3,5,7,19,3,5,3,3,5,7,3,5,7,17,11,13,3,5,7,29,11,3,3,5,3,3,5,3,5,7,3,5,7,19,11,13,3,5,7,31,11,13,3,5,7,43,3,5,7,17,11,13,3,5,7,3,5,3,5,7,3,5,7,19,3,5,3,5,7,13,3,5,3,5,7,13,11,13,19,3,5,3,5,7,3,3,5,3,5,7,3,3,5,7,3,5,7,17,11,3,5,7,19,11,13,31,17,19,31,3,5,7,3,5,3,3,5,7,11,11,13,17,17,19,23,23,31,3,5,3,3,5,7,11,11,3,5,7,19,11,13,3,3,5,7,11,11,3,5,7,19,3,5,7,3,5,7,3,5,7,3,5,7,47,11,13,41,17,19,3,5,7,3,5,3,3,5,7,11,11,13,3,5,7,23,11,3,5,7,19,11,13,3,5,7,31,3,5,7,17,11,13,23,17,3,5,7,67,11,13,31,3,5,7,3,5,3,3,5,3,3,5,7,11,11,3,5,7,19,11,13,3,5,7,3,5,7,3,5,7,43,11,13,61,17,19,3,3,5,7,11,11,13,17,17,3,3,5,7,11,11,13,17,17,19,23,23,3,5,7,3,5,7,37,3,5,7,3,5,3,3,5,3,5,7,13,3,5,7,3,5,7,23,11,3,3,5,7,11,11,3,5,7,19,11,13,37,3,5,7,23,11,3,5,7,3,5,7,61,11,13,3,3,5,3,3,5,7,11,11,3,5,7,19,11,13,3,3,5,7,11,11,13,17,17,3,3,5,7,3,5,3,3,5,7,11,11,3,5,7,19,3,5,7,17,11,13,23,17,19,3,5,7,47,11,13,41,17,19,47,23,43,3,5,3,5,7,3,5,7,19,3,5,7,17,11,13,23,17,3,3,5,3,5,7,13,3,5,7,17,11,13,23,17,3,3,5,3,5,7,13,3,5,7,3,5,7,3,5,3,5,7,13,11,13,3,3,5,7,11,11,13,17,17,19,23,23,3,5,7,3,3,5,7,3,5,3,5,7,3,5,7,19,11,13,31,3,5,7,3,5,3,3,5,7,3,5,3,5,7,3,5,7,19,11,13,3,5,7,3,5,7,3,5,7,43,11,13,61,3,5,3,5,7,3,5,7,19,11,13,3,5,7,31,3,5,7,3,5,3,5,7,13,11,13,19,17,19,31,23,29,31,3,5,7,53,11,13,41,17,19,3,5,7,53,11,3,5,7,19,3,5,3,5,7,3,3,5,7,3,5,7,17,11,13,23,17,19,29,23,3,5,7,31,11,13,3,3,5,7,11,11,13,17,17,3,5,7,61,3,5,3,5,7,13,11,13,3,5,7,103,11,13,31,3,5,7,23,11,3,3,5,3,5,7,13,3,5,7,3,5,7,3,5,3,3,5,3,5,7,3,5,7,19,3,5,3,3,5,7,3,5,7,17,11,3,3,5,7,11,11,3,5,7,19,3,5,3,5,7,13,11,13,19,3,5,7,23,11,3,5,7,19,11,13,3,3,5,7,3,5,3,3,5,7,11,11,13,17,17,3,5,7,31,11,13,31,3,5,3,5,7,3,5,7,19,3,5,7,3,5,3,5,7,13,11,13,19,17,19,3,5,7,31,3,5,7,17,11,3,5,7,3,5,7,3,5,7,31,3,5,7,17,11,3,5,7,19,11,13,3,5,7,31,11,13,37,3,5,3,5,7,3,5,7,3,3,5,7,11,11,13,17,17,19,23,23,43,29,29,3,3,5,7,11,11,3,5,7,19,3,5,3,5,7,13,11,13,19,3,5,3,5,7,13,3,5,7,17,11,13,3,5,7,3,5,7,53,11,13,3,5,3,5,7,3,5,7,19,11,13,37,17,19,31,3,5,7,29,11,3,3,5,7,11,11,13,17,17,3,5,7,37,11,13,31,17,19,37,23,41,43,3,5,3,3,5,7,11,11,13,3,5,7,3,5,3,5,7,13,11,13,3,5,7,3,5,7,31,3,5,3,5,7,13,3,5,7,17,11,13,23,17,19,29,23,3,3,5,3,3,5,7,11,11,13,3,5,7,23,11,13,29,17,19,41,23,37,41,29,3,3,5,7,3,5,7,3,5,7,3,5,3,5,7,3,3,5,7,11,11,13,3,5,3,5,7,13,11,13,3,3,5,7,11,11,3,3,5,7,11,11,13,17,17,3,3,5,7,11,11,13,17,17,3,5,7,3,5,7,31,11,13,37,17,19,43,3,5,7,29,11,13,41,17,3,5,7,67,3,5,3,3,5,3,3,5,7,11,11,13,17,17,19,23,23,3,5,7,31,3,5,7,17,11,13,3,5,7,3,5,7,59,11,3,3,5,3,5,7,3,3,5,7,3,5,7,17,11,3,3,5,7,11,11,13,3,5,7,23,11,3,3,5,7,11,11,3,5,7,19,11,13,37,3,5,7,3,5,3,5,7,3,5,7,19,3,5,7,3,5,7,3,5,7,29,11,13,41,17,3,5,7,31,11,13,3,3,5,3,5,7,13,11,13,19,3,5,7,3,5,3,5,7,13,3,5,7,17,11,3,5,7,19,3,5,7,3,5,7,3,5,7,29,11,13,53,17,19,41,23,3,5,7,3,3,5,7,11,11,3,5,7,19,11,13,61,3,5,3,5,7,3,5,7,19,11,13,79,17,19,3,3,5,7,11,11,3,5,7,19,11,13,79,3,5,3,3,5,7,11,11,3,5,7,19,11,13,31,3,5,3,5,7,13,3,5,7,17,11,13,23,17,19,3,5,3,5,7,3,3,5,3,5,7,3,3,5,7,11,11,13,3,5,3,5,7,13,11,13,19,17,19,37,3,5,7,29,11,13,53,17,19,41,23,3,5,7,31,11,13,3,3,5,3,5,7,3,5,7,3,3,5,7,3,5,7,17,11,13,23,17,19,29,23,3,3,5,7,3,5,7,17,11,13,23,17,3,5,7,3,5,7,31,11,13,3,3,5,7,3,5,7,17,11,13,3,5,7,29,11,13,47,17,3,3,5,3,5,7,3,5,7,19,11,13,43,3,5,3,3,5,7,11,11,13,17,17,19,3,5,7,29,11,13,53,17,19,41,23,43,3,5,7,53,11,3,5,7,3,3,5,7,11,11,3,3,5,7,11,11,3,3,5,7,11,11,3,5,7,3,3,5,7,11,11,3,3,5,7,11,11,3,5,7,3,5,7,37,3,5,7,17,11,13,23,17,19,29,23,61,41,29,31,3,5,7,47,11,3,3,5,7,11,11,3,5,7,19,3,5,7,3,5,7,23,11,3,5,7,19,11,13,31,17,19,3,5,7,3,5,7,43,11,13,3,5,7,61,11,13,3,3,5,7,11,11,13,17,17,19,3,5,7,3,5,3,5,7,3,5,7,3,5,7,31,11,13,31,17,19,3,3,5,7,11,11,3,5,7,19,11,13,61,3,5,7,3,5,3,3,5,3,5,7,13,11,13,19,17,19,31,23,29,3,3,5,7,11,11,13,3,5,7,3,5,7,29,11,13,59,17,3,5,7,31,3,5,7,3,5,7,3,5,7,29,11,13,71,17,19,3,5,7,47,11,13,53,17,3,3,5,3,5,7,3,3,5,7,3,5,7,3,5,7,23,11,3,5,7,3,5,7,31,11,13,3,5,7,37,11,13,3,5,7,61,11,13,61,17,19,3,3,5,7,3,5,3,5,7,13,11,13,19,17,19,3,5,7,31,3,5,7,17,11,13,23,17,19,29,23,61,3,5,3,3,5,3,5,7,3,3,5,7,11,11,13,3,5,3,5,7,13,11,13,19,3,5,7,23,11,13,29,17,19,53,23,43,41,29,31,3,5,7,53,11,3,5,7,3,5,7,73,11,13,3,5,7,37,11,13,43,3,5,7,3,5,7,29,11,3,5,7,19,11,13,3,3,5,3,5,7,3,5,7,19,3,5,7,3,5,7,23,11,3,3,5,3,5,7,13,11,13,19,3,5,7,3,5,7,3,5,3,5,7,3,3,5,7,11,11,3,3,5,7,11,11,13,17,17,3,5,7,37,11,13,3,5,7,37,3,5,7,17,11,13,23,17,19,3,5,3,5,7,3,5,7,19,11,13,3,3,5,7,3,5,7,3,5,7,3,5,7,29,11,13,47,17,19,41,23,31,47,29,3,5,7,3,5,7,43,11,13,61,3,5,3,5,7,13,3,5,7,17,11,3,5,7,19,3,5,7,17,11,13,3,5,7,29,11,13,53,17,19,3,5,3,3,5,3,5,7,13,11,13,19,17,19,31,23,29,3,5,7,37,11,13,3,5,7,3,3,5,7,11,11,13,17,17,3,5,7,3,5,7,3,5,7,37,11,13,43,3,5,7,23,11,3,5,7,19,11,13,67,3,5,3,5,7,13,11,13,19,17,19,139,23,29,31,29,31,3,5,7,3,5,7,3,5,7,3,5,7,61,3,5,7,3,5,3,3,5,7,11,11,13,3,5,7,3,5,3,3,5,7,3,5,7,17,11,13,23,17,19,29,23,3,5,7,3,3,5,3,5,7,13,11,13,19,17,19,3,3,5,3,5,7,13,11,13,3,3,5,7,3,5,3,5,7,13,11,13,19,17,19,31,23,29,31,3,5,7,3,5,7,3,5,3,5,7,13,3,5,7,17,11,3,5,7,19,11,13,37,17,19,31,23,43,37,29,31,43,3,5,7,41,11,13,47,17,3,3,5,7,3,5,3,3,5,3,3,5,7,11,11,3,5,7,19,11,13,31,3,5,7,3,5,3,5,7,13,3,5,7,17,11,3,5,7,3,5,7,37,11,13,31,17,19,37,3,5,3,3,5,7,3,5,7,17,11,13,23,17,19,29,23,31,59,29,31,3,5,3,5,7,13,3,5,7,17,11,3,5,7,3,5,7,3,5,7,31,3,5,7,3,5,7,23,11,13,3,5,3,5,7,3,3,5,7,3,5,3,5,7,3,3,5,7,11,11,3,3,5,7,11,11,13,17,17,3,5,7,3,5,7,31,11,13,37,17,19,43,3,5,3,5,7,13,11,13,3,5,7,67,11,13,31,3,5,7,23,11,13,29,17,19,47,23,97,41,29,3,5,7,3,5,7,43,11,13,79,17,19,127,3,5,3,5,7,13,11,13,19,17,19,3,5,7,31,3,5,7,3,5,3,5,7,3,5,7,19,11,13,31,3,5,7,3,5,7,3,5,7,41,11,3,3,5,7,11,11,3,5,7,19,11,13,3,5,7,31,3,5,7,17,11,3,3,5,7,11,11,3,5,7,19,3,5,7,17,11,13,3,5,7,29,11,3,5,7,19,11,13,37,17,19,31,23,47,3,3,5,3,5,7,13,3,5,7,3,5,3,5,7,13,3,5,7,17,11,13,23,17,19,3,5,7,53,11,3,5,7,3,5,7,3,3,5,7,3,5,7,17,11,3,5,7,19,11,13,3,3,5,7,11,11,3,5,7,3,5,7,3,5,7,3,5,7,37,3,5,7,3,5,7,23,11,3,5,7,3,3,5,7,3,5,7,3,5,7,3,5,7,29,11,3,5,7,19,3,5,7,17,11,13,23,17,19,29,23,43,3,5,7,3,5,7,47,11,13,53,17,19,59,23,3,3,5,7,11,11,13,17,17,19,3,5,3,5,7,13,3,5,7,17,11,3,5,7,19,11,13,37,17,19,31,23,43,37,29,31,3,5,7,61,3,5,7,17,11,13,23,17,19,3,5,3,3,5,7,11,11,3,5,7,3,3,5,7,3,5,3,5,7,13,11,13,19,17,19,3,5,7,31,3,5,7,17,11,13,3,5,7,29,11,13,53,17,19,3,5,7,47,11,13,53,17,3,5,7,3,3,5,7,11,11,13,3,5,7,3,5,7,29,11,3,3,5,7,11,11,3,3,5,7,3,5,7,17,11,3,5,7,19,11,13,31,3,5,3,5,7,13,11,13,19,17,19,67,23,29,3,3,5,7,11,11,13,17,17,3,3,5,7,11,11,3,3,5,7,11,11,3,5,7,19,11,13,37,17,19,31,3,5,3,3,5,3,5,7,13,3,5,7,17,11,13,23,17,3,5,7,3,5,7,3,3,5,7,11,11,13,3,5,7,23,11,13,29,17,3,5,7,37,3,5,3,5,7,3,5,7,19,11,13,61,17,19,31,23,31,37,29,31,3,3,5,7,11,11,3,3,5,7,3,5,3,5,7,3,5,7,3,5,7,31,3,5,7,3,5,3,5,7,13,11,13,3,5,7,3,5,7,31,3,5,7,17,11,13,3,5,3,5,7,13,11,13,19,3,5,7,23,11,13,3,5,7,59,11,3,5,7,19,11,13,37,17,19,31,23,47,3,5,7,3,5,7,61,11,13,3,5,7,3,3,5,7,11,11,13,17,17,19,23,23,3,5,7,31,3,5,7,17,11,13,23,17,19,3,5,7,59,11,3,5,7,3,5,7,43,11,13,31,3,5,3,3,5,7,3,5,7,17,11,3,5,7,19,3,5,7,3,5,3,5,7,3,5,7,19,11,13,31,17,19,31,23,31,37,29,31,3,5,7,73,11,13,61,3,5,7,23,11,3,3,5,7,11,11,13,3,5,7,23,11,3,3,5,7,11,11,13,17,17,3,3,5,7,11,11,13,17,17,19,3,5,7,29,11,13,53,17,19,41,23,43,3,5,7,53,11,13,59,17,19,3,5,7,3,5,7,173,11,13,83,17,3,5,7,31,11,13,31,17,19,3,5,7,3,3,5,7,11,11,13,17,17,19,3,5,3,5,7,3,3,5,7,11,11,3,5,7,19,3,5,7,17,11,3,5,7,3,5,7,3,5,7,31,3,5,3,5,7,3,3,5,7,11,11,3,3,5,7,11,11,13,3,5,3,5,7,3,5,7,3,3,5,7,11,11,13,3,5,3,5,7,13,11,13,19,3,5,7,23,11,13,29,17,19,3,5,3,5,7,3,5,7,19,11,13,43,17,19,31,3,5,3,5,7,13,3,5,7,3,5,3,5,7,13,3,5,3,5,7,13,11,13,19,3,5,7,3,5,3,5,7,13,11,13,19,3,5,7,23,11,13,3,5,3,3,5,7,11,11,13,17,17,19,23,23,31,29,29,31,3,5,3,5,7,13,11,13,19,17,19,61,23,29,3,5,7,3,5,7,3,5,7,79,11,13,3,5,7,61,11,13,3,5,7,73,11,13,79,3,5,7,3,5,3,3,5,3,5,7,13,11,13,19,17,19,3,5,7,3,5,7,37,11,13,3,5,7,61,3,5,7,3,5,3,5,7,13,11,13,3,3,5,7,11,11,13,3,5,7,23,11,13,29,17,19,47,23,37,41,29,31,3,5,7,53,11,13,59,17,3,3,5,7,3,5,7,17,11,13,23,17,19,29,23,3,5,7,31,11,13,37,3,5,7,3,5,7,29,11,3,5,7,19,11,13,3,5,7,3,3,5,3,5,7,13,3,5,7,17,11,3,5,7,3,5,7,3,5,7,31,11,13,37,17,19,43,23,31,3,5,7,67,11,13,61,3,5,7,3,5,3,5,7,13,3,5,7,17,11,13,3,5,7,29,11,13,59,17,19,3,5,7,47,11,3,3,5,7,11,11,3,3,5,3,5,7,3,5,7,19,11,13,37,17,19,31,3,5,7,3,5,3,5,7,13,11,13,19,3,5,3,3,5,3,5,7,13,11,13,19,3,5,7,3,5,7,29,11,13,3,5,7,41,11,13,47,17,19,53,23,37,3,5,7,71,11,3,5,7,3,5,7,61,3,5,7,17,11,3,3,5,7,11,11,13,17,17,19,23,23,37,29,29,31,3,5,3,5,7,3,3,5,7,11,11,13,3,5,3,5,7,13,11,13,19,3,5,7,3,5,7,29,11,13,53,17,19,41,23,31,47,29,31,53,41,3,5,7,43,11,13,3,5,7,61,3,5,7,3,5,7,23,11,3,3,5,3,5,7,13,11,13,19,17,19,37,3,5,7,29,11,3,5,7,19,3,5,7,17,11,13,23,17,3,3,5,7,11,11,3,5,7,19,11,13,43,3,5,3,3,5,7,11,11,13,3,5,7,3,5,7,29,11,13,53,17,3,5,7,3,5,7,31,3,5,3,5,7,13,3,5,3,5,7,3,5,7,19,3,5,7,3,5,7,3,5,7,29,11,13,3,5,7,3,5,3,5,7,3,5,7,3,5,7,31,3,5,7,17,11,13,23,17,19,3,5,3,5,7,13,11,13,19,17,19,43,3,5,3,5,7,13,11,13,3,3,5,7,11,11,3,5,7,3,3,5,7,11,11,3,5,7,19,11,13,3,3,5,3,5,7,13,11,13,19,17,19,67,3,5,7,3,5,7,41,11,13,41,17,19,47,23,31,53,29,31,3,5,7,3,5,3,5,7,13,3,5,7,17,11,3,5,7,19,11,13,3,5,7,3,3,5,7,11,11,13,17,17,19,23,23,67,29,29,3,3,5,7,3,5,3,3,5,7,11,11,13,17,17,3,5,7,31,11,13,3,3,5,7,3,5,7,17,11,3,5,7,19,3,5,7,17,11,13,23,17,19,29,23,43,3,5,7,41,11,13,3,5,7,3,5,7,59,11,13,83,17,19,3,5,7,3,5,3,5,7,13,11,13,19,3,5,7,3,5,3,5,7,13,11,13,3,5,7,31,3,5,7,3,5,7,23,11,13,3,5,3,5,7,3,5,7,19,11,13,3,5,7,3,5,7,37,11,13,3,3,5,7,11,11,13,17,17,3,5,7,67,11,13,31,17,19,37,3,5,3,3,5,7,11,11,3,5,7,19,11,13,31,17,19,3,5,7,37,3,5,3,5,7,13,11,13,19,3,5,3,3,5,7,3,5,7,17,11,13,23,17,19,29,23,3,5,7,3,5,7,37,11,13,43,3,5,7,3,5,7,3,5,7,41,11,3,5,7,3,3,5,7,11,11,3,3,5,3,3,5,7,11,11,13,17,17,19,23,23,3,3,5,3,5,7,3,5,7,3,5,7,67,11,13,3,5,7,3,5,7,43,11,13,73,3,5,7,23,11,3,5,7,19,11,13,3,5,7,3,5,7,37,3,5,3,5,7,13,11,13,19,17,19,61,23,29,31,29,31,37,47,37,3,5,7,157,11,13,139,3,5,7,23,11,13,3,5,7,3,5,3,5,7,3,3,5,7,11,11,13,3,5,7,3,5,7,29,11,13,3,5,7,41,11,13,47,17,3,3,5,7,11,11,3,5,7,19,3,5,7,17,11,13,23,17,19,29,23,3,3,5,7,11,11,13,3,5,7,3,5,3,5,7,3,5,7,19,11,13,31,17,19,3,3,5,7,11,11,13,3,5,7,3,5,3,5,7,13,11,13,3,5,7,31,3,5,7,3,5,7,23,11,13,3,5,3,5,7,3,5,7,19,11,13,3,5,7,3,3,5,7,11,11,13,3,5,7,23,11,13,3,5,3,5,7,13,11,13,19,3,5,7,3,5,7,29,11,13,71,17,3,5,7,3,3,5,7,11,11,3,5,7,19,3,5,7,17,11,13,23,17,19,3,5,7,3,5,7,41,11,13,47,17,19,53,23,31,59};
int main()
{
    int n;scanf("%d",&n);
    for(int i=2;2*i<=n;i++)
    printf("%d=%d+%d\n",2*i,b[i],2*i-b[i]);
    return 0;
}

Stats:
  A program to do common statistics calculations. Edit a seperate file with name of table and x & y points, 
  then run ./stats FILE to calculate statistics on points entered in FILE
  Statistics are printed in engineering format.
  
Use:
  ./stats -v or ./stats --version 
      print version
  ./stats FILE 
      read in a file and calculate statistics on points entered

    NOTE: version or file options but not both (can't do ./stats -v table1.txt)

    FILE format:
      1st line is name of table
      every other line after that is an x & y coordinate seperated by exactly 1 space

      example FILE:
        table1
        1.0 5
        6 7
        -99 2
        ... (ecetera)

        no leading or trailing whitespace and 1 x y coordinate per line

      see table1.txt, table2.txt, table3.txt as examples

      Problems:
        -the format has to be exact: cannot have leading or trailing whitespace and points are sperated by exactly 1 space
        - Errors reported in this program when functions fail print the file where the function causing the error is declared and the function definition, not exactly where the error occured. 
        (Ex if uedint_end() is called from main() in main.c and the table is full, it prints an error indicating table.c is the file when it should print that the error occured in main.c:int main(int argc, char *argv[]) with a line number.
        -double variables in C only have precision up to 15-17 digits. Anything beyond that looses accuracy (and files with very large numbers hasn't been tested as much as i'd like) 

#make program
gcc evaluate.c ../utils/filepath.c ../models/submission.c ../models/group.c ../models/process.c ../utils/str.c -o evaluate

#running program
./evaluate 1 256 2 /home/jeffxie/Documents/test/helloworld/ /home/jeffxie/Documents/test/test_program test_program


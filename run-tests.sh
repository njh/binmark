#!/bin/bash
#
# Bash script to run all the test cases in the tests directory
#
# .bm     : the input file
# .expect : the expected output file (binary)
# .result : the output of running the text locally
#

totalcount=0
failcount=0
errorcount=0

for filepath in tests/*.bm
do
  filename=${filepath##*/}
  testname=${filename%.*}
  expectedfile="tests/$testname.expect"
  resultfile="tests/$testname.result"

  ((totalcount++))
  echo "Testing: $testname"
  ./binmark -x $filepath > $resultfile
  if [ $? -ne 0 ]; then
      echo " => Error"
      ((errorcount++))
      continue
  fi

  # Now compare the results
  cmp $expectedfile $resultfile
  if [ $? -eq 0 ]; then
      echo " => OK"
  else
      echo " => Failed"
      ((failcount++))
  fi
done

echo
echo "Tests: $totalcount, Failures: $failcount, Errors: $errorcount"

if [ $totalcount -lt 1 ] || [ $failcount -gt 0 ] || [ $errorcount -gt 0 ]; then
    exit -1
fi


#!/bin/bash

trap "exit" INT

OUTDIRECTORY="OutputFromTest"
INDIRECTORY="TestFiles/udt/" #simple_expressions/"  #udt/"

#make a build directory if it doesn't exist. 
if [ ! -d "$OUTDIRECTORY" ]; then
  # Control will enter here if $OUTDIRECTORY doesn't exist.
  mkdir $OUTDIRECTORY
fi

#Clean it out. 
rm -rf $OUTDIRECTORY/*


for i in $INDIRECTORY*.cpsl
do
  name="${i#*$INDIRECTORY}";
  name="${name%%.cpsl}";
  #echo $name;
  echo "Testing $name";
  ./build/cpsl < $i  > $OUTDIRECTORY/$name.asm
  java -jar Mars4_5.jar $OUTDIRECTORY/$name.asm
  echo "";
  echo "";
done

echo "Finished Testing";

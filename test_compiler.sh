#!/bin/bash

trap "exit" INT

DIRECTORY="OutputFromTest"

#make a build directory if it doesn't exist. 
if [ ! -d "$DIRECTORY" ]; then
  # Control will enter here if $DIRECTORY doesn't exist.
  mkdir $DIRECTORY
fi

#Clean it out. 
rm -rf $DIRECTORY/*


for i in TestFiles/*.cpsl
do
  name="${i#*TestFiles/}";
  name="${name%%.cpsl}";
  echo $name;
  echo "Testing $name";
  ./build/cpsl < $i > $DIRECTORY/$name.asm
  java -jar Mars4_5.jar $DIRECTORY/$name.asm
  echo "";
  echo "";
done

echo "Finished Testing";

#!/bin/bash

#This creates a backup version of the binary for the cuda stuff

#change the directory
cd ..
#assign the version name
version_name=creal_daily_`date +"%m.%d.%y-%H.%M.%S"`.tar
#echo out the versioning name
echo $version_name
#tar the file
tar -cvvf $version_name cuda/
#bzip the file
bzip2 $version_name



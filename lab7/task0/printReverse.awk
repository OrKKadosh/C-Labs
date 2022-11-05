#! /usr/bin/awk -f

BEGIN	{ FS = " "} 
	{ print $1 "\t" $4 "\t" $3 "\t" $2 }
	

#! /usr/bin/awk -f

BEGIN	{ FS = " "} 
	{ if (/a/) 
		{ print $2 "\t" $4 }
	}

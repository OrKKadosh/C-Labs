#! /usr/bin/awk -f

BEGIN	{ 
	OFS = "\n"
	FS = "," 
	getline
	print "\n-------------------"
	}
	{ if ($2 >= 1970) {
		print "Actor Name: "$4 , "Movie Name: "$5 "\n-------------------"}
	}

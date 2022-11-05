#! /usr/bin/awk -f

BEGIN	{ 
		OFS = "\n"
		FS = "," 
		getline
		print "\n-------------------"
	}

	{ 
		count = 0
		if (NR >= 51 && NR <= 71) 
		{
			print "Actor Name: "$4 , "Movie Name: "$5 "\n-------------------"
			count = count + 1
		}
	}

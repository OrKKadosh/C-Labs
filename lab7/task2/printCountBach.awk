#! /usr/bin/awk -f

BEGIN	{ 
		FS = "," 
		getline
		print "\n-------------------"
		count = 0;
	}

	{ 
		
		if ($3 == "bachelor's degree") 
		{
			count = count + 1;
		}
	}
END	{
	print "Number of students whose parents have a bachelor's degree is: " count "\n-------------------\n"
	}

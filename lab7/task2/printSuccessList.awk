#! /usr/bin/awk -f

BEGIN	{ 
		FS = "," 
		getline
		print "\n-------------------"
		print "Success Student List"
		count = 0;
	}

	{ 
		if ($6 >= 80 && $7 >= 80 && $8 >= 80) 
		{
			print $0
			count = count + 1;
		}
	}
END	{
		print "The number of students : "count
	}

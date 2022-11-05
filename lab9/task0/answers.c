/*
0A
- Where is the entry point specified, and what is its value?
ELFexec - 0x8048294
ELFexec2short - 0x8048080

- What fields inside the file header differ? what does this mean?
only the entry point

- Where in the file does the code of function "main" start?
ELFexec2short:
	start virtual adress - 08048080
	start size - 0
	start section header - 1 (text)
	text virtual adress - 08048080
	text offset - 000080
	formula: section_file_offset + function_virtual_address - section_virtual_address
	000080 + 08048080 - 08048080 = 000080 (in hex)
	
ELFexec:
	start virtual adress - 0x8048294
	start size - 0
	start section header - 1 (text)
	text virtual adress - 08048080
	text offset - 000080
	formula: section_file_offset + function_virtual_address - section_virtual_address
	000080 + 08048080 - 08048080 = 000080 (in hex)

- Which file is infected?
	ELFexec is infected, because its entry point is not the function start's virtual adress, 
	so it starts from somewhere else, probably from the virus part.

0B
In this task, you are required to fix the infected file manually using Hexedit and readelf
- virus position:
000080 + 0x8048294 - 08048080 = 000294
we changed every part to 90 after the wrong entry point.
the program is still broken but there is no virus.
*/

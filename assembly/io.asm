IO	TD	STDIN
	JEQ	IO
	RD	STDIN
	WD	STDOUT
	J	STOP

STOP	J	STOP

STDOUT	BYTE	1
STDIN	BYTE	0

INLOOP	TD	INDEV
	JEQ	INLOOP
	RD	INDEV
	STA	DATA

OUTLOOP	TD	OUTDEV
	JEQ	OUTLOOP
	LDA	DATA
	WD	OUTDEV
	J	STOP

STOP	J	STOP

INDEV	BYTE	X'F5'
OUTDEV	BYTE	X'08'
DATA	WORD	1
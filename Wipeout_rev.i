VERSION		EQU	1
REVISION	EQU	33

DATE	MACRO
		dc.b '14.6.2009'
		ENDM

VERS	MACRO
		dc.b 'Wipeout 1.33'
		ENDM

VSTRING	MACRO
		dc.b 'Wipeout 1.33 (14.6.2009)',13,10,0
		ENDM

VERSTAG	MACRO
		dc.b 0,'$VER: Wipeout 1.33 (14.6.2009)',0
		ENDM

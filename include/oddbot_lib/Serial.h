// Serial.h
#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <iostream>
#include <fstream>
#include <termios.h>

#ifndef __SERIAL_H__
#define __SERIAL_H__

#define FC_DTRDSR       0x01
#define FC_RTSCTS       0x02
#define FC_XONXOFF      0x04
#define ASCII_BEL       0x07
#define ASCII_BS        0x08
#define ASCII_LF        0x0A
#define ASCII_CR        0x0D
#define ASCII_XON       0x11
#define ASCII_XOFF      0x13

class CSerial
{

public:
	CSerial(char *pn);
	//~CSerial();

	bool Open( int nBaud = 9600 );
	bool Close( void );
	char * portName;
	int ReadData();
	int SendData( const char *);
	//int ReadDataWaiting( void );
	char readBuffer[256];
	int thePORT;	
	int readCheck;
	int length(char strname []);
	bool IsOpened( void ){ return( is_port_open ); }

protected:
	bool WriteCommByte( unsigned char );

	bool is_port_open;

};

#endif

// Serial.cpp

#include "./Serial.h"
using namespace std;
CSerial::CSerial(char *pn)
{
	
	
	portName = pn;
	is_port_open = false;
	is_port_open = Open(9600);

}

//CSerial::~CSerial()
//{

//	Close();

//}

bool CSerial::Open( int nBaud )
{

	if( is_port_open ) return( true );

	thePORT = open( portName, O_RDWR| O_NONBLOCK | O_NDELAY );
/* Error Handling */
if ( thePORT < 0 )
{
    cout << "Error " << errno << " opening " << portName << ": " << strerror (errno) << endl;
    is_port_open = false;
}
else is_port_open = true;

struct termios tty;
memset (&tty, 0, sizeof tty);
struct tm * timeinfo;
char buffer [80];
time_t rawtime;
/* Error Handling */
if ( tcgetattr ( thePORT, &tty ) != 0 )
{
    cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << endl;
}

/* Set Baud Rate */
cfsetospeed (&tty, B9600);

/* Setting other Port Stuff */
tty.c_cflag     &=  ~PARENB;        // Make 8n1
tty.c_cflag     &=  ~CSTOPB;
tty.c_cflag     &=  ~CSIZE;
tty.c_cflag     |=  CS8;
tty.c_cflag     &=  ~CRTSCTS;       // no flow control
tty.c_lflag     =   0;          // no signaling chars, no echo, no canonical processing
tty.c_oflag     =   0;                  // no remapping, no delays
tty.c_cc[VMIN]      =   0;                  // read doesn't block
tty.c_cc[VTIME]     =   5;                  // 0.5 seconds read timeout

tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines
tty.c_iflag     &=  ~(IXON | IXOFF | IXANY);// turn off s/w flow ctrl
tty.c_lflag     &=  ~(ICANON | ECHO | ECHOE | ISIG); // make raw
tty.c_oflag     &=  ~OPOST;              // make raw

/* Flush Port, then applies attributes */
tcflush( thePORT, TCIFLUSH );

if ( tcsetattr ( thePORT, TCSANOW, &tty ) != 0)
{
    cout << "Error " << errno << " from tcsetattr" << endl;
}



	return( is_port_open );

}

bool CSerial::Close( void )
{

	if( !is_port_open ) return( true );

	close(thePORT);
	is_port_open = false;
	

	return( true );

}

//bool CSerial::WriteCommByte( unsigned char ucByte )
//{
//	BOOL bWriteStat;
//	DWORD dwBytesWritten;

//	bWriteStat = WriteFile( m_hIDComDev, (LPSTR) &ucByte, 1, &dwBytesWritten, &m_OverlappedWrite );
//	if( !bWriteStat && ( GetLastError() == ERROR_IO_PENDING ) ){
//		if( WaitForSingleObject( m_OverlappedWrite.hEvent, 1000 ) ) dwBytesWritten = 0;
//		else{
//			GetOverlappedResult( m_hIDComDev, &m_OverlappedWrite, &dwBytesWritten, FALSE );
//			m_OverlappedWrite.Offset += dwBytesWritten;
//			}
//		}

//	return( TRUE );

//}

int CSerial::SendData( const char *buffer )
{

	if( !is_port_open ) return( 0 );
	int n_written = write( thePORT, buffer, sizeof(buffer) -1 );
	//might need for loop, to pass size variable
	return( n_written);

}

//int CSerial::ReadDataWaiting( void )
//{

//	if( !is_port_open || m_hIDComDev == NULL ) return( 0 );

//	DWORD dwErrorFlags;
//	COMSTAT ComStat;

//	ClearCommError( m_hIDComDev, &dwErrorFlags, &ComStat );

//	return( (int) ComStat.cbInQue );

//}

//int CSerial::ReadData( char* readBuffer )
int CSerial::ReadData()
{

	if( !is_port_open ) return( 0 );


	/* Allocate memory for read buffer */
	
	
	//memset (&readBuffer, '\0', sizeof readBuffer);
	
	//    ofstream sensorData("sensor.log",ios::app);
	/* *** READ *** */

	//pointing to address?
	readCheck = read( thePORT, readBuffer , sizeof readBuffer);

	/* Error Handling */
//	if (readCheck < 0)
//	{
//	    cout << "Error reading: " << strerror(errno) << endl;
//	}

	//cout << "Read: " << readBuffer<< endl;


//	length1=length(buf);
//	if(length1>0)
//	   {time(&rawtime);
//	     timeinfo = localtime (&rawtime);
//	    strftime (buffer,80,"%F-%I-%M-%S ",timeinfo);
// 	   sensorData<<buffer<<buf;
//	  sensorData.close(); 

   	return readCheck;
	
}

	



int length(char strname [])
{
	int i=0;

	 while(strname[i]!='\0')
		      {i++;
		       }
	 return i;
}




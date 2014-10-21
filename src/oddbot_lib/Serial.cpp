// Serial.cpp

#include "./Serial.h"
using namespace std;
CSerial::CSerial(char *pn, int br=9600)
{
	
	
	portName = pn;
	baudRate = br;
	is_port_open = false;
	is_port_open = Open();

}

CSerial::~CSerial()
{

	Close();

}

bool CSerial::Open( )
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
switch(baudRate)
{
 	case 9600:
	cfsetospeed (&tty, B9600);
	break;

	case 38400:
	cfsetospeed (&tty, B38400);
	break;

	case 57600:
	cfsetospeed (&tty, B57600);
	break;

	case 115200:
	cfsetospeed (&tty, B115200);
	break;

	default:
	cfsetospeed (&tty, B9600);	
}


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


int CSerial::SendData( const char *buffer )
{

	if( !is_port_open ) return( 0 );
	readCheck = write( thePORT, buffer, sizeof(buffer) -1 );
	//might need for loop, to pass size variable
	return readCheck;

}


int CSerial::ReadData()
{

	if( !is_port_open ) return( 0 );


	/* *** READ *** */

	//pointing to address?
	readCheck = read( thePORT, readBuffer , sizeof readBuffer);

	

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




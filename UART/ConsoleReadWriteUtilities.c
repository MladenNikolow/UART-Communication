#include <stdio.h>
#include "Windows.h"
#include "ConsoleReadWriteUtilities.h"
#include "ErrorHandling.h"


static void PrintParity( const BYTE bParity )
{
	printf_s( "Parity: " );

	switch( bParity )
	{
		case EVENPARITY:
		{
			printf_s( "Even\n" );
			break;
		}

		case MARKPARITY:
		{
			printf_s( "Mark\n" );
			break;
		}

		case NOPARITY:
		{
			printf_s( "None\n" );
			break;
		}

		case ODDPARITY:
		{
			printf_s( "Odd\n" );
			break;
		}

		case SPACEPARITY:
		{
			printf_s( "Space\n" );
			break;
		}

		default:
		{
			printf_s( "Unknown\n" );
			break;
		}
	} // switch ( nParity )
}

void PrintStopBits( const BYTE bStopBits )
{
	printf_s( "Stop bits: " );

	switch ( bStopBits )
	{
		case ONESTOPBIT:
		{
			printf_s( "1 stop bit\n" );
			break;
		}

		case ONE5STOPBITS:
		{
			printf_s( "1.5 stop bits\n" );
			break;
		}

		case TWOSTOPBITS:
		{
			printf_s( "2 stop bits\n" );
			break;
		}

		default:
		{
			printf_s("Unknown\n");
			break;
		}
	} // switch ( nStopBits )

}

void PrintSerialPortInformation( const DWORD dwBaudRate, const BYTE bParity, const BYTE bStopBits )
{
	printf_s( "------------------ COM Port Configuration ------------------\n" );

	printf_s( "Baud rate: %ld\n", dwBaudRate );

	PrintParity( bParity );

	PrintStopBits( bStopBits );

	printf_s("------------------------------------------------------------\n");
}

bool ReadInputMessage( char szInputArray[], const int nMaxSize )
{
	printf_s( "Please, enter a string (up to %d characters): ", nMaxSize - 1 );
	
	if ( fgets( szInputArray, nMaxSize, stdin ) == NULL )
	{
		HandleError( UNABLE_TO_READ_INPUT_VIA_FGETS );
		return false;
	}

	// Remove the new line
	size_t nRealInputArraySize = strlen( szInputArray );
	if ( nRealInputArraySize > 0 
		&& szInputArray[ nRealInputArraySize - 1 ] == '\n' ) 
	{
		szInputArray[ nRealInputArraySize - 1 ] = '\0';
		--nRealInputArraySize;
	} else
	{
		printf_s( "Input was truncated! The message will be transmitted up to the maximum allowed size!\n" );
	}

	return true;
}
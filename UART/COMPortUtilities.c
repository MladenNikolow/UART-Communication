#include <stdio.h>
#include "COMPortUtilities.h"
#include "ErrorHandling.h"

bool IsHandleValid( HANDLE hCOMPort )
{
	if ( hCOMPort == INVALID_HANDLE_VALUE || hCOMPort == NULL )
		return false;
	
	return true;
}

bool OpenCOMPort( HANDLE hCOMPort )
{
	hCOMPort = INVALID_HANDLE_VALUE;

	printf_s("Opening COM Port...\n");

	hCOMPort = CreateFile( L"\\\\.\\COM3"
						 , GENERIC_READ | GENERIC_WRITE
						 , 0 /*dwShareMode*/
						 , 0 /*LPSECURITY_ATTRIBUTES*/
						 , OPEN_EXISTING
						 , FILE_ATTRIBUTE_NORMAL
						 , 0 /*hTemplateFile*/ );

	if ( hCOMPort == INVALID_HANDLE_VALUE )
	{
		HandleError( UNABLE_TO_OPEN_COM_PORT_VIA_CREATE_FILE );
		return false;
	}

	printf_s("Successfully opened COM port.\n");

	return true;
}

bool ConfigureCOMPort( HANDLE hCOMPort )
{
	printf_s("Configuring COM port.\n");

	if ( !IsHandleValid( hCOMPort ) )
	{
		HandleError( ATTEMPT_TO_CONFIGURE_INVALID_HANDLE_TO_COM_PORT );
		return false;
	}

	DCB dcb;
	if ( !GetCommState( hCOMPort, &dcb ) )
	{
		HandleError( UNABLE_TO_GET_CURRENT_STATE_OF_COM_PORT );
		return false;
	}

	dcb.BaudRate	= CBR_9600;
	dcb.ByteSize	= 8;
	dcb.Parity		= NOPARITY;
	dcb.StopBits	= ONESTOPBIT;

	if ( !SetCommState( hCOMPort, &dcb ) )
	{
		HandleError( UNABLE_TO_SET_STATE_OF_COM_PORT );
		return false;
	}

	printf_s("Succesfullty configured COM port.\n");

	return true;
}

bool CloseCOMPort( HANDLE hCOMPort )
{
	printf_s("Closing COM Port...\n");

	if ( !IsHandleValid( hCOMPort ) )
	{
		HandleError( ATTEMPT_TO_CLOSE_INVALID_HANDLE_TO_COM_PORT );
		return false;
	}

	if ( !CloseHandle( hCOMPort ) )
	{
		HandleError( UNABLE_TO_CLOSE_COM_PORT_VIA_CLOSE_HANDLE );
		return false;
	}

	printf_s("Successfully closed COM port.\n");

	return true;
}

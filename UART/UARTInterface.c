#include <stdio.h>
#include "UARTInterface.h"
#include "ErrorHandling.h"
#include "ConsoleReadWriteUtilities.h"

#define MAX_UART_MESSAGE_SIZE		256

bool SendDataViaUART( const HANDLE hCOMPort )
{
	char szInputArray[MAX_UART_MESSAGE_SIZE] = { 0 };
	if ( !ReadInputMessage( szInputArray, MAX_UART_MESSAGE_SIZE ) )
		return false;

	DWORD bytesWritten;
	if ( !WriteFile( hCOMPort
				   , szInputArray
				   , sizeof( szInputArray )
				   , &bytesWritten
				   , NULL ) )
	{
		HandleError( UNABLE_TO_SEND_DATA_VIA_UART );
		return false;
	}
		
	printf_s( "Send message via UART: \"%s\" \n", szInputArray );

	return true;
}

bool ReceiveDataViaUART( const HANDLE hCOMPort )
{
	char szReceivedMessage[ MAX_UART_MESSAGE_SIZE ] = { 0 };

	DWORD dwBytesReaded = 0UL;
	if ( !ReadFile( hCOMPort
				  , szReceivedMessage
				  , sizeof( szReceivedMessage )
				  , &dwBytesReaded
				  , NULL ) )
	{
		HandleError( UNABLE_TO_RECEIVE_DATA_VIA_UART );
		return false;
	}

	printf_s( "Received message via UART: \"%s\" \n", szReceivedMessage );

	return true;
}


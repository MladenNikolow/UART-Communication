#include <Windows.h>
#include <stdio.h>
#include "ErrorHandling.h"

void HandleError( const DetailedErrorTypes eDetailedErrorType )
{
	const DWORD dwErrorCode = GetLastError();

	switch ( eDetailedErrorType )
	{
		case NO_ERROR:
			break;

		case UNABLE_TO_OPEN_COM_PORT_VIA_CREATE_FILE:
		{
			printf_s( "Error while opening COM port! Context: CreateFile, Error code: %lu\n", dwErrorCode );
			break;
		}

		case UNABLE_TO_CLOSE_COM_PORT_VIA_CLOSE_HANDLE:
		{
			printf_s( "Error while closing COM port! Context: CloseHandle, Error code: %lu\n", dwErrorCode );
			break;
		}

		case ATTEMPT_TO_CLOSE_INVALID_HANDLE_TO_COM_PORT:
		{
			printf_s( "Error while closing COM port! The handle to the COM port is invalid.\n" );
			break;
		}

		case ATTEMPT_TO_CONFIGURE_INVALID_HANDLE_TO_COM_PORT:
		{
			printf_s("Error while configuring COM port! The handle to the COM port is invalid.\n");
			break;
		}

		case UNABLE_TO_GET_CURRENT_STATE_OF_COM_PORT:
		{
			printf_s( "Error while configuring the COM port. Can not retrieve the current state. Error code: %lu\n", dwErrorCode );
			break;
		}

		case UNABLE_TO_SET_STATE_OF_COM_PORT:
		{
			printf_s( "Error while configuring the COM port. Can not set the new state. Error code: %lu\n", dwErrorCode );
			break;
		}
	
		default:
		{
			printf_s( "Unknown Error\n" );
			break;
		}	
	} // switch
}
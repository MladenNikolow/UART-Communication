#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>
#include "ErrorHandling.h"

LPVOID FormMessageFromErrorCode( wchar_t** wszMessage, DWORD dwErrorCode )
{
	if ( wszMessage == NULL )
		return;

	LPVOID lpMessageBuffer = NULL;
	DWORD dwBufferLength = FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS
										 , NULL
										 , dwErrorCode
										 , MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT )
										 , (LPTSTR)&lpMessageBuffer
										 , 0
										 , NULL );

	if ( lpMessageBuffer )
		*wszMessage = (wchar_t*)lpMessageBuffer;
	else
		*wszMessage = L"";

	return lpMessageBuffer;
}

void HandleError( const DetailedErrorTypes eDetailedErrorType )
{
	const DWORD dwErrorCode = GetLastError();
	const bool bHasErrorCode = dwErrorCode != 0;

	LPVOID lpMessageBuffer = NULL;
	wchar_t* wszMessage = NULL;
	if ( bHasErrorCode )
		lpMessageBuffer = FormMessageFromErrorCode( &wszMessage, dwErrorCode );
	else
		wszMessage = L"";
		
	switch ( eDetailedErrorType )
	{
		case NO_ERROR:
			break;

		case UNABLE_TO_OPEN_COM_PORT_VIA_CREATE_FILE:
		{
			wprintf_s( L"Error while opening COM port! Context: CreateFile, Error message: %s", wszMessage );
			break;
		}

		case UNABLE_TO_CLOSE_COM_PORT_VIA_CLOSE_HANDLE:
		{
			wprintf_s( L"Error while closing COM port! Context: CloseHandle, Error message: %s\n", wszMessage );
			break;
		}

		case ATTEMPT_TO_CLOSE_INVALID_HANDLE_TO_COM_PORT:
		{
			wprintf_s( L"Error while closing COM port! The handle to the COM port is invalid.\n" );
			break;
		}

		case ATTEMPT_TO_CONFIGURE_INVALID_HANDLE_TO_COM_PORT:
		{
			printf_s("Error while configuring COM port! The handle to the COM port is invalid.\n");
			break;
		}

		case UNABLE_TO_GET_CURRENT_STATE_OF_COM_PORT:
		{
			wprintf_s( L"Error while configuring the COM port. Can not retrieve the current state. Error message: %s\n", wszMessage );
			break;
		}

		case UNABLE_TO_SET_STATE_OF_COM_PORT:
		{
			wprintf_s( L"Error while configuring the COM port. Can not set the new state. Error message: %s\n", wszMessage );
			break;
		}

		case UNABLE_TO_SET_TIMEOUT_OF_COM_PORT:
		{
			wprintf_s( L"Error while configuring the COM port. Can not set the timeout. Error message: %s\n", wszMessage );
			break;
		}

		case UNABLE_TO_SEND_DATA_VIA_UART:
		{
			wprintf_s( L"Error during sending data via UART. Error message: %s\n", wszMessage );
			break;
		}

		case  UNABLE_TO_RECEIVE_DATA_VIA_UART:
		{
			wprintf_s( L"Error during receiving data via UART. Error message: %s\n", wszMessage );
			break;
		}

		case UNABLE_TO_READ_INPUT_VIA_FGETS:
		{
			printf_s( "Error during receiving data via UART. Error context: fgets" );
			break;
		}

		case UNABLE_TO_CREATE_THREAD:
		{
			wprintf_s( L"Unable to create thread for opening a COM port. Error message: %s\n", wszMessage );
			break;
		}
		
		case UNABLE_TO_CLOSE_THREAD_HANDLE:
		{
			wprintf_s( L"Unable to close thread handle. Error message: %s\n", wszMessage );
			break;
		}

		case UNABLE_TO_RESUME_THREAD:
		{
			wprintf_s( L"Unable to resume thread. Error message: %s\n", wszMessage );
			break;
		}

		case THREAD_FAILED:
		{
			wprintf_s( L"Thread failed. Error message: %s\n", wszMessage );
			break;
		}

		case UNABLE_TO_GET_EXIT_CODE_FROM_THREAD:
		{
			wprintf_s( L"Unable to get exit code from thread. Error message: %s\n", wszMessage );
			break;
		}

		case UNABLE_TO_SET_MONITORED_EVENTS:
		{
			wprintf_s( L"Unable to set monitored events for the COM port. Error message: %s\n", wszMessage );
			break;
		}

		case TOO_LONG_INPUT_OUTPUT_OPERATIONS:
		{
			printf_s( "Too long to complete the input and output operations before close the COM port. Error context: WaitToCompleteCOMPortsOperations\n" );
			break;
		}

		default:
		{
			printf_s( "Unknown Error\n" );
			break;
		}	
	} // switch

	// Free memory if necessary
	if ( lpMessageBuffer )
	{
		LocalFree( lpMessageBuffer );
		lpMessageBuffer = NULL;
	}
	
}
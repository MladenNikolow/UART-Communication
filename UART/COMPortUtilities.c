#include <stdio.h>
#include "COMPortUtilities.h"
#include "ErrorHandling.h"
#include "ConsoleReadWriteUtilities.h"
#include <ntddser.h>

/// The name of the COM port
#define COM_PORT_NAME												"COM4"
#define COM_PORT_NAME_LITERAL										L"COM4"

/// How much threads will create
#define MAX_ATTEMPTS_FOR_MAIN_THREAD_TO_OPEN_COM_PORT				5
/// How much times every thread will try to open a handle to COM port
#define MAX_ATTEMPTS_FOR_ADDITIONAL_THREAD_TO_OPEN_COM_PORT			2
/// Total tries = MAX_ATTEMPTS_FOR_MAIN_THREAD_TO_OPEN_COM_PORT * MAX_ATTEMPTS_FOR_ADDITIONAL_THREAD_TO_OPEN_COM_PORT

/// Max attempts to wait for the COM port to complete the operations
#define MAX_ATTEMPTS_TO_WAIT_FOR_COM_PORT_TO_COMPLETE_OPERATIONS	10000


bool IsHandleValid( const HANDLE hCOMPort )
{
	if ( hCOMPort == INVALID_HANDLE_VALUE || hCOMPort == NULL )
		return false;
	
	return true;
}

uint64_t WINAPI TryOpenCOMPort( LPVOID pArguments )
{
	THREAD_RESULT* pThreadResult = (THREAD_RESULT*)pArguments;

    HANDLE hCOMPort = INVALID_HANDLE_VALUE;
    int nAttempts = 1;

    while ( nAttempts <  ( MAX_ATTEMPTS_FOR_ADDITIONAL_THREAD_TO_OPEN_COM_PORT + 1 ) )
	{
        hCOMPort = CreateFile( COM_PORT_NAME_LITERAL
							 , GENERIC_READ | GENERIC_WRITE
							 , 0 /*dwShareMode*/
							 , 0 /*LPSECURITY_ATTRIBUTES*/
							 , OPEN_EXISTING
							 , FILE_ATTRIBUTE_NORMAL
							 , 0 /*hTemplateFile*/ );

		if ( IsHandleValid( hCOMPort ) )
		{
			printf_s( "Attempt %d to open \"%s\" succeeded.\n", nAttempts, COM_PORT_NAME );
			break;
		}
			
		HandleError( UNABLE_TO_OPEN_COM_PORT_VIA_CREATE_FILE );
		printf_s( "Attempt %d to open \"%s\" failed.\n", nAttempts, COM_PORT_NAME );
        ++nAttempts;
    }

	pThreadResult->nnHandleResult = (uint64_t)hCOMPort;

	// !!We retun the same result, but if it is INVALID_HANDLE_VALUE it will be cutted, 
	// so the real result is in the thread data!!
	return pThreadResult->nnHandleResult;
}

HANDLE OpenCOMPort()
{
	HANDLE hCOMPort = INVALID_HANDLE_VALUE;

	printf_s( "Opening COM Port...\n" );

	HANDLE hThread;
	DWORD threadId = 0UL;

	int nTryCount = 0;
	while ( nTryCount < MAX_ATTEMPTS_FOR_MAIN_THREAD_TO_OPEN_COM_PORT )
	{
		THREAD_RESULT oThreadResult;
        hThread = CreateThread( NULL, 0, TryOpenCOMPort, &oThreadResult, CREATE_SUSPENDED, &threadId );

        if ( hThread == NULL ) 
		{
            HandleError( UNABLE_TO_CREATE_THREAD );
            continue;
        }

		if ( ResumeThread( hThread ) == (DWORD) -1 )
		{
			HandleError( UNABLE_TO_RESUME_THREAD );
			continue;
		}

        // Wait for the thread to complete
		DWORD dwThreadResult = WAIT_TIMEOUT;
        while ( ( dwThreadResult = WaitForSingleObject( hThread, INFINITE ) ) == WAIT_TIMEOUT )
		{
		}

		if ( dwThreadResult != WAIT_OBJECT_0 )
		{
			HandleError( THREAD_FAILED );
			continue;
		}

        // Get the handle value returned by the thread
		uint64_t nnThreadResult = 0ULL;
        if ( !GetExitCodeThread( hThread, &nnThreadResult ) )
		{
			HandleError( UNABLE_TO_GET_EXIT_CODE_FROM_THREAD );
			continue;
		}

		hCOMPort = (HANDLE)oThreadResult.nnHandleResult;

        if ( IsHandleValid ( hCOMPort ) ) 
		{
			if ( !CloseHandle( hThread ) )
			{
				HandleError( UNABLE_TO_CLOSE_THREAD_HANDLE );
				return false;
			}

            break;
        }

        if ( !CloseHandle( hThread ) )
		{
			HandleError( UNABLE_TO_CLOSE_THREAD_HANDLE );
			return false;
		}

        ++nTryCount;
        printf_s( "Main thread try %d failed to get a valid handle.\n\n", nTryCount );
    }

	if ( !IsHandleValid( hCOMPort ) )
	{
		HandleError( UNABLE_TO_OPEN_COM_PORT_VIA_CREATE_FILE );
		return false;
	}

	printf_s( "Successfully opened COM port.\n" );

	return hCOMPort;
}

static void SetSerialParamateresByPortMode( const COMPortModes eCOMPortMode, DCB* pDcbSerialParams )
{
	if ( !pDcbSerialParams )
		return;

	pDcbSerialParams->DCBlength = sizeof( *pDcbSerialParams );
	pDcbSerialParams->ByteSize = 8;

	switch ( eCOMPortMode )
	{
		case DEFAULT_COM_PORT_MODE:
		{
			pDcbSerialParams->BaudRate = CBR_9600;
			pDcbSerialParams->Parity = NOPARITY;
			pDcbSerialParams->StopBits = ONESTOPBIT;
			break;
		}

		case ADDITIONAL_COM_PORT_MODE:
		{
			pDcbSerialParams->BaudRate = CBR_19200;
			pDcbSerialParams->fParity = TRUE;
			pDcbSerialParams->Parity = SPACEPARITY;
			pDcbSerialParams->StopBits = TWOSTOPBITS;
			break;
		}

		default:
			break;
	}
}

/// <summary> Configure parameters for the serial communication of the COM port </summary>
/// <param name="eCOMPortMode"> [IN] COM port mode </param>
/// <param name="hCOMPort"> [IN] Handle to COM port </param>
/// <returns> true on success, false on error </returns>
static bool ConfigureSerialPortParameters( const COMPortModes eCOMPortMode, HANDLE hCOMPort )
{
	if ( !IsHandleValid( hCOMPort ) )
	{
		HandleError( ATTEMPT_TO_CONFIGURE_INVALID_HANDLE_TO_COM_PORT );
		return false;
	}

	DCB dcbSerialParams = { 0 };
	if ( !GetCommState( hCOMPort, &dcbSerialParams ) )
	{
		HandleError( UNABLE_TO_GET_CURRENT_STATE_OF_COM_PORT );
		return false;
	}

	SetSerialParamateresByPortMode( eCOMPortMode, &dcbSerialParams );

	if ( !SetCommState( hCOMPort, &dcbSerialParams ) )
	{
		HandleError( UNABLE_TO_SET_STATE_OF_COM_PORT );
		return false;
	}

	return true;
}

/// <summary> Configure the timeouts of the serial communication of the COM port </summary>
/// <param name="hCOMPort"> [IN] Handle to COM port </param>
/// <returns> true on success, false on error </returns>
static bool ConfigureSerialPortTimeouts( HANDLE hCOMPort )
{
	if ( !IsHandleValid( hCOMPort ) )
	{
		HandleError( ATTEMPT_TO_CLOSE_INVALID_HANDLE_TO_COM_PORT );
		return false;
	}

	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout			= 50;
	timeouts.ReadTotalTimeoutConstant		= 50;
	timeouts.ReadTotalTimeoutMultiplier		= 10;
	timeouts.WriteTotalTimeoutConstant		= 50;
	timeouts.WriteTotalTimeoutMultiplier	= 10;

	if ( !SetCommTimeouts( hCOMPort, &timeouts ) ) 
	{
		HandleError( UNABLE_TO_SET_TIMEOUT_OF_COM_PORT );
		return false;
	}

	return true;
}

/// <summary> Configure the monitored events for the COM port </summary>
/// <param name="hCOMPort"> [IN] Handle to COM port </param>
/// <returns> true on success, false on error </returns>
static bool ConfigureSerialPortMontitoredEvents( hCOMPort )
{
	DWORD dwEvtMask = EV_RXCHAR
					  | EV_TXEMPTY
					  | EV_RXFLAG;

	if ( !SetCommMask( hCOMPort, dwEvtMask ) ) 
	{
		HandleError( UNABLE_TO_SET_MONITORED_EVENTS );
		return false;
	}

	return true;
}

bool ConfigureCOMPort( const COMPortModes eCOMPortMode, const bool bIsReconfiguration, const HANDLE hCOMPort )
{
	if ( !bIsReconfiguration )
		printf_s( "Configuring COM port.\n" );
	else
		printf_s( "Reconfiguring COM port.\n" );

	if ( !ConfigureSerialPortParameters( eCOMPortMode, hCOMPort ) )
		return false;

	if ( !ConfigureSerialPortTimeouts( hCOMPort ) )
		return false;

	if ( !ConfigureSerialPortMontitoredEvents( hCOMPort ) )
		return false;

	if ( !bIsReconfiguration )
		printf_s( "Succesfullty configured COM port.\n" );
	else
		printf_s( "Succesfullty reconfigured COM port.\n" );
	
	DCB dcbSerialParams = { 0 };
	if ( !GetCommState( hCOMPort, &dcbSerialParams ) )
	{
		HandleError( UNABLE_TO_GET_CURRENT_STATE_OF_COM_PORT );
		return false;
	}

	PrintSerialPortInformation( dcbSerialParams.BaudRate
							  , dcbSerialParams.Parity
							  , dcbSerialParams.StopBits );

	return true;
}

bool WaitToCompleteCOMPortsOperations( HANDLE hCOMPort )
{
	printf_s( "Checking the COM port for incompleted operations...\n" );

	if ( !IsHandleValid( hCOMPort ) )
	{
		HandleError( ATTEMPT_TO_CLOSE_INVALID_HANDLE_TO_COM_PORT );
		return false;
	}

	DWORD bytesTransferred = 0UL;
	OVERLAPPED overlapped = { 0 };

	short sCounter = 0;

	while ( !GetOverlappedResult( hCOMPort, &overlapped, &bytesTransferred, FALSE )
			&& GetLastError() == ERROR_IO_INCOMPLETE ) 
	{
		++sCounter;
		if ( sCounter >= MAX_ATTEMPTS_TO_WAIT_FOR_COM_PORT_TO_COMPLETE_OPERATIONS )
			return false;
	}

	printf_s( "All operations of the COM port are completed.\n" );

	return true;
}

bool CloseCOMPort( const HANDLE hCOMPort )
{
	printf_s("Closing COM Port...\n");

	if ( !IsHandleValid( hCOMPort ) )
	{
		HandleError( ATTEMPT_TO_CLOSE_INVALID_HANDLE_TO_COM_PORT );
		return false;
	}

	if ( !WaitToCompleteCOMPortsOperations( hCOMPort ) )
	{
		HandleError( TOO_LONG_INPUT_OUTPUT_OPERATIONS );
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
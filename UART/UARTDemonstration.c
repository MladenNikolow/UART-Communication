#include "Windows.h"
#include "UARTDemonstration.h"
#include "COMPortUtilities.h"
#include "UARTInterface.h"

GeneralErrorTypes DemonstrateAllUARTModes()
{
	bool bIsFirstIteration = true;

	for( int nCOMPortMode = DEFAULT_COM_PORT_MODE; nCOMPortMode < COM_PORT_MODES_COUNT; ++nCOMPortMode )
	{
		HANDLE hCOMPort = OpenCOMPort( !bIsFirstIteration );

		if ( !IsHandleValid( hCOMPort ) )
			return UNABLE_TO_OPEN_COM_PORT;

		if ( !ConfigureCOMPort( (COMPortModes)nCOMPortMode, !bIsFirstIteration, hCOMPort ) )
			return UNABLE_TO_CONFIGURE_COM_PORT;

		if ( !SendDataViaUART( hCOMPort ) )
			return UNABLE_TO_SEND_DATA;

		if ( !ReceiveDataViaUART( hCOMPort ) )
			return UNABLE_TO_RECEIVE_DATA;

		if ( !CloseCOMPort( hCOMPort ) )
			return UNABLE_TO_CLOSE_COM_PORT;

		if ( bIsFirstIteration )
			bIsFirstIteration = false;
	}

	return NO_GENERAL_ERROR;
}
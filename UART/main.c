#include "Windows.h"
#include "COMPortUtilities.h"
#include "ErrorTypes.h"

int main()
{
	HANDLE hCOMPort = INVALID_HANDLE_VALUE;
	if ( !OpenCOMPort( hCOMPort ) )
		return UNABLE_TO_OPEN_COM_PORT;

	if ( !ConfigureCOMPort( hCOMPort ) )
		return UNABLE_TO_CONFIGURE_COM_PORT;

	if ( !CloseCOMPort( hCOMPort ) )
		return UNABLE_TO_CLOSE_COM_PORT;

	return NO_ERROR;
}
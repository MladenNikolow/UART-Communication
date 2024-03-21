#include <stdbool.h>
#include <stdint.h>
#include "Windows.h"

/// <summary> COM port work modes </summary>
typedef enum
{
	/// <summary> Baud rate: CBR_9600, Parity: NOPARITY, One stop bit </summary>
	DEFAULT_COM_PORT_MODE		= 0

	/// <summary> Baud rate: CBR_19200, Parity: SPACEPARITY, Two stop bit </summary>
,	ADDITIONAL_COM_PORT_MODE


,	COM_PORT_MODES_COUNT
} COMPortModes;

/// <summary> Result of the thread </summary>
typedef struct 
{
	/// <summary> Decimal represented value of the HANDLE od the COM port </summary>
	uint64_t	nnHandleResult;
} THREAD_RESULT;

/// <summary> Function to be executed by the thread for opening a HANDLE to COM port </summary>
uint64_t WINAPI TryOpenCOMPort( LPVOID pArguments );

/// <summary> Open COM port </summary>
/// <returns> Handle to the COM port </returns>
HANDLE OpenCOMPort();

/// <summary> Open COM port </summary>
/// <param name="hCOMPort"> [IN] Handle to COM port </param>
/// <returns> true - valid, false - not valid </returns>
bool IsHandleValid( const HANDLE hCOMPort );

/// <summary> Configure COM port </summary>
/// <param name="eCOMPortMode"> [IN] COM port mode </param>
/// <param name="bIsReconfiguration"> [IN] Is reconfiguration ( already is configured once ) </param>
/// <param name="hCOMPort"> [IN/OUT] Handle to COM port </param>
/// <returns> true on success, false on error </returns>
bool ConfigureCOMPort( const COMPortModes eCOMPortMode, const bool bIsReconfiguration, const HANDLE hCOMPort );

/// <summary> Close COM port </summary>
/// <param name="hCOMPort"> [IN] Handle to COM port </param>
/// <returns> true on success, false on error </returns>
bool CloseCOMPort( const HANDLE hCOMPort );
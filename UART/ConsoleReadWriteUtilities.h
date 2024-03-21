#pragma once
#include <stdbool.h>

/// <summary> Print on the console information about the serial port </summary>
/// <param name="dwBaudRate"> Baud rate </param>
/// <param name="bParity"> Parity type </param>
/// <param name="bStopBits"> Stop bits </param>
void PrintSerialPortInformation( const DWORD dwBaudRate, const BYTE bParity, const BYTE bStopBits );

/// <summary> Read input message </summary>
/// <param name="szInputArray"> [OUT] Array read from the console </param>
/// <param name="nMaxSize"> [IN] Max size of the input array </param>
/// <returns> true on success, false on error </returns>
bool ReadInputMessage( char szInputArray[], const int nMaxSize );
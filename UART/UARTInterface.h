#pragma once
#include <Windows.h>
#include <stdbool.h>

/// <summary> Send message via UART </summary>
/// <param name="hCOMPort"> [IN] Handle to COM port </param>
/// <returns> true on success, false on error </returns>
bool SendDataViaUART( const HANDLE hCOMPort );

/// <summary> Receive message via UART </summary>
/// <param name="hCOMPort"> [IN] Handle to COM port </param>
/// <returns> true on success, false on error </returns>
bool ReceiveDataViaUART( const HANDLE  hCOMPort );
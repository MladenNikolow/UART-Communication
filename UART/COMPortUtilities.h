#include <stdbool.h>
#include "Windows.h"

/// <summary> Open COM port </summary>
/// <param name="hCOMPort"> [OUT] Handle to COM port </param>
/// <returns> true on success, false on error </returns>
bool OpenCOMPort( HANDLE hCOMPort );

/// <summary> Open COM port </summary>
/// <param name="hCOMPort"> [IN] Handle to COM port </param>
/// /// <returns> true - valid, false - not valid </returns>
bool IsHandleValid( HANDLE hCOMPort );

/// <summary> Configure COM port </summary>
/// <param name="hCOMPort"> [IN/OUT] Handle to COM port </param>
/// <returns> true on success, false on error </returns>
bool ConfigureCOMPort( HANDLE hCOMPort );

/// <summary> Close COM port </summary>
/// <param name="hCOMPort"> [IN] Handle to COM port </param>
/// <returns> true on success, false on error </returns>
bool CloseCOMPort( HANDLE hCOMPort );
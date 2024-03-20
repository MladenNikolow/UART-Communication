#pragma once

/// <summary> List of general error types </summary>
typedef enum
{
    NO_GENERAL_ERROR                            = 0
    , UNABLE_TO_OPEN_COM_PORT
    , UNABLE_TO_CLOSE_COM_PORT
    , UNABLE_TO_CONFIGURE_COM_PORT

} GeneralErrorTypes;

/// <summary> List of detailed error types </summary>
typedef enum 
{
    NO_DETAILED_ERROR                            = 0
    , UNABLE_TO_OPEN_COM_PORT_VIA_CREATE_FILE
    , UNABLE_TO_CLOSE_COM_PORT_VIA_CLOSE_HANDLE
    , ATTEMPT_TO_CLOSE_INVALID_HANDLE_TO_COM_PORT
    , ATTEMPT_TO_CONFIGURE_INVALID_HANDLE_TO_COM_PORT
    , UNABLE_TO_GET_CURRENT_STATE_OF_COM_PORT
    , UNABLE_TO_SET_STATE_OF_COM_PORT

    /// !!! If you add new error value, should describe the handling of the error in ErrorHandling.c !!!
} DetailedErrorTypes;
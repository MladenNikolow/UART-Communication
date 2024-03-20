#pragma once

/// <summary> List of general error types </summary>
typedef enum
{
    NO_GENERAL_ERROR                            = 0
    , UNABLE_TO_OPEN_COM_PORT
    , UNABLE_TO_CLOSE_COM_PORT
    , UNABLE_TO_CONFIGURE_COM_PORT
    , UNABLE_TO_SEND_DATA
    , UNABLE_TO_RECEIVE_DATA
    , UNABLE_TO_READ_INPUT

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
    , UNABLE_TO_SET_TIMEOUT_OF_COM_PORT
    , UNABLE_TO_SEND_DATA_VIA_UART
    , UNABLE_TO_RECEIVE_DATA_VIA_UART
    , UNABLE_TO_READ_INPUT_VIA_FGETS
    , UNABLE_TO_CREATE_THREAD
    , UNABLE_TO_CLOSE_THREAD_HANDLE
    , UNABLE_TO_RESUME_THREAD
    , THREAD_FAILED
    , UNABLE_TO_GET_EXIT_CODE_FROM_THREAD
    , UNABLE_TO_SET_MONITORED_EVENTS
    , TOO_LONG_INPUT_OUTPUT_OPERATIONS

    /// !!! If you add new error value, should describe the handling of the error in ErrorHandling.c !!!
} DetailedErrorTypes;
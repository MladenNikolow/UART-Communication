# UART-Communication
ANSI C console application, using WinAPI to open a COM port and send/receive data via UART interface.

The used platform toolset is Visual Studio 2022 (v143).

External dependency: POSIX ( pthread-win32 )
Steps to add the dependency:
1. Download zip file from the original repo: https://github.com/GerHobbelt/pthread-win32?fbclid=IwAR33gTtmBz-T5GcDpTphRMa1RNGRg8uxeDuA7t0r26xcyObLBcJBOLCf6Ec
2. Unzip the files
3. Build the project
4. Link .lib to the project
5. Add .dll file in a directory, that is visible for the project.

Additional required instructions before running the application:
1. Change the define for the name of the COM port: COM_PORT_NAME.

Additional optional instructions before running the application:
1. Choose max size of the message sended/received via UART interface ( MAX_UART_MESSAGE_SIZE ).
2. Choose how much tries to start a thread for opening the COM port ( MAX_ATTEMPTS_FOR_MAIN_THREAD_TO_OPEN_COM_PORT ).
3. Choose how much times every thread will try to open the COM port ( MAX_ATTEMPTS_FOR_ADDITIONAL_THREAD_TO_OPEN_COM_PORT ).

//==============================================================================

#ifndef _H_connexionclientapi
#define _H_connexionclientapi

#include <IOKit/IOKitLib.h>

#include "ConnexionClient.h"

//==============================================================================
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
// Callback procedure types

typedef void	(*ConnexionAddedHandlerProc)		(io_connect_t connection);
typedef void	(*ConnexionRemovedHandlerProc)		(io_connect_t connection);
typedef void	(*ConnexionMessageHandlerProc)		(io_connect_t connection, natural_t messageType, void *messageArgument);

//==============================================================================
// Public APIs to be called once when the application starts up or shuts down

OSErr			InstallConnexionHandlers			(ConnexionMessageHandlerProc messageHandler, ConnexionAddedHandlerProc addedHandler, ConnexionRemovedHandlerProc removedHandler);
void			CleanupConnexionHandlers			(void);

//==============================================================================
// Public APIs to be called whenever the app wants to start/stop receiving data
// the mask parameter (client capabilities mask) specifies which buttons and controls must be forwarded to the client

UInt16			RegisterConnexionClient			(UInt32 signature, UInt8 *name, UInt16 mode, UInt32 mask);
void			SetConnexionClientMask				(UInt16 clientID, UInt32 mask);
void			UnregisterConnexionClient			(UInt16 clientID);

//==============================================================================
// Public API to send control commands to the driver and retrieve a result value

OSErr			ConnexionControl					(UInt32 message, SInt32 param, SInt32 *result);

//==============================================================================
#ifdef __cplusplus
}
#endif
//==============================================================================

#endif	// _H_connexionclientapi

//==============================================================================

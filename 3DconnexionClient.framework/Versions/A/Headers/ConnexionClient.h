//==============================================================================

#ifndef _H_connexionclient
#define _H_connexionclient

//==============================================================================
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
#pragma pack(push,2)
//==============================================================================
// Client registration modes

// Use kConnexionClientWildcard ('****') as the application signature in the
// RegisterConnexionClient API to take over the device system-wide in all
// applications:

#define kConnexionClientWildcard		0x2A2A2A2A

// There are two plugin operating modes: one takes over the device
// and disables all built-in driver assignments, the other complements
// the driver by only executing commands that are meant for plugins:

enum {
	kConnexionClientModeTakeOver		= 1,	// take over device completely, driver no longer executes assignments
	kConnexionClientModePlugin			= 2		// receive plugin assignments only, let driver take care of its own
};

//==============================================================================
// Client commands

// The following assignments must be executed by the client:

enum {
	kConnexionCmdNone					= 0,
	kConnexionCmdHandleRawData			= 1,
	kConnexionCmdHandleButtons			= 2,
	kConnexionCmdHandleAxis				= 3,
	
	kConnexionCmdAppSpecific			= 10
};

//==============================================================================
// Messages

// IOServiceOpen and newUserClient client type:

#define kConnexionUserClientType		'3dUC'		// used to create our user client when needed, and the IOHIDDevice one otherwise

// The following messages are sent from the Kernel driver to user space clients:

#define kConnexionMsgDeviceState		'3dSR'		// forwarded device state data
#define kConnexionMsgDoAction			'3dDA'		// execute an action through the user space helper

// Control messages for the kernel driver sent via the ConnexionControl API:

#define kConnexionCtlSetLEDState		'3dsl'		// set the LED state, param = (UInt8)ledState
#define kConnexionCtlGetDeviceID		'3did'		// get vendorID and productID in the high and low words of the result
#define kConnexionCtlTypeKeystroke		'3dke'		// type a keystroke, param = ((modifiers << 16) | (keyCode << 8) | charCode)
#define kConnexionCtlRollWheel			'3dro'		// roll the mouse wheel, param = ((modifiers << 16) | (direction << 8) | amount) - note that modifier keys are NOT released
#define kConnexionCtlReleaseMods		'3dre'		// release modifier keys, param = (modifiers << 16)
#define kConnexionCtlCalibrate			'3dca'		// calibrate the device with the current axes values (same as executing the calibrate assignment)
#define kConnexionCtlUncalibrate		'3dde'		// uncalibrate the device (i.e. reset calibration to 0,0,0,0,0,0)

// Client capability mask constants (this mask defines which buttons and controls should be sent to clients, the others are handled by the driver)

#define kConnexionMaskButton1			0x0001
#define kConnexionMaskButton2			0x0002
#define kConnexionMaskButton3			0x0004
#define kConnexionMaskButton4			0x0008
#define kConnexionMaskButton5			0x0010
#define kConnexionMaskButton6			0x0020
#define kConnexionMaskButton7			0x0040
#define kConnexionMaskButton8			0x0080

#define kConnexionMaskAxis1				0x0100
#define kConnexionMaskAxis2				0x0200
#define kConnexionMaskAxis3				0x0400
#define kConnexionMaskAxis4				0x0800
#define kConnexionMaskAxis5				0x1000
#define kConnexionMaskAxis6				0x2000

#define kConnexionMaskButtons			0x00FF
#define kConnexionMaskAxisTrans			0x0700
#define kConnexionMaskAxisRot			0x3800
#define kConnexionMaskAxis				0x3F00
#define kConnexionMaskAll				0x3FFF

//==============================================================================
// Device state record

// Structure type and current version:

#define kConnexionDeviceStateType		0x4D53		// 'MS' (Connexion State)
#define kConnexionDeviceStateVers		0x6D32		// 'm2' (version 2)

// This structure is used to forward device data and commands from the kext to the client:

typedef struct {
// header
	UInt16		version;			// kConnexionDeviceStateVers
	UInt16		client;				// identifier of the target client when sending a state message to all user clients
// command
	UInt16		command;			// command for the user-space client
	SInt16		param;				// optional parameter for the specified command
	SInt32		value;				// optional value for the specified command
	UInt64		time;				// timestamp for this message (clock_get_uptime)
// raw report
	UInt8		report[8];			// raw USB report from the device
// processed data
	UInt16		buttons;			// buttons
	SInt16		axis[6];			// x, y, z, rx, ry, rz
// reserved for future use
	UInt16		address;			// USB device address, used to tell one device from the other
	UInt32		reserved2;			// set to 0
} ConnexionDeviceState, *ConnexionDeviceStatePtr;

// Size of the above structure:

#define kConnexionDeviceStateSize (sizeof(ConnexionDeviceState))

//==============================================================================
#pragma pack(pop)
//==============================================================================
#ifdef __cplusplus
}
#endif
//==============================================================================

#endif	// _H_connexionclient

//==============================================================================

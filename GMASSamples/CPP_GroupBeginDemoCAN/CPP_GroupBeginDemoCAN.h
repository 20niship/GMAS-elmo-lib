/*
============================================================================
 Name : CPP_GroupBeginDemo.h
 Author  :		Benjamin Spitzer
 Version :
============================================================================
*/
/*
============================================================================
 Project general functions prototypes
============================================================================
*/
void MainInit();
void MachineSequences();
void MainClose();
void MachineSequencesInit();
void EnableMachineSequencesTimer(int TimerCycle);
void BackgroundProcesses();
void MachineSequencesClose();
int MachineSequencesTimer();
void ReadAllInputData();
void WriteAllOutputData();
void InsertLongVarToModbusShortArr(short* spArr, long lVal) ;
int OnRunTimeError(const char *msg,  unsigned int uiConnHndl, unsigned short usAxisRef, short sErrorID, unsigned short usStatus) ;
void Emergency_Received(unsigned short usAxisRef, short sEmcyCode) ;
void ModbusWrite_Received() ;
void TerminateApplication(int iSigNum);
int  CallbackFunc(unsigned char* recvBuffer, short recvBufferSize,void* lpsock);
/*
============================================================================
 States functions
============================================================================
*/
void StateFunction_PTP();
void StateFunction_Home () ;
void StateFunction_Stop () ;
void StateFunction_GroupBeginMovePulses () ;
void MMCPP_InitConnection() ;
/*
============================================================================
 General constants
============================================================================
*/
#define 	MAX_AXES				1		// number of Physical axes in the system. TODO Update MAX_AXES accordingly
#define 	FALSE					0
#define 	TRUE					1
#define 	SYNC_MULTIPLIER			2
#define 	NUM_MOTIONS				10
//
// TODO: Modbus memory map offsets must be updated accordingly.
#define 	MODBUS_READ_OUTPUTS_INDEX	0	// Start of Modbus read address
#define 	MODBUS_READ_CNT				16	// Number of registers to read.
#define 	MODBUS_UPDATE_START_INDEX	16	// Start of Modbus write address (update to host)
#define 	MODBUS_UPDATE_CNT			16	// Number of registers to update
/*
============================================================================
 Project constants
============================================================================
*/
#define		SLEEP_TIME				10000	// Sleep time of the backround idle loop, in micro seconds
#define		TIMER_CYCLE				20		// Cycle time of the main sequences timer, in ms
/*
============================================================================
 States Machines constants
============================================================================
*/
#define 	FIRST_SUB_STATE			1

enum eMainStateMachines						// TODO: Change names of state machines to reflect dedicated project
{
	eIDLE		= 	0,
	ePTP		,						// Main state machine #1 - PTP
	eHomeAll	,						// Main state machine #2 - Home
	eStopAll	,						// Main state machine #3 - Stop
	eGroupBeginMovePulses	,			// Main state machine #4 - PTP start stop group
} ;

//
// Following values the giSubState1 parameter can receive while giState1 = ePTP
enum eSubStateMachine_PTP
{
	eSubState_SM1_PowerOff  = 1	 ,	// Power off
	eSubState_SM1_WPowerOff	 ,		// Wait power off
	eSubState_SM1_ChOPMode   ,		// Change Operation mode to PP
	eSubState_SM1_WChOPMode	 ,		// Wait till Operation mode == PP
	eSubState_SM1_PowerOn 	 ,		// Power on
	eSubState_SM1_WPowerOn 	 ,		// Wait until Power on
	eSubState_SM1_Move1 	 ,		// Perform first motion
	eSubState_SM1_WMove1 	 ,		// Wait until wnd of motion
	eSubState_SM1_Move2 	 ,		// Perform second motion
	eSubState_SM1_WMove2 	 ,		// Wait until end of 2nd motion
};
//
// Following values the giSubState1 parameter can receive while giState1 = eHome
enum eSubStateMachine_Home
{
	eSubState_SM2_PowerOff  = 1	 ,	// Power off
	eSubState_SM2_WPowerOff	 	 ,	// Wait power off
	eSubState_SM2_ChOPModeHome   ,	// Change Operation mode to Homing
	eSubState_SM2_WChOPModeHome	 ,	// Wait till Operation mode == Homing
	eSubState_SM2_PowerOn 	 ,		// Power on
	eSubState_SM2_WPowerOn 	 ,		// Wait until Power on
	eSubState_SM2_DOHOME 	 ,		// Perform Homing
	eSubState_SM2_WDOHOME 	 ,		// Wait until Homing ended
};								
//									
// Following values the giSubState1 parameter can receive while giState1 = eStop
enum eSubStateMachine_Stop
{
	eSubState_SM3_Stop  = 1	 ,		// Stop
	eSubState_SM3_WStop	 	 ,		// Wait until all came to a stop
	eSubState_SM3_PowerOff ,		// Power off
	eSubState_SM3_WPowerOff ,		// wait until power off
};
//
// Following values the giSubState1 parameter can receive while giState1 = eGroupBeginMovePulses
enum eSubStateMachine_GroupBeginMovePulses
{
	eSubState_SM4_PowerOff  = 1	 ,	// Power off
	eSubState_SM4_WPowerOff	 ,		// Wait power off
	eSubState_SM4_ChOPMode   ,		// Change Operation mode to PP
	eSubState_SM4_WChOPMode	 ,		// Wait till Operation mode == PP
	eSubState_SM4_PowerOn 	 ,		// Power on
	eSubState_SM4_WPowerOn 	 ,		// Wait until Power on
	eSubState_SM4_Move1 	 ,		// Perform first motion to 0 Position
	eSubState_SM4_WMove1 	 ,		// Wait until wnd of motion
	eSubState_SM4_Move2 	 ,		// Perform step motions as per direction
	eSubState_SM4_WMove2 	 ,		// Wait until end of step motion
	eSubState_SM4_DelayCycle	 ,	// Perform delay cycle
};
/*
============================================================================
 Application global variables
============================================================================
*/
int 	giTerminate;		// Flag to request program termination
int		giReentrance;		// Used to detect reentrancy to the main timer function
//
int 	giTempState1;		// Holds temp state
int 	giState1;			// Holds the current state of the main state machine
int 	giPrevState1;		// Holds the value of giState1 at previous cycle
int		giSubState1;		// Holds the current state of the sub-state machine
//
//
// 		Data read from the GMAS core regarding the X, Y drives
int 	giStatus[MAX_AXES] ;// Holds PLCopen statuses for all axes
int 	giPos[MAX_AXES] ;	// Holds position for all axes.
//
/*
============================================================================
 Global structures for Elmo's Function Blocks
============================================================================
*/
long long llIO_Val ;
MMC_CONNECT_HNDL gConnHndl ;					// Connection Handle
CMMCConnection cConn ;							// Connection class
CMMCSingleAxis 	cAxes[MAX_AXES] ;				// Single axis class
CMMCHostComm	cHost ;							// Modbus host class
CMMCDS401Axis	ds401 ;
MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN 	mbus_write_in;
MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_OUT 	mbus_write_out;
MMC_MOTIONPARAMS_SINGLE 	stSingleDefault ;	// Single axis default data
MMC_HOMEDS402_IN			stDS402Home ;		// standard DS402 input structure

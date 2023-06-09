/*
============================================================================
 Name : 	CPP_GroupBeginDemo.cpp
 Author :	Benjamin Spitzer
 Version :	1.00
 Description : The following example supports the following functionalities:

	 - Modbus callback registration.
	 - Emergency callback registration.
	 - PDO3 and SYNC initializations.
	 - Modbus reading and updates of axis status and positions.
 	 - Point to Point
 	 - Homing
 	 - Stop All axes
 	 - Move Pulses

 The program works with MAX_AXES in DS402 Profile Position and DS402 Homing motion modes. These are configured automatically by
 the called functions.
 For the above functions, the following modbus 'codes' are to be sent to address 40001:

 	 - Point to Point 	- 1. Performs a PP motion, back and fourth, and sets power off to all MAX_AXES.
 	 - Homing			- 2. Performs a Homing on index, and sets power off to all MAX_AXES.
 	 - Stop All axes	- 3. Stops current motion and sets all motors off to all MAX_AXES.
 	 - Move Pulses 		- 4. Performs synchronized motions for MAX_AXES, NUM_MOTIONS times. And then changes direction NUM_MOTIONS times.
 	  	  	  	  	  	  	  This works infinately until stopped (by calling Stop All axes).

- PDO3 is configured to update, per SYNC, all positions and velocities of axes.
- A sync is set in the system to SYNC_MULTIPLIER cycle time.

	The following information is updated to the Modbus at address MODBUS_UPDATE_START_INDEX:
		- All positions of axes, depending on MAX_AXES.

============================================================================
*/

#include "MMC_definitions.h"
#include "mmcpplib.h"
#include "CPP_GroupBeginDemoCAN.h"	// Application header file.
#include <iostream>
#include <sys/time.h>			// For time structure
#include <signal.h>				// For Timer mechanism
/*
============================================================================
 Function:				main()
 Input arguments:		None.
 Output arguments: 		None.
 Returned value:		None.
 Version:				Version 1.00
 Updated:				10/03/2011
 Modifications:			N/A

 Description:

 The main function of this  project.
============================================================================
*/

int main()
{
	//
	//	Initialize system, axes and all needed initializations
	//
	MainInit();
	//
	//	Execute the state machine to handle the system sequences and control
	//
	MachineSequences();
	//
	//	Close what needs to be closed before program termination
	//
	MainClose();
	//
	return 1;		// Terminate the application program back to the Operating System
}
/*
============================================================================
 Function:				MainInit()
 Input arguments:		None.
 Output arguments: 		None.
 Returned value:		None.
 Version:				Version 1.00
 Updated:				10/03/2011
 Modifications:			N/A

 Description:

 Initilaize the system, including axes, communication, etc.
============================================================================
*/
void MainInit()
{
//
//	Here will come initialization code for all system, axes, communication etc.
//
// 	InitializeCommunication to the GMAS:
//
	int 	i;
	char 	sAxisName[20] ;
	long 	lStatus ;
	//
	// Perform IPC connection and enable ALL
	gConnHndl = cConn.ConnectIPCEx(0x7fffffff,(MMC_MB_CLBK)CallbackFunc) ;
	//
	// Start the Modbus Server on device 1.
	cHost.MbusStartServer(gConnHndl,1) ;
	//
	// Register Run Time Error Callback function
	CMMCPPGlobal::Instance()->RegisterRTE(OnRunTimeError);
	//
	// Register the callback function for Modbus and Emergency:
	cConn.RegisterEventCallback(MMCPP_MODBUS_WRITE,(void*)ModbusWrite_Received) ;
	cConn.RegisterEventCallback(MMCPP_EMCY,(void*)Emergency_Received) ;
	//
	// Set default motion parameters
	stSingleDefault.fEndVelocity	= 0 ;
	stSingleDefault.dbDistance 		= 100000 ;
	stSingleDefault.dbPosition 		= 0 ;
	stSingleDefault.fVelocity 		= 100000 ;
	stSingleDefault.fAcceleration 	= 1000000 ;
	stSingleDefault.fDeceleration 	= 1000000 ;
	stSingleDefault.fJerk 			= 20000000 ;
	stSingleDefault.eDirection 		= MC_POSITIVE_DIRECTION ;
	stSingleDefault.eBufferMode 	= MC_BUFFERED_MODE ;
	stSingleDefault.ucExecute 		= 1 ;
	//
	// Initialize axis names and default parameters.
	for (i = 0 ; i < MAX_AXES ; i++)
	{
		sprintf(sAxisName, "a%02d",i+1);
		cAxes[i].InitAxisData(sAxisName,gConnHndl) ;
		cAxes[i].SetDefaultParams(stSingleDefault) ;
		lStatus = cAxes[i].ReadStatus() ;
		if(lStatus & NC_AXIS_ERROR_STOP_MASK)
		{
			cAxes[i].Reset() ;
		}
	}
	//
	// Wait a bit and recheck if in Error state:
	sleep(1) ;
	for (i = 0 ; i < MAX_AXES ; i++)
	{
		lStatus = cAxes[i].ReadStatus() ;
		if(lStatus & NC_AXIS_ERROR_STOP_MASK)
		{
			cout << "One of axes is in error. Exiting." ;
			exit(1) ;
		}
		// Config PDO Example for PDO3 - Event Group1
		// cAxes[i].ConfigPDO(PDO_NUM_3,PDO_PARAM_REG,NC_COMM_EVENT_GROUP1,1,1,1,1,1) ;

		//		PDO_NUMBER_ENUM ePDONum,
		//		PDO_PARAM_TYPE_ENUM eParamType,
		//		unsigned int uiPDOCommParamEvent- object 2f20 sub index 3. If on event, then states the mask to emit PDO
		//		unsigned short usEventTimer -
		//		unsigned char ucEventGroup - Event group type.
		//		unsigned char ucPDOCommParam,
		//		unsigned char ucSubIndex,
		//		unsigned char ucPDOType)
		// Config UI1 and UI2 to be sent OnChange from Drive to Host after emit is sent.
		cAxes[i].ConfigPDO(PDO_NUM_3,PDO_PARAM_USE,
				0x20,	// Bit 5. User program �emit� command emits PDO.
				0 ,		// Timer
				NC_COMM_EVENT_GROUP12,
				254,	// ucPDOCommParam
				1,		// Sub Index
				1) ;	// PDO Type. 0 RPDO. 1 TPDO

		cAxes[i].ConfigPDO(PDO_NUM_3,PDO_PARAM_USE,
						0x0,	// PDO Config
						0 ,		// Timer
						NC_COMM_RXEVENT_GROUP1, // UIs
						255,	// ucPDOCommParam
						3,		// Sub Index
						0) ;	// PDO Type. 0 RPDO. 1 TPDO
	}
	//
	// Initialize SYNC's in the system:
	//
	CMMCPPGlobal::Instance()->SetSyncTime(gConnHndl, SYNC_MULTIPLIER) ;
	//
	// Option if DS401 in system, Init the IO. Reset if in Error.
	// ds401.InitAxisData("i01",gConnHndl);
	//	lStatus = ds401.ReadStatus() ;
	//	if(lStatus & NC_AXIS_ERROR_STOP_MASK)
	//	{
	//		ds401.Reset() ;
	//		sleep(1) ;
	//		lStatus   = ds401.ReadStatus() ;
	//		if(lStatus & NC_AXIS_ERROR_STOP_MASK)
	//		{
	//			cout << "Axis a1 in Error Stop. Aborting." ;
	//			exit(0) ;
	//		}
	//	}
	//
	return;
}
/*
============================================================================
 Function:				MainClose()
 Input arguments:		None.
 Output arguments: 		None.
 Returned value:		None.
 Version:				Version 1.00
 Updated:				10/03/2011
 Modifications:			N/A

 Description:

 Close all that needs to be closed before the application progra, is
 terminated.
============================================================================
*/
void MainClose()
{
//
//	Here will come code for all closing processes
//
	cHost.MbusStopServer() ;
	MMC_CloseConnection(gConnHndl) ;
	return;
}
/*
============================================================================
 Function:				MachineSequences()
 Input arguments:		None.
 Output arguments: 		None.
 Returned value:		None.
 Version:				Version 1.00
 Updated:				10/03/2011
 Modifications:			N/A

 Description:

 Starts the Main Timer function that will execute the states machines
 to control the system. Also performs a slow background loop for
 less time-critical background processes and monitoring of requests
 to terminate the application.
============================================================================
*/
void MachineSequences()
{
//
//	Init all variables of the states machines
//
	MachineSequencesInit();
//
//	Enable MachineSequencesTimer() every TIMER_CYCLE ms
//
	EnableMachineSequencesTimer(TIMER_CYCLE);
//
//	Background loop. Handles termination request and other less time-critical background proceses
//
	while (!giTerminate)
	{
		//
		// Comment this line if need of timer or synchronised timer:
		MachineSequencesTimer();
//
//		Execute background process if required
//
		BackgroundProcesses();
//
//		Sleep for ~SLEEP_TIME micro-seconds to reduce CPU load
//
		usleep(SLEEP_TIME);
	}
//
//	Termination requested. Close what needs to be cloased at the states machines
//
	MachineSequencesClose();

	return;		// Back to the main() for program termination
}
/*
============================================================================
 Function:				MachineSequencesInit()
 Input arguments:		None.
 Output arguments: 		None.
 Returned value:		None.
 Version:				Version 1.00
 Updated:				10/03/2011
 Modifications:			N/A

 Description:

 Initilaize the states machines variables
============================================================================
*/
void MachineSequencesInit()
{
//
//	Initializing all variables for the states machines
//
	giTerminate 	= FALSE;

	giState1 		= eIDLE;
	giPrevState1 	= eIDLE;
	giSubState1 	= eIDLE;
	//
	giReentrance = FALSE;

	return;
}
/*
============================================================================
 Function:				MachineSequencesClose()
 Input arguments:		None.
 Output arguments: 		None.
 Returned value:		None.
 Version:				Version 1.00
 Updated:				10/03/2011
 Modifications:			N/A

 Description:

 Close all that needs to be closed at the states machines before the
 application program is terminated.
============================================================================
*/
void MachineSequencesClose()
{
//
//	Here will come code for all closing processes
//
	return;
}
/*
============================================================================
 Function:				BackgroundProcesses()
 Input arguments:		None.
 Output arguments: 		None.
 Returned value:		None.
 Version:				Version 1.00
 Updated:				10/03/2011
 Modifications:			N/A

 Description:

 Performs background processes that are not managed by the States Machines.
 This can be saving logs to the FLASH, performing background calculations etc.
 Generally speaking, this function, although colored in red in the Close all that needs to be closed at the states machines before the
 application program is terminated.
============================================================================
*/
void BackgroundProcesses()
{
//
//	Here will come code for all closing processes
//
	return;
}
/*
============================================================================
 Function:				EnableMachineSequencesTimer()
 Input arguments:		None.
 Output arguments: 		None.
 Returned value:		None.
 Version:				Version 1.00
 Updated:				10/03/2011
 Modifications:			N/A

 Description:

 Enables the main machine sequences timer function, to be executed each
 TIMER_CYCLE ms.
============================================================================
*/
void EnableMachineSequencesTimer(int TimerCycle)
{
	struct itimerval timer;
	struct sigaction stSigAction;

	// Whenever a signal is caught, call TerminateApplication function
	stSigAction.sa_handler = TerminateApplication;

	sigaction(SIGINT, &stSigAction, NULL);
	sigaction(SIGTERM, &stSigAction, NULL);
	sigaction(SIGABRT, &stSigAction, NULL);
	sigaction(SIGQUIT, &stSigAction, NULL);
//
//	Enable the main machine sequences timer function
//
	timer.it_interval.tv_sec 	= 0;
	timer.it_interval.tv_usec 	= TimerCycle * 1000;// From ms to micro seconds
	timer.it_value.tv_sec 		= 0;
	timer.it_value.tv_usec 		= TimerCycle * 1000;// From ms to micro seconds

	// setitimer(ITIMER_REAL, &timer, NULL);

	// signal(SIGALRM, MachineSequencesTimer); 		// every TIMER_CYCLE ms SIGALRM is received which calls MachineSequencesTimer()
	//
	// Start syncronized timer in system - only with firmware supporting this.  Currently only supported in CAN
	//	MMC_DestroySYNCTimer(gConnHndl) ;
	//	MMC_CreateSYNCTimer(gConnHndl,MachineSequencesTimer,1) ;
	return;
}
/*
============================================================================
 Function:				MachineSequencesTimer()
 Input arguments:		None.
 Output arguments: 		None.
 Returned value:		None.
 Version:				Version 1.00
 Updated:				10/03/2011
 Modifications:			N/A

 Description:

 A timer function that is called by the OS every TIMER_CYCLE ms.
 It executes the machine sequences states machines and actully controls
 the sequences and behavior of the machine.
============================================================================
*/
int MachineSequencesTimer(void)
{
//
//	In case the application is waiting for termination, do nothing.
//	This can happen if giTerminate has been set, but the background loop
//	didn't handle it yet (it has a long sleep every loop)
//
	if (giTerminate == TRUE) return 0;
//
//	Avoid reentrance of this time function
//
//	Reentrance can theoretically happen if the execution of this timer function
//	is wrongly longer than TIMER_CYCLE. In such case, reentrance should be avoided
//	to prevent unexpected behavior (the code is not designed for reentrance).
//
//	In addition, some error handling should be taken by the user.
//
	if (giReentrance)
	{
//
//		Print an error message and return. Actual code should take application related error handling
//
		printf("Reentrancy!\n");

		return 0;
	}

	giReentrance = TRUE;		// to enable detection of reentrancy. The flag is cleared at teh end of this function
	//
//
//	Read all input data.
//
//	Here, every TIMER_CYCLE ms, the user should read all input data that may be
//	required for the states machine code and copy them into "mirror" variables.
//
//	The states machines code, below, should use only the mirror variables, to ensure
//	that all input data is synchronized to the timer event.
//
//	Input data can be from the Host (MODBUS) or from the drives or I/Os units
//	(readingfrom the GMAS core firmware using one of the Function Blocks library
//	functions) or from any other source.
//
	ReadAllInputData();
/*
============================================================================

	States Machines code starts here!

============================================================================
*/

//
//	In case it is a new state value, clear also the value of the sub-state
//	to ensure it will start from its beginning (from the first ssub-state)
//
	if(giTempState1 != eIDLE)
	{
		giState1  = giTempState1 ;
	}

	if (giState1 != giPrevState1)
	{
		giSubState1 	= FIRST_SUB_STATE;
		giPrevState1 	= giState1;
		mbus_write_in.startRef 		= 0	;       // Reset Current state we are running on in Modbus so we do not return to it.
		mbus_write_in.refCnt 		= 1	;
		mbus_write_in.regArr[0] 	= 0;
		cHost.MbusWriteHoldingRegisterTable(mbus_write_in) ;
	}
//	Handle the main state machine.
//
//	The value of the State variable is used to make decisions of the main states machine and to call,
//	as necessary, the relevant function that handles to process itslef in a sub-state machine.
//
	switch (giState1)
	{
//
//		Do nothing, waiting for commands
//
		case eIDLE:
		{
			break;
		}
		case ePTP:
		{
			StateFunction_PTP();
			break;
		}
		case eHomeAll:
		{
			StateFunction_Home();
			break;
		}
		case eStopAll:
		{
			StateFunction_Stop();
			break;
		}
		case eGroupBeginMovePulses:
		{
			StateFunction_GroupBeginMovePulses();
			break;
		}
//
//		The default case. Should not happen, the user can implement error handling.
//
		default:
		{
			break;
		}
	}

//
//	Write all output data
//
//	Here, every TIMER_CYCLE ms, after the execution of all states machines
//	(based on all the Input Data as read from all sources at teh top of this function)
//	the user should write all output data (written into mirror variables within the
//	states machines code) to the "external world" (MODBUS, GMAS FW core, ...).
//
//	After alll states machines were executed and generated their outputs, the outputs
//	are writen to the "external world" to actually execute the states machines "decisions"
//
	WriteAllOutputData();
//
//	Clear the reentrancy flag. Now next execution of this function is allowed
//
	giReentrance = FALSE;
//
	return 1;		// End of the sequences timer function. The function will be triggered again upon the next timer event.
}
/*
============================================================================
 Function:				ReadAllInputData()
 Input arguments:		None.
 Output arguments: 		None.
 Returned value:		None.
 Version:				Version 1.00
 Updated:				10/03/2011
 Modifications:			N/A

 Description:

 The data used during the processing of the states machines must be synchronized with the
 timer event and must be "frozen" during the processing of all states machines code, so that
 all decisions and calculations will use the same data.

 This function is called at the beginning of the timer function, each TIMER_CYCLE ms,
 to collect all required input data (as relevant to each application) and to copy
 it into "mirror" variables, that will be used by the state machines code.
 ============================================================================
*/
void ReadAllInputData()
{
	MMC_MODBUSREADHOLDINGREGISTERSTABLE_OUT 	mbus_read_out;
	MMC_MODBUSREADHOLDINGREGISTERSTABLE_IN 		mbus_read_in;
	int i ;
	long UI1,UI2  ;
//
//	Here should come the code to read all required input data, for instance:
//
//
// The data read here may arrive from different sources:
// 	- Host Communication (Modbus, Ethernet-IP. This can be read on a cyclic basis, or from a callback.
//	- GMAS Firmware. Such as actual positions, torque, velocities.

	mbus_read_in.startRef 	= MODBUS_READ_OUTPUTS_INDEX;
	mbus_read_in.refCnt 	= 16 ;	// TODO: Change the number of registers to read.

	cHost.MbusReadHoldingRegisterTable(MODBUS_READ_OUTPUTS_INDEX,MODBUS_READ_CNT,mbus_read_out) ;

	giTempState1= (mbus_read_out.regArr[1] << 16 & 0xFFFF0000) | (mbus_read_out.regArr[0] & 0xFFFF);
	//
	for(i = 0 ; i < MAX_AXES ; i++)
	{
		giStatus[i] 	= cAxes[i].ReadStatus() ;
		giPos[i] 		= (int)cAxes[i].GetActualPosition() ;
	}
	//
	// In case a DS401 is defined in the system. Read Inputs.
	//	llIO_Val = ds401.ReadDS401DInput();
	//
	// Read UI From Drive:
	UI1 = cAxes[0].GetBoolParameter(MMC_I_COMM_EV_USR_1_PARAM,0) ;
	UI2 = cAxes[0].GetBoolParameter(MMC_I_COMM_EV_USR_1_AUX_PARAM,0) ;
	return;
}
/*
============================================================================
 Function:				WriteAllOutputData()
 Input arguments:		None.
 Output arguments: 		None.
 Returned value:		None.
 Version:				Version 1.00
 Updated:				10/03/2011
 Modifications:			N/A

 Description:

 Write all the data, generated by the states machines code, to the "external
 world".

 This is done here (and not inside the states machines code) to ensure that
 all data is updated simultaneously and in a synchronous way.

 The states machines code write the data into "mirror" variables, that are here
 copied or sent to the "external world" (Host via MODBUS, GMAS core firmware, etc.)
  ============================================================================
*/
void WriteAllOutputData()
{
	int i ;
	static int j = 1 ;
	j++ ;
//
//	Here should come the code to write/send all ouput data
//
	mbus_write_in.startRef 		= MODBUS_UPDATE_START_INDEX	;       // index of start write modbus register.
	mbus_write_in.refCnt 		= MAX_AXES *2			;			// number of indexes to write
	//
	for ( i = 0 ; i < MAX_AXES ; i++)
	{
		InsertLongVarToModbusShortArr(&mbus_write_in.regArr[i*2],  (long) giPos[i]) ;
	}
	cHost.MbusWriteHoldingRegisterTable(mbus_write_in) ;
	//
	// Option to write DS401 Outputs
	// ds401.WriteDS401DOutput(llIO_Val);
	//
	cAxes[0].SetBoolParameter(j,MMC_I_COMM_EV_USR_3_PARAM,0);
	return;
}
/*
============================================================================
 Function:				StateFunction_PTP()
 Input arguments:		None.
 Output arguments: 		None.
 Returned value:		None.
 Version:				Version 1.00
 Updated:				10/03/2011
 Modifications:			N/A

 Description:

 A sub-states machine function. This function executes the sub-states machine
 of the PTP process.

	 Change Operation Mode.
	 Power Enable
	 Start Point To Point
	 Wait for end of Point to Point
	 Change Direction back
	 Wait for End of Point to Point
	 Power Off

 Each step is handled by a dedicated function. However, calling a function
 is not a must and the relevant code for each sub-state can be directly
 written within the switch-case structure.
============================================================================
*/
void StateFunction_PTP()
{
	int i,iCnt ;
	iCnt = 0 ;
//
//	Handle the sub-state machine.
//
//	The value of the Sub-State variable is used to make decisions of the sub-states machine and to call,
//	as necessary, the relevant function that handles to process itself.
//
	switch (giSubState1)
	{
//
//		Perform sub SM 1
//
		case eSubState_SM1_PowerOff:
			for(i = 0 ; i < MAX_AXES ; i++)
			{
				// Disable only if power off.
				if (!(giStatus[i] & NC_AXIS_DISABLED_MASK))
					cAxes[i].PowerOff() ;
			}
			giSubState1 = eSubState_SM1_WPowerOff ;
			break ;
		case eSubState_SM1_WPowerOff:
			for(i = 0 ; i < MAX_AXES ; i++)
			{
				// Check we are actually off.
				if (giStatus[i] & NC_AXIS_DISABLED_MASK)
				{
					iCnt++ ;
				}
			}
			if(iCnt == MAX_AXES)
			{
				//
				// If we reached here, then all axss are off.
				giSubState1 	= eSubState_SM1_ChOPMode ;
			}
			break ;
		case eSubState_SM1_ChOPMode:
			for(i = 0 ; i < MAX_AXES ; i++)
			{
				//
				// Change OP mode to Profile Position.
				if(cAxes[i].GetOpMode() != OPM402_PROFILE_POSITION_MODE)
				{
					cAxes[i].SetOpMode(OPM402_PROFILE_POSITION_MODE) ;
				}
			}
			giSubState1 	= eSubState_SM1_WChOPMode ;
			break ;
		case eSubState_SM1_WChOPMode:
			for(i = 0 ; i < MAX_AXES ; i++)
			{
				//
				// Check we are in Profile Position in all axes:
				if(cAxes[i].GetOpMode() == OPM402_PROFILE_POSITION_MODE)
				{
					// PDO1, RX change default to OnSync
					cAxes[i].ChangeDefaultPDOConfig(1,0,1) ;
					//cAxes[i].SendSdoCmd(1,1,2,1,0x1400,0) ;
					iCnt++ ;
				}
			}
			if(iCnt == MAX_AXES)
			{
				//
				// If we reached here, then all axes are in Profile Position.
				giSubState1 = eSubState_SM1_PowerOn ;
			}
			break ;
		case eSubState_SM1_PowerOn:
		{
			//
			// Performs power on for all axes
			for (i =0 ; i < MAX_AXES ; i++)
			{
				if (giStatus[i] & NC_AXIS_DISABLED_MASK)
					cAxes[i].PowerOn() ;
			}
			//
			//	Changing to the next sub-state and wait until power is on.
			//
			giSubState1 = eSubState_SM1_WPowerOn;

			break;
		}
		case eSubState_SM1_WPowerOn:
		{
			for (i =0 ; i < MAX_AXES ; i++)
			{
				//
				// Check we are in standstill (power is on) for all axes:
				if (giStatus[i] & NC_AXIS_STAND_STILL_MASK)
				{
					iCnt++ ;
				}
			}
			if(iCnt == MAX_AXES)
			{
				//
				// If we reached here, then all axes are in standstill
				giSubState1 = eSubState_SM1_Move1;
			}

			break;
		}
		case eSubState_SM1_Move1:
		{
			//
			// Perform motion for all axes.
			for (i =0 ; i < MAX_AXES ; i++)
			{
				cAxes[i].MoveAbsolute(400000.0,100000,MC_ABORTING_MODE) ;
			}
			//
			//	Changing to the next sub-state
			//
			giSubState1 = eSubState_SM1_WMove1;

			break;
		}
		case eSubState_SM1_WMove1:
		{
			//
			//	Changing to the next sub-state only if axis changed to standstill.
			//
			for (i =0 ; i < MAX_AXES ; i++)
			{
				if (giStatus[i] & NC_AXIS_STAND_STILL_MASK)
				{
					iCnt++ ;
				}
			}
			if(iCnt == MAX_AXES)
			{
				//
				// If we reached here, then all axes are in standstill - All ended motion
				giSubState1 = eSubState_SM1_Move2;
			}
			break;
		}
		case eSubState_SM1_Move2:
			//
			// Set motion Back for all axes
			for(i = 0 ; i < MAX_AXES ; i++)
			{
				cAxes[i].MoveAbsolute(0.0,100000,MC_ABORTING_MODE) ;
			}
			giSubState1 = eSubState_SM1_WMove2 ;
			break ;
		case eSubState_SM1_WMove2:
			//
			// Check End of motion for all axes
			for(i = 0 ; i < MAX_AXES ; i++)
			{
				if (giStatus[i] & NC_AXIS_STAND_STILL_MASK)
				{
					iCnt++ ;
				}
			}
			if(iCnt == MAX_AXES)
			{
				//
				// If we reached here, then all axes are in standstill - All ended motion
				for(i = 0 ; i < MAX_AXES ; i++)
				{
					//
					// Power off all axes:
					cAxes[i].PowerOff() ;
				}
				giState1 = eIDLE;
			}
			break ;
//
//		The default case. Should not happen, the user can implement error handling.
//
		default:
		{
			break;
		}
	}
//
	return;
}
/*
============================================================================
 Function:				StateFunction_2()
 Input arguments:		None.
 Output arguments: 		None.
 Returned value:		None.
 Version:				Version 1.00
 Updated:				10/03/2011
 Modifications:			N/A

 Description:

 A sub-states machine function. This function executes the sub-states machine
 of the XY move process.

 The move prcess, in this simplified example consists of the following steps:

 Begin move
 Wait for end of motion

 Each step is handled by a dedicated function. However, calling a function
 is not a must and the relevant code for each sub-state can be directly
 written within the switch-case structure.
============================================================================
*/
void StateFunction_Home()
{
	int i ,iCnt;
	iCnt = 0 ;
//
//	Handle the sub-state machine.
//
//	The value of the Sub-State variable is used to make decisions of the sub-states machine and to call,
//	as necessary, the relevant function that handles to process itself.
//
	switch (giSubState1)
	{
		case eSubState_SM2_PowerOff:
			//
			// {Power off all axes:
			for(i = 0 ; i < MAX_AXES ; i++)
			{
				if (!(giStatus[i] & NC_AXIS_DISABLED_MASK))
					cAxes[i].PowerOff() ;
			}
			giSubState1 	= eSubState_SM2_WPowerOff ;
			break ;
		case eSubState_SM2_WPowerOff:
			//
			// wait until all axes are powered off:
			for(i = 0 ; i < MAX_AXES ; i++)
			{
				if (giStatus[i] & NC_AXIS_DISABLED_MASK)
				{
					iCnt++ ;
				}
			}
			if(iCnt == MAX_AXES)
			{
				//
				// If we reached here, all axes are powered off.
				giSubState1 	= eSubState_SM2_ChOPModeHome ;
			}
			break ;
		case eSubState_SM2_ChOPModeHome:

			//
			// Change to DS402 homing mode
			for(i = 0 ; i < MAX_AXES ; i++)
			{
				if(cAxes[i].GetOpMode() != OPM402_HOMING_MODE)
				{
					cAxes[i].SetOpMode(OPM402_HOMING_MODE) ;
				}
			}
			giSubState1 = eSubState_SM2_WChOPModeHome ;
			break ;
		case eSubState_SM2_WChOPModeHome:
			//
			// Wait until all axes are in homing mode.
			for(i = 0 ; i < MAX_AXES ; i++)
			{
				if(cAxes[i].GetOpMode() == OPM402_HOMING_MODE)
				{
					iCnt++ ;
				}
			}
			if(iCnt == MAX_AXES)
			{
				//
				// If we reached here, all axes are in homing mode.
				giSubState1 	= eSubState_SM2_PowerOn ;
			}
			break ;
		case eSubState_SM2_PowerOn:
		{
			//
			// Power on axes:
			for (i =0 ; i < MAX_AXES ; i++)
			{
				if (giStatus[i] & NC_AXIS_DISABLED_MASK)
					cAxes[i].PowerOn() ;
			}
			giSubState1 	= eSubState_SM2_WPowerOn ;
			break;
		}
		case eSubState_SM2_WPowerOn:
		{
			//
			// Wait until all axes are powered on
			for (i =0 ; i < MAX_AXES ; i++)
			{
				if (giStatus[i] & NC_AXIS_STAND_STILL_MASK)
				{
					iCnt++ ;
				}
			}
			if(iCnt == MAX_AXES)
			{
				//
				// If we reached here, all axes are powered on.
				giSubState1 = eSubState_SM2_DOHOME;
			}
			break;
		}
		case eSubState_SM2_DOHOME:
		{
			//
			// Set homing to method 33, and set axes speeds, acceleration, etc ...
			stDS402Home.dbPosition 		= -500 ;
			stDS402Home.fAcceleration	= 100000;
			stDS402Home.fVelocity		= 100000;
			stDS402Home.fDistanceLimit	= 100000;
			stDS402Home.fTorqueLimit	= 1;
			stDS402Home.eBufferMode		= MC_BUFFERED_MODE;
			stDS402Home.uiHomingMethod	= 33;
			stDS402Home.uiTimeLimit		= 100000;
			for (i =0 ; i < MAX_AXES ; i++)
			{
				cAxes[i].SetDefaultHomeDS402Params(stDS402Home) ;
				cAxes[i].HomeDS402() ;
			}
			giSubState1 = eSubState_SM2_WDOHOME;
			break;
		}
		case eSubState_SM2_WDOHOME:
		{
			//
			//	Wait Home Complete
			//
			for(i = 0 ; i < MAX_AXES ; i++)
			{
				if (giStatus[i] & NC_AXIS_STAND_STILL_MASK)
				{
					iCnt++ ;
				}
			}
			if(iCnt == MAX_AXES)
			{
				//
				// If we reached here, homing is complete.
				for(i = 0 ; i < MAX_AXES ; i++)
				{
					cAxes[i].PowerOff() ;
				}
				giState1 = eIDLE;
			}
			break ;
		}
//
//		The default case. Should not happen, the user can implement error handling.
//
		default:
		{
			break;
		}
	}
//
	return;
}

void StateFunction_Stop()
{
	int i ,iCnt;
	iCnt = 0 ;
//
//	Handle the sub-state machine.
//
//	The value of the Sub-State variable is used to make decisions of the sub-states machine and to call,
//	as necessary, the relevant function that handles to process itslef.
//
	switch (giSubState1)
	{
		case eSubState_SM3_Stop:
			//
			// Call stop to all axes.
			for(i = 0 ; i < MAX_AXES ; i++)
			{
				cAxes[i].Stop() ;
			}
			giSubState1 = eSubState_SM3_WStop ;
			break ;
		case eSubState_SM3_WStop:
			//
			// Wait until all axes stopped
			for(i = 0 ; i < MAX_AXES ; i++)
			{
				if (giStatus[i] & NC_AXIS_STAND_STILL_MASK)
				{
					iCnt++ ;
				}
			}
			if(iCnt == MAX_AXES)
			{
				//
				// If we reached here, then all axes came to a stop
				giSubState1 	= eSubState_SM3_PowerOff ;
			}
			break ;
		case eSubState_SM3_PowerOff:
			for(i = 0 ; i < MAX_AXES ; i++)
			{
				//
				// Simply power off.
				cAxes[i].PowerOff() ;
			}
			break ;
			default:
			{
				break;
			}
		}
//
//		The default case. Should not happen, the user can implement error handling.
//
//
	return;
}

void StateFunction_GroupBeginMovePulses()
{
	int i,iCnt ;
	iCnt = 0 ;
	static int iDelay = 0  ;	// Delay counter to stop between motions
	static int iDir = 0 ;		// Specifies the current direction of the drives
	static int iNumMotions = 0 ;// Number of motion in each direction that were performed
//
//	Handle the sub-state machine.
//
//	The value of the Sub-State variable is used to make decisions of the sub-states machine and to call,
//	as necessary, the relevant function that handles to process itself.
//
	switch (giSubState1)
	{
		case eSubState_SM4_PowerOff:
			//
			// Power Off all axes
			for(i = 0 ; i < MAX_AXES ; i++)
			{
				if (!(giStatus[i] & NC_AXIS_DISABLED_MASK))
					cAxes[i].PowerOff() ;
			}
			giSubState1 	= eSubState_SM4_WPowerOff ;
			break ;
		case eSubState_SM4_WPowerOff:
			//
			// Check all axes are powered off
			for(i = 0 ; i < MAX_AXES ; i++)
			{
				if (giStatus[i] & NC_AXIS_DISABLED_MASK)
				{
					iCnt++ ;
				}
			}
			if(iCnt == MAX_AXES)
			{
				//
				// If we reached here, then all axes are powered off.
				giSubState1 	= eSubState_SM4_ChOPMode ;
			}
			break ;
		case eSubState_SM4_ChOPMode:
			for(i = 0 ; i < MAX_AXES ; i++)
			{
				//
				// Change OP mode to Profile Position.
				if(cAxes[i].GetOpMode() != OPM402_PROFILE_POSITION_MODE)
				{
					cAxes[i].SetOpMode(OPM402_PROFILE_POSITION_MODE) ;
				}
			}
			giSubState1 	= eSubState_SM4_WChOPMode ;
			break ;
		case eSubState_SM4_WChOPMode:
			//
			// Check all axes are in Profiile Position
			for(i = 0 ; i < MAX_AXES ; i++)
			{
				if(cAxes[i].GetOpMode() == OPM402_PROFILE_POSITION_MODE)
				{
					//
					// If in Profile poition - change rx PDO1 to be On Sync
					// In order for all axes to begin together.
					// PDO1, RX change default to OnSync
					cAxes[i].ChangeDefaultPDOConfig(1,0,1) ;
					//cAxes[i].SendSdoCmd(1,1,2,1,0x1400,0) ;
					iCnt++ ;
				}
			}
			if(iCnt == MAX_AXES)
			{
				//
				// If we reached here, then all of the axes are in Profile Position
				giSubState1 	= eSubState_SM4_PowerOn ;
			}
			break ;
		case eSubState_SM4_PowerOn:
		{
			//
			// Power On all axes.
			for (i =0 ; i < MAX_AXES ; i++)
			{
				if (giStatus[i] & NC_AXIS_DISABLED_MASK)
					cAxes[i].PowerOn() ;
			}
			//
			//	Changing to the next sub-state
			//
			giSubState1 = eSubState_SM4_WPowerOn;

			break;
		}
		case eSubState_SM4_WPowerOn:
		{
			//
			// wait until all axes are powered on:
			for (i =0 ; i < MAX_AXES ; i++)
			{
				if (giStatus[i] & NC_AXIS_STAND_STILL_MASK)
				{
					iCnt++ ;
				}
			}
			if(iCnt == MAX_AXES)
			{
				//
				// If we reached here, then all axes are powered on.
				giSubState1 = eSubState_SM4_Move1;
			}
			break;
		}
		case eSubState_SM4_Move1:
		{
			//
			// Goto 0. Absolute
			for(i = 0 ; i < MAX_AXES ; i++)
			{
				cAxes[i].MoveAbsolute(0.0,100000,MC_ABORTING_MODE) ;
			}
			giSubState1 = eSubState_SM4_WMove1 ;

			break;
		}
		case eSubState_SM4_WMove1:
		{
			//
			// Wait until all axes reached Absolute position 0.
			for(i = 0 ; i < MAX_AXES ; i++)
			{
				if (giStatus[i] & NC_AXIS_STAND_STILL_MASK)
				{
					iCnt++ ;
				}
			}
			if(iCnt == MAX_AXES)
			{
				//
				// If we reached here, them all axes are at 0 position.
				iDir = 0 ;
				iNumMotions = 0 ;
				giSubState1 = eSubState_SM4_Move2 ;
			}

			break;
		}
		case eSubState_SM4_Move2:
			//
			// Move in opposite direction if already moved 10 times.
			if(iNumMotions > NUM_MOTIONS)
			{
				iNumMotions = 0 ;	// Reset motion counter
				iDir^=1 ;			// change direction
			}
			for(i = 0 ; i < MAX_AXES ; i++)
			{
				if(iDir)
				{
					cAxes[i].MoveRelative(1000) ;
				}
				else
				{
					cAxes[i].MoveRelative(-1000) ;
				}
			}
			iNumMotions++;
			giSubState1 = eSubState_SM4_WMove2 ;
			break ;
		case eSubState_SM4_WMove2:
			for(i = 0 ; i < MAX_AXES ; i++)
			{
				//
				// Check if motion ended
				if (giStatus[i] & NC_AXIS_STAND_STILL_MASK)
				{
					iCnt++ ;
				}
			}
			if(iCnt == MAX_AXES)
			{
				//
				// Reached here if all motions ended. State = STANDSTILL
				// Reset Delay counter between motions
				iDelay = 0 ;
				giSubState1 = eSubState_SM4_DelayCycle;
			}
			break ;
		case eSubState_SM4_DelayCycle:
			//
			// Time spent in this state machine depends on frequency this
			// state machine is called.
			iDelay++ ;
			if(iDelay > 10)
			{
				giSubState1 = eSubState_SM4_Move2;
			}
			break ;
//
//		The default case. Should not happen, the user can implement error handling.
//
		default:
		{
			break;
		}
	}
//
	return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Function name	:	void callback function																		//
//	Created			:	Version 1.00																				//
//	Updated			:	3/12/2010																					//
//	Modifications	:	N/A																							//
//	Purpose			:	interuprt function 																			//
//																													//
//	Input			:	N/A																							//
//	Output			:	N/A																							//
//	Return Value	:	int																							//
//	Modifications:	:	N/A																							//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CallbackFunc(unsigned char* recvBuffer, short recvBufferSize,void* lpsock)
{
	// Whcih function ID was received ...
	switch(recvBuffer[1])
	{
	case ASYNC_REPLY_EVT:
		printf("ASYNC event Reply\r\n") ;
		break ;
	case EMCY_EVT:
		// Please note - The emergency event was registered.
		// printf("Emergency Event received\r\n") ;
		break ;
	case MOTIONENDED_EVT:
		printf("Motion Ended Event received\r\n") ;
		break ;
	case HBEAT_EVT:
		printf("H Beat Fail Event received\r\n") ;
		break ;
	case PDORCV_EVT:
		printf("PDO Received Event received - Updating Inputs\r\n") ;
		break ;
	case DRVERROR_EVT:
		printf("Drive Error Received Event received\r\n") ;
		break ;
	case HOME_ENDED_EVT:
		printf("Home Ended Event received\r\n") ;
		break ;
	case SYSTEMERROR_EVT:
		printf("System Error Event received\r\n") ;
		break ;
		/* This is commented as a specific event was written for this function. Once it occurs
		 * the ModbusWrite_Received will be called
			case MODBUS_WRITE_EVT:
			// TODO Update additional data to be read such as function parameters.
			// TODO Remove return 0 if you want to handle as part of callback.
			return 0;
			printf("Modbus Write Event received - Updating Outputs\r\n") ;

			break ;
		*/
	}
	//
	return 1 ;
}

void MMC_MbusWriteHoldingRegisterTable_wrapper(MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN *mbus_write_in,MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_OUT *mbus_write_out)
{
	if (MMC_MbusWriteHoldingRegisterTable(gConnHndl, mbus_write_in,
			mbus_write_out) != 0) {
		printf("ERROR:%s: MMC_MbusWriteHoldingRegisterTable fail \n",
				__func__);
		exit(-1) ;
	}
}

void MMC_MbusReadHoldingRegisterTable_wrapper(MMC_MODBUSREADHOLDINGREGISTERSTABLE_IN *mbus_read_in, MMC_MODBUSREADHOLDINGREGISTERSTABLE_OUT *mbus_read_out)
{
	if (MMC_MbusReadHoldingRegisterTable(gConnHndl, mbus_read_in,
			mbus_read_out) != 0) {
		printf("ERROR:%s: MMC_MbusReadHoldingRegisterTable fail \n",
				__func__);
		exit(1);
	}
}

void MMC_MbusStopServer_wrapper()
{
	MMC_MODBUSSTOPSERVER_IN mbus_stopserver_in;
	MMC_MODBUSSTOPSERVER_OUT mbus_stopserver_out;

	if(MMC_MbusStopServer(gConnHndl, &mbus_stopserver_in, &mbus_stopserver_out)!=0)
	{
		printf("ERROR:%s: MMC_MbusStoptServer fail \n", __func__);
					MMC_CloseConnection(gConnHndl);
					exit(-1);
	}
}

void InsertLongVarToModbusShortArr(short* spArr, long lVal)
{
	*spArr 		= (short) (lVal	& 0xFFFF);
	*(spArr + 1)= (short)((lVal >> 16) 	& 0xFFFF);
}
int OnRunTimeError(const char *msg,  unsigned int uiConnHndl, unsigned short usAxisRef, short sErrorID, unsigned short usStatus)
{
	MMC_CloseConnection(uiConnHndl);
	printf("OnRunTimeError: %s,axis ref=%d, err=%d, status=%d, bye\n", msg, usAxisRef, sErrorID, usStatus);
	exit(0);
}

///////////////////////////////////////////////////////////////////////
//	Function name	:	void terminate_application(int iSigNum)
//	Created			:	Version 1.00
//	Updated			:	20/05/2010
//	Modifications	:	N/A
//	Purpose			:	Called in case application is terminated, stop modbus, engines, and power off engines
//	Input			:	int iSigNum - Signal Num.
//	Output			:	N/A
//	Return Value	:	void
//
//	Modifications:	:	N/A
//////////////////////////////////////////////////////////////////////
void TerminateApplication(int iSigNum)
{
	//
	printf("In Terminate Application ...\n");
	giTerminate = 1 ;
	sigignore(SIGALRM);
	//
	// Wait till other threads exit properly.
	sleep(1) ;
	return ;
}
//
// Callback Function once a Modbus message is received.
void ModbusWrite_Received()
{
	printf("Modbus Write Received\n") ;
}
//
// Callback Function once an Emergency is received.
void Emergency_Received(unsigned short usAxisRef, short sEmcyCode)
{
	printf("Emergency Message Received on Axis %d. Code: %x\n",usAxisRef,sEmcyCode) ;
}

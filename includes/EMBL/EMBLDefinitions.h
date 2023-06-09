/*
 * EMBLDefinitions.h
 *
 *  Created on: May 06, 2015
 *      Author: Ilia 
 */
//#define _DEBUG__
#ifdef _DEBUG__
//Debug mode - TRACE causes printf output
#include <stdio.h>
#define TRACE(string) fprintf(stderr,string);// params = "string \n"
#define TRACE2(string,val) fprintf(stderr,string,val);// params = "string \n", val
#define TRACE3(string,val1,val2) fprintf(stderr,string,val1,val2);// params = "string \n", val1,val2
#define TRACE4(string,val1,val2,val3) fprintf(stderr,string,val1,val2,val3);// params = "string \n", val1,val2,val3
#else
//Release mode - TRACE expands to nothing!
#define TRACE(params)
#define TRACE2(string,val)
#define TRACE3(string,val1,val2)
#define TRACE4(string,val1,val2,val3)
#endif // _DEBUG__


//for EMBL coordination.
#ifndef __cplusplus
#include <stdbool.h>
#endif



#ifndef EMBLDEFINITIONS_H_
#define EMBLDEFINITIONS_H_


#define MAX_SLAVES_NUM 99
typedef enum
{
	eSOCKET1 			= 0,
	eSOCKET2 			= 1,
	eSOCKET3 			= 2,
	eSOCKET4 			= 3
}EMBL_SOCKET_ENUM;

typedef struct embl_out
{
	unsigned int   uiHndl;///< Returned function block handle.
	unsigned short usStatus; ///< Returned function block handle.
	short          sErrorID;
}EMBL_OUT;

//typedef struct
//{
//	unsigned int   uiHndl;		///< Returned function block handle.
//	unsigned short usStatus;	///< Returned function block handle.
//	short usErrorID;	///< Returned function block handle.
//}EMBL_FB_OBJECT_OUT;
typedef enum
{
	eDOWNLOAD = 1,
	eUPLOAD = 2
}EMBL_SDO_SERVICE_ENUM;
//Feedback sensot ID

#define	QUAD_ENCODER_PORT_B					1
#define	QUAD_ENCODER_PORT_A					2
#define	ANALOG_SIN_COS						3
#define	DIGITAL_HALL_ONLY					4
#define	SERIAL_ABSOLUTE_BISS 				5
#define	SERIAL_ABSOLUTE_PANASONIC			6
#define	SERIAL_ABSOLUTE_MITUTOYO 			7
#define	VIRTUAL_TWO_SINE_SIGNAL 			8
#define	SERIAL_ABSOLUTE_ENDAT 				9
#define	SERIAL_ABSOLUTE_TAMAGAWA 			10
#define	PULSE_AND_DIRECTION_PORT_B 			11
#define	PULSE_AND_DIRECTION_PORT_A 			12
#define	QUAD_ENCODER_PORT_B_EMULATED 		13
#define	QUAD_ENCODER_PORT_A_EMULATED 		14
#define	COPY_PROFILER_TO_SOCKET 			15
#define	ANALOG_INPUT_1 						16
#define	VIRTUAL_ABSOLUTE_GURLEY 			17
#define	ABSOLUTE_SSI 						18
#define	SERIAL_ABSOLUTE_INCREMENTAL_YASKAWA 19
#define	GANTRY_MASTER 						20
#define	SERIAL_EXCLUSIVE  					21
#define	RESOLVER 							22
#define	SERIAL_ABSOLUTE_KAWASAKI 			23
#define	SERIAL_ABSOLUTE_GENERAL_BISS 		24
#define	SERIAL_ABSOLUTE_SANYO_NIKON 		25
#define	SIMPLE_PROFILER 					26
#define	COPY_GANTRY_DIFFERENTIAL_POSITION 	27
#define	SERIAL_HIPERFACE 					28
#define	FAST_REFERENCE  					29
#define	SERIAL_ABSOLUTE_ENDAT_2_2 			30
#define	PANASONIC_INCREMENTAL 				31
#define	SERIAL_EXCLUSIVE_2 					32
#define	SERIAL_EXCLUSIVE_3					33
#define	STEPPER_CLOSED_LOOP 				34
#define	PWM_DUTY_CYCLE 						35

///Homing Methods

#define HOME_ATTAIN_BIT		(0x00040000)


#define HOMING_ON_BLOCK_REVERSE -1
#define	HOMING_ON_BLOCK_FORWARD	-2

#define	HOMING_ON_RLS_FALLING_EDGE_AND_INDEX	1
#define	HOMING_ON_FLS_FALLING_EDGE_AND_INDEX	2
#define	HOMING_ON_RLS_FALLING_EDGE				17
#define	HOMING_ON_FLS_FALLING_EDGE				18

#define	HOME_ON_POSITIVE_SIDE_FALLING_EDGE_INDEX	3
#define	HOME_ON_POSITIVE_SIDE_RISING_EDGE_INDEX		4
#define	HOME_ON_NEGATIVE_SIDE_FALLING_EDGE_INDEX	5
#define	HOME_ON_NEGATIVE_SIDE_RISING_EDGE_INDEX		6

#define	HOME_ON_POSITIVE_SIDE_FALLING_EDGE 	19
#define	HOME_ON_POSITIVE_SIDE_RISING_EDGE	20
#define	HOME_ON_NEGATIVE_SIDE_FALLING_EDGE 	21
#define	HOME_ON_NEGATIVE_SIDE_RISING_EDGE 	22

#define	HOME_ON_NEGATIVE_SIDE_FALLING_EDGE_INDEX_FLS 	7
#define	HOME_ON_NEGATIVE_SIDE_RISING_EDGE_INDEX_FLS 	8
#define	HOME_ON_POSITIVE_SIDE_RISING_EDGE_INDEX_FLS	    9
#define	HOME_ON_POSITIVE_SIDE_FALLING_EDGE_INDEX_FLS 	10

#define	HOME_ON_NEGATIVE_SIDE_FALLING_EDGE_FLS 	23
#define	HOME_ON_NEGATIVE_SIDE_RISING_EDGE_FLS 	24
#define	HOME_ON_POSITIVE_SIDE_RISING_EDGE_FLS	25
#define	HOME_ON_POSITIVE_SIDE_FALLING_EDGE_FLS 	26

#define	HOME_ON_POSITIVE_SIDE_FALLING_EDGE_INDEX_RLS 	11
#define	HOME_ON_POSITIVE_SIDE_RISING_EDGE_INDEX_RLS	    12
#define	HOME_ON_NEGATIVE_SIDE_RISING_EDGE_INDEX_RLS 	13
#define	HOME_ON_NEGATIVE_SIDE_FALLING_EDGE_INDEX_RLS 	14

#define	HOME_ON_POSITIVE_SIDE_FALLING_EDGE_RLS 	27
#define	HOME_ON_POSITIVE_SIDE_RISING_EDGE_RLS	28
#define	HOME_ON_NEGATIVE_SIDE_RISING_EDGE_RLS 	29
#define	HOME_ON_NEGATIVE_SIDE_FALLING_EDGE_RLS 	30

#define	HOME_ON_INDEX_NEGATIVE_MOVE 	33
#define	HOME_ON_INDEX_POSITIVE_MOVE 	34
#define HOME_IMMEDIATE_ON_CURRENT_POSITION 35

//ERRORS
#define POWER_DISABLE_ERRORID	-10

#define HOMING_METHOD_NOTSUTIABLE_FOR_THIS_FEEDBACK  	-5000
#define VERIFICATION_TIMEOUT_ELAPSED  					-5001
#define COULD_NOT_FIND_FREE_SOCKET_FOR_EMULATION 		-5002
#define PULSE_DULATION_TIME_LIMIT_OUT_OF_RANGE		 	-5003
#define FIRST_PULSE_ABS_POSITION_OUT_OF_RANGE	 		-5004
#define ARRAY_SIZE_OUT_OF_RANGE	 				 		-5005
#define ARRAY_ISNOT_CONSISTENCY	 				 		-5006
#define AXIS_ERROR_STOP_MASK   							-5007 /// GMAS NC_AXIS_ERROR_STOP_MASK 0x00000400

#define ECAM_CAMIN_SLAVE_INVLAID_STATE	 				-5100
#define ILLEGAL_READ_PI_FUNTION							-5101
#define ECAM_INVALID_DATA_TABLE							-5102
#define ECAM_INVALID_OFFSET_TABLE						-5103
#endif /* EMBLDEFINITIONS_H_ */

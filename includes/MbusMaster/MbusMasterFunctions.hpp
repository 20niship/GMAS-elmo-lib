/**
 * @internal
 * @file MbusMasterFunctions.hpp
 *
 * @if NOTICE
 *
 * $Id: MbusMasterFunctions.hpp,v 1.18 2006/10/19 04:20:41 henrik Exp $
 *
 * Copyright (c) 2002-2006 FOCUS Software Engineering Pty Ltd, Australia.
 * All rights reserved. <www.focus-sw.com>
 *
 * USE OF THIS SOFTWARE IS GOVERNED BY THE TERMS AND CONDITIONS OF A
 * SEPARATE LICENSE STATEMENT AND LIMITED WARRANTY.
 *
 * IN PARTICULAR, YOU WILL INDEMNIFY AND HOLD FOCUS SOFTWARE ENGINEERING,
 * ITS RELATED COMPANIES AND ITS SUPPLIERS, HARMLESS FROM AND AGAINST ANY
 * CLAIMS OR LIABILITIES ARISING OUT OF THE USE, REPRODUCTION, OR
 * DISTRIBUTION OF YOUR PROGRAMS, INCLUDING ANY CLAIMS OR LIABILITIES
 * ARISING OUT OF OR RESULTING FROM THE USE, MODIFICATION, OR DISTRIBUTION
 * OF PROGRAMS OR FILES CREATED FROM, BASED ON, AND/OR DERIVED FROM THIS
 * SOURCE CODE FILE.
 *
 * @endif
 */


#ifndef _MBUSMASTERFUNCTIONS_H_INCLUDED
#define _MBUSMASTERFUNCTIONS_H_INCLUDED

#ifndef __cplusplus
#  error Must use C++ to compile this module!
#endif

// Package header
#include "hmtimer.hpp"
#include "BusProtocolErrors.h"


/*****************************************************************************
 * MbusMasterFunctions class declaration
 *****************************************************************************/

/**
 * @brief Base class which implements Modbus data and control functions
 *
 * The functions provided by this base class apply to all protocol flavours
 * via inheritance. For a more detailed description see section @ref
 * mbusmaster.
 *
 * @see mbusmaster
 * @see MbusSerialMasterProtocol, MbusRtuMasterProtocol
 * @see MbusAsciiMasterProtocol, MbusTcpMasterProtocol
 */
class
#if defined (_WINDLL) || defined(__DLL__)
   __declspec(dllexport)
#endif
MbusMasterFunctions
{

  protected:

   enum
   {
      MAX_DATA_SIZE = 10 + 250 // Max. size for 125 words
   };

   volatile unsigned long totalCounter;
   volatile unsigned long successCounter;
   int retryCnt;  // Retry counter
   int timeOut;   // Time-out in ms
   int pollDelay; // Delay between two Modbus read/writes in ms
   Timer silenceTimer;


  private:

   char bufferArr [MAX_DATA_SIZE];
   int bigEndianMachine;      // Auto-configured by constructor
   int bigEndianFloatMachine; // Auto-configured by constructor
   int swapInts;              // User flags
   int swapFloats;            // User flags


  protected:

    MbusMasterFunctions();


  public:

   virtual ~MbusMasterFunctions();


   /**************************************************************************
    * Modbus function codes
    **************************************************************************/

  public:

   /**
    * @name Bit Access
    * Table 0:00000 (Coils) and Table 1:0000 (Input Status)
    * @ingroup mbusmaster
    */
   //@{

   int readCoils(int slaveAddr, int startRef,
                 int bitArr[], int refCnt);

   int readInputDiscretes(int slaveAddr, int startRef,
                          int bitArr[], int refCnt);

   int writeCoil(int slaveAddr, int bitAddr, int bitVal);

   int forceMultipleCoils(int slaveAddr, int startRef,
                          const int bitArr[], int refCnt);

   //@}


   /**
    * @name 16-bit Access
   *  Table 4:00000 (Holding Registers) and Table 3:00000 (Input Registers)
    * @ingroup mbusmaster
    */
   //@{

   int readMultipleRegisters(int slaveAddr,
                             int startRef,
                             short regArr[], int refCnt);

   int readInputRegisters(int slaveAddr, int startRef,
                          short regArr[], int refCnt);

   int writeSingleRegister(int slaveAddr, int regAddr, short regVal);

   int writeMultipleRegisters(int slaveAddr,
                              int startRef,
                              const short regArr[], int refCnt);

   int maskWriteRegister(int slaveAddr, int regAddr,
                         short andMask, short orMask);

   int readWriteRegisters(int slaveAddr,
                          int readRef, short readArr[], int readCnt,
                          int writeRef,
                          const short writeArr[], int writeCnt);
   //@}

   /**
    * @name 32-bit Access
   *  Table 4:00000 (Holding Registers) and Table 3:00000 (Input Registers)
    * @ingroup mbusmaster
    */
   //@{

   int readMultipleLongInts(int slaveAddr,
                            int startRef,
                            long int32Arr[], int refCnt);

   int readInputLongInts(int slaveAddr,
                         int startRef,
                         long int32Arr[], int refCnt);

   int writeMultipleLongInts(int slaveAddr,
                             int startRef,
                             const long int32Arr[], int refCnt);

   int readMultipleFloats(int slaveAddr,
                          int startRef,
                          float float32Arr[], int refCnt);

   int readInputFloats(int slaveAddr,
                       int startRef,
                       float float32Arr[], int refCnt);

   int writeMultipleFloats(int slaveAddr,
                           int startRef,
                           const float float32Arr[], int refCnt);

   int readMultipleMod10000(int slaveAddr,
                            int startRef,
                            long int32Arr[], int refCnt);

   int readInputMod10000(int slaveAddr,
                         int startRef,
                         long int32Arr[], int refCnt);

   int writeMultipleMod10000(int slaveAddr,
                             int startRef,
                             const long int32Arr[], int refCnt);

   //@}


   /**
    * @name Diagnostics
    * @ingroup mbusmaster
    */
   //@{

   int readExceptionStatus(int slaveAddr, unsigned char *statusBytePtr);

   int returnQueryData(int slaveAddr,
                       const unsigned char queryArr[],
                       unsigned char echoArr[], int len);

   //@}


   /**************************************************************************
    * Protocol Configuration
    **************************************************************************/

   /**
    * @name Protocol Configuration
    * @ingroup mbusmaster
    */
   //@{

  public:

    int setTimeout(int timeOut);


   /**
    * Returns the time-out value.
    *
    * @remark The time-out value is indicative only and not guaranteed to
    * be maintained. How precise it is followed depends on the operating
    * system used, it's scheduling priority and it's system timer
    * resolution.
    * @return Timeout value in ms
    */
   int getTimeout() { return (timeOut); }


   int setPollDelay(int pollDelay);


   /**
    * Returns the poll delay time.
    *
    * @return Delay time in ms, 0 if poll delay is switched off
    */
   int getPollDelay() { return (pollDelay); }


   int setRetryCnt(int retryCnt);


   /**
    * Returns the automatic retry count.
    *
    * @return Retry count
    */
   int getRetryCnt() { return (retryCnt); }

   //@}


   /**************************************************************************
    * Transmission Statistic Functions
    **************************************************************************/

   /**
    * @name Transmission Statistic Functions
    * @ingroup mbusmaster
    */
   //@{

  public:

   /**
    * Returns how often a message transfer has been executed.
    *
    * @return Counter value
    */
   long getTotalCounter() { return (totalCounter); }

   /**
    * Resets total message transfer counter.
    */
   void resetTotalCounter() { totalCounter = 0UL; }

   /**
    * Returns how often a message transfer was successful.
    *
    * @return Counter value
    */
   long getSuccessCounter() { return (successCounter); }

   /**
    * Resets successful message transfer counter.
    */
   void resetSuccessCounter() { successCounter = 0UL; }

   //@}


   /**************************************************************************
    * Word Order Configuration
    **************************************************************************/

  public:

   /**
    * @name Word Order Configuration
    * @ingroup mbusmaster
    */
   //@{

   void configureBigEndianInts();

   void configureSwappedFloats();

   void configureLittleEndianInts();

   void configureIeeeFloats();

   //@}


   /**************************************************************************
    * Utility routines
    **************************************************************************/

  public:

   virtual int isOpen();

   /**
    * Closes an open protocol including any associated communication
    * resources (com ports or sockets).
    */
   virtual void closeProtocol() { }

   static TCHAR *getPackageVersion();


   /**************************************************************************
    * Internal subroutines
    **************************************************************************/

  protected:

   virtual int deliverMessage(int address, int function,
                              char sendDataArr[], int sendDataLen,
                              char rcvDataArr[], int rcvDataLen) = 0;

  private:

   int readBits(int function, int slaveAddr, int startRef,
                int bitArr[], int refCnt);

   int readRegisters(int function, int slaveAddr, int startRef,
                     short regArr[], int refCnt);


  private:

   // Disable default operator and copy constructor
   MbusMasterFunctions &operator= (MbusMasterFunctions &);
   MbusMasterFunctions (const MbusMasterFunctions &);

};


#endif // ifdef ..._H_INCLUDED


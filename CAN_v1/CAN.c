/*************************************************************************************************************************************/
/* Name:   CAN.c                                                                                                                    */
/* Author: Madonna Magdy                                                                                                             */
/* Version: V1                                                                                                                       */
/* Usage: This module contains the implementation for the CAN functions                                                             */
/*************************************************************************************************************************************/

  /************************************ Includes ************************************/
  #include "lstd.h"
  #include "SystemControl.h"
  #include "CAN_config.h"
  #include "CAN_reg.h"

  #include "NVIC.h"
  #include "GPIO.h"
  #include "GPIO_config.h"

volatile static CANCTL_Reg* const CAN_ControlReg_Arr[CAN_ChannelNum_Indicies]={
         CAN0_CONTROL_Reg,
         CAN1_CONTROL_Reg
};

volatile static CANBIT_Reg* const CAN_BitTimingReg_Arr[CAN_ChannelNum_Indicies]={
     CAN0_BITTIMING_REG,
     CAN1_BITTIMING_REG
};

volatile static CANIFnCMSK_Reg* const CAN_IFn_CommandMask[CAN_ChannelNum_Indicies][CAN_InterfaceNum_Indicies]={

             {CAN0_IF1_CommandMask_Reg,
              CAN0_IF2_CommandMask_Reg
             },

             {
              CAN1_IF1_CommandMask_Reg,
              CAN1_IF2_CommandMask_Reg
             }
};

volatile static CANIFnMCTL_Reg* const CAN_IFn_MessageCtlReg[CAN_ChannelNum_Indicies][CAN_InterfaceNum_Indicies]={
           {
            CAN0_IF1_MessageCtl_Reg,
            CAN0_IF2_MessageCtl_Reg
            },

            {
             CAN1_IF1_MessageCtl_Reg,
             CAN1_IF2_MessageCtl_Reg
            }
};

//#define CAN0_IF1_Arbitration2_Reg  ((volatile CANIFnARB2_Reg*)(CAN0_BaseAddress + 0x034))
/*volatile static CANIFnARB2_Reg* const CAN0_IF1_Arbitration2_Reg[CAN_ChannelNum_Indicies][CAN_InterfaceNum_Indicies]={

};*/


void CAN_Initialization(GPIO_CANConfigChannel_t* pt_CANConfigChannel, CAN_ConfigurationChannel_t*pt_CAN_ConfigurationChannel){

    /*STEP 1- Provide clk to the CAN Module*/
    /*To use the CAN controller, the peripheral clock must be enabled using the RCGC0 register*/
    SC_CAN_ClkIntialization(pt_CAN_ConfigurationChannel->SYSCTL_ConfigCANmoduleNum);

    /*STEP 2-Enable the alternative function select for the two pins Tx pin and Rx pin */
    /*the clock to the appropriate GPIO module must be enabled via the RCGC2
      register*/
    GPIO_EnableAFSEL_CAN(pt_CANConfigChannel);

    /*STEP 3-set the two bits for INIT and CCE in the control register to enable write access on the CANBIT register*/
    CAN_ControlReg_Arr[pt_CAN_ConfigurationChannel->ChannelNumIndexArr]->bits.INIT=1;
    CAN_ControlReg_Arr[pt_CAN_ConfigurationChannel->ChannelNumIndexArr]->bits.CCE=1;

    /*=================================== STEP 4- Calculating the bit Timing =========================================*/
    /*Freq of the CAN Clock is 16MHz and bit rate is 100k Mbps
     * bit time = 10micro sec
     * ############## BRP=16 ######################
     * */
    CAN_BitTimingReg_Arr[pt_CAN_ConfigurationChannel->ChannelNumIndexArr]->bits.BRP=pt_CAN_ConfigurationChannel->BaudRatePresVar;

    /*bit rate is 100 Kbps
     *bit time = 10 μs = n * tq = 10 * tq
     *tq = 1 μs
     *
     *
     * tSync = 1*tq= 1 micro sec fixed at 1 time quantum
     *tProp 1 µs = 1 * tq
     *
     *bit time = tSync + tTSeg1 + tTSeg2 = 10 * tq
      bit time = tSbit time = n*tq = 10*tq
     * tq = (Baud rate Pre-scaler)/CAN Clock =(16/16*(10^(6))) = 1 micro-sec
     * tq= 1 micro sec
     * tq= baudrate / CAN Clock
     * baudRate= tq*CAN Clock=16
     *
     *tSync = 1 * tq = 1 micro-sec fixed at one time quanta
     *tProp 1 µs = 1 * tq
     *
     * Sync + tProp + tPhase 1 + tPhase2
      tPhase 1 + tPhase2 = bit time - tSync - tProp
      tPhase 1 + tPhase2 = (10 * tq) - (1 * tq) - (1 * tq)
      tPhase 1 + tPhase2 = 8 * tq

      tPhase1 = 4 * tq
      tPhase2 = 4 * tq         tPhase1 = tPhase2

      tTSeg1 = tProp + tPhase1
      tTSeg1 = (1 * tq) + (4 * tq)
      tTSeg1 = 5 * tq
      TSEG1=tTSeg1-1=4

      tTSeg2 = tPhase2
      tTSeg2 = (Information Processing Time + 4) × tq
      tTSeg2 = 4 * tq
      TSEG2=4-1=3 Assumes IPT=0

      tSJW = 4 * tq   Least of 4, Phase1, and Phase2
      4-1=3
      */

    CAN_BitTimingReg_Arr[pt_CAN_ConfigurationChannel->ChannelNumIndexArr]->bits.TSEG1=pt_CAN_ConfigurationChannel->TimeSegBeforeSampleVar;
    CAN_BitTimingReg_Arr[pt_CAN_ConfigurationChannel->ChannelNumIndexArr]->bits.TSEG2=pt_CAN_ConfigurationChannel->TimeSegAfterSampleVar;

    CAN_BitTimingReg_Arr[pt_CAN_ConfigurationChannel->ChannelNumIndexArr]->bits.SJW=pt_CAN_ConfigurationChannel->SyncJumpWidthVar;


    /*STEP 5- init bit must be cleared in order to leave the initialization state */
    CAN_ControlReg_Arr[pt_CAN_ConfigurationChannel->ChannelNumIndexArr]->bits.INIT=0;
}

void CAN_Transmit_Polling_MessageObject(CAN_ConfigurationChannel_t*pt_CAN_ConfigurationChannel){

    /*===============================STEP 1=========================================*/

    /*STEP 1.1 --> Transfer the data in the CANIFn registers to the CAN
                   message object specified by the MNUM field in the CAN
                   Command Request*/
    CAN_IFn_CommandMask[pt_CAN_ConfigurationChannel->ChannelNumIndexArr][pt_CAN_ConfigurationChannel->InterfaceNumIndexArr]->bits.WRNRD=1;

    /*STEP 1.2 --> Mask bits unchanged*/
    CAN_IFn_CommandMask[pt_CAN_ConfigurationChannel->ChannelNumIndexArr][pt_CAN_ConfigurationChannel->InterfaceNumIndexArr]->bits.MASK=pt_CAN_ConfigurationChannel->ConfigureMaskBits;

    /*STEP 1.3 Access Arbitration Bits*/
    CAN_IFn_CommandMask[pt_CAN_ConfigurationChannel->ChannelNumIndexArr][pt_CAN_ConfigurationChannel->InterfaceNumIndexArr]->bits.ARB=pt_CAN_ConfigurationChannel->ConfigArbitBits;

    /*STEP 1.4 Access Control Bits*/
    CAN_IFn_CommandMask[pt_CAN_ConfigurationChannel->ChannelNumIndexArr][pt_CAN_ConfigurationChannel->InterfaceNumIndexArr]->bits.CONTROL=pt_CAN_ConfigurationChannel->ConfigCTLBits;


    /*STEP 1.5 no interrupt*/
    CAN_IFn_MessageCtlReg[pt_CAN_ConfigurationChannel->ChannelNumIndexArr][pt_CAN_ConfigurationChannel->InterfaceNumIndexArr]->bits.INTPND=0;


    /*STEP 1.6*/
    if(pt_CAN_ConfigurationChannel->ConfigNumBytesTrans == Transfer_0_To_3_Bytes){
        CAN_IFn_CommandMask[pt_CAN_ConfigurationChannel->ChannelNumIndexArr][pt_CAN_ConfigurationChannel->InterfaceNumIndexArr]->bits.DATAA=1;
    }


}


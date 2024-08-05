/* =====================================================================================*/
/*                                    INCLUDES                                          */
/* =====================================================================================*/


#include "CAN_config.h"
/*
 * typedef struct{
    CAN_ChannelNumIndexArr_t ChannelNumIndexArr;
    SC_ConfigCANmoduleNum_t SYSCTL_ConfigCANmoduleNum;
    u8_t BaudRatePresVar;
    u8_t TimeSegAfterSampleVar;
    u8_t TimeSegBeforeSampleVar;
    u8_t SyncJumpWidthVar;
}CAN_ConfigurationChannel_t;
 *
 *
 *
 *15,
   3,
   4,
   3


   typedef struct{
    CAN_ChannelNumIndexArr_t ChannelNumIndexArr;
    SC_ConfigCANmoduleNum_t SYSCTL_ConfigCANmoduleNum;
    CAN_InterfaceNumIndexArr_t InterfaceNumIndexArr;
    CAN_ConfigMaskBits_t ConfigureMaskBits;
    CAN_ConfigArbitBits_t ConfigArbitBits;
    CAN_ConfigCTLBits_t  ConfigCTLBits;
    CAN_ConfigNumBytesTrans_t ConfigNumBytesTrans;
    u8_t BaudRatePresVar;
    u8_t TimeSegAfterSampleVar;
    u8_t TimeSegBeforeSampleVar;
    u8_t SyncJumpWidthVar;
}CAN_ConfigurationChannel_t;


 * */



CAN_ConfigurationChannel_t CAN_Channel0_Config={
   CAN_Channel_0,
   SYSCTL_Module0CAN,
   CAN_Interface_1,
   MaskBitsUnchanged,
   ArbitBitsUnchanged,
   CTLBitsUnchanged,
   Transfer_0_To_3_Bytes,
   15,     /*Baud rate prescaler= 16-1*/
   3,      /*TimeSegAfterSampleVar*/
   4,      /*TimeSegBeforeSampleVar*/
   3        /*SyncJumpWidthVar*/
};

CAN_ConfigurationChannel_t CAN_Channel1_Config={
   CAN_Channel_1,
   SYSCTL_Module1CAN,
   CAN_Interface_2,
   MaskBitsUnchanged,
   ArbitBitsUnchanged,
   CTLBitsUnchanged,
   Transfer_0_To_3_Bytes,
   15,      /*Baud rate prescaler= 16-1*/
   3,
   4,
   3
};

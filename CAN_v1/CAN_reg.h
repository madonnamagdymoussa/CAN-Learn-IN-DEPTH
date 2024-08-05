#ifndef CAN_REG_H_
#define CAN_REG_H_

#include "lstd.h"

#define CAN0_BaseAddress (0x40040000)
#define CAN1_BaseAddress (0x40041000)

typedef union{

    struct{
      u32_t INIT:1;
      u32_t IE:1;
      u32_t SIE:1;
      u32_t EIE:1;
      u32_t :1;
      u32_t DAR:1;
      u32_t CCE:1;
      u32_t TEST:1;
      u32_t :24;
    }bits;

    u32_t Register;
}CANCTL_Reg;

typedef union {

    struct{
        u32_t BRP:6;
        u32_t SJW:2;
        u32_t TSEG1:4;
        u32_t TSEG2:3;
        u32_t :17;
    }bits;
    u32_t Register;
}CANBIT_Reg;

typedef union{
    struct{
        u32_t DATAB:1;
        u32_t DATAA:1;
        u32_t NEWDAT_TXRQST:1;
        u32_t CLRINTPND:1;
        u32_t CONTROL:1;
        u32_t ARB:1;
        u32_t MASK:1;
        u32_t WRNRD:1;
    }bits;
    u32_t Register;
}CANIFnCMSK_Reg;

typedef union{
    struct{

        u32_t DLC:4;
        u32_t :3;
        u32_t EOB:1;
        u32_t TXRQST:1;
        u32_t RMTEN:1;
        u32_t RXIE:1;
        u32_t TXIE:1;
        u32_t UMASK:1;
        u32_t INTPND:1;
        u32_t MSGLST:1;
        u32_t NEWDAT:1;
        u32_t :16;
    }bits;
u32_t Register;
}CANIFnMCTL_Reg;


typedef union{
    struct{
        u32_t ID:13;
        u32_t DIR:1;
        u32_t XTD:1;
        u32_t MSGVAL:1;
        u32_t :16;
    }bits;
    u32_t Register;
}CANIFnARB2_Reg;

#define CAN0_CONTROL_Reg   ((volatile CANCTL_Reg*)(CAN0_BaseAddress))
#define CAN1_CONTROL_Reg   ((volatile CANCTL_Reg*)(CAN1_BaseAddress))

#define CAN0_BITTIMING_REG  ((volatile CANBIT_Reg*)(CAN0_BaseAddress+0x00C))
#define CAN1_BITTIMING_REG  ((volatile CANBIT_Reg*)(CAN1_BaseAddress+0x00C))

#define CAN0_IF1_CommandMask_Reg  ((volatile CANIFnCMSK_Reg*)(CAN0_BaseAddress + 0x024))
#define CAN0_IF2_CommandMask_Reg  ((volatile CANIFnCMSK_Reg*)(CAN0_BaseAddress + 0x084))
#define CAN1_IF1_CommandMask_Reg  ((volatile CANIFnCMSK_Reg*)(CAN1_BaseAddress + 0x024))
#define CAN1_IF2_CommandMask_Reg  ((volatile CANIFnCMSK_Reg*)(CAN1_BaseAddress + 0x084))

#define CAN0_IF1_MessageCtl_Reg   ((volatile CANIFnMCTL_Reg*)(CAN0_BaseAddress + 0x038))
#define CAN0_IF2_MessageCtl_Reg   ((volatile CANIFnMCTL_Reg*)(CAN0_BaseAddress + 0x098))
#define CAN1_IF1_MessageCtl_Reg   ((volatile CANIFnMCTL_Reg*)(CAN1_BaseAddress + 0x038))
#define CAN1_IF2_MessageCtl_Reg   ((volatile CANIFnMCTL_Reg*)(CAN1_BaseAddress + 0x098))

#define CAN0_IF1_Arbitration2_Reg  ((volatile CANIFnARB2_Reg*)(CAN0_BaseAddress + 0x034))
#define CAN0_IF2_Arbitration2_Reg  ((volatile CANIFnARB2_Reg*)(CAN0_BaseAddress + 0x094))
#define CAN1_IF1_Arbitration2_Reg  ((volatile CANIFnARB2_Reg*)(CAN1_BaseAddress + 0x034))
#define CAN1_IF2_Arbitration2_Reg  ((volatile CANIFnARB2_Reg*)(CAN1_BaseAddress + 0x094))

#endif /* CAN_REG_H_ */

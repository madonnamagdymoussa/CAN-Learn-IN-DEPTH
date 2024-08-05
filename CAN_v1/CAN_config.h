#ifndef CAN_CONFIG_H_
#define CAN_CONFIG_H_

/*************************** Madonna Naming Convention in config.h file ***************************/

/* 1-If the enum constants is used for storing the Indices of an Array then the enum name must end with IndexArr_t
 * Example of the enum name: PeripheralName_xxxxIndexArr_t
 *
 * 1.1- If the enum constants is used for storing the Indices of the array the Last constant must store the total
 * number of the indices and that constant name must end with _Indices
 *
 * 2-If the enum constants is used for storing values that will be inserted inside the hardware registers(configurations) then
 * the enum name must begin with Configure keyword
 * Example of the enum name: PeripheralName_Configurexxxxxxx_t
 *
 * 2.1- IF the configuration is related to turning on or off or even controlling a Specific feature
 * then the enum name must end with Mode_t
 * Example of the enum name: PeripheralName_ConfigurexxxxxMode_t
 *
 *
 * 3-If the struct is used to store the information of specific channel such as the channel number
 * and the instance of the typedef enum related to configurations then
 * the name of the struct must end with ConfigurationChannel_t
 * Example of the struct name: PeripheralName_xxxxxConfigurationChannel_t
 *
 * 4-The Name of the Array of pointer to struct must end with  _ArrPtrStruct
 *
 *
 * */
/*************************** Madonna Naming Convention in config.h file ***************************/

#include "SystemControl_config.h"
#include "lstd.h"
/* =====================================================================================*/
/*                                    ENUM                                              */
/* =====================================================================================*/
typedef enum{
CAN_Channel_0,
CAN_Channel_1,
CAN_ChannelNum_Indicies
}CAN_ChannelNumIndexArr_t;

typedef enum{
CAN_Interface_1,
CAN_Interface_2,
CAN_InterfaceNum_Indicies
}CAN_InterfaceNumIndexArr_t;

typedef enum{
MaskBitsUnchanged,
Transfer_IDMASK_DIR_MXTD
}CAN_ConfigMaskBits_t;

typedef enum{
    ArbitBitsUnchanged,
    Transfer_ID_DIR_XTD_MSGVAL
}CAN_ConfigArbitBits_t;

typedef enum{
    CTLBitsUnchanged,
    TransferCTLBits
}CAN_ConfigCTLBits_t;

typedef enum{
    Transfer_0_To_3_Bytes,
    Transfer_4_To_7_Bytes
}CAN_ConfigNumBytesTrans_t;

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


extern CAN_ConfigurationChannel_t CAN_Channel0_Config;
extern CAN_ConfigurationChannel_t CAN_Channel1_Config;

#endif /* CAN_CONFIG_H_ */

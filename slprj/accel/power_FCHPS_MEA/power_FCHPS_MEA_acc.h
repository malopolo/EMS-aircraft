#ifndef RTW_HEADER_power_FCHPS_MEA_acc_h_
#define RTW_HEADER_power_FCHPS_MEA_acc_h_
#include <stddef.h>
#include <string.h>
#ifndef power_FCHPS_MEA_acc_COMMON_INCLUDES_
#define power_FCHPS_MEA_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "sl_AsyncioQueue/AsyncioQueueCAPI.h"
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "power_FCHPS_MEA_acc_types.h"
#include "multiword_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include "rt_defines.h"
typedef struct { real_T B_2_0_0 ; real_T B_2_1_0 ; }
B_Subsystempi2delay_power_FCHPS_MEA_T ; typedef struct { int32_T
Subsystempi2delay_sysIdxToRun ; int8_T Subsystempi2delay_SubsysRanBC ;
boolean_T Subsystempi2delay_MODE ; char_T pad_Subsystempi2delay_MODE [ 2 ] ;
} DW_Subsystempi2delay_power_FCHPS_MEA_T ; typedef struct { real_T B_3_0_0 ;
real_T B_3_1_0 ; } B_Subsystem1_power_FCHPS_MEA_T ; typedef struct { int32_T
Subsystem1_sysIdxToRun ; int8_T Subsystem1_SubsysRanBC ; boolean_T
Subsystem1_MODE ; char_T pad_Subsystem1_MODE [ 2 ] ; }
DW_Subsystem1_power_FCHPS_MEA_T ; typedef struct { creal_T B_4_14_0 ; real_T
B_27_0_0 [ 3 ] ; real_T B_27_1_0 ; real_T B_27_2_0 ; real_T B_27_3_0 [ 10 ] ;
real_T B_27_7_0 ; real_T B_27_9_0 ; real_T B_27_10_0 ; real_T B_27_12_0 ;
real_T B_27_15_0 ; real_T B_27_26_0 ; real_T B_27_32_0 ; real_T B_27_39_0 ;
real_T B_27_41_0 ; real_T B_27_42_0 ; real_T B_27_43_0 ; real_T B_27_44_0 ;
real_T B_27_45_0 ; real_T B_27_46_0 ; real_T B_27_51_0 ; real_T B_27_52_0 ;
real_T B_27_53_0 ; real_T B_27_54_0 ; real_T B_27_57_0 ; real_T B_27_59_0 ;
real_T B_27_60_0 ; real_T B_27_62_0 ; real_T B_27_64_0 ; real_T B_27_65_0 ;
real_T B_27_69_0 ; real_T B_27_71_0 ; real_T B_27_73_0 ; real_T B_27_76_0 [ 2
] ; real_T B_27_77_0 [ 2 ] ; real_T B_27_78_0 ; real_T B_27_79_0 ; real_T
B_27_81_0 ; real_T B_27_84_0 ; real_T B_27_86_0 ; real_T B_27_89_0 ; real_T
B_27_98_0 ; real_T B_27_99_0 ; real_T B_27_100_0 ; real_T B_27_101_0 ; real_T
B_27_102_0 ; real_T B_27_103_0 [ 43 ] ; real_T B_27_103_1 [ 13 ] ; real_T
B_27_114_0 ; real_T B_27_120_0 ; real_T B_27_129_0 ; real_T B_27_131_0 ;
real_T B_27_132_0 ; real_T B_27_136_0 ; real_T B_27_140_0 ; real_T B_27_144_0
; real_T B_27_152_0 ; real_T B_27_155_0 ; real_T B_27_165_0 ; real_T
B_27_168_0 ; real_T B_27_170_0 ; real_T B_27_172_0 ; real_T B_27_180_0 ;
real_T B_27_182_0 ; real_T B_27_222_0 ; real_T B_27_223_0 ; real_T B_27_238_0
; real_T B_27_248_0 ; real_T B_27_256_0 ; real_T B_27_259_0 ; real_T
B_27_289_0 ; real_T B_27_296_0 ; real_T B_27_297_0 ; real_T B_27_300_0 ;
real_T B_27_301_0 ; real_T B_27_303_0 ; real_T B_27_319_0 ; real_T B_27_320_0
; real_T B_27_322_0 ; real_T B_27_332_0 ; real_T B_27_333_0 ; real_T
B_27_337_0 ; real_T B_27_341_0 ; real_T B_27_345_0 ; real_T B_27_356_0 ;
real_T B_27_366_0 ; real_T B_27_369_0 ; real_T B_27_371_0 ; real_T B_27_373_0
; real_T B_27_381_0 ; real_T B_27_383_0 ; real_T B_27_410_0 ; real_T
B_27_411_0 ; real_T B_27_413_0 ; real_T B_27_414_0 ; real_T B_27_428_0 ;
real_T B_27_429_0 ; real_T B_27_432_0 ; real_T B_27_445_0 [ 3 ] ; real_T
B_27_447_0 [ 3 ] ; real_T B_27_449_0 ; real_T B_27_450_0 ; real_T B_27_451_0
; real_T B_27_459_0 ; real_T B_27_461_0 ; real_T B_27_462_0 ; real_T
B_27_463_0 ; real_T B_27_464_0 ; real_T B_27_466_0 ; real_T B_27_468_0 ;
real_T B_27_469_0 ; real_T B_27_470_0 ; real_T B_27_471_0 ; real_T B_27_472_0
; real_T B_27_473_0 ; real_T B_27_474_0 ; real_T B_27_475_0 ; real_T
B_27_476_0 ; real_T B_27_477_0 ; real_T B_27_478_0 ; real_T B_27_479_0 ;
real_T B_27_480_0 ; real_T B_27_481_0 ; real_T B_27_482_0 ; real_T B_27_483_0
; real_T B_27_484_0 ; real_T B_27_485_0 ; real_T B_27_486_0 ; real_T
B_27_487_0 ; real_T B_27_488_0 ; real_T B_27_489_0 ; real_T B_27_494_0 ;
real_T B_27_495_0 ; real_T B_27_496_0 ; real_T B_27_497_0 [ 3 ] ; real_T
B_27_498_0 [ 3 ] ; real_T B_27_501_0 [ 2 ] ; real_T B_27_544_0 [ 3 ] ; real_T
B_27_552_0 ; real_T B_27_556_0 ; real_T B_27_557_0 ; real_T B_27_564_0 ;
real_T B_27_565_0 ; real_T B_27_566_0 ; real_T B_27_570_0 ; real_T B_27_581_0
; real_T B_27_582_0 ; real_T B_27_583_0 [ 2 ] ; real_T B_27_584_0 [ 3 ] ;
real_T B_27_585_0 ; real_T B_27_586_0 ; real_T B_27_587_0 ; real_T B_27_588_0
; real_T B_27_589_0 ; real_T B_27_593_0 ; real_T B_27_597_0 ; real_T
B_27_601_0 ; real_T B_27_608_0 ; real_T B_27_613_0 ; real_T B_27_617_0 ;
real_T B_27_619_0 ; real_T B_27_620_0 ; real_T B_27_621_0 ; real_T B_27_622_0
[ 2 ] ; real_T B_27_656_0 ; real_T B_27_657_0 ; real_T B_27_670_0 ; real_T
B_27_671_0 ; real_T B_27_681_0 ; real_T B_27_688_0 ; real_T B_27_692_0 ;
real_T B_27_701_0 ; real_T B_27_731_0 ; real_T B_27_754_0 ; real_T B_27_755_0
; real_T B_27_765_0 ; real_T B_27_769_0 ; real_T B_27_0_0_m [ 13 ] ; real_T
B_27_1_0_c ; real_T B_27_2_0_k ; real_T B_27_3_0_c ; real_T B_27_4_0 ; real_T
B_27_6_0 ; real_T B_27_8_0 ; real_T B_27_9_0_b ; real_T B_27_10_0_p ; real_T
B_27_11_0 ; real_T B_27_12_0_c ; real_T B_27_13_0 ; real_T B_27_15_0_f ;
real_T B_27_17_0 ; real_T B_27_19_0 ; real_T B_27_20_0 ; real_T B_27_21_0 ;
real_T B_27_28_0 ; real_T B_27_39_0_g ; real_T B_27_40_0 ; real_T B_27_41_0_g
; real_T B_27_42_0_m ; real_T B_27_43_0_n ; real_T B_27_44_0_p ; real_T
B_27_45_0_l ; real_T B_27_46_0_j ; real_T B_27_47_0 ; real_T B_27_48_0 ;
real_T B_27_49_0 ; real_T B_27_50_0 ; real_T B_27_51_0_d ; real_T B_27_52_0_g
; real_T B_27_53_0_l ; real_T B_27_54_0_d ; real_T B_27_55_0 ; real_T
B_27_56_0 ; real_T B_27_57_0_d ; real_T B_27_58_0 ; real_T B_27_59_0_l ;
real_T B_27_60_0_o ; real_T B_27_61_0 ; real_T B_27_62_0_b ; real_T B_27_63_0
; real_T B_27_64_0_n ; real_T B_27_65_0_b ; real_T B_27_66_0 ; real_T
B_27_67_0 ; real_T B_27_68_0 ; real_T B_27_69_0_l ; real_T B_27_70_0 ; real_T
B_27_71_0_h ; real_T B_27_72_0 ; real_T B_27_77_0_b ; real_T B_27_78_0_d ;
real_T B_27_79_0_e ; real_T B_27_80_0 ; real_T B_27_81_0_b ; real_T B_27_82_0
; real_T B_27_83_0 ; real_T B_27_84_0_j ; real_T B_27_85_0 ; real_T
B_27_86_0_f ; real_T B_27_88_0 ; real_T B_27_90_0 ; real_T B_27_92_0 ; real_T
B_27_94_0 ; real_T B_27_95_0 ; real_T B_27_96_0 ; real_T B_27_97_0 ; real_T
B_27_98_0_a ; real_T B_27_99_0_j ; real_T B_27_100_0_j ; real_T B_27_101_0_o
; real_T B_27_102_0_n ; real_T B_27_103_0_i ; real_T B_26_0_1 ; real_T
B_26_0_2 ; real_T B_26_0_3 ; real_T B_26_0_4 ; real_T B_22_0_1 ; real_T
B_11_0_0 ; real_T B_11_1_0 ; real_T B_10_0_0 ; real_T B_10_1_0 ; real_T
B_5_0_0 ; real_T B_5_1_0 ; real_T B_4_0_0 ; real_T B_4_1_0 ; real_T B_4_2_0 ;
real_T B_4_4_0 ; real_T B_4_6_0 ; real_T B_4_7_0 ; real_T B_4_8_0 ; real_T
B_4_9_0 ; real_T B_4_11_0 ; real_T B_4_13_0 ; real_T B_4_15_0 ; real_T
B_4_16_0 ; real_T B_4_17_0 ; real_T B_4_18_0 ; real_T B_4_19_0 ; real_T
B_4_20_0 ; real_T B_4_21_0 ; real_T B_4_22_0 [ 3 ] ; real_T B_4_23_0 [ 3 ] ;
real_T B_4_26_0 [ 2 ] ; real_T B_4_0_0_o ; real_T B_4_1_0_n ; real_T B_1_0_0
; real_T B_1_1_0 ; real_T B_0_0_0 ; real_T B_0_1_0 ; real_T B_27_505_0 [ 3 ]
; real_T B_27_760_0 [ 4 ] ; uint8_T B_27_75_0 ; uint8_T B_27_24_0 ; uint8_T
B_27_26_0_m ; uint8_T B_27_31_0 ; uint8_T B_27_33_0 ; uint8_T B_27_36_0 ;
uint8_T B_27_38_0 ; uint8_T B_4_4_0_c ; uint8_T B_4_6_0_m ; boolean_T
B_27_85_0_m ; boolean_T B_27_87_0 ; boolean_T B_27_113_0 ; boolean_T
B_27_133_0 ; boolean_T B_27_288_0 ; boolean_T B_27_334_0 ; boolean_T
B_27_448_0 ; boolean_T B_27_465_0 ; boolean_T B_27_606_0 ; boolean_T
B_27_609_0 ; boolean_T B_27_665_0 ; boolean_T B_27_7_0_j ; boolean_T
B_27_16_0 ; boolean_T B_4_3_0 ; boolean_T B_4_10_0 ;
B_Subsystem1_power_FCHPS_MEA_T Subsystem1_h ;
B_Subsystempi2delay_power_FCHPS_MEA_T Subsystempi2delay_b ;
B_Subsystem1_power_FCHPS_MEA_T Subsystem1 ;
B_Subsystempi2delay_power_FCHPS_MEA_T Subsystempi2delay ;
B_Subsystem1_power_FCHPS_MEA_T Subsystem1_i ;
B_Subsystempi2delay_power_FCHPS_MEA_T Subsystempi2delay_d ; }
B_power_FCHPS_MEA_T ; typedef struct { real_T UnitDelay_DSTATE ; real_T
UnitDelay1_DSTATE ; real_T Currentfilter_states ; real_T inti_DSTATE ; real_T
DiscreteTimeIntegrator_DSTATE ; real_T UnitDelay2_DSTATE ; real_T
UnitDelay3_DSTATE ; real_T UnitDelay2_DSTATE_m ; real_T Celldynamic_states ;
real_T UnitDelay_DSTATE_a ; real_T DiscreteTimeIntegrator_DSTATE_f ; real_T
UnitDelay_DSTATE_c ; real_T UnitDelay3_DSTATE_c ; real_T UnitDelay2_DSTATE_e
; real_T UnitDelay3_DSTATE_l ; real_T StateSpace_DSTATE [ 12 ] ; real_T
DiscreteTimeIntegrator_DSTATE_n ; real_T UnitDelay_DSTATE_m ; real_T
DiscreteTimeIntegrator_DSTATE_p ; real_T DiscreteTimeIntegrator_DSTATE_o ;
real_T UnitDelay_DSTATE_k ; real_T DiscreteTimeIntegrator_DSTATE_c ; real_T
DiscreteTimeIntegrator_DSTATE_fi ; real_T DiscreteTimeIntegrator_DSTATE_h ;
real_T DiscreteTimeIntegrator_DSTATE_a ; real_T UnitDelay_DSTATE_l ; real_T
DiscreteTimeIntegrator_DSTATE_g ; real_T DiscreteTimeIntegrator_DSTATE_b ;
real_T UnitDelay4_DSTATE ; real_T UnitDelay1_DSTATE_f ; real_T
DiscreteTimeIntegrator_DSTATE_bt ; real_T UnitDelay2_DSTATE_p ; real_T
UnitDelay_DSTATE_h ; real_T DiscreteTimeIntegrator1_DSTATE ; real_T
DiscreteTimeIntegrator_DSTATE_e ; real_T lastSin [ 3 ] ; real_T lastCos [ 3 ]
; real_T itinit1_PreviousInput ; real_T itinit_PreviousInput ; real_T
Memory2_PreviousInput ; real_T Initial_FirstOutputTime ; real_T
Memory_PreviousInput ; real_T Memory_PreviousInput_g ; real_T PrevYA ; real_T
PrevYB ; real_T LastMajorTimeA ; real_T LastMajorTimeB ; real_T
Memory_PreviousInput_i ; real_T Memory_PreviousInput_l ; struct { real_T
modelTStart ; } VariableTransportDelay_RWORK ; struct { real_T modelTStart ;
} VariableTransportDelay_RWORK_e ; struct { real_T modelTStart ; }
VariableTransportDelay_RWORK_b ; struct { void * AS ; void * BS ; void * CS ;
void * DS ; void * DX_COL ; void * BD_COL ; void * TMP1 ; void * TMP2 ; void
* XTMP ; void * SWITCH_STATUS ; void * SWITCH_STATUS_INIT ; void * SW_CHG ;
void * G_STATE ; void * USWLAST ; void * XKM12 ; void * XKP12 ; void * XLAST
; void * ULAST ; void * IDX_SW_CHG ; void * Y_SWITCH ; void * SWITCH_TYPES ;
void * IDX_OUT_SW ; void * SWITCH_TOPO_SAVED_IDX ; void * SWITCH_MAP ; }
StateSpace_PWORK ; struct { void * AS ; void * BS ; void * CS ; void * DS ;
void * DX_COL ; void * BD_COL ; void * TMP1 ; void * TMP2 ; void * XTMP ;
void * SWITCH_STATUS ; void * SWITCH_STATUS_INIT ; void * SW_CHG ; void *
G_STATE ; void * USWLAST ; void * XKM12 ; void * XKP12 ; void * XLAST ; void
* ULAST ; void * IDX_SW_CHG ; void * Y_SWITCH ; void * SWITCH_TYPES ; void *
IDX_OUT_SW ; void * SWITCH_TOPO_SAVED_IDX ; void * SWITCH_MAP ; }
StateSpace_PWORK_p ; struct { void * AQHandles [ 2 ] ; }
TAQSigLogging_InsertedFor_BusCreator12_at_outport_0_1_PWORK ; void *
ToWorkspace_PWORK ; void * ToWorkspace1_PWORK ; void * ToWorkspace2_PWORK ;
struct { void * TUbufferPtrs [ 3 ] ; } VariableTransportDelay_PWORK ; struct
{ void * AQHandles ; }
TAQSigLogging_InsertedFor_Celldynamic_at_outport_0_PWORK ; struct { void *
AQHandles ; } TAQSigLogging_InsertedFor_Vactivation_at_outport_0_PWORK ; void
* Load1_PWORK [ 2 ] ; void * SuperCap_PWORK [ 2 ] ; void *
batterycommandscope_PWORK [ 2 ] ; void * Battery_PWORK [ 3 ] ; void *
Power_PWORK ; void * ToWorkspace_PWORK_n ; void * ToWorkspace1_1_PWORK ; void
* Converters_PWORK [ 2 ] ; void * FuelCell_PWORK [ 4 ] ; void * Load_PWORK [
2 ] ; struct { void * TUbufferPtrs [ 3 ] ; } VariableTransportDelay_PWORK_b ;
struct { void * TUbufferPtrs [ 3 ] ; } VariableTransportDelay_PWORK_c ;
int32_T systemEnable ; int32_T MATLABFunction_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitch2Inport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitch2Inport3_sysIdxToRun_j ; int32_T
TmpAtomicSubsysAtSwitch3Inport3_sysIdxToRun ; int32_T
MATLABFunction_sysIdxToRun_e ; int32_T
TmpAtomicSubsysAtSwitch2Inport3_sysIdxToRun_a ; int32_T
TmpAtomicSubsysAtSwitch1Inport1_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitch2Inport3_sysIdxToRun_jo ; int32_T
TmpAtomicSubsysAtSwitch2Inport3_sysIdxToRun_n ; int32_T
TmpAtomicSubsysAtSwitch2Inport3_sysIdxToRun_p ; int32_T
TmpAtomicSubsysAtMultiportSwitch1Inport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAtMultiportSwitch1Inport5_sysIdxToRun ; int32_T
TmpAtomicSubsysAtMultiportSwitch1Inport4_sysIdxToRun ; int32_T
TmpAtomicSubsysAtMultiportSwitch1Inport3_sysIdxToRun_e ; int32_T
TmpAtomicSubsysAtMultiportSwitch1Inport2_sysIdxToRun ; int32_T
Subsystem1_sysIdxToRun ; int32_T Subsystempi2delay_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun ; int32_T
AutomaticGainControl_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_k ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_m ; int_T StateSpace_IWORK [ 11 ]
; int_T StateSpace_IWORK_k [ 11 ] ; int_T Integrator_IWORK ; struct { int_T
Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize
; } VariableTransportDelay_IWORK ; struct { int_T Tail ; int_T Head ; int_T
Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
VariableTransportDelay_IWORK_n ; struct { int_T Tail ; int_T Head ; int_T
Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
VariableTransportDelay_IWORK_f ; int_T Saturation4_MODE ; int_T
Saturation3_MODE ; int_T Saturation4_MODE_n ; int_T Saturation1_MODE ; int_T
Saturation4_MODE_nx ; int_T Saturation5_MODE ; int_T MinMax_MODE ; int_T
Saturation2_MODE ; int_T Saturation2_MODE_b ; int_T Integrator_MODE ; int_T
Integrator_MODE_g ; int_T Saturation2_MODE_m ; int_T Saturation_MODE [ 2 ] ;
int_T zeroavoider_MODE ; int_T zeroavoider2_MODE ; int_T Saturation_MODE_d ;
int8_T inti_PrevResetState ; int8_T NerstVoltage_DWORK1 ; int8_T
Vactivation_DWORK1 ; int8_T DiscreteTimeIntegrator1_PrevResetState ; int8_T
Subsystem1_SubsysRanBC ; int8_T Subsystempi2delay_SubsysRanBC ; int8_T
AutomaticGainControl_SubsysRanBC ; uint8_T inti_IC_LOADING ; boolean_T
Switch_Mode ; boolean_T Compare_Mode ; boolean_T Compare_Mode_h ; boolean_T
LowerRelop1_Mode ; boolean_T UpperRelop_Mode ; boolean_T
RelationalOperator_Mode ; boolean_T RelationalOperator_Mode_h ; boolean_T
RelationalOperator_Mode_g ; boolean_T RelationalOperator_Mode_i ; boolean_T
UpperRelop_Mode_e ; boolean_T RelationalOperator_Mode_e ; boolean_T
RelationalOperator_Mode_c ; boolean_T Subsystem1_MODE ; boolean_T
Subsystempi2delay_MODE ; boolean_T AutomaticGainControl_MODE ; char_T
pad_AutomaticGainControl_MODE [ 5 ] ; DW_Subsystem1_power_FCHPS_MEA_T
Subsystem1_h ; DW_Subsystempi2delay_power_FCHPS_MEA_T Subsystempi2delay_b ;
DW_Subsystem1_power_FCHPS_MEA_T Subsystem1 ;
DW_Subsystempi2delay_power_FCHPS_MEA_T Subsystempi2delay ;
DW_Subsystem1_power_FCHPS_MEA_T Subsystem1_i ;
DW_Subsystempi2delay_power_FCHPS_MEA_T Subsystempi2delay_d ; }
DW_power_FCHPS_MEA_T ; typedef struct { real_T Airblowerdelay2_CSTATE ;
real_T Integrator_CSTATE ; real_T Integrator_CSTATE_g ; real_T
VariableTransportDelay_CSTATE ; real_T integrator_CSTATE ; real_T
TransferFcn_CSTATE ; real_T Integrator_x1_CSTATE ; real_T
Integrator_x2_CSTATE ; real_T VariableTransportDelay_CSTATE_n ; real_T
integrator_CSTATE_o ; real_T VariableTransportDelay_CSTATE_b ; real_T
integrator_CSTATE_i ; } X_power_FCHPS_MEA_T ; typedef struct { real_T
Airblowerdelay2_CSTATE ; real_T Integrator_CSTATE ; real_T
Integrator_CSTATE_g ; real_T VariableTransportDelay_CSTATE ; real_T
integrator_CSTATE ; real_T TransferFcn_CSTATE ; real_T Integrator_x1_CSTATE ;
real_T Integrator_x2_CSTATE ; real_T VariableTransportDelay_CSTATE_n ; real_T
integrator_CSTATE_o ; real_T VariableTransportDelay_CSTATE_b ; real_T
integrator_CSTATE_i ; } XDot_power_FCHPS_MEA_T ; typedef struct { boolean_T
Airblowerdelay2_CSTATE ; boolean_T Integrator_CSTATE ; boolean_T
Integrator_CSTATE_g ; boolean_T VariableTransportDelay_CSTATE ; boolean_T
integrator_CSTATE ; boolean_T TransferFcn_CSTATE ; boolean_T
Integrator_x1_CSTATE ; boolean_T Integrator_x2_CSTATE ; boolean_T
VariableTransportDelay_CSTATE_n ; boolean_T integrator_CSTATE_o ; boolean_T
VariableTransportDelay_CSTATE_b ; boolean_T integrator_CSTATE_i ; }
XDis_power_FCHPS_MEA_T ; typedef struct { real_T Airblowerdelay2_CSTATE ;
real_T Integrator_CSTATE ; real_T Integrator_CSTATE_g ; real_T
VariableTransportDelay_CSTATE ; real_T integrator_CSTATE ; real_T
TransferFcn_CSTATE ; real_T Integrator_x1_CSTATE ; real_T
Integrator_x2_CSTATE ; real_T VariableTransportDelay_CSTATE_n ; real_T
integrator_CSTATE_o ; real_T VariableTransportDelay_CSTATE_b ; real_T
integrator_CSTATE_i ; } CStateAbsTol_power_FCHPS_MEA_T ; typedef struct {
real_T Airblowerdelay2_CSTATE ; real_T Integrator_CSTATE ; real_T
Integrator_CSTATE_g ; real_T VariableTransportDelay_CSTATE ; real_T
integrator_CSTATE ; real_T TransferFcn_CSTATE ; real_T Integrator_x1_CSTATE ;
real_T Integrator_x2_CSTATE ; real_T VariableTransportDelay_CSTATE_n ; real_T
integrator_CSTATE_o ; real_T VariableTransportDelay_CSTATE_b ; real_T
integrator_CSTATE_i ; } CXPtMin_power_FCHPS_MEA_T ; typedef struct { real_T
Airblowerdelay2_CSTATE ; real_T Integrator_CSTATE ; real_T
Integrator_CSTATE_g ; real_T VariableTransportDelay_CSTATE ; real_T
integrator_CSTATE ; real_T TransferFcn_CSTATE ; real_T Integrator_x1_CSTATE ;
real_T Integrator_x2_CSTATE ; real_T VariableTransportDelay_CSTATE_n ; real_T
integrator_CSTATE_o ; real_T VariableTransportDelay_CSTATE_b ; real_T
integrator_CSTATE_i ; } CXPtMax_power_FCHPS_MEA_T ; typedef struct { real_T
Saturation4_UprLim_ZC ; real_T Saturation4_LwrLim_ZC ; real_T
Saturation3_UprLim_ZC ; real_T Saturation3_LwrLim_ZC ; real_T
Saturation4_UprLim_ZC_n ; real_T Saturation4_LwrLim_ZC_b ; real_T
Saturation1_UprLim_ZC ; real_T Saturation1_LwrLim_ZC ; real_T
Saturation4_UprLim_ZC_g ; real_T Saturation4_LwrLim_ZC_l ; real_T
Saturation5_UprLim_ZC ; real_T Saturation5_LwrLim_ZC ; real_T
Switch_SwitchCond_ZC ; real_T Compare_RelopInput_ZC ; real_T
MinMax_MinmaxInput_ZC ; real_T Saturation2_UprLim_ZC ; real_T
Saturation2_LwrLim_ZC ; real_T Compare_RelopInput_ZC_p ; real_T
LowerRelop1_RelopInput_ZC ; real_T UpperRelop_RelopInput_ZC ; real_T
RelationalOperator_RelopInput_ZC ; real_T RelationalOperator_RelopInput_ZC_a
; real_T Saturation2_UprLim_ZC_l ; real_T Saturation2_LwrLim_ZC_m ; real_T
RelationalOperator_RelopInput_ZC_f ; real_T Integrator_Reset_ZC ; real_T
Integrator_IntgUpLimit_ZC ; real_T Integrator_IntgLoLimit_ZC ; real_T
Integrator_LeaveSaturate_ZC ; real_T HitCrossing_HitNoOutput_ZC ; real_T
Integrator_IntgUpLimit_ZC_g ; real_T Integrator_IntgLoLimit_ZC_f ; real_T
Integrator_LeaveSaturate_ZC_k ; real_T RelationalOperator_RelopInput_ZC_e ;
real_T Saturation2_UprLim_ZC_lq ; real_T Saturation2_LwrLim_ZC_o ; real_T
UpperRelop_RelopInput_ZC_f ; real_T Saturation_UprLim_ZC [ 2 ] ; real_T
Saturation_LwrLim_ZC [ 2 ] ; real_T zeroavoider_UprLim_ZC ; real_T
zeroavoider_LwrLim_ZC ; real_T zeroavoider2_UprLim_ZC ; real_T
zeroavoider2_LwrLim_ZC ; real_T RelationalOperator_RelopInput_ZC_h ; real_T
RelationalOperator_RelopInput_ZC_b ; real_T Saturation_UprLim_ZC_p ; real_T
Saturation_LwrLim_ZC_m ; } ZCV_power_FCHPS_MEA_T ; typedef struct {
ZCSigState Saturation4_UprLim_ZCE ; ZCSigState Saturation4_LwrLim_ZCE ;
ZCSigState Saturation3_UprLim_ZCE ; ZCSigState Saturation3_LwrLim_ZCE ;
ZCSigState Saturation4_UprLim_ZCE_h ; ZCSigState Saturation4_LwrLim_ZCE_h ;
ZCSigState Saturation1_UprLim_ZCE ; ZCSigState Saturation1_LwrLim_ZCE ;
ZCSigState Saturation4_UprLim_ZCE_b ; ZCSigState Saturation4_LwrLim_ZCE_g ;
ZCSigState Saturation5_UprLim_ZCE ; ZCSigState Saturation5_LwrLim_ZCE ;
ZCSigState Switch_SwitchCond_ZCE ; ZCSigState Compare_RelopInput_ZCE ;
ZCSigState MinMax_MinmaxInput_ZCE ; ZCSigState Saturation2_UprLim_ZCE ;
ZCSigState Saturation2_LwrLim_ZCE ; ZCSigState Compare_RelopInput_ZCE_b ;
ZCSigState LowerRelop1_RelopInput_ZCE ; ZCSigState UpperRelop_RelopInput_ZCE
; ZCSigState RelationalOperator_RelopInput_ZCE ; ZCSigState
RelationalOperator_RelopInput_ZCE_m ; ZCSigState Saturation2_UprLim_ZCE_c ;
ZCSigState Saturation2_LwrLim_ZCE_c ; ZCSigState
RelationalOperator_RelopInput_ZCE_d ; ZCSigState Integrator_Reset_ZCE ;
ZCSigState Integrator_IntgUpLimit_ZCE ; ZCSigState Integrator_IntgLoLimit_ZCE
; ZCSigState Integrator_LeaveSaturate_ZCE ; ZCSigState
HitCrossing_HitNoOutput_ZCE ; ZCSigState Integrator_IntgUpLimit_ZCE_m ;
ZCSigState Integrator_IntgLoLimit_ZCE_k ; ZCSigState
Integrator_LeaveSaturate_ZCE_g ; ZCSigState
RelationalOperator_RelopInput_ZCE_j ; ZCSigState Saturation2_UprLim_ZCE_b ;
ZCSigState Saturation2_LwrLim_ZCE_b ; ZCSigState UpperRelop_RelopInput_ZCE_g
; ZCSigState Saturation_UprLim_ZCE [ 2 ] ; ZCSigState Saturation_LwrLim_ZCE [
2 ] ; ZCSigState zeroavoider_UprLim_ZCE ; ZCSigState zeroavoider_LwrLim_ZCE ;
ZCSigState zeroavoider2_UprLim_ZCE ; ZCSigState zeroavoider2_LwrLim_ZCE ;
ZCSigState RelationalOperator_RelopInput_ZCE_dw ; ZCSigState
RelationalOperator_RelopInput_ZCE_c ; ZCSigState Saturation_UprLim_ZCE_i ;
ZCSigState Saturation_LwrLim_ZCE_o ; } PrevZCX_power_FCHPS_MEA_T ; typedef
struct { const real_T B_27_0_0 ; const real_T B_27_1_0 ; const real_T
B_27_2_0 ; const real_T B_27_3_0 ; const real_T B_27_4_0 ; }
ConstB_power_FCHPS_MEA_T ;
#define power_FCHPS_MEA_rtC(S) ((ConstB_power_FCHPS_MEA_T *) _ssGetConstBlockIO(S))
struct P_Subsystempi2delay_power_FCHPS_MEA_T_ { real_T P_0 [ 2 ] ; } ; struct
P_Subsystem1_power_FCHPS_MEA_T_ { real_T P_0 [ 2 ] ; } ; struct
P_power_FCHPS_MEA_T_ { real_T P_0 ; real_T P_1 ; real_T P_2 ; real_T P_3 ;
real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7 ; real_T P_8 ; real_T P_9 ;
real_T P_10 ; real_T P_11 ; real_T P_12 ; real_T P_13 ; real_T P_14 ; real_T
P_15 [ 9 ] ; real_T P_16 ; real_T P_17 ; real_T P_18 ; real_T P_19 ; real_T
P_20 ; real_T P_21 ; real_T P_22 [ 2 ] ; real_T P_23 [ 2 ] ; real_T P_24 ;
real_T P_25 ; real_T P_26 ; real_T P_27 ; real_T P_28 ; real_T P_29 ; real_T
P_30 ; real_T P_31 ; real_T P_32 ; real_T P_33 ; real_T P_34 ; real_T P_35 ;
real_T P_36 [ 3 ] ; real_T P_37 [ 3 ] ; real_T P_38 [ 3 ] ; real_T P_39 [ 3 ]
; real_T P_40 ; real_T P_41 ; real_T P_42 [ 2 ] ; real_T P_43 [ 40 ] ; real_T
P_44 ; real_T P_45 ; real_T P_46 ; real_T P_47 [ 2 ] ; real_T P_48 ; real_T
P_49 ; real_T P_50 ; real_T P_51 ; real_T P_52 ; real_T P_53 ; real_T P_54 ;
real_T P_55 ; real_T P_56 ; real_T P_57 ; real_T P_58 ; real_T P_59 ; real_T
P_60 ; real_T P_61 ; real_T P_62 [ 2 ] ; real_T P_63 ; real_T P_64 ; real_T
P_65 ; real_T P_66 ; real_T P_67 ; real_T P_68 ; real_T P_69 ; real_T P_70 ;
real_T P_71 ; real_T P_72 ; real_T P_73 ; real_T P_74 ; real_T P_75 ; real_T
P_76 ; real_T P_77 ; real_T P_78 ; real_T P_79 ; real_T P_80 ; real_T P_81 ;
real_T P_82 ; real_T P_83 ; real_T P_84 ; real_T P_85 ; real_T P_86 ; real_T
P_87 ; real_T P_88 ; real_T P_89 ; real_T P_90 [ 2 ] ; real_T P_91 ; real_T
P_92 ; real_T P_93 ; real_T P_94 ; real_T P_95 ; real_T P_96 ; real_T P_97 ;
real_T P_98 ; real_T P_99 ; real_T P_100 ; real_T P_101 ; real_T P_102 ;
real_T P_103 [ 2 ] ; real_T P_104 [ 144 ] ; real_T P_105 [ 2 ] ; real_T P_106
[ 276 ] ; real_T P_107 [ 2 ] ; real_T P_108 [ 516 ] ; real_T P_109 [ 2 ] ;
real_T P_110 [ 989 ] ; real_T P_111 [ 2 ] ; real_T P_112 [ 12 ] ; real_T
P_113 ; real_T P_114 ; real_T P_115 ; real_T P_116 ; real_T P_117 ; real_T
P_118 ; real_T P_119 ; real_T P_120 ; real_T P_121 ; real_T P_122 ; real_T
P_123 ; real_T P_124 ; real_T P_125 ; real_T P_126 ; real_T P_127 ; real_T
P_128 ; real_T P_129 ; real_T P_130 ; real_T P_131 ; real_T P_132 ; real_T
P_133 ; real_T P_134 ; real_T P_135 ; real_T P_136 ; real_T P_137 ; real_T
P_138 ; real_T P_139 ; real_T P_140 ; real_T P_141 ; real_T P_142 ; real_T
P_143 ; real_T P_144 ; real_T P_145 ; real_T P_146 ; real_T P_147 ; real_T
P_148 ; real_T P_149 ; real_T P_150 ; real_T P_151 ; real_T P_152 ; real_T
P_153 ; real_T P_154 ; real_T P_155 ; real_T P_156 ; real_T P_157 ; real_T
P_158 ; real_T P_159 ; real_T P_160 ; real_T P_161 ; real_T P_162 ; real_T
P_163 ; real_T P_164 ; real_T P_165 ; real_T P_166 ; real_T P_167 ; real_T
P_168 ; real_T P_169 ; real_T P_170 ; real_T P_171 ; real_T P_172 ; real_T
P_173 ; real_T P_174 ; real_T P_175 ; real_T P_176 ; real_T P_177 ; real_T
P_178 ; real_T P_179 ; real_T P_180 ; real_T P_181 ; real_T P_182 ; real_T
P_183 ; real_T P_184 ; real_T P_185 ; real_T P_186 ; real_T P_187 ; real_T
P_188 ; real_T P_189 ; real_T P_190 ; real_T P_191 ; real_T P_192 ; real_T
P_193 ; real_T P_194 ; real_T P_195 ; real_T P_196 ; real_T P_197 ; real_T
P_198 ; real_T P_199 ; real_T P_200 ; real_T P_201 ; real_T P_202 ; real_T
P_203 ; real_T P_204 ; real_T P_205 ; real_T P_206 ; real_T P_207 ; real_T
P_208 ; real_T P_209 ; real_T P_210 ; real_T P_211 ; real_T P_212 ; real_T
P_213 ; real_T P_214 ; real_T P_215 ; real_T P_216 ; real_T P_217 ; real_T
P_218 ; real_T P_219 ; real_T P_220 ; real_T P_221 ; real_T P_222 ; real_T
P_223 ; real_T P_224 ; real_T P_225 ; real_T P_226 ; real_T P_227 ; real_T
P_228 ; real_T P_229 ; real_T P_230 ; real_T P_231 ; real_T P_232 ; real_T
P_233 ; real_T P_234 ; real_T P_235 ; real_T P_236 ; real_T P_237 ; real_T
P_238 ; real_T P_239 ; real_T P_240 ; real_T P_241 ; real_T P_242 ; real_T
P_243 ; real_T P_244 [ 31 ] ; real_T P_245 [ 31 ] ; real_T P_246 ; real_T
P_247 ; real_T P_248 ; real_T P_249 ; real_T P_250 ; real_T P_251 ; real_T
P_252 ; real_T P_253 ; real_T P_254 ; real_T P_255 ; real_T P_256 ; real_T
P_257 ; real_T P_258 ; real_T P_259 [ 9 ] ; real_T P_260 ; real_T P_261 ;
real_T P_262 ; real_T P_263 ; real_T P_264 ; real_T P_265 ; real_T P_266 ;
real_T P_267 ; real_T P_268 ; real_T P_269 ; real_T P_270 ; real_T P_271 ;
real_T P_272 ; real_T P_273 ; real_T P_274 ; real_T P_275 ; real_T P_276 ;
real_T P_277 ; real_T P_278 ; real_T P_279 ; real_T P_280 ; real_T P_281 ;
real_T P_282 ; real_T P_283 ; real_T P_284 ; real_T P_285 ; real_T P_286 ;
real_T P_287 ; real_T P_288 ; real_T P_289 ; real_T P_290 ; real_T P_291 ;
real_T P_292 ; real_T P_293 ; real_T P_294 ; real_T P_295 ; real_T P_296 ;
real_T P_297 [ 9 ] ; real_T P_298 ; real_T P_299 ; real_T P_300 ; real_T
P_301 ; real_T P_302 ; real_T P_303 [ 9 ] ; real_T P_304 ; real_T P_305 ;
real_T P_306 ; real_T P_307 ; real_T P_308 ; real_T P_309 ; real_T P_310 ;
real_T P_311 ; real_T P_312 ; real_T P_313 ; real_T P_314 ; real_T P_315 ;
real_T P_316 ; real_T P_317 ; real_T P_318 ; real_T P_319 ; real_T P_320 ;
real_T P_321 ; real_T P_322 ; real_T P_323 ; real_T P_324 ; real_T P_325 ;
real_T P_326 ; real_T P_327 ; real_T P_328 ; real_T P_329 ; real_T P_330 ;
real_T P_331 ; real_T P_332 ; real_T P_333 ; real_T P_334 ; real_T P_335 ;
real_T P_336 ; real_T P_337 ; real_T P_338 ; real_T P_339 ; real_T P_340 ;
real_T P_341 ; real_T P_342 ; real_T P_343 ; real_T P_344 ; real_T P_345 ;
real_T P_346 ; real_T P_347 ; real_T P_348 ; real_T P_349 ; real_T P_350 ;
real_T P_351 ; real_T P_352 ; real_T P_353 [ 13 ] ; real_T P_354 ; real_T
P_355 ; real_T P_356 ; real_T P_357 ; real_T P_358 ; real_T P_359 ; real_T
P_360 ; real_T P_361 ; real_T P_362 ; real_T P_363 ; real_T P_364 ; real_T
P_365 ; real_T P_366 ; real_T P_367 ; real_T P_368 ; real_T P_369 ; real_T
P_370 ; real_T P_371 ; real_T P_372 ; real_T P_373 ; real_T P_374 ; real_T
P_375 ; real_T P_376 ; real_T P_377 ; real_T P_378 ; real_T P_379 ; real_T
P_380 ; real_T P_381 ; real_T P_382 ; real_T P_383 ; real_T P_384 ; real_T
P_385 ; real_T P_386 ; real_T P_387 ; real_T P_388 ; real_T P_389 ; real_T
P_390 ; real_T P_391 ; real_T P_392 ; real_T P_393 ; real_T P_394 ; real_T
P_395 ; real_T P_396 ; real_T P_397 ; real_T P_398 ; real_T P_399 ; real_T
P_400 ; real_T P_401 ; real_T P_402 ; real_T P_403 ; real_T P_404 ; real_T
P_405 ; real_T P_406 ; real_T P_407 ; real_T P_408 ; real_T P_409 ; real_T
P_410 ; real_T P_411 ; real_T P_412 ; real_T P_413 ; real_T P_414 ; real_T
P_415 ; real_T P_416 ; real_T P_417 ; real_T P_418 ; real_T P_419 ; real_T
P_420 ; real_T P_421 ; real_T P_422 ; real_T P_423 ; real_T P_424 ; real_T
P_425 ; real_T P_426 ; real_T P_427 ; real_T P_428 ; real_T P_429 ; real_T
P_430 ; real_T P_431 ; real_T P_432 ; real_T P_433 ; real_T P_434 ; real_T
P_435 ; real_T P_436 ; real_T P_437 ; real_T P_438 ; real_T P_439 ; real_T
P_440 ; real_T P_441 ; real_T P_442 ; real_T P_443 ; real_T P_444 ; real_T
P_445 ; real_T P_446 ; real_T P_447 ; real_T P_448 ; real_T P_449 ; real_T
P_450 ; real_T P_451 ; real_T P_452 ; P_Subsystem1_power_FCHPS_MEA_T
Subsystem1_h ; P_Subsystempi2delay_power_FCHPS_MEA_T Subsystempi2delay_b ;
P_Subsystem1_power_FCHPS_MEA_T Subsystem1 ;
P_Subsystempi2delay_power_FCHPS_MEA_T Subsystempi2delay ;
P_Subsystem1_power_FCHPS_MEA_T Subsystem1_i ;
P_Subsystempi2delay_power_FCHPS_MEA_T Subsystempi2delay_d ; } ; extern
P_power_FCHPS_MEA_T power_FCHPS_MEA_rtDefaultP ; extern const
ConstB_power_FCHPS_MEA_T power_FCHPS_MEA_rtInvariant ;
#endif

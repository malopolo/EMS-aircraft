#ifndef RTW_HEADER_power_FCHPS_MEA_acc_private_h_
#define RTW_HEADER_power_FCHPS_MEA_acc_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "power_FCHPS_MEA_acc.h"
#if !defined(ss_VALIDATE_MEMORY)
#define ss_VALIDATE_MEMORY(S, ptr)   if(!(ptr)) {\
  ssSetErrorStatus(S, RT_MEMORY_ALLOCATION_ERROR);\
  }
#endif
#if !defined(rt_FREE)
#if !defined(_WIN32)
#define rt_FREE(ptr)   if((ptr) != (NULL)) {\
  free((ptr));\
  (ptr) = (NULL);\
  }
#else
#define rt_FREE(ptr)   if((ptr) != (NULL)) {\
  free((void *)(ptr));\
  (ptr) = (NULL);\
  }
#endif
#endif
#ifndef __RTW_UTFREE__
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T power_FCHPS_MEA_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr
, int_T * tailPtr , int_T * headPtr , int_T * lastPtr , real_T tMinusDelay ,
real_T * * tBufPtr , real_T * * uBufPtr , real_T * * xBufPtr , boolean_T
isfixedbuf , boolean_T istransportdelay , int_T * maxNewBufSzPtr ) ; real_T
power_FCHPS_MEA_acc_rt_VTDelayfindtDInterpolate ( real_T x , real_T * tBuf ,
real_T * uBuf , real_T * xBuf , int_T bufSz , int_T head , int_T tail , int_T
* pLast , real_T t , real_T tStart , boolean_T discrete , boolean_T
minorStepAndTAtLastMajorOutput , real_T initOutput , real_T * appliedDelay )
; extern real_T look1_binlxpw ( real_T u0 , const real_T bp0 [ ] , const
real_T table [ ] , uint32_T maxIndex ) ; void
power_FCHPS_MEA_Subsystempi2delay_Init ( SimStruct * S ,
B_Subsystempi2delay_power_FCHPS_MEA_T * localB ,
P_Subsystempi2delay_power_FCHPS_MEA_T * localP ) ; void
power_FCHPS_MEA_Subsystempi2delay_Disable ( SimStruct * S ,
DW_Subsystempi2delay_power_FCHPS_MEA_T * localDW ) ; void
power_FCHPS_MEA_Subsystempi2delay ( SimStruct * S , uint8_T rtu_Enable ,
const real_T rtu_alpha_beta [ 2 ] , real_T rtu_wt ,
B_Subsystempi2delay_power_FCHPS_MEA_T * localB ,
DW_Subsystempi2delay_power_FCHPS_MEA_T * localDW ) ; void
power_FCHPS_MEA_Subsystem1_Init ( SimStruct * S ,
B_Subsystem1_power_FCHPS_MEA_T * localB , P_Subsystem1_power_FCHPS_MEA_T *
localP ) ; void power_FCHPS_MEA_Subsystem1_Disable ( SimStruct * S ,
DW_Subsystem1_power_FCHPS_MEA_T * localDW ) ; void power_FCHPS_MEA_Subsystem1
( SimStruct * S , uint8_T rtu_Enable , const real_T rtu_alpha_beta [ 2 ] ,
real_T rtu_wt , B_Subsystem1_power_FCHPS_MEA_T * localB ,
DW_Subsystem1_power_FCHPS_MEA_T * localDW ) ; void
power_FCHPS_MEA_Subsystempi2delay_Term ( SimStruct * const S ) ; void
power_FCHPS_MEA_Subsystem1_Term ( SimStruct * const S ) ;
#endif

#include <math.h>
#include "power_FCHPS_MEA_acc.h"
#include "power_FCHPS_MEA_acc_private.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include <stdio.h>
#include "slexec_vm_simstruct_bridge.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_lookup_functions.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "simtarget/slSimTgtMdlrefSfcnBridge.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#include "simtarget/slAccSfcnBridge.h"
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T power_FCHPS_MEA_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr
, int_T * tailPtr , int_T * headPtr , int_T * lastPtr , real_T tMinusDelay ,
real_T * * tBufPtr , real_T * * uBufPtr , real_T * * xBufPtr , boolean_T
isfixedbuf , boolean_T istransportdelay , int_T * maxNewBufSzPtr ) { int_T
testIdx ; int_T tail = * tailPtr ; int_T bufSz = * bufSzPtr ; real_T * tBuf =
* tBufPtr ; real_T * xBuf = ( NULL ) ; int_T numBuffer = 2 ; if (
istransportdelay ) { numBuffer = 3 ; xBuf = * xBufPtr ; } testIdx = ( tail <
( bufSz - 1 ) ) ? ( tail + 1 ) : 0 ; if ( ( tMinusDelay <= tBuf [ testIdx ] )
&& ! isfixedbuf ) { int_T j ; real_T * tempT ; real_T * tempU ; real_T *
tempX = ( NULL ) ; real_T * uBuf = * uBufPtr ; int_T newBufSz = bufSz + 1024
; if ( newBufSz > * maxNewBufSzPtr ) { * maxNewBufSzPtr = newBufSz ; } tempU
= ( real_T * ) utMalloc ( numBuffer * newBufSz * sizeof ( real_T ) ) ; if (
tempU == ( NULL ) ) { return ( false ) ; } tempT = tempU + newBufSz ; if (
istransportdelay ) tempX = tempT + newBufSz ; for ( j = tail ; j < bufSz ; j
++ ) { tempT [ j - tail ] = tBuf [ j ] ; tempU [ j - tail ] = uBuf [ j ] ; if
( istransportdelay ) tempX [ j - tail ] = xBuf [ j ] ; } for ( j = 0 ; j <
tail ; j ++ ) { tempT [ j + bufSz - tail ] = tBuf [ j ] ; tempU [ j + bufSz -
tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j + bufSz - tail ] =
xBuf [ j ] ; } if ( * lastPtr > tail ) { * lastPtr -= tail ; } else { *
lastPtr += ( bufSz - tail ) ; } * tailPtr = 0 ; * headPtr = bufSz ; utFree (
uBuf ) ; * bufSzPtr = newBufSz ; * tBufPtr = tempT ; * uBufPtr = tempU ; if (
istransportdelay ) * xBufPtr = tempX ; } else { * tailPtr = testIdx ; }
return ( true ) ; } real_T power_FCHPS_MEA_acc_rt_VTDelayfindtDInterpolate (
real_T x , real_T * tBuf , real_T * uBuf , real_T * xBuf , int_T bufSz ,
int_T head , int_T tail , int_T * pLast , real_T t , real_T tStart ,
boolean_T discrete , boolean_T minorStepAndTAtLastMajorOutput , real_T
initOutput , real_T * appliedDelay ) { int_T n , k ; real_T f ; int_T kp1 ;
real_T tminustD , tL , tR , uD , uL , uR , fU ; if (
minorStepAndTAtLastMajorOutput ) { if ( * pLast == head ) { * pLast = ( *
pLast == 0 ) ? bufSz - 1 : * pLast - 1 ; } head = ( head == 0 ) ? bufSz - 1 :
head - 1 ; } if ( x <= 1 ) { return initOutput ; } k = * pLast ; n = 0 ; for
( ; ; ) { n ++ ; if ( n > bufSz ) break ; if ( x - xBuf [ k ] > 1.0 ) { if (
k == head ) { int_T km1 ; f = ( x - 1.0 - xBuf [ k ] ) / ( x - xBuf [ k ] ) ;
tminustD = ( 1.0 - f ) * tBuf [ k ] + f * t ; km1 = k - 1 ; if ( km1 < 0 )
km1 = bufSz - 1 ; tL = tBuf [ km1 ] ; tR = tBuf [ k ] ; uL = uBuf [ km1 ] ;
uR = uBuf [ k ] ; break ; } kp1 = k + 1 ; if ( kp1 == bufSz ) kp1 = 0 ; if (
x - xBuf [ kp1 ] <= 1.0 ) { f = ( x - 1.0 - xBuf [ k ] ) / ( xBuf [ kp1 ] -
xBuf [ k ] ) ; tL = tBuf [ k ] ; tR = tBuf [ kp1 ] ; uL = uBuf [ k ] ; uR =
uBuf [ kp1 ] ; tminustD = ( 1.0 - f ) * tL + f * tR ; break ; } k = kp1 ; }
else { if ( k == tail ) { f = ( x - 1.0 ) / xBuf [ k ] ; if ( discrete ) {
return ( uBuf [ tail ] ) ; } kp1 = k + 1 ; if ( kp1 == bufSz ) kp1 = 0 ;
tminustD = ( 1 - f ) * tStart + f * tBuf [ k ] ; tL = tBuf [ k ] ; tR = tBuf
[ kp1 ] ; uL = uBuf [ k ] ; uR = uBuf [ kp1 ] ; break ; } k = k - 1 ; if ( k
< 0 ) k = bufSz - 1 ; } } * pLast = k ; if ( tR == tL ) { fU = 1.0 ; } else {
fU = ( tminustD - tL ) / ( tR - tL ) ; } if ( discrete ) { uD = ( fU > ( 1.0
- fU ) ) ? uR : uL ; } else { uD = ( 1.0 - fU ) * uL + fU * uR ; } *
appliedDelay = t - tminustD ; return uD ; } real_T look1_binlxpw ( real_T u0
, const real_T bp0 [ ] , const real_T table [ ] , uint32_T maxIndex ) {
real_T frac ; real_T yL_0d0 ; uint32_T bpIdx ; uint32_T iLeft ; uint32_T
iRght ; if ( u0 <= bp0 [ 0U ] ) { iLeft = 0U ; frac = ( u0 - bp0 [ 0U ] ) / (
bp0 [ 1U ] - bp0 [ 0U ] ) ; } else if ( u0 < bp0 [ maxIndex ] ) { bpIdx =
maxIndex >> 1U ; iLeft = 0U ; iRght = maxIndex ; while ( iRght - iLeft > 1U )
{ if ( u0 < bp0 [ bpIdx ] ) { iRght = bpIdx ; } else { iLeft = bpIdx ; }
bpIdx = ( iRght + iLeft ) >> 1U ; } frac = ( u0 - bp0 [ iLeft ] ) / ( bp0 [
iLeft + 1U ] - bp0 [ iLeft ] ) ; } else { iLeft = maxIndex - 1U ; frac = ( u0
- bp0 [ maxIndex - 1U ] ) / ( bp0 [ maxIndex ] - bp0 [ maxIndex - 1U ] ) ; }
yL_0d0 = table [ iLeft ] ; return ( table [ iLeft + 1U ] - yL_0d0 ) * frac +
yL_0d0 ; } void rt_ssGetBlockPath ( SimStruct * S , int_T sysIdx , int_T
blkIdx , char_T * * path ) { _ssGetBlockPath ( S , sysIdx , blkIdx , path ) ;
} void rt_ssSet_slErrMsg ( SimStruct * S , void * diag ) { if ( !
_ssIsErrorStatusAslErrMsg ( S ) ) { _ssSet_slErrMsg ( S , diag ) ; } else {
_ssDiscardDiagnostic ( S , diag ) ; } } void rt_ssReportDiagnosticAsWarning (
SimStruct * S , void * diag ) { _ssReportDiagnosticAsWarning ( S , diag ) ; }
void power_FCHPS_MEA_Subsystempi2delay_Init ( SimStruct * S ,
B_Subsystempi2delay_power_FCHPS_MEA_T * localB ,
P_Subsystempi2delay_power_FCHPS_MEA_T * localP ) { localB -> B_2_0_0 = localP
-> P_0 [ 0 ] ; localB -> B_2_1_0 = localP -> P_0 [ 1 ] ; } void
power_FCHPS_MEA_Subsystempi2delay_Disable ( SimStruct * S ,
DW_Subsystempi2delay_power_FCHPS_MEA_T * localDW ) { localDW ->
Subsystempi2delay_MODE = false ; } void power_FCHPS_MEA_Subsystempi2delay (
SimStruct * S , uint8_T rtu_Enable , const real_T rtu_alpha_beta [ 2 ] ,
real_T rtu_wt , B_Subsystempi2delay_power_FCHPS_MEA_T * localB ,
DW_Subsystempi2delay_power_FCHPS_MEA_T * localDW ) { int32_T isHit ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( ( isHit != 0 ) && ( ssIsMajorTimeStep ( S
) != 0 ) ) { if ( rtu_Enable > 0 ) { if ( ! localDW -> Subsystempi2delay_MODE
) { if ( ssGetTaskTime ( S , 1 ) != ssGetTStart ( S ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } localDW ->
Subsystempi2delay_MODE = true ; } } else { if ( localDW ->
Subsystempi2delay_MODE ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
power_FCHPS_MEA_Subsystempi2delay_Disable ( S , localDW ) ; } } } if (
localDW -> Subsystempi2delay_MODE ) { localB -> B_2_0_0 = rtu_alpha_beta [ 0
] * muDoubleScalarSin ( rtu_wt ) - rtu_alpha_beta [ 1 ] * muDoubleScalarCos (
rtu_wt ) ; localB -> B_2_1_0 = rtu_alpha_beta [ 0 ] * muDoubleScalarCos (
rtu_wt ) + rtu_alpha_beta [ 1 ] * muDoubleScalarSin ( rtu_wt ) ; if (
ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( localDW ->
Subsystempi2delay_SubsysRanBC ) ; } } } void
power_FCHPS_MEA_Subsystempi2delay_Term ( SimStruct * const S ) { } void
power_FCHPS_MEA_Subsystem1_Init ( SimStruct * S ,
B_Subsystem1_power_FCHPS_MEA_T * localB , P_Subsystem1_power_FCHPS_MEA_T *
localP ) { localB -> B_3_0_0 = localP -> P_0 [ 0 ] ; localB -> B_3_1_0 =
localP -> P_0 [ 1 ] ; } void power_FCHPS_MEA_Subsystem1_Disable ( SimStruct *
S , DW_Subsystem1_power_FCHPS_MEA_T * localDW ) { localDW -> Subsystem1_MODE
= false ; } void power_FCHPS_MEA_Subsystem1 ( SimStruct * S , uint8_T
rtu_Enable , const real_T rtu_alpha_beta [ 2 ] , real_T rtu_wt ,
B_Subsystem1_power_FCHPS_MEA_T * localB , DW_Subsystem1_power_FCHPS_MEA_T *
localDW ) { int32_T isHit ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( (
isHit != 0 ) && ( ssIsMajorTimeStep ( S ) != 0 ) ) { if ( rtu_Enable > 0 ) {
if ( ! localDW -> Subsystem1_MODE ) { if ( ssGetTaskTime ( S , 1 ) !=
ssGetTStart ( S ) ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; }
localDW -> Subsystem1_MODE = true ; } } else { if ( localDW ->
Subsystem1_MODE ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
power_FCHPS_MEA_Subsystem1_Disable ( S , localDW ) ; } } } if ( localDW ->
Subsystem1_MODE ) { localB -> B_3_0_0 = rtu_alpha_beta [ 0 ] *
muDoubleScalarCos ( rtu_wt ) + rtu_alpha_beta [ 1 ] * muDoubleScalarSin (
rtu_wt ) ; localB -> B_3_1_0 = - rtu_alpha_beta [ 0 ] * muDoubleScalarSin (
rtu_wt ) + rtu_alpha_beta [ 1 ] * muDoubleScalarCos ( rtu_wt ) ; if (
ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( localDW ->
Subsystem1_SubsysRanBC ) ; } } } void power_FCHPS_MEA_Subsystem1_Term (
SimStruct * const S ) { } static void mdlOutputs ( SimStruct * S , int_T tid
) { real_T B_28_283_0 ; B_power_FCHPS_MEA_T * _rtB ; DW_power_FCHPS_MEA_T *
_rtDW ; P_power_FCHPS_MEA_T * _rtP ; PrevZCX_power_FCHPS_MEA_T * _rtZCE ;
X_power_FCHPS_MEA_T * _rtX ; real_T rtb_B_28_115_0 ; real_T rtb_B_28_123_0 ;
real_T rtb_B_28_127_0 ; real_T rtb_B_28_131_0 ; real_T rtb_B_28_159_0 ;
real_T rtb_B_28_164_0 ; real_T rtb_B_28_165_0 ; real_T rtb_B_28_16_0 ; real_T
rtb_B_28_185_0 ; real_T rtb_B_28_19_0 ; real_T rtb_B_28_20_0 ; real_T
rtb_B_28_21_0 ; real_T rtb_B_28_224_0 ; real_T rtb_B_28_31_0 ; real_T
rtb_B_28_362_0 ; real_T rtb_B_28_364_0 ; real_T rtb_B_28_37_0 ; real_T
rtb_B_28_385_0 ; real_T rtb_B_28_391_0 ; real_T rtb_B_28_436_0 ; real_T
rtb_B_28_437_0 ; real_T rtb_B_28_438_0 ; real_T rtb_B_28_4_0 ; real_T
rtb_B_28_51_0 ; real_T rtb_B_28_52_0 ; real_T rtb_B_28_5_0 ; real_T
rtb_B_28_6_0 ; real_T rtb_B_28_94_0 ; real_T rtb_B_28_99_0 ; real_T tmp ;
real_T tmp_0 ; int32_T isHit ; boolean_T rtb_B_28_121_0 ; boolean_T
rtb_B_28_13_0 ; boolean_T rtb_B_28_141_0 ; boolean_T rtb_B_28_172_0 ;
boolean_T rtb_B_28_360_0 ; boolean_T rtb_B_28_38_0 ; boolean_T rtb_B_28_414_0
; boolean_T rtb_B_28_445_0 ; boolean_T rtb_B_28_582_0 ; _rtDW = ( (
DW_power_FCHPS_MEA_T * ) ssGetRootDWork ( S ) ) ; _rtZCE = ( (
PrevZCX_power_FCHPS_MEA_T * ) _ssGetPrevZCSigState ( S ) ) ; _rtX = ( (
X_power_FCHPS_MEA_T * ) ssGetContStates ( S ) ) ; _rtP = ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_power_FCHPS_MEA_T * ) _ssGetModelBlockIO ( S ) ) ; isHit = ssIsSampleHit (
S , 2 , 0 ) ; if ( isHit != 0 ) { if ( _rtDW -> systemEnable != 0 ) { tmp =
ssGetTaskTime ( S , 2 ) ; tmp = muDoubleScalarSin ( _rtP -> P_35 * tmp ) ;
tmp_0 = ssGetTaskTime ( S , 2 ) ; tmp_0 = muDoubleScalarCos ( _rtP -> P_35 *
tmp_0 ) ; _rtDW -> lastSin [ 0 ] = tmp ; _rtDW -> lastCos [ 0 ] = tmp_0 ;
_rtDW -> lastSin [ 1 ] = tmp ; _rtDW -> lastCos [ 1 ] = tmp_0 ; _rtDW ->
lastSin [ 2 ] = tmp ; _rtDW -> lastCos [ 2 ] = tmp_0 ; _rtDW -> systemEnable
= 0 ; } _rtB -> B_28_0_0 [ 0 ] = ( ( _rtDW -> lastSin [ 0 ] * _rtP -> P_39 [
0 ] + _rtDW -> lastCos [ 0 ] * _rtP -> P_38 [ 0 ] ) * _rtP -> P_37 [ 0 ] + (
_rtDW -> lastCos [ 0 ] * _rtP -> P_39 [ 0 ] - _rtDW -> lastSin [ 0 ] * _rtP
-> P_38 [ 0 ] ) * _rtP -> P_36 [ 0 ] ) * _rtP -> P_33 + _rtP -> P_34 ; _rtB
-> B_28_0_0 [ 1 ] = ( ( _rtDW -> lastSin [ 1 ] * _rtP -> P_39 [ 1 ] + _rtDW
-> lastCos [ 1 ] * _rtP -> P_38 [ 1 ] ) * _rtP -> P_37 [ 1 ] + ( _rtDW ->
lastCos [ 1 ] * _rtP -> P_39 [ 1 ] - _rtDW -> lastSin [ 1 ] * _rtP -> P_38 [
1 ] ) * _rtP -> P_36 [ 1 ] ) * _rtP -> P_33 + _rtP -> P_34 ; _rtB -> B_28_0_0
[ 2 ] = ( ( _rtDW -> lastSin [ 2 ] * _rtP -> P_39 [ 2 ] + _rtDW -> lastCos [
2 ] * _rtP -> P_38 [ 2 ] ) * _rtP -> P_37 [ 2 ] + ( _rtDW -> lastCos [ 2 ] *
_rtP -> P_39 [ 2 ] - _rtDW -> lastSin [ 2 ] * _rtP -> P_38 [ 2 ] ) * _rtP ->
P_36 [ 2 ] ) * _rtP -> P_33 + _rtP -> P_34 ; _rtB -> B_28_1_0 = _rtDW ->
UnitDelay_DSTATE ; _rtB -> B_28_2_0 = _rtDW -> UnitDelay1_DSTATE ;
ssCallAccelRunBlock ( S , 28 , 3 , SS_CALL_MDL_OUTPUTS ) ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { rtb_B_28_4_0 = _rtDW ->
itinit1_PreviousInput ; rtb_B_28_5_0 = _rtP -> P_45 * _rtDW ->
itinit1_PreviousInput ; rtb_B_28_6_0 = 1.000001 * rtb_B_28_5_0 *
0.96339113680154431 / 0.9999 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if (
isHit != 0 ) { _rtB -> B_28_7_0 = _rtP -> P_46 * _rtDW ->
Currentfilter_states ; _rtB -> B_28_9_0 = ( _rtB -> B_28_7_0 >
power_FCHPS_MEA_rtC ( S ) -> B_28_0_0 ) ; } isHit = ssIsSampleHit ( S , 1 , 0
) ; if ( isHit != 0 ) { _rtB -> B_28_10_0 = _rtDW -> itinit_PreviousInput ; }
isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { if ( _rtDW ->
inti_IC_LOADING != 0 ) { _rtDW -> inti_DSTATE = _rtB -> B_28_10_0 ; if (
_rtDW -> inti_DSTATE >= _rtP -> P_51 ) { _rtDW -> inti_DSTATE = _rtP -> P_51
; } else { if ( _rtDW -> inti_DSTATE <= _rtP -> P_52 ) { _rtDW -> inti_DSTATE
= _rtP -> P_52 ; } } } if ( ( _rtB -> B_28_9_0 > 0.0 ) && ( _rtDW ->
inti_PrevResetState <= 0 ) ) { _rtDW -> inti_DSTATE = _rtB -> B_28_10_0 ; if
( _rtDW -> inti_DSTATE >= _rtP -> P_51 ) { _rtDW -> inti_DSTATE = _rtP ->
P_51 ; } else { if ( _rtDW -> inti_DSTATE <= _rtP -> P_52 ) { _rtDW ->
inti_DSTATE = _rtP -> P_52 ; } } } if ( _rtDW -> inti_DSTATE >= _rtP -> P_51
) { _rtDW -> inti_DSTATE = _rtP -> P_51 ; } else { if ( _rtDW -> inti_DSTATE
<= _rtP -> P_52 ) { _rtDW -> inti_DSTATE = _rtP -> P_52 ; } } _rtB ->
B_28_12_0 = _rtP -> P_53 * _rtDW -> inti_DSTATE ; } isHit = ssIsSampleHit ( S
, 1 , 0 ) ; if ( isHit != 0 ) { rtb_B_28_13_0 = ( _rtB -> B_28_12_0 >
rtb_B_28_5_0 ) ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) {
if ( _rtB -> B_28_12_0 < _rtB -> B_28_47_0_l ) { _rtB -> B_28_15_0 = _rtB ->
B_28_47_0_l ; } else { _rtB -> B_28_15_0 = _rtB -> B_28_12_0 ; } } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( rtb_B_28_13_0 ) {
rtb_B_28_16_0 = rtb_B_28_5_0 ; } else { rtb_B_28_16_0 = _rtB -> B_28_15_0 ; }
if ( rtb_B_28_6_0 <= rtb_B_28_16_0 ) { rtb_B_28_16_0 = rtb_B_28_5_0 ; }
rtb_B_28_19_0 = - 0.010421968635193955 * rtb_B_28_4_0 / ( rtb_B_28_4_0 -
rtb_B_28_16_0 ) * rtb_B_28_16_0 ; rtb_B_28_20_0 = - _rtB -> B_28_9_0 *
0.010421968635193955 * _rtB -> B_28_7_0 * rtb_B_28_4_0 / ( rtb_B_28_4_0 -
rtb_B_28_16_0 ) ; rtb_B_28_21_0 = _rtP -> P_54 * rtb_B_28_4_0 ; if ( ! ( _rtB
-> B_28_12_0 > rtb_B_28_21_0 ) ) { rtb_B_28_5_0 = - rtb_B_28_21_0 * 0.999 *
0.1 * 0.9999 ; if ( _rtB -> B_28_12_0 < rtb_B_28_5_0 ) { rtb_B_28_21_0 =
rtb_B_28_5_0 ; } else { rtb_B_28_21_0 = _rtB -> B_28_12_0 ; } } } isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_28_26_0 = ( _rtB
-> B_28_7_0 < power_FCHPS_MEA_rtC ( S ) -> B_28_1_0 ) ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { switch ( ( int32_T ) _rtB
-> B_28_48_0_j ) { case 1 : rtb_B_28_31_0 = - ( _rtB -> B_28_52_0 * _rtB ->
B_28_26_0 ) * 0.010421968635193955 * ( _rtB -> B_28_52_0 * _rtB -> B_28_7_0 )
* ( 41.519999999999875 / ( _rtB -> B_28_52_0 * rtb_B_28_21_0 +
4.1519999999999877 ) ) ; break ; case 2 : rtb_B_28_31_0 = _rtB -> B_28_49_0 *
rtb_B_28_4_0 ; rtb_B_28_31_0 = - ( _rtB -> B_28_49_0 * _rtB -> B_28_26_0 ) *
0.010421968635193955 * ( _rtB -> B_28_49_0 * _rtB -> B_28_7_0 ) *
rtb_B_28_31_0 / ( _rtB -> B_28_49_0 * rtb_B_28_21_0 + rtb_B_28_31_0 * 0.1 ) ;
break ; case 3 : rtb_B_28_31_0 = - ( _rtB -> B_28_51_0 * _rtB -> B_28_26_0 )
* 0.010421968635193955 * ( _rtB -> B_28_51_0 * _rtB -> B_28_7_0 ) * (
41.519999999999875 / ( muDoubleScalarAbs ( _rtB -> B_28_51_0 * rtb_B_28_21_0
) + 4.1519999999999877 ) ) ; break ; default : rtb_B_28_31_0 = - ( _rtB ->
B_28_50_0 * _rtB -> B_28_26_0 ) * 0.010421968635193955 * ( _rtB -> B_28_50_0
* _rtB -> B_28_7_0 ) * ( 41.519999999999875 / ( muDoubleScalarAbs ( _rtB ->
B_28_50_0 * rtb_B_28_21_0 ) + 4.1519999999999877 ) ) ; break ; } } isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_28_32_0 = _rtDW
-> DiscreteTimeIntegrator_DSTATE ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if
( isHit != 0 ) { switch ( ( int32_T ) _rtB -> B_28_53_0_d ) { case 1 :
rtb_B_28_37_0 = _rtB -> B_28_32_0 ; break ; case 2 : if ( rtb_B_28_16_0 >
_rtP -> P_24 ) { rtb_B_28_37_0 = _rtP -> P_24 ; } else if ( rtb_B_28_16_0 <
_rtP -> P_25 ) { rtb_B_28_37_0 = _rtP -> P_25 ; } else { rtb_B_28_37_0 =
rtb_B_28_16_0 ; } rtb_B_28_37_0 = muDoubleScalarExp ( - 1.5306122448979591 *
rtb_B_28_37_0 ) * 3.5357645420568784 ; break ; case 3 : rtb_B_28_37_0 = _rtB
-> B_28_32_0 ; break ; default : rtb_B_28_37_0 = _rtB -> B_28_32_0 ; break ;
} rtb_B_28_37_0 = ( ( ( ( rtb_B_28_19_0 + rtb_B_28_20_0 ) + rtb_B_28_31_0 ) +
rtb_B_28_37_0 ) + - 0.0 * rtb_B_28_16_0 ) + _rtB -> B_28_44_0_m ;
rtb_B_28_38_0 = ( rtb_B_28_37_0 > _rtB -> B_28_45_0_n ) ; } isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_28_39_0 = _rtDW
-> Memory2_PreviousInput ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit
!= 0 ) { if ( rtb_B_28_38_0 ) { _rtB -> B_28_41_0 = _rtB -> B_28_45_0_n ; }
else if ( rtb_B_28_37_0 < _rtB -> B_28_39_0 ) { _rtB -> B_28_41_0 = _rtB ->
B_28_39_0 ; } else { _rtB -> B_28_41_0 = rtb_B_28_37_0 ; } } isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_28_42_0 = _rtDW
-> UnitDelay2_DSTATE ; _rtB -> B_28_43_0 = _rtDW -> UnitDelay1_DSTATE_a ;
_rtB -> B_28_44_0 = _rtDW -> UnitDelay3_DSTATE ; _rtB -> B_28_45_0 = _rtDW ->
UnitDelay2_DSTATE_m ; _rtB -> B_28_46_0 = _rtDW -> UnitDelay1_DSTATE_d ; _rtB
-> B_28_47_0 = _rtP -> P_63 * _rtDW -> Celldynamic_states ; _rtB -> B_28_48_0
= _rtDW -> UnitDelay_DSTATE_a ; rtb_B_28_51_0 = 1.0311642900000002E+10 * _rtB
-> B_28_48_0 / 2.2438542634362938E+10 ; if ( rtb_B_28_51_0 > _rtP -> P_67 ) {
rtb_B_28_51_0 = _rtP -> P_67 ; } else { if ( rtb_B_28_51_0 < _rtP -> P_68 ) {
rtb_B_28_51_0 = _rtP -> P_68 ; } } if ( rtb_B_28_51_0 > _rtP -> P_69 ) {
rtb_B_28_51_0 = _rtP -> P_69 ; } else { if ( rtb_B_28_51_0 < _rtP -> P_70 ) {
rtb_B_28_51_0 = _rtP -> P_70 ; } } rtb_B_28_52_0 = 3.9E+6 * _rtB -> B_28_48_0
* 8.3145 * _rtB -> B_28_98_0 / ( 192970.0 * _rtB -> B_28_94_0 * 101325.0 *
rtb_B_28_51_0 * _rtB -> B_28_91_0_f ) ; if ( _rtB -> B_28_89_0 > _rtP -> P_71
) { _rtB -> B_28_53_0 = rtb_B_28_51_0 ; } else { _rtB -> B_28_53_0 =
rtb_B_28_52_0 ; } if ( _rtB -> B_28_53_0 > _rtP -> P_72 ) { _rtB -> B_28_54_0
= _rtP -> P_72 ; } else if ( _rtB -> B_28_53_0 < _rtP -> P_73 ) { _rtB ->
B_28_54_0 = _rtP -> P_73 ; } else { _rtB -> B_28_54_0 = _rtB -> B_28_53_0 ; }
} _rtB -> B_28_55_0 = 0.0 ; _rtB -> B_28_55_0 += _rtP -> P_75 * _rtX ->
Airblowerdelay2_CSTATE ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
Saturation4_MODE = _rtB -> B_28_55_0 >= _rtP -> P_76 ? 1 : _rtB -> B_28_55_0
> _rtP -> P_77 ? 0 : - 1 ; } _rtB -> B_28_56_0 = _rtDW -> Saturation4_MODE ==
1 ? _rtP -> P_76 : _rtDW -> Saturation4_MODE == - 1 ? _rtP -> P_77 : _rtB ->
B_28_55_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Saturation3_MODE =
_rtB -> B_28_56_0 >= _rtP -> P_78 ? 1 : _rtB -> B_28_56_0 > _rtP -> P_79 ? 0
: - 1 ; } rtb_B_28_31_0 = 3.9E+6 * _rtB -> B_28_48_0 * 8.3145 * _rtB ->
B_28_98_0 / ( 385940.0 * _rtB -> B_28_96_0 * 101325.0 * ( _rtDW ->
Saturation3_MODE == 1 ? _rtP -> P_78 : _rtDW -> Saturation3_MODE == - 1 ?
_rtP -> P_79 : _rtB -> B_28_56_0 ) * _rtB -> B_28_92_0 ) ; if ( _rtB ->
B_28_90_0 > _rtP -> P_80 ) { _rtB -> B_28_59_0 = _rtB -> B_28_56_0 ; } else {
_rtB -> B_28_59_0 = rtb_B_28_31_0 ; } if ( ssIsMajorTimeStep ( S ) != 0 ) {
_rtDW -> Saturation4_MODE_n = _rtB -> B_28_59_0 >= _rtP -> P_81 ? 1 : _rtB ->
B_28_59_0 > _rtP -> P_82 ? 0 : - 1 ; } rtb_B_28_37_0 = _rtDW ->
Saturation4_MODE_n == 1 ? _rtP -> P_81 : _rtDW -> Saturation4_MODE_n == - 1 ?
_rtP -> P_82 : _rtB -> B_28_59_0 ; _rtB -> B_28_61_0 = _rtB -> B_28_98_0 ;
_rtB -> B_28_62_0 = ( 1.0 - _rtB -> B_28_54_0 ) * _rtB -> B_28_91_0_f * _rtB
-> B_28_94_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
Saturation1_MODE = _rtB -> B_28_62_0 >= _rtP -> P_83 ? 1 : _rtB -> B_28_62_0
> _rtP -> P_84 ? 0 : - 1 ; } rtb_B_28_19_0 = _rtDW -> Saturation1_MODE == 1 ?
_rtP -> P_83 : _rtDW -> Saturation1_MODE == - 1 ? _rtP -> P_84 : _rtB ->
B_28_62_0 ; _rtB -> B_28_64_0 = ( 1.0 - rtb_B_28_37_0 ) * _rtB -> B_28_92_0 *
_rtB -> B_28_96_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
Saturation4_MODE_nx = _rtB -> B_28_64_0 >= _rtP -> P_85 ? 1 : _rtB ->
B_28_64_0 > _rtP -> P_86 ? 0 : - 1 ; } rtb_B_28_20_0 = _rtDW ->
Saturation4_MODE_nx == 1 ? _rtP -> P_85 : _rtDW -> Saturation4_MODE_nx == - 1
? _rtP -> P_86 : _rtB -> B_28_64_0 ; _rtB -> B_28_66_0 = ( 2.0 * _rtB ->
B_28_92_0 * rtb_B_28_37_0 + 0.01 ) * _rtB -> B_28_96_0 ; if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Saturation5_MODE = _rtB ->
B_28_66_0 >= _rtP -> P_87 ? 1 : _rtB -> B_28_66_0 > _rtP -> P_88 ? 0 : - 1 ;
_rtDW -> Switch_Mode = ( _rtB -> B_28_61_0 >= _rtP -> P_89 ) ; } _rtB ->
B_28_67_0 = _rtDW -> Saturation5_MODE == 1 ? _rtP -> P_87 : _rtDW ->
Saturation5_MODE == - 1 ? _rtP -> P_88 : _rtB -> B_28_66_0 ; if (
rtb_B_28_20_0 < 0.0 ) { rtb_B_28_37_0 = - muDoubleScalarSqrt ( -
rtb_B_28_20_0 ) ; } else { rtb_B_28_37_0 = muDoubleScalarSqrt ( rtb_B_28_20_0
) ; } if ( _rtDW -> Switch_Mode ) { tmp = _rtB -> B_28_67_0 ; } else { tmp =
_rtB -> B_28_88_0_j ; } rtb_B_28_37_0 = rtb_B_28_19_0 * rtb_B_28_37_0 / tmp ;
if ( ssIsMajorTimeStep ( S ) != 0 ) { if ( _rtDW -> NerstVoltage_DWORK1 != 0
) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; _rtDW ->
NerstVoltage_DWORK1 = 0 ; } } else { if ( rtb_B_28_37_0 < 0.0 ) {
rtb_B_28_37_0 = 0.0 ; _rtDW -> NerstVoltage_DWORK1 = 1 ; } } rtb_B_28_37_0 =
( ( _rtB -> B_28_61_0 - 298.15 ) * - 0.00023024304296004561 + 1.229 ) +
8.3145 * _rtB -> B_28_61_0 / 192970.0 * muDoubleScalarLog ( rtb_B_28_37_0 ) ;
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Compare_Mode = ( _rtB -> B_28_59_0
> _rtB -> B_28_83_0_e ) ; } _rtB -> B_28_71_0 = _rtDW -> Compare_Mode ; }
rtb_B_28_37_0 = ( rtb_B_28_37_0 - ( _rtB -> B_28_59_0 - 0.4288457324020854 )
* 2.0 / 7.8193997606410246 ) * _rtB -> B_28_71_0 + ( 1.0 - _rtB -> B_28_71_0
) * rtb_B_28_37_0 ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) {
if ( _rtB -> B_28_48_0 > _rtP -> P_90 ) { _rtB -> B_28_73_0 = _rtP -> P_90 ;
} else if ( _rtB -> B_28_48_0 < _rtP -> P_91 ) { _rtB -> B_28_73_0 = _rtP ->
P_91 ; } else { _rtB -> B_28_73_0 = _rtB -> B_28_48_0 ; } _rtB -> B_28_75_0 =
( _rtB -> B_28_73_0 > _rtB -> B_28_85_0 ) ; } rtb_B_28_37_0 =
muDoubleScalarCos ( ( _rtB -> B_28_73_0 / 320.0 - 1.0 ) * 7.8539816339744828
) * rtb_B_28_37_0 * _rtB -> B_28_75_0 + ( 1.0 - _rtB -> B_28_75_0 ) *
rtb_B_28_37_0 ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) {
_rtB -> B_28_77_0_m = ( uint8_T ) ( _rtB -> B_28_48_0 > power_FCHPS_MEA_rtC (
S ) -> B_28_3_0 ) ; } _rtB -> B_28_78_0 [ 0 ] = ( real_T ) _rtB ->
B_28_77_0_m * _rtB -> B_28_59_0 ; _rtB -> B_28_78_0 [ 1 ] = ( real_T ) _rtB
-> B_28_77_0_m * _rtB -> B_28_53_0 ; _rtB -> B_28_79_0 [ 0 ] = _rtP -> P_92 [
0 ] * _rtB -> B_28_78_0 [ 0 ] ; _rtB -> B_28_79_0 [ 1 ] = _rtP -> P_92 [ 1 ]
* _rtB -> B_28_78_0 [ 1 ] ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtB ->
B_28_80_0 = _rtB -> B_28_79_0 [ 0 ] ; _rtDW -> MinMax_MODE = 0 ; if ( _rtB ->
B_28_79_0 [ 1 ] > _rtB -> B_28_79_0 [ 0 ] ) { _rtB -> B_28_80_0 = _rtB ->
B_28_79_0 [ 1 ] ; _rtDW -> MinMax_MODE = 1 ; } _rtDW -> Saturation2_MODE =
_rtB -> B_28_80_0 >= _rtP -> P_93 ? 1 : _rtB -> B_28_80_0 > _rtP -> P_94 ? 0
: - 1 ; } else { _rtB -> B_28_80_0 = _rtB -> B_28_79_0 [ _rtDW -> MinMax_MODE
] ; } _rtB -> B_28_81_0 = _rtDW -> Saturation2_MODE == 1 ? _rtP -> P_93 :
_rtDW -> Saturation2_MODE == - 1 ? _rtP -> P_94 : _rtB -> B_28_80_0 ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S
) != 0 ) { _rtDW -> Compare_Mode_h = ( _rtB -> B_28_81_0 > _rtB -> B_28_84_0
) ; } _rtB -> B_28_83_0 = _rtDW -> Compare_Mode_h ; } _rtB -> B_28_86_0 = (
muDoubleScalarCos ( ( _rtB -> B_28_81_0 - 1.0 ) * 7.8539816339744828 ) *
rtb_B_28_37_0 * _rtB -> B_28_83_0 + ( 1.0 - _rtB -> B_28_83_0 ) *
rtb_B_28_37_0 ) * _rtP -> P_95 + _rtB -> B_28_47_0 ; isHit = ssIsSampleHit (
S , 1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW
-> LowerRelop1_Mode = ( _rtB -> B_28_86_0 > _rtB -> B_28_86_0_b ) ; } _rtB ->
B_28_87_0_c = _rtDW -> LowerRelop1_Mode ; } isHit = ssIsSampleHit ( S , 2 , 0
) ; if ( isHit != 0 ) { _rtB -> B_28_88_0 = _rtP -> P_96 * _rtB -> B_28_48_0
; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> UpperRelop_Mode = ( _rtB ->
B_28_86_0 < _rtB -> B_28_88_0 ) ; } _rtB -> B_28_89_0_p = _rtDW ->
UpperRelop_Mode ; } if ( _rtB -> B_28_87_0_c ) { _rtB -> B_28_91_0 = _rtB ->
B_28_86_0_b ; } else if ( _rtB -> B_28_89_0_p ) { _rtB -> B_28_91_0 = _rtB ->
B_28_88_0 ; } else { _rtB -> B_28_91_0 = _rtB -> B_28_86_0 ; } isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { rtb_B_28_94_0 = _rtDW ->
DiscreteTimeIntegrator_DSTATE_f + _rtB -> B_28_99_0 ; if ( rtb_B_28_94_0 >
_rtP -> P_99 ) { rtb_B_28_94_0 = _rtP -> P_99 ; } else { if ( rtb_B_28_94_0 <
_rtP -> P_100 ) { rtb_B_28_94_0 = _rtP -> P_100 ; } } rtb_B_28_99_0 =
5.5496029969229008 / rtb_B_28_94_0 * muDoubleScalarAsinh (
0.0071777299424921562 * rtb_B_28_94_0 ) + _rtB -> B_28_105_0_i ; _rtB ->
B_28_100_0 = rtb_B_28_94_0 * rtb_B_28_99_0 ; _rtB -> B_28_101_0 = _rtDW ->
UnitDelay_DSTATE_c ; _rtB -> B_28_102_0 = _rtDW -> UnitDelay3_DSTATE_c ; _rtB
-> B_28_103_0 = _rtDW -> UnitDelay2_DSTATE_p ; _rtB -> B_28_104_0 = _rtDW ->
UnitDelay2_DSTATE_e ; _rtB -> B_28_105_0 = _rtDW -> UnitDelay3_DSTATE_l ;
_rtB -> B_28_106_0 = _rtDW -> UnitDelay2_DSTATE_j ; ssCallAccelRunBlock ( S ,
28 , 107 , SS_CALL_MDL_OUTPUTS ) ; rtb_B_28_94_0 = _rtP -> P_117 * _rtB ->
B_28_107_0 [ 18 ] ; rtb_B_28_115_0 = _rtP -> P_118 * _rtB -> B_28_107_0 [ 19
] ; _rtB -> B_28_117_0 = ( rtb_B_28_94_0 >= _rtP -> P_119 * rtb_B_28_115_0 )
; _rtB -> B_28_119_0 = ( _rtP -> P_120 * _rtB -> B_28_107_0 [ 43 ] <= _rtB ->
B_28_5_0 ) ; } _rtB -> B_28_120_0 = ssGetT ( S ) ; isHit = ssIsSampleHit ( S
, 1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW
-> RelationalOperator_Mode = ( _rtB -> B_28_120_0 >= _rtB -> B_28_3_0_c ) ; }
rtb_B_28_121_0 = _rtDW -> RelationalOperator_Mode ; } isHit = ssIsSampleHit (
S , 2 , 0 ) ; if ( isHit != 0 ) { rtb_B_28_123_0 = _rtP -> P_122 * _rtB ->
B_28_107_0 [ 41 ] ; _rtB -> B_28_126_0 = _rtP -> P_123 * _rtB -> B_28_107_0 [
34 ] ; rtb_B_28_127_0 = _rtB -> B_28_73_0_h - _rtB -> B_28_126_0 ;
rtb_B_28_131_0 = _rtP -> P_124 * rtb_B_28_127_0 + _rtDW ->
DiscreteTimeIntegrator_DSTATE_h ; if ( rtb_B_28_131_0 > _rtP -> P_129 ) {
rtb_B_28_131_0 = _rtP -> P_129 ; } else { if ( rtb_B_28_131_0 < _rtP -> P_130
) { rtb_B_28_131_0 = _rtP -> P_130 ; } } if ( _rtB -> B_28_126_0 >= _rtB ->
B_28_68_0 ) { _rtB -> B_28_135_0 = _rtB -> B_28_69_0 ; } else if ( _rtB ->
B_28_126_0 <= _rtB -> B_28_70_0 ) { _rtB -> B_28_135_0 = _rtB -> B_28_67_0_b
; } else { _rtB -> B_28_135_0 = _rtDW -> UnitDelay_DSTATE_m ; } if ( _rtB ->
B_28_135_0 > _rtP -> P_132 ) { if ( rtb_B_28_131_0 > _rtP -> P_26 ) { _rtB ->
B_28_137_0 = _rtP -> P_26 ; } else if ( rtb_B_28_131_0 < _rtP -> P_27 ) {
_rtB -> B_28_137_0 = _rtP -> P_27 ; } else { _rtB -> B_28_137_0 =
rtb_B_28_131_0 ; } } else { _rtB -> B_28_137_0 = _rtB -> B_28_58_0 ; } _rtB
-> B_28_138_0 = rtb_B_28_94_0 * _rtB -> B_28_4_0 / ( ( ( -
0.00493827160493827 * rtb_B_28_123_0 + 0.88888888888888884 ) * ( real_T ) (
rtb_B_28_123_0 >= 9.0 ) + ( real_T ) ( rtb_B_28_123_0 < 9.0 ) * 0.88 ) * (
_rtP -> P_121 * _rtB -> B_28_107_0 [ 20 ] ) + 0.1 ) * ( real_T ) (
rtb_B_28_123_0 > 20.0 ) + ( real_T ) ( rtb_B_28_123_0 <= 20.0 ) * _rtB ->
B_28_137_0 ; _rtB -> B_28_139_0 = ( _rtB -> B_28_138_0 >= _rtB -> B_28_6_0 )
; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { rtb_B_28_141_0
= ( _rtB -> B_28_117_0 || ( _rtB -> B_28_119_0 && rtb_B_28_121_0 && _rtB ->
B_28_139_0 ) ) ; _rtB -> B_28_142_0 = rtb_B_28_141_0 ; _rtB -> B_28_146_0 =
rtb_B_28_141_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) {
_rtB -> B_28_150_0 = _rtP -> P_133 * _rtB -> B_28_107_0 [ 40 ] ; if ( _rtB ->
B_28_135_0 > _rtP -> P_138 ) { _rtB -> B_28_158_0 = _rtB -> B_28_73_0_h ; }
else { _rtB -> B_28_158_0 = _rtB -> B_28_59_0_d ; } rtb_B_28_159_0 = _rtB ->
B_28_158_0 - rtb_B_28_94_0 ; _rtB -> B_28_161_0 = _rtP -> P_140 *
rtb_B_28_159_0 ; rtb_B_28_159_0 = _rtP -> P_139 * rtb_B_28_159_0 + _rtDW ->
DiscreteTimeIntegrator_DSTATE_p ; if ( rtb_B_28_159_0 > _rtP -> P_141 ) {
rtb_B_28_159_0 = _rtP -> P_141 ; } else { if ( rtb_B_28_159_0 < _rtP -> P_142
) { rtb_B_28_159_0 = _rtP -> P_142 ; } } rtb_B_28_164_0 = _rtDW ->
DiscreteTimeIntegrator_DSTATE_o ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if
( isHit != 0 ) { rtb_B_28_165_0 = _rtB -> B_28_138_0 * ( real_T )
rtb_B_28_141_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) {
rtb_B_28_37_0 = ( ( - 0.00493827160493827 * rtb_B_28_123_0 +
0.88888888888888884 ) * ( real_T ) ( rtb_B_28_123_0 >= 9.0 ) + ( real_T ) (
rtb_B_28_123_0 < 9.0 ) * 0.88 ) * rtb_B_28_115_0 ; if ( rtb_B_28_37_0 > _rtP
-> P_147 ) { rtb_B_28_37_0 = _rtP -> P_147 ; } else { if ( rtb_B_28_37_0 <
_rtP -> P_148 ) { rtb_B_28_37_0 = _rtP -> P_148 ; } } _rtB -> B_28_171_0 = (
rtb_B_28_159_0 + rtb_B_28_123_0 ) * ( rtb_B_28_94_0 / rtb_B_28_37_0 ) ; }
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { rtb_B_28_172_0 = (
_rtB -> B_28_171_0 > rtb_B_28_165_0 ) ; } isHit = ssIsSampleHit ( S , 2 , 0 )
; if ( isHit != 0 ) { if ( _rtB -> B_28_171_0 < _rtB -> B_28_2_0_k ) { _rtB
-> B_28_174_0 = _rtB -> B_28_2_0_k ; } else { _rtB -> B_28_174_0 = _rtB ->
B_28_171_0 ; } } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if
( ! rtb_B_28_172_0 ) { rtb_B_28_165_0 = _rtB -> B_28_174_0 ; } _rtB ->
B_28_176_0 = rtb_B_28_165_0 - _rtB -> B_28_150_0 ; } isHit = ssIsSampleHit (
S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_28_178_0 = _rtP -> P_150 * _rtB
-> B_28_176_0 ; rtb_B_28_37_0 = _rtP -> P_149 * _rtB -> B_28_176_0 +
rtb_B_28_164_0 ; if ( rtb_B_28_37_0 > _rtP -> P_151 ) { rtb_B_28_37_0 = _rtP
-> P_151 ; } else { if ( rtb_B_28_37_0 < _rtP -> P_152 ) { rtb_B_28_37_0 =
_rtP -> P_152 ; } } if ( rtb_B_28_94_0 > _rtP -> P_153 ) { rtb_B_28_159_0 =
_rtP -> P_153 ; } else if ( rtb_B_28_94_0 < _rtP -> P_154 ) { rtb_B_28_159_0
= _rtP -> P_154 ; } else { rtb_B_28_159_0 = rtb_B_28_94_0 ; } rtb_B_28_185_0
= _rtB -> B_28_1_0_c - ( rtb_B_28_115_0 - rtb_B_28_37_0 ) / rtb_B_28_159_0 ;
if ( rtb_B_28_185_0 > _rtP -> P_155 ) { rtb_B_28_185_0 = _rtP -> P_155 ; }
else { if ( rtb_B_28_185_0 < _rtP -> P_156 ) { rtb_B_28_185_0 = _rtP -> P_156
; } } _rtB -> B_28_186_0 = ( 1.0 - rtb_B_28_185_0 ) * rtb_B_28_94_0 ; _rtB ->
B_28_188_0 = ( ( - 0.00493827160493827 * rtb_B_28_123_0 + 0.88888888888888884
) * ( real_T ) ( rtb_B_28_123_0 >= 9.0 ) + ( real_T ) ( rtb_B_28_123_0 < 9.0
) * 0.88 ) * ( 1.0 - rtb_B_28_185_0 ) * _rtB -> B_28_150_0 ; rtb_B_28_185_0 =
_rtP -> P_157 * _rtB -> B_28_107_0 [ 42 ] ; rtb_B_28_224_0 = _rtP -> P_158 *
_rtB -> B_28_107_0 [ 44 ] ; rtb_B_28_123_0 = _rtP -> P_163 * _rtB ->
B_28_107_0 [ 21 ] ; rtb_B_28_94_0 = _rtB -> B_28_7_0_b - rtb_B_28_123_0 ;
_rtB -> B_28_232_0 = _rtP -> P_165 * rtb_B_28_94_0 ; rtb_B_28_37_0 = _rtP ->
P_164 * rtb_B_28_94_0 + _rtDW -> DiscreteTimeIntegrator_DSTATE_pd ; if (
rtb_B_28_37_0 > _rtP -> P_166 ) { rtb_B_28_37_0 = _rtP -> P_166 ; } else { if
( rtb_B_28_37_0 < _rtP -> P_167 ) { rtb_B_28_37_0 = _rtP -> P_167 ; } }
rtb_B_28_94_0 = rtb_B_28_37_0 + rtb_B_28_185_0 ; if ( rtb_B_28_94_0 > _rtB ->
B_28_8_0 ) { rtb_B_28_94_0 = _rtB -> B_28_8_0 ; } else { if ( rtb_B_28_94_0 <
_rtB -> B_28_9_0_p ) { rtb_B_28_94_0 = _rtB -> B_28_9_0_p ; } }
rtb_B_28_165_0 = rtb_B_28_94_0 - rtb_B_28_224_0 ; _rtB -> B_28_242_0 = _rtP
-> P_173 * rtb_B_28_165_0 ; rtb_B_28_94_0 = _rtP -> P_176 * _rtB ->
B_28_107_0 [ 22 ] ; rtb_B_28_37_0 = _rtP -> P_172 * rtb_B_28_165_0 + _rtDW ->
DiscreteTimeIntegrator_DSTATE_e ; if ( rtb_B_28_37_0 > _rtP -> P_174 ) {
rtb_B_28_37_0 = _rtP -> P_174 ; } else { if ( rtb_B_28_37_0 < _rtP -> P_175 )
{ rtb_B_28_37_0 = _rtP -> P_175 ; } } if ( rtb_B_28_94_0 > _rtP -> P_177 ) {
rtb_B_28_159_0 = _rtP -> P_177 ; } else if ( rtb_B_28_94_0 < _rtP -> P_178 )
{ rtb_B_28_159_0 = _rtP -> P_178 ; } else { rtb_B_28_159_0 = rtb_B_28_94_0 ;
} rtb_B_28_123_0 = ( rtb_B_28_37_0 + rtb_B_28_123_0 ) / rtb_B_28_159_0 ; if (
rtb_B_28_123_0 > _rtP -> P_179 ) { rtb_B_28_123_0 = _rtP -> P_179 ; } else {
if ( rtb_B_28_123_0 < _rtP -> P_180 ) { rtb_B_28_123_0 = _rtP -> P_180 ; } }
_rtB -> B_28_250_0 = rtb_B_28_123_0 * rtb_B_28_94_0 ; _rtB -> B_28_252_0 =
rtb_B_28_123_0 * rtb_B_28_224_0 / ( ( - 0.005611672278338942 * rtb_B_28_185_0
+ 0.88888888888888884 ) * ( real_T ) ( rtb_B_28_185_0 >= 7.92 ) + ( real_T )
( rtb_B_28_185_0 < 7.92 ) * 0.88 ) ; rtb_B_28_224_0 = _rtP -> P_181 * _rtB ->
B_28_107_0 [ 45 ] ; B_28_283_0 = ( - 0.0044444444444444418 * rtb_B_28_224_0 +
0.88888888888888884 ) * ( real_T ) ( rtb_B_28_224_0 >= 10.0 ) + ( real_T ) (
rtb_B_28_224_0 < 10.0 ) * 0.88 ; { if ( _rtDW ->
TAQSigLogging_InsertedFor_Fcn4_at_outport_0_PWORK . AQHandles &&
ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_Fcn4_at_outport_0_PWORK . AQHandles , ssGetTaskTime
( S , 2 ) , ( char * ) & B_28_283_0 + 0 ) ; } } rtb_B_28_37_0 = _rtP -> P_182
* rtb_B_28_131_0 ; if ( rtb_B_28_37_0 > _rtP -> P_183 ) { rtb_B_28_37_0 =
_rtP -> P_183 ; } else { if ( rtb_B_28_37_0 < _rtP -> P_184 ) { rtb_B_28_37_0
= _rtP -> P_184 ; } } _rtB -> B_28_292_0 = ( ( rtb_B_28_37_0 - _rtDW ->
UnitDelay_DSTATE_p ) * _rtP -> P_186 + _rtP -> P_187 * _rtDW ->
UnitDelay_DSTATE_p ) * _rtP -> P_188 ; if ( _rtB -> B_28_135_0 > _rtP ->
P_189 ) { _rtB -> B_28_293_0 = _rtB -> B_28_292_0 ; } else { _rtB ->
B_28_293_0 = _rtB -> B_28_56_0_d ; } rtb_B_28_131_0 = _rtP -> P_190 * _rtB ->
B_28_107_0 [ 46 ] ; rtb_B_28_185_0 = _rtP -> P_195 * _rtB -> B_28_107_0 [ 23
] ; rtb_B_28_123_0 = ( real_T ) ( _rtB -> B_28_293_0 > _rtB -> B_28_10_0_c )
* ( _rtB -> B_28_57_0 - rtb_B_28_185_0 ) ; _rtB -> B_28_307_0 = _rtP -> P_197
* rtb_B_28_123_0 ; rtb_B_28_37_0 = _rtP -> P_196 * rtb_B_28_123_0 + _rtDW ->
DiscreteTimeIntegrator_DSTATE_c ; if ( rtb_B_28_37_0 > _rtP -> P_198 ) {
rtb_B_28_37_0 = _rtP -> P_198 ; } else { if ( rtb_B_28_37_0 < _rtP -> P_199 )
{ rtb_B_28_37_0 = _rtP -> P_199 ; } } rtb_B_28_224_0 += rtb_B_28_37_0 ; if (
rtb_B_28_224_0 > _rtB -> B_28_293_0 ) { rtb_B_28_224_0 = _rtB -> B_28_293_0 ;
} else { if ( rtb_B_28_224_0 < _rtB -> B_28_11_0 ) { rtb_B_28_224_0 = _rtB ->
B_28_11_0 ; } } rtb_B_28_123_0 = rtb_B_28_224_0 - rtb_B_28_131_0 ; _rtB ->
B_28_317_0 = _rtP -> P_205 * rtb_B_28_123_0 ; rtb_B_28_224_0 = _rtP -> P_208
* _rtB -> B_28_107_0 [ 24 ] ; rtb_B_28_37_0 = _rtP -> P_204 * rtb_B_28_123_0
+ _rtDW -> DiscreteTimeIntegrator_DSTATE_fi ; if ( rtb_B_28_37_0 > _rtP ->
P_206 ) { rtb_B_28_37_0 = _rtP -> P_206 ; } else { if ( rtb_B_28_37_0 < _rtP
-> P_207 ) { rtb_B_28_37_0 = _rtP -> P_207 ; } } if ( rtb_B_28_224_0 > _rtP
-> P_209 ) { rtb_B_28_94_0 = _rtP -> P_209 ; } else if ( rtb_B_28_224_0 <
_rtP -> P_210 ) { rtb_B_28_94_0 = _rtP -> P_210 ; } else { rtb_B_28_94_0 =
rtb_B_28_224_0 ; } rtb_B_28_185_0 = ( rtb_B_28_37_0 + rtb_B_28_185_0 ) /
rtb_B_28_94_0 ; if ( rtb_B_28_185_0 > _rtP -> P_211 ) { rtb_B_28_185_0 = _rtP
-> P_211 ; } else { if ( rtb_B_28_185_0 < _rtP -> P_212 ) { rtb_B_28_185_0 =
_rtP -> P_212 ; } } _rtB -> B_28_325_0 = rtb_B_28_185_0 * rtb_B_28_224_0 ; if
( B_28_283_0 > _rtP -> P_213 ) { tmp = _rtP -> P_213 ; } else if ( B_28_283_0
< _rtP -> P_214 ) { tmp = _rtP -> P_214 ; } else { tmp = B_28_283_0 ; } _rtB
-> B_28_327_0 = rtb_B_28_185_0 * rtb_B_28_131_0 / tmp ; rtb_B_28_185_0 = _rtP
-> P_215 * _rtB -> B_28_107_0 [ 25 ] ; rtb_B_28_224_0 = _rtP -> P_216 * _rtB
-> B_28_107_0 [ 26 ] ; _rtB -> B_28_356_0 = ( rtb_B_28_185_0 >= _rtP -> P_217
* rtb_B_28_224_0 ) ; _rtB -> B_28_358_0 = ( _rtP -> P_218 * _rtB ->
B_28_107_0 [ 50 ] <= _rtB -> B_28_16_0 ) ; } _rtB -> B_28_359_0 = ssGetT ( S
) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> RelationalOperator_Mode_h = ( _rtB
-> B_28_359_0 >= _rtB -> B_28_14_0 ) ; } rtb_B_28_360_0 = _rtDW ->
RelationalOperator_Mode_h ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if (
isHit != 0 ) { rtb_B_28_362_0 = _rtP -> P_220 * _rtB -> B_28_107_0 [ 48 ] ;
rtb_B_28_364_0 = rtb_B_28_185_0 * _rtB -> B_28_15_0_g / ( ( ( -
0.001234567901234569 * rtb_B_28_362_0 + 0.90555555555555556 ) * ( real_T ) (
rtb_B_28_362_0 >= 22.5 ) + ( real_T ) ( rtb_B_28_362_0 < 22.5 ) * 0.9 ) * (
_rtP -> P_219 * _rtB -> B_28_107_0 [ 27 ] ) + 0.1 ) ; _rtB -> B_28_366_0 =
_rtP -> P_221 * _rtB -> B_28_107_0 [ 38 ] * _rtB -> B_28_126_0 ; isHit =
ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_28_367_0 = _rtB
-> B_28_366_0 ; } } isHit = ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) {
_rtB -> B_28_373_0 = ( ( _rtB -> B_28_367_0 - _rtDW -> UnitDelay_DSTATE_aa )
* _rtP -> P_223 + _rtP -> P_224 * _rtDW -> UnitDelay_DSTATE_aa ) * _rtP ->
P_225 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
rtb_B_28_37_0 = ( 1.0 - rtb_B_28_16_0 / ( _rtP -> P_226 * rtb_B_28_4_0 ) ) *
100.0 ; if ( rtb_B_28_37_0 > _rtP -> P_227 ) { _rtB -> B_28_376_0 = _rtP ->
P_227 ; } else if ( rtb_B_28_37_0 < _rtP -> P_228 ) { _rtB -> B_28_376_0 =
_rtP -> P_228 ; } else { _rtB -> B_28_376_0 = rtb_B_28_37_0 ; } isHit =
ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_28_377_0 = _rtB
-> B_28_376_0 ; } } isHit = ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) {
_rtB -> B_28_379_0 [ 0 ] = _rtB -> B_28_373_0 ; _rtB -> B_28_379_0 [ 1 ] =
_rtB -> B_28_377_0 ; _rtB -> B_28_379_0 [ 2 ] = _rtDW -> UnitDelay2_DSTATE_g
; ssCallAccelRunBlock ( S , 28 , 380 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_28_381_0 = _rtP -> P_230 * _rtB -> B_28_380_0 [ 0 ] ; } isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { rtb_B_28_385_0 = _rtB ->
B_28_71_0_l - _rtB -> B_28_126_0 ; rtb_B_28_391_0 = _rtB -> B_28_72_0 - _rtB
-> B_28_126_0 ; rtb_B_28_37_0 = _rtP -> P_231 * _rtB -> B_28_107_0 [ 30 ] ;
rtb_B_28_4_0 = _rtP -> P_234 * rtb_B_28_385_0 + _rtDW ->
DiscreteTimeIntegrator_DSTATE_l ; rtb_B_28_131_0 = _rtP -> P_241 *
rtb_B_28_391_0 + _rtDW -> DiscreteTimeIntegrator_DSTATE_n ; if (
rtb_B_28_37_0 > _rtP -> P_232 ) { rtb_B_28_37_0 = _rtP -> P_232 ; } else { if
( rtb_B_28_37_0 < _rtP -> P_233 ) { rtb_B_28_37_0 = _rtP -> P_233 ; } } if (
rtb_B_28_4_0 > _rtP -> P_239 ) { rtb_B_28_4_0 = _rtP -> P_239 ; } else { if (
rtb_B_28_4_0 < _rtP -> P_240 ) { rtb_B_28_4_0 = _rtP -> P_240 ; } } if (
rtb_B_28_131_0 > _rtP -> P_246 ) { rtb_B_28_131_0 = _rtP -> P_246 ; } else {
if ( rtb_B_28_131_0 < _rtP -> P_247 ) { rtb_B_28_131_0 = _rtP -> P_247 ; } }
rtb_B_28_37_0 = ( _rtB -> B_28_381_0 / rtb_B_28_37_0 + rtb_B_28_4_0 ) +
rtb_B_28_131_0 ; if ( rtb_B_28_37_0 > _rtP -> P_248 ) { _rtB -> B_28_397_0 =
_rtP -> P_248 ; } else if ( rtb_B_28_37_0 < _rtP -> P_249 ) { _rtB ->
B_28_397_0 = _rtP -> P_249 ; } else { _rtB -> B_28_397_0 = rtb_B_28_37_0 ; }
isHit = ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_28_398_0
= _rtB -> B_28_397_0 ; } } isHit = ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit
!= 0 ) { if ( _rtB -> B_28_398_0 <= _rtB -> B_28_60_0 ) { _rtB -> B_28_400_0
= _rtB -> B_28_398_0 ; } else { _rtB -> B_28_400_0 = _rtB -> B_28_60_0 ; } }
isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { if ( _rtB ->
B_28_135_0 > _rtP -> P_250 ) { rtb_B_28_4_0 = _rtB -> B_28_400_0 ; } else {
rtb_B_28_4_0 = _rtB -> B_28_62_0_o ; } rtb_B_28_131_0 = ( _rtB -> B_28_48_0 +
_rtB -> B_28_78_0_d ) - _rtB -> B_28_61_0_l ; _rtB -> B_28_410_0 = ( ( ( (
real_T ) ( rtb_B_28_4_0 < rtb_B_28_131_0 ) * rtb_B_28_4_0 + ( real_T ) (
rtb_B_28_4_0 >= rtb_B_28_131_0 ) * rtb_B_28_131_0 ) - _rtDW ->
UnitDelay_DSTATE_l ) * _rtP -> P_252 + _rtP -> P_253 * _rtDW ->
UnitDelay_DSTATE_l ) * _rtP -> P_254 ; _rtB -> B_28_411_0 = ( real_T ) (
rtb_B_28_362_0 > 50.0 ) * rtb_B_28_364_0 + ( real_T ) ( rtb_B_28_362_0 <=
50.0 ) * _rtB -> B_28_410_0 ; _rtB -> B_28_412_0 = ( _rtB -> B_28_411_0 >=
_rtB -> B_28_17_0 ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0
) { rtb_B_28_414_0 = ( _rtB -> B_28_356_0 || ( _rtB -> B_28_358_0 &&
rtb_B_28_360_0 && _rtB -> B_28_412_0 ) ) ; _rtB -> B_28_415_0 =
rtb_B_28_414_0 ; _rtB -> B_28_419_0 = rtb_B_28_414_0 ; } isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_28_423_0 = _rtP
-> P_255 * _rtB -> B_28_107_0 [ 47 ] ; if ( _rtB -> B_28_135_0 > _rtP ->
P_260 ) { tmp = _rtB -> B_28_64_0_b ; } else { tmp = _rtB -> B_28_63_0 ; }
rtb_B_28_364_0 = tmp - rtb_B_28_185_0 ; _rtB -> B_28_434_0 = _rtP -> P_262 *
rtb_B_28_364_0 ; rtb_B_28_436_0 = _rtP -> P_261 * rtb_B_28_364_0 + _rtDW ->
DiscreteTimeIntegrator_DSTATE_g ; if ( rtb_B_28_436_0 > _rtP -> P_263 ) {
rtb_B_28_436_0 = _rtP -> P_263 ; } else { if ( rtb_B_28_436_0 < _rtP -> P_264
) { rtb_B_28_436_0 = _rtP -> P_264 ; } } rtb_B_28_437_0 = _rtDW ->
DiscreteTimeIntegrator_DSTATE_b ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if
( isHit != 0 ) { rtb_B_28_438_0 = _rtB -> B_28_411_0 * ( real_T )
rtb_B_28_414_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) {
rtb_B_28_37_0 = ( ( - 0.001234567901234569 * rtb_B_28_362_0 +
0.90555555555555556 ) * ( real_T ) ( rtb_B_28_362_0 >= 22.5 ) + ( real_T ) (
rtb_B_28_362_0 < 22.5 ) * 0.9 ) * rtb_B_28_224_0 ; if ( rtb_B_28_37_0 > _rtP
-> P_269 ) { rtb_B_28_37_0 = _rtP -> P_269 ; } else { if ( rtb_B_28_37_0 <
_rtP -> P_270 ) { rtb_B_28_37_0 = _rtP -> P_270 ; } } _rtB -> B_28_444_0 = (
rtb_B_28_436_0 + rtb_B_28_362_0 ) * ( rtb_B_28_185_0 / rtb_B_28_37_0 ) ; }
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { rtb_B_28_445_0 = (
_rtB -> B_28_444_0 > rtb_B_28_438_0 ) ; } isHit = ssIsSampleHit ( S , 2 , 0 )
; if ( isHit != 0 ) { if ( _rtB -> B_28_444_0 < _rtB -> B_28_13_0 ) { _rtB ->
B_28_447_0 = _rtB -> B_28_13_0 ; } else { _rtB -> B_28_447_0 = _rtB ->
B_28_444_0 ; } } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if
( ! rtb_B_28_445_0 ) { rtb_B_28_438_0 = _rtB -> B_28_447_0 ; } _rtB ->
B_28_449_0 = rtb_B_28_438_0 - _rtB -> B_28_423_0 ; } isHit = ssIsSampleHit (
S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_28_451_0 = _rtP -> P_272 * _rtB
-> B_28_449_0 ; rtb_B_28_37_0 = _rtP -> P_271 * _rtB -> B_28_449_0 +
rtb_B_28_437_0 ; if ( rtb_B_28_37_0 > _rtP -> P_273 ) { rtb_B_28_37_0 = _rtP
-> P_273 ; } else { if ( rtb_B_28_37_0 < _rtP -> P_274 ) { rtb_B_28_37_0 =
_rtP -> P_274 ; } } if ( rtb_B_28_185_0 > _rtP -> P_275 ) { rtb_B_28_364_0 =
_rtP -> P_275 ; } else if ( rtb_B_28_185_0 < _rtP -> P_276 ) { rtb_B_28_364_0
= _rtP -> P_276 ; } else { rtb_B_28_364_0 = rtb_B_28_185_0 ; } rtb_B_28_438_0
= _rtB -> B_28_12_0_f - ( rtb_B_28_224_0 - rtb_B_28_37_0 ) / rtb_B_28_364_0 ;
if ( rtb_B_28_438_0 > _rtP -> P_277 ) { rtb_B_28_438_0 = _rtP -> P_277 ; }
else { if ( rtb_B_28_438_0 < _rtP -> P_278 ) { rtb_B_28_438_0 = _rtP -> P_278
; } } _rtB -> B_28_459_0 = ( 1.0 - rtb_B_28_438_0 ) * rtb_B_28_185_0 ; _rtB
-> B_28_461_0 = ( ( - 0.001234567901234569 * rtb_B_28_362_0 +
0.90555555555555556 ) * ( real_T ) ( rtb_B_28_362_0 >= 22.5 ) + ( real_T ) (
rtb_B_28_362_0 < 22.5 ) * 0.9 ) * ( 1.0 - rtb_B_28_438_0 ) * _rtB ->
B_28_423_0 ; rtb_B_28_362_0 = _rtP -> P_279 * _rtB -> B_28_107_0 [ 49 ] ;
rtb_B_28_438_0 = _rtP -> P_280 * _rtB -> B_28_107_0 [ 51 ] ; rtb_B_28_436_0 =
_rtP -> P_285 * _rtB -> B_28_107_0 [ 28 ] ; rtb_B_28_437_0 = _rtB ->
B_28_18_0 - rtb_B_28_436_0 ; _rtB -> B_28_505_0 = _rtP -> P_287 *
rtb_B_28_437_0 ; rtb_B_28_364_0 = _rtP -> P_294 * _rtB -> B_28_107_0 [ 29 ] ;
rtb_B_28_4_0 = ( ( - 0.0014029180695847375 * rtb_B_28_362_0 +
0.90555555555555556 ) * ( real_T ) ( rtb_B_28_362_0 >= 19.8 ) + ( real_T ) (
rtb_B_28_362_0 < 19.8 ) * 0.9 ) * _rtB -> B_28_410_0 * rtb_B_28_364_0 / (
rtb_B_28_436_0 + 0.1 ) ; if ( rtb_B_28_4_0 > _rtB -> B_28_20_0 ) {
rtb_B_28_4_0 = _rtB -> B_28_20_0 ; } else { if ( rtb_B_28_4_0 < _rtB ->
B_28_19_0 ) { rtb_B_28_4_0 = _rtB -> B_28_19_0 ; } } rtb_B_28_37_0 = _rtP ->
P_286 * rtb_B_28_437_0 + _rtDW -> DiscreteTimeIntegrator_DSTATE_hn ; if (
rtb_B_28_37_0 > _rtP -> P_288 ) { rtb_B_28_37_0 = _rtP -> P_288 ; } else { if
( rtb_B_28_37_0 < _rtP -> P_289 ) { rtb_B_28_37_0 = _rtP -> P_289 ; } }
rtb_B_28_437_0 = rtb_B_28_37_0 + rtb_B_28_362_0 ; if ( ! ( rtb_B_28_437_0 >
rtb_B_28_4_0 ) ) { if ( rtb_B_28_437_0 < _rtB -> B_28_21_0 ) { rtb_B_28_4_0 =
_rtB -> B_28_21_0 ; } else { rtb_B_28_4_0 = rtb_B_28_437_0 ; } }
rtb_B_28_437_0 = rtb_B_28_4_0 - rtb_B_28_438_0 ; _rtB -> B_28_521_0 = _rtP ->
P_296 * rtb_B_28_437_0 ; rtb_B_28_37_0 = _rtP -> P_295 * rtb_B_28_437_0 +
_rtDW -> DiscreteTimeIntegrator_DSTATE_hc ; if ( rtb_B_28_37_0 > _rtP ->
P_297 ) { rtb_B_28_37_0 = _rtP -> P_297 ; } else { if ( rtb_B_28_37_0 < _rtP
-> P_298 ) { rtb_B_28_37_0 = _rtP -> P_298 ; } } if ( rtb_B_28_364_0 > _rtP
-> P_299 ) { rtb_B_28_437_0 = _rtP -> P_299 ; } else if ( rtb_B_28_364_0 <
_rtP -> P_300 ) { rtb_B_28_437_0 = _rtP -> P_300 ; } else { rtb_B_28_437_0 =
rtb_B_28_364_0 ; } rtb_B_28_436_0 = ( rtb_B_28_37_0 + rtb_B_28_436_0 ) /
rtb_B_28_437_0 ; if ( rtb_B_28_436_0 > _rtP -> P_301 ) { rtb_B_28_436_0 =
_rtP -> P_301 ; } else { if ( rtb_B_28_436_0 < _rtP -> P_302 ) {
rtb_B_28_436_0 = _rtP -> P_302 ; } } _rtB -> B_28_528_0 = rtb_B_28_436_0 *
rtb_B_28_364_0 ; _rtB -> B_28_530_0 = rtb_B_28_436_0 * rtb_B_28_438_0 / ( ( -
0.0014029180695847375 * rtb_B_28_362_0 + 0.90555555555555556 ) * ( real_T ) (
rtb_B_28_362_0 >= 19.8 ) + ( real_T ) ( rtb_B_28_362_0 < 19.8 ) * 0.9 ) ;
_rtB -> B_28_555_0 = _rtP -> P_303 * _rtB -> B_28_107_0 [ 39 ] * _rtB ->
B_28_126_0 ; _rtB -> B_28_556_0 = _rtP -> P_304 * _rtB -> B_28_107_0 [ 37 ] ;
_rtB -> B_28_557_0 = _rtB -> B_28_126_0 * _rtB -> B_28_556_0 ; _rtB ->
B_28_558_0 = _rtP -> P_305 * _rtB -> B_28_107_0 [ 56 ] ; _rtB -> B_28_559_0 =
_rtB -> B_28_126_0 * _rtB -> B_28_558_0 ; } _rtB -> B_28_561_0 =
look1_binlxpw ( ssGetT ( S ) , _rtP -> P_307 , _rtP -> P_306 , 30U ) ; _rtB
-> B_28_562_0 = _rtP -> P_308 * _rtB -> B_28_561_0 ; isHit = ssIsSampleHit (
S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_28_563_0 = ( _rtB -> B_28_555_0 +
_rtB -> B_28_557_0 ) + _rtB -> B_28_559_0 ; } ssCallAccelRunBlock ( S , 28 ,
564 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_28_567_0 = ( _rtB -> B_28_54_0_g -
_rtB -> B_28_562_0 / _rtB -> B_28_366_0 ) * _rtP -> P_309 ; if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Abs_MODE = ( _rtB -> B_28_567_0 >=
0.0 ) ; } _rtB -> B_28_568_0 = _rtDW -> Abs_MODE > 0 ? _rtB -> B_28_567_0 : -
_rtB -> B_28_567_0 ; _rtB -> B_28_571_0 = ( _rtB -> B_28_55_0_l - _rtB ->
B_28_562_0 / _rtB -> B_28_563_0 ) * _rtP -> P_310 ; if ( ssIsMajorTimeStep (
S ) != 0 ) { _rtDW -> Abs1_MODE = ( _rtB -> B_28_571_0 >= 0.0 ) ; } _rtB ->
B_28_572_0 = _rtDW -> Abs1_MODE > 0 ? _rtB -> B_28_571_0 : - _rtB ->
B_28_571_0 ; ssCallAccelRunBlock ( S , 28 , 573 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 28 , 574 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Saturation2_MODE_b = _rtB ->
B_28_561_0 >= _rtP -> P_311 ? 1 : _rtB -> B_28_561_0 > _rtP -> P_312 ? 0 : -
1 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
rtb_B_28_582_0 = ( _rtB -> B_28_376_0 <= _rtB -> B_28_65_0 ) ; } isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_28_583_0 = _rtDW
-> UnitDelay4_DSTATE ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit !=
0 ) { if ( rtb_B_28_582_0 ) { _rtB -> B_28_584_0 = _rtB -> B_28_66_0_n ; }
else { _rtB -> B_28_584_0 = _rtB -> B_28_583_0 ; } rtb_B_28_37_0 = ( ( _rtB
-> B_28_584_0 != 0.0 ) && ( _rtB -> B_28_135_0 != 0.0 ) ) ; if (
rtb_B_28_37_0 > _rtP -> P_314 ) { _rtB -> B_28_587_0 = _rtP -> P_314 ; } else
if ( rtb_B_28_37_0 < _rtP -> P_315 ) { _rtB -> B_28_587_0 = _rtP -> P_315 ; }
else { _rtB -> B_28_587_0 = rtb_B_28_37_0 ; } } rtb_B_28_438_0 = ( _rtDW ->
Saturation2_MODE_b == 1 ? _rtP -> P_311 : _rtDW -> Saturation2_MODE_b == - 1
? _rtP -> P_312 : _rtB -> B_28_561_0 ) * _rtB -> B_28_587_0 * _rtP -> P_316 ;
rtb_B_28_362_0 = rtb_B_28_438_0 * _rtB -> B_28_33_0 ; rtb_B_28_37_0 =
muDoubleScalarPower ( rtb_B_28_438_0 , 2.0 ) - muDoubleScalarPower (
rtb_B_28_362_0 , 2.0 ) ; rtb_B_28_364_0 = _rtP -> P_317 * rtb_B_28_362_0 ; if
( rtb_B_28_37_0 < 0.0 ) { rtb_B_28_37_0 = - muDoubleScalarSqrt ( -
rtb_B_28_37_0 ) ; } else { rtb_B_28_37_0 = muDoubleScalarSqrt ( rtb_B_28_37_0
) ; } rtb_B_28_436_0 = _rtP -> P_318 * rtb_B_28_37_0 ; if ( rtb_B_28_436_0 ==
0.0 ) { rtb_B_28_362_0 = 1.0 / rtb_B_28_364_0 ; rtb_B_28_185_0 = 0.0 ; } else
if ( rtb_B_28_364_0 == 0.0 ) { rtb_B_28_362_0 = 0.0 ; rtb_B_28_185_0 = - (
1.0 / rtb_B_28_436_0 ) ; } else { rtb_B_28_437_0 = muDoubleScalarAbs (
rtb_B_28_364_0 ) ; rtb_B_28_362_0 = muDoubleScalarAbs ( rtb_B_28_436_0 ) ; if
( rtb_B_28_437_0 > rtb_B_28_362_0 ) { rtb_B_28_437_0 = rtb_B_28_436_0 /
rtb_B_28_364_0 ; rtb_B_28_185_0 = rtb_B_28_437_0 * rtb_B_28_436_0 +
rtb_B_28_364_0 ; rtb_B_28_362_0 = 1.0 / rtb_B_28_185_0 ; rtb_B_28_185_0 = - (
rtb_B_28_437_0 / rtb_B_28_185_0 ) ; } else if ( rtb_B_28_362_0 ==
rtb_B_28_437_0 ) { rtb_B_28_362_0 = ( rtb_B_28_364_0 > 0.0 ? 0.5 : - 0.5 ) /
rtb_B_28_437_0 ; rtb_B_28_185_0 = - ( rtb_B_28_436_0 > 0.0 ? 0.5 : - 0.5 ) /
rtb_B_28_437_0 ; } else { rtb_B_28_437_0 = rtb_B_28_364_0 / rtb_B_28_436_0 ;
rtb_B_28_185_0 = rtb_B_28_437_0 * rtb_B_28_364_0 + rtb_B_28_436_0 ;
rtb_B_28_362_0 = rtb_B_28_437_0 / rtb_B_28_185_0 ; rtb_B_28_185_0 = - ( 1.0 /
rtb_B_28_185_0 ) ; } } rtb_B_28_224_0 = rtb_B_28_362_0 * _rtB -> B_28_22_0 ;
rtb_B_28_185_0 *= _rtB -> B_28_22_0 ; isHit = ssIsSampleHit ( S , 2 , 0 ) ;
if ( isHit != 0 ) { _rtB -> B_28_600_0 [ 0 ] = _rtP -> P_319 * _rtB ->
B_28_3_0 [ 0 ] * _rtP -> P_322 ; _rtB -> B_28_600_0 [ 1 ] = _rtP -> P_320 *
_rtB -> B_28_3_0 [ 1 ] * _rtP -> P_322 ; _rtB -> B_28_600_0 [ 2 ] = _rtP ->
P_321 * _rtB -> B_28_3_0 [ 2 ] * _rtP -> P_322 ; for ( isHit = 0 ; isHit < 3
; isHit ++ ) { _rtB -> B_28_602_0 [ isHit ] = _rtP -> P_324 * ( _rtP -> P_323
[ isHit + 6 ] * _rtB -> B_28_600_0 [ 2 ] + ( _rtP -> P_323 [ isHit + 3 ] *
_rtB -> B_28_600_0 [ 1 ] + _rtP -> P_323 [ isHit ] * _rtB -> B_28_600_0 [ 0 ]
) ) ; } } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> RelationalOperator_Mode_g = ( _rtX
-> Integrator_CSTATE > _rtB -> B_28_25_0 ) ; } _rtB -> B_28_603_0 = _rtDW ->
RelationalOperator_Mode_g ; } _rtB -> B_28_604_0 = _rtX -> Integrator_CSTATE
- _rtB -> B_28_25_0 ; if ( ( _rtDW -> Initial_FirstOutputTime == ( rtMinusInf
) ) || ( _rtDW -> Initial_FirstOutputTime == ssGetTaskTime ( S , 0 ) ) ) {
_rtDW -> Initial_FirstOutputTime = ssGetTaskTime ( S , 0 ) ; _rtB ->
B_28_605_0 = _rtP -> P_325 ; } else { _rtB -> B_28_605_0 = _rtB -> B_28_604_0
; } if ( ssIsMajorTimeStep ( S ) != 0 ) { rtb_B_28_13_0 = ( _rtB ->
B_28_603_0 && ( _rtZCE -> Integrator_Reset_ZCE != 1 ) ) ; _rtZCE ->
Integrator_Reset_ZCE = _rtB -> B_28_603_0 ; if ( rtb_B_28_13_0 || ( _rtDW ->
Integrator_IWORK != 0 ) ) { _rtX -> Integrator_CSTATE = _rtB -> B_28_605_0 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } if ( _rtX ->
Integrator_CSTATE >= _rtP -> P_326 ) { if ( _rtX -> Integrator_CSTATE != _rtP
-> P_326 ) { _rtX -> Integrator_CSTATE = _rtP -> P_326 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE = 3 ; } else if ( _rtX -> Integrator_CSTATE <= _rtP -> P_327
) { if ( _rtX -> Integrator_CSTATE != _rtP -> P_327 ) { _rtX ->
Integrator_CSTATE = _rtP -> P_327 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE = 4 ; } else { if ( _rtDW -> Integrator_MODE != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW -> Integrator_MODE
= 0 ; } _rtB -> B_28_606_0 = _rtX -> Integrator_CSTATE ; } else { _rtB ->
B_28_606_0 = _rtX -> Integrator_CSTATE ; } power_FCHPS_MEA_Subsystem1 ( S ,
_rtB -> B_28_36_0 , & _rtB -> B_28_602_0 [ 0 ] , _rtB -> B_28_606_0 , & _rtB
-> Subsystem1_h , & _rtDW -> Subsystem1_h ) ;
power_FCHPS_MEA_Subsystempi2delay ( S , _rtB -> B_28_38_0 , & _rtB ->
B_28_602_0 [ 0 ] , _rtB -> B_28_606_0 , & _rtB -> Subsystempi2delay_b , &
_rtDW -> Subsystempi2delay_b ) ; if ( _rtB -> B_28_36_0 != 0 ) {
rtb_B_28_364_0 = _rtB -> Subsystem1_h . B_3_0_0 ; rtb_B_28_436_0 = _rtB ->
Subsystem1_h . B_3_1_0 ; } else { rtb_B_28_364_0 = _rtB ->
Subsystempi2delay_b . B_2_0_0 ; rtb_B_28_436_0 = _rtB -> Subsystempi2delay_b
. B_2_1_0 ; } if ( - rtb_B_28_185_0 == 0.0 ) { rtb_B_28_362_0 = 1.0 /
rtb_B_28_224_0 ; rtb_B_28_185_0 = 0.0 ; } else if ( rtb_B_28_224_0 == 0.0 ) {
rtb_B_28_362_0 = 0.0 ; rtb_B_28_185_0 = - ( 1.0 / - rtb_B_28_185_0 ) ; } else
{ rtb_B_28_437_0 = muDoubleScalarAbs ( rtb_B_28_224_0 ) ; rtb_B_28_362_0 =
muDoubleScalarAbs ( - rtb_B_28_185_0 ) ; if ( rtb_B_28_437_0 > rtb_B_28_362_0
) { rtb_B_28_437_0 = - rtb_B_28_185_0 / rtb_B_28_224_0 ; rtb_B_28_185_0 =
rtb_B_28_437_0 * - rtb_B_28_185_0 + rtb_B_28_224_0 ; rtb_B_28_362_0 = 1.0 /
rtb_B_28_185_0 ; rtb_B_28_185_0 = - ( rtb_B_28_437_0 / rtb_B_28_185_0 ) ; }
else if ( rtb_B_28_362_0 == rtb_B_28_437_0 ) { rtb_B_28_362_0 = (
rtb_B_28_224_0 > 0.0 ? 0.5 : - 0.5 ) / rtb_B_28_437_0 ; rtb_B_28_185_0 = - (
- rtb_B_28_185_0 > 0.0 ? 0.5 : - 0.5 ) / rtb_B_28_437_0 ; } else {
rtb_B_28_437_0 = rtb_B_28_224_0 / - rtb_B_28_185_0 ; rtb_B_28_185_0 =
rtb_B_28_437_0 * rtb_B_28_224_0 + - rtb_B_28_185_0 ; rtb_B_28_362_0 =
rtb_B_28_437_0 / rtb_B_28_185_0 ; rtb_B_28_185_0 = - ( 1.0 / rtb_B_28_185_0 )
; } } rtb_B_28_224_0 = rtb_B_28_362_0 * rtb_B_28_364_0 - rtb_B_28_185_0 *
rtb_B_28_436_0 ; rtb_B_28_185_0 = rtb_B_28_362_0 * rtb_B_28_436_0 +
rtb_B_28_185_0 * rtb_B_28_364_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { _rtB -> B_28_614_0 = _rtDW -> Memory_PreviousInput ; if (
ssIsMajorTimeStep ( S ) != 0 ) { if ( _rtB -> B_28_24_0 > 0.0 ) { if ( !
_rtDW -> AutomaticGainControl_MODE ) { if ( ssGetTaskTime ( S , 1 ) !=
ssGetTStart ( S ) ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } (
void ) memset ( & ( ( ( XDis_power_FCHPS_MEA_T * ) ssGetContStateDisabled ( S
) ) -> VariableTransportDelay_CSTATE_n ) , 0 , 4 * sizeof ( boolean_T ) ) ;
_rtDW -> AutomaticGainControl_MODE = true ; } } else { if ( ssGetTaskTime ( S
, 1 ) == ssGetTStart ( S ) ) { ( void ) memset ( & ( ( (
XDis_power_FCHPS_MEA_T * ) ssGetContStateDisabled ( S ) ) ->
VariableTransportDelay_CSTATE_n ) , 1 , 4 * sizeof ( boolean_T ) ) ; } if (
_rtDW -> AutomaticGainControl_MODE ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; ( void ) memset ( & ( ( (
XDis_power_FCHPS_MEA_T * ) ssGetContStateDisabled ( S ) ) ->
VariableTransportDelay_CSTATE_n ) , 1 , 4 * sizeof ( boolean_T ) ) ; if (
_rtDW -> Subsystempi2delay_d . Subsystempi2delay_MODE ) {
power_FCHPS_MEA_Subsystempi2delay_Disable ( S , & _rtDW ->
Subsystempi2delay_d ) ; } if ( _rtDW -> Subsystem1_i . Subsystem1_MODE ) {
power_FCHPS_MEA_Subsystem1_Disable ( S , & _rtDW -> Subsystem1_i ) ; } _rtDW
-> AutomaticGainControl_MODE = false ; } } } } if ( _rtDW ->
AutomaticGainControl_MODE ) { { real_T * * uBuffer = ( real_T * * ) & _rtDW
-> VariableTransportDelay_PWORK_b . TUbufferPtrs [ 0 ] ; real_T * * tBuffer =
( real_T * * ) & _rtDW -> VariableTransportDelay_PWORK_b . TUbufferPtrs [ 1 ]
; real_T * * xBuffer = ( real_T * * ) & _rtDW ->
VariableTransportDelay_PWORK_b . TUbufferPtrs [ 2 ] ; real_T simTime = ssGetT
( S ) ; real_T appliedDelay ; _rtB -> B_4_0_0 =
power_FCHPS_MEA_acc_rt_VTDelayfindtDInterpolate ( ( ( X_power_FCHPS_MEA_T * )
ssGetContStates ( S ) ) -> VariableTransportDelay_CSTATE_n , * tBuffer , *
uBuffer , * xBuffer , _rtDW -> VariableTransportDelay_IWORK_n .
CircularBufSize , _rtDW -> VariableTransportDelay_IWORK_n . Head , _rtDW ->
VariableTransportDelay_IWORK_n . Tail , & _rtDW ->
VariableTransportDelay_IWORK_n . Last , simTime , 0.0 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
, _rtP -> P_2 , & appliedDelay ) ; } _rtB -> B_4_1_0 = _rtX ->
integrator_CSTATE_o ; _rtB -> B_4_2_0 = ssGetT ( S ) ; isHit = ssIsSampleHit
( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) {
_rtDW -> RelationalOperator_Mode_e = ( _rtB -> B_4_2_0 >= _rtB -> B_4_0_0_m )
; } _rtB -> B_4_3_0 = _rtDW -> RelationalOperator_Mode_e ; _rtB -> B_4_4_0 =
_rtDW -> Memory_PreviousInput_i ; } if ( _rtB -> B_4_3_0 ) { _rtB -> B_0_0_0
= _rtB -> B_4_1_0 - _rtB -> B_4_0_0 ; _rtB -> B_0_1_0 = _rtB -> B_0_0_0 *
_rtB -> B_28_614_0 ; _rtB -> B_4_6_0 = _rtB -> B_0_1_0 ; } else { _rtB ->
B_4_6_0 = _rtB -> B_4_4_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW
-> VariableTransportDelay_PWORK_c . TUbufferPtrs [ 0 ] ; real_T * * tBuffer =
( real_T * * ) & _rtDW -> VariableTransportDelay_PWORK_c . TUbufferPtrs [ 1 ]
; real_T * * xBuffer = ( real_T * * ) & _rtDW ->
VariableTransportDelay_PWORK_c . TUbufferPtrs [ 2 ] ; real_T simTime = ssGetT
( S ) ; real_T appliedDelay ; _rtB -> B_4_7_0 =
power_FCHPS_MEA_acc_rt_VTDelayfindtDInterpolate ( ( ( X_power_FCHPS_MEA_T * )
ssGetContStates ( S ) ) -> VariableTransportDelay_CSTATE_b , * tBuffer , *
uBuffer , * xBuffer , _rtDW -> VariableTransportDelay_IWORK_f .
CircularBufSize , _rtDW -> VariableTransportDelay_IWORK_f . Head , _rtDW ->
VariableTransportDelay_IWORK_f . Tail , & _rtDW ->
VariableTransportDelay_IWORK_f . Last , simTime , 0.0 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
, _rtP -> P_6 , & appliedDelay ) ; } _rtB -> B_4_8_0 = _rtX ->
integrator_CSTATE_i ; _rtB -> B_4_9_0 = ssGetT ( S ) ; isHit = ssIsSampleHit
( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) {
_rtDW -> RelationalOperator_Mode_c = ( _rtB -> B_4_9_0 >= _rtB -> B_4_1_0_c )
; } _rtB -> B_4_10_0 = _rtDW -> RelationalOperator_Mode_c ; _rtB -> B_4_11_0
= _rtDW -> Memory_PreviousInput_l ; } if ( _rtB -> B_4_10_0 ) { _rtB ->
B_1_0_0 = _rtB -> B_4_8_0 - _rtB -> B_4_7_0 ; _rtB -> B_1_1_0 = _rtB ->
B_1_0_0 * _rtB -> B_28_614_0 ; _rtB -> B_4_13_0 = _rtB -> B_1_1_0 ; } else {
_rtB -> B_4_13_0 = _rtB -> B_4_11_0 ; } _rtB -> B_4_14_0 . re = _rtB ->
B_4_6_0 ; _rtB -> B_4_14_0 . im = _rtB -> B_4_13_0 ; _rtB -> B_4_15_0 =
muDoubleScalarHypot ( _rtB -> B_4_14_0 . re , _rtB -> B_4_14_0 . im ) ; if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Saturation_MODE_d = _rtB ->
B_4_15_0 >= _rtP -> P_9 ? 1 : _rtB -> B_4_15_0 > _rtP -> P_10 ? 0 : - 1 ; }
_rtB -> B_4_16_0 = _rtDW -> Saturation_MODE_d == 1 ? _rtP -> P_9 : _rtDW ->
Saturation_MODE_d == - 1 ? _rtP -> P_10 : _rtB -> B_4_15_0 ; _rtB -> B_4_17_0
= 1.0 / _rtB -> B_4_16_0 ; if ( _rtB -> B_28_614_0 > _rtP -> P_11 ) { _rtB ->
B_4_18_0 = _rtP -> P_11 ; } else if ( _rtB -> B_28_614_0 < _rtP -> P_12 ) {
_rtB -> B_4_18_0 = _rtP -> P_12 ; } else { _rtB -> B_4_18_0 = _rtB ->
B_28_614_0 ; } _rtB -> B_4_19_0 = 1.0 / _rtB -> B_4_18_0 ; if ( _rtB ->
B_28_614_0 > _rtP -> P_13 ) { _rtB -> B_4_20_0 = _rtP -> P_13 ; } else if (
_rtB -> B_28_614_0 < _rtP -> P_14 ) { _rtB -> B_4_20_0 = _rtP -> P_14 ; }
else { _rtB -> B_4_20_0 = _rtB -> B_28_614_0 ; } _rtB -> B_4_21_0 = 1.0 /
_rtB -> B_4_20_0 ; for ( isHit = 0 ; isHit < 3 ; isHit ++ ) { _rtB ->
B_4_22_0 [ isHit ] = 0.0 ; _rtB -> B_4_22_0 [ isHit ] += _rtP -> P_15 [ isHit
] * _rtB -> B_28_600_0 [ 0 ] ; _rtB -> B_4_22_0 [ isHit ] += _rtP -> P_15 [
isHit + 3 ] * _rtB -> B_28_600_0 [ 1 ] ; _rtB -> B_4_22_0 [ isHit ] += _rtP
-> P_15 [ isHit + 6 ] * _rtB -> B_28_600_0 [ 2 ] ; _rtB -> B_4_23_0 [ isHit ]
= _rtP -> P_16 * _rtB -> B_4_22_0 [ isHit ] ; }
power_FCHPS_MEA_Subsystempi2delay ( S , _rtB -> B_4_6_0_c , & _rtB ->
B_4_23_0 [ 0 ] , _rtB -> B_28_606_0 , & _rtB -> Subsystempi2delay_d , & _rtDW
-> Subsystempi2delay_d ) ; power_FCHPS_MEA_Subsystem1 ( S , _rtB -> B_4_4_0_h
, & _rtB -> B_4_23_0 [ 0 ] , _rtB -> B_28_606_0 , & _rtB -> Subsystem1_i , &
_rtDW -> Subsystem1_i ) ; if ( _rtB -> B_4_4_0_h != 0 ) { _rtB -> B_4_26_0 [
0 ] = _rtB -> Subsystem1_i . B_3_0_0 ; _rtB -> B_4_26_0 [ 1 ] = _rtB ->
Subsystem1_i . B_3_1_0 ; } else { _rtB -> B_4_26_0 [ 0 ] = _rtB ->
Subsystempi2delay_d . B_2_0_0 ; _rtB -> B_4_26_0 [ 1 ] = _rtB ->
Subsystempi2delay_d . B_2_1_0 ; } if ( ssIsMajorTimeStep ( S ) != 0 ) {
srUpdateBC ( _rtDW -> AutomaticGainControl_SubsysRanBC ) ; } } if (
ssIsMajorTimeStep ( S ) != 0 ) { if ( _rtX -> Integrator_CSTATE_g >= _rtP ->
P_331 ) { if ( _rtX -> Integrator_CSTATE_g != _rtP -> P_331 ) { _rtX ->
Integrator_CSTATE_g = _rtP -> P_331 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_g = 3 ; } else if ( _rtX -> Integrator_CSTATE_g <= _rtP ->
P_332 ) { if ( _rtX -> Integrator_CSTATE_g != _rtP -> P_332 ) { _rtX ->
Integrator_CSTATE_g = _rtP -> P_332 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_g = 4 ; } else { if ( _rtDW -> Integrator_MODE_g != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_g = 0 ; } _rtB -> B_28_616_0 = _rtX -> Integrator_CSTATE_g ;
} else { _rtB -> B_28_616_0 = _rtX -> Integrator_CSTATE_g ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> VariableTransportDelay_PWORK .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
VariableTransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T * * xBuffer = (
real_T * * ) & _rtDW -> VariableTransportDelay_PWORK . TUbufferPtrs [ 2 ] ;
real_T simTime = ssGetT ( S ) ; real_T appliedDelay ; _rtB -> B_28_617_0 =
power_FCHPS_MEA_acc_rt_VTDelayfindtDInterpolate ( ( ( X_power_FCHPS_MEA_T * )
ssGetContStates ( S ) ) -> VariableTransportDelay_CSTATE , * tBuffer , *
uBuffer , * xBuffer , _rtDW -> VariableTransportDelay_IWORK . CircularBufSize
, _rtDW -> VariableTransportDelay_IWORK . Head , _rtDW ->
VariableTransportDelay_IWORK . Tail , & _rtDW -> VariableTransportDelay_IWORK
. Last , simTime , 0.0 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) , _rtP -> P_334 , &
appliedDelay ) ; } _rtB -> B_28_618_0 = _rtX -> integrator_CSTATE ; _rtB ->
B_28_619_0 = ssGetT ( S ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit
!= 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
RelationalOperator_Mode_i = ( _rtB -> B_28_619_0 >= _rtB -> B_28_26_0_g ) ; }
_rtB -> B_28_620_0 = _rtDW -> RelationalOperator_Mode_i ; _rtB -> B_28_621_0
= _rtDW -> Memory_PreviousInput_g ; } if ( _rtB -> B_28_620_0 ) { _rtB ->
B_5_0_0 = _rtB -> B_28_618_0 - _rtB -> B_28_617_0 ; _rtB -> B_5_1_0 = _rtB ->
B_5_0_0 * _rtB -> B_28_614_0 ; _rtB -> B_28_623_0 = _rtB -> B_5_1_0 ; } else
{ _rtB -> B_28_623_0 = _rtB -> B_28_621_0 ; } _rtB -> B_28_624_0 = _rtB ->
B_28_623_0 * _rtB -> B_4_17_0 ; _rtB -> B_28_625_0 = _rtP -> P_337 * _rtB ->
B_28_624_0 ; _rtB -> B_28_626_0 = _rtP -> P_338 * _rtB -> B_28_624_0 ; _rtB
-> B_28_627_0 = _rtP -> P_339 * _rtB -> B_28_624_0 ; _rtB -> B_28_628_0 = 0.0
; _rtB -> B_28_628_0 += _rtP -> P_341 * _rtX -> TransferFcn_CSTATE ; _rtB ->
B_28_628_0 += _rtP -> P_342 * _rtB -> B_28_627_0 ; _rtB -> B_28_629_0 = (
_rtB -> B_28_625_0 + _rtB -> B_28_616_0 ) + _rtB -> B_28_628_0 ; if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Saturation2_MODE_m = _rtB ->
B_28_629_0 >= _rtP -> P_343 ? 1 : _rtB -> B_28_629_0 > _rtP -> P_344 ? 0 : -
1 ; } _rtB -> B_28_630_0 = _rtDW -> Saturation2_MODE_m == 1 ? _rtP -> P_343 :
_rtDW -> Saturation2_MODE_m == - 1 ? _rtP -> P_344 : _rtB -> B_28_629_0 ;
_rtB -> B_28_631_0 = _rtP -> P_345 * _rtB -> B_28_630_0 ; if ( ( _rtDW ->
LastMajorTimeA >= ssGetTaskTime ( S , 0 ) ) && ( _rtDW -> LastMajorTimeB >=
ssGetTaskTime ( S , 0 ) ) ) { _rtB -> B_28_632_0 = _rtB -> B_28_631_0 ; }
else { if ( ( ( _rtDW -> LastMajorTimeA < _rtDW -> LastMajorTimeB ) && (
_rtDW -> LastMajorTimeB < ssGetTaskTime ( S , 0 ) ) ) || ( ( _rtDW ->
LastMajorTimeA >= _rtDW -> LastMajorTimeB ) && ( _rtDW -> LastMajorTimeA >=
ssGetTaskTime ( S , 0 ) ) ) ) { rtb_B_28_437_0 = ssGetTaskTime ( S , 0 ) -
_rtDW -> LastMajorTimeB ; rtb_B_28_364_0 = _rtDW -> PrevYB ; } else {
rtb_B_28_437_0 = ssGetTaskTime ( S , 0 ) - _rtDW -> LastMajorTimeA ;
rtb_B_28_364_0 = _rtDW -> PrevYA ; } rtb_B_28_4_0 = rtb_B_28_437_0 * _rtP ->
P_346 ; rtb_B_28_436_0 = _rtB -> B_28_631_0 - rtb_B_28_364_0 ; if (
rtb_B_28_436_0 > rtb_B_28_4_0 ) { _rtB -> B_28_632_0 = rtb_B_28_364_0 +
rtb_B_28_4_0 ; } else { rtb_B_28_437_0 *= _rtP -> P_347 ; if ( rtb_B_28_436_0
< rtb_B_28_437_0 ) { _rtB -> B_28_632_0 = rtb_B_28_364_0 + rtb_B_28_437_0 ; }
else { _rtB -> B_28_632_0 = _rtB -> B_28_631_0 ; } } } _rtB -> B_28_633_0 =
_rtX -> Integrator_x1_CSTATE ; _rtB -> B_28_634_0 = _rtP -> P_349 * _rtB ->
B_28_633_0 ; _rtB -> B_28_635_0 = _rtX -> Integrator_x2_CSTATE ; _rtB ->
B_28_636_0 = _rtP -> P_351 * _rtB -> B_28_635_0 ; _rtB -> B_28_637_0 = _rtP
-> P_352 * _rtB -> B_28_633_0 ; _rtB -> B_28_638_0 = _rtP -> P_353 * _rtB ->
B_28_635_0 ; _rtB -> B_28_639_0 = _rtB -> B_28_634_0 + _rtB -> B_28_636_0 ;
_rtB -> B_28_640_0 = _rtB -> B_28_637_0 + _rtB -> B_28_638_0 ; _rtB ->
B_28_641_0 = _rtP -> P_354 * _rtB -> B_28_632_0 ; _rtB -> B_28_642_0 = _rtB
-> B_28_639_0 + _rtB -> B_28_641_0 ; _rtB -> B_28_643_0 = _rtP -> P_355 *
_rtB -> B_28_632_0 ; _rtB -> B_28_644_0 = _rtB -> B_28_640_0 + _rtB ->
B_28_643_0 ; _rtB -> B_28_649_0 = ( _rtP -> P_356 * _rtB -> B_28_633_0 + _rtP
-> P_357 * _rtB -> B_28_635_0 ) + _rtP -> P_358 * _rtB -> B_28_632_0 ; if (
_rtB -> B_28_614_0 > _rtP -> P_359 ) { _rtB -> B_28_650_0 = _rtP -> P_359 ; }
else if ( _rtB -> B_28_614_0 < _rtP -> P_360 ) { _rtB -> B_28_650_0 = _rtP ->
P_360 ; } else { _rtB -> B_28_650_0 = _rtB -> B_28_614_0 ; } _rtB ->
B_28_651_0 = 1.0 / _rtB -> B_28_650_0 ; for ( isHit = 0 ; isHit < 3 ; isHit
++ ) { _rtB -> B_28_652_0 [ isHit ] = 0.0 ; _rtB -> B_28_652_0 [ isHit ] +=
_rtP -> P_361 [ isHit ] * _rtB -> B_28_600_0 [ 0 ] ; _rtB -> B_28_652_0 [
isHit ] += _rtP -> P_361 [ isHit + 3 ] * _rtB -> B_28_600_0 [ 1 ] ; _rtB ->
B_28_652_0 [ isHit ] += _rtP -> P_361 [ isHit + 6 ] * _rtB -> B_28_600_0 [ 2
] ; _rtB -> B_28_653_0 [ isHit ] = _rtP -> P_362 * _rtB -> B_28_652_0 [ isHit
] ; } power_FCHPS_MEA_Subsystempi2delay ( S , _rtB -> B_28_31_0 , & _rtB ->
B_28_653_0 [ 0 ] , _rtB -> B_28_606_0 , & _rtB -> Subsystempi2delay , & _rtDW
-> Subsystempi2delay ) ; power_FCHPS_MEA_Subsystem1 ( S , _rtB -> B_28_29_0 ,
& _rtB -> B_28_653_0 [ 0 ] , _rtB -> B_28_606_0 , & _rtB -> Subsystem1 , &
_rtDW -> Subsystem1 ) ; if ( _rtB -> B_28_29_0 != 0 ) { _rtB -> B_28_656_0 [
0 ] = _rtB -> Subsystem1 . B_3_0_0 ; _rtB -> B_28_656_0 [ 1 ] = _rtB ->
Subsystem1 . B_3_1_0 ; } else { _rtB -> B_28_656_0 [ 0 ] = _rtB ->
Subsystempi2delay . B_2_0_0 ; _rtB -> B_28_656_0 [ 1 ] = _rtB ->
Subsystempi2delay . B_2_1_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if (
isHit != 0 ) { _rtB -> B_28_660_0 [ 0 ] = _rtP -> P_363 * _rtB -> B_28_3_0 [
5 ] * _rtP -> P_366 ; _rtB -> B_28_660_0 [ 1 ] = _rtP -> P_364 * _rtB ->
B_28_3_0 [ 6 ] * _rtP -> P_366 ; _rtB -> B_28_660_0 [ 2 ] = _rtP -> P_365 *
_rtB -> B_28_3_0 [ 7 ] * _rtP -> P_366 ; } isHit = ssIsSampleHit ( S , 1 , 0
) ; if ( ( isHit != 0 ) && ( ssIsMajorTimeStep ( S ) != 0 ) ) { if ( _rtB ->
B_28_41_0_m > 0 ) { if ( ! _rtDW -> Subsystem1_MODE ) { if ( ssGetTaskTime (
S , 1 ) != ssGetTStart ( S ) ) { ssSetBlockStateForSolverChangedAtMajorStep (
S ) ; } _rtDW -> Subsystem1_MODE = true ; } } else { if ( _rtDW ->
Subsystem1_MODE ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; _rtDW
-> Subsystem1_MODE = false ; } } } if ( _rtDW -> Subsystem1_MODE ) { _rtB ->
B_11_0_0 = rtb_B_28_224_0 * muDoubleScalarCos ( _rtB -> B_28_606_0 ) -
rtb_B_28_185_0 * muDoubleScalarSin ( _rtB -> B_28_606_0 ) ; _rtB -> B_11_1_0
= rtb_B_28_224_0 * muDoubleScalarSin ( _rtB -> B_28_606_0 ) + rtb_B_28_185_0
* muDoubleScalarCos ( _rtB -> B_28_606_0 ) ; if ( ssIsMajorTimeStep ( S ) !=
0 ) { srUpdateBC ( _rtDW -> Subsystem1_SubsysRanBC ) ; } } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( ( isHit != 0 ) && ( ssIsMajorTimeStep ( S
) != 0 ) ) { if ( _rtB -> B_28_43_0_j > 0 ) { if ( ! _rtDW ->
Subsystempi2delay_MODE ) { if ( ssGetTaskTime ( S , 1 ) != ssGetTStart ( S )
) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Subsystempi2delay_MODE = true ; } } else { if ( _rtDW ->
Subsystempi2delay_MODE ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
_rtDW -> Subsystempi2delay_MODE = false ; } } } if ( _rtDW ->
Subsystempi2delay_MODE ) { _rtB -> B_10_0_0 = rtb_B_28_224_0 *
muDoubleScalarSin ( _rtB -> B_28_606_0 ) + rtb_B_28_185_0 * muDoubleScalarCos
( _rtB -> B_28_606_0 ) ; _rtB -> B_10_1_0 = - rtb_B_28_224_0 *
muDoubleScalarCos ( _rtB -> B_28_606_0 ) + rtb_B_28_185_0 * muDoubleScalarSin
( _rtB -> B_28_606_0 ) ; if ( ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC (
_rtDW -> Subsystempi2delay_SubsysRanBC ) ; } } if ( _rtB -> B_28_41_0_m != 0
) { rtb_B_28_364_0 = _rtB -> B_11_0_0 ; rtb_B_28_436_0 = _rtB -> B_11_1_0 ; }
else { rtb_B_28_364_0 = _rtB -> B_10_0_0 ; rtb_B_28_436_0 = _rtB -> B_10_1_0
; } for ( isHit = 0 ; isHit < 3 ; isHit ++ ) { _rtB -> B_28_699_0 [ isHit ] =
0.0 ; _rtB -> B_28_699_0 [ isHit ] += _rtP -> P_367 [ isHit ] *
rtb_B_28_364_0 ; _rtB -> B_28_699_0 [ isHit ] += _rtP -> P_367 [ isHit + 3 ]
* rtb_B_28_436_0 ; _rtB -> B_28_699_0 [ isHit ] += _rtP -> P_367 [ isHit + 6
] * 0.0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB ->
B_28_707_0 = _rtP -> P_368 * _rtB -> B_28_107_0 [ 35 ] ; _rtB -> B_28_711_0 =
_rtP -> P_369 * _rtB -> B_28_707_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ;
if ( isHit != 0 ) { _rtB -> B_28_712_0 = _rtB -> B_28_41_0 - _rtB ->
B_28_711_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB
-> B_28_719_0 = ( ( real_T ) ( _rtB -> B_28_707_0 < power_FCHPS_MEA_rtC ( S )
-> B_28_2_0 ) * _rtP -> P_370 - _rtB -> B_28_32_0 ) * muDoubleScalarAbs (
_rtB -> B_28_707_0 ) * _rtP -> P_371 ; } isHit = ssIsSampleHit ( S , 1 , 0 )
; if ( isHit != 0 ) { _rtB -> B_28_720_0 = _rtP -> P_372 * rtb_B_28_16_0 ; }
isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_28_721_0
= _rtP -> P_373 * _rtB -> B_28_707_0 ; _rtB -> B_28_734_0 = _rtP -> P_374 *
rtb_B_28_385_0 ; _rtB -> B_28_735_0 = _rtP -> P_375 * rtb_B_28_391_0 ; _rtB
-> B_28_736_0 = _rtP -> P_376 * rtb_B_28_127_0 ; if ( _rtB -> B_28_126_0 >=
_rtB -> B_28_74_0 ) { _rtB -> B_28_740_0 = _rtB -> B_28_75_0_b ; } else if (
_rtB -> B_28_126_0 <= _rtB -> B_28_76_0 ) { _rtB -> B_28_740_0 = _rtB ->
B_28_77_0 ; } else { _rtB -> B_28_740_0 = _rtDW -> UnitDelay1_DSTATE_f ; }
rtb_B_28_37_0 = 1.0311642900000002E+10 * _rtB -> B_28_48_0 /
3.521360402784E+9 + ( real_T ) ( _rtB -> B_28_48_0 <= 100.0 ) * 30.0 ; if (
rtb_B_28_37_0 > _rtP -> P_378 ) { _rtB -> B_28_744_0 = _rtP -> P_378 ; } else
if ( rtb_B_28_37_0 < _rtP -> P_379 ) { _rtB -> B_28_744_0 = _rtP -> P_379 ; }
else { _rtB -> B_28_744_0 = rtb_B_28_37_0 ; } _rtB -> B_28_748_0 = _rtP ->
P_380 * _rtB -> B_28_107_0 [ 52 ] ; { if ( _rtDW ->
TAQSigLogging_InsertedFor_Celldynamic_at_outport_0_PWORK . AQHandles &&
ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_Celldynamic_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 2 ) , ( char * ) & _rtB -> B_28_47_0 + 0 ) ; } } _rtB ->
B_28_753_0 = ( _rtB -> B_28_48_0 > _rtB -> B_28_87_0 ) ; } _rtB -> B_28_755_0
= ( rtb_B_28_19_0 * 101325.0 + rtb_B_28_20_0 * 101325.0 ) / ( 8.3145 * _rtB
-> B_28_61_0 ) * ( 2.6629860000000003E-18 * _rtB -> B_28_61_0 ) *
muDoubleScalarExp ( - 114559.38331414459 / ( 8.3145 * _rtB -> B_28_61_0 ) ) /
6.626e-34 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> UpperRelop_Mode_e = ( _rtB ->
B_28_48_0 < _rtB -> B_28_755_0 ) ; } _rtB -> B_28_756_0 = _rtDW ->
UpperRelop_Mode_e ; } if ( _rtB -> B_28_753_0 ) { rtb_B_28_127_0 = _rtB ->
B_28_87_0 ; } else if ( _rtB -> B_28_756_0 ) { rtb_B_28_127_0 = _rtB ->
B_28_755_0 ; } else { rtb_B_28_127_0 = _rtB -> B_28_48_0 ; } rtb_B_28_385_0 =
8.3145 * _rtB -> B_28_61_0 / 182461.51774658303 ; if ( ssIsMajorTimeStep ( S
) != 0 ) { if ( _rtDW -> Vactivation_DWORK1 != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; _rtDW ->
Vactivation_DWORK1 = 0 ; } } else { if ( rtb_B_28_127_0 < 0.0 ) {
rtb_B_28_127_0 = 0.0 ; _rtDW -> Vactivation_DWORK1 = 1 ; } } rtb_B_28_37_0 =
_rtB -> B_28_755_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { if ( _rtDW ->
Vactivation_DWORK1 != 0 ) { ssSetBlockStateForSolverChangedAtMajorStep ( S )
; ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; _rtDW ->
Vactivation_DWORK1 = 0 ; } } else { if ( _rtB -> B_28_755_0 < 0.0 ) {
rtb_B_28_37_0 = 0.0 ; _rtDW -> Vactivation_DWORK1 = 1 ; } } _rtB ->
B_28_760_0 = - 65.0 * rtb_B_28_385_0 * muDoubleScalarLog ( rtb_B_28_127_0 ) +
65.0 * rtb_B_28_385_0 * muDoubleScalarLog ( rtb_B_28_37_0 ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { { if ( _rtDW ->
TAQSigLogging_InsertedFor_Vactivation_at_outport_0_PWORK . AQHandles &&
ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_Vactivation_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_28_760_0 + 0 ) ; } } } if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Saturation_MODE [ 0 ] = _rtB ->
B_28_78_0 [ 0 ] >= _rtP -> P_381 ? 1 : _rtB -> B_28_78_0 [ 0 ] > _rtP ->
P_382 ? 0 : - 1 ; _rtDW -> Saturation_MODE [ 1 ] = _rtB -> B_28_78_0 [ 1 ] >=
_rtP -> P_381 ? 1 : _rtB -> B_28_78_0 [ 1 ] > _rtP -> P_382 ? 0 : - 1 ; }
rtb_B_28_436_0 = _rtDW -> Saturation_MODE [ 1 ] == 1 ? _rtP -> P_381 : _rtDW
-> Saturation_MODE [ 1 ] == - 1 ? _rtP -> P_382 : _rtB -> B_28_78_0 [ 1 ] ;
isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { if ( _rtB ->
B_28_89_0 > _rtP -> P_384 ) { _rtB -> B_28_764_0 = rtb_B_28_52_0 ; } else {
_rtB -> B_28_764_0 = rtb_B_28_51_0 ; } } _rtB -> B_28_766_0 = _rtB ->
B_28_91_0 - 0.024535460093391727 * _rtB -> B_28_48_0 ; _rtB -> B_28_767_0 =
65.0 * _rtB -> B_28_48_0 / ( 192970.0 * rtb_B_28_436_0 ) * 241830.0 ; _rtB ->
B_28_768_0 = _rtB -> B_28_766_0 * _rtB -> B_28_48_0 ; if ( ! ( _rtB ->
B_28_90_0 > _rtP -> P_383 ) ) { rtb_B_28_31_0 = _rtB -> B_28_56_0 ; } _rtB ->
B_28_769_0 [ 0 ] = _rtP -> P_385 * rtb_B_28_31_0 * ( _rtDW -> Saturation_MODE
[ 0 ] == 1 ? _rtP -> P_381 : _rtDW -> Saturation_MODE [ 0 ] == - 1 ? _rtP ->
P_382 : _rtB -> B_28_78_0 [ 0 ] ) ; _rtB -> B_28_769_0 [ 1 ] = _rtP -> P_385
* _rtB -> B_28_764_0 * rtb_B_28_436_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) {
_rtDW -> zeroavoider_MODE = _rtB -> B_28_767_0 >= _rtP -> P_386 ? 1 : _rtB ->
B_28_767_0 > _rtP -> P_387 ? 0 : - 1 ; _rtDW -> zeroavoider2_MODE = _rtB ->
B_28_768_0 >= _rtP -> P_388 ? 1 : _rtB -> B_28_768_0 > _rtP -> P_389 ? 0 : -
1 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB ->
B_28_803_0 = _rtDW -> DiscreteTimeIntegrator_DSTATE_bt ; _rtB -> B_28_804_0 =
( 0.0 - _rtB -> B_28_803_0 ) - _rtB -> B_28_558_0 ; rtb_B_28_51_0 = 1.0 /
rtb_B_28_99_0 * _rtB -> B_28_106_0_o ; _rtB -> B_28_812_0 = (
muDoubleScalarAbs ( _rtDW -> UnitDelay2_DSTATE_ps ) >= _rtB -> B_28_100_0_a )
; if ( _rtB -> B_28_812_0 || ( _rtDW ->
DiscreteTimeIntegrator1_PrevResetState != 0 ) ) { _rtDW ->
DiscreteTimeIntegrator1_DSTATE = _rtP -> P_395 ; } _rtB -> B_28_817_0 = ( ( (
( real_T ) ( ( _rtDW -> DiscreteTimeIntegrator1_DSTATE > 0.0 ) && ( _rtDW ->
DiscreteTimeIntegrator1_DSTATE <= 10.0 ) ) * ( _rtB -> B_28_102_0_j *
rtb_B_28_51_0 ) + ( real_T ) ( ( _rtDW -> DiscreteTimeIntegrator1_DSTATE >
10.0 ) && ( _rtDW -> DiscreteTimeIntegrator1_DSTATE <= 100.0 ) ) * ( _rtB ->
B_28_103_0_o * rtb_B_28_51_0 ) ) + _rtB -> B_28_104_0_n * rtb_B_28_51_0 * (
real_T ) ( _rtDW -> DiscreteTimeIntegrator1_DSTATE > 100.0 ) ) - _rtDW ->
UnitDelay_DSTATE_h ) * ( 1.0 / ( rtb_B_28_51_0 * 0.15 ) ) ; _rtB ->
B_28_818_0 = _rtP -> P_396 * _rtB -> B_28_558_0 ; _rtB -> B_28_828_0 = _rtP
-> P_397 * _rtB -> B_28_107_0 [ 32 ] ; _rtB -> B_28_835_0 = _rtP -> P_398 *
_rtB -> B_28_107_0 [ 53 ] ; _rtB -> B_28_839_0 = _rtP -> P_399 * _rtB ->
B_28_107_0 [ 31 ] ; _rtB -> B_28_848_0 = ( _rtP -> P_400 * _rtB -> B_28_107_0
[ 36 ] > power_FCHPS_MEA_rtC ( S ) -> B_28_4_0 ) ; rtb_B_28_37_0 = _rtP ->
P_405 * _rtB -> B_28_107_0 [ 17 ] * _rtP -> P_406 ; if ( rtb_B_28_37_0 > _rtP
-> P_407 ) { rtb_B_28_37_0 = _rtP -> P_407 ; } else { if ( rtb_B_28_37_0 <
_rtP -> P_408 ) { rtb_B_28_37_0 = _rtP -> P_408 ; } } _rtB -> B_28_878_0 = (
_rtP -> P_401 * _rtB -> B_28_3_0 [ 8 ] * ( _rtP -> P_402 * _rtB -> B_28_3_0 [
3 ] ) - _rtP -> P_403 * _rtB -> B_28_3_0 [ 4 ] * ( _rtP -> P_404 * _rtB ->
B_28_3_0 [ 9 ] ) ) / rtb_B_28_37_0 ; _rtB -> B_28_901_0 = ( _rtB ->
B_28_107_0_n - _rtB -> B_28_126_0 / _rtB -> B_28_108_0 ) * _rtP -> P_409 ;
_rtB -> B_28_902_0 = muDoubleScalarAbs ( _rtB -> B_28_901_0 ) ;
ssCallAccelRunBlock ( S , 28 , 903 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 28 , 904 , SS_CALL_MDL_OUTPUTS ) ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S ,
28 , 905 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 28 , 906 ,
SS_CALL_MDL_OUTPUTS ) ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit !=
0 ) { _rtB -> B_28_907_0 [ 0 ] = _rtB -> B_28_366_0 ; _rtB -> B_28_907_0 [ 1
] = _rtB -> B_28_555_0 ; _rtB -> B_28_907_0 [ 2 ] = _rtB -> B_28_557_0 ; _rtB
-> B_28_907_0 [ 3 ] = _rtB -> B_28_559_0 ; ssCallAccelRunBlock ( S , 28 , 908
, SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 28 , 909 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 28 , 910 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 28 , 911 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_28_912_0 = _rtDW ->
DiscreteTimeIntegrator_DSTATE_em ; } ssCallAccelRunBlock ( S , 28 , 913 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_28_916_0 = _rtP -> P_412 * _rtB ->
B_28_769_0 [ 1 ] * 117536.99999999999 / 2644.0110000000004 * _rtP -> P_413 ;
isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock
( S , 28 , 917 , SS_CALL_MDL_OUTPUTS ) ; } UNUSED_PARAMETER ( tid ) ; }
static void mdlOutputsTID4 ( SimStruct * S , int_T tid ) {
B_power_FCHPS_MEA_T * _rtB ; DW_power_FCHPS_MEA_T * _rtDW ;
P_power_FCHPS_MEA_T * _rtP ; real_T u0 ; _rtDW = ( ( DW_power_FCHPS_MEA_T * )
ssGetRootDWork ( S ) ) ; _rtP = ( ( P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S
) ) ; _rtB = ( ( B_power_FCHPS_MEA_T * ) _ssGetModelBlockIO ( S ) ) ; memcpy
( & _rtB -> B_28_0_0_m [ 0 ] , & _rtP -> P_414 [ 0 ] , 17U * sizeof ( real_T
) ) ; _rtB -> B_28_1_0_c = _rtP -> P_415 ; _rtB -> B_28_2_0_k = _rtP -> P_416
; _rtB -> B_28_3_0_c = _rtP -> P_417 ; _rtB -> B_28_4_0 = _rtP -> P_418 ;
_rtB -> B_28_5_0 = _rtP -> P_419 ; _rtB -> B_28_6_0 = _rtP -> P_420 ; _rtB ->
B_28_7_0_b = _rtP -> P_421 ; _rtB -> B_28_8_0 = _rtP -> P_422 ; _rtB ->
B_28_9_0_p = _rtP -> P_423 ; _rtB -> B_28_10_0_c = _rtP -> P_424 ; _rtB ->
B_28_11_0 = _rtP -> P_425 ; _rtB -> B_28_12_0_f = _rtP -> P_426 ; _rtB ->
B_28_13_0 = _rtP -> P_427 ; _rtB -> B_28_14_0 = _rtP -> P_428 ; _rtB ->
B_28_15_0_g = _rtP -> P_429 ; _rtB -> B_28_16_0 = _rtP -> P_430 ; _rtB ->
B_28_17_0 = _rtP -> P_431 ; _rtB -> B_28_18_0 = _rtP -> P_432 ; _rtB ->
B_28_19_0 = _rtP -> P_433 ; _rtB -> B_28_20_0 = _rtP -> P_434 ; _rtB ->
B_28_21_0 = _rtP -> P_435 ; _rtB -> B_28_22_0 = _rtP -> P_436 ; _rtB ->
B_4_0_0_m = _rtP -> P_17 ; _rtB -> B_4_1_0_c = _rtP -> P_18 ; _rtB ->
B_4_4_0_h = ( uint8_T ) ( _rtP -> P_19 == _rtP -> P_20 ) ; _rtB -> B_4_6_0_c
= ( uint8_T ) ( _rtP -> P_19 == _rtP -> P_21 ) ; if ( ssIsMajorTimeStep ( S )
!= 0 ) { srUpdateBC ( _rtDW -> AutomaticGainControl_SubsysRanBC ) ; } _rtB ->
B_28_24_0 = _rtP -> P_437 ; _rtB -> B_28_25_0 = _rtP -> P_438 ; _rtB ->
B_28_26_0_g = _rtP -> P_439 ; _rtB -> B_28_29_0 = ( uint8_T ) ( _rtP -> P_440
== _rtP -> P_441 ) ; _rtB -> B_28_31_0 = ( uint8_T ) ( _rtP -> P_440 == _rtP
-> P_442 ) ; if ( _rtP -> P_443 > _rtP -> P_444 ) { _rtB -> B_28_33_0 = _rtP
-> P_444 ; } else if ( _rtP -> P_443 < _rtP -> P_445 ) { _rtB -> B_28_33_0 =
_rtP -> P_445 ; } else { _rtB -> B_28_33_0 = _rtP -> P_443 ; } _rtB ->
B_28_36_0 = ( uint8_T ) ( _rtP -> P_446 == _rtP -> P_447 ) ; _rtB ->
B_28_38_0 = ( uint8_T ) ( _rtP -> P_446 == _rtP -> P_448 ) ; _rtB ->
B_28_41_0_m = ( uint8_T ) ( _rtP -> P_449 == _rtP -> P_450 ) ; _rtB ->
B_28_43_0_j = ( uint8_T ) ( _rtP -> P_449 == _rtP -> P_451 ) ; _rtB ->
B_28_44_0_m = _rtP -> P_452 ; _rtB -> B_28_45_0_n = _rtP -> P_453 ; _rtB ->
B_28_46_0_p = _rtP -> P_454 ; _rtB -> B_28_47_0_l = _rtP -> P_455 ; _rtB ->
B_28_48_0_j = _rtP -> P_456 ; _rtB -> B_28_49_0 = _rtP -> P_457 ; _rtB ->
B_28_50_0 = _rtP -> P_458 ; _rtB -> B_28_51_0 = _rtP -> P_459 ; _rtB ->
B_28_52_0 = _rtP -> P_460 ; _rtB -> B_28_53_0_d = _rtP -> P_461 ; _rtB ->
B_28_54_0_g = _rtP -> P_462 ; _rtB -> B_28_55_0_l = _rtP -> P_463 ; _rtB ->
B_28_56_0_d = _rtP -> P_464 ; _rtB -> B_28_57_0 = _rtP -> P_465 ; _rtB ->
B_28_58_0 = _rtP -> P_466 ; _rtB -> B_28_59_0_d = _rtP -> P_467 ; _rtB ->
B_28_60_0 = _rtP -> P_468 ; _rtB -> B_28_61_0_l = _rtP -> P_469 ; _rtB ->
B_28_62_0_o = _rtP -> P_470 ; _rtB -> B_28_63_0 = _rtP -> P_471 ; _rtB ->
B_28_64_0_b = _rtP -> P_472 ; _rtB -> B_28_65_0 = _rtP -> P_473 ; _rtB ->
B_28_66_0_n = _rtP -> P_474 ; _rtB -> B_28_67_0_b = _rtP -> P_475 ; _rtB ->
B_28_68_0 = _rtP -> P_476 ; _rtB -> B_28_69_0 = _rtP -> P_477 ; _rtB ->
B_28_70_0 = _rtP -> P_478 ; _rtB -> B_28_71_0_l = _rtP -> P_479 ; _rtB ->
B_28_72_0 = _rtP -> P_480 ; _rtB -> B_28_73_0_h = _rtP -> P_481 ; _rtB ->
B_28_74_0 = _rtP -> P_482 ; _rtB -> B_28_75_0_b = _rtP -> P_483 ; _rtB ->
B_28_76_0 = _rtP -> P_484 ; _rtB -> B_28_77_0 = _rtP -> P_485 ; _rtB ->
B_28_78_0_d = _rtP -> P_486 ; _rtB -> B_28_83_0_e = _rtP -> P_491 ; _rtB ->
B_28_84_0 = _rtP -> P_492 ; _rtB -> B_28_85_0 = _rtP -> P_493 ; _rtB ->
B_28_86_0_b = _rtP -> P_494 ; _rtB -> B_28_87_0 = _rtP -> P_495 ; _rtB ->
B_28_88_0_j = _rtP -> P_496 ; _rtB -> B_28_89_0 = _rtP -> P_497 ; _rtB ->
B_28_90_0 = _rtP -> P_498 ; u0 = _rtP -> P_488 * _rtP -> P_487 ; if ( u0 >
_rtP -> P_499 ) { _rtB -> B_28_91_0_f = _rtP -> P_499 ; } else if ( u0 < _rtP
-> P_500 ) { _rtB -> B_28_91_0_f = _rtP -> P_500 ; } else { _rtB ->
B_28_91_0_f = u0 ; } u0 = _rtP -> P_490 * _rtP -> P_489 ; if ( u0 > _rtP ->
P_501 ) { _rtB -> B_28_92_0 = _rtP -> P_501 ; } else if ( u0 < _rtP -> P_502
) { _rtB -> B_28_92_0 = _rtP -> P_502 ; } else { _rtB -> B_28_92_0 = u0 ; }
if ( _rtP -> P_503 > _rtP -> P_504 ) { _rtB -> B_28_94_0 = _rtP -> P_504 ; }
else if ( _rtP -> P_503 < _rtP -> P_505 ) { _rtB -> B_28_94_0 = _rtP -> P_505
; } else { _rtB -> B_28_94_0 = _rtP -> P_503 ; } if ( _rtP -> P_506 > _rtP ->
P_507 ) { _rtB -> B_28_96_0 = _rtP -> P_507 ; } else if ( _rtP -> P_506 <
_rtP -> P_508 ) { _rtB -> B_28_96_0 = _rtP -> P_508 ; } else { _rtB ->
B_28_96_0 = _rtP -> P_506 ; } if ( _rtP -> P_509 > _rtP -> P_510 ) { _rtB ->
B_28_98_0 = _rtP -> P_510 ; } else if ( _rtP -> P_509 < _rtP -> P_511 ) {
_rtB -> B_28_98_0 = _rtP -> P_511 ; } else { _rtB -> B_28_98_0 = _rtP ->
P_509 ; } _rtB -> B_28_99_0 = _rtP -> P_512 ; _rtB -> B_28_100_0_a = _rtP ->
P_513 ; _rtB -> B_28_101_0_j = _rtP -> P_514 ; _rtB -> B_28_102_0_j = _rtP ->
P_515 ; _rtB -> B_28_103_0_o = _rtP -> P_516 ; _rtB -> B_28_104_0_n = _rtP ->
P_517 ; _rtB -> B_28_105_0_i = _rtP -> P_518 ; _rtB -> B_28_106_0_o = _rtP ->
P_519 ; _rtB -> B_28_107_0_n = _rtP -> P_520 ; _rtB -> B_28_108_0 = _rtP ->
P_521 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { B_power_FCHPS_MEA_T *
_rtB ; DW_power_FCHPS_MEA_T * _rtDW ; P_power_FCHPS_MEA_T * _rtP ;
XDis_power_FCHPS_MEA_T * _rtXdis ; real_T HoldSine ; int32_T isHit ; _rtDW =
( ( DW_power_FCHPS_MEA_T * ) ssGetRootDWork ( S ) ) ; _rtXdis = ( (
XDis_power_FCHPS_MEA_T * ) ssGetContStateDisabled ( S ) ) ; _rtP = ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_power_FCHPS_MEA_T * ) _ssGetModelBlockIO ( S ) ) ; isHit = ssIsSampleHit (
S , 2 , 0 ) ; if ( isHit != 0 ) { HoldSine = _rtDW -> lastSin [ 0 ] ; _rtDW
-> lastSin [ 0 ] = _rtDW -> lastSin [ 0 ] * _rtP -> P_37 [ 0 ] + _rtDW ->
lastCos [ 0 ] * _rtP -> P_36 [ 0 ] ; _rtDW -> lastCos [ 0 ] = _rtDW ->
lastCos [ 0 ] * _rtP -> P_37 [ 0 ] - HoldSine * _rtP -> P_36 [ 0 ] ; HoldSine
= _rtDW -> lastSin [ 1 ] ; _rtDW -> lastSin [ 1 ] = _rtDW -> lastSin [ 1 ] *
_rtP -> P_37 [ 1 ] + _rtDW -> lastCos [ 1 ] * _rtP -> P_36 [ 1 ] ; _rtDW ->
lastCos [ 1 ] = _rtDW -> lastCos [ 1 ] * _rtP -> P_37 [ 1 ] - HoldSine * _rtP
-> P_36 [ 1 ] ; HoldSine = _rtDW -> lastSin [ 2 ] ; _rtDW -> lastSin [ 2 ] =
_rtDW -> lastSin [ 2 ] * _rtP -> P_37 [ 2 ] + _rtDW -> lastCos [ 2 ] * _rtP
-> P_36 [ 2 ] ; _rtDW -> lastCos [ 2 ] = _rtDW -> lastCos [ 2 ] * _rtP ->
P_37 [ 2 ] - HoldSine * _rtP -> P_36 [ 2 ] ; _rtDW -> UnitDelay_DSTATE = _rtB
-> B_28_699_0 [ 0 ] ; _rtDW -> UnitDelay1_DSTATE = _rtB -> B_28_699_0 [ 1 ] ;
ssCallAccelRunBlock ( S , 28 , 3 , SS_CALL_MDL_UPDATE ) ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW ->
itinit1_PreviousInput = _rtB -> B_28_46_0_p ; } isHit = ssIsSampleHit ( S , 2
, 0 ) ; if ( isHit != 0 ) { _rtDW -> Currentfilter_states = ( _rtB ->
B_28_707_0 - _rtP -> P_47 [ 1 ] * _rtDW -> Currentfilter_states ) / _rtP ->
P_47 [ 0 ] ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
_rtDW -> itinit_PreviousInput = _rtB -> B_28_720_0 ; } isHit = ssIsSampleHit
( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtDW -> inti_IC_LOADING = 0U ; _rtDW ->
inti_DSTATE += _rtP -> P_50 * _rtB -> B_28_707_0 ; if ( _rtDW -> inti_DSTATE
>= _rtP -> P_51 ) { _rtDW -> inti_DSTATE = _rtP -> P_51 ; } else { if ( _rtDW
-> inti_DSTATE <= _rtP -> P_52 ) { _rtDW -> inti_DSTATE = _rtP -> P_52 ; } }
if ( _rtB -> B_28_9_0 > 0.0 ) { _rtDW -> inti_PrevResetState = 1 ; } else if
( _rtB -> B_28_9_0 < 0.0 ) { _rtDW -> inti_PrevResetState = - 1 ; } else if (
_rtB -> B_28_9_0 == 0.0 ) { _rtDW -> inti_PrevResetState = 0 ; } else { _rtDW
-> inti_PrevResetState = 2 ; } _rtDW -> DiscreteTimeIntegrator_DSTATE += _rtP
-> P_55 * _rtB -> B_28_719_0 ; _rtDW -> Memory2_PreviousInput = _rtB ->
B_28_721_0 ; _rtDW -> UnitDelay2_DSTATE = _rtB -> B_28_186_0 ; _rtDW ->
UnitDelay1_DSTATE_a = _rtB -> B_28_250_0 ; _rtDW -> UnitDelay3_DSTATE = _rtB
-> B_28_325_0 ; _rtDW -> UnitDelay2_DSTATE_m = _rtB -> B_28_459_0 ; _rtDW ->
UnitDelay1_DSTATE_d = _rtB -> B_28_528_0 ; _rtDW -> Celldynamic_states = (
_rtB -> B_28_760_0 - _rtP -> P_64 [ 1 ] * _rtDW -> Celldynamic_states ) /
_rtP -> P_64 [ 0 ] ; _rtDW -> UnitDelay_DSTATE_a = _rtB -> B_28_748_0 ; _rtDW
-> DiscreteTimeIntegrator_DSTATE_f += _rtP -> P_97 * _rtB -> B_28_804_0 ;
_rtDW -> UnitDelay_DSTATE_c = _rtB -> B_28_878_0 ; _rtDW ->
UnitDelay3_DSTATE_c = _rtB -> B_28_188_0 ; _rtDW -> UnitDelay2_DSTATE_p =
_rtB -> B_28_252_0 ; _rtDW -> UnitDelay2_DSTATE_e = _rtB -> B_28_327_0 ;
_rtDW -> UnitDelay3_DSTATE_l = _rtB -> B_28_461_0 ; _rtDW ->
UnitDelay2_DSTATE_j = _rtB -> B_28_530_0 ; ssCallAccelRunBlock ( S , 28 , 107
, SS_CALL_MDL_UPDATE ) ; _rtDW -> DiscreteTimeIntegrator_DSTATE_h += _rtP ->
P_125 * _rtB -> B_28_736_0 ; if ( _rtDW -> DiscreteTimeIntegrator_DSTATE_h >=
_rtP -> P_127 ) { _rtDW -> DiscreteTimeIntegrator_DSTATE_h = _rtP -> P_127 ;
} else { if ( _rtDW -> DiscreteTimeIntegrator_DSTATE_h <= _rtP -> P_128 ) {
_rtDW -> DiscreteTimeIntegrator_DSTATE_h = _rtP -> P_128 ; } } _rtDW ->
UnitDelay_DSTATE_m = _rtB -> B_28_135_0 ; _rtDW ->
DiscreteTimeIntegrator_DSTATE_p += _rtP -> P_134 * _rtB -> B_28_161_0 ; if (
_rtDW -> DiscreteTimeIntegrator_DSTATE_p >= _rtP -> P_136 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_p = _rtP -> P_136 ; } else { if ( _rtDW ->
DiscreteTimeIntegrator_DSTATE_p <= _rtP -> P_137 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_p = _rtP -> P_137 ; } } _rtDW ->
DiscreteTimeIntegrator_DSTATE_o += _rtP -> P_143 * _rtB -> B_28_178_0 ; if (
_rtDW -> DiscreteTimeIntegrator_DSTATE_o >= _rtP -> P_145 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_o = _rtP -> P_145 ; } else { if ( _rtDW ->
DiscreteTimeIntegrator_DSTATE_o <= _rtP -> P_146 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_o = _rtP -> P_146 ; } } _rtDW ->
DiscreteTimeIntegrator_DSTATE_pd += _rtP -> P_159 * _rtB -> B_28_232_0 ; if (
_rtDW -> DiscreteTimeIntegrator_DSTATE_pd >= _rtP -> P_161 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_pd = _rtP -> P_161 ; } else { if ( _rtDW ->
DiscreteTimeIntegrator_DSTATE_pd <= _rtP -> P_162 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_pd = _rtP -> P_162 ; } } _rtDW ->
DiscreteTimeIntegrator_DSTATE_e += _rtP -> P_168 * _rtB -> B_28_242_0 ; if (
_rtDW -> DiscreteTimeIntegrator_DSTATE_e >= _rtP -> P_170 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_e = _rtP -> P_170 ; } else { if ( _rtDW ->
DiscreteTimeIntegrator_DSTATE_e <= _rtP -> P_171 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_e = _rtP -> P_171 ; } } _rtDW ->
UnitDelay_DSTATE_p = _rtB -> B_28_292_0 ; _rtDW ->
DiscreteTimeIntegrator_DSTATE_c += _rtP -> P_191 * _rtB -> B_28_307_0 ; if (
_rtDW -> DiscreteTimeIntegrator_DSTATE_c >= _rtP -> P_193 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_c = _rtP -> P_193 ; } else { if ( _rtDW ->
DiscreteTimeIntegrator_DSTATE_c <= _rtP -> P_194 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_c = _rtP -> P_194 ; } } _rtDW ->
DiscreteTimeIntegrator_DSTATE_fi += _rtP -> P_200 * _rtB -> B_28_317_0 ; if (
_rtDW -> DiscreteTimeIntegrator_DSTATE_fi >= _rtP -> P_202 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_fi = _rtP -> P_202 ; } else { if ( _rtDW ->
DiscreteTimeIntegrator_DSTATE_fi <= _rtP -> P_203 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_fi = _rtP -> P_203 ; } } } isHit =
ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) { _rtDW ->
UnitDelay_DSTATE_aa = _rtB -> B_28_373_0 ; _rtDW -> UnitDelay2_DSTATE_g =
_rtB -> B_28_380_0 [ 1 ] ; ssCallAccelRunBlock ( S , 28 , 380 ,
SS_CALL_MDL_UPDATE ) ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit !=
0 ) { _rtDW -> DiscreteTimeIntegrator_DSTATE_l += _rtP -> P_235 * _rtB ->
B_28_734_0 ; if ( _rtDW -> DiscreteTimeIntegrator_DSTATE_l >= _rtP -> P_237 )
{ _rtDW -> DiscreteTimeIntegrator_DSTATE_l = _rtP -> P_237 ; } else { if (
_rtDW -> DiscreteTimeIntegrator_DSTATE_l <= _rtP -> P_238 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_l = _rtP -> P_238 ; } } _rtDW ->
DiscreteTimeIntegrator_DSTATE_n += _rtP -> P_242 * _rtB -> B_28_735_0 ; if (
_rtDW -> DiscreteTimeIntegrator_DSTATE_n >= _rtP -> P_244 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_n = _rtP -> P_244 ; } else { if ( _rtDW ->
DiscreteTimeIntegrator_DSTATE_n <= _rtP -> P_245 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_n = _rtP -> P_245 ; } } _rtDW ->
UnitDelay_DSTATE_l = _rtB -> B_28_410_0 ; _rtDW ->
DiscreteTimeIntegrator_DSTATE_g += _rtP -> P_256 * _rtB -> B_28_434_0 ; if (
_rtDW -> DiscreteTimeIntegrator_DSTATE_g >= _rtP -> P_258 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_g = _rtP -> P_258 ; } else { if ( _rtDW ->
DiscreteTimeIntegrator_DSTATE_g <= _rtP -> P_259 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_g = _rtP -> P_259 ; } } _rtDW ->
DiscreteTimeIntegrator_DSTATE_b += _rtP -> P_265 * _rtB -> B_28_451_0 ; if (
_rtDW -> DiscreteTimeIntegrator_DSTATE_b >= _rtP -> P_267 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_b = _rtP -> P_267 ; } else { if ( _rtDW ->
DiscreteTimeIntegrator_DSTATE_b <= _rtP -> P_268 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_b = _rtP -> P_268 ; } } _rtDW ->
DiscreteTimeIntegrator_DSTATE_hn += _rtP -> P_281 * _rtB -> B_28_505_0 ; if (
_rtDW -> DiscreteTimeIntegrator_DSTATE_hn >= _rtP -> P_283 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_hn = _rtP -> P_283 ; } else { if ( _rtDW ->
DiscreteTimeIntegrator_DSTATE_hn <= _rtP -> P_284 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_hn = _rtP -> P_284 ; } } _rtDW ->
DiscreteTimeIntegrator_DSTATE_hc += _rtP -> P_290 * _rtB -> B_28_521_0 ; if (
_rtDW -> DiscreteTimeIntegrator_DSTATE_hc >= _rtP -> P_292 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_hc = _rtP -> P_292 ; } else { if ( _rtDW ->
DiscreteTimeIntegrator_DSTATE_hc <= _rtP -> P_293 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_hc = _rtP -> P_293 ; } } _rtDW ->
UnitDelay4_DSTATE = _rtB -> B_28_584_0 ; } _rtDW -> Integrator_IWORK = 0 ;
switch ( _rtDW -> Integrator_MODE ) { case 3 : if ( _rtB -> B_28_630_0 < 0.0
) { _rtDW -> Integrator_MODE = 1 ; ssSetBlockStateForSolverChangedAtMajorStep
( S ) ; } break ; case 4 : if ( _rtB -> B_28_630_0 > 0.0 ) { _rtDW ->
Integrator_MODE = 2 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; }
break ; } _rtXdis -> Integrator_CSTATE = ( ( _rtDW -> Integrator_MODE == 3 )
|| ( _rtDW -> Integrator_MODE == 4 ) ) ; isHit = ssIsSampleHit ( S , 1 , 0 )
; if ( isHit != 0 ) { _rtDW -> Memory_PreviousInput = _rtB -> B_28_649_0 ; }
if ( _rtDW -> AutomaticGainControl_MODE ) { { real_T * * uBuffer = ( real_T *
* ) & _rtDW -> VariableTransportDelay_PWORK_b . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & _rtDW -> VariableTransportDelay_PWORK_b .
TUbufferPtrs [ 1 ] ; real_T * * xBuffer = ( real_T * * ) & _rtDW ->
VariableTransportDelay_PWORK_b . TUbufferPtrs [ 2 ] ; real_T simTime = ssGetT
( S ) ; _rtDW -> VariableTransportDelay_IWORK_n . Head = ( ( _rtDW ->
VariableTransportDelay_IWORK_n . Head < ( _rtDW ->
VariableTransportDelay_IWORK_n . CircularBufSize - 1 ) ) ? ( _rtDW ->
VariableTransportDelay_IWORK_n . Head + 1 ) : 0 ) ; if ( _rtDW ->
VariableTransportDelay_IWORK_n . Head == _rtDW ->
VariableTransportDelay_IWORK_n . Tail ) { if ( !
power_FCHPS_MEA_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
VariableTransportDelay_IWORK_n . CircularBufSize , & _rtDW ->
VariableTransportDelay_IWORK_n . Tail , & _rtDW ->
VariableTransportDelay_IWORK_n . Head , & _rtDW ->
VariableTransportDelay_IWORK_n . Last , simTime - _rtP -> P_1 , tBuffer ,
uBuffer , xBuffer , ( boolean_T ) 0 , ( boolean_T ) 1 , & _rtDW ->
VariableTransportDelay_IWORK_n . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"vtdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
VariableTransportDelay_IWORK_n . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
VariableTransportDelay_IWORK_n . Head ] = _rtB -> B_4_1_0 ; ( * xBuffer ) [
_rtDW -> VariableTransportDelay_IWORK_n . Head ] = ( ( X_power_FCHPS_MEA_T *
) ssGetContStates ( S ) ) -> VariableTransportDelay_CSTATE_n ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW ->
Memory_PreviousInput_i = _rtB -> B_4_6_0 ; } { real_T * * uBuffer = ( real_T
* * ) & _rtDW -> VariableTransportDelay_PWORK_c . TUbufferPtrs [ 0 ] ; real_T
* * tBuffer = ( real_T * * ) & _rtDW -> VariableTransportDelay_PWORK_c .
TUbufferPtrs [ 1 ] ; real_T * * xBuffer = ( real_T * * ) & _rtDW ->
VariableTransportDelay_PWORK_c . TUbufferPtrs [ 2 ] ; real_T simTime = ssGetT
( S ) ; _rtDW -> VariableTransportDelay_IWORK_f . Head = ( ( _rtDW ->
VariableTransportDelay_IWORK_f . Head < ( _rtDW ->
VariableTransportDelay_IWORK_f . CircularBufSize - 1 ) ) ? ( _rtDW ->
VariableTransportDelay_IWORK_f . Head + 1 ) : 0 ) ; if ( _rtDW ->
VariableTransportDelay_IWORK_f . Head == _rtDW ->
VariableTransportDelay_IWORK_f . Tail ) { if ( !
power_FCHPS_MEA_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
VariableTransportDelay_IWORK_f . CircularBufSize , & _rtDW ->
VariableTransportDelay_IWORK_f . Tail , & _rtDW ->
VariableTransportDelay_IWORK_f . Head , & _rtDW ->
VariableTransportDelay_IWORK_f . Last , simTime - _rtP -> P_5 , tBuffer ,
uBuffer , xBuffer , ( boolean_T ) 0 , ( boolean_T ) 1 , & _rtDW ->
VariableTransportDelay_IWORK_f . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"vtdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
VariableTransportDelay_IWORK_f . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
VariableTransportDelay_IWORK_f . Head ] = _rtB -> B_4_8_0 ; ( * xBuffer ) [
_rtDW -> VariableTransportDelay_IWORK_f . Head ] = ( ( X_power_FCHPS_MEA_T *
) ssGetContStates ( S ) ) -> VariableTransportDelay_CSTATE_b ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW ->
Memory_PreviousInput_l = _rtB -> B_4_13_0 ; } } switch ( _rtDW ->
Integrator_MODE_g ) { case 3 : if ( _rtB -> B_28_626_0 < 0.0 ) { _rtDW ->
Integrator_MODE_g = 1 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; }
break ; case 4 : if ( _rtB -> B_28_626_0 > 0.0 ) { _rtDW -> Integrator_MODE_g
= 2 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis
-> Integrator_CSTATE_g = ( ( _rtDW -> Integrator_MODE_g == 3 ) || ( _rtDW ->
Integrator_MODE_g == 4 ) ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
VariableTransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = (
real_T * * ) & _rtDW -> VariableTransportDelay_PWORK . TUbufferPtrs [ 1 ] ;
real_T * * xBuffer = ( real_T * * ) & _rtDW -> VariableTransportDelay_PWORK .
TUbufferPtrs [ 2 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
VariableTransportDelay_IWORK . Head = ( ( _rtDW ->
VariableTransportDelay_IWORK . Head < ( _rtDW -> VariableTransportDelay_IWORK
. CircularBufSize - 1 ) ) ? ( _rtDW -> VariableTransportDelay_IWORK . Head +
1 ) : 0 ) ; if ( _rtDW -> VariableTransportDelay_IWORK . Head == _rtDW ->
VariableTransportDelay_IWORK . Tail ) { if ( !
power_FCHPS_MEA_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
VariableTransportDelay_IWORK . CircularBufSize , & _rtDW ->
VariableTransportDelay_IWORK . Tail , & _rtDW -> VariableTransportDelay_IWORK
. Head , & _rtDW -> VariableTransportDelay_IWORK . Last , simTime - _rtP ->
P_333 , tBuffer , uBuffer , xBuffer , ( boolean_T ) 0 , ( boolean_T ) 1 , &
_rtDW -> VariableTransportDelay_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus
( S , "vtdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [
_rtDW -> VariableTransportDelay_IWORK . Head ] = simTime ; ( * uBuffer ) [
_rtDW -> VariableTransportDelay_IWORK . Head ] = _rtB -> B_28_618_0 ; ( *
xBuffer ) [ _rtDW -> VariableTransportDelay_IWORK . Head ] = ( (
X_power_FCHPS_MEA_T * ) ssGetContStates ( S ) ) ->
VariableTransportDelay_CSTATE ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { _rtDW -> Memory_PreviousInput_g = _rtB -> B_28_623_0 ; } if (
_rtDW -> LastMajorTimeA == ( rtInf ) ) { _rtDW -> LastMajorTimeA =
ssGetTaskTime ( S , 0 ) ; _rtDW -> PrevYA = _rtB -> B_28_632_0 ; } else if (
_rtDW -> LastMajorTimeB == ( rtInf ) ) { _rtDW -> LastMajorTimeB =
ssGetTaskTime ( S , 0 ) ; _rtDW -> PrevYB = _rtB -> B_28_632_0 ; } else if (
_rtDW -> LastMajorTimeA < _rtDW -> LastMajorTimeB ) { _rtDW -> LastMajorTimeA
= ssGetTaskTime ( S , 0 ) ; _rtDW -> PrevYA = _rtB -> B_28_632_0 ; } else {
_rtDW -> LastMajorTimeB = ssGetTaskTime ( S , 0 ) ; _rtDW -> PrevYB = _rtB ->
B_28_632_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) {
_rtDW -> UnitDelay1_DSTATE_f = _rtB -> B_28_740_0 ; _rtDW ->
DiscreteTimeIntegrator_DSTATE_bt += _rtP -> P_390 * _rtB -> B_28_817_0 ;
_rtDW -> UnitDelay2_DSTATE_ps = _rtB -> B_28_818_0 ; _rtDW ->
UnitDelay_DSTATE_h = _rtB -> B_28_803_0 ; if ( ! _rtB -> B_28_812_0 ) { _rtDW
-> DiscreteTimeIntegrator1_DSTATE += _rtP -> P_394 * _rtB -> B_28_101_0_j ; }
_rtDW -> DiscreteTimeIntegrator1_PrevResetState = ( int8_T ) _rtB ->
B_28_812_0 ; _rtDW -> DiscreteTimeIntegrator_DSTATE_em += _rtP -> P_410 *
_rtB -> B_28_916_0 ; } UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID4 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { B_power_FCHPS_MEA_T * _rtB ;
DW_power_FCHPS_MEA_T * _rtDW ; P_power_FCHPS_MEA_T * _rtP ;
XDis_power_FCHPS_MEA_T * _rtXdis ; XDot_power_FCHPS_MEA_T * _rtXdot ;
X_power_FCHPS_MEA_T * _rtX ; _rtDW = ( ( DW_power_FCHPS_MEA_T * )
ssGetRootDWork ( S ) ) ; _rtXdis = ( ( XDis_power_FCHPS_MEA_T * )
ssGetContStateDisabled ( S ) ) ; _rtXdot = ( ( XDot_power_FCHPS_MEA_T * )
ssGetdX ( S ) ) ; _rtX = ( ( X_power_FCHPS_MEA_T * ) ssGetContStates ( S ) )
; _rtP = ( ( P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_power_FCHPS_MEA_T * ) _ssGetModelBlockIO ( S ) ) ; _rtXdot ->
Airblowerdelay2_CSTATE = 0.0 ; _rtXdot -> Airblowerdelay2_CSTATE += _rtP ->
P_74 * _rtX -> Airblowerdelay2_CSTATE ; _rtXdot -> Airblowerdelay2_CSTATE +=
_rtB -> B_28_744_0 ; if ( _rtXdis -> Integrator_CSTATE ) { _rtXdot ->
Integrator_CSTATE = 0.0 ; } else { _rtXdot -> Integrator_CSTATE = _rtB ->
B_28_630_0 ; } if ( _rtDW -> AutomaticGainControl_MODE ) { { real_T
instantDelay ; instantDelay = _rtB -> B_4_19_0 ; if ( instantDelay > _rtP ->
P_1 ) { instantDelay = _rtP -> P_1 ; } if ( instantDelay < 0.0 ) { ( (
XDot_power_FCHPS_MEA_T * ) ssGetdX ( S ) ) -> VariableTransportDelay_CSTATE_n
= 0 ; } else { ( ( XDot_power_FCHPS_MEA_T * ) ssGetdX ( S ) ) ->
VariableTransportDelay_CSTATE_n = 1.0 / instantDelay ; } } _rtXdot ->
integrator_CSTATE_o = _rtB -> B_4_26_0 [ 0 ] ; { real_T instantDelay ;
instantDelay = _rtB -> B_4_21_0 ; if ( instantDelay > _rtP -> P_5 ) {
instantDelay = _rtP -> P_5 ; } if ( instantDelay < 0.0 ) { ( (
XDot_power_FCHPS_MEA_T * ) ssGetdX ( S ) ) -> VariableTransportDelay_CSTATE_b
= 0 ; } else { ( ( XDot_power_FCHPS_MEA_T * ) ssGetdX ( S ) ) ->
VariableTransportDelay_CSTATE_b = 1.0 / instantDelay ; } } _rtXdot ->
integrator_CSTATE_i = _rtB -> B_4_26_0 [ 1 ] ; } else { { real_T * dx ; int_T
i ; dx = & ( ( ( XDot_power_FCHPS_MEA_T * ) ssGetdX ( S ) ) ->
VariableTransportDelay_CSTATE_n ) ; for ( i = 0 ; i < 4 ; i ++ ) { dx [ i ] =
0.0 ; } } } if ( _rtXdis -> Integrator_CSTATE_g ) { _rtXdot ->
Integrator_CSTATE_g = 0.0 ; } else { _rtXdot -> Integrator_CSTATE_g = _rtB ->
B_28_626_0 ; } { real_T instantDelay ; instantDelay = _rtB -> B_28_651_0 ; if
( instantDelay > _rtP -> P_333 ) { instantDelay = _rtP -> P_333 ; } if (
instantDelay < 0.0 ) { ( ( XDot_power_FCHPS_MEA_T * ) ssGetdX ( S ) ) ->
VariableTransportDelay_CSTATE = 0 ; } else { ( ( XDot_power_FCHPS_MEA_T * )
ssGetdX ( S ) ) -> VariableTransportDelay_CSTATE = 1.0 / instantDelay ; } }
_rtXdot -> integrator_CSTATE = _rtB -> B_28_656_0 [ 1 ] ; _rtXdot ->
TransferFcn_CSTATE = 0.0 ; _rtXdot -> TransferFcn_CSTATE += _rtP -> P_340 *
_rtX -> TransferFcn_CSTATE ; _rtXdot -> TransferFcn_CSTATE += _rtB ->
B_28_627_0 ; _rtXdot -> Integrator_x1_CSTATE = _rtB -> B_28_642_0 ; _rtXdot
-> Integrator_x2_CSTATE = _rtB -> B_28_644_0 ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { B_power_FCHPS_MEA_T * _rtB ;
DW_power_FCHPS_MEA_T * _rtDW ; P_power_FCHPS_MEA_T * _rtP ;
X_power_FCHPS_MEA_T * _rtX ; ZCV_power_FCHPS_MEA_T * _rtZCSV ; _rtDW = ( (
DW_power_FCHPS_MEA_T * ) ssGetRootDWork ( S ) ) ; _rtZCSV = ( (
ZCV_power_FCHPS_MEA_T * ) ssGetSolverZcSignalVector ( S ) ) ; _rtX = ( (
X_power_FCHPS_MEA_T * ) ssGetContStates ( S ) ) ; _rtP = ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_power_FCHPS_MEA_T * ) _ssGetModelBlockIO ( S ) ) ; _rtZCSV ->
Saturation4_UprLim_ZC = _rtB -> B_28_55_0 - _rtP -> P_76 ; _rtZCSV ->
Saturation4_LwrLim_ZC = _rtB -> B_28_55_0 - _rtP -> P_77 ; _rtZCSV ->
Saturation3_UprLim_ZC = _rtB -> B_28_56_0 - _rtP -> P_78 ; _rtZCSV ->
Saturation3_LwrLim_ZC = _rtB -> B_28_56_0 - _rtP -> P_79 ; _rtZCSV ->
Saturation4_UprLim_ZC_n = _rtB -> B_28_59_0 - _rtP -> P_81 ; _rtZCSV ->
Saturation4_LwrLim_ZC_b = _rtB -> B_28_59_0 - _rtP -> P_82 ; _rtZCSV ->
Saturation1_UprLim_ZC = _rtB -> B_28_62_0 - _rtP -> P_83 ; _rtZCSV ->
Saturation1_LwrLim_ZC = _rtB -> B_28_62_0 - _rtP -> P_84 ; _rtZCSV ->
Saturation4_UprLim_ZC_g = _rtB -> B_28_64_0 - _rtP -> P_85 ; _rtZCSV ->
Saturation4_LwrLim_ZC_l = _rtB -> B_28_64_0 - _rtP -> P_86 ; _rtZCSV ->
Saturation5_UprLim_ZC = _rtB -> B_28_66_0 - _rtP -> P_87 ; _rtZCSV ->
Saturation5_LwrLim_ZC = _rtB -> B_28_66_0 - _rtP -> P_88 ; _rtZCSV ->
Switch_SwitchCond_ZC = _rtB -> B_28_61_0 - _rtP -> P_89 ; _rtZCSV ->
Compare_RelopInput_ZC = _rtB -> B_28_59_0 - _rtB -> B_28_83_0_e ; _rtZCSV ->
MinMax_MinmaxInput_ZC = muDoubleScalarMax ( _rtB -> B_28_79_0 [ 1 ] , _rtB ->
B_28_79_0 [ 0 ] ) - _rtB -> B_28_79_0 [ _rtDW -> MinMax_MODE ] ; _rtZCSV ->
Saturation2_UprLim_ZC = _rtB -> B_28_80_0 - _rtP -> P_93 ; _rtZCSV ->
Saturation2_LwrLim_ZC = _rtB -> B_28_80_0 - _rtP -> P_94 ; _rtZCSV ->
Compare_RelopInput_ZC_p = _rtB -> B_28_81_0 - _rtB -> B_28_84_0 ; _rtZCSV ->
LowerRelop1_RelopInput_ZC = _rtB -> B_28_86_0 - _rtB -> B_28_86_0_b ; _rtZCSV
-> UpperRelop_RelopInput_ZC = _rtB -> B_28_86_0 - _rtB -> B_28_88_0 ; _rtZCSV
-> RelationalOperator_RelopInput_ZC = _rtB -> B_28_120_0 - _rtB -> B_28_3_0_c
; _rtZCSV -> RelationalOperator_RelopInput_ZC_a = _rtB -> B_28_359_0 - _rtB
-> B_28_14_0 ; _rtZCSV -> Abs_AbsZc_ZC = _rtB -> B_28_567_0 ; _rtZCSV ->
Abs1_AbsZc_ZC = _rtB -> B_28_571_0 ; _rtZCSV -> Saturation2_UprLim_ZC_l =
_rtB -> B_28_561_0 - _rtP -> P_311 ; _rtZCSV -> Saturation2_LwrLim_ZC_m =
_rtB -> B_28_561_0 - _rtP -> P_312 ; _rtZCSV ->
RelationalOperator_RelopInput_ZC_f = _rtX -> Integrator_CSTATE - _rtB ->
B_28_25_0 ; switch ( _rtDW -> Integrator_MODE ) { case 1 : _rtZCSV ->
Integrator_IntgUpLimit_ZC = 0.0 ; _rtZCSV -> Integrator_IntgLoLimit_ZC = _rtP
-> P_326 - _rtP -> P_327 ; break ; case 2 : _rtZCSV ->
Integrator_IntgUpLimit_ZC = _rtP -> P_327 - _rtP -> P_326 ; _rtZCSV ->
Integrator_IntgLoLimit_ZC = 0.0 ; break ; default : _rtZCSV ->
Integrator_IntgUpLimit_ZC = _rtX -> Integrator_CSTATE - _rtP -> P_326 ;
_rtZCSV -> Integrator_IntgLoLimit_ZC = _rtX -> Integrator_CSTATE - _rtP ->
P_327 ; break ; } if ( ( _rtDW -> Integrator_MODE == 3 ) || ( _rtDW ->
Integrator_MODE == 4 ) ) { _rtZCSV -> Integrator_LeaveSaturate_ZC = _rtB ->
B_28_630_0 ; } else { _rtZCSV -> Integrator_LeaveSaturate_ZC = 0.0 ; }
_rtZCSV -> HitCrossing_HitNoOutput_ZC = _rtB -> B_28_606_0 - _rtP -> P_328 ;
if ( _rtDW -> AutomaticGainControl_MODE ) { _rtZCSV ->
RelationalOperator_RelopInput_ZC_h = _rtB -> B_4_2_0 - _rtB -> B_4_0_0_m ;
_rtZCSV -> RelationalOperator_RelopInput_ZC_b = _rtB -> B_4_9_0 - _rtB ->
B_4_1_0_c ; _rtZCSV -> Saturation_UprLim_ZC_p = _rtB -> B_4_15_0 - _rtP ->
P_9 ; _rtZCSV -> Saturation_LwrLim_ZC_m = _rtB -> B_4_15_0 - _rtP -> P_10 ; }
else { { real_T * zcsv = & ( ( ( ZCV_power_FCHPS_MEA_T * )
ssGetSolverZcSignalVector ( S ) ) -> RelationalOperator_RelopInput_ZC_h ) ;
int_T i ; for ( i = 0 ; i < 4 ; i ++ ) { zcsv [ i ] = 0.0 ; } } } switch (
_rtDW -> Integrator_MODE_g ) { case 1 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_g = 0.0 ; _rtZCSV -> Integrator_IntgLoLimit_ZC_f =
_rtP -> P_331 - _rtP -> P_332 ; break ; case 2 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_g = _rtP -> P_332 - _rtP -> P_331 ; _rtZCSV ->
Integrator_IntgLoLimit_ZC_f = 0.0 ; break ; default : _rtZCSV ->
Integrator_IntgUpLimit_ZC_g = _rtX -> Integrator_CSTATE_g - _rtP -> P_331 ;
_rtZCSV -> Integrator_IntgLoLimit_ZC_f = _rtX -> Integrator_CSTATE_g - _rtP
-> P_332 ; break ; } if ( ( _rtDW -> Integrator_MODE_g == 3 ) || ( _rtDW ->
Integrator_MODE_g == 4 ) ) { _rtZCSV -> Integrator_LeaveSaturate_ZC_k = _rtB
-> B_28_626_0 ; } else { _rtZCSV -> Integrator_LeaveSaturate_ZC_k = 0.0 ; }
_rtZCSV -> RelationalOperator_RelopInput_ZC_e = _rtB -> B_28_619_0 - _rtB ->
B_28_26_0_g ; _rtZCSV -> Saturation2_UprLim_ZC_lq = _rtB -> B_28_629_0 - _rtP
-> P_343 ; _rtZCSV -> Saturation2_LwrLim_ZC_o = _rtB -> B_28_629_0 - _rtP ->
P_344 ; _rtZCSV -> UpperRelop_RelopInput_ZC_f = _rtB -> B_28_48_0 - _rtB ->
B_28_755_0 ; _rtZCSV -> Saturation_UprLim_ZC [ 0 ] = _rtB -> B_28_78_0 [ 0 ]
- _rtP -> P_381 ; _rtZCSV -> Saturation_LwrLim_ZC [ 0 ] = _rtB -> B_28_78_0 [
0 ] - _rtP -> P_382 ; _rtZCSV -> Saturation_UprLim_ZC [ 1 ] = _rtB ->
B_28_78_0 [ 1 ] - _rtP -> P_381 ; _rtZCSV -> Saturation_LwrLim_ZC [ 1 ] =
_rtB -> B_28_78_0 [ 1 ] - _rtP -> P_382 ; _rtZCSV -> zeroavoider_UprLim_ZC =
_rtB -> B_28_767_0 - _rtP -> P_386 ; _rtZCSV -> zeroavoider_LwrLim_ZC = _rtB
-> B_28_767_0 - _rtP -> P_387 ; _rtZCSV -> zeroavoider2_UprLim_ZC = _rtB ->
B_28_768_0 - _rtP -> P_388 ; _rtZCSV -> zeroavoider2_LwrLim_ZC = _rtB ->
B_28_768_0 - _rtP -> P_389 ; } static void mdlInitializeSizes ( SimStruct * S
) { ssSetChecksumVal ( S , 0 , 2938666066U ) ; ssSetChecksumVal ( S , 1 ,
288249069U ) ; ssSetChecksumVal ( S , 2 , 2957560144U ) ; ssSetChecksumVal (
S , 3 , 508576521U ) ; { mxArray * slVerStructMat = NULL ; mxArray * slStrMat
= mxCreateString ( "simulink" ) ; char slVerChar [ 10 ] ; int status =
mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat , "ver" ) ; if ( status
== 0 ) { mxArray * slVerMat = mxGetField ( slVerStructMat , 0 , "Version" ) ;
if ( slVerMat == NULL ) { status = 1 ; } else { status = mxGetString (
slVerMat , slVerChar , 10 ) ; } } mxDestroyArray ( slStrMat ) ;
mxDestroyArray ( slVerStructMat ) ; if ( ( status == 1 ) || ( strcmp (
slVerChar , "10.2" ) != 0 ) ) { return ; } } ssSetOptions ( S ,
SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork ( S ) != sizeof (
DW_power_FCHPS_MEA_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_power_FCHPS_MEA_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_power_FCHPS_MEA_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetModelRtp ( S , ( real_T *
) & power_FCHPS_MEA_rtDefaultP ) ; _ssSetConstBlockIO ( S , &
power_FCHPS_MEA_rtInvariant ) ; rt_InitInfAndNaN ( sizeof ( real_T ) ) ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_9 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_25 = rtMinusInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_52 = rtMinusInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_67 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_69 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_76 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_78 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_83 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_85 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_87 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_99 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_147 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_153 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_177 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_209 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_213 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_232 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_269 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_275 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_299 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_311 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_326 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_327 = rtMinusInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_331 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_343 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_378 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_386 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_388 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_407 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_494 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_495 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_504 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_507 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_510 = rtInf ; } static
void mdlInitializeSampleTimes ( SimStruct * S ) { slAccRegPrmChangeFcn ( S ,
mdlOutputsTID4 ) ; } static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"

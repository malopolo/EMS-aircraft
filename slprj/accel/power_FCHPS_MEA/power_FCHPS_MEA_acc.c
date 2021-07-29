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
) { B_power_FCHPS_MEA_T * _rtB ; DW_power_FCHPS_MEA_T * _rtDW ;
P_power_FCHPS_MEA_T * _rtP ; PrevZCX_power_FCHPS_MEA_T * _rtZCE ;
X_power_FCHPS_MEA_T * _rtX ; real_T rtb_B_26_111_0 ; real_T rtb_B_26_117_0 ;
real_T rtb_B_26_121_0 ; real_T rtb_B_26_125_0 ; real_T rtb_B_26_153_0 ;
real_T rtb_B_26_158_0 ; real_T rtb_B_26_159_0 ; real_T rtb_B_26_16_0 ; real_T
rtb_B_26_179_0 ; real_T rtb_B_26_19_0 ; real_T rtb_B_26_20_0 ; real_T
rtb_B_26_21_0 ; real_T rtb_B_26_229_0 ; real_T rtb_B_26_292_0 ; real_T
rtb_B_26_294_0 ; real_T rtb_B_26_308_0 ; real_T rtb_B_26_314_0 ; real_T
rtb_B_26_31_0 ; real_T rtb_B_26_359_0 ; real_T rtb_B_26_360_0 ; real_T
rtb_B_26_361_0 ; real_T rtb_B_26_37_0 ; real_T rtb_B_26_49_0 ; real_T
rtb_B_26_4_0 ; real_T rtb_B_26_50_0 ; real_T rtb_B_26_5_0 ; real_T
rtb_B_26_6_0 ; real_T rtb_B_26_92_0 ; real_T rtb_B_26_97_0 ; real_T tmp ;
real_T tmp_0 ; int32_T isHit ; boolean_T rtb_B_26_115_0 ; boolean_T
rtb_B_26_135_0 ; boolean_T rtb_B_26_13_0 ; boolean_T rtb_B_26_166_0 ;
boolean_T rtb_B_26_290_0 ; boolean_T rtb_B_26_337_0 ; boolean_T
rtb_B_26_368_0 ; boolean_T rtb_B_26_38_0 ; boolean_T rtb_B_26_428_0 ; _rtDW =
( ( DW_power_FCHPS_MEA_T * ) ssGetRootDWork ( S ) ) ; _rtZCE = ( (
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
= 0 ; } _rtB -> B_26_0_0 [ 0 ] = ( ( _rtDW -> lastSin [ 0 ] * _rtP -> P_39 [
0 ] + _rtDW -> lastCos [ 0 ] * _rtP -> P_38 [ 0 ] ) * _rtP -> P_37 [ 0 ] + (
_rtDW -> lastCos [ 0 ] * _rtP -> P_39 [ 0 ] - _rtDW -> lastSin [ 0 ] * _rtP
-> P_38 [ 0 ] ) * _rtP -> P_36 [ 0 ] ) * _rtP -> P_33 + _rtP -> P_34 ; _rtB
-> B_26_0_0 [ 1 ] = ( ( _rtDW -> lastSin [ 1 ] * _rtP -> P_39 [ 1 ] + _rtDW
-> lastCos [ 1 ] * _rtP -> P_38 [ 1 ] ) * _rtP -> P_37 [ 1 ] + ( _rtDW ->
lastCos [ 1 ] * _rtP -> P_39 [ 1 ] - _rtDW -> lastSin [ 1 ] * _rtP -> P_38 [
1 ] ) * _rtP -> P_36 [ 1 ] ) * _rtP -> P_33 + _rtP -> P_34 ; _rtB -> B_26_0_0
[ 2 ] = ( ( _rtDW -> lastSin [ 2 ] * _rtP -> P_39 [ 2 ] + _rtDW -> lastCos [
2 ] * _rtP -> P_38 [ 2 ] ) * _rtP -> P_37 [ 2 ] + ( _rtDW -> lastCos [ 2 ] *
_rtP -> P_39 [ 2 ] - _rtDW -> lastSin [ 2 ] * _rtP -> P_38 [ 2 ] ) * _rtP ->
P_36 [ 2 ] ) * _rtP -> P_33 + _rtP -> P_34 ; _rtB -> B_26_1_0 = _rtDW ->
UnitDelay_DSTATE ; _rtB -> B_26_2_0 = _rtDW -> UnitDelay1_DSTATE ;
ssCallAccelRunBlock ( S , 26 , 3 , SS_CALL_MDL_OUTPUTS ) ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { rtb_B_26_4_0 = _rtDW ->
itinit1_PreviousInput ; rtb_B_26_5_0 = _rtP -> P_45 * _rtDW ->
itinit1_PreviousInput ; rtb_B_26_6_0 = 1.000001 * rtb_B_26_5_0 *
0.96339113680154431 / 0.9999 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if (
isHit != 0 ) { _rtB -> B_26_7_0 = _rtP -> P_46 * _rtDW ->
Currentfilter_states ; _rtB -> B_26_9_0 = ( _rtB -> B_26_7_0 >
power_FCHPS_MEA_rtC ( S ) -> B_26_0_0 ) ; } isHit = ssIsSampleHit ( S , 1 , 0
) ; if ( isHit != 0 ) { _rtB -> B_26_10_0 = _rtDW -> itinit_PreviousInput ; }
isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { if ( _rtDW ->
inti_IC_LOADING != 0 ) { _rtDW -> inti_DSTATE = _rtB -> B_26_10_0 ; if (
_rtDW -> inti_DSTATE >= _rtP -> P_51 ) { _rtDW -> inti_DSTATE = _rtP -> P_51
; } else { if ( _rtDW -> inti_DSTATE <= _rtP -> P_52 ) { _rtDW -> inti_DSTATE
= _rtP -> P_52 ; } } } if ( ( _rtB -> B_26_9_0 > 0.0 ) && ( _rtDW ->
inti_PrevResetState <= 0 ) ) { _rtDW -> inti_DSTATE = _rtB -> B_26_10_0 ; if
( _rtDW -> inti_DSTATE >= _rtP -> P_51 ) { _rtDW -> inti_DSTATE = _rtP ->
P_51 ; } else { if ( _rtDW -> inti_DSTATE <= _rtP -> P_52 ) { _rtDW ->
inti_DSTATE = _rtP -> P_52 ; } } } if ( _rtDW -> inti_DSTATE >= _rtP -> P_51
) { _rtDW -> inti_DSTATE = _rtP -> P_51 ; } else { if ( _rtDW -> inti_DSTATE
<= _rtP -> P_52 ) { _rtDW -> inti_DSTATE = _rtP -> P_52 ; } } _rtB ->
B_26_12_0 = _rtP -> P_53 * _rtDW -> inti_DSTATE ; } isHit = ssIsSampleHit ( S
, 1 , 0 ) ; if ( isHit != 0 ) { rtb_B_26_13_0 = ( _rtB -> B_26_12_0 >
rtb_B_26_5_0 ) ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) {
if ( _rtB -> B_26_12_0 < _rtB -> B_26_42_0_m ) { _rtB -> B_26_15_0 = _rtB ->
B_26_42_0_m ; } else { _rtB -> B_26_15_0 = _rtB -> B_26_12_0 ; } } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( rtb_B_26_13_0 ) {
rtb_B_26_16_0 = rtb_B_26_5_0 ; } else { rtb_B_26_16_0 = _rtB -> B_26_15_0 ; }
if ( rtb_B_26_6_0 <= rtb_B_26_16_0 ) { rtb_B_26_16_0 = rtb_B_26_5_0 ; }
rtb_B_26_19_0 = - 0.010421968635193955 * rtb_B_26_4_0 / ( rtb_B_26_4_0 -
rtb_B_26_16_0 ) * rtb_B_26_16_0 ; rtb_B_26_20_0 = - _rtB -> B_26_9_0 *
0.010421968635193955 * _rtB -> B_26_7_0 * rtb_B_26_4_0 / ( rtb_B_26_4_0 -
rtb_B_26_16_0 ) ; rtb_B_26_21_0 = _rtP -> P_54 * rtb_B_26_4_0 ; if ( ! ( _rtB
-> B_26_12_0 > rtb_B_26_21_0 ) ) { rtb_B_26_5_0 = - rtb_B_26_21_0 * 0.999 *
0.1 * 0.9999 ; if ( _rtB -> B_26_12_0 < rtb_B_26_5_0 ) { rtb_B_26_21_0 =
rtb_B_26_5_0 ; } else { rtb_B_26_21_0 = _rtB -> B_26_12_0 ; } } } isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_26_26_0 = ( _rtB
-> B_26_7_0 < power_FCHPS_MEA_rtC ( S ) -> B_26_1_0 ) ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { switch ( ( int32_T ) _rtB
-> B_26_43_0_n ) { case 1 : rtb_B_26_31_0 = - ( _rtB -> B_26_47_0 * _rtB ->
B_26_26_0 ) * 0.010421968635193955 * ( _rtB -> B_26_47_0 * _rtB -> B_26_7_0 )
* ( 41.519999999999875 / ( _rtB -> B_26_47_0 * rtb_B_26_21_0 +
4.1519999999999877 ) ) ; break ; case 2 : rtb_B_26_31_0 = _rtB -> B_26_44_0_p
* rtb_B_26_4_0 ; rtb_B_26_31_0 = - ( _rtB -> B_26_44_0_p * _rtB -> B_26_26_0
) * 0.010421968635193955 * ( _rtB -> B_26_44_0_p * _rtB -> B_26_7_0 ) *
rtb_B_26_31_0 / ( _rtB -> B_26_44_0_p * rtb_B_26_21_0 + rtb_B_26_31_0 * 0.1 )
; break ; case 3 : rtb_B_26_31_0 = - ( _rtB -> B_26_46_0_j * _rtB ->
B_26_26_0 ) * 0.010421968635193955 * ( _rtB -> B_26_46_0_j * _rtB -> B_26_7_0
) * ( 41.519999999999875 / ( muDoubleScalarAbs ( _rtB -> B_26_46_0_j *
rtb_B_26_21_0 ) + 4.1519999999999877 ) ) ; break ; default : rtb_B_26_31_0 =
- ( _rtB -> B_26_45_0_l * _rtB -> B_26_26_0 ) * 0.010421968635193955 * ( _rtB
-> B_26_45_0_l * _rtB -> B_26_7_0 ) * ( 41.519999999999875 / (
muDoubleScalarAbs ( _rtB -> B_26_45_0_l * rtb_B_26_21_0 ) +
4.1519999999999877 ) ) ; break ; } } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if
( isHit != 0 ) { _rtB -> B_26_32_0 = _rtDW -> DiscreteTimeIntegrator_DSTATE ;
} isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { switch ( (
int32_T ) _rtB -> B_26_48_0 ) { case 1 : rtb_B_26_37_0 = _rtB -> B_26_32_0 ;
break ; case 2 : if ( rtb_B_26_16_0 > _rtP -> P_24 ) { rtb_B_26_37_0 = _rtP
-> P_24 ; } else if ( rtb_B_26_16_0 < _rtP -> P_25 ) { rtb_B_26_37_0 = _rtP
-> P_25 ; } else { rtb_B_26_37_0 = rtb_B_26_16_0 ; } rtb_B_26_37_0 =
muDoubleScalarExp ( - 1.5306122448979591 * rtb_B_26_37_0 ) *
3.5357645420568784 ; break ; case 3 : rtb_B_26_37_0 = _rtB -> B_26_32_0 ;
break ; default : rtb_B_26_37_0 = _rtB -> B_26_32_0 ; break ; } rtb_B_26_37_0
= ( ( ( ( rtb_B_26_19_0 + rtb_B_26_20_0 ) + rtb_B_26_31_0 ) + rtb_B_26_37_0 )
+ - 0.0 * rtb_B_26_16_0 ) + _rtB -> B_26_39_0_g ; rtb_B_26_38_0 = (
rtb_B_26_37_0 > _rtB -> B_26_40_0 ) ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ;
if ( isHit != 0 ) { _rtB -> B_26_39_0 = _rtDW -> Memory2_PreviousInput ; }
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( rtb_B_26_38_0
) { _rtB -> B_26_41_0 = _rtB -> B_26_40_0 ; } else if ( rtb_B_26_37_0 < _rtB
-> B_26_39_0 ) { _rtB -> B_26_41_0 = _rtB -> B_26_39_0 ; } else { _rtB ->
B_26_41_0 = rtb_B_26_37_0 ; } } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if (
isHit != 0 ) { _rtB -> B_26_42_0 = _rtDW -> UnitDelay2_DSTATE ; _rtB ->
B_26_43_0 = _rtDW -> UnitDelay3_DSTATE ; _rtB -> B_26_44_0 = _rtDW ->
UnitDelay2_DSTATE_m ; _rtB -> B_26_45_0 = _rtP -> P_61 * _rtDW ->
Celldynamic_states ; _rtB -> B_26_46_0 = _rtDW -> UnitDelay_DSTATE_a ;
rtb_B_26_49_0 = 1.0311642900000002E+10 * _rtB -> B_26_46_0 /
2.2438542634362938E+10 ; if ( rtb_B_26_49_0 > _rtP -> P_65 ) { rtb_B_26_49_0
= _rtP -> P_65 ; } else { if ( rtb_B_26_49_0 < _rtP -> P_66 ) { rtb_B_26_49_0
= _rtP -> P_66 ; } } if ( rtb_B_26_49_0 > _rtP -> P_67 ) { rtb_B_26_49_0 =
_rtP -> P_67 ; } else { if ( rtb_B_26_49_0 < _rtP -> P_68 ) { rtb_B_26_49_0 =
_rtP -> P_68 ; } } rtb_B_26_50_0 = 3.9E+6 * _rtB -> B_26_46_0 * 8.3145 * _rtB
-> B_26_92_0 / ( 192970.0 * _rtB -> B_26_88_0 * 101325.0 * rtb_B_26_49_0 *
_rtB -> B_26_85_0 ) ; if ( _rtB -> B_26_83_0 > _rtP -> P_69 ) { _rtB ->
B_26_51_0 = rtb_B_26_49_0 ; } else { _rtB -> B_26_51_0 = rtb_B_26_50_0 ; } if
( _rtB -> B_26_51_0 > _rtP -> P_70 ) { _rtB -> B_26_52_0 = _rtP -> P_70 ; }
else if ( _rtB -> B_26_51_0 < _rtP -> P_71 ) { _rtB -> B_26_52_0 = _rtP ->
P_71 ; } else { _rtB -> B_26_52_0 = _rtB -> B_26_51_0 ; } } _rtB -> B_26_53_0
= 0.0 ; _rtB -> B_26_53_0 += _rtP -> P_73 * _rtX -> Airblowerdelay2_CSTATE ;
if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Saturation4_MODE = _rtB ->
B_26_53_0 >= _rtP -> P_74 ? 1 : _rtB -> B_26_53_0 > _rtP -> P_75 ? 0 : - 1 ;
} _rtB -> B_26_54_0 = _rtDW -> Saturation4_MODE == 1 ? _rtP -> P_74 : _rtDW
-> Saturation4_MODE == - 1 ? _rtP -> P_75 : _rtB -> B_26_53_0 ; if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Saturation3_MODE = _rtB ->
B_26_54_0 >= _rtP -> P_76 ? 1 : _rtB -> B_26_54_0 > _rtP -> P_77 ? 0 : - 1 ;
} rtb_B_26_31_0 = 3.9E+6 * _rtB -> B_26_46_0 * 8.3145 * _rtB -> B_26_92_0 / (
385940.0 * _rtB -> B_26_90_0 * 101325.0 * ( _rtDW -> Saturation3_MODE == 1 ?
_rtP -> P_76 : _rtDW -> Saturation3_MODE == - 1 ? _rtP -> P_77 : _rtB ->
B_26_54_0 ) * _rtB -> B_26_86_0_f ) ; if ( _rtB -> B_26_84_0_j > _rtP -> P_78
) { _rtB -> B_26_57_0 = _rtB -> B_26_54_0 ; } else { _rtB -> B_26_57_0 =
rtb_B_26_31_0 ; } if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
Saturation4_MODE_n = _rtB -> B_26_57_0 >= _rtP -> P_79 ? 1 : _rtB ->
B_26_57_0 > _rtP -> P_80 ? 0 : - 1 ; } rtb_B_26_37_0 = _rtDW ->
Saturation4_MODE_n == 1 ? _rtP -> P_79 : _rtDW -> Saturation4_MODE_n == - 1 ?
_rtP -> P_80 : _rtB -> B_26_57_0 ; _rtB -> B_26_59_0 = _rtB -> B_26_92_0 ;
_rtB -> B_26_60_0 = ( 1.0 - _rtB -> B_26_52_0 ) * _rtB -> B_26_85_0 * _rtB ->
B_26_88_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Saturation1_MODE =
_rtB -> B_26_60_0 >= _rtP -> P_81 ? 1 : _rtB -> B_26_60_0 > _rtP -> P_82 ? 0
: - 1 ; } rtb_B_26_19_0 = _rtDW -> Saturation1_MODE == 1 ? _rtP -> P_81 :
_rtDW -> Saturation1_MODE == - 1 ? _rtP -> P_82 : _rtB -> B_26_60_0 ; _rtB ->
B_26_62_0 = ( 1.0 - rtb_B_26_37_0 ) * _rtB -> B_26_86_0_f * _rtB -> B_26_90_0
; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Saturation4_MODE_nx = _rtB
-> B_26_62_0 >= _rtP -> P_83 ? 1 : _rtB -> B_26_62_0 > _rtP -> P_84 ? 0 : - 1
; } rtb_B_26_20_0 = _rtDW -> Saturation4_MODE_nx == 1 ? _rtP -> P_83 : _rtDW
-> Saturation4_MODE_nx == - 1 ? _rtP -> P_84 : _rtB -> B_26_62_0 ; _rtB ->
B_26_64_0 = ( 2.0 * _rtB -> B_26_86_0_f * rtb_B_26_37_0 + 0.01 ) * _rtB ->
B_26_90_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Saturation5_MODE =
_rtB -> B_26_64_0 >= _rtP -> P_85 ? 1 : _rtB -> B_26_64_0 > _rtP -> P_86 ? 0
: - 1 ; _rtDW -> Switch_Mode = ( _rtB -> B_26_59_0 >= _rtP -> P_87 ) ; } _rtB
-> B_26_65_0 = _rtDW -> Saturation5_MODE == 1 ? _rtP -> P_85 : _rtDW ->
Saturation5_MODE == - 1 ? _rtP -> P_86 : _rtB -> B_26_64_0 ; if (
rtb_B_26_20_0 < 0.0 ) { rtb_B_26_37_0 = - muDoubleScalarSqrt ( -
rtb_B_26_20_0 ) ; } else { rtb_B_26_37_0 = muDoubleScalarSqrt ( rtb_B_26_20_0
) ; } if ( _rtDW -> Switch_Mode ) { tmp = _rtB -> B_26_65_0 ; } else { tmp =
_rtB -> B_26_82_0 ; } rtb_B_26_37_0 = rtb_B_26_19_0 * rtb_B_26_37_0 / tmp ;
if ( ssIsMajorTimeStep ( S ) != 0 ) { if ( _rtDW -> NerstVoltage_DWORK1 != 0
) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; _rtDW ->
NerstVoltage_DWORK1 = 0 ; } } else { if ( rtb_B_26_37_0 < 0.0 ) {
rtb_B_26_37_0 = 0.0 ; _rtDW -> NerstVoltage_DWORK1 = 1 ; } } rtb_B_26_37_0 =
( ( _rtB -> B_26_59_0 - 298.15 ) * - 0.00023024304296004561 + 1.229 ) +
8.3145 * _rtB -> B_26_59_0 / 192970.0 * muDoubleScalarLog ( rtb_B_26_37_0 ) ;
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Compare_Mode = ( _rtB -> B_26_57_0
> _rtB -> B_26_77_0_b ) ; } _rtB -> B_26_69_0 = _rtDW -> Compare_Mode ; }
rtb_B_26_37_0 = ( rtb_B_26_37_0 - ( _rtB -> B_26_57_0 - 0.4288457324020854 )
* 2.0 / 7.8193997606410246 ) * _rtB -> B_26_69_0 + ( 1.0 - _rtB -> B_26_69_0
) * rtb_B_26_37_0 ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) {
if ( _rtB -> B_26_46_0 > _rtP -> P_88 ) { _rtB -> B_26_71_0 = _rtP -> P_88 ;
} else if ( _rtB -> B_26_46_0 < _rtP -> P_89 ) { _rtB -> B_26_71_0 = _rtP ->
P_89 ; } else { _rtB -> B_26_71_0 = _rtB -> B_26_46_0 ; } _rtB -> B_26_73_0 =
( _rtB -> B_26_71_0 > _rtB -> B_26_79_0_e ) ; } rtb_B_26_37_0 =
muDoubleScalarCos ( ( _rtB -> B_26_71_0 / 320.0 - 1.0 ) * 7.8539816339744828
) * rtb_B_26_37_0 * _rtB -> B_26_73_0 + ( 1.0 - _rtB -> B_26_73_0 ) *
rtb_B_26_37_0 ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) {
_rtB -> B_26_75_0 = ( uint8_T ) ( _rtB -> B_26_46_0 > power_FCHPS_MEA_rtC ( S
) -> B_26_3_0 ) ; } _rtB -> B_26_76_0 [ 0 ] = ( real_T ) _rtB -> B_26_75_0 *
_rtB -> B_26_57_0 ; _rtB -> B_26_76_0 [ 1 ] = ( real_T ) _rtB -> B_26_75_0 *
_rtB -> B_26_51_0 ; _rtB -> B_26_77_0 [ 0 ] = _rtP -> P_90 [ 0 ] * _rtB ->
B_26_76_0 [ 0 ] ; _rtB -> B_26_77_0 [ 1 ] = _rtP -> P_90 [ 1 ] * _rtB ->
B_26_76_0 [ 1 ] ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtB -> B_26_78_0 =
_rtB -> B_26_77_0 [ 0 ] ; _rtDW -> MinMax_MODE = 0 ; if ( _rtB -> B_26_77_0 [
1 ] > _rtB -> B_26_77_0 [ 0 ] ) { _rtB -> B_26_78_0 = _rtB -> B_26_77_0 [ 1 ]
; _rtDW -> MinMax_MODE = 1 ; } _rtDW -> Saturation2_MODE = _rtB -> B_26_78_0
>= _rtP -> P_91 ? 1 : _rtB -> B_26_78_0 > _rtP -> P_92 ? 0 : - 1 ; } else {
_rtB -> B_26_78_0 = _rtB -> B_26_77_0 [ _rtDW -> MinMax_MODE ] ; } _rtB ->
B_26_79_0 = _rtDW -> Saturation2_MODE == 1 ? _rtP -> P_91 : _rtDW ->
Saturation2_MODE == - 1 ? _rtP -> P_92 : _rtB -> B_26_78_0 ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S
) != 0 ) { _rtDW -> Compare_Mode_h = ( _rtB -> B_26_79_0 > _rtB ->
B_26_78_0_d ) ; } _rtB -> B_26_81_0 = _rtDW -> Compare_Mode_h ; } _rtB ->
B_26_84_0 = ( muDoubleScalarCos ( ( _rtB -> B_26_79_0 - 1.0 ) *
7.8539816339744828 ) * rtb_B_26_37_0 * _rtB -> B_26_81_0 + ( 1.0 - _rtB ->
B_26_81_0 ) * rtb_B_26_37_0 ) * _rtP -> P_93 + _rtB -> B_26_45_0 ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S
) != 0 ) { _rtDW -> LowerRelop1_Mode = ( _rtB -> B_26_84_0 > _rtB ->
B_26_80_0 ) ; } _rtB -> B_26_85_0_m = _rtDW -> LowerRelop1_Mode ; } isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_26_86_0 = _rtP ->
P_94 * _rtB -> B_26_46_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit
!= 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> UpperRelop_Mode = (
_rtB -> B_26_84_0 < _rtB -> B_26_86_0 ) ; } _rtB -> B_26_87_0 = _rtDW ->
UpperRelop_Mode ; } if ( _rtB -> B_26_85_0_m ) { _rtB -> B_26_89_0 = _rtB ->
B_26_80_0 ; } else if ( _rtB -> B_26_87_0 ) { _rtB -> B_26_89_0 = _rtB ->
B_26_86_0 ; } else { _rtB -> B_26_89_0 = _rtB -> B_26_84_0 ; } isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { rtb_B_26_92_0 = _rtDW ->
DiscreteTimeIntegrator_DSTATE_f + _rtB -> B_26_94_0 ; if ( rtb_B_26_92_0 >
_rtP -> P_97 ) { rtb_B_26_92_0 = _rtP -> P_97 ; } else { if ( rtb_B_26_92_0 <
_rtP -> P_98 ) { rtb_B_26_92_0 = _rtP -> P_98 ; } } rtb_B_26_97_0 =
5.5496029969229008 / rtb_B_26_92_0 * muDoubleScalarAsinh (
0.0071777299424921562 * rtb_B_26_92_0 ) + _rtB -> B_26_100_0_j ; _rtB ->
B_26_98_0 = rtb_B_26_92_0 * rtb_B_26_97_0 ; _rtB -> B_26_99_0 = _rtDW ->
UnitDelay_DSTATE_c ; _rtB -> B_26_100_0 = _rtDW -> UnitDelay3_DSTATE_c ; _rtB
-> B_26_101_0 = _rtDW -> UnitDelay2_DSTATE_e ; _rtB -> B_26_102_0 = _rtDW ->
UnitDelay3_DSTATE_l ; ssCallAccelRunBlock ( S , 26 , 103 ,
SS_CALL_MDL_OUTPUTS ) ; rtb_B_26_92_0 = _rtP -> P_113 * _rtB -> B_26_103_0 [
14 ] ; rtb_B_26_111_0 = _rtP -> P_114 * _rtB -> B_26_103_0 [ 15 ] ; _rtB ->
B_26_113_0 = ( rtb_B_26_92_0 >= _rtP -> P_115 * rtb_B_26_111_0 ) ; } _rtB ->
B_26_114_0 = ssGetT ( S ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit
!= 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
RelationalOperator_Mode = ( _rtB -> B_26_114_0 >= _rtB -> B_26_3_0_c ) ; }
rtb_B_26_115_0 = _rtDW -> RelationalOperator_Mode ; } isHit = ssIsSampleHit (
S , 2 , 0 ) ; if ( isHit != 0 ) { rtb_B_26_117_0 = _rtP -> P_117 * _rtB ->
B_26_103_0 [ 33 ] ; _rtB -> B_26_120_0 = _rtP -> P_118 * _rtB -> B_26_103_0 [
26 ] ; rtb_B_26_121_0 = _rtB -> B_26_67_0 - _rtB -> B_26_120_0 ;
rtb_B_26_125_0 = _rtP -> P_119 * rtb_B_26_121_0 + _rtDW ->
DiscreteTimeIntegrator_DSTATE_n ; if ( rtb_B_26_125_0 > _rtP -> P_124 ) {
rtb_B_26_125_0 = _rtP -> P_124 ; } else { if ( rtb_B_26_125_0 < _rtP -> P_125
) { rtb_B_26_125_0 = _rtP -> P_125 ; } } if ( _rtB -> B_26_120_0 >= _rtB ->
B_26_62_0_b ) { _rtB -> B_26_129_0 = _rtB -> B_26_63_0 ; } else if ( _rtB ->
B_26_120_0 <= _rtB -> B_26_64_0_n ) { _rtB -> B_26_129_0 = _rtB -> B_26_61_0
; } else { _rtB -> B_26_129_0 = _rtDW -> UnitDelay_DSTATE_m ; } if ( _rtB ->
B_26_129_0 > _rtP -> P_127 ) { if ( rtb_B_26_125_0 > _rtP -> P_26 ) { _rtB ->
B_26_131_0 = _rtP -> P_26 ; } else if ( rtb_B_26_125_0 < _rtP -> P_27 ) {
_rtB -> B_26_131_0 = _rtP -> P_27 ; } else { _rtB -> B_26_131_0 =
rtb_B_26_125_0 ; } } else { _rtB -> B_26_131_0 = _rtB -> B_26_52_0_g ; } _rtB
-> B_26_132_0 = rtb_B_26_92_0 * _rtB -> B_26_4_0 / ( ( ( -
0.00493827160493827 * rtb_B_26_117_0 + 0.88888888888888884 ) * ( real_T ) (
rtb_B_26_117_0 >= 9.0 ) + ( real_T ) ( rtb_B_26_117_0 < 9.0 ) * 0.88 ) * (
_rtP -> P_116 * _rtB -> B_26_103_0 [ 16 ] ) + 0.1 ) * ( real_T ) (
rtb_B_26_117_0 > 20.0 ) + ( real_T ) ( rtb_B_26_117_0 <= 20.0 ) * _rtB ->
B_26_131_0 ; _rtB -> B_26_133_0 = ( _rtB -> B_26_132_0 >= _rtB -> B_26_6_0 )
; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { rtb_B_26_135_0
= ( _rtB -> B_26_113_0 || ( _rtB -> B_26_7_0_j && rtb_B_26_115_0 && _rtB ->
B_26_133_0 ) ) ; _rtB -> B_26_136_0 = rtb_B_26_135_0 ; _rtB -> B_26_140_0 =
rtb_B_26_135_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) {
_rtB -> B_26_144_0 = _rtP -> P_128 * _rtB -> B_26_103_0 [ 32 ] ; if ( _rtB ->
B_26_129_0 > _rtP -> P_133 ) { _rtB -> B_26_152_0 = _rtB -> B_26_67_0 ; }
else { _rtB -> B_26_152_0 = _rtB -> B_26_53_0_l ; } rtb_B_26_153_0 = _rtB ->
B_26_152_0 - rtb_B_26_92_0 ; _rtB -> B_26_155_0 = _rtP -> P_135 *
rtb_B_26_153_0 ; rtb_B_26_153_0 = _rtP -> P_134 * rtb_B_26_153_0 + _rtDW ->
DiscreteTimeIntegrator_DSTATE_p ; if ( rtb_B_26_153_0 > _rtP -> P_136 ) {
rtb_B_26_153_0 = _rtP -> P_136 ; } else { if ( rtb_B_26_153_0 < _rtP -> P_137
) { rtb_B_26_153_0 = _rtP -> P_137 ; } } rtb_B_26_158_0 = _rtDW ->
DiscreteTimeIntegrator_DSTATE_o ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if
( isHit != 0 ) { rtb_B_26_159_0 = _rtB -> B_26_132_0 * ( real_T )
rtb_B_26_135_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) {
rtb_B_26_37_0 = ( ( - 0.00493827160493827 * rtb_B_26_117_0 +
0.88888888888888884 ) * ( real_T ) ( rtb_B_26_117_0 >= 9.0 ) + ( real_T ) (
rtb_B_26_117_0 < 9.0 ) * 0.88 ) * rtb_B_26_111_0 ; if ( rtb_B_26_37_0 > _rtP
-> P_142 ) { rtb_B_26_37_0 = _rtP -> P_142 ; } else { if ( rtb_B_26_37_0 <
_rtP -> P_143 ) { rtb_B_26_37_0 = _rtP -> P_143 ; } } _rtB -> B_26_165_0 = (
rtb_B_26_153_0 + rtb_B_26_117_0 ) * ( rtb_B_26_92_0 / rtb_B_26_37_0 ) ; }
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { rtb_B_26_166_0 = (
_rtB -> B_26_165_0 > rtb_B_26_159_0 ) ; } isHit = ssIsSampleHit ( S , 2 , 0 )
; if ( isHit != 0 ) { if ( _rtB -> B_26_165_0 < _rtB -> B_26_2_0_k ) { _rtB
-> B_26_168_0 = _rtB -> B_26_2_0_k ; } else { _rtB -> B_26_168_0 = _rtB ->
B_26_165_0 ; } } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if
( ! rtb_B_26_166_0 ) { rtb_B_26_159_0 = _rtB -> B_26_168_0 ; } _rtB ->
B_26_170_0 = rtb_B_26_159_0 - _rtB -> B_26_144_0 ; } isHit = ssIsSampleHit (
S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_26_172_0 = _rtP -> P_145 * _rtB
-> B_26_170_0 ; rtb_B_26_37_0 = _rtP -> P_144 * _rtB -> B_26_170_0 +
rtb_B_26_158_0 ; if ( rtb_B_26_37_0 > _rtP -> P_146 ) { rtb_B_26_37_0 = _rtP
-> P_146 ; } else { if ( rtb_B_26_37_0 < _rtP -> P_147 ) { rtb_B_26_37_0 =
_rtP -> P_147 ; } } if ( rtb_B_26_92_0 > _rtP -> P_148 ) { rtb_B_26_179_0 =
_rtP -> P_148 ; } else if ( rtb_B_26_92_0 < _rtP -> P_149 ) { rtb_B_26_179_0
= _rtP -> P_149 ; } else { rtb_B_26_179_0 = rtb_B_26_92_0 ; } rtb_B_26_179_0
= _rtB -> B_26_1_0_c - ( rtb_B_26_111_0 - rtb_B_26_37_0 ) / rtb_B_26_179_0 ;
if ( rtb_B_26_179_0 > _rtP -> P_150 ) { rtb_B_26_179_0 = _rtP -> P_150 ; }
else { if ( rtb_B_26_179_0 < _rtP -> P_151 ) { rtb_B_26_179_0 = _rtP -> P_151
; } } _rtB -> B_26_180_0 = ( 1.0 - rtb_B_26_179_0 ) * rtb_B_26_92_0 ; _rtB ->
B_26_182_0 = ( ( - 0.00493827160493827 * rtb_B_26_117_0 + 0.88888888888888884
) * ( real_T ) ( rtb_B_26_117_0 >= 9.0 ) + ( real_T ) ( rtb_B_26_117_0 < 9.0
) * 0.88 ) * ( 1.0 - rtb_B_26_179_0 ) * _rtB -> B_26_144_0 ; rtb_B_26_37_0 =
_rtP -> P_152 * rtb_B_26_125_0 ; if ( rtb_B_26_37_0 > _rtP -> P_153 ) {
rtb_B_26_37_0 = _rtP -> P_153 ; } else { if ( rtb_B_26_37_0 < _rtP -> P_154 )
{ rtb_B_26_37_0 = _rtP -> P_154 ; } } _rtB -> B_26_222_0 = ( ( rtb_B_26_37_0
- _rtDW -> UnitDelay_DSTATE_k ) * _rtP -> P_156 + _rtP -> P_157 * _rtDW ->
UnitDelay_DSTATE_k ) * _rtP -> P_158 ; if ( _rtB -> B_26_129_0 > _rtP ->
P_159 ) { _rtB -> B_26_223_0 = _rtB -> B_26_222_0 ; } else { _rtB ->
B_26_223_0 = _rtB -> B_26_50_0 ; } rtb_B_26_179_0 = _rtP -> P_160 * _rtB ->
B_26_103_0 [ 34 ] ; rtb_B_26_229_0 = _rtP -> P_161 * _rtB -> B_26_103_0 [ 35
] ; rtb_B_26_117_0 = _rtP -> P_166 * _rtB -> B_26_103_0 [ 17 ] ;
rtb_B_26_125_0 = ( real_T ) ( _rtB -> B_26_223_0 > _rtB -> B_26_8_0 ) * (
_rtB -> B_26_51_0_d - rtb_B_26_117_0 ) ; _rtB -> B_26_238_0 = _rtP -> P_168 *
rtb_B_26_125_0 ; rtb_B_26_37_0 = _rtP -> P_167 * rtb_B_26_125_0 + _rtDW ->
DiscreteTimeIntegrator_DSTATE_c ; if ( rtb_B_26_37_0 > _rtP -> P_169 ) {
rtb_B_26_37_0 = _rtP -> P_169 ; } else { if ( rtb_B_26_37_0 < _rtP -> P_170 )
{ rtb_B_26_37_0 = _rtP -> P_170 ; } } rtb_B_26_125_0 = rtb_B_26_37_0 +
rtb_B_26_179_0 ; if ( rtb_B_26_125_0 > _rtB -> B_26_223_0 ) { rtb_B_26_125_0
= _rtB -> B_26_223_0 ; } else { if ( rtb_B_26_125_0 < _rtB -> B_26_9_0_b ) {
rtb_B_26_125_0 = _rtB -> B_26_9_0_b ; } } rtb_B_26_92_0 = rtb_B_26_125_0 -
rtb_B_26_229_0 ; _rtB -> B_26_248_0 = _rtP -> P_176 * rtb_B_26_92_0 ;
rtb_B_26_125_0 = _rtP -> P_179 * _rtB -> B_26_103_0 [ 18 ] ; rtb_B_26_37_0 =
_rtP -> P_175 * rtb_B_26_92_0 + _rtDW -> DiscreteTimeIntegrator_DSTATE_fi ;
if ( rtb_B_26_37_0 > _rtP -> P_177 ) { rtb_B_26_37_0 = _rtP -> P_177 ; } else
{ if ( rtb_B_26_37_0 < _rtP -> P_178 ) { rtb_B_26_37_0 = _rtP -> P_178 ; } }
if ( rtb_B_26_125_0 > _rtP -> P_180 ) { rtb_B_26_92_0 = _rtP -> P_180 ; }
else if ( rtb_B_26_125_0 < _rtP -> P_181 ) { rtb_B_26_92_0 = _rtP -> P_181 ;
} else { rtb_B_26_92_0 = rtb_B_26_125_0 ; } rtb_B_26_117_0 = ( rtb_B_26_37_0
+ rtb_B_26_117_0 ) / rtb_B_26_92_0 ; if ( rtb_B_26_117_0 > _rtP -> P_182 ) {
rtb_B_26_117_0 = _rtP -> P_182 ; } else { if ( rtb_B_26_117_0 < _rtP -> P_183
) { rtb_B_26_117_0 = _rtP -> P_183 ; } } _rtB -> B_26_256_0 = rtb_B_26_117_0
* rtb_B_26_125_0 ; rtb_B_26_37_0 = ( - 0.0044444444444444418 * rtb_B_26_179_0
+ 0.88888888888888884 ) * ( real_T ) ( rtb_B_26_179_0 >= 10.0 ) + ( real_T )
( rtb_B_26_179_0 < 10.0 ) * 0.88 ; if ( rtb_B_26_37_0 > _rtP -> P_184 ) {
rtb_B_26_37_0 = _rtP -> P_184 ; } else { if ( rtb_B_26_37_0 < _rtP -> P_185 )
{ rtb_B_26_37_0 = _rtP -> P_185 ; } } _rtB -> B_26_259_0 = rtb_B_26_117_0 *
rtb_B_26_229_0 / rtb_B_26_37_0 ; rtb_B_26_179_0 = _rtP -> P_186 * _rtB ->
B_26_103_0 [ 19 ] ; rtb_B_26_229_0 = _rtP -> P_187 * _rtB -> B_26_103_0 [ 20
] ; _rtB -> B_26_288_0 = ( rtb_B_26_179_0 >= _rtP -> P_188 * rtb_B_26_229_0 )
; } _rtB -> B_26_289_0 = ssGetT ( S ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ;
if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
RelationalOperator_Mode_h = ( _rtB -> B_26_289_0 >= _rtB -> B_26_12_0_c ) ; }
rtb_B_26_290_0 = _rtDW -> RelationalOperator_Mode_h ; } isHit = ssIsSampleHit
( S , 2 , 0 ) ; if ( isHit != 0 ) { rtb_B_26_292_0 = _rtP -> P_190 * _rtB ->
B_26_103_0 [ 37 ] ; rtb_B_26_294_0 = rtb_B_26_179_0 * _rtB -> B_26_13_0 / ( (
( - 0.001234567901234569 * rtb_B_26_292_0 + 0.90555555555555556 ) * ( real_T
) ( rtb_B_26_292_0 >= 22.5 ) + ( real_T ) ( rtb_B_26_292_0 < 22.5 ) * 0.9 ) *
( _rtP -> P_189 * _rtB -> B_26_103_0 [ 21 ] ) + 0.1 ) ; _rtB -> B_26_296_0 =
_rtP -> P_191 * _rtB -> B_26_103_0 [ 30 ] * _rtB -> B_26_120_0 ; isHit =
ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_26_297_0 = _rtB
-> B_26_296_0 ; } } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
rtb_B_26_37_0 = ( 1.0 - rtb_B_26_16_0 / ( _rtP -> P_192 * rtb_B_26_4_0 ) ) *
100.0 ; if ( rtb_B_26_37_0 > _rtP -> P_193 ) { _rtB -> B_26_300_0 = _rtP ->
P_193 ; } else if ( rtb_B_26_37_0 < _rtP -> P_194 ) { _rtB -> B_26_300_0 =
_rtP -> P_194 ; } else { _rtB -> B_26_300_0 = rtb_B_26_37_0 ; } isHit =
ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_26_301_0 = _rtB
-> B_26_300_0 ; } } isHit = ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) {
_rtB -> B_26_302_0 [ 0 ] = _rtB -> B_26_297_0 ; _rtB -> B_26_302_0 [ 1 ] =
_rtB -> B_26_301_0 ; ssCallAccelRunBlock ( S , 26 , 303 , SS_CALL_MDL_OUTPUTS
) ; _rtB -> B_26_304_0 = _rtP -> P_195 * _rtB -> B_26_303_0 [ 0 ] ; } isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { rtb_B_26_308_0 = _rtB ->
B_26_65_0_b - _rtB -> B_26_120_0 ; rtb_B_26_314_0 = _rtB -> B_26_66_0 - _rtB
-> B_26_120_0 ; rtb_B_26_37_0 = _rtP -> P_196 * _rtB -> B_26_103_0 [ 22 ] ;
rtb_B_26_4_0 = _rtP -> P_199 * rtb_B_26_308_0 + _rtDW ->
DiscreteTimeIntegrator_DSTATE_h ; rtb_B_26_117_0 = _rtP -> P_206 *
rtb_B_26_314_0 + _rtDW -> DiscreteTimeIntegrator_DSTATE_a ; if (
rtb_B_26_37_0 > _rtP -> P_197 ) { rtb_B_26_37_0 = _rtP -> P_197 ; } else { if
( rtb_B_26_37_0 < _rtP -> P_198 ) { rtb_B_26_37_0 = _rtP -> P_198 ; } } if (
rtb_B_26_4_0 > _rtP -> P_204 ) { rtb_B_26_4_0 = _rtP -> P_204 ; } else { if (
rtb_B_26_4_0 < _rtP -> P_205 ) { rtb_B_26_4_0 = _rtP -> P_205 ; } } if (
rtb_B_26_117_0 > _rtP -> P_211 ) { rtb_B_26_117_0 = _rtP -> P_211 ; } else {
if ( rtb_B_26_117_0 < _rtP -> P_212 ) { rtb_B_26_117_0 = _rtP -> P_212 ; } }
rtb_B_26_37_0 = ( _rtB -> B_26_304_0 / rtb_B_26_37_0 + rtb_B_26_4_0 ) +
rtb_B_26_117_0 ; if ( rtb_B_26_37_0 > _rtP -> P_213 ) { _rtB -> B_26_320_0 =
_rtP -> P_213 ; } else if ( rtb_B_26_37_0 < _rtP -> P_214 ) { _rtB ->
B_26_320_0 = _rtP -> P_214 ; } else { _rtB -> B_26_320_0 = rtb_B_26_37_0 ; }
isHit = ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_26_321_0
= _rtB -> B_26_320_0 ; } } isHit = ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit
!= 0 ) { if ( _rtB -> B_26_321_0 <= _rtB -> B_26_54_0_d ) { _rtB ->
B_26_323_0 = _rtB -> B_26_321_0 ; } else { _rtB -> B_26_323_0 = _rtB ->
B_26_54_0_d ; } } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) {
if ( _rtB -> B_26_129_0 > _rtP -> P_215 ) { rtb_B_26_4_0 = _rtB -> B_26_323_0
; } else { rtb_B_26_4_0 = _rtB -> B_26_56_0 ; } rtb_B_26_117_0 = ( _rtB ->
B_26_46_0 + _rtB -> B_26_72_0 ) - _rtB -> B_26_55_0 ; _rtB -> B_26_333_0 = (
( ( ( real_T ) ( rtb_B_26_4_0 < rtb_B_26_117_0 ) * rtb_B_26_4_0 + ( real_T )
( rtb_B_26_4_0 >= rtb_B_26_117_0 ) * rtb_B_26_117_0 ) - _rtDW ->
UnitDelay_DSTATE_l ) * _rtP -> P_217 + _rtP -> P_218 * _rtDW ->
UnitDelay_DSTATE_l ) * _rtP -> P_219 ; _rtB -> B_26_334_0 = ( real_T ) (
rtb_B_26_292_0 > 50.0 ) * rtb_B_26_294_0 + ( real_T ) ( rtb_B_26_292_0 <=
50.0 ) * _rtB -> B_26_333_0 ; _rtB -> B_26_335_0 = ( _rtB -> B_26_334_0 >=
_rtB -> B_26_15_0_f ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit !=
0 ) { rtb_B_26_337_0 = ( _rtB -> B_26_288_0 || ( _rtB -> B_26_16_0 &&
rtb_B_26_290_0 && _rtB -> B_26_335_0 ) ) ; _rtB -> B_26_338_0 =
rtb_B_26_337_0 ; _rtB -> B_26_342_0 = rtb_B_26_337_0 ; } isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_26_346_0 = _rtP
-> P_220 * _rtB -> B_26_103_0 [ 36 ] ; if ( _rtB -> B_26_129_0 > _rtP ->
P_225 ) { tmp = _rtB -> B_26_58_0 ; } else { tmp = _rtB -> B_26_57_0_d ; }
rtb_B_26_294_0 = tmp - rtb_B_26_179_0 ; _rtB -> B_26_357_0 = _rtP -> P_227 *
rtb_B_26_294_0 ; rtb_B_26_359_0 = _rtP -> P_226 * rtb_B_26_294_0 + _rtDW ->
DiscreteTimeIntegrator_DSTATE_g ; if ( rtb_B_26_359_0 > _rtP -> P_228 ) {
rtb_B_26_359_0 = _rtP -> P_228 ; } else { if ( rtb_B_26_359_0 < _rtP -> P_229
) { rtb_B_26_359_0 = _rtP -> P_229 ; } } rtb_B_26_360_0 = _rtDW ->
DiscreteTimeIntegrator_DSTATE_b ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if
( isHit != 0 ) { rtb_B_26_361_0 = _rtB -> B_26_334_0 * ( real_T )
rtb_B_26_337_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) {
rtb_B_26_37_0 = ( ( - 0.001234567901234569 * rtb_B_26_292_0 +
0.90555555555555556 ) * ( real_T ) ( rtb_B_26_292_0 >= 22.5 ) + ( real_T ) (
rtb_B_26_292_0 < 22.5 ) * 0.9 ) * rtb_B_26_229_0 ; if ( rtb_B_26_37_0 > _rtP
-> P_234 ) { rtb_B_26_37_0 = _rtP -> P_234 ; } else { if ( rtb_B_26_37_0 <
_rtP -> P_235 ) { rtb_B_26_37_0 = _rtP -> P_235 ; } } _rtB -> B_26_367_0 = (
rtb_B_26_359_0 + rtb_B_26_292_0 ) * ( rtb_B_26_179_0 / rtb_B_26_37_0 ) ; }
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { rtb_B_26_368_0 = (
_rtB -> B_26_367_0 > rtb_B_26_361_0 ) ; } isHit = ssIsSampleHit ( S , 2 , 0 )
; if ( isHit != 0 ) { if ( _rtB -> B_26_367_0 < _rtB -> B_26_11_0 ) { _rtB ->
B_26_370_0 = _rtB -> B_26_11_0 ; } else { _rtB -> B_26_370_0 = _rtB ->
B_26_367_0 ; } } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if
( ! rtb_B_26_368_0 ) { rtb_B_26_361_0 = _rtB -> B_26_370_0 ; } _rtB ->
B_26_372_0 = rtb_B_26_361_0 - _rtB -> B_26_346_0 ; } isHit = ssIsSampleHit (
S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_26_374_0 = _rtP -> P_237 * _rtB
-> B_26_372_0 ; rtb_B_26_37_0 = _rtP -> P_236 * _rtB -> B_26_372_0 +
rtb_B_26_360_0 ; if ( rtb_B_26_37_0 > _rtP -> P_238 ) { rtb_B_26_37_0 = _rtP
-> P_238 ; } else { if ( rtb_B_26_37_0 < _rtP -> P_239 ) { rtb_B_26_37_0 =
_rtP -> P_239 ; } } if ( rtb_B_26_179_0 > _rtP -> P_240 ) { rtb_B_26_294_0 =
_rtP -> P_240 ; } else if ( rtb_B_26_179_0 < _rtP -> P_241 ) { rtb_B_26_294_0
= _rtP -> P_241 ; } else { rtb_B_26_294_0 = rtb_B_26_179_0 ; } rtb_B_26_361_0
= _rtB -> B_26_10_0_p - ( rtb_B_26_229_0 - rtb_B_26_37_0 ) / rtb_B_26_294_0 ;
if ( rtb_B_26_361_0 > _rtP -> P_242 ) { rtb_B_26_361_0 = _rtP -> P_242 ; }
else { if ( rtb_B_26_361_0 < _rtP -> P_243 ) { rtb_B_26_361_0 = _rtP -> P_243
; } } _rtB -> B_26_382_0 = ( 1.0 - rtb_B_26_361_0 ) * rtb_B_26_179_0 ; _rtB
-> B_26_384_0 = ( ( - 0.001234567901234569 * rtb_B_26_292_0 +
0.90555555555555556 ) * ( real_T ) ( rtb_B_26_292_0 >= 22.5 ) + ( real_T ) (
rtb_B_26_292_0 < 22.5 ) * 0.9 ) * ( 1.0 - rtb_B_26_361_0 ) * _rtB ->
B_26_346_0 ; } _rtB -> B_26_411_0 = ssGetT ( S ) ; isHit = ssIsSampleHit ( S
, 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_26_412_0 = _rtB -> B_26_411_0 ; }
_rtB -> B_26_414_0 = look1_binlxpw ( ssGetT ( S ) , _rtP -> P_245 , _rtP ->
P_244 , 30U ) ; _rtB -> B_26_415_0 = _rtP -> P_246 * _rtB -> B_26_414_0 ;
ssCallAccelRunBlock ( S , 25 , 0 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { { if ( _rtDW ->
TAQSigLogging_InsertedFor_BusCreator12_at_outport_0_1_PWORK . AQHandles [ 0 ]
&& ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_BusCreator12_at_outport_0_1_PWORK . AQHandles [ 0 ]
, ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_25_0_3 + 0 ) ;
sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_BusCreator12_at_outport_0_1_PWORK . AQHandles [ 1 ]
, ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_25_0_4 + 0 ) ; } } }
ssCallAccelRunBlock ( S , 26 , 418 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 26 , 419 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 26 , 420 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Saturation2_MODE_b = _rtB ->
B_26_414_0 >= _rtP -> P_247 ? 1 : _rtB -> B_26_414_0 > _rtP -> P_248 ? 0 : -
1 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
rtb_B_26_428_0 = ( _rtB -> B_26_300_0 <= _rtB -> B_26_59_0_l ) ; } isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_26_429_0 = _rtDW
-> UnitDelay4_DSTATE ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit !=
0 ) { if ( rtb_B_26_428_0 ) { _rtB -> B_26_430_0 = _rtB -> B_26_60_0_o ; }
else { _rtB -> B_26_430_0 = _rtB -> B_26_429_0 ; } rtb_B_26_37_0 = ( ( _rtB
-> B_26_430_0 != 0.0 ) && ( _rtB -> B_26_129_0 != 0.0 ) ) ; if (
rtb_B_26_37_0 > _rtP -> P_250 ) { _rtB -> B_26_433_0 = _rtP -> P_250 ; } else
if ( rtb_B_26_37_0 < _rtP -> P_251 ) { _rtB -> B_26_433_0 = _rtP -> P_251 ; }
else { _rtB -> B_26_433_0 = rtb_B_26_37_0 ; } } rtb_B_26_361_0 = ( _rtDW ->
Saturation2_MODE_b == 1 ? _rtP -> P_247 : _rtDW -> Saturation2_MODE_b == - 1
? _rtP -> P_248 : _rtB -> B_26_414_0 ) * _rtB -> B_26_433_0 * _rtP -> P_252 ;
rtb_B_26_292_0 = rtb_B_26_361_0 * _rtB -> B_26_28_0 ; rtb_B_26_37_0 =
muDoubleScalarPower ( rtb_B_26_361_0 , 2.0 ) - muDoubleScalarPower (
rtb_B_26_292_0 , 2.0 ) ; rtb_B_26_294_0 = _rtP -> P_253 * rtb_B_26_292_0 ; if
( rtb_B_26_37_0 < 0.0 ) { rtb_B_26_37_0 = - muDoubleScalarSqrt ( -
rtb_B_26_37_0 ) ; } else { rtb_B_26_37_0 = muDoubleScalarSqrt ( rtb_B_26_37_0
) ; } rtb_B_26_359_0 = _rtP -> P_254 * rtb_B_26_37_0 ; if ( rtb_B_26_359_0 ==
0.0 ) { rtb_B_26_360_0 = 1.0 / rtb_B_26_294_0 ; rtb_B_26_292_0 = 0.0 ; } else
if ( rtb_B_26_294_0 == 0.0 ) { rtb_B_26_360_0 = 0.0 ; rtb_B_26_292_0 = - (
1.0 / rtb_B_26_359_0 ) ; } else { rtb_B_26_292_0 = muDoubleScalarAbs (
rtb_B_26_294_0 ) ; rtb_B_26_360_0 = muDoubleScalarAbs ( rtb_B_26_359_0 ) ; if
( rtb_B_26_292_0 > rtb_B_26_360_0 ) { rtb_B_26_292_0 = rtb_B_26_359_0 /
rtb_B_26_294_0 ; rtb_B_26_4_0 = rtb_B_26_292_0 * rtb_B_26_359_0 +
rtb_B_26_294_0 ; rtb_B_26_360_0 = 1.0 / rtb_B_26_4_0 ; rtb_B_26_292_0 = - (
rtb_B_26_292_0 / rtb_B_26_4_0 ) ; } else if ( rtb_B_26_360_0 ==
rtb_B_26_292_0 ) { rtb_B_26_360_0 = ( rtb_B_26_294_0 > 0.0 ? 0.5 : - 0.5 ) /
rtb_B_26_292_0 ; rtb_B_26_292_0 = - ( rtb_B_26_359_0 > 0.0 ? 0.5 : - 0.5 ) /
rtb_B_26_292_0 ; } else { rtb_B_26_292_0 = rtb_B_26_294_0 / rtb_B_26_359_0 ;
rtb_B_26_4_0 = rtb_B_26_292_0 * rtb_B_26_294_0 + rtb_B_26_359_0 ;
rtb_B_26_360_0 = rtb_B_26_292_0 / rtb_B_26_4_0 ; rtb_B_26_292_0 = - ( 1.0 /
rtb_B_26_4_0 ) ; } } rtb_B_26_4_0 = rtb_B_26_360_0 * _rtB -> B_26_17_0 ;
rtb_B_26_179_0 = rtb_B_26_292_0 * _rtB -> B_26_17_0 ; isHit = ssIsSampleHit (
S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_26_446_0 [ 0 ] = _rtP -> P_255 *
_rtB -> B_26_3_0 [ 0 ] * _rtP -> P_258 ; _rtB -> B_26_446_0 [ 1 ] = _rtP ->
P_256 * _rtB -> B_26_3_0 [ 1 ] * _rtP -> P_258 ; _rtB -> B_26_446_0 [ 2 ] =
_rtP -> P_257 * _rtB -> B_26_3_0 [ 2 ] * _rtP -> P_258 ; for ( isHit = 0 ;
isHit < 3 ; isHit ++ ) { _rtB -> B_26_448_0 [ isHit ] = _rtP -> P_260 * (
_rtP -> P_259 [ isHit + 6 ] * _rtB -> B_26_446_0 [ 2 ] + ( _rtP -> P_259 [
isHit + 3 ] * _rtB -> B_26_446_0 [ 1 ] + _rtP -> P_259 [ isHit ] * _rtB ->
B_26_446_0 [ 0 ] ) ) ; } } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit
!= 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
RelationalOperator_Mode_g = ( _rtX -> Integrator_CSTATE > _rtB -> B_26_20_0 )
; } _rtB -> B_26_449_0 = _rtDW -> RelationalOperator_Mode_g ; } _rtB ->
B_26_450_0 = _rtX -> Integrator_CSTATE - _rtB -> B_26_20_0 ; if ( ( _rtDW ->
Initial_FirstOutputTime == ( rtMinusInf ) ) || ( _rtDW ->
Initial_FirstOutputTime == ssGetTaskTime ( S , 0 ) ) ) { _rtDW ->
Initial_FirstOutputTime = ssGetTaskTime ( S , 0 ) ; _rtB -> B_26_451_0 = _rtP
-> P_261 ; } else { _rtB -> B_26_451_0 = _rtB -> B_26_450_0 ; } if (
ssIsMajorTimeStep ( S ) != 0 ) { rtb_B_26_13_0 = ( _rtB -> B_26_449_0 && (
_rtZCE -> Integrator_Reset_ZCE != 1 ) ) ; _rtZCE -> Integrator_Reset_ZCE =
_rtB -> B_26_449_0 ; if ( rtb_B_26_13_0 || ( _rtDW -> Integrator_IWORK != 0 )
) { _rtX -> Integrator_CSTATE = _rtB -> B_26_451_0 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } if ( _rtX ->
Integrator_CSTATE >= _rtP -> P_262 ) { if ( _rtX -> Integrator_CSTATE != _rtP
-> P_262 ) { _rtX -> Integrator_CSTATE = _rtP -> P_262 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE = 3 ; } else if ( _rtX -> Integrator_CSTATE <= _rtP -> P_263
) { if ( _rtX -> Integrator_CSTATE != _rtP -> P_263 ) { _rtX ->
Integrator_CSTATE = _rtP -> P_263 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE = 4 ; } else { if ( _rtDW -> Integrator_MODE != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW -> Integrator_MODE
= 0 ; } _rtB -> B_26_452_0 = _rtX -> Integrator_CSTATE ; } else { _rtB ->
B_26_452_0 = _rtX -> Integrator_CSTATE ; } power_FCHPS_MEA_Subsystem1 ( S ,
_rtB -> B_26_31_0 , & _rtB -> B_26_448_0 [ 0 ] , _rtB -> B_26_452_0 , & _rtB
-> Subsystem1_h , & _rtDW -> Subsystem1_h ) ;
power_FCHPS_MEA_Subsystempi2delay ( S , _rtB -> B_26_33_0 , & _rtB ->
B_26_448_0 [ 0 ] , _rtB -> B_26_452_0 , & _rtB -> Subsystempi2delay_b , &
_rtDW -> Subsystempi2delay_b ) ; if ( _rtB -> B_26_31_0 != 0 ) {
rtb_B_26_294_0 = _rtB -> Subsystem1_h . B_3_0_0 ; rtb_B_26_359_0 = _rtB ->
Subsystem1_h . B_3_1_0 ; } else { rtb_B_26_294_0 = _rtB ->
Subsystempi2delay_b . B_2_0_0 ; rtb_B_26_359_0 = _rtB -> Subsystempi2delay_b
. B_2_1_0 ; } if ( - rtb_B_26_179_0 == 0.0 ) { rtb_B_26_360_0 = 1.0 /
rtb_B_26_4_0 ; rtb_B_26_292_0 = 0.0 ; } else if ( rtb_B_26_4_0 == 0.0 ) {
rtb_B_26_360_0 = 0.0 ; rtb_B_26_292_0 = - ( 1.0 / - rtb_B_26_179_0 ) ; } else
{ rtb_B_26_292_0 = muDoubleScalarAbs ( rtb_B_26_4_0 ) ; rtb_B_26_360_0 =
muDoubleScalarAbs ( - rtb_B_26_179_0 ) ; if ( rtb_B_26_292_0 > rtb_B_26_360_0
) { rtb_B_26_292_0 = - rtb_B_26_179_0 / rtb_B_26_4_0 ; rtb_B_26_4_0 +=
rtb_B_26_292_0 * - rtb_B_26_179_0 ; rtb_B_26_360_0 = 1.0 / rtb_B_26_4_0 ;
rtb_B_26_292_0 = - ( rtb_B_26_292_0 / rtb_B_26_4_0 ) ; } else if (
rtb_B_26_360_0 == rtb_B_26_292_0 ) { rtb_B_26_360_0 = ( rtb_B_26_4_0 > 0.0 ?
0.5 : - 0.5 ) / rtb_B_26_292_0 ; rtb_B_26_292_0 = - ( - rtb_B_26_179_0 > 0.0
? 0.5 : - 0.5 ) / rtb_B_26_292_0 ; } else { rtb_B_26_292_0 = rtb_B_26_4_0 / -
rtb_B_26_179_0 ; rtb_B_26_4_0 = rtb_B_26_292_0 * rtb_B_26_4_0 + -
rtb_B_26_179_0 ; rtb_B_26_360_0 = rtb_B_26_292_0 / rtb_B_26_4_0 ;
rtb_B_26_292_0 = - ( 1.0 / rtb_B_26_4_0 ) ; } } rtb_B_26_179_0 =
rtb_B_26_360_0 * rtb_B_26_294_0 - rtb_B_26_292_0 * rtb_B_26_359_0 ;
rtb_B_26_292_0 = rtb_B_26_360_0 * rtb_B_26_359_0 + rtb_B_26_292_0 *
rtb_B_26_294_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
_rtB -> B_26_460_0 = _rtDW -> Memory_PreviousInput ; if ( ssIsMajorTimeStep (
S ) != 0 ) { if ( _rtB -> B_26_19_0 > 0.0 ) { if ( ! _rtDW ->
AutomaticGainControl_MODE ) { if ( ssGetTaskTime ( S , 1 ) != ssGetTStart ( S
) ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } ( void ) memset (
& ( ( ( XDis_power_FCHPS_MEA_T * ) ssGetContStateDisabled ( S ) ) ->
VariableTransportDelay_CSTATE_n ) , 0 , 4 * sizeof ( boolean_T ) ) ; _rtDW ->
AutomaticGainControl_MODE = true ; } } else { if ( ssGetTaskTime ( S , 1 ) ==
ssGetTStart ( S ) ) { ( void ) memset ( & ( ( ( XDis_power_FCHPS_MEA_T * )
ssGetContStateDisabled ( S ) ) -> VariableTransportDelay_CSTATE_n ) , 1 , 4 *
sizeof ( boolean_T ) ) ; } if ( _rtDW -> AutomaticGainControl_MODE ) {
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
_rtDW -> RelationalOperator_Mode_e = ( _rtB -> B_4_2_0 >= _rtB -> B_4_0_0_o )
; } _rtB -> B_4_3_0 = _rtDW -> RelationalOperator_Mode_e ; _rtB -> B_4_4_0 =
_rtDW -> Memory_PreviousInput_i ; } if ( _rtB -> B_4_3_0 ) { _rtB -> B_0_0_0
= _rtB -> B_4_1_0 - _rtB -> B_4_0_0 ; _rtB -> B_0_1_0 = _rtB -> B_0_0_0 *
_rtB -> B_26_460_0 ; _rtB -> B_4_6_0 = _rtB -> B_0_1_0 ; } else { _rtB ->
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
_rtDW -> RelationalOperator_Mode_c = ( _rtB -> B_4_9_0 >= _rtB -> B_4_1_0_n )
; } _rtB -> B_4_10_0 = _rtDW -> RelationalOperator_Mode_c ; _rtB -> B_4_11_0
= _rtDW -> Memory_PreviousInput_l ; } if ( _rtB -> B_4_10_0 ) { _rtB ->
B_1_0_0 = _rtB -> B_4_8_0 - _rtB -> B_4_7_0 ; _rtB -> B_1_1_0 = _rtB ->
B_1_0_0 * _rtB -> B_26_460_0 ; _rtB -> B_4_13_0 = _rtB -> B_1_1_0 ; } else {
_rtB -> B_4_13_0 = _rtB -> B_4_11_0 ; } _rtB -> B_4_14_0 . re = _rtB ->
B_4_6_0 ; _rtB -> B_4_14_0 . im = _rtB -> B_4_13_0 ; _rtB -> B_4_15_0 =
muDoubleScalarHypot ( _rtB -> B_4_14_0 . re , _rtB -> B_4_14_0 . im ) ; if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Saturation_MODE_d = _rtB ->
B_4_15_0 >= _rtP -> P_9 ? 1 : _rtB -> B_4_15_0 > _rtP -> P_10 ? 0 : - 1 ; }
_rtB -> B_4_16_0 = _rtDW -> Saturation_MODE_d == 1 ? _rtP -> P_9 : _rtDW ->
Saturation_MODE_d == - 1 ? _rtP -> P_10 : _rtB -> B_4_15_0 ; _rtB -> B_4_17_0
= 1.0 / _rtB -> B_4_16_0 ; if ( _rtB -> B_26_460_0 > _rtP -> P_11 ) { _rtB ->
B_4_18_0 = _rtP -> P_11 ; } else if ( _rtB -> B_26_460_0 < _rtP -> P_12 ) {
_rtB -> B_4_18_0 = _rtP -> P_12 ; } else { _rtB -> B_4_18_0 = _rtB ->
B_26_460_0 ; } _rtB -> B_4_19_0 = 1.0 / _rtB -> B_4_18_0 ; if ( _rtB ->
B_26_460_0 > _rtP -> P_13 ) { _rtB -> B_4_20_0 = _rtP -> P_13 ; } else if (
_rtB -> B_26_460_0 < _rtP -> P_14 ) { _rtB -> B_4_20_0 = _rtP -> P_14 ; }
else { _rtB -> B_4_20_0 = _rtB -> B_26_460_0 ; } _rtB -> B_4_21_0 = 1.0 /
_rtB -> B_4_20_0 ; for ( isHit = 0 ; isHit < 3 ; isHit ++ ) { _rtB ->
B_4_22_0 [ isHit ] = 0.0 ; _rtB -> B_4_22_0 [ isHit ] += _rtP -> P_15 [ isHit
] * _rtB -> B_26_446_0 [ 0 ] ; _rtB -> B_4_22_0 [ isHit ] += _rtP -> P_15 [
isHit + 3 ] * _rtB -> B_26_446_0 [ 1 ] ; _rtB -> B_4_22_0 [ isHit ] += _rtP
-> P_15 [ isHit + 6 ] * _rtB -> B_26_446_0 [ 2 ] ; _rtB -> B_4_23_0 [ isHit ]
= _rtP -> P_16 * _rtB -> B_4_22_0 [ isHit ] ; }
power_FCHPS_MEA_Subsystempi2delay ( S , _rtB -> B_4_6_0_m , & _rtB ->
B_4_23_0 [ 0 ] , _rtB -> B_26_452_0 , & _rtB -> Subsystempi2delay_d , & _rtDW
-> Subsystempi2delay_d ) ; power_FCHPS_MEA_Subsystem1 ( S , _rtB -> B_4_4_0_c
, & _rtB -> B_4_23_0 [ 0 ] , _rtB -> B_26_452_0 , & _rtB -> Subsystem1_i , &
_rtDW -> Subsystem1_i ) ; if ( _rtB -> B_4_4_0_c != 0 ) { _rtB -> B_4_26_0 [
0 ] = _rtB -> Subsystem1_i . B_3_0_0 ; _rtB -> B_4_26_0 [ 1 ] = _rtB ->
Subsystem1_i . B_3_1_0 ; } else { _rtB -> B_4_26_0 [ 0 ] = _rtB ->
Subsystempi2delay_d . B_2_0_0 ; _rtB -> B_4_26_0 [ 1 ] = _rtB ->
Subsystempi2delay_d . B_2_1_0 ; } if ( ssIsMajorTimeStep ( S ) != 0 ) {
srUpdateBC ( _rtDW -> AutomaticGainControl_SubsysRanBC ) ; } } if (
ssIsMajorTimeStep ( S ) != 0 ) { if ( _rtX -> Integrator_CSTATE_g >= _rtP ->
P_267 ) { if ( _rtX -> Integrator_CSTATE_g != _rtP -> P_267 ) { _rtX ->
Integrator_CSTATE_g = _rtP -> P_267 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_g = 3 ; } else if ( _rtX -> Integrator_CSTATE_g <= _rtP ->
P_268 ) { if ( _rtX -> Integrator_CSTATE_g != _rtP -> P_268 ) { _rtX ->
Integrator_CSTATE_g = _rtP -> P_268 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_g = 4 ; } else { if ( _rtDW -> Integrator_MODE_g != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_g = 0 ; } _rtB -> B_26_462_0 = _rtX -> Integrator_CSTATE_g ;
} else { _rtB -> B_26_462_0 = _rtX -> Integrator_CSTATE_g ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> VariableTransportDelay_PWORK .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
VariableTransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T * * xBuffer = (
real_T * * ) & _rtDW -> VariableTransportDelay_PWORK . TUbufferPtrs [ 2 ] ;
real_T simTime = ssGetT ( S ) ; real_T appliedDelay ; _rtB -> B_26_463_0 =
power_FCHPS_MEA_acc_rt_VTDelayfindtDInterpolate ( ( ( X_power_FCHPS_MEA_T * )
ssGetContStates ( S ) ) -> VariableTransportDelay_CSTATE , * tBuffer , *
uBuffer , * xBuffer , _rtDW -> VariableTransportDelay_IWORK . CircularBufSize
, _rtDW -> VariableTransportDelay_IWORK . Head , _rtDW ->
VariableTransportDelay_IWORK . Tail , & _rtDW -> VariableTransportDelay_IWORK
. Last , simTime , 0.0 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) , _rtP -> P_270 , &
appliedDelay ) ; } _rtB -> B_26_464_0 = _rtX -> integrator_CSTATE ; _rtB ->
B_26_465_0 = ssGetT ( S ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit
!= 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
RelationalOperator_Mode_i = ( _rtB -> B_26_465_0 >= _rtB -> B_26_21_0 ) ; }
_rtB -> B_26_466_0 = _rtDW -> RelationalOperator_Mode_i ; _rtB -> B_26_467_0
= _rtDW -> Memory_PreviousInput_g ; } if ( _rtB -> B_26_466_0 ) { _rtB ->
B_5_0_0 = _rtB -> B_26_464_0 - _rtB -> B_26_463_0 ; _rtB -> B_5_1_0 = _rtB ->
B_5_0_0 * _rtB -> B_26_460_0 ; _rtB -> B_26_469_0 = _rtB -> B_5_1_0 ; } else
{ _rtB -> B_26_469_0 = _rtB -> B_26_467_0 ; } _rtB -> B_26_470_0 = _rtB ->
B_26_469_0 * _rtB -> B_4_17_0 ; _rtB -> B_26_471_0 = _rtP -> P_273 * _rtB ->
B_26_470_0 ; _rtB -> B_26_472_0 = _rtP -> P_274 * _rtB -> B_26_470_0 ; _rtB
-> B_26_473_0 = _rtP -> P_275 * _rtB -> B_26_470_0 ; _rtB -> B_26_474_0 = 0.0
; _rtB -> B_26_474_0 += _rtP -> P_277 * _rtX -> TransferFcn_CSTATE ; _rtB ->
B_26_474_0 += _rtP -> P_278 * _rtB -> B_26_473_0 ; _rtB -> B_26_475_0 = (
_rtB -> B_26_471_0 + _rtB -> B_26_462_0 ) + _rtB -> B_26_474_0 ; if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Saturation2_MODE_m = _rtB ->
B_26_475_0 >= _rtP -> P_279 ? 1 : _rtB -> B_26_475_0 > _rtP -> P_280 ? 0 : -
1 ; } _rtB -> B_26_476_0 = _rtDW -> Saturation2_MODE_m == 1 ? _rtP -> P_279 :
_rtDW -> Saturation2_MODE_m == - 1 ? _rtP -> P_280 : _rtB -> B_26_475_0 ;
_rtB -> B_26_477_0 = _rtP -> P_281 * _rtB -> B_26_476_0 ; if ( ( _rtDW ->
LastMajorTimeA >= ssGetTaskTime ( S , 0 ) ) && ( _rtDW -> LastMajorTimeB >=
ssGetTaskTime ( S , 0 ) ) ) { _rtB -> B_26_478_0 = _rtB -> B_26_477_0 ; }
else { if ( ( ( _rtDW -> LastMajorTimeA < _rtDW -> LastMajorTimeB ) && (
_rtDW -> LastMajorTimeB < ssGetTaskTime ( S , 0 ) ) ) || ( ( _rtDW ->
LastMajorTimeA >= _rtDW -> LastMajorTimeB ) && ( _rtDW -> LastMajorTimeA >=
ssGetTaskTime ( S , 0 ) ) ) ) { rtb_B_26_360_0 = ssGetTaskTime ( S , 0 ) -
_rtDW -> LastMajorTimeB ; rtb_B_26_294_0 = _rtDW -> PrevYB ; } else {
rtb_B_26_360_0 = ssGetTaskTime ( S , 0 ) - _rtDW -> LastMajorTimeA ;
rtb_B_26_294_0 = _rtDW -> PrevYA ; } rtb_B_26_4_0 = rtb_B_26_360_0 * _rtP ->
P_282 ; rtb_B_26_359_0 = _rtB -> B_26_477_0 - rtb_B_26_294_0 ; if (
rtb_B_26_359_0 > rtb_B_26_4_0 ) { _rtB -> B_26_478_0 = rtb_B_26_294_0 +
rtb_B_26_4_0 ; } else { rtb_B_26_360_0 *= _rtP -> P_283 ; if ( rtb_B_26_359_0
< rtb_B_26_360_0 ) { _rtB -> B_26_478_0 = rtb_B_26_294_0 + rtb_B_26_360_0 ; }
else { _rtB -> B_26_478_0 = _rtB -> B_26_477_0 ; } } } _rtB -> B_26_479_0 =
_rtX -> Integrator_x1_CSTATE ; _rtB -> B_26_480_0 = _rtP -> P_285 * _rtB ->
B_26_479_0 ; _rtB -> B_26_481_0 = _rtX -> Integrator_x2_CSTATE ; _rtB ->
B_26_482_0 = _rtP -> P_287 * _rtB -> B_26_481_0 ; _rtB -> B_26_483_0 = _rtP
-> P_288 * _rtB -> B_26_479_0 ; _rtB -> B_26_484_0 = _rtP -> P_289 * _rtB ->
B_26_481_0 ; _rtB -> B_26_485_0 = _rtB -> B_26_480_0 + _rtB -> B_26_482_0 ;
_rtB -> B_26_486_0 = _rtB -> B_26_483_0 + _rtB -> B_26_484_0 ; _rtB ->
B_26_487_0 = _rtP -> P_290 * _rtB -> B_26_478_0 ; _rtB -> B_26_488_0 = _rtB
-> B_26_485_0 + _rtB -> B_26_487_0 ; _rtB -> B_26_489_0 = _rtP -> P_291 *
_rtB -> B_26_478_0 ; _rtB -> B_26_490_0 = _rtB -> B_26_486_0 + _rtB ->
B_26_489_0 ; _rtB -> B_26_495_0 = ( _rtP -> P_292 * _rtB -> B_26_479_0 + _rtP
-> P_293 * _rtB -> B_26_481_0 ) + _rtP -> P_294 * _rtB -> B_26_478_0 ; if (
_rtB -> B_26_460_0 > _rtP -> P_295 ) { _rtB -> B_26_496_0 = _rtP -> P_295 ; }
else if ( _rtB -> B_26_460_0 < _rtP -> P_296 ) { _rtB -> B_26_496_0 = _rtP ->
P_296 ; } else { _rtB -> B_26_496_0 = _rtB -> B_26_460_0 ; } _rtB ->
B_26_497_0 = 1.0 / _rtB -> B_26_496_0 ; for ( isHit = 0 ; isHit < 3 ; isHit
++ ) { _rtB -> B_26_498_0 [ isHit ] = 0.0 ; _rtB -> B_26_498_0 [ isHit ] +=
_rtP -> P_297 [ isHit ] * _rtB -> B_26_446_0 [ 0 ] ; _rtB -> B_26_498_0 [
isHit ] += _rtP -> P_297 [ isHit + 3 ] * _rtB -> B_26_446_0 [ 1 ] ; _rtB ->
B_26_498_0 [ isHit ] += _rtP -> P_297 [ isHit + 6 ] * _rtB -> B_26_446_0 [ 2
] ; _rtB -> B_26_499_0 [ isHit ] = _rtP -> P_298 * _rtB -> B_26_498_0 [ isHit
] ; } power_FCHPS_MEA_Subsystempi2delay ( S , _rtB -> B_26_26_0_m , & _rtB ->
B_26_499_0 [ 0 ] , _rtB -> B_26_452_0 , & _rtB -> Subsystempi2delay , & _rtDW
-> Subsystempi2delay ) ; power_FCHPS_MEA_Subsystem1 ( S , _rtB -> B_26_24_0 ,
& _rtB -> B_26_499_0 [ 0 ] , _rtB -> B_26_452_0 , & _rtB -> Subsystem1 , &
_rtDW -> Subsystem1 ) ; if ( _rtB -> B_26_24_0 != 0 ) { _rtB -> B_26_502_0 [
0 ] = _rtB -> Subsystem1 . B_3_0_0 ; _rtB -> B_26_502_0 [ 1 ] = _rtB ->
Subsystem1 . B_3_1_0 ; } else { _rtB -> B_26_502_0 [ 0 ] = _rtB ->
Subsystempi2delay . B_2_0_0 ; _rtB -> B_26_502_0 [ 1 ] = _rtB ->
Subsystempi2delay . B_2_1_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if (
isHit != 0 ) { _rtB -> B_26_506_0 [ 0 ] = _rtP -> P_299 * _rtB -> B_26_3_0 [
5 ] * _rtP -> P_302 ; _rtB -> B_26_506_0 [ 1 ] = _rtP -> P_300 * _rtB ->
B_26_3_0 [ 6 ] * _rtP -> P_302 ; _rtB -> B_26_506_0 [ 2 ] = _rtP -> P_301 *
_rtB -> B_26_3_0 [ 7 ] * _rtP -> P_302 ; } isHit = ssIsSampleHit ( S , 1 , 0
) ; if ( ( isHit != 0 ) && ( ssIsMajorTimeStep ( S ) != 0 ) ) { if ( _rtB ->
B_26_36_0 > 0 ) { if ( ! _rtDW -> Subsystem1_MODE ) { if ( ssGetTaskTime ( S
, 1 ) != ssGetTStart ( S ) ) { ssSetBlockStateForSolverChangedAtMajorStep ( S
) ; } _rtDW -> Subsystem1_MODE = true ; } } else { if ( _rtDW ->
Subsystem1_MODE ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; _rtDW
-> Subsystem1_MODE = false ; } } } if ( _rtDW -> Subsystem1_MODE ) { _rtB ->
B_11_0_0 = rtb_B_26_179_0 * muDoubleScalarCos ( _rtB -> B_26_452_0 ) -
rtb_B_26_292_0 * muDoubleScalarSin ( _rtB -> B_26_452_0 ) ; _rtB -> B_11_1_0
= rtb_B_26_179_0 * muDoubleScalarSin ( _rtB -> B_26_452_0 ) + rtb_B_26_292_0
* muDoubleScalarCos ( _rtB -> B_26_452_0 ) ; if ( ssIsMajorTimeStep ( S ) !=
0 ) { srUpdateBC ( _rtDW -> Subsystem1_SubsysRanBC ) ; } } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( ( isHit != 0 ) && ( ssIsMajorTimeStep ( S
) != 0 ) ) { if ( _rtB -> B_26_38_0 > 0 ) { if ( ! _rtDW ->
Subsystempi2delay_MODE ) { if ( ssGetTaskTime ( S , 1 ) != ssGetTStart ( S )
) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Subsystempi2delay_MODE = true ; } } else { if ( _rtDW ->
Subsystempi2delay_MODE ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
_rtDW -> Subsystempi2delay_MODE = false ; } } } if ( _rtDW ->
Subsystempi2delay_MODE ) { _rtB -> B_10_0_0 = rtb_B_26_179_0 *
muDoubleScalarSin ( _rtB -> B_26_452_0 ) + rtb_B_26_292_0 * muDoubleScalarCos
( _rtB -> B_26_452_0 ) ; _rtB -> B_10_1_0 = - rtb_B_26_179_0 *
muDoubleScalarCos ( _rtB -> B_26_452_0 ) + rtb_B_26_292_0 * muDoubleScalarSin
( _rtB -> B_26_452_0 ) ; if ( ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC (
_rtDW -> Subsystempi2delay_SubsysRanBC ) ; } } if ( _rtB -> B_26_36_0 != 0 )
{ rtb_B_26_294_0 = _rtB -> B_11_0_0 ; rtb_B_26_359_0 = _rtB -> B_11_1_0 ; }
else { rtb_B_26_294_0 = _rtB -> B_10_0_0 ; rtb_B_26_359_0 = _rtB -> B_10_1_0
; } for ( isHit = 0 ; isHit < 3 ; isHit ++ ) { _rtB -> B_26_545_0 [ isHit ] =
0.0 ; _rtB -> B_26_545_0 [ isHit ] += _rtP -> P_303 [ isHit ] *
rtb_B_26_294_0 ; _rtB -> B_26_545_0 [ isHit ] += _rtP -> P_303 [ isHit + 3 ]
* rtb_B_26_359_0 ; _rtB -> B_26_545_0 [ isHit ] += _rtP -> P_303 [ isHit + 6
] * 0.0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB ->
B_26_553_0 = _rtP -> P_304 * _rtB -> B_26_103_0 [ 27 ] ; _rtB -> B_26_557_0 =
_rtP -> P_305 * _rtB -> B_26_553_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ;
if ( isHit != 0 ) { _rtB -> B_26_558_0 = _rtB -> B_26_41_0 - _rtB ->
B_26_557_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB
-> B_26_565_0 = ( ( real_T ) ( _rtB -> B_26_553_0 < power_FCHPS_MEA_rtC ( S )
-> B_26_2_0 ) * _rtP -> P_306 - _rtB -> B_26_32_0 ) * muDoubleScalarAbs (
_rtB -> B_26_553_0 ) * _rtP -> P_307 ; } isHit = ssIsSampleHit ( S , 1 , 0 )
; if ( isHit != 0 ) { _rtB -> B_26_566_0 = _rtP -> P_308 * rtb_B_26_16_0 ; }
isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_26_567_0
= _rtP -> P_309 * _rtB -> B_26_553_0 ; _rtB -> B_26_571_0 = _rtP -> P_310 *
_rtB -> B_26_103_0 [ 29 ] ; _rtB -> B_26_582_0 = _rtP -> P_312 *
rtb_B_26_308_0 ; _rtB -> B_26_583_0 = _rtP -> P_313 * rtb_B_26_314_0 ; _rtB
-> B_26_584_0 = _rtP -> P_314 * rtb_B_26_121_0 ; _rtB -> B_26_585_0 = _rtP ->
P_315 * _rtB -> B_26_103_0 [ 42 ] ; _rtB -> B_26_586_0 = _rtB -> B_26_120_0 *
_rtB -> B_26_585_0 ; _rtB -> B_26_587_0 = _rtP -> P_311 * _rtB -> B_26_103_0
[ 31 ] * _rtB -> B_26_120_0 ; _rtB -> B_26_588_0 = _rtB -> B_26_120_0 * _rtB
-> B_26_571_0 ; if ( _rtB -> B_26_120_0 >= _rtB -> B_26_68_0 ) { _rtB ->
B_26_592_0 = _rtB -> B_26_69_0_l ; } else if ( _rtB -> B_26_120_0 <= _rtB ->
B_26_70_0 ) { _rtB -> B_26_592_0 = _rtB -> B_26_71_0_h ; } else { _rtB ->
B_26_592_0 = _rtDW -> UnitDelay1_DSTATE_f ; } rtb_B_26_37_0 =
1.0311642900000002E+10 * _rtB -> B_26_46_0 / 3.521360402784E+9 + ( real_T ) (
_rtB -> B_26_46_0 <= 100.0 ) * 30.0 ; if ( rtb_B_26_37_0 > _rtP -> P_317 ) {
_rtB -> B_26_596_0 = _rtP -> P_317 ; } else if ( rtb_B_26_37_0 < _rtP ->
P_318 ) { _rtB -> B_26_596_0 = _rtP -> P_318 ; } else { _rtB -> B_26_596_0 =
rtb_B_26_37_0 ; } _rtB -> B_26_600_0 = _rtP -> P_319 * _rtB -> B_26_103_0 [
38 ] ; { if ( _rtDW ->
TAQSigLogging_InsertedFor_Celldynamic_at_outport_0_PWORK . AQHandles &&
ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_Celldynamic_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 2 ) , ( char * ) & _rtB -> B_26_45_0 + 0 ) ; } } _rtB ->
B_26_605_0 = ( _rtB -> B_26_46_0 > _rtB -> B_26_81_0_b ) ; } _rtB ->
B_26_607_0 = ( rtb_B_26_19_0 * 101325.0 + rtb_B_26_20_0 * 101325.0 ) / (
8.3145 * _rtB -> B_26_59_0 ) * ( 2.6629860000000003E-18 * _rtB -> B_26_59_0 )
* muDoubleScalarExp ( - 114559.38331414459 / ( 8.3145 * _rtB -> B_26_59_0 ) )
/ 6.626e-34 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> UpperRelop_Mode_e = ( _rtB ->
B_26_46_0 < _rtB -> B_26_607_0 ) ; } _rtB -> B_26_608_0 = _rtDW ->
UpperRelop_Mode_e ; } if ( _rtB -> B_26_605_0 ) { rtb_B_26_121_0 = _rtB ->
B_26_81_0_b ; } else if ( _rtB -> B_26_608_0 ) { rtb_B_26_121_0 = _rtB ->
B_26_607_0 ; } else { rtb_B_26_121_0 = _rtB -> B_26_46_0 ; } rtb_B_26_308_0 =
8.3145 * _rtB -> B_26_59_0 / 182461.51774658303 ; if ( ssIsMajorTimeStep ( S
) != 0 ) { if ( _rtDW -> Vactivation_DWORK1 != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; _rtDW ->
Vactivation_DWORK1 = 0 ; } } else { if ( rtb_B_26_121_0 < 0.0 ) {
rtb_B_26_121_0 = 0.0 ; _rtDW -> Vactivation_DWORK1 = 1 ; } } rtb_B_26_37_0 =
_rtB -> B_26_607_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { if ( _rtDW ->
Vactivation_DWORK1 != 0 ) { ssSetBlockStateForSolverChangedAtMajorStep ( S )
; ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; _rtDW ->
Vactivation_DWORK1 = 0 ; } } else { if ( _rtB -> B_26_607_0 < 0.0 ) {
rtb_B_26_37_0 = 0.0 ; _rtDW -> Vactivation_DWORK1 = 1 ; } } _rtB ->
B_26_612_0 = - 65.0 * rtb_B_26_308_0 * muDoubleScalarLog ( rtb_B_26_121_0 ) +
65.0 * rtb_B_26_308_0 * muDoubleScalarLog ( rtb_B_26_37_0 ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { { if ( _rtDW ->
TAQSigLogging_InsertedFor_Vactivation_at_outport_0_PWORK . AQHandles &&
ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_Vactivation_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_26_612_0 + 0 ) ; } } } if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Saturation_MODE [ 0 ] = _rtB ->
B_26_76_0 [ 0 ] >= _rtP -> P_320 ? 1 : _rtB -> B_26_76_0 [ 0 ] > _rtP ->
P_321 ? 0 : - 1 ; _rtDW -> Saturation_MODE [ 1 ] = _rtB -> B_26_76_0 [ 1 ] >=
_rtP -> P_320 ? 1 : _rtB -> B_26_76_0 [ 1 ] > _rtP -> P_321 ? 0 : - 1 ; }
rtb_B_26_359_0 = _rtDW -> Saturation_MODE [ 1 ] == 1 ? _rtP -> P_320 : _rtDW
-> Saturation_MODE [ 1 ] == - 1 ? _rtP -> P_321 : _rtB -> B_26_76_0 [ 1 ] ;
isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { if ( _rtB ->
B_26_83_0 > _rtP -> P_323 ) { _rtB -> B_26_616_0 = rtb_B_26_50_0 ; } else {
_rtB -> B_26_616_0 = rtb_B_26_49_0 ; } } _rtB -> B_26_618_0 = _rtB ->
B_26_89_0 - 0.024535460093391727 * _rtB -> B_26_46_0 ; _rtB -> B_26_619_0 =
65.0 * _rtB -> B_26_46_0 / ( 192970.0 * rtb_B_26_359_0 ) * 241830.0 ; _rtB ->
B_26_620_0 = _rtB -> B_26_618_0 * _rtB -> B_26_46_0 ; if ( ! ( _rtB ->
B_26_84_0_j > _rtP -> P_322 ) ) { rtb_B_26_31_0 = _rtB -> B_26_54_0 ; } _rtB
-> B_26_621_0 [ 0 ] = _rtP -> P_324 * rtb_B_26_31_0 * ( _rtDW ->
Saturation_MODE [ 0 ] == 1 ? _rtP -> P_320 : _rtDW -> Saturation_MODE [ 0 ]
== - 1 ? _rtP -> P_321 : _rtB -> B_26_76_0 [ 0 ] ) ; _rtB -> B_26_621_0 [ 1 ]
= _rtP -> P_324 * _rtB -> B_26_616_0 * rtb_B_26_359_0 ; if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> zeroavoider_MODE = _rtB ->
B_26_619_0 >= _rtP -> P_325 ? 1 : _rtB -> B_26_619_0 > _rtP -> P_326 ? 0 : -
1 ; _rtDW -> zeroavoider2_MODE = _rtB -> B_26_620_0 >= _rtP -> P_327 ? 1 :
_rtB -> B_26_620_0 > _rtP -> P_328 ? 0 : - 1 ; } isHit = ssIsSampleHit ( S ,
2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_26_655_0 = _rtDW ->
DiscreteTimeIntegrator_DSTATE_bt ; _rtB -> B_26_656_0 = ( 0.0 - _rtB ->
B_26_655_0 ) - _rtB -> B_26_585_0 ; rtb_B_26_49_0 = 1.0 / rtb_B_26_97_0 *
_rtB -> B_26_101_0_o ; _rtB -> B_26_664_0 = ( muDoubleScalarAbs ( _rtDW ->
UnitDelay2_DSTATE_p ) >= _rtB -> B_26_95_0 ) ; if ( _rtB -> B_26_664_0 || (
_rtDW -> DiscreteTimeIntegrator1_PrevResetState != 0 ) ) { _rtDW ->
DiscreteTimeIntegrator1_DSTATE = _rtP -> P_334 ; } _rtB -> B_26_669_0 = ( ( (
( real_T ) ( ( _rtDW -> DiscreteTimeIntegrator1_DSTATE > 0.0 ) && ( _rtDW ->
DiscreteTimeIntegrator1_DSTATE <= 10.0 ) ) * ( _rtB -> B_26_97_0 *
rtb_B_26_49_0 ) + ( real_T ) ( ( _rtDW -> DiscreteTimeIntegrator1_DSTATE >
10.0 ) && ( _rtDW -> DiscreteTimeIntegrator1_DSTATE <= 100.0 ) ) * ( _rtB ->
B_26_98_0_a * rtb_B_26_49_0 ) ) + _rtB -> B_26_99_0_j * rtb_B_26_49_0 * (
real_T ) ( _rtDW -> DiscreteTimeIntegrator1_DSTATE > 100.0 ) ) - _rtDW ->
UnitDelay_DSTATE_h ) * ( 1.0 / ( rtb_B_26_49_0 * 0.15 ) ) ; _rtB ->
B_26_670_0 = _rtP -> P_335 * _rtB -> B_26_585_0 ; _rtB -> B_26_680_0 = _rtP
-> P_336 * _rtB -> B_26_103_0 [ 24 ] ; _rtB -> B_26_687_0 = _rtP -> P_337 *
_rtB -> B_26_103_0 [ 39 ] ; _rtB -> B_26_691_0 = _rtP -> P_338 * _rtB ->
B_26_103_0 [ 23 ] ; _rtB -> B_26_700_0 = ( _rtP -> P_339 * _rtB -> B_26_103_0
[ 28 ] > power_FCHPS_MEA_rtC ( S ) -> B_26_4_0 ) ; rtb_B_26_37_0 = _rtP ->
P_344 * _rtB -> B_26_103_0 [ 13 ] * _rtP -> P_345 ; if ( rtb_B_26_37_0 > _rtP
-> P_346 ) { rtb_B_26_37_0 = _rtP -> P_346 ; } else { if ( rtb_B_26_37_0 <
_rtP -> P_347 ) { rtb_B_26_37_0 = _rtP -> P_347 ; } } _rtB -> B_26_730_0 = (
_rtP -> P_340 * _rtB -> B_26_3_0 [ 8 ] * ( _rtP -> P_341 * _rtB -> B_26_3_0 [
3 ] ) - _rtP -> P_342 * _rtB -> B_26_3_0 [ 4 ] * ( _rtP -> P_343 * _rtB ->
B_26_3_0 [ 9 ] ) ) / rtb_B_26_37_0 ; _rtB -> B_26_753_0 = ( _rtB ->
B_26_102_0_n - _rtB -> B_26_120_0 / _rtB -> B_26_103_0_i ) * _rtP -> P_348 ;
_rtB -> B_26_754_0 = muDoubleScalarAbs ( _rtB -> B_26_753_0 ) ;
ssCallAccelRunBlock ( S , 26 , 755 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 26 , 756 , SS_CALL_MDL_OUTPUTS ) ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S ,
26 , 757 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 26 , 758 ,
SS_CALL_MDL_OUTPUTS ) ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit !=
0 ) { _rtB -> B_26_759_0 [ 0 ] = _rtB -> B_26_296_0 ; _rtB -> B_26_759_0 [ 1
] = _rtB -> B_26_587_0 ; _rtB -> B_26_759_0 [ 2 ] = _rtB -> B_26_588_0 ; _rtB
-> B_26_759_0 [ 3 ] = _rtB -> B_26_586_0 ; ssCallAccelRunBlock ( S , 26 , 760
, SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 26 , 761 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 26 , 762 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 26 , 763 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_26_764_0 = _rtDW ->
DiscreteTimeIntegrator_DSTATE_e ; } ssCallAccelRunBlock ( S , 26 , 765 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_26_768_0 = _rtP -> P_351 * _rtB ->
B_26_621_0 [ 1 ] * 117536.99999999999 / 2644.0110000000004 * _rtP -> P_352 ;
isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock
( S , 26 , 769 , SS_CALL_MDL_OUTPUTS ) ; } UNUSED_PARAMETER ( tid ) ; }
static void mdlOutputsTID4 ( SimStruct * S , int_T tid ) {
B_power_FCHPS_MEA_T * _rtB ; DW_power_FCHPS_MEA_T * _rtDW ;
P_power_FCHPS_MEA_T * _rtP ; real_T u0 ; _rtDW = ( ( DW_power_FCHPS_MEA_T * )
ssGetRootDWork ( S ) ) ; _rtP = ( ( P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S
) ) ; _rtB = ( ( B_power_FCHPS_MEA_T * ) _ssGetModelBlockIO ( S ) ) ; memcpy
( & _rtB -> B_26_0_0_m [ 0 ] , & _rtP -> P_353 [ 0 ] , 13U * sizeof ( real_T
) ) ; _rtB -> B_26_1_0_c = _rtP -> P_354 ; _rtB -> B_26_2_0_k = _rtP -> P_355
; _rtB -> B_26_3_0_c = _rtP -> P_356 ; _rtB -> B_26_4_0 = _rtP -> P_357 ;
_rtB -> B_26_6_0 = _rtP -> P_359 ; _rtB -> B_26_7_0_j = ( 0.0 <= _rtP ->
P_358 ) ; _rtB -> B_26_8_0 = _rtP -> P_360 ; _rtB -> B_26_9_0_b = _rtP ->
P_361 ; _rtB -> B_26_10_0_p = _rtP -> P_362 ; _rtB -> B_26_11_0 = _rtP ->
P_363 ; _rtB -> B_26_12_0_c = _rtP -> P_364 ; _rtB -> B_26_13_0 = _rtP ->
P_365 ; _rtB -> B_26_15_0_f = _rtP -> P_367 ; _rtB -> B_26_16_0 = ( 0.0 <=
_rtP -> P_366 ) ; _rtB -> B_26_17_0 = _rtP -> P_368 ; _rtB -> B_4_0_0_o =
_rtP -> P_17 ; _rtB -> B_4_1_0_n = _rtP -> P_18 ; _rtB -> B_4_4_0_c = (
uint8_T ) ( _rtP -> P_19 == _rtP -> P_20 ) ; _rtB -> B_4_6_0_m = ( uint8_T )
( _rtP -> P_19 == _rtP -> P_21 ) ; if ( ssIsMajorTimeStep ( S ) != 0 ) {
srUpdateBC ( _rtDW -> AutomaticGainControl_SubsysRanBC ) ; } _rtB ->
B_26_19_0 = _rtP -> P_369 ; _rtB -> B_26_20_0 = _rtP -> P_370 ; _rtB ->
B_26_21_0 = _rtP -> P_371 ; _rtB -> B_26_24_0 = ( uint8_T ) ( _rtP -> P_372
== _rtP -> P_373 ) ; _rtB -> B_26_26_0_m = ( uint8_T ) ( _rtP -> P_372 ==
_rtP -> P_374 ) ; if ( _rtP -> P_375 > _rtP -> P_376 ) { _rtB -> B_26_28_0 =
_rtP -> P_376 ; } else if ( _rtP -> P_375 < _rtP -> P_377 ) { _rtB ->
B_26_28_0 = _rtP -> P_377 ; } else { _rtB -> B_26_28_0 = _rtP -> P_375 ; }
_rtB -> B_26_31_0 = ( uint8_T ) ( _rtP -> P_378 == _rtP -> P_379 ) ; _rtB ->
B_26_33_0 = ( uint8_T ) ( _rtP -> P_378 == _rtP -> P_380 ) ; _rtB ->
B_26_36_0 = ( uint8_T ) ( _rtP -> P_381 == _rtP -> P_382 ) ; _rtB ->
B_26_38_0 = ( uint8_T ) ( _rtP -> P_381 == _rtP -> P_383 ) ; _rtB ->
B_26_39_0_g = _rtP -> P_384 ; _rtB -> B_26_40_0 = _rtP -> P_385 ; _rtB ->
B_26_41_0_g = _rtP -> P_386 ; _rtB -> B_26_42_0_m = _rtP -> P_387 ; _rtB ->
B_26_43_0_n = _rtP -> P_388 ; _rtB -> B_26_44_0_p = _rtP -> P_389 ; _rtB ->
B_26_45_0_l = _rtP -> P_390 ; _rtB -> B_26_46_0_j = _rtP -> P_391 ; _rtB ->
B_26_47_0 = _rtP -> P_392 ; _rtB -> B_26_48_0 = _rtP -> P_393 ; _rtB ->
B_26_49_0 = _rtP -> P_394 ; _rtB -> B_26_50_0 = _rtP -> P_395 ; _rtB ->
B_26_51_0_d = _rtP -> P_396 ; _rtB -> B_26_52_0_g = _rtP -> P_397 ; _rtB ->
B_26_53_0_l = _rtP -> P_398 ; _rtB -> B_26_54_0_d = _rtP -> P_399 ; _rtB ->
B_26_55_0 = _rtP -> P_400 ; _rtB -> B_26_56_0 = _rtP -> P_401 ; _rtB ->
B_26_57_0_d = _rtP -> P_402 ; _rtB -> B_26_58_0 = _rtP -> P_403 ; _rtB ->
B_26_59_0_l = _rtP -> P_404 ; _rtB -> B_26_60_0_o = _rtP -> P_405 ; _rtB ->
B_26_61_0 = _rtP -> P_406 ; _rtB -> B_26_62_0_b = _rtP -> P_407 ; _rtB ->
B_26_63_0 = _rtP -> P_408 ; _rtB -> B_26_64_0_n = _rtP -> P_409 ; _rtB ->
B_26_65_0_b = _rtP -> P_410 ; _rtB -> B_26_66_0 = _rtP -> P_411 ; _rtB ->
B_26_67_0 = _rtP -> P_412 ; _rtB -> B_26_68_0 = _rtP -> P_413 ; _rtB ->
B_26_69_0_l = _rtP -> P_414 ; _rtB -> B_26_70_0 = _rtP -> P_415 ; _rtB ->
B_26_71_0_h = _rtP -> P_416 ; _rtB -> B_26_72_0 = _rtP -> P_417 ; _rtB ->
B_26_77_0_b = _rtP -> P_422 ; _rtB -> B_26_78_0_d = _rtP -> P_423 ; _rtB ->
B_26_79_0_e = _rtP -> P_424 ; _rtB -> B_26_80_0 = _rtP -> P_425 ; _rtB ->
B_26_81_0_b = _rtP -> P_426 ; _rtB -> B_26_82_0 = _rtP -> P_427 ; _rtB ->
B_26_83_0 = _rtP -> P_428 ; _rtB -> B_26_84_0_j = _rtP -> P_429 ; u0 = _rtP
-> P_419 * _rtP -> P_418 ; if ( u0 > _rtP -> P_430 ) { _rtB -> B_26_85_0 =
_rtP -> P_430 ; } else if ( u0 < _rtP -> P_431 ) { _rtB -> B_26_85_0 = _rtP
-> P_431 ; } else { _rtB -> B_26_85_0 = u0 ; } u0 = _rtP -> P_421 * _rtP ->
P_420 ; if ( u0 > _rtP -> P_432 ) { _rtB -> B_26_86_0_f = _rtP -> P_432 ; }
else if ( u0 < _rtP -> P_433 ) { _rtB -> B_26_86_0_f = _rtP -> P_433 ; } else
{ _rtB -> B_26_86_0_f = u0 ; } if ( _rtP -> P_434 > _rtP -> P_435 ) { _rtB ->
B_26_88_0 = _rtP -> P_435 ; } else if ( _rtP -> P_434 < _rtP -> P_436 ) {
_rtB -> B_26_88_0 = _rtP -> P_436 ; } else { _rtB -> B_26_88_0 = _rtP ->
P_434 ; } if ( _rtP -> P_437 > _rtP -> P_438 ) { _rtB -> B_26_90_0 = _rtP ->
P_438 ; } else if ( _rtP -> P_437 < _rtP -> P_439 ) { _rtB -> B_26_90_0 =
_rtP -> P_439 ; } else { _rtB -> B_26_90_0 = _rtP -> P_437 ; } if ( _rtP ->
P_440 > _rtP -> P_441 ) { _rtB -> B_26_92_0 = _rtP -> P_441 ; } else if (
_rtP -> P_440 < _rtP -> P_442 ) { _rtB -> B_26_92_0 = _rtP -> P_442 ; } else
{ _rtB -> B_26_92_0 = _rtP -> P_440 ; } _rtB -> B_26_94_0 = _rtP -> P_443 ;
_rtB -> B_26_95_0 = _rtP -> P_444 ; _rtB -> B_26_96_0 = _rtP -> P_445 ; _rtB
-> B_26_97_0 = _rtP -> P_446 ; _rtB -> B_26_98_0_a = _rtP -> P_447 ; _rtB ->
B_26_99_0_j = _rtP -> P_448 ; _rtB -> B_26_100_0_j = _rtP -> P_449 ; _rtB ->
B_26_101_0_o = _rtP -> P_450 ; _rtB -> B_26_102_0_n = _rtP -> P_451 ; _rtB ->
B_26_103_0_i = _rtP -> P_452 ; UNUSED_PARAMETER ( tid ) ; }
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
-> B_26_545_0 [ 0 ] ; _rtDW -> UnitDelay1_DSTATE = _rtB -> B_26_545_0 [ 1 ] ;
ssCallAccelRunBlock ( S , 26 , 3 , SS_CALL_MDL_UPDATE ) ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW ->
itinit1_PreviousInput = _rtB -> B_26_41_0_g ; } isHit = ssIsSampleHit ( S , 2
, 0 ) ; if ( isHit != 0 ) { _rtDW -> Currentfilter_states = ( _rtB ->
B_26_553_0 - _rtP -> P_47 [ 1 ] * _rtDW -> Currentfilter_states ) / _rtP ->
P_47 [ 0 ] ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
_rtDW -> itinit_PreviousInput = _rtB -> B_26_566_0 ; } isHit = ssIsSampleHit
( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtDW -> inti_IC_LOADING = 0U ; _rtDW ->
inti_DSTATE += _rtP -> P_50 * _rtB -> B_26_553_0 ; if ( _rtDW -> inti_DSTATE
>= _rtP -> P_51 ) { _rtDW -> inti_DSTATE = _rtP -> P_51 ; } else { if ( _rtDW
-> inti_DSTATE <= _rtP -> P_52 ) { _rtDW -> inti_DSTATE = _rtP -> P_52 ; } }
if ( _rtB -> B_26_9_0 > 0.0 ) { _rtDW -> inti_PrevResetState = 1 ; } else if
( _rtB -> B_26_9_0 < 0.0 ) { _rtDW -> inti_PrevResetState = - 1 ; } else if (
_rtB -> B_26_9_0 == 0.0 ) { _rtDW -> inti_PrevResetState = 0 ; } else { _rtDW
-> inti_PrevResetState = 2 ; } _rtDW -> DiscreteTimeIntegrator_DSTATE += _rtP
-> P_55 * _rtB -> B_26_565_0 ; _rtDW -> Memory2_PreviousInput = _rtB ->
B_26_567_0 ; _rtDW -> UnitDelay2_DSTATE = _rtB -> B_26_180_0 ; _rtDW ->
UnitDelay3_DSTATE = _rtB -> B_26_256_0 ; _rtDW -> UnitDelay2_DSTATE_m = _rtB
-> B_26_382_0 ; _rtDW -> Celldynamic_states = ( _rtB -> B_26_612_0 - _rtP ->
P_62 [ 1 ] * _rtDW -> Celldynamic_states ) / _rtP -> P_62 [ 0 ] ; _rtDW ->
UnitDelay_DSTATE_a = _rtB -> B_26_600_0 ; _rtDW ->
DiscreteTimeIntegrator_DSTATE_f += _rtP -> P_95 * _rtB -> B_26_656_0 ; _rtDW
-> UnitDelay_DSTATE_c = _rtB -> B_26_730_0 ; _rtDW -> UnitDelay3_DSTATE_c =
_rtB -> B_26_182_0 ; _rtDW -> UnitDelay2_DSTATE_e = _rtB -> B_26_259_0 ;
_rtDW -> UnitDelay3_DSTATE_l = _rtB -> B_26_384_0 ; ssCallAccelRunBlock ( S ,
26 , 103 , SS_CALL_MDL_UPDATE ) ; _rtDW -> DiscreteTimeIntegrator_DSTATE_n +=
_rtP -> P_120 * _rtB -> B_26_584_0 ; if ( _rtDW ->
DiscreteTimeIntegrator_DSTATE_n >= _rtP -> P_122 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_n = _rtP -> P_122 ; } else { if ( _rtDW ->
DiscreteTimeIntegrator_DSTATE_n <= _rtP -> P_123 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_n = _rtP -> P_123 ; } } _rtDW ->
UnitDelay_DSTATE_m = _rtB -> B_26_129_0 ; _rtDW ->
DiscreteTimeIntegrator_DSTATE_p += _rtP -> P_129 * _rtB -> B_26_155_0 ; if (
_rtDW -> DiscreteTimeIntegrator_DSTATE_p >= _rtP -> P_131 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_p = _rtP -> P_131 ; } else { if ( _rtDW ->
DiscreteTimeIntegrator_DSTATE_p <= _rtP -> P_132 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_p = _rtP -> P_132 ; } } _rtDW ->
DiscreteTimeIntegrator_DSTATE_o += _rtP -> P_138 * _rtB -> B_26_172_0 ; if (
_rtDW -> DiscreteTimeIntegrator_DSTATE_o >= _rtP -> P_140 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_o = _rtP -> P_140 ; } else { if ( _rtDW ->
DiscreteTimeIntegrator_DSTATE_o <= _rtP -> P_141 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_o = _rtP -> P_141 ; } } _rtDW ->
UnitDelay_DSTATE_k = _rtB -> B_26_222_0 ; _rtDW ->
DiscreteTimeIntegrator_DSTATE_c += _rtP -> P_162 * _rtB -> B_26_238_0 ; if (
_rtDW -> DiscreteTimeIntegrator_DSTATE_c >= _rtP -> P_164 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_c = _rtP -> P_164 ; } else { if ( _rtDW ->
DiscreteTimeIntegrator_DSTATE_c <= _rtP -> P_165 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_c = _rtP -> P_165 ; } } _rtDW ->
DiscreteTimeIntegrator_DSTATE_fi += _rtP -> P_171 * _rtB -> B_26_248_0 ; if (
_rtDW -> DiscreteTimeIntegrator_DSTATE_fi >= _rtP -> P_173 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_fi = _rtP -> P_173 ; } else { if ( _rtDW ->
DiscreteTimeIntegrator_DSTATE_fi <= _rtP -> P_174 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_fi = _rtP -> P_174 ; } } } isHit =
ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S ,
26 , 303 , SS_CALL_MDL_UPDATE ) ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if
( isHit != 0 ) { _rtDW -> DiscreteTimeIntegrator_DSTATE_h += _rtP -> P_200 *
_rtB -> B_26_582_0 ; if ( _rtDW -> DiscreteTimeIntegrator_DSTATE_h >= _rtP ->
P_202 ) { _rtDW -> DiscreteTimeIntegrator_DSTATE_h = _rtP -> P_202 ; } else {
if ( _rtDW -> DiscreteTimeIntegrator_DSTATE_h <= _rtP -> P_203 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_h = _rtP -> P_203 ; } } _rtDW ->
DiscreteTimeIntegrator_DSTATE_a += _rtP -> P_207 * _rtB -> B_26_583_0 ; if (
_rtDW -> DiscreteTimeIntegrator_DSTATE_a >= _rtP -> P_209 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_a = _rtP -> P_209 ; } else { if ( _rtDW ->
DiscreteTimeIntegrator_DSTATE_a <= _rtP -> P_210 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_a = _rtP -> P_210 ; } } _rtDW ->
UnitDelay_DSTATE_l = _rtB -> B_26_333_0 ; _rtDW ->
DiscreteTimeIntegrator_DSTATE_g += _rtP -> P_221 * _rtB -> B_26_357_0 ; if (
_rtDW -> DiscreteTimeIntegrator_DSTATE_g >= _rtP -> P_223 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_g = _rtP -> P_223 ; } else { if ( _rtDW ->
DiscreteTimeIntegrator_DSTATE_g <= _rtP -> P_224 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_g = _rtP -> P_224 ; } } _rtDW ->
DiscreteTimeIntegrator_DSTATE_b += _rtP -> P_230 * _rtB -> B_26_374_0 ; if (
_rtDW -> DiscreteTimeIntegrator_DSTATE_b >= _rtP -> P_232 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_b = _rtP -> P_232 ; } else { if ( _rtDW ->
DiscreteTimeIntegrator_DSTATE_b <= _rtP -> P_233 ) { _rtDW ->
DiscreteTimeIntegrator_DSTATE_b = _rtP -> P_233 ; } } _rtDW ->
UnitDelay4_DSTATE = _rtB -> B_26_430_0 ; } _rtDW -> Integrator_IWORK = 0 ;
switch ( _rtDW -> Integrator_MODE ) { case 3 : if ( _rtB -> B_26_476_0 < 0.0
) { _rtDW -> Integrator_MODE = 1 ; ssSetBlockStateForSolverChangedAtMajorStep
( S ) ; } break ; case 4 : if ( _rtB -> B_26_476_0 > 0.0 ) { _rtDW ->
Integrator_MODE = 2 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; }
break ; } _rtXdis -> Integrator_CSTATE = ( ( _rtDW -> Integrator_MODE == 3 )
|| ( _rtDW -> Integrator_MODE == 4 ) ) ; isHit = ssIsSampleHit ( S , 1 , 0 )
; if ( isHit != 0 ) { _rtDW -> Memory_PreviousInput = _rtB -> B_26_495_0 ; }
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
Integrator_MODE_g ) { case 3 : if ( _rtB -> B_26_472_0 < 0.0 ) { _rtDW ->
Integrator_MODE_g = 1 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; }
break ; case 4 : if ( _rtB -> B_26_472_0 > 0.0 ) { _rtDW -> Integrator_MODE_g
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
P_269 , tBuffer , uBuffer , xBuffer , ( boolean_T ) 0 , ( boolean_T ) 1 , &
_rtDW -> VariableTransportDelay_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus
( S , "vtdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [
_rtDW -> VariableTransportDelay_IWORK . Head ] = simTime ; ( * uBuffer ) [
_rtDW -> VariableTransportDelay_IWORK . Head ] = _rtB -> B_26_464_0 ; ( *
xBuffer ) [ _rtDW -> VariableTransportDelay_IWORK . Head ] = ( (
X_power_FCHPS_MEA_T * ) ssGetContStates ( S ) ) ->
VariableTransportDelay_CSTATE ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { _rtDW -> Memory_PreviousInput_g = _rtB -> B_26_469_0 ; } if (
_rtDW -> LastMajorTimeA == ( rtInf ) ) { _rtDW -> LastMajorTimeA =
ssGetTaskTime ( S , 0 ) ; _rtDW -> PrevYA = _rtB -> B_26_478_0 ; } else if (
_rtDW -> LastMajorTimeB == ( rtInf ) ) { _rtDW -> LastMajorTimeB =
ssGetTaskTime ( S , 0 ) ; _rtDW -> PrevYB = _rtB -> B_26_478_0 ; } else if (
_rtDW -> LastMajorTimeA < _rtDW -> LastMajorTimeB ) { _rtDW -> LastMajorTimeA
= ssGetTaskTime ( S , 0 ) ; _rtDW -> PrevYA = _rtB -> B_26_478_0 ; } else {
_rtDW -> LastMajorTimeB = ssGetTaskTime ( S , 0 ) ; _rtDW -> PrevYB = _rtB ->
B_26_478_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) {
_rtDW -> UnitDelay1_DSTATE_f = _rtB -> B_26_592_0 ; _rtDW ->
DiscreteTimeIntegrator_DSTATE_bt += _rtP -> P_329 * _rtB -> B_26_669_0 ;
_rtDW -> UnitDelay2_DSTATE_p = _rtB -> B_26_670_0 ; _rtDW ->
UnitDelay_DSTATE_h = _rtB -> B_26_655_0 ; if ( ! _rtB -> B_26_664_0 ) { _rtDW
-> DiscreteTimeIntegrator1_DSTATE += _rtP -> P_333 * _rtB -> B_26_96_0 ; }
_rtDW -> DiscreteTimeIntegrator1_PrevResetState = ( int8_T ) _rtB ->
B_26_664_0 ; _rtDW -> DiscreteTimeIntegrator_DSTATE_e += _rtP -> P_349 * _rtB
-> B_26_768_0 ; } UNUSED_PARAMETER ( tid ) ; }
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
P_72 * _rtX -> Airblowerdelay2_CSTATE ; _rtXdot -> Airblowerdelay2_CSTATE +=
_rtB -> B_26_596_0 ; if ( _rtXdis -> Integrator_CSTATE ) { _rtXdot ->
Integrator_CSTATE = 0.0 ; } else { _rtXdot -> Integrator_CSTATE = _rtB ->
B_26_476_0 ; } if ( _rtDW -> AutomaticGainControl_MODE ) { { real_T
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
B_26_472_0 ; } { real_T instantDelay ; instantDelay = _rtB -> B_26_497_0 ; if
( instantDelay > _rtP -> P_269 ) { instantDelay = _rtP -> P_269 ; } if (
instantDelay < 0.0 ) { ( ( XDot_power_FCHPS_MEA_T * ) ssGetdX ( S ) ) ->
VariableTransportDelay_CSTATE = 0 ; } else { ( ( XDot_power_FCHPS_MEA_T * )
ssGetdX ( S ) ) -> VariableTransportDelay_CSTATE = 1.0 / instantDelay ; } }
_rtXdot -> integrator_CSTATE = _rtB -> B_26_502_0 [ 1 ] ; _rtXdot ->
TransferFcn_CSTATE = 0.0 ; _rtXdot -> TransferFcn_CSTATE += _rtP -> P_276 *
_rtX -> TransferFcn_CSTATE ; _rtXdot -> TransferFcn_CSTATE += _rtB ->
B_26_473_0 ; _rtXdot -> Integrator_x1_CSTATE = _rtB -> B_26_488_0 ; _rtXdot
-> Integrator_x2_CSTATE = _rtB -> B_26_490_0 ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { B_power_FCHPS_MEA_T * _rtB ;
DW_power_FCHPS_MEA_T * _rtDW ; P_power_FCHPS_MEA_T * _rtP ;
X_power_FCHPS_MEA_T * _rtX ; ZCV_power_FCHPS_MEA_T * _rtZCSV ; _rtDW = ( (
DW_power_FCHPS_MEA_T * ) ssGetRootDWork ( S ) ) ; _rtZCSV = ( (
ZCV_power_FCHPS_MEA_T * ) ssGetSolverZcSignalVector ( S ) ) ; _rtX = ( (
X_power_FCHPS_MEA_T * ) ssGetContStates ( S ) ) ; _rtP = ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_power_FCHPS_MEA_T * ) _ssGetModelBlockIO ( S ) ) ; _rtZCSV ->
Saturation4_UprLim_ZC = _rtB -> B_26_53_0 - _rtP -> P_74 ; _rtZCSV ->
Saturation4_LwrLim_ZC = _rtB -> B_26_53_0 - _rtP -> P_75 ; _rtZCSV ->
Saturation3_UprLim_ZC = _rtB -> B_26_54_0 - _rtP -> P_76 ; _rtZCSV ->
Saturation3_LwrLim_ZC = _rtB -> B_26_54_0 - _rtP -> P_77 ; _rtZCSV ->
Saturation4_UprLim_ZC_n = _rtB -> B_26_57_0 - _rtP -> P_79 ; _rtZCSV ->
Saturation4_LwrLim_ZC_b = _rtB -> B_26_57_0 - _rtP -> P_80 ; _rtZCSV ->
Saturation1_UprLim_ZC = _rtB -> B_26_60_0 - _rtP -> P_81 ; _rtZCSV ->
Saturation1_LwrLim_ZC = _rtB -> B_26_60_0 - _rtP -> P_82 ; _rtZCSV ->
Saturation4_UprLim_ZC_g = _rtB -> B_26_62_0 - _rtP -> P_83 ; _rtZCSV ->
Saturation4_LwrLim_ZC_l = _rtB -> B_26_62_0 - _rtP -> P_84 ; _rtZCSV ->
Saturation5_UprLim_ZC = _rtB -> B_26_64_0 - _rtP -> P_85 ; _rtZCSV ->
Saturation5_LwrLim_ZC = _rtB -> B_26_64_0 - _rtP -> P_86 ; _rtZCSV ->
Switch_SwitchCond_ZC = _rtB -> B_26_59_0 - _rtP -> P_87 ; _rtZCSV ->
Compare_RelopInput_ZC = _rtB -> B_26_57_0 - _rtB -> B_26_77_0_b ; _rtZCSV ->
MinMax_MinmaxInput_ZC = muDoubleScalarMax ( _rtB -> B_26_77_0 [ 1 ] , _rtB ->
B_26_77_0 [ 0 ] ) - _rtB -> B_26_77_0 [ _rtDW -> MinMax_MODE ] ; _rtZCSV ->
Saturation2_UprLim_ZC = _rtB -> B_26_78_0 - _rtP -> P_91 ; _rtZCSV ->
Saturation2_LwrLim_ZC = _rtB -> B_26_78_0 - _rtP -> P_92 ; _rtZCSV ->
Compare_RelopInput_ZC_p = _rtB -> B_26_79_0 - _rtB -> B_26_78_0_d ; _rtZCSV
-> LowerRelop1_RelopInput_ZC = _rtB -> B_26_84_0 - _rtB -> B_26_80_0 ;
_rtZCSV -> UpperRelop_RelopInput_ZC = _rtB -> B_26_84_0 - _rtB -> B_26_86_0 ;
_rtZCSV -> RelationalOperator_RelopInput_ZC = _rtB -> B_26_114_0 - _rtB ->
B_26_3_0_c ; _rtZCSV -> RelationalOperator_RelopInput_ZC_a = _rtB ->
B_26_289_0 - _rtB -> B_26_12_0_c ; _rtZCSV -> Saturation2_UprLim_ZC_l = _rtB
-> B_26_414_0 - _rtP -> P_247 ; _rtZCSV -> Saturation2_LwrLim_ZC_m = _rtB ->
B_26_414_0 - _rtP -> P_248 ; _rtZCSV -> RelationalOperator_RelopInput_ZC_f =
_rtX -> Integrator_CSTATE - _rtB -> B_26_20_0 ; switch ( _rtDW ->
Integrator_MODE ) { case 1 : _rtZCSV -> Integrator_IntgUpLimit_ZC = 0.0 ;
_rtZCSV -> Integrator_IntgLoLimit_ZC = _rtP -> P_262 - _rtP -> P_263 ; break
; case 2 : _rtZCSV -> Integrator_IntgUpLimit_ZC = _rtP -> P_263 - _rtP ->
P_262 ; _rtZCSV -> Integrator_IntgLoLimit_ZC = 0.0 ; break ; default :
_rtZCSV -> Integrator_IntgUpLimit_ZC = _rtX -> Integrator_CSTATE - _rtP ->
P_262 ; _rtZCSV -> Integrator_IntgLoLimit_ZC = _rtX -> Integrator_CSTATE -
_rtP -> P_263 ; break ; } if ( ( _rtDW -> Integrator_MODE == 3 ) || ( _rtDW
-> Integrator_MODE == 4 ) ) { _rtZCSV -> Integrator_LeaveSaturate_ZC = _rtB
-> B_26_476_0 ; } else { _rtZCSV -> Integrator_LeaveSaturate_ZC = 0.0 ; }
_rtZCSV -> HitCrossing_HitNoOutput_ZC = _rtB -> B_26_452_0 - _rtP -> P_264 ;
if ( _rtDW -> AutomaticGainControl_MODE ) { _rtZCSV ->
RelationalOperator_RelopInput_ZC_h = _rtB -> B_4_2_0 - _rtB -> B_4_0_0_o ;
_rtZCSV -> RelationalOperator_RelopInput_ZC_b = _rtB -> B_4_9_0 - _rtB ->
B_4_1_0_n ; _rtZCSV -> Saturation_UprLim_ZC_p = _rtB -> B_4_15_0 - _rtP ->
P_9 ; _rtZCSV -> Saturation_LwrLim_ZC_m = _rtB -> B_4_15_0 - _rtP -> P_10 ; }
else { { real_T * zcsv = & ( ( ( ZCV_power_FCHPS_MEA_T * )
ssGetSolverZcSignalVector ( S ) ) -> RelationalOperator_RelopInput_ZC_h ) ;
int_T i ; for ( i = 0 ; i < 4 ; i ++ ) { zcsv [ i ] = 0.0 ; } } } switch (
_rtDW -> Integrator_MODE_g ) { case 1 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_g = 0.0 ; _rtZCSV -> Integrator_IntgLoLimit_ZC_f =
_rtP -> P_267 - _rtP -> P_268 ; break ; case 2 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_g = _rtP -> P_268 - _rtP -> P_267 ; _rtZCSV ->
Integrator_IntgLoLimit_ZC_f = 0.0 ; break ; default : _rtZCSV ->
Integrator_IntgUpLimit_ZC_g = _rtX -> Integrator_CSTATE_g - _rtP -> P_267 ;
_rtZCSV -> Integrator_IntgLoLimit_ZC_f = _rtX -> Integrator_CSTATE_g - _rtP
-> P_268 ; break ; } if ( ( _rtDW -> Integrator_MODE_g == 3 ) || ( _rtDW ->
Integrator_MODE_g == 4 ) ) { _rtZCSV -> Integrator_LeaveSaturate_ZC_k = _rtB
-> B_26_472_0 ; } else { _rtZCSV -> Integrator_LeaveSaturate_ZC_k = 0.0 ; }
_rtZCSV -> RelationalOperator_RelopInput_ZC_e = _rtB -> B_26_465_0 - _rtB ->
B_26_21_0 ; _rtZCSV -> Saturation2_UprLim_ZC_lq = _rtB -> B_26_475_0 - _rtP
-> P_279 ; _rtZCSV -> Saturation2_LwrLim_ZC_o = _rtB -> B_26_475_0 - _rtP ->
P_280 ; _rtZCSV -> UpperRelop_RelopInput_ZC_f = _rtB -> B_26_46_0 - _rtB ->
B_26_607_0 ; _rtZCSV -> Saturation_UprLim_ZC [ 0 ] = _rtB -> B_26_76_0 [ 0 ]
- _rtP -> P_320 ; _rtZCSV -> Saturation_LwrLim_ZC [ 0 ] = _rtB -> B_26_76_0 [
0 ] - _rtP -> P_321 ; _rtZCSV -> Saturation_UprLim_ZC [ 1 ] = _rtB ->
B_26_76_0 [ 1 ] - _rtP -> P_320 ; _rtZCSV -> Saturation_LwrLim_ZC [ 1 ] =
_rtB -> B_26_76_0 [ 1 ] - _rtP -> P_321 ; _rtZCSV -> zeroavoider_UprLim_ZC =
_rtB -> B_26_619_0 - _rtP -> P_325 ; _rtZCSV -> zeroavoider_LwrLim_ZC = _rtB
-> B_26_619_0 - _rtP -> P_326 ; _rtZCSV -> zeroavoider2_UprLim_ZC = _rtB ->
B_26_620_0 - _rtP -> P_327 ; _rtZCSV -> zeroavoider2_LwrLim_ZC = _rtB ->
B_26_620_0 - _rtP -> P_328 ; } static void mdlInitializeSizes ( SimStruct * S
) { ssSetChecksumVal ( S , 0 , 1082120810U ) ; ssSetChecksumVal ( S , 1 ,
1683116139U ) ; ssSetChecksumVal ( S , 2 , 1733079937U ) ; ssSetChecksumVal (
S , 3 , 1757656180U ) ; { mxArray * slVerStructMat = NULL ; mxArray *
slStrMat = mxCreateString ( "simulink" ) ; char slVerChar [ 10 ] ; int status
= mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat , "ver" ) ; if (
status == 0 ) { mxArray * slVerMat = mxGetField ( slVerStructMat , 0 ,
"Version" ) ; if ( slVerMat == NULL ) { status = 1 ; } else { status =
mxGetString ( slVerMat , slVerChar , 10 ) ; } } mxDestroyArray ( slStrMat ) ;
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
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_65 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_67 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_74 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_76 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_81 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_83 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_85 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_97 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_142 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_148 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_180 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_184 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_197 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_234 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_240 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_247 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_262 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_263 = rtMinusInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_267 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_279 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_317 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_325 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_327 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_346 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_425 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_426 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_435 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_438 = rtInf ; ( (
P_power_FCHPS_MEA_T * ) ssGetModelRtp ( S ) ) -> P_441 = rtInf ; } static
void mdlInitializeSampleTimes ( SimStruct * S ) { { SimStruct * childS ;
SysOutputFcn * callSysFcns ; childS = ssGetSFunction ( S , 0 ) ; callSysFcns
= ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; } slAccRegPrmChangeFcn ( S , mdlOutputsTID4 ) ; }
static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"

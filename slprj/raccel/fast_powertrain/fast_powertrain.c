#include "rt_logging_mmi.h"
#include "fast_powertrain_capi.h"
#include <math.h>
#include "fast_powertrain.h"
#include "fast_powertrain_private.h"
#include "fast_powertrain_dt.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "slsa_sim_engine.h"
extern void * CreateDiagnosticAsVoidPtr_wrapper ( const char * id , int nargs
, ... ) ; RTWExtModeInfo * gblRTWExtModeInfo = NULL ; void
raccelForceExtModeShutdown ( boolean_T extModeStartPktReceived ) { if ( !
extModeStartPktReceived ) { boolean_T stopRequested = false ;
rtExtModeWaitForStartPkt ( gblRTWExtModeInfo , 3 , & stopRequested ) ; }
rtExtModeShutdown ( 3 ) ; }
#include "slsv_diagnostic_codegen_c_api.h"
const int_T gblNumToFiles = 0 ; const int_T gblNumFrFiles = 0 ; const int_T
gblNumFrWksBlocks = 0 ;
#ifdef RSIM_WITH_SOLVER_MULTITASKING
boolean_T gbl_raccel_isMultitasking = 1 ;
#else
boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
boolean_T gbl_raccel_tid01eq = 1 ; int_T gbl_raccel_NumST = 4 ; const char_T
* gbl_raccel_Version = "9.4 (R2020b) 29-Jul-2020" ; void
raccel_setup_MMIStateLog ( SimStruct * S ) {
#ifdef UseMMIDataLogging
rt_FillStateSigInfoFromMMI ( ssGetRTWLogInfo ( S ) , & ssGetErrorStatus ( S )
) ;
#else
UNUSED_PARAMETER ( S ) ;
#endif
} static DataMapInfo rt_dataMapInfo ; DataMapInfo * rt_dataMapInfoPtr = &
rt_dataMapInfo ; rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; const int_T gblNumRootInportBlks = 0 ; const int_T
gblNumModelInputs = 0 ; extern const char * gblInportFileName ; extern
rtInportTUtable * gblInportTUtables ; const int_T gblInportDataTypeIdx [ ] =
{ - 1 } ; const int_T gblInportDims [ ] = { - 1 } ; const int_T
gblInportComplex [ ] = { - 1 } ; const int_T gblInportInterpoFlag [ ] = { - 1
} ; const int_T gblInportContinuous [ ] = { - 1 } ; int_T enableFcnCallFlag [
] = { 1 , 1 , 1 , 1 } ; const char * raccelLoadInputsAndAperiodicHitTimes (
SimStruct * S , const char * inportFileName , int * matFileFormat ) { return
rt_RAccelReadInportsMatFile ( S , inportFileName , matFileFormat ) ; } const
real_T fast_powertrain_RGND = 0.0 ; B rtB ; DW rtDW ; static SimStruct
model_S ; SimStruct * const rtS = & model_S ; static real_T hiov1ctmx0 (
real_T x ) ; real_T look1_binlxpw ( real_T u0 , const real_T bp0 [ ] , const
real_T table [ ] , uint32_T maxIndex ) { real_T frac ; real_T yL_0d0 ;
uint32_T bpIdx ; uint32_T iLeft ; uint32_T iRght ; if ( u0 <= bp0 [ 0U ] ) {
iLeft = 0U ; frac = ( u0 - bp0 [ 0U ] ) / ( bp0 [ 1U ] - bp0 [ 0U ] ) ; }
else if ( u0 < bp0 [ maxIndex ] ) { bpIdx = maxIndex >> 1U ; iLeft = 0U ;
iRght = maxIndex ; while ( iRght - iLeft > 1U ) { if ( u0 < bp0 [ bpIdx ] ) {
iRght = bpIdx ; } else { iLeft = bpIdx ; } bpIdx = ( iRght + iLeft ) >> 1U ;
} frac = ( u0 - bp0 [ iLeft ] ) / ( bp0 [ iLeft + 1U ] - bp0 [ iLeft ] ) ; }
else { iLeft = maxIndex - 1U ; frac = ( u0 - bp0 [ maxIndex - 1U ] ) / ( bp0
[ maxIndex ] - bp0 [ maxIndex - 1U ] ) ; } yL_0d0 = table [ iLeft ] ; return
( table [ iLeft + 1U ] - yL_0d0 ) * frac + yL_0d0 ; } static real_T
hiov1ctmx0 ( real_T x ) { real_T r ; if ( muDoubleScalarIsNaN ( x ) ||
muDoubleScalarIsInf ( x ) ) { r = ( rtNaN ) ; } else if ( x == 0.0 ) { r =
0.0 ; } else { r = muDoubleScalarRem ( x , 2.0 ) ; if ( r == 0.0 ) { r = 0.0
; } else { if ( x < 0.0 ) { r += 2.0 ; } } } return r ; } void MdlInitialize
( void ) { boolean_T tmp ; rtDW . ebacjx4abi = rtP . itinit3_InitialCondition
; rtDW . ae4fdc50fw = rtP . Currentfilter5_InitialStates ; rtDW . cbffa5ojlz
= rtP . itinit_InitialCondition ; rtDW . jjhzuiuwr5 = 2 ; rtDW . kt2if2m30y =
1U ; if ( ssIsFirstInitCond ( rtS ) ) { tmp = slIsRapidAcceleratorSimulating
( ) ; if ( tmp ) { tmp = ssGetGlobalInitialStatesAvailable ( rtS ) ; rtDW .
kt2if2m30y = ( uint8_T ) ! tmp ; } else { rtDW . kt2if2m30y = 1U ; } } rtDW .
bkylhixnvg = rtP . DiscreteTimeIntegrator_IC ; rtDW . cfb4bptno0 = rtP .
Memory2_InitialCondition ; rtDW . mcqhrorlxr = rtP .
UnitDelay1_InitialCondition ; rtDW . hyrzihgqre = rtP .
UnitDelay2_InitialCondition ; rtDW . opkdjwnlyz = rtP .
UnitDelay2_InitialCondition_kplvr2c540 ; rtDW . nbkcuaxc3y = rtP .
Delay_InitialCondition ; rtDW . blkk50vpkb = rtP .
DiscreteTimeIntegrator_IC_bjhalm0xhc ; rtDW . ifljlxnawa = rtP .
UnitDelay_InitialCondition ; rtDW . df3h3bq4ax = rtP .
UnitDelay1_InitialCondition_b5qtmccqei ; rtDW . ew4rinximz = rtP .
DiscreteTimeIntegrator_IC_p2dyd1g5fi ; rtDW . nb0afwz3qd = rtP .
UnitDelay2_InitialCondition_mynahauzpq ; rtDW . ntr0qnnxwd = rtP .
UnitDelay3_InitialCondition ; rtDW . m01vpi11le = rtP .
UnitDelay3_InitialCondition_kgclqpwylc ; rtDW . p53jjbkpzn = rtP .
UnitDelay1_InitialCondition_pmpt1ejnb2 ; rtDW . mkxkhcmalu = rtP .
UnitDelay4_InitialCondition ; rtDW . jejzfwqaao = rtP .
UnitDelay_InitialCondition_ckvjp4gfil ; { SimStruct * rts = ssGetSFunction (
rtS , 0 ) ; sfcnInitializeConditions ( rts ) ; if ( ssGetErrorStatus ( rts )
!= ( NULL ) ) return ; } rtDW . k0okhesaat = rtP . DiscretePIController1_Init
; rtDW . fzr1ogugs2 = rtP . DiscretePIController2_Init ; rtDW . gepbsobs0a =
rtP . DiscretePIController2_Init_ofcbucrrnd ; rtDW . i4wxuhmfgf = rtP .
DiscretePIController3_Init ; rtDW . hzeqqg0jia = rtP .
DiscretePIController4_Init ; rtDW . f51eegc2bu = rtP .
DiscretePIController3_Init_lcdytxavmn ; rtDW . fxt15s43p4 = rtP .
DiscretePIController4_Init_ojyv5ifd0r ; rtDW . bljv3otj05 = rtP .
Memory_InitialCondition ; rtDW . b4zh5qri0d = rtP . Battery_SOC ; rtDW .
ic00z2hy2m = rtP . Memory17_InitialCondition ; rtDW . fzp55m5l14 = rtP .
Memory16_InitialCondition ; rtDW . bsqle4x1ip = rtP .
Memory15_InitialCondition ; rtDW . ehtf41cg10 = rtP .
Memory14_InitialCondition ; rtDW . p2pkpj1mv5 = rtP .
Memory13_InitialCondition ; rtDW . cn5opu2pzs = rtP .
Memory12_InitialCondition ; rtDW . fimioqcfmg = rtP .
Memory11_InitialCondition ; rtDW . ksxohwmcoh = rtP .
Memory10_InitialCondition ; rtDW . bv3zs25i1r = rtP .
Memory9_InitialCondition ; rtDW . nqhcy2vec4 = rtP . Battery_SOC ; rtDW .
p5fqadhn5b = rtP . Memory7_InitialCondition ; rtDW . ikqkqwjh3n = rtP .
Memory6_InitialCondition ; rtDW . awv1q3egsu = rtP . Memory5_InitialCondition
; rtDW . bhhdr2vx1r = rtP . Memory4_InitialCondition ; rtDW . m4yjnvjtaz =
rtP . Memory3_InitialCondition ; rtDW . pztkm2b5s5 = rtP .
Memory2_InitialCondition_nmqdt3zohg ; rtDW . hsvqv45oph = rtP .
Memory1_InitialCondition ; rtDW . cg2af1bnv1 = rtP .
Memory_InitialCondition_fgdsbtcau2 ; rtDW . jp23k4f2go = rtP .
Memory3_InitialCondition_npuv0s0rz0 ; rtDW . chezipvofm = rtP .
Memory2_InitialCondition_otmdfxbv2b ; rtDW . lypv2c215x = rtP .
Memory1_InitialCondition_eyxrd3us35 ; rtDW . dhksroq5rn = rtP .
Memory_InitialCondition_afcza04ewo ; rtDW . gyaphxw5hc = rtP .
itinit1_InitialCondition ; rtDW . g3gghz3gaz = rtP .
DiscreteTimeIntegrator_IC_muc3fdmls2 ; rtDW . abf3scvxey = rtP .
UnitDelay2_InitialCondition_bdexezlukf ; rtDW . h1wh3z4evx = rtP .
UnitDelay_InitialCondition_br0av5wkrv ; rtDW . bds32z0txa = rtP .
DiscreteTimeIntegrator1_IC ; rtDW . kalc0i12gy = 0 ; rtDW . c4quijr14v = rtP
. UnitDelay1_InitialCondition_gagfd2xjhh ; rtDW . knii4eahbq = 0.5 ; rtDW .
n0cer4zw0t = 0.0 ; } void MdlStart ( void ) { { bool
externalInputIsInDatasetFormat = false ; void * pISigstreamManager =
rt_GetISigstreamManager ( rtS ) ;
rtwISigstreamManagerGetInputIsInDatasetFormat ( pISigstreamManager , &
externalInputIsInDatasetFormat ) ; if ( externalInputIsInDatasetFormat ) { }
} { static int_T rt_ToWksWidths [ ] = { 2 } ; static int_T
rt_ToWksNumDimensions [ ] = { 1 } ; static int_T rt_ToWksDimensions [ ] = { 2
} ; static boolean_T rt_ToWksIsVarDims [ ] = { 0 } ; static void *
rt_ToWksCurrSigDims [ ] = { ( NULL ) } ; static int_T rt_ToWksCurrSigDimsSize
[ ] = { 4 } ; static BuiltInDTypeId rt_ToWksDataTypeIds [ ] = { SS_DOUBLE } ;
static int_T rt_ToWksComplexSignals [ ] = { 0 } ; static int_T
rt_ToWksFrameData [ ] = { 0 } ; static RTWPreprocessingFcnPtr
rt_ToWksLoggingPreprocessingFcnPtrs [ ] = { ( NULL ) } ; static const char_T
* rt_ToWksLabels [ ] = { "" } ; static RTWLogSignalInfo rt_ToWksSignalInfo =
{ 1 , rt_ToWksWidths , rt_ToWksNumDimensions , rt_ToWksDimensions ,
rt_ToWksIsVarDims , rt_ToWksCurrSigDims , rt_ToWksCurrSigDimsSize ,
rt_ToWksDataTypeIds , rt_ToWksComplexSignals , rt_ToWksFrameData ,
rt_ToWksLoggingPreprocessingFcnPtrs , { rt_ToWksLabels } , ( NULL ) , ( NULL
) , ( NULL ) , { ( NULL ) } , { ( NULL ) } , ( NULL ) , ( NULL ) } ; static
const char_T rt_ToWksBlockName [ ] = "fast_powertrain/To Workspace3" ; rtDW .
op222kfxbt . LoggedData = rt_CreateStructLogVar ( ssGetRTWLogInfo ( rtS ) ,
ssGetTStart ( rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS
) ) , "FC" , 0 , 0 , 1 , 0.001 , & rt_ToWksSignalInfo , rt_ToWksBlockName ) ;
if ( rtDW . op222kfxbt . LoggedData == ( NULL ) ) return ; ssCachePointer (
rtS , & ( rtDW . op222kfxbt . LoggedData ) ) ; } { static int_T
rt_ToWksWidths [ ] = { 1 } ; static int_T rt_ToWksNumDimensions [ ] = { 1 } ;
static int_T rt_ToWksDimensions [ ] = { 1 } ; static boolean_T
rt_ToWksIsVarDims [ ] = { 0 } ; static void * rt_ToWksCurrSigDims [ ] = { (
NULL ) } ; static int_T rt_ToWksCurrSigDimsSize [ ] = { 4 } ; static
BuiltInDTypeId rt_ToWksDataTypeIds [ ] = { SS_DOUBLE } ; static int_T
rt_ToWksComplexSignals [ ] = { 0 } ; static int_T rt_ToWksFrameData [ ] = { 0
} ; static RTWPreprocessingFcnPtr rt_ToWksLoggingPreprocessingFcnPtrs [ ] = {
( NULL ) } ; static const char_T * rt_ToWksLabels [ ] = { "" } ; static
RTWLogSignalInfo rt_ToWksSignalInfo = { 1 , rt_ToWksWidths ,
rt_ToWksNumDimensions , rt_ToWksDimensions , rt_ToWksIsVarDims ,
rt_ToWksCurrSigDims , rt_ToWksCurrSigDimsSize , rt_ToWksDataTypeIds ,
rt_ToWksComplexSignals , rt_ToWksFrameData ,
rt_ToWksLoggingPreprocessingFcnPtrs , { rt_ToWksLabels } , ( NULL ) , ( NULL
) , ( NULL ) , { ( NULL ) } , { ( NULL ) } , ( NULL ) , ( NULL ) } ; static
const char_T rt_ToWksBlockName [ ] = "fast_powertrain/To Workspace4" ; rtDW .
lqgtrexdqd . LoggedData = rt_CreateStructLogVar ( ssGetRTWLogInfo ( rtS ) ,
ssGetTStart ( rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS
) ) , "Batt" , 0 , 0 , 1 , 0.001 , & rt_ToWksSignalInfo , rt_ToWksBlockName )
; if ( rtDW . lqgtrexdqd . LoggedData == ( NULL ) ) return ; ssCachePointer (
rtS , & ( rtDW . lqgtrexdqd . LoggedData ) ) ; } { SimStruct * rts =
ssGetSFunction ( rtS , 0 ) ; sfcnStart ( rts ) ; if ( ssGetErrorStatus ( rts
) != ( NULL ) ) return ; } MdlInitialize ( ) ; } void MdlOutputs ( int_T tid
) { static const int8_T b_e [ 24 ] = { 1 , 2 , 3 , 4 , 1 , 2 , 3 , 4 , 1 , 2
, 3 , 4 , 1 , 1 , 1 , 1 , 2 , 2 , 2 , 2 , 3 , 3 , 3 , 3 } ; static const
int8_T b_p [ 12 ] = { 1 , 2 , 2 , 4 , 3 , 1 , 2 , 2 , 3 , 1 , 1 , 2 } ;
real_T apd5tvlmvq [ 12 ] ; real_T outputMFCache [ 8 ] ; real_T inputMFCache [
7 ] ; real_T P_H2 ; real_T P_O2 ; real_T bpn0ye43tk ; real_T c0h2wv1ka1 ;
real_T cghr0c1um4 ; real_T dympzpkrgu ; real_T evtimpzdcg ; real_T ibatdAv2 ;
real_T ikoled0vgw ; real_T lz43o1ysvx ; real_T n3rh31a5nj ; real_T osqmdqbygi
; real_T poa1xlshpn ; int32_T s ; int8_T b ; boolean_T buzsg0vune ; boolean_T
jljm1xonmp ; ikoled0vgw = rtP . R2_Gain * rtDW . ebacjx4abi ; evtimpzdcg =
rtP . Currentfilter5_NumCoef * rtDW . ae4fdc50fw ; rtB . nzprtrw2gw = (
evtimpzdcg > rtP . Constant_Value ) ; if ( rtDW . kt2if2m30y != 0 ) { rtDW .
ns3jml1yrn = rtDW . cbffa5ojlz ; if ( rtDW . ns3jml1yrn >= rtP .
inti_UpperSat ) { rtDW . ns3jml1yrn = rtP . inti_UpperSat ; } else { if (
rtDW . ns3jml1yrn <= rtP . inti_LowerSat ) { rtDW . ns3jml1yrn = rtP .
inti_LowerSat ; } } } if ( ( rtB . nzprtrw2gw > 0.0 ) && ( rtDW . jjhzuiuwr5
<= 0 ) ) { rtDW . ns3jml1yrn = rtDW . cbffa5ojlz ; if ( rtDW . ns3jml1yrn >=
rtP . inti_UpperSat ) { rtDW . ns3jml1yrn = rtP . inti_UpperSat ; } else { if
( rtDW . ns3jml1yrn <= rtP . inti_LowerSat ) { rtDW . ns3jml1yrn = rtP .
inti_LowerSat ; } } } if ( rtDW . ns3jml1yrn >= rtP . inti_UpperSat ) { rtDW
. ns3jml1yrn = rtP . inti_UpperSat ; } else { if ( rtDW . ns3jml1yrn <= rtP .
inti_LowerSat ) { rtDW . ns3jml1yrn = rtP . inti_LowerSat ; } } n3rh31a5nj =
rtP . Gain_Gain * rtDW . ns3jml1yrn ; if ( n3rh31a5nj > ikoled0vgw ) {
dympzpkrgu = ikoled0vgw ; } else if ( n3rh31a5nj < rtP . Constant9_Value ) {
dympzpkrgu = rtP . Constant9_Value ; } else { dympzpkrgu = n3rh31a5nj ; } if
( ! ( 1.000001 * ikoled0vgw * 0.96711798839458663 / 0.9999 <= dympzpkrgu ) )
{ ikoled0vgw = dympzpkrgu ; } dympzpkrgu = rtP . R3_Gain * rtDW . ebacjx4abi
; if ( ! ( n3rh31a5nj > dympzpkrgu ) ) { dympzpkrgu = - dympzpkrgu * 0.999 *
0.1 * 0.9999 ; if ( ! ( n3rh31a5nj < dympzpkrgu ) ) { dympzpkrgu = n3rh31a5nj
; } } switch ( ( int32_T ) rtP . Battery_BatType ) { case 1 : n3rh31a5nj = -
( ( real_T ) ( evtimpzdcg < rtP . Constant_Value_lc2t2ikfiz ) * rtP .
Constant4_Value ) * 0.023973807375425208 * ( rtP . Constant4_Value *
evtimpzdcg ) * ( 15.509999999999961 / ( rtP . Constant4_Value * dympzpkrgu +
1.5509999999999962 ) ) ; dympzpkrgu = rtDW . bkylhixnvg ; break ; case 2 :
n3rh31a5nj = rtP . Constant1_Value_ixcqqm1d4w * rtDW . ebacjx4abi ;
n3rh31a5nj = - ( ( real_T ) ( evtimpzdcg < rtP . Constant_Value_lc2t2ikfiz )
* rtP . Constant1_Value_ixcqqm1d4w ) * 0.023973807375425208 * ( rtP .
Constant1_Value_ixcqqm1d4w * evtimpzdcg ) * n3rh31a5nj / ( rtP .
Constant1_Value_ixcqqm1d4w * dympzpkrgu + n3rh31a5nj * 0.1 ) ; if (
ikoled0vgw > rtP . Saturation_UpperSat ) { dympzpkrgu = rtP .
Saturation_UpperSat ; } else if ( ikoled0vgw < rtP . Saturation_LowerSat ) {
dympzpkrgu = rtP . Saturation_LowerSat ; } else { dympzpkrgu = ikoled0vgw ; }
dympzpkrgu = muDoubleScalarExp ( - 4.07079646017699 * dympzpkrgu ) *
4.0308462269645284 ; break ; case 3 : n3rh31a5nj = - ( ( real_T ) (
evtimpzdcg < rtP . Constant_Value_lc2t2ikfiz ) * rtP .
Constant3_Value_nmyyw0epx1 ) * 0.023973807375425208 * ( rtP .
Constant3_Value_nmyyw0epx1 * evtimpzdcg ) * ( 15.509999999999961 / (
muDoubleScalarAbs ( rtP . Constant3_Value_nmyyw0epx1 * dympzpkrgu ) +
1.5509999999999962 ) ) ; dympzpkrgu = rtDW . bkylhixnvg ; break ; default :
n3rh31a5nj = - ( ( real_T ) ( evtimpzdcg < rtP . Constant_Value_lc2t2ikfiz )
* rtP . Constant2_Value_m10aoab32w ) * 0.023973807375425208 * ( rtP .
Constant2_Value_m10aoab32w * evtimpzdcg ) * ( 15.509999999999961 / (
muDoubleScalarAbs ( rtP . Constant2_Value_m10aoab32w * dympzpkrgu ) +
1.5509999999999962 ) ) ; dympzpkrgu = rtDW . bkylhixnvg ; break ; }
evtimpzdcg = ( ( ( ( - rtB . nzprtrw2gw * 0.023973807375425208 * evtimpzdcg *
rtDW . ebacjx4abi / ( rtDW . ebacjx4abi - ikoled0vgw ) + -
0.023973807375425208 * rtDW . ebacjx4abi / ( rtDW . ebacjx4abi - ikoled0vgw )
* ikoled0vgw ) + n3rh31a5nj ) + dympzpkrgu ) + - 0.0 * ikoled0vgw ) + rtP .
Constant_Value_m3ckpdnl3e ; if ( evtimpzdcg > rtP .
Constant1_Value_bcnppbahb4 ) { rtB . klfwarvagc = rtP .
Constant1_Value_bcnppbahb4 ; } else if ( evtimpzdcg < rtDW . cfb4bptno0 ) {
rtB . klfwarvagc = rtDW . cfb4bptno0 ; } else { rtB . klfwarvagc = evtimpzdcg
; } rtB . i0ujncnh35 = rtDW . mcqhrorlxr ; rtB . dplapzekhr = rtDW .
hyrzihgqre ; rtB . b2m0nyy1iq = rtDW . opkdjwnlyz ; if ( rtDW . nbkcuaxc3y >
rtP . Saturation_UpperSat_gvrgxklgqx ) { evtimpzdcg = rtP .
Saturation_UpperSat_gvrgxklgqx ; } else if ( rtDW . nbkcuaxc3y < rtP .
Saturation_LowerSat_cndq0w2uve ) { evtimpzdcg = rtP .
Saturation_LowerSat_cndq0w2uve ; } else { evtimpzdcg = rtDW . nbkcuaxc3y ; }
n3rh31a5nj = rtDW . blkk50vpkb * rtDW . ifljlxnawa ; dympzpkrgu = evtimpzdcg
/ 78.4 ; P_H2 = ( muDoubleScalarExp ( - ( 1.635 * dympzpkrgu /
2044.2367985553271 ) ) * 34.2846722597678 - 1.0 ) * 0.02114647602598696 ;
P_O2 = ( muDoubleScalarExp ( - ( 4.192 * dympzpkrgu / 2044.2367985553271 ) )
* 23.644601558460554 - 1.0 ) * 0.04229295205197392 ; if ( dympzpkrgu /
0.57397959183673464 < 1.0 ) { osqmdqbygi = muDoubleScalarLog ( 1.0 -
dympzpkrgu / 0.57397959183673464 ) * 0.019592739868891536 -
0.01019279637112634 ; } else { osqmdqbygi = muDoubleScalarLog ( dympzpkrgu /
0.57397959183673464 ) * 0.019592739868891536 - 0.01019279637112634 ; }
lz43o1ysvx = - evtimpzdcg * 0.00030510673175708632 ; bpn0ye43tk =
muDoubleScalarLog ( P_H2 * muDoubleScalarSqrt ( P_O2 ) ) *
0.013061826579261027 + 1.22475 ; if ( - 0.000187 * muDoubleScalarLog (
evtimpzdcg ) > 0.0 ) { c0h2wv1ka1 = 0.0 ; } else if ( - 0.000187 *
muDoubleScalarLog ( evtimpzdcg ) < - 1.2 ) { c0h2wv1ka1 = - 1.2 ; } else {
c0h2wv1ka1 = - 0.000187 * muDoubleScalarLog ( evtimpzdcg ) ; } rtB .
pmkgps0zyu = ( 1.0 - n3rh31a5nj / ( - ( ( ( ( muDoubleScalarLog ( P_H2 /
1.09E+6 * 0.77569205792374141 ) * 4.3E-5 + 0.0039196634733096071 ) +
muDoubleScalarLog ( P_O2 / 5.08E+6 * 5.1693714943699343 ) * 7.4E-5 ) +
c0h2wv1ka1 ) * 303.15 + - 0.9514 ) - osqmdqbygi ) ) * ( evtimpzdcg / 2.0 ) ;
rtB . crs0im5dqp = 1.0 ; if ( dympzpkrgu / 0.57397959183673464 >= 1.0 ) {
osqmdqbygi = 0.0 ; lz43o1ysvx = 0.0 ; rtB . pmkgps0zyu = 0.0 ; bpn0ye43tk = -
35.0 * evtimpzdcg ; if ( bpn0ye43tk <= 0.0 ) { bpn0ye43tk = 0.0 ; } rtB .
crs0im5dqp = 0.0 ; } evtimpzdcg = ( ( ( bpn0ye43tk + lz43o1ysvx ) -
n3rh31a5nj ) + osqmdqbygi ) * rtP . Multiply_Gain ; if ( evtimpzdcg > rtP .
Constant_Value_kfm5xzok4i ) { rtB . dg1zqpobap = rtP .
Constant_Value_kfm5xzok4i ; } else { n3rh31a5nj = 0.00030510673175708632 *
rtDW . df3h3bq4ax ; if ( evtimpzdcg < n3rh31a5nj ) { rtB . dg1zqpobap =
n3rh31a5nj ; } else { rtB . dg1zqpobap = evtimpzdcg ; } } n3rh31a5nj = rtDW .
ew4rinximz + rtP . Constant19_Value ; if ( n3rh31a5nj > rtP .
Saturation_UpperSat_e2k0qdtv2s ) { n3rh31a5nj = rtP .
Saturation_UpperSat_e2k0qdtv2s ; } else { if ( n3rh31a5nj < rtP .
Saturation_LowerSat_d5xrshbz0z ) { n3rh31a5nj = rtP .
Saturation_LowerSat_d5xrshbz0z ; } } evtimpzdcg = 2.5692606467235652 /
n3rh31a5nj * muDoubleScalarAsinh ( 0.24105519058637831 * n3rh31a5nj ) + rtP .
Constant_Value_oibu00r03f ; rtB . m2zun0bmq0 = n3rh31a5nj * evtimpzdcg ; rtB
. bnsiwqbz4c = rtDW . nb0afwz3qd ; rtB . nd5vhw3hdp = rtDW . ntr0qnnxwd ; rtB
. pkslvtv3r5 = rtDW . m01vpi11le ; rtB . cp1s511zvk = ( ( ( ( rtP .
Constant9_Value_b1nk1ggw4w + 273.15 ) - 298.15 ) * rtP .
Constant5_Value_k3metw3ccu + rtP . PVMODULE1_Isc ) * rtP . PVMODULE1_Npar *
rtP . Constant10_Value / 1000.0 * rtP . PVMODULE1_Npar - ( rtDW . mkxkhcmalu
* rtP . PVMODULE1_Rs + rtDW . p53jjbkpzn ) / rtP . PVMODULE1_Rsh ) - rtP .
PVMODULE1_Isc / ( muDoubleScalarExp ( 1.602E-19 * rtP . PVMODULE1_Voc / ( rtP
. PVMODULE1_Ncell * 1.3806E-23 * rtP . PVMODULE1_df * ( rtP .
Constant9_Value_b1nk1ggw4w + 273.15 ) ) ) - 1.0 ) * muDoubleScalarPower ( (
rtP . Constant9_Value_b1nk1ggw4w + 273.15 ) / 298.15 , 3.0 ) *
muDoubleScalarExp ( ( 1.0 / ( rtP . Constant9_Value_b1nk1ggw4w + 273.15 ) -
0.0033540164346805303 ) * ( 1.7958419999999999E-19 / ( 8.617333262145E-5 *
rtP . PVMODULE1_df ) ) ) * rtP . PVMODULE1_Npar * ( muDoubleScalarExp ( (
rtDW . mkxkhcmalu * rtP . PVMODULE1_Rs / rtP . PVMODULE1_Npar + rtDW .
p53jjbkpzn / rtP . PVMODULE1_Nser ) / ( ( rtP . Constant9_Value_b1nk1ggw4w +
273.15 ) * 8.6179775280898876E-5 * rtP . PVMODULE1_df * rtP . PVMODULE1_Ncell
) ) - 1.0 ) ; n3rh31a5nj = look1_binlxpw ( ssGetT ( rtS ) , rtP . t , rtP . w
, 180719U ) ; dympzpkrgu = rtB . b11tooymbq / n3rh31a5nj ; if ( ! (
muDoubleScalarAbs ( dympzpkrgu ) > rtP . VariableResistor_Rabsmin ) ) { if (
muDoubleScalarSign ( dympzpkrgu ) > rtP . Switch1_Threshold ) { dympzpkrgu =
rtP . VariableResistor_Rabsmin ; } else { dympzpkrgu = - rtP .
VariableResistor_Rabsmin ; } } rtB . mdng4h4wi3 = rtP . Constant5_Value /
dympzpkrgu ; rtB . akgc550kdx = rtDW . jejzfwqaao ; rtB . aunoa00r4h = rtB .
mdng4h4wi3 - rtB . akgc550kdx ; { SimStruct * rts = ssGetSFunction ( rtS , 0
) ; sfcnOutputs ( rts , 0 ) ; } P_O2 = rtP .
donotdeletethisgain_Gain_jjlpkzumz0 * rtB . ds4vmpgjgq [ 24 ] ; osqmdqbygi =
rtP . donotdeletethisgain_Gain_fbjp1xgx2i * rtB . ds4vmpgjgq [ 13 ] ;
cghr0c1um4 = rtP . Constant6_Value - osqmdqbygi ; rtB . lwbnk1tqoe = rtP .
DiscretePIController1_Ki * cghr0c1um4 ; dympzpkrgu = rtP .
donotdeletethisgain_Gain_pnt2zcpibt * rtB . ds4vmpgjgq [ 20 ] ; P_H2 = rtP .
Constant6_Value - dympzpkrgu ; lz43o1ysvx = rtP . DiscretePIController2_Kp *
P_H2 + rtDW . gepbsobs0a ; if ( lz43o1ysvx > rtP .
Saturation2_UpperSat_hr00iu210k ) { lz43o1ysvx = rtP .
Saturation2_UpperSat_hr00iu210k ; } else { if ( lz43o1ysvx < rtP .
Saturation2_LowerSat_kq0ryizxeu ) { lz43o1ysvx = rtP .
Saturation2_LowerSat_kq0ryizxeu ; } } if ( lz43o1ysvx > rtP .
Saturation7_UpperSat ) { c0h2wv1ka1 = rtP . Saturation7_UpperSat ; } else if
( lz43o1ysvx < rtP . Saturation7_LowerSat ) { c0h2wv1ka1 = rtP .
Saturation7_LowerSat ; } else { c0h2wv1ka1 = lz43o1ysvx ; } bpn0ye43tk = rtP
. donotdeletethisgain_Gain_pc1oacxtz5 * rtB . ds4vmpgjgq [ 12 ] ; poa1xlshpn
= rtP . DiscretePIController1_Kp * cghr0c1um4 + rtDW . k0okhesaat ;
cghr0c1um4 = bpn0ye43tk * rtP . BidirectionalBOOSTBUCKBattfast_n_boost ; if (
poa1xlshpn > rtP . Saturation2_UpperSat ) { poa1xlshpn = rtP .
Saturation2_UpperSat ; } else { if ( poa1xlshpn < rtP . Saturation2_LowerSat
) { poa1xlshpn = rtP . Saturation2_LowerSat ; } } if ( cghr0c1um4 > rtP .
Saturation4_UpperSat ) { cghr0c1um4 = rtP . Saturation4_UpperSat ; } else {
if ( cghr0c1um4 < rtP . Saturation4_LowerSat ) { cghr0c1um4 = rtP .
Saturation4_LowerSat ; } } cghr0c1um4 = ( rtP .
donotdeletethisgain_Gain_kzwtp4lcwh * rtB . ds4vmpgjgq [ 23 ] + poa1xlshpn )
* ( osqmdqbygi / cghr0c1um4 ) ; if ( ! ( cghr0c1um4 > c0h2wv1ka1 ) ) { if (
cghr0c1um4 < rtP . Constant2_Value ) { c0h2wv1ka1 = rtP . Constant2_Value ; }
else { c0h2wv1ka1 = cghr0c1um4 ; } } c0h2wv1ka1 -= P_O2 ; rtB . lnggl4hxqa =
rtP . DiscretePIController2_Ki * c0h2wv1ka1 ; poa1xlshpn = rtP .
Constant6_Value - bpn0ye43tk ; rtB . cnvh3z11oj = rtP .
DiscretePIController3_Ki * poa1xlshpn ; cghr0c1um4 = rtP .
Multiply_Gain_dppzkzoubi * lz43o1ysvx ; if ( cghr0c1um4 > rtP .
Saturation6_UpperSat ) { cghr0c1um4 = rtP . Saturation6_UpperSat ; } else {
if ( cghr0c1um4 < rtP . Saturation6_LowerSat ) { cghr0c1um4 = rtP .
Saturation6_LowerSat ; } } poa1xlshpn = rtP . DiscretePIController3_Kp *
poa1xlshpn + rtDW . i4wxuhmfgf ; if ( poa1xlshpn > rtP .
Saturation2_UpperSat_ldjga0hth1 ) { poa1xlshpn = rtP .
Saturation2_UpperSat_ldjga0hth1 ; } else { if ( poa1xlshpn < rtP .
Saturation2_LowerSat_ebdt35gruq ) { poa1xlshpn = rtP .
Saturation2_LowerSat_ebdt35gruq ; } } poa1xlshpn -= rtP .
donotdeletethisgain_Gain * rtB . ds4vmpgjgq [ 22 ] ; if ( ! ( poa1xlshpn >
cghr0c1um4 ) ) { if ( poa1xlshpn < rtP . Constant1_Value ) { cghr0c1um4 = rtP
. Constant1_Value ; } else { cghr0c1um4 = poa1xlshpn ; } } cghr0c1um4 += P_O2
; rtB . caydqvbppv = rtP . DiscretePIController4_Ki * cghr0c1um4 ; jljm1xonmp
= ( lz43o1ysvx < rtP . Constant8_Value_iqk3wb1evy ) ; poa1xlshpn = rtP .
DiscretePIController4_Kp * cghr0c1um4 + rtDW . hzeqqg0jia ; if ( poa1xlshpn >
rtP . Saturation2_UpperSat_pjhhcyvloo ) { poa1xlshpn = rtP .
Saturation2_UpperSat_pjhhcyvloo ; } else { if ( poa1xlshpn < rtP .
Saturation2_LowerSat_j0yt25ma5v ) { poa1xlshpn = rtP .
Saturation2_LowerSat_j0yt25ma5v ; } } if ( osqmdqbygi > rtP .
Saturation_UpperSat_jsjpgzsi1y ) { lz43o1ysvx = rtP .
Saturation_UpperSat_jsjpgzsi1y ; } else if ( osqmdqbygi < rtP .
Saturation_LowerSat_ebjhnxsenp ) { lz43o1ysvx = rtP .
Saturation_LowerSat_ebjhnxsenp ; } else { lz43o1ysvx = osqmdqbygi ; }
poa1xlshpn = ( poa1xlshpn + bpn0ye43tk ) / lz43o1ysvx ; cghr0c1um4 = rtP .
DiscretePIController2_Kp_jtir0rv5nd * c0h2wv1ka1 + rtDW . fzr1ogugs2 ; if (
cghr0c1um4 > rtP . Saturation2_UpperSat_csxykusiqi ) { cghr0c1um4 = rtP .
Saturation2_UpperSat_csxykusiqi ; } else { if ( cghr0c1um4 < rtP .
Saturation2_LowerSat_djxegxbmlp ) { cghr0c1um4 = rtP .
Saturation2_LowerSat_djxegxbmlp ; } } if ( osqmdqbygi > rtP .
Saturation2_UpperSat_amgcitvjo2 ) { lz43o1ysvx = rtP .
Saturation2_UpperSat_amgcitvjo2 ; } else if ( osqmdqbygi < rtP .
Saturation2_LowerSat_lkim1nsn2b ) { lz43o1ysvx = rtP .
Saturation2_LowerSat_lkim1nsn2b ; } else { lz43o1ysvx = osqmdqbygi ; }
cghr0c1um4 = rtP . Constant_Value_ffncqspxq4 - ( bpn0ye43tk - cghr0c1um4 ) /
lz43o1ysvx ; if ( poa1xlshpn > rtP . Saturation1_UpperSat ) { poa1xlshpn =
rtP . Saturation1_UpperSat ; } else { if ( poa1xlshpn < rtP .
Saturation1_LowerSat ) { poa1xlshpn = rtP . Saturation1_LowerSat ; } } if (
cghr0c1um4 > rtP . Saturation3_UpperSat ) { cghr0c1um4 = rtP .
Saturation3_UpperSat ; } else { if ( cghr0c1um4 < rtP . Saturation3_LowerSat
) { cghr0c1um4 = rtP . Saturation3_LowerSat ; } } lz43o1ysvx = ( rtP .
Constant3_Value - ( real_T ) jljm1xonmp ) * cghr0c1um4 + ( real_T )
jljm1xonmp * poa1xlshpn ; if ( ! jljm1xonmp ) { rtB . e2chijmfh2 = ( 1.0 -
lz43o1ysvx ) * osqmdqbygi ; rtB . ajuoykrpve = ( 1.0 - lz43o1ysvx ) * P_O2 *
rtP . BidirectionalBOOSTBUCKBattfast_n_boost ; } else { rtB . e2chijmfh2 =
osqmdqbygi * lz43o1ysvx ; rtB . ajuoykrpve = P_O2 * lz43o1ysvx / rtP .
BidirectionalBOOSTBUCKBattfast_n_buck ; } rtB . kx2yvfrvbs = rtP .
donotdeletethisgain_Gain_fiwukkn2yr * rtB . ds4vmpgjgq [ 28 ] ; rtB .
i4u1u0nk00 = rtP . donotdeletethisgain_Gain_hbuypofava * rtB . ds4vmpgjgq [
34 ] ; rtB . npdclyuhqf = rtP . donotdeletethisgain_Gain_ebxbsb35rt * rtB .
ds4vmpgjgq [ 31 ] * dympzpkrgu ; poa1xlshpn = ( 1.0 - ikoled0vgw / ( rtP .
R4_Gain * rtDW . ebacjx4abi ) ) * 100.0 ; if ( poa1xlshpn > rtP .
Saturation_UpperSat_ms3dxtbvew ) { rtB . jqk43gypqg = rtP .
Saturation_UpperSat_ms3dxtbvew ; } else if ( poa1xlshpn < rtP .
Saturation_LowerSat_p3nlfvz151 ) { rtB . jqk43gypqg = rtP .
Saturation_LowerSat_p3nlfvz151 ; } else { rtB . jqk43gypqg = poa1xlshpn ; }
rtB . pkp0sjqqg3 = rtP . Multiply3_Gain * rtB . jqk43gypqg ; bpn0ye43tk = (
n3rh31a5nj - rtB . npdclyuhqf ) * rtP . Multiply2_Gain ; P_O2 = 0.0 ;
inputMFCache [ 0 ] = muDoubleScalarExp ( - ( ( bpn0ye43tk - 0.581817557957467
) * ( bpn0ye43tk - 0.581817557957467 ) ) / 1.2723031177304711 ) ;
inputMFCache [ 1 ] = muDoubleScalarExp ( - ( ( bpn0ye43tk - 0.581200711689766
) * ( bpn0ye43tk - 0.581200711689766 ) ) / 0.60361583762949134 ) ;
inputMFCache [ 2 ] = muDoubleScalarExp ( - ( ( bpn0ye43tk - 0.26186596932149
) * ( bpn0ye43tk - 0.26186596932149 ) ) / 0.54184671130284889 ) ;
inputMFCache [ 3 ] = muDoubleScalarExp ( - ( ( bpn0ye43tk - 0.701958361808373
) * ( bpn0ye43tk - 0.701958361808373 ) ) / 0.090880078917346716 ) ;
inputMFCache [ 4 ] = muDoubleScalarExp ( - ( ( rtB . pkp0sjqqg3 -
0.691039393320396 ) * ( rtB . pkp0sjqqg3 - 0.691039393320396 ) ) /
0.30504945984178128 ) ; inputMFCache [ 5 ] = muDoubleScalarExp ( - ( ( rtB .
pkp0sjqqg3 - 0.468488935462738 ) * ( rtB . pkp0sjqqg3 - 0.468488935462738 ) )
/ 0.4254266971780265 ) ; inputMFCache [ 6 ] = muDoubleScalarExp ( - ( ( rtB .
pkp0sjqqg3 - 0.36580773500089 ) * ( rtB . pkp0sjqqg3 - 0.36580773500089 ) ) /
0.34895906569881247 ) ; for ( s = 0 ; s < 12 ; s ++ ) { lz43o1ysvx =
inputMFCache [ b_e [ s ] - 1 ] ; if ( 1.0 > lz43o1ysvx ) { c0h2wv1ka1 =
lz43o1ysvx ; } else { c0h2wv1ka1 = 1.0 ; } lz43o1ysvx = inputMFCache [ b_e [
s + 12 ] + 3 ] ; if ( ( c0h2wv1ka1 > lz43o1ysvx ) || ( muDoubleScalarIsNaN (
c0h2wv1ka1 ) && ( ! muDoubleScalarIsNaN ( lz43o1ysvx ) ) ) ) { c0h2wv1ka1 =
lz43o1ysvx ; } P_O2 += c0h2wv1ka1 ; apd5tvlmvq [ s ] = c0h2wv1ka1 ; }
bpn0ye43tk = 0.0 ; outputMFCache [ 0 ] = muDoubleScalarExp ( - ( ( rtP .
OutputSamplePoints_Value [ 0 ] - 0.458163785492621 ) * ( rtP .
OutputSamplePoints_Value [ 0 ] - 0.458163785492621 ) ) / 0.57469979880055444
) ; outputMFCache [ 1 ] = muDoubleScalarExp ( - ( ( rtP .
OutputSamplePoints_Value [ 0 ] - 0.485752092545331 ) * ( rtP .
OutputSamplePoints_Value [ 0 ] - 0.485752092545331 ) ) / 0.092631531919254939
) ; outputMFCache [ 2 ] = muDoubleScalarExp ( - ( ( rtP .
OutputSamplePoints_Value [ 0 ] - 0.263038299935429 ) * ( rtP .
OutputSamplePoints_Value [ 0 ] - 0.263038299935429 ) ) / 0.36562694302305776
) ; outputMFCache [ 3 ] = muDoubleScalarExp ( - ( ( rtP .
OutputSamplePoints_Value [ 0 ] - 0.433029391937309 ) * ( rtP .
OutputSamplePoints_Value [ 0 ] - 0.433029391937309 ) ) / 0.11944238797715841
) ; lz43o1ysvx = 0.0 ; outputMFCache [ 4 ] = muDoubleScalarExp ( - ( ( rtP .
OutputSamplePoints_Value [ 1 ] - 0.458163785492621 ) * ( rtP .
OutputSamplePoints_Value [ 1 ] - 0.458163785492621 ) ) / 0.57469979880055444
) ; outputMFCache [ 5 ] = muDoubleScalarExp ( - ( ( rtP .
OutputSamplePoints_Value [ 1 ] - 0.485752092545331 ) * ( rtP .
OutputSamplePoints_Value [ 1 ] - 0.485752092545331 ) ) / 0.092631531919254939
) ; outputMFCache [ 6 ] = muDoubleScalarExp ( - ( ( rtP .
OutputSamplePoints_Value [ 1 ] - 0.263038299935429 ) * ( rtP .
OutputSamplePoints_Value [ 1 ] - 0.263038299935429 ) ) / 0.36562694302305776
) ; outputMFCache [ 7 ] = muDoubleScalarExp ( - ( ( rtP .
OutputSamplePoints_Value [ 1 ] - 0.433029391937309 ) * ( rtP .
OutputSamplePoints_Value [ 1 ] - 0.433029391937309 ) ) / 0.11944238797715841
) ; for ( s = 0 ; s < 12 ; s ++ ) { c0h2wv1ka1 = apd5tvlmvq [ s ] ; b = b_p [
s ] ; osqmdqbygi = outputMFCache [ b - 1 ] ; if ( ( osqmdqbygi > c0h2wv1ka1 )
|| ( muDoubleScalarIsNaN ( osqmdqbygi ) && ( ! muDoubleScalarIsNaN (
c0h2wv1ka1 ) ) ) ) { osqmdqbygi = c0h2wv1ka1 ; } if ( ( bpn0ye43tk <
osqmdqbygi ) || ( muDoubleScalarIsNaN ( bpn0ye43tk ) && ( !
muDoubleScalarIsNaN ( osqmdqbygi ) ) ) ) { } else { osqmdqbygi = bpn0ye43tk ;
} bpn0ye43tk = osqmdqbygi ; osqmdqbygi = outputMFCache [ b + 3 ] ; if ( (
osqmdqbygi > c0h2wv1ka1 ) || ( muDoubleScalarIsNaN ( osqmdqbygi ) && ( !
muDoubleScalarIsNaN ( c0h2wv1ka1 ) ) ) ) { osqmdqbygi = c0h2wv1ka1 ; } if ( (
lz43o1ysvx < osqmdqbygi ) || ( muDoubleScalarIsNaN ( lz43o1ysvx ) && ( !
muDoubleScalarIsNaN ( osqmdqbygi ) ) ) ) { } else { osqmdqbygi = lz43o1ysvx ;
} lz43o1ysvx = osqmdqbygi ; } if ( P_O2 == 0.0 ) { P_O2 = 0.5 ; } else {
osqmdqbygi = bpn0ye43tk + lz43o1ysvx ; if ( osqmdqbygi == 0.0 ) { P_O2 = (
rtP . OutputSamplePoints_Value [ 0 ] + rtP . OutputSamplePoints_Value [ 1 ] )
/ 2.0 ; } else { P_O2 = ( rtP . OutputSamplePoints_Value [ 0 ] * bpn0ye43tk +
rtP . OutputSamplePoints_Value [ 1 ] * lz43o1ysvx ) * ( 1.0 / osqmdqbygi ) ;
} } rtB . iuiyd4knlc = rtP . donotdeletethisgain_Gain_liz3gjfhcs * rtB .
ds4vmpgjgq [ 18 ] ; P_O2 = P_O2 * rtP . Constant_Value_embijewti4 / rtB .
iuiyd4knlc ; jljm1xonmp = ( rtB . i4u1u0nk00 < P_O2 ) ; buzsg0vune = (
n3rh31a5nj < rtP . Constant7_Value ) ; rtB . bbivpaarxt = rtP .
donotdeletethisgain_Gain_ntvbbpumog * rtB . ds4vmpgjgq [ 16 ] ; rtB .
nh1zxcsjip = ( ( ( real_T ) ! jljm1xonmp * rtP . Constant6_Value + ( real_T )
jljm1xonmp * rtP . Constant4_Value_chdfctpggi ) * ( real_T ) ! buzsg0vune + (
real_T ) buzsg0vune * rtP . Constant6_Value ) - rtB . bbivpaarxt ; rtB .
gvxuq2ivcx = rtP . DiscretePIController3_Ki_catboe4e3q * rtB . nh1zxcsjip ;
P_O2 *= rtB . nkylddyjyp ; osqmdqbygi = rtP .
donotdeletethisgain_Gain_mnd4o03d53 * rtB . ds4vmpgjgq [ 17 ] ; poa1xlshpn =
rtP . DiscretePIController3_Kp_ppecbhclte * rtB . nh1zxcsjip + rtDW .
f51eegc2bu ; cghr0c1um4 = osqmdqbygi * rtP . BoostFCfast_n ; if ( poa1xlshpn
> rtP . Saturation2_UpperSat_fkd04pf2k1 ) { poa1xlshpn = rtP .
Saturation2_UpperSat_fkd04pf2k1 ; } else { if ( poa1xlshpn < rtP .
Saturation2_LowerSat_mzohmr2g2n ) { poa1xlshpn = rtP .
Saturation2_LowerSat_mzohmr2g2n ; } } if ( cghr0c1um4 > rtP .
Saturation2_UpperSat_aip5hjdd2y ) { cghr0c1um4 = rtP .
Saturation2_UpperSat_aip5hjdd2y ; } else { if ( cghr0c1um4 < rtP .
Saturation2_LowerSat_czr0zyeyrx ) { cghr0c1um4 = rtP .
Saturation2_LowerSat_czr0zyeyrx ; } } rtB . evwgggutgq = ( rtP .
donotdeletethisgain_Gain_bnrrpg33he * rtB . ds4vmpgjgq [ 29 ] + poa1xlshpn )
* ( rtB . bbivpaarxt / cghr0c1um4 ) ; if ( rtB . evwgggutgq < rtP .
Constant1_Value_avw5uhdxx5 ) { rtB . pd50rghzbf = rtP .
Constant1_Value_avw5uhdxx5 ; } else { rtB . pd50rghzbf = rtB . evwgggutgq ; }
if ( ! ( rtB . evwgggutgq > P_O2 ) ) { P_O2 = rtB . pd50rghzbf ; } rtB .
k4spxtemch = P_O2 - rtB . kx2yvfrvbs ; rtB . oaypl0xy40 = rtP .
DiscretePIController4_Ki_ksfhmxpwtu * rtB . k4spxtemch ; poa1xlshpn = rtP .
DiscretePIController4_Kp_crtfhdlpjf * rtB . k4spxtemch + rtDW . fxt15s43p4 ;
if ( poa1xlshpn > rtP . Saturation2_UpperSat_kim5qyxfwz ) { poa1xlshpn = rtP
. Saturation2_UpperSat_kim5qyxfwz ; } else { if ( poa1xlshpn < rtP .
Saturation2_LowerSat_dlfntvjpxg ) { poa1xlshpn = rtP .
Saturation2_LowerSat_dlfntvjpxg ; } } if ( rtB . bbivpaarxt > rtP .
Saturation_UpperSat_e2l0llad23 ) { c0h2wv1ka1 = rtP .
Saturation_UpperSat_e2l0llad23 ; } else if ( rtB . bbivpaarxt < rtP .
Saturation_LowerSat_daenvoeirh ) { c0h2wv1ka1 = rtP .
Saturation_LowerSat_daenvoeirh ; } else { c0h2wv1ka1 = rtB . bbivpaarxt ; }
P_O2 = rtP . Constant_Value_jrk1wafdx5 - ( osqmdqbygi - poa1xlshpn ) /
c0h2wv1ka1 ; if ( P_O2 > rtP . Saturation1_UpperSat_ix0yodnig1 ) { P_O2 = rtP
. Saturation1_UpperSat_ix0yodnig1 ; } else { if ( P_O2 < rtP .
Saturation1_LowerSat_nfi0d0pja5 ) { P_O2 = rtP .
Saturation1_LowerSat_nfi0d0pja5 ; } } rtB . hejghjylpf = ( 1.0 - P_O2 ) * rtB
. bbivpaarxt ; rtB . lkdpawgj3d = ( 1.0 - P_O2 ) * rtP . BoostFCfast_n * rtB
. kx2yvfrvbs ; rtB . jqrtcbjb0q [ 0 ] = rtB . i4u1u0nk00 ; rtB . jqrtcbjb0q [
1 ] = rtB . iuiyd4knlc ; if ( ssGetLogOutput ( rtS ) ) { { double locTime =
ssGetTaskTime ( rtS , 1 ) ; ; if ( rtwTimeInLoggingInterval (
rtliGetLoggingInterval ( ssGetRootSS ( rtS ) -> mdlInfo -> rtwLogInfo ) ,
locTime ) ) { rt_UpdateStructLogVar ( ( StructLogVar * ) rtDW . op222kfxbt .
LoggedData , ( NULL ) , & rtB . jqrtcbjb0q [ 0 ] ) ; } } } if (
ssGetLogOutput ( rtS ) ) { { double locTime = ssGetTaskTime ( rtS , 1 ) ; ;
if ( rtwTimeInLoggingInterval ( rtliGetLoggingInterval ( ssGetRootSS ( rtS )
-> mdlInfo -> rtwLogInfo ) , locTime ) ) { rt_UpdateStructLogVar ( (
StructLogVar * ) rtDW . lqgtrexdqd . LoggedData , ( NULL ) , & rtB .
jqk43gypqg ) ; } } } rtB . bsiskimpq4 = rtP .
donotdeletethisgain_Gain_bvblu5w4wa * rtB . ds4vmpgjgq [ 30 ] * dympzpkrgu ;
rtB . k04sqjkmui = rtP . donotdeletethisgain_Gain_e2kry42snu * rtB .
ds4vmpgjgq [ 21 ] ; rtB . b1fl12txsf = rtDW . b4zh5qri0d ; rtB . orc5wcdxm1 =
rtDW . ic00z2hy2m + 1.0 ; rtB . akwd4yohpb = rtDW . fzp55m5l14 + 1.0 ; s = !
( rtDW . b4zh5qri0d - rtDW . nqhcy2vec4 <= 0.0 ) ; rtB . e4esbiadth = rtDW .
ksxohwmcoh ; P_O2 = rtDW . bv3zs25i1r ; if ( s == 0 ) { osqmdqbygi = rtDW .
bsqle4x1ip + muDoubleScalarAbs ( rtDW . bljv3otj05 ) ; rtB . e4esbiadth =
osqmdqbygi / ( rtDW . ic00z2hy2m + 1.0 ) ; lz43o1ysvx = 0.0 ; rtB .
akwd4yohpb = 0.0 ; } else { osqmdqbygi = 0.0 ; rtB . orc5wcdxm1 = 0.0 ;
lz43o1ysvx = rtDW . ehtf41cg10 + muDoubleScalarAbs ( rtDW . bljv3otj05 ) ;
P_O2 = lz43o1ysvx / ( rtDW . fzp55m5l14 + 1.0 ) ; } bpn0ye43tk = rtDW .
hsvqv45oph ; if ( s == rtDW . cg2af1bnv1 ) { cghr0c1um4 = rtDW . awv1q3egsu ;
poa1xlshpn = rtDW . ikqkqwjh3n ; c0h2wv1ka1 = rtDW . p5fqadhn5b ; } else {
c0h2wv1ka1 = 100.0 - rtDW . b4zh5qri0d ; bpn0ye43tk = rtDW . hsvqv45oph + 1.0
; cghr0c1um4 = rtDW . ikqkqwjh3n ; poa1xlshpn = rtDW . p5fqadhn5b ; } rtB .
ctjnl3duhv = s ; ibatdAv2 = rtDW . fimioqcfmg ; if ( hiov1ctmx0 ( bpn0ye43tk
) == 0.0 ) { ibatdAv2 = rtDW . ksxohwmcoh ; } rtB . i4esmxfcaq = rtDW .
bhhdr2vx1r ; rtB . ewvuxv0roa = rtDW . m4yjnvjtaz ; rtB . frtehkabsr = rtDW .
pztkm2b5s5 ; rtB . fjva4ba3yf = rtDW . p2pkpj1mv5 ; rtB . ojpp3hq5ld = rtDW .
cn5opu2pzs ; if ( hiov1ctmx0 ( bpn0ye43tk ) > 0.0 ) { rtB . i4esmxfcaq =
c0h2wv1ka1 ; rtB . ewvuxv0roa = poa1xlshpn ; rtB . frtehkabsr = cghr0c1um4 ;
rtB . fjva4ba3yf = P_O2 ; rtB . ojpp3hq5ld = ibatdAv2 ; } rtB . hwgkbedju4 =
osqmdqbygi ; rtB . akgbctleuf = lz43o1ysvx ; rtB . ddwaerj1qf = ibatdAv2 ;
rtB . dv32o2egzr = P_O2 ; rtB . liwqgy4ofb = c0h2wv1ka1 ; rtB . cf3awerlht =
poa1xlshpn ; rtB . o0lhjiunqy = cghr0c1um4 ; rtB . paaipnyjy4 = bpn0ye43tk ;
if ( rtB . ojpp3hq5ld > rtP . Saturation1_UpperSat_hftla4v5jl ) { P_O2 = rtP
. Saturation1_UpperSat_hftla4v5jl ; } else if ( rtB . ojpp3hq5ld < rtP .
Saturation1_LowerSat_mlv0levcl5 ) { P_O2 = rtP .
Saturation1_LowerSat_mlv0levcl5 ; } else { P_O2 = rtB . ojpp3hq5ld ; } if (
rtB . fjva4ba3yf > rtP . Saturation2_UpperSat_fd3ezm0unh ) { osqmdqbygi = rtP
. Saturation2_UpperSat_fd3ezm0unh ; } else if ( rtB . fjva4ba3yf < rtP .
Saturation2_LowerSat_a0oq1v4uhe ) { osqmdqbygi = rtP .
Saturation2_LowerSat_a0oq1v4uhe ; } else { osqmdqbygi = rtB . fjva4ba3yf ; }
if ( rtB . ewvuxv0roa > rtP . Saturation_UpperSat_ip0sfxxemb ) { c0h2wv1ka1 =
rtP . Saturation_UpperSat_ip0sfxxemb ; } else if ( rtB . ewvuxv0roa < rtP .
Saturation_LowerSat_oc4mpky1ii ) { c0h2wv1ka1 = rtP .
Saturation_LowerSat_oc4mpky1ii ; } else { c0h2wv1ka1 = rtB . ewvuxv0roa ; }
lz43o1ysvx = c0h2wv1ka1 / 100.0 ; if ( lz43o1ysvx < 0.0 ) { lz43o1ysvx = -
muDoubleScalarPower ( - lz43o1ysvx , - 1.4036774610288021 ) ; } else {
lz43o1ysvx = muDoubleScalarPower ( lz43o1ysvx , - 1.4036774610288021 ) ; } if
( P_O2 < 0.0 ) { P_O2 = - muDoubleScalarPower ( - P_O2 , -
0.27980355032182014 ) ; } else { P_O2 = muDoubleScalarPower ( P_O2 , -
0.27980355032182014 ) ; } if ( osqmdqbygi < 0.0 ) { osqmdqbygi = -
muDoubleScalarPower ( - osqmdqbygi , - 0.28145011599379088 ) ; } else {
osqmdqbygi = muDoubleScalarPower ( osqmdqbygi , - 0.28145011599379088 ) ; }
rtB . jpdjo1yg5c = muDoubleScalarExp ( ( 0.0033540164346805303 - 1.0 / rtB .
ju3eqofxsv ) * - 2166.323400377928 ) * ( 2421.7324404493365 * lz43o1ysvx ) *
P_O2 * osqmdqbygi ; if ( rtB . ewvuxv0roa > rtP .
Saturation1_UpperSat_joqzp4lauk ) { P_O2 = rtP .
Saturation1_UpperSat_joqzp4lauk ; } else if ( rtB . ewvuxv0roa < rtP .
Saturation1_LowerSat_cp5xe3rdvj ) { P_O2 = rtP .
Saturation1_LowerSat_cp5xe3rdvj ; } else { P_O2 = rtB . ewvuxv0roa ; }
osqmdqbygi = rtDW . chezipvofm ; rtB . gxs3xlh0jb = rtDW . lypv2c215x ; rtB .
cuh2ly0avr = rtDW . dhksroq5rn ; if ( ( rtB . paaipnyjy4 >= 3.0 ) && ( ! (
rtB . jpdjo1yg5c == rtDW . jp23k4f2go ) ) ) { if ( rtB . frtehkabsr > rtP .
Saturation2_UpperSat_lknfecgs12 ) { c0h2wv1ka1 = rtP .
Saturation2_UpperSat_lknfecgs12 ; } else if ( rtB . frtehkabsr < rtP .
Saturation2_LowerSat_djkw5ghtjz ) { c0h2wv1ka1 = rtP .
Saturation2_LowerSat_djkw5ghtjz ; } else { c0h2wv1ka1 = rtB . frtehkabsr ; }
if ( rtB . i4esmxfcaq > rtP . Saturation_UpperSat_hsf1hlgzdw ) { osqmdqbygi =
rtP . Saturation_UpperSat_hsf1hlgzdw ; } else if ( rtB . i4esmxfcaq < rtP .
Saturation_LowerSat_peon1dscjc ) { osqmdqbygi = rtP .
Saturation_LowerSat_peon1dscjc ; } else { osqmdqbygi = rtB . i4esmxfcaq ; }
osqmdqbygi = ( ( 1.0 - c0h2wv1ka1 / P_O2 ) * ( 0.5 / rtB . jpdjo1yg5c ) +
rtDW . chezipvofm ) + ( 1.0 - osqmdqbygi / P_O2 ) * ( 0.5 / rtB . jpdjo1yg5c
) ; rtB . cuh2ly0avr = osqmdqbygi * rtP . Constant_Value_nct1bh10mh ; } rtB .
h0hkib4ron = osqmdqbygi ; rtB . aoywj0c0aw = rtDW . gyaphxw5hc - ( rtDW .
gyaphxw5hc - 4.86 ) * ( rtB . h0hkib4ron + rtP . Constant1_Value_aacpe0p2s4 )
; rtB . gswcpufwfm = ( ( real_T ) ( rtB . k04sqjkmui < rtP .
Constant_Value_pty4zc05uj ) * rtP . Gain4_Gain - rtDW . bkylhixnvg ) *
muDoubleScalarAbs ( rtB . k04sqjkmui ) * rtP . Gain1_Gain ; rtB . nfrcslok3r
= rtP . Gain2_Gain * ikoled0vgw ; rtB . bp13llqzit = rtP . R1_Gain * rtB .
k04sqjkmui ; rtB . b0ihg4ev5s = rtP . DiscretePIController2_Ki_lu2imaebpa *
P_H2 ; rtB . aljtveo2dl = muDoubleScalarAbs ( rtB . bsiskimpq4 - n3rh31a5nj )
/ muDoubleScalarAbs ( n3rh31a5nj ) * rtP . Multiply_Gain_ghq4r0q5k3 ; rtB .
jr2i1iijlv = muDoubleScalarAbs ( dympzpkrgu - rtP . Constant6_Value ) / rtB .
mnnico2kpm * rtP . Multiply1_Gain ; ikoled0vgw = rtB . bsiskimpq4 -
n3rh31a5nj ; rtB . in3foousin = ikoled0vgw * ikoled0vgw ; ikoled0vgw =
dympzpkrgu - rtP . Constant6_Value ; rtB . pu2uj4duj0 = ikoled0vgw *
ikoled0vgw ; ikoled0vgw = rtP . donotdeletethisgain_Gain_nzzshfnxdx * rtB .
ds4vmpgjgq [ 36 ] ; rtB . dn4cfjoyu3 = rtDW . g3gghz3gaz ; rtB . ee4dkbgmbt =
( 0.0 - rtB . dn4cfjoyu3 ) - ikoled0vgw ; evtimpzdcg = 1.0 / evtimpzdcg * rtP
. Constant1_Value_ktzhc0x1wo ; rtB . nvvl1et5cw = ( muDoubleScalarAbs ( rtDW
. abf3scvxey ) >= rtP . CompareToConstant_const ) ; if ( rtB . nvvl1et5cw ||
( rtDW . kalc0i12gy != 0 ) ) { rtDW . bds32z0txa = rtP .
DiscreteTimeIntegrator1_IC ; } rtB . a3xn5q0qbv = ( ( ( ( real_T ) ( ( rtDW .
bds32z0txa > 0.0 ) && ( rtDW . bds32z0txa <= 10.0 ) ) * ( rtP .
Constant2_Value_krq4yfjnno * evtimpzdcg ) + ( real_T ) ( ( rtDW . bds32z0txa
> 10.0 ) && ( rtDW . bds32z0txa <= 100.0 ) ) * ( rtP .
Constant3_Value_acddb2uoov * evtimpzdcg ) ) + rtP .
Constant4_Value_fthefd0get * evtimpzdcg * ( real_T ) ( rtDW . bds32z0txa >
100.0 ) ) - rtDW . h1wh3z4evx ) * ( 1.0 / ( evtimpzdcg * 0.15 ) ) ; rtB .
d2aecp5kgr = rtP . Gain_Gain_duepg35cnl * ikoled0vgw ; ikoled0vgw = rtP .
donotdeletethisgain_Gain_ghiynr5jt3 * rtB . ds4vmpgjgq [ 25 ] ; if (
ssIsSampleHit ( rtS , 2 , 0 ) ) { rtB . cataaai4vr = rtDW . c4quijr14v ; } if
( rtB . cataaai4vr > rtP . Saturation1_UpperSat_jbsy2jdb2e ) { evtimpzdcg =
rtP . Saturation1_UpperSat_jbsy2jdb2e ; } else if ( rtB . cataaai4vr < rtP .
Saturation1_LowerSat_km3pw1r5au ) { evtimpzdcg = rtP .
Saturation1_LowerSat_km3pw1r5au ; } else { evtimpzdcg = rtB . cataaai4vr ; }
rtB . glbb5pdj1b = ( 1.0 - evtimpzdcg ) * ( rtP .
donotdeletethisgain_Gain_l30jrki0pa * rtB . ds4vmpgjgq [ 14 ] ) ; rtB .
i5qlxhsaeo = ( 1.0 - evtimpzdcg ) * rtP . BoostPVfast_n * ikoled0vgw ;
evtimpzdcg = rtP . donotdeletethisgain_Gain_m3s0jpprkc * rtB . ds4vmpgjgq [
15 ] * ikoled0vgw ; s = 0 ; if ( evtimpzdcg > rtDW . n0cer4zw0t ) { s = 1 ; }
if ( evtimpzdcg < rtDW . n0cer4zw0t ) { s = - 1 ; } rtB . ktal25amyn = (
real_T ) s * 1.0E-5 + rtDW . knii4eahbq ; if ( ( evtimpzdcg <= 10.0 ) && (
ikoled0vgw > 0.0 ) ) { rtB . ktal25amyn = 0.5 ; } if ( rtB . ktal25amyn < 0.1
) { rtB . ktal25amyn = 0.1 ; } if ( rtB . ktal25amyn > 0.9 ) { rtB .
ktal25amyn = 0.9 ; } rtDW . knii4eahbq = rtB . ktal25amyn ; rtDW . n0cer4zw0t
= evtimpzdcg ; rtB . nw10mpmiwb = rtP . donotdeletethisgain_Gain_hoplgufukg *
rtB . ds4vmpgjgq [ 35 ] ; rtB . dsv2bbs0k1 = rtP .
donotdeletethisgain_Gain_hqauyrnmgx * rtB . ds4vmpgjgq [ 19 ] ;
UNUSED_PARAMETER ( tid ) ; } void MdlOutputsTID3 ( int_T tid ) { memcpy ( &
rtB . oaxo1bryj0 [ 0 ] , & rtP . SwitchCurrents_Value [ 0 ] , 12U * sizeof (
real_T ) ) ; rtB . mnnico2kpm = muDoubleScalarAbs ( rtP . Constant6_Value ) ;
rtB . ju3eqofxsv = rtP . Ta_Value + rtP . Constant8_Value ; rtB . nkylddyjyp
= rtP . Constant1_Value_f3txfozlof ; rtB . aqkf223m44 = rtP .
Constant3_Value_cnmqtz2p2n ; rtB . b11tooymbq = rtP . Constant6_Value * rtP .
Constant6_Value ; rtB . gpw42pjoku = rtP . Constant2_Value_d2yksltlle ; rtB .
ftivrztnav = rtP . eee_Value ; UNUSED_PARAMETER ( tid ) ; } void MdlUpdate (
int_T tid ) { rtDW . ebacjx4abi = rtB . aoywj0c0aw ; rtDW . ae4fdc50fw = (
rtB . k04sqjkmui - rtP . Currentfilter5_DenCoef [ 1 ] * rtDW . ae4fdc50fw ) /
rtP . Currentfilter5_DenCoef [ 0 ] ; rtDW . cbffa5ojlz = rtB . nfrcslok3r ;
rtDW . kt2if2m30y = 0U ; rtDW . ns3jml1yrn += rtP . inti_gainval * rtB .
k04sqjkmui ; if ( rtDW . ns3jml1yrn >= rtP . inti_UpperSat ) { rtDW .
ns3jml1yrn = rtP . inti_UpperSat ; } else { if ( rtDW . ns3jml1yrn <= rtP .
inti_LowerSat ) { rtDW . ns3jml1yrn = rtP . inti_LowerSat ; } } if ( rtB .
nzprtrw2gw > 0.0 ) { rtDW . jjhzuiuwr5 = 1 ; } else if ( rtB . nzprtrw2gw <
0.0 ) { rtDW . jjhzuiuwr5 = - 1 ; } else if ( rtB . nzprtrw2gw == 0.0 ) {
rtDW . jjhzuiuwr5 = 0 ; } else { rtDW . jjhzuiuwr5 = 2 ; } rtDW . bkylhixnvg
+= rtP . DiscreteTimeIntegrator_gainval * rtB . gswcpufwfm ; rtDW .
cfb4bptno0 = rtB . bp13llqzit ; rtDW . mcqhrorlxr = rtB . e2chijmfh2 ; rtDW .
hyrzihgqre = rtB . glbb5pdj1b ; rtDW . opkdjwnlyz = rtB . hejghjylpf ; rtDW .
nbkcuaxc3y = rtB . i4u1u0nk00 ; rtDW . blkk50vpkb += rtP .
DiscreteTimeIntegrator_gainval_m4ai2wnufy * rtB . pmkgps0zyu ; rtDW .
ifljlxnawa = rtB . crs0im5dqp ; rtDW . df3h3bq4ax = rtB . i4u1u0nk00 ; rtDW .
ew4rinximz += rtP . DiscreteTimeIntegrator_gainval_lknx5x0oaz * rtB .
ee4dkbgmbt ; rtDW . nb0afwz3qd = rtB . ajuoykrpve ; rtDW . ntr0qnnxwd = rtB .
i5qlxhsaeo ; rtDW . m01vpi11le = rtB . lkdpawgj3d ; rtDW . p53jjbkpzn = rtB .
dsv2bbs0k1 ; rtDW . mkxkhcmalu = rtB . nw10mpmiwb ; rtDW . jejzfwqaao = rtB .
mdng4h4wi3 ; { SimStruct * rts = ssGetSFunction ( rtS , 0 ) ; sfcnUpdate (
rts , 0 ) ; if ( ssGetErrorStatus ( rts ) != ( NULL ) ) return ; } rtDW .
k0okhesaat += rtP . DiscreteTimeIntegrator_gainval_figs31oe21 * rtB .
lwbnk1tqoe ; if ( rtDW . k0okhesaat >= rtP . DiscreteTimeIntegrator_UpperSat
) { rtDW . k0okhesaat = rtP . DiscreteTimeIntegrator_UpperSat ; } else { if (
rtDW . k0okhesaat <= rtP . DiscreteTimeIntegrator_LowerSat ) { rtDW .
k0okhesaat = rtP . DiscreteTimeIntegrator_LowerSat ; } } rtDW . fzr1ogugs2 +=
rtP . DiscreteTimeIntegrator_gainval_k22hedow4a * rtB . lnggl4hxqa ; if (
rtDW . fzr1ogugs2 >= rtP . DiscreteTimeIntegrator_UpperSat_j2u1431tvu ) {
rtDW . fzr1ogugs2 = rtP . DiscreteTimeIntegrator_UpperSat_j2u1431tvu ; } else
{ if ( rtDW . fzr1ogugs2 <= rtP . DiscreteTimeIntegrator_LowerSat_bvygkv3zts
) { rtDW . fzr1ogugs2 = rtP . DiscreteTimeIntegrator_LowerSat_bvygkv3zts ; }
} rtDW . gepbsobs0a += rtP . DiscreteTimeIntegrator_gainval_jv55x3tqio * rtB
. b0ihg4ev5s ; if ( rtDW . gepbsobs0a >= rtP .
DiscreteTimeIntegrator_UpperSat_n2g2yvldpg ) { rtDW . gepbsobs0a = rtP .
DiscreteTimeIntegrator_UpperSat_n2g2yvldpg ; } else { if ( rtDW . gepbsobs0a
<= rtP . DiscreteTimeIntegrator_LowerSat_fv0zcc4hsa ) { rtDW . gepbsobs0a =
rtP . DiscreteTimeIntegrator_LowerSat_fv0zcc4hsa ; } } rtDW . i4wxuhmfgf +=
rtP . DiscreteTimeIntegrator_gainval_adna3qjceq * rtB . cnvh3z11oj ; if (
rtDW . i4wxuhmfgf >= rtP . DiscreteTimeIntegrator_UpperSat_iu43zm3tho ) {
rtDW . i4wxuhmfgf = rtP . DiscreteTimeIntegrator_UpperSat_iu43zm3tho ; } else
{ if ( rtDW . i4wxuhmfgf <= rtP . DiscreteTimeIntegrator_LowerSat_bdtob5uhem
) { rtDW . i4wxuhmfgf = rtP . DiscreteTimeIntegrator_LowerSat_bdtob5uhem ; }
} rtDW . hzeqqg0jia += rtP . DiscreteTimeIntegrator_gainval_djg22thboz * rtB
. caydqvbppv ; if ( rtDW . hzeqqg0jia >= rtP .
DiscreteTimeIntegrator_UpperSat_k2jkcmkhdm ) { rtDW . hzeqqg0jia = rtP .
DiscreteTimeIntegrator_UpperSat_k2jkcmkhdm ; } else { if ( rtDW . hzeqqg0jia
<= rtP . DiscreteTimeIntegrator_LowerSat_gmrhfgoeip ) { rtDW . hzeqqg0jia =
rtP . DiscreteTimeIntegrator_LowerSat_gmrhfgoeip ; } } rtDW . f51eegc2bu +=
rtP . DiscreteTimeIntegrator_gainval_cdol2y5vzn * rtB . gvxuq2ivcx ; if (
rtDW . f51eegc2bu >= rtP . DiscreteTimeIntegrator_UpperSat_hfo2y053hj ) {
rtDW . f51eegc2bu = rtP . DiscreteTimeIntegrator_UpperSat_hfo2y053hj ; } else
{ if ( rtDW . f51eegc2bu <= rtP . DiscreteTimeIntegrator_LowerSat_c0vq2ip5xz
) { rtDW . f51eegc2bu = rtP . DiscreteTimeIntegrator_LowerSat_c0vq2ip5xz ; }
} rtDW . fxt15s43p4 += rtP . DiscreteTimeIntegrator_gainval_cqdxvpityq * rtB
. oaypl0xy40 ; if ( rtDW . fxt15s43p4 >= rtP .
DiscreteTimeIntegrator_UpperSat_bbsxbmka10 ) { rtDW . fxt15s43p4 = rtP .
DiscreteTimeIntegrator_UpperSat_bbsxbmka10 ; } else { if ( rtDW . fxt15s43p4
<= rtP . DiscreteTimeIntegrator_LowerSat_fbeqnj3sm1 ) { rtDW . fxt15s43p4 =
rtP . DiscreteTimeIntegrator_LowerSat_fbeqnj3sm1 ; } } rtDW . bljv3otj05 =
rtB . k04sqjkmui ; rtDW . b4zh5qri0d = rtB . jqk43gypqg ; rtDW . ic00z2hy2m =
rtB . orc5wcdxm1 ; rtDW . fzp55m5l14 = rtB . akwd4yohpb ; rtDW . bsqle4x1ip =
rtB . hwgkbedju4 ; rtDW . ehtf41cg10 = rtB . akgbctleuf ; rtDW . p2pkpj1mv5 =
rtB . fjva4ba3yf ; rtDW . cn5opu2pzs = rtB . ojpp3hq5ld ; rtDW . fimioqcfmg =
rtB . ddwaerj1qf ; rtDW . ksxohwmcoh = rtB . e4esbiadth ; rtDW . bv3zs25i1r =
rtB . dv32o2egzr ; rtDW . nqhcy2vec4 = rtB . b1fl12txsf ; rtDW . p5fqadhn5b =
rtB . liwqgy4ofb ; rtDW . ikqkqwjh3n = rtB . cf3awerlht ; rtDW . awv1q3egsu =
rtB . o0lhjiunqy ; rtDW . bhhdr2vx1r = rtB . i4esmxfcaq ; rtDW . m4yjnvjtaz =
rtB . ewvuxv0roa ; rtDW . pztkm2b5s5 = rtB . frtehkabsr ; rtDW . hsvqv45oph =
rtB . paaipnyjy4 ; rtDW . cg2af1bnv1 = rtB . ctjnl3duhv ; rtDW . jp23k4f2go =
rtB . jpdjo1yg5c ; rtDW . chezipvofm = rtB . h0hkib4ron ; rtDW . lypv2c215x =
rtB . gxs3xlh0jb ; rtDW . dhksroq5rn = rtB . cuh2ly0avr ; rtDW . gyaphxw5hc =
rtP . Constant12_Value ; rtDW . g3gghz3gaz += rtP .
DiscreteTimeIntegrator_gainval_fhcrjdv1um * rtB . a3xn5q0qbv ; rtDW .
abf3scvxey = rtB . d2aecp5kgr ; rtDW . h1wh3z4evx = rtB . dn4cfjoyu3 ; rtDW .
bds32z0txa += rtP . DiscreteTimeIntegrator1_gainval * rtP .
Constant1_Value_lfvx2nwcp2 ; rtDW . kalc0i12gy = ( int8_T ) rtB . nvvl1et5cw
; if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { rtDW . c4quijr14v = rtB . ktal25amyn
; } UNUSED_PARAMETER ( tid ) ; } void MdlUpdateTID3 ( int_T tid ) {
UNUSED_PARAMETER ( tid ) ; } void MdlTerminate ( void ) { { SimStruct * rts =
ssGetSFunction ( rtS , 0 ) ; sfcnTerminate ( rts ) ; } } void
MdlInitializeSizes ( void ) { ssSetNumContStates ( rtS , 0 ) ; ssSetNumY (
rtS , 0 ) ; ssSetNumU ( rtS , 0 ) ; ssSetDirectFeedThrough ( rtS , 0 ) ;
ssSetNumSampleTimes ( rtS , 3 ) ; ssSetNumBlocks ( rtS , 589 ) ;
ssSetNumBlockIO ( rtS , 94 ) ; ssSetNumBlockParams ( rtS , 363720 ) ; } void
MdlInitializeSampleTimes ( void ) { ssSetSampleTime ( rtS , 0 , 0.0 ) ;
ssSetSampleTime ( rtS , 1 , 0.001 ) ; ssSetSampleTime ( rtS , 2 , 0.01 ) ;
ssSetOffsetTime ( rtS , 0 , 0.0 ) ; ssSetOffsetTime ( rtS , 1 , 0.0 ) ;
ssSetOffsetTime ( rtS , 2 , 0.0 ) ; } void raccel_set_checksum ( ) {
ssSetChecksumVal ( rtS , 0 , 128974220U ) ; ssSetChecksumVal ( rtS , 1 ,
3459481193U ) ; ssSetChecksumVal ( rtS , 2 , 3351760960U ) ; ssSetChecksumVal
( rtS , 3 , 1013255462U ) ; }
#if defined(_MSC_VER)
#pragma optimize( "", off )
#endif
SimStruct * raccel_register_model ( ssExecutionInfo * executionInfo ) {
static struct _ssMdlInfo mdlInfo ; ( void ) memset ( ( char * ) rtS , 0 ,
sizeof ( SimStruct ) ) ; ( void ) memset ( ( char * ) & mdlInfo , 0 , sizeof
( struct _ssMdlInfo ) ) ; ssSetMdlInfoPtr ( rtS , & mdlInfo ) ;
ssSetExecutionInfo ( rtS , executionInfo ) ; { static time_T mdlPeriod [
NSAMPLE_TIMES ] ; static time_T mdlOffset [ NSAMPLE_TIMES ] ; static time_T
mdlTaskTimes [ NSAMPLE_TIMES ] ; static int_T mdlTsMap [ NSAMPLE_TIMES ] ;
static int_T mdlSampleHits [ NSAMPLE_TIMES ] ; static boolean_T
mdlTNextWasAdjustedPtr [ NSAMPLE_TIMES ] ; static int_T mdlPerTaskSampleHits
[ NSAMPLE_TIMES * NSAMPLE_TIMES ] ; static time_T mdlTimeOfNextSampleHit [
NSAMPLE_TIMES ] ; { int_T i ; for ( i = 0 ; i < NSAMPLE_TIMES ; i ++ ) {
mdlPeriod [ i ] = 0.0 ; mdlOffset [ i ] = 0.0 ; mdlTaskTimes [ i ] = 0.0 ;
mdlTsMap [ i ] = i ; mdlSampleHits [ i ] = 1 ; } } ssSetSampleTimePtr ( rtS ,
& mdlPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rtS , & mdlOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rtS , & mdlTsMap [ 0 ] ) ; ssSetTPtr ( rtS , &
mdlTaskTimes [ 0 ] ) ; ssSetSampleHitPtr ( rtS , & mdlSampleHits [ 0 ] ) ;
ssSetTNextWasAdjustedPtr ( rtS , & mdlTNextWasAdjustedPtr [ 0 ] ) ;
ssSetPerTaskSampleHitsPtr ( rtS , & mdlPerTaskSampleHits [ 0 ] ) ;
ssSetTimeOfNextSampleHitPtr ( rtS , & mdlTimeOfNextSampleHit [ 0 ] ) ; }
ssSetSolverMode ( rtS , SOLVER_MODE_SINGLETASKING ) ; { ssSetBlockIO ( rtS ,
( ( void * ) & rtB ) ) ; ssSetWorkSizeInBytes ( rtS , sizeof ( rtB ) ,
"BlockIO" ) ; ( void ) memset ( ( ( void * ) & rtB ) , 0 , sizeof ( B ) ) ; }
{ void * dwork = ( void * ) & rtDW ; ssSetRootDWork ( rtS , dwork ) ;
ssSetWorkSizeInBytes ( rtS , sizeof ( rtDW ) , "DWork" ) ; ( void ) memset (
dwork , 0 , sizeof ( DW ) ) ; } { static DataTypeTransInfo dtInfo ; ( void )
memset ( ( char_T * ) & dtInfo , 0 , sizeof ( dtInfo ) ) ;
ssSetModelMappingInfo ( rtS , & dtInfo ) ; dtInfo . numDataTypes = 18 ;
dtInfo . dataTypeSizes = & rtDataTypeSizes [ 0 ] ; dtInfo . dataTypeNames = &
rtDataTypeNames [ 0 ] ; dtInfo . BTransTable = & rtBTransTable ; dtInfo .
PTransTable = & rtPTransTable ; dtInfo . dataTypeInfoTable =
rtDataTypeInfoTable ; } fast_powertrain_InitializeDataMapInfo ( ) ;
ssSetIsRapidAcceleratorActive ( rtS , true ) ; ssSetRootSS ( rtS , rtS ) ;
ssSetVersion ( rtS , SIMSTRUCT_VERSION_LEVEL2 ) ; ssSetModelName ( rtS ,
"fast_powertrain" ) ; ssSetPath ( rtS , "fast_powertrain" ) ; ssSetTStart (
rtS , 0.0 ) ; ssSetTFinal ( rtS , 200.0 ) ; ssSetStepSize ( rtS , 0.001 ) ;
ssSetFixedStepSize ( rtS , 0.001 ) ; { static RTWLogInfo rt_DataLoggingInfo ;
rt_DataLoggingInfo . loggingInterval = NULL ; ssSetRTWLogInfo ( rtS , &
rt_DataLoggingInfo ) ; } { { static int_T rt_LoggedStateWidths [ ] = { 1 , 1
, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 13 , 1 , 1 , 1
, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 } ; static int_T
rt_LoggedStateNumDimensions [ ] = { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1
, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 }
; static int_T rt_LoggedStateDimensions [ ] = { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1
, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 13 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1
, 1 , 1 , 1 } ; static boolean_T rt_LoggedStateIsVarDims [ ] = { 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 } ; static BuiltInDTypeId
rt_LoggedStateDataTypeIds [ ] = { SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE } ; static int_T
rt_LoggedStateComplexSignals [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
} ; static RTWPreprocessingFcnPtr rt_LoggingStatePreprocessingFcnPtrs [ ] = {
( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) ,
( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) ,
( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) ,
( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) ,
( NULL ) , ( NULL ) } ; static const char_T * rt_LoggedStateLabels [ ] = {
"states" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" } ; static const char_T * rt_LoggedStateBlockNames [ ] =
{ "fast_powertrain/Battery/Model/Current filter5" ,
"fast_powertrain/Battery/Model/int(i)" ,
"fast_powertrain/Battery/Model/Exp/Discrete-Time\nIntegrator" ,
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Unit Delay1" ,
"fast_powertrain/Boost - PV - fast/Unit Delay2" ,
"fast_powertrain/Boost FC - fast/Unit Delay2" ,
"fast_powertrain/PEMFC matfunc V2/Delay" ,
"fast_powertrain/PEMFC matfunc V2/Discrete-Time\nIntegrator" ,
"fast_powertrain/PEMFC matfunc V2/Unit Delay" ,
"fast_powertrain/PEMFC matfunc V2/Unit Delay1" ,
"fast_powertrain/Supercapacitor1/Model/Discrete/Discrete-Time\nIntegrator" ,
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Unit Delay2" ,
"fast_powertrain/Boost - PV - fast/Unit Delay3" ,
"fast_powertrain/Boost FC - fast/Unit Delay3" ,
"fast_powertrain/PV MODULE1/Unit Delay1" ,
"fast_powertrain/PV MODULE1/Unit Delay4" ,
"fast_powertrain/powergui1/EquivalentModel1/Unit Delay" ,
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ,
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete\nPI Controller1/Discrete-Time\nIntegrator"
,
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete\nPI Controller2/Discrete-Time\nIntegrator"
, "fast_powertrain/Discrete\nPI Controller2/Discrete-Time\nIntegrator" ,
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete\nPI Controller3/Discrete-Time\nIntegrator"
,
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete\nPI Controller4/Discrete-Time\nIntegrator"
,
 "fast_powertrain/Boost FC - fast/Discrete\nPI Controller3/Discrete-Time\nIntegrator"
,
 "fast_powertrain/Boost FC - fast/Discrete\nPI Controller4/Discrete-Time\nIntegrator"
,
 "fast_powertrain/Supercapacitor1/Model/Discrete/Self_discharge Model/Discrete-Time\nIntegrator"
,
 "fast_powertrain/Supercapacitor1/Model/Discrete/Self_discharge Model/Unit Delay2"
,
"fast_powertrain/Supercapacitor1/Model/Discrete/Self_discharge Model/Unit Delay"
,
 "fast_powertrain/Supercapacitor1/Model/Discrete/Self_discharge Model/Discrete-Time\nIntegrator1"
, "fast_powertrain/Boost - PV - fast/Unit Delay1" } ; static const char_T *
rt_LoggedStateNames [ ] = { "states" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" } ; static boolean_T
rt_LoggedStateCrossMdlRef [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ;
static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert [ ] = { { 0 , SS_DOUBLE
, SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 ,
0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } } ; static
RTWLogSignalInfo rt_LoggedStateSignalInfo = { 30 , rt_LoggedStateWidths ,
rt_LoggedStateNumDimensions , rt_LoggedStateDimensions ,
rt_LoggedStateIsVarDims , ( NULL ) , ( NULL ) , rt_LoggedStateDataTypeIds ,
rt_LoggedStateComplexSignals , ( NULL ) , rt_LoggingStatePreprocessingFcnPtrs
, { rt_LoggedStateLabels } , ( NULL ) , ( NULL ) , ( NULL ) , {
rt_LoggedStateBlockNames } , { rt_LoggedStateNames } ,
rt_LoggedStateCrossMdlRef , rt_RTWLogDataTypeConvert } ; static void *
rt_LoggedStateSignalPtrs [ 30 ] ; rtliSetLogXSignalPtrs ( ssGetRTWLogInfo (
rtS ) , ( LogSignalPtrsType ) rt_LoggedStateSignalPtrs ) ;
rtliSetLogXSignalInfo ( ssGetRTWLogInfo ( rtS ) , & rt_LoggedStateSignalInfo
) ; rt_LoggedStateSignalPtrs [ 0 ] = ( void * ) & rtDW . ae4fdc50fw ;
rt_LoggedStateSignalPtrs [ 1 ] = ( void * ) & rtDW . ns3jml1yrn ;
rt_LoggedStateSignalPtrs [ 2 ] = ( void * ) & rtDW . bkylhixnvg ;
rt_LoggedStateSignalPtrs [ 3 ] = ( void * ) & rtDW . mcqhrorlxr ;
rt_LoggedStateSignalPtrs [ 4 ] = ( void * ) & rtDW . hyrzihgqre ;
rt_LoggedStateSignalPtrs [ 5 ] = ( void * ) & rtDW . opkdjwnlyz ;
rt_LoggedStateSignalPtrs [ 6 ] = ( void * ) & rtDW . nbkcuaxc3y ;
rt_LoggedStateSignalPtrs [ 7 ] = ( void * ) & rtDW . blkk50vpkb ;
rt_LoggedStateSignalPtrs [ 8 ] = ( void * ) & rtDW . ifljlxnawa ;
rt_LoggedStateSignalPtrs [ 9 ] = ( void * ) & rtDW . df3h3bq4ax ;
rt_LoggedStateSignalPtrs [ 10 ] = ( void * ) & rtDW . ew4rinximz ;
rt_LoggedStateSignalPtrs [ 11 ] = ( void * ) & rtDW . nb0afwz3qd ;
rt_LoggedStateSignalPtrs [ 12 ] = ( void * ) & rtDW . ntr0qnnxwd ;
rt_LoggedStateSignalPtrs [ 13 ] = ( void * ) & rtDW . m01vpi11le ;
rt_LoggedStateSignalPtrs [ 14 ] = ( void * ) & rtDW . p53jjbkpzn ;
rt_LoggedStateSignalPtrs [ 15 ] = ( void * ) & rtDW . mkxkhcmalu ;
rt_LoggedStateSignalPtrs [ 16 ] = ( void * ) & rtDW . jejzfwqaao ;
rt_LoggedStateSignalPtrs [ 17 ] = ( void * ) rtDW . fs5pddw5ow ;
rt_LoggedStateSignalPtrs [ 18 ] = ( void * ) & rtDW . k0okhesaat ;
rt_LoggedStateSignalPtrs [ 19 ] = ( void * ) & rtDW . fzr1ogugs2 ;
rt_LoggedStateSignalPtrs [ 20 ] = ( void * ) & rtDW . gepbsobs0a ;
rt_LoggedStateSignalPtrs [ 21 ] = ( void * ) & rtDW . i4wxuhmfgf ;
rt_LoggedStateSignalPtrs [ 22 ] = ( void * ) & rtDW . hzeqqg0jia ;
rt_LoggedStateSignalPtrs [ 23 ] = ( void * ) & rtDW . f51eegc2bu ;
rt_LoggedStateSignalPtrs [ 24 ] = ( void * ) & rtDW . fxt15s43p4 ;
rt_LoggedStateSignalPtrs [ 25 ] = ( void * ) & rtDW . g3gghz3gaz ;
rt_LoggedStateSignalPtrs [ 26 ] = ( void * ) & rtDW . abf3scvxey ;
rt_LoggedStateSignalPtrs [ 27 ] = ( void * ) & rtDW . h1wh3z4evx ;
rt_LoggedStateSignalPtrs [ 28 ] = ( void * ) & rtDW . bds32z0txa ;
rt_LoggedStateSignalPtrs [ 29 ] = ( void * ) & rtDW . c4quijr14v ; }
rtliSetLogT ( ssGetRTWLogInfo ( rtS ) , "tout" ) ; rtliSetLogX (
ssGetRTWLogInfo ( rtS ) , "" ) ; rtliSetLogXFinal ( ssGetRTWLogInfo ( rtS ) ,
"" ) ; rtliSetLogVarNameModifier ( ssGetRTWLogInfo ( rtS ) , "none" ) ;
rtliSetLogFormat ( ssGetRTWLogInfo ( rtS ) , 4 ) ; rtliSetLogMaxRows (
ssGetRTWLogInfo ( rtS ) , 0 ) ; rtliSetLogDecimation ( ssGetRTWLogInfo ( rtS
) , 1 ) ; rtliSetLogY ( ssGetRTWLogInfo ( rtS ) , "" ) ;
rtliSetLogYSignalInfo ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ;
rtliSetLogYSignalPtrs ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ; } { static
ssSolverInfo slvrInfo ; ssSetSolverInfo ( rtS , & slvrInfo ) ;
ssSetSolverName ( rtS , "FixedStepDiscrete" ) ; ssSetVariableStepSolver ( rtS
, 0 ) ; ssSetSolverConsistencyChecking ( rtS , 0 ) ;
ssSetSolverAdaptiveZcDetection ( rtS , 0 ) ; ssSetSolverRobustResetMethod (
rtS , 0 ) ; ssSetSolverStateProjection ( rtS , 0 ) ;
ssSetSolverMassMatrixType ( rtS , ( ssMatrixType ) 0 ) ;
ssSetSolverMassMatrixNzMax ( rtS , 0 ) ; ssSetModelOutputs ( rtS , MdlOutputs
) ; ssSetModelLogData ( rtS , rt_UpdateTXYLogVars ) ;
ssSetModelLogDataIfInInterval ( rtS , rt_UpdateTXXFYLogVars ) ;
ssSetModelUpdate ( rtS , MdlUpdate ) ; ssSetTNextTid ( rtS , INT_MIN ) ;
ssSetTNext ( rtS , rtMinusInf ) ; ssSetSolverNeedsReset ( rtS ) ;
ssSetNumNonsampledZCs ( rtS , 0 ) ; } ssSetChecksumVal ( rtS , 0 , 128974220U
) ; ssSetChecksumVal ( rtS , 1 , 3459481193U ) ; ssSetChecksumVal ( rtS , 2 ,
3351760960U ) ; ssSetChecksumVal ( rtS , 3 , 1013255462U ) ; { static const
sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE ; static RTWExtModeInfo
rt_ExtModeInfo ; static const sysRanDType * systemRan [ 23 ] ;
gblRTWExtModeInfo = & rt_ExtModeInfo ; ssSetRTWExtModeInfo ( rtS , &
rt_ExtModeInfo ) ; rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo ,
systemRan ) ; systemRan [ 0 ] = & rtAlwaysEnabled ; systemRan [ 1 ] = &
rtAlwaysEnabled ; systemRan [ 2 ] = & rtAlwaysEnabled ; systemRan [ 3 ] = &
rtAlwaysEnabled ; systemRan [ 4 ] = & rtAlwaysEnabled ; systemRan [ 5 ] = &
rtAlwaysEnabled ; systemRan [ 6 ] = & rtAlwaysEnabled ; systemRan [ 7 ] = &
rtAlwaysEnabled ; systemRan [ 8 ] = & rtAlwaysEnabled ; systemRan [ 9 ] = &
rtAlwaysEnabled ; systemRan [ 10 ] = & rtAlwaysEnabled ; systemRan [ 11 ] = &
rtAlwaysEnabled ; systemRan [ 12 ] = & rtAlwaysEnabled ; systemRan [ 13 ] = &
rtAlwaysEnabled ; systemRan [ 14 ] = & rtAlwaysEnabled ; systemRan [ 15 ] = &
rtAlwaysEnabled ; systemRan [ 16 ] = & rtAlwaysEnabled ; systemRan [ 17 ] = &
rtAlwaysEnabled ; systemRan [ 18 ] = & rtAlwaysEnabled ; systemRan [ 19 ] = &
rtAlwaysEnabled ; systemRan [ 20 ] = & rtAlwaysEnabled ; systemRan [ 21 ] = &
rtAlwaysEnabled ; systemRan [ 22 ] = & rtAlwaysEnabled ;
rteiSetModelMappingInfoPtr ( ssGetRTWExtModeInfo ( rtS ) , &
ssGetModelMappingInfo ( rtS ) ) ; rteiSetChecksumsPtr ( ssGetRTWExtModeInfo (
rtS ) , ssGetChecksums ( rtS ) ) ; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS )
, ssGetTPtr ( rtS ) ) ; } rtP . Saturation_LowerSat = rtMinusInf ; rtP .
inti_LowerSat = rtMinusInf ; rtP . Saturation_UpperSat_gvrgxklgqx = rtInf ;
rtP . Saturation_UpperSat_e2k0qdtv2s = rtInf ; rtP . Saturation4_UpperSat =
rtInf ; rtP . Saturation_UpperSat_jsjpgzsi1y = rtInf ; rtP .
Saturation2_UpperSat_amgcitvjo2 = rtInf ; rtP .
Saturation2_UpperSat_aip5hjdd2y = rtInf ; rtP .
Saturation_UpperSat_e2l0llad23 = rtInf ; rtP . Saturation_UpperSat_ip0sfxxemb
= rtInf ; rtP . Saturation1_UpperSat_hftla4v5jl = rtInf ; rtP .
Saturation2_UpperSat_fd3ezm0unh = rtInf ; rtP .
Saturation_UpperSat_hsf1hlgzdw = rtInf ; rtP .
Saturation1_UpperSat_joqzp4lauk = rtInf ; rtP .
Saturation2_UpperSat_lknfecgs12 = rtInf ; rtP . Constant_Value_kfm5xzok4i =
rtInf ; ssSetNumSFunctions ( rtS , 1 ) ; { static SimStruct childSFunctions [
1 ] ; static SimStruct * childSFunctionPtrs [ 1 ] ; ( void ) memset ( ( void
* ) & childSFunctions [ 0 ] , 0 , sizeof ( childSFunctions ) ) ;
ssSetSFunctions ( rtS , & childSFunctionPtrs [ 0 ] ) ; ssSetSFunction ( rtS ,
0 , & childSFunctions [ 0 ] ) ; { SimStruct * rts = ssGetSFunction ( rtS , 0
) ; static time_T sfcnPeriod [ 1 ] ; static time_T sfcnOffset [ 1 ] ; static
int_T sfcnTsMap [ 1 ] ; ( void ) memset ( ( void * ) sfcnPeriod , 0 , sizeof
( time_T ) * 1 ) ; ( void ) memset ( ( void * ) sfcnOffset , 0 , sizeof (
time_T ) * 1 ) ; ssSetSampleTimePtr ( rts , & sfcnPeriod [ 0 ] ) ;
ssSetOffsetTimePtr ( rts , & sfcnOffset [ 0 ] ) ; ssSetSampleTimeTaskIDPtr (
rts , sfcnTsMap ) ; { static struct _ssBlkInfo2 _blkInfo2 ; struct
_ssBlkInfo2 * blkInfo2 = & _blkInfo2 ; ssSetBlkInfo2Ptr ( rts , blkInfo2 ) ;
} { static struct _ssPortInfo2 _portInfo2 ; struct _ssPortInfo2 * portInfo2 =
& _portInfo2 ; _ssSetBlkInfo2PortInfo2Ptr ( rts , portInfo2 ) ; }
ssSetMdlInfoPtr ( rts , ssGetMdlInfoPtr ( rtS ) ) ; { static struct
_ssSFcnModelMethods2 methods2 ; ssSetModelMethods2 ( rts , & methods2 ) ; } {
static struct _ssSFcnModelMethods3 methods3 ; ssSetModelMethods3 ( rts , &
methods3 ) ; } { static struct _ssSFcnModelMethods4 methods4 ;
ssSetModelMethods4 ( rts , & methods4 ) ; } { static struct _ssStatesInfo2
statesInfo2 ; static ssPeriodicStatesInfo periodicStatesInfo ; static
ssJacobianPerturbationBounds jacPerturbationBounds ; ssSetStatesInfo2 ( rts ,
& statesInfo2 ) ; ssSetPeriodicStatesInfo ( rts , & periodicStatesInfo ) ;
ssSetJacobianPerturbationBounds ( rts , & jacPerturbationBounds ) ; } {
static struct _ssPortInputs inputPortInfo [ 3 ] ; _ssSetNumInputPorts ( rts ,
3 ) ; ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static
struct _ssInPortUnit inputPortUnits [ 3 ] ; _ssSetPortInfo2ForInputUnits (
rts , & inputPortUnits [ 0 ] ) ; } ssSetInputPortUnit ( rts , 0 , 0 ) ;
ssSetInputPortUnit ( rts , 1 , 0 ) ; ssSetInputPortUnit ( rts , 2 , 0 ) ; {
static struct _ssInPortCoSimAttribute inputPortCoSimAttribute [ 3 ] ;
_ssSetPortInfo2ForInputCoSimAttribute ( rts , & inputPortCoSimAttribute [ 0 ]
) ; } ssSetInputPortIsContinuousQuantity ( rts , 0 , 0 ) ;
ssSetInputPortIsContinuousQuantity ( rts , 1 , 0 ) ;
ssSetInputPortIsContinuousQuantity ( rts , 2 , 0 ) ; { static real_T const *
sfcnUPtrs [ 24 ] ; { int_T i1 ; const real_T * u0 = & rtB . oaxo1bryj0 [ 0 ]
; for ( i1 = 0 ; i1 < 12 ; i1 ++ ) { sfcnUPtrs [ i1 ] = & u0 [ i1 ] ; }
sfcnUPtrs [ 12 ] = & rtB . klfwarvagc ; sfcnUPtrs [ 13 ] = & rtB . i0ujncnh35
; sfcnUPtrs [ 14 ] = & rtB . dplapzekhr ; sfcnUPtrs [ 15 ] = & rtB .
b2m0nyy1iq ; sfcnUPtrs [ 16 ] = & rtB . dg1zqpobap ; sfcnUPtrs [ 17 ] = & rtB
. m2zun0bmq0 ; sfcnUPtrs [ 18 ] = & rtB . bnsiwqbz4c ; sfcnUPtrs [ 19 ] = &
rtB . nd5vhw3hdp ; sfcnUPtrs [ 20 ] = & rtB . pkslvtv3r5 ; sfcnUPtrs [ 21 ] =
& rtB . cp1s511zvk ; sfcnUPtrs [ 22 ] = & rtB . ftivrztnav ; sfcnUPtrs [ 23 ]
= ( ( const real_T * ) & fast_powertrain_RGND ) ; } ssSetInputPortSignalPtrs
( rts , 0 , ( InputPtrsType ) & sfcnUPtrs [ 0 ] ) ;
_ssSetInputPortNumDimensions ( rts , 0 , 1 ) ; ssSetInputPortWidth ( rts , 0
, 24 ) ; } { static real_T const * sfcnUPtrs [ 12 ] ; sfcnUPtrs [ 0 ] = & rtB
. aqkf223m44 ; sfcnUPtrs [ 1 ] = & rtB . aqkf223m44 ; sfcnUPtrs [ 2 ] = & rtB
. gpw42pjoku ; sfcnUPtrs [ 3 ] = & rtB . gpw42pjoku ; sfcnUPtrs [ 4 ] = & rtB
. nkylddyjyp ; sfcnUPtrs [ 5 ] = & rtB . nkylddyjyp ; sfcnUPtrs [ 6 ] = ( (
const real_T * ) & fast_powertrain_RGND ) ; sfcnUPtrs [ 7 ] = ( ( const
real_T * ) & fast_powertrain_RGND ) ; sfcnUPtrs [ 8 ] = ( ( const real_T * )
& fast_powertrain_RGND ) ; sfcnUPtrs [ 9 ] = ( ( const real_T * ) &
fast_powertrain_RGND ) ; sfcnUPtrs [ 10 ] = ( ( const real_T * ) &
fast_powertrain_RGND ) ; sfcnUPtrs [ 11 ] = ( ( const real_T * ) &
fast_powertrain_RGND ) ; ssSetInputPortSignalPtrs ( rts , 1 , ( InputPtrsType
) & sfcnUPtrs [ 0 ] ) ; _ssSetInputPortNumDimensions ( rts , 1 , 1 ) ;
ssSetInputPortWidth ( rts , 1 , 12 ) ; } { static real_T const * sfcnUPtrs [
1 ] ; sfcnUPtrs [ 0 ] = & rtB . aunoa00r4h ; ssSetInputPortSignalPtrs ( rts ,
2 , ( InputPtrsType ) & sfcnUPtrs [ 0 ] ) ; _ssSetInputPortNumDimensions (
rts , 2 , 1 ) ; ssSetInputPortWidth ( rts , 2 , 1 ) ; } } { static struct
_ssPortOutputs outputPortInfo [ 3 ] ; ssSetPortInfoForOutputs ( rts , &
outputPortInfo [ 0 ] ) ; _ssSetNumOutputPorts ( rts , 3 ) ; { static struct
_ssOutPortUnit outputPortUnits [ 3 ] ; _ssSetPortInfo2ForOutputUnits ( rts ,
& outputPortUnits [ 0 ] ) ; } ssSetOutputPortUnit ( rts , 0 , 0 ) ;
ssSetOutputPortUnit ( rts , 1 , 0 ) ; ssSetOutputPortUnit ( rts , 2 , 0 ) ; {
static struct _ssOutPortCoSimAttribute outputPortCoSimAttribute [ 3 ] ;
_ssSetPortInfo2ForOutputCoSimAttribute ( rts , & outputPortCoSimAttribute [ 0
] ) ; } ssSetOutputPortIsContinuousQuantity ( rts , 0 , 0 ) ;
ssSetOutputPortIsContinuousQuantity ( rts , 1 , 0 ) ;
ssSetOutputPortIsContinuousQuantity ( rts , 2 , 0 ) ; {
_ssSetOutputPortNumDimensions ( rts , 0 , 1 ) ; ssSetOutputPortWidth ( rts ,
0 , 38 ) ; ssSetOutputPortSignal ( rts , 0 , ( ( real_T * ) rtB . ds4vmpgjgq
) ) ; } { _ssSetOutputPortNumDimensions ( rts , 1 , 1 ) ;
ssSetOutputPortWidth ( rts , 1 , 12 ) ; ssSetOutputPortSignal ( rts , 1 , ( (
real_T * ) rtB . aprtxoz0cz ) ) ; } { _ssSetOutputPortNumDimensions ( rts , 2
, 1 ) ; ssSetOutputPortWidth ( rts , 2 , 1 ) ; ssSetOutputPortSignal ( rts ,
2 , ( ( real_T * ) & rtB . dsl30exhdf ) ) ; } } ssSetDiscStates ( rts , (
real_T * ) & rtDW . fs5pddw5ow [ 0 ] ) ; ssSetModelName ( rts , "State-Space"
) ; ssSetPath ( rts ,
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) ; if (
ssGetRTModel ( rtS ) == ( NULL ) ) { ssSetParentSS ( rts , rtS ) ;
ssSetRootSS ( rts , ssGetRootSS ( rtS ) ) ; } else { ssSetRTModel ( rts ,
ssGetRTModel ( rtS ) ) ; ssSetParentSS ( rts , ( NULL ) ) ; ssSetRootSS ( rts
, rts ) ; } ssSetVersion ( rts , SIMSTRUCT_VERSION_LEVEL2 ) ; { static
mxArray * sfcnParams [ 24 ] ; ssSetSFcnParamsCount ( rts , 24 ) ;
ssSetSFcnParamsPtr ( rts , & sfcnParams [ 0 ] ) ; ssSetSFcnParam ( rts , 0 ,
( mxArray * ) rtP . StateSpace_P1_Size ) ; ssSetSFcnParam ( rts , 1 , (
mxArray * ) rtP . StateSpace_P2_Size ) ; ssSetSFcnParam ( rts , 2 , ( mxArray
* ) rtP . StateSpace_P3_Size ) ; ssSetSFcnParam ( rts , 3 , ( mxArray * ) rtP
. StateSpace_P4_Size ) ; ssSetSFcnParam ( rts , 4 , ( mxArray * ) rtP .
StateSpace_P5_Size ) ; ssSetSFcnParam ( rts , 5 , ( mxArray * ) rtP .
StateSpace_P6_Size ) ; ssSetSFcnParam ( rts , 6 , ( mxArray * ) rtP .
StateSpace_P7_Size ) ; ssSetSFcnParam ( rts , 7 , ( mxArray * ) rtP .
StateSpace_P8_Size ) ; ssSetSFcnParam ( rts , 8 , ( mxArray * ) rtP .
StateSpace_P9_Size ) ; ssSetSFcnParam ( rts , 9 , ( mxArray * ) rtP .
StateSpace_P10_Size ) ; ssSetSFcnParam ( rts , 10 , ( mxArray * ) rtP .
StateSpace_P11_Size ) ; ssSetSFcnParam ( rts , 11 , ( mxArray * ) rtP .
StateSpace_P12_Size ) ; ssSetSFcnParam ( rts , 12 , ( mxArray * ) rtP .
StateSpace_P13_Size ) ; ssSetSFcnParam ( rts , 13 , ( mxArray * ) rtP .
StateSpace_P14_Size ) ; ssSetSFcnParam ( rts , 14 , ( mxArray * ) rtP .
StateSpace_P15_Size ) ; ssSetSFcnParam ( rts , 15 , ( mxArray * ) rtP .
StateSpace_P16_Size ) ; ssSetSFcnParam ( rts , 16 , ( mxArray * ) rtP .
StateSpace_P17_Size ) ; ssSetSFcnParam ( rts , 17 , ( mxArray * ) rtP .
StateSpace_P18_Size ) ; ssSetSFcnParam ( rts , 18 , ( mxArray * ) rtP .
StateSpace_P19_Size ) ; ssSetSFcnParam ( rts , 19 , ( mxArray * ) rtP .
StateSpace_P20_Size ) ; ssSetSFcnParam ( rts , 20 , ( mxArray * ) rtP .
StateSpace_P21_Size ) ; ssSetSFcnParam ( rts , 21 , ( mxArray * ) rtP .
StateSpace_P22_Size ) ; ssSetSFcnParam ( rts , 22 , ( mxArray * ) rtP .
StateSpace_P23_Size ) ; ssSetSFcnParam ( rts , 23 , ( mxArray * ) rtP .
StateSpace_P24_Size ) ; } ssSetRWork ( rts , ( real_T * ) & rtDW . e0g3wfol1j
) ; ssSetIWork ( rts , ( int_T * ) & rtDW . jpo5gkezdl [ 0 ] ) ; ssSetPWork (
rts , ( void * * ) & rtDW . jdobxxns3j [ 0 ] ) ; { static struct
_ssDWorkRecord dWorkRecord [ 4 ] ; static struct _ssDWorkAuxRecord
dWorkAuxRecord [ 4 ] ; ssSetSFcnDWork ( rts , dWorkRecord ) ;
ssSetSFcnDWorkAux ( rts , dWorkAuxRecord ) ; _ssSetNumDWork ( rts , 4 ) ;
ssSetDWorkWidth ( rts , 0 , 1 ) ; ssSetDWorkDataType ( rts , 0 , SS_DOUBLE )
; ssSetDWorkComplexSignal ( rts , 0 , 0 ) ; ssSetDWork ( rts , 0 , & rtDW .
e0g3wfol1j ) ; ssSetDWorkWidth ( rts , 1 , 12 ) ; ssSetDWorkDataType ( rts ,
1 , SS_INTEGER ) ; ssSetDWorkComplexSignal ( rts , 1 , 0 ) ; ssSetDWork ( rts
, 1 , & rtDW . jpo5gkezdl [ 0 ] ) ; ssSetDWorkWidth ( rts , 2 , 65 ) ;
ssSetDWorkDataType ( rts , 2 , SS_POINTER ) ; ssSetDWorkComplexSignal ( rts ,
2 , 0 ) ; ssSetDWork ( rts , 2 , & rtDW . jdobxxns3j [ 0 ] ) ;
ssSetDWorkWidth ( rts , 3 , 13 ) ; ssSetDWorkDataType ( rts , 3 , SS_DOUBLE )
; ssSetDWorkComplexSignal ( rts , 3 , 0 ) ; ssSetDWorkUsedAsDState ( rts , 3
, 1 ) ; ssSetDWork ( rts , 3 , & rtDW . fs5pddw5ow [ 0 ] ) ; }
sfun_spssw_discc_DSS ( rts ) ; sfcnInitializeSizes ( rts ) ;
sfcnInitializeSampleTimes ( rts ) ; ssSetSampleTime ( rts , 0 , 0.001 ) ;
ssSetOffsetTime ( rts , 0 , 0.0 ) ; sfcnTsMap [ 0 ] = 1 ;
ssSetNumNonsampledZCs ( rts , 0 ) ; _ssSetInputPortConnected ( rts , 0 , 1 )
; _ssSetInputPortConnected ( rts , 1 , 1 ) ; _ssSetInputPortConnected ( rts ,
2 , 1 ) ; _ssSetOutputPortConnected ( rts , 0 , 1 ) ;
_ssSetOutputPortConnected ( rts , 1 , 1 ) ; _ssSetOutputPortConnected ( rts ,
2 , 1 ) ; _ssSetOutputPortBeingMerged ( rts , 0 , 0 ) ;
_ssSetOutputPortBeingMerged ( rts , 1 , 0 ) ; _ssSetOutputPortBeingMerged (
rts , 2 , 0 ) ; ssSetInputPortBufferDstPort ( rts , 0 , - 1 ) ;
ssSetInputPortBufferDstPort ( rts , 1 , - 1 ) ; ssSetInputPortBufferDstPort (
rts , 2 , - 1 ) ; } } return rtS ; }
#if defined(_MSC_VER)
#pragma optimize( "", on )
#endif
const int_T gblParameterTuningTid = 3 ; void MdlOutputsParameterSampleTime (
int_T tid ) { MdlOutputsTID3 ( tid ) ; }

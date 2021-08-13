#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "fast_powertrain_capi_host.h"
#define sizeof(s) ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el) ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s) (s)    
#else
#include "builtin_typeid_types.h"
#include "fast_powertrain.h"
#include "fast_powertrain_capi.h"
#include "fast_powertrain_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST                  
#define TARGET_STRING(s)               (NULL)                    
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static const rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 15 , TARGET_STRING
( "fast_powertrain/Fuzzy Logic Controller" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 0 } , { 1 , 19 , TARGET_STRING ( "fast_powertrain/MATLAB Function" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 2 , 19 , TARGET_STRING (
"fast_powertrain/MATLAB Function" ) , TARGET_STRING ( "" ) , 1 , 0 , 0 , 0 ,
1 } , { 3 , 19 , TARGET_STRING ( "fast_powertrain/MATLAB Function" ) ,
TARGET_STRING ( "" ) , 2 , 0 , 0 , 0 , 1 } , { 4 , 19 , TARGET_STRING (
"fast_powertrain/MATLAB Function" ) , TARGET_STRING ( "" ) , 3 , 0 , 0 , 0 ,
1 } , { 5 , 20 , TARGET_STRING ( "fast_powertrain/MATLAB Function2" ) ,
TARGET_STRING ( "" ) , 1 , 0 , 0 , 0 , 1 } , { 6 , 24 , TARGET_STRING (
"fast_powertrain/PV - FC - control" ) , TARGET_STRING ( "" ) , 2 , 0 , 0 , 0
, 1 } , { 7 , 24 , TARGET_STRING ( "fast_powertrain/PV - FC - control" ) ,
TARGET_STRING ( "" ) , 3 , 0 , 0 , 0 , 1 } , { 8 , 0 , TARGET_STRING (
"fast_powertrain/Multiply3" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } ,
{ 9 , 0 , TARGET_STRING ( "fast_powertrain/1-D Lookup Table1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 10 , 0 , TARGET_STRING (
"fast_powertrain/Square" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , {
11 , 0 , TARGET_STRING ( "fast_powertrain/Product21" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 2 } , { 12 , 0 , TARGET_STRING (
"fast_powertrain/Saturation" ) , TARGET_STRING ( "radiation" ) , 0 , 0 , 0 ,
0 , 2 } , { 13 , 10 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/MATLAB Function5" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 14 , 10 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/MATLAB Function5" )
, TARGET_STRING ( "" ) , 1 , 0 , 0 , 0 , 1 } , { 15 , 0 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Unit Delay1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 16 , 0 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Unit Delay2" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 17 , 13 , TARGET_STRING (
"fast_powertrain/Boost - PV - fast/MPPT" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 1 } , { 18 , 0 , TARGET_STRING (
"fast_powertrain/Boost - PV - fast/Fcn" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 1 } , { 19 , 0 , TARGET_STRING (
"fast_powertrain/Boost - PV - fast/Fcn1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 1 } , { 20 , 0 , TARGET_STRING (
"fast_powertrain/Boost - PV - fast/Unit Delay1" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 3 } , { 21 , 0 , TARGET_STRING (
"fast_powertrain/Boost - PV - fast/Unit Delay2" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 1 } , { 22 , 0 , TARGET_STRING (
"fast_powertrain/Boost - PV - fast/Unit Delay3" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 1 } , { 23 , 0 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Fcn" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 ,
0 , 4 } , { 24 , 0 , TARGET_STRING ( "fast_powertrain/Boost FC - fast/Fcn1" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 25 , 0 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Product1" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 1 } , { 26 , 0 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Product2" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 1 } , { 27 , 0 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Sum3" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 ,
0 , 1 } , { 28 , 0 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Unit Delay2" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 4 } , { 29 , 0 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Unit Delay3" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 4 } , { 30 , 0 , TARGET_STRING (
"fast_powertrain/Discrete PI Controller2/Kp5" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 1 } , { 31 , 15 , TARGET_STRING (
"fast_powertrain/Fuzzy Logic Controller/Defuzzify Outputs" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 0 } , { 32 , 22 , TARGET_STRING (
"fast_powertrain/PEMFC matfunc V2/MATLAB Function" ) , TARGET_STRING ( "" ) ,
7 , 0 , 0 , 0 , 1 } , { 33 , 22 , TARGET_STRING (
"fast_powertrain/PEMFC matfunc V2/MATLAB Function" ) , TARGET_STRING ( "" ) ,
8 , 0 , 0 , 0 , 1 } , { 34 , 25 , TARGET_STRING (
"fast_powertrain/PV MODULE1/PV_function" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 1 } , { 35 , 0 , TARGET_STRING (
"fast_powertrain/Variable Resistor/1//R" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 0 } , { 36 , 0 , TARGET_STRING (
"fast_powertrain/Battery/Current Measurement/do not delete this gain" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 37 , 0 , TARGET_STRING (
"fast_powertrain/Battery/Model/Data Type Conversion1" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 1 } , { 38 , 0 , TARGET_STRING (
"fast_powertrain/Battery/Model/Data Type Conversion2" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 1 } , { 39 , 0 , TARGET_STRING (
"fast_powertrain/Battery/Model/Gain" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0
, 1 } , { 40 , 0 , TARGET_STRING ( "fast_powertrain/Battery/Model/Gain2" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 41 , 0 , TARGET_STRING (
"fast_powertrain/Battery/Model/R1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
1 } , { 42 , 0 , TARGET_STRING ( "fast_powertrain/Battery/Model/Memory" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 43 , 0 , TARGET_STRING (
"fast_powertrain/Battery/Model/Memory2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 1 } , { 44 , 0 , TARGET_STRING (
"fast_powertrain/Battery/Model/it init" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 4 } , { 45 , 0 , TARGET_STRING (
"fast_powertrain/Battery/Model/it init2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 4 } , { 46 , 0 , TARGET_STRING (
"fast_powertrain/Battery/Model/Saturation" ) , TARGET_STRING ( "SOC (%)" ) ,
0 , 0 , 0 , 0 , 4 } , { 47 , 0 , TARGET_STRING (
"fast_powertrain/Battery/Model/Sum" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0
, 2 } , { 48 , 0 , TARGET_STRING (
"fast_powertrain/Battery/Model/Current filter5" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 1 } , { 49 , 0 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller1/Kp5"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 50 , 0 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller2/Kp5"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 51 , 0 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller3/Kp5"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 52 , 0 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller4/Kp5"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 53 , 0 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Current Measurement/do not delete this gain"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 54 , 0 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Current Measurement1/do not delete this gain"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 55 , 0 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Discrete PI Controller3/Kp5" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 56 , 0 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Discrete PI Controller4/Kp5" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 57 , 0 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Voltage Measurement/do not delete this gain"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 58 , 0 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Voltage Measurement1/do not delete this gain"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 59 , 0 , TARGET_STRING (
"fast_powertrain/PEMFC matfunc V2/Current Measurement/do not delete this gain"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 60 , 0 , TARGET_STRING (
"fast_powertrain/PEMFC matfunc V2/Saturation Dynamic/Switch2" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 61 , 0 , TARGET_STRING (
"fast_powertrain/PV MODULE1/Current Measurement/do not delete this gain" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 62 , 0 , TARGET_STRING (
"fast_powertrain/PV MODULE1/Voltage Measurement/do not delete this gain" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 63 , 0 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"" ) , 0 , 0 , 1 , 0 , 1 } , { 64 , 0 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"" ) , 1 , 0 , 2 , 0 , 1 } , { 65 , 0 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"" ) , 2 , 0 , 0 , 0 , 1 } , { 66 , 0 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/Sum" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 0 } , { 67 , 0 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/Unit Delay" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 68 , 2 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/DOD and average current calculation Block"
) , TARGET_STRING ( "" ) , 3 , 0 , 0 , 0 , 1 } , { 69 , 2 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/DOD and average current calculation Block"
) , TARGET_STRING ( "" ) , 4 , 0 , 0 , 0 , 1 } , { 70 , 2 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/DOD and average current calculation Block"
) , TARGET_STRING ( "" ) , 5 , 0 , 0 , 0 , 1 } , { 71 , 2 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/DOD and average current calculation Block"
) , TARGET_STRING ( "" ) , 6 , 0 , 0 , 0 , 1 } , { 72 , 2 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/DOD and average current calculation Block"
) , TARGET_STRING ( "" ) , 7 , 0 , 0 , 0 , 1 } , { 73 , 2 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/DOD and average current calculation Block"
) , TARGET_STRING ( "" ) , 8 , 0 , 0 , 0 , 1 } , { 74 , 2 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/DOD and average current calculation Block"
) , TARGET_STRING ( "" ) , 9 , 0 , 0 , 0 , 1 } , { 75 , 2 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/DOD and average current calculation Block"
) , TARGET_STRING ( "" ) , 10 , 0 , 0 , 0 , 1 } , { 76 , 2 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/DOD and average current calculation Block"
) , TARGET_STRING ( "" ) , 11 , 0 , 0 , 0 , 1 } , { 77 , 2 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/DOD and average current calculation Block"
) , TARGET_STRING ( "" ) , 12 , 0 , 0 , 0 , 1 } , { 78 , 2 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/DOD and average current calculation Block"
) , TARGET_STRING ( "" ) , 13 , 0 , 0 , 0 , 1 } , { 79 , 2 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/DOD and average current calculation Block"
) , TARGET_STRING ( "" ) , 14 , 0 , 0 , 0 , 1 } , { 80 , 2 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/DOD and average current calculation Block"
) , TARGET_STRING ( "" ) , 15 , 0 , 0 , 0 , 1 } , { 81 , 2 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/DOD and average current calculation Block"
) , TARGET_STRING ( "" ) , 16 , 0 , 0 , 0 , 1 } , { 82 , 2 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/DOD and average current calculation Block"
) , TARGET_STRING ( "" ) , 17 , 0 , 0 , 0 , 1 } , { 83 , 2 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/DOD and average current calculation Block"
) , TARGET_STRING ( "" ) , 18 , 0 , 0 , 0 , 1 } , { 84 , 2 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/DOD and average current calculation Block"
) , TARGET_STRING ( "" ) , 19 , 0 , 0 , 0 , 1 } , { 85 , 2 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/DOD and average current calculation Block"
) , TARGET_STRING ( "" ) , 20 , 0 , 0 , 0 , 1 } , { 86 , 0 , TARGET_STRING (
"fast_powertrain/Battery/Model/Aging Model/Zero-Order Hold" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 87 , 0 , TARGET_STRING (
"fast_powertrain/Battery/Model/Aging Model/Zero-Order Hold1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 88 , 0 , TARGET_STRING (
"fast_powertrain/Battery/Model/Exp/Discrete-Time Integrator" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 89 , 0 , TARGET_STRING (
"fast_powertrain/Battery/Model/Exp/Gain1" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 1 } , { 90 , 0 , TARGET_STRING (
"fast_powertrain/Battery/Model/Saturation Dynamic/Switch2" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 4 } , { 91 , 0 , TARGET_STRING (
"fast_powertrain/Battery/Model/Saturation Dynamic1/Switch" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 92 , 0 , TARGET_STRING (
"fast_powertrain/PV MODULE1/Diode/Model/eee" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 2 } , { 93 , 0 , TARGET_STRING (
"fast_powertrain/Supercapacitor1/Model/Discrete/Add2" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 1 } , { 94 , 0 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/Sources/SwitchCurrents" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 2 , 0 , 2 } , { 95 , 1 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/Aging factor Calculation Block/MATLAB Function1"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 96 , 1 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/Aging factor Calculation Block/MATLAB Function1"
) , TARGET_STRING ( "" ) , 1 , 0 , 0 , 0 , 1 } , { 97 , 1 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/Aging factor Calculation Block/MATLAB Function1"
) , TARGET_STRING ( "" ) , 2 , 0 , 0 , 0 , 1 } , { 98 , 0 , TARGET_STRING (
"fast_powertrain/Battery/Model/Aging Model/Aging factor Calculation Block/Sum"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 99 , 0 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/Capacity and Internal  Resistance Adjustment Block/Fcn1"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 100 , 0 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/Max. Number of Cycles Calculation Block/Fcn"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 101 , 0 , TARGET_STRING (
 "fast_powertrain/Supercapacitor1/Model/Discrete/Self_discharge Model/Discrete-Time Integrator"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 102 , 0 , TARGET_STRING (
"fast_powertrain/Supercapacitor1/Model/Discrete/Self_discharge Model/Gain" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 103 , 0 , TARGET_STRING (
"fast_powertrain/Supercapacitor1/Model/Discrete/Self_discharge Model/Divide5"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 104 , 0 , TARGET_STRING (
"fast_powertrain/Supercapacitor1/Model/Discrete/Stern Model/Product1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 105 , 0 , TARGET_STRING (
 "fast_powertrain/Supercapacitor1/Model/Discrete/Self_discharge Model/Compare To Constant/Compare"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 1 } , { 0 , 0 , ( NULL ) , ( NULL
) , 0 , 0 , 0 , 0 , 0 } } ; static const rtwCAPI_BlockParameters
rtBlockParameters [ ] = { { 106 , TARGET_STRING ( "fast_powertrain/Battery" )
, TARGET_STRING ( "BatType" ) , 0 , 0 , 0 } , { 107 , TARGET_STRING (
"fast_powertrain/Battery" ) , TARGET_STRING ( "SOC" ) , 0 , 0 , 0 } , { 108 ,
TARGET_STRING ( "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast" ) ,
TARGET_STRING ( "n_buck" ) , 0 , 0 , 0 } , { 109 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast" ) , TARGET_STRING (
"n_boost" ) , 0 , 0 , 0 } , { 110 , TARGET_STRING (
"fast_powertrain/Boost - PV - fast" ) , TARGET_STRING ( "n" ) , 0 , 0 , 0 } ,
{ 111 , TARGET_STRING ( "fast_powertrain/Boost FC - fast" ) , TARGET_STRING (
"n" ) , 0 , 0 , 0 } , { 112 , TARGET_STRING (
"fast_powertrain/Discrete PI Controller2" ) , TARGET_STRING ( "Kp" ) , 0 , 0
, 0 } , { 113 , TARGET_STRING ( "fast_powertrain/Discrete PI Controller2" ) ,
TARGET_STRING ( "Ki" ) , 0 , 0 , 0 } , { 114 , TARGET_STRING (
"fast_powertrain/Discrete PI Controller2" ) , TARGET_STRING ( "Init" ) , 0 ,
0 , 0 } , { 115 , TARGET_STRING ( "fast_powertrain/PV MODULE1" ) ,
TARGET_STRING ( "Npar" ) , 0 , 0 , 0 } , { 116 , TARGET_STRING (
"fast_powertrain/PV MODULE1" ) , TARGET_STRING ( "Nser" ) , 0 , 0 , 0 } , {
117 , TARGET_STRING ( "fast_powertrain/PV MODULE1" ) , TARGET_STRING (
"Ncell" ) , 0 , 0 , 0 } , { 118 , TARGET_STRING (
"fast_powertrain/PV MODULE1" ) , TARGET_STRING ( "Voc" ) , 0 , 0 , 0 } , {
119 , TARGET_STRING ( "fast_powertrain/PV MODULE1" ) , TARGET_STRING ( "Isc"
) , 0 , 0 , 0 } , { 120 , TARGET_STRING ( "fast_powertrain/PV MODULE1" ) ,
TARGET_STRING ( "Vmpp" ) , 0 , 0 , 0 } , { 121 , TARGET_STRING (
"fast_powertrain/PV MODULE1" ) , TARGET_STRING ( "Impp" ) , 0 , 0 , 0 } , {
122 , TARGET_STRING ( "fast_powertrain/PV MODULE1" ) , TARGET_STRING (
"beta_Voc" ) , 0 , 0 , 0 } , { 123 , TARGET_STRING (
"fast_powertrain/PV MODULE1" ) , TARGET_STRING ( "I0" ) , 0 , 0 , 0 } , { 124
, TARGET_STRING ( "fast_powertrain/PV MODULE1" ) , TARGET_STRING ( "df" ) , 0
, 0 , 0 } , { 125 , TARGET_STRING ( "fast_powertrain/PV MODULE1" ) ,
TARGET_STRING ( "Rsh" ) , 0 , 0 , 0 } , { 126 , TARGET_STRING (
"fast_powertrain/PV MODULE1" ) , TARGET_STRING ( "Rs" ) , 0 , 0 , 0 } , { 127
, TARGET_STRING ( "fast_powertrain/Subsystem" ) , TARGET_STRING (
"irradiance_const" ) , 0 , 0 , 0 } , { 128 , TARGET_STRING (
"fast_powertrain/Variable Resistor" ) , TARGET_STRING ( "Rabsmin" ) , 0 , 0 ,
0 } , { 129 , TARGET_STRING ( "fast_powertrain/Constant4" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 130 , TARGET_STRING ( "fast_powertrain/Constant5"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 131 , TARGET_STRING (
"fast_powertrain/Constant6" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , {
132 , TARGET_STRING ( "fast_powertrain/Constant7" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 133 , TARGET_STRING ( "fast_powertrain/Constant8" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 134 , TARGET_STRING (
"fast_powertrain/Multiply2" ) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , {
135 , TARGET_STRING ( "fast_powertrain/Multiply3" ) , TARGET_STRING ( "Gain"
) , 0 , 0 , 0 } , { 136 , TARGET_STRING ( "fast_powertrain/Saturation" ) ,
TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 137 , TARGET_STRING (
"fast_powertrain/Saturation" ) , TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 }
, { 138 , TARGET_STRING ( "fast_powertrain/Battery/Ta" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 139 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller1"
) , TARGET_STRING ( "Kp" ) , 0 , 0 , 0 } , { 140 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller1"
) , TARGET_STRING ( "Ki" ) , 0 , 0 , 0 } , { 141 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller1"
) , TARGET_STRING ( "Init" ) , 0 , 0 , 0 } , { 142 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller2"
) , TARGET_STRING ( "Kp" ) , 0 , 0 , 0 } , { 143 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller2"
) , TARGET_STRING ( "Ki" ) , 0 , 0 , 0 } , { 144 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller2"
) , TARGET_STRING ( "Init" ) , 0 , 0 , 0 } , { 145 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller3"
) , TARGET_STRING ( "Kp" ) , 0 , 0 , 0 } , { 146 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller3"
) , TARGET_STRING ( "Ki" ) , 0 , 0 , 0 } , { 147 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller3"
) , TARGET_STRING ( "Init" ) , 0 , 0 , 0 } , { 148 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller4"
) , TARGET_STRING ( "Kp" ) , 0 , 0 , 0 } , { 149 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller4"
) , TARGET_STRING ( "Ki" ) , 0 , 0 , 0 } , { 150 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller4"
) , TARGET_STRING ( "Init" ) , 0 , 0 , 0 } , { 151 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 152 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Constant1" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 153 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Constant2" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 154 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Constant3" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 155 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Multiply" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 156 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Saturation" ) ,
TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 157 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Saturation" ) ,
TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 158 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Saturation1" ) ,
TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 159 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Saturation1" ) ,
TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 160 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Saturation2" ) ,
TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 161 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Saturation2" ) ,
TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 162 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Saturation3" ) ,
TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 163 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Saturation3" ) ,
TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 164 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Saturation4" ) ,
TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 165 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Saturation4" ) ,
TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 166 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Saturation6" ) ,
TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 167 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Saturation6" ) ,
TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 168 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Saturation7" ) ,
TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 169 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Saturation7" ) ,
TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 170 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Unit Delay1" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 171 , TARGET_STRING (
"fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Unit Delay2" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 172 , TARGET_STRING (
"fast_powertrain/Boost - PV - fast/Saturation1" ) , TARGET_STRING (
"UpperLimit" ) , 0 , 0 , 0 } , { 173 , TARGET_STRING (
"fast_powertrain/Boost - PV - fast/Saturation1" ) , TARGET_STRING (
"LowerLimit" ) , 0 , 0 , 0 } , { 174 , TARGET_STRING (
"fast_powertrain/Boost - PV - fast/Unit Delay1" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 175 , TARGET_STRING (
"fast_powertrain/Boost - PV - fast/Unit Delay2" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 176 , TARGET_STRING (
"fast_powertrain/Boost - PV - fast/Unit Delay3" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 177 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Discrete PI Controller3" ) , TARGET_STRING (
"Kp" ) , 0 , 0 , 0 } , { 178 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Discrete PI Controller3" ) , TARGET_STRING (
"Ki" ) , 0 , 0 , 0 } , { 179 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Discrete PI Controller3" ) , TARGET_STRING (
"Init" ) , 0 , 0 , 0 } , { 180 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Discrete PI Controller4" ) , TARGET_STRING (
"Kp" ) , 0 , 0 , 0 } , { 181 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Discrete PI Controller4" ) , TARGET_STRING (
"Ki" ) , 0 , 0 , 0 } , { 182 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Discrete PI Controller4" ) , TARGET_STRING (
"Init" ) , 0 , 0 , 0 } , { 183 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Constant" ) , TARGET_STRING ( "Value" ) , 0
, 0 , 0 } , { 184 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Constant1" ) , TARGET_STRING ( "Value" ) , 0
, 0 , 0 } , { 185 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Saturation" ) , TARGET_STRING ( "UpperLimit"
) , 0 , 0 , 0 } , { 186 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Saturation" ) , TARGET_STRING ( "LowerLimit"
) , 0 , 0 , 0 } , { 187 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Saturation1" ) , TARGET_STRING (
"UpperLimit" ) , 0 , 0 , 0 } , { 188 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Saturation1" ) , TARGET_STRING (
"LowerLimit" ) , 0 , 0 , 0 } , { 189 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Saturation2" ) , TARGET_STRING (
"UpperLimit" ) , 0 , 0 , 0 } , { 190 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Saturation2" ) , TARGET_STRING (
"LowerLimit" ) , 0 , 0 , 0 } , { 191 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Unit Delay2" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 192 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Unit Delay3" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 193 , TARGET_STRING (
"fast_powertrain/Current Measurement/do not delete this gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 194 , TARGET_STRING (
"fast_powertrain/Discrete PI Controller2/Discrete-Time Integrator" ) ,
TARGET_STRING ( "gainval" ) , 0 , 0 , 0 } , { 195 , TARGET_STRING (
"fast_powertrain/Discrete PI Controller2/Discrete-Time Integrator" ) ,
TARGET_STRING ( "UpperSaturationLimit" ) , 0 , 0 , 0 } , { 196 ,
TARGET_STRING (
"fast_powertrain/Discrete PI Controller2/Discrete-Time Integrator" ) ,
TARGET_STRING ( "LowerSaturationLimit" ) , 0 , 0 , 0 } , { 197 ,
TARGET_STRING ( "fast_powertrain/Discrete PI Controller2/Saturation2" ) ,
TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 198 , TARGET_STRING (
"fast_powertrain/Discrete PI Controller2/Saturation2" ) , TARGET_STRING (
"LowerLimit" ) , 0 , 0 , 0 } , { 199 , TARGET_STRING (
"fast_powertrain/Fuzzy Logic Controller/Output Sample Points" ) ,
TARGET_STRING ( "Value" ) , 0 , 3 , 0 } , { 200 , TARGET_STRING (
"fast_powertrain/PEMFC matfunc V2/Constant" ) , TARGET_STRING ( "Value" ) , 0
, 0 , 0 } , { 201 , TARGET_STRING (
"fast_powertrain/PEMFC matfunc V2/Discrete-Time Integrator" ) , TARGET_STRING
( "gainval" ) , 0 , 0 , 0 } , { 202 , TARGET_STRING (
"fast_powertrain/PEMFC matfunc V2/Discrete-Time Integrator" ) , TARGET_STRING
( "InitialCondition" ) , 0 , 0 , 0 } , { 203 , TARGET_STRING (
"fast_powertrain/PEMFC matfunc V2/Multiply" ) , TARGET_STRING ( "Gain" ) , 0
, 0 , 0 } , { 204 , TARGET_STRING (
"fast_powertrain/PEMFC matfunc V2/Saturation" ) , TARGET_STRING (
"UpperLimit" ) , 0 , 0 , 0 } , { 205 , TARGET_STRING (
"fast_powertrain/PEMFC matfunc V2/Saturation" ) , TARGET_STRING (
"LowerLimit" ) , 0 , 0 , 0 } , { 206 , TARGET_STRING (
"fast_powertrain/PEMFC matfunc V2/Delay" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 207 , TARGET_STRING (
"fast_powertrain/PEMFC matfunc V2/Unit Delay" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 208 , TARGET_STRING (
"fast_powertrain/PEMFC matfunc V2/Unit Delay1" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 209 , TARGET_STRING (
"fast_powertrain/PV MODULE1/Constant5" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 210 , TARGET_STRING ( "fast_powertrain/PV MODULE1/Unit Delay1" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 211 , TARGET_STRING (
"fast_powertrain/PV MODULE1/Unit Delay4" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 212 , TARGET_STRING (
"fast_powertrain/Variable Resistor/Constant5" ) , TARGET_STRING ( "Value" ) ,
0 , 0 , 0 } , { 213 , TARGET_STRING (
"fast_powertrain/Battery/Current Measurement/do not delete this gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 214 , TARGET_STRING (
"fast_powertrain/Battery/Model/Constant" ) , TARGET_STRING ( "Value" ) , 0 ,
0 , 0 } , { 215 , TARGET_STRING ( "fast_powertrain/Battery/Model/Constant1" )
, TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 216 , TARGET_STRING (
"fast_powertrain/Battery/Model/Constant12" ) , TARGET_STRING ( "Value" ) , 0
, 0 , 0 } , { 217 , TARGET_STRING (
"fast_powertrain/Battery/Model/Constant14" ) , TARGET_STRING ( "Value" ) , 0
, 0 , 0 } , { 218 , TARGET_STRING ( "fast_powertrain/Battery/Model/Constant8"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 219 , TARGET_STRING (
"fast_powertrain/Battery/Model/Constant9" ) , TARGET_STRING ( "Value" ) , 0 ,
0 , 0 } , { 220 , TARGET_STRING ( "fast_powertrain/Battery/Model/int(i)" ) ,
TARGET_STRING ( "gainval" ) , 0 , 0 , 0 } , { 221 , TARGET_STRING (
"fast_powertrain/Battery/Model/int(i)" ) , TARGET_STRING (
"UpperSaturationLimit" ) , 0 , 0 , 0 } , { 222 , TARGET_STRING (
"fast_powertrain/Battery/Model/int(i)" ) , TARGET_STRING (
"LowerSaturationLimit" ) , 0 , 0 , 0 } , { 223 , TARGET_STRING (
"fast_powertrain/Battery/Model/Gain" ) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0
} , { 224 , TARGET_STRING ( "fast_powertrain/Battery/Model/Gain2" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 225 , TARGET_STRING (
"fast_powertrain/Battery/Model/R1" ) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 }
, { 226 , TARGET_STRING ( "fast_powertrain/Battery/Model/R2" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 227 , TARGET_STRING (
"fast_powertrain/Battery/Model/R3" ) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 }
, { 228 , TARGET_STRING ( "fast_powertrain/Battery/Model/R4" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 229 , TARGET_STRING (
"fast_powertrain/Battery/Model/Memory" ) , TARGET_STRING ( "InitialCondition"
) , 0 , 0 , 0 } , { 230 , TARGET_STRING (
"fast_powertrain/Battery/Model/Memory2" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 231 , TARGET_STRING (
"fast_powertrain/Battery/Model/it init" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 232 , TARGET_STRING (
"fast_powertrain/Battery/Model/it init1" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 233 , TARGET_STRING (
"fast_powertrain/Battery/Model/Saturation" ) , TARGET_STRING ( "UpperLimit" )
, 0 , 0 , 0 } , { 234 , TARGET_STRING (
"fast_powertrain/Battery/Model/Saturation" ) , TARGET_STRING ( "LowerLimit" )
, 0 , 0 , 0 } , { 235 , TARGET_STRING (
"fast_powertrain/Battery/Model/Current filter5" ) , TARGET_STRING (
"Numerator" ) , 0 , 0 , 0 } , { 236 , TARGET_STRING (
"fast_powertrain/Battery/Model/Current filter5" ) , TARGET_STRING (
"Denominator" ) , 0 , 3 , 0 } , { 237 , TARGET_STRING (
"fast_powertrain/Battery/Model/Current filter5" ) , TARGET_STRING (
"InitialStates" ) , 0 , 0 , 0 } , { 238 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Current Measurement1/do not delete this gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 239 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Current Measurement10/do not delete this gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 240 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Current Measurement9/do not delete this gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 241 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller1/Discrete-Time Integrator"
) , TARGET_STRING ( "gainval" ) , 0 , 0 , 0 } , { 242 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller1/Discrete-Time Integrator"
) , TARGET_STRING ( "UpperSaturationLimit" ) , 0 , 0 , 0 } , { 243 ,
TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller1/Discrete-Time Integrator"
) , TARGET_STRING ( "LowerSaturationLimit" ) , 0 , 0 , 0 } , { 244 ,
TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller1/Saturation2"
) , TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 245 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller1/Saturation2"
) , TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 246 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller2/Discrete-Time Integrator"
) , TARGET_STRING ( "gainval" ) , 0 , 0 , 0 } , { 247 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller2/Discrete-Time Integrator"
) , TARGET_STRING ( "UpperSaturationLimit" ) , 0 , 0 , 0 } , { 248 ,
TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller2/Discrete-Time Integrator"
) , TARGET_STRING ( "LowerSaturationLimit" ) , 0 , 0 , 0 } , { 249 ,
TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller2/Saturation2"
) , TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 250 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller2/Saturation2"
) , TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 251 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller3/Discrete-Time Integrator"
) , TARGET_STRING ( "gainval" ) , 0 , 0 , 0 } , { 252 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller3/Discrete-Time Integrator"
) , TARGET_STRING ( "UpperSaturationLimit" ) , 0 , 0 , 0 } , { 253 ,
TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller3/Discrete-Time Integrator"
) , TARGET_STRING ( "LowerSaturationLimit" ) , 0 , 0 , 0 } , { 254 ,
TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller3/Saturation2"
) , TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 255 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller3/Saturation2"
) , TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 256 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller4/Discrete-Time Integrator"
) , TARGET_STRING ( "gainval" ) , 0 , 0 , 0 } , { 257 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller4/Discrete-Time Integrator"
) , TARGET_STRING ( "UpperSaturationLimit" ) , 0 , 0 , 0 } , { 258 ,
TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller4/Discrete-Time Integrator"
) , TARGET_STRING ( "LowerSaturationLimit" ) , 0 , 0 , 0 } , { 259 ,
TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller4/Saturation2"
) , TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 260 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Discrete PI Controller4/Saturation2"
) , TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 261 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Voltage Measurement11/do not delete this gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 262 , TARGET_STRING (
 "fast_powertrain/Bidirectional BOOST//BUCK - Batt - fast/Voltage Measurement9/do not delete this gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 263 , TARGET_STRING (
"fast_powertrain/Boost - PV - fast/Current Measurement/do not delete this gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 264 , TARGET_STRING (
"fast_powertrain/Boost - PV - fast/Current Measurement2/do not delete this gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 265 , TARGET_STRING (
"fast_powertrain/Boost - PV - fast/Voltage Measurement/do not delete this gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 266 , TARGET_STRING (
"fast_powertrain/Boost - PV - fast/Voltage Measurement1/do not delete this gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 267 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Current Measurement/do not delete this gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 268 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Current Measurement1/do not delete this gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 269 , TARGET_STRING (
 "fast_powertrain/Boost FC - fast/Discrete PI Controller3/Discrete-Time Integrator"
) , TARGET_STRING ( "gainval" ) , 0 , 0 , 0 } , { 270 , TARGET_STRING (
 "fast_powertrain/Boost FC - fast/Discrete PI Controller3/Discrete-Time Integrator"
) , TARGET_STRING ( "UpperSaturationLimit" ) , 0 , 0 , 0 } , { 271 ,
TARGET_STRING (
 "fast_powertrain/Boost FC - fast/Discrete PI Controller3/Discrete-Time Integrator"
) , TARGET_STRING ( "LowerSaturationLimit" ) , 0 , 0 , 0 } , { 272 ,
TARGET_STRING (
"fast_powertrain/Boost FC - fast/Discrete PI Controller3/Saturation2" ) ,
TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 273 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Discrete PI Controller3/Saturation2" ) ,
TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 274 , TARGET_STRING (
 "fast_powertrain/Boost FC - fast/Discrete PI Controller4/Discrete-Time Integrator"
) , TARGET_STRING ( "gainval" ) , 0 , 0 , 0 } , { 275 , TARGET_STRING (
 "fast_powertrain/Boost FC - fast/Discrete PI Controller4/Discrete-Time Integrator"
) , TARGET_STRING ( "UpperSaturationLimit" ) , 0 , 0 , 0 } , { 276 ,
TARGET_STRING (
 "fast_powertrain/Boost FC - fast/Discrete PI Controller4/Discrete-Time Integrator"
) , TARGET_STRING ( "LowerSaturationLimit" ) , 0 , 0 , 0 } , { 277 ,
TARGET_STRING (
"fast_powertrain/Boost FC - fast/Discrete PI Controller4/Saturation2" ) ,
TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 278 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Discrete PI Controller4/Saturation2" ) ,
TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 279 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Voltage Measurement/do not delete this gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 280 , TARGET_STRING (
"fast_powertrain/Boost FC - fast/Voltage Measurement1/do not delete this gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 281 , TARGET_STRING (
"fast_powertrain/PEMFC matfunc V2/Current Measurement/do not delete this gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 282 , TARGET_STRING (
"fast_powertrain/PEMFC matfunc V2/Voltage Measurement/do not delete this gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 283 , TARGET_STRING (
"fast_powertrain/PV MODULE1/Current Measurement/do not delete this gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 284 , TARGET_STRING (
"fast_powertrain/PV MODULE1/Voltage Measurement/do not delete this gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 285 , TARGET_STRING (
"fast_powertrain/Supercapacitor1/I1/do not delete this gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 286 , TARGET_STRING (
"fast_powertrain/Supercapacitor1/Voltage Measurement/do not delete this gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 287 , TARGET_STRING (
"fast_powertrain/Variable Resistor/Nearzero resistance/Switch1" ) ,
TARGET_STRING ( "Threshold" ) , 0 , 0 , 0 } , { 288 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P1" ) , 0 , 0 , 0 } , { 289 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P2" ) , 0 , 4 , 0 } , { 290 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P3" ) , 0 , 5 , 0 } , { 291 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P4" ) , 0 , 6 , 0 } , { 292 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P5" ) , 0 , 7 , 0 } , { 293 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P6" ) , 0 , 8 , 0 } , { 294 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P7" ) , 0 , 0 , 0 } , { 295 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P8" ) , 0 , 9 , 0 } , { 296 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P10" ) , 0 , 0 , 0 } , { 297 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P11" ) , 0 , 0 , 0 } , { 298 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P13" ) , 0 , 0 , 0 } , { 299 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P14" ) , 0 , 0 , 0 } , { 300 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P16" ) , 0 , 0 , 0 } , { 301 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P17" ) , 0 , 0 , 0 } , { 302 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P18" ) , 0 , 0 , 0 } , { 303 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P19" ) , 0 , 0 , 0 } , { 304 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P20" ) , 0 , 10 , 0 } , { 305 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P21" ) , 0 , 10 , 0 } , { 306 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P22" ) , 0 , 2 , 0 } , { 307 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P23" ) , 0 , 10 , 0 } , { 308 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P24" ) , 0 , 0 , 0 } , { 309 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/Unit Delay" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 310 , TARGET_STRING (
"fast_powertrain/Battery/Model/Aging Model/it init3" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 311 , TARGET_STRING (
"fast_powertrain/Battery/Model/Compare To Zero/Constant" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 312 , TARGET_STRING (
"fast_powertrain/Battery/Model/Compare To Zero2/Constant" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 313 , TARGET_STRING (
"fast_powertrain/Battery/Model/E_dyn Charge/Constant1" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 314 , TARGET_STRING (
"fast_powertrain/Battery/Model/E_dyn Charge/Constant2" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 315 , TARGET_STRING (
"fast_powertrain/Battery/Model/E_dyn Charge/Constant3" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 316 , TARGET_STRING (
"fast_powertrain/Battery/Model/E_dyn Charge/Constant4" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 317 , TARGET_STRING (
"fast_powertrain/Battery/Model/Exp/Discrete-Time Integrator" ) ,
TARGET_STRING ( "gainval" ) , 0 , 0 , 0 } , { 318 , TARGET_STRING (
"fast_powertrain/Battery/Model/Exp/Discrete-Time Integrator" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 319 , TARGET_STRING (
"fast_powertrain/Battery/Model/Exp/Gain1" ) , TARGET_STRING ( "Gain" ) , 0 ,
0 , 0 } , { 320 , TARGET_STRING ( "fast_powertrain/Battery/Model/Exp/Gain4" )
, TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 321 , TARGET_STRING (
"fast_powertrain/Battery/Model/Exp/Saturation" ) , TARGET_STRING (
"UpperLimit" ) , 0 , 0 , 0 } , { 322 , TARGET_STRING (
"fast_powertrain/Battery/Model/Exp/Saturation" ) , TARGET_STRING (
"LowerLimit" ) , 0 , 0 , 0 } , { 323 , TARGET_STRING (
"fast_powertrain/PV MODULE1/Diode/Model/eee" ) , TARGET_STRING ( "Value" ) ,
0 , 0 , 0 } , { 324 , TARGET_STRING (
"fast_powertrain/Supercapacitor1/Model/Discrete/Constant19" ) , TARGET_STRING
( "Value" ) , 0 , 0 , 0 } , { 325 , TARGET_STRING (
"fast_powertrain/Supercapacitor1/Model/Discrete/Discrete-Time Integrator" ) ,
TARGET_STRING ( "gainval" ) , 0 , 0 , 0 } , { 326 , TARGET_STRING (
"fast_powertrain/Supercapacitor1/Model/Discrete/Discrete-Time Integrator" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 327 , TARGET_STRING (
"fast_powertrain/powergui1/EquivalentModel1/Sources/SwitchCurrents" ) ,
TARGET_STRING ( "Value" ) , 0 , 2 , 0 } , { 328 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/Aging factor Calculation Block/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 329 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/Aging factor Calculation Block/Constant1"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 330 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/Aging factor Calculation Block/Memory"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 331 ,
TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/Aging factor Calculation Block/Memory1"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 332 ,
TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/Aging factor Calculation Block/Memory2"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 333 ,
TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/Aging factor Calculation Block/Memory3"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 334 ,
TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/Aging factor Calculation Block/Saturation"
) , TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 335 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/Aging factor Calculation Block/Saturation"
) , TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 336 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/Aging factor Calculation Block/Saturation1"
) , TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 337 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/Aging factor Calculation Block/Saturation1"
) , TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 338 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/Aging factor Calculation Block/Saturation2"
) , TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 339 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/Aging factor Calculation Block/Saturation2"
) , TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 340 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/Max. Number of Cycles Calculation Block/Saturation"
) , TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 341 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/Max. Number of Cycles Calculation Block/Saturation"
) , TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 342 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/Max. Number of Cycles Calculation Block/Saturation1"
) , TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 343 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/Max. Number of Cycles Calculation Block/Saturation1"
) , TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 344 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/Max. Number of Cycles Calculation Block/Saturation2"
) , TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 345 , TARGET_STRING (
 "fast_powertrain/Battery/Model/Aging Model/Max. Number of Cycles Calculation Block/Saturation2"
) , TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 346 , TARGET_STRING (
"fast_powertrain/Battery/Model/Aging Model/Subsystem/Memory" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 347 , TARGET_STRING (
"fast_powertrain/Battery/Model/Aging Model/Subsystem/Memory1" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 348 , TARGET_STRING (
"fast_powertrain/Battery/Model/Aging Model/Subsystem/Memory10" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 349 , TARGET_STRING (
"fast_powertrain/Battery/Model/Aging Model/Subsystem/Memory11" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 350 , TARGET_STRING (
"fast_powertrain/Battery/Model/Aging Model/Subsystem/Memory12" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 351 , TARGET_STRING (
"fast_powertrain/Battery/Model/Aging Model/Subsystem/Memory13" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 352 , TARGET_STRING (
"fast_powertrain/Battery/Model/Aging Model/Subsystem/Memory14" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 353 , TARGET_STRING (
"fast_powertrain/Battery/Model/Aging Model/Subsystem/Memory15" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 354 , TARGET_STRING (
"fast_powertrain/Battery/Model/Aging Model/Subsystem/Memory16" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 355 , TARGET_STRING (
"fast_powertrain/Battery/Model/Aging Model/Subsystem/Memory17" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 356 , TARGET_STRING (
"fast_powertrain/Battery/Model/Aging Model/Subsystem/Memory2" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 357 , TARGET_STRING (
"fast_powertrain/Battery/Model/Aging Model/Subsystem/Memory3" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 358 , TARGET_STRING (
"fast_powertrain/Battery/Model/Aging Model/Subsystem/Memory4" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 359 , TARGET_STRING (
"fast_powertrain/Battery/Model/Aging Model/Subsystem/Memory5" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 360 , TARGET_STRING (
"fast_powertrain/Battery/Model/Aging Model/Subsystem/Memory6" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 361 , TARGET_STRING (
"fast_powertrain/Battery/Model/Aging Model/Subsystem/Memory7" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 362 , TARGET_STRING (
"fast_powertrain/Battery/Model/Aging Model/Subsystem/Memory9" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 363 , TARGET_STRING (
"fast_powertrain/Battery/Model/Exp/Compare To Zero2/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 364 , TARGET_STRING (
 "fast_powertrain/Supercapacitor1/Model/Discrete/Self_discharge Model/Compare To Constant"
) , TARGET_STRING ( "const" ) , 0 , 0 , 0 } , { 365 , TARGET_STRING (
"fast_powertrain/Supercapacitor1/Model/Discrete/Self_discharge Model/Constant1"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 366 , TARGET_STRING (
"fast_powertrain/Supercapacitor1/Model/Discrete/Self_discharge Model/Constant2"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 367 , TARGET_STRING (
"fast_powertrain/Supercapacitor1/Model/Discrete/Self_discharge Model/Constant3"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 368 , TARGET_STRING (
"fast_powertrain/Supercapacitor1/Model/Discrete/Self_discharge Model/Constant4"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 369 , TARGET_STRING (
 "fast_powertrain/Supercapacitor1/Model/Discrete/Self_discharge Model/Discrete-Time Integrator"
) , TARGET_STRING ( "gainval" ) , 0 , 0 , 0 } , { 370 , TARGET_STRING (
 "fast_powertrain/Supercapacitor1/Model/Discrete/Self_discharge Model/Discrete-Time Integrator"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 371 ,
TARGET_STRING (
 "fast_powertrain/Supercapacitor1/Model/Discrete/Self_discharge Model/Discrete-Time Integrator1"
) , TARGET_STRING ( "gainval" ) , 0 , 0 , 0 } , { 372 , TARGET_STRING (
 "fast_powertrain/Supercapacitor1/Model/Discrete/Self_discharge Model/Discrete-Time Integrator1"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 373 ,
TARGET_STRING (
"fast_powertrain/Supercapacitor1/Model/Discrete/Self_discharge Model/Gain" )
, TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 374 , TARGET_STRING (
"fast_powertrain/Supercapacitor1/Model/Discrete/Self_discharge Model/Unit Delay"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 375 ,
TARGET_STRING (
 "fast_powertrain/Supercapacitor1/Model/Discrete/Self_discharge Model/Unit Delay2"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 376 ,
TARGET_STRING (
"fast_powertrain/Supercapacitor1/Model/Discrete/Stern Model/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 377 , TARGET_STRING (
"fast_powertrain/Supercapacitor1/Model/Discrete/Stern Model/Constant1" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 378 , TARGET_STRING (
"fast_powertrain/Supercapacitor1/Model/Discrete/Stern Model/Saturation" ) ,
TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 379 , TARGET_STRING (
"fast_powertrain/Supercapacitor1/Model/Discrete/Stern Model/Saturation" ) ,
TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 0 , ( NULL ) , ( NULL ) , 0
, 0 , 0 } } ; static const rtwCAPI_Signals rtRootInputs [ ] = { { 0 , 0 , (
NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ; static const rtwCAPI_Signals
rtRootOutputs [ ] = { { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ;
static const rtwCAPI_ModelParameters rtModelParameters [ ] = { { 380 ,
TARGET_STRING ( "t" ) , 0 , 11 , 0 } , { 381 , TARGET_STRING ( "w" ) , 0 , 11
, 0 } , { 0 , ( NULL ) , 0 , 0 , 0 } } ;
#ifndef HOST_CAPI_BUILD
static void * rtDataAddrMap [ ] = { & rtB . b5ekoo4s5v , & rtB . djegcg25ae ,
& rtB . ijubt5styh , & rtB . fxmmxdki1w , & rtB . mykimnyubj , & rtB .
idvqtvfoyk , & rtB . dgk2xu5prp , & rtB . fsyjc2e3jn , & rtB . pkp0sjqqg3 , &
rtB . l1bfou4fat , & rtB . b11tooymbq , & rtB . npdclyuhqf , & rtB .
k401caq3eb , & rtB . e2chijmfh2 , & rtB . ajuoykrpve , & rtB . i0ujncnh35 , &
rtB . bnsiwqbz4c , & rtB . ktal25amyn , & rtB . glbb5pdj1b , & rtB .
i5qlxhsaeo , & rtB . cataaai4vr , & rtB . dplapzekhr , & rtB . nd5vhw3hdp , &
rtB . hejghjylpf , & rtB . lkdpawgj3d , & rtB . fiwvizlnvo , & rtB .
ds12aiafx0 , & rtB . nh1zxcsjip , & rtB . b2m0nyy1iq , & rtB . pkslvtv3r5 , &
rtB . b0ihg4ev5s , & rtB . b5ekoo4s5v , & rtB . pmkgps0zyu , & rtB .
crs0im5dqp , & rtB . cp1s511zvk , & rtB . mdng4h4wi3 , & rtB . k04sqjkmui , &
rtB . igs1gia5uf , & rtB . nzprtrw2gw , & rtB . ltu4eypckt , & rtB .
nfrcslok3r , & rtB . bp13llqzit , & rtB . ewf3nftshe , & rtB . hxodaq3aem , &
rtB . cw3ajebfce , & rtB . cabjp2xkxg , & rtB . jqk43gypqg , & rtB .
ju3eqofxsv , & rtB . krbxk224wc , & rtB . lwbnk1tqoe , & rtB . lnggl4hxqa , &
rtB . cnvh3z11oj , & rtB . caydqvbppv , & rtB . kx2yvfrvbs , & rtB .
pydykgygzv , & rtB . gvxuq2ivcx , & rtB . oaypl0xy40 , & rtB . bbivpaarxt , &
rtB . mm1bpfcahk , & rtB . i4u1u0nk00 , & rtB . dg1zqpobap , & rtB .
nw10mpmiwb , & rtB . dsv2bbs0k1 , & rtB . ds4vmpgjgq [ 0 ] , & rtB .
aprtxoz0cz [ 0 ] , & rtB . dsl30exhdf , & rtB . aunoa00r4h , & rtB .
akgc550kdx , & rtB . orc5wcdxm1 , & rtB . akwd4yohpb , & rtB . hwgkbedju4 , &
rtB . akgbctleuf , & rtB . fjva4ba3yf , & rtB . ojpp3hq5ld , & rtB .
ddwaerj1qf , & rtB . e4esbiadth , & rtB . dv32o2egzr , & rtB . b1fl12txsf , &
rtB . liwqgy4ofb , & rtB . cf3awerlht , & rtB . o0lhjiunqy , & rtB .
i4esmxfcaq , & rtB . ewvuxv0roa , & rtB . frtehkabsr , & rtB . paaipnyjy4 , &
rtB . ctjnl3duhv , & rtB . hdopse5d1y , & rtB . mz2im1vd2w , & rtB .
nba4nhpuqe , & rtB . gswcpufwfm , & rtB . klfwarvagc , & rtB . pg2rvzlxso , &
rtB . ftivrztnav , & rtB . ee4dkbgmbt , & rtB . oaxo1bryj0 [ 0 ] , & rtB .
h0hkib4ron , & rtB . gxs3xlh0jb , & rtB . cuh2ly0avr , & rtB . jjcrtkkpmt , &
rtB . aoywj0c0aw , & rtB . jpdjo1yg5c , & rtB . dn4cfjoyu3 , & rtB .
d2aecp5kgr , & rtB . a3xn5q0qbv , & rtB . m2zun0bmq0 , & rtB . nvvl1et5cw , &
rtP . Battery_BatType , & rtP . Battery_SOC , & rtP .
BidirectionalBOOSTBUCKBattfast_n_buck , & rtP .
BidirectionalBOOSTBUCKBattfast_n_boost , & rtP . BoostPVfast_n , & rtP .
BoostFCfast_n , & rtP . DiscretePIController2_Kp , & rtP .
DiscretePIController2_Ki_lu2imaebpa , & rtP . DiscretePIController2_Init , &
rtP . PVMODULE1_Npar , & rtP . PVMODULE1_Nser , & rtP . PVMODULE1_Ncell , &
rtP . PVMODULE1_Voc , & rtP . PVMODULE1_Isc , & rtP . PVMODULE1_Vmpp , & rtP
. PVMODULE1_Impp , & rtP . PVMODULE1_beta_Voc , & rtP . PVMODULE1_I0 , & rtP
. PVMODULE1_df , & rtP . PVMODULE1_Rsh , & rtP . PVMODULE1_Rs , & rtP .
Subsystem_irradiance_const , & rtP . VariableResistor_Rabsmin , & rtP .
Constant4_Value , & rtP . Constant5_Value_kbjoyjqk2a , & rtP .
Constant6_Value , & rtP . Constant7_Value , & rtP . Constant8_Value , & rtP .
Multiply2_Gain , & rtP . Multiply3_Gain , & rtP .
Saturation_UpperSat_nd1j1mqyat , & rtP . Saturation_LowerSat_jwye2411i5 , &
rtP . Ta_Value , & rtP . DiscretePIController1_Kp , & rtP .
DiscretePIController1_Ki , & rtP . DiscretePIController1_Init , & rtP .
DiscretePIController2_Kp_jtir0rv5nd , & rtP . DiscretePIController2_Ki , &
rtP . DiscretePIController2_Init_naho2d0zuf , & rtP .
DiscretePIController3_Kp , & rtP . DiscretePIController3_Ki , & rtP .
DiscretePIController3_Init , & rtP . DiscretePIController4_Kp , & rtP .
DiscretePIController4_Ki , & rtP . DiscretePIController4_Init , & rtP .
Constant_Value_ffncqspxq4 , & rtP . Constant1_Value , & rtP . Constant2_Value
, & rtP . Constant3_Value , & rtP . Multiply_Gain_dppzkzoubi , & rtP .
Saturation_UpperSat_jsjpgzsi1y , & rtP . Saturation_LowerSat_ebjhnxsenp , &
rtP . Saturation1_UpperSat , & rtP . Saturation1_LowerSat , & rtP .
Saturation2_UpperSat_amgcitvjo2 , & rtP . Saturation2_LowerSat_lkim1nsn2b , &
rtP . Saturation3_UpperSat , & rtP . Saturation3_LowerSat , & rtP .
Saturation4_UpperSat , & rtP . Saturation4_LowerSat , & rtP .
Saturation6_UpperSat , & rtP . Saturation6_LowerSat , & rtP .
Saturation7_UpperSat , & rtP . Saturation7_LowerSat , & rtP .
UnitDelay1_InitialCondition , & rtP . UnitDelay2_InitialCondition_mynahauzpq
, & rtP . Saturation1_UpperSat_jbsy2jdb2e , & rtP .
Saturation1_LowerSat_km3pw1r5au , & rtP .
UnitDelay1_InitialCondition_gagfd2xjhh , & rtP . UnitDelay2_InitialCondition
, & rtP . UnitDelay3_InitialCondition , & rtP .
DiscretePIController3_Kp_ppecbhclte , & rtP .
DiscretePIController3_Ki_catboe4e3q , & rtP .
DiscretePIController3_Init_lcdytxavmn , & rtP .
DiscretePIController4_Kp_crtfhdlpjf , & rtP .
DiscretePIController4_Ki_ksfhmxpwtu , & rtP .
DiscretePIController4_Init_ojyv5ifd0r , & rtP . Constant_Value_jrk1wafdx5 , &
rtP . Constant1_Value_avw5uhdxx5 , & rtP . Saturation_UpperSat_e2l0llad23 , &
rtP . Saturation_LowerSat_daenvoeirh , & rtP .
Saturation1_UpperSat_ix0yodnig1 , & rtP . Saturation1_LowerSat_nfi0d0pja5 , &
rtP . Saturation2_UpperSat_aip5hjdd2y , & rtP .
Saturation2_LowerSat_czr0zyeyrx , & rtP .
UnitDelay2_InitialCondition_kplvr2c540 , & rtP .
UnitDelay3_InitialCondition_kgclqpwylc , & rtP .
donotdeletethisgain_Gain_bvblu5w4wa , & rtP .
DiscreteTimeIntegrator_gainval_jv55x3tqio , & rtP .
DiscreteTimeIntegrator_UpperSat_n2g2yvldpg , & rtP .
DiscreteTimeIntegrator_LowerSat_fv0zcc4hsa , & rtP . Saturation2_UpperSat , &
rtP . Saturation2_LowerSat , & rtP . OutputSamplePoints_Value [ 0 ] , & rtP .
Constant_Value_kfm5xzok4i , & rtP . DiscreteTimeIntegrator_gainval_m4ai2wnufy
, & rtP . DiscreteTimeIntegrator_IC_bjhalm0xhc , & rtP . Multiply_Gain , &
rtP . Saturation_UpperSat_gvrgxklgqx , & rtP . Saturation_LowerSat_cndq0w2uve
, & rtP . Delay_InitialCondition , & rtP . UnitDelay_InitialCondition , & rtP
. UnitDelay1_InitialCondition_b5qtmccqei , & rtP . Constant5_Value_k3metw3ccu
, & rtP . UnitDelay1_InitialCondition_pmpt1ejnb2 , & rtP .
UnitDelay4_InitialCondition , & rtP . Constant5_Value , & rtP .
donotdeletethisgain_Gain_e2kry42snu , & rtP . Constant_Value_m3ckpdnl3e , &
rtP . Constant1_Value_bcnppbahb4 , & rtP . Constant12_Value , & rtP .
Constant14_Value , & rtP . Constant8_Value_hfo2s31sle , & rtP .
Constant9_Value , & rtP . inti_gainval , & rtP . inti_UpperSat , & rtP .
inti_LowerSat , & rtP . Gain_Gain , & rtP . Gain2_Gain , & rtP . R1_Gain , &
rtP . R2_Gain , & rtP . R3_Gain , & rtP . R4_Gain , & rtP .
Memory_InitialCondition , & rtP . Memory2_InitialCondition , & rtP .
itinit_InitialCondition , & rtP . itinit1_InitialCondition , & rtP .
Saturation_UpperSat_ms3dxtbvew , & rtP . Saturation_LowerSat_p3nlfvz151 , &
rtP . Currentfilter5_NumCoef , & rtP . Currentfilter5_DenCoef [ 0 ] , & rtP .
Currentfilter5_InitialStates , & rtP . donotdeletethisgain_Gain , & rtP .
donotdeletethisgain_Gain_kzwtp4lcwh , & rtP .
donotdeletethisgain_Gain_jjlpkzumz0 , & rtP .
DiscreteTimeIntegrator_gainval_figs31oe21 , & rtP .
DiscreteTimeIntegrator_UpperSat , & rtP . DiscreteTimeIntegrator_LowerSat , &
rtP . Saturation2_UpperSat_a2flzvrl0h , & rtP .
Saturation2_LowerSat_imcsw2haey , & rtP .
DiscreteTimeIntegrator_gainval_k22hedow4a , & rtP .
DiscreteTimeIntegrator_UpperSat_j2u1431tvu , & rtP .
DiscreteTimeIntegrator_LowerSat_bvygkv3zts , & rtP .
Saturation2_UpperSat_csxykusiqi , & rtP . Saturation2_LowerSat_djxegxbmlp , &
rtP . DiscreteTimeIntegrator_gainval_adna3qjceq , & rtP .
DiscreteTimeIntegrator_UpperSat_iu43zm3tho , & rtP .
DiscreteTimeIntegrator_LowerSat_bdtob5uhem , & rtP .
Saturation2_UpperSat_ldjga0hth1 , & rtP . Saturation2_LowerSat_ebdt35gruq , &
rtP . DiscreteTimeIntegrator_gainval_djg22thboz , & rtP .
DiscreteTimeIntegrator_UpperSat_k2jkcmkhdm , & rtP .
DiscreteTimeIntegrator_LowerSat_gmrhfgoeip , & rtP .
Saturation2_UpperSat_pjhhcyvloo , & rtP . Saturation2_LowerSat_j0yt25ma5v , &
rtP . donotdeletethisgain_Gain_pc1oacxtz5 , & rtP .
donotdeletethisgain_Gain_fbjp1xgx2i , & rtP .
donotdeletethisgain_Gain_ghiynr5jt3 , & rtP .
donotdeletethisgain_Gain_jhmspkg22p , & rtP .
donotdeletethisgain_Gain_l30jrki0pa , & rtP .
donotdeletethisgain_Gain_m3s0jpprkc , & rtP .
donotdeletethisgain_Gain_fiwukkn2yr , & rtP .
donotdeletethisgain_Gain_bnrrpg33he , & rtP .
DiscreteTimeIntegrator_gainval_cdol2y5vzn , & rtP .
DiscreteTimeIntegrator_UpperSat_hfo2y053hj , & rtP .
DiscreteTimeIntegrator_LowerSat_c0vq2ip5xz , & rtP .
Saturation2_UpperSat_fkd04pf2k1 , & rtP . Saturation2_LowerSat_mzohmr2g2n , &
rtP . DiscreteTimeIntegrator_gainval_cqdxvpityq , & rtP .
DiscreteTimeIntegrator_UpperSat_bbsxbmka10 , & rtP .
DiscreteTimeIntegrator_LowerSat_fbeqnj3sm1 , & rtP .
Saturation2_UpperSat_kim5qyxfwz , & rtP . Saturation2_LowerSat_dlfntvjpxg , &
rtP . donotdeletethisgain_Gain_ntvbbpumog , & rtP .
donotdeletethisgain_Gain_mnd4o03d53 , & rtP .
donotdeletethisgain_Gain_hbuypofava , & rtP .
donotdeletethisgain_Gain_liz3gjfhcs , & rtP .
donotdeletethisgain_Gain_hoplgufukg , & rtP .
donotdeletethisgain_Gain_hqauyrnmgx , & rtP .
donotdeletethisgain_Gain_nzzshfnxdx , & rtP .
donotdeletethisgain_Gain_pnt2zcpibt , & rtP . Switch1_Threshold , & rtP .
StateSpace_P1 , & rtP . StateSpace_P2 [ 0 ] , & rtP . StateSpace_P3 [ 0 ] , &
rtP . StateSpace_P4 [ 0 ] , & rtP . StateSpace_P5 [ 0 ] , & rtP .
StateSpace_P6 [ 0 ] , & rtP . StateSpace_P7 , & rtP . StateSpace_P8 [ 0 ] , &
rtP . StateSpace_P10 , & rtP . StateSpace_P11 , & rtP . StateSpace_P13 , &
rtP . StateSpace_P14 , & rtP . StateSpace_P16 , & rtP . StateSpace_P17 , &
rtP . StateSpace_P18 , & rtP . StateSpace_P19 , & rtP . StateSpace_P20 [ 0 ]
, & rtP . StateSpace_P21 [ 0 ] , & rtP . StateSpace_P22 [ 0 ] , & rtP .
StateSpace_P23 [ 0 ] , & rtP . StateSpace_P24 , & rtP .
UnitDelay_InitialCondition_ckvjp4gfil , & rtP . itinit3_InitialCondition , &
rtP . Constant_Value , & rtP . Constant_Value_lc2t2ikfiz , & rtP .
Constant1_Value_ixcqqm1d4w , & rtP . Constant2_Value_m10aoab32w , & rtP .
Constant3_Value_nmyyw0epx1 , & rtP . Constant4_Value_jmvupybtnc , & rtP .
DiscreteTimeIntegrator_gainval , & rtP . DiscreteTimeIntegrator_IC , & rtP .
Gain1_Gain , & rtP . Gain4_Gain , & rtP . Saturation_UpperSat , & rtP .
Saturation_LowerSat , & rtP . eee_Value , & rtP . Constant19_Value , & rtP .
DiscreteTimeIntegrator_gainval_lknx5x0oaz , & rtP .
DiscreteTimeIntegrator_IC_p2dyd1g5fi , & rtP . SwitchCurrents_Value [ 0 ] , &
rtP . Constant_Value_nct1bh10mh , & rtP . Constant1_Value_aacpe0p2s4 , & rtP
. Memory_InitialCondition_afcza04ewo , & rtP .
Memory1_InitialCondition_eyxrd3us35 , & rtP .
Memory2_InitialCondition_otmdfxbv2b , & rtP .
Memory3_InitialCondition_npuv0s0rz0 , & rtP . Saturation_UpperSat_hsf1hlgzdw
, & rtP . Saturation_LowerSat_peon1dscjc , & rtP .
Saturation1_UpperSat_joqzp4lauk , & rtP . Saturation1_LowerSat_cp5xe3rdvj , &
rtP . Saturation2_UpperSat_lknfecgs12 , & rtP .
Saturation2_LowerSat_djkw5ghtjz , & rtP . Saturation_UpperSat_ip0sfxxemb , &
rtP . Saturation_LowerSat_oc4mpky1ii , & rtP .
Saturation1_UpperSat_hftla4v5jl , & rtP . Saturation1_LowerSat_mlv0levcl5 , &
rtP . Saturation2_UpperSat_fd3ezm0unh , & rtP .
Saturation2_LowerSat_a0oq1v4uhe , & rtP . Memory_InitialCondition_fgdsbtcau2
, & rtP . Memory1_InitialCondition , & rtP . Memory10_InitialCondition , &
rtP . Memory11_InitialCondition , & rtP . Memory12_InitialCondition , & rtP .
Memory13_InitialCondition , & rtP . Memory14_InitialCondition , & rtP .
Memory15_InitialCondition , & rtP . Memory16_InitialCondition , & rtP .
Memory17_InitialCondition , & rtP . Memory2_InitialCondition_nmqdt3zohg , &
rtP . Memory3_InitialCondition , & rtP . Memory4_InitialCondition , & rtP .
Memory5_InitialCondition , & rtP . Memory6_InitialCondition , & rtP .
Memory7_InitialCondition , & rtP . Memory9_InitialCondition , & rtP .
Constant_Value_pty4zc05uj , & rtP . CompareToConstant_const , & rtP .
Constant1_Value_lfvx2nwcp2 , & rtP . Constant2_Value_krq4yfjnno , & rtP .
Constant3_Value_acddb2uoov , & rtP . Constant4_Value_fthefd0get , & rtP .
DiscreteTimeIntegrator_gainval_fhcrjdv1um , & rtP .
DiscreteTimeIntegrator_IC_muc3fdmls2 , & rtP .
DiscreteTimeIntegrator1_gainval , & rtP . DiscreteTimeIntegrator1_IC , & rtP
. Gain_Gain_duepg35cnl , & rtP . UnitDelay_InitialCondition_br0av5wkrv , &
rtP . UnitDelay2_InitialCondition_bdexezlukf , & rtP .
Constant_Value_oibu00r03f , & rtP . Constant1_Value_ktzhc0x1wo , & rtP .
Saturation_UpperSat_e2k0qdtv2s , & rtP . Saturation_LowerSat_d5xrshbz0z , &
rtP . t [ 0 ] , & rtP . w [ 0 ] , } ; static int32_T * rtVarDimsAddrMap [ ] =
{ ( NULL ) } ;
#endif
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap [ ] = { { "double" ,
"real_T" , 0 , 0 , sizeof ( real_T ) , SS_DOUBLE , 0 , 0 , 0 } , {
"unsigned char" , "boolean_T" , 0 , 0 , sizeof ( boolean_T ) , SS_BOOLEAN , 0
, 0 , 0 } } ;
#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif
static TARGET_CONST rtwCAPI_ElementMap rtElementMap [ ] = { { ( NULL ) , 0 ,
0 , 0 , 0 } , } ; static const rtwCAPI_DimensionMap rtDimensionMap [ ] = { {
rtwCAPI_SCALAR , 0 , 2 , 0 } , { rtwCAPI_VECTOR , 2 , 2 , 0 } , {
rtwCAPI_VECTOR , 4 , 2 , 0 } , { rtwCAPI_VECTOR , 6 , 2 , 0 } , {
rtwCAPI_MATRIX_COL_MAJOR , 8 , 2 , 0 } , { rtwCAPI_MATRIX_COL_MAJOR , 10 , 2
, 0 } , { rtwCAPI_MATRIX_COL_MAJOR , 12 , 2 , 0 } , {
rtwCAPI_MATRIX_COL_MAJOR , 14 , 2 , 0 } , { rtwCAPI_VECTOR , 16 , 2 , 0 } , {
rtwCAPI_VECTOR , 18 , 2 , 0 } , { rtwCAPI_VECTOR , 20 , 2 , 0 } , {
rtwCAPI_VECTOR , 22 , 2 , 0 } } ; static const uint_T rtDimensionArray [ ] =
{ 1 , 1 , 38 , 1 , 12 , 1 , 1 , 2 , 13 , 13 , 13 , 24 , 38 , 13 , 38 , 24 ,
13 , 1 , 1 , 3 , 1 , 12 , 1 , 12000 } ; static const real_T
rtcapiStoredFloats [ ] = { 0.0 , 0.001 , 0.01 , 0.0001 } ; static const
rtwCAPI_FixPtMap rtFixPtMap [ ] = { { ( NULL ) , ( NULL ) ,
rtwCAPI_FIX_RESERVED , 0 , 0 , 0 } , } ; static const rtwCAPI_SampleTimeMap
rtSampleTimeMap [ ] = { { ( const void * ) & rtcapiStoredFloats [ 0 ] , (
const void * ) & rtcapiStoredFloats [ 0 ] , 0 , 0 } , { ( const void * ) &
rtcapiStoredFloats [ 1 ] , ( const void * ) & rtcapiStoredFloats [ 0 ] , 2 ,
0 } , { ( NULL ) , ( NULL ) , 4 , 0 } , { ( const void * ) &
rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 0 ] , 3 ,
0 } , { ( const void * ) & rtcapiStoredFloats [ 3 ] , ( const void * ) &
rtcapiStoredFloats [ 0 ] , 1 , 0 } } ; static rtwCAPI_ModelMappingStaticInfo
mmiStatic = { { rtBlockSignals , 106 , rtRootInputs , 0 , rtRootOutputs , 0 }
, { rtBlockParameters , 274 , rtModelParameters , 2 } , { ( NULL ) , 0 } , {
rtDataTypeMap , rtDimensionMap , rtFixPtMap , rtElementMap , rtSampleTimeMap
, rtDimensionArray } , "float" , { 1762363870U , 1195011890U , 2924741027U ,
1444366352U } , ( NULL ) , 0 , 0 } ; const rtwCAPI_ModelMappingStaticInfo *
fast_powertrain_GetCAPIStaticMap ( void ) { return & mmiStatic ; }
#ifndef HOST_CAPI_BUILD
void fast_powertrain_InitializeDataMapInfo ( void ) { rtwCAPI_SetVersion ( (
* rt_dataMapInfoPtr ) . mmi , 1 ) ; rtwCAPI_SetStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , & mmiStatic ) ; rtwCAPI_SetLoggingStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ; rtwCAPI_SetDataAddressMap ( ( *
rt_dataMapInfoPtr ) . mmi , rtDataAddrMap ) ; rtwCAPI_SetVarDimsAddressMap (
( * rt_dataMapInfoPtr ) . mmi , rtVarDimsAddrMap ) ;
rtwCAPI_SetInstanceLoggingInfo ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArray ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( ( * rt_dataMapInfoPtr ) . mmi , 0 ) ; }
#else
#ifdef __cplusplus
extern "C" {
#endif
void fast_powertrain_host_InitializeDataMapInfo (
fast_powertrain_host_DataMapInfo_T * dataMap , const char * path ) {
rtwCAPI_SetVersion ( dataMap -> mmi , 1 ) ; rtwCAPI_SetStaticMap ( dataMap ->
mmi , & mmiStatic ) ; rtwCAPI_SetDataAddressMap ( dataMap -> mmi , NULL ) ;
rtwCAPI_SetVarDimsAddressMap ( dataMap -> mmi , NULL ) ; rtwCAPI_SetPath (
dataMap -> mmi , path ) ; rtwCAPI_SetFullPath ( dataMap -> mmi , NULL ) ;
rtwCAPI_SetChildMMIArray ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( dataMap -> mmi , 0 ) ; }
#ifdef __cplusplus
}
#endif
#endif

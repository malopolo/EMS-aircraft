#ifndef RTW_HEADER_fast_powertrain_h_
#define RTW_HEADER_fast_powertrain_h_
#include <stddef.h>
#include <string.h>
#include "rtw_modelmap.h"
#ifndef fast_powertrain_COMMON_INCLUDES_
#define fast_powertrain_COMMON_INCLUDES_
#include <stdlib.h>
#include "sl_AsyncioQueue/AsyncioQueueCAPI.h"
#include "rtwtypes.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "simtarget/slSimTgtSlioSdiRTW.h"
#include "sigstream_rtw.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "rt_logging.h"
#include "dt_info.h"
#include "ext_work.h"
#endif
#include "fast_powertrain_types.h"
#include "multiword_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include "rtGetInf.h"
#include "rt_defines.h"
#define MODEL_NAME fast_powertrain
#define NSAMPLE_TIMES (5) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (105) 
#define NUM_ZC_EVENTS (0) 
#ifndef NCSTATES
#define NCSTATES (0)   
#elif NCSTATES != 0
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (*rt_dataMapInfoPtr)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val) (rt_dataMapInfoPtr = &val)
#endif
#ifndef IN_RACCEL_MAIN
#endif
typedef struct { real_T krbxk224wc ; real_T nzprtrw2gw ; real_T cw3ajebfce ;
real_T ltu4eypckt ; real_T pg2rvzlxso ; real_T igs1gia5uf ; real_T nba4nhpuqe
; real_T hxodaq3aem ; real_T klfwarvagc ; real_T i0ujncnh35 ; real_T
dplapzekhr ; real_T b2m0nyy1iq ; real_T dg1zqpobap ; real_T m2zun0bmq0 ;
real_T bnsiwqbz4c ; real_T nd5vhw3hdp ; real_T pkslvtv3r5 ; real_T l1bfou4fat
; real_T mdng4h4wi3 ; real_T akgc550kdx ; real_T aunoa00r4h ; real_T
ds4vmpgjgq [ 38 ] ; real_T aprtxoz0cz [ 12 ] ; real_T dsl30exhdf ; real_T
lwbnk1tqoe ; real_T lnggl4hxqa ; real_T cnvh3z11oj ; real_T caydqvbppv ;
real_T cataaai4vr ; real_T glbb5pdj1b ; real_T i5qlxhsaeo ; real_T kx2yvfrvbs
; real_T pydykgygzv ; real_T i4u1u0nk00 ; real_T bbivpaarxt ; real_T
nh1zxcsjip ; real_T gvxuq2ivcx ; real_T fiwvizlnvo ; real_T mm1bpfcahk ;
real_T ds12aiafx0 ; real_T oaypl0xy40 ; real_T hejghjylpf ; real_T lkdpawgj3d
; real_T b0ihg4ev5s ; real_T dn4cfjoyu3 ; real_T ee4dkbgmbt ; real_T
a3xn5q0qbv ; real_T d2aecp5kgr ; real_T jqk43gypqg ; real_T k04sqjkmui ;
real_T ewf3nftshe ; real_T hdopse5d1y ; real_T cabjp2xkxg ; real_T mz2im1vd2w
; real_T jpdjo1yg5c ; real_T jjcrtkkpmt ; real_T aoywj0c0aw ; real_T
gswcpufwfm ; real_T nfrcslok3r ; real_T bp13llqzit ; real_T nw10mpmiwb ;
real_T dsv2bbs0k1 ; real_T oaxo1bryj0 [ 12 ] ; real_T pkp0sjqqg3 ; real_T
npdclyuhqf ; real_T b11tooymbq ; real_T ju3eqofxsv ; real_T k401caq3eb ;
real_T ftivrztnav ; real_T cp1s511zvk ; real_T dgk2xu5prp ; real_T fsyjc2e3jn
; real_T pmkgps0zyu ; real_T crs0im5dqp ; real_T idvqtvfoyk ; real_T
djegcg25ae ; real_T ijubt5styh ; real_T fxmmxdki1w ; real_T mykimnyubj ;
real_T b5ekoo4s5v ; real_T ktal25amyn ; real_T e2chijmfh2 ; real_T ajuoykrpve
; real_T orc5wcdxm1 ; real_T akwd4yohpb ; real_T hwgkbedju4 ; real_T
akgbctleuf ; real_T fjva4ba3yf ; real_T ojpp3hq5ld ; real_T ddwaerj1qf ;
real_T e4esbiadth ; real_T dv32o2egzr ; real_T b1fl12txsf ; real_T liwqgy4ofb
; real_T cf3awerlht ; real_T o0lhjiunqy ; real_T i4esmxfcaq ; real_T
ewvuxv0roa ; real_T frtehkabsr ; real_T paaipnyjy4 ; real_T ctjnl3duhv ;
real_T h0hkib4ron ; real_T gxs3xlh0jb ; real_T cuh2ly0avr ; boolean_T
nvvl1et5cw ; } B ; typedef struct { real_T ae4fdc50fw ; real_T ns3jml1yrn ;
real_T bkylhixnvg ; real_T mcqhrorlxr ; real_T hyrzihgqre ; real_T opkdjwnlyz
; real_T nbkcuaxc3y ; real_T blkk50vpkb ; real_T ifljlxnawa ; real_T
df3h3bq4ax ; real_T ew4rinximz ; real_T nb0afwz3qd ; real_T ntr0qnnxwd ;
real_T m01vpi11le ; real_T p53jjbkpzn ; real_T mkxkhcmalu ; real_T jejzfwqaao
; real_T fs5pddw5ow [ 13 ] ; real_T k0okhesaat ; real_T gepbsobs0a ; real_T
fzr1ogugs2 ; real_T i4wxuhmfgf ; real_T hzeqqg0jia ; real_T c4quijr14v ;
real_T f51eegc2bu ; real_T fxt15s43p4 ; real_T g3gghz3gaz ; real_T abf3scvxey
; real_T h1wh3z4evx ; real_T bds32z0txa ; real_T ebacjx4abi ; real_T
cbffa5ojlz ; real_T cfb4bptno0 ; real_T bljv3otj05 ; real_T b4zh5qri0d ;
real_T ic00z2hy2m ; real_T fzp55m5l14 ; real_T bsqle4x1ip ; real_T ehtf41cg10
; real_T p2pkpj1mv5 ; real_T cn5opu2pzs ; real_T fimioqcfmg ; real_T
ksxohwmcoh ; real_T bv3zs25i1r ; real_T nqhcy2vec4 ; real_T p5fqadhn5b ;
real_T ikqkqwjh3n ; real_T awv1q3egsu ; real_T bhhdr2vx1r ; real_T m4yjnvjtaz
; real_T pztkm2b5s5 ; real_T hsvqv45oph ; real_T cg2af1bnv1 ; real_T
jp23k4f2go ; real_T chezipvofm ; real_T lypv2c215x ; real_T dhksroq5rn ;
real_T gyaphxw5hc ; real_T n0cer4zw0t ; real_T knii4eahbq ; real_T e0g3wfol1j
; void * jdobxxns3j [ 65 ] ; struct { void * AQHandles ; } ct5pbogejq ;
struct { void * LoggedData ; } op222kfxbt ; struct { void * LoggedData ; }
lqgtrexdqd ; int_T jpo5gkezdl [ 12 ] ; int8_T jjhzuiuwr5 ; int8_T kalc0i12gy
; uint8_T kt2if2m30y ; } DW ; typedef struct { rtwCAPI_ModelMappingInfo mmi ;
} DataMapInfo ; struct P_ { real_T t [ 12000 ] ; real_T w [ 12000 ] ; real_T
Battery_BatType ; real_T PVMODULE1_I0 ; real_T PVMODULE1_Impp ; real_T
DiscretePIController1_Init ; real_T DiscretePIController2_Init ; real_T
DiscretePIController2_Init_naho2d0zuf ; real_T DiscretePIController3_Init ;
real_T DiscretePIController4_Init ; real_T
DiscretePIController3_Init_lcdytxavmn ; real_T
DiscretePIController4_Init_ojyv5ifd0r ; real_T PVMODULE1_Isc ; real_T
DiscretePIController1_Ki ; real_T DiscretePIController2_Ki ; real_T
DiscretePIController3_Ki ; real_T DiscretePIController4_Ki ; real_T
DiscretePIController3_Ki_catboe4e3q ; real_T
DiscretePIController4_Ki_ksfhmxpwtu ; real_T
DiscretePIController2_Ki_lu2imaebpa ; real_T DiscretePIController2_Kp ;
real_T DiscretePIController1_Kp ; real_T DiscretePIController2_Kp_jtir0rv5nd
; real_T DiscretePIController3_Kp ; real_T DiscretePIController4_Kp ; real_T
DiscretePIController3_Kp_ppecbhclte ; real_T
DiscretePIController4_Kp_crtfhdlpjf ; real_T PVMODULE1_Ncell ; real_T
PVMODULE1_Npar ; real_T PVMODULE1_Nser ; real_T VariableResistor_Rabsmin ;
real_T PVMODULE1_Rs ; real_T PVMODULE1_Rsh ; real_T Battery_SOC ; real_T
PVMODULE1_Vmpp ; real_T PVMODULE1_Voc ; real_T PVMODULE1_beta_Voc ; real_T
CompareToConstant_const ; real_T PVMODULE1_df ; real_T
Subsystem_irradiance_const ; real_T BoostPVfast_n ; real_T BoostFCfast_n ;
real_T BidirectionalBOOSTBUCKBattfast_n_boost ; real_T
BidirectionalBOOSTBUCKBattfast_n_buck ; real_T Saturation_UpperSat ; real_T
Saturation_LowerSat ; real_T OutputSamplePoints_Value [ 2 ] ; real_T
Switch1_Threshold ; real_T Constant_Value ; real_T Constant_Value_lc2t2ikfiz
; real_T Constant_Value_pty4zc05uj ; real_T itinit3_InitialCondition ; real_T
R2_Gain ; real_T Currentfilter5_NumCoef ; real_T Currentfilter5_DenCoef [ 2 ]
; real_T Currentfilter5_InitialStates ; real_T itinit_InitialCondition ;
real_T inti_gainval ; real_T inti_UpperSat ; real_T inti_LowerSat ; real_T
Gain_Gain ; real_T R3_Gain ; real_T DiscreteTimeIntegrator_gainval ; real_T
DiscreteTimeIntegrator_IC ; real_T Memory2_InitialCondition ; real_T
UnitDelay1_InitialCondition ; real_T UnitDelay2_InitialCondition ; real_T
UnitDelay2_InitialCondition_kplvr2c540 ; real_T Delay_InitialCondition ;
real_T Saturation_UpperSat_gvrgxklgqx ; real_T Saturation_LowerSat_cndq0w2uve
; real_T DiscreteTimeIntegrator_gainval_m4ai2wnufy ; real_T
DiscreteTimeIntegrator_IC_bjhalm0xhc ; real_T UnitDelay_InitialCondition ;
real_T Multiply_Gain ; real_T UnitDelay1_InitialCondition_b5qtmccqei ; real_T
DiscreteTimeIntegrator_gainval_lknx5x0oaz ; real_T
DiscreteTimeIntegrator_IC_p2dyd1g5fi ; real_T Saturation_UpperSat_e2k0qdtv2s
; real_T Saturation_LowerSat_d5xrshbz0z ; real_T
UnitDelay2_InitialCondition_mynahauzpq ; real_T UnitDelay3_InitialCondition ;
real_T UnitDelay3_InitialCondition_kgclqpwylc ; real_T
UnitDelay1_InitialCondition_pmpt1ejnb2 ; real_T UnitDelay4_InitialCondition ;
real_T UnitDelay_InitialCondition_ckvjp4gfil ; real_T StateSpace_P1_Size [ 2
] ; real_T StateSpace_P1 ; real_T StateSpace_P2_Size [ 2 ] ; real_T
StateSpace_P2 [ 169 ] ; real_T StateSpace_P3_Size [ 2 ] ; real_T
StateSpace_P3 [ 312 ] ; real_T StateSpace_P4_Size [ 2 ] ; real_T
StateSpace_P4 [ 494 ] ; real_T StateSpace_P5_Size [ 2 ] ; real_T
StateSpace_P5 [ 912 ] ; real_T StateSpace_P6_Size [ 2 ] ; real_T
StateSpace_P6 [ 13 ] ; real_T StateSpace_P7_Size [ 2 ] ; real_T StateSpace_P7
; real_T StateSpace_P8_Size [ 2 ] ; real_T StateSpace_P8 [ 3 ] ; real_T
StateSpace_P9_Size [ 2 ] ; real_T StateSpace_P10_Size [ 2 ] ; real_T
StateSpace_P10 ; real_T StateSpace_P11_Size [ 2 ] ; real_T StateSpace_P11 ;
real_T StateSpace_P12_Size [ 2 ] ; real_T StateSpace_P13_Size [ 2 ] ; real_T
StateSpace_P13 ; real_T StateSpace_P14_Size [ 2 ] ; real_T StateSpace_P14 ;
real_T StateSpace_P15_Size [ 2 ] ; real_T StateSpace_P16_Size [ 2 ] ; real_T
StateSpace_P16 ; real_T StateSpace_P17_Size [ 2 ] ; real_T StateSpace_P17 ;
real_T StateSpace_P18_Size [ 2 ] ; real_T StateSpace_P18 ; real_T
StateSpace_P19_Size [ 2 ] ; real_T StateSpace_P19 ; real_T
StateSpace_P20_Size [ 2 ] ; real_T StateSpace_P20 [ 12 ] ; real_T
StateSpace_P21_Size [ 2 ] ; real_T StateSpace_P21 [ 12 ] ; real_T
StateSpace_P22_Size [ 2 ] ; real_T StateSpace_P22 [ 12 ] ; real_T
StateSpace_P23_Size [ 2 ] ; real_T StateSpace_P23 [ 12 ] ; real_T
StateSpace_P24_Size [ 2 ] ; real_T StateSpace_P24 ; real_T
donotdeletethisgain_Gain ; real_T donotdeletethisgain_Gain_kzwtp4lcwh ;
real_T donotdeletethisgain_Gain_jjlpkzumz0 ; real_T
DiscreteTimeIntegrator_gainval_figs31oe21 ; real_T
DiscreteTimeIntegrator_UpperSat ; real_T DiscreteTimeIntegrator_LowerSat ;
real_T donotdeletethisgain_Gain_pnt2zcpibt ; real_T
DiscreteTimeIntegrator_gainval_jv55x3tqio ; real_T
DiscreteTimeIntegrator_UpperSat_n2g2yvldpg ; real_T
DiscreteTimeIntegrator_LowerSat_fv0zcc4hsa ; real_T Saturation2_UpperSat ;
real_T Saturation2_LowerSat ; real_T donotdeletethisgain_Gain_fbjp1xgx2i ;
real_T Saturation2_UpperSat_a2flzvrl0h ; real_T
Saturation2_LowerSat_imcsw2haey ; real_T
DiscreteTimeIntegrator_gainval_k22hedow4a ; real_T
DiscreteTimeIntegrator_UpperSat_j2u1431tvu ; real_T
DiscreteTimeIntegrator_LowerSat_bvygkv3zts ; real_T Saturation7_UpperSat ;
real_T Saturation7_LowerSat ; real_T donotdeletethisgain_Gain_pc1oacxtz5 ;
real_T Saturation4_UpperSat ; real_T Saturation4_LowerSat ; real_T
Saturation2_UpperSat_csxykusiqi ; real_T Saturation2_LowerSat_djxegxbmlp ;
real_T DiscreteTimeIntegrator_gainval_adna3qjceq ; real_T
DiscreteTimeIntegrator_UpperSat_iu43zm3tho ; real_T
DiscreteTimeIntegrator_LowerSat_bdtob5uhem ; real_T
Saturation2_UpperSat_ldjga0hth1 ; real_T Saturation2_LowerSat_ebdt35gruq ;
real_T DiscreteTimeIntegrator_gainval_djg22thboz ; real_T
DiscreteTimeIntegrator_UpperSat_k2jkcmkhdm ; real_T
DiscreteTimeIntegrator_LowerSat_gmrhfgoeip ; real_T Multiply_Gain_dppzkzoubi
; real_T Saturation6_UpperSat ; real_T Saturation6_LowerSat ; real_T
Saturation2_UpperSat_pjhhcyvloo ; real_T Saturation2_LowerSat_j0yt25ma5v ;
real_T Saturation_UpperSat_jsjpgzsi1y ; real_T Saturation_LowerSat_ebjhnxsenp
; real_T Saturation2_UpperSat_amgcitvjo2 ; real_T
Saturation2_LowerSat_lkim1nsn2b ; real_T Saturation1_UpperSat ; real_T
Saturation1_LowerSat ; real_T Saturation3_UpperSat ; real_T
Saturation3_LowerSat ; real_T donotdeletethisgain_Gain_ghiynr5jt3 ; real_T
donotdeletethisgain_Gain_jhmspkg22p ; real_T
UnitDelay1_InitialCondition_gagfd2xjhh ; real_T
Saturation1_UpperSat_jbsy2jdb2e ; real_T Saturation1_LowerSat_km3pw1r5au ;
real_T donotdeletethisgain_Gain_l30jrki0pa ; real_T
donotdeletethisgain_Gain_m3s0jpprkc ; real_T
donotdeletethisgain_Gain_fiwukkn2yr ; real_T
donotdeletethisgain_Gain_bnrrpg33he ; real_T
DiscreteTimeIntegrator_gainval_cdol2y5vzn ; real_T
DiscreteTimeIntegrator_UpperSat_hfo2y053hj ; real_T
DiscreteTimeIntegrator_LowerSat_c0vq2ip5xz ; real_T
donotdeletethisgain_Gain_liz3gjfhcs ; real_T
donotdeletethisgain_Gain_hbuypofava ; real_T Multiply2_Gain ; real_T
donotdeletethisgain_Gain_ntvbbpumog ; real_T Saturation2_UpperSat_fkd04pf2k1
; real_T Saturation2_LowerSat_mzohmr2g2n ; real_T
DiscreteTimeIntegrator_gainval_cqdxvpityq ; real_T
DiscreteTimeIntegrator_UpperSat_bbsxbmka10 ; real_T
DiscreteTimeIntegrator_LowerSat_fbeqnj3sm1 ; real_T
donotdeletethisgain_Gain_mnd4o03d53 ; real_T Saturation2_UpperSat_aip5hjdd2y
; real_T Saturation2_LowerSat_czr0zyeyrx ; real_T
Saturation2_UpperSat_kim5qyxfwz ; real_T Saturation2_LowerSat_dlfntvjpxg ;
real_T Saturation_UpperSat_e2l0llad23 ; real_T Saturation_LowerSat_daenvoeirh
; real_T Saturation1_UpperSat_ix0yodnig1 ; real_T
Saturation1_LowerSat_nfi0d0pja5 ; real_T donotdeletethisgain_Gain_bvblu5w4wa
; real_T donotdeletethisgain_Gain_nzzshfnxdx ; real_T
DiscreteTimeIntegrator_gainval_fhcrjdv1um ; real_T
DiscreteTimeIntegrator_IC_muc3fdmls2 ; real_T
UnitDelay2_InitialCondition_bdexezlukf ; real_T
UnitDelay_InitialCondition_br0av5wkrv ; real_T
DiscreteTimeIntegrator1_gainval ; real_T DiscreteTimeIntegrator1_IC ; real_T
Gain_Gain_duepg35cnl ; real_T R4_Gain ; real_T Saturation_UpperSat_ms3dxtbvew
; real_T Saturation_LowerSat_p3nlfvz151 ; real_T
donotdeletethisgain_Gain_e2kry42snu ; real_T Memory_InitialCondition ; real_T
Memory17_InitialCondition ; real_T Memory16_InitialCondition ; real_T
Memory15_InitialCondition ; real_T Memory14_InitialCondition ; real_T
Memory13_InitialCondition ; real_T Memory12_InitialCondition ; real_T
Memory11_InitialCondition ; real_T Memory10_InitialCondition ; real_T
Memory9_InitialCondition ; real_T Memory7_InitialCondition ; real_T
Memory6_InitialCondition ; real_T Memory5_InitialCondition ; real_T
Memory4_InitialCondition ; real_T Memory3_InitialCondition ; real_T
Memory2_InitialCondition_nmqdt3zohg ; real_T Memory1_InitialCondition ;
real_T Memory_InitialCondition_fgdsbtcau2 ; real_T
Saturation_UpperSat_ip0sfxxemb ; real_T Saturation_LowerSat_oc4mpky1ii ;
real_T Saturation1_UpperSat_hftla4v5jl ; real_T
Saturation1_LowerSat_mlv0levcl5 ; real_T Saturation2_UpperSat_fd3ezm0unh ;
real_T Saturation2_LowerSat_a0oq1v4uhe ; real_T
Memory3_InitialCondition_npuv0s0rz0 ; real_T Saturation_UpperSat_hsf1hlgzdw ;
real_T Saturation_LowerSat_peon1dscjc ; real_T
Saturation1_UpperSat_joqzp4lauk ; real_T Saturation1_LowerSat_cp5xe3rdvj ;
real_T Saturation2_UpperSat_lknfecgs12 ; real_T
Saturation2_LowerSat_djkw5ghtjz ; real_T Memory2_InitialCondition_otmdfxbv2b
; real_T Memory1_InitialCondition_eyxrd3us35 ; real_T
Memory_InitialCondition_afcza04ewo ; real_T itinit1_InitialCondition ; real_T
Gain4_Gain ; real_T Gain1_Gain ; real_T Gain2_Gain ; real_T R1_Gain ; real_T
donotdeletethisgain_Gain_hoplgufukg ; real_T
donotdeletethisgain_Gain_hqauyrnmgx ; real_T SwitchCurrents_Value [ 12 ] ;
real_T Constant_Value_ffncqspxq4 ; real_T Constant1_Value ; real_T
Constant2_Value ; real_T Constant3_Value ; real_T Constant_Value_jrk1wafdx5 ;
real_T Constant1_Value_avw5uhdxx5 ; real_T Constant5_Value ; real_T
Constant4_Value ; real_T Constant6_Value ; real_T Constant7_Value ; real_T
Constant8_Value ; real_T Multiply3_Gain ; real_T Constant_Value_kfm5xzok4i ;
real_T Constant19_Value ; real_T Constant1_Value_lfvx2nwcp2 ; real_T
Constant2_Value_krq4yfjnno ; real_T Constant3_Value_acddb2uoov ; real_T
Constant4_Value_fthefd0get ; real_T Constant_Value_oibu00r03f ; real_T
Constant1_Value_ktzhc0x1wo ; real_T Constant_Value_nct1bh10mh ; real_T
Constant1_Value_aacpe0p2s4 ; real_T Constant_Value_m3ckpdnl3e ; real_T
Constant1_Value_bcnppbahb4 ; real_T Constant12_Value ; real_T
Constant14_Value ; real_T Constant8_Value_hfo2s31sle ; real_T Constant9_Value
; real_T Constant1_Value_ixcqqm1d4w ; real_T Constant2_Value_m10aoab32w ;
real_T Constant3_Value_nmyyw0epx1 ; real_T Constant4_Value_jmvupybtnc ;
real_T Ta_Value ; real_T Constant5_Value_kbjoyjqk2a ; real_T
Constant5_Value_k3metw3ccu ; real_T Saturation_UpperSat_nd1j1mqyat ; real_T
Saturation_LowerSat_jwye2411i5 ; real_T eee_Value ; } ; extern const real_T
fast_powertrain_RGND ; extern const char * RT_MEMORY_ALLOCATION_ERROR ;
extern B rtB ; extern DW rtDW ; extern P rtP ; extern const
rtwCAPI_ModelMappingStaticInfo * fast_powertrain_GetCAPIStaticMap ( void ) ;
extern SimStruct * const rtS ; extern const int_T gblNumToFiles ; extern
const int_T gblNumFrFiles ; extern const int_T gblNumFrWksBlocks ; extern
rtInportTUtable * gblInportTUtables ; extern const char * gblInportFileName ;
extern const int_T gblNumRootInportBlks ; extern const int_T
gblNumModelInputs ; extern const int_T gblInportDataTypeIdx [ ] ; extern
const int_T gblInportDims [ ] ; extern const int_T gblInportComplex [ ] ;
extern const int_T gblInportInterpoFlag [ ] ; extern const int_T
gblInportContinuous [ ] ; extern const int_T gblParameterTuningTid ; extern
DataMapInfo * rt_dataMapInfoPtr ; extern rtwCAPI_ModelMappingInfo *
rt_modelMapInfoPtr ; void MdlOutputs ( int_T tid ) ; void
MdlOutputsParameterSampleTime ( int_T tid ) ; void MdlUpdate ( int_T tid ) ;
void MdlTerminate ( void ) ; void MdlInitializeSizes ( void ) ; void
MdlInitializeSampleTimes ( void ) ; SimStruct * raccel_register_model (
ssExecutionInfo * executionInfo ) ;
#endif

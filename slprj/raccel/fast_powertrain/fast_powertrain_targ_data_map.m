  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 1;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc paramMap
    ;%
    paramMap.nSections           = nTotSects;
    paramMap.sectIdxOffset       = sectIdxOffset;
      paramMap.sections(nTotSects) = dumSection; %prealloc
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (rtP)
    ;%
      section.nData     = 300;
      section.data(300)  = dumData; %prealloc
      
	  ;% rtP.t
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtP.w
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 12000;
	
	  ;% rtP.Battery_BatType
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 24000;
	
	  ;% rtP.PVMODULE1_I0
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 24001;
	
	  ;% rtP.PVMODULE1_Impp
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 24002;
	
	  ;% rtP.DiscretePIController1_Init
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 24003;
	
	  ;% rtP.DiscretePIController2_Init
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 24004;
	
	  ;% rtP.DiscretePIController2_Init_naho2d0zuf
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 24005;
	
	  ;% rtP.DiscretePIController3_Init
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 24006;
	
	  ;% rtP.DiscretePIController4_Init
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 24007;
	
	  ;% rtP.DiscretePIController3_Init_lcdytxavmn
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 24008;
	
	  ;% rtP.DiscretePIController4_Init_ojyv5ifd0r
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 24009;
	
	  ;% rtP.PVMODULE1_Isc
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 24010;
	
	  ;% rtP.DiscretePIController1_Ki
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 24011;
	
	  ;% rtP.DiscretePIController2_Ki
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 24012;
	
	  ;% rtP.DiscretePIController3_Ki
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 24013;
	
	  ;% rtP.DiscretePIController4_Ki
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 24014;
	
	  ;% rtP.DiscretePIController3_Ki_catboe4e3q
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 24015;
	
	  ;% rtP.DiscretePIController4_Ki_ksfhmxpwtu
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 24016;
	
	  ;% rtP.DiscretePIController2_Ki_lu2imaebpa
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 24017;
	
	  ;% rtP.DiscretePIController2_Kp
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 24018;
	
	  ;% rtP.DiscretePIController1_Kp
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 24019;
	
	  ;% rtP.DiscretePIController2_Kp_jtir0rv5nd
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 24020;
	
	  ;% rtP.DiscretePIController3_Kp
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 24021;
	
	  ;% rtP.DiscretePIController4_Kp
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 24022;
	
	  ;% rtP.DiscretePIController3_Kp_ppecbhclte
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 24023;
	
	  ;% rtP.DiscretePIController4_Kp_crtfhdlpjf
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 24024;
	
	  ;% rtP.PVMODULE1_Ncell
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 24025;
	
	  ;% rtP.PVMODULE1_Npar
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 24026;
	
	  ;% rtP.PVMODULE1_Nser
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 24027;
	
	  ;% rtP.VariableResistor_Rabsmin
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 24028;
	
	  ;% rtP.PVMODULE1_Rs
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 24029;
	
	  ;% rtP.PVMODULE1_Rsh
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 24030;
	
	  ;% rtP.Battery_SOC
	  section.data(34).logicalSrcIdx = 33;
	  section.data(34).dtTransOffset = 24031;
	
	  ;% rtP.PVMODULE1_Vmpp
	  section.data(35).logicalSrcIdx = 34;
	  section.data(35).dtTransOffset = 24032;
	
	  ;% rtP.PVMODULE1_Voc
	  section.data(36).logicalSrcIdx = 35;
	  section.data(36).dtTransOffset = 24033;
	
	  ;% rtP.PVMODULE1_beta_Voc
	  section.data(37).logicalSrcIdx = 36;
	  section.data(37).dtTransOffset = 24034;
	
	  ;% rtP.CompareToConstant_const
	  section.data(38).logicalSrcIdx = 37;
	  section.data(38).dtTransOffset = 24035;
	
	  ;% rtP.PVMODULE1_df
	  section.data(39).logicalSrcIdx = 38;
	  section.data(39).dtTransOffset = 24036;
	
	  ;% rtP.Subsystem_irradiance_const
	  section.data(40).logicalSrcIdx = 39;
	  section.data(40).dtTransOffset = 24037;
	
	  ;% rtP.BoostPVfast_n
	  section.data(41).logicalSrcIdx = 40;
	  section.data(41).dtTransOffset = 24038;
	
	  ;% rtP.BoostFCfast_n
	  section.data(42).logicalSrcIdx = 41;
	  section.data(42).dtTransOffset = 24039;
	
	  ;% rtP.BidirectionalBOOSTBUCKBattfast_n_boost
	  section.data(43).logicalSrcIdx = 42;
	  section.data(43).dtTransOffset = 24040;
	
	  ;% rtP.BidirectionalBOOSTBUCKBattfast_n_buck
	  section.data(44).logicalSrcIdx = 43;
	  section.data(44).dtTransOffset = 24041;
	
	  ;% rtP.Saturation_UpperSat
	  section.data(45).logicalSrcIdx = 44;
	  section.data(45).dtTransOffset = 24042;
	
	  ;% rtP.Saturation_LowerSat
	  section.data(46).logicalSrcIdx = 45;
	  section.data(46).dtTransOffset = 24043;
	
	  ;% rtP.OutputSamplePoints_Value
	  section.data(47).logicalSrcIdx = 46;
	  section.data(47).dtTransOffset = 24044;
	
	  ;% rtP.Switch1_Threshold
	  section.data(48).logicalSrcIdx = 47;
	  section.data(48).dtTransOffset = 24046;
	
	  ;% rtP.Constant_Value
	  section.data(49).logicalSrcIdx = 48;
	  section.data(49).dtTransOffset = 24047;
	
	  ;% rtP.Constant_Value_lc2t2ikfiz
	  section.data(50).logicalSrcIdx = 49;
	  section.data(50).dtTransOffset = 24048;
	
	  ;% rtP.Constant_Value_pty4zc05uj
	  section.data(51).logicalSrcIdx = 50;
	  section.data(51).dtTransOffset = 24049;
	
	  ;% rtP.itinit3_InitialCondition
	  section.data(52).logicalSrcIdx = 51;
	  section.data(52).dtTransOffset = 24050;
	
	  ;% rtP.R2_Gain
	  section.data(53).logicalSrcIdx = 52;
	  section.data(53).dtTransOffset = 24051;
	
	  ;% rtP.Currentfilter5_NumCoef
	  section.data(54).logicalSrcIdx = 53;
	  section.data(54).dtTransOffset = 24052;
	
	  ;% rtP.Currentfilter5_DenCoef
	  section.data(55).logicalSrcIdx = 54;
	  section.data(55).dtTransOffset = 24053;
	
	  ;% rtP.Currentfilter5_InitialStates
	  section.data(56).logicalSrcIdx = 55;
	  section.data(56).dtTransOffset = 24055;
	
	  ;% rtP.itinit_InitialCondition
	  section.data(57).logicalSrcIdx = 56;
	  section.data(57).dtTransOffset = 24056;
	
	  ;% rtP.inti_gainval
	  section.data(58).logicalSrcIdx = 57;
	  section.data(58).dtTransOffset = 24057;
	
	  ;% rtP.inti_UpperSat
	  section.data(59).logicalSrcIdx = 58;
	  section.data(59).dtTransOffset = 24058;
	
	  ;% rtP.inti_LowerSat
	  section.data(60).logicalSrcIdx = 59;
	  section.data(60).dtTransOffset = 24059;
	
	  ;% rtP.Gain_Gain
	  section.data(61).logicalSrcIdx = 60;
	  section.data(61).dtTransOffset = 24060;
	
	  ;% rtP.R3_Gain
	  section.data(62).logicalSrcIdx = 61;
	  section.data(62).dtTransOffset = 24061;
	
	  ;% rtP.DiscreteTimeIntegrator_gainval
	  section.data(63).logicalSrcIdx = 62;
	  section.data(63).dtTransOffset = 24062;
	
	  ;% rtP.DiscreteTimeIntegrator_IC
	  section.data(64).logicalSrcIdx = 63;
	  section.data(64).dtTransOffset = 24063;
	
	  ;% rtP.Memory2_InitialCondition
	  section.data(65).logicalSrcIdx = 64;
	  section.data(65).dtTransOffset = 24064;
	
	  ;% rtP.UnitDelay1_InitialCondition
	  section.data(66).logicalSrcIdx = 65;
	  section.data(66).dtTransOffset = 24065;
	
	  ;% rtP.UnitDelay2_InitialCondition
	  section.data(67).logicalSrcIdx = 66;
	  section.data(67).dtTransOffset = 24066;
	
	  ;% rtP.UnitDelay2_InitialCondition_kplvr2c540
	  section.data(68).logicalSrcIdx = 67;
	  section.data(68).dtTransOffset = 24067;
	
	  ;% rtP.Delay_InitialCondition
	  section.data(69).logicalSrcIdx = 68;
	  section.data(69).dtTransOffset = 24068;
	
	  ;% rtP.Saturation_UpperSat_gvrgxklgqx
	  section.data(70).logicalSrcIdx = 69;
	  section.data(70).dtTransOffset = 24069;
	
	  ;% rtP.Saturation_LowerSat_cndq0w2uve
	  section.data(71).logicalSrcIdx = 70;
	  section.data(71).dtTransOffset = 24070;
	
	  ;% rtP.DiscreteTimeIntegrator_gainval_m4ai2wnufy
	  section.data(72).logicalSrcIdx = 71;
	  section.data(72).dtTransOffset = 24071;
	
	  ;% rtP.DiscreteTimeIntegrator_IC_bjhalm0xhc
	  section.data(73).logicalSrcIdx = 72;
	  section.data(73).dtTransOffset = 24072;
	
	  ;% rtP.UnitDelay_InitialCondition
	  section.data(74).logicalSrcIdx = 73;
	  section.data(74).dtTransOffset = 24073;
	
	  ;% rtP.Multiply_Gain
	  section.data(75).logicalSrcIdx = 74;
	  section.data(75).dtTransOffset = 24074;
	
	  ;% rtP.UnitDelay1_InitialCondition_b5qtmccqei
	  section.data(76).logicalSrcIdx = 75;
	  section.data(76).dtTransOffset = 24075;
	
	  ;% rtP.DiscreteTimeIntegrator_gainval_lknx5x0oaz
	  section.data(77).logicalSrcIdx = 76;
	  section.data(77).dtTransOffset = 24076;
	
	  ;% rtP.DiscreteTimeIntegrator_IC_p2dyd1g5fi
	  section.data(78).logicalSrcIdx = 77;
	  section.data(78).dtTransOffset = 24077;
	
	  ;% rtP.Saturation_UpperSat_e2k0qdtv2s
	  section.data(79).logicalSrcIdx = 78;
	  section.data(79).dtTransOffset = 24078;
	
	  ;% rtP.Saturation_LowerSat_d5xrshbz0z
	  section.data(80).logicalSrcIdx = 79;
	  section.data(80).dtTransOffset = 24079;
	
	  ;% rtP.UnitDelay2_InitialCondition_mynahauzpq
	  section.data(81).logicalSrcIdx = 80;
	  section.data(81).dtTransOffset = 24080;
	
	  ;% rtP.UnitDelay3_InitialCondition
	  section.data(82).logicalSrcIdx = 81;
	  section.data(82).dtTransOffset = 24081;
	
	  ;% rtP.UnitDelay3_InitialCondition_kgclqpwylc
	  section.data(83).logicalSrcIdx = 82;
	  section.data(83).dtTransOffset = 24082;
	
	  ;% rtP.UnitDelay1_InitialCondition_pmpt1ejnb2
	  section.data(84).logicalSrcIdx = 83;
	  section.data(84).dtTransOffset = 24083;
	
	  ;% rtP.UnitDelay4_InitialCondition
	  section.data(85).logicalSrcIdx = 84;
	  section.data(85).dtTransOffset = 24084;
	
	  ;% rtP.UnitDelay_InitialCondition_ckvjp4gfil
	  section.data(86).logicalSrcIdx = 85;
	  section.data(86).dtTransOffset = 24085;
	
	  ;% rtP.StateSpace_P1_Size
	  section.data(87).logicalSrcIdx = 86;
	  section.data(87).dtTransOffset = 24086;
	
	  ;% rtP.StateSpace_P1
	  section.data(88).logicalSrcIdx = 87;
	  section.data(88).dtTransOffset = 24088;
	
	  ;% rtP.StateSpace_P2_Size
	  section.data(89).logicalSrcIdx = 88;
	  section.data(89).dtTransOffset = 24089;
	
	  ;% rtP.StateSpace_P2
	  section.data(90).logicalSrcIdx = 89;
	  section.data(90).dtTransOffset = 24091;
	
	  ;% rtP.StateSpace_P3_Size
	  section.data(91).logicalSrcIdx = 90;
	  section.data(91).dtTransOffset = 24260;
	
	  ;% rtP.StateSpace_P3
	  section.data(92).logicalSrcIdx = 91;
	  section.data(92).dtTransOffset = 24262;
	
	  ;% rtP.StateSpace_P4_Size
	  section.data(93).logicalSrcIdx = 92;
	  section.data(93).dtTransOffset = 24574;
	
	  ;% rtP.StateSpace_P4
	  section.data(94).logicalSrcIdx = 93;
	  section.data(94).dtTransOffset = 24576;
	
	  ;% rtP.StateSpace_P5_Size
	  section.data(95).logicalSrcIdx = 94;
	  section.data(95).dtTransOffset = 25070;
	
	  ;% rtP.StateSpace_P5
	  section.data(96).logicalSrcIdx = 95;
	  section.data(96).dtTransOffset = 25072;
	
	  ;% rtP.StateSpace_P6_Size
	  section.data(97).logicalSrcIdx = 96;
	  section.data(97).dtTransOffset = 25984;
	
	  ;% rtP.StateSpace_P6
	  section.data(98).logicalSrcIdx = 97;
	  section.data(98).dtTransOffset = 25986;
	
	  ;% rtP.StateSpace_P7_Size
	  section.data(99).logicalSrcIdx = 98;
	  section.data(99).dtTransOffset = 25999;
	
	  ;% rtP.StateSpace_P7
	  section.data(100).logicalSrcIdx = 99;
	  section.data(100).dtTransOffset = 26001;
	
	  ;% rtP.StateSpace_P8_Size
	  section.data(101).logicalSrcIdx = 100;
	  section.data(101).dtTransOffset = 26002;
	
	  ;% rtP.StateSpace_P8
	  section.data(102).logicalSrcIdx = 101;
	  section.data(102).dtTransOffset = 26004;
	
	  ;% rtP.StateSpace_P9_Size
	  section.data(103).logicalSrcIdx = 102;
	  section.data(103).dtTransOffset = 26007;
	
	  ;% rtP.StateSpace_P10_Size
	  section.data(104).logicalSrcIdx = 104;
	  section.data(104).dtTransOffset = 26009;
	
	  ;% rtP.StateSpace_P10
	  section.data(105).logicalSrcIdx = 105;
	  section.data(105).dtTransOffset = 26011;
	
	  ;% rtP.StateSpace_P11_Size
	  section.data(106).logicalSrcIdx = 106;
	  section.data(106).dtTransOffset = 26012;
	
	  ;% rtP.StateSpace_P11
	  section.data(107).logicalSrcIdx = 107;
	  section.data(107).dtTransOffset = 26014;
	
	  ;% rtP.StateSpace_P12_Size
	  section.data(108).logicalSrcIdx = 108;
	  section.data(108).dtTransOffset = 26015;
	
	  ;% rtP.StateSpace_P13_Size
	  section.data(109).logicalSrcIdx = 110;
	  section.data(109).dtTransOffset = 26017;
	
	  ;% rtP.StateSpace_P13
	  section.data(110).logicalSrcIdx = 111;
	  section.data(110).dtTransOffset = 26019;
	
	  ;% rtP.StateSpace_P14_Size
	  section.data(111).logicalSrcIdx = 112;
	  section.data(111).dtTransOffset = 26020;
	
	  ;% rtP.StateSpace_P14
	  section.data(112).logicalSrcIdx = 113;
	  section.data(112).dtTransOffset = 26022;
	
	  ;% rtP.StateSpace_P15_Size
	  section.data(113).logicalSrcIdx = 114;
	  section.data(113).dtTransOffset = 26023;
	
	  ;% rtP.StateSpace_P16_Size
	  section.data(114).logicalSrcIdx = 116;
	  section.data(114).dtTransOffset = 26025;
	
	  ;% rtP.StateSpace_P16
	  section.data(115).logicalSrcIdx = 117;
	  section.data(115).dtTransOffset = 26027;
	
	  ;% rtP.StateSpace_P17_Size
	  section.data(116).logicalSrcIdx = 118;
	  section.data(116).dtTransOffset = 26028;
	
	  ;% rtP.StateSpace_P17
	  section.data(117).logicalSrcIdx = 119;
	  section.data(117).dtTransOffset = 26030;
	
	  ;% rtP.StateSpace_P18_Size
	  section.data(118).logicalSrcIdx = 120;
	  section.data(118).dtTransOffset = 26031;
	
	  ;% rtP.StateSpace_P18
	  section.data(119).logicalSrcIdx = 121;
	  section.data(119).dtTransOffset = 26033;
	
	  ;% rtP.StateSpace_P19_Size
	  section.data(120).logicalSrcIdx = 122;
	  section.data(120).dtTransOffset = 26034;
	
	  ;% rtP.StateSpace_P19
	  section.data(121).logicalSrcIdx = 123;
	  section.data(121).dtTransOffset = 26036;
	
	  ;% rtP.StateSpace_P20_Size
	  section.data(122).logicalSrcIdx = 124;
	  section.data(122).dtTransOffset = 26037;
	
	  ;% rtP.StateSpace_P20
	  section.data(123).logicalSrcIdx = 125;
	  section.data(123).dtTransOffset = 26039;
	
	  ;% rtP.StateSpace_P21_Size
	  section.data(124).logicalSrcIdx = 126;
	  section.data(124).dtTransOffset = 26051;
	
	  ;% rtP.StateSpace_P21
	  section.data(125).logicalSrcIdx = 127;
	  section.data(125).dtTransOffset = 26053;
	
	  ;% rtP.StateSpace_P22_Size
	  section.data(126).logicalSrcIdx = 128;
	  section.data(126).dtTransOffset = 26065;
	
	  ;% rtP.StateSpace_P22
	  section.data(127).logicalSrcIdx = 129;
	  section.data(127).dtTransOffset = 26067;
	
	  ;% rtP.StateSpace_P23_Size
	  section.data(128).logicalSrcIdx = 130;
	  section.data(128).dtTransOffset = 26079;
	
	  ;% rtP.StateSpace_P23
	  section.data(129).logicalSrcIdx = 131;
	  section.data(129).dtTransOffset = 26081;
	
	  ;% rtP.StateSpace_P24_Size
	  section.data(130).logicalSrcIdx = 132;
	  section.data(130).dtTransOffset = 26093;
	
	  ;% rtP.StateSpace_P24
	  section.data(131).logicalSrcIdx = 133;
	  section.data(131).dtTransOffset = 26095;
	
	  ;% rtP.donotdeletethisgain_Gain
	  section.data(132).logicalSrcIdx = 134;
	  section.data(132).dtTransOffset = 26096;
	
	  ;% rtP.donotdeletethisgain_Gain_kzwtp4lcwh
	  section.data(133).logicalSrcIdx = 135;
	  section.data(133).dtTransOffset = 26097;
	
	  ;% rtP.donotdeletethisgain_Gain_jjlpkzumz0
	  section.data(134).logicalSrcIdx = 136;
	  section.data(134).dtTransOffset = 26098;
	
	  ;% rtP.DiscreteTimeIntegrator_gainval_figs31oe21
	  section.data(135).logicalSrcIdx = 137;
	  section.data(135).dtTransOffset = 26099;
	
	  ;% rtP.DiscreteTimeIntegrator_UpperSat
	  section.data(136).logicalSrcIdx = 138;
	  section.data(136).dtTransOffset = 26100;
	
	  ;% rtP.DiscreteTimeIntegrator_LowerSat
	  section.data(137).logicalSrcIdx = 139;
	  section.data(137).dtTransOffset = 26101;
	
	  ;% rtP.donotdeletethisgain_Gain_pnt2zcpibt
	  section.data(138).logicalSrcIdx = 140;
	  section.data(138).dtTransOffset = 26102;
	
	  ;% rtP.DiscreteTimeIntegrator_gainval_jv55x3tqio
	  section.data(139).logicalSrcIdx = 141;
	  section.data(139).dtTransOffset = 26103;
	
	  ;% rtP.DiscreteTimeIntegrator_UpperSat_n2g2yvldpg
	  section.data(140).logicalSrcIdx = 142;
	  section.data(140).dtTransOffset = 26104;
	
	  ;% rtP.DiscreteTimeIntegrator_LowerSat_fv0zcc4hsa
	  section.data(141).logicalSrcIdx = 143;
	  section.data(141).dtTransOffset = 26105;
	
	  ;% rtP.Saturation2_UpperSat
	  section.data(142).logicalSrcIdx = 144;
	  section.data(142).dtTransOffset = 26106;
	
	  ;% rtP.Saturation2_LowerSat
	  section.data(143).logicalSrcIdx = 145;
	  section.data(143).dtTransOffset = 26107;
	
	  ;% rtP.donotdeletethisgain_Gain_fbjp1xgx2i
	  section.data(144).logicalSrcIdx = 146;
	  section.data(144).dtTransOffset = 26108;
	
	  ;% rtP.Saturation2_UpperSat_a2flzvrl0h
	  section.data(145).logicalSrcIdx = 147;
	  section.data(145).dtTransOffset = 26109;
	
	  ;% rtP.Saturation2_LowerSat_imcsw2haey
	  section.data(146).logicalSrcIdx = 148;
	  section.data(146).dtTransOffset = 26110;
	
	  ;% rtP.DiscreteTimeIntegrator_gainval_k22hedow4a
	  section.data(147).logicalSrcIdx = 149;
	  section.data(147).dtTransOffset = 26111;
	
	  ;% rtP.DiscreteTimeIntegrator_UpperSat_j2u1431tvu
	  section.data(148).logicalSrcIdx = 150;
	  section.data(148).dtTransOffset = 26112;
	
	  ;% rtP.DiscreteTimeIntegrator_LowerSat_bvygkv3zts
	  section.data(149).logicalSrcIdx = 151;
	  section.data(149).dtTransOffset = 26113;
	
	  ;% rtP.Saturation7_UpperSat
	  section.data(150).logicalSrcIdx = 152;
	  section.data(150).dtTransOffset = 26114;
	
	  ;% rtP.Saturation7_LowerSat
	  section.data(151).logicalSrcIdx = 153;
	  section.data(151).dtTransOffset = 26115;
	
	  ;% rtP.donotdeletethisgain_Gain_pc1oacxtz5
	  section.data(152).logicalSrcIdx = 154;
	  section.data(152).dtTransOffset = 26116;
	
	  ;% rtP.Saturation4_UpperSat
	  section.data(153).logicalSrcIdx = 155;
	  section.data(153).dtTransOffset = 26117;
	
	  ;% rtP.Saturation4_LowerSat
	  section.data(154).logicalSrcIdx = 156;
	  section.data(154).dtTransOffset = 26118;
	
	  ;% rtP.Saturation2_UpperSat_csxykusiqi
	  section.data(155).logicalSrcIdx = 157;
	  section.data(155).dtTransOffset = 26119;
	
	  ;% rtP.Saturation2_LowerSat_djxegxbmlp
	  section.data(156).logicalSrcIdx = 158;
	  section.data(156).dtTransOffset = 26120;
	
	  ;% rtP.DiscreteTimeIntegrator_gainval_adna3qjceq
	  section.data(157).logicalSrcIdx = 159;
	  section.data(157).dtTransOffset = 26121;
	
	  ;% rtP.DiscreteTimeIntegrator_UpperSat_iu43zm3tho
	  section.data(158).logicalSrcIdx = 160;
	  section.data(158).dtTransOffset = 26122;
	
	  ;% rtP.DiscreteTimeIntegrator_LowerSat_bdtob5uhem
	  section.data(159).logicalSrcIdx = 161;
	  section.data(159).dtTransOffset = 26123;
	
	  ;% rtP.Saturation2_UpperSat_ldjga0hth1
	  section.data(160).logicalSrcIdx = 162;
	  section.data(160).dtTransOffset = 26124;
	
	  ;% rtP.Saturation2_LowerSat_ebdt35gruq
	  section.data(161).logicalSrcIdx = 163;
	  section.data(161).dtTransOffset = 26125;
	
	  ;% rtP.DiscreteTimeIntegrator_gainval_djg22thboz
	  section.data(162).logicalSrcIdx = 164;
	  section.data(162).dtTransOffset = 26126;
	
	  ;% rtP.DiscreteTimeIntegrator_UpperSat_k2jkcmkhdm
	  section.data(163).logicalSrcIdx = 165;
	  section.data(163).dtTransOffset = 26127;
	
	  ;% rtP.DiscreteTimeIntegrator_LowerSat_gmrhfgoeip
	  section.data(164).logicalSrcIdx = 166;
	  section.data(164).dtTransOffset = 26128;
	
	  ;% rtP.Multiply_Gain_dppzkzoubi
	  section.data(165).logicalSrcIdx = 167;
	  section.data(165).dtTransOffset = 26129;
	
	  ;% rtP.Saturation6_UpperSat
	  section.data(166).logicalSrcIdx = 168;
	  section.data(166).dtTransOffset = 26130;
	
	  ;% rtP.Saturation6_LowerSat
	  section.data(167).logicalSrcIdx = 169;
	  section.data(167).dtTransOffset = 26131;
	
	  ;% rtP.Saturation2_UpperSat_pjhhcyvloo
	  section.data(168).logicalSrcIdx = 170;
	  section.data(168).dtTransOffset = 26132;
	
	  ;% rtP.Saturation2_LowerSat_j0yt25ma5v
	  section.data(169).logicalSrcIdx = 171;
	  section.data(169).dtTransOffset = 26133;
	
	  ;% rtP.Saturation_UpperSat_jsjpgzsi1y
	  section.data(170).logicalSrcIdx = 172;
	  section.data(170).dtTransOffset = 26134;
	
	  ;% rtP.Saturation_LowerSat_ebjhnxsenp
	  section.data(171).logicalSrcIdx = 173;
	  section.data(171).dtTransOffset = 26135;
	
	  ;% rtP.Saturation2_UpperSat_amgcitvjo2
	  section.data(172).logicalSrcIdx = 174;
	  section.data(172).dtTransOffset = 26136;
	
	  ;% rtP.Saturation2_LowerSat_lkim1nsn2b
	  section.data(173).logicalSrcIdx = 175;
	  section.data(173).dtTransOffset = 26137;
	
	  ;% rtP.Saturation1_UpperSat
	  section.data(174).logicalSrcIdx = 176;
	  section.data(174).dtTransOffset = 26138;
	
	  ;% rtP.Saturation1_LowerSat
	  section.data(175).logicalSrcIdx = 177;
	  section.data(175).dtTransOffset = 26139;
	
	  ;% rtP.Saturation3_UpperSat
	  section.data(176).logicalSrcIdx = 178;
	  section.data(176).dtTransOffset = 26140;
	
	  ;% rtP.Saturation3_LowerSat
	  section.data(177).logicalSrcIdx = 179;
	  section.data(177).dtTransOffset = 26141;
	
	  ;% rtP.donotdeletethisgain_Gain_ghiynr5jt3
	  section.data(178).logicalSrcIdx = 180;
	  section.data(178).dtTransOffset = 26142;
	
	  ;% rtP.donotdeletethisgain_Gain_jhmspkg22p
	  section.data(179).logicalSrcIdx = 181;
	  section.data(179).dtTransOffset = 26143;
	
	  ;% rtP.UnitDelay1_InitialCondition_gagfd2xjhh
	  section.data(180).logicalSrcIdx = 182;
	  section.data(180).dtTransOffset = 26144;
	
	  ;% rtP.Saturation1_UpperSat_jbsy2jdb2e
	  section.data(181).logicalSrcIdx = 183;
	  section.data(181).dtTransOffset = 26145;
	
	  ;% rtP.Saturation1_LowerSat_km3pw1r5au
	  section.data(182).logicalSrcIdx = 184;
	  section.data(182).dtTransOffset = 26146;
	
	  ;% rtP.donotdeletethisgain_Gain_l30jrki0pa
	  section.data(183).logicalSrcIdx = 185;
	  section.data(183).dtTransOffset = 26147;
	
	  ;% rtP.donotdeletethisgain_Gain_m3s0jpprkc
	  section.data(184).logicalSrcIdx = 186;
	  section.data(184).dtTransOffset = 26148;
	
	  ;% rtP.donotdeletethisgain_Gain_fiwukkn2yr
	  section.data(185).logicalSrcIdx = 187;
	  section.data(185).dtTransOffset = 26149;
	
	  ;% rtP.donotdeletethisgain_Gain_bnrrpg33he
	  section.data(186).logicalSrcIdx = 188;
	  section.data(186).dtTransOffset = 26150;
	
	  ;% rtP.DiscreteTimeIntegrator_gainval_cdol2y5vzn
	  section.data(187).logicalSrcIdx = 189;
	  section.data(187).dtTransOffset = 26151;
	
	  ;% rtP.DiscreteTimeIntegrator_UpperSat_hfo2y053hj
	  section.data(188).logicalSrcIdx = 190;
	  section.data(188).dtTransOffset = 26152;
	
	  ;% rtP.DiscreteTimeIntegrator_LowerSat_c0vq2ip5xz
	  section.data(189).logicalSrcIdx = 191;
	  section.data(189).dtTransOffset = 26153;
	
	  ;% rtP.donotdeletethisgain_Gain_liz3gjfhcs
	  section.data(190).logicalSrcIdx = 192;
	  section.data(190).dtTransOffset = 26154;
	
	  ;% rtP.donotdeletethisgain_Gain_hbuypofava
	  section.data(191).logicalSrcIdx = 193;
	  section.data(191).dtTransOffset = 26155;
	
	  ;% rtP.Multiply2_Gain
	  section.data(192).logicalSrcIdx = 194;
	  section.data(192).dtTransOffset = 26156;
	
	  ;% rtP.donotdeletethisgain_Gain_ntvbbpumog
	  section.data(193).logicalSrcIdx = 195;
	  section.data(193).dtTransOffset = 26157;
	
	  ;% rtP.Saturation2_UpperSat_fkd04pf2k1
	  section.data(194).logicalSrcIdx = 196;
	  section.data(194).dtTransOffset = 26158;
	
	  ;% rtP.Saturation2_LowerSat_mzohmr2g2n
	  section.data(195).logicalSrcIdx = 197;
	  section.data(195).dtTransOffset = 26159;
	
	  ;% rtP.DiscreteTimeIntegrator_gainval_cqdxvpityq
	  section.data(196).logicalSrcIdx = 198;
	  section.data(196).dtTransOffset = 26160;
	
	  ;% rtP.DiscreteTimeIntegrator_UpperSat_bbsxbmka10
	  section.data(197).logicalSrcIdx = 199;
	  section.data(197).dtTransOffset = 26161;
	
	  ;% rtP.DiscreteTimeIntegrator_LowerSat_fbeqnj3sm1
	  section.data(198).logicalSrcIdx = 200;
	  section.data(198).dtTransOffset = 26162;
	
	  ;% rtP.donotdeletethisgain_Gain_mnd4o03d53
	  section.data(199).logicalSrcIdx = 201;
	  section.data(199).dtTransOffset = 26163;
	
	  ;% rtP.Saturation2_UpperSat_aip5hjdd2y
	  section.data(200).logicalSrcIdx = 202;
	  section.data(200).dtTransOffset = 26164;
	
	  ;% rtP.Saturation2_LowerSat_czr0zyeyrx
	  section.data(201).logicalSrcIdx = 203;
	  section.data(201).dtTransOffset = 26165;
	
	  ;% rtP.Saturation2_UpperSat_kim5qyxfwz
	  section.data(202).logicalSrcIdx = 204;
	  section.data(202).dtTransOffset = 26166;
	
	  ;% rtP.Saturation2_LowerSat_dlfntvjpxg
	  section.data(203).logicalSrcIdx = 205;
	  section.data(203).dtTransOffset = 26167;
	
	  ;% rtP.Saturation_UpperSat_e2l0llad23
	  section.data(204).logicalSrcIdx = 206;
	  section.data(204).dtTransOffset = 26168;
	
	  ;% rtP.Saturation_LowerSat_daenvoeirh
	  section.data(205).logicalSrcIdx = 207;
	  section.data(205).dtTransOffset = 26169;
	
	  ;% rtP.Saturation1_UpperSat_ix0yodnig1
	  section.data(206).logicalSrcIdx = 208;
	  section.data(206).dtTransOffset = 26170;
	
	  ;% rtP.Saturation1_LowerSat_nfi0d0pja5
	  section.data(207).logicalSrcIdx = 209;
	  section.data(207).dtTransOffset = 26171;
	
	  ;% rtP.donotdeletethisgain_Gain_bvblu5w4wa
	  section.data(208).logicalSrcIdx = 210;
	  section.data(208).dtTransOffset = 26172;
	
	  ;% rtP.donotdeletethisgain_Gain_nzzshfnxdx
	  section.data(209).logicalSrcIdx = 211;
	  section.data(209).dtTransOffset = 26173;
	
	  ;% rtP.DiscreteTimeIntegrator_gainval_fhcrjdv1um
	  section.data(210).logicalSrcIdx = 212;
	  section.data(210).dtTransOffset = 26174;
	
	  ;% rtP.DiscreteTimeIntegrator_IC_muc3fdmls2
	  section.data(211).logicalSrcIdx = 213;
	  section.data(211).dtTransOffset = 26175;
	
	  ;% rtP.UnitDelay2_InitialCondition_bdexezlukf
	  section.data(212).logicalSrcIdx = 214;
	  section.data(212).dtTransOffset = 26176;
	
	  ;% rtP.UnitDelay_InitialCondition_br0av5wkrv
	  section.data(213).logicalSrcIdx = 215;
	  section.data(213).dtTransOffset = 26177;
	
	  ;% rtP.DiscreteTimeIntegrator1_gainval
	  section.data(214).logicalSrcIdx = 216;
	  section.data(214).dtTransOffset = 26178;
	
	  ;% rtP.DiscreteTimeIntegrator1_IC
	  section.data(215).logicalSrcIdx = 217;
	  section.data(215).dtTransOffset = 26179;
	
	  ;% rtP.Gain_Gain_duepg35cnl
	  section.data(216).logicalSrcIdx = 218;
	  section.data(216).dtTransOffset = 26180;
	
	  ;% rtP.R4_Gain
	  section.data(217).logicalSrcIdx = 219;
	  section.data(217).dtTransOffset = 26181;
	
	  ;% rtP.Saturation_UpperSat_ms3dxtbvew
	  section.data(218).logicalSrcIdx = 220;
	  section.data(218).dtTransOffset = 26182;
	
	  ;% rtP.Saturation_LowerSat_p3nlfvz151
	  section.data(219).logicalSrcIdx = 221;
	  section.data(219).dtTransOffset = 26183;
	
	  ;% rtP.donotdeletethisgain_Gain_e2kry42snu
	  section.data(220).logicalSrcIdx = 222;
	  section.data(220).dtTransOffset = 26184;
	
	  ;% rtP.Memory_InitialCondition
	  section.data(221).logicalSrcIdx = 223;
	  section.data(221).dtTransOffset = 26185;
	
	  ;% rtP.Memory17_InitialCondition
	  section.data(222).logicalSrcIdx = 224;
	  section.data(222).dtTransOffset = 26186;
	
	  ;% rtP.Memory16_InitialCondition
	  section.data(223).logicalSrcIdx = 225;
	  section.data(223).dtTransOffset = 26187;
	
	  ;% rtP.Memory15_InitialCondition
	  section.data(224).logicalSrcIdx = 226;
	  section.data(224).dtTransOffset = 26188;
	
	  ;% rtP.Memory14_InitialCondition
	  section.data(225).logicalSrcIdx = 227;
	  section.data(225).dtTransOffset = 26189;
	
	  ;% rtP.Memory13_InitialCondition
	  section.data(226).logicalSrcIdx = 228;
	  section.data(226).dtTransOffset = 26190;
	
	  ;% rtP.Memory12_InitialCondition
	  section.data(227).logicalSrcIdx = 229;
	  section.data(227).dtTransOffset = 26191;
	
	  ;% rtP.Memory11_InitialCondition
	  section.data(228).logicalSrcIdx = 230;
	  section.data(228).dtTransOffset = 26192;
	
	  ;% rtP.Memory10_InitialCondition
	  section.data(229).logicalSrcIdx = 231;
	  section.data(229).dtTransOffset = 26193;
	
	  ;% rtP.Memory9_InitialCondition
	  section.data(230).logicalSrcIdx = 232;
	  section.data(230).dtTransOffset = 26194;
	
	  ;% rtP.Memory7_InitialCondition
	  section.data(231).logicalSrcIdx = 233;
	  section.data(231).dtTransOffset = 26195;
	
	  ;% rtP.Memory6_InitialCondition
	  section.data(232).logicalSrcIdx = 234;
	  section.data(232).dtTransOffset = 26196;
	
	  ;% rtP.Memory5_InitialCondition
	  section.data(233).logicalSrcIdx = 235;
	  section.data(233).dtTransOffset = 26197;
	
	  ;% rtP.Memory4_InitialCondition
	  section.data(234).logicalSrcIdx = 236;
	  section.data(234).dtTransOffset = 26198;
	
	  ;% rtP.Memory3_InitialCondition
	  section.data(235).logicalSrcIdx = 237;
	  section.data(235).dtTransOffset = 26199;
	
	  ;% rtP.Memory2_InitialCondition_nmqdt3zohg
	  section.data(236).logicalSrcIdx = 238;
	  section.data(236).dtTransOffset = 26200;
	
	  ;% rtP.Memory1_InitialCondition
	  section.data(237).logicalSrcIdx = 239;
	  section.data(237).dtTransOffset = 26201;
	
	  ;% rtP.Memory_InitialCondition_fgdsbtcau2
	  section.data(238).logicalSrcIdx = 240;
	  section.data(238).dtTransOffset = 26202;
	
	  ;% rtP.Saturation_UpperSat_ip0sfxxemb
	  section.data(239).logicalSrcIdx = 241;
	  section.data(239).dtTransOffset = 26203;
	
	  ;% rtP.Saturation_LowerSat_oc4mpky1ii
	  section.data(240).logicalSrcIdx = 242;
	  section.data(240).dtTransOffset = 26204;
	
	  ;% rtP.Saturation1_UpperSat_hftla4v5jl
	  section.data(241).logicalSrcIdx = 243;
	  section.data(241).dtTransOffset = 26205;
	
	  ;% rtP.Saturation1_LowerSat_mlv0levcl5
	  section.data(242).logicalSrcIdx = 244;
	  section.data(242).dtTransOffset = 26206;
	
	  ;% rtP.Saturation2_UpperSat_fd3ezm0unh
	  section.data(243).logicalSrcIdx = 245;
	  section.data(243).dtTransOffset = 26207;
	
	  ;% rtP.Saturation2_LowerSat_a0oq1v4uhe
	  section.data(244).logicalSrcIdx = 246;
	  section.data(244).dtTransOffset = 26208;
	
	  ;% rtP.Memory3_InitialCondition_npuv0s0rz0
	  section.data(245).logicalSrcIdx = 247;
	  section.data(245).dtTransOffset = 26209;
	
	  ;% rtP.Saturation_UpperSat_hsf1hlgzdw
	  section.data(246).logicalSrcIdx = 248;
	  section.data(246).dtTransOffset = 26210;
	
	  ;% rtP.Saturation_LowerSat_peon1dscjc
	  section.data(247).logicalSrcIdx = 249;
	  section.data(247).dtTransOffset = 26211;
	
	  ;% rtP.Saturation1_UpperSat_joqzp4lauk
	  section.data(248).logicalSrcIdx = 250;
	  section.data(248).dtTransOffset = 26212;
	
	  ;% rtP.Saturation1_LowerSat_cp5xe3rdvj
	  section.data(249).logicalSrcIdx = 251;
	  section.data(249).dtTransOffset = 26213;
	
	  ;% rtP.Saturation2_UpperSat_lknfecgs12
	  section.data(250).logicalSrcIdx = 252;
	  section.data(250).dtTransOffset = 26214;
	
	  ;% rtP.Saturation2_LowerSat_djkw5ghtjz
	  section.data(251).logicalSrcIdx = 253;
	  section.data(251).dtTransOffset = 26215;
	
	  ;% rtP.Memory2_InitialCondition_otmdfxbv2b
	  section.data(252).logicalSrcIdx = 254;
	  section.data(252).dtTransOffset = 26216;
	
	  ;% rtP.Memory1_InitialCondition_eyxrd3us35
	  section.data(253).logicalSrcIdx = 255;
	  section.data(253).dtTransOffset = 26217;
	
	  ;% rtP.Memory_InitialCondition_afcza04ewo
	  section.data(254).logicalSrcIdx = 256;
	  section.data(254).dtTransOffset = 26218;
	
	  ;% rtP.itinit1_InitialCondition
	  section.data(255).logicalSrcIdx = 257;
	  section.data(255).dtTransOffset = 26219;
	
	  ;% rtP.Gain4_Gain
	  section.data(256).logicalSrcIdx = 258;
	  section.data(256).dtTransOffset = 26220;
	
	  ;% rtP.Gain1_Gain
	  section.data(257).logicalSrcIdx = 259;
	  section.data(257).dtTransOffset = 26221;
	
	  ;% rtP.Gain2_Gain
	  section.data(258).logicalSrcIdx = 260;
	  section.data(258).dtTransOffset = 26222;
	
	  ;% rtP.R1_Gain
	  section.data(259).logicalSrcIdx = 261;
	  section.data(259).dtTransOffset = 26223;
	
	  ;% rtP.donotdeletethisgain_Gain_hoplgufukg
	  section.data(260).logicalSrcIdx = 262;
	  section.data(260).dtTransOffset = 26224;
	
	  ;% rtP.donotdeletethisgain_Gain_hqauyrnmgx
	  section.data(261).logicalSrcIdx = 263;
	  section.data(261).dtTransOffset = 26225;
	
	  ;% rtP.SwitchCurrents_Value
	  section.data(262).logicalSrcIdx = 264;
	  section.data(262).dtTransOffset = 26226;
	
	  ;% rtP.Constant_Value_ffncqspxq4
	  section.data(263).logicalSrcIdx = 265;
	  section.data(263).dtTransOffset = 26238;
	
	  ;% rtP.Constant1_Value
	  section.data(264).logicalSrcIdx = 266;
	  section.data(264).dtTransOffset = 26239;
	
	  ;% rtP.Constant2_Value
	  section.data(265).logicalSrcIdx = 267;
	  section.data(265).dtTransOffset = 26240;
	
	  ;% rtP.Constant3_Value
	  section.data(266).logicalSrcIdx = 268;
	  section.data(266).dtTransOffset = 26241;
	
	  ;% rtP.Constant_Value_jrk1wafdx5
	  section.data(267).logicalSrcIdx = 269;
	  section.data(267).dtTransOffset = 26242;
	
	  ;% rtP.Constant1_Value_avw5uhdxx5
	  section.data(268).logicalSrcIdx = 270;
	  section.data(268).dtTransOffset = 26243;
	
	  ;% rtP.Constant5_Value
	  section.data(269).logicalSrcIdx = 271;
	  section.data(269).dtTransOffset = 26244;
	
	  ;% rtP.Constant4_Value
	  section.data(270).logicalSrcIdx = 272;
	  section.data(270).dtTransOffset = 26245;
	
	  ;% rtP.Constant6_Value
	  section.data(271).logicalSrcIdx = 273;
	  section.data(271).dtTransOffset = 26246;
	
	  ;% rtP.Constant7_Value
	  section.data(272).logicalSrcIdx = 274;
	  section.data(272).dtTransOffset = 26247;
	
	  ;% rtP.Constant8_Value
	  section.data(273).logicalSrcIdx = 275;
	  section.data(273).dtTransOffset = 26248;
	
	  ;% rtP.Multiply3_Gain
	  section.data(274).logicalSrcIdx = 276;
	  section.data(274).dtTransOffset = 26249;
	
	  ;% rtP.Constant_Value_kfm5xzok4i
	  section.data(275).logicalSrcIdx = 277;
	  section.data(275).dtTransOffset = 26250;
	
	  ;% rtP.Constant19_Value
	  section.data(276).logicalSrcIdx = 278;
	  section.data(276).dtTransOffset = 26251;
	
	  ;% rtP.Constant1_Value_lfvx2nwcp2
	  section.data(277).logicalSrcIdx = 279;
	  section.data(277).dtTransOffset = 26252;
	
	  ;% rtP.Constant2_Value_krq4yfjnno
	  section.data(278).logicalSrcIdx = 280;
	  section.data(278).dtTransOffset = 26253;
	
	  ;% rtP.Constant3_Value_acddb2uoov
	  section.data(279).logicalSrcIdx = 281;
	  section.data(279).dtTransOffset = 26254;
	
	  ;% rtP.Constant4_Value_fthefd0get
	  section.data(280).logicalSrcIdx = 282;
	  section.data(280).dtTransOffset = 26255;
	
	  ;% rtP.Constant_Value_oibu00r03f
	  section.data(281).logicalSrcIdx = 283;
	  section.data(281).dtTransOffset = 26256;
	
	  ;% rtP.Constant1_Value_ktzhc0x1wo
	  section.data(282).logicalSrcIdx = 284;
	  section.data(282).dtTransOffset = 26257;
	
	  ;% rtP.Constant_Value_nct1bh10mh
	  section.data(283).logicalSrcIdx = 285;
	  section.data(283).dtTransOffset = 26258;
	
	  ;% rtP.Constant1_Value_aacpe0p2s4
	  section.data(284).logicalSrcIdx = 286;
	  section.data(284).dtTransOffset = 26259;
	
	  ;% rtP.Constant_Value_m3ckpdnl3e
	  section.data(285).logicalSrcIdx = 287;
	  section.data(285).dtTransOffset = 26260;
	
	  ;% rtP.Constant1_Value_bcnppbahb4
	  section.data(286).logicalSrcIdx = 288;
	  section.data(286).dtTransOffset = 26261;
	
	  ;% rtP.Constant12_Value
	  section.data(287).logicalSrcIdx = 289;
	  section.data(287).dtTransOffset = 26262;
	
	  ;% rtP.Constant14_Value
	  section.data(288).logicalSrcIdx = 290;
	  section.data(288).dtTransOffset = 26263;
	
	  ;% rtP.Constant8_Value_hfo2s31sle
	  section.data(289).logicalSrcIdx = 291;
	  section.data(289).dtTransOffset = 26264;
	
	  ;% rtP.Constant9_Value
	  section.data(290).logicalSrcIdx = 292;
	  section.data(290).dtTransOffset = 26265;
	
	  ;% rtP.Constant1_Value_ixcqqm1d4w
	  section.data(291).logicalSrcIdx = 293;
	  section.data(291).dtTransOffset = 26266;
	
	  ;% rtP.Constant2_Value_m10aoab32w
	  section.data(292).logicalSrcIdx = 294;
	  section.data(292).dtTransOffset = 26267;
	
	  ;% rtP.Constant3_Value_nmyyw0epx1
	  section.data(293).logicalSrcIdx = 295;
	  section.data(293).dtTransOffset = 26268;
	
	  ;% rtP.Constant4_Value_jmvupybtnc
	  section.data(294).logicalSrcIdx = 296;
	  section.data(294).dtTransOffset = 26269;
	
	  ;% rtP.Ta_Value
	  section.data(295).logicalSrcIdx = 297;
	  section.data(295).dtTransOffset = 26270;
	
	  ;% rtP.Constant5_Value_kbjoyjqk2a
	  section.data(296).logicalSrcIdx = 298;
	  section.data(296).dtTransOffset = 26271;
	
	  ;% rtP.Constant5_Value_k3metw3ccu
	  section.data(297).logicalSrcIdx = 299;
	  section.data(297).dtTransOffset = 26272;
	
	  ;% rtP.Saturation_UpperSat_nd1j1mqyat
	  section.data(298).logicalSrcIdx = 300;
	  section.data(298).dtTransOffset = 26273;
	
	  ;% rtP.Saturation_LowerSat_jwye2411i5
	  section.data(299).logicalSrcIdx = 301;
	  section.data(299).dtTransOffset = 26274;
	
	  ;% rtP.eee_Value
	  section.data(300).logicalSrcIdx = 302;
	  section.data(300).dtTransOffset = 26275;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (parameter)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    paramMap.nTotData = nTotData;
    


  ;%**************************
  ;% Create Block Output Map *
  ;%**************************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 2;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (rtB)
    ;%
      section.nData     = 104;
      section.data(104)  = dumData; %prealloc
      
	  ;% rtB.krbxk224wc
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtB.nzprtrw2gw
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtB.cw3ajebfce
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtB.ltu4eypckt
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtB.pg2rvzlxso
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtB.igs1gia5uf
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtB.nba4nhpuqe
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtB.hxodaq3aem
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtB.klfwarvagc
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtB.i0ujncnh35
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% rtB.dplapzekhr
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% rtB.b2m0nyy1iq
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% rtB.dg1zqpobap
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% rtB.m2zun0bmq0
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% rtB.bnsiwqbz4c
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% rtB.nd5vhw3hdp
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
	  ;% rtB.pkslvtv3r5
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 16;
	
	  ;% rtB.l1bfou4fat
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 17;
	
	  ;% rtB.mdng4h4wi3
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 18;
	
	  ;% rtB.akgc550kdx
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 19;
	
	  ;% rtB.aunoa00r4h
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 20;
	
	  ;% rtB.ds4vmpgjgq
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 21;
	
	  ;% rtB.aprtxoz0cz
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 59;
	
	  ;% rtB.dsl30exhdf
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 71;
	
	  ;% rtB.lwbnk1tqoe
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 72;
	
	  ;% rtB.lnggl4hxqa
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 73;
	
	  ;% rtB.cnvh3z11oj
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 74;
	
	  ;% rtB.caydqvbppv
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 75;
	
	  ;% rtB.cataaai4vr
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 76;
	
	  ;% rtB.glbb5pdj1b
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 77;
	
	  ;% rtB.i5qlxhsaeo
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 78;
	
	  ;% rtB.kx2yvfrvbs
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 79;
	
	  ;% rtB.pydykgygzv
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 80;
	
	  ;% rtB.i4u1u0nk00
	  section.data(34).logicalSrcIdx = 33;
	  section.data(34).dtTransOffset = 81;
	
	  ;% rtB.bbivpaarxt
	  section.data(35).logicalSrcIdx = 34;
	  section.data(35).dtTransOffset = 82;
	
	  ;% rtB.nh1zxcsjip
	  section.data(36).logicalSrcIdx = 35;
	  section.data(36).dtTransOffset = 83;
	
	  ;% rtB.gvxuq2ivcx
	  section.data(37).logicalSrcIdx = 36;
	  section.data(37).dtTransOffset = 84;
	
	  ;% rtB.fiwvizlnvo
	  section.data(38).logicalSrcIdx = 37;
	  section.data(38).dtTransOffset = 85;
	
	  ;% rtB.mm1bpfcahk
	  section.data(39).logicalSrcIdx = 38;
	  section.data(39).dtTransOffset = 86;
	
	  ;% rtB.ds12aiafx0
	  section.data(40).logicalSrcIdx = 39;
	  section.data(40).dtTransOffset = 87;
	
	  ;% rtB.oaypl0xy40
	  section.data(41).logicalSrcIdx = 40;
	  section.data(41).dtTransOffset = 88;
	
	  ;% rtB.hejghjylpf
	  section.data(42).logicalSrcIdx = 41;
	  section.data(42).dtTransOffset = 89;
	
	  ;% rtB.lkdpawgj3d
	  section.data(43).logicalSrcIdx = 42;
	  section.data(43).dtTransOffset = 90;
	
	  ;% rtB.b0ihg4ev5s
	  section.data(44).logicalSrcIdx = 43;
	  section.data(44).dtTransOffset = 91;
	
	  ;% rtB.dn4cfjoyu3
	  section.data(45).logicalSrcIdx = 44;
	  section.data(45).dtTransOffset = 92;
	
	  ;% rtB.ee4dkbgmbt
	  section.data(46).logicalSrcIdx = 45;
	  section.data(46).dtTransOffset = 93;
	
	  ;% rtB.a3xn5q0qbv
	  section.data(47).logicalSrcIdx = 46;
	  section.data(47).dtTransOffset = 94;
	
	  ;% rtB.d2aecp5kgr
	  section.data(48).logicalSrcIdx = 47;
	  section.data(48).dtTransOffset = 95;
	
	  ;% rtB.jqk43gypqg
	  section.data(49).logicalSrcIdx = 48;
	  section.data(49).dtTransOffset = 96;
	
	  ;% rtB.k04sqjkmui
	  section.data(50).logicalSrcIdx = 49;
	  section.data(50).dtTransOffset = 97;
	
	  ;% rtB.ewf3nftshe
	  section.data(51).logicalSrcIdx = 50;
	  section.data(51).dtTransOffset = 98;
	
	  ;% rtB.hdopse5d1y
	  section.data(52).logicalSrcIdx = 51;
	  section.data(52).dtTransOffset = 99;
	
	  ;% rtB.cabjp2xkxg
	  section.data(53).logicalSrcIdx = 52;
	  section.data(53).dtTransOffset = 100;
	
	  ;% rtB.mz2im1vd2w
	  section.data(54).logicalSrcIdx = 53;
	  section.data(54).dtTransOffset = 101;
	
	  ;% rtB.jpdjo1yg5c
	  section.data(55).logicalSrcIdx = 54;
	  section.data(55).dtTransOffset = 102;
	
	  ;% rtB.jjcrtkkpmt
	  section.data(56).logicalSrcIdx = 55;
	  section.data(56).dtTransOffset = 103;
	
	  ;% rtB.aoywj0c0aw
	  section.data(57).logicalSrcIdx = 56;
	  section.data(57).dtTransOffset = 104;
	
	  ;% rtB.gswcpufwfm
	  section.data(58).logicalSrcIdx = 57;
	  section.data(58).dtTransOffset = 105;
	
	  ;% rtB.nfrcslok3r
	  section.data(59).logicalSrcIdx = 58;
	  section.data(59).dtTransOffset = 106;
	
	  ;% rtB.bp13llqzit
	  section.data(60).logicalSrcIdx = 59;
	  section.data(60).dtTransOffset = 107;
	
	  ;% rtB.nw10mpmiwb
	  section.data(61).logicalSrcIdx = 60;
	  section.data(61).dtTransOffset = 108;
	
	  ;% rtB.dsv2bbs0k1
	  section.data(62).logicalSrcIdx = 61;
	  section.data(62).dtTransOffset = 109;
	
	  ;% rtB.oaxo1bryj0
	  section.data(63).logicalSrcIdx = 62;
	  section.data(63).dtTransOffset = 110;
	
	  ;% rtB.pkp0sjqqg3
	  section.data(64).logicalSrcIdx = 63;
	  section.data(64).dtTransOffset = 122;
	
	  ;% rtB.npdclyuhqf
	  section.data(65).logicalSrcIdx = 64;
	  section.data(65).dtTransOffset = 123;
	
	  ;% rtB.b11tooymbq
	  section.data(66).logicalSrcIdx = 65;
	  section.data(66).dtTransOffset = 124;
	
	  ;% rtB.ju3eqofxsv
	  section.data(67).logicalSrcIdx = 66;
	  section.data(67).dtTransOffset = 125;
	
	  ;% rtB.k401caq3eb
	  section.data(68).logicalSrcIdx = 67;
	  section.data(68).dtTransOffset = 126;
	
	  ;% rtB.ftivrztnav
	  section.data(69).logicalSrcIdx = 68;
	  section.data(69).dtTransOffset = 127;
	
	  ;% rtB.cp1s511zvk
	  section.data(70).logicalSrcIdx = 69;
	  section.data(70).dtTransOffset = 128;
	
	  ;% rtB.dgk2xu5prp
	  section.data(71).logicalSrcIdx = 70;
	  section.data(71).dtTransOffset = 129;
	
	  ;% rtB.fsyjc2e3jn
	  section.data(72).logicalSrcIdx = 71;
	  section.data(72).dtTransOffset = 130;
	
	  ;% rtB.pmkgps0zyu
	  section.data(73).logicalSrcIdx = 72;
	  section.data(73).dtTransOffset = 131;
	
	  ;% rtB.crs0im5dqp
	  section.data(74).logicalSrcIdx = 73;
	  section.data(74).dtTransOffset = 132;
	
	  ;% rtB.idvqtvfoyk
	  section.data(75).logicalSrcIdx = 74;
	  section.data(75).dtTransOffset = 133;
	
	  ;% rtB.djegcg25ae
	  section.data(76).logicalSrcIdx = 75;
	  section.data(76).dtTransOffset = 134;
	
	  ;% rtB.ijubt5styh
	  section.data(77).logicalSrcIdx = 76;
	  section.data(77).dtTransOffset = 135;
	
	  ;% rtB.fxmmxdki1w
	  section.data(78).logicalSrcIdx = 77;
	  section.data(78).dtTransOffset = 136;
	
	  ;% rtB.mykimnyubj
	  section.data(79).logicalSrcIdx = 78;
	  section.data(79).dtTransOffset = 137;
	
	  ;% rtB.b5ekoo4s5v
	  section.data(80).logicalSrcIdx = 79;
	  section.data(80).dtTransOffset = 138;
	
	  ;% rtB.ktal25amyn
	  section.data(81).logicalSrcIdx = 80;
	  section.data(81).dtTransOffset = 139;
	
	  ;% rtB.e2chijmfh2
	  section.data(82).logicalSrcIdx = 81;
	  section.data(82).dtTransOffset = 140;
	
	  ;% rtB.ajuoykrpve
	  section.data(83).logicalSrcIdx = 82;
	  section.data(83).dtTransOffset = 141;
	
	  ;% rtB.orc5wcdxm1
	  section.data(84).logicalSrcIdx = 83;
	  section.data(84).dtTransOffset = 142;
	
	  ;% rtB.akwd4yohpb
	  section.data(85).logicalSrcIdx = 84;
	  section.data(85).dtTransOffset = 143;
	
	  ;% rtB.hwgkbedju4
	  section.data(86).logicalSrcIdx = 85;
	  section.data(86).dtTransOffset = 144;
	
	  ;% rtB.akgbctleuf
	  section.data(87).logicalSrcIdx = 86;
	  section.data(87).dtTransOffset = 145;
	
	  ;% rtB.fjva4ba3yf
	  section.data(88).logicalSrcIdx = 87;
	  section.data(88).dtTransOffset = 146;
	
	  ;% rtB.ojpp3hq5ld
	  section.data(89).logicalSrcIdx = 88;
	  section.data(89).dtTransOffset = 147;
	
	  ;% rtB.ddwaerj1qf
	  section.data(90).logicalSrcIdx = 89;
	  section.data(90).dtTransOffset = 148;
	
	  ;% rtB.e4esbiadth
	  section.data(91).logicalSrcIdx = 90;
	  section.data(91).dtTransOffset = 149;
	
	  ;% rtB.dv32o2egzr
	  section.data(92).logicalSrcIdx = 91;
	  section.data(92).dtTransOffset = 150;
	
	  ;% rtB.b1fl12txsf
	  section.data(93).logicalSrcIdx = 92;
	  section.data(93).dtTransOffset = 151;
	
	  ;% rtB.liwqgy4ofb
	  section.data(94).logicalSrcIdx = 93;
	  section.data(94).dtTransOffset = 152;
	
	  ;% rtB.cf3awerlht
	  section.data(95).logicalSrcIdx = 94;
	  section.data(95).dtTransOffset = 153;
	
	  ;% rtB.o0lhjiunqy
	  section.data(96).logicalSrcIdx = 95;
	  section.data(96).dtTransOffset = 154;
	
	  ;% rtB.i4esmxfcaq
	  section.data(97).logicalSrcIdx = 96;
	  section.data(97).dtTransOffset = 155;
	
	  ;% rtB.ewvuxv0roa
	  section.data(98).logicalSrcIdx = 97;
	  section.data(98).dtTransOffset = 156;
	
	  ;% rtB.frtehkabsr
	  section.data(99).logicalSrcIdx = 98;
	  section.data(99).dtTransOffset = 157;
	
	  ;% rtB.paaipnyjy4
	  section.data(100).logicalSrcIdx = 99;
	  section.data(100).dtTransOffset = 158;
	
	  ;% rtB.ctjnl3duhv
	  section.data(101).logicalSrcIdx = 100;
	  section.data(101).dtTransOffset = 159;
	
	  ;% rtB.h0hkib4ron
	  section.data(102).logicalSrcIdx = 101;
	  section.data(102).dtTransOffset = 160;
	
	  ;% rtB.gxs3xlh0jb
	  section.data(103).logicalSrcIdx = 102;
	  section.data(103).dtTransOffset = 161;
	
	  ;% rtB.cuh2ly0avr
	  section.data(104).logicalSrcIdx = 103;
	  section.data(104).dtTransOffset = 162;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.nvvl1et5cw
	  section.data(1).logicalSrcIdx = 104;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (signal)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    sigMap.nTotData = nTotData;
    


  ;%*******************
  ;% Create DWork Map *
  ;%*******************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 5;
    sectIdxOffset = 2;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc dworkMap
    ;%
    dworkMap.nSections           = nTotSects;
    dworkMap.sectIdxOffset       = sectIdxOffset;
      dworkMap.sections(nTotSects) = dumSection; %prealloc
    dworkMap.nTotData            = -1;
    
    ;%
    ;% Auto data (rtDW)
    ;%
      section.nData     = 61;
      section.data(61)  = dumData; %prealloc
      
	  ;% rtDW.ae4fdc50fw
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.ns3jml1yrn
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.bkylhixnvg
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtDW.mcqhrorlxr
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtDW.hyrzihgqre
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtDW.opkdjwnlyz
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtDW.nbkcuaxc3y
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtDW.blkk50vpkb
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtDW.ifljlxnawa
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtDW.df3h3bq4ax
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% rtDW.ew4rinximz
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% rtDW.nb0afwz3qd
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% rtDW.ntr0qnnxwd
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% rtDW.m01vpi11le
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% rtDW.p53jjbkpzn
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% rtDW.mkxkhcmalu
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
	  ;% rtDW.jejzfwqaao
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 16;
	
	  ;% rtDW.fs5pddw5ow
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 17;
	
	  ;% rtDW.k0okhesaat
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 30;
	
	  ;% rtDW.gepbsobs0a
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 31;
	
	  ;% rtDW.fzr1ogugs2
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 32;
	
	  ;% rtDW.i4wxuhmfgf
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 33;
	
	  ;% rtDW.hzeqqg0jia
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 34;
	
	  ;% rtDW.c4quijr14v
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 35;
	
	  ;% rtDW.f51eegc2bu
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 36;
	
	  ;% rtDW.fxt15s43p4
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 37;
	
	  ;% rtDW.g3gghz3gaz
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 38;
	
	  ;% rtDW.abf3scvxey
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 39;
	
	  ;% rtDW.h1wh3z4evx
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 40;
	
	  ;% rtDW.bds32z0txa
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 41;
	
	  ;% rtDW.ebacjx4abi
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 42;
	
	  ;% rtDW.cbffa5ojlz
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 43;
	
	  ;% rtDW.cfb4bptno0
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 44;
	
	  ;% rtDW.bljv3otj05
	  section.data(34).logicalSrcIdx = 33;
	  section.data(34).dtTransOffset = 45;
	
	  ;% rtDW.b4zh5qri0d
	  section.data(35).logicalSrcIdx = 34;
	  section.data(35).dtTransOffset = 46;
	
	  ;% rtDW.ic00z2hy2m
	  section.data(36).logicalSrcIdx = 35;
	  section.data(36).dtTransOffset = 47;
	
	  ;% rtDW.fzp55m5l14
	  section.data(37).logicalSrcIdx = 36;
	  section.data(37).dtTransOffset = 48;
	
	  ;% rtDW.bsqle4x1ip
	  section.data(38).logicalSrcIdx = 37;
	  section.data(38).dtTransOffset = 49;
	
	  ;% rtDW.ehtf41cg10
	  section.data(39).logicalSrcIdx = 38;
	  section.data(39).dtTransOffset = 50;
	
	  ;% rtDW.p2pkpj1mv5
	  section.data(40).logicalSrcIdx = 39;
	  section.data(40).dtTransOffset = 51;
	
	  ;% rtDW.cn5opu2pzs
	  section.data(41).logicalSrcIdx = 40;
	  section.data(41).dtTransOffset = 52;
	
	  ;% rtDW.fimioqcfmg
	  section.data(42).logicalSrcIdx = 41;
	  section.data(42).dtTransOffset = 53;
	
	  ;% rtDW.ksxohwmcoh
	  section.data(43).logicalSrcIdx = 42;
	  section.data(43).dtTransOffset = 54;
	
	  ;% rtDW.bv3zs25i1r
	  section.data(44).logicalSrcIdx = 43;
	  section.data(44).dtTransOffset = 55;
	
	  ;% rtDW.nqhcy2vec4
	  section.data(45).logicalSrcIdx = 44;
	  section.data(45).dtTransOffset = 56;
	
	  ;% rtDW.p5fqadhn5b
	  section.data(46).logicalSrcIdx = 45;
	  section.data(46).dtTransOffset = 57;
	
	  ;% rtDW.ikqkqwjh3n
	  section.data(47).logicalSrcIdx = 46;
	  section.data(47).dtTransOffset = 58;
	
	  ;% rtDW.awv1q3egsu
	  section.data(48).logicalSrcIdx = 47;
	  section.data(48).dtTransOffset = 59;
	
	  ;% rtDW.bhhdr2vx1r
	  section.data(49).logicalSrcIdx = 48;
	  section.data(49).dtTransOffset = 60;
	
	  ;% rtDW.m4yjnvjtaz
	  section.data(50).logicalSrcIdx = 49;
	  section.data(50).dtTransOffset = 61;
	
	  ;% rtDW.pztkm2b5s5
	  section.data(51).logicalSrcIdx = 50;
	  section.data(51).dtTransOffset = 62;
	
	  ;% rtDW.hsvqv45oph
	  section.data(52).logicalSrcIdx = 51;
	  section.data(52).dtTransOffset = 63;
	
	  ;% rtDW.cg2af1bnv1
	  section.data(53).logicalSrcIdx = 52;
	  section.data(53).dtTransOffset = 64;
	
	  ;% rtDW.jp23k4f2go
	  section.data(54).logicalSrcIdx = 53;
	  section.data(54).dtTransOffset = 65;
	
	  ;% rtDW.chezipvofm
	  section.data(55).logicalSrcIdx = 54;
	  section.data(55).dtTransOffset = 66;
	
	  ;% rtDW.lypv2c215x
	  section.data(56).logicalSrcIdx = 55;
	  section.data(56).dtTransOffset = 67;
	
	  ;% rtDW.dhksroq5rn
	  section.data(57).logicalSrcIdx = 56;
	  section.data(57).dtTransOffset = 68;
	
	  ;% rtDW.gyaphxw5hc
	  section.data(58).logicalSrcIdx = 57;
	  section.data(58).dtTransOffset = 69;
	
	  ;% rtDW.n0cer4zw0t
	  section.data(59).logicalSrcIdx = 58;
	  section.data(59).dtTransOffset = 70;
	
	  ;% rtDW.knii4eahbq
	  section.data(60).logicalSrcIdx = 59;
	  section.data(60).dtTransOffset = 71;
	
	  ;% rtDW.e0g3wfol1j
	  section.data(61).logicalSrcIdx = 60;
	  section.data(61).dtTransOffset = 72;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% rtDW.jdobxxns3j
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.ct5pbogejq.AQHandles
	  section.data(2).logicalSrcIdx = 62;
	  section.data(2).dtTransOffset = 65;
	
	  ;% rtDW.op222kfxbt.LoggedData
	  section.data(3).logicalSrcIdx = 63;
	  section.data(3).dtTransOffset = 66;
	
	  ;% rtDW.lqgtrexdqd.LoggedData
	  section.data(4).logicalSrcIdx = 64;
	  section.data(4).dtTransOffset = 67;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.jpo5gkezdl
	  section.data(1).logicalSrcIdx = 65;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% rtDW.jjhzuiuwr5
	  section.data(1).logicalSrcIdx = 66;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.kalc0i12gy
	  section.data(2).logicalSrcIdx = 67;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.kt2if2m30y
	  section.data(1).logicalSrcIdx = 68;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (dwork)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    dworkMap.nTotData = nTotData;
    


  ;%
  ;% Add individual maps to base struct.
  ;%

  targMap.paramMap  = paramMap;    
  targMap.signalMap = sigMap;
  targMap.dworkMap  = dworkMap;
  
  ;%
  ;% Add checksums to base struct.
  ;%


  targMap.checksum0 = 481942086;
  targMap.checksum1 = 2148804559;
  targMap.checksum2 = 3671713165;
  targMap.checksum3 = 1349130020;


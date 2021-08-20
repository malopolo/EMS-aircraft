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
      section.nData     = 304;
      section.data(304)  = dumData; %prealloc
      
	  ;% rtP.t
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtP.w
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 180720;
	
	  ;% rtP.Battery_BatType
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 361440;
	
	  ;% rtP.PVMODULE1_I0
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 361441;
	
	  ;% rtP.PVMODULE1_Impp
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 361442;
	
	  ;% rtP.DiscretePIController1_Init
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 361443;
	
	  ;% rtP.DiscretePIController2_Init
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 361444;
	
	  ;% rtP.DiscretePIController2_Init_ofcbucrrnd
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 361445;
	
	  ;% rtP.DiscretePIController3_Init
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 361446;
	
	  ;% rtP.DiscretePIController4_Init
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 361447;
	
	  ;% rtP.DiscretePIController3_Init_lcdytxavmn
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 361448;
	
	  ;% rtP.DiscretePIController4_Init_ojyv5ifd0r
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 361449;
	
	  ;% rtP.PVMODULE1_Isc
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 361450;
	
	  ;% rtP.DiscretePIController1_Ki
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 361451;
	
	  ;% rtP.DiscretePIController2_Ki
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 361452;
	
	  ;% rtP.DiscretePIController3_Ki
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 361453;
	
	  ;% rtP.DiscretePIController4_Ki
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 361454;
	
	  ;% rtP.DiscretePIController3_Ki_catboe4e3q
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 361455;
	
	  ;% rtP.DiscretePIController4_Ki_ksfhmxpwtu
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 361456;
	
	  ;% rtP.DiscretePIController2_Ki_lu2imaebpa
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 361457;
	
	  ;% rtP.DiscretePIController1_Kp
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 361458;
	
	  ;% rtP.DiscretePIController2_Kp
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 361459;
	
	  ;% rtP.DiscretePIController2_Kp_jtir0rv5nd
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 361460;
	
	  ;% rtP.DiscretePIController3_Kp
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 361461;
	
	  ;% rtP.DiscretePIController4_Kp
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 361462;
	
	  ;% rtP.DiscretePIController3_Kp_ppecbhclte
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 361463;
	
	  ;% rtP.DiscretePIController4_Kp_crtfhdlpjf
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 361464;
	
	  ;% rtP.PVMODULE1_Ncell
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 361465;
	
	  ;% rtP.PVMODULE1_Npar
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 361466;
	
	  ;% rtP.PVMODULE1_Nser
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 361467;
	
	  ;% rtP.VariableResistor_Rabsmin
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 361468;
	
	  ;% rtP.PVMODULE1_Rs
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 361469;
	
	  ;% rtP.PVMODULE1_Rsh
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 361470;
	
	  ;% rtP.Battery_SOC
	  section.data(34).logicalSrcIdx = 33;
	  section.data(34).dtTransOffset = 361471;
	
	  ;% rtP.PVMODULE1_Vmpp
	  section.data(35).logicalSrcIdx = 34;
	  section.data(35).dtTransOffset = 361472;
	
	  ;% rtP.PVMODULE1_Voc
	  section.data(36).logicalSrcIdx = 35;
	  section.data(36).dtTransOffset = 361473;
	
	  ;% rtP.PVMODULE1_beta_Voc
	  section.data(37).logicalSrcIdx = 36;
	  section.data(37).dtTransOffset = 361474;
	
	  ;% rtP.CompareToConstant_const
	  section.data(38).logicalSrcIdx = 37;
	  section.data(38).dtTransOffset = 361475;
	
	  ;% rtP.PVMODULE1_df
	  section.data(39).logicalSrcIdx = 38;
	  section.data(39).dtTransOffset = 361476;
	
	  ;% rtP.BoostFCfast_n
	  section.data(40).logicalSrcIdx = 39;
	  section.data(40).dtTransOffset = 361477;
	
	  ;% rtP.BoostPVfast_n
	  section.data(41).logicalSrcIdx = 40;
	  section.data(41).dtTransOffset = 361478;
	
	  ;% rtP.BidirectionalBOOSTBUCKBattfast_n_boost
	  section.data(42).logicalSrcIdx = 41;
	  section.data(42).dtTransOffset = 361479;
	
	  ;% rtP.BidirectionalBOOSTBUCKBattfast_n_buck
	  section.data(43).logicalSrcIdx = 42;
	  section.data(43).dtTransOffset = 361480;
	
	  ;% rtP.Saturation_UpperSat
	  section.data(44).logicalSrcIdx = 43;
	  section.data(44).dtTransOffset = 361481;
	
	  ;% rtP.Saturation_LowerSat
	  section.data(45).logicalSrcIdx = 44;
	  section.data(45).dtTransOffset = 361482;
	
	  ;% rtP.OutputSamplePoints_Value
	  section.data(46).logicalSrcIdx = 45;
	  section.data(46).dtTransOffset = 361483;
	
	  ;% rtP.Switch1_Threshold
	  section.data(47).logicalSrcIdx = 46;
	  section.data(47).dtTransOffset = 361485;
	
	  ;% rtP.Constant_Value
	  section.data(48).logicalSrcIdx = 47;
	  section.data(48).dtTransOffset = 361486;
	
	  ;% rtP.Constant_Value_lc2t2ikfiz
	  section.data(49).logicalSrcIdx = 48;
	  section.data(49).dtTransOffset = 361487;
	
	  ;% rtP.Constant_Value_pty4zc05uj
	  section.data(50).logicalSrcIdx = 49;
	  section.data(50).dtTransOffset = 361488;
	
	  ;% rtP.itinit3_InitialCondition
	  section.data(51).logicalSrcIdx = 50;
	  section.data(51).dtTransOffset = 361489;
	
	  ;% rtP.R2_Gain
	  section.data(52).logicalSrcIdx = 51;
	  section.data(52).dtTransOffset = 361490;
	
	  ;% rtP.Currentfilter5_NumCoef
	  section.data(53).logicalSrcIdx = 52;
	  section.data(53).dtTransOffset = 361491;
	
	  ;% rtP.Currentfilter5_DenCoef
	  section.data(54).logicalSrcIdx = 53;
	  section.data(54).dtTransOffset = 361492;
	
	  ;% rtP.Currentfilter5_InitialStates
	  section.data(55).logicalSrcIdx = 54;
	  section.data(55).dtTransOffset = 361494;
	
	  ;% rtP.itinit_InitialCondition
	  section.data(56).logicalSrcIdx = 55;
	  section.data(56).dtTransOffset = 361495;
	
	  ;% rtP.inti_gainval
	  section.data(57).logicalSrcIdx = 56;
	  section.data(57).dtTransOffset = 361496;
	
	  ;% rtP.inti_UpperSat
	  section.data(58).logicalSrcIdx = 57;
	  section.data(58).dtTransOffset = 361497;
	
	  ;% rtP.inti_LowerSat
	  section.data(59).logicalSrcIdx = 58;
	  section.data(59).dtTransOffset = 361498;
	
	  ;% rtP.Gain_Gain
	  section.data(60).logicalSrcIdx = 59;
	  section.data(60).dtTransOffset = 361499;
	
	  ;% rtP.R3_Gain
	  section.data(61).logicalSrcIdx = 60;
	  section.data(61).dtTransOffset = 361500;
	
	  ;% rtP.DiscreteTimeIntegrator_gainval
	  section.data(62).logicalSrcIdx = 61;
	  section.data(62).dtTransOffset = 361501;
	
	  ;% rtP.DiscreteTimeIntegrator_IC
	  section.data(63).logicalSrcIdx = 62;
	  section.data(63).dtTransOffset = 361502;
	
	  ;% rtP.Memory2_InitialCondition
	  section.data(64).logicalSrcIdx = 63;
	  section.data(64).dtTransOffset = 361503;
	
	  ;% rtP.UnitDelay1_InitialCondition
	  section.data(65).logicalSrcIdx = 64;
	  section.data(65).dtTransOffset = 361504;
	
	  ;% rtP.UnitDelay2_InitialCondition
	  section.data(66).logicalSrcIdx = 65;
	  section.data(66).dtTransOffset = 361505;
	
	  ;% rtP.UnitDelay2_InitialCondition_kplvr2c540
	  section.data(67).logicalSrcIdx = 66;
	  section.data(67).dtTransOffset = 361506;
	
	  ;% rtP.Delay_InitialCondition
	  section.data(68).logicalSrcIdx = 67;
	  section.data(68).dtTransOffset = 361507;
	
	  ;% rtP.Saturation_UpperSat_gvrgxklgqx
	  section.data(69).logicalSrcIdx = 68;
	  section.data(69).dtTransOffset = 361508;
	
	  ;% rtP.Saturation_LowerSat_cndq0w2uve
	  section.data(70).logicalSrcIdx = 69;
	  section.data(70).dtTransOffset = 361509;
	
	  ;% rtP.DiscreteTimeIntegrator_gainval_m4ai2wnufy
	  section.data(71).logicalSrcIdx = 70;
	  section.data(71).dtTransOffset = 361510;
	
	  ;% rtP.DiscreteTimeIntegrator_IC_bjhalm0xhc
	  section.data(72).logicalSrcIdx = 71;
	  section.data(72).dtTransOffset = 361511;
	
	  ;% rtP.UnitDelay_InitialCondition
	  section.data(73).logicalSrcIdx = 72;
	  section.data(73).dtTransOffset = 361512;
	
	  ;% rtP.Multiply_Gain
	  section.data(74).logicalSrcIdx = 73;
	  section.data(74).dtTransOffset = 361513;
	
	  ;% rtP.UnitDelay1_InitialCondition_b5qtmccqei
	  section.data(75).logicalSrcIdx = 74;
	  section.data(75).dtTransOffset = 361514;
	
	  ;% rtP.DiscreteTimeIntegrator_gainval_lknx5x0oaz
	  section.data(76).logicalSrcIdx = 75;
	  section.data(76).dtTransOffset = 361515;
	
	  ;% rtP.DiscreteTimeIntegrator_IC_p2dyd1g5fi
	  section.data(77).logicalSrcIdx = 76;
	  section.data(77).dtTransOffset = 361516;
	
	  ;% rtP.Saturation_UpperSat_e2k0qdtv2s
	  section.data(78).logicalSrcIdx = 77;
	  section.data(78).dtTransOffset = 361517;
	
	  ;% rtP.Saturation_LowerSat_d5xrshbz0z
	  section.data(79).logicalSrcIdx = 78;
	  section.data(79).dtTransOffset = 361518;
	
	  ;% rtP.UnitDelay2_InitialCondition_mynahauzpq
	  section.data(80).logicalSrcIdx = 79;
	  section.data(80).dtTransOffset = 361519;
	
	  ;% rtP.UnitDelay3_InitialCondition
	  section.data(81).logicalSrcIdx = 80;
	  section.data(81).dtTransOffset = 361520;
	
	  ;% rtP.UnitDelay3_InitialCondition_kgclqpwylc
	  section.data(82).logicalSrcIdx = 81;
	  section.data(82).dtTransOffset = 361521;
	
	  ;% rtP.UnitDelay1_InitialCondition_pmpt1ejnb2
	  section.data(83).logicalSrcIdx = 82;
	  section.data(83).dtTransOffset = 361522;
	
	  ;% rtP.UnitDelay4_InitialCondition
	  section.data(84).logicalSrcIdx = 83;
	  section.data(84).dtTransOffset = 361523;
	
	  ;% rtP.UnitDelay_InitialCondition_ckvjp4gfil
	  section.data(85).logicalSrcIdx = 84;
	  section.data(85).dtTransOffset = 361524;
	
	  ;% rtP.StateSpace_P1_Size
	  section.data(86).logicalSrcIdx = 85;
	  section.data(86).dtTransOffset = 361525;
	
	  ;% rtP.StateSpace_P1
	  section.data(87).logicalSrcIdx = 86;
	  section.data(87).dtTransOffset = 361527;
	
	  ;% rtP.StateSpace_P2_Size
	  section.data(88).logicalSrcIdx = 87;
	  section.data(88).dtTransOffset = 361528;
	
	  ;% rtP.StateSpace_P2
	  section.data(89).logicalSrcIdx = 88;
	  section.data(89).dtTransOffset = 361530;
	
	  ;% rtP.StateSpace_P3_Size
	  section.data(90).logicalSrcIdx = 89;
	  section.data(90).dtTransOffset = 361699;
	
	  ;% rtP.StateSpace_P3
	  section.data(91).logicalSrcIdx = 90;
	  section.data(91).dtTransOffset = 361701;
	
	  ;% rtP.StateSpace_P4_Size
	  section.data(92).logicalSrcIdx = 91;
	  section.data(92).dtTransOffset = 362013;
	
	  ;% rtP.StateSpace_P4
	  section.data(93).logicalSrcIdx = 92;
	  section.data(93).dtTransOffset = 362015;
	
	  ;% rtP.StateSpace_P5_Size
	  section.data(94).logicalSrcIdx = 93;
	  section.data(94).dtTransOffset = 362509;
	
	  ;% rtP.StateSpace_P5
	  section.data(95).logicalSrcIdx = 94;
	  section.data(95).dtTransOffset = 362511;
	
	  ;% rtP.StateSpace_P6_Size
	  section.data(96).logicalSrcIdx = 95;
	  section.data(96).dtTransOffset = 363423;
	
	  ;% rtP.StateSpace_P6
	  section.data(97).logicalSrcIdx = 96;
	  section.data(97).dtTransOffset = 363425;
	
	  ;% rtP.StateSpace_P7_Size
	  section.data(98).logicalSrcIdx = 97;
	  section.data(98).dtTransOffset = 363438;
	
	  ;% rtP.StateSpace_P7
	  section.data(99).logicalSrcIdx = 98;
	  section.data(99).dtTransOffset = 363440;
	
	  ;% rtP.StateSpace_P8_Size
	  section.data(100).logicalSrcIdx = 99;
	  section.data(100).dtTransOffset = 363441;
	
	  ;% rtP.StateSpace_P8
	  section.data(101).logicalSrcIdx = 100;
	  section.data(101).dtTransOffset = 363443;
	
	  ;% rtP.StateSpace_P9_Size
	  section.data(102).logicalSrcIdx = 101;
	  section.data(102).dtTransOffset = 363446;
	
	  ;% rtP.StateSpace_P10_Size
	  section.data(103).logicalSrcIdx = 103;
	  section.data(103).dtTransOffset = 363448;
	
	  ;% rtP.StateSpace_P10
	  section.data(104).logicalSrcIdx = 104;
	  section.data(104).dtTransOffset = 363450;
	
	  ;% rtP.StateSpace_P11_Size
	  section.data(105).logicalSrcIdx = 105;
	  section.data(105).dtTransOffset = 363451;
	
	  ;% rtP.StateSpace_P11
	  section.data(106).logicalSrcIdx = 106;
	  section.data(106).dtTransOffset = 363453;
	
	  ;% rtP.StateSpace_P12_Size
	  section.data(107).logicalSrcIdx = 107;
	  section.data(107).dtTransOffset = 363454;
	
	  ;% rtP.StateSpace_P13_Size
	  section.data(108).logicalSrcIdx = 109;
	  section.data(108).dtTransOffset = 363456;
	
	  ;% rtP.StateSpace_P13
	  section.data(109).logicalSrcIdx = 110;
	  section.data(109).dtTransOffset = 363458;
	
	  ;% rtP.StateSpace_P14_Size
	  section.data(110).logicalSrcIdx = 111;
	  section.data(110).dtTransOffset = 363459;
	
	  ;% rtP.StateSpace_P14
	  section.data(111).logicalSrcIdx = 112;
	  section.data(111).dtTransOffset = 363461;
	
	  ;% rtP.StateSpace_P15_Size
	  section.data(112).logicalSrcIdx = 113;
	  section.data(112).dtTransOffset = 363462;
	
	  ;% rtP.StateSpace_P16_Size
	  section.data(113).logicalSrcIdx = 115;
	  section.data(113).dtTransOffset = 363464;
	
	  ;% rtP.StateSpace_P16
	  section.data(114).logicalSrcIdx = 116;
	  section.data(114).dtTransOffset = 363466;
	
	  ;% rtP.StateSpace_P17_Size
	  section.data(115).logicalSrcIdx = 117;
	  section.data(115).dtTransOffset = 363467;
	
	  ;% rtP.StateSpace_P17
	  section.data(116).logicalSrcIdx = 118;
	  section.data(116).dtTransOffset = 363469;
	
	  ;% rtP.StateSpace_P18_Size
	  section.data(117).logicalSrcIdx = 119;
	  section.data(117).dtTransOffset = 363470;
	
	  ;% rtP.StateSpace_P18
	  section.data(118).logicalSrcIdx = 120;
	  section.data(118).dtTransOffset = 363472;
	
	  ;% rtP.StateSpace_P19_Size
	  section.data(119).logicalSrcIdx = 121;
	  section.data(119).dtTransOffset = 363473;
	
	  ;% rtP.StateSpace_P19
	  section.data(120).logicalSrcIdx = 122;
	  section.data(120).dtTransOffset = 363475;
	
	  ;% rtP.StateSpace_P20_Size
	  section.data(121).logicalSrcIdx = 123;
	  section.data(121).dtTransOffset = 363476;
	
	  ;% rtP.StateSpace_P20
	  section.data(122).logicalSrcIdx = 124;
	  section.data(122).dtTransOffset = 363478;
	
	  ;% rtP.StateSpace_P21_Size
	  section.data(123).logicalSrcIdx = 125;
	  section.data(123).dtTransOffset = 363490;
	
	  ;% rtP.StateSpace_P21
	  section.data(124).logicalSrcIdx = 126;
	  section.data(124).dtTransOffset = 363492;
	
	  ;% rtP.StateSpace_P22_Size
	  section.data(125).logicalSrcIdx = 127;
	  section.data(125).dtTransOffset = 363504;
	
	  ;% rtP.StateSpace_P22
	  section.data(126).logicalSrcIdx = 128;
	  section.data(126).dtTransOffset = 363506;
	
	  ;% rtP.StateSpace_P23_Size
	  section.data(127).logicalSrcIdx = 129;
	  section.data(127).dtTransOffset = 363518;
	
	  ;% rtP.StateSpace_P23
	  section.data(128).logicalSrcIdx = 130;
	  section.data(128).dtTransOffset = 363520;
	
	  ;% rtP.StateSpace_P24_Size
	  section.data(129).logicalSrcIdx = 131;
	  section.data(129).dtTransOffset = 363532;
	
	  ;% rtP.StateSpace_P24
	  section.data(130).logicalSrcIdx = 132;
	  section.data(130).dtTransOffset = 363534;
	
	  ;% rtP.donotdeletethisgain_Gain
	  section.data(131).logicalSrcIdx = 133;
	  section.data(131).dtTransOffset = 363535;
	
	  ;% rtP.donotdeletethisgain_Gain_kzwtp4lcwh
	  section.data(132).logicalSrcIdx = 134;
	  section.data(132).dtTransOffset = 363536;
	
	  ;% rtP.donotdeletethisgain_Gain_jjlpkzumz0
	  section.data(133).logicalSrcIdx = 135;
	  section.data(133).dtTransOffset = 363537;
	
	  ;% rtP.DiscreteTimeIntegrator_gainval_figs31oe21
	  section.data(134).logicalSrcIdx = 136;
	  section.data(134).dtTransOffset = 363538;
	
	  ;% rtP.DiscreteTimeIntegrator_UpperSat
	  section.data(135).logicalSrcIdx = 137;
	  section.data(135).dtTransOffset = 363539;
	
	  ;% rtP.DiscreteTimeIntegrator_LowerSat
	  section.data(136).logicalSrcIdx = 138;
	  section.data(136).dtTransOffset = 363540;
	
	  ;% rtP.donotdeletethisgain_Gain_fbjp1xgx2i
	  section.data(137).logicalSrcIdx = 139;
	  section.data(137).dtTransOffset = 363541;
	
	  ;% rtP.Saturation2_UpperSat
	  section.data(138).logicalSrcIdx = 140;
	  section.data(138).dtTransOffset = 363542;
	
	  ;% rtP.Saturation2_LowerSat
	  section.data(139).logicalSrcIdx = 141;
	  section.data(139).dtTransOffset = 363543;
	
	  ;% rtP.DiscreteTimeIntegrator_gainval_k22hedow4a
	  section.data(140).logicalSrcIdx = 142;
	  section.data(140).dtTransOffset = 363544;
	
	  ;% rtP.DiscreteTimeIntegrator_UpperSat_j2u1431tvu
	  section.data(141).logicalSrcIdx = 143;
	  section.data(141).dtTransOffset = 363545;
	
	  ;% rtP.DiscreteTimeIntegrator_LowerSat_bvygkv3zts
	  section.data(142).logicalSrcIdx = 144;
	  section.data(142).dtTransOffset = 363546;
	
	  ;% rtP.donotdeletethisgain_Gain_pnt2zcpibt
	  section.data(143).logicalSrcIdx = 145;
	  section.data(143).dtTransOffset = 363547;
	
	  ;% rtP.DiscreteTimeIntegrator_gainval_jv55x3tqio
	  section.data(144).logicalSrcIdx = 146;
	  section.data(144).dtTransOffset = 363548;
	
	  ;% rtP.DiscreteTimeIntegrator_UpperSat_n2g2yvldpg
	  section.data(145).logicalSrcIdx = 147;
	  section.data(145).dtTransOffset = 363549;
	
	  ;% rtP.DiscreteTimeIntegrator_LowerSat_fv0zcc4hsa
	  section.data(146).logicalSrcIdx = 148;
	  section.data(146).dtTransOffset = 363550;
	
	  ;% rtP.Saturation2_UpperSat_hr00iu210k
	  section.data(147).logicalSrcIdx = 149;
	  section.data(147).dtTransOffset = 363551;
	
	  ;% rtP.Saturation2_LowerSat_kq0ryizxeu
	  section.data(148).logicalSrcIdx = 150;
	  section.data(148).dtTransOffset = 363552;
	
	  ;% rtP.Saturation7_UpperSat
	  section.data(149).logicalSrcIdx = 151;
	  section.data(149).dtTransOffset = 363553;
	
	  ;% rtP.Saturation7_LowerSat
	  section.data(150).logicalSrcIdx = 152;
	  section.data(150).dtTransOffset = 363554;
	
	  ;% rtP.donotdeletethisgain_Gain_pc1oacxtz5
	  section.data(151).logicalSrcIdx = 153;
	  section.data(151).dtTransOffset = 363555;
	
	  ;% rtP.Saturation4_UpperSat
	  section.data(152).logicalSrcIdx = 154;
	  section.data(152).dtTransOffset = 363556;
	
	  ;% rtP.Saturation4_LowerSat
	  section.data(153).logicalSrcIdx = 155;
	  section.data(153).dtTransOffset = 363557;
	
	  ;% rtP.Saturation2_UpperSat_csxykusiqi
	  section.data(154).logicalSrcIdx = 156;
	  section.data(154).dtTransOffset = 363558;
	
	  ;% rtP.Saturation2_LowerSat_djxegxbmlp
	  section.data(155).logicalSrcIdx = 157;
	  section.data(155).dtTransOffset = 363559;
	
	  ;% rtP.DiscreteTimeIntegrator_gainval_adna3qjceq
	  section.data(156).logicalSrcIdx = 158;
	  section.data(156).dtTransOffset = 363560;
	
	  ;% rtP.DiscreteTimeIntegrator_UpperSat_iu43zm3tho
	  section.data(157).logicalSrcIdx = 159;
	  section.data(157).dtTransOffset = 363561;
	
	  ;% rtP.DiscreteTimeIntegrator_LowerSat_bdtob5uhem
	  section.data(158).logicalSrcIdx = 160;
	  section.data(158).dtTransOffset = 363562;
	
	  ;% rtP.Saturation2_UpperSat_ldjga0hth1
	  section.data(159).logicalSrcIdx = 161;
	  section.data(159).dtTransOffset = 363563;
	
	  ;% rtP.Saturation2_LowerSat_ebdt35gruq
	  section.data(160).logicalSrcIdx = 162;
	  section.data(160).dtTransOffset = 363564;
	
	  ;% rtP.DiscreteTimeIntegrator_gainval_djg22thboz
	  section.data(161).logicalSrcIdx = 163;
	  section.data(161).dtTransOffset = 363565;
	
	  ;% rtP.DiscreteTimeIntegrator_UpperSat_k2jkcmkhdm
	  section.data(162).logicalSrcIdx = 164;
	  section.data(162).dtTransOffset = 363566;
	
	  ;% rtP.DiscreteTimeIntegrator_LowerSat_gmrhfgoeip
	  section.data(163).logicalSrcIdx = 165;
	  section.data(163).dtTransOffset = 363567;
	
	  ;% rtP.Multiply_Gain_dppzkzoubi
	  section.data(164).logicalSrcIdx = 166;
	  section.data(164).dtTransOffset = 363568;
	
	  ;% rtP.Saturation6_UpperSat
	  section.data(165).logicalSrcIdx = 167;
	  section.data(165).dtTransOffset = 363569;
	
	  ;% rtP.Saturation6_LowerSat
	  section.data(166).logicalSrcIdx = 168;
	  section.data(166).dtTransOffset = 363570;
	
	  ;% rtP.Saturation2_UpperSat_pjhhcyvloo
	  section.data(167).logicalSrcIdx = 169;
	  section.data(167).dtTransOffset = 363571;
	
	  ;% rtP.Saturation2_LowerSat_j0yt25ma5v
	  section.data(168).logicalSrcIdx = 170;
	  section.data(168).dtTransOffset = 363572;
	
	  ;% rtP.Saturation_UpperSat_jsjpgzsi1y
	  section.data(169).logicalSrcIdx = 171;
	  section.data(169).dtTransOffset = 363573;
	
	  ;% rtP.Saturation_LowerSat_ebjhnxsenp
	  section.data(170).logicalSrcIdx = 172;
	  section.data(170).dtTransOffset = 363574;
	
	  ;% rtP.Saturation2_UpperSat_amgcitvjo2
	  section.data(171).logicalSrcIdx = 173;
	  section.data(171).dtTransOffset = 363575;
	
	  ;% rtP.Saturation2_LowerSat_lkim1nsn2b
	  section.data(172).logicalSrcIdx = 174;
	  section.data(172).dtTransOffset = 363576;
	
	  ;% rtP.Saturation1_UpperSat
	  section.data(173).logicalSrcIdx = 175;
	  section.data(173).dtTransOffset = 363577;
	
	  ;% rtP.Saturation1_LowerSat
	  section.data(174).logicalSrcIdx = 176;
	  section.data(174).dtTransOffset = 363578;
	
	  ;% rtP.Saturation3_UpperSat
	  section.data(175).logicalSrcIdx = 177;
	  section.data(175).dtTransOffset = 363579;
	
	  ;% rtP.Saturation3_LowerSat
	  section.data(176).logicalSrcIdx = 178;
	  section.data(176).dtTransOffset = 363580;
	
	  ;% rtP.donotdeletethisgain_Gain_fiwukkn2yr
	  section.data(177).logicalSrcIdx = 179;
	  section.data(177).dtTransOffset = 363581;
	
	  ;% rtP.donotdeletethisgain_Gain_bnrrpg33he
	  section.data(178).logicalSrcIdx = 180;
	  section.data(178).dtTransOffset = 363582;
	
	  ;% rtP.DiscreteTimeIntegrator_gainval_cdol2y5vzn
	  section.data(179).logicalSrcIdx = 181;
	  section.data(179).dtTransOffset = 363583;
	
	  ;% rtP.DiscreteTimeIntegrator_UpperSat_hfo2y053hj
	  section.data(180).logicalSrcIdx = 182;
	  section.data(180).dtTransOffset = 363584;
	
	  ;% rtP.DiscreteTimeIntegrator_LowerSat_c0vq2ip5xz
	  section.data(181).logicalSrcIdx = 183;
	  section.data(181).dtTransOffset = 363585;
	
	  ;% rtP.donotdeletethisgain_Gain_hbuypofava
	  section.data(182).logicalSrcIdx = 184;
	  section.data(182).dtTransOffset = 363586;
	
	  ;% rtP.donotdeletethisgain_Gain_ebxbsb35rt
	  section.data(183).logicalSrcIdx = 185;
	  section.data(183).dtTransOffset = 363587;
	
	  ;% rtP.Multiply2_Gain
	  section.data(184).logicalSrcIdx = 186;
	  section.data(184).dtTransOffset = 363588;
	
	  ;% rtP.R4_Gain
	  section.data(185).logicalSrcIdx = 187;
	  section.data(185).dtTransOffset = 363589;
	
	  ;% rtP.Saturation_UpperSat_ms3dxtbvew
	  section.data(186).logicalSrcIdx = 188;
	  section.data(186).dtTransOffset = 363590;
	
	  ;% rtP.Saturation_LowerSat_p3nlfvz151
	  section.data(187).logicalSrcIdx = 189;
	  section.data(187).dtTransOffset = 363591;
	
	  ;% rtP.Multiply3_Gain
	  section.data(188).logicalSrcIdx = 190;
	  section.data(188).dtTransOffset = 363592;
	
	  ;% rtP.donotdeletethisgain_Gain_liz3gjfhcs
	  section.data(189).logicalSrcIdx = 191;
	  section.data(189).dtTransOffset = 363593;
	
	  ;% rtP.donotdeletethisgain_Gain_ntvbbpumog
	  section.data(190).logicalSrcIdx = 192;
	  section.data(190).dtTransOffset = 363594;
	
	  ;% rtP.Saturation2_UpperSat_fkd04pf2k1
	  section.data(191).logicalSrcIdx = 193;
	  section.data(191).dtTransOffset = 363595;
	
	  ;% rtP.Saturation2_LowerSat_mzohmr2g2n
	  section.data(192).logicalSrcIdx = 194;
	  section.data(192).dtTransOffset = 363596;
	
	  ;% rtP.DiscreteTimeIntegrator_gainval_cqdxvpityq
	  section.data(193).logicalSrcIdx = 195;
	  section.data(193).dtTransOffset = 363597;
	
	  ;% rtP.DiscreteTimeIntegrator_UpperSat_bbsxbmka10
	  section.data(194).logicalSrcIdx = 196;
	  section.data(194).dtTransOffset = 363598;
	
	  ;% rtP.DiscreteTimeIntegrator_LowerSat_fbeqnj3sm1
	  section.data(195).logicalSrcIdx = 197;
	  section.data(195).dtTransOffset = 363599;
	
	  ;% rtP.donotdeletethisgain_Gain_mnd4o03d53
	  section.data(196).logicalSrcIdx = 198;
	  section.data(196).dtTransOffset = 363600;
	
	  ;% rtP.Saturation2_UpperSat_aip5hjdd2y
	  section.data(197).logicalSrcIdx = 199;
	  section.data(197).dtTransOffset = 363601;
	
	  ;% rtP.Saturation2_LowerSat_czr0zyeyrx
	  section.data(198).logicalSrcIdx = 200;
	  section.data(198).dtTransOffset = 363602;
	
	  ;% rtP.Saturation2_UpperSat_kim5qyxfwz
	  section.data(199).logicalSrcIdx = 201;
	  section.data(199).dtTransOffset = 363603;
	
	  ;% rtP.Saturation2_LowerSat_dlfntvjpxg
	  section.data(200).logicalSrcIdx = 202;
	  section.data(200).dtTransOffset = 363604;
	
	  ;% rtP.Saturation_UpperSat_e2l0llad23
	  section.data(201).logicalSrcIdx = 203;
	  section.data(201).dtTransOffset = 363605;
	
	  ;% rtP.Saturation_LowerSat_daenvoeirh
	  section.data(202).logicalSrcIdx = 204;
	  section.data(202).dtTransOffset = 363606;
	
	  ;% rtP.Saturation1_UpperSat_ix0yodnig1
	  section.data(203).logicalSrcIdx = 205;
	  section.data(203).dtTransOffset = 363607;
	
	  ;% rtP.Saturation1_LowerSat_nfi0d0pja5
	  section.data(204).logicalSrcIdx = 206;
	  section.data(204).dtTransOffset = 363608;
	
	  ;% rtP.donotdeletethisgain_Gain_bvblu5w4wa
	  section.data(205).logicalSrcIdx = 207;
	  section.data(205).dtTransOffset = 363609;
	
	  ;% rtP.donotdeletethisgain_Gain_e2kry42snu
	  section.data(206).logicalSrcIdx = 208;
	  section.data(206).dtTransOffset = 363610;
	
	  ;% rtP.Memory_InitialCondition
	  section.data(207).logicalSrcIdx = 209;
	  section.data(207).dtTransOffset = 363611;
	
	  ;% rtP.Memory17_InitialCondition
	  section.data(208).logicalSrcIdx = 210;
	  section.data(208).dtTransOffset = 363612;
	
	  ;% rtP.Memory16_InitialCondition
	  section.data(209).logicalSrcIdx = 211;
	  section.data(209).dtTransOffset = 363613;
	
	  ;% rtP.Memory15_InitialCondition
	  section.data(210).logicalSrcIdx = 212;
	  section.data(210).dtTransOffset = 363614;
	
	  ;% rtP.Memory14_InitialCondition
	  section.data(211).logicalSrcIdx = 213;
	  section.data(211).dtTransOffset = 363615;
	
	  ;% rtP.Memory13_InitialCondition
	  section.data(212).logicalSrcIdx = 214;
	  section.data(212).dtTransOffset = 363616;
	
	  ;% rtP.Memory12_InitialCondition
	  section.data(213).logicalSrcIdx = 215;
	  section.data(213).dtTransOffset = 363617;
	
	  ;% rtP.Memory11_InitialCondition
	  section.data(214).logicalSrcIdx = 216;
	  section.data(214).dtTransOffset = 363618;
	
	  ;% rtP.Memory10_InitialCondition
	  section.data(215).logicalSrcIdx = 217;
	  section.data(215).dtTransOffset = 363619;
	
	  ;% rtP.Memory9_InitialCondition
	  section.data(216).logicalSrcIdx = 218;
	  section.data(216).dtTransOffset = 363620;
	
	  ;% rtP.Memory7_InitialCondition
	  section.data(217).logicalSrcIdx = 219;
	  section.data(217).dtTransOffset = 363621;
	
	  ;% rtP.Memory6_InitialCondition
	  section.data(218).logicalSrcIdx = 220;
	  section.data(218).dtTransOffset = 363622;
	
	  ;% rtP.Memory5_InitialCondition
	  section.data(219).logicalSrcIdx = 221;
	  section.data(219).dtTransOffset = 363623;
	
	  ;% rtP.Memory4_InitialCondition
	  section.data(220).logicalSrcIdx = 222;
	  section.data(220).dtTransOffset = 363624;
	
	  ;% rtP.Memory3_InitialCondition
	  section.data(221).logicalSrcIdx = 223;
	  section.data(221).dtTransOffset = 363625;
	
	  ;% rtP.Memory2_InitialCondition_nmqdt3zohg
	  section.data(222).logicalSrcIdx = 224;
	  section.data(222).dtTransOffset = 363626;
	
	  ;% rtP.Memory1_InitialCondition
	  section.data(223).logicalSrcIdx = 225;
	  section.data(223).dtTransOffset = 363627;
	
	  ;% rtP.Memory_InitialCondition_fgdsbtcau2
	  section.data(224).logicalSrcIdx = 226;
	  section.data(224).dtTransOffset = 363628;
	
	  ;% rtP.Saturation_UpperSat_ip0sfxxemb
	  section.data(225).logicalSrcIdx = 227;
	  section.data(225).dtTransOffset = 363629;
	
	  ;% rtP.Saturation_LowerSat_oc4mpky1ii
	  section.data(226).logicalSrcIdx = 228;
	  section.data(226).dtTransOffset = 363630;
	
	  ;% rtP.Saturation1_UpperSat_hftla4v5jl
	  section.data(227).logicalSrcIdx = 229;
	  section.data(227).dtTransOffset = 363631;
	
	  ;% rtP.Saturation1_LowerSat_mlv0levcl5
	  section.data(228).logicalSrcIdx = 230;
	  section.data(228).dtTransOffset = 363632;
	
	  ;% rtP.Saturation2_UpperSat_fd3ezm0unh
	  section.data(229).logicalSrcIdx = 231;
	  section.data(229).dtTransOffset = 363633;
	
	  ;% rtP.Saturation2_LowerSat_a0oq1v4uhe
	  section.data(230).logicalSrcIdx = 232;
	  section.data(230).dtTransOffset = 363634;
	
	  ;% rtP.Memory3_InitialCondition_npuv0s0rz0
	  section.data(231).logicalSrcIdx = 233;
	  section.data(231).dtTransOffset = 363635;
	
	  ;% rtP.Saturation_UpperSat_hsf1hlgzdw
	  section.data(232).logicalSrcIdx = 234;
	  section.data(232).dtTransOffset = 363636;
	
	  ;% rtP.Saturation_LowerSat_peon1dscjc
	  section.data(233).logicalSrcIdx = 235;
	  section.data(233).dtTransOffset = 363637;
	
	  ;% rtP.Saturation1_UpperSat_joqzp4lauk
	  section.data(234).logicalSrcIdx = 236;
	  section.data(234).dtTransOffset = 363638;
	
	  ;% rtP.Saturation1_LowerSat_cp5xe3rdvj
	  section.data(235).logicalSrcIdx = 237;
	  section.data(235).dtTransOffset = 363639;
	
	  ;% rtP.Saturation2_UpperSat_lknfecgs12
	  section.data(236).logicalSrcIdx = 238;
	  section.data(236).dtTransOffset = 363640;
	
	  ;% rtP.Saturation2_LowerSat_djkw5ghtjz
	  section.data(237).logicalSrcIdx = 239;
	  section.data(237).dtTransOffset = 363641;
	
	  ;% rtP.Memory2_InitialCondition_otmdfxbv2b
	  section.data(238).logicalSrcIdx = 240;
	  section.data(238).dtTransOffset = 363642;
	
	  ;% rtP.Memory1_InitialCondition_eyxrd3us35
	  section.data(239).logicalSrcIdx = 241;
	  section.data(239).dtTransOffset = 363643;
	
	  ;% rtP.Memory_InitialCondition_afcza04ewo
	  section.data(240).logicalSrcIdx = 242;
	  section.data(240).dtTransOffset = 363644;
	
	  ;% rtP.itinit1_InitialCondition
	  section.data(241).logicalSrcIdx = 243;
	  section.data(241).dtTransOffset = 363645;
	
	  ;% rtP.Gain4_Gain
	  section.data(242).logicalSrcIdx = 244;
	  section.data(242).dtTransOffset = 363646;
	
	  ;% rtP.Gain1_Gain
	  section.data(243).logicalSrcIdx = 245;
	  section.data(243).dtTransOffset = 363647;
	
	  ;% rtP.Gain2_Gain
	  section.data(244).logicalSrcIdx = 246;
	  section.data(244).dtTransOffset = 363648;
	
	  ;% rtP.R1_Gain
	  section.data(245).logicalSrcIdx = 247;
	  section.data(245).dtTransOffset = 363649;
	
	  ;% rtP.Multiply_Gain_ghq4r0q5k3
	  section.data(246).logicalSrcIdx = 248;
	  section.data(246).dtTransOffset = 363650;
	
	  ;% rtP.Multiply1_Gain
	  section.data(247).logicalSrcIdx = 249;
	  section.data(247).dtTransOffset = 363651;
	
	  ;% rtP.donotdeletethisgain_Gain_nzzshfnxdx
	  section.data(248).logicalSrcIdx = 250;
	  section.data(248).dtTransOffset = 363652;
	
	  ;% rtP.DiscreteTimeIntegrator_gainval_fhcrjdv1um
	  section.data(249).logicalSrcIdx = 251;
	  section.data(249).dtTransOffset = 363653;
	
	  ;% rtP.DiscreteTimeIntegrator_IC_muc3fdmls2
	  section.data(250).logicalSrcIdx = 252;
	  section.data(250).dtTransOffset = 363654;
	
	  ;% rtP.UnitDelay2_InitialCondition_bdexezlukf
	  section.data(251).logicalSrcIdx = 253;
	  section.data(251).dtTransOffset = 363655;
	
	  ;% rtP.UnitDelay_InitialCondition_br0av5wkrv
	  section.data(252).logicalSrcIdx = 254;
	  section.data(252).dtTransOffset = 363656;
	
	  ;% rtP.DiscreteTimeIntegrator1_gainval
	  section.data(253).logicalSrcIdx = 255;
	  section.data(253).dtTransOffset = 363657;
	
	  ;% rtP.DiscreteTimeIntegrator1_IC
	  section.data(254).logicalSrcIdx = 256;
	  section.data(254).dtTransOffset = 363658;
	
	  ;% rtP.Gain_Gain_duepg35cnl
	  section.data(255).logicalSrcIdx = 257;
	  section.data(255).dtTransOffset = 363659;
	
	  ;% rtP.donotdeletethisgain_Gain_ghiynr5jt3
	  section.data(256).logicalSrcIdx = 258;
	  section.data(256).dtTransOffset = 363660;
	
	  ;% rtP.UnitDelay1_InitialCondition_gagfd2xjhh
	  section.data(257).logicalSrcIdx = 259;
	  section.data(257).dtTransOffset = 363661;
	
	  ;% rtP.Saturation1_UpperSat_jbsy2jdb2e
	  section.data(258).logicalSrcIdx = 260;
	  section.data(258).dtTransOffset = 363662;
	
	  ;% rtP.Saturation1_LowerSat_km3pw1r5au
	  section.data(259).logicalSrcIdx = 261;
	  section.data(259).dtTransOffset = 363663;
	
	  ;% rtP.donotdeletethisgain_Gain_l30jrki0pa
	  section.data(260).logicalSrcIdx = 262;
	  section.data(260).dtTransOffset = 363664;
	
	  ;% rtP.donotdeletethisgain_Gain_m3s0jpprkc
	  section.data(261).logicalSrcIdx = 263;
	  section.data(261).dtTransOffset = 363665;
	
	  ;% rtP.donotdeletethisgain_Gain_hoplgufukg
	  section.data(262).logicalSrcIdx = 264;
	  section.data(262).dtTransOffset = 363666;
	
	  ;% rtP.donotdeletethisgain_Gain_hqauyrnmgx
	  section.data(263).logicalSrcIdx = 265;
	  section.data(263).dtTransOffset = 363667;
	
	  ;% rtP.SwitchCurrents_Value
	  section.data(264).logicalSrcIdx = 266;
	  section.data(264).dtTransOffset = 363668;
	
	  ;% rtP.Constant_Value_ffncqspxq4
	  section.data(265).logicalSrcIdx = 267;
	  section.data(265).dtTransOffset = 363680;
	
	  ;% rtP.Constant1_Value
	  section.data(266).logicalSrcIdx = 268;
	  section.data(266).dtTransOffset = 363681;
	
	  ;% rtP.Constant2_Value
	  section.data(267).logicalSrcIdx = 269;
	  section.data(267).dtTransOffset = 363682;
	
	  ;% rtP.Constant3_Value
	  section.data(268).logicalSrcIdx = 270;
	  section.data(268).dtTransOffset = 363683;
	
	  ;% rtP.Constant_Value_jrk1wafdx5
	  section.data(269).logicalSrcIdx = 271;
	  section.data(269).dtTransOffset = 363684;
	
	  ;% rtP.Constant1_Value_avw5uhdxx5
	  section.data(270).logicalSrcIdx = 272;
	  section.data(270).dtTransOffset = 363685;
	
	  ;% rtP.Constant5_Value
	  section.data(271).logicalSrcIdx = 273;
	  section.data(271).dtTransOffset = 363686;
	
	  ;% rtP.Constant6_Value
	  section.data(272).logicalSrcIdx = 274;
	  section.data(272).dtTransOffset = 363687;
	
	  ;% rtP.Constant_Value_nct1bh10mh
	  section.data(273).logicalSrcIdx = 275;
	  section.data(273).dtTransOffset = 363688;
	
	  ;% rtP.Constant1_Value_aacpe0p2s4
	  section.data(274).logicalSrcIdx = 276;
	  section.data(274).dtTransOffset = 363689;
	
	  ;% rtP.Constant_Value_m3ckpdnl3e
	  section.data(275).logicalSrcIdx = 277;
	  section.data(275).dtTransOffset = 363690;
	
	  ;% rtP.Constant1_Value_bcnppbahb4
	  section.data(276).logicalSrcIdx = 278;
	  section.data(276).dtTransOffset = 363691;
	
	  ;% rtP.Constant12_Value
	  section.data(277).logicalSrcIdx = 279;
	  section.data(277).dtTransOffset = 363692;
	
	  ;% rtP.Constant14_Value
	  section.data(278).logicalSrcIdx = 280;
	  section.data(278).dtTransOffset = 363693;
	
	  ;% rtP.Constant8_Value
	  section.data(279).logicalSrcIdx = 281;
	  section.data(279).dtTransOffset = 363694;
	
	  ;% rtP.Constant9_Value
	  section.data(280).logicalSrcIdx = 282;
	  section.data(280).dtTransOffset = 363695;
	
	  ;% rtP.Constant1_Value_ixcqqm1d4w
	  section.data(281).logicalSrcIdx = 283;
	  section.data(281).dtTransOffset = 363696;
	
	  ;% rtP.Constant2_Value_m10aoab32w
	  section.data(282).logicalSrcIdx = 284;
	  section.data(282).dtTransOffset = 363697;
	
	  ;% rtP.Constant3_Value_nmyyw0epx1
	  section.data(283).logicalSrcIdx = 285;
	  section.data(283).dtTransOffset = 363698;
	
	  ;% rtP.Constant4_Value
	  section.data(284).logicalSrcIdx = 286;
	  section.data(284).dtTransOffset = 363699;
	
	  ;% rtP.Ta_Value
	  section.data(285).logicalSrcIdx = 287;
	  section.data(285).dtTransOffset = 363700;
	
	  ;% rtP.Constant_Value_embijewti4
	  section.data(286).logicalSrcIdx = 288;
	  section.data(286).dtTransOffset = 363701;
	
	  ;% rtP.Constant1_Value_f3txfozlof
	  section.data(287).logicalSrcIdx = 289;
	  section.data(287).dtTransOffset = 363702;
	
	  ;% rtP.Constant3_Value_cnmqtz2p2n
	  section.data(288).logicalSrcIdx = 290;
	  section.data(288).dtTransOffset = 363703;
	
	  ;% rtP.Constant4_Value_chdfctpggi
	  section.data(289).logicalSrcIdx = 291;
	  section.data(289).dtTransOffset = 363704;
	
	  ;% rtP.Constant7_Value
	  section.data(290).logicalSrcIdx = 292;
	  section.data(290).dtTransOffset = 363705;
	
	  ;% rtP.Constant8_Value_iqk3wb1evy
	  section.data(291).logicalSrcIdx = 293;
	  section.data(291).dtTransOffset = 363706;
	
	  ;% rtP.Constant_Value_kfm5xzok4i
	  section.data(292).logicalSrcIdx = 294;
	  section.data(292).dtTransOffset = 363707;
	
	  ;% rtP.Constant19_Value
	  section.data(293).logicalSrcIdx = 295;
	  section.data(293).dtTransOffset = 363708;
	
	  ;% rtP.Constant1_Value_lfvx2nwcp2
	  section.data(294).logicalSrcIdx = 296;
	  section.data(294).dtTransOffset = 363709;
	
	  ;% rtP.Constant2_Value_krq4yfjnno
	  section.data(295).logicalSrcIdx = 297;
	  section.data(295).dtTransOffset = 363710;
	
	  ;% rtP.Constant3_Value_acddb2uoov
	  section.data(296).logicalSrcIdx = 298;
	  section.data(296).dtTransOffset = 363711;
	
	  ;% rtP.Constant4_Value_fthefd0get
	  section.data(297).logicalSrcIdx = 299;
	  section.data(297).dtTransOffset = 363712;
	
	  ;% rtP.Constant_Value_oibu00r03f
	  section.data(298).logicalSrcIdx = 300;
	  section.data(298).dtTransOffset = 363713;
	
	  ;% rtP.Constant1_Value_ktzhc0x1wo
	  section.data(299).logicalSrcIdx = 301;
	  section.data(299).dtTransOffset = 363714;
	
	  ;% rtP.Constant2_Value_d2yksltlle
	  section.data(300).logicalSrcIdx = 302;
	  section.data(300).dtTransOffset = 363715;
	
	  ;% rtP.Constant10_Value
	  section.data(301).logicalSrcIdx = 303;
	  section.data(301).dtTransOffset = 363716;
	
	  ;% rtP.Constant9_Value_b1nk1ggw4w
	  section.data(302).logicalSrcIdx = 304;
	  section.data(302).dtTransOffset = 363717;
	
	  ;% rtP.Constant5_Value_k3metw3ccu
	  section.data(303).logicalSrcIdx = 305;
	  section.data(303).dtTransOffset = 363718;
	
	  ;% rtP.eee_Value
	  section.data(304).logicalSrcIdx = 306;
	  section.data(304).dtTransOffset = 363719;
	
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
      section.nData     = 92;
      section.data(92)  = dumData; %prealloc
      
	  ;% rtB.nzprtrw2gw
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtB.klfwarvagc
	  section.data(2).logicalSrcIdx = 2;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtB.i0ujncnh35
	  section.data(3).logicalSrcIdx = 3;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtB.dplapzekhr
	  section.data(4).logicalSrcIdx = 4;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtB.b2m0nyy1iq
	  section.data(5).logicalSrcIdx = 5;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtB.dg1zqpobap
	  section.data(6).logicalSrcIdx = 6;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtB.m2zun0bmq0
	  section.data(7).logicalSrcIdx = 7;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtB.bnsiwqbz4c
	  section.data(8).logicalSrcIdx = 8;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtB.nd5vhw3hdp
	  section.data(9).logicalSrcIdx = 9;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtB.pkslvtv3r5
	  section.data(10).logicalSrcIdx = 10;
	  section.data(10).dtTransOffset = 9;
	
	  ;% rtB.mdng4h4wi3
	  section.data(11).logicalSrcIdx = 11;
	  section.data(11).dtTransOffset = 10;
	
	  ;% rtB.akgc550kdx
	  section.data(12).logicalSrcIdx = 12;
	  section.data(12).dtTransOffset = 11;
	
	  ;% rtB.aunoa00r4h
	  section.data(13).logicalSrcIdx = 13;
	  section.data(13).dtTransOffset = 12;
	
	  ;% rtB.ds4vmpgjgq
	  section.data(14).logicalSrcIdx = 14;
	  section.data(14).dtTransOffset = 13;
	
	  ;% rtB.aprtxoz0cz
	  section.data(15).logicalSrcIdx = 15;
	  section.data(15).dtTransOffset = 51;
	
	  ;% rtB.dsl30exhdf
	  section.data(16).logicalSrcIdx = 16;
	  section.data(16).dtTransOffset = 63;
	
	  ;% rtB.lwbnk1tqoe
	  section.data(17).logicalSrcIdx = 17;
	  section.data(17).dtTransOffset = 64;
	
	  ;% rtB.lnggl4hxqa
	  section.data(18).logicalSrcIdx = 18;
	  section.data(18).dtTransOffset = 65;
	
	  ;% rtB.cnvh3z11oj
	  section.data(19).logicalSrcIdx = 19;
	  section.data(19).dtTransOffset = 66;
	
	  ;% rtB.caydqvbppv
	  section.data(20).logicalSrcIdx = 20;
	  section.data(20).dtTransOffset = 67;
	
	  ;% rtB.kx2yvfrvbs
	  section.data(21).logicalSrcIdx = 21;
	  section.data(21).dtTransOffset = 68;
	
	  ;% rtB.i4u1u0nk00
	  section.data(22).logicalSrcIdx = 22;
	  section.data(22).dtTransOffset = 69;
	
	  ;% rtB.npdclyuhqf
	  section.data(23).logicalSrcIdx = 23;
	  section.data(23).dtTransOffset = 70;
	
	  ;% rtB.jqk43gypqg
	  section.data(24).logicalSrcIdx = 24;
	  section.data(24).dtTransOffset = 71;
	
	  ;% rtB.pkp0sjqqg3
	  section.data(25).logicalSrcIdx = 25;
	  section.data(25).dtTransOffset = 72;
	
	  ;% rtB.iuiyd4knlc
	  section.data(26).logicalSrcIdx = 26;
	  section.data(26).dtTransOffset = 73;
	
	  ;% rtB.bbivpaarxt
	  section.data(27).logicalSrcIdx = 27;
	  section.data(27).dtTransOffset = 74;
	
	  ;% rtB.nh1zxcsjip
	  section.data(28).logicalSrcIdx = 28;
	  section.data(28).dtTransOffset = 75;
	
	  ;% rtB.gvxuq2ivcx
	  section.data(29).logicalSrcIdx = 29;
	  section.data(29).dtTransOffset = 76;
	
	  ;% rtB.evwgggutgq
	  section.data(30).logicalSrcIdx = 30;
	  section.data(30).dtTransOffset = 77;
	
	  ;% rtB.pd50rghzbf
	  section.data(31).logicalSrcIdx = 31;
	  section.data(31).dtTransOffset = 78;
	
	  ;% rtB.k4spxtemch
	  section.data(32).logicalSrcIdx = 32;
	  section.data(32).dtTransOffset = 79;
	
	  ;% rtB.oaypl0xy40
	  section.data(33).logicalSrcIdx = 33;
	  section.data(33).dtTransOffset = 80;
	
	  ;% rtB.hejghjylpf
	  section.data(34).logicalSrcIdx = 34;
	  section.data(34).dtTransOffset = 81;
	
	  ;% rtB.lkdpawgj3d
	  section.data(35).logicalSrcIdx = 35;
	  section.data(35).dtTransOffset = 82;
	
	  ;% rtB.jqrtcbjb0q
	  section.data(36).logicalSrcIdx = 36;
	  section.data(36).dtTransOffset = 83;
	
	  ;% rtB.bsiskimpq4
	  section.data(37).logicalSrcIdx = 37;
	  section.data(37).dtTransOffset = 85;
	
	  ;% rtB.k04sqjkmui
	  section.data(38).logicalSrcIdx = 38;
	  section.data(38).dtTransOffset = 86;
	
	  ;% rtB.jpdjo1yg5c
	  section.data(39).logicalSrcIdx = 39;
	  section.data(39).dtTransOffset = 87;
	
	  ;% rtB.aoywj0c0aw
	  section.data(40).logicalSrcIdx = 40;
	  section.data(40).dtTransOffset = 88;
	
	  ;% rtB.gswcpufwfm
	  section.data(41).logicalSrcIdx = 41;
	  section.data(41).dtTransOffset = 89;
	
	  ;% rtB.nfrcslok3r
	  section.data(42).logicalSrcIdx = 42;
	  section.data(42).dtTransOffset = 90;
	
	  ;% rtB.bp13llqzit
	  section.data(43).logicalSrcIdx = 43;
	  section.data(43).dtTransOffset = 91;
	
	  ;% rtB.b0ihg4ev5s
	  section.data(44).logicalSrcIdx = 44;
	  section.data(44).dtTransOffset = 92;
	
	  ;% rtB.aljtveo2dl
	  section.data(45).logicalSrcIdx = 45;
	  section.data(45).dtTransOffset = 93;
	
	  ;% rtB.jr2i1iijlv
	  section.data(46).logicalSrcIdx = 46;
	  section.data(46).dtTransOffset = 94;
	
	  ;% rtB.in3foousin
	  section.data(47).logicalSrcIdx = 47;
	  section.data(47).dtTransOffset = 95;
	
	  ;% rtB.pu2uj4duj0
	  section.data(48).logicalSrcIdx = 48;
	  section.data(48).dtTransOffset = 96;
	
	  ;% rtB.dn4cfjoyu3
	  section.data(49).logicalSrcIdx = 49;
	  section.data(49).dtTransOffset = 97;
	
	  ;% rtB.ee4dkbgmbt
	  section.data(50).logicalSrcIdx = 50;
	  section.data(50).dtTransOffset = 98;
	
	  ;% rtB.a3xn5q0qbv
	  section.data(51).logicalSrcIdx = 51;
	  section.data(51).dtTransOffset = 99;
	
	  ;% rtB.d2aecp5kgr
	  section.data(52).logicalSrcIdx = 52;
	  section.data(52).dtTransOffset = 100;
	
	  ;% rtB.cataaai4vr
	  section.data(53).logicalSrcIdx = 53;
	  section.data(53).dtTransOffset = 101;
	
	  ;% rtB.glbb5pdj1b
	  section.data(54).logicalSrcIdx = 54;
	  section.data(54).dtTransOffset = 102;
	
	  ;% rtB.i5qlxhsaeo
	  section.data(55).logicalSrcIdx = 55;
	  section.data(55).dtTransOffset = 103;
	
	  ;% rtB.nw10mpmiwb
	  section.data(56).logicalSrcIdx = 56;
	  section.data(56).dtTransOffset = 104;
	
	  ;% rtB.dsv2bbs0k1
	  section.data(57).logicalSrcIdx = 57;
	  section.data(57).dtTransOffset = 105;
	
	  ;% rtB.oaxo1bryj0
	  section.data(58).logicalSrcIdx = 58;
	  section.data(58).dtTransOffset = 106;
	
	  ;% rtB.mnnico2kpm
	  section.data(59).logicalSrcIdx = 59;
	  section.data(59).dtTransOffset = 118;
	
	  ;% rtB.ju3eqofxsv
	  section.data(60).logicalSrcIdx = 60;
	  section.data(60).dtTransOffset = 119;
	
	  ;% rtB.nkylddyjyp
	  section.data(61).logicalSrcIdx = 61;
	  section.data(61).dtTransOffset = 120;
	
	  ;% rtB.aqkf223m44
	  section.data(62).logicalSrcIdx = 62;
	  section.data(62).dtTransOffset = 121;
	
	  ;% rtB.b11tooymbq
	  section.data(63).logicalSrcIdx = 63;
	  section.data(63).dtTransOffset = 122;
	
	  ;% rtB.gpw42pjoku
	  section.data(64).logicalSrcIdx = 64;
	  section.data(64).dtTransOffset = 123;
	
	  ;% rtB.ftivrztnav
	  section.data(65).logicalSrcIdx = 65;
	  section.data(65).dtTransOffset = 124;
	
	  ;% rtB.cp1s511zvk
	  section.data(66).logicalSrcIdx = 66;
	  section.data(66).dtTransOffset = 125;
	
	  ;% rtB.pmkgps0zyu
	  section.data(67).logicalSrcIdx = 67;
	  section.data(67).dtTransOffset = 126;
	
	  ;% rtB.crs0im5dqp
	  section.data(68).logicalSrcIdx = 68;
	  section.data(68).dtTransOffset = 127;
	
	  ;% rtB.ktal25amyn
	  section.data(69).logicalSrcIdx = 69;
	  section.data(69).dtTransOffset = 128;
	
	  ;% rtB.e2chijmfh2
	  section.data(70).logicalSrcIdx = 70;
	  section.data(70).dtTransOffset = 129;
	
	  ;% rtB.ajuoykrpve
	  section.data(71).logicalSrcIdx = 71;
	  section.data(71).dtTransOffset = 130;
	
	  ;% rtB.orc5wcdxm1
	  section.data(72).logicalSrcIdx = 72;
	  section.data(72).dtTransOffset = 131;
	
	  ;% rtB.akwd4yohpb
	  section.data(73).logicalSrcIdx = 73;
	  section.data(73).dtTransOffset = 132;
	
	  ;% rtB.hwgkbedju4
	  section.data(74).logicalSrcIdx = 74;
	  section.data(74).dtTransOffset = 133;
	
	  ;% rtB.akgbctleuf
	  section.data(75).logicalSrcIdx = 75;
	  section.data(75).dtTransOffset = 134;
	
	  ;% rtB.fjva4ba3yf
	  section.data(76).logicalSrcIdx = 76;
	  section.data(76).dtTransOffset = 135;
	
	  ;% rtB.ojpp3hq5ld
	  section.data(77).logicalSrcIdx = 77;
	  section.data(77).dtTransOffset = 136;
	
	  ;% rtB.ddwaerj1qf
	  section.data(78).logicalSrcIdx = 78;
	  section.data(78).dtTransOffset = 137;
	
	  ;% rtB.e4esbiadth
	  section.data(79).logicalSrcIdx = 79;
	  section.data(79).dtTransOffset = 138;
	
	  ;% rtB.dv32o2egzr
	  section.data(80).logicalSrcIdx = 80;
	  section.data(80).dtTransOffset = 139;
	
	  ;% rtB.b1fl12txsf
	  section.data(81).logicalSrcIdx = 81;
	  section.data(81).dtTransOffset = 140;
	
	  ;% rtB.liwqgy4ofb
	  section.data(82).logicalSrcIdx = 82;
	  section.data(82).dtTransOffset = 141;
	
	  ;% rtB.cf3awerlht
	  section.data(83).logicalSrcIdx = 83;
	  section.data(83).dtTransOffset = 142;
	
	  ;% rtB.o0lhjiunqy
	  section.data(84).logicalSrcIdx = 84;
	  section.data(84).dtTransOffset = 143;
	
	  ;% rtB.i4esmxfcaq
	  section.data(85).logicalSrcIdx = 85;
	  section.data(85).dtTransOffset = 144;
	
	  ;% rtB.ewvuxv0roa
	  section.data(86).logicalSrcIdx = 86;
	  section.data(86).dtTransOffset = 145;
	
	  ;% rtB.frtehkabsr
	  section.data(87).logicalSrcIdx = 87;
	  section.data(87).dtTransOffset = 146;
	
	  ;% rtB.paaipnyjy4
	  section.data(88).logicalSrcIdx = 88;
	  section.data(88).dtTransOffset = 147;
	
	  ;% rtB.ctjnl3duhv
	  section.data(89).logicalSrcIdx = 89;
	  section.data(89).dtTransOffset = 148;
	
	  ;% rtB.h0hkib4ron
	  section.data(90).logicalSrcIdx = 90;
	  section.data(90).dtTransOffset = 149;
	
	  ;% rtB.gxs3xlh0jb
	  section.data(91).logicalSrcIdx = 91;
	  section.data(91).dtTransOffset = 150;
	
	  ;% rtB.cuh2ly0avr
	  section.data(92).logicalSrcIdx = 92;
	  section.data(92).dtTransOffset = 151;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.nvvl1et5cw
	  section.data(1).logicalSrcIdx = 93;
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
	
	  ;% rtDW.fzr1ogugs2
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 31;
	
	  ;% rtDW.gepbsobs0a
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 32;
	
	  ;% rtDW.i4wxuhmfgf
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 33;
	
	  ;% rtDW.hzeqqg0jia
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 34;
	
	  ;% rtDW.f51eegc2bu
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 35;
	
	  ;% rtDW.fxt15s43p4
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 36;
	
	  ;% rtDW.g3gghz3gaz
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 37;
	
	  ;% rtDW.abf3scvxey
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 38;
	
	  ;% rtDW.h1wh3z4evx
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 39;
	
	  ;% rtDW.bds32z0txa
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 40;
	
	  ;% rtDW.c4quijr14v
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
      
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% rtDW.jdobxxns3j
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.op222kfxbt.LoggedData
	  section.data(2).logicalSrcIdx = 62;
	  section.data(2).dtTransOffset = 65;
	
	  ;% rtDW.lqgtrexdqd.LoggedData
	  section.data(3).logicalSrcIdx = 63;
	  section.data(3).dtTransOffset = 66;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.jpo5gkezdl
	  section.data(1).logicalSrcIdx = 64;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% rtDW.jjhzuiuwr5
	  section.data(1).logicalSrcIdx = 65;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.kalc0i12gy
	  section.data(2).logicalSrcIdx = 66;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.kt2if2m30y
	  section.data(1).logicalSrcIdx = 67;
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


  targMap.checksum0 = 128974220;
  targMap.checksum1 = 3459481193;
  targMap.checksum2 = 3351760960;
  targMap.checksum3 = 1013255462;


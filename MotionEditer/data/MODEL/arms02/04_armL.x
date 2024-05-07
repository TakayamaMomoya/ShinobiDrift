xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 170;
 5.88546;-20.76028;6.24017;,
 10.51852;-16.21825;10.96091;,
 0.24284;-16.42955;15.23008;,
 0.32430;-20.87462;8.55063;,
 -10.04156;-16.62569;10.98136;,
 -5.24160;-20.98082;6.25123;,
 -14.31026;-16.69188;0.70353;,
 -7.55179;-21.01656;0.68891;,
 -10.06270;-16.58931;-9.58275;,
 -5.25306;-20.96110;-4.87799;,
 0.21292;-16.37808;-13.85190;,
 0.30812;-20.84676;-7.18840;,
 10.49736;-16.18184;-9.60316;,
 5.87402;-20.74056;-4.88905;,
 5.87402;-20.74056;-4.88905;,
 10.49736;-16.18184;-9.60316;,
 14.76604;-16.11571;0.67463;,
 8.18421;-20.70482;0.67329;,
 10.51852;-16.21825;10.96091;,
 5.88546;-20.76028;6.24017;,
 10.51852;-16.21825;10.96091;,
 13.54109;-9.49129;14.12184;,
 0.11526;-9.76728;19.69973;,
 0.24284;-16.42955;15.23008;,
 0.11526;-9.76728;19.69973;,
 -13.32196;-10.02360;14.14851;,
 -10.04156;-16.62569;10.98136;,
 -13.32196;-10.02360;14.14851;,
 -18.89930;-10.11005;0.71989;,
 -14.31026;-16.69188;0.70353;,
 -13.34960;-9.97602;-12.71976;,
 -10.06270;-16.58931;-9.58275;,
 -13.34960;-9.97602;-12.71976;,
 0.07618;-9.70003;-18.29773;,
 0.21292;-16.37808;-13.85190;,
 0.07618;-9.70003;-18.29773;,
 13.51344;-9.44372;-12.74646;,
 10.49736;-16.18184;-9.60316;,
 13.51344;-9.44372;-12.74646;,
 19.09075;-9.35725;0.68213;,
 13.54109;-9.49129;14.12184;,
 14.49292;-1.60330;15.24165;,
 -0.03902;-1.90202;21.27919;,
 -14.58338;-2.17947;15.27055;,
 -13.32196;-10.02360;14.14851;,
 -14.58338;-2.17947;15.27055;,
 -20.62023;-2.27305;0.73553;,
 -14.61330;-2.12801;-13.81144;,
 -13.34960;-9.97602;-12.71976;,
 -14.61330;-2.12801;-13.81144;,
 -0.08132;-1.82929;-19.84897;,
 14.46302;-1.55184;-13.84033;,
 14.46302;-1.55184;-13.84033;,
 20.49994;-1.45819;0.69467;,
 14.49292;-1.60330;15.24165;,
 13.22928;6.24472;14.14999;,
 -0.19652;5.96872;19.72789;,
 -13.63376;5.71241;14.17668;,
 -13.63376;5.71241;14.17668;,
 -19.21108;5.62594;0.74805;,
 -13.66140;5.75998;-12.69160;,
 -13.66140;5.75998;-12.69160;,
 -0.23560;6.03598;-18.26955;,
 13.20165;6.29228;-12.71830;,
 13.20165;6.29228;-12.71830;,
 18.77894;6.37876;0.71031;,
 13.22928;6.24472;14.14999;,
 13.22928;6.24472;14.14999;,
 9.94238;12.85806;11.01295;,
 -0.33326;12.64682;15.28211;,
 -0.19652;5.96872;19.72789;,
 -0.33326;12.64682;15.28211;,
 -10.61772;12.45065;11.03340;,
 -10.61772;12.45065;11.03340;,
 -14.88640;12.38443;0.75558;,
 -10.63886;12.48706;-9.53071;,
 -10.63886;12.48706;-9.53071;,
 -0.36318;12.69827;-13.79987;,
 -0.23560;6.03598;-18.26955;,
 -0.36318;12.69827;-13.79987;,
 9.92123;12.89445;-9.55112;,
 13.20165;6.29228;-12.71830;,
 9.92123;12.89445;-9.55112;,
 14.18992;12.96063;0.72667;,
 9.94238;12.85806;11.01295;,
 5.13271;17.22977;6.30817;,
 -0.42846;17.11546;8.61864;,
 -5.99436;17.00922;6.31923;,
 -10.61772;12.45065;11.03340;,
 -5.99436;17.00922;6.31923;,
 -8.30452;16.97351;0.75691;,
 -6.00579;17.02893;-4.81001;,
 -10.63886;12.48706;-9.53071;,
 -6.00579;17.02893;-4.81001;,
 -0.44466;17.14329;-7.12043;,
 5.12124;17.24950;-4.82104;,
 7.43149;17.28532;0.74127;,
 14.18992;12.96063;0.72667;,
 0.34724;-22.42570;0.67830;,
 8.18421;-20.70482;0.67329;,
 -0.46756;18.69444;0.75189;,
 -8.30452;16.97351;0.75691;,
 16.77776;-0.97212;-22.14701;,
 17.87059;-0.72264;-22.14769;,
 17.51799;-54.66044;-22.24276;,
 16.40406;-54.68256;-22.24167;,
 16.77776;-0.97212;-22.14701;,
 16.82332;-1.05048;22.14980;,
 17.87059;-0.72264;-22.14769;,
 22.35644;0.29260;-17.66709;,
 22.39278;0.23012;17.66293;,
 17.91615;-0.80098;22.14912;,
 16.44964;-54.76092;22.05515;,
 17.56356;-54.73878;22.05403;,
 17.91615;-0.80098;22.14912;,
 16.82332;-1.05048;22.14980;,
 16.44964;-54.76092;22.05515;,
 16.40406;-54.68256;-22.24167;,
 17.56356;-54.73878;22.05403;,
 17.51799;-54.66044;-22.24276;,
 22.04219;-54.64200;17.56620;,
 22.00585;-54.57952;-17.76381;,
 22.35644;0.29260;-17.66709;,
 22.39278;0.23012;17.66293;,
 22.04219;-54.64200;17.56620;,
 22.00585;-54.57952;-17.76381;,
 -19.61135;1.59594;17.70855;,
 -19.64769;1.65842;-17.62147;,
 -17.92742;-55.37084;-17.72412;,
 -17.89106;-55.43334;17.60587;,
 9.49169;-59.97106;-22.24391;,
 9.53727;-60.04942;22.05289;,
 9.53727;-60.04942;22.05289;,
 9.56534;-9.81138;22.14175;,
 9.56534;-9.81138;22.14175;,
 9.51976;-9.73302;-22.15504;,
 9.51976;-9.73302;-22.15504;,
 9.49169;-59.97106;-22.24391;,
 -6.95686;-60.29700;-22.22757;,
 -6.91127;-60.37534;22.06924;,
 -6.91127;-60.37534;22.06924;,
 -7.83228;-11.27245;22.15707;,
 -7.83228;-11.27245;22.15707;,
 -7.87784;-11.19411;-22.13973;,
 -7.87784;-11.19411;-22.13973;,
 -6.95686;-60.29700;-22.22757;,
 -12.37210;-55.25278;-22.21306;,
 -12.32652;-55.33115;22.08373;,
 -12.32652;-55.33115;22.08373;,
 -15.11238;1.08934;22.18644;,
 -15.11238;1.08934;22.18644;,
 -15.15794;1.16770;-22.11037;,
 -15.15794;1.16770;-22.11037;,
 -12.37210;-55.25278;-22.21306;,
 -13.40396;-55.35242;22.08481;,
 -13.44952;-55.27407;-22.21198;,
 -19.64769;1.65842;-17.62147;,
 -19.61135;1.59594;17.70855;,
 -17.89106;-55.43334;17.60587;,
 -17.92742;-55.37084;-17.72412;,
 -13.40396;-55.35242;22.08481;,
 -13.44952;-55.27407;-22.21198;,
 -15.15794;1.16770;-22.11037;,
 -13.44952;-55.27407;-22.21198;,
 17.51799;-54.66044;-22.24276;,
 17.87059;-0.72264;-22.14769;,
 -13.40396;-55.35242;22.08481;,
 -15.11238;1.08934;22.18644;,
 17.91615;-0.80098;22.14912;,
 17.56356;-54.73878;22.05403;;
 
 99;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;14,15,16,17;,
 4;17,16,18,19;,
 4;20,21,22,23;,
 4;2,24,25,4;,
 4;26,27,28,29;,
 4;29,28,30,31;,
 4;8,32,33,10;,
 4;34,35,36,37;,
 4;15,38,39,16;,
 4;16,39,40,18;,
 4;21,41,42,22;,
 4;22,42,43,44;,
 4;27,45,46,28;,
 4;28,46,47,30;,
 4;48,49,50,35;,
 4;35,50,51,36;,
 4;38,52,53,39;,
 4;39,53,54,40;,
 4;41,55,56,42;,
 4;42,56,57,43;,
 4;45,58,59,46;,
 4;46,59,60,47;,
 4;49,61,62,50;,
 4;50,62,63,51;,
 4;52,64,65,53;,
 4;53,65,66,54;,
 4;67,68,69,70;,
 4;56,71,72,57;,
 4;58,73,74,59;,
 4;59,74,75,60;,
 4;61,76,77,62;,
 4;78,79,80,81;,
 4;64,82,83,65;,
 4;65,83,84,66;,
 4;68,85,86,69;,
 4;69,86,87,88;,
 4;73,89,90,74;,
 4;74,90,91,75;,
 4;92,93,94,79;,
 4;79,94,95,80;,
 4;80,95,96,97;,
 4;97,96,85,68;,
 3;3,98,0;,
 3;5,98,3;,
 3;7,98,5;,
 3;9,98,7;,
 3;11,98,9;,
 3;13,98,11;,
 3;99,98,13;,
 3;0,98,99;,
 3;85,100,86;,
 3;86,100,87;,
 3;87,100,101;,
 3;101,100,93;,
 3;93,100,94;,
 3;94,100,95;,
 3;95,100,96;,
 3;96,100,85;,
 4;102,103,104,105;,
 3;106,107,108;,
 3;108,107,109;,
 3;109,107,110;,
 3;110,107,111;,
 4;112,113,114,115;,
 3;116,117,118;,
 3;117,119,118;,
 3;118,119,120;,
 3;120,119,121;,
 4;122,123,124,125;,
 4;126,127,128,129;,
 4;130,117,116,131;,
 4;132,112,115,133;,
 4;134,107,106,135;,
 4;136,102,105,137;,
 4;138,130,131,139;,
 4;140,132,133,141;,
 4;142,134,135,143;,
 4;144,136,137,145;,
 4;146,138,139,147;,
 4;148,140,141,149;,
 4;150,142,143,151;,
 4;152,144,145,153;,
 3;154,148,149;,
 3;152,153,155;,
 4;156,157,150,151;,
 3;158,159,160;,
 3;159,161,160;,
 3;160,161,147;,
 3;147,161,146;,
 4;128,127,162,163;,
 4;164,165,122,125;,
 4;126,129,166,167;,
 4;168,169,124,123;;
 
 MeshMaterialList {
  1;
  99;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\MATERIAL\\arms_00.png";
   }
  }
 }
 MeshNormals {
  101;
  0.287676;-0.919696;0.267212;,
  0.018714;-0.925226;0.378955;,
  -0.250483;-0.930362;0.267740;,
  -0.362220;-0.932092;-0.001278;,
  -0.251038;-0.929408;-0.270518;,
  0.017931;-0.923878;-0.382266;,
  0.287123;-0.918743;-0.271058;,
  0.398855;-0.917012;-0.002034;,
  0.512960;-0.700095;0.496729;,
  0.014776;-0.710337;0.703707;,
  -0.483834;-0.719848;0.497718;,
  -0.690789;-0.723056;-0.000570;,
  -0.484860;-0.718083;-0.499267;,
  0.013326;-0.707842;-0.706245;,
  0.511934;-0.698331;-0.500258;,
  0.718889;-0.695122;-0.001970;,
  0.660894;-0.372699;0.651395;,
  0.008567;-0.386109;0.922413;,
  -0.644315;-0.398563;0.652692;,
  -0.915304;-0.402764;0.000228;,
  -0.645658;-0.396252;-0.652771;,
  0.006668;-0.382842;-0.923790;,
  0.659551;-0.370389;-0.654068;,
  0.930540;-0.366187;-0.001606;,
  0.707694;0.012759;0.706403;,
  0.001029;-0.001768;0.999998;,
  -0.706240;-0.015259;0.707808;,
  -0.999803;-0.019811;0.000993;,
  -0.707695;-0.012758;-0.706403;,
  -0.001028;0.001769;-0.999998;,
  0.706240;0.015261;-0.707808;,
  0.999803;0.019813;-0.000993;,
  0.645658;0.396251;0.652772;,
  -0.006668;0.382840;0.923791;,
  -0.659551;0.370387;0.654069;,
  -0.930541;0.366184;0.001605;,
  -0.660895;0.372696;-0.651395;,
  -0.008567;0.386106;-0.922415;,
  0.644315;0.398561;-0.652692;,
  0.915304;0.402763;-0.000229;,
  0.484858;0.718084;0.499267;,
  -0.013325;0.707842;0.706245;,
  -0.511933;0.698332;0.500257;,
  -0.718888;0.695123;0.001969;,
  -0.512959;0.700096;-0.496728;,
  -0.014776;0.710338;-0.703706;,
  0.483832;0.719848;-0.497719;,
  0.690789;0.723057;0.000569;,
  0.251036;0.929408;0.270521;,
  -0.017931;0.923879;0.382264;,
  -0.287122;0.918743;0.271057;,
  -0.398852;0.917013;0.002034;,
  -0.287675;0.919696;-0.267213;,
  -0.018715;0.925226;-0.378956;,
  0.250480;0.930361;-0.267746;,
  0.362215;0.932094;0.001278;,
  0.019810;-0.999802;-0.001791;,
  -0.019813;0.999802;0.001790;,
  -0.001027;0.001769;-0.999998;,
  0.001030;-0.001769;0.999998;,
  -0.343633;0.939102;0.002017;,
  0.330134;-0.943932;-0.002009;,
  0.001028;-0.001769;0.999998;,
  -0.462988;0.886362;0.002044;,
  -0.357010;-0.934100;-0.001285;,
  0.001029;-0.001769;0.999998;,
  -0.083685;0.996491;0.001849;,
  -0.357036;-0.934090;-0.001285;,
  -0.228847;-0.973461;-0.001487;,
  -0.251717;-0.009349;0.967756;,
  0.543443;0.839445;0.000926;,
  -0.923921;-0.027203;-0.381616;,
  -0.383629;-0.009930;-0.923434;,
  0.381979;-0.000840;-0.924171;,
  0.019812;-0.999802;-0.001788;,
  -0.222591;0.974910;0.001953;,
  -0.923133;-0.028556;0.383419;,
  -0.381719;-0.013198;0.924184;,
  -0.222578;0.974913;0.001968;,
  -0.222584;0.974912;0.001961;,
  0.383879;-0.004109;0.923374;,
  0.019812;-0.999802;-0.001788;,
  -0.524130;0.851636;0.002046;,
  -0.222577;0.974913;0.001953;,
  0.330164;-0.943921;-0.002009;,
  0.225731;-0.974188;-0.001955;,
  0.019846;-0.999802;-0.001789;,
  0.019825;-0.999802;-0.001788;,
  0.923571;-0.005254;-0.383392;,
  0.924357;-0.006607;0.381471;,
  -0.001029;0.001769;-0.999998;,
  -0.001029;0.001770;-0.999998;,
  0.001033;-0.001769;0.999998;,
  0.861676;0.507458;0.000011;,
  -0.253715;-0.005925;-0.967261;,
  -0.001033;0.001769;-0.999998;,
  0.110278;0.993899;0.001645;,
  0.019816;-0.999802;-0.001789;,
  0.019816;-0.999802;-0.001789;,
  0.019791;-0.999803;-0.001789;,
  0.019770;-0.999803;-0.001789;;
  99;
  4;0,8,9,1;,
  4;1,9,10,2;,
  4;2,10,11,3;,
  4;3,11,12,4;,
  4;4,12,13,5;,
  4;5,13,14,6;,
  4;6,14,15,7;,
  4;7,15,8,0;,
  4;8,16,17,9;,
  4;9,17,18,10;,
  4;10,18,19,11;,
  4;11,19,20,12;,
  4;12,20,21,13;,
  4;13,21,22,14;,
  4;14,22,23,15;,
  4;15,23,16,8;,
  4;16,24,25,17;,
  4;17,25,26,18;,
  4;18,26,27,19;,
  4;19,27,28,20;,
  4;20,28,29,21;,
  4;21,29,30,22;,
  4;22,30,31,23;,
  4;23,31,24,16;,
  4;24,32,33,25;,
  4;25,33,34,26;,
  4;26,34,35,27;,
  4;27,35,36,28;,
  4;28,36,37,29;,
  4;29,37,38,30;,
  4;30,38,39,31;,
  4;31,39,32,24;,
  4;32,40,41,33;,
  4;33,41,42,34;,
  4;34,42,43,35;,
  4;35,43,44,36;,
  4;36,44,45,37;,
  4;37,45,46,38;,
  4;38,46,47,39;,
  4;39,47,40,32;,
  4;40,48,49,41;,
  4;41,49,50,42;,
  4;42,50,51,43;,
  4;43,51,52,44;,
  4;44,52,53,45;,
  4;45,53,54,46;,
  4;46,54,55,47;,
  4;47,55,48,40;,
  3;1,56,0;,
  3;2,56,1;,
  3;3,56,2;,
  3;4,56,3;,
  3;5,56,4;,
  3;6,56,5;,
  3;7,56,6;,
  3;0,56,7;,
  3;48,57,49;,
  3;49,57,50;,
  3;50,57,51;,
  3;51,57,52;,
  3;52,57,53;,
  3;53,57,54;,
  3;54,57,55;,
  3;55,57,48;,
  4;58,73,73,58;,
  3;82,60,83;,
  3;83,60,75;,
  3;75,60,79;,
  3;79,60,78;,
  4;59,80,80,59;,
  3;84,85,86;,
  3;85,87,86;,
  3;86,87,81;,
  3;81,87,74;,
  4;88,89,89,88;,
  4;76,71,71,76;,
  4;61,85,84,61;,
  4;62,59,59,62;,
  4;63,60,82,63;,
  4;90,58,58,90;,
  4;64,61,61,64;,
  4;65,62,62,65;,
  4;66,63,63,66;,
  4;91,90,90,91;,
  4;67,64,64,68;,
  4;92,65,65,69;,
  4;70,93,93,70;,
  4;94,91,91,95;,
  3;77,92,69;,
  3;94,95,72;,
  4;96,96,70,70;,
  3;97,98,99;,
  3;98,100,99;,
  3;99,100,68;,
  3;68,100,67;,
  4;71,71,94,72;,
  4;73,73,88,88;,
  4;76,76,77,69;,
  4;80,80,89,89;;
 }
 MeshTextureCoords {
  170;
  0.388770;0.428760;,
  0.392400;0.432690;,
  0.383870;0.436230;,
  0.384160;0.430680;,
  0.375340;0.432690;,
  0.379540;0.428760;,
  0.371800;0.424130;,
  0.377620;0.424130;,
  0.375340;0.415570;,
  0.379540;0.419490;,
  0.383870;0.412020;,
  0.384160;0.417580;,
  0.392400;0.415570;,
  0.388770;0.419490;,
  0.377140;0.440960;,
  0.373220;0.436950;,
  0.381770;0.436680;,
  0.381770;0.440810;,
  0.390330;0.436950;,
  0.386410;0.440960;,
  0.391910;0.414020;,
  0.394100;0.419760;,
  0.382950;0.418900;,
  0.383380;0.413360;,
  0.383440;0.439940;,
  0.372290;0.435310;,
  0.374110;0.438060;,
  0.371480;0.432730;,
  0.382670;0.433090;,
  0.382670;0.438340;,
  0.393850;0.432730;,
  0.391220;0.438060;,
  0.372290;0.412940;,
  0.383440;0.408310;,
  0.381420;0.435770;,
  0.380990;0.430230;,
  0.392140;0.429360;,
  0.389950;0.435100;,
  0.370590;0.431210;,
  0.381770;0.430850;,
  0.392960;0.431210;,
  0.394510;0.426370;,
  0.382440;0.425430;,
  0.370370;0.424490;,
  0.371800;0.418030;,
  0.370560;0.426270;,
  0.382670;0.426660;,
  0.394770;0.426270;,
  0.369840;0.431100;,
  0.368410;0.424640;,
  0.380480;0.423700;,
  0.392550;0.422760;,
  0.369670;0.424610;,
  0.381770;0.424220;,
  0.393880;0.424610;,
  0.393080;0.432820;,
  0.381930;0.431960;,
  0.370780;0.431090;,
  0.371480;0.419670;,
  0.382670;0.420030;,
  0.393850;0.419670;,
  0.368820;0.418030;,
  0.379970;0.417170;,
  0.391120;0.416300;,
  0.370590;0.418150;,
  0.381770;0.417790;,
  0.392960;0.418150;,
  0.392720;0.413280;,
  0.389670;0.415910;,
  0.381140;0.412360;,
  0.381570;0.408650;,
  0.381500;0.437490;,
  0.372970;0.436830;,
  0.374110;0.413930;,
  0.382670;0.414200;,
  0.391220;0.413930;,
  0.371010;0.412290;,
  0.379540;0.411630;,
  0.381570;0.440280;,
  0.381140;0.436570;,
  0.389670;0.433030;,
  0.392720;0.435650;,
  0.373220;0.412820;,
  0.381770;0.412540;,
  0.390330;0.412820;,
  0.385470;0.419830;,
  0.380850;0.417910;,
  0.376230;0.419830;,
  0.372610;0.415910;,
  0.378030;0.409920;,
  0.382670;0.410070;,
  0.387300;0.409920;,
  0.372610;0.433030;,
  0.376230;0.429100;,
  0.380850;0.431020;,
  0.385470;0.429100;,
  0.387380;0.424470;,
  0.393210;0.424470;,
  0.384260;0.424130;,
  0.390690;0.424130;,
  0.380750;0.424470;,
  0.374320;0.424470;,
  0.180560;0.447430;,
  0.182140;0.447060;,
  0.181990;0.525280;,
  0.180380;0.525320;,
  0.184810;0.377750;,
  0.242430;0.375930;,
  0.184760;0.376290;,
  0.190410;0.370130;,
  0.236380;0.368670;,
  0.242390;0.374470;,
  0.291040;0.446600;,
  0.292650;0.446600;,
  0.294520;0.524800;,
  0.292930;0.524470;,
  0.242320;0.380900;,
  0.184700;0.382730;,
  0.242280;0.379440;,
  0.184650;0.381260;,
  0.236260;0.373710;,
  0.190300;0.375170;,
  0.189610;0.444810;,
  0.240850;0.444810;,
  0.240850;0.524280;,
  0.189610;0.524280;,
  0.298730;0.445860;,
  0.349950;0.444640;,
  0.351940;0.525720;,
  0.300720;0.526930;,
  0.184970;0.392260;,
  0.242590;0.390440;,
  0.280880;0.439100;,
  0.282180;0.511950;,
  0.242710;0.386210;,
  0.185080;0.388030;,
  0.170090;0.460180;,
  0.170390;0.533040;,
  0.185640;0.413920;,
  0.243260;0.412100;,
  0.257020;0.439040;,
  0.256920;0.510270;,
  0.243410;0.409210;,
  0.185790;0.411040;,
  0.144870;0.462420;,
  0.146540;0.533620;,
  0.185870;0.420620;,
  0.243490;0.418800;,
  0.249300;0.446490;,
  0.246670;0.528380;,
  0.243740;0.417760;,
  0.186120;0.419580;,
  0.134230;0.444540;,
  0.138650;0.526340;,
  0.247730;0.446490;,
  0.137090;0.526380;,
  0.192130;0.425270;,
  0.238090;0.423810;,
  0.237890;0.426310;,
  0.191930;0.427760;,
  0.243540;0.420220;,
  0.185910;0.422040;,
  0.356460;0.444830;,
  0.358430;0.525070;,
  0.183110;0.524790;,
  0.183110;0.446670;,
  0.294210;0.526590;,
  0.292240;0.446350;,
  0.247350;0.446670;,
  0.247350;0.524790;;
 }
}
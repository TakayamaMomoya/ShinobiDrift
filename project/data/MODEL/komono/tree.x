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
 268;
 0.12860;-0.28885;1.05154;,
 0.12860;-0.28885;-8.41460;,
 6.65731;-0.28885;-5.64203;,
 9.36160;-0.28885;1.05154;,
 6.65731;-0.28885;7.74512;,
 0.12859;-0.28885;10.51769;,
 -6.40012;-0.28885;7.74512;,
 -9.10440;-0.28885;1.05154;,
 -6.40012;-0.28885;-5.64203;,
 -7.75496;7.54391;1.05154;,
 -5.44592;7.54391;-4.74989;,
 -5.12711;30.21695;1.05154;,
 -3.58775;30.21695;-2.81608;,
 0.12860;30.21695;-4.41810;,
 0.12860;7.54391;-7.15293;,
 -5.44592;7.54391;6.85297;,
 -3.58775;30.21695;4.91916;,
 0.12859;7.54391;9.25600;,
 0.12859;30.21695;6.52118;,
 5.70311;7.54391;6.85297;,
 3.84494;30.21695;4.91916;,
 5.38430;30.21695;1.05154;,
 8.01215;7.54391;1.05154;,
 5.70311;7.54391;-4.74990;,
 3.84494;30.21695;-2.81608;,
 0.12860;48.14466;-2.15652;,
 -2.20876;48.14466;-1.21690;,
 0.12860;82.32875;1.05154;,
 2.46595;48.14466;-1.21690;,
 3.43411;48.14466;1.05154;,
 2.46595;48.14466;3.31999;,
 0.12859;48.14466;4.25960;,
 -2.20876;48.14466;3.31999;,
 -3.17692;48.14466;1.05154;,
 1.16177;43.75043;1.05154;,
 1.16177;43.75043;-1.32625;,
 2.05430;42.20450;-0.62981;,
 2.42399;41.56418;1.05154;,
 2.05430;42.20450;2.73289;,
 1.16177;43.75043;3.42933;,
 0.26923;45.29634;2.73289;,
 -0.10046;45.93668;1.05154;,
 0.26923;45.29634;-0.62981;,
 2.40540;46.95735;1.05154;,
 2.72105;46.41062;-0.40572;,
 9.48414;50.21464;1.05154;,
 9.69459;49.85016;0.08004;,
 10.20264;48.97018;-0.32237;,
 3.48313;45.09066;-1.00933;,
 2.72105;46.41062;2.50880;,
 9.69459;49.85016;2.02305;,
 3.48313;45.09066;3.11241;,
 10.20264;48.97018;2.42545;,
 4.24522;43.77070;2.50880;,
 10.71069;48.09019;2.02305;,
 10.92114;47.72570;1.05154;,
 4.56087;43.22396;1.05154;,
 4.24522;43.77070;-0.40572;,
 10.71069;48.09019;0.08004;,
 17.11046;52.95840;0.32945;,
 16.83395;53.43734;0.54095;,
 25.16757;57.61016;1.05154;,
 17.38698;52.47949;0.54095;,
 17.50150;52.28111;1.05154;,
 17.38698;52.47949;1.56213;,
 17.11046;52.95840;1.77363;,
 16.83395;53.43734;1.56213;,
 16.71943;53.63571;1.05154;,
 -10.66694;60.63536;-0.48930;,
 8.58970;60.63536;-0.48930;,
 13.26664;44.69597;-5.51496;,
 -10.66694;44.69597;-5.51496;,
 8.35287;48.83939;9.13330;,
 8.35287;57.36637;-17.91084;,
 -5.75318;57.36637;-17.91084;,
 -5.75318;48.83939;9.13330;,
 -10.66624;57.41863;1.33512;,
 13.26720;57.45925;1.40639;,
 13.25616;44.80501;12.32385;,
 -10.67727;44.76436;12.25257;,
 8.30514;59.43575;16.48471;,
 8.40052;40.91229;-4.98542;,
 -5.70544;40.88836;-5.02745;,
 -5.80083;59.41183;16.44269;,
 -10.66694;47.06074;-5.43384;,
 13.26664;47.06074;-5.43384;,
 13.26664;35.24293;-17.25164;,
 -10.66694;35.24293;-17.25164;,
 8.35287;32.15437;-2.34526;,
 8.35287;52.20547;-22.39638;,
 -5.75318;52.20548;-22.39638;,
 -5.75318;32.15437;-2.34526;,
 -4.56655;43.89855;-13.81704;,
 7.93872;43.89855;6.58970;,
 18.01505;32.08074;0.41491;,
 5.50979;32.08074;-19.99183;,
 2.73783;28.99217;4.01379;,
 19.83425;49.04329;-6.46290;,
 12.46385;49.04330;-18.49030;,
 -4.63256;28.99217;-8.01360;,
 9.03037;43.89855;-7.76597;,
 -4.35315;43.89855;12.07590;,
 5.44426;32.08074;18.68433;,
 18.82777;32.08074;-1.15753;,
 -4.16594;28.99217;6.27507;,
 12.45722;49.04329;17.48752;,
 20.34521;49.04330;5.79307;,
 3.72209;28.99217;-5.41938;,
 -0.37178;43.89855;13.00882;,
 -8.55754;43.89855;-9.48142;,
 -19.66264;32.08074;-5.43948;,
 -11.47690;32.08074;17.05079;,
 -3.97460;28.99217;-5.92032;,
 -22.81652;49.04329;0.93759;,
 -17.99197;49.04330;14.19296;,
 0.84994;28.99217;7.33504;,
 -8.89139;51.95433;18.16098;,
 -11.91325;52.39316;-5.57701;,
 -2.83207;38.43417;-6.99109;,
 0.18977;37.99533;16.74689;,
 3.80834;52.31690;-2.62553;,
 -19.72619;36.73197;0.08232;,
 -17.94518;36.47336;14.07312;,
 5.58932;52.05833;11.36526;,
 -14.78672;52.84974;18.16098;,
 -17.80860;53.28854;-5.57701;,
 -8.72741;39.32956;-6.99109;,
 -5.70557;38.89073;16.74689;,
 -2.08700;53.21231;-2.62553;,
 -25.62152;37.62736;0.08232;,
 -23.84053;37.36876;14.07312;,
 -0.30601;52.95373;11.36526;,
 -10.42698;53.11726;18.16098;,
 -10.70577;56.15803;-5.57701;,
 -22.15909;44.06913;-6.99109;,
 -21.88039;41.02833;16.74689;,
 -7.10978;40.85304;-2.62553;,
 -25.22908;60.09907;0.08232;,
 -23.18274;55.70005;14.07312;,
 -6.94542;39.06090;11.36526;,
 -4.07621;63.87891;8.73664;,
 -5.74864;64.38264;-4.84165;,
 -1.79141;55.71788;-5.65051;,
 -0.11900;55.21413;7.92778;,
 3.13898;63.01025;-3.15338;,
 -11.49273;56.18328;-1.60447;,
 -10.50705;55.88641;6.39836;,
 4.12467;62.71337;4.84945;,
 -4.07621;72.04716;8.73664;,
 -5.74864;72.55091;-4.84165;,
 -1.79141;63.88619;-5.65051;,
 -0.11900;63.38242;7.92778;,
 3.13898;71.17853;-3.15338;,
 -11.49273;64.35156;-1.60447;,
 -10.50705;64.05467;6.39836;,
 4.12467;70.88165;4.84945;,
 -0.74832;75.48862;8.73664;,
 -1.89967;76.80209;-4.84165;,
 -3.13536;67.35699;-5.65051;,
 -1.98403;66.04352;7.92778;,
 4.91021;70.92851;-3.15338;,
 -11.11592;72.89257;-1.60447;,
 -10.43736;72.11844;6.39836;,
 5.58880;70.15443;4.84945;,
 -0.85982;76.79431;7.98929;,
 0.72677;75.80414;-5.57252;,
 3.87577;66.83593;-4.54932;,
 2.28915;67.82612;9.01249;,
 8.79578;73.98859;-1.65867;,
 -6.40334;68.49465;-3.03567;,
 -7.33847;69.07822;4.95745;,
 7.86067;74.57222;6.33445;,
 -0.85982;68.86229;7.98929;,
 0.72677;67.87206;-5.57252;,
 3.87577;58.90390;-4.54932;,
 2.28915;59.89409;9.01249;,
 8.79578;66.05656;-1.65867;,
 -6.40334;60.56260;-3.03567;,
 -7.33847;61.14614;4.95745;,
 7.86067;66.64016;6.33445;,
 15.40780;52.68566;0.92343;,
 2.19878;52.18644;-2.63931;,
 3.65028;43.71971;-6.83443;,
 16.85930;44.21891;-3.27166;,
 7.19754;51.42482;-10.26530;,
 3.71862;43.91632;3.68505;,
 11.50382;44.21047;5.78488;,
 14.98273;51.71908;-8.16547;,
 15.40780;52.68566;6.91674;,
 2.19878;52.18644;3.35400;,
 3.65028;43.71971;-0.84112;,
 16.85930;44.21891;2.72165;,
 7.19754;51.42482;-4.27198;,
 3.71862;43.91632;9.67836;,
 11.50382;44.21047;11.77820;,
 14.98273;51.71908;-2.17216;,
 23.06953;56.69317;3.35553;,
 9.86051;56.19395;-0.20721;,
 11.31202;47.72720;-4.40233;,
 24.52104;48.22643;-0.83955;,
 14.85927;55.43232;-7.83319;,
 11.38036;47.92382;6.11715;,
 19.16555;48.21799;8.21699;,
 22.64447;55.72659;-5.73337;,
 7.35523;67.55153;1.04923;,
 -5.85380;67.05231;-2.51351;,
 -4.40229;58.58556;-6.70863;,
 8.80673;59.08480;-3.14586;,
 -0.85503;66.29068;-10.13949;,
 -4.33395;58.78218;3.81085;,
 3.45125;59.07635;5.91068;,
 6.93017;66.58495;-8.03967;,
 7.35523;76.33079;1.04923;,
 -5.85380;75.83157;-2.51351;,
 -4.40229;67.36482;-6.70863;,
 8.80673;67.86406;-3.14586;,
 -0.85503;75.06994;-10.13949;,
 -4.33395;67.56144;3.81085;,
 3.45125;67.85562;5.91068;,
 6.93017;75.36421;-8.03967;,
 7.35523;64.78239;7.98617;,
 -5.85380;64.28316;4.42343;,
 -4.40229;55.81641;0.22831;,
 8.80673;56.31565;3.79108;,
 -0.85503;63.52153;-3.20256;,
 -4.33395;56.01304;10.74778;,
 3.45125;56.30721;12.84762;,
 6.93017;63.81580;-1.10273;,
 4.85597;80.72505;6.64120;,
 -2.73746;80.43809;4.59310;,
 -1.90303;75.57081;2.18147;,
 5.69039;75.85779;4.22958;,
 0.13617;80.00022;0.20918;,
 -1.86375;75.68384;8.22876;,
 2.61170;75.85295;9.43589;,
 4.61162;80.16937;1.41630;,
 4.85597;81.03416;-0.81862;,
 -2.73746;79.13080;-1.62748;,
 -1.90303;74.55678;1.30249;,
 5.69039;76.46016;2.11138;,
 0.13617;75.14750;-3.51005;,
 -1.86375;79.79855;4.32020;,
 2.61170;80.92035;4.79694;,
 4.61162;76.26935;-3.03334;,
 4.85597;84.76168;0.10493;,
 -2.73746;82.85833;-0.70393;,
 -1.90303;78.28431;2.22604;,
 5.69039;80.18768;3.03493;,
 0.13617;78.87503;-2.58650;,
 -1.86375;83.52607;5.24374;,
 2.61170;84.64788;5.72049;,
 4.61162;79.99688;-2.10979;,
 -7.12779;82.29324;12.73982;,
 -21.48027;54.67558;10.65802;,
 -11.60862;52.29216;-11.14640;,
 0.73805;84.38116;-9.06460;,
 -20.54629;62.86931;-7.46912;,
 4.85505;52.20387;9.58412;,
 12.13180;71.11670;10.81120;,
 -13.26951;81.78220;-6.24205;,
 1.25345;81.33756;12.73982;,
 15.21372;49.91691;10.65802;,
 23.87934;55.21193;-11.14640;,
 9.91941;86.63268;-9.06460;,
 1.29393;52.68615;-7.46912;,
 24.83597;58.36534;9.58412;,
 16.60803;76.88419;10.81120;,
 -6.93403;71.20504;-6.24205;;
 
 180;
 3;0,1,2;,
 3;0,2,3;,
 3;0,3,4;,
 3;0,4,5;,
 3;0,5,6;,
 3;0,6,7;,
 3;0,7,8;,
 3;0,8,1;,
 4;8,7,9,10;,
 4;9,11,12,10;,
 4;12,13,14,10;,
 4;8,10,14,1;,
 4;6,15,9,7;,
 4;16,11,9,15;,
 4;15,17,18,16;,
 4;5,17,15,6;,
 4;4,19,17,5;,
 4;20,18,17,19;,
 4;21,20,19,22;,
 4;3,22,19,4;,
 4;2,23,22,3;,
 4;24,21,22,23;,
 4;13,24,23,14;,
 4;1,14,23,2;,
 3;25,26,27;,
 3;28,25,27;,
 3;29,28,27;,
 3;30,29,27;,
 3;31,30,27;,
 3;32,31,27;,
 3;33,32,27;,
 3;33,27,26;,
 4;21,29,30,20;,
 4;20,30,31,18;,
 4;24,28,29,21;,
 4;12,26,25,13;,
 4;28,24,13,25;,
 4;12,11,33,26;,
 4;33,11,16,32;,
 4;32,16,18,31;,
 3;34,35,36;,
 3;34,36,37;,
 3;34,37,38;,
 3;34,38,39;,
 3;34,39,40;,
 3;34,40,41;,
 3;34,41,42;,
 3;34,42,35;,
 4;42,41,43,44;,
 4;43,45,46,44;,
 4;46,47,48,44;,
 4;42,44,48,35;,
 4;40,49,43,41;,
 4;50,45,43,49;,
 4;49,51,52,50;,
 4;39,51,49,40;,
 4;38,53,51,39;,
 4;54,52,51,53;,
 4;55,54,53,56;,
 4;37,56,53,38;,
 4;36,57,56,37;,
 4;58,55,56,57;,
 4;47,58,57,48;,
 4;35,48,57,36;,
 3;59,60,61;,
 3;62,59,61;,
 3;63,62,61;,
 3;64,63,61;,
 3;65,64,61;,
 3;66,65,61;,
 3;67,66,61;,
 3;67,61,60;,
 4;55,63,64,54;,
 4;54,64,65,52;,
 4;58,62,63,55;,
 4;46,60,59,47;,
 4;62,58,47,59;,
 4;46,45,67,60;,
 4;67,45,50,66;,
 4;66,50,52,65;,
 4;68,69,70,71;,
 4;71,70,69,68;,
 4;72,73,74,75;,
 4;75,74,73,72;,
 4;76,77,78,79;,
 4;79,78,77,76;,
 4;80,81,82,83;,
 4;83,82,81,80;,
 4;84,85,86,87;,
 4;87,86,85,84;,
 4;88,89,90,91;,
 4;91,90,89,88;,
 4;92,93,94,95;,
 4;95,94,93,92;,
 4;96,97,98,99;,
 4;99,98,97,96;,
 4;100,101,102,103;,
 4;103,102,101,100;,
 4;104,105,106,107;,
 4;107,106,105,104;,
 4;108,109,110,111;,
 4;111,110,109,108;,
 4;112,113,114,115;,
 4;115,114,113,112;,
 4;116,117,118,119;,
 4;119,118,117,116;,
 4;120,121,122,123;,
 4;123,122,121,120;,
 4;124,125,126,127;,
 4;127,126,125,124;,
 4;128,129,130,131;,
 4;131,130,129,128;,
 4;132,133,134,135;,
 4;135,134,133,132;,
 4;136,137,138,139;,
 4;139,138,137,136;,
 4;140,141,142,143;,
 4;143,142,141,140;,
 4;144,145,146,147;,
 4;147,146,145,144;,
 4;148,149,150,151;,
 4;151,150,149,148;,
 4;152,153,154,155;,
 4;155,154,153,152;,
 4;156,157,158,159;,
 4;159,158,157,156;,
 4;160,161,162,163;,
 4;163,162,161,160;,
 4;164,165,166,167;,
 4;167,166,165,164;,
 4;168,169,170,171;,
 4;171,170,169,168;,
 4;172,173,174,175;,
 4;175,174,173,172;,
 4;176,177,178,179;,
 4;179,178,177,176;,
 4;180,181,182,183;,
 4;183,182,181,180;,
 4;184,185,186,187;,
 4;187,186,185,184;,
 4;188,189,190,191;,
 4;191,190,189,188;,
 4;192,193,194,195;,
 4;195,194,193,192;,
 4;196,197,198,199;,
 4;199,198,197,196;,
 4;200,201,202,203;,
 4;203,202,201,200;,
 4;204,205,206,207;,
 4;207,206,205,204;,
 4;208,209,210,211;,
 4;211,210,209,208;,
 4;212,213,214,215;,
 4;215,214,213,212;,
 4;216,217,218,219;,
 4;219,218,217,216;,
 4;220,221,222,223;,
 4;223,222,221,220;,
 4;224,225,226,227;,
 4;227,226,225,224;,
 4;228,229,230,231;,
 4;231,230,229,228;,
 4;232,233,234,235;,
 4;235,234,233,232;,
 4;236,237,238,239;,
 4;239,238,237,236;,
 4;240,241,242,243;,
 4;243,242,241,240;,
 4;244,245,246,247;,
 4;247,246,245,244;,
 4;248,249,250,251;,
 4;251,250,249,248;,
 4;252,253,254,255;,
 4;255,254,253,252;,
 4;256,257,258,259;,
 4;259,258,257,256;,
 4;260,261,262,263;,
 4;263,262,261,260;,
 4;264,265,266,267;,
 4;267,266,265,264;;
 
 MeshMaterialList {
  2;
  180;
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Pictures\\team\\bck0004-009.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Pictures\\team\\publicdomainq-0009046dzj.png";
   }
  }
 }
}
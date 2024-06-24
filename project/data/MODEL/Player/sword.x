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
 191;
 10.22258;-18.69596;-1.17506;,
 10.73501;-18.46336;-0.95195;,
 9.79953;-18.88813;-0.29584;,
 9.26277;-19.13183;-0.49746;,
 10.50856;-18.18921;-1.41087;,
 10.22258;-18.69596;-1.17506;,
 9.26373;-19.13141;-1.45633;,
 9.11987;-18.81973;-1.81512;,
 10.86625;-18.02735;-1.12617;,
 -5.72781;17.56917;-1.41058;,
 -5.37013;17.72933;-1.12548;,
 10.73501;-18.46336;-0.95195;,
 11.35755;-17.80558;-0.29347;,
 11.11384;-18.29131;-0.30034;,
 8.81783;-19.33385;-1.45633;,
 9.26373;-19.13141;-1.45633;,
 8.81882;-19.33335;-0.49749;,
 8.67709;-19.01996;-1.81498;,
 8.81783;-19.33385;-1.45633;,
 7.85899;-19.76924;-1.17506;,
 7.28887;-19.65286;-1.41058;,
 -7.55884;16.73594;-1.81512;,
 -7.11608;16.93628;-1.81498;,
 7.34664;-20.00190;-0.95195;,
 7.85899;-19.76924;-1.17506;,
 8.28210;-19.57712;-0.29584;,
 6.93115;-19.81302;-1.12550;,
 7.34664;-20.00190;-0.95195;,
 6.96779;-20.17393;-0.30034;,
 6.44166;-20.04146;-0.29113;,
 -9.30523;15.94357;-1.12616;,
 -8.94754;16.10544;-1.41087;,
 6.96779;-20.17393;0.19628;,
 6.96779;-20.17393;-0.30034;,
 8.28210;-19.57712;0.19177;,
 6.44167;-20.03779;0.18941;,
 6.96779;-20.17393;0.19628;,
 7.34664;-20.00190;0.84790;,
 6.93199;-19.81379;1.02211;,
 -9.79925;15.72424;0.18707;,
 -9.79648;15.72183;-0.29346;,
 7.85899;-19.76924;1.07100;,
 7.34664;-20.00190;0.84790;,
 8.81882;-19.33335;0.39343;,
 7.28927;-19.65098;1.30682;,
 7.85899;-19.76924;1.07100;,
 8.81783;-19.33385;1.35227;,
 8.67787;-19.02040;1.71106;,
 -8.94921;16.10638;1.30651;,
 -9.30520;15.94251;1.02142;,
 9.26373;-19.13141;1.35227;,
 8.81783;-19.33385;1.35227;,
 9.26277;-19.13183;0.39343;,
 9.12003;-18.81884;1.71093;,
 9.26373;-19.13141;1.35227;,
 10.22258;-18.69596;1.07096;,
 10.51023;-18.19017;1.30651;,
 -7.11688;16.93665;1.71106;,
 -7.55902;16.73502;1.71093;,
 10.73501;-18.46336;0.84789;,
 10.22258;-18.69596;1.07096;,
 9.79953;-18.88813;0.19177;,
 10.86621;-18.02623;1.02145;,
 10.73501;-18.46336;0.84789;,
 11.11384;-18.29131;0.19628;,
 11.36031;-17.80803;0.18707;,
 -5.37095;17.73013;1.02211;,
 -5.72822;17.56735;1.30681;,
 11.11384;-18.29131;-0.30034;,
 11.11384;-18.29131;0.19628;,
 -4.88067;17.95776;-0.29113;,
 -4.88067;17.95407;0.18941;,
 -5.78562;17.91823;-0.95195;,
 -6.29794;17.68551;-1.17506;,
 -7.25780;17.24968;-0.49746;,
 -6.72108;17.49339;-0.29584;,
 -5.78562;17.91823;-0.95195;,
 -5.40677;18.09023;-0.30034;,
 -6.29794;17.68551;-1.17506;,
 -7.25684;17.25010;-1.45633;,
 -7.25684;17.25010;-1.45633;,
 -7.70273;17.04760;-1.45633;,
 -7.70176;17.04810;-0.49746;,
 -7.70273;17.04760;-1.45633;,
 -8.66155;16.61222;-1.17506;,
 -8.66155;16.61222;-1.17506;,
 -9.17399;16.37955;-0.95195;,
 -8.23849;16.80432;-0.29584;,
 -9.17399;16.37955;-0.95195;,
 -9.55277;16.20754;-0.30034;,
 -9.55277;16.20754;-0.30034;,
 -9.55277;16.20754;0.19628;,
 -8.23849;16.80432;0.19177;,
 -9.55277;16.20754;0.19628;,
 -9.17399;16.37955;0.84790;,
 -9.17399;16.37955;0.84790;,
 -8.66155;16.61222;1.07098;,
 -7.70176;17.04810;0.39343;,
 -8.66155;16.61222;1.07098;,
 -7.70273;17.04760;1.35227;,
 -7.70273;17.04760;1.35227;,
 -7.25684;17.25010;1.35227;,
 -7.25780;17.24968;0.39340;,
 -7.25684;17.25010;1.35227;,
 -6.29794;17.68551;1.07096;,
 -6.29794;17.68551;1.07096;,
 -5.78562;17.91823;0.84789;,
 -6.72108;17.49339;0.19177;,
 -5.78562;17.91823;0.84789;,
 -5.40677;18.09023;0.19628;,
 -5.40677;18.09023;0.19628;,
 -5.40677;18.09023;-0.30034;,
 10.73501;-18.46336;-0.95195;,
 8.81783;-19.33385;-1.45633;,
 7.34664;-20.00190;-0.95195;,
 6.96779;-20.17393;0.19628;,
 7.85899;-19.76924;1.07100;,
 9.26373;-19.13141;1.35227;,
 10.73501;-18.46336;0.84789;,
 11.11384;-18.29131;-0.30034;,
 -5.78562;17.91823;-0.95195;,
 -7.70273;17.04760;-1.45633;,
 -9.17399;16.37955;-0.95195;,
 -9.55277;16.20754;0.19628;,
 -8.66155;16.61222;1.07098;,
 -7.25684;17.25010;1.35227;,
 -5.78562;17.91823;0.84789;,
 -5.40677;18.09023;-0.30034;,
 3.32830;-22.95675;4.19143;,
 2.98065;-22.83127;4.19143;,
 2.98065;-22.83127;-4.23947;,
 3.32830;-22.95675;-4.23947;,
 3.21718;-22.72025;4.45276;,
 14.99849;-17.47657;4.19143;,
 14.88744;-17.24004;4.45276;,
 2.99502;-22.24704;4.45276;,
 2.75846;-22.35816;4.19143;,
 15.12397;-17.12895;4.19143;,
 14.99849;-17.47657;-4.23947;,
 15.12397;-17.12895;-4.23947;,
 14.90176;-16.65580;4.19143;,
 14.66523;-16.76687;4.45276;,
 2.88394;-22.01054;4.19143;,
 2.88394;-22.01054;-4.23947;,
 2.75846;-22.35816;-4.23947;,
 14.55416;-16.53036;4.19143;,
 14.90176;-16.65580;-4.23947;,
 14.55418;-16.53033;-4.23947;,
 2.99502;-22.24704;-4.50080;,
 3.21718;-22.72025;-4.50080;,
 14.66523;-16.76687;-4.50080;,
 14.88744;-17.24004;-4.50080;,
 7.73754;-24.59935;1.26815;,
 13.44650;-21.91851;1.26815;,
 11.72515;-18.25284;1.26815;,
 6.01620;-20.93367;1.26815;,
 11.72515;-18.25284;-1.31619;,
 6.01620;-20.93367;-1.31619;,
 13.44650;-21.91851;-1.31619;,
 7.73754;-24.59935;-1.31619;,
 55.41608;-113.92178;-0.72637;,
 52.85532;-114.42215;-0.72637;,
 50.82435;-110.60623;-0.72637;,
 53.27094;-109.29612;-0.72637;,
 11.23102;-18.64245;-0.72637;,
 8.71755;-19.80815;-0.72637;,
 6.56138;-20.80796;-0.04869;,
 11.23102;-18.64245;-0.04869;,
 11.23102;-18.64245;0.62902;,
 8.71755;-19.80815;0.62902;,
 50.82435;-110.60623;0.62902;,
 53.27094;-109.29612;0.62902;,
 55.37319;-118.89453;-0.05380;,
 52.83884;-117.65352;-0.05889;,
 48.66826;-111.60608;-0.06912;,
 6.56138;-20.80796;-0.04869;,
 8.71755;-19.80815;-0.72637;,
 34.58653;-69.00562;-0.72637;,
 53.27094;-109.29612;-0.72637;,
 11.23102;-18.64245;0.62902;,
 53.27094;-109.29612;0.62902;,
 52.85532;-114.42215;0.62902;,
 55.41608;-113.92178;0.62902;,
 8.71755;-19.80815;0.62902;,
 11.23102;-18.64245;-0.72637;,
 34.58653;-69.00562;-0.72637;,
 55.41608;-113.92178;-0.72637;,
 58.01304;-119.52178;-0.04869;,
 55.41608;-113.92178;0.62902;,
 51.16838;-115.44143;-0.06296;,
 58.01304;-119.52178;-0.04869;;
 
 149;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,4,9,10;,
 4;11,8,12,13;,
 4;14,15,3,16;,
 4;17,18,19,20;,
 4;7,17,21,22;,
 4;23,24,16,25;,
 4;26,27,28,29;,
 4;20,26,30,31;,
 4;32,33,25,34;,
 4;35,36,37,38;,
 4;29,35,39,40;,
 4;41,42,34,43;,
 4;44,45,46,47;,
 4;38,44,48,49;,
 4;50,51,43,52;,
 4;53,54,55,56;,
 4;47,53,57,58;,
 4;59,60,52,61;,
 4;62,63,64,65;,
 4;56,62,66,67;,
 4;68,69,61,2;,
 4;65,12,70,71;,
 4;72,73,74,75;,
 4;10,76,77,70;,
 4;78,9,22,79;,
 4;80,81,82,74;,
 4;83,21,31,84;,
 4;85,86,87,82;,
 4;88,30,40,89;,
 4;90,91,92,87;,
 4;93,39,49,94;,
 4;95,96,97,92;,
 4;98,48,58,99;,
 4;100,101,102,97;,
 4;103,57,67,104;,
 4;105,106,107,102;,
 4;108,66,71,109;,
 4;110,111,75,107;,
 4;4,7,22,9;,
 4;17,20,31,21;,
 4;26,29,40,30;,
 4;35,38,49,39;,
 4;44,47,58,48;,
 4;53,56,67,57;,
 4;62,65,71,66;,
 4;12,8,10,70;,
 3;15,0,3;,
 3;24,14,16;,
 3;33,23,25;,
 3;42,32,34;,
 3;51,41,43;,
 3;60,50,52;,
 3;69,59,61;,
 3;1,68,2;,
 3;73,80,74;,
 3;81,85,82;,
 3;86,90,87;,
 3;91,95,92;,
 3;96,100,97;,
 3;101,105,102;,
 3;106,110,107;,
 3;111,72,75;,
 4;5,4,8,112;,
 4;113,17,7,6;,
 4;114,26,20,19;,
 4;115,35,29,28;,
 4;116,44,38,37;,
 4;117,53,47,46;,
 4;118,62,56,55;,
 4;119,12,65,64;,
 4;120,10,9,78;,
 4;79,22,21,121;,
 4;84,31,30,122;,
 4;89,40,39,123;,
 4;94,49,48,124;,
 4;99,58,57,125;,
 4;104,67,66,126;,
 4;109,71,70,127;,
 3;34,25,43;,
 3;25,16,43;,
 3;43,16,52;,
 3;16,3,52;,
 3;52,3,61;,
 3;3,2,61;,
 3;87,92,82;,
 3;92,97,82;,
 3;82,97,74;,
 3;97,102,74;,
 3;74,102,75;,
 3;102,107,75;,
 4;128,129,130,131;,
 4;132,128,133,134;,
 4;129,132,135,136;,
 4;137,133,138,139;,
 4;134,137,140,141;,
 4;136,142,143,144;,
 4;142,135,141,145;,
 4;145,140,146,147;,
 4;144,148,149,130;,
 4;148,143,147,150;,
 4;150,146,139,151;,
 4;131,149,151,138;,
 4;132,134,141,135;,
 4;142,145,147,143;,
 4;148,150,151,149;,
 4;131,138,133,128;,
 4;137,139,146,140;,
 4;130,129,136,144;,
 3;128,132,129;,
 3;137,134,133;,
 3;136,135,142;,
 3;145,141,140;,
 3;144,143,148;,
 3;150,147,146;,
 3;130,149,131;,
 3;138,151,139;,
 4;152,153,154,155;,
 4;155,154,156,157;,
 4;157,156,158,159;,
 4;159,158,153,152;,
 4;153,158,156,154;,
 4;159,152,155,157;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;168,169,170,171;,
 3;161,172,173;,
 4;162,174,175,176;,
 3;164,167,177;,
 3;177,167,178;,
 3;167,179,178;,
 3;179,180,178;,
 4;171,170,181,182;,
 3;172,181,173;,
 4;175,174,170,169;,
 4;167,166,183,179;,
 3;176,184,162;,
 3;162,184,185;,
 3;185,163,162;,
 3;178,180,186;,
 3;186,180,187;,
 3;180,188,187;,
 3;173,181,189;,
 3;161,173,189;,
 4;190,172,161,160;,
 4;182,181,172,190;,
 4;189,181,170,174;,
 4;161,189,174,162;;
 
 MeshMaterialList {
  1;
  149;
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
    "data\\TEXTURE\\MATERIAL\\Sword00.png";
   }
  }
 }
 MeshNormals {
  153;
  0.511027;-0.786171;-0.347543;,
  0.502882;-0.202847;-0.840216;,
  0.757028;-0.091739;-0.646911;,
  0.613409;-0.743220;-0.267122;,
  0.338981;-0.864801;-0.370421;,
  0.053191;-0.406114;-0.912273;,
  0.270558;-0.307401;-0.912306;,
  0.427800;-0.824479;-0.370435;,
  0.155917;-0.951064;-0.266772;,
  -0.429033;-0.630727;-0.646618;,
  -0.178480;-0.512595;-0.839876;,
  0.255380;-0.902435;-0.346976;,
  0.091010;-0.990514;0.102952;,
  -0.613922;-0.744315;0.262859;,
  -0.613941;-0.744875;-0.261223;,
  0.091441;-0.990651;-0.101239;,
  0.255610;-0.902156;0.347531;,
  -0.178237;-0.512116;0.840219;,
  -0.429130;-0.630358;0.646914;,
  0.155896;-0.950971;0.267117;,
  0.427981;-0.824393;0.370416;,
  0.270750;-0.307340;0.912270;,
  0.053364;-0.406012;0.912308;,
  0.339165;-0.864722;0.370437;,
  0.613459;-0.743303;0.266776;,
  0.757241;-0.092062;0.646615;,
  0.503400;-0.202990;0.839871;,
  0.511384;-0.786187;0.346982;,
  0.685907;-0.720371;-0.102942;,
  0.964444;-0.027577;-0.262844;,
  0.964875;-0.027932;0.261222;,
  0.685726;-0.720787;0.101225;,
  -0.155919;0.951065;-0.266766;,
  0.429041;0.630724;-0.646615;,
  0.178472;0.512612;-0.839867;,
  -0.255384;0.902431;-0.346982;,
  -0.339041;0.864777;-0.370422;,
  -0.053238;0.406130;-0.912263;,
  -0.270589;0.307396;-0.912299;,
  -0.427844;0.824446;-0.370456;,
  -0.511043;0.786168;-0.347527;,
  -0.502882;0.202848;-0.840216;,
  -0.757037;0.091742;-0.646899;,
  -0.613433;0.743215;-0.267079;,
  -0.685899;0.720379;-0.102936;,
  -0.964446;0.027580;-0.262836;,
  -0.964878;0.027944;0.261210;,
  -0.685715;0.720798;0.101214;,
  -0.613476;0.743305;0.266730;,
  -0.757251;0.092071;0.646601;,
  -0.503402;0.202983;0.839872;,
  -0.511393;0.786183;0.346977;,
  -0.428016;0.824357;0.370457;,
  -0.270766;0.307321;0.912271;,
  -0.053402;0.406013;0.912306;,
  -0.339218;0.864693;0.370455;,
  -0.255633;0.902153;0.347522;,
  0.178198;0.512140;0.840213;,
  0.429116;0.630383;0.646898;,
  -0.155920;0.950977;0.267081;,
  -0.091010;0.990516;0.102929;,
  0.613930;0.744313;0.262847;,
  0.613954;0.744869;-0.261212;,
  -0.091436;0.990654;-0.101218;,
  0.413430;-0.910536;0.000014;,
  0.413387;-0.910556;0.000010;,
  0.413451;-0.910526;-0.000008;,
  0.413484;-0.910511;0.000007;,
  0.413493;-0.910507;-0.000006;,
  0.413417;-0.910542;0.000008;,
  0.413399;-0.910550;-0.000010;,
  0.413436;-0.910533;-0.000018;,
  -0.413466;0.910520;0.000001;,
  -0.413456;0.910524;-0.000018;,
  -0.413484;0.910511;-0.000014;,
  -0.413473;0.910517;0.000007;,
  -0.413484;0.910512;-0.000006;,
  -0.413470;0.910518;0.000013;,
  -0.413456;0.910524;0.000018;,
  -0.413472;0.910517;-0.000001;,
  -0.071425;-0.973980;0.215085;,
  0.008698;-0.524741;0.851218;,
  -0.567082;-0.795083;0.215083;,
  0.973972;-0.071432;0.215119;,
  0.398196;-0.341829;0.851230;,
  0.556571;-0.679107;0.478584;,
  -0.861977;-0.167093;0.478619;,
  -0.524690;-0.008692;0.851249;,
  -0.795058;0.567099;0.215130;,
  -0.167105;0.861996;0.478581;,
  0.341795;0.398210;0.851237;,
  0.679071;0.556605;0.478595;,
  -0.973970;0.071413;-0.215133;,
  -0.795058;0.567099;-0.215129;,
  -0.524692;-0.008692;-0.851248;,
  -0.008693;0.524700;-0.851243;,
  0.071434;0.973969;-0.215130;,
  0.567095;0.795063;-0.215126;,
  -0.567083;-0.795083;-0.215082;,
  -0.341823;-0.398213;-0.851225;,
  -0.071425;-0.973980;-0.215084;,
  0.795052;-0.567115;-0.215112;,
  0.524704;0.008697;-0.851240;,
  0.973972;-0.071432;-0.215118;,
  0.000000;-0.000000;1.000000;,
  -0.425052;0.905169;0.000000;,
  0.000000;0.000000;-1.000000;,
  -0.000910;-0.067159;-0.997742;,
  -0.083909;-0.044208;-0.995492;,
  -0.420720;0.907190;-0.000117;,
  -0.127356;-0.059115;0.990094;,
  -0.001889;-0.068160;0.997673;,
  -0.130996;-0.068801;0.988993;,
  0.907196;0.420709;-0.000014;,
  -0.249475;-0.131439;-0.959419;,
  -0.420720;0.907191;-0.000027;,
  0.907197;0.420706;-0.000003;,
  -0.129151;-0.140845;0.981571;,
  -0.176308;-0.198261;-0.964162;,
  -0.122513;-0.136968;-0.982970;,
  -0.049196;-0.167734;-0.984604;,
  -0.266226;-0.177286;0.947467;,
  0.300576;-0.640085;0.707068;,
  -0.640066;-0.300543;0.707099;,
  0.940590;-0.339544;-0.000000;,
  0.640060;0.300588;0.707085;,
  -0.940600;0.339516;0.000000;,
  -0.300581;0.640098;0.707054;,
  0.339508;0.940603;0.000002;,
  -0.640068;-0.300544;-0.707097;,
  -0.300577;0.640088;-0.707065;,
  0.640062;0.300589;-0.707083;,
  0.300577;-0.640087;-0.707066;,
  0.425053;-0.905169;-0.000000;,
  0.905168;0.425054;0.000000;,
  -0.905169;-0.425052;0.000000;,
  -0.245326;-0.113660;-0.962755;,
  -0.123821;-0.057366;-0.990645;,
  0.907197;0.420705;0.000000;,
  0.907197;0.420706;-0.000002;,
  0.907197;0.420707;-0.000002;,
  0.907197;0.420706;0.000000;,
  0.907196;0.420708;-0.000007;,
  -0.053549;-0.171630;0.983705;,
  -0.185376;-0.203705;0.961322;,
  -0.252189;-0.117059;0.960572;,
  -0.259135;-0.136101;0.956204;,
  -0.420720;0.907190;0.000063;,
  0.907196;0.420709;0.000006;,
  0.907195;0.420710;-0.000040;,
  -0.254367;-0.171809;-0.951724;,
  -0.001817;-0.134015;-0.990978;,
  -0.003770;-0.136003;0.990701;;
  149;
  4;0,3,71,70;,
  4;1,0,7,6;,
  4;2,1,34,33;,
  4;3,2,29,28;,
  4;4,7,70,69;,
  4;5,4,11,10;,
  4;6,5,38,37;,
  4;8,11,69,68;,
  4;9,8,15,14;,
  4;10,9,42,41;,
  4;12,15,68,67;,
  4;13,12,19,18;,
  4;14,13,46,45;,
  4;16,19,67,66;,
  4;17,16,23,22;,
  4;18,17,50,49;,
  4;20,23,66,65;,
  4;21,20,27,26;,
  4;22,21,54,53;,
  4;24,27,65,64;,
  4;25,24,31,30;,
  4;26,25,58,57;,
  4;28,31,64,71;,
  4;30,29,62,61;,
  4;32,35,73,72;,
  4;33,32,63,62;,
  4;35,34,37,36;,
  4;36,39,74,73;,
  4;39,38,41,40;,
  4;40,43,75,74;,
  4;43,42,45,44;,
  4;44,47,76,75;,
  4;47,46,49,48;,
  4;48,51,77,76;,
  4;51,50,53,52;,
  4;52,55,78,77;,
  4;55,54,57,56;,
  4;56,59,79,78;,
  4;59,58,61,60;,
  4;60,63,72,79;,
  4;1,6,37,34;,
  4;5,10,41,38;,
  4;9,14,45,42;,
  4;13,18,49,46;,
  4;17,22,53,50;,
  4;21,26,57,54;,
  4;25,30,61,58;,
  4;29,2,33,62;,
  3;7,0,70;,
  3;11,4,69;,
  3;15,8,68;,
  3;19,12,67;,
  3;23,16,66;,
  3;27,20,65;,
  3;31,24,64;,
  3;3,28,71;,
  3;35,36,73;,
  3;39,40,74;,
  3;43,44,75;,
  3;47,48,76;,
  3;51,52,77;,
  3;55,56,78;,
  3;59,60,79;,
  3;63,32,72;,
  4;0,1,2,3;,
  4;4,5,6,7;,
  4;8,9,10,11;,
  4;12,13,14,15;,
  4;16,17,18,19;,
  4;20,21,22,23;,
  4;24,25,26,27;,
  4;28,29,30,31;,
  4;32,33,34,35;,
  4;36,37,38,39;,
  4;40,41,42,43;,
  4;44,45,46,47;,
  4;48,49,50,51;,
  4;52,53,54,55;,
  4;56,57,58,59;,
  4;60,61,62,63;,
  3;67,68,66;,
  3;68,69,66;,
  3;66,69,65;,
  3;69,70,65;,
  3;65,70,64;,
  3;70,71,64;,
  3;75,76,74;,
  3;76,77,74;,
  3;74,77,73;,
  3;77,78,73;,
  3;73,78,72;,
  3;78,79,72;,
  4;80,82,98,100;,
  4;81,122,85,84;,
  4;123,123,87,86;,
  4;83,124,101,103;,
  4;125,125,91,90;,
  4;126,88,93,92;,
  4;127,127,127,89;,
  4;128,128,97,96;,
  4;129,94,99,129;,
  4;130,130,130,95;,
  4;131,131,131,102;,
  4;132,132,132,132;,
  4;81,84,90,87;,
  4;88,89,96,93;,
  4;94,95,102,99;,
  4;100,101,85,80;,
  4;83,103,97,91;,
  4;98,82,86,92;,
  3;80,81,82;,
  3;83,84,85;,
  3;86,87,88;,
  3;89,90,91;,
  3;92,93,94;,
  3;95,96,97;,
  3;98,99,100;,
  3;101,102,103;,
  4;104,104,104,104;,
  4;105,105,105,105;,
  4;106,106,106,106;,
  4;133,133,133,133;,
  4;134,134,134,134;,
  4;135,135,135,135;,
  4;107,119,108,106;,
  4;109,109,115,115;,
  4;104,110,112,104;,
  3;119,120,118;,
  4;108,114,136,137;,
  3;138,139,116;,
  3;116,139,140;,
  3;139,141,140;,
  3;141,142,140;,
  4;104,112,117,111;,
  3;143,117,144;,
  4;145,146,112,110;,
  4;115,115,147,147;,
  3;137,106,108;,
  3;108,106,106;,
  3;106,106,108;,
  3;140,142,148;,
  3;148,142,113;,
  3;142,149,113;,
  3;144,117,121;,
  3;119,118,150;,
  4;151,120,119,107;,
  4;111,117,143,152;,
  4;121,117,112,146;,
  4;119,150,114,108;;
 }
 MeshTextureCoords {
  191;
  0.326410;0.727610;,
  0.338050;0.745070;,
  0.316800;0.796430;,
  0.304610;0.780650;,
  0.104920;0.946520;,
  0.101640;0.948440;,
  0.088250;0.943050;,
  0.085550;0.938720;,
  0.109910;0.948530;,
  0.087420;0.568310;,
  0.092400;0.570330;,
  0.110720;0.952090;,
  0.116750;0.951290;,
  0.116070;0.954240;,
  0.294510;0.705590;,
  0.304630;0.705590;,
  0.294530;0.780650;,
  0.079380;0.936230;,
  0.077000;0.938530;,
  0.063620;0.933140;,
  0.060010;0.928460;,
  0.061880;0.558050;,
  0.068050;0.560540;,
  0.261090;0.745070;,
  0.272730;0.727610;,
  0.282340;0.796430;,
  0.055030;0.926440;,
  0.054530;0.929490;,
  0.049180;0.927330;,
  0.048180;0.923730;,
  0.037530;0.548250;,
  0.042510;0.550260;,
  0.252490;0.834950;,
  0.252490;0.796080;,
  0.282340;0.834600;,
  0.048190;0.923710;,
  0.049180;0.927330;,
  0.054530;0.929480;,
  0.055040;0.926450;,
  0.030660;0.545440;,
  0.030680;0.545480;,
  0.272730;0.903430;,
  0.261090;0.885960;,
  0.294530;0.850390;,
  0.060020;0.928450;,
  0.063620;0.933140;,
  0.077000;0.938530;,
  0.079390;0.936240;,
  0.042500;0.550230;,
  0.037520;0.548250;,
  0.304630;0.925450;,
  0.294510;0.925450;,
  0.304610;0.850390;,
  0.085560;0.938720;,
  0.088250;0.943050;,
  0.101640;0.948440;,
  0.104940;0.946540;,
  0.068040;0.560530;,
  0.061870;0.558050;,
  0.338050;0.885960;,
  0.326410;0.903430;,
  0.316800;0.834600;,
  0.109910;0.948520;,
  0.110720;0.952090;,
  0.116070;0.954240;,
  0.116770;0.951330;,
  0.092400;0.570320;,
  0.087410;0.568320;,
  0.346650;0.796080;,
  0.346650;0.834950;,
  0.099260;0.573040;,
  0.099240;0.573060;,
  0.336120;0.745070;,
  0.324480;0.727610;,
  0.302680;0.780650;,
  0.314870;0.796430;,
  0.092910;0.567290;,
  0.098250;0.569440;,
  0.083820;0.563630;,
  0.070430;0.558240;,
  0.302710;0.705590;,
  0.292580;0.705590;,
  0.292600;0.780650;,
  0.059190;0.553720;,
  0.045800;0.548330;,
  0.270800;0.727610;,
  0.259170;0.745070;,
  0.280410;0.796430;,
  0.036710;0.544680;,
  0.031360;0.542530;,
  0.250560;0.796080;,
  0.250560;0.834950;,
  0.280410;0.834600;,
  0.031360;0.542530;,
  0.036710;0.544680;,
  0.259170;0.885960;,
  0.270800;0.903430;,
  0.292600;0.850390;,
  0.045800;0.548330;,
  0.059180;0.553720;,
  0.292580;0.925450;,
  0.302710;0.925450;,
  0.302680;0.850390;,
  0.070430;0.558240;,
  0.083820;0.563630;,
  0.324480;0.903430;,
  0.336120;0.885960;,
  0.314870;0.834600;,
  0.092910;0.567290;,
  0.098250;0.569440;,
  0.344720;0.834950;,
  0.344720;0.796080;,
  0.108270;0.951110;,
  0.082940;0.940920;,
  0.056980;0.930470;,
  0.046360;0.926200;,
  0.056980;0.930470;,
  0.082310;0.940660;,
  0.108270;0.951110;,
  0.118890;0.955380;,
  0.090450;0.566300;,
  0.065120;0.556110;,
  0.039170;0.545670;,
  0.028540;0.541390;,
  0.039170;0.545670;,
  0.064490;0.555860;,
  0.090450;0.566300;,
  0.101070;0.570570;,
  0.812810;0.452830;,
  0.808970;0.452830;,
  0.808970;0.324820;,
  0.812810;0.324820;,
  0.811570;0.456800;,
  0.941080;0.452830;,
  0.939850;0.456800;,
  0.809110;0.456800;,
  0.806510;0.452830;,
  0.942450;0.452830;,
  0.941080;0.324820;,
  0.942450;0.324820;,
  0.939980;0.452830;,
  0.937380;0.456800;,
  0.807870;0.452830;,
  0.807870;0.324820;,
  0.806510;0.324820;,
  0.936150;0.452830;,
  0.939980;0.324820;,
  0.936150;0.324820;,
  0.809110;0.320860;,
  0.811570;0.320860;,
  0.937380;0.320860;,
  0.939850;0.320860;,
  0.841970;0.196510;,
  0.974720;0.122930;,
  0.934290;0.023330;,
  0.801540;0.096910;,
  0.934290;0.023330;,
  0.801540;0.096910;,
  0.974720;0.122930;,
  0.841970;0.196510;,
  0.691400;0.035270;,
  0.677060;0.068180;,
  0.650700;0.071040;,
  0.661450;0.035000;,
  0.079970;0.282550;,
  0.045020;0.282550;,
  0.015030;0.317530;,
  0.079970;0.317530;,
  0.074480;0.029690;,
  0.062800;0.065710;,
  0.650700;0.071040;,
  0.661450;0.035000;,
  0.708810;0.063220;,
  0.688440;0.086210;,
  0.640690;0.101940;,
  0.052790;0.096620;,
  0.062800;0.065710;,
  0.408090;0.282550;,
  0.670580;0.282550;,
  0.079970;0.352500;,
  0.670580;0.352500;,
  0.677060;0.068180;,
  0.691400;0.035270;,
  0.045020;0.352500;,
  0.074480;0.029690;,
  0.400570;0.032640;,
  0.700720;0.282550;,
  0.737200;0.317530;,
  0.700720;0.352500;,
  0.670060;0.093670;,
  0.727660;0.035600;;
 }
}
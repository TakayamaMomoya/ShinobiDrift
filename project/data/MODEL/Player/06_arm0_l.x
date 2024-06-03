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
 74;
 38.13559;6.22754;5.74917;,
 37.82486;0.00003;10.79760;,
 40.76225;0.00003;9.40266;,
 40.92860;7.74560;7.41675;,
 38.13559;-6.22748;5.74917;,
 40.92860;-7.74559;7.41675;,
 37.82486;-11.12642;-0.32885;,
 40.61791;-8.67045;-0.47831;,
 38.13559;-6.22748;-6.70583;,
 40.92860;-7.74559;-8.07444;,
 37.82486;0.00003;-11.45529;,
 40.61791;0.00003;-9.14879;,
 38.13559;6.22754;-6.70583;,
 40.92860;7.74560;-8.07444;,
 37.82486;11.12647;-0.32885;,
 40.61791;8.67048;-0.47831;,
 -7.00520;0.00003;5.74351;,
 -7.00520;4.29377;3.96497;,
 -8.80087;0.00003;-0.32885;,
 -7.00520;-4.29379;3.96497;,
 -7.00520;-6.07233;-0.32885;,
 -7.00520;-4.29379;-4.62264;,
 -7.00520;0.00003;-6.40121;,
 -7.00520;4.29377;-4.62264;,
 -7.00520;6.07241;-0.32885;,
 46.75038;4.78913;4.46028;,
 46.75038;0.00003;6.44399;,
 49.33744;0.00003;-0.32885;,
 46.75038;-4.78910;4.46028;,
 46.75038;-6.77281;-0.32885;,
 46.75038;-4.78910;-5.11795;,
 46.75038;0.00003;-7.10169;,
 46.75038;4.78913;-5.11795;,
 46.75038;6.77284;-0.32885;,
 -3.44992;0.00003;10.04453;,
 -3.44992;7.33513;7.00625;,
 -3.44992;-7.33510;7.00625;,
 -3.44992;-10.37338;-0.32885;,
 -3.44992;-7.33510;-7.66395;,
 -3.44992;0.00003;-10.70223;,
 -3.44992;7.33513;-7.66395;,
 -3.44992;10.37339;-0.32885;,
 43.31618;9.47040;-0.32885;,
 43.31618;6.69664;6.36776;,
 43.31618;6.69664;-7.02546;,
 43.31618;0.00003;-9.79930;,
 43.31618;-6.69661;-7.02546;,
 43.31618;-9.47042;-0.32885;,
 43.31618;-6.69661;6.36776;,
 43.31618;0.00003;9.14160;,
 1.46593;8.43389;8.10504;,
 1.46593;0.00003;11.59848;,
 31.59543;0.00003;11.56165;,
 31.59543;8.40788;8.07903;,
 1.46593;-8.43386;8.10504;,
 31.59543;-8.40785;8.07903;,
 1.46593;-11.92733;-0.32885;,
 31.59543;-11.89050;-0.32885;,
 1.46593;-8.43386;-8.76274;,
 31.59543;-8.40785;-8.73670;,
 1.46593;0.00003;-12.25618;,
 31.59543;0.00003;-12.21935;,
 1.46593;8.43389;-8.76274;,
 31.59543;8.40788;-8.73670;,
 1.46593;11.92736;-0.32885;,
 31.59543;11.89053;-0.32885;,
 34.47094;8.40524;8.07636;,
 34.47094;0.00003;9.30825;,
 34.47094;-8.40521;8.07636;,
 34.47094;-9.63710;-0.32885;,
 34.47094;-8.40521;-8.73406;,
 34.47094;0.00003;-9.96595;,
 34.47094;8.40524;-8.73406;,
 34.47094;9.63707;-0.32885;;
 
 80;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,0,3,15;,
 3;16,17,18;,
 3;19,16,18;,
 3;20,19,18;,
 3;21,20,18;,
 3;22,21,18;,
 3;23,22,18;,
 3;24,23,18;,
 3;17,24,18;,
 3;25,26,27;,
 3;26,28,27;,
 3;28,29,27;,
 3;29,30,27;,
 3;30,31,27;,
 3;31,32,27;,
 3;32,33,27;,
 3;33,25,27;,
 4;17,16,34,35;,
 4;16,19,36,34;,
 4;19,20,37,36;,
 4;20,21,38,37;,
 4;21,22,39,38;,
 4;22,23,40,39;,
 4;23,24,41,40;,
 4;24,17,35,41;,
 4;42,43,25,33;,
 4;44,42,33,32;,
 4;45,44,32,31;,
 4;46,45,31,30;,
 4;47,46,30,29;,
 4;48,47,29,28;,
 4;49,48,28,26;,
 4;43,49,26,25;,
 4;50,51,52,53;,
 4;51,54,55,52;,
 4;54,56,57,55;,
 4;56,58,59,57;,
 4;58,60,61,59;,
 4;60,62,63,61;,
 4;62,64,65,63;,
 4;64,50,53,65;,
 4;15,3,43,42;,
 4;13,15,42,44;,
 4;11,13,44,45;,
 4;9,11,45,46;,
 4;7,9,46,47;,
 4;5,7,47,48;,
 4;2,5,48,49;,
 4;3,2,49,43;,
 4;66,67,1,0;,
 4;67,68,4,1;,
 4;68,69,6,4;,
 4;69,70,8,6;,
 4;70,71,10,8;,
 4;71,72,12,10;,
 4;72,73,14,12;,
 4;73,66,0,14;,
 4;35,34,51,50;,
 4;34,36,54,51;,
 4;36,37,56,54;,
 4;37,38,58,56;,
 4;38,39,60,58;,
 4;39,40,62,60;,
 4;40,41,64,62;,
 4;41,35,50,64;,
 4;65,53,66,73;,
 4;63,65,73,72;,
 4;61,63,72,71;,
 4;59,61,71,70;,
 4;57,59,70,69;,
 4;55,57,69,68;,
 4;52,55,68,67;,
 4;53,52,67,66;;
 
 MeshMaterialList {
  1;
  80;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\TEXTURE\\MATERIAL\\Player00.png";
   }
  }
 }
 MeshNormals {
  74;
  -0.884022;0.330533;0.330536;,
  -0.884022;0.000001;0.467445;,
  -0.884023;-0.330532;0.330533;,
  -0.884023;-0.467444;-0.000000;,
  -0.884023;-0.330533;-0.330532;,
  -0.884023;0.000001;-0.467444;,
  -0.884022;0.330533;-0.330535;,
  -0.884022;0.467444;-0.000000;,
  0.808363;0.416264;0.416262;,
  0.808363;0.000001;0.588684;,
  0.808363;-0.416262;0.416262;,
  0.808363;-0.588684;-0.000000;,
  0.808363;-0.416263;-0.416262;,
  0.808364;0.000001;-0.588683;,
  0.808363;0.416265;-0.416261;,
  0.808362;0.588686;-0.000000;,
  -1.000000;0.000000;-0.000000;,
  1.000000;0.000001;-0.000000;,
  -0.563675;0.584067;0.584068;,
  -0.563675;0.000001;0.825997;,
  -0.563675;-0.584067;0.584068;,
  -0.563675;-0.825996;-0.000000;,
  -0.563676;-0.584067;-0.584068;,
  -0.563676;0.000001;-0.825996;,
  -0.563675;0.584067;-0.584068;,
  -0.563675;0.825997;-0.000000;,
  0.433419;0.652848;0.621239;,
  0.368487;0.929633;-0.000568;,
  0.398256;0.650314;-0.646903;,
  0.382040;0.000001;-0.924146;,
  0.398256;-0.650313;-0.646905;,
  0.368487;-0.929633;-0.000568;,
  0.433419;-0.652846;0.621240;,
  0.467162;0.000001;0.884172;,
  0.251713;0.685113;0.683565;,
  0.246686;0.000000;0.969096;,
  0.251714;-0.685111;0.683566;,
  0.237812;-0.971306;0.003149;,
  0.241681;-0.685343;-0.686946;,
  0.228654;0.000000;-0.973508;,
  0.241680;0.685345;-0.686945;,
  0.237808;0.971307;0.003149;,
  0.075932;0.737500;0.671065;,
  0.065359;0.997862;0.000632;,
  0.079120;0.707335;-0.702437;,
  0.082024;0.000000;-0.996630;,
  0.079116;-0.707335;-0.702438;,
  0.065352;-0.997862;0.000632;,
  0.075928;-0.737499;0.671066;,
  0.085056;0.000001;0.996376;,
  0.051721;0.723588;0.688291;,
  0.008708;0.000000;0.999962;,
  0.051722;-0.723587;0.688292;,
  0.091156;-0.995827;0.004440;,
  0.083968;-0.704579;-0.704640;,
  0.084226;0.000000;-0.996447;,
  0.083968;0.704580;-0.704639;,
  0.091154;0.995827;0.004440;,
  -0.152396;0.698847;0.698848;,
  -0.152395;0.000001;0.988320;,
  -0.152395;-0.698847;0.698848;,
  -0.152395;-0.988320;-0.000000;,
  -0.152395;-0.698847;-0.698848;,
  -0.152395;0.000001;-0.988320;,
  -0.152395;0.698847;-0.698848;,
  -0.152396;0.988320;-0.000000;,
  0.176064;0.696061;0.696061;,
  0.166871;0.985979;-0.000000;,
  0.176062;0.696061;-0.696061;,
  0.166868;0.000000;-0.985979;,
  0.176061;-0.696061;-0.696062;,
  0.166868;-0.985979;-0.000000;,
  0.176062;-0.696060;0.696062;,
  0.166870;0.000000;0.985979;;
  80;
  4;50,51,49,42;,
  4;51,52,48,49;,
  4;52,53,47,48;,
  4;53,54,46,47;,
  4;54,55,45,46;,
  4;55,56,44,45;,
  4;56,57,43,44;,
  4;57,50,42,43;,
  3;1,0,16;,
  3;2,1,16;,
  3;3,2,16;,
  3;4,3,16;,
  3;5,4,16;,
  3;6,5,16;,
  3;7,6,16;,
  3;0,7,16;,
  3;8,9,17;,
  3;9,10,17;,
  3;10,11,17;,
  3;11,12,17;,
  3;12,13,17;,
  3;13,14,17;,
  3;14,15,17;,
  3;15,8,17;,
  4;0,1,19,18;,
  4;1,2,20,19;,
  4;2,3,21,20;,
  4;3,4,22,21;,
  4;4,5,23,22;,
  4;5,6,24,23;,
  4;6,7,25,24;,
  4;7,0,18,25;,
  4;27,26,8,15;,
  4;28,27,15,14;,
  4;29,28,14,13;,
  4;30,29,13,12;,
  4;31,30,12,11;,
  4;32,31,11,10;,
  4;33,32,10,9;,
  4;26,33,9,8;,
  4;58,59,73,66;,
  4;59,60,72,73;,
  4;60,61,71,72;,
  4;61,62,70,71;,
  4;62,63,69,70;,
  4;63,64,68,69;,
  4;64,65,67,68;,
  4;65,58,66,67;,
  4;43,42,26,27;,
  4;44,43,27,28;,
  4;45,44,28,29;,
  4;46,45,29,30;,
  4;47,46,30,31;,
  4;48,47,31,32;,
  4;49,48,32,33;,
  4;42,49,33,26;,
  4;34,35,51,50;,
  4;35,36,52,51;,
  4;36,37,53,52;,
  4;37,38,54,53;,
  4;38,39,55,54;,
  4;39,40,56,55;,
  4;40,41,57,56;,
  4;41,34,50,57;,
  4;18,19,59,58;,
  4;19,20,60,59;,
  4;20,21,61,60;,
  4;21,22,62,61;,
  4;22,23,63,62;,
  4;23,24,64,63;,
  4;24,25,65,64;,
  4;25,18,58,65;,
  4;67,66,34,41;,
  4;68,67,41,40;,
  4;69,68,40,39;,
  4;70,69,39,38;,
  4;71,70,38,37;,
  4;72,71,37,36;,
  4;73,72,36,35;,
  4;66,73,35,34;;
 }
 MeshTextureCoords {
  74;
  0.053793;0.556285;,
  0.054887;0.574536;,
  0.044540;0.574536;,
  0.043954;0.551835;,
  0.053793;0.592788;,
  0.043954;0.597237;,
  0.054887;0.607145;,
  0.045048;0.599947;,
  0.053793;0.592788;,
  0.043954;0.597237;,
  0.054887;0.574536;,
  0.045048;0.574536;,
  0.053793;0.556285;,
  0.043954;0.551835;,
  0.054887;0.541927;,
  0.045048;0.549125;,
  0.212803;0.574536;,
  0.212803;0.561952;,
  0.219129;0.574536;,
  0.212803;0.587120;,
  0.212803;0.592333;,
  0.212803;0.587120;,
  0.212803;0.574536;,
  0.212803;0.561952;,
  0.212803;0.556739;,
  0.023446;0.560500;,
  0.023446;0.574536;,
  0.014333;0.574536;,
  0.023446;0.588572;,
  0.023446;0.594386;,
  0.023446;0.588572;,
  0.023446;0.574536;,
  0.023446;0.560500;,
  0.023446;0.554686;,
  0.200280;0.574536;,
  0.200280;0.553039;,
  0.200280;0.596034;,
  0.200280;0.604938;,
  0.200280;0.596034;,
  0.200280;0.574536;,
  0.200280;0.553039;,
  0.200280;0.544134;,
  0.035544;0.546780;,
  0.035544;0.554910;,
  0.035544;0.554910;,
  0.035544;0.574536;,
  0.035544;0.594163;,
  0.035544;0.602292;,
  0.035544;0.594163;,
  0.035544;0.574536;,
  0.182963;0.549818;,
  0.182963;0.574536;,
  0.076830;0.574536;,
  0.076830;0.549895;,
  0.182963;0.599254;,
  0.076830;0.599178;,
  0.182963;0.609493;,
  0.076830;0.609385;,
  0.182963;0.599254;,
  0.076830;0.599178;,
  0.182963;0.574536;,
  0.076830;0.574536;,
  0.182963;0.549818;,
  0.076830;0.549895;,
  0.182963;0.539580;,
  0.076830;0.539688;,
  0.066702;0.549902;,
  0.066702;0.574536;,
  0.066702;0.599170;,
  0.066702;0.602780;,
  0.066702;0.599170;,
  0.066702;0.574536;,
  0.066702;0.549902;,
  0.066702;0.546292;;
 }
}
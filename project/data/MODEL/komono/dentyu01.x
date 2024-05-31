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
 214;
 0.00000;153.80633;-5.77741;,
 4.18840;153.80633;-4.08524;,
 4.18840;0.20976;-4.08524;,
 0.00000;0.20976;-5.77741;,
 5.92329;153.80633;0.00000;,
 5.92329;0.20976;0.00000;,
 4.18840;153.80633;4.08524;,
 4.18840;0.20976;4.08524;,
 0.00000;153.80633;5.77741;,
 0.00000;0.20976;5.77741;,
 -4.18840;153.80633;4.08524;,
 -4.18840;0.20976;4.08524;,
 -5.92329;153.80633;0.00000;,
 -5.92329;0.20976;0.00000;,
 -4.18840;153.80633;-4.08524;,
 -4.18840;0.20976;-4.08524;,
 0.00000;153.80633;0.00000;,
 0.00000;0.20976;0.00000;,
 -11.80827;151.41250;-30.56313;,
 -5.97365;151.41250;-30.56313;,
 -5.97365;149.45526;-30.56313;,
 -11.80827;149.45526;-30.56313;,
 -5.97365;151.41250;30.56313;,
 -5.97365;149.45526;30.56313;,
 -11.80827;151.41250;30.56313;,
 -11.80827;149.45526;30.56313;,
 -11.80827;132.11073;-30.56313;,
 -5.97365;132.11073;-30.56313;,
 -5.97365;130.15349;-30.56313;,
 -11.80827;130.15349;-30.56313;,
 -5.97365;132.11073;30.56313;,
 -5.97365;130.15349;30.56313;,
 -11.80827;132.11073;30.56313;,
 -11.80827;130.15349;30.56313;,
 -229.13748;145.03552;-29.64080;,
 -11.97449;151.18841;-29.64080;,
 -11.97449;150.86831;-29.64080;,
 -229.13748;144.71543;-29.64080;,
 -11.97449;151.18841;-29.20025;,
 -11.97449;150.86831;-29.20025;,
 -229.13748;145.03552;-29.20025;,
 -229.13748;144.71543;-29.20025;,
 -229.13748;145.03552;-23.82209;,
 -11.97449;151.18841;-23.82209;,
 -11.97449;150.86831;-23.82209;,
 -229.13748;144.71543;-23.82209;,
 -11.97449;151.18841;-23.38155;,
 -11.97449;150.86831;-23.38155;,
 -229.13748;145.03552;-23.38155;,
 -229.13748;144.71543;-23.38155;,
 -229.13748;145.03552;-16.43270;,
 -11.97449;151.18841;-16.43270;,
 -11.97449;150.86831;-16.43270;,
 -229.13748;144.71543;-16.43270;,
 -11.97449;151.18841;-15.99215;,
 -11.97449;150.86831;-15.99215;,
 -229.13748;145.03552;-15.99215;,
 -229.13748;144.71543;-15.99215;,
 -229.13748;145.03552;-9.08690;,
 -11.97449;151.18841;-9.08690;,
 -11.97449;150.86831;-9.08690;,
 -229.13748;144.71543;-9.08690;,
 -11.97449;151.18841;-8.64636;,
 -11.97449;150.86831;-8.64636;,
 -229.13748;145.03552;-8.64636;,
 -229.13748;144.71543;-8.64636;,
 -229.13748;145.03552;10.43755;,
 -11.97449;151.18841;10.43755;,
 -11.97449;150.86831;10.43755;,
 -229.13748;144.71543;10.43755;,
 -11.97449;151.18841;10.87809;,
 -11.97449;150.86831;10.87809;,
 -229.13748;145.03552;10.87809;,
 -229.13748;144.71543;10.87809;,
 -229.13748;145.03552;15.88376;,
 -11.97449;151.18841;15.88376;,
 -11.97449;150.86831;15.88376;,
 -229.13748;144.71543;15.88376;,
 -11.97449;151.18841;16.32430;,
 -11.97449;150.86831;16.32430;,
 -229.13748;145.03552;16.32430;,
 -229.13748;144.71543;16.32430;,
 -229.13748;145.03552;22.91803;,
 -11.97449;151.18841;22.91803;,
 -11.97449;150.86831;22.91803;,
 -229.13748;144.71543;22.91803;,
 -11.97449;151.18841;23.35858;,
 -11.97449;150.86831;23.35858;,
 -229.13748;145.03552;23.35858;,
 -229.13748;144.71543;23.35858;,
 -229.13748;145.03552;28.68661;,
 -11.97449;151.18841;28.68661;,
 -11.97449;150.86831;28.68661;,
 -229.13748;144.71543;28.68661;,
 -11.97449;151.18841;29.12715;,
 -11.97449;150.86831;29.12715;,
 -229.13748;145.03552;29.12715;,
 -229.13748;144.71543;29.12715;,
 5.89532;108.14998;2.19542;,
 8.13470;108.14998;2.19542;,
 8.13470;108.14998;-2.19542;,
 5.89532;108.14998;-2.19542;,
 5.89532;88.14998;-2.19542;,
 8.13470;88.14998;-2.19542;,
 8.13470;88.14998;2.19542;,
 5.89532;88.14998;2.19542;,
 5.89532;105.09518;2.19542;,
 5.89532;105.09518;-2.19542;,
 8.13470;105.09518;2.19542;,
 8.13470;105.09518;-2.19542;,
 5.89532;94.97888;2.19542;,
 5.89532;94.97888;-2.19542;,
 8.13470;94.97888;2.19542;,
 8.13470;94.97888;-2.19542;,
 12.78134;110.00065;2.19542;,
 12.78134;110.00065;-2.19542;,
 12.78134;106.94585;2.19542;,
 12.78134;106.94585;-2.19542;,
 5.89532;97.66898;2.19542;,
 5.89532;97.66898;-2.19542;,
 8.13470;97.66898;2.19542;,
 8.13470;97.66898;-2.19542;,
 12.24417;96.91416;-2.19542;,
 12.24417;94.22406;-2.19542;,
 12.24417;96.91416;2.19542;,
 12.24417;94.22406;2.19542;,
 -5.63323;108.14998;-2.19542;,
 -7.87261;108.14998;-2.19542;,
 -7.87261;108.14998;2.19542;,
 -5.63323;108.14998;2.19542;,
 -5.63323;88.14998;2.19542;,
 -7.87261;88.14998;2.19542;,
 -7.87261;88.14998;-2.19542;,
 -5.63323;88.14998;-2.19542;,
 -5.63323;105.09518;-2.19542;,
 -5.63323;105.09518;2.19542;,
 -7.87261;105.09518;-2.19542;,
 -7.87261;105.09518;2.19542;,
 -5.63323;94.97888;-2.19542;,
 -5.63323;94.97888;2.19542;,
 -7.87261;94.97888;-2.19542;,
 -7.87261;94.97888;2.19542;,
 -12.51925;110.00065;-2.19542;,
 -12.51925;110.00065;2.19542;,
 -12.51925;106.94585;-2.19542;,
 -12.51925;106.94585;2.19542;,
 -5.63323;97.66898;-2.19542;,
 -5.63323;97.66898;2.19542;,
 -7.87261;97.66898;-2.19542;,
 -7.87261;97.66898;2.19542;,
 -11.98207;96.91416;2.19542;,
 -11.98207;94.22406;2.19542;,
 -11.98207;96.91416;-2.19542;,
 -11.98207;94.22406;-2.19542;,
 18.90601;112.49407;-7.34014;,
 23.72214;112.49407;-5.19026;,
 23.72214;92.49407;-5.19026;,
 18.90601;92.49407;-7.34014;,
 25.71704;112.49407;0.00000;,
 25.71704;92.49407;0.00000;,
 23.72214;112.49407;5.19026;,
 23.72214;92.49407;5.19026;,
 18.90601;112.49407;7.34014;,
 18.90601;92.49407;7.34014;,
 14.08988;112.49407;5.19026;,
 14.08988;92.49407;5.19026;,
 12.09497;112.49407;0.00000;,
 12.09497;92.49407;0.00000;,
 14.08988;112.49407;-5.19026;,
 14.08988;92.49407;-5.19026;,
 18.90601;112.49407;0.00000;,
 18.90601;92.49407;0.00000;,
 -18.16393;112.49407;-7.34014;,
 -13.34780;112.49407;-5.19026;,
 -13.34780;92.49407;-5.19026;,
 -18.16393;92.49407;-7.34014;,
 -11.35289;112.49407;0.00000;,
 -11.35289;92.49407;0.00000;,
 -13.34780;112.49407;5.19026;,
 -13.34780;92.49407;5.19026;,
 -18.16393;112.49407;7.34014;,
 -18.16393;92.49407;7.34014;,
 -22.98006;112.49407;5.19026;,
 -22.98006;92.49407;5.19026;,
 -24.97496;112.49407;0.00000;,
 -24.97496;92.49407;0.00000;,
 -22.98005;112.49407;-5.19026;,
 -22.98005;92.49407;-5.19026;,
 -18.16393;112.49407;0.00000;,
 -18.16393;92.49407;0.00000;,
 -229.00948;72.47106;-0.61367;,
 -5.37080;72.47107;-1.12289;,
 -5.37080;72.47106;-0.80279;,
 -229.00948;72.47106;-0.29358;,
 -5.37080;72.91160;-1.12289;,
 -5.37080;72.91161;-0.80280;,
 -229.00948;72.91161;-0.61367;,
 -229.00948;72.91161;-0.29358;,
 -229.00948;78.28977;-0.61367;,
 -5.37080;78.28977;-1.12288;,
 -5.37080;78.28977;-0.80279;,
 -229.00948;78.28978;-0.29358;,
 -5.37080;78.73032;-1.12289;,
 -5.37080;78.73032;-0.80279;,
 -229.00948;78.73032;-0.61367;,
 -229.00948;78.73031;-0.29357;,
 -229.00948;85.67916;-0.61367;,
 -5.37080;85.67916;0.70603;,
 -5.37080;85.67917;1.02611;,
 -229.00948;85.67916;-0.29358;,
 -5.37080;86.11971;0.70602;,
 -5.37080;86.11971;1.02612;,
 -229.00948;86.11971;-0.61366;,
 -229.00948;86.11971;-0.29358;;
 
 202;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,0,3,15;,
 3;16,1,0;,
 3;16,4,1;,
 3;16,6,4;,
 3;16,8,6;,
 3;16,10,8;,
 3;16,12,10;,
 3;16,14,12;,
 3;16,0,14;,
 3;17,3,2;,
 3;17,2,5;,
 3;17,5,7;,
 3;17,7,9;,
 3;17,9,11;,
 3;17,11,13;,
 3;17,13,15;,
 3;17,15,3;,
 4;18,19,20,21;,
 4;19,22,23,20;,
 4;22,24,25,23;,
 4;24,18,21,25;,
 4;24,22,19,18;,
 4;21,20,23,25;,
 4;26,27,28,29;,
 4;27,30,31,28;,
 4;30,32,33,31;,
 4;32,26,29,33;,
 4;32,30,27,26;,
 4;29,28,31,33;,
 4;34,35,36,37;,
 4;35,38,39,36;,
 4;38,40,41,39;,
 4;40,34,37,41;,
 4;40,38,35,34;,
 4;37,36,39,41;,
 4;42,43,44,45;,
 4;43,46,47,44;,
 4;46,48,49,47;,
 4;48,42,45,49;,
 4;48,46,43,42;,
 4;45,44,47,49;,
 4;50,51,52,53;,
 4;51,54,55,52;,
 4;54,56,57,55;,
 4;56,50,53,57;,
 4;56,54,51,50;,
 4;53,52,55,57;,
 4;58,59,60,61;,
 4;59,62,63,60;,
 4;62,64,65,63;,
 4;64,58,61,65;,
 4;64,62,59,58;,
 4;61,60,63,65;,
 4;66,67,68,69;,
 4;67,70,71,68;,
 4;70,72,73,71;,
 4;72,66,69,73;,
 4;72,70,67,66;,
 4;69,68,71,73;,
 4;74,75,76,77;,
 4;75,78,79,76;,
 4;78,80,81,79;,
 4;80,74,77,81;,
 4;80,78,75,74;,
 4;77,76,79,81;,
 4;82,83,84,85;,
 4;83,86,87,84;,
 4;86,88,89,87;,
 4;88,82,85,89;,
 4;88,86,83,82;,
 4;85,84,87,89;,
 4;90,91,92,93;,
 4;91,94,95,92;,
 4;94,96,97,95;,
 4;96,90,93,97;,
 4;96,94,91,90;,
 4;93,92,95,97;,
 4;98,99,100,101;,
 4;102,103,104,105;,
 4;106,98,101,107;,
 4;99,98,106,108;,
 4;100,109,107,101;,
 4;102,105,110,111;,
 4;104,112,110,105;,
 4;103,102,111,113;,
 4;103,113,112,104;,
 4;114,115,100,99;,
 4;116,114,99,108;,
 4;117,116,108,109;,
 4;115,117,109,100;,
 4;115,114,116,117;,
 4;111,110,118,119;,
 4;107,119,118,106;,
 4;108,106,118,120;,
 4;118,110,112,120;,
 4;109,108,120,121;,
 4;109,121,119,107;,
 4;113,111,119,121;,
 4;122,123,113,121;,
 4;124,122,121,120;,
 4;125,124,120,112;,
 4;123,125,112,113;,
 4;123,122,124,125;,
 4;126,127,128,129;,
 4;130,131,132,133;,
 4;134,126,129,135;,
 4;127,126,134,136;,
 4;128,137,135,129;,
 4;130,133,138,139;,
 4;132,140,138,133;,
 4;131,130,139,141;,
 4;131,141,140,132;,
 4;142,143,128,127;,
 4;144,142,127,136;,
 4;145,144,136,137;,
 4;143,145,137,128;,
 4;143,142,144,145;,
 4;139,138,146,147;,
 4;135,147,146,134;,
 4;136,134,146,148;,
 4;146,138,140,148;,
 4;137,136,148,149;,
 4;137,149,147,135;,
 4;141,139,147,149;,
 4;150,151,141,149;,
 4;152,150,149,148;,
 4;153,152,148,140;,
 4;151,153,140,141;,
 4;151,150,152,153;,
 4;154,155,156,157;,
 4;155,158,159,156;,
 4;158,160,161,159;,
 4;160,162,163,161;,
 4;162,164,165,163;,
 4;164,166,167,165;,
 4;166,168,169,167;,
 4;168,154,157,169;,
 3;170,155,154;,
 3;170,158,155;,
 3;170,160,158;,
 3;170,162,160;,
 3;170,164,162;,
 3;170,166,164;,
 3;170,168,166;,
 3;170,154,168;,
 3;171,157,156;,
 3;171,156,159;,
 3;171,159,161;,
 3;171,161,163;,
 3;171,163,165;,
 3;171,165,167;,
 3;171,167,169;,
 3;171,169,157;,
 4;172,173,174,175;,
 4;173,176,177,174;,
 4;176,178,179,177;,
 4;178,180,181,179;,
 4;180,182,183,181;,
 4;182,184,185,183;,
 4;184,186,187,185;,
 4;186,172,175,187;,
 3;188,173,172;,
 3;188,176,173;,
 3;188,178,176;,
 3;188,180,178;,
 3;188,182,180;,
 3;188,184,182;,
 3;188,186,184;,
 3;188,172,186;,
 3;189,175,174;,
 3;189,174,177;,
 3;189,177,179;,
 3;189,179,181;,
 3;189,181,183;,
 3;189,183,185;,
 3;189,185,187;,
 3;189,187,175;,
 4;190,191,192,193;,
 4;191,194,195,192;,
 4;194,196,197,195;,
 4;196,190,193,197;,
 4;196,194,191,190;,
 4;193,192,195,197;,
 4;198,199,200,201;,
 4;199,202,203,200;,
 4;202,204,205,203;,
 4;204,198,201,205;,
 4;204,202,199,198;,
 4;201,200,203,205;,
 4;206,207,208,209;,
 4;207,210,211,208;,
 4;210,212,213,211;,
 4;212,206,209,213;,
 4;212,210,207,206;,
 4;209,208,211,213;;
 
 MeshMaterialList {
  4;
  202;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
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
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Pictures\\team\\metal_00003.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Pictures\\team\\metal02.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.200000;0.200000;0.200000;;
   0.200000;0.200000;0.200000;;
   TextureFilename {
    "C:\\Users\\student\\Pictures\\team\\metal_00003.jpg";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
}

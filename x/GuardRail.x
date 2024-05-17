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
 204;
 -27.67869;19.63102;-1.57178;,
 -26.55612;19.63102;-1.11141;,
 -26.55612;-0.36898;-1.11141;,
 -27.67869;-0.36898;-1.57178;,
 -26.09115;19.63102;0.00000;,
 -26.09115;-0.36898;0.00000;,
 -26.55612;19.63102;1.11141;,
 -26.55612;-0.36898;1.11141;,
 -27.67869;19.63102;1.57178;,
 -27.67869;-0.36898;1.57178;,
 -28.80125;19.63102;1.11141;,
 -28.80125;-0.36898;1.11141;,
 -29.26622;19.63102;-0.00000;,
 -29.26622;-0.36898;-0.00000;,
 -28.80125;19.63102;-1.11141;,
 -28.80125;-0.36898;-1.11141;,
 -27.67869;19.63102;0.00000;,
 -27.67869;-0.36898;0.00000;,
 27.58066;19.63102;-1.57178;,
 28.70322;19.63102;-1.11141;,
 28.70322;-0.36898;-1.11141;,
 27.58066;-0.36898;-1.57178;,
 29.16820;19.63102;0.00000;,
 29.16820;-0.36898;0.00000;,
 28.70322;19.63102;1.11141;,
 28.70322;-0.36898;1.11141;,
 27.58066;19.63102;1.57178;,
 27.58066;-0.36898;1.57178;,
 26.45810;19.63102;1.11141;,
 26.45810;-0.36898;1.11141;,
 25.99312;19.63102;-0.00000;,
 25.99312;-0.36898;-0.00000;,
 26.45810;19.63102;-1.11141;,
 26.45810;-0.36898;-1.11141;,
 27.58066;19.63102;0.00000;,
 27.58066;-0.36898;-0.00000;,
 22.75109;14.70400;-1.69287;,
 22.75109;10.69075;-1.83599;,
 22.75109;10.74580;-1.74063;,
 22.75109;14.70400;-1.58275;,
 22.75109;10.16941;-1.53499;,
 22.75109;10.22446;-1.43963;,
 22.75109;18.70214;-1.72993;,
 22.75109;18.75720;-1.82528;,
 22.75109;19.18640;-1.45034;,
 22.75109;19.24146;-1.54570;,
 35.31257;10.16941;1.74719;,
 35.22520;10.69075;1.96003;,
 35.15777;10.74580;1.89260;,
 35.24515;10.22446;1.67976;,
 35.12400;14.70400;1.85882;,
 35.04614;14.70400;1.78096;,
 35.15020;18.70214;1.88503;,
 35.21763;18.75720;1.95246;,
 35.15689;19.24146;1.75476;,
 35.16532;19.18640;1.68733;,
 31.90538;10.22446;-1.43963;,
 31.90538;10.74580;-1.74063;,
 31.90538;14.70400;-1.69287;,
 31.90538;10.69075;-1.83599;,
 31.90538;14.70400;-1.58275;,
 31.90538;18.70214;-1.72993;,
 31.90538;19.24146;-1.54570;,
 31.90538;18.75720;-1.82528;,
 31.90538;19.18640;-1.45034;,
 31.90538;10.16941;-1.53499;,
 33.94027;19.18640;-1.45034;,
 33.94027;19.24146;-1.54570;,
 33.94027;14.70400;-1.58275;,
 33.94027;18.70214;-1.72993;,
 36.12842;19.24146;-1.54570;,
 36.12842;19.18640;-1.45034;,
 36.12842;14.70400;-1.58275;,
 36.12842;18.70214;-1.72993;,
 33.94027;18.75720;-1.82528;,
 33.94027;14.70400;-1.69287;,
 36.12842;18.75720;-1.82528;,
 36.12842;14.70400;-1.69287;,
 36.12842;10.69075;-1.83599;,
 33.94027;10.69075;-1.83599;,
 33.94027;10.74580;-1.74063;,
 36.12842;10.74580;-1.74063;,
 37.95234;10.74580;-0.04493;,
 37.81562;14.70400;0.03401;,
 37.91098;14.70400;-0.02105;,
 38.03492;10.69075;-0.09261;,
 37.94307;18.70214;-0.03958;,
 37.70094;19.18640;0.10022;,
 37.78352;19.24146;0.05254;,
 38.02565;18.75720;-0.08726;,
 37.77425;10.16941;0.05789;,
 36.12842;10.16941;-1.53499;,
 36.12842;10.22446;-1.43963;,
 37.69167;10.22446;0.10557;,
 33.94027;10.16941;-1.53499;,
 33.94027;10.22446;-1.43963;,
 37.63286;10.16941;1.84202;,
 37.55785;10.22446;1.83214;,
 37.78619;18.70214;1.86220;,
 37.67043;14.70400;1.84696;,
 37.75703;14.70400;1.85837;,
 37.86119;18.75720;1.87208;,
 37.56627;19.18640;1.83325;,
 37.64128;19.24146;1.84313;,
 37.86961;10.69075;1.87319;,
 37.79460;10.74580;1.86331;,
 -20.27816;19.25569;-1.27735;,
 22.78218;19.25569;-1.27735;,
 22.78218;19.25569;-1.45244;,
 -20.27816;19.25569;-1.45244;,
 -20.27816;10.12872;-1.48003;,
 22.78218;10.12872;-1.48003;,
 22.78218;10.12872;-1.30494;,
 -20.27816;10.12872;-1.30494;,
 -20.27816;17.62059;-1.67460;,
 22.78218;17.62059;-1.67460;,
 22.78218;17.62059;-1.84969;,
 -20.27816;17.62059;-1.84969;,
 22.78218;11.62153;-1.63215;,
 -20.27816;11.62153;-1.63215;,
 22.78218;11.62153;-1.80725;,
 -20.27816;11.62153;-1.80725;,
 -20.27816;16.15640;-1.23106;,
 -20.27816;16.15640;-1.40616;,
 -20.27816;14.69220;-1.47711;,
 -20.27816;14.69220;-1.30202;,
 -20.27816;13.15687;-1.71600;,
 -20.27816;13.15687;-1.54090;,
 22.78218;16.15640;-1.23106;,
 22.78218;13.15687;-1.54090;,
 22.78218;14.69220;-1.30202;,
 22.78218;13.15687;-1.71600;,
 22.78218;14.69220;-1.47711;,
 22.78218;16.15640;-1.40616;,
 -20.26514;14.70687;-1.69287;,
 -20.26514;18.72011;-1.83599;,
 -20.26514;18.66506;-1.74063;,
 -20.26514;14.70687;-1.58275;,
 -20.26514;19.24145;-1.53499;,
 -20.26514;19.18640;-1.43963;,
 -20.26514;10.70873;-1.72993;,
 -20.26514;10.65367;-1.82528;,
 -20.26514;10.22446;-2.45590;,
 -20.26514;10.16941;-1.54570;,
 -32.82658;19.24146;1.74719;,
 -32.73922;18.72011;1.96003;,
 -32.67179;18.66506;1.89260;,
 -32.75916;19.18640;1.67976;,
 -32.63802;14.70687;1.85882;,
 -32.56015;14.70687;1.78096;,
 -32.66422;10.70873;1.88503;,
 -32.73165;10.65367;1.95246;,
 -32.67090;10.16941;1.75476;,
 -32.67934;10.22446;1.68733;,
 -29.41940;19.18640;-1.43963;,
 -29.41940;18.66506;-1.74063;,
 -29.41939;14.70686;-1.69287;,
 -29.41940;18.72011;-1.83599;,
 -29.41939;14.70686;-1.58275;,
 -29.41940;10.70873;-1.72993;,
 -29.41940;10.16941;-1.54570;,
 -29.41940;10.65367;-1.82528;,
 -29.41939;10.22446;-1.45034;,
 -29.41940;19.24146;-1.53499;,
 -31.45429;10.22446;-1.45034;,
 -31.45429;10.16941;-1.54570;,
 -31.45429;14.70686;-1.58275;,
 -31.45429;10.70872;-1.72993;,
 -33.64244;10.16940;-1.54570;,
 -33.64244;10.22446;-1.45034;,
 -33.64244;14.70686;-1.58275;,
 -33.64244;10.70872;-1.72993;,
 -31.45429;10.65367;-1.82528;,
 -31.45429;14.70686;-1.69287;,
 -33.64243;10.65367;-1.82528;,
 -33.64244;14.70686;-1.69287;,
 -33.64244;18.72012;-1.83599;,
 -31.45429;18.72012;-1.83599;,
 -31.45429;18.66506;-1.74063;,
 -33.64244;18.66506;-1.74063;,
 -35.47648;18.66506;-0.28684;,
 -35.33976;14.70687;-0.20790;,
 -35.43512;14.70686;-0.26295;,
 -35.55907;18.72012;-0.33451;,
 -35.46721;10.70873;-0.28148;,
 -35.22508;10.22446;-0.14169;,
 -35.30766;10.16941;-0.18937;,
 -35.54980;10.65367;-0.32916;,
 -35.29840;19.24145;-0.18402;,
 -33.64243;19.24146;-1.53499;,
 -33.64244;19.18640;-1.43963;,
 -35.21582;19.18640;-0.13634;,
 -31.45429;19.24146;-1.53499;,
 -31.45429;19.18640;-1.43963;,
 -35.14687;19.24145;1.84202;,
 -35.07187;19.18640;1.83214;,
 -35.30020;10.70872;1.86220;,
 -35.18444;14.70687;1.84696;,
 -35.27105;14.70687;1.85837;,
 -35.37520;10.65367;1.87208;,
 -35.08029;10.22446;1.83325;,
 -35.15529;10.16941;1.84313;,
 -35.38362;18.72011;1.87319;,
 -35.30862;18.66506;1.86331;;
 
 212;
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
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,18,21,33;,
 3;34,19,18;,
 3;34,22,19;,
 3;34,24,22;,
 3;34,26,24;,
 3;34,28,26;,
 3;34,30,28;,
 3;34,32,30;,
 3;34,18,32;,
 3;35,21,20;,
 3;35,20,23;,
 3;35,23,25;,
 3;35,25,27;,
 3;35,27,29;,
 3;35,29,31;,
 3;35,31,33;,
 3;35,33,21;,
 4;36,37,38,39;,
 4;40,41,38,37;,
 4;42,43,36,39;,
 4;42,44,45,43;,
 4;46,47,48,49;,
 4;50,51,48,47;,
 4;52,51,50,53;,
 4;54,55,52,53;,
 4;56,57,38,41;,
 4;36,58,59,37;,
 4;57,60,39,38;,
 4;39,60,61,42;,
 4;62,63,43,45;,
 4;61,64,44,42;,
 4;58,36,43,63;,
 4;40,65,56,41;,
 4;37,59,65,40;,
 4;64,62,45,44;,
 4;62,64,66,67;,
 4;61,60,68,69;,
 4;70,67,66,71;,
 4;68,72,73,69;,
 4;63,74,75,58;,
 4;75,74,76,77;,
 4;77,78,79,75;,
 4;80,81,72,68;,
 4;60,57,80,68;,
 4;58,75,79,59;,
 4;72,81,82,83;,
 4;77,84,85,78;,
 4;73,72,83,86;,
 4;71,73,86,87;,
 4;76,70,88,89;,
 4;71,66,69,73;,
 4;70,76,74,67;,
 4;62,67,74,63;,
 4;64,61,69,66;,
 4;78,85,90,91;,
 4;82,81,92,93;,
 4;94,79,78,91;,
 4;80,95,92,81;,
 4;56,95,80,57;,
 4;94,65,59,79;,
 4;70,71,87,88;,
 4;91,92,95,94;,
 4;91,90,93,92;,
 4;65,94,95,56;,
 4;76,89,84,77;,
 3;96,93,90;,
 3;97,93,96;,
 4;51,52,98,99;,
 4;53,50,100,101;,
 4;98,86,83,99;,
 4;89,101,100,84;,
 4;98,102,87,86;,
 4;89,88,103,101;,
 4;98,52,55,102;,
 4;53,101,103,54;,
 4;54,103,102,55;,
 4;102,103,88,87;,
 4;47,104,100,50;,
 4;99,83,82,105;,
 4;85,84,100,104;,
 4;99,105,48,51;,
 4;49,48,105,97;,
 4;96,104,47,46;,
 4;93,97,105,82;,
 4;85,104,96,90;,
 4;97,96,46,49;,
 4;106,107,108,109;,
 4;110,111,112,113;,
 4;107,106,114,115;,
 4;108,116,117,109;,
 4;109,117,114,106;,
 4;108,107,115,116;,
 4;112,118,119,113;,
 4;120,111,110,121;,
 4;110,113,119,121;,
 4;111,120,118,112;,
 4;122,114,117,123;,
 4;124,125,122,123;,
 4;124,126,127,125;,
 4;121,119,127,126;,
 4;115,114,122,128;,
 4;127,129,130,125;,
 4;130,128,122,125;,
 4;118,129,127,119;,
 4;131,126,124,132;,
 4;117,116,133,123;,
 4;124,123,133,132;,
 4;116,115,128,133;,
 4;128,130,132,133;,
 4;132,130,129,131;,
 4;120,131,129,118;,
 4;121,126,131,120;,
 4;134,135,136,137;,
 4;138,139,136,135;,
 4;140,141,134,137;,
 4;140,142,143,141;,
 4;144,145,146,147;,
 4;148,149,146,145;,
 4;150,149,148,151;,
 4;152,153,150,151;,
 4;154,155,136,139;,
 4;134,156,157,135;,
 4;155,158,137,136;,
 4;137,158,159,140;,
 4;160,161,141,143;,
 4;159,162,142,140;,
 4;156,134,141,161;,
 4;138,163,154,139;,
 4;135,157,163,138;,
 4;162,160,143,142;,
 4;160,162,164,165;,
 4;159,158,166,167;,
 4;168,165,164,169;,
 4;166,170,171,167;,
 4;161,172,173,156;,
 4;173,172,174,175;,
 4;175,176,177,173;,
 4;178,179,170,166;,
 4;158,155,178,166;,
 4;156,173,177,157;,
 4;170,179,180,181;,
 4;175,182,183,176;,
 4;171,170,181,184;,
 4;169,171,184,185;,
 4;174,168,186,187;,
 4;169,164,167,171;,
 4;168,174,172,165;,
 4;160,165,172,161;,
 4;162,159,167,164;,
 4;176,183,188,189;,
 4;180,179,190,191;,
 4;192,177,176,189;,
 4;178,193,190,179;,
 4;154,193,178,155;,
 4;192,163,157,177;,
 4;168,169,185,186;,
 4;189,190,193,192;,
 4;189,188,191,190;,
 4;163,192,193,154;,
 4;174,187,182,175;,
 3;194,191,188;,
 3;195,191,194;,
 4;149,150,196,197;,
 4;151,148,198,199;,
 4;196,184,181,197;,
 4;187,199,198,182;,
 4;196,200,185,184;,
 4;187,186,201,199;,
 4;196,150,153,200;,
 4;151,199,201,152;,
 4;152,201,200,153;,
 4;200,201,186,185;,
 4;145,202,198,148;,
 4;197,181,180,203;,
 4;183,182,198,202;,
 4;197,203,146,149;,
 4;147,146,203,195;,
 4;194,202,145,144;,
 4;191,195,203,180;,
 4;183,202,194,188;,
 4;195,194,144,147;;
 
 MeshMaterialList {
  1;
  212;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.797647;0.797647;0.797647;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
}

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
 266;
 -1.03356;10.11290;-13.97580;,
 0.26362;10.11290;-13.97580;,
 0.26362;9.36005;-13.71143;,
 -1.03356;9.36005;-13.71143;,
 2.74765;24.11110;-6.79853;,
 2.38150;24.11110;-10.15678;,
 -3.15143;24.11110;-10.15678;,
 -3.51758;24.11110;-6.79853;,
 -4.66719;16.98859;12.80857;,
 3.89726;16.98859;12.80857;,
 3.89726;17.90713;12.80857;,
 -4.66719;17.90713;12.80857;,
 -3.15143;1.97884;-10.15678;,
 2.38150;1.97884;-10.15678;,
 2.74765;1.97884;-6.79853;,
 -3.51758;1.97884;-6.79853;,
 5.19473;10.53481;-7.53794;,
 6.76817;16.74052;-3.38596;,
 6.76817;15.93653;-3.28587;,
 5.19473;9.74505;-7.39221;,
 -7.53810;16.74052;-3.38596;,
 -5.96466;10.53481;-7.53794;,
 -5.96466;9.74505;-7.39221;,
 -7.53810;15.93653;-3.28587;,
 -1.54623;8.90000;-14.20426;,
 -0.94268;8.90000;-14.20426;,
 -0.61543;1.72551;-19.62241;,
 0.17275;8.90000;-14.20426;,
 -0.49565;1.72551;-19.62241;,
 -0.27428;1.72551;-19.62241;,
 -0.15450;1.72551;-19.62241;,
 0.77629;8.90000;-14.20426;,
 5.37533;9.48361;-7.48339;,
 7.01915;15.69613;-3.35350;,
 6.13772;1.97884;-6.79853;,
 5.37533;1.97884;-10.15678;,
 -7.78908;15.69613;-3.35350;,
 -6.14526;9.48361;-7.48339;,
 -6.14526;1.97884;-10.15678;,
 -6.90765;1.97884;-6.79853;,
 5.37534;22.23712;-10.15678;,
 6.13772;22.23712;-6.79853;,
 7.01915;16.90209;-3.50365;,
 5.37533;10.66828;-7.70201;,
 -0.54066;20.11406;-25.21988;,
 -0.22928;20.11406;-25.21988;,
 -0.17003;19.51174;-26.37974;,
 -0.59991;19.51174;-26.37974;,
 -6.90765;22.23712;-6.79853;,
 -6.14526;22.23712;-10.15678;,
 -6.14526;10.66828;-7.70201;,
 -7.78907;16.90209;-3.50365;,
 0.77629;10.02926;-14.60081;,
 -0.06078;19.52330;-26.38443;,
 0.96552;9.36005;-13.71143;,
 0.96552;10.11290;-13.97580;,
 -0.15450;1.72551;-19.62241;,
 0.77629;8.90000;-14.20426;,
 -0.27428;1.72551;-19.62241;,
 -1.54623;8.90000;-14.20426;,
 -0.61543;1.72551;-19.62241;,
 -1.73545;10.11290;-13.97580;,
 -1.73545;9.36005;-13.71143;,
 -0.70915;19.52330;-26.38443;,
 -1.54623;10.02926;-14.60081;,
 -1.03356;9.36005;-13.71143;,
 0.26362;9.36005;-13.71143;,
 0.26362;10.11290;-13.97580;,
 -1.03356;10.11290;-13.97580;,
 -0.94268;10.02926;-14.60081;,
 0.17275;10.02926;-14.60081;,
 5.19473;9.74505;-7.39221;,
 6.76817;15.93653;-3.28587;,
 7.81018;16.09416;0.56849;,
 7.40483;16.28857;0.58443;,
 7.40483;17.12367;0.58443;,
 7.81018;17.34684;0.56849;,
 6.76817;16.74052;-3.38596;,
 5.19473;10.53481;-7.53794;,
 -7.53810;15.93653;-3.28587;,
 -5.96466;9.74505;-7.39221;,
 -5.96466;10.53481;-7.53794;,
 -7.53810;16.74052;-3.38596;,
 -8.58010;17.34684;0.56849;,
 -8.17476;17.12367;0.58443;,
 -8.17476;16.28857;0.58443;,
 -8.58010;16.09416;0.56849;,
 0.96552;9.36005;-13.71143;,
 0.96552;10.11290;-13.97580;,
 -1.73545;9.36005;-13.71143;,
 -1.73545;10.11290;-13.97580;,
 -6.14526;1.97884;-10.15678;,
 -0.61543;1.72551;-19.62241;,
 -0.49565;1.72551;-19.62241;,
 -6.90765;1.97884;-6.79853;,
 -6.14526;22.23712;-10.15678;,
 -6.90765;22.23712;-6.79853;,
 -0.70915;19.52330;-26.38443;,
 -1.73545;10.11290;-13.97580;,
 -1.54623;10.02926;-14.60081;,
 -1.73545;9.36005;-13.71143;,
 0.96552;9.36005;-13.71143;,
 0.77629;10.02926;-14.60081;,
 0.96552;10.11290;-13.97580;,
 -0.06078;19.52330;-26.38443;,
 5.37534;22.23712;-10.15678;,
 6.13772;22.23712;-6.79853;,
 5.37533;1.97884;-10.15678;,
 6.13772;1.97884;-6.79853;,
 -0.15450;1.72551;-19.62241;,
 -0.70915;19.52330;-26.38443;,
 -0.59991;19.51174;-26.37974;,
 -0.17003;19.51174;-26.37974;,
 -0.06078;19.52330;-26.38443;,
 8.87267;17.85859;11.33713;,
 8.87476;21.55604;11.36767;,
 7.56016;20.50816;12.80857;,
 7.49779;17.90713;12.80857;,
 7.49779;17.90713;12.80857;,
 7.49718;16.98859;12.80857;,
 8.87271;16.91115;11.33776;,
 8.87267;17.85859;11.33713;,
 7.45074;9.58933;11.32143;,
 8.88320;7.25712;11.49084;,
 -8.26772;17.90713;12.80857;,
 -8.26812;20.46496;12.80857;,
 -9.64469;21.55604;11.36767;,
 -9.64260;17.85859;11.33713;,
 -9.64260;17.85859;11.33713;,
 -9.64265;16.91115;11.33776;,
 -8.26711;16.98859;12.80857;,
 -8.26772;17.90713;12.80857;,
 -9.65529;7.26777;11.52241;,
 -8.25711;9.55950;11.32143;,
 3.89726;9.58119;11.32143;,
 3.87330;7.30526;11.63378;,
 -4.64324;7.30526;11.63378;,
 -4.66719;9.58119;11.32143;,
 -4.41811;21.97297;12.80857;,
 -4.63873;23.42804;11.41281;,
 3.64818;21.97297;12.80857;,
 3.86880;23.42804;11.41281;,
 -4.66719;17.90713;12.80857;,
 3.89726;17.90713;12.80857;,
 8.87267;17.85859;11.33713;,
 8.87271;16.91115;11.33776;,
 -9.64265;16.91115;11.33776;,
 -9.64260;17.85859;11.33713;,
 8.88320;7.25712;11.49084;,
 7.81018;4.44603;0.53101;,
 -4.32080;3.42421;0.54653;,
 2.62631;3.37250;0.54732;,
 -7.65555;3.37250;0.54732;,
 -9.65529;7.26777;11.52241;,
 -4.63873;23.42804;11.39138;,
 3.86880;23.42804;11.39138;,
 3.55086;24.11110;0.54705;,
 -4.32080;24.11110;0.54705;,
 7.81018;22.23712;0.56849;,
 8.87476;21.55604;11.36767;,
 -9.64469;21.55604;11.36767;,
 -8.58010;22.23712;0.56849;,
 -7.65555;3.37250;0.54732;,
 -8.58010;22.23712;0.54705;,
 -9.64469;21.55604;11.34623;,
 8.87476;21.55604;11.34623;,
 7.81018;22.23712;0.54705;,
 7.81018;4.44603;0.53101;,
 -6.90765;1.97884;-6.79853;,
 -3.51758;1.97884;-6.79853;,
 2.74765;1.97884;-6.79853;,
 6.13772;1.97884;-6.79853;,
 7.40483;17.12367;0.58443;,
 7.40483;16.28857;0.58443;,
 6.13772;22.23712;-6.81997;,
 2.74765;24.11110;-6.81997;,
 -4.32080;24.11110;0.56849;,
 3.55086;24.11110;0.56849;,
 -8.58010;22.23712;0.56849;,
 -8.17476;16.28857;0.58443;,
 -8.17476;17.12367;0.58443;,
 3.18942;-5.04508;3.33058;,
 3.18942;5.25097;3.33058;,
 -0.11641;5.25097;4.69988;,
 -0.11641;-5.04508;4.69988;,
 -3.42224;5.25097;3.33058;,
 -3.42224;-5.04508;3.33058;,
 -4.79154;5.25097;0.02472;,
 -4.79154;-5.04508;0.02472;,
 -3.42224;5.25097;-3.28109;,
 -3.42224;-5.04508;-3.28109;,
 -0.11641;5.25097;-4.65043;,
 -0.11641;-5.04508;-4.65043;,
 3.18942;5.25097;-3.28109;,
 3.18942;-5.04508;-3.28109;,
 4.55874;5.25097;0.02472;,
 4.55874;-5.04508;0.02472;,
 3.18942;5.25097;3.33058;,
 -0.11641;5.25097;0.02472;,
 -0.11641;5.25097;4.69988;,
 -3.42224;5.25097;3.33058;,
 -4.79154;5.25097;0.02472;,
 -3.42224;5.25097;-3.28109;,
 -0.11641;5.25097;-4.65043;,
 3.18942;5.25097;-3.28109;,
 4.55874;5.25097;0.02472;,
 -8.01829;1.32725;-9.72377;,
 -9.91577;14.87198;2.85755;,
 9.91576;14.87198;2.85755;,
 8.01829;1.32725;-9.72377;,
 -9.91577;20.29473;2.80560;,
 -11.80875;20.88559;13.10326;,
 11.80875;20.88559;13.10326;,
 9.91576;20.29473;2.80560;,
 -11.93656;14.48456;13.99004;,
 -11.93656;7.69429;12.27474;,
 11.93655;7.69429;12.27474;,
 11.93655;14.48456;13.99004;,
 -11.41374;4.26989;8.58309;,
 -8.01829;1.32725;-9.72377;,
 8.01829;1.32725;-9.72377;,
 11.41373;4.26989;8.58309;,
 11.93655;14.48456;13.99004;,
 11.93655;7.69429;12.27474;,
 11.80875;15.46284;13.15522;,
 9.91576;14.87198;2.85755;,
 11.41373;4.26989;8.58309;,
 8.01829;1.32725;-9.72377;,
 11.80875;15.46284;13.15522;,
 -11.80875;15.46284;13.15522;,
 -8.01829;1.32725;-9.72377;,
 -11.41374;4.26989;8.58309;,
 -9.91577;14.87198;2.85755;,
 -11.80875;15.46284;13.15522;,
 -11.93656;7.69429;12.27474;,
 -11.93656;14.48456;13.99004;,
 -11.41374;4.26989;8.58309;,
 11.41373;4.26989;8.58309;,
 -9.91577;20.29473;2.80560;,
 9.91576;20.29473;2.80560;,
 9.91576;20.29473;2.80560;,
 11.80875;20.88559;13.10326;,
 11.80875;20.88559;13.10326;,
 -11.80875;20.88559;13.10326;,
 -11.80875;20.88559;13.10326;,
 -9.91577;20.29473;2.80560;,
 -4.32080;24.11110;0.56849;,
 -4.32080;24.11110;0.54705;,
 3.55086;24.11110;0.54705;,
 3.55086;24.11110;0.56849;,
 3.86880;23.42804;11.41281;,
 3.86880;23.42804;11.39138;,
 -4.63873;23.42804;11.39138;,
 -4.63873;23.42804;11.41281;,
 -8.58010;22.23712;0.56849;,
 -8.58010;22.23712;0.54705;,
 -9.64469;21.55604;11.34623;,
 -9.64469;21.55604;11.36767;,
 7.81018;22.23712;0.56849;,
 7.81018;22.23712;0.54705;,
 8.87476;21.55604;11.34623;,
 8.87476;21.55604;11.36767;,
 2.74765;24.11110;-6.81997;,
 2.74765;24.11110;-6.79853;,
 6.13772;22.23712;-6.81997;,
 6.13772;22.23712;-6.79853;;
 
 150;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 3;24,25,26;,
 3;25,27,26;,
 3;26,27,28;,
 3;28,27,29;,
 3;29,27,30;,
 3;30,27,31;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;6,5,45,44;,
 4;52,53,40,43;,
 4;54,55,16,19;,
 4;56,57,32,35;,
 3;58,13,12;,
 4;37,59,60,38;,
 4;21,61,62,22;,
 4;49,63,64,50;,
 4;65,66,27,25;,
 4;67,68,69,70;,
 4;32,71,72,33;,
 4;73,74,75,76;,
 4;77,78,43,42;,
 4;79,80,37,36;,
 4;50,81,82,51;,
 4;83,84,85,86;,
 4;57,87,71,32;,
 4;43,78,88,52;,
 4;37,80,89,59;,
 4;64,90,81,50;,
 3;91,92,12;,
 3;12,92,58;,
 3;58,92,93;,
 4;94,91,12,15;,
 4;95,96,7,6;,
 4;97,95,6,44;,
 3;97,44,47;,
 4;68,98,99,69;,
 4;62,61,0,3;,
 4;24,100,65,25;,
 4;66,101,31,27;,
 4;1,55,54,2;,
 4;102,103,67,70;,
 3;45,104,46;,
 4;5,105,104,45;,
 4;106,105,5,4;,
 4;13,107,108,14;,
 4;58,109,107,13;,
 4;99,110,111,69;,
 4;112,70,69,111;,
 4;113,102,70,112;,
 4;114,115,116,117;,
 4;118,119,120,121;,
 4;119,122,123,120;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;129,132,133,130;,
 4;122,134,135,123;,
 4;132,136,137,133;,
 4;136,135,134,137;,
 4;125,138,139,126;,
 4;138,140,141,139;,
 4;115,141,140,116;,
 4;137,134,9,8;,
 4;142,143,140,138;,
 4;76,144,145,73;,
 4;86,146,147,83;,
 4;73,145,148,149;,
 4;135,136,150,151;,
 4;152,153,146,86;,
 4;154,155,156,157;,
 4;158,159,144,76;,
 4;83,147,160,161;,
 4;136,132,162,150;,
 4;130,133,137,8;,
 4;131,130,8,11;,
 4;125,124,142,138;,
 4;163,164,154,157;,
 4;155,165,166,156;,
 4;143,117,116,140;,
 4;9,119,118,10;,
 4;134,122,119,9;,
 4;167,123,135,151;,
 4;162,168,169,150;,
 4;170,151,150,169;,
 4;171,167,151,170;,
 4;33,73,149,34;,
 4;72,74,73,33;,
 4;17,172,173,18;,
 4;76,75,77,42;,
 4;41,158,76,42;,
 4;156,166,174,175;,
 4;176,177,4,7;,
 4;96,178,176,7;,
 4;83,161,48,51;,
 4;82,84,83,51;,
 4;179,180,20,23;,
 4;86,85,79,36;,
 4;152,86,36,39;,
 4;181,182,183,184;,
 4;184,183,185,186;,
 4;186,185,187,188;,
 4;188,187,189,190;,
 4;190,189,191,192;,
 4;192,191,193,194;,
 4;194,193,195,196;,
 4;196,195,182,181;,
 3;197,198,199;,
 3;199,198,200;,
 3;200,198,201;,
 3;201,198,202;,
 3;202,198,203;,
 3;203,198,204;,
 3;204,198,205;,
 3;205,198,197;,
 4;206,207,208,209;,
 4;210,211,212,213;,
 4;214,215,216,217;,
 4;218,219,220,221;,
 3;222,223,224;,
 3;224,223,225;,
 3;223,226,225;,
 3;225,226,227;,
 4;214,217,228,229;,
 3;230,231,232;,
 3;232,231,233;,
 3;231,234,233;,
 3;233,234,235;,
 4;236,237,216,215;,
 4;207,238,239,208;,
 4;225,240,241,224;,
 4;228,242,243,229;,
 4;233,244,245,232;,
 4;246,247,248,249;,
 4;250,251,252,253;,
 4;254,255,247,246;,
 4;253,252,256,257;,
 4;257,256,255,254;,
 4;258,259,260,261;,
 4;261,260,251,250;,
 4;249,248,262,263;,
 4;263,262,264,265;,
 4;265,264,259,258;;
 
 MeshMaterialList {
  1;
  150;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\TEXTURE\\MATERIAL\\arms_01.png";
   }
  }
 }
 MeshNormals {
  189;
  -0.223122;0.558013;-0.799273;,
  0.303054;0.534100;-0.789237;,
  -0.892076;-0.186179;-0.411750;,
  0.892075;-0.186181;-0.411751;,
  -0.988312;0.006168;-0.152322;,
  0.988312;0.006168;-0.152322;,
  -0.989887;-0.045857;-0.134241;,
  0.988127;-0.001736;-0.153633;,
  -0.429827;0.562536;-0.706260;,
  0.429827;0.562534;-0.706261;,
  -0.039294;0.000000;-0.999228;,
  0.039295;0.000000;-0.999228;,
  -0.932616;-0.114984;-0.342060;,
  0.932616;-0.114985;-0.342060;,
  0.957513;-0.280802;-0.065723;,
  0.734250;0.330429;-0.593038;,
  0.888122;0.150750;-0.434180;,
  -0.888123;0.150750;-0.434180;,
  -0.734249;0.330431;-0.593037;,
  -0.957513;-0.280800;-0.065725;,
  -0.814742;0.160402;-0.557196;,
  0.814742;0.160397;-0.557197;,
  0.469650;-0.269303;-0.840776;,
  -0.469650;-0.269303;-0.840776;,
  0.901291;-0.095725;-0.422505;,
  0.767041;0.206863;-0.607334;,
  -0.767041;0.206866;-0.607334;,
  -0.901291;-0.095725;-0.422505;,
  0.000000;0.602651;-0.798005;,
  0.000000;-0.999911;0.013378;,
  0.000000;-0.999871;0.016054;,
  0.001907;-0.965096;0.261889;,
  0.047056;-0.964770;0.258854;,
  0.000057;-0.098930;0.995094;,
  0.000149;-0.098833;0.995104;,
  0.000000;0.000000;1.000000;,
  -0.227426;0.973093;-0.036968;,
  0.000000;1.000000;0.000000;,
  -0.270719;0.947575;-0.169745;,
  0.270718;0.947575;-0.169745;,
  -0.107772;0.915945;-0.386562;,
  0.107773;0.915945;-0.386561;,
  0.007496;-0.962999;-0.269400;,
  -0.007497;-0.962999;-0.269400;,
  0.000000;-0.331324;-0.943517;,
  0.000000;0.669326;-0.742968;,
  0.000000;0.641278;-0.767309;,
  0.056551;0.884865;-0.462403;,
  -0.056545;0.884865;-0.462403;,
  0.947711;-0.003188;0.319114;,
  0.399912;-0.003202;0.916548;,
  0.286893;-0.070882;0.955337;,
  0.555066;-0.035964;0.831028;,
  -0.397350;-0.000845;0.917667;,
  -0.946815;-0.000819;0.321778;,
  -0.551038;-0.034095;0.833784;,
  -0.284252;-0.069788;0.956206;,
  0.124139;-0.052388;0.990881;,
  0.185554;0.022008;0.982387;,
  -0.119848;-0.049132;0.991576;,
  -0.179522;0.026643;0.983393;,
  -0.005921;0.127285;0.991849;,
  -0.002850;-0.035177;0.999377;,
  -0.532060;0.632550;0.562843;,
  -0.365782;0.240460;0.899101;,
  -0.067753;0.361666;0.929842;,
  -0.165631;0.902581;0.397383;,
  0.535350;0.633965;0.558112;,
  0.369302;0.241455;0.897394;,
  0.003726;-0.036639;0.999322;,
  0.007243;0.124580;0.992183;,
  0.164737;0.903786;0.395009;,
  0.067141;0.364293;0.928861;,
  -0.971322;0.004946;-0.237718;,
  0.000998;-0.995439;0.095394;,
  0.023883;-0.994108;0.105734;,
  0.962282;0.031152;-0.270264;,
  0.795696;0.400734;-0.454181;,
  0.928172;0.286655;-0.237331;,
  0.909733;-0.414961;0.013916;,
  0.912495;-0.409004;0.008276;,
  0.971284;-0.015146;-0.237441;,
  0.129900;0.991295;-0.021456;,
  -0.244802;0.968742;-0.040135;,
  -0.971284;-0.015146;-0.237441;,
  -0.912497;-0.409000;0.008274;,
  -0.909735;-0.414957;0.013913;,
  -0.928172;0.286655;-0.237331;,
  -0.808720;0.390256;-0.440082;,
  0.707106;0.000000;0.707107;,
  -0.707108;0.000000;0.707106;,
  -1.000000;0.000000;-0.000003;,
  -0.707110;0.000000;-0.707104;,
  0.000000;0.000000;-1.000000;,
  0.707108;0.000000;-0.707106;,
  1.000000;0.000000;-0.000003;,
  0.000000;0.680569;-0.732684;,
  0.000000;0.361130;-0.932515;,
  0.000000;0.227492;0.973780;,
  0.000000;0.350411;0.936596;,
  0.986828;0.021600;-0.160324;,
  0.000000;-0.510001;0.860174;,
  0.000000;-0.898867;0.438221;,
  0.000000;0.998358;-0.057284;,
  -0.184952;0.982431;0.024949;,
  -0.191824;0.980158;0.049949;,
  0.209782;0.977725;0.006682;,
  0.184951;0.982431;0.024949;,
  -0.376495;0.925751;0.035172;,
  -0.363473;0.931439;0.017590;,
  0.410420;0.911710;-0.018426;,
  0.363473;0.931439;0.017590;,
  0.227426;0.973094;-0.036967;,
  0.442613;0.893822;-0.071946;,
  0.000000;-0.999642;0.026754;,
  0.000000;0.730999;-0.682378;,
  0.000000;-0.991165;0.132639;,
  0.260611;0.486168;-0.834100;,
  0.480656;-0.836684;0.262546;,
  -0.260611;0.486168;-0.834100;,
  -0.480661;-0.836682;0.262542;,
  0.172582;-0.984403;-0.034164;,
  0.086920;-0.994980;0.049596;,
  0.071200;-0.979497;-0.188459;,
  -0.071202;-0.979497;-0.188459;,
  -0.086921;-0.994980;0.049595;,
  -0.172584;-0.984402;-0.034165;,
  0.000000;-0.999911;0.013378;,
  0.000000;0.000000;0.000000;,
  0.003836;-0.995405;0.095681;,
  -0.520280;0.830942;-0.197089;,
  -0.474447;0.876840;-0.077785;,
  -0.219889;0.885917;-0.408411;,
  0.000000;-0.331324;-0.943517;,
  0.219891;0.885917;-0.408410;,
  0.520277;0.830944;-0.197088;,
  0.505647;0.858688;-0.083520;,
  0.000000;-0.999911;0.013378;,
  0.049677;-0.991969;0.116315;,
  -0.027549;-0.777573;-0.628189;,
  -0.013776;-0.778336;-0.627697;,
  0.013774;-0.778336;-0.627697;,
  0.027546;-0.777573;-0.628189;,
  0.965414;-0.235264;-0.112365;,
  0.995185;-0.000046;-0.098011;,
  0.961283;0.224219;-0.160188;,
  -0.967956;0.201062;-0.150451;,
  -0.993513;-0.018011;-0.112282;,
  -0.990932;0.004109;-0.134305;,
  0.995203;-0.000081;-0.097835;,
  0.046474;-0.950676;0.306686;,
  0.001817;-0.943127;0.332429;,
  -0.991336;-0.036005;-0.126318;,
  0.995173;0.000124;-0.098139;,
  -0.995173;0.000124;-0.098139;,
  0.007165;-0.943046;0.332585;,
  0.007421;-0.964973;0.262246;,
  0.097475;-0.961876;0.255526;,
  0.096330;-0.955119;0.280123;,
  0.866540;0.460539;-0.192387;,
  0.860857;-0.500252;-0.093127;,
  -0.442614;0.893821;-0.071946;,
  -0.860860;-0.500247;-0.093128;,
  -0.510138;-0.860089;-0.002548;,
  -0.866541;0.460537;-0.192386;,
  0.000000;-0.987326;0.158703;,
  0.992660;0.029620;-0.117254;,
  0.986514;0.036329;-0.159596;,
  0.982781;0.028686;-0.182534;,
  0.982251;0.039793;-0.183300;,
  0.981465;0.037141;-0.188006;,
  -0.981465;0.037141;-0.188006;,
  -0.982734;0.037643;-0.181154;,
  -0.982624;0.025152;-0.183894;,
  -0.986213;0.025933;-0.163434;,
  -0.988895;0.032701;-0.144974;,
  -0.992659;0.029622;-0.117263;,
  0.000000;-0.009580;-0.999954;,
  0.983536;-0.001731;-0.180701;,
  0.000000;0.009582;0.999954;,
  -0.983537;-0.001731;-0.180700;,
  0.205762;-0.978602;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.472225;-0.881478;-0.000000;,
  0.538910;-0.842364;-0.000000;,
  -0.280748;-0.959782;0.000000;,
  -0.538913;-0.842361;0.000000;,
  -0.483789;-0.875185;0.000000;,
  -0.249815;-0.968294;0.000000;;
  150;
  4;44,44,44,44;,
  4;82,39,38,83;,
  4;34,33,35,35;,
  4;30,29,75,74;,
  4;24,79,78,25;,
  4;86,27,26,87;,
  3;8,45,0;,
  3;45,46,0;,
  3;0,46,28;,
  3;28,46,28;,
  3;28,46,1;,
  3;1,46,9;,
  4;15,77,76,16;,
  4;88,18,17,73;,
  4;13,81,80,14;,
  4;40,41,48,47;,
  4;84,12,19,85;,
  4;38,39,41,40;,
  4;3,3,13,14;,
  4;21,22,24,25;,
  4;1,9,15,16;,
  3;114,29,30;,
  4;18,8,0,17;,
  4;27,23,20,26;,
  4;12,2,2,19;,
  4;115,115,46,45;,
  4;116,116,43,42;,
  4;15,25,117,77;,
  4;10,10,10,10;,
  4;79,118,14,80;,
  4;119,26,18,88;,
  4;19,120,86,85;,
  4;11,11,11,11;,
  4;9,21,25,15;,
  4;121,118,122,123;,
  4;18,26,20,8;,
  4;124,125,120,126;,
  3;127,114,30;,
  3;30,114,114;,
  3;128,128,128;,
  4;129,127,30,74;,
  4;130,131,83,38;,
  4;132,130,38,40;,
  3;132,40,47;,
  4;116,125,124,43;,
  4;133,23,44,44;,
  4;8,115,115,45;,
  4;115,115,9,46;,
  4;44,22,133,44;,
  4;123,122,116,42;,
  3;41,134,48;,
  4;39,135,134,41;,
  4;136,135,39,82;,
  4;29,137,138,75;,
  4;114,114,137,29;,
  4;124,139,140,43;,
  4;141,42,43,140;,
  4;142,123,42,141;,
  4;49,67,68,50;,
  4;50,51,52,49;,
  4;51,57,58,52;,
  4;53,64,63,54;,
  4;54,55,56,53;,
  4;55,60,59,56;,
  4;57,69,70,58;,
  4;60,61,62,59;,
  4;61,70,69,62;,
  4;64,65,66,63;,
  4;65,72,71,66;,
  4;67,71,72,68;,
  4;62,69,33,34;,
  4;35,35,72,65;,
  4;143,49,144,145;,
  4;146,147,54,148;,
  4;145,144,149,7;,
  4;150,151,31,32;,
  4;6,152,147,146;,
  4;104,107,106,105;,
  4;5,153,49,143;,
  4;148,54,154,4;,
  4;151,155,156,31;,
  4;56,59,62,34;,
  4;53,56,34,35;,
  4;64,53,35,65;,
  4;108,109,104,105;,
  4;107,111,110,106;,
  4;35,50,68,72;,
  4;33,51,50,35;,
  4;69,57,51,33;,
  4;157,158,150,32;,
  4;156,129,74,31;,
  4;75,32,31,74;,
  4;138,157,32,75;,
  4;77,145,7,76;,
  4;78,159,145,77;,
  4;79,160,159,78;,
  4;143,160,79,80;,
  4;81,5,143,80;,
  4;106,110,113,112;,
  4;36,37,82,83;,
  4;131,161,36,83;,
  4;148,4,84,85;,
  4;86,162,163,85;,
  4;164,162,86,87;,
  4;146,164,87,88;,
  4;6,146,88,73;,
  4;89,89,35,35;,
  4;35,35,90,90;,
  4;90,90,91,91;,
  4;91,91,92,92;,
  4;92,92,93,93;,
  4;93,93,94,94;,
  4;94,94,95,95;,
  4;95,95,89,89;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  4;96,97,97,96;,
  4;103,103,103,103;,
  4;98,101,101,98;,
  4;102,165,165,102;,
  3;166,167,100;,
  3;100,167,168;,
  3;167,169,168;,
  3;168,169,170;,
  4;98,98,99,99;,
  3;171,172,173;,
  3;173,172,174;,
  3;172,175,174;,
  3;174,175,176;,
  4;102,102,101,101;,
  4;97,177,177,97;,
  4;168,178,178,100;,
  4;99,179,179,99;,
  4;174,180,180,173;,
  4;181,181,182,182;,
  4;71,107,104,66;,
  4;183,183,181,181;,
  4;66,104,109,63;,
  4;184,184,183,183;,
  4;185,185,186,186;,
  4;67,111,107,71;,
  4;37,106,112,82;,
  4;187,187,188,188;,
  4;188,188,185,185;;
 }
 MeshTextureCoords {
  266;
  0.119810;0.248580;,
  0.119810;0.248580;,
  0.122020;0.254760;,
  0.122020;0.254760;,
  0.035480;0.222590;,
  0.036640;0.214430;,
  0.055440;0.214210;,
  0.056780;0.222350;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.057480;0.226620;,
  0.034240;0.226650;,
  0.032840;0.244810;,
  0.059160;0.244780;,
  0.173440;0.245120;,
  0.208030;0.194180;,
  0.208860;0.200780;,
  0.174660;0.251600;,
  0.208030;0.194180;,
  0.173440;0.245120;,
  0.174660;0.251600;,
  0.208860;0.200780;,
  0.090890;0.229760;,
  0.094950;0.229760;,
  0.097150;0.270560;,
  0.102450;0.229760;,
  0.097960;0.270560;,
  0.099440;0.270560;,
  0.100250;0.270560;,
  0.106510;0.229760;,
  0.126010;0.115680;,
  0.149310;0.079040;,
  0.129880;0.159940;,
  0.110930;0.159940;,
  0.149310;0.079040;,
  0.126010;0.115680;,
  0.110930;0.159940;,
  0.129880;0.159940;,
  0.110930;0.040470;,
  0.129880;0.040470;,
  0.148470;0.071930;,
  0.124780;0.108690;,
  0.046140;0.177730;,
  0.045080;0.177740;,
  0.044850;0.174930;,
  0.046310;0.174910;,
  0.129880;0.040470;,
  0.110930;0.040470;,
  0.124780;0.108690;,
  0.148470;0.071930;,
  0.085860;0.112460;,
  0.019380;0.056470;,
  0.122020;0.254760;,
  0.119810;0.248580;,
  0.057530;0.161430;,
  0.088100;0.119120;,
  0.045000;0.175440;,
  0.088100;0.119120;,
  0.057530;0.161430;,
  0.119810;0.248580;,
  0.122020;0.254760;,
  0.019380;0.056470;,
  0.085860;0.112460;,
  0.094340;0.227140;,
  0.103060;0.227140;,
  0.103060;0.222860;,
  0.094340;0.222860;,
  0.094950;0.223340;,
  0.102450;0.223340;,
  0.126530;0.114140;,
  0.149700;0.077620;,
  0.171440;0.076690;,
  0.171530;0.075550;,
  0.171530;0.070620;,
  0.171440;0.069310;,
  0.149130;0.072880;,
  0.125710;0.109480;,
  0.149700;0.077620;,
  0.126530;0.114140;,
  0.125710;0.109480;,
  0.149130;0.072880;,
  0.171440;0.069310;,
  0.171530;0.070620;,
  0.171530;0.075550;,
  0.171440;0.076690;,
  0.090880;0.116410;,
  0.089390;0.111970;,
  0.090880;0.116410;,
  0.089390;0.111970;,
  0.070060;0.226600;,
  0.046430;0.175440;,
  0.045930;0.175440;,
  0.073410;0.244760;,
  0.065620;0.214090;,
  0.068310;0.222210;,
  0.046680;0.174890;,
  0.089620;0.222860;,
  0.090890;0.223340;,
  0.089620;0.227140;,
  0.107780;0.227140;,
  0.106510;0.223340;,
  0.107780;0.222860;,
  0.044480;0.174920;,
  0.026460;0.214540;,
  0.023960;0.222730;,
  0.021660;0.226670;,
  0.018590;0.244830;,
  0.044500;0.175440;,
  0.096520;0.169350;,
  0.097250;0.169420;,
  0.100140;0.169420;,
  0.100880;0.169350;,
  0.334070;0.060980;,
  0.334080;0.046020;,
  0.327730;0.050260;,
  0.327420;0.060780;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.251260;0.060780;,
  0.251260;0.050430;,
  0.244610;0.046020;,
  0.244620;0.060980;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.269860;0.044330;,
  0.268790;0.038440;,
  0.308830;0.044330;,
  0.309890;0.038440;,
  0.268660;0.060780;,
  0.310030;0.060780;,
  0.232200;0.066290;,
  0.232200;0.071880;,
  0.232200;0.071880;,
  0.232200;0.066290;,
  0.233060;0.128810;,
  0.171230;0.145390;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.171320;0.151720;,
  0.233240;0.128750;,
  0.061110;0.266470;,
  0.032190;0.266810;,
  0.032960;0.240460;,
  0.059720;0.240150;,
  0.171440;0.040470;,
  0.232370;0.044480;,
  0.232370;0.044480;,
  0.171440;0.040470;,
  0.000000;1.000000;,
  0.074200;0.239980;,
  0.078130;0.266170;,
  0.015170;0.266900;,
  0.018480;0.240630;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.241100;0.191040;,
  0.241100;0.197890;,
  0.023960;0.222680;,
  0.035480;0.222540;,
  0.059720;0.240200;,
  0.032960;0.240520;,
  0.074200;0.240030;,
  0.241100;0.197890;,
  0.241100;0.191040;,
  0.306850;0.249930;,
  0.306850;0.197050;,
  0.314600;0.197050;,
  0.314600;0.249930;,
  0.306850;0.197050;,
  0.306850;0.249930;,
  0.288150;0.197050;,
  0.288150;0.249930;,
  0.269450;0.197050;,
  0.269450;0.249930;,
  0.261710;0.197050;,
  0.261710;0.249930;,
  0.269450;0.197050;,
  0.269450;0.249930;,
  0.288150;0.197050;,
  0.288150;0.249930;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.347850;0.106550;,
  0.339900;0.071500;,
  0.422980;0.071500;,
  0.415030;0.106550;,
  0.253120;0.106590;,
  0.246600;0.066150;,
  0.327940;0.066150;,
  0.321420;0.106590;,
  0.249900;0.080980;,
  0.249900;0.097770;,
  0.325770;0.097770;,
  0.325770;0.080980;,
  0.244740;0.065880;,
  0.257330;0.106280;,
  0.316790;0.106280;,
  0.329370;0.065880;,
  0.309070;0.142050;,
  0.301150;0.161770;,
  0.305210;0.139210;,
  0.257680;0.140930;,
  0.284110;0.171720;,
  0.199600;0.180260;,
  0.325370;0.078560;,
  0.250310;0.078560;,
  0.199600;0.180260;,
  0.284110;0.171720;,
  0.257680;0.140930;,
  0.305210;0.139210;,
  0.301150;0.161770;,
  0.309070;0.142050;,
  0.251560;0.106240;,
  0.324110;0.106240;,
  0.339900;0.057470;,
  0.422980;0.057470;,
  0.257440;0.125180;,
  0.304970;0.123470;,
  0.325370;0.065160;,
  0.250310;0.065160;,
  0.304970;0.123470;,
  0.257440;0.125180;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;;
 }
}
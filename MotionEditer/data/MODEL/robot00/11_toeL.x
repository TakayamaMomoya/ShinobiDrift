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
 239;
 0.00002;-6.44484;-20.39020;,
 2.61718;-6.44484;-20.39020;,
 2.61718;-9.15370;-21.13658;,
 0.00002;-9.15370;-21.13658;,
 0.00002;0.03908;0.30016;,
 5.67364;0.03908;0.30016;,
 5.30346;-0.00614;-4.46036;,
 0.00002;-0.00614;-4.46036;,
 0.00002;-8.94080;0.71398;,
 5.67364;-8.94080;0.71398;,
 5.67364;0.03908;0.30016;,
 0.00002;0.03908;0.30016;,
 0.00002;-9.14602;-4.03918;,
 5.30346;-9.14602;-4.03918;,
 5.67364;-8.94080;0.71398;,
 0.00002;-8.94080;0.71398;,
 5.30346;-0.00614;-4.46036;,
 5.67364;0.03908;0.30016;,
 5.67364;-8.94080;0.71398;,
 5.30346;-9.14602;-4.03918;,
 -5.67362;-8.94080;0.71398;,
 -5.67362;0.03908;0.30016;,
 -5.30346;-0.00614;-4.46036;,
 -5.30346;-9.14602;-4.03918;,
 0.00002;-0.20828;-7.16044;,
 3.30910;-1.12526;-6.91978;,
 2.83962;-2.49298;-9.69098;,
 0.00002;-1.03334;-9.95666;,
 4.75600;-4.25651;-7.54730;,
 4.75600;-9.32898;-8.27730;,
 0.00002;-9.32898;-8.27730;,
 4.75600;-9.32898;-8.27730;,
 -4.75601;-4.25651;-7.54730;,
 -4.75601;-9.32898;-8.27730;,
 2.47015;-4.88043;-15.91166;,
 0.00002;-4.12561;-16.14484;,
 3.71794;-9.78524;-18.84532;,
 3.71794;-7.00754;-18.20706;,
 0.00002;-9.78524;-18.84532;,
 3.71794;-9.78524;-18.84532;,
 -3.71792;-7.00754;-18.20706;,
 -3.71792;-9.78524;-18.84532;,
 0.00002;-9.15370;-21.13658;,
 2.61718;-9.15370;-21.13658;,
 2.61718;-9.15370;-21.13658;,
 2.61718;-6.44484;-20.39020;,
 2.67388;-6.65576;-19.18758;,
 0.00002;-6.51346;-19.15128;,
 -2.61717;-6.44484;-20.39020;,
 -2.61717;-9.15370;-21.13658;,
 4.75600;-4.25651;-7.54730;,
 3.73270;-4.38505;-7.52764;,
 4.77200;-0.03952;-5.16488;,
 5.30346;-0.00614;-4.46036;,
 4.77200;-0.03952;-5.16488;,
 0.00002;0.00206;-5.36520;,
 -5.30346;-0.00614;-4.46036;,
 -4.77198;-0.03952;-5.16488;,
 -3.73269;-4.38505;-7.52764;,
 -4.75601;-4.25651;-7.54730;,
 3.71794;-7.00754;-18.20706;,
 2.67120;-7.03644;-18.27050;,
 3.73270;-4.38505;-7.52764;,
 4.75600;-4.25651;-7.54730;,
 -4.75601;-4.25651;-7.54730;,
 -3.73269;-4.38505;-7.52764;,
 -2.67118;-7.03644;-18.27050;,
 -3.71792;-7.00754;-18.20706;,
 -2.67386;-6.65576;-19.18758;,
 -2.61717;-6.44484;-20.39020;,
 2.61718;-6.44484;-20.39020;,
 0.00002;-6.44484;-20.39020;,
 3.73270;-4.38505;-7.52764;,
 2.83962;-2.49298;-9.69098;,
 3.30910;-1.12526;-6.91978;,
 4.77200;-0.03952;-5.16488;,
 -4.77198;-0.03952;-5.16488;,
 -3.30906;-1.12526;-6.91978;,
 -2.83960;-2.49298;-9.69098;,
 -3.73269;-4.38505;-7.52764;,
 2.67120;-7.03644;-18.27050;,
 2.47015;-4.88043;-15.91166;,
 -2.47016;-4.88043;-15.91166;,
 -2.67118;-7.03644;-18.27050;,
 -2.67386;-6.65576;-19.18758;,
 2.67388;-6.65576;-19.18758;,
 -4.75601;-9.32898;-8.27730;,
 -3.71792;-9.78524;-18.84532;,
 -5.30346;-9.14602;-4.03918;,
 -5.67362;-8.94080;0.71398;,
 -5.67362;0.03908;0.30016;,
 -5.67362;-8.94080;0.71398;,
 -5.30346;-0.00614;-4.46036;,
 -5.67362;0.03908;0.30016;,
 -4.77198;-0.03952;-5.16488;,
 -3.30906;-1.12526;-6.91978;,
 -2.83960;-2.49298;-9.69098;,
 -2.47016;-4.88043;-15.91166;,
 -2.61717;-9.15370;-21.13658;,
 -2.61717;-6.44484;-20.39020;,
 -2.61717;-9.15370;-21.13658;,
 6.73853;-1.20928;5.18560;,
 -6.73853;-1.20928;5.18560;,
 -6.73853;-3.26931;6.03888;,
 6.73853;-3.26931;6.03888;,
 -6.73853;-5.32931;5.18560;,
 6.73853;-5.32931;5.18560;,
 6.73853;-5.32931;5.18560;,
 -6.73853;-5.32931;5.18560;,
 -6.73853;-6.18258;3.12560;,
 6.73853;-6.18258;3.12560;,
 -6.73853;-5.32931;1.06558;,
 6.73853;-5.32931;1.06558;,
 6.73853;-5.32931;1.06558;,
 -6.73853;-5.32931;1.06558;,
 -6.73853;-3.26931;0.21230;,
 6.73853;-3.26931;0.21230;,
 -6.73853;-1.20928;1.06558;,
 6.73853;-1.20928;1.06558;,
 6.73853;-1.20928;1.06558;,
 -6.73853;-1.20928;1.06558;,
 -6.73853;-0.35600;3.12560;,
 6.73853;-0.35600;3.12560;,
 -6.73853;-1.20928;5.18560;,
 6.73853;-1.20928;5.18560;,
 6.73853;-3.26931;6.03888;,
 6.73853;-3.26931;3.12560;,
 6.73853;-1.20928;5.18560;,
 6.73853;-5.32931;5.18560;,
 6.73853;-6.18258;3.12560;,
 6.73853;-5.32931;1.06558;,
 6.73853;-3.26931;0.21230;,
 6.73853;-1.20928;1.06558;,
 6.73853;-0.35600;3.12560;,
 -6.73853;-1.20928;5.18560;,
 -6.73853;-3.26931;3.12560;,
 -6.73853;-3.26931;6.03888;,
 -6.73853;-5.32931;5.18560;,
 -6.73853;-6.18258;3.12560;,
 -6.73853;-5.32931;1.06558;,
 -6.73853;-3.26931;0.21230;,
 -6.73853;-1.20928;1.06558;,
 -6.73853;-0.35600;3.12560;,
 1.15864;-6.04582;4.56980;,
 1.15864;-1.02582;4.60128;,
 5.82636;-1.02582;4.60128;,
 5.82636;-6.04582;4.56980;,
 1.15864;-1.02582;4.60128;,
 1.15864;-1.09736;8.13642;,
 5.82636;-1.09736;8.13642;,
 5.82636;-1.02582;4.60128;,
 1.15864;-1.71824;19.50994;,
 1.15864;-3.12811;20.19574;,
 5.82636;-3.12811;20.19574;,
 5.82636;-1.71824;19.50994;,
 1.15864;-6.11736;8.10496;,
 1.15864;-6.04582;4.56980;,
 5.82636;-6.04582;4.56980;,
 5.82636;-6.11736;8.10496;,
 5.82636;-6.04582;4.56980;,
 5.82636;-1.02582;4.60128;,
 5.82636;-1.09736;8.13642;,
 5.82636;-6.11736;8.10496;,
 1.15864;-6.11736;8.10496;,
 1.15864;-1.09736;8.13642;,
 1.15864;-1.02582;4.60128;,
 1.15864;-6.04582;4.56980;,
 1.15864;-3.29755;12.28592;,
 5.82636;-3.29755;12.28592;,
 5.82636;-3.29755;12.28592;,
 5.82636;-8.84698;10.09934;,
 5.82636;-8.84698;10.09934;,
 1.15864;-8.84698;10.09934;,
 1.15864;-8.84698;10.09934;,
 1.15864;-3.29755;12.28592;,
 1.15864;-3.64291;15.54998;,
 5.82636;-3.64291;15.54998;,
 5.82636;-3.64291;15.54998;,
 5.82636;-8.82526;16.91274;,
 5.82636;-8.82526;16.91274;,
 1.15864;-8.82526;16.91274;,
 1.15864;-8.82526;16.91274;,
 1.15864;-3.64291;15.54998;,
 1.15864;-1.71824;19.50994;,
 5.82636;-1.71824;19.50994;,
 5.82636;-1.71824;19.50994;,
 5.82636;-3.12811;20.19574;,
 5.82636;-8.82526;16.91274;,
 1.15864;-8.82526;16.91274;,
 1.15864;-3.12811;20.19574;,
 1.15864;-1.71824;19.50994;,
 -5.97558;-6.04582;4.56980;,
 -5.97558;-1.02582;4.60128;,
 -1.30784;-1.02582;4.60128;,
 -1.30784;-6.04582;4.56980;,
 -5.97558;-1.02582;4.60128;,
 -5.97558;-1.09736;8.13642;,
 -1.30784;-1.09736;8.13642;,
 -1.30784;-1.02582;4.60128;,
 -5.97558;-1.71824;19.50994;,
 -5.97558;-3.12811;20.19574;,
 -1.30784;-3.12811;20.19574;,
 -1.30784;-1.71824;19.50994;,
 -5.97558;-6.11736;8.10496;,
 -5.97558;-6.04582;4.56980;,
 -1.30784;-6.04582;4.56980;,
 -1.30784;-6.11736;8.10496;,
 -1.30784;-6.04582;4.56980;,
 -1.30784;-1.02582;4.60128;,
 -1.30784;-1.09736;8.13642;,
 -1.30784;-6.11736;8.10496;,
 -5.97558;-6.11736;8.10496;,
 -5.97558;-1.09736;8.13642;,
 -5.97558;-1.02582;4.60128;,
 -5.97558;-6.04582;4.56980;,
 -5.97558;-3.29755;12.28592;,
 -1.30784;-3.29755;12.28592;,
 -1.30784;-3.29755;12.28592;,
 -1.30784;-8.84698;10.09934;,
 -1.30784;-8.84698;10.09934;,
 -5.97558;-8.84698;10.09934;,
 -5.97558;-8.84698;10.09934;,
 -5.97558;-3.29755;12.28592;,
 -5.97558;-3.64291;15.54998;,
 -1.30784;-3.64291;15.54998;,
 -1.30784;-3.64291;15.54998;,
 -1.30784;-8.82526;16.91274;,
 -1.30784;-8.82526;16.91274;,
 -5.97558;-8.82526;16.91274;,
 -5.97558;-8.82526;16.91274;,
 -5.97558;-3.64291;15.54998;,
 -5.97558;-1.71824;19.50994;,
 -1.30784;-1.71824;19.50994;,
 -1.30784;-1.71824;19.50994;,
 -1.30784;-3.12811;20.19574;,
 -1.30784;-8.82526;16.91274;,
 -5.97558;-8.82526;16.91274;,
 -5.97558;-3.12811;20.19574;,
 -5.97558;-1.71824;19.50994;;
 
 106;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,16,19,29;,
 4;30,31,13,12;,
 4;22,32,33,23;,
 4;27,26,34,35;,
 4;36,37,28,29;,
 4;38,39,31,30;,
 4;32,40,41,33;,
 4;42,43,39,38;,
 4;36,44,45,37;,
 4;34,46,47,35;,
 4;40,48,49,41;,
 4;50,51,52,53;,
 4;6,54,55,7;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;67,66,68,69;,
 4;47,46,70,71;,
 4;70,46,61,60;,
 4;72,73,74,75;,
 4;54,25,24,55;,
 4;76,77,78,79;,
 4;80,81,73,72;,
 4;79,78,82,83;,
 3;83,82,84;,
 3;85,81,80;,
 4;86,87,38,30;,
 4;88,86,30,12;,
 4;89,88,12,15;,
 4;90,91,8,11;,
 4;92,93,4,7;,
 4;55,94,92,7;,
 4;24,95,94,55;,
 4;96,95,24,27;,
 4;97,96,27,35;,
 4;47,68,97,35;,
 4;69,68,47,71;,
 4;98,99,0,3;,
 4;87,100,42,38;,
 4;101,102,103,104;,
 4;104,103,105,106;,
 4;107,108,109,110;,
 4;110,109,111,112;,
 4;113,114,115,116;,
 4;116,115,117,118;,
 4;119,120,121,122;,
 4;122,121,123,124;,
 3;125,126,127;,
 3;128,126,125;,
 3;129,126,128;,
 3;130,126,129;,
 3;131,126,130;,
 3;132,126,131;,
 3;133,126,132;,
 3;127,126,133;,
 3;134,135,136;,
 3;136,135,137;,
 3;137,135,138;,
 3;138,135,139;,
 3;139,135,140;,
 3;140,135,141;,
 3;141,135,142;,
 3;142,135,134;,
 4;143,144,145,146;,
 4;147,148,149,150;,
 4;151,152,153,154;,
 4;155,156,157,158;,
 4;159,160,161,162;,
 4;163,164,165,166;,
 4;148,167,168,149;,
 4;161,169,170,162;,
 4;158,171,172,155;,
 4;163,173,174,164;,
 4;167,175,176,168;,
 4;169,177,178,170;,
 4;171,179,180,172;,
 4;173,181,182,174;,
 4;175,183,184,176;,
 4;177,185,186,178;,
 4;187,153,152,188;,
 4;181,189,190,182;,
 4;191,192,193,194;,
 4;195,196,197,198;,
 4;199,200,201,202;,
 4;203,204,205,206;,
 4;207,208,209,210;,
 4;211,212,213,214;,
 4;196,215,216,197;,
 4;209,217,218,210;,
 4;206,219,220,203;,
 4;211,221,222,212;,
 4;215,223,224,216;,
 4;217,225,226,218;,
 4;219,227,228,220;,
 4;221,229,230,222;,
 4;223,231,232,224;,
 4;225,233,234,226;,
 4;235,201,200,236;,
 4;229,237,238,230;;
 
 MeshMaterialList {
  1;
  106;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\TEXTURE\\MATERIAL\\ac2_02.png";
   }
  }
 }
 MeshNormals {
  88;
  -0.963037;0.062903;-0.261920;,
  0.963038;0.062903;-0.261919;,
  -0.996987;-0.003571;-0.077488;,
  0.000000;0.999955;-0.009499;,
  0.000000;0.046034;0.998940;,
  -0.993688;0.000958;-0.112173;,
  0.002084;0.999895;-0.014320;,
  0.000000;-0.999069;0.043133;,
  -0.992305;0.012036;-0.123227;,
  0.992306;0.012036;-0.123226;,
  -0.903005;0.105383;-0.416505;,
  0.000000;0.265634;-0.964074;,
  -0.637806;0.573291;-0.514335;,
  0.637808;0.573289;-0.514335;,
  0.517329;0.594907;-0.615188;,
  -0.517325;0.594910;-0.615189;,
  0.002643;0.999801;0.019773;,
  -0.002644;0.999801;0.019773;,
  -0.091755;0.994283;-0.054607;,
  0.091756;0.994283;-0.054607;,
  -0.702755;0.598870;-0.384045;,
  0.702756;0.598869;-0.384045;,
  0.509768;0.737861;-0.442378;,
  -0.666740;0.580692;-0.467178;,
  -0.741275;0.593831;-0.312850;,
  0.741275;0.593832;-0.312849;,
  0.000000;-0.993633;-0.112663;,
  0.000000;-0.999069;0.043132;,
  0.000000;0.999955;-0.009499;,
  0.000000;0.999897;-0.014320;,
  0.000000;0.983160;-0.182747;,
  0.000000;0.931004;-0.365008;,
  0.000001;0.916984;-0.398923;,
  0.000002;0.875542;-0.483142;,
  0.000001;0.973327;-0.229421;,
  0.000000;0.265634;-0.964074;,
  0.000000;0.707105;0.707108;,
  0.000000;-0.000002;1.000000;,
  0.000000;-0.707107;0.707106;,
  0.000000;-1.000000;0.000002;,
  0.000000;-0.707109;-0.707105;,
  0.000000;-0.000002;-1.000000;,
  0.000000;0.707107;-0.707107;,
  0.000000;1.000000;0.000002;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.006271;-0.999980;,
  0.000000;0.967944;0.251167;,
  0.000000;-0.886988;-0.461793;,
  0.000000;0.956372;0.292152;,
  0.000000;-0.892335;-0.451375;,
  0.000000;0.984987;-0.172629;,
  0.000000;-0.999995;0.003188;,
  0.000000;0.437425;0.899255;,
  0.000000;-0.035014;0.999387;,
  0.000000;-0.892335;-0.451375;,
  0.000000;-0.999995;0.003188;,
  0.000000;-0.999069;0.043135;,
  0.000000;-0.999069;0.043135;,
  0.993688;0.000958;-0.112175;,
  0.996987;-0.003571;-0.077492;,
  0.000000;-0.964050;-0.265721;,
  0.903005;0.105383;-0.416505;,
  0.169947;0.794221;-0.583380;,
  0.373785;0.455157;-0.808157;,
  0.004168;0.999808;-0.019140;,
  -0.373776;0.455160;-0.808159;,
  -0.169943;0.794221;-0.583380;,
  -0.045852;0.979706;0.195123;,
  0.045852;0.979706;0.195123;,
  0.000000;0.993604;0.112918;,
  0.984114;0.164889;-0.065805;,
  -0.984115;0.164884;-0.065805;,
  -0.997681;0.061776;0.028559;,
  0.997681;0.061782;0.028561;,
  0.000000;-0.999069;0.043132;,
  0.000000;-0.999069;0.043135;,
  0.000000;0.046034;0.998940;,
  -0.002084;0.999895;-0.014320;,
  0.000000;0.999955;-0.009499;,
  -0.004168;0.999808;-0.019140;,
  -0.156693;0.927601;-0.339122;,
  0.000000;0.265634;-0.964074;,
  0.000000;0.999795;0.020233;,
  0.000000;-0.999795;-0.020233;,
  0.000000;0.899396;-0.437135;,
  0.000000;-0.499286;0.866437;,
  0.000000;-0.999795;-0.020233;;
  106;
  4;35,11,11,35;,
  4;28,3,6,29;,
  4;4,4,4,4;,
  4;7,7,57,58;,
  4;59,60,60,59;,
  4;2,2,5,5;,
  4;31,22,21,32;,
  4;9,59,59,9;,
  4;27,27,7,7;,
  4;5,8,8,5;,
  4;32,21,25,33;,
  4;1,1,9,9;,
  4;26,26,27,27;,
  4;8,0,0,8;,
  4;61,61,26,26;,
  4;1,62,62,1;,
  4;25,19,34,33;,
  4;0,10,10,0;,
  4;63,13,14,64;,
  4;6,65,30,29;,
  4;66,15,12,67;,
  4;17,17,13,63;,
  4;67,12,16,16;,
  4;16,16,18,68;,
  4;34,19,69,70;,
  4;69,19,17,17;,
  4;13,21,22,14;,
  4;14,22,31,30;,
  4;15,23,20,12;,
  4;71,25,21,13;,
  4;12,20,24,72;,
  3;72,24,73;,
  3;74,25,71;,
  4;75,26,26,27;,
  4;7,75,27,7;,
  4;76,7,7,58;,
  4;77,77,4,4;,
  4;78,79,28,29;,
  4;30,80,78,29;,
  4;31,81,15,30;,
  4;20,23,31,32;,
  4;24,20,32,33;,
  4;34,18,24,33;,
  4;68,18,34,70;,
  4;82,82,35,35;,
  4;26,61,61,26;,
  4;36,36,37,37;,
  4;37,37,38,38;,
  4;38,38,39,39;,
  4;39,39,40,40;,
  4;40,40,41,41;,
  4;41,41,42,42;,
  4;42,42,43,43;,
  4;43,43,36,36;,
  3;44,44,44;,
  3;44,44,44;,
  3;44,44,44;,
  3;44,44,44;,
  3;44,44,44;,
  3;44,44,44;,
  3;44,44,44;,
  3;44,44,44;,
  3;45,45,45;,
  3;45,45,45;,
  3;45,45,45;,
  3;45,45,45;,
  3;45,45,45;,
  3;45,45,45;,
  3;45,45,45;,
  3;45,45,45;,
  4;46,46,46,46;,
  4;83,47,47,83;,
  4;53,54,54,53;,
  4;48,84,84,48;,
  4;44,44,44,44;,
  4;45,45,45,45;,
  4;47,49,49,47;,
  4;44,44,44,44;,
  4;48,50,50,48;,
  4;45,45,45,45;,
  4;49,51,51,49;,
  4;44,44,44,44;,
  4;50,52,52,50;,
  4;45,45,45,45;,
  4;51,85,85,51;,
  4;44,44,44,44;,
  4;86,54,54,86;,
  4;45,45,45,45;,
  4;46,46,46,46;,
  4;83,47,47,83;,
  4;53,54,54,53;,
  4;48,87,87,48;,
  4;44,44,44,44;,
  4;45,45,45,45;,
  4;47,49,49,47;,
  4;44,44,44,44;,
  4;48,55,55,48;,
  4;45,45,45,45;,
  4;49,51,51,49;,
  4;44,44,44,44;,
  4;55,56,56,55;,
  4;45,45,45,45;,
  4;51,85,85,51;,
  4;44,44,44,44;,
  4;86,54,54,86;,
  4;45,45,45,45;;
 }
 MeshTextureCoords {
  239;
  0.640440;0.951360;,
  0.665400;0.951260;,
  0.665500;0.977090;,
  0.640540;0.977200;,
  0.641310;0.784810;,
  0.684820;0.784810;,
  0.681980;0.821310;,
  0.641310;0.821310;,
  0.639520;0.725540;,
  0.684110;0.725770;,
  0.683640;0.778560;,
  0.639050;0.778330;,
  0.541160;0.781030;,
  0.561670;0.781030;,
  0.563100;0.799410;,
  0.541160;0.799410;,
  0.709330;0.844180;,
  0.727020;0.821950;,
  0.770190;0.853790;,
  0.753270;0.876590;,
  0.510700;0.855800;,
  0.553820;0.823860;,
  0.571560;0.846070;,
  0.527670;0.878570;,
  0.641310;0.842010;,
  0.666690;0.840170;,
  0.663090;0.861420;,
  0.641310;0.863450;,
  0.717420;0.874470;,
  0.738180;0.896920;,
  0.541160;0.764640;,
  0.559550;0.764640;,
  0.563530;0.876380;,
  0.542800;0.898880;,
  0.660250;0.909120;,
  0.641310;0.910900;,
  0.700560;0.947610;,
  0.690080;0.934210;,
  0.541160;0.723780;,
  0.555540;0.723780;,
  0.590980;0.936080;,
  0.580530;0.949510;,
  0.541160;0.714920;,
  0.551290;0.714920;,
  0.689020;0.955860;,
  0.679270;0.942210;,
  0.661820;0.934230;,
  0.641310;0.933960;,
  0.601810;0.944070;,
  0.592090;0.957730;,
  0.589400;0.821660;,
  0.579780;0.823680;,
  0.586250;0.781570;,
  0.591280;0.780830;,
  0.677900;0.826710;,
  0.641310;0.828250;,
  0.692610;0.782980;,
  0.697610;0.783910;,
  0.702450;0.826250;,
  0.692910;0.823850;,
  0.669820;0.926720;,
  0.661800;0.927200;,
  0.669930;0.844830;,
  0.677780;0.844980;,
  0.604850;0.844980;,
  0.612690;0.844830;,
  0.620830;0.927200;,
  0.612810;0.926720;,
  0.620810;0.934230;,
  0.621250;0.943460;,
  0.661380;0.943460;,
  0.641310;0.943460;,
  0.704320;0.854080;,
  0.685230;0.860570;,
  0.686660;0.838940;,
  0.686220;0.824470;,
  0.596990;0.820520;,
  0.596130;0.836090;,
  0.597070;0.859440;,
  0.576680;0.851920;,
  0.682710;0.928630;,
  0.677900;0.906730;,
  0.603720;0.909370;,
  0.597930;0.932830;,
  0.603780;0.937540;,
  0.677180;0.932860;,
  0.522780;0.764640;,
  0.526790;0.723780;,
  0.520660;0.781030;,
  0.519230;0.799410;,
  0.594470;0.778110;,
  0.594930;0.725320;,
  0.600650;0.821310;,
  0.597810;0.784810;,
  0.604720;0.826710;,
  0.615940;0.840170;,
  0.619540;0.861420;,
  0.622370;0.909120;,
  0.615580;0.977300;,
  0.615470;0.951460;,
  0.531050;0.714920;,
  0.712050;0.797590;,
  0.712050;0.714230;,
  0.724790;0.714230;,
  0.724790;0.797590;,
  0.737530;0.714230;,
  0.737530;0.797590;,
  0.712240;0.797530;,
  0.712240;0.714240;,
  0.724970;0.714240;,
  0.724970;0.797530;,
  0.737700;0.714240;,
  0.737700;0.797530;,
  0.711890;0.798320;,
  0.711890;0.712370;,
  0.725030;0.712370;,
  0.725030;0.798320;,
  0.738170;0.712370;,
  0.738170;0.798320;,
  0.712580;0.797330;,
  0.712580;0.712270;,
  0.725590;0.712270;,
  0.725590;0.797330;,
  0.738590;0.712270;,
  0.738590;0.797330;,
  0.789200;0.727670;,
  0.768700;0.727670;,
  0.783200;0.713180;,
  0.783200;0.742160;,
  0.768700;0.748170;,
  0.754210;0.742160;,
  0.748210;0.727670;,
  0.754210;0.713180;,
  0.768700;0.707170;,
  0.753960;0.712870;,
  0.768450;0.727370;,
  0.747950;0.727370;,
  0.753960;0.741860;,
  0.768450;0.747860;,
  0.782940;0.741860;,
  0.788950;0.727370;,
  0.782940;0.712870;,
  0.768450;0.706870;,
  0.814000;0.778680;,
  0.814000;0.738730;,
  0.851150;0.738730;,
  0.851150;0.778680;,
  0.857820;0.842780;,
  0.857820;0.817900;,
  0.890660;0.817900;,
  0.890660;0.842780;,
  0.857460;0.897330;,
  0.857460;0.887410;,
  0.890300;0.887410;,
  0.890300;0.897330;,
  0.858350;0.928570;,
  0.858350;0.903700;,
  0.891190;0.903700;,
  0.891190;0.928570;,
  0.959610;0.989680;,
  0.915370;0.990000;,
  0.915580;0.958840;,
  0.959820;0.958520;,
  0.800780;0.955300;,
  0.843040;0.955040;,
  0.843650;0.984800;,
  0.801380;0.985060;,
  0.857820;0.788710;,
  0.890660;0.788710;,
  0.934470;0.922010;,
  0.983640;0.940620;,
  0.891190;0.942600;,
  0.858350;0.942600;,
  0.777800;0.938510;,
  0.824520;0.920110;,
  0.857820;0.765740;,
  0.890660;0.765740;,
  0.937120;0.893200;,
  0.982630;0.880580;,
  0.891190;0.990540;,
  0.858350;0.990540;,
  0.777990;0.881160;,
  0.821610;0.892630;,
  0.857820;0.737880;,
  0.890660;0.737880;,
  0.919690;0.858540;,
  0.932030;0.852330;,
  0.890300;0.847320;,
  0.857460;0.847320;,
  0.825950;0.853520;,
  0.837820;0.859290;,
  0.813280;0.778980;,
  0.813280;0.738380;,
  0.851040;0.738380;,
  0.851040;0.778980;,
  0.858200;0.842180;,
  0.858200;0.817300;,
  0.891040;0.817300;,
  0.891040;0.842180;,
  0.857370;0.897330;,
  0.857370;0.887410;,
  0.890210;0.887410;,
  0.890210;0.897330;,
  0.857170;0.928530;,
  0.857170;0.903660;,
  0.890010;0.903660;,
  0.890010;0.928530;,
  0.960050;0.990290;,
  0.915480;0.990790;,
  0.915560;0.959400;,
  0.960130;0.958890;,
  0.800970;0.955740;,
  0.843400;0.955480;,
  0.844010;0.985360;,
  0.801580;0.985620;,
  0.858200;0.788110;,
  0.891040;0.788110;,
  0.934450;0.922210;,
  0.984050;0.940760;,
  0.890010;0.942570;,
  0.857170;0.942570;,
  0.777900;0.938890;,
  0.824810;0.920410;,
  0.858200;0.765140;,
  0.891040;0.765140;,
  0.937000;0.893180;,
  0.982800;0.880280;,
  0.890010;0.990500;,
  0.857170;0.990500;,
  0.778090;0.881300;,
  0.821890;0.892820;,
  0.858200;0.737280;,
  0.891040;0.737280;,
  0.919300;0.858330;,
  0.931710;0.852020;,
  0.890210;0.847330;,
  0.857370;0.847330;,
  0.826240;0.853560;,
  0.838150;0.859350;;
 }
}
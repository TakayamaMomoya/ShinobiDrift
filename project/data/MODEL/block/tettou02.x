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
 -1.94921;576.77003;5.51679;,
 -1.46722;576.77003;2.32871;,
 -1.53924;5.78600;-44.15074;,
 -42.66407;5.78600;-40.96266;,
 -4.92658;576.77003;5.34654;,
 36.69413;5.78600;-41.13291;,
 2.15981;576.77003;-5.68416;,
 -40.20140;5.78600;40.76945;,
 2.64179;5.78600;38.90613;,
 2.64179;576.77003;-7.54748;,
 2.81179;576.77003;-7.54539;,
 46.09757;5.78600;38.90613;,
 -6.81517;576.52315;-2.52914;,
 -4.91212;576.52315;-3.75684;,
 41.56731;5.53912;-3.75683;,
 39.42036;5.53912;-44.84841;,
 -5.32360;576.52315;-1.14377;,
 41.15580;5.53912;42.14200;,
 5.72430;576.52315;-0.13116;,
 4.22161;576.52315;-2.95675;,
 -40.66762;5.53912;-2.95674;,
 -39.16495;5.53912;43.44790;,
 1.90012;578.58922;-1.45910;,
 -41.65718;7.60519;-43.73107;,
 46.28237;439.04127;-15.00721;,
 46.28237;439.04127;-11.63631;,
 6.45728;463.09449;-11.63631;,
 6.45728;463.09449;-14.83419;,
 -48.95934;439.04127;-11.63631;,
 -48.95934;439.04127;-15.00721;,
 -9.52205;463.09449;-14.83419;,
 -9.52205;463.09449;-11.63631;,
 51.78736;438.93892;-15.00721;,
 -54.88802;438.93892;-15.00721;,
 51.78736;438.93892;-11.63631;,
 -54.88802;438.93892;-11.63631;,
 51.81285;438.90465;-11.63631;,
 7.08365;467.15816;-11.63631;,
 51.81285;438.90465;-15.00721;,
 7.08365;467.15816;-14.62206;,
 -54.87757;438.99966;-15.00721;,
 -10.14836;467.15816;-14.62206;,
 -54.87757;438.99966;-11.63631;,
 -10.14836;467.15816;-11.63631;,
 51.78736;434.22632;-15.00721;,
 -54.88802;434.22632;-15.00721;,
 51.78736;434.22632;-11.63631;,
 -54.88802;434.22632;-11.63631;,
 103.62157;343.39180;-26.69085;,
 103.62157;343.39180;-23.31995;,
 10.68184;379.96163;-19.25694;,
 10.68184;379.96163;-22.62784;,
 -105.82119;343.39180;-23.31995;,
 -105.82119;343.39180;-26.69085;,
 -13.73406;379.96163;-22.62784;,
 -13.73406;379.96163;-19.25694;,
 115.72749;343.23616;-26.69085;,
 -118.85879;343.23616;-26.69085;,
 115.72749;343.23616;-23.31995;,
 -118.85879;343.23616;-23.31995;,
 115.78345;343.18394;-23.31995;,
 11.63897;386.13997;-19.25694;,
 115.78345;343.18394;-26.69085;,
 11.63897;386.13997;-21.97873;,
 -118.83565;343.32837;-26.69085;,
 -14.69104;386.13997;-21.97873;,
 -118.83565;343.32837;-23.31995;,
 -14.69104;386.13997;-19.25694;,
 115.72749;336.07112;-26.69085;,
 -118.85879;336.07112;-26.69085;,
 115.72749;336.07112;-23.31995;,
 -118.85879;336.07112;-23.31995;,
 115.81699;232.74341;-36.50852;,
 115.81699;232.74341;-33.13762;,
 22.77247;275.21565;-28.68577;,
 22.77247;275.21565;-30.90293;,
 -117.91514;232.74341;-33.13762;,
 -117.91514;232.74341;-36.50852;,
 -25.82200;275.21565;-30.90293;,
 -25.82200;275.21565;-28.68577;,
 129.32696;232.56270;-36.50852;,
 -132.46475;232.56270;-36.50852;,
 129.32696;232.56270;-33.13762;,
 -132.46475;232.56270;-33.13762;,
 129.38941;232.50201;-33.13762;,
 22.42769;282.39109;-28.68577;,
 129.38941;232.50201;-36.50852;,
 22.42769;282.39109;-30.90293;,
 -132.43897;232.66973;-36.50852;,
 -25.47712;282.39109;-30.90293;,
 -132.43897;232.66973;-33.13762;,
 -25.47712;282.39109;-28.68577;,
 129.13394;224.24119;-35.99136;,
 -132.46475;224.24119;-36.50852;,
 129.13394;224.24119;-33.67241;,
 -132.46475;224.24119;-33.13762;,
 126.35106;227.35952;-39.57220;,
 129.23237;227.35952;-38.44245;,
 129.23237;212.53057;-38.44245;,
 126.35106;212.53057;-39.57220;,
 130.42578;227.35952;-35.71493;,
 130.42578;212.53057;-35.71493;,
 129.23237;227.35952;-32.98741;,
 129.23237;212.53057;-32.98741;,
 126.35106;227.35952;-31.85765;,
 126.35106;212.53057;-31.85765;,
 123.46967;227.35952;-32.98741;,
 123.46967;212.53057;-32.98741;,
 122.27627;227.35952;-35.71493;,
 122.27627;212.53057;-35.71493;,
 123.46967;227.35952;-38.44245;,
 123.46967;212.53057;-38.44245;,
 126.35106;227.35952;-35.71493;,
 126.35106;212.53057;-35.71493;,
 -132.06543;227.35952;-39.57220;,
 -129.18408;227.35952;-38.44245;,
 -129.18408;212.53057;-38.44245;,
 -132.06543;212.53057;-39.57220;,
 -127.99072;227.35952;-35.71493;,
 -127.99072;212.53057;-35.71493;,
 -129.18408;227.35952;-32.98741;,
 -129.18408;212.53057;-32.98741;,
 -132.06543;227.35952;-31.85765;,
 -132.06543;212.53057;-31.85765;,
 -134.94678;227.35952;-32.98741;,
 -134.94678;212.53057;-32.98741;,
 -136.14024;227.35952;-35.71493;,
 -136.14024;212.53057;-35.71493;,
 -134.94678;227.35952;-38.44245;,
 -134.94678;212.53057;-38.44245;,
 -132.06543;227.35952;-35.71493;,
 -132.06543;212.53057;-35.71493;,
 -118.20137;337.13834;-29.39211;,
 -115.32002;337.13834;-28.26236;,
 -115.32002;322.30938;-28.26236;,
 -118.20137;322.30938;-29.39211;,
 -114.12666;337.13834;-25.53484;,
 -114.12666;322.30938;-25.53484;,
 -115.32002;337.13834;-22.80732;,
 -115.32002;322.30938;-22.80732;,
 -118.20137;337.13834;-21.67756;,
 -118.20137;322.30938;-21.67756;,
 -121.08272;337.13834;-22.80732;,
 -121.08272;322.30938;-22.80732;,
 -122.27617;337.13834;-25.53484;,
 -122.27617;322.30938;-25.53484;,
 -121.08272;337.13834;-28.26236;,
 -121.08272;322.30938;-28.26236;,
 -118.20137;337.13834;-25.53484;,
 -118.20137;322.30938;-25.53484;,
 114.77754;337.13834;-29.39211;,
 117.65888;337.13834;-28.26236;,
 117.65888;322.30938;-28.26236;,
 114.77754;322.30938;-29.39211;,
 118.85224;337.13834;-25.53484;,
 118.85224;322.30938;-25.53484;,
 117.65888;337.13834;-22.80732;,
 117.65888;322.30938;-22.80732;,
 114.77754;337.13834;-21.67756;,
 114.77754;322.30938;-21.67756;,
 111.89622;337.13834;-22.80732;,
 111.89622;322.30938;-22.80732;,
 110.70275;337.13834;-25.53484;,
 110.70275;322.30938;-25.53484;,
 111.89622;337.13834;-28.26236;,
 111.89622;322.30938;-28.26236;,
 114.77754;337.13834;-25.53484;,
 114.77754;322.30938;-25.53484;,
 51.47496;436.80084;-16.92857;,
 54.35631;436.80084;-15.79882;,
 54.35631;421.97188;-15.79882;,
 51.47496;421.97188;-16.92857;,
 55.54967;436.80084;-13.07130;,
 55.54967;421.97188;-13.07130;,
 54.35631;436.80084;-10.34378;,
 54.35631;421.97188;-10.34378;,
 51.47496;436.80084;-9.21403;,
 51.47496;421.97188;-9.21403;,
 48.59360;436.80084;-10.34378;,
 48.59360;421.97188;-10.34378;,
 47.40014;436.80084;-13.07130;,
 47.40014;421.97188;-13.07130;,
 48.59360;436.80084;-15.79882;,
 48.59360;421.97188;-15.79882;,
 51.47496;436.80084;-13.07130;,
 51.47496;421.97188;-13.07130;,
 -54.56693;437.10738;-16.92857;,
 -51.68551;437.10738;-15.79882;,
 -51.68551;422.27842;-15.79882;,
 -54.56693;422.27842;-16.92857;,
 -50.49215;437.10738;-13.07130;,
 -50.49215;422.27842;-13.07130;,
 -51.68551;437.10738;-10.34378;,
 -51.68551;422.27842;-10.34378;,
 -54.56693;437.10738;-9.21403;,
 -54.56693;422.27842;-9.21403;,
 -57.44817;437.10738;-10.34378;,
 -57.44817;422.27842;-10.34378;,
 -58.64163;437.10738;-13.07130;,
 -58.64163;422.27842;-13.07130;,
 -57.44817;437.10738;-15.79882;,
 -57.44817;422.27842;-15.79882;,
 -54.56693;437.10738;-13.07130;,
 -54.56693;422.27842;-13.07130;;
 
 224;
 4;0,1,2,3;,
 4;4,5,2,1;,
 4;6,7,8,9;,
 4;10,9,8,11;,
 4;12,13,14,15;,
 4;16,17,14,13;,
 4;18,19,20,21;,
 4;22,23,20,19;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;30,27,26,31;,
 4;28,25,24,29;,
 4;32,33,29,24;,
 4;34,32,24,25;,
 4;35,34,25,28;,
 4;33,35,28,29;,
 4;36,37,26,25;,
 4;38,36,25,24;,
 4;39,38,24,27;,
 4;39,37,36,38;,
 4;40,41,30,29;,
 4;42,40,29,28;,
 4;43,42,28,31;,
 4;43,41,40,42;,
 4;37,43,31,26;,
 4;41,39,27,30;,
 4;43,37,39,41;,
 4;44,45,33,32;,
 4;46,44,32,34;,
 4;47,46,34,35;,
 4;45,47,35,33;,
 4;45,44,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;54,51,50,55;,
 4;52,49,48,53;,
 4;56,57,53,48;,
 4;58,56,48,49;,
 4;59,58,49,52;,
 4;57,59,52,53;,
 4;60,61,50,49;,
 4;62,60,49,48;,
 4;63,62,48,51;,
 4;63,61,60,62;,
 4;64,65,54,53;,
 4;66,64,53,52;,
 4;67,66,52,55;,
 4;67,65,64,66;,
 4;61,67,55,50;,
 4;65,63,51,54;,
 4;67,61,63,65;,
 4;68,69,57,56;,
 4;70,68,56,58;,
 4;71,70,58,59;,
 4;69,71,59,57;,
 4;69,68,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;78,75,74,79;,
 4;76,73,72,77;,
 4;80,81,77,72;,
 4;82,80,72,73;,
 4;83,82,73,76;,
 4;81,83,76,77;,
 4;84,85,74,73;,
 4;86,84,73,72;,
 4;87,86,72,75;,
 4;87,85,84,86;,
 4;88,89,78,77;,
 4;90,88,77,76;,
 4;91,90,76,79;,
 4;91,89,88,90;,
 4;85,91,79,74;,
 4;89,87,75,78;,
 4;91,85,87,89;,
 4;92,93,81,80;,
 4;94,92,80,82;,
 4;95,94,82,83;,
 4;93,95,83,81;,
 4;93,92,94,95;,
 4;96,97,98,99;,
 4;97,100,101,98;,
 4;100,102,103,101;,
 4;102,104,105,103;,
 4;104,106,107,105;,
 4;106,108,109,107;,
 4;108,110,111,109;,
 4;110,96,99,111;,
 3;112,97,96;,
 3;112,100,97;,
 3;112,102,100;,
 3;112,104,102;,
 3;112,106,104;,
 3;112,108,106;,
 3;112,110,108;,
 3;112,96,110;,
 3;113,99,98;,
 3;113,98,101;,
 3;113,101,103;,
 3;113,103,105;,
 3;113,105,107;,
 3;113,107,109;,
 3;113,109,111;,
 3;113,111,99;,
 4;114,115,116,117;,
 4;115,118,119,116;,
 4;118,120,121,119;,
 4;120,122,123,121;,
 4;122,124,125,123;,
 4;124,126,127,125;,
 4;126,128,129,127;,
 4;128,114,117,129;,
 3;130,115,114;,
 3;130,118,115;,
 3;130,120,118;,
 3;130,122,120;,
 3;130,124,122;,
 3;130,126,124;,
 3;130,128,126;,
 3;130,114,128;,
 3;131,117,116;,
 3;131,116,119;,
 3;131,119,121;,
 3;131,121,123;,
 3;131,123,125;,
 3;131,125,127;,
 3;131,127,129;,
 3;131,129,117;,
 4;132,133,134,135;,
 4;133,136,137,134;,
 4;136,138,139,137;,
 4;138,140,141,139;,
 4;140,142,143,141;,
 4;142,144,145,143;,
 4;144,146,147,145;,
 4;146,132,135,147;,
 3;148,133,132;,
 3;148,136,133;,
 3;148,138,136;,
 3;148,140,138;,
 3;148,142,140;,
 3;148,144,142;,
 3;148,146,144;,
 3;148,132,146;,
 3;149,135,134;,
 3;149,134,137;,
 3;149,137,139;,
 3;149,139,141;,
 3;149,141,143;,
 3;149,143,145;,
 3;149,145,147;,
 3;149,147,135;,
 4;150,151,152,153;,
 4;151,154,155,152;,
 4;154,156,157,155;,
 4;156,158,159,157;,
 4;158,160,161,159;,
 4;160,162,163,161;,
 4;162,164,165,163;,
 4;164,150,153,165;,
 3;166,151,150;,
 3;166,154,151;,
 3;166,156,154;,
 3;166,158,156;,
 3;166,160,158;,
 3;166,162,160;,
 3;166,164,162;,
 3;166,150,164;,
 3;167,153,152;,
 3;167,152,155;,
 3;167,155,157;,
 3;167,157,159;,
 3;167,159,161;,
 3;167,161,163;,
 3;167,163,165;,
 3;167,165,153;,
 4;168,169,170,171;,
 4;169,172,173,170;,
 4;172,174,175,173;,
 4;174,176,177,175;,
 4;176,178,179,177;,
 4;178,180,181,179;,
 4;180,182,183,181;,
 4;182,168,171,183;,
 3;184,169,168;,
 3;184,172,169;,
 3;184,174,172;,
 3;184,176,174;,
 3;184,178,176;,
 3;184,180,178;,
 3;184,182,180;,
 3;184,168,182;,
 3;185,171,170;,
 3;185,170,173;,
 3;185,173,175;,
 3;185,175,177;,
 3;185,177,179;,
 3;185,179,181;,
 3;185,181,183;,
 3;185,183,171;,
 4;186,187,188,189;,
 4;187,190,191,188;,
 4;190,192,193,191;,
 4;192,194,195,193;,
 4;194,196,197,195;,
 4;196,198,199,197;,
 4;198,200,201,199;,
 4;200,186,189,201;,
 3;202,187,186;,
 3;202,190,187;,
 3;202,192,190;,
 3;202,194,192;,
 3;202,196,194;,
 3;202,198,196;,
 3;202,200,198;,
 3;202,186,200;,
 3;203,189,188;,
 3;203,188,191;,
 3;203,191,193;,
 3;203,193,195;,
 3;203,195,197;,
 3;203,197,199;,
 3;203,199,201;,
 3;203,201,189;;
 
 MeshMaterialList {
  2;
  224;
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
    "C:\\Users\\student\\Downloads\\145150.png";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
}
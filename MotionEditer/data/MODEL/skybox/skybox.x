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
 67;
 0.00000;31184.38171;0.00000;,
 0.00000;29764.21607;-12376.10878;,
 8751.22435;29764.21607;-8751.22435;,
 12376.10878;29764.21607;0.00054;,
 8751.22435;29764.21607;8751.22435;,
 -0.00108;29764.21607;12376.10878;,
 -8751.22435;29764.21607;8751.22435;,
 -12376.10878;29764.21607;-0.00015;,
 -8751.22435;29764.21607;-8751.22435;,
 0.00000;29764.21607;-12376.10878;,
 0.00000;22753.74253;-22868.09878;,
 16170.15962;22753.74253;-16170.15962;,
 8751.22435;29764.21607;-8751.22435;,
 22868.09878;22753.74253;0.00100;,
 16170.15962;22753.74253;16170.15962;,
 -0.00200;22753.74253;22868.09878;,
 -16170.15962;22753.74253;16170.15962;,
 -22868.09878;22753.74253;-0.00027;,
 -16170.15962;22753.74253;-16170.15962;,
 0.00000;22753.74253;-22868.09878;,
 0.00000;12261.79471;-29878.56607;,
 21127.30813;12261.79471;-21127.30813;,
 29878.56607;12261.79471;0.00131;,
 21127.30813;12261.79471;21127.30813;,
 -0.00261;12261.79471;29878.56607;,
 -21127.30813;12261.79471;21127.30813;,
 -29878.56607;12261.79471;-0.00036;,
 -21127.30813;12261.79471;-21127.30813;,
 0.00000;12261.79471;-29878.56607;,
 0.00000;-114.31631;-32340.31923;,
 22868.09878;-114.31631;-22868.09878;,
 32340.31923;-114.31631;0.00141;,
 22868.09878;-114.31631;22868.09878;,
 -0.00283;-114.31631;32340.31923;,
 -22868.09878;-114.31631;22868.05972;,
 -32340.31923;-114.31631;-0.00039;,
 -22868.09878;-114.31631;-22868.05972;,
 0.00000;-114.31631;-32340.31923;,
 0.00000;-12490.42362;-29878.56607;,
 21127.30813;-12490.42362;-21127.30813;,
 29878.56607;-12490.42362;0.00131;,
 21127.30813;-12490.42362;21127.30813;,
 -0.00261;-12490.42362;29878.56607;,
 -21127.30813;-12490.42362;21127.30813;,
 -29878.56607;-12490.42362;-0.00036;,
 -21127.30813;-12490.42362;-21127.30813;,
 0.00000;-12490.42362;-29878.56607;,
 0.00000;-22982.36128;-22868.09878;,
 16170.15962;-22982.36128;-16170.15962;,
 22868.09878;-22982.36128;0.00100;,
 16170.15962;-22982.36128;16170.15962;,
 -0.00200;-22982.36128;22868.09878;,
 -16170.15962;-22982.36128;16170.15962;,
 -22868.09878;-22982.36128;-0.00027;,
 -16170.15962;-22982.36128;-16170.15962;,
 0.00000;-22982.36128;-22868.09878;,
 0.00000;-29992.88482;-12376.11581;,
 8751.22435;-29992.88482;-8751.22435;,
 12376.11581;-29992.88482;0.00054;,
 8751.22435;-29992.88482;8751.22435;,
 -0.00108;-29992.88482;12376.11581;,
 -8751.22435;-29992.88482;8751.22435;,
 -12376.11581;-29992.88482;-0.00015;,
 -8751.22435;-29992.88482;-8751.22435;,
 0.00000;-29992.88482;-12376.11581;,
 0.00000;-31378.15047;-0.00000;,
 0.00000;-31378.15047;-0.00000;;
 
 64;
 3;0,1,2;,
 3;0,2,3;,
 3;0,3,4;,
 3;0,4,5;,
 3;0,5,6;,
 3;0,6,7;,
 3;0,7,8;,
 3;0,8,1;,
 4;9,10,11,12;,
 4;12,11,13,3;,
 4;3,13,14,4;,
 4;4,14,15,5;,
 4;5,15,16,6;,
 4;6,16,17,7;,
 4;7,17,18,8;,
 4;8,18,19,1;,
 4;10,20,21,11;,
 4;11,21,22,13;,
 4;13,22,23,14;,
 4;14,23,24,15;,
 4;15,24,25,16;,
 4;16,25,26,17;,
 4;17,26,27,18;,
 4;18,27,28,19;,
 4;20,29,30,21;,
 4;21,30,31,22;,
 4;22,31,32,23;,
 4;23,32,33,24;,
 4;24,33,34,25;,
 4;25,34,35,26;,
 4;26,35,36,27;,
 4;27,36,37,28;,
 4;29,38,39,30;,
 4;30,39,40,31;,
 4;31,40,41,32;,
 4;32,41,42,33;,
 4;33,42,43,34;,
 4;34,43,44,35;,
 4;35,44,45,36;,
 4;36,45,46,37;,
 4;38,47,48,39;,
 4;39,48,49,40;,
 4;40,49,50,41;,
 4;41,50,51,42;,
 4;42,51,52,43;,
 4;43,52,53,44;,
 4;44,53,54,45;,
 4;45,54,55,46;,
 4;47,56,57,48;,
 4;48,57,58,49;,
 4;49,58,59,50;,
 4;50,59,60,51;,
 4;51,60,61,52;,
 4;52,61,62,53;,
 4;53,62,63,54;,
 4;54,63,64,55;,
 3;56,65,57;,
 3;57,65,58;,
 3;58,65,59;,
 3;59,66,60;,
 3;60,66,61;,
 3;61,66,62;,
 3;62,66,63;,
 3;63,66,64;;
 
 MeshMaterialList {
  1;
  64;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.400000;0.400000;0.400000;;
   TextureFilename {
    "data\\TEXTURE\\BG\\sky000.jpg";
   }
  }
 }
 MeshNormals {
  58;
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.939831;0.341640;,
  -0.241576;-0.939831;0.241576;,
  -0.341640;-0.939831;-0.000000;,
  -0.241576;-0.939831;-0.241576;,
  0.000000;-0.939831;-0.341640;,
  0.241577;-0.939831;-0.241576;,
  0.341640;-0.939831;-0.000000;,
  0.241576;-0.939831;0.241576;,
  0.000000;-0.709231;0.704976;,
  -0.498494;-0.709230;0.498494;,
  -0.704976;-0.709231;-0.000000;,
  -0.498494;-0.709230;-0.498494;,
  0.000000;-0.709231;-0.704976;,
  0.498494;-0.709230;-0.498494;,
  0.704976;-0.709231;-0.000000;,
  0.498494;-0.709230;0.498494;,
  0.000000;-0.384551;0.923104;,
  -0.652733;-0.384551;0.652733;,
  -0.923104;-0.384551;0.000000;,
  -0.652733;-0.384551;-0.652733;,
  0.000000;-0.384551;-0.923104;,
  0.652733;-0.384551;-0.652733;,
  0.923104;-0.384551;0.000000;,
  0.652733;-0.384551;0.652733;,
  0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.000000;-0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  0.000000;0.384552;0.923104;,
  -0.652733;0.384552;0.652733;,
  -0.923103;0.384552;0.000000;,
  -0.652733;0.384552;-0.652733;,
  0.000000;0.384551;-0.923104;,
  0.652733;0.384551;-0.652733;,
  0.923104;0.384552;0.000000;,
  0.652733;0.384551;0.652733;,
  0.000000;0.709230;0.704977;,
  -0.498495;0.709229;0.498495;,
  -0.704977;0.709230;-0.000000;,
  -0.498495;0.709229;-0.498495;,
  0.000000;0.709230;-0.704977;,
  0.498495;0.709229;-0.498495;,
  0.704977;0.709230;0.000000;,
  0.498495;0.709229;0.498495;,
  0.000000;0.940313;0.340310;,
  -0.240636;0.940313;0.240636;,
  -0.340310;0.940313;-0.000000;,
  -0.240636;0.940313;-0.240636;,
  0.000000;0.940313;-0.340310;,
  0.240636;0.940313;-0.240636;,
  0.340310;0.940313;0.000000;,
  0.240636;0.940313;0.240636;,
  -0.000000;1.000000;0.000000;;
  64;
  3;0,1,2;,
  3;0,2,3;,
  3;0,3,4;,
  3;0,4,5;,
  3;0,5,6;,
  3;0,6,7;,
  3;0,7,8;,
  3;0,8,1;,
  4;1,9,10,2;,
  4;2,10,11,3;,
  4;3,11,12,4;,
  4;4,12,13,5;,
  4;5,13,14,6;,
  4;6,14,15,7;,
  4;7,15,16,8;,
  4;8,16,9,1;,
  4;9,17,18,10;,
  4;10,18,19,11;,
  4;11,19,20,12;,
  4;12,20,21,13;,
  4;13,21,22,14;,
  4;14,22,23,15;,
  4;15,23,24,16;,
  4;16,24,17,9;,
  4;17,25,26,18;,
  4;18,26,27,19;,
  4;19,27,28,20;,
  4;20,28,29,21;,
  4;21,29,30,22;,
  4;22,30,31,23;,
  4;23,31,32,24;,
  4;24,32,25,17;,
  4;25,33,34,26;,
  4;26,34,35,27;,
  4;27,35,36,28;,
  4;28,36,37,29;,
  4;29,37,38,30;,
  4;30,38,39,31;,
  4;31,39,40,32;,
  4;32,40,33,25;,
  4;33,41,42,34;,
  4;34,42,43,35;,
  4;35,43,44,36;,
  4;36,44,45,37;,
  4;37,45,46,38;,
  4;38,46,47,39;,
  4;39,47,48,40;,
  4;40,48,41,33;,
  4;41,49,50,42;,
  4;42,50,51,43;,
  4;43,51,52,44;,
  4;44,52,53,45;,
  4;45,53,54,46;,
  4;46,54,55,47;,
  4;47,55,56,48;,
  4;48,56,49,41;,
  3;49,57,50;,
  3;50,57,51;,
  3;51,57,52;,
  3;52,57,53;,
  3;53,57,54;,
  3;54,57,55;,
  3;55,57,56;,
  3;56,57,49;;
 }
 MeshTextureCoords {
  67;
  0.750000;0.000000;,
  1.000000;0.098977;,
  1.125000;0.098977;,
  0.250000;0.098977;,
  0.375000;0.098977;,
  0.500000;0.098977;,
  0.625000;0.098977;,
  0.750000;0.098977;,
  0.875000;0.098977;,
  0.000000;0.098977;,
  0.000000;0.210062;,
  0.125000;0.210062;,
  0.125000;0.098977;,
  0.250000;0.210062;,
  0.375000;0.210062;,
  0.500000;0.210062;,
  0.625000;0.210062;,
  0.750000;0.210062;,
  0.875000;0.210062;,
  1.000000;0.210062;,
  0.000000;0.344013;,
  0.125000;0.344013;,
  0.250000;0.344013;,
  0.375000;0.344013;,
  0.500000;0.344013;,
  0.625000;0.344013;,
  0.750000;0.344013;,
  0.875000;0.344013;,
  1.000000;0.344013;,
  0.000000;0.500218;,
  0.125000;0.500218;,
  0.250000;0.500218;,
  0.375000;0.500218;,
  0.500000;0.500218;,
  0.625000;0.500218;,
  0.750000;0.500218;,
  0.875000;0.500218;,
  1.000000;0.500218;,
  0.000000;0.656353;,
  0.125000;0.656353;,
  0.250000;0.656353;,
  0.375000;0.656353;,
  0.500000;0.656353;,
  0.625000;0.656353;,
  0.750000;0.656353;,
  0.875000;0.656353;,
  1.000000;0.656353;,
  0.000000;0.790169;,
  0.125000;0.790169;,
  0.250000;0.790169;,
  0.375000;0.790169;,
  0.500000;0.790169;,
  0.625000;0.790169;,
  0.750000;0.790169;,
  0.875000;0.790169;,
  1.000000;0.790169;,
  0.000000;0.901130;,
  0.125000;0.901130;,
  0.250000;0.901130;,
  0.375000;0.901130;,
  0.500000;0.901130;,
  0.625000;0.901130;,
  0.750000;0.901130;,
  0.875000;0.901130;,
  1.000000;0.901130;,
  -0.250000;1.000000;,
  0.750000;1.000000;;
 }
}

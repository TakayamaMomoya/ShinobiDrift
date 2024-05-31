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
 43;
 0.00000;75.44036;-1.59547;,
 1.03646;75.44036;-1.12817;,
 1.03646;0.26141;-1.12817;,
 0.00000;0.26141;-1.59547;,
 1.46577;75.44036;0.00000;,
 1.46577;0.26141;0.00000;,
 1.03646;75.44036;1.12817;,
 1.03646;0.26141;1.12817;,
 0.00000;75.44036;1.59547;,
 0.00000;0.26141;1.59547;,
 -1.03646;75.44036;1.12817;,
 -1.03646;0.26141;1.12817;,
 -1.46577;75.44036;0.00000;,
 -1.46577;0.26141;0.00000;,
 -1.03646;75.44036;-1.12817;,
 -1.03646;0.26141;-1.12817;,
 0.00000;75.44036;0.00000;,
 0.00000;0.26141;0.00000;,
 1.19149;76.28524;-1.60484;,
 1.51664;81.65055;-1.60484;,
 4.75541;80.30901;-1.60484;,
 -1.25499;81.65055;-1.60484;,
 -0.92983;76.28524;-1.60484;,
 2.69148;74.78524;-1.60484;,
 6.71526;78.34916;-1.60484;,
 0.13082;73.72458;-1.60484;,
 -2.42983;74.78524;-1.60484;,
 -2.42983;72.66392;-1.60484;,
 -0.92983;71.16392;-1.60484;,
 1.19149;71.16392;-1.60484;,
 2.69148;72.66392;-1.60484;,
 8.05679;75.11040;-1.60484;,
 8.05679;72.33876;-1.60484;,
 6.71526;69.09999;-1.60484;,
 4.75541;67.14015;-1.60484;,
 1.51664;65.79861;-1.60484;,
 -1.25499;65.79861;-1.60484;,
 -4.49376;67.14015;-1.60484;,
 -6.45360;69.09999;-1.60484;,
 -7.79515;72.33876;-1.60484;,
 -7.79515;75.11039;-1.60484;,
 -6.45360;78.34916;-1.60484;,
 -4.49376;80.30901;-1.60484;;
 
 72;
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
 3;18,19,20;,
 4;21,19,18,22;,
 4;23,18,20,24;,
 3;25,22,18;,
 3;25,26,22;,
 3;25,27,26;,
 3;25,28,27;,
 3;25,29,28;,
 3;25,30,29;,
 3;25,23,30;,
 3;25,18,23;,
 3;23,24,31;,
 4;30,23,31,32;,
 3;30,32,33;,
 4;29,30,33,34;,
 3;29,34,35;,
 4;28,29,35,36;,
 3;28,36,37;,
 4;27,28,37,38;,
 3;27,38,39;,
 4;26,27,39,40;,
 3;26,40,41;,
 4;22,26,41,42;,
 3;22,42,21;,
 3;20,19,18;,
 4;22,18,19,21;,
 4;24,20,18,23;,
 3;18,22,25;,
 3;22,26,25;,
 3;26,27,25;,
 3;27,28,25;,
 3;28,29,25;,
 3;29,30,25;,
 3;30,23,25;,
 3;23,18,25;,
 3;31,24,23;,
 4;32,31,23,30;,
 3;33,32,30;,
 4;34,33,30,29;,
 3;35,34,29;,
 4;36,35,29,28;,
 3;37,36,28;,
 4;38,37,28,27;,
 3;39,38,27;,
 4;40,39,27,26;,
 3;41,40,26;,
 4;42,41,26,22;,
 3;21,42,22;;
 
 MeshMaterialList {
  3;
  72;
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\クローン\\ShinobiDrift\\project\\data\\TEXTURE\\MATERIAL\\5226.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.150000;0.150000;0.150000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\クローン\\ShinobiDrift\\project\\data\\TEXTURE\\MATERIAL\\metal_00003.jpg";
   }
  }
 }
}

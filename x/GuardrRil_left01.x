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
 60;
 -27.89996;19.63102;-1.36605;,
 -26.77740;19.63102;-0.90569;,
 -26.77740;-0.36898;-0.90569;,
 -27.89996;-0.36898;-1.36605;,
 -26.31243;19.63102;0.20573;,
 -26.31243;-0.36898;0.20573;,
 -26.77740;19.63102;1.31714;,
 -26.77740;-0.36898;1.31714;,
 -27.89996;19.63102;1.77750;,
 -27.89996;-0.36898;1.77750;,
 -29.02252;19.63102;1.31714;,
 -29.02252;-0.36898;1.31714;,
 -29.48749;19.63102;0.20573;,
 -29.48749;-0.36898;0.20573;,
 -29.02252;19.63102;-0.90569;,
 -29.02252;-0.36898;-0.90569;,
 -27.89996;19.63102;0.20573;,
 -27.89996;-0.36898;0.20573;,
 27.58066;19.63102;-1.39674;,
 28.70322;19.63102;-0.93638;,
 28.70322;-0.36898;-0.93638;,
 27.58066;-0.36898;-1.39674;,
 29.16819;19.63102;0.17503;,
 29.16819;-0.36898;0.17503;,
 28.70322;19.63102;1.28645;,
 28.70322;-0.36898;1.28645;,
 27.58066;19.63102;1.74681;,
 27.58066;-0.36898;1.74681;,
 26.45810;19.63102;1.28645;,
 26.45810;-0.36898;1.28645;,
 25.99312;19.63102;0.17503;,
 25.99312;-0.36898;0.17503;,
 26.45810;19.63102;-0.93638;,
 26.45810;-0.36898;-0.93638;,
 27.58066;19.63102;0.17503;,
 27.58066;-0.36898;0.17503;,
 -30.26803;10.19510;2.44336;,
 -30.26803;10.19510;2.52338;,
 -30.26804;19.23622;2.52338;,
 -30.26804;19.23622;2.44336;,
 38.60595;10.19511;0.49158;,
 38.60595;10.19511;0.41156;,
 38.60594;19.23622;0.41156;,
 38.60594;19.23622;0.49158;,
 -34.76138;19.23201;0.40493;,
 -34.76113;19.23583;0.48770;,
 -32.38658;19.23564;0.48576;,
 -32.38696;19.22990;0.40161;,
 -30.42484;19.22779;0.39830;,
 -30.42433;19.23543;0.48382;,
 -34.75117;10.19510;0.41159;,
 -32.37166;10.19509;0.41161;,
 -32.36904;10.19490;0.49434;,
 -30.40092;10.19484;0.49526;,
 -30.40443;10.19509;0.41163;,
 -34.74943;10.19497;0.49342;,
 -34.78419;10.19510;2.47898;,
 -34.78931;19.23411;2.47564;,
 -34.78917;19.23602;2.55704;,
 -34.78333;10.19504;2.55990;;
 
 71;
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
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,47,46,49;,
 4;50,44,47,51;,
 4;52,53,49,46;,
 4;54,51,47,48;,
 4;52,46,45,55;,
 4;50,51,52,55;,
 4;52,51,54,53;,
 4;50,56,57,44;,
 4;58,59,55,45;,
 4;58,38,37,59;,
 4;50,55,59,56;,
 4;36,56,59,37;,
 4;44,57,58,45;,
 4;48,42,41,54;,
 4;54,41,40,53;,
 4;43,42,48,49;,
 4;59,37,38,58;,
 4;36,37,59,56;,
 4;37,36,39,38;,
 4;40,43,49,53;;
 
 MeshMaterialList {
  2;
  71;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "C:\\Users\\student\\Pictures\\team\\GardRail01.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.050000;0.050000;0.050000;;
   TextureFilename {
    "C:\\Users\\student\\Pictures\\team\\metal_00003.jpg";
   }
  }
 }
}

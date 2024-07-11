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
 114;
 3.65145;9.49116;-8.66282;,
 3.07873;9.49116;9.37141;,
 3.13241;8.70545;9.37141;,
 3.69899;8.70545;-8.66282;,
 1.80454;8.70545;-10.00000;,
 1.80454;9.49116;-10.00000;,
 -3.93502;9.49116;-9.10293;,
 -3.93502;8.70545;-9.10293;,
 -3.06542;9.49116;0.44854;,
 -3.06542;8.70545;0.44854;,
 -3.11497;9.49116;9.24437;,
 -3.11497;8.70545;9.24437;,
 -1.96751;9.49116;10.00000;,
 -1.96751;8.70545;10.00000;,
 0.00000;9.49116;10.00000;,
 0.00000;8.70545;10.00000;,
 1.96751;9.49116;10.00000;,
 1.96751;8.70545;10.00000;,
 -2.01584;8.89650;-5.90484;,
 2.03822;8.89650;-5.90484;,
 2.03822;8.89650;-6.39648;,
 -2.01584;8.89650;-6.39648;,
 -1.27595;0.86789;-6.39648;,
 2.23119;0.86789;-6.39648;,
 2.23119;0.86789;-5.90484;,
 -1.27595;0.86789;-5.90484;,
 -1.64376;7.89293;-5.90484;,
 -1.44247;6.88935;-5.90484;,
 2.13385;6.88935;-5.90484;,
 2.09567;7.89293;-5.90484;,
 2.13385;6.88935;-6.39648;,
 2.09567;7.89293;-6.39648;,
 -1.44247;6.88935;-6.39648;,
 -1.64376;7.89293;-6.39648;,
 -1.37482;5.88577;-5.90484;,
 -1.30636;4.88220;-5.90484;,
 2.15874;4.88220;-5.90484;,
 2.15834;5.88577;-5.90484;,
 -1.30636;4.88220;-6.39648;,
 -1.37482;5.88577;-6.39648;,
 2.15834;5.88577;-6.39648;,
 2.15874;4.88220;-6.39648;,
 2.18567;3.87862;-5.90484;,
 -1.27137;3.87862;-5.90484;,
 -1.30492;2.87504;-5.90484;,
 2.21410;2.87504;-5.90484;,
 2.18567;3.87862;-6.39648;,
 2.21410;2.87504;-6.39648;,
 -1.30492;2.87504;-6.39648;,
 -1.27137;3.87862;-6.39648;,
 -1.27662;1.87146;-5.90484;,
 -1.27662;1.87146;-6.39648;,
 2.22489;1.87146;-5.90484;,
 2.22489;1.87146;-6.39648;,
 -2.01584;8.89650;6.57204;,
 2.03822;8.89650;6.57204;,
 2.03822;8.89650;6.08041;,
 -2.01584;8.89650;6.08041;,
 -1.27595;0.86789;6.08041;,
 2.23119;0.86789;6.08041;,
 2.23119;0.86789;6.57204;,
 -1.27595;0.86789;6.57204;,
 -1.64376;7.89293;6.57204;,
 -1.44247;6.88935;6.57204;,
 2.13385;6.88935;6.57204;,
 2.09567;7.89293;6.57204;,
 2.13385;6.88935;6.08041;,
 2.09567;7.89293;6.08041;,
 -1.44247;6.88935;6.08041;,
 -1.64376;7.89293;6.08041;,
 -1.37482;5.88577;6.57204;,
 -1.30636;4.88220;6.57204;,
 2.15874;4.88220;6.57204;,
 2.15834;5.88577;6.57204;,
 -1.30636;4.88220;6.08041;,
 -1.37482;5.88577;6.08041;,
 2.15834;5.88577;6.08041;,
 2.15874;4.88220;6.08041;,
 2.18567;3.87862;6.57204;,
 -1.27137;3.87862;6.57204;,
 -1.30492;2.87504;6.57204;,
 2.21410;2.87504;6.57204;,
 2.18567;3.87862;6.08041;,
 2.21410;2.87504;6.08041;,
 -1.30492;2.87504;6.08041;,
 -1.27137;3.87862;6.08041;,
 -1.27662;1.87146;6.57204;,
 -1.27662;1.87146;6.08041;,
 2.22489;1.87146;6.57204;,
 2.22489;1.87146;6.08041;,
 -1.61799;0.87598;-5.18920;,
 2.55922;0.87598;-5.18920;,
 2.55922;0.87598;-6.98733;,
 -1.61799;0.87598;-6.98733;,
 -2.91755;0.06236;-6.98733;,
 3.85878;0.06236;-6.98733;,
 3.85878;0.06236;-5.18920;,
 -2.91755;0.06236;-5.18920;,
 3.85878;0.30067;-5.18920;,
 -2.91755;0.30067;-5.18920;,
 3.85878;0.30067;-6.98733;,
 -2.91755;0.30067;-6.98733;,
 -1.61799;0.86513;7.22956;,
 2.55922;0.86513;7.22956;,
 2.55922;0.86513;5.43142;,
 -1.61799;0.86513;5.43142;,
 -2.91755;0.05152;5.43142;,
 3.85878;0.05152;5.43142;,
 3.85878;0.05152;7.22956;,
 -2.91755;0.05152;7.22956;,
 3.85878;0.28983;7.22956;,
 -2.91755;0.28983;7.22956;,
 3.85878;0.28983;5.43142;,
 -2.91755;0.28983;5.43142;;
 
 106;
 4;0,1,2,3;,
 4;0,3,4,5;,
 4;6,5,4,7;,
 3;8,5,6;,
 3;9,7,4;,
 4;9,8,6,7;,
 4;10,8,9,11;,
 3;12,8,10;,
 4;13,12,10,11;,
 4;14,12,13,15;,
 4;14,5,8,12;,
 3;16,5,14;,
 4;14,15,17,16;,
 4;1,16,17,2;,
 4;5,16,1,0;,
 4;9,4,17,15;,
 4;15,13,11,9;,
 4;2,17,4,3;,
 4;18,19,20,21;,
 4;22,23,24,25;,
 4;26,27,28,29;,
 4;19,18,26,29;,
 4;29,28,30,31;,
 4;20,19,29,31;,
 4;32,33,31,30;,
 4;21,20,31,33;,
 4;21,33,26,18;,
 4;32,27,26,33;,
 4;34,35,36,37;,
 4;28,27,34,37;,
 4;38,39,40,41;,
 4;40,39,32,30;,
 4;32,39,34,27;,
 4;30,28,37,40;,
 4;37,36,41,40;,
 4;34,39,38,35;,
 4;42,43,44,45;,
 4;42,36,35,43;,
 4;41,36,42,46;,
 4;47,46,42,45;,
 4;46,47,48,49;,
 4;38,41,46,49;,
 4;50,51,22,25;,
 4;48,51,50,44;,
 4;50,52,45,44;,
 4;50,25,24,52;,
 4;23,53,52,24;,
 4;47,45,52,53;,
 4;51,53,23,22;,
 4;47,53,51,48;,
 4;48,44,43,49;,
 4;38,49,43,35;,
 4;54,55,56,57;,
 4;58,59,60,61;,
 4;62,63,64,65;,
 4;55,54,62,65;,
 4;65,64,66,67;,
 4;56,55,65,67;,
 4;68,69,67,66;,
 4;57,56,67,69;,
 4;57,69,62,54;,
 4;68,63,62,69;,
 4;70,71,72,73;,
 4;64,63,70,73;,
 4;74,75,76,77;,
 4;76,75,68,66;,
 4;68,75,70,63;,
 4;66,64,73,76;,
 4;73,72,77,76;,
 4;70,75,74,71;,
 4;78,79,80,81;,
 4;78,72,71,79;,
 4;77,72,78,82;,
 4;83,82,78,81;,
 4;82,83,84,85;,
 4;74,77,82,85;,
 4;86,87,58,61;,
 4;84,87,86,80;,
 4;86,88,81,80;,
 4;86,61,60,88;,
 4;59,89,88,60;,
 4;83,81,88,89;,
 4;87,89,59,58;,
 4;83,89,87,84;,
 4;84,80,79,85;,
 4;74,85,79,71;,
 4;90,91,92,93;,
 4;94,95,96,97;,
 4;97,96,98,99;,
 4;90,99,98,91;,
 4;95,100,98,96;,
 4;92,91,98,100;,
 4;100,95,94,101;,
 4;93,92,100,101;,
 4;94,97,99,101;,
 4;93,101,99,90;,
 4;102,103,104,105;,
 4;106,107,108,109;,
 4;109,108,110,111;,
 4;102,111,110,103;,
 4;107,112,110,108;,
 4;104,103,110,112;,
 4;112,107,106,113;,
 4;105,104,112,113;,
 4;106,109,111,113;,
 4;105,113,111,102;;
 
 MeshMaterialList {
  3;
  106;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  2;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\MATERIAL\\N845_mokumetex_TP_V4.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\MATERIAL\\wood-texture_00008.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\MATERIAL\\wood-texture_00016.jpg";
   }
  }
 }
}

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
 50;
 2.97416;4.78539;4.78536;,
 2.97416;0.00004;6.76750;,
 43.03673;0.00004;5.54045;,
 43.03673;3.91774;3.91770;,
 2.97416;-4.78532;4.78536;,
 43.03673;-3.91767;3.91770;,
 2.97416;-6.76752;-0.00000;,
 43.03673;-4.62827;-0.00000;,
 2.97416;-4.78532;-4.78536;,
 43.03673;-3.91767;-3.91770;,
 2.97416;0.00004;-6.76750;,
 43.03673;0.00004;-5.54045;,
 2.97416;4.78539;-4.78536;,
 43.03673;3.91774;-3.91770;,
 2.97416;6.76748;0.00000;,
 43.03673;5.54049;0.00000;,
 -6.24626;0.00004;3.45719;,
 -6.24626;2.44462;2.44461;,
 -8.17803;0.00004;0.00000;,
 -6.24626;-2.44458;2.44461;,
 -6.24626;-3.45715;0.00000;,
 -6.24626;-2.44458;-2.44461;,
 -6.24626;0.00004;-3.45719;,
 -6.24626;2.44462;-2.44461;,
 -6.24626;3.45723;0.00000;,
 51.58335;2.72661;2.72660;,
 51.58335;0.00004;3.85600;,
 54.36642;0.00004;0.00000;,
 51.58335;-2.72653;2.72660;,
 51.58335;-2.87922;-0.00000;,
 51.58335;-2.72653;-2.72660;,
 51.58335;0.00004;-3.85600;,
 51.58335;2.72661;-2.72660;,
 51.58335;3.85600;0.00000;,
 -2.42154;0.00004;5.90590;,
 -2.42154;4.17613;4.17610;,
 -2.42154;-4.17606;4.17610;,
 -2.42154;-5.90586;0.00000;,
 -2.42154;-4.17606;-4.17610;,
 -2.42154;0.00004;-5.90590;,
 -2.42154;4.17613;-4.17610;,
 -2.42154;5.90593;0.00000;,
 47.88883;5.39185;0.00000;,
 47.88883;3.81261;3.81260;,
 47.88883;3.81261;-3.81260;,
 47.88883;0.00004;-5.39181;,
 47.88886;-3.81256;-3.81260;,
 47.88886;-4.20274;-0.00000;,
 47.88886;-3.81256;3.81260;,
 47.88883;0.00004;5.39181;;
 
 56;
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
 4;35,34,1,0;,
 4;34,36,4,1;,
 4;36,37,6,4;,
 4;37,38,8,6;,
 4;38,39,10,8;,
 4;39,40,12,10;,
 4;40,41,14,12;,
 4;41,35,0,14;,
 4;15,3,43,42;,
 4;13,15,42,44;,
 4;11,13,44,45;,
 4;9,11,45,46;,
 4;7,9,46,47;,
 4;5,7,47,48;,
 4;2,5,48,49;,
 4;3,2,49,43;;
 
 MeshMaterialList {
  1;
  56;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  50;
  -0.731184;0.482374;0.482376;,
  -0.731184;0.000001;0.682181;,
  -0.731184;-0.482374;0.482374;,
  -0.731183;-0.682181;0.000000;,
  -0.731184;-0.482374;-0.482374;,
  -0.731184;0.000001;-0.682181;,
  -0.731184;0.482374;-0.482376;,
  -0.731184;0.682180;0.000000;,
  0.625221;0.551860;0.551859;,
  0.625222;0.000001;0.780447;,
  0.627477;-0.640148;0.443263;,
  0.536085;-0.844164;-0.000000;,
  0.627477;-0.640148;-0.443263;,
  0.625222;0.000001;-0.780447;,
  0.625221;0.551860;-0.551859;,
  0.625222;0.780447;0.000000;,
  -1.000000;0.000000;-0.000000;,
  0.999170;-0.040744;-0.000000;,
  -0.357873;0.660276;0.660275;,
  -0.357874;0.000000;0.933770;,
  -0.357875;-0.660274;0.660276;,
  -0.357877;-0.933769;0.000000;,
  -0.357875;-0.660274;-0.660276;,
  -0.357874;0.000000;-0.933770;,
  -0.357873;0.660276;-0.660275;,
  -0.357872;0.933771;0.000000;,
  0.211682;0.691082;0.691083;,
  0.211683;0.977338;0.000000;,
  0.211682;0.691082;-0.691083;,
  0.211680;0.000001;-0.977339;,
  0.223332;-0.780248;-0.584240;,
  0.191991;-0.981397;-0.000000;,
  0.223332;-0.780248;0.584240;,
  0.211680;0.000001;0.977339;,
  -0.063904;0.705663;0.705660;,
  -0.063905;0.000000;0.997956;,
  -0.061321;-0.724168;0.686892;,
  -0.056169;-0.998421;0.000000;,
  -0.061321;-0.724168;-0.686892;,
  -0.063905;0.000000;-0.997956;,
  -0.063904;0.705663;-0.705660;,
  -0.063902;0.997956;0.000000;,
  0.030618;0.706776;0.706775;,
  0.030618;0.999531;0.000000;,
  0.030618;0.706776;-0.706775;,
  0.030617;0.000000;-0.999531;,
  0.043311;-0.766251;-0.641080;,
  0.049614;-0.998768;-0.000000;,
  0.043311;-0.766251;0.641080;,
  0.030617;0.000000;0.999531;;
  56;
  4;34,35,49,42;,
  4;35,36,48,49;,
  4;36,37,47,48;,
  4;37,38,46,47;,
  4;38,39,45,46;,
  4;39,40,44,45;,
  4;40,41,43,44;,
  4;41,34,42,43;,
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
  4;18,19,35,34;,
  4;19,20,36,35;,
  4;20,21,37,36;,
  4;21,22,38,37;,
  4;22,23,39,38;,
  4;23,24,40,39;,
  4;24,25,41,40;,
  4;25,18,34,41;,
  4;43,42,26,27;,
  4;44,43,27,28;,
  4;45,44,28,29;,
  4;46,45,29,30;,
  4;47,46,30,31;,
  4;48,47,31,32;,
  4;49,48,32,33;,
  4;42,49,33,26;;
 }
 MeshTextureCoords {
  50;
  0.200208;0.668439;,
  0.200208;0.689442;,
  0.056663;0.689442;,
  0.056663;0.672247;,
  0.200208;0.710445;,
  0.056663;0.706637;,
  0.200208;0.719145;,
  0.056663;0.709756;,
  0.200208;0.710445;,
  0.056663;0.706637;,
  0.200208;0.689442;,
  0.056663;0.689442;,
  0.200208;0.668439;,
  0.056663;0.672247;,
  0.200208;0.659739;,
  0.056663;0.665125;,
  0.233245;0.689442;,
  0.233245;0.678713;,
  0.240167;0.689442;,
  0.233245;0.700172;,
  0.233245;0.704616;,
  0.233245;0.700172;,
  0.233245;0.689442;,
  0.233245;0.678713;,
  0.233245;0.674268;,
  0.026040;0.677475;,
  0.026040;0.689442;,
  0.016068;0.689442;,
  0.026040;0.701409;,
  0.026040;0.702079;,
  0.026040;0.701409;,
  0.026040;0.689442;,
  0.026040;0.677475;,
  0.026040;0.672518;,
  0.219541;0.689442;,
  0.219541;0.671113;,
  0.219541;0.707771;,
  0.219541;0.715363;,
  0.219541;0.707771;,
  0.219541;0.689442;,
  0.219541;0.671113;,
  0.219541;0.663521;,
  0.039278;0.665777;,
  0.039278;0.672708;,
  0.039278;0.672708;,
  0.039278;0.689442;,
  0.039278;0.706176;,
  0.039278;0.707888;,
  0.039278;0.706176;,
  0.039278;0.689442;;
 }
}
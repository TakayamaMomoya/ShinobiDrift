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
 447;
 -14.16092;19.33183;14.39204;,
 -12.01561;19.33183;14.39204;,
 -12.01561;21.05026;14.39204;,
 -14.16092;21.05026;14.39204;,
 -12.01561;19.13183;14.39204;,
 -14.16092;19.13183;14.39204;,
 -11.83906;21.05026;14.39204;,
 -11.83906;19.33183;14.39204;,
 -14.16092;21.15026;14.30465;,
 -12.01561;21.15026;14.30465;,
 -14.24919;19.33183;14.30465;,
 -14.24919;21.05026;14.30465;,
 -14.24919;19.13183;14.30465;,
 -11.92734;19.23183;14.35709;,
 -11.83906;19.23183;14.30465;,
 -11.92734;19.13183;14.30465;,
 -11.83906;21.15026;14.30465;,
 -14.16092;19.33183;-14.39204;,
 -14.16092;21.05026;-14.39204;,
 -12.01561;21.05026;-14.39204;,
 -12.01561;19.33183;-14.39204;,
 -14.24919;21.05026;-14.30465;,
 -14.24919;19.33183;-14.30465;,
 -12.01561;21.15026;-14.30465;,
 -14.16092;21.15026;-14.30465;,
 -11.83906;19.33183;-14.39204;,
 -11.83906;21.05026;-14.39204;,
 -14.16092;19.13183;-14.39204;,
 -12.01561;19.13183;-14.39204;,
 -14.24919;19.13183;-14.30465;,
 -11.83906;21.15026;-14.30465;,
 -11.92734;19.23183;-14.35709;,
 -11.92734;19.13183;-14.30465;,
 -11.83906;19.23183;-14.30465;,
 11.64812;19.33183;14.39204;,
 11.64812;21.05026;14.39204;,
 11.64812;19.23183;14.30465;,
 11.82467;21.05026;14.39204;,
 11.82467;19.33183;14.39204;,
 11.64812;21.15026;14.30465;,
 11.73640;19.23183;14.35709;,
 11.82467;19.13183;14.39204;,
 11.73640;19.13183;14.30465;,
 11.82467;21.15026;14.30465;,
 14.16092;19.33183;14.39204;,
 14.16092;21.05026;14.39204;,
 14.24919;21.05026;14.30465;,
 14.24919;19.33183;14.30465;,
 14.16092;21.15026;14.30465;,
 14.16092;19.13183;14.39204;,
 14.24919;19.13183;14.30465;,
 14.16092;21.05026;-14.39204;,
 14.16092;19.33183;-14.39204;,
 11.82467;19.33183;-14.39204;,
 11.82467;21.05026;-14.39204;,
 14.24919;19.33183;-14.30465;,
 14.24919;21.05026;-14.30465;,
 11.82467;19.13183;-14.39204;,
 14.16092;19.13183;-14.39204;,
 11.64812;21.05026;-14.39204;,
 11.64812;19.33183;-14.39204;,
 14.16092;21.15026;-14.30465;,
 11.82467;21.15026;-14.30465;,
 14.24919;19.13183;-14.30465;,
 11.73640;19.23183;-14.35709;,
 11.64812;19.23183;-14.30465;,
 11.73640;19.13183;-14.30465;,
 11.64812;21.15026;-14.30465;,
 11.64812;19.23183;12.35952;,
 -11.83906;19.23183;12.35952;,
 11.73640;19.13183;12.35952;,
 -11.92734;19.13183;12.35952;,
 11.64812;19.23183;12.18471;,
 -11.83906;19.23183;12.18471;,
 11.73640;19.19184;12.27211;,
 11.82467;19.13183;12.27211;,
 11.82467;19.23183;12.18471;,
 -11.92734;19.19184;12.27211;,
 -12.01561;19.23183;12.18471;,
 -12.01561;19.13183;12.27211;,
 14.24919;19.33183;12.35952;,
 14.24919;21.05026;12.35952;,
 14.24919;19.13183;12.35952;,
 14.24919;21.05026;12.18471;,
 14.24919;19.33183;12.18471;,
 14.16092;21.15026;12.35952;,
 14.21389;19.23183;12.27211;,
 14.16092;19.23183;12.18471;,
 14.16092;19.13183;12.27211;,
 14.16092;21.15026;12.18471;,
 11.82467;21.15026;12.35952;,
 11.82467;21.15026;12.18471;,
 11.64812;21.15026;12.35952;,
 11.64812;21.15026;12.18471;,
 -11.83906;21.15026;12.35952;,
 -12.01561;21.15026;12.35952;,
 -11.83906;21.15026;12.18471;,
 -12.01561;21.15026;12.18471;,
 -14.16092;21.15026;12.35952;,
 -14.16092;21.15026;12.18471;,
 -14.24919;21.05026;12.35952;,
 -14.24919;21.05026;12.18471;,
 -14.24919;19.33183;12.35952;,
 -14.24919;19.33183;12.18471;,
 -14.24919;19.13183;12.35952;,
 -14.21389;19.23183;12.27211;,
 -14.16092;19.13183;12.27211;,
 -14.16092;19.23183;12.18471;,
 14.16092;21.15026;-12.08591;,
 11.82467;21.15026;-12.08591;,
 11.82467;21.15026;-12.26072;,
 14.16092;21.15026;-12.26072;,
 11.64812;21.15026;-12.08591;,
 14.24919;21.05026;-12.08591;,
 14.24919;21.05026;-12.26072;,
 11.64812;21.15026;-12.26072;,
 -11.83906;21.15026;-12.26072;,
 -12.01561;21.15026;-12.26072;,
 -11.83906;21.15026;-12.08591;,
 -12.01561;21.15026;-12.08591;,
 -14.16092;21.15026;-12.08591;,
 -14.16092;21.15026;-12.26072;,
 -14.24919;21.05026;-12.08591;,
 -14.24919;21.05026;-12.26072;,
 11.82467;19.23183;-12.08591;,
 14.16092;19.23183;-12.08591;,
 11.64812;19.23183;-12.08591;,
 14.16092;19.13183;-12.17331;,
 11.82467;19.13183;-12.17331;,
 14.24919;19.33183;-12.08591;,
 11.73640;19.19184;-12.17331;,
 11.73640;19.13183;-12.26072;,
 11.64812;19.23183;-12.26072;,
 14.21389;19.23183;-12.17331;,
 14.24919;19.33183;-12.26072;,
 14.24919;19.13183;-12.26072;,
 -11.83906;19.23183;-12.08591;,
 -11.83906;19.23183;-12.26072;,
 -12.01561;19.23183;-12.08591;,
 -11.92734;19.19184;-12.17331;,
 -11.92734;19.13183;-12.26072;,
 -12.01561;19.13183;-12.17331;,
 -14.16092;19.23183;-12.08591;,
 -14.24919;19.33183;-12.08591;,
 -14.16092;19.13183;-12.17331;,
 -14.21389;19.23183;-12.17331;,
 -14.24919;19.13183;-12.26072;,
 -14.24919;19.33183;-12.26072;,
 -12.10714;8.59499;14.04261;,
 -12.10714;8.59499;12.26450;,
 -12.19675;8.49499;12.26450;,
 -12.19675;8.49499;14.04261;,
 -12.19675;8.59499;12.18460;,
 -12.19675;8.59499;14.12251;,
 -14.37439;8.59499;14.12251;,
 -14.37439;8.49499;14.04261;,
 -14.46399;8.59499;14.04261;,
 -14.46399;8.59499;12.26450;,
 -14.37439;8.49499;12.26450;,
 -14.37439;8.59499;12.18460;,
 11.66667;8.59499;12.87251;,
 11.66667;8.59499;14.65062;,
 11.75628;8.41589;14.44157;,
 11.75628;8.41589;12.69858;,
 11.75628;8.59499;14.73052;,
 11.75628;8.59499;12.79261;,
 14.12774;8.51391;12.62026;,
 14.12774;8.41589;12.69858;,
 14.21734;8.51391;12.69858;,
 14.21734;8.51391;14.44157;,
 14.12774;8.41589;14.44157;,
 14.12774;8.51391;14.51989;,
 14.31519;8.51391;-14.73294;,
 12.17955;8.59499;-15.04205;,
 12.17955;8.41589;-14.65462;,
 14.31519;8.41589;-14.65462;,
 12.09886;8.59499;-14.96215;,
 14.39589;8.51391;-14.65462;,
 14.39589;8.51391;-12.82310;,
 14.31519;8.41589;-12.82310;,
 14.31519;8.51391;-12.74478;,
 12.17955;8.59499;-13.01382;,
 12.17955;8.41589;-12.82310;,
 12.09886;8.59499;-13.09372;,
 -12.31121;8.59499;-12.31869;,
 -12.31121;8.59499;-14.18712;,
 -12.39190;8.49499;-14.18712;,
 -12.39190;8.49499;-12.31869;,
 -12.39190;8.59499;-14.26702;,
 -12.39190;8.59499;-12.23879;,
 -14.35300;8.59499;-12.23879;,
 -14.35300;8.49499;-12.31869;,
 -14.43370;8.59499;-12.31869;,
 -14.43370;8.59499;-14.18712;,
 -14.35300;8.49499;-14.18712;,
 -14.35300;8.59499;-14.26702;,
 -14.60901;19.18044;15.12805;,
 14.60901;19.18044;15.12805;,
 27.38700;0.38520;29.95940;,
 -27.38700;0.38520;29.95940;,
 -14.60901;19.18044;-15.12805;,
 -27.38700;0.38520;-29.95940;,
 14.60901;19.18044;-15.12805;,
 15.84983;20.38520;-16.41295;,
 -15.84983;20.38520;-16.41295;,
 -15.84983;20.38520;16.41295;,
 15.84983;20.38520;16.41295;,
 29.71313;0.38520;0.00000;,
 27.38700;0.38520;-29.95940;,
 29.71313;0.38520;-28.44102;,
 29.71313;0.38520;-32.50402;,
 29.71313;0.38520;-24.37802;,
 29.71313;0.38520;-20.31501;,
 29.71313;0.38520;-16.25201;,
 29.71313;0.38520;-12.18901;,
 29.71313;0.38520;-8.12601;,
 29.71313;0.38520;-4.06300;,
 29.71313;0.38520;4.06300;,
 29.71313;0.38520;8.12601;,
 29.71313;0.38520;12.18901;,
 29.71313;0.38520;16.25201;,
 29.71313;0.38520;20.31501;,
 29.71313;0.38520;24.37802;,
 29.71313;0.38520;28.44102;,
 29.71313;0.38520;32.50402;,
 0.00000;0.38520;-32.50402;,
 3.71414;0.38520;-32.50402;,
 7.42828;0.38520;-32.50402;,
 11.14242;0.38520;-32.50402;,
 14.85656;0.38520;-32.50402;,
 18.57071;0.38520;-32.50402;,
 22.28485;0.38520;-32.50402;,
 25.99899;0.38520;-32.50402;,
 -11.14242;0.38520;-32.50402;,
 -14.85656;0.38520;-32.50402;,
 -7.42828;0.38520;-32.50402;,
 -3.71414;0.38520;-32.50402;,
 -18.57071;0.38520;-32.50402;,
 -22.28485;0.38520;-32.50402;,
 -25.99899;0.38520;-32.50402;,
 -29.71313;0.38520;-32.50402;,
 -29.71313;0.38520;0.00000;,
 -29.71313;0.38520;-28.44102;,
 -29.71313;0.38520;-24.37802;,
 -29.71313;0.38520;-20.31501;,
 -29.71313;0.38520;-16.25201;,
 -29.71313;0.38520;-12.18901;,
 -29.71313;0.38520;-8.12601;,
 -29.71313;0.38520;-4.06300;,
 -29.71313;0.38520;4.06300;,
 -29.71313;0.38520;8.12601;,
 -29.71313;0.38520;12.18901;,
 -29.71313;0.38520;16.25201;,
 -29.71313;0.38520;20.31501;,
 -29.71313;0.38520;24.37802;,
 -29.71313;0.38520;28.44102;,
 -29.71312;0.46628;31.91171;,
 25.99899;0.38520;32.50402;,
 22.28485;0.38520;32.50402;,
 18.57071;0.38520;32.50402;,
 14.85656;0.38520;32.50402;,
 11.14242;0.38520;32.50402;,
 7.42828;0.38520;32.50402;,
 13.69350;0.38520;31.23171;,
 0.00000;0.38520;32.50402;,
 3.71414;0.38520;32.50402;,
 -3.71414;0.38520;32.50402;,
 -7.42828;0.38520;32.50402;,
 -11.14242;0.38520;32.50402;,
 -14.85656;0.38520;32.50402;,
 -18.57071;0.38520;32.50402;,
 -22.28485;0.38520;32.50402;,
 -25.99899;0.38520;32.50402;,
 20.75781;10.38520;-9.34047;,
 20.75781;10.38520;-7.50183;,
 20.75781;10.38520;-11.17911;,
 20.75781;10.38520;-13.01774;,
 20.75781;10.38520;9.34047;,
 20.75781;10.38520;7.50183;,
 20.75781;10.38520;11.17911;,
 20.75781;10.38520;13.01774;,
 20.75781;10.38520;14.85638;,
 20.75781;10.38520;16.69501;,
 20.75781;10.38520;18.53365;,
 20.75781;10.38520;20.37228;,
 20.75781;10.38520;22.21092;,
 20.75781;10.38520;-14.85638;,
 20.75781;10.38520;-16.69501;,
 20.75781;10.38520;-18.53365;,
 20.75781;10.38520;-20.37228;,
 20.75781;10.38520;-22.21092;,
 19.06864;10.38520;-22.21092;,
 17.37946;10.38520;-22.21092;,
 15.69029;10.38520;-22.21092;,
 14.00112;10.38520;-22.21092;,
 12.31196;10.38520;-22.21092;,
 10.62279;10.38520;-22.21092;,
 8.93362;10.38520;-22.21092;,
 7.24445;10.38520;-22.21092;,
 -8.93362;10.38520;-22.21092;,
 -7.24445;10.38520;-22.21092;,
 -10.62279;10.38520;-22.21092;,
 -12.31196;10.38520;-22.21092;,
 -14.00112;10.38520;-22.21092;,
 -15.69029;10.38520;-22.21092;,
 -17.37946;10.38520;-22.21092;,
 -19.06864;10.38520;-22.21092;,
 -20.75781;10.38520;-22.21092;,
 -20.75781;10.38520;-20.37228;,
 -20.75781;10.38520;-18.53365;,
 -20.75781;10.38520;-16.69501;,
 -20.75781;10.38520;-14.85638;,
 -20.75781;10.38520;-13.01774;,
 -20.75781;10.38520;-11.17911;,
 -20.75781;10.38520;-9.34047;,
 -20.75781;10.38520;-7.50183;,
 -20.75781;10.38520;7.50183;,
 -20.75781;10.38520;9.34047;,
 -20.75781;10.38520;11.17911;,
 -20.75781;10.38520;13.01774;,
 -20.75781;10.38520;14.85638;,
 -20.75781;10.38520;16.69501;,
 -20.75781;10.38520;18.53365;,
 -20.75781;10.38520;20.37228;,
 -20.75781;10.38520;22.21092;,
 -19.06864;10.38520;22.21092;,
 -17.37946;10.38520;22.21092;,
 -15.69029;10.38520;22.21092;,
 -14.00112;10.38520;22.21092;,
 -12.31196;10.38520;22.21092;,
 -10.62279;10.38520;22.21092;,
 -8.93362;10.38520;22.21092;,
 -7.24445;10.38520;22.21092;,
 8.93362;10.38520;22.21092;,
 7.24445;10.38520;22.21092;,
 10.62279;10.38520;22.21092;,
 12.31196;10.38520;22.21092;,
 14.00112;10.38520;22.21092;,
 15.69029;10.38520;22.21092;,
 17.37946;10.38520;22.21092;,
 19.06864;10.38520;22.21092;,
 25.16154;5.36752;-5.59920;,
 25.16154;5.36752;-6.50036;,
 25.16154;5.36752;-3.62759;,
 25.16154;5.36752;3.72606;,
 25.16154;5.36752;5.69767;,
 25.16154;5.36752;8.57044;,
 25.16154;5.36752;6.59883;,
 25.16154;5.36752;9.47160;,
 25.16154;5.36752;11.44320;,
 25.16154;5.36752;12.34436;,
 25.16154;5.36752;14.31597;,
 25.16154;5.36752;15.21714;,
 25.16154;5.36752;17.18875;,
 25.16154;5.36752;18.08990;,
 25.16154;5.36752;20.06151;,
 25.16154;5.36752;20.96267;,
 25.16154;5.36752;22.93428;,
 25.16154;5.36752;23.83543;,
 25.16154;5.36752;25.80705;,
 25.16154;5.36752;26.81823;,
 22.46913;5.36752;26.70820;,
 23.31371;5.36752;26.70820;,
 21.62454;5.36752;26.70820;,
 18.93212;5.36752;26.70820;,
 19.77672;5.36752;26.70820;,
 17.08429;5.36752;26.70820;,
 16.23972;5.36752;26.70820;,
 14.39188;5.36752;26.70820;,
 13.54730;5.36752;26.70820;,
 11.69947;5.36752;26.70820;,
 10.85488;5.36752;26.70820;,
 9.00705;5.36752;26.70820;,
 8.16247;5.36752;26.70820;,
 6.31464;5.36752;26.70820;,
 5.47005;5.36752;26.70820;,
 3.62222;5.36752;26.70820;,
 -3.62222;5.36752;26.70820;,
 -4.46681;5.36752;26.70820;,
 -6.31464;5.36752;26.70820;,
 -7.15922;5.36752;26.70820;,
 -9.00705;5.36752;26.70820;,
 -9.85164;5.36752;26.70820;,
 25.16154;5.36752;-8.47196;,
 25.16154;5.36752;-9.37312;,
 25.16154;5.36752;-11.34474;,
 25.16154;5.36752;-12.24590;,
 25.16154;5.36752;-14.21750;,
 25.16154;5.36752;-15.11866;,
 25.16154;5.36752;-17.09027;,
 25.16154;5.36752;-17.99143;,
 25.16154;5.36752;-19.96304;,
 25.16154;5.36752;-20.86419;,
 25.16154;5.36752;-22.83580;,
 25.16154;5.36752;-23.73695;,
 20.92988;9.78282;-22.39504;,
 25.16154;5.36752;-25.70857;,
 25.16154;5.36752;-26.60973;,
 23.31371;5.36752;-26.60973;,
 22.46913;5.36752;-26.60973;,
 20.62130;5.36752;-26.60973;,
 19.77672;5.36752;-26.60973;,
 17.92888;5.36752;-26.60973;,
 17.08429;5.36752;-26.60973;,
 15.23647;5.36752;-26.60973;,
 14.39188;5.36752;-26.60973;,
 12.54405;5.36752;-26.60973;,
 11.69947;5.36752;-26.60973;,
 9.85164;5.36752;-26.60973;,
 9.00705;5.36752;-26.60973;,
 7.15922;5.36752;-26.60973;,
 6.31464;5.36752;-26.60973;,
 4.46680;5.36752;-26.60973;,
 3.62222;5.36752;-26.60973;,
 -3.62222;5.36752;-26.60973;,
 -6.31464;5.36752;-26.60973;,
 -5.47005;5.36752;-26.60973;,
 -8.16247;5.36752;-26.60973;,
 -9.00705;5.36752;-26.60973;,
 -10.85488;5.36752;-26.60973;,
 -11.69947;5.36752;-26.60973;,
 -13.54730;5.36752;-26.60973;,
 -14.39189;5.36752;-26.60973;,
 -16.23972;5.36752;-26.60973;,
 -17.08430;5.36752;-26.60973;,
 -18.93213;5.36752;-26.60973;,
 -19.77671;5.36752;-26.60973;,
 -21.62455;5.36752;-26.60973;,
 -22.46913;5.36752;-26.60973;,
 -24.31696;5.36752;-26.60973;,
 -25.16155;5.36752;-26.60973;,
 -25.16155;5.36752;-24.63813;,
 -25.16155;5.36752;-23.73695;,
 -25.16155;5.36752;-21.76536;,
 -25.16155;5.36752;-20.86419;,
 -25.16155;5.36752;-18.89258;,
 -25.16155;5.36752;-17.99143;,
 -25.16155;5.36752;-16.01982;,
 -25.16155;5.36752;-15.11866;,
 -25.16155;5.36752;-13.14705;,
 -25.16155;5.36752;-12.24590;,
 -25.16155;5.36752;-10.27429;,
 -25.16155;5.36752;-9.37312;,
 -25.16155;5.36752;-7.40152;,
 -25.16155;5.36752;-6.50036;,
 -25.16155;5.36752;-4.52875;,
 -25.16155;5.36752;-3.62759;;
 
 724;
 4;0,1,2,3;,
 4;4,1,0,5;,
 4;6,2,1,7;,
 4;8,3,2,9;,
 4;10,0,3,11;,
 4;10,12,5,0;,
 3;13,7,1;,
 3;13,14,7;,
 3;13,15,14;,
 3;13,4,15;,
 3;13,1,4;,
 4;6,16,9,2;,
 3;8,11,3;,
 4;17,18,19,20;,
 4;21,18,17,22;,
 4;23,19,18,24;,
 4;25,20,19,26;,
 4;27,17,20,28;,
 4;27,29,22,17;,
 3;21,24,18;,
 4;23,30,26,19;,
 3;31,28,20;,
 3;31,32,28;,
 3;31,33,32;,
 3;31,25,33;,
 3;31,20,25;,
 4;7,34,35,6;,
 4;36,34,7,14;,
 4;37,35,34,38;,
 4;16,6,35,39;,
 3;40,38,34;,
 3;40,41,38;,
 3;40,42,41;,
 3;40,36,42;,
 3;40,34,36;,
 4;37,43,39,35;,
 4;44,45,37,38;,
 4;46,45,44,47;,
 4;43,37,45,48;,
 4;49,44,38,41;,
 4;49,50,47,44;,
 3;46,48,45;,
 4;51,52,53,54;,
 4;55,52,51,56;,
 4;57,53,52,58;,
 4;59,54,53,60;,
 4;61,51,54,62;,
 3;61,56,51;,
 4;55,63,58,52;,
 3;64,60,53;,
 3;64,65,60;,
 3;64,66,65;,
 3;64,57,66;,
 3;64,53,57;,
 4;59,67,62,54;,
 4;60,25,26,59;,
 4;33,25,60,65;,
 4;67,59,26,30;,
 4;68,36,14,69;,
 4;42,36,68,70;,
 4;71,69,14,15;,
 4;72,68,69,73;,
 3;74,70,68;,
 3;74,75,70;,
 3;74,76,75;,
 3;74,72,76;,
 3;74,68,72;,
 3;77,73,69;,
 3;77,78,73;,
 3;77,79,78;,
 3;77,71,79;,
 3;77,69,71;,
 4;46,47,80,81;,
 4;82,80,47,50;,
 4;83,81,80,84;,
 4;48,46,81,85;,
 3;86,84,80;,
 3;86,87,84;,
 3;86,88,87;,
 3;86,82,88;,
 3;86,80,82;,
 4;83,89,85,81;,
 4;48,85,90,43;,
 4;91,90,85,89;,
 4;39,43,90,92;,
 4;91,93,92,90;,
 4;94,16,39,92;,
 4;9,16,94,95;,
 4;96,94,92,93;,
 4;96,97,95,94;,
 4;9,95,98,8;,
 4;99,98,95,97;,
 4;11,8,98,100;,
 4;99,101,100,98;,
 4;11,100,102,10;,
 4;103,102,100,101;,
 4;12,10,102,104;,
 3;105,104,102;,
 3;105,106,104;,
 3;105,107,106;,
 3;105,103,107;,
 3;105,102,103;,
 4;108,109,91,89;,
 4;110,109,108,111;,
 4;93,91,109,112;,
 4;113,108,89,83;,
 4;113,114,111,108;,
 4;110,115,112,109;,
 4;62,110,111,61;,
 4;115,110,62,67;,
 4;56,61,111,114;,
 4;67,30,116,115;,
 4;117,116,30,23;,
 4;112,115,116,118;,
 4;117,119,118,116;,
 4;93,112,118,96;,
 4;97,96,118,119;,
 4;99,97,119,120;,
 4;121,120,119,117;,
 4;101,99,120,122;,
 4;121,123,122,120;,
 4;24,121,117,23;,
 4;123,121,24,21;,
 4;76,124,125,87;,
 4;126,124,76,72;,
 4;127,125,124,128;,
 4;84,87,125,129;,
 4;75,76,87,88;,
 3;130,128,124;,
 3;130,131,128;,
 3;130,132,131;,
 3;130,126,132;,
 3;130,124,126;,
 3;133,129,125;,
 3;133,134,129;,
 3;133,135,134;,
 3;133,127,135;,
 3;133,125,127;,
 4;136,126,72,73;,
 4;132,126,136,137;,
 4;138,136,73,78;,
 3;139,137,136;,
 3;139,140,137;,
 3;139,141,140;,
 3;139,138,141;,
 3;139,136,138;,
 4;65,132,137,33;,
 4;131,132,65,66;,
 4;32,33,137,140;,
 4;78,107,142,138;,
 4;106,107,78,79;,
 4;143,142,107,103;,
 4;141,138,142,144;,
 3;145,144,142;,
 3;145,146,144;,
 3;145,147,146;,
 3;145,143,147;,
 3;145,142,143;,
 4;22,147,123,21;,
 4;146,147,22,29;,
 4;122,123,147,143;,
 4;122,143,103,101;,
 4;55,56,114,134;,
 4;129,134,114,113;,
 4;63,55,134,135;,
 4;84,129,113,83;,
 4;148,149,71,15;,
 4;150,149,148,151;,
 4;79,71,149,152;,
 4;153,148,15,4;,
 3;153,151,148;,
 3;150,152,149;,
 4;154,153,4,5;,
 4;151,153,154,155;,
 4;156,154,5,12;,
 3;156,155,154;,
 4;157,156,12,104;,
 4;155,156,157,158;,
 4;159,157,104,106;,
 3;159,158,157;,
 4;152,159,106,79;,
 4;158,159,152,150;,
 4;150,151,155,158;,
 4;160,161,42,70;,
 4;162,161,160,163;,
 4;41,42,161,164;,
 4;165,160,70,75;,
 3;165,163,160;,
 3;162,164,161;,
 4;166,165,75,88;,
 4;163,165,166,167;,
 4;168,166,88,82;,
 3;168,167,166;,
 4;169,168,82,50;,
 4;167,168,169,170;,
 4;171,169,50,49;,
 3;171,170,169;,
 4;164,171,49,41;,
 4;170,171,164,162;,
 4;162,163,167,170;,
 4;172,173,57,58;,
 4;174,173,172,175;,
 4;66,57,173,176;,
 4;177,172,58,63;,
 3;177,175,172;,
 3;174,176,173;,
 4;178,177,63,135;,
 4;175,177,178,179;,
 4;180,178,135,127;,
 3;180,179,178;,
 4;181,180,127,128;,
 4;179,180,181,182;,
 4;183,181,128,131;,
 3;183,182,181;,
 4;176,183,131,66;,
 4;182,183,176,174;,
 4;174,175,179,182;,
 4;184,185,32,140;,
 4;186,185,184,187;,
 4;28,32,185,188;,
 4;189,184,140,141;,
 3;189,187,184;,
 3;186,188,185;,
 4;190,189,141,144;,
 4;187,189,190,191;,
 4;192,190,144,146;,
 3;192,191,190;,
 4;193,192,146,29;,
 4;191,192,193,194;,
 4;195,193,29,27;,
 3;195,194,193;,
 4;188,195,27,28;,
 4;194,195,188,186;,
 4;186,187,191,194;,
 4;196,197,198,199;,
 4;200,196,199,201;,
 4;200,202,197,196;,
 4;203,204,205,206;,
 3;207,198,208;,
 3;209,208,210;,
 3;209,211,208;,
 3;212,208,211;,
 3;212,213,208;,
 3;214,208,213;,
 3;214,215,208;,
 3;216,208,215;,
 3;216,207,208;,
 3;217,198,207;,
 3;217,218,198;,
 3;219,198,218;,
 3;219,220,198;,
 3;221,198,220;,
 3;221,222,198;,
 3;223,198,222;,
 3;223,224,198;,
 3;225,208,201;,
 3;226,208,225;,
 3;226,227,208;,
 3;228,208,227;,
 3;228,229,208;,
 3;230,208,229;,
 3;230,231,208;,
 3;232,208,231;,
 3;232,210,208;,
 3;233,201,234;,
 3;233,235,201;,
 3;236,201,235;,
 3;236,225,201;,
 3;237,201,238;,
 3;237,234,201;,
 3;239,201,240;,
 3;239,238,201;,
 3;241,201,199;,
 3;242,201,243;,
 3;242,240,201;,
 3;244,201,245;,
 3;244,243,201;,
 3;246,201,247;,
 3;246,245,201;,
 3;248,201,241;,
 3;248,247,201;,
 3;249,199,250;,
 3;249,241,199;,
 3;251,199,252;,
 3;251,250,199;,
 3;253,199,254;,
 3;253,252,199;,
 3;255,199,256;,
 3;255,254,199;,
 3;257,198,224;,
 3;257,258,198;,
 3;259,198,258;,
 3;259,260,198;,
 3;261,198,260;,
 3;261,262,198;,
 3;263,198,262;,
 3;263,199,198;,
 3;263,264,199;,
 3;265,263,262;,
 3;265,264,263;,
 3;266,199,264;,
 3;266,267,199;,
 3;268,199,267;,
 3;268,269,199;,
 3;270,199,269;,
 3;270,271,199;,
 3;272,199,271;,
 3;272,256,199;,
 3;273,203,274;,
 3;275,203,273;,
 3;276,203,275;,
 3;277,278,206;,
 3;279,277,206;,
 3;280,279,206;,
 3;281,280,206;,
 3;282,281,206;,
 3;283,282,206;,
 3;284,283,206;,
 3;285,284,206;,
 3;286,203,276;,
 3;287,203,286;,
 3;288,203,287;,
 3;289,203,288;,
 3;290,203,289;,
 3;291,203,290;,
 3;292,203,291;,
 3;293,203,292;,
 3;294,203,293;,
 3;295,203,294;,
 3;296,203,295;,
 3;297,203,296;,
 3;298,203,297;,
 3;299,204,300;,
 3;301,204,299;,
 3;302,204,301;,
 3;303,204,302;,
 3;304,204,303;,
 3;305,204,304;,
 3;306,204,305;,
 3;307,204,306;,
 3;308,204,307;,
 3;309,204,308;,
 3;310,204,309;,
 3;311,204,310;,
 3;312,204,311;,
 3;313,204,312;,
 3;314,204,313;,
 3;315,204,314;,
 3;316,241,249;,
 3;317,316,249;,
 3;317,205,316;,
 3;317,249,250;,
 3;318,250,251;,
 3;318,317,250;,
 3;318,205,317;,
 3;319,318,251;,
 3;319,205,318;,
 3;319,251,252;,
 3;320,319,252;,
 3;320,205,319;,
 3;320,252,253;,
 3;321,253,254;,
 3;321,320,253;,
 3;321,205,320;,
 3;322,321,254;,
 3;322,205,321;,
 3;322,254,255;,
 3;323,322,255;,
 3;323,205,322;,
 3;323,255,256;,
 3;324,256,272;,
 3;324,323,256;,
 3;324,205,323;,
 3;325,272,271;,
 3;325,324,272;,
 3;325,205,324;,
 3;326,271,270;,
 3;326,325,271;,
 3;326,205,325;,
 3;327,326,270;,
 3;327,205,326;,
 3;327,270,269;,
 3;328,269,268;,
 3;328,327,269;,
 3;328,205,327;,
 3;329,328,268;,
 3;329,205,328;,
 3;330,205,329;,
 3;331,205,330;,
 3;332,205,331;,
 3;333,206,334;,
 3;335,206,333;,
 3;336,206,335;,
 3;337,206,336;,
 3;338,206,337;,
 3;339,206,338;,
 3;340,285,206;,
 3;340,206,339;,
 4;203,206,278,274;,
 4;334,206,205,332;,
 4;204,315,316,205;,
 4;300,204,203,298;,
 3;341,207,216;,
 3;341,273,274;,
 3;342,341,216;,
 3;342,273,341;,
 3;342,216,215;,
 3;343,274,278;,
 3;343,341,274;,
 3;343,207,341;,
 3;344,217,207;,
 3;344,343,278;,
 3;344,207,343;,
 3;345,278,277;,
 3;345,344,278;,
 3;345,217,344;,
 3;346,218,217;,
 3;346,277,279;,
 3;347,346,217;,
 3;347,277,346;,
 3;347,345,277;,
 3;347,217,345;,
 3;348,219,218;,
 3;348,346,279;,
 3;348,218,346;,
 3;349,279,280;,
 3;349,348,279;,
 3;349,219,348;,
 3;350,220,219;,
 3;350,349,280;,
 3;350,219,349;,
 3;351,280,281;,
 3;351,350,280;,
 3;351,220,350;,
 3;352,351,281;,
 3;352,220,351;,
 3;352,221,220;,
 3;353,281,282;,
 3;353,352,281;,
 3;353,221,352;,
 3;354,353,282;,
 3;354,221,353;,
 3;354,222,221;,
 3;355,354,282;,
 3;355,222,354;,
 3;355,282,283;,
 3;356,223,222;,
 3;356,355,283;,
 3;356,222,355;,
 3;357,283,284;,
 3;357,356,283;,
 3;357,223,356;,
 3;358,357,284;,
 3;358,223,357;,
 3;358,224,223;,
 3;359,358,284;,
 3;359,224,358;,
 3;359,284,285;,
 3;360,257,224;,
 3;360,359,285;,
 3;360,224,359;,
 3;361,340,339;,
 3;361,285,340;,
 3;362,360,285;,
 3;362,257,360;,
 3;362,361,257;,
 3;362,285,361;,
 3;363,361,339;,
 3;363,257,361;,
 3;363,258,257;,
 3;364,339,338;,
 3;364,259,258;,
 3;365,364,258;,
 3;365,339,364;,
 3;365,363,339;,
 3;365,258,363;,
 3;366,364,338;,
 3;366,259,364;,
 3;366,338,337;,
 3;367,260,259;,
 3;367,366,337;,
 3;367,259,366;,
 3;368,337,336;,
 3;368,367,337;,
 3;368,260,367;,
 3;369,368,336;,
 3;369,260,368;,
 3;369,261,260;,
 3;370,336,335;,
 3;370,369,336;,
 3;370,261,369;,
 3;371,262,261;,
 3;371,370,335;,
 3;371,261,370;,
 3;372,335,333;,
 3;372,371,335;,
 3;372,262,371;,
 3;373,372,333;,
 3;373,262,372;,
 3;373,265,262;,
 3;374,373,333;,
 3;374,265,373;,
 3;374,333,334;,
 3;375,264,265;,
 3;375,374,334;,
 3;375,265,374;,
 3;376,334,332;,
 3;376,375,334;,
 3;376,264,375;,
 3;377,376,332;,
 3;377,264,376;,
 3;377,332,331;,
 3;378,377,331;,
 3;378,264,377;,
 3;378,266,264;,
 3;379,331,330;,
 3;379,378,331;,
 3;379,266,378;,
 3;380,379,330;,
 3;380,266,379;,
 3;380,267,266;,
 3;381,380,330;,
 3;381,267,380;,
 3;381,330,329;,
 3;382,268,267;,
 3;382,329,268;,
 3;382,381,329;,
 3;382,267,381;,
 3;383,275,273;,
 3;383,342,215;,
 3;383,273,342;,
 3;384,383,215;,
 3;384,275,383;,
 3;384,215,214;,
 3;385,276,275;,
 3;385,384,214;,
 3;385,275,384;,
 3;386,385,214;,
 3;386,276,385;,
 3;386,214,213;,
 3;387,286,276;,
 3;387,386,213;,
 3;387,276,386;,
 3;388,213,212;,
 3;388,387,213;,
 3;388,286,387;,
 3;389,287,286;,
 3;389,388,212;,
 3;389,286,388;,
 3;390,389,212;,
 3;390,287,389;,
 3;390,212,211;,
 3;391,288,287;,
 3;391,390,211;,
 3;391,287,390;,
 3;392,211,209;,
 3;392,391,211;,
 3;392,288,391;,
 3;393,392,209;,
 3;393,288,392;,
 3;393,289,288;,
 3;394,209,210;,
 3;394,393,209;,
 3;394,289,393;,
 3;395,201,208;,
 3;395,202,200;,
 3;395,200,201;,
 3;395,197,202;,
 3;395,208,198;,
 3;395,198,197;,
 3;396,394,210;,
 3;396,289,394;,
 3;396,290,289;,
 3;397,210,232;,
 3;397,396,210;,
 3;397,290,396;,
 3;398,397,232;,
 3;398,290,397;,
 3;398,291,290;,
 3;399,398,232;,
 3;399,291,398;,
 3;399,232,231;,
 3;400,292,291;,
 3;400,399,231;,
 3;400,291,399;,
 3;401,231,230;,
 3;401,400,231;,
 3;401,292,400;,
 3;402,293,292;,
 3;402,401,230;,
 3;402,292,401;,
 3;403,230,229;,
 3;403,402,230;,
 3;403,293,402;,
 3;404,403,229;,
 3;404,293,403;,
 3;404,294,293;,
 3;405,229,228;,
 3;405,404,229;,
 3;405,294,404;,
 3;406,295,294;,
 3;406,405,228;,
 3;406,294,405;,
 3;407,228,227;,
 3;407,406,228;,
 3;407,295,406;,
 3;408,296,295;,
 3;408,407,227;,
 3;408,295,407;,
 3;409,227,226;,
 3;409,408,227;,
 3;409,296,408;,
 3;410,297,296;,
 3;410,409,226;,
 3;410,296,409;,
 3;411,410,226;,
 3;411,297,410;,
 3;411,226,225;,
 3;412,411,225;,
 3;412,297,411;,
 3;412,298,297;,
 3;413,300,298;,
 3;413,412,225;,
 3;413,298,412;,
 3;414,225,236;,
 3;414,413,225;,
 3;414,300,413;,
 3;415,299,300;,
 3;415,236,235;,
 3;416,414,236;,
 3;416,300,414;,
 3;416,415,300;,
 3;416,236,415;,
 3;417,301,299;,
 3;417,415,235;,
 3;417,299,415;,
 3;418,235,233;,
 3;418,417,235;,
 3;418,301,417;,
 3;419,418,233;,
 3;419,301,418;,
 3;419,302,301;,
 3;420,233,234;,
 3;420,419,233;,
 3;420,302,419;,
 3;421,303,302;,
 3;421,420,234;,
 3;421,302,420;,
 3;422,234,237;,
 3;422,421,234;,
 3;422,303,421;,
 3;423,304,303;,
 3;423,422,237;,
 3;423,303,422;,
 3;424,237,238;,
 3;424,423,237;,
 3;424,304,423;,
 3;425,305,304;,
 3;425,424,238;,
 3;425,304,424;,
 3;426,238,239;,
 3;426,425,238;,
 3;426,305,425;,
 3;427,306,305;,
 3;427,426,239;,
 3;427,305,426;,
 3;428,239,240;,
 3;428,427,239;,
 3;428,306,427;,
 3;429,428,240;,
 3;429,306,428;,
 3;429,307,306;,
 3;430,429,240;,
 3;430,307,429;,
 3;430,240,242;,
 3;431,308,307;,
 3;431,430,242;,
 3;431,307,430;,
 3;432,242,243;,
 3;432,431,242;,
 3;432,308,431;,
 3;433,309,308;,
 3;433,432,243;,
 3;433,308,432;,
 3;434,243,244;,
 3;434,433,243;,
 3;434,309,433;,
 3;435,310,309;,
 3;435,434,244;,
 3;435,309,434;,
 3;436,244,245;,
 3;436,435,244;,
 3;436,310,435;,
 3;437,311,310;,
 3;437,436,245;,
 3;437,310,436;,
 3;438,437,245;,
 3;438,311,437;,
 3;438,245,246;,
 3;439,312,311;,
 3;439,438,246;,
 3;439,311,438;,
 3;440,246,247;,
 3;440,439,246;,
 3;440,312,439;,
 3;441,313,312;,
 3;441,440,247;,
 3;441,312,440;,
 3;442,441,247;,
 3;442,313,441;,
 3;442,247,248;,
 3;443,314,313;,
 3;443,442,248;,
 3;443,313,442;,
 3;444,248,241;,
 3;444,443,248;,
 3;444,314,443;,
 3;445,315,314;,
 3;445,444,241;,
 3;445,314,444;,
 3;446,316,315;,
 3;446,241,316;,
 3;446,445,241;,
 3;446,315,445;;
 
 MeshMaterialList {
  2;
  724;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
   0.800000;0.715200;0.599200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.489600;0.351200;0.282400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
}
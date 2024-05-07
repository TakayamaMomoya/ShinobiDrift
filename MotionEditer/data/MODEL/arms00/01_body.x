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
 409;
 16.58650;16.31862;90.91300;,
 8.74790;54.32827;64.30468;,
 0.36880;56.02780;67.73594;,
 0.36880;19.30024;96.93264;,
 -8.01026;54.32827;64.30468;,
 -15.84884;16.31862;90.91300;,
 -11.83938;50.22526;56.02089;,
 -22.56646;9.12052;76.38030;,
 -8.01026;46.12228;47.73713;,
 -15.84884;1.92242;61.84755;,
 0.36880;44.42277;44.30588;,
 0.36880;-1.05915;55.82789;,
 8.74790;46.12228;47.73713;,
 16.58650;1.92242;61.84755;,
 12.57698;50.22526;56.02089;,
 23.30406;9.12052;76.38030;,
 0.36880;19.30024;96.93264;,
 0.36880;9.12052;76.38030;,
 16.58650;16.31862;90.91300;,
 -15.84884;16.31862;90.91300;,
 -22.56646;9.12052;76.38030;,
 -15.84884;1.92242;61.84755;,
 0.36880;-1.05915;55.82789;,
 16.58650;1.92242;61.84755;,
 23.30406;9.12052;76.38030;,
 8.74790;54.32827;64.30468;,
 0.36880;50.22526;56.02089;,
 0.36880;56.02780;67.73594;,
 -8.01026;54.32827;64.30468;,
 -11.83938;50.22526;56.02089;,
 -8.01026;46.12228;47.73713;,
 0.36880;44.42277;44.30588;,
 8.74790;46.12228;47.73713;,
 12.57698;50.22526;56.02089;,
 50.47507;25.45078;85.49014;,
 44.35657;55.11967;64.72070;,
 37.81619;56.44619;67.39901;,
 37.81619;27.77810;90.18885;,
 31.27578;55.11967;64.72070;,
 25.15728;25.45078;85.49014;,
 28.28698;51.91700;58.25469;,
 19.91382;19.83220;74.14646;,
 31.27578;48.71438;51.78871;,
 25.15728;14.21361;62.80278;,
 37.81619;47.38778;49.11041;,
 37.81619;11.88630;58.10405;,
 44.35657;48.71438;51.78871;,
 50.47507;14.21361;62.80278;,
 47.34540;51.91700;58.25469;,
 55.71860;19.83220;74.14646;,
 37.81619;27.77810;90.18885;,
 37.81619;19.83220;74.14646;,
 50.47507;25.45078;85.49014;,
 25.15728;25.45078;85.49014;,
 19.91382;19.83220;74.14646;,
 25.15728;14.21361;62.80278;,
 37.81619;11.88630;58.10405;,
 50.47507;14.21361;62.80278;,
 55.71860;19.83220;74.14646;,
 44.35657;55.11967;64.72070;,
 37.81619;51.91700;58.25469;,
 37.81619;56.44619;67.39901;,
 31.27578;55.11967;64.72070;,
 28.28698;51.91700;58.25469;,
 31.27578;48.71438;51.78871;,
 37.81619;47.38778;49.11041;,
 44.35657;48.71438;51.78871;,
 47.34540;51.91700;58.25469;,
 -14.95128;25.33096;-61.53047;,
 -14.95128;81.27263;-85.86304;,
 19.06270;81.27263;-85.86304;,
 19.06270;25.33096;-61.53047;,
 -19.89834;102.76166;-69.90081;,
 -19.89834;117.00413;-27.29025;,
 24.00977;117.00413;-27.29025;,
 24.00977;102.76166;-69.90081;,
 -19.89834;114.43406;-23.31254;,
 -19.89834;18.10689;-15.72554;,
 24.00977;18.10689;-15.72554;,
 24.00977;114.43406;-23.31254;,
 -19.89834;18.10689;-15.72554;,
 -19.89834;22.66942;-46.89714;,
 24.00977;22.66942;-46.89714;,
 24.00977;18.10689;-15.72554;,
 24.00977;18.10689;-15.72554;,
 24.00977;22.66942;-46.89714;,
 24.00977;114.43406;-23.31254;,
 24.00977;117.00413;-27.29025;,
 24.00977;102.76166;-69.90081;,
 24.00977;94.88366;-78.30776;,
 -19.89834;94.88366;-78.30776;,
 -19.89834;22.66942;-46.89714;,
 -19.89834;102.76166;-69.90081;,
 -19.89834;117.00413;-27.29025;,
 -19.89834;18.10689;-15.72554;,
 -19.89834;114.43406;-23.31254;,
 24.00977;94.88366;-78.30776;,
 -19.89834;94.88366;-78.30776;,
 24.00977;117.00413;-27.29025;,
 -19.89834;117.00413;-27.29025;,
 -19.89834;22.66942;-46.89714;,
 -18.21077;24.68247;-48.84580;,
 22.32212;24.68247;-48.84580;,
 24.00977;22.66942;-46.89714;,
 22.32212;91.34544;-77.84185;,
 24.00977;94.88366;-78.30776;,
 -18.21077;91.34544;-77.84185;,
 -19.89834;94.88366;-78.30776;,
 -18.21077;24.68247;-48.84580;,
 22.32212;24.68247;-48.84580;,
 22.32212;91.34544;-77.84185;,
 -18.21077;91.34544;-77.84185;,
 -64.00521;37.36920;38.04499;,
 -64.00521;114.98932;38.04499;,
 64.74282;114.98932;38.04499;,
 64.74282;37.36920;38.04499;,
 -64.00521;114.98932;38.04499;,
 -64.00521;114.36719;63.94205;,
 64.74282;114.36719;63.94205;,
 64.74282;114.98932;38.04499;,
 -64.00521;87.23073;86.48563;,
 -64.00521;37.36920;92.13916;,
 64.74282;37.36920;92.13916;,
 64.74282;87.23073;86.48563;,
 -64.00521;37.36920;92.13916;,
 -64.00521;37.36920;38.04499;,
 64.74282;37.36920;38.04499;,
 64.74282;37.36920;92.13916;,
 64.74282;37.36920;92.13916;,
 64.74282;37.36920;38.04499;,
 64.74282;87.23073;86.48563;,
 64.74282;114.36719;63.94205;,
 64.74282;114.98932;38.04499;,
 -64.00521;37.36920;38.04499;,
 -64.00521;37.36920;92.13916;,
 -64.00521;114.98932;38.04499;,
 -64.00521;114.36719;63.94205;,
 -64.00521;87.23073;86.48563;,
 -64.00521;87.23073;86.48563;,
 64.74282;87.23073;86.48563;,
 38.26202;117.43439;-22.73942;,
 38.26202;102.42726;-40.43446;,
 1.43356;102.42726;-40.43446;,
 1.43356;117.43439;-22.73942;,
 1.43356;71.46340;39.31876;,
 38.26202;71.46340;39.31876;,
 38.26202;114.04938;39.31876;,
 1.43356;114.04938;39.31876;,
 1.43356;43.81748;39.31876;,
 38.26202;41.42688;39.31876;,
 -35.39487;41.42688;39.31876;,
 -35.39487;71.46340;39.31876;,
 -35.39487;114.04938;39.31876;,
 -35.39487;102.42726;-40.43446;,
 -35.39487;117.43439;-22.73942;,
 -70.50328;70.62988;-62.29288;,
 -69.77054;69.45031;-62.45125;,
 -72.22332;70.29114;-60.47754;,
 -60.86254;47.77618;-50.86592;,
 -63.21526;49.21516;-49.18095;,
 -61.57090;47.41016;-49.98746;,
 -69.76617;71.80706;-62.13800;,
 -69.76617;102.42726;-40.43446;,
 -72.22332;99.97067;-39.62430;,
 63.70009;45.31478;39.31876;,
 63.73304;46.62068;-49.24345;,
 66.08239;48.07930;37.25013;,
 66.08239;48.94622;-28.71898;,
 66.08239;49.21516;-49.18095;,
 64.43806;47.41016;-49.98746;,
 -72.22332;114.97731;-22.60922;,
 -69.76617;117.43439;-22.73942;,
 -72.22332;111.59076;37.25671;,
 -72.22332;71.48612;37.25676;,
 -69.76612;71.46340;39.31876;,
 -69.76617;114.04938;39.31876;,
 72.63332;102.42726;-40.43446;,
 72.63332;117.43439;-22.73942;,
 75.09044;114.97731;-22.60922;,
 75.09044;99.97067;-39.62430;,
 72.63332;114.04938;39.31876;,
 72.63326;71.46340;39.31876;,
 75.09044;71.48612;37.25676;,
 75.09044;111.59076;37.25671;,
 -63.21526;48.07930;37.25013;,
 -60.83294;45.31478;39.31876;,
 75.09044;70.29114;-60.47754;,
 75.09044;71.98184;-22.17675;,
 -72.22332;71.98184;-22.17675;,
 -63.21526;48.94622;-28.71898;,
 -69.76612;71.46340;39.31876;,
 -60.83294;45.31478;39.31876;,
 -35.39487;41.42688;39.31876;,
 -35.39487;71.46340;39.31876;,
 -69.76617;114.04938;39.31876;,
 -35.39487;114.04938;39.31876;,
 -69.76617;102.42726;-40.43446;,
 -69.76617;117.43439;-22.73942;,
 38.26202;41.42688;39.31876;,
 63.70009;45.31478;39.31876;,
 72.63326;71.46340;39.31876;,
 38.26202;71.46340;39.31876;,
 72.63332;117.43439;-22.73942;,
 72.63332;102.42726;-40.43446;,
 72.63332;114.04938;39.31876;,
 38.26202;114.04938;39.31876;,
 72.63332;71.80706;-62.13800;,
 73.37038;70.62988;-62.29288;,
 1.43356;69.44642;-62.47656;,
 -35.39487;69.44130;-62.51324;,
 -35.39487;71.78890;-62.15438;,
 1.43356;71.79951;-62.14479;,
 38.26202;71.78890;-62.15438;,
 38.26202;69.44130;-62.51324;,
 72.63332;71.80706;-62.13800;,
 72.63768;69.45031;-62.45125;,
 -69.77054;69.45031;-62.45125;,
 -69.76617;71.80706;-62.13800;,
 -69.76617;71.80706;-62.13800;,
 -69.77054;69.45031;-62.45125;,
 -70.50328;70.62988;-62.29288;,
 72.63768;69.45031;-62.45125;,
 72.63332;71.80706;-62.13800;,
 73.37038;70.62988;-62.29288;,
 -60.86590;46.62068;-49.24345;,
 63.72968;47.77618;-50.86592;,
 72.63768;69.45031;-62.45125;,
 1.43356;45.11948;-49.23690;,
 -35.39487;42.72876;-49.22798;,
 -35.36729;43.92725;-50.82720;,
 1.43356;46.29041;-50.84940;,
 38.23438;43.92716;-50.82720;,
 38.26202;42.72876;-49.22800;,
 63.72968;47.77618;-50.86592;,
 63.73304;46.62068;-49.24345;,
 -60.86590;46.62068;-49.24345;,
 -60.86254;47.77618;-50.86592;,
 38.26202;41.42688;39.31876;,
 1.43356;43.81748;39.31876;,
 -35.39487;41.42688;39.31876;,
 -60.83294;45.31478;39.31876;,
 63.70009;45.31478;39.31876;,
 38.23438;43.92716;-50.82720;,
 1.43356;46.29041;-50.84940;,
 -35.36729;43.92725;-50.82720;,
 -60.86254;47.77618;-50.86592;,
 63.72968;47.77618;-50.86592;,
 -60.86254;47.77618;-50.86592;,
 -60.86590;46.62068;-49.24345;,
 -61.57090;47.41016;-49.98746;,
 63.72968;47.77618;-50.86592;,
 64.43806;47.41016;-49.98746;,
 63.73304;46.62068;-49.24345;,
 38.26202;114.04938;39.31876;,
 72.63332;114.04938;39.31876;,
 72.63332;117.43439;-22.73942;,
 38.26202;117.43439;-22.73942;,
 1.43356;114.04938;39.31876;,
 1.43356;117.43439;-22.73942;,
 -35.39487;114.04938;39.31876;,
 -35.39487;117.43439;-22.73942;,
 -69.76617;117.43439;-22.73942;,
 -69.76617;114.04938;39.31876;,
 -25.17444;25.45078;85.49014;,
 -31.29296;55.11967;64.72070;,
 -37.83333;56.44619;67.39901;,
 -37.83333;27.77810;90.18885;,
 -44.37374;55.11967;64.72070;,
 -50.49224;25.45078;85.49014;,
 -47.36257;51.91700;58.25469;,
 -55.73575;19.83220;74.14646;,
 -44.37374;48.71438;51.78871;,
 -50.49224;14.21361;62.80278;,
 -37.83333;47.38778;49.11041;,
 -37.83333;11.88630;58.10405;,
 -31.29296;48.71438;51.78871;,
 -25.17444;14.21361;62.80278;,
 -28.30410;51.91700;58.25469;,
 -19.93092;19.83220;74.14646;,
 -37.83333;27.77810;90.18885;,
 -37.83333;19.83220;74.14646;,
 -25.17444;25.45078;85.49014;,
 -50.49224;25.45078;85.49014;,
 -55.73575;19.83220;74.14646;,
 -50.49224;14.21361;62.80278;,
 -37.83333;11.88630;58.10405;,
 -25.17444;14.21361;62.80278;,
 -19.93092;19.83220;74.14646;,
 -31.29296;55.11967;64.72070;,
 -37.83333;51.91700;58.25469;,
 -37.83333;56.44619;67.39901;,
 -44.37374;55.11967;64.72070;,
 -47.36257;51.91700;58.25469;,
 -44.37374;48.71438;51.78871;,
 -37.83333;47.38778;49.11041;,
 -31.29296;48.71438;51.78871;,
 -28.30410;51.91700;58.25469;,
 -81.94897;164.98819;61.17324;,
 -81.94897;206.97534;70.66345;,
 -64.64932;206.97534;70.66345;,
 -64.64932;164.98819;61.17324;,
 -81.94897;206.97534;70.66345;,
 -81.94897;209.54409;99.41310;,
 -64.64932;209.54409;99.41310;,
 -64.64932;206.97534;70.66345;,
 -80.50136;193.91961;112.08692;,
 -80.50136;158.95912;104.18491;,
 -66.09697;158.95912;104.18491;,
 -66.09697;193.91961;112.08692;,
 -81.94897;76.86738;69.55615;,
 -81.94897;82.95310;42.63116;,
 -64.64932;82.95310;42.63116;,
 -64.64932;76.86738;69.55615;,
 -64.64932;164.98819;61.17324;,
 -64.64932;206.97534;70.66345;,
 -64.64932;209.54409;99.41310;,
 -64.64932;158.90232;88.09822;,
 -81.94897;158.90232;88.09822;,
 -81.94897;209.54409;99.41310;,
 -81.94897;206.97534;70.66345;,
 -81.94897;164.98819;61.17324;,
 -81.94897;82.95310;42.63116;,
 -64.64932;82.95310;42.63116;,
 -64.64932;82.95310;42.63116;,
 -64.64932;76.86738;69.55615;,
 -81.94897;158.90232;88.09822;,
 -81.94897;76.86738;69.55615;,
 -64.64932;76.86738;69.55615;,
 -64.64932;158.90232;88.09822;,
 -81.94897;76.86738;69.55615;,
 -81.94897;82.95310;42.63116;,
 -80.50136;193.91961;112.08692;,
 -66.09697;193.91961;112.08692;,
 -66.09697;193.91961;112.08692;,
 -66.09697;158.95912;104.18491;,
 -64.64932;158.90232;88.09822;,
 -66.09697;158.95912;104.18491;,
 -80.50136;158.95912;104.18491;,
 -81.94897;158.90232;88.09822;,
 -80.50136;158.95912;104.18491;,
 -80.50136;193.91961;112.08692;,
 -46.33427;2.67689;-32.42966;,
 -54.68598;48.34446;-38.54054;,
 57.74362;48.34446;-38.54054;,
 49.39194;2.67689;-32.42966;,
 -54.68598;48.34446;-38.54054;,
 -54.68598;48.34446;37.17302;,
 57.74362;48.34446;37.17302;,
 57.74362;48.34446;-38.54054;,
 -54.68598;48.34446;37.17302;,
 -46.33427;2.67689;31.06213;,
 49.39194;2.67689;31.06213;,
 57.74362;48.34446;37.17302;,
 -46.33427;2.67689;31.06213;,
 -46.33427;2.67689;-32.42966;,
 49.39194;2.67689;-32.42966;,
 49.39194;2.67689;31.06213;,
 49.39194;2.67689;-32.42966;,
 57.74362;48.34446;-38.54054;,
 57.74362;48.34446;37.17302;,
 49.39194;2.67689;31.06213;,
 -46.33427;2.67689;31.06213;,
 -54.68598;48.34446;37.17302;,
 -54.68598;48.34446;-38.54054;,
 -46.33427;2.67689;-32.42966;,
 64.64932;164.98819;61.17324;,
 64.64932;206.97534;70.66345;,
 81.94898;206.97534;70.66345;,
 81.94898;164.98819;61.17324;,
 64.64932;206.97534;70.66345;,
 64.64932;209.54409;99.41310;,
 81.94898;209.54409;99.41310;,
 81.94898;206.97534;70.66345;,
 66.09692;193.91961;112.08692;,
 66.09692;158.95912;104.18491;,
 80.50137;158.95912;104.18491;,
 80.50137;193.91961;112.08692;,
 64.64932;76.86738;69.55615;,
 64.64932;82.95310;42.63116;,
 81.94898;82.95310;42.63116;,
 81.94898;76.86738;69.55615;,
 81.94898;164.98819;61.17324;,
 81.94898;206.97534;70.66345;,
 81.94898;209.54409;99.41310;,
 81.94898;158.90232;88.09822;,
 64.64932;158.90232;88.09822;,
 64.64932;209.54409;99.41310;,
 64.64932;206.97534;70.66345;,
 64.64932;164.98819;61.17324;,
 64.64932;82.95310;42.63116;,
 81.94898;82.95310;42.63116;,
 81.94898;82.95310;42.63116;,
 81.94898;76.86738;69.55615;,
 64.64932;158.90232;88.09822;,
 64.64932;76.86738;69.55615;,
 81.94898;76.86738;69.55615;,
 81.94898;158.90232;88.09822;,
 64.64932;76.86738;69.55615;,
 64.64932;82.95310;42.63116;,
 66.09692;193.91961;112.08692;,
 80.50137;193.91961;112.08692;,
 80.50137;193.91961;112.08692;,
 80.50137;158.95912;104.18491;,
 81.94898;158.90232;88.09822;,
 80.50137;158.95912;104.18491;,
 66.09692;158.95912;104.18491;,
 64.64932;158.90232;88.09822;,
 66.09692;158.95912;104.18491;,
 66.09692;193.91961;112.08692;;
 
 217;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,1,0;,
 3;16,17,18;,
 3;19,17,16;,
 3;20,17,19;,
 3;21,17,20;,
 3;22,17,21;,
 3;23,17,22;,
 3;24,17,23;,
 3;18,17,24;,
 3;25,26,27;,
 3;27,26,28;,
 3;28,26,29;,
 3;29,26,30;,
 3;30,26,31;,
 3;31,26,32;,
 3;32,26,33;,
 3;33,26,25;,
 4;34,35,36,37;,
 4;37,36,38,39;,
 4;39,38,40,41;,
 4;41,40,42,43;,
 4;43,42,44,45;,
 4;45,44,46,47;,
 4;47,46,48,49;,
 4;49,48,35,34;,
 3;50,51,52;,
 3;53,51,50;,
 3;54,51,53;,
 3;55,51,54;,
 3;56,51,55;,
 3;57,51,56;,
 3;58,51,57;,
 3;52,51,58;,
 3;59,60,61;,
 3;61,60,62;,
 3;62,60,63;,
 3;63,60,64;,
 3;64,60,65;,
 3;65,60,66;,
 3;66,60,67;,
 3;67,60,59;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;80,81,82,83;,
 3;84,85,86;,
 3;86,85,87;,
 3;87,85,88;,
 3;88,85,89;,
 3;90,91,92;,
 3;92,91,93;,
 3;91,94,93;,
 3;93,94,95;,
 4;72,75,96,97;,
 4;76,79,98,99;,
 4;100,101,102,103;,
 4;103,102,104,105;,
 4;105,104,106,107;,
 4;107,106,101,100;,
 4;108,68,71,109;,
 4;109,71,70,110;,
 4;110,70,69,111;,
 4;111,69,68,108;,
 4;112,113,114,115;,
 4;116,117,118,119;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 3;128,129,130;,
 3;130,129,131;,
 3;131,129,132;,
 3;133,134,135;,
 3;135,134,136;,
 3;136,134,137;,
 4;138,139,118,117;,
 4;140,141,142,143;,
 4;144,145,146,147;,
 4;148,149,145,144;,
 4;150,148,144,151;,
 4;151,144,147,152;,
 4;143,142,153,154;,
 3;155,156,157;,
 3;156,158,157;,
 3;157,158,159;,
 3;159,158,160;,
 3;155,157,161;,
 3;161,157,162;,
 3;162,157,163;,
 3;164,165,166;,
 3;166,165,167;,
 3;167,165,168;,
 3;168,165,169;,
 4;163,170,171,162;,
 4;172,173,174,175;,
 4;176,177,178,179;,
 4;180,181,182,183;,
 4;173,184,185,174;,
 4;181,164,166,182;,
 4;186,179,178,187;,
 4;170,163,157,188;,
 4;168,186,187,167;,
 4;188,157,159,189;,
 4;190,191,192,193;,
 4;194,190,193,195;,
 4;196,197,154,153;,
 4;198,199,200,201;,
 4;202,203,141,140;,
 4;201,200,204,205;,
 3;176,179,206;,
 3;179,186,206;,
 3;206,186,207;,
 4;208,209,210,211;,
 4;211,212,213,208;,
 4;212,214,215,213;,
 4;209,216,217,210;,
 4;142,141,212,211;,
 4;153,142,211,210;,
 4;217,196,153,210;,
 4;141,203,214,212;,
 3;218,219,220;,
 3;221,222,223;,
 3;159,160,189;,
 3;160,224,189;,
 3;224,185,189;,
 3;189,185,184;,
 3;169,225,168;,
 3;168,225,186;,
 3;225,226,186;,
 3;186,226,207;,
 4;227,228,229,230;,
 4;230,231,232,227;,
 4;231,233,234,232;,
 4;228,235,236,229;,
 4;227,232,237,238;,
 4;228,227,238,239;,
 4;240,235,228,239;,
 4;232,234,241,237;,
 4;208,213,242,243;,
 4;209,208,243,244;,
 4;245,216,209,244;,
 4;213,215,246,242;,
 3;247,248,249;,
 3;250,251,252;,
 4;187,182,166,167;,
 4;178,183,182,187;,
 4;177,180,183,178;,
 4;253,254,255,256;,
 4;257,253,256,258;,
 4;259,257,258,260;,
 4;261,262,259,260;,
 4;170,172,175,171;,
 4;173,172,170,188;,
 4;184,173,188,189;,
 4;263,264,265,266;,
 4;266,265,267,268;,
 4;268,267,269,270;,
 4;270,269,271,272;,
 4;272,271,273,274;,
 4;274,273,275,276;,
 4;276,275,277,278;,
 4;278,277,264,263;,
 3;279,280,281;,
 3;282,280,279;,
 3;283,280,282;,
 3;284,280,283;,
 3;285,280,284;,
 3;286,280,285;,
 3;287,280,286;,
 3;281,280,287;,
 3;288,289,290;,
 3;290,289,291;,
 3;291,289,292;,
 3;292,289,293;,
 3;293,289,294;,
 3;294,289,295;,
 3;295,289,296;,
 3;296,289,288;,
 4;297,298,299,300;,
 4;301,302,303,304;,
 4;305,306,307,308;,
 4;309,310,311,312;,
 4;313,314,315,316;,
 4;317,318,319,320;,
 4;321,297,300,322;,
 4;323,313,316,324;,
 4;325,326,327,328;,
 4;329,317,320,330;,
 4;302,331,332,303;,
 4;315,333,334,316;,
 4;335,336,337,338;,
 4;317,339,340,318;,
 4;341,342,343,344;,
 4;345,346,347,348;,
 4;349,350,351,352;,
 4;353,354,355,356;,
 4;357,358,359,360;,
 4;361,362,363,364;,
 4;365,366,367,368;,
 4;369,370,371,372;,
 4;373,374,375,376;,
 4;377,378,379,380;,
 4;381,382,383,384;,
 4;385,386,387,388;,
 4;389,365,368,390;,
 4;391,381,384,392;,
 4;393,394,395,396;,
 4;397,385,388,398;,
 4;370,399,400,371;,
 4;383,401,402,384;,
 4;403,404,405,406;,
 4;385,407,408,386;;
 
 MeshMaterialList {
  1;
  217;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "arms_00.png";
   }
  }
 }
 MeshNormals {
  204;
  0.695658;0.500104;0.515710;,
  -0.000001;0.625219;0.780449;,
  -0.695657;0.500104;0.515711;,
  -0.973728;0.204054;-0.101069;,
  -0.695656;-0.107163;-0.710337;,
  -0.000001;-0.241932;-0.970293;,
  0.695657;-0.107162;-0.710336;,
  0.973729;0.204054;-0.101069;,
  0.000000;-0.896104;0.443844;,
  -0.000000;0.896104;-0.443845;,
  0.695657;0.500105;0.515710;,
  0.000001;0.625219;0.780449;,
  -0.695658;0.500104;0.515709;,
  -0.973729;0.204053;-0.101069;,
  -0.695658;-0.107162;-0.710336;,
  0.000001;-0.241931;-0.970293;,
  0.695657;-0.107162;-0.710336;,
  0.973728;0.204054;-0.101070;,
  -0.000000;-0.896104;0.443845;,
  -0.000000;0.896104;-0.443844;,
  -0.188864;-0.760953;-0.620710;,
  0.188856;-0.760953;-0.620712;,
  0.000000;0.078520;0.996913;,
  0.000000;0.858863;-0.512206;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;-0.000000;,
  0.000000;0.992131;0.125205;,
  0.000000;0.512315;0.858798;,
  -0.192470;-0.779014;-0.596735;,
  0.192463;-0.779014;-0.596737;,
  0.568754;-0.227116;-0.790530;,
  -0.192330;0.056441;-0.979706;,
  0.000000;-0.398865;-0.917009;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.112663;0.993633;,
  0.000000;0.392232;0.919866;,
  0.000000;0.900098;0.435688;,
  0.000000;0.000000;1.000000;,
  0.000000;0.675788;-0.737096;,
  -0.000005;0.675786;-0.737098;,
  0.000005;0.675786;-0.737098;,
  -0.804568;-0.507766;-0.307966;,
  -0.859048;-0.062814;-0.508027;,
  0.799288;-0.547522;-0.247706;,
  0.868729;-0.144499;-0.473741;,
  -0.424042;0.595349;-0.682457;,
  -0.837572;0.366060;-0.405554;,
  -0.906318;0.000000;0.422596;,
  -0.342043;0.000000;0.939684;,
  0.799245;0.385123;-0.461398;,
  0.350836;0.631158;-0.691776;,
  0.911127;0.270249;0.311148;,
  0.342046;0.000000;0.939683;,
  -0.905340;-0.170289;0.389053;,
  -0.368063;-0.069883;0.927171;,
  0.905340;-0.170289;0.389050;,
  0.368066;-0.069883;0.927170;,
  -0.392759;-0.141732;0.908654;,
  -0.859722;-0.456664;0.228772;,
  0.837998;-0.519222;0.167832;,
  0.628471;-0.738716;0.243563;,
  -0.000000;-0.150184;-0.988658;,
  0.000000;0.372099;-0.928193;,
  0.000129;0.371176;-0.928562;,
  0.004837;-0.154375;-0.988000;,
  -0.004837;-0.154375;-0.988000;,
  -0.000129;0.371176;-0.928562;,
  -0.297847;0.391292;-0.870734;,
  -0.511586;0.118493;-0.851023;,
  -0.297993;-0.234242;-0.925382;,
  0.189389;-0.133422;-0.972795;,
  0.511585;0.118491;-0.851024;,
  0.365812;0.405444;-0.837733;,
  -0.000000;-0.947622;-0.319394;,
  -0.000001;-0.637566;-0.770396;,
  0.041047;-0.947001;-0.318596;,
  0.022545;-0.640303;-0.767791;,
  -0.041047;-0.946999;-0.318603;,
  -0.022545;-0.640298;-0.767796;,
  -0.430426;-0.610959;-0.664427;,
  -0.666031;-0.664019;-0.339825;,
  -0.447990;-0.856141;-0.257541;,
  0.430426;-0.610958;-0.664427;,
  0.549762;-0.814453;-0.185550;,
  0.619486;-0.642528;-0.450994;,
  0.849319;-0.527865;-0.003914;,
  0.982336;-0.187125;0.000569;,
  0.928854;0.348896;-0.124509;,
  0.394197;0.868796;-0.299671;,
  0.000000;0.947827;-0.318786;,
  -0.394194;0.868797;-0.299671;,
  -0.928853;0.348898;-0.124510;,
  -0.982336;-0.187125;0.000569;,
  -0.818239;-0.574849;-0.005693;,
  0.695656;0.500105;0.515711;,
  0.000001;0.625219;0.780449;,
  -0.695656;0.500105;0.515711;,
  -0.973728;0.204054;-0.101070;,
  -0.695657;-0.107162;-0.710337;,
  0.000001;-0.241931;-0.970293;,
  0.695656;-0.107163;-0.710337;,
  0.973728;0.204054;-0.101070;,
  -0.000000;-0.896104;0.443845;,
  -0.000000;0.896104;-0.443844;,
  0.000000;-0.975395;-0.220464;,
  0.000000;0.220465;-0.975395;,
  0.000000;0.921026;0.389502;,
  0.000000;0.220465;-0.975395;,
  0.999533;-0.006697;0.029801;,
  -0.999532;-0.006705;0.029837;,
  0.000000;0.227594;0.973756;,
  0.000000;-0.220465;0.975395;,
  0.000000;-0.132630;-0.991166;,
  0.000000;1.000000;0.000000;,
  0.000000;-0.132630;0.991166;,
  0.000000;-0.975395;-0.220464;,
  0.000000;0.220465;-0.975395;,
  0.000000;0.921026;0.389502;,
  0.999532;-0.006705;0.029838;,
  -0.999533;-0.006697;0.029800;,
  0.000000;-0.220465;0.975395;,
  0.000000;-0.896103;0.443846;,
  -0.000001;-0.896104;0.443845;,
  0.000001;-0.896104;0.443845;,
  0.000000;-0.896105;0.443843;,
  -0.000000;-0.896105;0.443843;,
  -0.000000;-0.896104;0.443843;,
  0.000000;-0.896105;0.443843;,
  0.000000;-0.896105;0.443843;,
  0.000000;0.896103;-0.443846;,
  -0.000000;0.896103;-0.443846;,
  -0.000000;0.896103;-0.443846;,
  0.000000;0.896104;-0.443845;,
  -0.000000;0.896104;-0.443844;,
  -0.000000;0.896104;-0.443844;,
  0.000000;0.896104;-0.443844;,
  -0.000000;-0.896103;0.443846;,
  -0.000001;-0.896104;0.443845;,
  0.000001;-0.896104;0.443845;,
  0.000000;-0.896104;0.443845;,
  -0.000000;-0.896103;0.443845;,
  0.000000;-0.896103;0.443845;,
  0.000000;-0.896104;0.443845;,
  0.000000;-0.896104;0.443845;,
  -0.000003;0.896104;-0.443844;,
  -0.000000;0.896105;-0.443842;,
  0.000003;0.896104;-0.443844;,
  0.000000;0.896104;-0.443845;,
  0.000001;0.896104;-0.443844;,
  -0.000000;0.896103;-0.443846;,
  -0.000001;0.896104;-0.443844;,
  0.000000;0.896104;-0.443845;,
  0.000000;-0.989457;-0.144825;,
  0.000000;0.336758;-0.941591;,
  -0.199011;0.100576;-0.974823;,
  0.503702;-0.344572;-0.792183;,
  0.000000;-0.998696;-0.051057;,
  0.961302;-0.109886;-0.252633;,
  0.000000;0.622938;-0.782271;,
  -0.961301;-0.109888;-0.252638;,
  0.000000;0.999712;0.024016;,
  0.000000;-1.000000;-0.000000;,
  -0.580729;-0.814015;-0.011518;,
  0.629532;-0.551357;-0.547444;,
  0.043392;-0.998950;-0.014684;,
  0.000000;-0.999892;-0.014701;,
  -0.043392;-0.998950;-0.014684;,
  0.387209;0.920602;0.050603;,
  0.000000;0.998516;0.054465;,
  0.000000;0.998516;0.054465;,
  0.000000;0.998516;0.054465;,
  -0.387206;0.920604;0.050603;,
  -0.714002;0.699065;0.038847;,
  -0.000000;-0.896103;0.443846;,
  -0.000001;-0.896104;0.443845;,
  0.000001;-0.896104;0.443845;,
  0.000000;-0.896104;0.443845;,
  -0.000000;-0.896104;0.443845;,
  0.000000;-0.896104;0.443845;,
  0.000000;-0.896104;0.443845;,
  0.000000;-0.896104;0.443845;,
  -0.000003;0.896104;-0.443844;,
  -0.000000;0.896105;-0.443842;,
  0.000001;0.896104;-0.443844;,
  -0.000000;0.896103;-0.443846;,
  -0.000001;0.896104;-0.443844;,
  0.000000;0.996032;-0.088994;,
  0.998950;-0.010047;0.044707;,
  -0.998947;-0.010059;0.044761;,
  0.000000;0.220465;-0.975395;,
  0.000000;-0.220465;0.975395;,
  0.995801;-0.020072;0.089320;,
  0.000000;-0.999994;0.003531;,
  -0.995791;-0.020097;0.089428;,
  0.983686;-0.179896;-0.000000;,
  -0.983685;-0.179897;0.000000;,
  0.000000;0.996032;-0.088994;,
  0.998947;-0.010059;0.044762;,
  -0.998950;-0.010046;0.044705;,
  0.000000;0.220465;-0.975395;,
  0.000000;-0.220465;0.975395;,
  0.995790;-0.020097;0.089429;,
  0.000000;-0.999994;0.003531;,
  -0.995801;-0.020071;0.089317;;
  217;
  4;0,0,1,1;,
  4;1,1,2,2;,
  4;2,2,3,3;,
  4;3,3,4,4;,
  4;4,4,5,5;,
  4;5,5,6,6;,
  4;6,6,7,7;,
  4;7,7,0,0;,
  3;121,8,122;,
  3;123,8,121;,
  3;124,8,123;,
  3;125,8,124;,
  3;126,8,125;,
  3;127,8,126;,
  3;128,8,127;,
  3;122,8,128;,
  3;129,9,130;,
  3;130,9,131;,
  3;131,9,132;,
  3;132,9,133;,
  3;133,9,134;,
  3;134,9,135;,
  3;135,9,132;,
  3;132,9,129;,
  4;10,10,11,11;,
  4;11,11,12,12;,
  4;12,12,13,13;,
  4;13,13,14,14;,
  4;14,14,15,15;,
  4;15,15,16,16;,
  4;16,16,17,17;,
  4;17,17,10,10;,
  3;136,18,137;,
  3;138,18,136;,
  3;139,18,138;,
  3;140,18,139;,
  3;141,18,140;,
  3;142,18,141;,
  3;143,18,142;,
  3;137,18,143;,
  3;144,19,145;,
  3;145,19,146;,
  3;146,19,147;,
  3;147,19,148;,
  3;148,19,149;,
  3;149,19,150;,
  3;150,19,151;,
  3;151,19,144;,
  4;32,32,32,32;,
  4;23,26,26,23;,
  4;27,22,22,27;,
  4;152,20,21,152;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;24,24,24;,
  3;24,24,24;,
  3;24,24,24;,
  3;24,24,24;,
  4;23,23,153,154;,
  4;27,27,26,26;,
  4;20,28,29,21;,
  4;21,29,30,155;,
  4;153,30,31,154;,
  4;154,31,28,20;,
  4;28,156,156,29;,
  4;157,157,157,30;,
  4;158,158,158,31;,
  4;159,159,159,159;,
  4;33,33,33,33;,
  4;160,36,36,160;,
  4;35,34,34,35;,
  4;161,161,161,161;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;24,24,24;,
  3;24,24,24;,
  3;24,24,24;,
  4;35,35,36,36;,
  4;89,40,38,89;,
  4;37,37,37,37;,
  4;37,37,37,37;,
  4;37,37,37,37;,
  4;37,37,37,37;,
  4;89,38,39,89;,
  3;68,69,42;,
  3;69,79,42;,
  3;42,79,41;,
  3;41,79,80;,
  3;68,42,67;,
  3;67,42,45;,
  3;45,42,46;,
  3;60,83,59;,
  3;59,83,85;,
  3;85,83,43;,
  3;43,83,84;,
  4;46,91,90,45;,
  4;47,53,54,48;,
  4;50,88,87,49;,
  4;52,56,55,51;,
  4;53,58,57,54;,
  4;56,60,59,55;,
  4;44,49,87,86;,
  4;91,46,42,92;,
  4;43,44,86,85;,
  4;92,42,41,93;,
  4;54,57,37,37;,
  4;48,54,37,37;,
  4;45,90,89,39;,
  4;37,37,56,37;,
  4;88,50,40,89;,
  4;37,56,52,37;,
  3;50,49,72;,
  3;49,44,72;,
  3;72,44,71;,
  4;61,65,66,62;,
  4;62,63,64,61;,
  4;63,72,70,64;,
  4;65,69,67,66;,
  4;38,40,63,62;,
  4;39,38,62,66;,
  4;67,45,39,66;,
  4;40,50,72,63;,
  3;67,69,68;,
  3;70,72,71;,
  3;41,80,93;,
  3;80,81,93;,
  3;81,162,93;,
  3;93,162,58;,
  3;84,82,43;,
  3;43,82,44;,
  3;82,163,44;,
  3;44,70,71;,
  4;73,77,78,74;,
  4;74,76,75,73;,
  4;76,82,83,75;,
  4;77,81,79,78;,
  4;73,75,164,165;,
  4;77,73,165,166;,
  4;162,81,77,166;,
  4;75,83,60,164;,
  4;61,64,76,74;,
  4;65,61,74,78;,
  4;79,69,65,78;,
  4;64,70,82,76;,
  3;79,81,80;,
  3;82,84,83;,
  4;86,55,59,85;,
  4;87,51,55,86;,
  4;88,167,51,87;,
  4;168,167,88,89;,
  4;169,168,89,89;,
  4;170,169,89,89;,
  4;90,171,170,89;,
  4;91,172,171,90;,
  4;53,47,91,92;,
  4;58,53,92,93;,
  4;94,94,95,95;,
  4;95,95,96,96;,
  4;96,96,97,97;,
  4;97,97,98,98;,
  4;98,98,99,99;,
  4;99,99,100,100;,
  4;100,100,101,101;,
  4;101,101,94,94;,
  3;173,102,174;,
  3;175,102,173;,
  3;176,102,175;,
  3;177,102,176;,
  3;178,102,177;,
  3;179,102,178;,
  3;180,102,179;,
  3;174,102,180;,
  3;181,103,182;,
  3;182,103,146;,
  3;146,103,147;,
  3;147,103,183;,
  3;183,103,184;,
  3;184,103,185;,
  3;185,103,147;,
  3;147,103,181;,
  4;107,105,105,107;,
  4;186,106,106,186;,
  4;110,111,111,110;,
  4;104,104,104,104;,
  4;25,25,187,108;,
  4;109,188,24,24;,
  4;189,107,107,189;,
  4;25,25,108,25;,
  4;190,190,190,190;,
  4;24,109,24,24;,
  4;106,110,110,106;,
  4;187,191,191,108;,
  4;192,192,192,192;,
  4;109,193,193,188;,
  4;112,112,112,112;,
  4;113,113,113,113;,
  4;114,114,114,114;,
  4;161,161,161,161;,
  4;194,194,194,194;,
  4;195,195,195,195;,
  4;107,116,116,107;,
  4;196,117,117,196;,
  4;110,120,120,110;,
  4;115,115,115,115;,
  4;25,25,197,118;,
  4;119,198,24,24;,
  4;199,107,107,199;,
  4;25,25,118,25;,
  4;200,200,200,200;,
  4;24,119,24,24;,
  4;117,110,110,117;,
  4;197,201,201,118;,
  4;202,202,202,202;,
  4;119,203,203,198;;
 }
 MeshTextureCoords {
  409;
  0.896230;0.401180;,
  0.884480;0.349900;,
  0.889010;0.349910;,
  0.904170;0.401200;,
  0.884480;0.349900;,
  0.896230;0.401180;,
  0.873560;0.349880;,
  0.877060;0.401140;,
  0.862630;0.349860;,
  0.857900;0.401100;,
  0.858100;0.349850;,
  0.849960;0.401080;,
  0.862630;0.349860;,
  0.857900;0.401100;,
  0.873560;0.349880;,
  0.877060;0.401140;,
  0.950390;0.347010;,
  0.950650;0.375330;,
  0.930500;0.355480;,
  0.970430;0.355130;,
  0.978880;0.375080;,
  0.970800;0.395170;,
  0.950920;0.403640;,
  0.930880;0.395520;,
  0.922420;0.375570;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.896810;0.401770;,
  0.885030;0.350350;,
  0.889570;0.350360;,
  0.904780;0.401790;,
  0.885030;0.350350;,
  0.896810;0.401770;,
  0.874080;0.350330;,
  0.877590;0.401730;,
  0.863120;0.350300;,
  0.858370;0.401690;,
  0.858580;0.350290;,
  0.850410;0.401670;,
  0.863120;0.350300;,
  0.858370;0.401690;,
  0.874080;0.350330;,
  0.877590;0.401730;,
  0.949420;0.349160;,
  0.949670;0.375750;,
  0.930740;0.357110;,
  0.968240;0.356790;,
  0.976180;0.375520;,
  0.968590;0.394390;,
  0.949910;0.402350;,
  0.931090;0.394720;,
  0.923150;0.375980;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.593120;0.334800;,
  0.593730;0.255640;,
  0.641900;0.255940;,
  0.641300;0.335090;,
  0.518130;0.293270;,
  0.518130;0.233180;,
  0.562660;0.233180;,
  0.562660;0.293270;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.519760;0.316520;,
  0.519760;0.358920;,
  0.562170;0.358920;,
  0.562170;0.316520;,
  0.509060;0.355270;,
  0.471290;0.349980;,
  0.499860;0.243730;,
  0.495050;0.240750;,
  0.443420;0.257240;,
  0.433230;0.266370;,
  0.433230;0.266370;,
  0.471290;0.349980;,
  0.443420;0.257240;,
  0.495050;0.240750;,
  0.509060;0.355270;,
  0.499860;0.243730;,
  0.562660;0.305130;,
  0.518130;0.305130;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.576270;0.355890;,
  0.579390;0.352000;,
  0.655350;0.351810;,
  0.658550;0.355680;,
  0.654780;0.239180;,
  0.657930;0.233660;,
  0.578820;0.239360;,
  0.575650;0.233870;,
  0.588200;0.341840;,
  0.645600;0.342190;,
  0.646310;0.247860;,
  0.588910;0.247510;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.973730;0.234150;,
  0.973970;0.251030;,
  0.872500;0.251990;,
  0.872270;0.235110;,
  0.974180;0.266550;,
  0.974630;0.299050;,
  0.873170;0.300010;,
  0.872720;0.267510;,
  0.974640;0.299720;,
  0.975130;0.334980;,
  0.873670;0.335940;,
  0.873180;0.300690;,
  0.851950;0.331330;,
  0.778920;0.331330;,
  0.844320;0.267460;,
  0.813880;0.232700;,
  0.778920;0.231910;,
  0.778920;0.331330;,
  0.851950;0.331330;,
  0.778920;0.231910;,
  0.813880;0.232700;,
  0.844320;0.267460;,
  0.974170;0.265720;,
  0.872710;0.266690;,
  0.205010;0.229940;,
  0.205010;0.254280;,
  0.141060;0.254280;,
  0.141060;0.229940;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.077110;0.254280;,
  0.077110;0.229940;,
  0.257890;0.364290;,
  0.257730;0.365920;,
  0.259670;0.364750;,
  0.269100;0.395930;,
  0.270750;0.393940;,
  0.269960;0.396440;,
  0.258040;0.362660;,
  0.279330;0.320260;,
  0.280130;0.323660;,
  0.357590;0.399340;,
  0.270690;0.397530;,
  0.355560;0.395510;,
  0.290830;0.394310;,
  0.270750;0.393940;,
  0.269960;0.396440;,
  0.296820;0.302880;,
  0.296700;0.299480;,
  0.355570;0.307570;,
  0.355570;0.363100;,
  0.357590;0.363130;,
  0.357590;0.304170;,
  0.279330;0.320260;,
  0.296700;0.299480;,
  0.296820;0.302880;,
  0.280130;0.323660;,
  0.357590;0.304170;,
  0.357590;0.363130;,
  0.355570;0.363100;,
  0.355570;0.307570;,
  0.355560;0.395510;,
  0.357590;0.399340;,
  0.259670;0.364750;,
  0.297250;0.362410;,
  0.297250;0.362410;,
  0.290830;0.394310;,
  0.363870;0.340400;,
  0.379170;0.362510;,
  0.422730;0.365800;,
  0.422730;0.340400;,
  0.363870;0.304380;,
  0.422730;0.304380;,
  0.017420;0.254280;,
  0.017420;0.229940;,
  0.422880;0.365380;,
  0.379320;0.362090;,
  0.364030;0.339980;,
  0.422880;0.339980;,
  0.264690;0.229940;,
  0.264690;0.254280;,
  0.364030;0.303960;,
  0.422880;0.303960;,
  0.258040;0.362660;,
  0.257890;0.364290;,
  0.141060;0.307750;,
  0.077110;0.307760;,
  0.077110;0.303960;,
  0.141060;0.303940;,
  0.205010;0.303960;,
  0.205010;0.307760;,
  0.264690;0.303930;,
  0.264690;0.307750;,
  0.017420;0.307750;,
  0.017420;0.303930;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.270690;0.397530;,
  0.269100;0.395930;,
  0.257730;0.365920;,
  0.342700;0.284620;,
  0.305070;0.284620;,
  0.305090;0.285530;,
  0.342700;0.285540;,
  0.380310;0.285530;,
  0.380340;0.284620;,
  0.406360;0.285550;,
  0.406360;0.284620;,
  0.279040;0.284620;,
  0.279040;0.285550;,
  0.380340;0.234200;,
  0.342700;0.234200;,
  0.305070;0.234200;,
  0.279070;0.234200;,
  0.406330;0.234200;,
  0.204960;0.349130;,
  0.141060;0.345300;,
  0.077150;0.349130;,
  0.032880;0.342890;,
  0.249230;0.342890;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.375310;0.234090;,
  0.405370;0.234090;,
  0.405370;0.285510;,
  0.375310;0.285510;,
  0.343090;0.234090;,
  0.343090;0.285510;,
  0.310880;0.234090;,
  0.310880;0.285510;,
  0.280820;0.285510;,
  0.280820;0.234090;,
  0.896810;0.401770;,
  0.885030;0.350350;,
  0.889570;0.350360;,
  0.904780;0.401790;,
  0.885030;0.350350;,
  0.896810;0.401770;,
  0.874080;0.350330;,
  0.877590;0.401730;,
  0.863120;0.350300;,
  0.858370;0.401690;,
  0.858580;0.350290;,
  0.850410;0.401670;,
  0.863120;0.350300;,
  0.858370;0.401690;,
  0.874080;0.350330;,
  0.877590;0.401730;,
  0.949880;0.349260;,
  0.950130;0.375860;,
  0.931210;0.357220;,
  0.968700;0.356890;,
  0.976650;0.375630;,
  0.969060;0.394500;,
  0.950380;0.402450;,
  0.931560;0.394820;,
  0.923620;0.376090;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.770000;0.430550;,
  0.735510;0.430850;,
  0.735390;0.416640;,
  0.769880;0.416340;,
  0.733500;0.430620;,
  0.709880;0.430820;,
  0.709760;0.416610;,
  0.733370;0.416410;,
  0.672590;0.355760;,
  0.672590;0.414090;,
  0.694000;0.414090;,
  0.694000;0.355760;,
  0.761830;0.406150;,
  0.739710;0.406340;,
  0.739580;0.392130;,
  0.761700;0.391940;,
  0.756360;0.388360;,
  0.716160;0.388610;,
  0.707740;0.363000;,
  0.756200;0.362580;,
  0.755810;0.360910;,
  0.707350;0.361330;,
  0.715770;0.386940;,
  0.755970;0.386690;,
  0.837400;0.429960;,
  0.837270;0.415750;,
  0.834900;0.387870;,
  0.834740;0.362090;,
  0.836040;0.405580;,
  0.768650;0.406170;,
  0.768530;0.391960;,
  0.835920;0.391370;,
  0.834350;0.360420;,
  0.834510;0.386200;,
  0.699460;0.429730;,
  0.699350;0.417890;,
  0.719270;0.348170;,
  0.752740;0.347960;,
  0.762480;0.343930;,
  0.775720;0.344830;,
  0.775990;0.356660;,
  0.762800;0.358140;,
  0.752350;0.346290;,
  0.718880;0.346500;,
  0.678060;0.274330;,
  0.672000;0.236750;,
  0.753530;0.236750;,
  0.747480;0.274330;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.672000;0.236750;,
  0.678060;0.274330;,
  0.747480;0.274330;,
  0.753530;0.236750;,
  0.677140;0.287720;,
  0.677140;0.334690;,
  0.749850;0.334690;,
  0.749850;0.287720;,
  0.676870;0.273770;,
  0.669950;0.239070;,
  0.755670;0.239070;,
  0.748750;0.273770;,
  0.748750;0.273770;,
  0.755670;0.239070;,
  0.669950;0.239070;,
  0.676870;0.273770;,
  0.770000;0.430540;,
  0.735510;0.430840;,
  0.735390;0.416630;,
  0.769880;0.416330;,
  0.733490;0.430400;,
  0.709880;0.430610;,
  0.709750;0.416400;,
  0.733370;0.416190;,
  0.673530;0.355760;,
  0.673530;0.414090;,
  0.694930;0.414090;,
  0.694930;0.355760;,
  0.761830;0.406630;,
  0.739710;0.406820;,
  0.739590;0.392610;,
  0.761710;0.392420;,
  0.755420;0.387520;,
  0.715220;0.387770;,
  0.706800;0.362160;,
  0.755260;0.361740;,
  0.756820;0.361510;,
  0.708360;0.361930;,
  0.716780;0.387540;,
  0.756980;0.387290;,
  0.837400;0.429950;,
  0.837270;0.415740;,
  0.833960;0.387030;,
  0.833800;0.361250;,
  0.836050;0.406060;,
  0.768650;0.406650;,
  0.768530;0.392440;,
  0.835920;0.391850;,
  0.835360;0.361020;,
  0.835520;0.386800;,
  0.699460;0.429510;,
  0.699350;0.417680;,
  0.718330;0.347330;,
  0.751810;0.347120;,
  0.762670;0.343610;,
  0.775910;0.344510;,
  0.776170;0.356340;,
  0.762980;0.357820;,
  0.753370;0.346890;,
  0.719890;0.347100;;
 }
}

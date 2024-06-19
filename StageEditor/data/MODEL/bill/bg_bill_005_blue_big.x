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
 320;
 -202.14890;-0.05292;-244.76607;,
 -242.15921;-5.61087;-244.92348;,
 -242.15921;931.95129;-244.92348;,
 -198.05931;933.29086;-244.92005;,
 -242.13564;932.94050;-198.87408;,
 -198.05931;933.29086;-244.92005;,
 -242.15921;931.95129;-244.92348;,
 -241.90444;-2.63214;-197.13806;,
 -242.15921;-5.61087;-244.92348;,
 -202.14890;-0.05292;-244.76607;,
 -242.15921;931.95129;-244.92348;,
 -242.15921;-5.61087;-244.92348;,
 -241.90444;-2.63214;-197.13806;,
 -242.13564;932.94050;-198.87408;,
 200.16495;-0.76932;-244.46914;,
 245.25675;-5.61087;245.25675;,
 245.26051;930.42233;-197.83664;,
 245.25675;930.03879;-244.92348;,
 196.68780;930.11262;-244.75454;,
 245.22928;0.64584;-199.80503;,
 245.25675;-5.61087;-244.92348;,
 245.25675;930.03879;-244.92348;,
 245.26051;930.42233;-197.83664;,
 245.22928;0.64584;-199.80503;,
 245.25675;-5.61087;-244.92348;,
 245.25675;930.03879;-244.92348;,
 245.25675;-5.61087;-244.92348;,
 200.16495;-0.76932;-244.46914;,
 196.68780;930.11262;-244.75454;,
 -198.05931;933.29086;-244.92005;,
 196.68780;930.11262;-244.75454;,
 200.16495;-0.76932;-244.46914;,
 -202.14890;-0.05292;-244.76607;,
 245.91895;-8.26524;198.39780;,
 245.25675;928.35151;245.25675;,
 245.25675;-5.61087;245.25675;,
 245.91895;-8.26524;198.39780;,
 246.81096;922.78167;198.80090;,
 245.91895;-8.26524;198.39780;,
 245.22928;0.64584;-199.80503;,
 245.26051;930.42233;-197.83664;,
 246.81096;922.78167;198.80090;,
 198.22913;-1.06668;243.66598;,
 245.25675;928.35151;245.25675;,
 192.73149;926.86309;247.02640;,
 198.22913;-1.06668;243.66598;,
 245.25675;-5.61087;245.25675;,
 -195.23592;-0.26415;243.54080;,
 -242.15921;-5.61087;245.25675;,
 -195.23592;-0.26415;243.54080;,
 198.22913;-1.06668;243.66598;,
 192.73149;926.86309;247.02640;,
 -193.21614;926.57107;246.92480;,
 -242.15921;926.41825;245.25675;,
 -242.15921;-5.61087;245.25675;,
 -195.23592;-0.26415;243.54080;,
 -193.21614;926.57107;246.92480;,
 -244.05902;924.72273;196.85699;,
 -193.21614;926.57107;246.92480;,
 -242.15921;926.41825;245.25675;,
 -244.03526;-12.61071;198.68472;,
 -244.03526;-12.61071;198.68472;,
 -242.15921;-5.61087;245.25675;,
 -242.15921;926.41825;245.25675;,
 -244.05902;924.72273;196.85699;,
 -244.03526;-12.61071;198.68472;,
 -244.05902;924.72273;196.85699;,
 -242.13564;932.94050;-198.87408;,
 -241.90444;-2.63214;-197.13806;,
 192.73149;926.86309;247.02640;,
 245.25675;928.35151;245.25675;,
 246.81096;922.78167;198.80090;,
 -90.00000;103.38543;245.10212;,
 90.00000;103.38543;245.10212;,
 90.00000;114.97158;245.10204;,
 -90.00000;114.97158;245.10204;,
 -90.00000;114.97158;-245.10204;,
 90.00000;114.97158;-245.10204;,
 90.00000;103.38543;-245.10212;,
 -90.00000;103.38543;-245.10212;,
 -90.00000;278.87714;245.63141;,
 90.00000;278.87714;245.63141;,
 90.00000;290.46321;245.63133;,
 -90.00000;290.46321;245.63133;,
 -90.00000;290.46321;-245.63133;,
 90.00000;290.46321;-245.63133;,
 90.00000;278.87714;-245.63141;,
 -90.00000;278.87714;-245.63141;,
 -90.00000;455.50763;245.63141;,
 90.00000;455.50763;245.63141;,
 90.00000;467.09378;245.63133;,
 -90.00000;467.09378;245.63133;,
 -90.00000;467.09378;-245.63133;,
 90.00000;467.09378;-245.63133;,
 90.00000;455.50763;-245.63141;,
 -90.00000;455.50763;-245.63141;,
 -90.00000;632.41714;247.86666;,
 90.00000;632.41714;247.86666;,
 90.00000;644.00316;247.86655;,
 -90.00000;644.00316;247.86655;,
 -90.00000;644.00316;-247.86655;,
 90.00000;644.00316;-247.86655;,
 90.00000;632.41714;-247.86666;,
 -90.00000;632.41714;-247.86666;,
 -90.00000;810.94760;247.86666;,
 90.00000;810.94760;247.86666;,
 90.00000;822.53362;247.86655;,
 -90.00000;822.53362;247.86655;,
 -90.00000;822.53362;-247.86655;,
 90.00000;822.53362;-247.86655;,
 90.00000;810.94760;-247.86666;,
 -90.00000;810.94760;-247.86666;,
 148.20066;809.53191;247.86666;,
 193.64084;809.53191;247.86666;,
 193.64084;821.11792;247.86655;,
 148.20066;821.11792;247.86655;,
 148.20066;821.11792;-247.86655;,
 193.64084;821.11792;-247.86655;,
 193.64084;809.53191;-247.86666;,
 148.20066;809.53191;-247.86666;,
 -190.02429;809.53191;247.86666;,
 -144.58418;809.53191;247.86666;,
 -144.58418;821.11792;247.86655;,
 -190.02429;821.11792;247.86655;,
 -190.02429;821.11792;-247.86655;,
 -144.58418;821.11792;-247.86655;,
 -144.58418;809.53191;-247.86666;,
 -190.02429;809.53191;-247.86666;,
 -190.02429;633.57323;247.86666;,
 -144.58418;633.57323;247.86666;,
 -144.58418;645.15941;247.86655;,
 -190.02429;645.15941;247.86655;,
 -190.02429;645.15941;-247.86655;,
 -144.58418;645.15941;-247.86655;,
 -144.58418;633.57323;-247.86666;,
 -190.02429;633.57323;-247.86666;,
 -190.02429;457.80597;247.86666;,
 -144.58418;457.80597;247.86666;,
 -144.58418;469.39212;247.86655;,
 -190.02429;469.39212;247.86655;,
 -190.02429;469.39212;-247.86655;,
 -144.58418;469.39212;-247.86655;,
 -144.58418;457.80597;-247.86666;,
 -190.02429;457.80597;-247.86666;,
 -194.27463;278.62703;247.86666;,
 -148.83443;278.62703;247.86666;,
 -148.83443;290.21311;247.86655;,
 -194.27463;290.21311;247.86655;,
 -194.27463;290.21311;-247.86655;,
 -148.83443;290.21311;-247.86655;,
 -148.83443;278.62703;-247.86666;,
 -194.27463;278.62703;-247.86666;,
 -194.27463;104.58522;247.86666;,
 -148.83443;104.58522;247.86666;,
 -148.83443;116.17137;247.86655;,
 -194.27463;116.17137;247.86655;,
 -194.27463;116.17137;-247.86655;,
 -148.83443;116.17137;-247.86655;,
 -148.83443;104.58522;-247.86666;,
 -194.27463;104.58522;-247.86666;,
 151.90146;104.58522;247.86666;,
 197.34156;104.58522;247.86666;,
 197.34156;116.17137;247.86655;,
 151.90146;116.17137;247.86655;,
 151.90146;116.17137;-247.86655;,
 197.34156;116.17137;-247.86655;,
 197.34156;104.58522;-247.86666;,
 151.90146;104.58522;-247.86666;,
 150.86141;456.22105;247.86666;,
 196.30151;456.22105;247.86666;,
 196.30151;467.80723;247.86655;,
 150.86141;467.80723;247.86655;,
 150.86141;467.80723;-247.86655;,
 196.30151;467.80723;-247.86655;,
 196.30151;456.22105;-247.86666;,
 150.86141;456.22105;-247.86666;,
 151.15491;280.28410;247.86666;,
 196.59501;280.28410;247.86666;,
 196.59501;291.87026;247.86655;,
 151.15491;291.87026;247.86655;,
 151.15491;291.87026;-247.86655;,
 196.59501;291.87026;-247.86655;,
 196.59501;280.28410;-247.86666;,
 151.15491;280.28410;-247.86666;,
 150.86141;632.41055;247.86666;,
 196.30151;632.41055;247.86666;,
 196.30151;643.99667;247.86655;,
 150.86141;643.99667;247.86655;,
 150.86141;643.99667;-247.86655;,
 196.30151;643.99667;-247.86655;,
 196.30151;632.41055;-247.86666;,
 150.86141;632.41055;-247.86666;,
 246.31037;103.38543;99.96120;,
 246.31037;103.38543;-80.03880;,
 246.31028;114.97158;-80.03880;,
 246.31028;114.97158;99.96120;,
 -246.31028;114.97158;99.96120;,
 -246.31028;114.97158;-80.03880;,
 -246.31037;103.38543;-80.03880;,
 -246.31037;103.38543;99.96120;,
 246.31037;279.58131;99.96120;,
 246.31037;279.58131;-80.03880;,
 246.31028;291.16746;-80.03880;,
 246.31028;291.16746;99.96120;,
 -246.31028;291.16746;99.96120;,
 -246.31028;291.16746;-80.03880;,
 -246.31037;279.58131;-80.03880;,
 -246.31037;279.58131;99.96120;,
 246.31037;455.48675;99.96120;,
 246.31037;455.48675;-80.03880;,
 246.31028;467.07291;-80.03880;,
 246.31028;467.07291;99.96120;,
 -246.31028;467.07291;99.96120;,
 -246.31028;467.07291;-80.03880;,
 -246.31037;455.48675;-80.03880;,
 -246.31037;455.48675;99.96120;,
 246.31037;632.45889;99.96120;,
 246.31037;632.45889;-80.03880;,
 246.31028;644.04501;-80.03880;,
 246.31028;644.04501;99.96120;,
 -246.31028;644.04501;99.96120;,
 -246.31028;644.04501;-80.03880;,
 -246.31037;632.45889;-80.03880;,
 -246.31037;632.45889;99.96120;,
 246.58398;808.69541;99.96120;,
 246.58398;808.69541;-80.03880;,
 246.58387;820.28159;-80.03880;,
 246.58387;820.28159;99.96120;,
 -246.58387;820.28159;99.96120;,
 -246.58387;820.28159;-80.03880;,
 -246.58398;808.69541;-80.03880;,
 -246.58398;808.69541;99.96120;,
 246.73285;808.55182;198.47978;,
 246.73285;808.55182;153.03951;,
 246.73274;820.13783;153.03951;,
 246.73274;820.13783;198.47978;,
 -246.73274;820.13783;198.47978;,
 -246.73274;820.13783;153.03951;,
 -246.73285;808.55182;153.03951;,
 -246.73285;808.55182;198.47978;,
 246.73285;808.55182;198.47978;,
 246.73285;808.55182;153.03951;,
 246.73274;820.13783;153.03951;,
 246.73274;820.13783;198.47978;,
 -246.73274;820.13783;198.47978;,
 -246.73274;820.13783;153.03951;,
 -246.73285;808.55182;153.03951;,
 -246.73285;808.55182;198.47978;,
 246.73285;632.21851;198.47978;,
 246.73285;632.21851;153.03951;,
 246.73274;643.80463;153.03951;,
 246.73274;643.80463;198.47978;,
 -246.73274;643.80463;198.47978;,
 -246.73274;643.80463;153.03951;,
 -246.73285;632.21851;153.03951;,
 -246.73285;632.21851;198.47978;,
 246.73285;455.08300;198.47978;,
 246.73285;455.08300;153.03951;,
 246.73274;466.66905;153.03951;,
 246.73274;466.66905;198.47978;,
 -246.73274;466.66905;198.47978;,
 -246.73274;466.66905;153.03951;,
 -246.73285;455.08300;153.03951;,
 -246.73285;455.08300;198.47978;,
 246.73285;278.83242;198.47978;,
 246.73285;278.83242;153.03951;,
 246.73274;290.41855;153.03951;,
 246.73274;290.41855;198.47978;,
 -246.73274;290.41855;198.47978;,
 -246.73274;290.41855;153.03951;,
 -246.73285;278.83242;153.03951;,
 -246.73285;278.83242;198.47978;,
 246.73285;102.39209;198.47978;,
 246.73285;102.39209;153.03951;,
 246.73274;113.97816;153.03951;,
 246.73274;113.97816;198.47978;,
 -246.73274;113.97816;198.47978;,
 -246.73274;113.97816;153.03951;,
 -246.73285;102.39209;153.03951;,
 -246.73285;102.39209;198.47978;,
 246.73285;102.39209;-153.42399;,
 246.73285;102.39209;-198.86426;,
 246.73274;113.97816;-198.86426;,
 246.73274;113.97816;-153.42399;,
 -246.73274;113.97816;-153.42399;,
 -246.73274;113.97816;-198.86426;,
 -246.73285;102.39209;-198.86426;,
 -246.73285;102.39209;-153.42399;,
 246.73285;279.18404;-153.42399;,
 246.73285;279.18404;-198.86426;,
 246.73274;290.77011;-198.86426;,
 246.73274;290.77011;-153.42399;,
 -246.73274;290.77011;-153.42399;,
 -246.73274;290.77011;-198.86426;,
 -246.73285;279.18404;-198.86426;,
 -246.73285;279.18404;-153.42399;,
 246.73285;456.77995;-153.42399;,
 246.73285;456.77995;-198.86426;,
 246.73274;468.36611;-198.86426;,
 246.73274;468.36611;-153.42399;,
 -246.73274;468.36611;-153.42399;,
 -246.73274;468.36611;-198.86426;,
 -246.73285;456.77995;-198.86426;,
 -246.73285;456.77995;-153.42399;,
 246.73285;631.98681;-153.42399;,
 246.73285;631.98681;-198.86426;,
 246.73274;643.57299;-198.86426;,
 246.73274;643.57299;-153.42399;,
 -246.73274;643.57299;-153.42399;,
 -246.73274;643.57299;-198.86426;,
 -246.73285;631.98681;-198.86426;,
 -246.73285;631.98681;-153.42399;,
 246.73285;807.87506;-153.42399;,
 246.73285;807.87506;-198.86426;,
 246.73274;819.46124;-198.86426;,
 246.73274;819.46124;-153.42399;,
 -246.73274;819.46124;-153.42399;,
 -246.73274;819.46124;-198.86426;,
 -246.73285;807.87506;-198.86426;,
 -246.73285;807.87506;-153.42399;;
 
 91;
 4;0,1,2,3;,
 3;4,5,6;,
 3;7,8,9;,
 4;10,11,12,13;,
 3;14,15,9;,
 3;16,17,18;,
 3;19,14,20;,
 4;21,22,23,24;,
 4;25,26,27,28;,
 4;29,30,31,32;,
 3;33,14,19;,
 3;33,15,14;,
 4;34,35,36,37;,
 4;38,39,40,41;,
 3;42,9,15;,
 4;43,44,45,46;,
 3;47,9,42;,
 3;47,48,9;,
 4;49,50,51,52;,
 4;53,54,55,56;,
 3;57,58,4;,
 3;57,59,58;,
 3;60,9,48;,
 3;60,7,9;,
 4;61,62,63,64;,
 4;65,66,67,68;,
 4;69,70,71,5;,
 4;58,69,5,4;,
 4;16,18,5,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;96,97,98,99;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;116,117,118,119;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;132,133,134,135;,
 4;136,137,138,139;,
 4;140,141,142,143;,
 4;144,145,146,147;,
 4;148,149,150,151;,
 4;152,153,154,155;,
 4;156,157,158,159;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;168,169,170,171;,
 4;172,173,174,175;,
 4;176,177,178,179;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;188,189,190,191;,
 4;192,193,194,195;,
 4;196,197,198,199;,
 4;200,201,202,203;,
 4;204,205,206,207;,
 4;208,209,210,211;,
 4;212,213,214,215;,
 4;216,217,218,219;,
 4;220,221,222,223;,
 4;224,225,226,227;,
 4;228,229,230,231;,
 4;232,233,234,235;,
 4;236,237,238,239;,
 4;240,241,242,243;,
 4;244,245,246,247;,
 4;248,249,250,251;,
 4;252,253,254,255;,
 4;256,257,258,259;,
 4;260,261,262,263;,
 4;264,265,266,267;,
 4;268,269,270,271;,
 4;272,273,274,275;,
 4;276,277,278,279;,
 4;280,281,282,283;,
 4;284,285,286,287;,
 4;288,289,290,291;,
 4;292,293,294,295;,
 4;296,297,298,299;,
 4;300,301,302,303;,
 4;304,305,306,307;,
 4;308,309,310,311;,
 4;312,313,314,315;,
 4;316,317,318,319;;
 
 MeshMaterialList {
  6;
  91;
  0,
  3,
  5,
  0,
  5,
  3,
  5,
  0,
  0,
  1,
  5,
  5,
  0,
  2,
  5,
  0,
  5,
  5,
  1,
  0,
  3,
  3,
  5,
  5,
  0,
  2,
  3,
  3,
  3,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
  Material {
   0.178824;0.354510;0.545882;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\MATERIAL\\window_wall2.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\MATERIAL\\window_wall2.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\MATERIAL\\conc_flore.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.780000;0.780000;0.780000;;
   TextureFilename {
    "data\\TEXTURE\\MATERIAL\\window_wall2.jpg";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  101;
  0.002009;-0.000083;-0.999998;,
  0.001492;0.999966;-0.008145;,
  -0.104397;-0.985117;0.136546;,
  0.999716;-0.000482;0.023812;,
  -0.216745;-0.975503;0.037610;,
  0.001248;-0.001789;0.999998;,
  0.495425;-0.868111;0.030605;,
  0.001293;-0.000159;-0.999999;,
  -0.028548;0.999585;0.003829;,
  0.086178;-0.996117;0.017991;,
  -0.003511;0.999983;0.004671;,
  -0.150382;-0.987922;0.037364;,
  -0.025568;-0.998023;0.057419;,
  0.999945;-0.000488;0.010492;,
  -0.250215;-0.968144;0.009464;,
  -0.000156;-0.002674;0.999996;,
  -0.050378;-0.997960;0.039224;,
  0.000478;-0.002713;0.999996;,
  0.055643;-0.998450;-0.001220;,
  -0.029202;0.999547;-0.007245;,
  0.461148;-0.887132;0.018436;,
  -0.007079;0.999841;-0.016350;,
  -0.030353;0.999309;-0.021451;,
  0.137101;-0.988683;0.060899;,
  0.147353;-0.988789;0.024168;,
  -0.999996;-0.000123;0.002924;,
  -0.999999;-0.000135;-0.001101;,
  1.000000;-0.000017;0.000265;,
  0.999999;-0.000255;-0.001283;,
  -0.006777;-0.000160;-0.999977;,
  -0.003100;-0.000198;-0.999995;,
  -0.000019;-0.001711;0.999998;,
  -0.019073;0.999818;-0.000667;,
  -0.001930;0.999388;-0.034934;,
  -0.999850;-0.000060;0.017309;,
  -0.999210;0.000026;0.039735;,
  0.005290;0.999514;-0.030721;,
  0.009393;0.997224;-0.073864;,
  0.000441;0.999602;-0.028219;,
  0.000000;0.000007;1.000000;,
  0.000000;0.000007;-1.000000;,
  0.000000;0.000007;1.000000;,
  0.000000;0.000007;-1.000000;,
  0.000000;0.000007;1.000000;,
  0.000000;0.000007;-1.000000;,
  0.000000;0.000009;1.000000;,
  0.000000;0.000009;-1.000000;,
  0.000000;0.000009;1.000000;,
  0.000000;0.000009;-1.000000;,
  0.000000;0.000009;1.000000;,
  0.000000;0.000009;-1.000000;,
  0.000000;0.000009;1.000000;,
  0.000000;0.000009;-1.000000;,
  0.000000;0.000009;1.000000;,
  0.000000;0.000009;-1.000000;,
  0.000000;0.000009;1.000000;,
  0.000000;0.000009;-1.000000;,
  0.000000;0.000009;1.000000;,
  0.000000;0.000009;-1.000000;,
  0.000000;0.000009;1.000000;,
  0.000000;0.000009;-1.000000;,
  0.000000;0.000009;1.000000;,
  0.000000;0.000009;-1.000000;,
  0.000000;0.000009;1.000000;,
  0.000000;0.000009;-1.000000;,
  0.000000;0.000009;1.000000;,
  0.000000;0.000009;-1.000000;,
  0.000000;0.000009;1.000000;,
  0.000000;0.000009;-1.000000;,
  1.000000;0.000007;0.000000;,
  -1.000000;0.000007;0.000000;,
  1.000000;0.000007;0.000000;,
  -1.000000;0.000007;0.000000;,
  1.000000;0.000007;0.000000;,
  -1.000000;0.000007;0.000000;,
  1.000000;0.000007;0.000000;,
  -1.000000;0.000007;0.000000;,
  1.000000;0.000009;0.000000;,
  -1.000000;0.000009;0.000000;,
  1.000000;0.000009;0.000000;,
  -1.000000;0.000009;0.000000;,
  1.000000;0.000009;0.000000;,
  -1.000000;0.000009;0.000000;,
  1.000000;0.000009;0.000000;,
  -1.000000;0.000009;0.000000;,
  1.000000;0.000009;0.000000;,
  -1.000000;0.000009;0.000000;,
  1.000000;0.000009;0.000000;,
  -1.000000;0.000009;0.000000;,
  1.000000;0.000009;0.000000;,
  -1.000000;0.000009;0.000000;,
  1.000000;0.000009;0.000000;,
  -1.000000;0.000009;0.000000;,
  1.000000;0.000009;0.000000;,
  -1.000000;0.000009;0.000000;,
  1.000000;0.000009;0.000000;,
  -1.000000;0.000009;0.000000;,
  1.000000;0.000009;0.000000;,
  -1.000000;0.000009;0.000000;,
  1.000000;0.000009;0.000000;,
  -1.000000;0.000009;0.000000;;
  91;
  4;7,0,0,7;,
  3;8,21,22;,
  3;9,23,24;,
  4;25,25,26,26;,
  3;11,4,24;,
  3;10,1,10;,
  3;12,11,2;,
  4;27,28,28,27;,
  4;29,29,30,30;,
  4;7,30,30,7;,
  3;14,11,12;,
  3;14,4,11;,
  4;3,3,13,13;,
  4;13,28,28,13;,
  3;16,24,4;,
  4;31,15,15,31;,
  3;18,24,16;,
  3;18,6,24;,
  4;17,15,15,17;,
  4;5,5,17,17;,
  3;19,32,8;,
  3;19,33,32;,
  3;20,24,6;,
  3;20,9,24;,
  4;34,35,35,34;,
  4;34,34,26,26;,
  4;36,37,38,21;,
  4;32,36,21,8;,
  4;10,10,21,38;,
  4;39,39,39,39;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;44,44,44,44;,
  4;45,45,45,45;,
  4;46,46,46,46;,
  4;47,47,47,47;,
  4;48,48,48,48;,
  4;49,49,49,49;,
  4;50,50,50,50;,
  4;51,51,51,51;,
  4;52,52,52,52;,
  4;53,53,53,53;,
  4;54,54,54,54;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;57,57,57,57;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;61,61,61,61;,
  4;62,62,62,62;,
  4;63,63,63,63;,
  4;64,64,64,64;,
  4;65,65,65,65;,
  4;66,66,66,66;,
  4;67,67,67,67;,
  4;68,68,68,68;,
  4;69,69,69,69;,
  4;70,70,70,70;,
  4;71,71,71,71;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;74,74,74,74;,
  4;75,75,75,75;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;78,78,78,78;,
  4;79,79,79,79;,
  4;80,80,80,80;,
  4;81,81,81,81;,
  4;82,82,82,82;,
  4;83,83,83,83;,
  4;84,84,84,84;,
  4;85,85,85,85;,
  4;86,86,86,86;,
  4;87,87,87,87;,
  4;88,88,88,88;,
  4;89,89,89,89;,
  4;90,90,90,90;,
  4;91,91,91,91;,
  4;92,92,92,92;,
  4;93,93,93,93;,
  4;94,94,94,94;,
  4;95,95,95,95;,
  4;96,96,96,96;,
  4;97,97,97,97;,
  4;98,98,98,98;,
  4;99,99,99,99;,
  4;100,100,100,100;;
 }
 MeshTextureCoords {
  320;
  -0.578430;3.057180;,
  -0.855760;3.057180;,
  -0.855760;-2.125580;,
  -0.557250;-2.125580;,
  -0.052420;0.887880;,
  0.069220;1.043080;,
  -0.052410;1.043090;,
  0.000000;0.098270;,
  0.000000;0.000000;,
  0.102280;0.000000;,
  -0.827170;-2.136620;,
  -0.827170;3.072060;,
  -0.559390;3.072060;,
  -0.443850;-2.136620;,
  0.900660;0.000000;,
  1.000000;1.000000;,
  1.052470;0.910480;,
  1.052480;1.043020;,
  0.922310;1.043030;,
  1.000000;0.132280;,
  1.000000;0.000000;,
  -0.850950;-2.136620;,
  -0.523610;-2.136620;,
  -0.490490;3.072060;,
  -0.850950;3.072060;,
  1.855760;-2.125580;,
  1.855760;3.057180;,
  1.586410;3.057180;,
  1.536300;-2.125580;,
  0.009520;-4.149260;,
  0.987080;-4.131250;,
  0.995690;1.144540;,
  -0.000610;1.140480;,
  1.000000;0.847020;,
  1.874020;-2.136620;,
  1.874020;3.072060;,
  1.457140;3.072060;,
  1.386790;-2.136620;,
  0.033750;1.187020;,
  1.019880;1.136520;,
  1.015000;-4.132980;,
  0.032750;-4.089680;,
  0.915410;1.000000;,
  1.855760;-2.125580;,
  1.564060;-2.125580;,
  1.626400;3.057180;,
  1.855760;3.057180;,
  0.129790;1.000000;,
  0.000000;1.000000;,
  0.016510;1.141680;,
  0.990900;1.146230;,
  0.977290;-4.112830;,
  0.021510;-4.111170;,
  -0.855760;-2.125580;,
  -0.855760;3.057180;,
  -0.503830;3.057180;,
  -0.492710;-2.125580;,
  -0.052470;0.045390;,
  0.095450;-0.060300;,
  -0.052480;-0.060290;,
  0.000000;0.892540;,
  1.604970;3.072060;,
  1.897800;3.072060;,
  1.897800;-2.136620;,
  1.636800;-2.136620;,
  0.033040;1.211650;,
  0.037570;-4.100680;,
  1.017570;-4.147250;,
  1.013270;1.155100;,
  0.933550;-0.060350;,
  1.052410;-0.060360;,
  1.052420;0.136930;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;,
  0.313960;0.542290;,
  0.707460;0.542290;,
  0.707460;0.498450;,
  0.313960;0.498450;,
  0.313960;0.498450;,
  0.707460;0.498450;,
  0.707460;0.542290;,
  0.313960;0.542290;;
 }
}
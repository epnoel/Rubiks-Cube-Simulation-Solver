/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#pragma once

#include "RubiksCubeProcessor.h"


RubiksCubeProcessor::RubiksCubeProcessor() {
    cubeCode = "WWWWWWWWWRRRRRRRRRBBBBBBBBBOOOOOOOOOGGGGGGGGGYYYYYYYYY";

    // Corners

    std::string corner1, corner2, corner3, corner4, corner5, corner6, corner7, corner8;

    corner1 = "";
    corner1 += cubeCode[24];
    corner1 += cubeCode[45];
    corner1 += cubeCode[17];

    corner2 = "";
    corner2 += cubeCode[26];
    corner2 += cubeCode[33];
    corner2 += cubeCode[47];

    corner3 = "";
    corner3 += cubeCode[44];
    corner3 += cubeCode[15];
    corner3 += cubeCode[51];

    corner4 = "";
    corner4 += cubeCode[42];
    corner4 += cubeCode[53];
    corner4 += cubeCode[35];

    corner5 = "";
    corner5 += cubeCode[18];
    corner5 += cubeCode[11];
    corner5 += cubeCode[6];

    corner6 = "";
    corner6 += cubeCode[20];
    corner6 += cubeCode[8];
    corner6 += cubeCode[27];

    corner7 = "";
    corner7 += cubeCode[38];
    corner7 += cubeCode[0];
    corner7 += cubeCode[9];

    corner8 = "";
    corner8 += cubeCode[36];
    corner8 += cubeCode[29];
    corner8 += cubeCode[2];

    cornerNames = { corner2, corner6, corner3, corner4, corner5, corner1, corner8, corner7 };

    loadInCornerMap(cornerMap);
    loadInCornerPermutation(cornerPermutation);

    // {URF, UBR, DLF, DFR, ULB, UFL, DRB, DBL}
    cornerFinderMap = { {cornerPermutation[0], cornerNames[0] },
                        {cornerPermutation[1], cornerNames[1]},
                        {cornerPermutation[2], cornerNames[2]},
                        {cornerPermutation[3], cornerNames[3]},
                        {cornerPermutation[4], cornerNames[4]},
                        {cornerPermutation[5], cornerNames[5]},
                        {cornerPermutation[6], cornerNames[6]},
                        {cornerPermutation[7], cornerNames[7]} };


    // Edges

    std::string edge1, edge2, edge3, edge4, edge5, edge6, edge7, edge8, edge9, edge10, edge11, edge12;

    // Edge 1
    // returnEdge[0] = cubeCode[46];
    // returnEdge[1] = cubeCode[25];
    //determineEdgeGoodness(cubeCode[25], cubeCode[46], true);
    edge1 = "";
    edge1 += cubeCode[25];
    edge1 += cubeCode[46];

    // Edge 2
    // returnEdge[2] = cubeCode[48];
    // returnEdge[3] = cubeCode[16];
    determineEdgeGoodness(cubeCode[48], cubeCode[16], false);
    edge2 = "";
    edge2 += cubeCode[48];
    edge2 += cubeCode[16];

    // Edge 3
    // returnEdge[4] = cubeCode[50];
    // returnEdge[5] = cubeCode[34];
    //determineEdgeGoodness(cubeCode[50], cubeCode[34], false);
    edge3 = "";
    edge3 += cubeCode[50];
    edge3 += cubeCode[34];

    // Edge 4
    // returnEdge[6] = cubeCode[52];
    // returnEdge[7] = cubeCode[43];
    //determineEdgeGoodness(cubeCode[43], cubeCode[52], true);
    edge4 = "";
    edge4 += cubeCode[43];
    edge4 += cubeCode[52];


    // Edge 5
    // returnEdge[8] = cubeCode[19];
    // returnEdge[9] = cubeCode[7];
    //determineEdgeGoodness(cubeCode[19], cubeCode[7], true);
    edge5 = "";
    edge5 += cubeCode[19];
    edge5 += cubeCode[7];

    // Edge 6
    // returnEdge[10] = cubeCode[5];
    // returnEdge[11] = cubeCode[28];
    // determineEdgeGoodness(cubeCode[5], cubeCode[28], false);
    edge6 = "";
    edge6 += cubeCode[5];
    edge6 += cubeCode[28];

    // Edge 7
    // returnEdge[12] = cubeCode[3];
    // returnEdge[13] = cubeCode[10];
    //determineEdgeGoodness(cubeCode[3], cubeCode[10], false);
    edge7 = "";
    edge7 += cubeCode[3];
    edge7 += cubeCode[10];

    // Edge 8
    // returnEdge[14] = cubeCode[1];
    // returnEdge[15] = cubeCode[37];
    //determineEdgeGoodness(cubeCode[37], cubeCode[1], true);
    edge8 = "";
    edge8 += cubeCode[37];
    edge8 += cubeCode[1];

    // Edge 9
    // returnEdge[16] = cubeCode[21];
    // returnEdge[17] = cubeCode[14];
    //determineEdgeGoodness(cubeCode[21], cubeCode[14], true);
    edge9 = "";
    edge9 += cubeCode[21];
    edge9 += cubeCode[14];

    // Edge 10
    // returnEdge[18] = cubeCode[23];
    // returnEdge[19] = cubeCode[30];
    //determineEdgeGoodness(cubeCode[23], cubeCode[30], true);
    edge10 = "";
    edge10 += cubeCode[23];
    edge10 += cubeCode[30];

    // Edge 11
    // returnEdge[20] = cubeCode[12];
    // returnEdge[21] = cubeCode[41];
    //determineEdgeGoodness(cubeCode[41], cubeCode[12], true);
    edge11 = "";
    edge11 += cubeCode[41];
    edge11 += cubeCode[12];

    // Edge 12
    // returnEdge[22] = cubeCode[32];
    // returnEdge[23] = cubeCode[39];
    //determineEdgeGoodness(cubeCode[39], cubeCode[32], true);
    edge12 = "";
    edge12 += cubeCode[39];
    edge12 += cubeCode[32];


    std::map<std::vector<char>, int> edgeMap;
    loadInEdgeMap(edgeMap);
    loadInEdgePermutation(edgePermutation);

    // {UF, UR, UB, UL, DF, DR, DB, DL, FR, BR, BL, FL}

    edgeNames = { edge1, edge10, edge5, edge9, edge4, edge12, edge8, edge11, edge3, edge6, edge7, edge2 };

    edgeFinderMap = { {edgePermutation[0], edgeNames[0] },
                        {edgePermutation[1], edgeNames[1]},
                        {edgePermutation[2], edgeNames[2]},
                        {edgePermutation[3], edgeNames[3]},
                        {edgePermutation[4], edgeNames[4]},
                        {edgePermutation[5], edgeNames[5]},
                        {edgePermutation[6], edgeNames[6]},
                        {edgePermutation[7], edgeNames[7]},
                        {edgePermutation[8], edgeNames[8]},
                        {edgePermutation[9], edgeNames[9]},
                        {edgePermutation[10], edgeNames[10]},
                        {edgePermutation[11], edgeNames[11]} };


    // Phase Tables
    //loadPhaseTable(fileNamePhase1, phase1Map);
    //loadPhaseTable(fileNamePhase2, phase2Map);
    //loadPhaseTable(fileNamePhase3, phase3Map);
    //loadPhaseTable(fileNamePhase4, phase4Map);

}

void RubiksCubeProcessor::loadInPhaseTables()
{
    // Phase Tables
    loadPhaseTable(fileNamePhase1, phase1Map);
    std::cout << "Loaded Phase 1 -> size = " << phase1Map.size() << std::endl;

    loadPhaseTable(fileNamePhase2, phase2Map);
    std::cout << "Loaded Phase 2 -> size = " << phase2Map.size() << std::endl;

    loadPhaseTable(fileNamePhase3, phase3Map);
    std::cout << "Loaded Phase 3 -> size = " << phase3Map.size() << std::endl;

    loadPhaseTable(fileNamePhase4, phase4Map);
    std::cout << "Loaded Phase 4 -> size = " << phase4Map.size() << std::endl;
}

std::string RubiksCubeProcessor::getCubeCode()
{
    return cubeCode;
}

void RubiksCubeProcessor::rotateFrontString() {
    //rotate90(v[5]);

    int start = 9 * 5;

    // std::vector<char> firstTemp = {cubeCode[45],cubeCode[46],cubeCode[50],cubeCode[47]}

    // cubeCode[45] = cubeCode[51];
    // cubeCode[46] = cubeCode[48];
    // cubeCode[47] = firstTemp[0];
    // cubeCode[48] = cubeCode[52];
    // cubeCode[49] = cubeCode[49];
    // cubeCode[50] = firstTemp[1];
    // cubeCode[51] = cubeCode[53];
    // cubeCode[52] = firstTemp[2];
    // cubeCode[53] = firstTemp[3];

    std::vector<char> firstTemp = { cubeCode[start],cubeCode[start + 1],cubeCode[start + 5],cubeCode[start + 2] };

    cubeCode[45] = cubeCode[start + 6];
    cubeCode[46] = cubeCode[start + 3];
    cubeCode[47] = firstTemp[0];
    cubeCode[48] = cubeCode[start + 7];
    cubeCode[49] = cubeCode[start + 4];
    cubeCode[50] = firstTemp[1];
    cubeCode[51] = cubeCode[start + 8];
    cubeCode[52] = firstTemp[2];
    cubeCode[53] = firstTemp[3];



    //string temp = v[3][2];
    std::vector<char> temp = { cubeCode[33],cubeCode[34],cubeCode[35] };

    //v[3][2] = v[2][2];
    cubeCode[33] = cubeCode[24];
    cubeCode[34] = cubeCode[25];
    cubeCode[35] = cubeCode[26];

    //v[2][2] = v[1][2];
    cubeCode[24] = cubeCode[15];
    cubeCode[25] = cubeCode[16];
    cubeCode[26] = cubeCode[17];

    //v[1][2] = v[4][2];
    cubeCode[15] = cubeCode[42];
    cubeCode[16] = cubeCode[43];
    cubeCode[17] = cubeCode[44];

    cubeCode[42] = temp[0];
    cubeCode[43] = temp[1];
    cubeCode[44] = temp[2];
}

void RubiksCubeProcessor::rotateFrontCCWString() {
    //rotate90CCW(v[5]);

    int start = 9 * 5;

    // std::vector<char> firstTemp = {cubeCode[46],cubeCode[45],cubeCode[48],cubeCode[51]}

    // cubeCode[45] = cubeCode[47];
    // cubeCode[46] = cubeCode[50];
    // cubeCode[47] = cubeCode[53];
    // cubeCode[48] = firstTemp[0];
    // cubeCode[49] = cubeCode[49];
    // cubeCode[50] = cubeCode[52];
    // cubeCode[51] = firstTemp[1];
    // cubeCode[52] = firstTemp[2];
    // cubeCode[53] = firstTemp[3];

    std::vector<char> firstTemp = { cubeCode[start + 1],cubeCode[start],cubeCode[start + 3],cubeCode[start + 6] };

    cubeCode[start] = cubeCode[start + 2];
    cubeCode[start + 1] = cubeCode[start + 5];
    cubeCode[start + 2] = cubeCode[start + 8];
    cubeCode[start + 3] = firstTemp[0];
    cubeCode[start + 4] = cubeCode[start + 4];
    cubeCode[start + 5] = cubeCode[start + 7];
    cubeCode[start + 6] = firstTemp[1];
    cubeCode[start + 7] = firstTemp[2];
    cubeCode[start + 8] = firstTemp[3];

    //string temp = v[3][2];
    std::vector<char> temp = { cubeCode[33],cubeCode[34],cubeCode[35] };

    //v[3][2] = v[4][2];
    cubeCode[33] = cubeCode[42];
    cubeCode[34] = cubeCode[43];
    cubeCode[35] = cubeCode[44];

    //v[4][2] = v[1][2];
    cubeCode[42] = cubeCode[15];
    cubeCode[43] = cubeCode[16];
    cubeCode[44] = cubeCode[17];

    //v[1][2] = v[2][2];
    cubeCode[15] = cubeCode[24];
    cubeCode[16] = cubeCode[25];
    cubeCode[17] = cubeCode[26];

    //v[2][2] = temp;
    cubeCode[24] = temp[0];
    cubeCode[25] = temp[1];
    cubeCode[26] = temp[2];
}

void RubiksCubeProcessor::rotateFrontTwiceString() {
    rotateFrontString();
    rotateFrontString();
}

void RubiksCubeProcessor::rotateBackString() {
    //rotate90(v[0]);

    int start = 0;

    std::vector<char> firstTemp = { cubeCode[start],cubeCode[start + 1],cubeCode[start + 5],cubeCode[start + 2] };

    cubeCode[start] = cubeCode[start + 6];
    cubeCode[start + 1] = cubeCode[start + 3];
    cubeCode[start + 2] = firstTemp[0];
    cubeCode[start + 3] = cubeCode[start + 7];
    cubeCode[start + 4] = cubeCode[start + 4];
    cubeCode[start + 5] = firstTemp[1];
    cubeCode[start + 6] = cubeCode[start + 8];
    cubeCode[start + 7] = firstTemp[2];
    cubeCode[start + 8] = firstTemp[3];

    //string temp = v[1][0];
    std::vector<char> temp = { cubeCode[9],cubeCode[10],cubeCode[11] };

    //v[1][0] = v[2][0];
    cubeCode[9] = cubeCode[18];
    cubeCode[10] = cubeCode[19];
    cubeCode[11] = cubeCode[20];

    //v[2][0] = v[3][0];
    cubeCode[18] = cubeCode[27];
    cubeCode[19] = cubeCode[28];
    cubeCode[20] = cubeCode[29];

    //v[3][0] = v[4][0];
    cubeCode[27] = cubeCode[36];
    cubeCode[28] = cubeCode[37];
    cubeCode[29] = cubeCode[38];

    //v[4][0] = temp;
    cubeCode[36] = temp[0];
    cubeCode[37] = temp[1];
    cubeCode[38] = temp[2];

}

void RubiksCubeProcessor::rotateBackCCWString() {
    //rotate90CCW(v[0]);

    int start = 0;

    std::vector<char> firstTemp = { cubeCode[start + 1],cubeCode[start],cubeCode[start + 3],cubeCode[start + 6] };

    cubeCode[start] = cubeCode[start + 2];
    cubeCode[start + 1] = cubeCode[start + 5];
    cubeCode[start + 2] = cubeCode[start + 8];
    cubeCode[start + 3] = firstTemp[0];
    cubeCode[start + 4] = cubeCode[start + 4];
    cubeCode[start + 5] = cubeCode[start + 7];
    cubeCode[start + 6] = firstTemp[1];
    cubeCode[start + 7] = firstTemp[2];
    cubeCode[start + 8] = firstTemp[3];


    //string temp = v[1][0];
    std::vector<char> temp = { cubeCode[9],cubeCode[10],cubeCode[11] };

    //v[1][0] = v[4][0];
    cubeCode[9] = cubeCode[36];
    cubeCode[10] = cubeCode[37];
    cubeCode[11] = cubeCode[38];

    //v[4][0] = v[3][0];
    cubeCode[36] = cubeCode[27];
    cubeCode[37] = cubeCode[28];
    cubeCode[38] = cubeCode[29];

    //v[3][0] = v[2][0];
    cubeCode[27] = cubeCode[18];
    cubeCode[28] = cubeCode[19];
    cubeCode[29] = cubeCode[20];

    //v[2][0] = temp;
    cubeCode[18] = temp[0];
    cubeCode[19] = temp[1];
    cubeCode[20] = temp[2];
}

void RubiksCubeProcessor::rotateBackTwiceString() {
    rotateBackString();
    rotateBackString();
}

void RubiksCubeProcessor::rotateLeftString() {
    //rotate90(v[1]);

    int start = 9 * 1;

    std::vector<char> firstTemp = { cubeCode[start],cubeCode[start + 1],cubeCode[start + 5],cubeCode[start + 2] };

    cubeCode[start] = cubeCode[start + 6];
    cubeCode[start + 1] = cubeCode[start + 3];
    cubeCode[start + 2] = firstTemp[0];
    cubeCode[start + 3] = cubeCode[start + 7];
    cubeCode[start + 4] = cubeCode[start + 4];
    cubeCode[start + 5] = firstTemp[1];
    cubeCode[start + 6] = cubeCode[start + 8];
    cubeCode[start + 7] = firstTemp[2];
    cubeCode[start + 8] = firstTemp[3];

    std::vector<char> temp = { cubeCode[9 * 0 + 3 * 0 + 1 * 0],cubeCode[9 * 0 + 3 * 1 + 1 * 0],cubeCode[9 * 0 + 3 * 2 + 1 * 0] };

    cubeCode[9 * 0 + 3 * 0 + 1 * 0] = cubeCode[9 * 4 + 3 * 2 + 1 * 2];
    cubeCode[9 * 0 + 3 * 1 + 1 * 0] = cubeCode[9 * 4 + 3 * 1 + 1 * 2];
    cubeCode[9 * 0 + 3 * 2 + 1 * 0] = cubeCode[9 * 4 + 3 * 0 + 1 * 2];

    cubeCode[9 * 4 + 3 * 0 + 1 * 2] = cubeCode[9 * 5 + 3 * 2 + 1 * 0];
    cubeCode[9 * 4 + 3 * 1 + 1 * 2] = cubeCode[9 * 5 + 3 * 1 + 1 * 0];
    cubeCode[9 * 4 + 3 * 2 + 1 * 2] = cubeCode[9 * 5 + 3 * 0 + 1 * 0];

    cubeCode[9 * 5 + 3 * 0 + 1 * 0] = cubeCode[9 * 2 + 3 * 0 + 1 * 0];
    cubeCode[9 * 5 + 3 * 1 + 1 * 0] = cubeCode[9 * 2 + 3 * 1 + 1 * 0];
    cubeCode[9 * 5 + 3 * 2 + 1 * 0] = cubeCode[9 * 2 + 3 * 2 + 1 * 0];

    cubeCode[9 * 2 + 3 * 0 + 1 * 0] = temp[0];
    cubeCode[9 * 2 + 3 * 1 + 1 * 0] = temp[1];
    cubeCode[9 * 2 + 3 * 2 + 1 * 0] = temp[2];

}

void RubiksCubeProcessor::rotateLeftCCWString() {
    //rotate90CCW(v[1]);

    int start = 9 * 1;

    std::vector<char> firstTemp = { cubeCode[start + 1],cubeCode[start],cubeCode[start + 3],cubeCode[start + 6] };

    cubeCode[start] = cubeCode[start + 2];
    cubeCode[start + 1] = cubeCode[start + 5];
    cubeCode[start + 2] = cubeCode[start + 8];
    cubeCode[start + 3] = firstTemp[0];
    cubeCode[start + 4] = cubeCode[start + 4];
    cubeCode[start + 5] = cubeCode[start + 7];
    cubeCode[start + 6] = firstTemp[1];
    cubeCode[start + 7] = firstTemp[2];
    cubeCode[start + 8] = firstTemp[3];

    std::vector<char> temp = { cubeCode[9 * 0 + 3 * 0 + 1 * 0],cubeCode[9 * 0 + 3 * 1 + 1 * 0],cubeCode[9 * 0 + 3 * 2 + 1 * 0] };


    cubeCode[9 * 0 + 3 * 0 + 1 * 0] = cubeCode[9 * 2 + 3 * 0 + 1 * 0];
    cubeCode[9 * 0 + 3 * 1 + 1 * 0] = cubeCode[9 * 2 + 3 * 1 + 1 * 0];
    cubeCode[9 * 0 + 3 * 2 + 1 * 0] = cubeCode[9 * 2 + 3 * 2 + 1 * 0];

    cubeCode[9 * 2 + 3 * 0 + 1 * 0] = cubeCode[9 * 5 + 3 * 0 + 1 * 0];
    cubeCode[9 * 2 + 3 * 1 + 1 * 0] = cubeCode[9 * 5 + 3 * 1 + 1 * 0];
    cubeCode[9 * 2 + 3 * 2 + 1 * 0] = cubeCode[9 * 5 + 3 * 2 + 1 * 0];

    cubeCode[9 * 5 + 3 * 0 + 1 * 0] = cubeCode[9 * 4 + 3 * 2 + 1 * 2];
    cubeCode[9 * 5 + 3 * 1 + 1 * 0] = cubeCode[9 * 4 + 3 * 1 + 1 * 2];
    cubeCode[9 * 5 + 3 * 2 + 1 * 0] = cubeCode[9 * 4 + 3 * 0 + 1 * 2];

    cubeCode[9 * 4 + 3 * 2 + 1 * 2] = temp[0];
    cubeCode[9 * 4 + 3 * 1 + 1 * 2] = temp[1];
    cubeCode[9 * 4 + 3 * 0 + 1 * 2] = temp[2];

}

void RubiksCubeProcessor::rotateLeftTwiceString() {
    rotateLeftString();
    rotateLeftString();
}

void RubiksCubeProcessor::rotateRightString() {
    //rotate90(v[3]);

    int start = 9 * 3;

    std::vector<char> firstTemp = { cubeCode[start],cubeCode[start + 1],cubeCode[start + 5],cubeCode[start + 2] };

    cubeCode[start] = cubeCode[start + 6];
    cubeCode[start + 1] = cubeCode[start + 3];
    cubeCode[start + 2] = firstTemp[0];
    cubeCode[start + 3] = cubeCode[start + 7];
    cubeCode[start + 4] = cubeCode[start + 4];
    cubeCode[start + 5] = firstTemp[1];
    cubeCode[start + 6] = cubeCode[start + 8];
    cubeCode[start + 7] = firstTemp[2];
    cubeCode[start + 8] = firstTemp[3];

    std::vector<char> temp = { cubeCode[9 * 0 + 3 * 0 + 1 * 2],cubeCode[9 * 0 + 3 * 1 + 1 * 2],cubeCode[9 * 0 + 3 * 2 + 1 * 2] };

    cubeCode[9 * 0 + 3 * 0 + 1 * 2] = cubeCode[9 * 2 + 3 * 0 + 1 * 2];
    cubeCode[9 * 0 + 3 * 1 + 1 * 2] = cubeCode[9 * 2 + 3 * 1 + 1 * 2];
    cubeCode[9 * 0 + 3 * 2 + 1 * 2] = cubeCode[9 * 2 + 3 * 2 + 1 * 2];

    cubeCode[9 * 2 + 3 * 0 + 1 * 2] = cubeCode[9 * 5 + 3 * 0 + 1 * 2];
    cubeCode[9 * 2 + 3 * 1 + 1 * 2] = cubeCode[9 * 5 + 3 * 1 + 1 * 2];
    cubeCode[9 * 2 + 3 * 2 + 1 * 2] = cubeCode[9 * 5 + 3 * 2 + 1 * 2];

    cubeCode[9 * 5 + 3 * 0 + 1 * 2] = cubeCode[9 * 4 + 3 * 2 + 1 * 0];
    cubeCode[9 * 5 + 3 * 1 + 1 * 2] = cubeCode[9 * 4 + 3 * 1 + 1 * 0];
    cubeCode[9 * 5 + 3 * 2 + 1 * 2] = cubeCode[9 * 4 + 3 * 0 + 1 * 0];

    cubeCode[9 * 4 + 3 * 0 + 1 * 0] = temp[2];
    cubeCode[9 * 4 + 3 * 1 + 1 * 0] = temp[1];
    cubeCode[9 * 4 + 3 * 2 + 1 * 0] = temp[0];


}

void RubiksCubeProcessor::rotateRightCCWString() {
    //rotate90CCW(v[3]);

    int start = 9 * 3;

    std::vector<char> firstTemp = { cubeCode[start + 1],cubeCode[start],cubeCode[start + 3],cubeCode[start + 6] };

    cubeCode[start] = cubeCode[start + 2];
    cubeCode[start + 1] = cubeCode[start + 5];
    cubeCode[start + 2] = cubeCode[start + 8];
    cubeCode[start + 3] = firstTemp[0];
    cubeCode[start + 4] = cubeCode[start + 4];
    cubeCode[start + 5] = cubeCode[start + 7];
    cubeCode[start + 6] = firstTemp[1];
    cubeCode[start + 7] = firstTemp[2];
    cubeCode[start + 8] = firstTemp[3];

    std::vector<char> temp = { cubeCode[9 * 0 + 3 * 0 + 1 * 2],cubeCode[9 * 0 + 3 * 1 + 1 * 2],cubeCode[9 * 0 + 3 * 2 + 1 * 2] };


    cubeCode[9 * 0 + 3 * 0 + 1 * 2] = cubeCode[9 * 4 + 3 * 2 + 1 * 0];
    cubeCode[9 * 0 + 3 * 1 + 1 * 2] = cubeCode[9 * 4 + 3 * 1 + 1 * 0];
    cubeCode[9 * 0 + 3 * 2 + 1 * 2] = cubeCode[9 * 4 + 3 * 0 + 1 * 0];

    cubeCode[9 * 4 + 3 * 2 + 1 * 0] = cubeCode[9 * 5 + 3 * 0 + 1 * 2];
    cubeCode[9 * 4 + 3 * 1 + 1 * 0] = cubeCode[9 * 5 + 3 * 1 + 1 * 2];
    cubeCode[9 * 4 + 3 * 0 + 1 * 0] = cubeCode[9 * 5 + 3 * 2 + 1 * 2];

    cubeCode[9 * 5 + 3 * 0 + 1 * 2] = cubeCode[9 * 2 + 3 * 0 + 1 * 2];
    cubeCode[9 * 5 + 3 * 1 + 1 * 2] = cubeCode[9 * 2 + 3 * 1 + 1 * 2];
    cubeCode[9 * 5 + 3 * 2 + 1 * 2] = cubeCode[9 * 2 + 3 * 2 + 1 * 2];

    cubeCode[9 * 2 + 3 * 0 + 1 * 2] = temp[0];
    cubeCode[9 * 2 + 3 * 1 + 1 * 2] = temp[1];
    cubeCode[9 * 2 + 3 * 2 + 1 * 2] = temp[2];

}

void RubiksCubeProcessor::rotateRightTwiceString() {
    rotateRightString();
    rotateRightString();
}

void RubiksCubeProcessor::rotateTopString() {
    //rotate90(v[2]);

    int start = 9 * 2;

    std::vector<char> firstTemp = { cubeCode[start],cubeCode[start + 1],cubeCode[start + 5],cubeCode[start + 2] };

    cubeCode[start] = cubeCode[start + 6];
    cubeCode[start + 1] = cubeCode[start + 3];
    cubeCode[start + 2] = firstTemp[0];
    cubeCode[start + 3] = cubeCode[start + 7];
    cubeCode[start + 4] = cubeCode[start + 4];
    cubeCode[start + 5] = firstTemp[1];
    cubeCode[start + 6] = cubeCode[start + 8];
    cubeCode[start + 7] = firstTemp[2];
    cubeCode[start + 8] = firstTemp[3];

    std::vector<char> temp = { cubeCode[9 * 1 + 3 * 0 + 1 * 2],cubeCode[9 * 1 + 3 * 1 + 1 * 2],cubeCode[9 * 1 + 3 * 2 + 1 * 2] };

    cubeCode[9 * 1 + 3 * 0 + 1 * 2] = cubeCode[9 * 5 + 3 * 0 + 1 * 0];
    cubeCode[9 * 1 + 3 * 1 + 1 * 2] = cubeCode[9 * 5 + 3 * 0 + 1 * 1];
    cubeCode[9 * 1 + 3 * 2 + 1 * 2] = cubeCode[9 * 5 + 3 * 0 + 1 * 2];

    cubeCode[9 * 5 + 3 * 0 + 1 * 0] = cubeCode[9 * 3 + 3 * 2 + 1 * 0];
    cubeCode[9 * 5 + 3 * 0 + 1 * 1] = cubeCode[9 * 3 + 3 * 1 + 1 * 0];
    cubeCode[9 * 5 + 3 * 0 + 1 * 2] = cubeCode[9 * 3 + 3 * 0 + 1 * 0];

    cubeCode[9 * 3 + 3 * 0 + 1 * 0] = cubeCode[9 * 0 + 3 * 2 + 1 * 0];
    cubeCode[9 * 3 + 3 * 1 + 1 * 0] = cubeCode[9 * 0 + 3 * 2 + 1 * 1];
    cubeCode[9 * 3 + 3 * 2 + 1 * 0] = cubeCode[9 * 0 + 3 * 2 + 1 * 2];

    cubeCode[9 * 0 + 3 * 2 + 1 * 0] = temp[2];
    cubeCode[9 * 0 + 3 * 2 + 1 * 1] = temp[1];
    cubeCode[9 * 0 + 3 * 2 + 1 * 2] = temp[0];


}

void RubiksCubeProcessor::rotateTopCCWString() {
    //rotate90CCW(v[2]);

    int start = 9 * 2;

    std::vector<char> firstTemp = { cubeCode[start + 1],cubeCode[start],cubeCode[start + 3],cubeCode[start + 6] };

    cubeCode[start] = cubeCode[start + 2];
    cubeCode[start + 1] = cubeCode[start + 5];
    cubeCode[start + 2] = cubeCode[start + 8];
    cubeCode[start + 3] = firstTemp[0];
    cubeCode[start + 4] = cubeCode[start + 4];
    cubeCode[start + 5] = cubeCode[start + 7];
    cubeCode[start + 6] = firstTemp[1];
    cubeCode[start + 7] = firstTemp[2];
    cubeCode[start + 8] = firstTemp[3];

    std::vector<char> temp = { cubeCode[9 * 1 + 3 * 0 + 1 * 2],cubeCode[9 * 1 + 3 * 1 + 1 * 2],cubeCode[9 * 1 + 3 * 2 + 1 * 2] };

    cubeCode[9 * 1 + 3 * 0 + 1 * 2] = cubeCode[9 * 0 + 3 * 2 + 1 * 2];
    cubeCode[9 * 1 + 3 * 1 + 1 * 2] = cubeCode[9 * 0 + 3 * 2 + 1 * 1];
    cubeCode[9 * 1 + 3 * 2 + 1 * 2] = cubeCode[9 * 0 + 3 * 2 + 1 * 0];

    cubeCode[9 * 0 + 3 * 2 + 1 * 2] = cubeCode[9 * 3 + 3 * 2 + 1 * 0];
    cubeCode[9 * 0 + 3 * 2 + 1 * 1] = cubeCode[9 * 3 + 3 * 1 + 1 * 0];
    cubeCode[9 * 0 + 3 * 2 + 1 * 0] = cubeCode[9 * 3 + 3 * 0 + 1 * 0];

    cubeCode[9 * 3 + 3 * 2 + 1 * 0] = cubeCode[9 * 5 + 3 * 0 + 1 * 0];
    cubeCode[9 * 3 + 3 * 1 + 1 * 0] = cubeCode[9 * 5 + 3 * 0 + 1 * 1];
    cubeCode[9 * 3 + 3 * 0 + 1 * 0] = cubeCode[9 * 5 + 3 * 0 + 1 * 2];

    cubeCode[9 * 5 + 3 * 0 + 1 * 0] = temp[0];
    cubeCode[9 * 5 + 3 * 0 + 1 * 1] = temp[1];
    cubeCode[9 * 5 + 3 * 0 + 1 * 2] = temp[2];


}

void RubiksCubeProcessor::rotateTopTwiceString() {
    rotateTopString();
    rotateTopString();
}

void RubiksCubeProcessor::rotateBottomString() {
    //rotate90(v[4]);

    int start = 9 * 4;

    std::vector<char> firstTemp = { cubeCode[start],cubeCode[start + 1],cubeCode[start + 5],cubeCode[start + 2] };

    cubeCode[start] = cubeCode[start + 6];
    cubeCode[start + 1] = cubeCode[start + 3];
    cubeCode[start + 2] = firstTemp[0];
    cubeCode[start + 3] = cubeCode[start + 7];
    cubeCode[start + 4] = cubeCode[start + 4];
    cubeCode[start + 5] = firstTemp[1];
    cubeCode[start + 6] = cubeCode[start + 8];
    cubeCode[start + 7] = firstTemp[2];
    cubeCode[start + 8] = firstTemp[3];

    std::vector<char> temp = { cubeCode[9 * 1 + 3 * 0 + 1 * 0],cubeCode[9 * 1 + 3 * 1 + 1 * 0],cubeCode[9 * 1 + 3 * 2 + 1 * 0] };

    cubeCode[9 * 1 + 3 * 0 + 1 * 0] = cubeCode[9 * 0 + 3 * 0 + 1 * 2];
    cubeCode[9 * 1 + 3 * 1 + 1 * 0] = cubeCode[9 * 0 + 3 * 0 + 1 * 1];
    cubeCode[9 * 1 + 3 * 2 + 1 * 0] = cubeCode[9 * 0 + 3 * 0 + 1 * 0];

    cubeCode[9 * 0 + 3 * 0 + 1 * 0] = cubeCode[9 * 3 + 3 * 0 + 1 * 2];
    cubeCode[9 * 0 + 3 * 0 + 1 * 1] = cubeCode[9 * 3 + 3 * 1 + 1 * 2];
    cubeCode[9 * 0 + 3 * 0 + 1 * 2] = cubeCode[9 * 3 + 3 * 2 + 1 * 2];

    cubeCode[9 * 3 + 3 * 0 + 1 * 2] = cubeCode[9 * 5 + 3 * 2 + 1 * 2];
    cubeCode[9 * 3 + 3 * 1 + 1 * 2] = cubeCode[9 * 5 + 3 * 2 + 1 * 1];
    cubeCode[9 * 3 + 3 * 2 + 1 * 2] = cubeCode[9 * 5 + 3 * 2 + 1 * 0];

    cubeCode[9 * 5 + 3 * 2 + 1 * 0] = temp[0];
    cubeCode[9 * 5 + 3 * 2 + 1 * 1] = temp[1];
    cubeCode[9 * 5 + 3 * 2 + 1 * 2] = temp[2];

}

void RubiksCubeProcessor::rotateBottomCCWString() {
    //rotate90CCW(v[4]);

    int start = 9 * 4;

    std::vector<char> firstTemp = { cubeCode[start + 1],cubeCode[start],cubeCode[start + 3],cubeCode[start + 6] };

    cubeCode[start] = cubeCode[start + 2];
    cubeCode[start + 1] = cubeCode[start + 5];
    cubeCode[start + 2] = cubeCode[start + 8];
    cubeCode[start + 3] = firstTemp[0];
    cubeCode[start + 4] = cubeCode[start + 4];
    cubeCode[start + 5] = cubeCode[start + 7];
    cubeCode[start + 6] = firstTemp[1];
    cubeCode[start + 7] = firstTemp[2];
    cubeCode[start + 8] = firstTemp[3];

    std::vector<char> temp = { cubeCode[9 * 1 + 3 * 0 + 1 * 0],cubeCode[9 * 1 + 3 * 1 + 1 * 0],cubeCode[9 * 1 + 3 * 2 + 1 * 0] };

    cubeCode[9 * 1 + 3 * 0 + 1 * 0] = cubeCode[9 * 5 + 3 * 2 + 1 * 0];
    cubeCode[9 * 1 + 3 * 1 + 1 * 0] = cubeCode[9 * 5 + 3 * 2 + 1 * 1];
    cubeCode[9 * 1 + 3 * 2 + 1 * 0] = cubeCode[9 * 5 + 3 * 2 + 1 * 2];

    cubeCode[9 * 5 + 3 * 2 + 1 * 0] = cubeCode[9 * 3 + 3 * 2 + 1 * 2];
    cubeCode[9 * 5 + 3 * 2 + 1 * 1] = cubeCode[9 * 3 + 3 * 1 + 1 * 2];
    cubeCode[9 * 5 + 3 * 2 + 1 * 2] = cubeCode[9 * 3 + 3 * 0 + 1 * 2];

    cubeCode[9 * 3 + 3 * 0 + 1 * 2] = cubeCode[9 * 0 + 3 * 0 + 1 * 0];
    cubeCode[9 * 3 + 3 * 1 + 1 * 2] = cubeCode[9 * 0 + 3 * 0 + 1 * 1];
    cubeCode[9 * 3 + 3 * 2 + 1 * 2] = cubeCode[9 * 0 + 3 * 0 + 1 * 2];

    cubeCode[9 * 0 + 3 * 0 + 1 * 0] = temp[2];
    cubeCode[9 * 0 + 3 * 0 + 1 * 1] = temp[1];
    cubeCode[9 * 0 + 3 * 0 + 1 * 2] = temp[0];

}

void RubiksCubeProcessor::rotateBottomTwiceString() {
    rotateBottomString();
    rotateBottomString();
}

void RubiksCubeProcessor::loadInEdgeMap(std::map<std::vector<char>, int>& m) {

    std::vector<std::vector<char>> c;
    std::vector<int> goodness;

    // Edge 1
    // returnEdge[0] = cubeCode[46];
    // returnEdge[1] = cubeCode[25];
    goodness.push_back(!determineEdgeGoodness(cubeCode[25], cubeCode[46], true));
    c.push_back({ cubeCode[25],cubeCode[46] });


    // Edge 2
    // returnEdge[2] = cubeCode[48];
    // returnEdge[3] = cubeCode[16];
    goodness.push_back(!determineEdgeGoodness(cubeCode[48], cubeCode[16], false));
    c.push_back({ cubeCode[48],cubeCode[16] });

    // Edge 3
    // returnEdge[4] = cubeCode[50];
    // returnEdge[5] = cubeCode[34];
    goodness.push_back(!determineEdgeGoodness(cubeCode[50], cubeCode[34], false));
    c.push_back({ cubeCode[50],cubeCode[34] });

    // Edge 4
    // returnEdge[6] = cubeCode[52];
    // returnEdge[7] = cubeCode[43];
    goodness.push_back(!determineEdgeGoodness(cubeCode[43], cubeCode[52], true));
    c.push_back({ cubeCode[43],cubeCode[52] });

    // Edge 5
    // returnEdge[8] = cubeCode[19];
    // returnEdge[9] = cubeCode[7];
    goodness.push_back(!determineEdgeGoodness(cubeCode[19], cubeCode[7], true));
    c.push_back({ cubeCode[19],cubeCode[7] });

    // Edge 6
    // returnEdge[10] = cubeCode[5];
    // returnEdge[11] = cubeCode[28];
    goodness.push_back(!determineEdgeGoodness(cubeCode[5], cubeCode[28], false));
    c.push_back({ cubeCode[5],cubeCode[28] });

    // Edge 7
    // returnEdge[12] = cubeCode[3];
    // returnEdge[13] = cubeCode[10];
    goodness.push_back(!determineEdgeGoodness(cubeCode[3], cubeCode[10], false));
    c.push_back({ cubeCode[3],cubeCode[10] });

    // Edge 8
    // returnEdge[14] = cubeCode[1];
    // returnEdge[15] = cubeCode[37];
    goodness.push_back(!determineEdgeGoodness(cubeCode[37], cubeCode[1], true));
    c.push_back({ cubeCode[37],cubeCode[1] });

    // Edge 9
    // returnEdge[16] = cubeCode[21];
    // returnEdge[17] = cubeCode[14];
    goodness.push_back(!determineEdgeGoodness(cubeCode[21], cubeCode[14], true));
    c.push_back({ cubeCode[21],cubeCode[14] });

    // Edge 10
    // returnEdge[18] = cubeCode[23];
    // returnEdge[19] = cubeCode[30];
    goodness.push_back(!determineEdgeGoodness(cubeCode[23], cubeCode[30], true));
    c.push_back({ cubeCode[23],cubeCode[30] });

    // Edge 11
    // returnEdge[20] = cubeCode[12];
    // returnEdge[21] = cubeCode[41];
    goodness.push_back(!determineEdgeGoodness(cubeCode[41], cubeCode[12], true));
    c.push_back({ cubeCode[41],cubeCode[12] });

    // Edge 12
    // returnEdge[22] = cubeCode[32];
    // returnEdge[23] = cubeCode[39];
    goodness.push_back(!determineEdgeGoodness(cubeCode[39], cubeCode[32], true));
    c.push_back({ cubeCode[39],cubeCode[32] });

    int count = 0;

    for (auto& i : c) {
        std::sort(i.begin(), i.end());
        m.insert({ i,goodness[count] });
        count++;
    }
}

void RubiksCubeProcessor::loadInEdgePermutation(std::unordered_map<int, std::vector<char>>& mPerm)
{

    std::vector<std::vector<char>> c;
    int count = 0;

    //std::vector<std::string> edgeNames = { edge1, edge10, edge5, edge9, edge4, edge12, edge8, edge11, edge3, edge6, edge7, edge2 };

    // Edge 1
    // returnEdge[0] = cubeCode[46];
    // returnEdge[1] = cubeCode[25];
    //goodness.push_back(determineEdgeGoodness(cubeCode[25],cubeCode[46],true));
    c.push_back({ cubeCode[25],cubeCode[46] });
    std::sort(c.back().begin(), c.back().end());
    mPerm.insert({ count,c.back() });
    count++;

    // Edge 10
    // returnEdge[18] = cubeCode[23];
    // returnEdge[19] = cubeCode[30];
    c.push_back({ cubeCode[23],cubeCode[30] });
    std::sort(c.back().begin(), c.back().end());
    mPerm.insert({ count,c.back() });
    count++;

    // Edge 5
    // returnEdge[8] = cubeCode[19];
    // returnEdge[9] = cubeCode[7];
    c.push_back({ cubeCode[19],cubeCode[7] });
    std::sort(c.back().begin(), c.back().end());
    mPerm.insert({ count,c.back() });
    count++;

    // Edge 9
    // returnEdge[16] = cubeCode[21];
    // returnEdge[17] = cubeCode[14];
    c.push_back({ cubeCode[21],cubeCode[14] });
    std::sort(c.back().begin(), c.back().end());
    mPerm.insert({ count,c.back() });
    count++;

    // Edge 4
    // returnEdge[6] = cubeCode[52];
    // returnEdge[7] = cubeCode[43];
    c.push_back({ cubeCode[43],cubeCode[52] });
    std::sort(c.back().begin(), c.back().end());
    mPerm.insert({ count,c.back() });
    count++;

    // Edge 12
    // returnEdge[22] = cubeCode[32];
    // returnEdge[23] = cubeCode[39];
    c.push_back({ cubeCode[39],cubeCode[32] });
    std::sort(c.back().begin(), c.back().end());
    mPerm.insert({ count,c.back() });
    count++;

    // Edge 8
    // returnEdge[14] = cubeCode[1];
    // returnEdge[15] = cubeCode[37];
    c.push_back({ cubeCode[37],cubeCode[1] });
    std::sort(c.back().begin(), c.back().end());
    mPerm.insert({ count,c.back() });
    count++;

    // Edge 11
    // returnEdge[20] = cubeCode[12];
    // returnEdge[21] = cubeCode[41];
    c.push_back({ cubeCode[41],cubeCode[12] });
    std::sort(c.back().begin(), c.back().end());
    mPerm.insert({ count,c.back() });
    count++;

    // Edge 3
    // returnEdge[4] = cubeCode[50];
    // returnEdge[5] = cubeCode[34];
    c.push_back({ cubeCode[50],cubeCode[34] });
    std::sort(c.back().begin(), c.back().end());
    mPerm.insert({ count,c.back() });
    count++;

    // Edge 6
    // returnEdge[10] = cubeCode[5];
    // returnEdge[11] = cubeCode[28];
    c.push_back({ cubeCode[5],cubeCode[28] });
    std::sort(c.back().begin(), c.back().end());
    mPerm.insert({ count,c.back() });
    count++;

    // Edge 7
    // returnEdge[12] = cubeCode[3];
    // returnEdge[13] = cubeCode[10];
    c.push_back({ cubeCode[3],cubeCode[10] });
    std::sort(c.back().begin(), c.back().end());
    mPerm.insert({ count,c.back() });
    count++;

    // Edge 2
    // returnEdge[2] = cubeCode[48];
    // returnEdge[3] = cubeCode[16];
    c.push_back({ cubeCode[48],cubeCode[16] });
    std::sort(c.back().begin(), c.back().end());
    mPerm.insert({ count,c.back() });
    count++;

    // Debug
    if (mPerm.size() != 12) {
        std::cout << "mPerm.size() = " << mPerm.size() << std::endl;
        std::cout << "s = " << cubeCode << std::endl;
    }

}

void RubiksCubeProcessor::loadInCornerMap(std::map<std::vector<char>, int>& m)
{

    std::vector<std::vector<char>> c;
    std::vector<int> orientation;

    // returnCorner[0] = cubeCode[24];
    // returnCorner[1] = cubeCode[17]; // if top, then 1
    // returnCorner[2] = cubeCode[45]; // if top, then 2
    orientation.push_back(determineCornerGoodness(cubeCode[24], cubeCode[17], cubeCode[45]));
    c.push_back({ cubeCode[24],cubeCode[17],cubeCode[45] });

    // Corner 2
    // returnCorner[3] = cubeCode[26];
    // returnCorner[4] = cubeCode[33]; // if top, then 2
    // returnCorner[5] = cubeCode[47]; // if top, then 1
    orientation.push_back(determineCornerGoodness(cubeCode[26], cubeCode[47], cubeCode[33]));
    c.push_back({ cubeCode[26],cubeCode[33],cubeCode[47] });

    // Corner 3
    // returnCorner[6] = cubeCode[51]; // if top, then 1
    // returnCorner[7] = cubeCode[15]; // if top, then 2
    // returnCorner[8] = cubeCode[44];
    orientation.push_back(determineCornerGoodness(cubeCode[44], cubeCode[51], cubeCode[15]));
    c.push_back({ cubeCode[15],cubeCode[44],cubeCode[51] });

    // Corner 4
    // returnCorner[9] = cubeCode[53]; // if top, then 2
    // returnCorner[10] = cubeCode[35]; // if top, then 1
    // returnCorner[11] = cubeCode[42];
    orientation.push_back(determineCornerGoodness(cubeCode[42], cubeCode[35], cubeCode[53]));
    c.push_back({ cubeCode[35],cubeCode[42],cubeCode[53] });

    // Corner 5
    // returnCorner[12] = cubeCode[18];
    // returnCorner[13] = cubeCode[11]; // if top, then 2
    // returnCorner[14] = cubeCode[6]; // if top, then 1
    orientation.push_back(determineCornerGoodness(cubeCode[18], cubeCode[6], cubeCode[11]));
    c.push_back({ cubeCode[18],cubeCode[11],cubeCode[6] });

    // Corner 6
    // returnCorner[15] = cubeCode[20];
    // returnCorner[16] = cubeCode[27]; // if top, then 1
    // returnCorner[17] = cubeCode[8]; // if top, then 2
    orientation.push_back(determineCornerGoodness(cubeCode[20], cubeCode[27], cubeCode[8]));
    c.push_back({ cubeCode[20],cubeCode[27],cubeCode[8] });

    // Corner 7
    // returnCorner[18] = cubeCode[0]; // if top, then 2
    // returnCorner[19] = cubeCode[9]; // if top, then 1
    // returnCorner[20] = cubeCode[38];
    orientation.push_back(determineCornerGoodness(cubeCode[38], cubeCode[9], cubeCode[0]));
    c.push_back({ cubeCode[0],cubeCode[9],cubeCode[38] });

    // Corner 8
    // returnCorner[21] = cubeCode[2]; // if top, then 1
    // returnCorner[22] = cubeCode[29]; // if top, then 2
    // returnCorner[23] = cubeCode[36];
    orientation.push_back(determineCornerGoodness(cubeCode[36], cubeCode[2], cubeCode[29]));
    c.push_back({ cubeCode[2],cubeCode[29],cubeCode[36] });

    int count = 0;

    for (auto& i : c) {
        std::sort(i.begin(), i.end());
        m.insert({ i,orientation[count] });
        count++;
    }
}

void RubiksCubeProcessor::loadInCornerPermutation(std::unordered_map<int, std::vector<char>>& mPerm)
{
    std::vector<std::vector<char>> c;

    //std::vector<std::string> cornerNames = { corner2, corner6, corner3, corner4, corner5, corner1, corner8, corner7 };

    int count = 0;

    // Corner 2
    // returnCorner[3] = cubeCode[26];
    // returnCorner[4] = cubeCode[33]; // if top, then 2
    // returnCorner[5] = cubeCode[47]; // if top, then 1
    c.push_back({ cubeCode[26],cubeCode[33],cubeCode[47] });
    std::sort(c.back().begin(), c.back().end());
    mPerm.insert({ count,c.back() });
    count++;

    // Corner 6
    // returnCorner[15] = cubeCode[20];
    // returnCorner[16] = cubeCode[27]; // if top, then 1
    // returnCorner[17] = cubeCode[8]; // if top, then 2
    c.push_back({ cubeCode[20],cubeCode[27],cubeCode[8] });
    std::sort(c.back().begin(), c.back().end());
    mPerm.insert({ count,c.back() });
    count++;

    // Corner 3
    // returnCorner[6] = cubeCode[51]; // if top, then 1
    // returnCorner[7] = cubeCode[15]; // if top, then 2
    // returnCorner[8] = cubeCode[44];
    c.push_back({ cubeCode[15],cubeCode[44],cubeCode[51] });
    std::sort(c.back().begin(), c.back().end());
    mPerm.insert({ count,c.back() });
    count++;

    // Debug
    //std::cout << "{cubeCode[15], cubeCode[44], cubeCode[51] } = {" << cubeCode[15] << "," << cubeCode[44] << "," << cubeCode[51] << "}" << std::endl;

    // Corner 4
    // returnCorner[9] = cubeCode[53]; // if top, then 2
    // returnCorner[10] = cubeCode[35]; // if top, then 1
    // returnCorner[11] = cubeCode[42];
    c.push_back({ cubeCode[35],cubeCode[42],cubeCode[53] });
    std::sort(c.back().begin(), c.back().end());
    mPerm.insert({ count,c.back() });
    count++;

    // Corner 5
    // returnCorner[12] = cubeCode[18];
    // returnCorner[13] = cubeCode[11]; // if top, then 2
    // returnCorner[14] = cubeCode[6]; // if top, then 1
    c.push_back({ cubeCode[18],cubeCode[11],cubeCode[6] });
    std::sort(c.back().begin(), c.back().end());
    mPerm.insert({ count,c.back() });
    count++;

    // Corner 1
    // returnCorner[0] = cubeCode[24];
    // returnCorner[1] = cubeCode[17]; // if top, then 1
    // returnCorner[2] = cubeCode[45]; // if top, then 2
    c.push_back({ cubeCode[24],cubeCode[17],cubeCode[45] });
    std::sort(c.back().begin(), c.back().end());
    mPerm.insert({ count,c.back() });
    count++;

    // Corner 8
    // returnCorner[21] = cubeCode[2]; // if top, then 1
    // returnCorner[22] = cubeCode[29]; // if top, then 2
    // returnCorner[23] = cubeCode[36];
    c.push_back({ cubeCode[2],cubeCode[29],cubeCode[36] });
    std::sort(c.back().begin(), c.back().end());
    mPerm.insert({ count,c.back() });
    count++;

    // Corner 7
    // returnCorner[18] = cubeCode[0]; // if top, then 2
    // returnCorner[19] = cubeCode[9]; // if top, then 1
    // returnCorner[20] = cubeCode[38];
    c.push_back({ cubeCode[0],cubeCode[9],cubeCode[38] });
    std::sort(c.back().begin(), c.back().end());
    mPerm.insert({ count,c.back() });
    count++;
}

bool RubiksCubeProcessor::unevenColorAmount()
{
    std::vector<int> colors(6, 0);
    for (auto i : cubeCode)
    {
        if (i == 'W') {
            cubeCode[0]++;
            if (cubeCode[0] > 9) {
                std::cout << "Uneven White" << std::endl;
                return true;
            }
        }
        else if (i == 'R')
        {
            cubeCode[1]++;
            if (cubeCode[1] > 9) {
                std::cout << "Uneven Red" << std::endl;
                return true;
            }
        }
        else if (i == 'B') {
            cubeCode[2]++;
            if (cubeCode[2] > 9) {
                std::cout << "Uneven Blue" << std::endl;
                return true;
            }
        }
        else if (i == 'O') {
            cubeCode[3]++;
            if (cubeCode[3] > 9) {
                std::cout << "Uneven Orange" << std::endl;
                return true;
            }
        }
        else if (i == 'G') {
            cubeCode[4]++;
            if (cubeCode[4] > 9) {
                std::cout << "Uneven Green" << std::endl;
                return true;
            }
        }
        else {
            cubeCode[5]++;
            if (cubeCode[5] > 9) {
                std::cout << "Uneven Yellow" << std::endl;
                return true;
            }
        }
    }

    return false;
}

void RubiksCubeProcessor::rotateCubeString(int moveNumber) {
    switch (moveNumber) {
    case 0:
        rotateFrontString();
        break;
    case 1:
        rotateFrontCCWString();
        break;
    case 2:
        rotateBackString();
        break;
    case 3:
        rotateBackCCWString();
        break;
    case 4:
        rotateLeftString();
        break;
    case 5:
        rotateLeftCCWString();
        break;
    case 6:
        rotateRightString();
        break;
    case 7:
        rotateRightCCWString();
        break;
    case 8:
        rotateTopString();
        break;
    case 9:
        rotateTopCCWString();
        break;
    case 10:
        rotateBottomString();
        break;
    case 11:
        rotateBottomCCWString();
        break;
    case 12:
        rotateFrontTwiceString();
        break;
    case 13:
        rotateBackTwiceString();
        break;
    case 14:
        rotateLeftTwiceString();
        break;
    case 15:
        rotateRightTwiceString();
        break;
    case 16:
        rotateTopTwiceString();
        break;
    case 17:
        rotateBottomTwiceString();
        break;
    }
}

bool RubiksCubeProcessor::determineEdgeGoodness(char face1, char face2, bool nonMiddleEdge = true)
{
    if (nonMiddleEdge) {
        if (face1 == 'O' || face1 == 'R')
        {

            // Debug
            //std::cout << "T/B OR -> {" << face1 << "," << face2 << "} -> False" << std::endl;

            return false;
        }
        else if (face1 == 'B' || face1 == 'G')
        {

            // Debug
            //std::cout << "T/B BG -> {" << face1 << "," << face2 << "} -> True" << std::endl;

            return true;
        }
        else if (face1 == 'Y' || face1 == 'W')
        {
            if (face2 == 'B' || face2 == 'G')
            {

                // Debug
                //std::cout << "T/B YW to BG -> {" << face1 << "," << face2 << "} -> False" << std::endl;

                return false;
            }
            else {

                // Debug
                //std::cout << "T/B YW to OR -> {" << face1 << "," << face2 << "} -> True" << std::endl;

                return true;
            }
        }
        else {
            return true;
        }
    }
    else {
        if (face1 == 'O' || face1 == 'R')
        {

            // Debug
            //std::cout << "F/B OR -> {" << face1 << "," << face2 << "} -> False" << std::endl;

            return false;
        }
        else if (face1 == 'B' || face1 == 'G')
        {

            // Debug
            //std::cout << "F/B BG -> {" << face1 << "," << face2 << "} -> True" << std::endl;

            return true;
        }
        else if (face1 == 'Y' || face1 == 'W')
        {
            if (face2 == 'B' || face2 == 'G')
            {

                // Debug
                //std::cout << "F/B YW to BG -> {" << face1 << "," << face2 << "} -> False" << std::endl;

                return false;
            }
            else {


                // Debug
                //std::cout << "F/B YW to OR -> {" << face1 << "," << face2 << "} -> True" << std::endl;
                return true;
            }
        }
        else {
            return true;
        }
    }
}

int RubiksCubeProcessor::determineCornerGoodness(char face1, char face2, char face3)
{
    if (face1 == 'B' || face1 == 'G') {
        return 0;
    }
    else if (face2 == 'B' || face2 == 'G') {
        return 1;
    }
    else {
        return 2;
    }
}

void RubiksCubeProcessor::rotateCubeRandom(std::vector<int>& rotationHistory, std::unordered_map<int, std::vector<int>> movesAndOpposites)
{
    int number = rand() % 12;
    int lastRotation = -1;

    if (!rotationHistory.empty()) {
        lastRotation = movesAndOpposites.find(rotationHistory.back())->second[0];
    }

    while (number == lastRotation) {
        number = rand() % 12;
    }

    // Debug
    std::cout << "number = " << number << std::endl;

    rotateCubeString(number);
    rotationHistory.push_back(number);

}

void RubiksCubeProcessor::updateEdgeMapAndPermutation(std::map<std::vector<char>, int>& edgeMap, std::unordered_map<int, std::vector<char>>& edgePermutation,
    std::map<std::vector<char>, std::string>& edgeFinderMap, std::vector<std::string>& edgeNames,
    std::vector<int>& edgePos, std::vector<int>& edgeOrient)
{
    loadInEdgeMap(edgeMap);
    loadInEdgePermutation(edgePermutation);

    for (int i = 0; i < edgePos.size(); i++)
    {
        std::string edge = edgeFinderMap[edgePermutation[i]];

        int count = 0;
        for (int j = 0; j < edgeNames.size(); j++)
        {
            if (edgeNames[j] == edge)
            {
                break;
            }

            count++;
        }

        edgePos[i] = count;
        edgeOrient[i] = edgeMap[edgePermutation[i]];
    }

}

void RubiksCubeProcessor::updateCornerMapAndPermutation(std::map<std::vector<char>, int>& cornerMap, std::unordered_map<int, std::vector<char>>& cornerPermutation,
    std::map<std::vector<char>, std::string>& cornerFinderMap, std::vector<std::string>& cornerNames,
    std::vector<int>& cornerPos, std::vector<int>& cornerOrient)
{
    loadInCornerMap(cornerMap);
    loadInCornerPermutation(cornerPermutation);

    // Debug
    //std::cout << "Corner Permutations: " << std::endl;
    //for (auto a = cornerPermutation.begin(); a != cornerPermutation.end(); a++)
    //{
    //    for (auto b : a->second)
    //    {
    //        std::cout << b << ", ";
    //    }

    //    if (a->second[0] == 'G' && a->second[1] == 'G' && a->second[2] == 'R')
    //    {
    //        std::cout << "-> " << a->first;
    //    }

    //    std::cout << std::endl;

    //}

    for (int i = 0; i < cornerPos.size(); i++)
    {
        std::string corner = cornerFinderMap[cornerPermutation[i]];

        int count = 0;
        for (int j = 0; j < cornerNames.size(); j++)
        {
            if (cornerNames[j] == corner)
            {
                break;
            }

            count++;
        }

        cornerPos[i] = count;
        cornerOrient[i] = cornerMap[cornerPermutation[i]];
    }

}

int RubiksCubeProcessor::translateRotationMove(std::string s)
{

    switch (s[0]) {
    case 'F':
        if (s[1] == '1')
        {
            return 0;
        }
        else if (s[1] == '2')
        {
            return 12;
        }
        else {
            return 1;
        }
        break;
    case 'B':
        if (s[1] == '1')
        {
            return 2;
        }
        else if (s[1] == '2')
        {
            return 13;
        }
        else {
            return 3;
        }
        break;
    case 'L':
        if (s[1] == '1')
        {
            return 4;
        }
        else if (s[1] == '2')
        {
            return 14;
        }
        else {
            return 5;
        }
        break;
    case 'R':
        if (s[1] == '1')
        {
            return 6;
        }
        else if (s[1] == '2')
        {
            return 15;
        }
        else {
            return 7;
        }
        break;
    case 'U':
        if (s[1] == '1')
        {
            return 8;
        }
        else if (s[1] == '2')
        {
            return 16;
        }
        else {
            return 9;
        }
        break;
    case 'D':
        if (s[1] == '1')
        {
            return 10;
        }
        else if (s[1] == '2')
        {
            return 17;
        }
        else {
            return 11;
        }
        break;
    }

    return -1;

}

void RubiksCubeProcessor::loadPhaseTable(std::string fileName, std::unordered_map<int64_t, std::vector<int>>& phase1Map)
{
    std::ifstream inFile;
    inFile.open(fileName);


    if (!inFile.is_open()) {
        std::cout << "Could not open file" << std::endl;
        return;
    }

    std::string entireLine = "";

    while (getline(inFile, entireLine))
    {
        std::istringstream is(entireLine);

        int64_t num;
        is >> num;

        std::string moves;
        is >> moves;

        std::vector<int> moveNums = {};

        if (moves != "E") {
            for (int i = 0; i < moves.size() / 2; i++)
            {
                std::string temp = "";
                temp += moves[i * 2];
                temp += moves[i * 2 + 1];

                moveNums.push_back(translateRotationMove(temp));
            }
        }

        phase1Map.insert({ num,moveNums });

    }

}

int64_t	RubiksCubeProcessor::idPhase1(std::vector<int> edgeOrient) {
    int64_t id = 0;
    for (int i = 0; i < 12; i++)
    {
        id <<= 1;
        id += edgeOrient[i];
    }
    return id;
}

int64_t	RubiksCubeProcessor::idPhase2(std::vector<int> cornerOrient, std::vector<int> edgePos) {
    int64_t id = 0;
    for (int i = 0; i < 8; i++)
    {
        id <<= 2;
        id += cornerOrient[i];
    }
    for (int i = 0; i < 12; i++) {
        id <<= 2;
        if (edgePos[i] < 8)
            id++;
    }
    return id;
}

int64_t	RubiksCubeProcessor::idPhase3(std::vector<std::string> cornerNames, std::vector<int> cornerOrient, std::vector<int> cornerPos,
    std::vector<std::string> edgeNames, std::vector<int> edgeOrient, std::vector<int> edgePos)
{
    //string faces = "FRUBLD";
    std::string faces = "YOBWRG";

    int64_t id = 0;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 3; j++) {
            id <<= 1;
            char t = cornerNames[cornerPos[i]][(cornerOrient[i] + j) % 3];
            if (!(t == cornerNames[i][j] ||
                t == faces[(faces.find(cornerNames[i][j]) + 3) % 6])) {
                id++;
            }
        }
    }
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 2; j++) {
            id <<= 1;
            char t = edgeNames[edgePos[i]][(edgeOrient[i] + j) % 2];
            if (!(t == edgeNames[i][j] ||
                t == faces[(faces.find(edgeNames[i][j]) + 3) % 6])) {
                id++;
            }
        }
    }
    for (int i = 0; i < 8; i++)
    {
        id <<= 1;
        if (cornerPos[i] % 4 != i % 4) {
            id++;
        }
    }
    id <<= 1;
    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 8; j++) {
            id ^= cornerPos[i] > cornerPos[j];
        }
    }
    return id;
}

int64_t	RubiksCubeProcessor::idPhase4(std::vector<std::string> cornerNames, std::vector<int> cornerOrient, std::vector<int> cornerPos,
    std::vector<std::string> edgeNames, std::vector<int> edgeOrient, std::vector<int> edgePos)
{
    //string faces = "FRUBLD";
    std::string faces = "YOBWRG";

    int64_t id = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            id <<= 1;
            char t = cornerNames[cornerPos[i]][(/*cornerOrient[i]*/0 + j) % 3];
            if (t == faces[(faces.find(cornerNames[i][j]) + 3) % 6]) {
                id++;
            }
        }
    }

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 2; j++) {
            id <<= 1;
            char t = edgeNames[edgePos[i]][(/*edgeOrient[i]*/0 + j) % 2];
            if (t == faces[(faces.find(edgeNames[i][j]) + 3) % 6]) {
                id++;
            }
        }
    }
    return id;
}

void RubiksCubeProcessor::printOrientationAndPermutationInfo()
{
    std::cout << "string = " << cubeCode << std::endl;
    std::cout << std::endl;
    std::cout << "Corner Position and Orientation: " << std::endl;
    for (int i = 0; i < cornerPos.size(); i++)
    {
        std::cout << i << ": " << cornerPos[i] << " -> Orientation: " << cornerOrientation[i] << std::endl;
    }
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "Edge Position and Orientation: " << std::endl;
    for (int i = 0; i < edgePos.size(); i++)
    {
        std::cout << i << ": " << edgePos[i] << " -> Orientation: " << edgeOrientation[i] << std::endl;
    }
    std::cout << std::endl;
}

std::vector<int> RubiksCubeProcessor::solveMoves()
{
    std::vector<int> theMoves;

    std::string oldCubeCode = cubeCode;

    cornerMap.clear();
    cornerPermutation.clear();

    edgeMap.clear();
    edgePermutation.clear();

    updateCornerMapAndPermutation(cornerMap, cornerPermutation, cornerFinderMap, cornerNames, cornerPos, cornerOrientation);
    updateEdgeMapAndPermutation(edgeMap, edgePermutation, edgeFinderMap, edgeNames, edgePos, edgeOrientation);

    int phaseCount = 0;
    while (phaseCount < 4)
    {
        int64_t phaseID = 0;

        if (phaseCount == 0)
        {
            phaseID = idPhase1(edgeOrientation);

            if (phase1Map.find(phaseID) != phase1Map.end())
            {

                std::cout << "phase1ID Found!" << std::endl;
                std::cout << "phase1D = " << phaseID << std::endl;
                std::cout << "cubeCode before = " << cubeCode << std::endl;
                std::cout << "Moves:" << std::endl;

                for (auto a : phase1Map.find(phaseID)->second)
                {
                    std::cout << a << ",";
                    rotateCubeString(a);
                    theMoves.push_back(a);
                }

                std::cout << "cubeCode after = " << cubeCode << std::endl;
                std::cout << std::endl;
            }

        }
        else if (phaseCount == 1)
        {
            phaseID = idPhase2(cornerOrientation, edgePos);

            if (phase2Map.find(phaseID) != phase2Map.end())
            {

                std::cout << "phase2ID Found!" << std::endl;
                std::cout << "phase2D = " << phaseID << std::endl;
                std::cout << "Moves:" << std::endl;
                for (auto a : phase2Map.find(phaseID)->second)
                {
                    std::cout << a << ",";
                    rotateCubeString(a);
                    theMoves.push_back(a);
                }

                std::cout << std::endl;
            }

        }
        else if (phaseCount == 2)
        {
            phaseID = idPhase3(cornerNames, cornerOrientation, cornerPos, edgeNames, edgeOrientation, edgePos);

            if (phase3Map.find(phaseID) != phase3Map.end())
            {

                std::cout << "phase3ID Found!" << std::endl;
                std::cout << "phase3D = " << phaseID << std::endl;
                std::cout << "Moves:" << std::endl;
                for (auto a : phase3Map.find(phaseID)->second)
                {
                    std::cout << a << ",";
                    rotateCubeString(a);
                    theMoves.push_back(a);
                }

                std::cout << std::endl;
            }

        }
        else if (phaseCount == 3)
        {
            phaseID = idPhase4(cornerNames, cornerOrientation, cornerPos, edgeNames, edgeOrientation, edgePos);

            if (phase4Map.find(phaseID) != phase4Map.end())
            {

                std::cout << "phase4ID Found!" << std::endl;
                std::cout << "phase4D = " << phaseID << std::endl;
                std::cout << "Moves:" << std::endl;
                for (auto a : phase4Map.find(phaseID)->second)
                {
                    std::cout << a << ",";
                    rotateCubeString(a);
                    theMoves.push_back(a);
                }

                std::cout << std::endl;
            }
            else {
                std::cout << "phase4ID not found" << std::endl;
                std::cout << std::endl;
                break;
            }
        }

        cornerMap.clear();
        cornerPermutation.clear();

        edgeMap.clear();
        edgePermutation.clear();

        updateCornerMapAndPermutation(cornerMap, cornerPermutation, cornerFinderMap, cornerNames, cornerPos, cornerOrientation);
        updateEdgeMapAndPermutation(edgeMap, edgePermutation, edgeFinderMap, edgeNames, edgePos, edgeOrientation);

        std::cout << "Phase ID = " << phaseID << "; phaseCount = " << phaseCount << std::endl;
        std::cout << "HERE" << std::endl;
        std::cout << std::endl;


        if ((phaseID == 0 || phaseID == 5592320) && phaseCount >= 4) {
            std::cout << "Broke from phase" << std::endl;
            break;
        }
        else if (phaseID == 0 || phaseID == 5592320)
        {
            phaseCount++;
        }

    }

    cubeCode = oldCubeCode;

    return theMoves;
}

void RubiksCubeProcessor::rotateCubeRandomlyMultiple(int times)
{
    for (int i = 0; i < times; i++) { // 87 -> 2 phase 3
        rotateCubeRandom(rotationHistory, moveNumbersAndOpposites);
    }
}

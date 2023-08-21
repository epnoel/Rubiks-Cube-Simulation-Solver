#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <chrono>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <map>
#include <fstream>
#include <sstream>

class RubiksCubeProcessor {

public:
    RubiksCubeProcessor();

    void loadInPhaseTables();

    std::string getCubeCode();

    void rotateFrontString();

    void rotateFrontCCWString();

    void rotateFrontTwiceString();

    void rotateBackString();

    void rotateBackCCWString();

    void rotateBackTwiceString();

    void rotateLeftString();

    void rotateLeftCCWString();

    void rotateLeftTwiceString();

    void rotateRightString();

    void rotateRightCCWString();

    void rotateRightTwiceString();

    void rotateTopString();

    void rotateTopCCWString();

    void rotateTopTwiceString();

    void rotateBottomString();

    void rotateBottomCCWString();

    void rotateBottomTwiceString();

    void loadInEdgeMap(std::map<std::vector<char>, int>& m);

    void loadInEdgePermutation(std::unordered_map<int, std::vector<char>>& mPerm);

    void loadInCornerMap(std::map<std::vector<char>, int>& m);

    void loadInCornerPermutation(std::unordered_map<int, std::vector<char>>& mPerm);

    bool unevenColorAmount();

    void rotateCubeString(int moveNumber);

    bool determineEdgeGoodness(char face1, char face2, bool nonMiddleEdge);

    int determineCornerGoodness(char face1, char face2, char face3);

    void rotateCubeRandom(std::vector<int>& rotationHistory, std::unordered_map<int, std::vector<int>> movesAndOpposites);

    void updateEdgeMapAndPermutation(std::map<std::vector<char>, int>& edgeMap, std::unordered_map<int, std::vector<char>>& edgePermutation,
        std::map<std::vector<char>, std::string>& edgeFinderMap, std::vector<std::string>& edgeNames,
        std::vector<int>& edgePos, std::vector<int>& edgeOrient);

    void updateCornerMapAndPermutation(std::map<std::vector<char>, int>& cornerMap, std::unordered_map<int, std::vector<char>>& cornerPermutation,
        std::map<std::vector<char>, std::string>& cornerFinderMap, std::vector<std::string>& cornerNames,
        std::vector<int>& cornerPos, std::vector<int>& cornerOrient);

    int translateRotationMove(std::string s);

    void loadPhaseTable(std::string fileName, std::unordered_map<int64_t, std::vector<int>>& phase1Map);

    int64_t	idPhase1(std::vector<int> edgeOrient);

    int64_t	idPhase2(std::vector<int> cornerOrient, std::vector<int> edgePos);

    int64_t	idPhase3(std::vector<std::string> cornerNames, std::vector<int> cornerOrient, std::vector<int> cornerPos,
        std::vector<std::string> edgeNames, std::vector<int> edgeOrient, std::vector<int> edgePos);

    int64_t	idPhase4(std::vector<std::string> cornerNames, std::vector<int> cornerOrient, std::vector<int> cornerPos,
        std::vector<std::string> edgeNames, std::vector<int> edgeOrient, std::vector<int> edgePos);

    void printOrientationAndPermutationInfo();

    std::vector<int> solveMoves();

    void rotateCubeRandomlyMultiple(int times);

private:
    std::string cubeCode;

    // Corners 
    std::vector<std::string> cornerNames;
    std::map<std::vector<char>, int> cornerMap;
    std::unordered_map<int, std::vector<char>> cornerPermutation;
    std::map<std::vector<char>, std::string> cornerFinderMap;
    std::vector<int> cornerPos = { 0, 1, 2, 3, 4, 5, 6, 7 };
    std::vector<int> cornerOrientation = { 0, 0, 0, 0, 0, 0, 0, 0 };

    // Edges
    std::vector<std::string> edgeNames;
    std::map<std::vector<char>, int> edgeMap;
    std::unordered_map<int, std::vector<char>> edgePermutation;
    std::map<std::vector<char>, std::string> edgeFinderMap;
    std::vector<int> edgePos = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    std::vector<int> edgeOrientation = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    std::string fileNamePhase1 = "phase1.txt";
    std::string fileNamePhase2 = "phase2.txt";
    std::string fileNamePhase3 = "phase3.txt";
    std::string fileNamePhase4 = "phase4.txt";

    std::unordered_map<int64_t, std::vector<int>> phase1Map;
    std::unordered_map<int64_t, std::vector<int>> phase2Map;
    std::unordered_map<int64_t, std::vector<int>> phase3Map;
    std::unordered_map<int64_t, std::vector<int>> phase4Map;

    std::vector<int> rotationHistory;

public:
    std::unordered_map<int, std::vector<int>> moveNumbersAndOpposites = { {0,{1,3,12}}, // Front
                                                                          {1,{0,2,12}}, // Front CCW
                                                                          {2,{3,1,13}}, // Back
                                                                          {3,{2,0,13}}, // Back CCW
                                                                          {4,{5,7,14}}, // Left 
                                                                          {5,{4,6,14}}, // Left CCW
                                                                          {6,{7,5,15}}, // Right
                                                                          {7,{6,4,15}}, // Right CCW
                                                                          {8,{9,11,16}}, // Top
                                                                          {9,{8,10,16}}, // Top CCw
                                                                          {10,{11,9,17}}, // Bottom
                                                                          {11,{10,8,17}}, // Bottom CCW
                                                                          {12,{12,1,0}}, // Front 2
                                                                          {13,{13,3,2}}, // Back 2
                                                                          {14,{14,5,4}}, // Left 2
                                                                          {15,{15,7,6}}, // Right 2
                                                                          {16,{16,9,8}}, // Top 2
                                                                          {17,{17,11,10}} }; // Bottom 2

};

#include <SFML\Graphics.hpp>
#include "RubiksCube.h"
#include "RubiksCubeProcessor.h"
#include <stack>
#include <queue>
#include <time.h>
#include <tchar.h>
#include <stdio.h>
#include "SerialClass.h"	// Library described above
#include "Vertex.h"
#include "Face.h"
#include "Cube.h"


int main() {

	sf::Vector2f vCameraPos = { 0.5f, 0.5f }; // was 0.5f, 0.5f
	float fCameraAngle = 10.0f; // was 0.f
	float fCameraAngleTarget = fCameraAngle;
	float fCameraPitch = 5.5f; // was 5.5f
	float fCameraZoom = 86.0f; // was 16.f

	vCameraPos *= fCameraZoom;
	std::cout << "vCameraPos = (" << vCameraPos.x << "," << vCameraPos.y << ")" << std::endl;


	sf::Image* greenSquare, * blueSquare, * redSquare, * orangeSquare, * whiteSquare, * yellowSquare, *blackSquare;

	int imageSquareSize = 40;
	int imageChange = imageSquareSize / 10; // x * 0.1
	int imageLimit = imageSquareSize - 2 * imageChange; // x - 2*x*0.1

	greenSquare = new sf::Image;
	greenSquare->create(imageSquareSize, imageSquareSize, sf::Color::Black);
	blueSquare = new sf::Image;
	blueSquare->create(imageSquareSize, imageSquareSize, sf::Color::Black);
	redSquare = new sf::Image;
	redSquare->create(imageSquareSize, imageSquareSize, sf::Color::Black);
	orangeSquare = new sf::Image;
	orangeSquare->create(imageSquareSize, imageSquareSize, sf::Color::Black);
	whiteSquare = new sf::Image;
	whiteSquare->create(imageSquareSize, imageSquareSize, sf::Color::Black);
	yellowSquare = new sf::Image;
	yellowSquare->create(imageSquareSize, imageSquareSize, sf::Color::Black);
	blackSquare = new sf::Image;
	blackSquare->create(imageSquareSize, imageSquareSize, sf::Color::Black);

	sf::Color orangeColor({ 255,165,0 });

	for (int i = 0; i < imageLimit; i++) {
		for (int j = 0; j < imageLimit; j++) {
			greenSquare->setPixel(i + imageChange, j + imageChange, sf::Color::Green);
			blueSquare->setPixel(i + imageChange, j + imageChange, sf::Color::Blue);
			redSquare->setPixel(i + imageChange, j + imageChange, sf::Color::Red);
			orangeSquare->setPixel(i + imageChange, j + imageChange, orangeColor);
			whiteSquare->setPixel(i + imageChange, j + imageChange, sf::Color::White);
			yellowSquare->setPixel(i + imageChange, j + imageChange, sf::Color::Yellow);
		}
	}

	sf::Image editImage;

	int screenWidth = 800;
	int screenHeight = 800;
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML works!");


	/*Cube *cube1 = new Cube;
	cube1->position = { 0,0,0 };
	cube1->loadFaceImages(whiteSquare, yellowSquare, greenSquare, blueSquare, redSquare, orangeSquare);

	Cube *cube2 = new Cube;
	cube2->position = { 1,0,0};
	cube2->loadFaceImages(whiteSquare, yellowSquare, greenSquare, blueSquare, redSquare, orangeSquare);

	Cube *cube3 = new Cube;
	cube3->position = { 2,0,0 };
	cube3->loadFaceImages(whiteSquare, yellowSquare, greenSquare, blueSquare, redSquare, orangeSquare);

	Cube* cube4 = new Cube;
	cube4->position = { 0,1,0 };
	cube4->loadFaceImages(whiteSquare, yellowSquare, greenSquare, blueSquare, redSquare, orangeSquare);

	Cube* cube5 = new Cube;
	cube5->position = { 0,0,-1 };
	cube5->loadFaceImages(whiteSquare, yellowSquare, greenSquare, blueSquare, redSquare, orangeSquare);

	Cube* cube6 = new Cube;
	cube6->position = { 0,2,0 };
	cube6->loadFaceImages(whiteSquare, yellowSquare, greenSquare, blueSquare, redSquare, orangeSquare);

	Cube* cube7 = new Cube;
	cube7->position = { 0,0,-2 };
	cube7->loadFaceImages(whiteSquare, yellowSquare, greenSquare, blueSquare, redSquare, orangeSquare);

	std::vector<Cube*> allCubes;
	allCubes.push_back(cube1);
	allCubes.push_back(cube2);
	allCubes.push_back(cube3);
	allCubes.push_back(cube4);
	allCubes.push_back(cube5);
	allCubes.push_back(cube6);
	allCubes.push_back(cube7);*/

	//std::vector<std::vector<Cube*>> allCubes;
	std::vector<sf::Image*> faceImages = { greenSquare, blueSquare, whiteSquare, yellowSquare, redSquare, orangeSquare, blackSquare };

	RubiksCube rubiksCube;

	std::string theCube = "WWWWWWWWWRRRRRRRRRBBBBBBBBBOOOOOOOOOGGGGGGGGGYYYYYYYYY";

	std::unordered_map<std::string, std::vector<int>> individualCubeColors;

	individualCubeColors = { {"200", {0, 6, 3, 6, 4, 6}}, // RYG -> {44, n, 51, n, 15, n}
							 {"210", {0, 6, 3, 6, 6, 6}}, // YG -> {43, n, 52, n, n, n}
							 {"220", {0, 6, 3, 6, 6, 5}}, // OYG -> {42, n, 53, n, n, 35}
							 {"100", {0, 6, 6, 6, 4, 6}}, // GR -> {41, n, n, n, 12, n}
							 {"110", {0, 6, 6, 6, 6, 6}}, // G -> {40, n, n, n, n, n}
							 {"120", {0, 6, 6, 6, 6, 5}}, // GO -> {39, n, n, n, n, 32}
							 {"000", {0, 6, 6, 2, 4, 6}}, // RWG -> {38, n, n, 0, 9, n}
							 {"010", {0, 6, 6, 2, 6, 6}}, // GW -> {37, n, n, 1, n, n}
							 {"020", {0, 6, 6, 2, 6, 5}}, // OWG -> {36, n, n, 2, n, 29}
							 {"201", {6, 6, 3, 6, 4, 6}}, // RY -> {n, n, 48, n, 16, n}
							 {"211", {6, 6, 3, 6, 6, 6}}, // Y -> {n, n, 49, n, n, n}
							 {"221", {6, 6, 3, 6, 6, 5}}, // OY -> {n, n, 50, n, n, 34}
							 {"101", {6, 6, 6, 6, 4, 6}}, // R -> {n, n, n, n, 13, n}
							 {"111", {6, 6, 6, 6, 6, 6}}, // Don't draw middle cube
							 {"121", {6, 6, 6, 6, 6, 5}}, // O -> {n, n, n, n, n, 31}
							 {"001", {6, 6, 6, 2, 4, 6}}, // RW -> {n, n, n, 3, 10, n}
							 {"011", {6, 6, 6, 2, 6, 6}}, // W -> {n, n, n, 4, n, n}
							 {"021", {6, 6, 6, 2, 6, 5}}, // OW -> {n, n, n, 5, n, 28}
							 {"202", {6, 1, 3, 6, 4, 6}}, // RYB -> {n, 24, 45, n, 17, n}
							 {"212", {6, 1, 3, 6, 6, 6}}, // BY -> {n, 25, 46, n, n, n}
							 {"222", {6, 1, 3, 6, 6, 5}}, // OYB -> {n, 26, 47, n, n, 33}
							 {"102", {6, 1, 6, 6, 4, 6}}, // RB -> {n, 21, n, n, 14, n}
							 {"112", {6, 1, 6, 6, 6, 6}}, // B -> {n, 22, n, n, n, n}
							 {"122", {6, 1, 6, 6, 6, 5}}, // OB -> {n, 23, n, n, n, 30}
							 {"002", {6, 1, 6, 2, 4, 6}}, // RWB -> {n, 18, n, 6, 11, n}
							 {"012", {6, 1, 6, 2, 6, 6}}, // BW -> {n, 19, n, 7, n, n}
							 {"022", {6, 1, 6, 2, 6, 5}} }; // BWO -> {n, 20, n, 8, n, 27}

	RubiksCubeProcessor RubiksCubeProcessor;
	RubiksCubeProcessor.loadInPhaseTables();
	//RubiksCubeProcessor.solveMoves();


	rubiksCube.create3x3Cube(faceImages, RubiksCubeProcessor.getCubeCode());

	//faceImages.clear();
	//delete greenSquare;
	//delete blueSquare;
	//delete redSquare;
	//delete orangeSquare;
	//delete whiteSquare;
	//delete yellowSquare;

	bool rotateZ = false;
	bool rotateY = false;
	bool rotateX = false;

	std::vector<float> rotations(6, 0.f);

	window.setFramerateLimit(50);

	float arbitraryAngleAmount = 0.f;

	bool startArbRot = false;
	bool startRot3 = false;
	bool startRot4 = false;
	bool stopAllRot = false;

	std::stack<int> randomMoves;
	// shuffleCube(randomMoves, RubiksCubeProcessor.moveNumbersAndOpposites, 37);

	std::queue<int> solutions;
	//for (auto d : rubik)
	bool solveMode = false;
	int currentMove = -1;

	float currentPotAngle = 0.f;
	float changePotAngle = 0.f;

	Serial* SP = new Serial("\\\\.\\COM3");    // adjust as needed, used for Arduino

	if (SP->IsConnected())
		printf("We're connected");


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed && currentMove == -1)
			{
				if (event.key.code == sf::Keyboard::F)
				{
					currentMove = 0;
				}
				else if (event.key.code == sf::Keyboard::B)
				{
					currentMove = 2;
				}
				else if (event.key.code == sf::Keyboard::L)
				{
					currentMove = 4;
				}
				else if (event.key.code == sf::Keyboard::R)
				{
					currentMove = 6;
				}
				else if (event.key.code == sf::Keyboard::U)
				{
					currentMove = 8;
				}
				else if (event.key.code == sf::Keyboard::D)
				{
					currentMove = 10;
				}
				else if (event.key.code == sf::Keyboard::S)
				{
					for (auto d : RubiksCubeProcessor.solveMoves())
					{
						solutions.push(d);
						std::cout << d << ", ";
					}
					currentMove = -3;
				}
				else if (event.key.code == sf::Keyboard::A)
				{
					currentMove = -2;
					rubiksCube.shuffleCube(randomMoves, RubiksCubeProcessor.moveNumbersAndOpposites, 37);
				}
				else if (event.key.code == sf::Keyboard::P)
				{
					fCameraAngle += 0.05f;
					std::cout << "fCameraAngle = " << fCameraAngle << std::endl;
				}
				else if (event.key.code == sf::Keyboard::Q)
				{
					fCameraAngle -= 0.05f;
					std::cout << "fCameraAngle = " << fCameraAngle << std::endl;
				}
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::P)
				{
					fCameraAngle += 0.05f;
					std::cout << "fCameraAngle = " << fCameraAngle << std::endl;
				}
				else if (event.key.code == sf::Keyboard::Q)
				{
					fCameraAngle -= 0.05f;
					std::cout << "fCameraAngle = " << fCameraAngle << std::endl;
				}
			}
		}

		if (/*currentMove == -1*/ true )
		{


			if (SP->IsConnected())
			{

				char incomingData[256] = "";			// don't forget to pre-allocate memory
				//printf("%s\n",incomingData);
				int dataLength = 255;
				int readResult = 0;

				std::vector<std::string> angleButtonStrings;

				int track = 0;

				for (int a = 0; a < 2; a++) {
					readResult = SP->ReadData(incomingData, dataLength);

					// std::cout << "incomingData.size() = " << sizeof(incomingData) << std::endl;

					// printf("Bytes read: (0 means no data available) %i\n",readResult);
					incomingData[readResult] = 0;
				}

				//printf("%s", incomingData);

				Sleep(2);

				std::string s = "";
				int start = false;

				for (auto i : incomingData)
				{
 
					if (i == 13 && start)
					{

						angleButtonStrings.push_back(s);
						s.clear();

						start = false;
						track++;

						if (track > 1) {
							break;
						}
					}

					if (start)
					{
						s.push_back(i);
					}

					if (i == 10 && !start && s.empty())
					{
						start = true;
					}

				}

				int kPos, aPos;
				if (angleButtonStrings[0][0] == 'K')
				{
					kPos = 0;
					aPos = 1;
				}
				else {
					kPos = 1;
					aPos = 0;
				}


				// Debug
				//std::cout << "angleButtonStrnigs.size() = " << angleButtonStrings.size() << std::endl;

				if (angleButtonStrings.size() == 2 && angleButtonStrings[0].size() > 3 && angleButtonStrings[1].size() > 3
					&& angleButtonStrings[kPos][0] == 'K' && angleButtonStrings[aPos][0] == 'A')
				{
					std::string sVal;

					// Button Pressed - Key Val

					// Debug
					sVal = angleButtonStrings[kPos].substr(3);
					//std::cout << "angleButtonStrings[kPos] = " << angleButtonStrings[kPos] << std::endl;
					//std::cout << "K: " << sVal << std::endl;

					if (currentMove == -1) {
						if (stoi(sVal) >= 1022 && stoi(sVal) <= 1023)
						{
							currentMove = 0;

							// Debug
							// std::cout << "s is equal to 1023" << std::endl;
						}
						else if (stoi(sVal) >= 1000 && stoi(sVal) <= 1003)
						{
							currentMove = 2;
						}
						else if (stoi(sVal) >= 930 && stoi(sVal) <= 933)
						{
							currentMove = 4;
						}
						else if (stoi(sVal) >= 696 && stoi(sVal) <= 699)
						{
							currentMove = 6;
						}
						else if (stoi(sVal) >= 511 && stoi(sVal) <= 514)
						{
							currentMove = 8;
						}
						else if (stoi(sVal) >= 6 && stoi(sVal) <= 10)
						{
							currentMove = 10;
						}
						else {
							currentMove = -1;
						}
					}


					sVal = angleButtonStrings[aPos].substr(3);

					// Debug
					//std::cout << "angleButtonStrings[aPos] = " << angleButtonStrings[aPos] << std::endl;
					//std::cout << "sVal.size() for aPos = " << sVal.size() << std::endl;



					float potAngle;
					
					if (sVal.size() == 4) {
						potAngle = std::stof(sVal);
					}
					else {
						potAngle = currentPotAngle;
					}


					changePotAngle = potAngle - currentPotAngle;

					if (abs(changePotAngle) < 0.02f)
					{
						changePotAngle = 0.f;
					}
					else {
						currentPotAngle = potAngle;
					}

					fCameraAngle += changePotAngle;

					// Debug
					// std::cout << "potAngle = " << potAngle << std::endl;
					// std::cout << "changePotAngle = " << changePotAngle << std::endl;
					// std::cout << "fCameraAngle = " << fCameraAngle << std::endl;


					//std::cout << "A: " << sVal << std::endl;
					//std::cout << std::endl;
				}

			}

		}

		window.clear();

		//fCameraAngle += 0.02f; // was 0.02f
		//fCameraAngle = fmod(fCameraAngle, 50.f);


		//if (startArbRot) {
		//	arbitraryAngleAmount += 0.06f;
		//	//arbitraryAngleAmount = fmod(arbitraryAngleAmount, 60.f);
		//}

		//if (arbitraryAngleAmount > 3.14159f / 2.f && !startRot3 && !stopAllRot)
		//{

		//	// Debug
		//	std::cout << "Arb Angle 1 Called" << std::endl;

		//	startArbRot = false;
		//	//arbitraryAngleAmount -= 0.02f;
		//	startRot3 = true;
		//	RubiksCubeProcessor.rotateRightString();;

		//	arbitraryAngleAmount = 0.f;

		//	edit3x3Cube(allCubes, faceImages, RubiksCubeProcessor.getCubeCode());


		//}


		//if (startRot3) {
		//	rotations[3] += 0.06f;
		//}

		//if (rotations[3] > 3.14159f / 2.f && !startRot4)
		//{

		//	// Debug
		//	std::cout << "Rot 3 Called" << std::endl;
		//	startRot3 = false;
		//	//rotations[3] -= 0.02;
		//	startRot4 = true;
		//	RubiksCubeProcessor.rotateTopString();

		//	rotations[3] = 0.f;

		//	edit3x3Cube(allCubes, faceImages, RubiksCubeProcessor.getCubeCode());
		//}


		//if (startRot4)
		//{
		//	rotations[4] += 0.06f;
		//}

		//if (rotations[4] > 3.14159f)
		//{

		//	// Debug
		//	std::cout << "Rot 4 Called" << std::endl;

		//	rotations[4] -= 0.02f;
		//	startRot4 = false;
		//	RubiksCubeProcessor.rotateFrontTwiceString();

		//	std::cout << "RubiksCubeProcessor.getCubeCode() = " << RubiksCubeProcessor.getCubeCode() << std::endl;
		//	std::cout << "cubeCode[50][34] = {" << RubiksCubeProcessor.getCubeCode()[50] << "," << RubiksCubeProcessor.getCubeCode()[34] << "}" << std::endl;

		//	edit3x3Cube(allCubes, faceImages, RubiksCubeProcessor.getCubeCode());


		//	stopAllRot = true;
		//	rotations[4] = 0.f;
		//}

		// Debug
		// std::cout << "fCameraPitch = " << fCameraPitch << std::endl;

		std::vector<Face> visibleFaces;
		std::map<std::vector<int>, bool> registeredProjectedVertexSets; // midpoints, true if twice, false if once

		int foundCount = 0;
		sf::Vector3f midpointRowPosition = { 1.5f,1.5f,0.5f };
		float signChange = -1.f;

		if (rotateZ) {
			for (auto& row : rubiksCube.allCubes) {

				for (auto& cube : row) {
					// Get the projection coordinates of the cube
					//setCubeProjectionCoordinates(*cube, fCameraAngle, fCameraPitch, fCameraZoom, { vCameraPos.x,vCameraPos.y,0.f }, { screenWidth,screenHeight });
					rubiksCube.rotateCubeAboutArbitraryAxis(*cube, { 0,0,1 }, midpointRowPosition, signChange * arbitraryAngleAmount, fCameraAngle, fCameraPitch,
						fCameraZoom, { vCameraPos.x,vCameraPos.y,0.f }, { screenWidth,screenHeight });

					// Get the visible Faces of the Cube
					rubiksCube.calculateVisibleFaces(*cube);

					// Find and determine adjacent faces (aka faces that touch each other)
					for (int b = 0; b < cube->visibleFaces.size(); b++) {

						int midPointX, midPointY, midPointZ;
						midPointX = (cube->faces[b].vertices[0].worldXYZ.x + cube->faces[b].vertices[1].worldXYZ.x
							+ cube->faces[b].vertices[2].worldXYZ.x + cube->faces[b].vertices[3].worldXYZ.x) / 4;
						midPointY = (cube->faces[b].vertices[0].worldXYZ.y + cube->faces[b].vertices[1].worldXYZ.y
							+ cube->faces[b].vertices[2].worldXYZ.y + cube->faces[b].vertices[3].worldXYZ.y) / 4;
						midPointZ = (cube->faces[b].vertices[0].worldXYZ.z + cube->faces[b].vertices[1].worldXYZ.z
							+ cube->faces[b].vertices[2].worldXYZ.z + cube->faces[b].vertices[3].worldXYZ.z) / 4;

						std::vector<int> intPositions = { midPointX, midPointY, midPointZ };

						auto mapFinder = registeredProjectedVertexSets.find(intPositions);

						if (mapFinder == registeredProjectedVertexSets.end())
						{

							registeredProjectedVertexSets.insert({ intPositions,false });
						}
						else {
							// Debug
							mapFinder->second = true;
							foundCount++;
						}
					}

				}

				midpointRowPosition.z += 1.f;
				signChange *= -1.f;
			}
		}

		if (rotateY) 
		{
			for (int a = 0; a < 3; a++)
			{

				std::vector<Cube*> cubeList;

				for (int b = 0; b < 3; b++)
				{
					//allCubes[b][a];
					//allCubes[b][a + 3];
					//allCubes[b][a + 6];

					cubeList.push_back(rubiksCube.allCubes[b][a]);
					cubeList.push_back(rubiksCube.allCubes[b][a + 3]);
					cubeList.push_back(rubiksCube.allCubes[b][a + 6]);

				}

				for (auto& cube : cubeList)
				{

					// Rotate About Y-Axis
					rubiksCube.rotateCubeAboutArbitraryAxis(*cube, { 0,1,0 }, midpointRowPosition, signChange * arbitraryAngleAmount, fCameraAngle, fCameraPitch,
						fCameraZoom, { vCameraPos.x,vCameraPos.y,0.f }, { screenWidth,screenHeight });

					// Get the visible Faces of the Cube
					rubiksCube.calculateVisibleFaces(*cube);

					// Find and determine adjacent faces (aka faces that touch each other)
					for (int b = 0; b < cube->visibleFaces.size(); b++) {

						int midPointX, midPointY, midPointZ;
						midPointX = (cube->faces[b].vertices[0].worldXYZ.x + cube->faces[b].vertices[1].worldXYZ.x
							+ cube->faces[b].vertices[2].worldXYZ.x + cube->faces[b].vertices[3].worldXYZ.x) / 4;
						midPointY = (cube->faces[b].vertices[0].worldXYZ.y + cube->faces[b].vertices[1].worldXYZ.y
							+ cube->faces[b].vertices[2].worldXYZ.y + cube->faces[b].vertices[3].worldXYZ.y) / 4;
						midPointZ = (cube->faces[b].vertices[0].worldXYZ.z + cube->faces[b].vertices[1].worldXYZ.z
							+ cube->faces[b].vertices[2].worldXYZ.z + cube->faces[b].vertices[3].worldXYZ.z) / 4;

						std::vector<int> intPositions = { midPointX, midPointY, midPointZ };

						auto mapFinder = registeredProjectedVertexSets.find(intPositions);

						if (mapFinder == registeredProjectedVertexSets.end())
						{

							registeredProjectedVertexSets.insert({ intPositions,false });
						}
						else {
							// Debug
							mapFinder->second = true;
							foundCount++;
						}
					}
				}

				midpointRowPosition.y += 1.f;
				signChange *= -1.f;

			}
		}

		if (rotateX)
		{
			for (int a = 0; a < 3; a++)
			{

				std::vector<Cube*> cubeList;

				for (int b = 0; b < 3; b++)
				{
					//allCubes[b][a*3];
					//allCubes[b][a*3 + 1];
					//allCubes[b][a*3 + 2];

					cubeList.push_back(rubiksCube.allCubes[b][a*3]);
					cubeList.push_back(rubiksCube.allCubes[b][a*3 + 1]);
					cubeList.push_back(rubiksCube.allCubes[b][a*3 + 2]);

				}

				for (auto& cube : cubeList)
				{

					// Rotate About Y-Axis
					rubiksCube.rotateCubeAboutArbitraryAxis(*cube, { 1,0,0 }, midpointRowPosition, signChange * arbitraryAngleAmount, fCameraAngle, fCameraPitch,
						fCameraZoom, { vCameraPos.x,vCameraPos.y,0.f }, { screenWidth,screenHeight });

					// Get the visible Faces of the Cube
					rubiksCube.calculateVisibleFaces(*cube);

					// Find and determine adjacent faces (aka faces that touch each other)
					for (int b = 0; b < cube->visibleFaces.size(); b++) {

						int midPointX, midPointY, midPointZ;
						midPointX = (cube->faces[b].vertices[0].worldXYZ.x + cube->faces[b].vertices[1].worldXYZ.x
							+ cube->faces[b].vertices[2].worldXYZ.x + cube->faces[b].vertices[3].worldXYZ.x) / 4;
						midPointY = (cube->faces[b].vertices[0].worldXYZ.y + cube->faces[b].vertices[1].worldXYZ.y
							+ cube->faces[b].vertices[2].worldXYZ.y + cube->faces[b].vertices[3].worldXYZ.y) / 4;
						midPointZ = (cube->faces[b].vertices[0].worldXYZ.z + cube->faces[b].vertices[1].worldXYZ.z
							+ cube->faces[b].vertices[2].worldXYZ.z + cube->faces[b].vertices[3].worldXYZ.z) / 4;

						std::vector<int> intPositions = { midPointX, midPointY, midPointZ };

						auto mapFinder = registeredProjectedVertexSets.find(intPositions);

						if (mapFinder == registeredProjectedVertexSets.end())
						{

							registeredProjectedVertexSets.insert({ intPositions,false });
						}
						else {
							// Debug
							mapFinder->second = true;
							foundCount++;
						}
					}
				}

				midpointRowPosition.x += 1.f;
				signChange *= -1.f;
				signChange *= 0.f;

			}
		}

		if (rotateZ) {
			if (!startRot3 && !startRot4) {
				rubiksCube.rotateRight(fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
					screenHeight, midpointRowPosition, registeredProjectedVertexSets);
			}
			else if (startRot3 && !startRot4) {
				rubiksCube.rotateTop(fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, rotations[3], screenWidth,
					screenHeight, midpointRowPosition, registeredProjectedVertexSets);
			}
			else
			{
				rubiksCube.rotateFront(fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, rotations[4], screenWidth,
					screenHeight, midpointRowPosition, registeredProjectedVertexSets);
			}
		}


		float limit = 3.14159f / 2.f;

		if (randomMoves.empty()/* && !solveMode*/ && currentMove == -1)
		{
			rubiksCube.rotateFront(fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, 0.f, screenWidth,
				screenHeight, midpointRowPosition, registeredProjectedVertexSets);

		}

		if (currentMove > -1)
		{
			if (currentMove > 11)
			{
				limit *= 2;
			}

			if (arbitraryAngleAmount < limit)
			{
				rubiksCube.rotateFromRotationNumber(currentMove, fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
					screenHeight, midpointRowPosition, registeredProjectedVertexSets);
				arbitraryAngleAmount += 3.14159f / 25.f;
			}
			else {
				arbitraryAngleAmount = 0.f;
				RubiksCubeProcessor.rotateCubeString(currentMove);

				rubiksCube.edit3x3Cube(faceImages, RubiksCubeProcessor.getCubeCode());

				rubiksCube.rotateFromRotationNumber(currentMove, fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, 0.f, screenWidth,
					screenHeight, midpointRowPosition, registeredProjectedVertexSets);

				currentMove = -1;
			}
		}

		if (!solutions.empty())
		{
			if (solutions.front() > 11)
			{
				limit *= 2.f;
			}

			if (arbitraryAngleAmount < limit)
			{
				rubiksCube.rotateFromRotationNumber(solutions.front(), fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
					screenHeight, midpointRowPosition, registeredProjectedVertexSets);
				arbitraryAngleAmount += 3.14159f / 25.f; // was 3.14159f / 100.f
			}
			else {
				std::cout << "solutions.front() = " << solutions.front() << std::endl;

				arbitraryAngleAmount = 0.f;
				RubiksCubeProcessor.rotateCubeString(solutions.front());

				rubiksCube.edit3x3Cube(faceImages, RubiksCubeProcessor.getCubeCode());

				rubiksCube.rotateFromRotationNumber(solutions.front(), fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
					screenHeight, midpointRowPosition, registeredProjectedVertexSets);

				solutions.pop();

				if (solutions.empty())
				{
					currentMove = -1;
				}

			}
		}

		if (!randomMoves.empty()) {

			if (randomMoves.top() > 11)
			{
				limit *= 2.f;
			}

			if (arbitraryAngleAmount < limit) {


				rubiksCube.rotateFromRotationNumber(randomMoves.top(), fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
					screenHeight, midpointRowPosition, registeredProjectedVertexSets);
				arbitraryAngleAmount += 3.14159f / 25.f; // was 3.14159f / 100.f
			}
			else {

				std::cout << "randomMoves.top() = " << randomMoves.top() << std::endl;

				arbitraryAngleAmount = 0.f;
				RubiksCubeProcessor.rotateCubeString(randomMoves.top());

				rubiksCube.edit3x3Cube(faceImages, RubiksCubeProcessor.getCubeCode());

				rubiksCube.rotateFromRotationNumber(randomMoves.top(), fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
					screenHeight, midpointRowPosition, registeredProjectedVertexSets);

				randomMoves.pop();

				if (randomMoves.empty())
				{
					currentMove = -1;
				}

			}
		}

		for (auto& row : rubiksCube.allCubes) {

			for (auto& cube : row) {

				// Add the visible faces to the visibleFaces vector
				for (int a = 0; a < cube->visibleFaces.size(); a++) {
					if (cube->visibleFaces[a]) {

						int midPointX, midPointY, midPointZ;
						midPointX = (cube->faces[a].vertices[0].worldXYZ.x + cube->faces[a].vertices[1].worldXYZ.x
							+ cube->faces[a].vertices[2].worldXYZ.x + cube->faces[a].vertices[3].worldXYZ.x) / 4;
						midPointY = (cube->faces[a].vertices[0].worldXYZ.y + cube->faces[a].vertices[1].worldXYZ.y
							+ cube->faces[a].vertices[2].worldXYZ.y + cube->faces[a].vertices[3].worldXYZ.y) / 4;
						midPointZ = (cube->faces[a].vertices[0].worldXYZ.z + cube->faces[a].vertices[1].worldXYZ.z
							+ cube->faces[a].vertices[2].worldXYZ.z + cube->faces[a].vertices[3].worldXYZ.z) / 4;

						std::vector<int> intPositions = { midPointX, midPointY, midPointZ };

						auto mapFinder = registeredProjectedVertexSets.find(intPositions);

						if (mapFinder->second == false)
						{
							visibleFaces.push_back(cube->faces[a]);
						}

					}
				}
			}
		}


		int theCount = 0;

		std::vector<sf::Vector2f> positions;
		std::vector<sf::Vector2f> positions2;

		// Debug
		//std::cout << "visibleFaces.size() = " << visibleFaces.size() << std::endl;
		//std::cout << "registeredProjectedVertexSets.size() = " << registeredProjectedVertexSets.size() << std::endl;
		//std::cout << "foundCount = " << foundCount << std::endl;


		// Sort in order of depth, from farthest away to closest
		std::sort(visibleFaces.begin(), visibleFaces.end(), [](const Face& q1, const Face& q2)
			{
				float z1 = -(q1.vertices[0].worldXYZ.y + q1.vertices[1].worldXYZ.y + q1.vertices[2].worldXYZ.y + q1.vertices[3].worldXYZ.y) * 0.25f;
				float z2 = -(q2.vertices[0].worldXYZ.y + q2.vertices[1].worldXYZ.y + q2.vertices[2].worldXYZ.y + q2.vertices[3].worldXYZ.y) * 0.25f;
				return z1 < z2;
			});

		for (int i = 0; i < visibleFaces.size(); i++) {

			sf::Vector2f imagePos3;
			sf::Image otherEditImage3;

			//textureTriangle(visibleFaces[i].vertices[0], visibleFaces[i].vertices[1], visibleFaces[i].vertices[2],
			//	{ 0,0,0 }, { 0,1,0 }, { 1,1,0 },
			//	*visibleFaces[i].image, otherEditImage3, imagePos3);

			rubiksCube.combineTextureTriangles(visibleFaces[i].vertices[0], visibleFaces[i].vertices[1], visibleFaces[i].vertices[2], visibleFaces[i].vertices[3],
				{ 0,0,0 }, { 0,1,0 }, { 1,1,0 }, { 1,0,0 }, *visibleFaces[i].image, otherEditImage3, imagePos3);


			positions.push_back(imagePos3);


			if (otherEditImage3.getSize().x != 0) {
				visibleFaces[i].texture1 = new sf::Texture;
				visibleFaces[i].texture1->loadFromImage(otherEditImage3);
			}
			else {

				visibleFaces[i].texture1 = new sf::Texture;

				sf::Image transparentPixel;
				transparentPixel.create(1, 1, sf::Color::Transparent);

				visibleFaces[i].texture1->loadFromImage(transparentPixel);

				// Debug
				std::cout << "otherEditImage3.size() = (" << otherEditImage3.getSize().x << "," << otherEditImage3.getSize().y << ")" << std::endl;
				std::cout << "imagePos3 = (" << imagePos3.x << "," << imagePos3.y << ")" << std::endl;
			}

			//sf::Vector2f imagePos4;
			//sf::Image otherEditImage4;


			//textureTriangle(visibleFaces[i].vertices[0], visibleFaces[i].vertices[2], visibleFaces[i].vertices[3],
			//	{ 0,0,0 }, { 1,1,0 }, { 1,0,0 },
			//	*visibleFaces[i].image, otherEditImage4, imagePos4);

			//positions2.push_back(imagePos4);

			//if (otherEditImage4.getSize().x != 0) {
			//	visibleFaces[i].texture2 = new sf::Texture;
			//	visibleFaces[i].texture2->loadFromImage(otherEditImage4);
			//}
			//else {
			//	visibleFaces[i].texture2 = new sf::Texture;

			//	sf::Image transparentPixel;
			//	transparentPixel.create(1, 1, sf::Color::Transparent);

			//	visibleFaces[i].texture2->loadFromImage(transparentPixel);
			//	// Debug
			//	std::cout << "otherEditImage4.size() = (" << otherEditImage4.getSize().x << "," << otherEditImage4.getSize().y << ")" << std::endl;
			//}

		}

		for (auto& i : visibleFaces) {

			// Debug
			//std::cout << "theCount = " << theCount << std::endl;
			//std::cout << "positions.size() = " << positions.size() << std::endl;
			//std::cout << "positions2.size() = " << positions2.size() << std::endl;

			sf::Sprite* drawSprite = new sf::Sprite;
			drawSprite->setTexture(*i.texture1);
			drawSprite->setPosition(positions[theCount]);
			window.draw(*drawSprite);

			//sf::Sprite* drawSprite2 = new sf::Sprite;
			//drawSprite2->setTexture(*i.texture2);
			//drawSprite2->setPosition(positions2[theCount]);
			//window.draw(*drawSprite2);

			delete drawSprite;
			//delete drawSprite2;

			delete i.texture1;
			//delete i.texture2;
			theCount++;
		}

		window.display();
	}

	return 0;
}
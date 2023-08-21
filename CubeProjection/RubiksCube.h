#pragma once

#include <vector>
#include "Cube.h"
#include <stack>
#include <unordered_map>
#include <iostream>

class RubiksCube {

public:

	RubiksCube();

	void setCubeProjectionCoordinates(Cube& cube1, const float fAngle, const float fPitch, const float fScale, const sf::Vector3f vCamera, sf::Vector2i screenSize,
		sf::Vector3i axisVector);

	sf::Vector2f convertToRegularCoords(sf::Vector2f normalizedVal, int height, int width);

	void determineImagePosition(Vertex vertex1, Vertex vertex2, Vertex vertex3, sf::Vector2f& imagePosition, sf::Vector2i& imageSize);

	void textureTriangle(Vertex vertex1, Vertex vertex2, Vertex vertex3, sf::Vector3f uvw1, sf::Vector3f uvw2, sf::Vector3f uvw3, sf::Image originalImage, sf::Image& editImage,
		sf::Vector2f& imagePosition, bool existingImage, int changeX, int changeY);

	void combineTextureTriangles(Vertex vertex1, Vertex vertex2, Vertex vertex3, Vertex vertex4, sf::Vector3f uvw1, sf::Vector3f uvw2, sf::Vector3f uvw3, sf::Vector3f uvw4,
		sf::Image originalImage, sf::Image& editImage, sf::Vector2f& imagePosition);

	void calculateVisibleFaces(Cube& cube1);

	void rotateCubeAboutArbitraryAxis(Cube& cube1, sf::Vector3f axisVector, sf::Vector3f midpoint, float angleAmount, float fAngle, float fPitch, float fScale,
		sf::Vector3f vCamera, sf::Vector2i screenSize);

	int determineColorIndex(char c);

	void create3x3Cube(std::vector<sf::Image*> faceImages, std::string theCube);

	void edit3x3Cube(std::vector<sf::Image*> faceImages,
		std::string theCube);

	void rotateFront(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
		float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
		std::map<std::vector<int>, bool>& registeredProjectedVertexSets);


	void rotateFrontCCW(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
		float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
		std::map<std::vector<int>, bool>& registeredProjectedVertexSets);

	void rotateBack(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
		float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
		std::map<std::vector<int>, bool>& registeredProjectedVertexSets);

	void rotateBackCCW(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
		float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
		std::map<std::vector<int>, bool>& registeredProjectedVertexSets);

	void rotateLeft(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
		float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
		std::map<std::vector<int>, bool>& registeredProjectedVertexSets);

	void rotateLeftCCW(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
		float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
		std::map<std::vector<int>, bool>& registeredProjectedVertexSets);

	void rotateRight(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
		float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
		std::map<std::vector<int>, bool>& registeredProjectedVertexSets);

	void rotateRightCCW(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
		float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
		std::map<std::vector<int>, bool>& registeredProjectedVertexSets);


	void rotateTop(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
		float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
		std::map<std::vector<int>, bool>& registeredProjectedVertexSets);

	void rotateTopCCW(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
		float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
		std::map<std::vector<int>, bool>& registeredProjectedVertexSets);

	void rotateBottom(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
		float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
		std::map<std::vector<int>, bool>& registeredProjectedVertexSets);


	void rotateBottomCCW(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
		float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
		std::map<std::vector<int>, bool>& registeredProjectedVertexSets);

	void rotateFromRotationNumber(int rotNumber, float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
		float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
		std::map<std::vector<int>, bool>& registeredProjectedVertexSets);

	void shuffleCube(std::stack<int>& randomMoves, std::unordered_map<int, std::vector<int>> moveNumbersAndOpposites, int times);

public:
	std::vector<std::vector<Cube*>> allCubes;
private:
	std::vector<sf::Image*> faceImages;
};

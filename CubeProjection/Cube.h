#pragma once

#include "Face.h"

struct Cube {


	Cube() {
		faces[FacePosition::Top] = Face({ 0,1,1 }, { 0,0,1 }, { 1,0,1 }, { 1,1,1 }); // Top (7,0,3,4)
		faces[FacePosition::Bottom] = Face({ 0,0,0 }, { 0,1,0 }, { 1,1,0 }, { 1,0,0 }); // Bottom (1,6,5,2)
		faces[FacePosition::Left] = Face({ 0,1,1 }, { 0,1,0 }, { 0,0,0 }, { 0,0,1 }); // Left (7, 6, 1, 0)
		faces[FacePosition::Right] = Face({ 1,0,1 }, { 1,0,0 }, { 1,1,0 }, { 1,1,1 }); // Right (3, 2, 5, 4)
		faces[FacePosition::Front] = Face({ 0,0,1 }, { 0,0,0 }, { 1,0,0 }, { 1,0,1 }); // Front (0, 1, 2, 3)
		faces[FacePosition::Back] = Face({ 1,1,1 }, { 1,1,0 }, { 0,1,0 }, { 0,1,1 }); // Back (4, 5, 6, 7)

		facesOrder[FacePosition::Top] = { 7,0,3,4 };
		facesOrder[FacePosition::Bottom] = { 1,6,5,2 };
		facesOrder[FacePosition::Left] = { 7, 6, 1, 0 };
		facesOrder[FacePosition::Right] = { 3, 2, 5, 4 };
		facesOrder[FacePosition::Front] = { 0, 1, 2, 3 };
		facesOrder[FacePosition::Back] = { 4, 5, 6, 7 };

		vertices[0] = faces[FacePosition::Front].vertices[0];
		vertices[1] = faces[FacePosition::Front].vertices[1];
		vertices[2] = faces[FacePosition::Front].vertices[2];
		vertices[3] = faces[FacePosition::Front].vertices[3];
		vertices[4] = faces[FacePosition::Back].vertices[0];
		vertices[5] = faces[FacePosition::Back].vertices[1];
		vertices[6] = faces[FacePosition::Back].vertices[2];
		vertices[7] = faces[FacePosition::Back].vertices[3];

		position = faces[FacePosition::Front].vertices[1].worldXYZ;
	}


	Cube(Face face1, Face face2, Face face3, Face face4, Face face5, Face face6) {
		faces[FacePosition::Top] = face1;
		faces[FacePosition::Bottom] = face2;
		faces[FacePosition::Left] = face3;
		faces[FacePosition::Right] = face4;
		faces[FacePosition::Front] = face5;
		faces[FacePosition::Back] = face6;

		facesOrder[FacePosition::Top] = { 7,0,3,4 };
		facesOrder[FacePosition::Bottom] = { 1,6,5,2 };
		facesOrder[FacePosition::Left] = { 7, 6, 1, 0 };
		facesOrder[FacePosition::Right] = { 3, 2, 5, 4 };
		facesOrder[FacePosition::Front] = { 0, 1, 2, 3 };
		facesOrder[FacePosition::Back] = { 4, 5, 6, 7 };

		vertices[0] = faces[FacePosition::Front].vertices[0]; // (0,0,1)
		vertices[1] = faces[FacePosition::Front].vertices[1]; // (0,0,0)
		vertices[2] = faces[FacePosition::Front].vertices[2]; // (1,0,0)
		vertices[3] = faces[FacePosition::Front].vertices[3]; // (1,0,1)
		vertices[4] = faces[FacePosition::Back].vertices[0]; // (1,1,1)
		vertices[5] = faces[FacePosition::Back].vertices[1]; // (1,1,0)
		vertices[6] = faces[FacePosition::Back].vertices[2]; // (0,1,0)
		vertices[7] = faces[FacePosition::Back].vertices[3]; // (0,1,1)

		position = faces[FacePosition::Front].vertices[1].worldXYZ;

	}

	void loadFaceImages(sf::Image* topFace, sf::Image* bottomFace, sf::Image* leftFace, sf::Image* rightFace, sf::Image* frontFace, sf::Image* backFace) {

		faces[FacePosition::Top].image = topFace;
		//faces[FacePosition::Top].image = new sf::Image;
		//faces[FacePosition::Top].image->create(topFace.getSize().x, topFace.getSize().y);
		//faces[FacePosition::Top].image->copy(topFace, 0, 0, sf::IntRect(0, 0, topFace.getSize().x, topFace.getSize().y));
		//faces[FacePosition::Top].image = &topFace;

		faces[FacePosition::Bottom].image = bottomFace;
		//faces[FacePosition::Bottom].image = new sf::Image;
		//faces[FacePosition::Bottom].image->create(bottomFace.getSize().x, bottomFace.getSize().y);
		//faces[FacePosition::Bottom].image->copy(bottomFace, 0, 0, sf::IntRect(0, 0, bottomFace.getSize().x, bottomFace.getSize().y));
		//faces[FacePosition::Bottom].image = &bottomFace;

		faces[FacePosition::Left].image = leftFace;
		//faces[FacePosition::Left].image = new sf::Image;
		//faces[FacePosition::Left].image->create(leftFace.getSize().x, leftFace.getSize().y);
		//faces[FacePosition::Left].image->copy(leftFace, 0, 0, sf::IntRect(0, 0, leftFace.getSize().x, leftFace.getSize().y));
		//faces[FacePosition::Left].image = &leftFace;

		faces[FacePosition::Right].image = rightFace;
		//faces[FacePosition::Right].image = new sf::Image;
		//faces[FacePosition::Right].image->create(rightFace.getSize().x, rightFace.getSize().y);
		//faces[FacePosition::Right].image->copy(rightFace, 0, 0, sf::IntRect(0, 0, rightFace.getSize().x, rightFace.getSize().y));
		//faces[FacePosition::Right].image = &rightFace;

		faces[FacePosition::Front].image = frontFace;
		//faces[FacePosition::Front].image = new sf::Image;
		//faces[FacePosition::Front].image->create(frontFace.getSize().x, frontFace.getSize().y);
		//faces[FacePosition::Front].image->copy(frontFace, 0, 0, sf::IntRect(0, 0, frontFace.getSize().x, frontFace.getSize().y));
		//faces[FacePosition::Front].image = &frontFace;

		faces[FacePosition::Back].image = backFace;
		//faces[FacePosition::Back].image = new sf::Image;
		//faces[FacePosition::Back].image->create(backFace.getSize().x, backFace.getSize().y);
		//faces[FacePosition::Back].image->copy(backFace, 0, 0, sf::IntRect(0, 0, backFace.getSize().x, backFace.getSize().y));
		//faces[FacePosition::Back].image = &backFace;
	}

	int size = 0;
	sf::Vector3f position; // midpoint position in 3D name
	std::vector<Face> faces = std::vector<Face>(6); // 1. top, 2. bottom, 3. left, 4. right, 5. front, 6. back
	std::vector<std::vector<int>> facesOrder = std::vector<std::vector<int>>(6, std::vector<int>(4));
	std::vector<Vertex> vertices = std::vector<Vertex>(8);
	std::vector<bool> visibleFaces = std::vector<bool>(6, false); // 1. top, 2. bottom, 3. left, 4. right, 5. front, 6. back
	std::string identity; // Corner, edge, or middle
};
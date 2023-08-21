#pragma once

#include "Vertex.h"

enum FacePosition {
	Top = 0,
	Bottom = 1,
	Left = 2,
	Right = 3,
	Front = 4,
	Back = 5
};

struct Face {

	Face() {

	}

	Face(sf::Vector3f topLeft, sf::Vector3f bottomLeft, sf::Vector3f bottomRight, sf::Vector3f topRight) {
		Vertex vertex1(topLeft);
		Vertex vertex2(bottomLeft);
		Vertex vertex3(bottomRight);
		Vertex vertex4(topRight);

		vertices[0] = vertex1;
		vertices[1] = vertex2;
		vertices[2] = vertex3;
		vertices[3] = vertex4;
	}

	Face(Vertex vertex1, Vertex vertex2, Vertex vertex3, Vertex vertex4) {
		vertices[0] = vertex1;
		vertices[1] = vertex2;
		vertices[2] = vertex3;
		vertices[3] = vertex4;
	}

	std::vector<Vertex> vertices = std::vector<Vertex>(4);
	sf::Image* image;
	sf::Texture* texture1;
	sf::Texture* texture2;

};

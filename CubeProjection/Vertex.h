#pragma once

#include <SFML\Graphics.hpp>

struct Vertex {

	Vertex() {

	}

	Vertex(sf::Vector3f worldXYZ) {
		this->worldXYZ = worldXYZ;
	}

	sf::Vector3f worldXYZ = { 0.f,0.f,0.f };
	sf::Vector3i projectedXYZ = { 0,0,0 };
};

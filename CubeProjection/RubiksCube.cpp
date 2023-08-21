#pragma once

#include "RubiksCube.h"

RubiksCube::RubiksCube() {

}

void RubiksCube::setCubeProjectionCoordinates(Cube& cube1, const float fAngle, const float fPitch, const float fScale, const sf::Vector3f vCamera, sf::Vector2i screenSize,
	sf::Vector3i axisVector = { 0,0,0 }) {

	std::vector<sf::Vector3f> unitCube(8), rotCube(8), worldCube(8);

	unitCube[0] = { 0.f, 0.f, fScale }; // Front Top Left
	unitCube[1] = { 0.f, 0.f, 0.f }; // Front Bottom Left
	unitCube[2] = { fScale, 0.f, 0.f }; // Front Bottom Right
	unitCube[3] = { fScale, 0.f, fScale }; // Front Top Right
	unitCube[4] = { fScale, fScale, fScale }; // Back Top Right
	unitCube[5] = { fScale, fScale, 0.f }; // Back Bottom Right
	unitCube[6] = { 0.f, fScale, 0.f }; // Back Bottom Left
	unitCube[7] = { 0.f, fScale, fScale }; // Back Top left

	//vertices[0] = faces[FacePosition::Front].vertices[0]; // (0,0,1)
	//vertices[1] = faces[FacePosition::Front].vertices[1]; // (0,0,0)
	//vertices[2] = faces[FacePosition::Front].vertices[2]; // (1,0,0)
	//vertices[3] = faces[FacePosition::Front].vertices[3]; // (1,0,1)
	//vertices[4] = faces[FacePosition::Back].vertices[0]; // (1,1,1)
	//vertices[5] = faces[FacePosition::Back].vertices[1]; // (1,1,0)
	//vertices[6] = faces[FacePosition::Back].vertices[2]; // (0,1,0)
	//vertices[7] = faces[FacePosition::Back].vertices[3]; // (0,1,1)

	// Translate Cube in X-Z Plane
	for (int i = 0; i < 8; i++)
	{
		unitCube[i].x += (cube1.position.x * fScale - vCamera.x);
		unitCube[i].y += (cube1.position.y * fScale - vCamera.y);
		unitCube[i].z += (cube1.position.z * -fScale - vCamera.z);
	}

	// Rotate Cube in Z-Axis (up) around origin
	float s = sinf(fAngle);
	float c = cosf(fAngle);
	for (int i = 0; i < 8; i++)
	{
		rotCube[i].x = unitCube[i].x * c + unitCube[i].y * -s;
		rotCube[i].y = unitCube[i].x * s + unitCube[i].y * c;
		rotCube[i].z = unitCube[i].z;
	}

	// Rotate Cube in X-Axis around origin (tilt slighly overhead)
	s = sinf(fPitch);
	c = cosf(fPitch);
	for (int i = 0; i < 8; i++)
	{
		worldCube[i].x = rotCube[i].x;
		worldCube[i].y = rotCube[i].y * c + rotCube[i].z * -s;
		worldCube[i].z = rotCube[i].y * s + rotCube[i].z * c;
	}


	// Project Cube Orthographically - Full Screen Centered
	for (int i = 0; i < 8; i++)
	{
		cube1.vertices[i].projectedXYZ.x = worldCube[i].x + screenSize.x * 0.5f;
		cube1.vertices[i].projectedXYZ.y = worldCube[i].z + screenSize.y * 0.5f;
		cube1.vertices[i].projectedXYZ.z = worldCube[i].z;

		cube1.vertices[i].worldXYZ.x = worldCube[i].x;
		cube1.vertices[i].worldXYZ.y = worldCube[i].y;
		cube1.vertices[i].worldXYZ.z = worldCube[i].z;

	}

	// Set Face Vertices
	for (int i = 0; i < cube1.faces.size(); i++) {
		cube1.faces[i].vertices = { cube1.vertices[cube1.facesOrder[i][0]], cube1.vertices[cube1.facesOrder[i][1]],
									cube1.vertices[cube1.facesOrder[i][2]], cube1.vertices[cube1.facesOrder[i][3]] };
	}
}

sf::Vector2f RubiksCube::convertToRegularCoords(sf::Vector2f normalizedVal, int height, int width) {
	float fHeight = (float)height;
	float fWidth = (float)width;

	float xPart, yPart;
	xPart = normalizedVal.x * (fWidth - 1.f);
	yPart = normalizedVal.y * (fHeight - 1.f);

	return { xPart, yPart };
}

void RubiksCube::determineImagePosition(Vertex vertex1, Vertex vertex2, Vertex vertex3, sf::Vector2f& imagePosition, sf::Vector2i& imageSize)
{
	int x1, y1, x2, y2, x3, y3;
	x1 = vertex1.projectedXYZ.x;
	y1 = vertex1.projectedXYZ.y;
	x2 = vertex2.projectedXYZ.x;
	y2 = vertex2.projectedXYZ.y;
	x3 = vertex3.projectedXYZ.x;
	y3 = vertex3.projectedXYZ.y;


	if (y2 < y1)
	{
		std::swap(y1, y2);
		std::swap(x1, x2);
	}

	if (y3 < y1)
	{
		std::swap(y1, y3);
		std::swap(x1, x3);
	}

	if (y3 < y2)
	{
		std::swap(y2, y3);
		std::swap(x2, x3);
	}

	int dy1 = y2 - y1;
	int dx1 = x2 - x1;

	int dy2 = y3 - y1;
	int dx2 = x3 - x1;

	float tex_u, tex_v, tex_w;

	float dax_step = 0, dbx_step = 0,
		du1_step = 0, dv1_step = 0,
		du2_step = 0, dv2_step = 0,
		dw1_step = 0, dw2_step = 0;

	if (dy1) dax_step = dx1 / (float)abs(dy1);
	if (dy2) dbx_step = dx2 / (float)abs(dy2);

	int minX = std::min(x1, std::min(x2, x3));
	int maxX = std::max(x1, std::max(x2, x3));
	int theWidth = maxX - minX;
	int theHeight = y3 - y1;

	imagePosition = { (float)minX,(float)y1 };

	imageSize = { theWidth, theHeight + 1 };
}

void RubiksCube::textureTriangle(Vertex vertex1, Vertex vertex2, Vertex vertex3, sf::Vector3f uvw1, sf::Vector3f uvw2, sf::Vector3f uvw3, sf::Image originalImage, sf::Image& editImage,
	sf::Vector2f& imagePosition, bool existingImage = false, int changeX = 0, int changeY = 0)

{

	int x1, y1, x2, y2, x3, y3;
	x1 = vertex1.projectedXYZ.x;
	y1 = vertex1.projectedXYZ.y;
	x2 = vertex2.projectedXYZ.x;
	y2 = vertex2.projectedXYZ.y;
	x3 = vertex3.projectedXYZ.x;
	y3 = vertex3.projectedXYZ.y;


	float u1, v1, w1, u2, v2, w2, u3, v3, w3;
	u1 = uvw1.x;
	v1 = uvw1.y;
	w1 = uvw1.z;
	u2 = uvw2.x;
	v2 = uvw2.y;
	w2 = uvw2.z;
	u3 = uvw3.x;
	v3 = uvw3.y;
	w3 = uvw3.z;

	if (y2 < y1)
	{
		std::swap(y1, y2);
		std::swap(x1, x2);
		std::swap(u1, u2);
		std::swap(v1, v2);
		std::swap(w1, w2);
	}

	if (y3 < y1)
	{
		std::swap(y1, y3);
		std::swap(x1, x3);
		std::swap(u1, u3);
		std::swap(v1, v3);
		std::swap(w1, w3);
	}

	if (y3 < y2)
	{
		std::swap(y2, y3);
		std::swap(x2, x3);
		std::swap(u2, u3);
		std::swap(v2, v3);
		std::swap(w2, w3);
	}

	int dy1 = y2 - y1;
	int dx1 = x2 - x1;
	float dv1 = v2 - v1;
	float du1 = u2 - u1;
	float dw1 = w2 - w1;

	int dy2 = y3 - y1;
	int dx2 = x3 - x1;
	float dv2 = v3 - v1;
	float du2 = u3 - u1;
	float dw2 = w3 - w1;

	float tex_u, tex_v, tex_w;

	float dax_step = 0, dbx_step = 0,
		du1_step = 0, dv1_step = 0,
		du2_step = 0, dv2_step = 0,
		dw1_step = 0, dw2_step = 0;

	if (dy1) dax_step = (float)dx1 / (float)abs(dy1);
	if (dy2) dbx_step = (float)dx2 / (float)abs(dy2);

	if (dy1) du1_step = (float)du1 / (float)abs(dy1);
	if (dy1) dv1_step = (float)dv1 / (float)abs(dy1);
	if (dy1) dw1_step = (float)dw1 / (float)abs(dy1);

	if (dy2) du2_step = (float)du2 / (float)abs(dy2);
	if (dy2) dv2_step = (float)dv2 / (float)abs(dy2);
	if (dy2) dw2_step = (float)dw2 / (float)abs(dy2);

	int minX = std::min(x1, std::min(x2, x3));
	int maxX = std::max(x1, std::max(x2, x3));
	int theWidth = maxX - minX;
	int theHeight = y3 - y1;

	imagePosition = { (float)minX,(float)y1 };

	int originalImageHeight = originalImage.getSize().y;
	int originalImageWidth = originalImage.getSize().x;

	// Debug
	//std::cout << "editImage.size() = (" << theWidth << "," << theHeight << ")" << std::endl;

	if (existingImage == false) {
		editImage.create(theWidth, theHeight + 1, sf::Color::Transparent);
		//std::cout << "existingImage = false" << std::endl;
		//std::cout << "editImage.size() = " << editImage.getSize().x << "," << editImage.getSize().y << std::endl;
	}


	int rowCount, columnCount;
	rowCount = 0;
	columnCount = 0;

	if (dy1)
	{
		for (int i = y1; i <= y2; i++)
		{
			int ax = x1 + (float)(i - y1) * dax_step;
			int bx = x1 + (float)(i - y1) * dbx_step;

			float tex_su = u1 + (float)(i - y1) * du1_step;
			float tex_sv = v1 + (float)(i - y1) * dv1_step;
			float tex_sw = w1 + (float)(i - y1) * dw1_step;

			float tex_eu = u1 + (float)(i - y1) * du2_step;
			float tex_ev = v1 + (float)(i - y1) * dv2_step;
			float tex_ew = w1 + (float)(i - y1) * dw2_step;

			if (ax > bx)
			{
				std::swap(ax, bx);
				std::swap(tex_su, tex_eu);
				std::swap(tex_sv, tex_ev);
				std::swap(tex_sw, tex_ew);
			}

			tex_u = tex_su;
			tex_v = tex_sv;
			tex_w = tex_sw;

			float tstep = 1.0f / ((float)(bx - ax));
			float t = 0.0f;

			for (int j = ax; j < bx; j++)
			{
				tex_u = (1.0f - t) * tex_su + t * tex_eu;
				tex_v = (1.0f - t) * tex_sv + t * tex_ev;
				tex_w = (1.0f - t) * tex_sw + t * tex_ew;

				sf::Vector2f pixel = convertToRegularCoords({ tex_u,tex_v }, originalImageHeight, originalImageWidth);

				// Debug
				//std::cout << "Pass 1" << std::endl;

				sf::Color pixelColor = originalImage.getPixel(pixel.x, pixel.y);

				// Debug
				if (j - minX + changeX >= editImage.getSize().x || rowCount + changeY >= editImage.getSize().y
					|| j - minX + changeX <= 0 || rowCount + changeY <= 0) {
					//std::cout << "editImage.size() = (" << editImage.getSize().x << "," << editImage.getSize().y << ")" << std::endl;
					//std::cout << "(j-minX+changeX,rowCount+changeY) = (" << j - minX + changeX << "," << rowCount + changeY << ")" << std::endl;
					//std::cout << "y1 to y2" << std::endl;
				}


				//if (rowCount + changeY == 0) {
				//	continue;
				//}

				editImage.setPixel(j - minX + changeX, rowCount + changeY, pixelColor);


				//if (tex_w > pDepthBuffer[i * ScreenWidth() + j])
				//{
				//	Draw(j, i, tex->SampleGlyph(tex_u / tex_w, tex_v / tex_w), tex->SampleColour(tex_u / tex_w, tex_v / tex_w));
				//	pDepthBuffer[i * ScreenWidth() + j] = tex_w;
				//}
				t += tstep;
			}

			rowCount++;

		}
	}


	dy1 = y3 - y2;
	dx1 = x3 - x2;
	dv1 = v3 - v2;
	du1 = u3 - u2;
	dw1 = w3 - w2;

	if (dy1) dax_step = dx1 / (float)abs(dy1);
	if (dy2) dbx_step = dx2 / (float)abs(dy2);

	du1_step = 0, dv1_step = 0;
	if (dy1) du1_step = du1 / (float)abs(dy1);
	if (dy1) dv1_step = dv1 / (float)abs(dy1);
	if (dy1) dw1_step = dw1 / (float)abs(dy1);


	if (dy1)
	{
		for (int i = y2; i <= y3; i++)
		{
			int ax = x2 + (float)(i - y2) * dax_step;
			int bx = x1 + (float)(i - y1) * dbx_step;

			float tex_su = u2 + (float)(i - y2) * du1_step;
			float tex_sv = v2 + (float)(i - y2) * dv1_step;
			float tex_sw = w2 + (float)(i - y2) * dw1_step;

			float tex_eu = u1 + (float)(i - y1) * du2_step;
			float tex_ev = v1 + (float)(i - y1) * dv2_step;
			float tex_ew = w1 + (float)(i - y1) * dw2_step;

			if (ax > bx)
			{
				std::swap(ax, bx);
				std::swap(tex_su, tex_eu);
				std::swap(tex_sv, tex_ev);
				std::swap(tex_sw, tex_ew);
			}

			tex_u = tex_su;
			tex_v = tex_sv;
			tex_w = tex_sw;

			float tstep = 1.0f / ((float)(bx - ax));
			float t = 0.0f;

			for (int j = ax; j < bx; j++)
			{
				tex_u = (1.0f - t) * tex_su + t * tex_eu;
				tex_v = (1.0f - t) * tex_sv + t * tex_ev;
				tex_w = (1.0f - t) * tex_sw + t * tex_ew;

				sf::Vector2f pixel = convertToRegularCoords({ tex_u,tex_v }, originalImageHeight, originalImageWidth);
				sf::Color pixelColor = originalImage.getPixel(pixel.x, pixel.y);

				// Debug
				//std::cout << "Pass 2 " << std::endl;

				if (j - minX + changeX >= editImage.getSize().x || rowCount + changeY >= editImage.getSize().y
					|| j - minX + changeX <= 0 || rowCount + changeY <= 0) {
					//std::cout << "editImage.size() = (" << editImage.getSize().x << "," << editImage.getSize().y << ")" << std::endl;
					//std::cout << "(j-minX+changeX,rowCount+changeY) = (" << j - minX + changeX << "," << rowCount + changeY << ")" << std::endl;
					//std::cout << "y2 to y3" << std::endl;
					//std::cout << "i = " << i << std::endl;
				}

				//if (rowCount + changeY == 0) {
				//	continue;
				//}

				editImage.setPixel(j - minX + changeX, rowCount + changeY, pixelColor);

				//if (tex_w > pDepthBuffer[i * ScreenWidth() + j])
				//{
				//	Draw(j, i, tex->SampleGlyph(tex_u / tex_w, tex_v / tex_w), tex->SampleColour(tex_u / tex_w, tex_v / tex_w));
				//	pDepthBuffer[i * ScreenWidth() + j] = tex_w;
				//}
				t += tstep;
			}

			rowCount++;
		}
	}
}

void RubiksCube::combineTextureTriangles(Vertex vertex1, Vertex vertex2, Vertex vertex3, Vertex vertex4, sf::Vector3f uvw1, sf::Vector3f uvw2, sf::Vector3f uvw3, sf::Vector3f uvw4,
	sf::Image originalImage, sf::Image& editImage, sf::Vector2f& imagePosition)
{

	sf::Vector2i imageSizeLeft, imageSizeRight;

	sf::Image leftImage, rightImage;
	sf::Vector2f leftImagePositionTL, rightImagePositionTL, leftImagePositionBR, rightImagePositionBR;

	determineImagePosition(vertex1, vertex2, vertex3, leftImagePositionTL, imageSizeLeft);
	determineImagePosition(vertex1, vertex3, vertex4, rightImagePositionTL, imageSizeRight);

	leftImagePositionBR = { leftImagePositionTL.x + imageSizeLeft.x, leftImagePositionTL.y + imageSizeLeft.y };
	rightImagePositionBR = { rightImagePositionTL.x + imageSizeRight.x, rightImagePositionTL.y + imageSizeRight.y };

	// Debug
	//std::cout << "leftImagePosition = (" << leftImagePosition.x << "," << leftImagePosition.y << ")" << std::endl;
	//std::cout << "rightImagePosition = (" << rightImagePosition.x << "," << rightImagePosition.y << ")" << std::endl;
	//std::cout << "imageSizeLeft = (" << imageSizeLeft.x << "," << imageSizeLeft.y << ")" << std::endl;
	//std::cout << "imageSizeRight = (" << imageSizeRight.x << "," << imageSizeRight.y << ")" << std::endl;

	//textureTriangle(vertex1, vertex2, vertex3, uvw1, uvw2, uvw3, originalImage, leftImage, leftImagePosition);
	//textureTriangle(vertex1, vertex3, vertex4, uvw1, uvw3, uvw4, originalImage, rightImage, rightImagePosition);

	int leftStartY, rightStartY, leftStartX, rightStartX;
	float theWidth, theHeight;

	theWidth = std::max(rightImagePositionBR.x, leftImagePositionBR.x) - std::min(rightImagePositionTL.x, leftImagePositionTL.x);
	theHeight = std::max(rightImagePositionBR.y, leftImagePositionBR.y) - std::min(rightImagePositionTL.y, leftImagePositionTL.y);

	leftStartX = leftImagePositionTL.x - std::min(rightImagePositionTL.x, leftImagePositionTL.x);
	leftStartY = leftImagePositionTL.y - std::min(rightImagePositionTL.y, leftImagePositionTL.y);

	rightStartX = rightImagePositionTL.x - std::min(rightImagePositionTL.x, leftImagePositionTL.x);
	rightStartY = rightImagePositionTL.y - std::min(rightImagePositionTL.y, leftImagePositionTL.y);


	//if (leftImagePosition.y < rightImagePosition.y) {
	//	theHeight = (rightImagePosition.y - leftImagePosition.y) + imageSizeRight.y;
	//	rightStartY = leftImagePosition.y - rightImagePosition.y;
	//	leftStartY = 0;
	//}
	//else {
	//	theHeight = (leftImagePosition.y - rightImagePosition.y) + imageSizeLeft.y;
	//	leftStartY = rightImagePosition.y - leftImagePosition.y;
	//	rightStartY = 0;
	//}


	//if (leftImagePosition.x < rightImagePosition.x) {
	//	theWidth = (rightImagePosition.x - leftImagePosition.x) + imageSizeRight.x;
	//	rightStartX = leftImagePosition.x - rightImagePosition.x;
	//	leftStartX = 0;
	//}
	//else {
	//	theWidth = (leftImagePosition.x - rightImagePosition.x) + imageSizeLeft.x;
	//	leftStartX = rightImagePosition.x - leftImagePosition.x;
	//	rightStartX = 0;
	//}

	imagePosition = { std::min(leftImagePositionTL.x,rightImagePositionTL.x), std::min(leftImagePositionTL.y,rightImagePositionTL.y) };
	sf::Vector2i widthHeight = { (int)theWidth, (int)theHeight };

	if (widthHeight.x == 0 || widthHeight.y == 0) {
		return;
	}

	editImage.create(widthHeight.x, widthHeight.y, sf::Color::Transparent);

	// Debug
	//std::cout << "widthHeight = (" << widthHeight.x << "," << widthHeight.y << ")" << std::endl;
	//std::cout << "editImage.size() before = (" << editImage.getSize().x << "," << editImage.getSize().y << ")" << std::endl;

	textureTriangle(vertex1, vertex2, vertex3, uvw1, uvw2, uvw3, originalImage, editImage, leftImagePositionTL, true, abs(leftStartX), abs(leftStartY));
	textureTriangle(vertex1, vertex3, vertex4, uvw1, uvw3, uvw4, originalImage, editImage, rightImagePositionTL, true, abs(rightStartX), abs(rightStartY));

	// Debug
	//if (widthHeight.y < 40) {
	//	std::cout << "leftImage.height = " << leftImage.getSize().y << "; leftImage.width = " << leftImage.getSize().x << std::endl;
	//	std::cout << "rightImage.height = " << rightImage.getSize().y << "; rightImage.width = " << rightImage.getSize().x << std::endl;
	//	std::cout << "widthHeight.y = " << widthHeight.y << std::endl;
	//	std::cout << "(leftImagePosition.y - rightImagePosition.y) = " << (leftImagePosition.y - rightImagePosition.y) << std::endl;
	//	std::cout << "leftImagePosition = (" << leftImagePosition.x << "," << leftImagePosition.y << ")" << std::endl;
	//	std::cout << "rightImagePosition = (" << rightImagePosition.x << "," << rightImagePosition.y << ")" << std::endl;
	//	std::cout << std::endl;
	//}

	//for (int i = 0; i < widthHeight.y; i++) {
	//	for (int j = 0; j < widthHeight.x; j++) {

	//		if (leftStartY + i > -1 && leftStartY + i < leftImage.getSize().y
	//			&& j + leftStartX > -1 && j + leftStartX < leftImage.getSize().x) {
	//			if (leftImage.getPixel(leftStartX + j, leftStartY + i) != sf::Color::Transparent) {
	//				editImage.setPixel(j, i, leftImage.getPixel(leftStartX + j, leftStartY + i));
	//				continue;
	//			}
	//		}

	//		if (rightStartY + i > -1 && rightStartY + i < rightImage.getSize().y
	//			&& j + rightStartX > -1 && j + rightStartX < rightImage.getSize().x) {
	//			if (rightImage.getPixel(rightStartX + j, rightStartY + i) != sf::Color::Transparent) {
	//				editImage.setPixel(j, i, rightImage.getPixel(rightStartX + j, rightStartY + i));
	//			}
	//		}

	//	}
	//}


}

void RubiksCube::calculateVisibleFaces(Cube& cube1) {

	auto checkNormal = [&](int v1, int v2, int v3)
	{
		sf::Vector2i a = { cube1.vertices[v1].projectedXYZ.x, cube1.vertices[v1].projectedXYZ.y };
		sf::Vector2i b = { cube1.vertices[v2].projectedXYZ.x, cube1.vertices[v2].projectedXYZ.y };
		sf::Vector2i c = { cube1.vertices[v3].projectedXYZ.x, cube1.vertices[v3].projectedXYZ.y };

		sf::Vector2i ba = { b.x - a.x, b.y - a.y };
		sf::Vector2i ca = { c.x - a.x, c.y - a.y };

		int crossProduct = ba.x * ca.y - ba.y * ca.x;

		return  crossProduct > 0;
	};

	cube1.visibleFaces[FacePosition::Top] = checkNormal(cube1.facesOrder[FacePosition::Top][0], cube1.facesOrder[FacePosition::Top][1],
		cube1.facesOrder[FacePosition::Top][2]);
	cube1.visibleFaces[FacePosition::Bottom] = checkNormal(cube1.facesOrder[FacePosition::Bottom][0], cube1.facesOrder[FacePosition::Bottom][1],
		cube1.facesOrder[FacePosition::Bottom][2]);
	cube1.visibleFaces[FacePosition::Left] = checkNormal(cube1.facesOrder[FacePosition::Left][0], cube1.facesOrder[FacePosition::Left][1],
		cube1.facesOrder[FacePosition::Left][2]);
	cube1.visibleFaces[FacePosition::Right] = checkNormal(cube1.facesOrder[FacePosition::Right][0], cube1.facesOrder[FacePosition::Right][1],
		cube1.facesOrder[FacePosition::Right][2]);
	cube1.visibleFaces[FacePosition::Front] = checkNormal(cube1.facesOrder[FacePosition::Front][0], cube1.facesOrder[FacePosition::Front][1],
		cube1.facesOrder[FacePosition::Front][2]);
	cube1.visibleFaces[FacePosition::Back] = checkNormal(cube1.facesOrder[FacePosition::Back][0], cube1.facesOrder[FacePosition::Back][1],
		cube1.facesOrder[FacePosition::Back][2]);
}

void RubiksCube::rotateCubeAboutArbitraryAxis(Cube& cube1, sf::Vector3f axisVector, sf::Vector3f midpoint, float angleAmount, float fAngle, float fPitch, float fScale,
	sf::Vector3f vCamera, sf::Vector2i screenSize)
{
	std::vector<sf::Vector3f> unitCube(8), rotAxisCube(8), rotCube(8), worldCube(8);

	unitCube[0] = { 0.f, 0.f, fScale }; // Front Top Left
	unitCube[1] = { 0.f, 0.f, 0.f }; // Front Bottom Left
	unitCube[2] = { fScale, 0.f, 0.f }; // Front Bottom Right
	unitCube[3] = { fScale, 0.f, fScale }; // Front Top Right
	unitCube[4] = { fScale, fScale, fScale }; // Back Top Right
	unitCube[5] = { fScale, fScale, 0.f }; // Back Bottom Right
	unitCube[6] = { 0.f, fScale, 0.f }; // Back Bottom Left
	unitCube[7] = { 0.f, fScale, fScale }; // Back Top left

	//unitCube[0] = { 0.f - 0.5f - cube1.position.x, 0.f - 0.5f - cube1.position.y, (1.f - 0.5f + cube1.position.z)}; // Front Top Left
	//unitCube[1] = { 0.f - 0.5f - cube1.position.x, 0.f - 0.5f - cube1.position.y, 0.f - 0.5f + cube1.position.z }; // Front Bottom Left
	//unitCube[2] = { (1.f - 0.5f) - cube1.position.x, 0.f - 0.5f - cube1.position.y, 0.f - 0.5f + cube1.position.z }; // Front Bottom Right
	//unitCube[3] = { (1.f - 0.5f) - cube1.position.x, 0.f - 0.5f - cube1.position.y, (1.f - 0.5f) + cube1.position.z }; // Front Top Right
	//unitCube[4] = { (1.f - 0.5f) - cube1.position.x, (1.f - 0.5f) - cube1.position.y, (1.f - 0.5f) + cube1.position.z }; // Back Top Right
	//unitCube[5] = { (1.f - 0.5f) - cube1.position.x, (1.f - 0.5f) - cube1.position.y, 0.f - 0.5f + cube1.position.z }; // Back Bottom Right
	//unitCube[6] = { 0.f - 0.5f - cube1.position.x, (1.f - 0.5f) - cube1.position.y, 0.f - 0.5f + cube1.position.z }; // Back Bottom Left
	//unitCube[7] = { 0.f - 0.5f - cube1.position.x, (1.f - 0.5f) - cube1.position.y, (1.f - 0.5f) + cube1.position.z }; // Back Top left

	// Debug
	//std::cout << "unitCube[0] = (" << unitCube[0].x << "," << unitCube[0].y << "," << unitCube[0].z << ")" << std::endl;
	//std::cout << "unitCube[1] = (" << unitCube[1].x << "," << unitCube[1].y << "," << unitCube[1].z << ")" << std::endl;
	//std::cout << "unitCube[2] = (" << unitCube[2].x << "," << unitCube[2].y << "," << unitCube[2].z << ")" << std::endl;
	//std::cout << "unitCube[3] = (" << unitCube[3].x << "," << unitCube[3].y << "," << unitCube[3].z << ")" << std::endl;
	//std::cout << "unitCube[4] = (" << unitCube[4].x << "," << unitCube[4].y << "," << unitCube[4].z << ")" << std::endl;
	//std::cout << "unitCube[5] = (" << unitCube[5].x << "," << unitCube[5].y << "," << unitCube[5].z << ")" << std::endl;
	//std::cout << "unitCube[6] = (" << unitCube[6].x << "," << unitCube[6].y << "," << unitCube[6].z << ")" << std::endl;
	//std::cout << "unitCube[7] = (" << unitCube[7].x << "," << unitCube[7].y << "," << unitCube[7].z << ")" << std::endl;

	//vertices[0] = faces[FacePosition::Front].vertices[0]; // (0,0,1)
	//vertices[1] = faces[FacePosition::Front].vertices[1]; // (0,0,0)
	//vertices[2] = faces[FacePosition::Front].vertices[2]; // (1,0,0)
	//vertices[3] = faces[FacePosition::Front].vertices[3]; // (1,0,1)
	//vertices[4] = faces[FacePosition::Back].vertices[0]; // (1,1,1)
	//vertices[5] = faces[FacePosition::Back].vertices[1]; // (1,1,0)
	//vertices[6] = faces[FacePosition::Back].vertices[2]; // (0,1,0)
	//vertices[7] = faces[FacePosition::Back].vertices[3]; // (0,1,1)


	// Translate Cube in X-Z Plane
	for (int i = 0; i < 8; i++)
	{
		unitCube[i].x += ((cube1.position.x - midpoint.x) * fScale);
		unitCube[i].y += ((cube1.position.y - midpoint.y) * fScale);
		unitCube[i].z += ((cube1.position.z - midpoint.z) * -fScale);
	}

	// Rotate Cube about Arbitrary Axis
	float sf = sinf(angleAmount);
	float cf = cosf(angleAmount);
	for (int i = 0; i < 8; i++) {
		rotAxisCube[i].x = (cf + powf(axisVector.x, 2) * (1.f - cf)) * unitCube[i].x
			+ (axisVector.x * axisVector.y * (1.f - cf) - axisVector.z * sf) * unitCube[i].y
			+ (axisVector.x * axisVector.z * (1.f - cf) + axisVector.y * sf) * unitCube[i].z;
		rotAxisCube[i].y = (axisVector.y * axisVector.x * (1.f - cf) + axisVector.z * sf) * unitCube[i].x
			+ (cf + powf(axisVector.y, 2) * (1.f - cf)) * unitCube[i].y
			+ (axisVector.y * axisVector.z * (1.f - cf) - axisVector.x * sf) * unitCube[i].z;
		rotAxisCube[i].z = (axisVector.z * axisVector.x * (1.f - cf) - axisVector.y * sf) * unitCube[i].x
			+ (axisVector.z * axisVector.y * (1.f - cf) + axisVector.x * sf) * unitCube[i].y
			+ (cf + powf(axisVector.z, 2) * (1.f - cf)) * unitCube[i].z;

		//rotAxisCube[i].x += (0.5f + cube1.position.x);
		//rotAxisCube[i].y += (0.5f + cube1.position.y);
		//rotAxisCube[i].z += (0.5f - cube1.position.z);

		rotAxisCube[i].x += midpoint.x * fScale - vCamera.x;
		rotAxisCube[i].y += midpoint.y * fScale - vCamera.y;
		rotAxisCube[i].z += midpoint.z * -fScale - vCamera.z;

		// Debug
		//std::cout << "unitCube[" << i << "] = (" << unitCube[0].x << ", " << unitCube[0].y << ", " << unitCube[0].z << ")" << std::endl;

	}


	// Rotate Cube in Z-Axis (up) around origin
	float s = sinf(fAngle);
	float c = cosf(fAngle);
	for (int i = 0; i < 8; i++)
	{
		rotCube[i].x = rotAxisCube[i].x * c + rotAxisCube[i].y * -s;
		rotCube[i].y = rotAxisCube[i].x * s + rotAxisCube[i].y * c;
		rotCube[i].z = rotAxisCube[i].z;
	}

	// Rotate Cube in X-Axis around origin (tilt slighly overhead)
	s = sinf(fPitch);
	c = cosf(fPitch);
	for (int i = 0; i < 8; i++)
	{
		worldCube[i].x = rotCube[i].x;
		worldCube[i].y = rotCube[i].y * c - rotCube[i].z * s;
		worldCube[i].z = rotCube[i].y * s + rotCube[i].z * c;
	}


	// Project Cube Orthographically - Full Screen Centered
	for (int i = 0; i < 8; i++)
	{
		cube1.vertices[i].projectedXYZ.x = worldCube[i].x + ((float)screenSize.x) * 0.5f;
		cube1.vertices[i].projectedXYZ.y = worldCube[i].z + ((float)screenSize.y) * 0.5f;
		cube1.vertices[i].projectedXYZ.z = worldCube[i].z;

		cube1.vertices[i].worldXYZ.x = worldCube[i].x;
		cube1.vertices[i].worldXYZ.y = worldCube[i].y;
		cube1.vertices[i].worldXYZ.z = worldCube[i].z;

		// Debug
		//std::cout << "cube1.vertices[" << i << "].projectedXYZ = (" << cube1.vertices[i].projectedXYZ.x << "," << cube1.vertices[i].projectedXYZ.y << ",";
		//std::cout << cube1.vertices[i].projectedXYZ.z << ")" << std::endl;

	}

	// Set Face Vertices
	for (int i = 0; i < cube1.faces.size(); i++) {
		cube1.faces[i].vertices = { cube1.vertices[cube1.facesOrder[i][0]], cube1.vertices[cube1.facesOrder[i][1]],
									cube1.vertices[cube1.facesOrder[i][2]], cube1.vertices[cube1.facesOrder[i][3]] };
	}
}

int RubiksCube::determineColorIndex(char c)
{


	//std::vector<sf::Image*> faceImages = { greenSquare, blueSquare, whiteSquare, yellowSquare, redSquare, orangeSquare, blackSquare };


	switch (c) {
	case 'W':
		return 2;
	case 'R':
		return 4;
	case 'B':
		return 1;
	case 'O':
		return 5;
	case 'G':
		return 0;
	case 'Y':
		return 3;
	}

	return -1;
}

void RubiksCube::create3x3Cube(std::vector<sf::Image*> faceImages, std::string theCube)
{

	std::unordered_map<std::string, std::vector<int>> individualCubeColors;

	individualCubeColors = { {"200", {determineColorIndex(theCube[44]), 6, determineColorIndex(theCube[51]), 6, determineColorIndex(theCube[15]), 6}}, // RYG -> {44, n, 51, n, 15, n}
							{"210", {determineColorIndex(theCube[43]), 6, determineColorIndex(theCube[52]), 6, 6, 6}}, // YG -> {43, n, 52, n, n, n}
							{"220", {determineColorIndex(theCube[42]), 6, determineColorIndex(theCube[53]), 6, 6, determineColorIndex(theCube[35])}}, // OYG -> {42, n, 53, n, n, 35}
							{"100", {determineColorIndex(theCube[41]), 6, 6, 6, determineColorIndex(theCube[12]), 6}}, // GR -> {41, n, n, n, 12, n}
							{"110", {determineColorIndex(theCube[40]), 6, 6, 6, 6, 6}}, // G -> {40, n, n, n, n, n}
							{"120", {determineColorIndex(theCube[39]), 6, 6, 6, 6, determineColorIndex(theCube[32])}}, // GO -> {39, n, n, n, n, 32}
							{"000", {determineColorIndex(theCube[38]), 6, 6, determineColorIndex(theCube[0]), determineColorIndex(theCube[9]), 6}}, // RWG -> {38, n, n, 0, 9, n}
							{"010", {determineColorIndex(theCube[37]), 6, 6, determineColorIndex(theCube[1]), 6, 6}}, // GW -> {37, n, n, 1, n, n}
							{"020", {determineColorIndex(theCube[36]), 6, 6, determineColorIndex(theCube[2]), 6, determineColorIndex(theCube[29])}}, // OWG -> {36, n, n, 2, n, 29}
							{"201", {6, 6, determineColorIndex(theCube[48]), 6, determineColorIndex(theCube[16]), 6}}, // RY -> {n, n, 48, n, 16, n}
							{"211", {6, 6, determineColorIndex(theCube[49]), 6, 6, 6}}, // Y -> {n, n, 49, n, n, n}
							{"221", {6, 6, determineColorIndex(theCube[50]), 6, 6, determineColorIndex(theCube[35])}}, // OY -> {n, n, 50, n, n, 34}
							{"101", {6, 6, 6, 6, determineColorIndex(theCube[13]), 6}}, // R -> {n, n, n, n, 13, n}
							{"111", {6, 6, 6, 6, 6, 6}}, // Don't draw middle cube
							{"121", {6, 6, 6, 6, 6, determineColorIndex(theCube[31])}}, // O -> {n, n, n, n, n, 31}
							{"001", {6, 6, 6, determineColorIndex(theCube[3]), determineColorIndex(theCube[10]), 6}}, // RW -> {n, n, n, 3, 10, n}
							{"011", {6, 6, 6, determineColorIndex(theCube[4]), 6, 6}}, // W -> {n, n, n, 4, n, n}
							{"021", {6, 6, 6, determineColorIndex(theCube[5]), 6, determineColorIndex(theCube[28])}}, // OW -> {n, n, n, 5, n, 28}
							{"202", {6, determineColorIndex(theCube[24]), determineColorIndex(theCube[45]), 6, determineColorIndex(theCube[17]), 6}}, // RYB -> {n, 24, 45, n, 17, n}
							{"212", {6, determineColorIndex(theCube[25]), determineColorIndex(theCube[46]), 6, 6, 6}}, // BY -> {n, 25, 46, n, n, n}
							{"222", {6, determineColorIndex(theCube[26]), determineColorIndex(theCube[47]), 6, 6, determineColorIndex(theCube[33])}}, // OYB -> {n, 26, 47, n, n, 33}
							{"102", {6, determineColorIndex(theCube[21]), 6, 6, determineColorIndex(theCube[14]), 6}}, // RB -> {n, 21, n, n, 14, n}
							{"112", {6, determineColorIndex(theCube[22]), 6, 6, 6, 6}}, // B -> {n, 22, n, n, n, n}
							{"122", {6, determineColorIndex(theCube[23]), 6, 6, 6, determineColorIndex(theCube[30])}}, // OB -> {n, 23, n, n, n, 30}
							{"002", {6, determineColorIndex(theCube[18]), 6, determineColorIndex(theCube[6]), determineColorIndex(theCube[11]), 6}}, // RWB -> {n, 18, n, 6, 11, n}
							{"012", {6, determineColorIndex(theCube[19]), 6, determineColorIndex(theCube[7]), 6, 6}}, // BW -> {n, 19, n, 7, n, n}
							{"022", {6, determineColorIndex(theCube[20]), 6, determineColorIndex(theCube[8]), 6, determineColorIndex(theCube[27])}} }; // BWO -> {n, 20, n, 8, n, 27}

	allCubes.resize(3);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {

				std::string s = "";
				s += std::to_string(j);
				s += std::to_string(k);
				s += std::to_string(i);

				auto finder = individualCubeColors.find(s);
				std::vector<int> cols;


				if (finder == individualCubeColors.end())
				{
					std::cout << "finder -> not found" << std::endl;
					continue;
				}
				else {
					cols = finder->second;
				}

				Cube* oneCube = new Cube;
				oneCube->position = { (float)j, (float)k, (float)i };
				//oneCube->loadFaceImages(faceImages[0], faceImages[1], faceImages[2], faceImages[3], faceImages[4], faceImages[5]);
				oneCube->loadFaceImages(faceImages[cols[0]], faceImages[cols[1]], faceImages[cols[3]], faceImages[cols[2]],
					faceImages[cols[4]], faceImages[cols[5]]);
				allCubes[i].push_back(oneCube);
			}
		}
	}
}

void RubiksCube::edit3x3Cube(std::vector<sf::Image*> faceImages,
	std::string theCube)
{
	std::unordered_map<std::string, std::vector<int>> individualCubeColors;

	individualCubeColors = { {"200", {determineColorIndex(theCube[44]), 6, determineColorIndex(theCube[51]), 6, determineColorIndex(theCube[15]), 6}}, // RYG -> {44, n, 51, n, 15, n}
							{"210", {determineColorIndex(theCube[43]), 6, determineColorIndex(theCube[52]), 6, 6, 6}}, // YG -> {43, n, 52, n, n, n}
							{"220", {determineColorIndex(theCube[42]), 6, determineColorIndex(theCube[53]), 6, 6, determineColorIndex(theCube[35])}}, // OYG -> {42, n, 53, n, n, 35}
							{"100", {determineColorIndex(theCube[41]), 6, 6, 6, determineColorIndex(theCube[12]), 6}}, // GR -> {41, n, n, n, 12, n}
							{"110", {determineColorIndex(theCube[40]), 6, 6, 6, 6, 6}}, // G -> {40, n, n, n, n, n}
							{"120", {determineColorIndex(theCube[39]), 6, 6, 6, 6, determineColorIndex(theCube[32])}}, // GO -> {39, n, n, n, n, 32}
							{"000", {determineColorIndex(theCube[38]), 6, 6, determineColorIndex(theCube[0]), determineColorIndex(theCube[9]), 6}}, // RWG -> {38, n, n, 0, 9, n}
							{"010", {determineColorIndex(theCube[37]), 6, 6, determineColorIndex(theCube[1]), 6, 6}}, // GW -> {37, n, n, 1, n, n}
							{"020", {determineColorIndex(theCube[36]), 6, 6, determineColorIndex(theCube[2]), 6, determineColorIndex(theCube[29])}}, // OWG -> {36, n, n, 2, n, 29}
							{"201", {6, 6, determineColorIndex(theCube[48]), 6, determineColorIndex(theCube[16]), 6}}, // RY -> {n, n, 48, n, 16, n}
							{"211", {6, 6, determineColorIndex(theCube[49]), 6, 6, 6}}, // Y -> {n, n, 49, n, n, n}
							{"221", {6, 6, determineColorIndex(theCube[50]), 6, 6, determineColorIndex(theCube[34])}}, // OY -> {n, n, 50, n, n, 34}
							{"101", {6, 6, 6, 6, determineColorIndex(theCube[13]), 6}}, // R -> {n, n, n, n, 13, n}
							{"111", {6, 6, 6, 6, 6, 6}}, // Don't draw middle cube
							{"121", {6, 6, 6, 6, 6, determineColorIndex(theCube[31])}}, // O -> {n, n, n, n, n, 31}
							{"001", {6, 6, 6, determineColorIndex(theCube[3]), determineColorIndex(theCube[10]), 6}}, // RW -> {n, n, n, 3, 10, n}
							{"011", {6, 6, 6, determineColorIndex(theCube[4]), 6, 6}}, // W -> {n, n, n, 4, n, n}
							{"021", {6, 6, 6, determineColorIndex(theCube[5]), 6, determineColorIndex(theCube[28])}}, // OW -> {n, n, n, 5, n, 28}
							{"202", {6, determineColorIndex(theCube[24]), determineColorIndex(theCube[45]), 6, determineColorIndex(theCube[17]), 6}}, // RYB -> {n, 24, 45, n, 17, n}
							{"212", {6, determineColorIndex(theCube[25]), determineColorIndex(theCube[46]), 6, 6, 6}}, // BY -> {n, 25, 46, n, n, n}
							{"222", {6, determineColorIndex(theCube[26]), determineColorIndex(theCube[47]), 6, 6, determineColorIndex(theCube[33])}}, // OYB -> {n, 26, 47, n, n, 33}
							{"102", {6, determineColorIndex(theCube[21]), 6, 6, determineColorIndex(theCube[14]), 6}}, // RB -> {n, 21, n, n, 14, n}
							{"112", {6, determineColorIndex(theCube[22]), 6, 6, 6, 6}}, // B -> {n, 22, n, n, n, n}
							{"122", {6, determineColorIndex(theCube[23]), 6, 6, 6, determineColorIndex(theCube[30])}}, // OB -> {n, 23, n, n, n, 30}
							{"002", {6, determineColorIndex(theCube[18]), 6, determineColorIndex(theCube[6]), determineColorIndex(theCube[11]), 6}}, // RWB -> {n, 18, n, 6, 11, n}
							{"012", {6, determineColorIndex(theCube[19]), 6, determineColorIndex(theCube[7]), 6, 6}}, // BW -> {n, 19, n, 7, n, n}
							{"022", {6, determineColorIndex(theCube[20]), 6, determineColorIndex(theCube[8]), 6, determineColorIndex(theCube[27])}} }; // BWO -> {n, 20, n, 8, n, 27}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {

				std::string s = "";
				s += std::to_string(j);
				s += std::to_string(k);
				s += std::to_string(i);

				auto finder = individualCubeColors.find(s);
				std::vector<int> cols;

				if (finder == individualCubeColors.end())
				{
					std::cout << "finder -> not found" << std::endl;
					continue;
				}
				else {
					cols = finder->second;
				}

				allCubes[i][j * 3 + k]->position = { (float)j, (float)k, (float)i };
				//oneCube->loadFaceImages(faceImages[0], faceImages[1], faceImages[2], faceImages[3], faceImages[4], faceImages[5]);
				allCubes[i][j * 3 + k]->loadFaceImages(faceImages[cols[0]], faceImages[cols[1]], faceImages[cols[3]], faceImages[cols[2]],
					faceImages[cols[4]], faceImages[cols[5]]);

			}
		}
	}
}

void RubiksCube::rotateFront(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
	float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
	std::map<std::vector<int>, bool>& registeredProjectedVertexSets)
{

	float signChange = 1.f;

	for (int a = 2; a >= 0; a--)
	{

		std::vector<Cube*> cubeList;

		for (int b = 0; b < 3; b++)
		{
			//allCubes[b][a*3];
			//allCubes[b][a*3 + 1];
			//allCubes[b][a*3 + 2];

			cubeList.push_back(allCubes[b][a * 3]);
			cubeList.push_back(allCubes[b][a * 3 + 1]);
			cubeList.push_back(allCubes[b][a * 3 + 2]);


		}

		for (auto& cube : cubeList)
		{

			// Rotate About Y-Axis
			rotateCubeAboutArbitraryAxis(*cube, { 1,0,0 }, midpointRowPosition, signChange * arbitraryAngleAmount, fCameraAngle, fCameraPitch,
				fCameraZoom, { vCameraPos.x,vCameraPos.y,0.f }, { screenWidth,screenHeight });

			// Get the visible Faces of the Cube
			calculateVisibleFaces(*cube);

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
				}
			}
		}

		midpointRowPosition.x += 1.f;
		signChange *= -1.f;
		signChange *= 0.f;

	}

}


void RubiksCube::rotateFrontCCW(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
	float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
	std::map<std::vector<int>, bool>& registeredProjectedVertexSets)
{

	float signChange = -1.f;

	for (int a = 2; a >= 0; a--)
	{

		std::vector<Cube*> cubeList;

		for (int b = 0; b < 3; b++)
		{
			//allCubes[b][a*3];
			//allCubes[b][a*3 + 1];
			//allCubes[b][a*3 + 2];

			cubeList.push_back(allCubes[b][a * 3]);
			cubeList.push_back(allCubes[b][a * 3 + 1]);
			cubeList.push_back(allCubes[b][a * 3 + 2]);


		}

		for (auto& cube : cubeList)
		{

			// Rotate About Y-Axis
			rotateCubeAboutArbitraryAxis(*cube, { 1,0,0 }, midpointRowPosition, signChange * arbitraryAngleAmount, fCameraAngle, fCameraPitch,
				fCameraZoom, { vCameraPos.x,vCameraPos.y,0.f }, { screenWidth,screenHeight });

			// Get the visible Faces of the Cube
			calculateVisibleFaces(*cube);

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
				}
			}
		}

		midpointRowPosition.x += 1.f;
		signChange *= -1.f;
		signChange *= 0.f;

	}

}

void RubiksCube::rotateBack(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
	float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
	std::map<std::vector<int>, bool>& registeredProjectedVertexSets)
{

	float signChange = -1.f;

	for (int a = 0; a < 3; a++)
	{

		std::vector<Cube*> cubeList;

		for (int b = 0; b < 3; b++)
		{
			//allCubes[b][a*3];
			//allCubes[b][a*3 + 1];
			//allCubes[b][a*3 + 2];


			cubeList.push_back(allCubes[b][a * 3]);
			cubeList.push_back(allCubes[b][a * 3 + 1]);
			cubeList.push_back(allCubes[b][a * 3 + 2]);


		}

		for (auto& cube : cubeList)
		{

			// Rotate About Y-Axis
			rotateCubeAboutArbitraryAxis(*cube, { 1,0,0 }, midpointRowPosition, signChange * arbitraryAngleAmount, fCameraAngle, fCameraPitch,
				fCameraZoom, { vCameraPos.x,vCameraPos.y,0.f }, { screenWidth,screenHeight });

			// Get the visible Faces of the Cube
			calculateVisibleFaces(*cube);

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
				}
			}
		}

		midpointRowPosition.x += 1.f;
		signChange *= -1.f;
		signChange *= 0.f;

	}

}

void RubiksCube::rotateBackCCW(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
	float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
	std::map<std::vector<int>, bool>& registeredProjectedVertexSets)
{

	float signChange = 1.f;

	for (int a = 0; a < 3; a++)
	{

		std::vector<Cube*> cubeList;

		for (int b = 0; b < 3; b++)
		{
			//allCubes[b][a*3];
			//allCubes[b][a*3 + 1];
			//allCubes[b][a*3 + 2];


			cubeList.push_back(allCubes[b][a * 3]);
			cubeList.push_back(allCubes[b][a * 3 + 1]);
			cubeList.push_back(allCubes[b][a * 3 + 2]);


		}

		for (auto& cube : cubeList)
		{

			// Rotate About Y-Axis
			rotateCubeAboutArbitraryAxis(*cube, { 1,0,0 }, midpointRowPosition, signChange * arbitraryAngleAmount, fCameraAngle, fCameraPitch,
				fCameraZoom, { vCameraPos.x,vCameraPos.y,0.f }, { screenWidth,screenHeight });

			// Get the visible Faces of the Cube
			calculateVisibleFaces(*cube);

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
				}
			}
		}

		midpointRowPosition.x += 1.f;
		signChange *= -1.f;
		signChange *= 0.f;

	}

}

void RubiksCube::rotateLeft(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
	float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
	std::map<std::vector<int>, bool>& registeredProjectedVertexSets)
{

	float signChange = -1.f;

	for (int a = 0; a < 3; a++)
	{

		std::vector<Cube*> cubeList;

		for (int b = 0; b < 3; b++)
		{
			allCubes[b][a];
			allCubes[b][a + 3];
			allCubes[b][a + 6];

			cubeList.push_back(allCubes[b][a]);
			cubeList.push_back(allCubes[b][a + 3]);
			cubeList.push_back(allCubes[b][a + 6]);

		}

		for (auto& cube : cubeList)
		{

			// Rotate About Y-Axis
			rotateCubeAboutArbitraryAxis(*cube, { 0,1,0 }, midpointRowPosition, signChange * arbitraryAngleAmount, fCameraAngle, fCameraPitch,
				fCameraZoom, { vCameraPos.x,vCameraPos.y,0.f }, { screenWidth,screenHeight });

			// Get the visible Faces of the Cube
			calculateVisibleFaces(*cube);

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
				}
			}
		}

		midpointRowPosition.y += 1.f;
		signChange *= 0.f;

	}

}

void RubiksCube::rotateLeftCCW(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
	float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
	std::map<std::vector<int>, bool>& registeredProjectedVertexSets)
{

	float signChange = 1.f;

	for (int a = 0; a < 3; a++)
	{

		std::vector<Cube*> cubeList;

		for (int b = 0; b < 3; b++)
		{
			allCubes[b][a];
			allCubes[b][a + 3];
			allCubes[b][a + 6];

			cubeList.push_back(allCubes[b][a]);
			cubeList.push_back(allCubes[b][a + 3]);
			cubeList.push_back(allCubes[b][a + 6]);

		}

		for (auto& cube : cubeList)
		{

			// Rotate About Y-Axis
			rotateCubeAboutArbitraryAxis(*cube, { 0,1,0 }, midpointRowPosition, signChange * arbitraryAngleAmount, fCameraAngle, fCameraPitch,
				fCameraZoom, { vCameraPos.x,vCameraPos.y,0.f }, { screenWidth,screenHeight });

			// Get the visible Faces of the Cube
			calculateVisibleFaces(*cube);

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
				}
			}
		}

		midpointRowPosition.y += 1.f;
		signChange *= 0.f;

	}

}

void RubiksCube::rotateRight(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
	float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
	std::map<std::vector<int>, bool>& registeredProjectedVertexSets)
{

	float signChange = 1.f;

	for (int a = 2; a >= 0; a--)
	{

		std::vector<Cube*> cubeList;

		for (int b = 0; b < 3; b++)
		{
			allCubes[b][a];
			allCubes[b][a + 3];
			allCubes[b][a + 6];

			cubeList.push_back(allCubes[b][a]);
			cubeList.push_back(allCubes[b][a + 3]);
			cubeList.push_back(allCubes[b][a + 6]);

		}

		for (auto& cube : cubeList)
		{

			// Rotate About Y-Axis
			rotateCubeAboutArbitraryAxis(*cube, { 0,1,0 }, midpointRowPosition, signChange * arbitraryAngleAmount, fCameraAngle, fCameraPitch,
				fCameraZoom, { vCameraPos.x,vCameraPos.y,0.f }, { screenWidth,screenHeight });

			// Get the visible Faces of the Cube
			calculateVisibleFaces(*cube);

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
				}
			}
		}

		midpointRowPosition.y += 1.f;
		signChange *= 0.f;

	}

}

void RubiksCube::rotateRightCCW(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
	float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
	std::map<std::vector<int>, bool>& registeredProjectedVertexSets)
{

	float signChange = -1.f;

	for (int a = 2; a >= 0; a--)
	{

		std::vector<Cube*> cubeList;

		for (int b = 0; b < 3; b++)
		{
			allCubes[b][a];
			allCubes[b][a + 3];
			allCubes[b][a + 6];

			cubeList.push_back(allCubes[b][a]);
			cubeList.push_back(allCubes[b][a + 3]);
			cubeList.push_back(allCubes[b][a + 6]);

		}

		for (auto& cube : cubeList)
		{

			// Rotate About Y-Axis
			rotateCubeAboutArbitraryAxis(*cube, { 0,1,0 }, midpointRowPosition, signChange * arbitraryAngleAmount, fCameraAngle, fCameraPitch,
				fCameraZoom, { vCameraPos.x,vCameraPos.y,0.f }, { screenWidth,screenHeight });

			// Get the visible Faces of the Cube
			calculateVisibleFaces(*cube);

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
				}
			}
		}

		midpointRowPosition.y += 1.f;
		signChange *= 0.f;

	}

}


void RubiksCube::rotateTop(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
	float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
	std::map<std::vector<int>, bool>& registeredProjectedVertexSets)
{

	float signChange = -1.f;

	for (int i = 2; i >= 0; i--) {

		for (auto& cube : allCubes[i]) {
			// Get the projection coordinates of the cube
			//setCubeProjectionCoordinates(*cube, fCameraAngle, fCameraPitch, fCameraZoom, { vCameraPos.x,vCameraPos.y,0.f }, { screenWidth,screenHeight });
			rotateCubeAboutArbitraryAxis(*cube, { 0,0,1 }, midpointRowPosition, signChange * arbitraryAngleAmount, fCameraAngle, fCameraPitch,
				fCameraZoom, { vCameraPos.x,vCameraPos.y,0.f }, { screenWidth,screenHeight });

			// Get the visible Faces of the Cube
			calculateVisibleFaces(*cube);

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
				}
			}

		}

		midpointRowPosition.z += 1.f;
		signChange *= 0.f;
	}

}

void RubiksCube::rotateTopCCW(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
	float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
	std::map<std::vector<int>, bool>& registeredProjectedVertexSets)
{

	float signChange = 1.f;

	for (int i = 2; i >= 0; i--) {

		for (auto& cube : allCubes[i]) {
			// Get the projection coordinates of the cube
			//setCubeProjectionCoordinates(*cube, fCameraAngle, fCameraPitch, fCameraZoom, { vCameraPos.x,vCameraPos.y,0.f }, { screenWidth,screenHeight });
			rotateCubeAboutArbitraryAxis(*cube, { 0,0,1 }, midpointRowPosition, signChange * arbitraryAngleAmount, fCameraAngle, fCameraPitch,
				fCameraZoom, { vCameraPos.x,vCameraPos.y,0.f }, { screenWidth,screenHeight });

			// Get the visible Faces of the Cube
			calculateVisibleFaces(*cube);

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
				}
			}

		}

		midpointRowPosition.z += 1.f;
		signChange *= 0.f;
	}

}

void RubiksCube::rotateBottom(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
	float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
	std::map<std::vector<int>, bool>& registeredProjectedVertexSets)
{

	float signChange = 1.f; // was 1.f

	for (int i = 0; i < 3; i++) {

		for (auto& cube : allCubes[i]) {
			// Get the projection coordinates of the cube
			//setCubeProjectionCoordinates(*cube, fCameraAngle, fCameraPitch, fCameraZoom, { vCameraPos.x,vCameraPos.y,0.f }, { screenWidth,screenHeight });
			rotateCubeAboutArbitraryAxis(*cube, { 0,0,1 }, midpointRowPosition, signChange * arbitraryAngleAmount, fCameraAngle, fCameraPitch,
				fCameraZoom, { vCameraPos.x,vCameraPos.y,0.f }, { screenWidth,screenHeight });

			// Get the visible Faces of the Cube
			calculateVisibleFaces(*cube);

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
				}
			}

		}

		midpointRowPosition.z += 1.f;
		signChange *= 0.f;
	}

}


void RubiksCube::rotateBottomCCW(float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
	float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
	std::map<std::vector<int>, bool>& registeredProjectedVertexSets)
{

	float signChange = -1.f; // was 1.f

	for (int i = 0; i < 3; i++) {

		for (auto& cube : allCubes[i]) {
			// Get the projection coordinates of the cube
			//setCubeProjectionCoordinates(*cube, fCameraAngle, fCameraPitch, fCameraZoom, { vCameraPos.x,vCameraPos.y,0.f }, { screenWidth,screenHeight });
			rotateCubeAboutArbitraryAxis(*cube, { 0,0,1 }, midpointRowPosition, signChange * arbitraryAngleAmount, fCameraAngle, fCameraPitch,
				fCameraZoom, { vCameraPos.x,vCameraPos.y,0.f }, { screenWidth,screenHeight });

			// Get the visible Faces of the Cube
			calculateVisibleFaces(*cube);

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
				}
			}

		}

		midpointRowPosition.z += 1.f;
		signChange *= 0.f;
	}

}

void RubiksCube::rotateFromRotationNumber(int rotNumber, float fCameraAngle, float fCameraPitch, float fCameraZoom, sf::Vector2f vCameraPos,
	float arbitraryAngleAmount, int screenWidth, int screenHeight, sf::Vector3f midpointRowPosition,
	std::map<std::vector<int>, bool>& registeredProjectedVertexSets)
{
	switch (rotNumber)
	{
	case 0:
		rotateFront(fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
			screenHeight, midpointRowPosition, registeredProjectedVertexSets);
		break;
	case 1:
		rotateFrontCCW(fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
			screenHeight, midpointRowPosition, registeredProjectedVertexSets);
		break;
	case 2:
		rotateBack(fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
			screenHeight, midpointRowPosition, registeredProjectedVertexSets);
		break;
	case 3:
		rotateBackCCW(fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
			screenHeight, midpointRowPosition, registeredProjectedVertexSets);
		break;
	case 4:
		rotateLeft(fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
			screenHeight, midpointRowPosition, registeredProjectedVertexSets);
		break;
	case 5:
		rotateLeftCCW(fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
			screenHeight, midpointRowPosition, registeredProjectedVertexSets);
		break;
	case 6:
		rotateRight(fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
			screenHeight, midpointRowPosition, registeredProjectedVertexSets);
		break;
	case 7:
		rotateRightCCW(fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
			screenHeight, midpointRowPosition, registeredProjectedVertexSets);
		break;
	case 8:
		rotateTop(fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
			screenHeight, midpointRowPosition, registeredProjectedVertexSets);
		break;
	case 9:
		rotateTopCCW(fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
			screenHeight, midpointRowPosition, registeredProjectedVertexSets);
		break;
	case 10:
		rotateBottom(fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
			screenHeight, midpointRowPosition, registeredProjectedVertexSets);
		break;
	case 11:
		rotateBottomCCW(fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
			screenHeight, midpointRowPosition, registeredProjectedVertexSets);
		break;
	case 12:
		rotateFront(fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
			screenHeight, midpointRowPosition, registeredProjectedVertexSets);
		break;
	case 13:
		rotateBack(fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
			screenHeight, midpointRowPosition, registeredProjectedVertexSets);
		break;
	case 14:
		rotateLeft(fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
			screenHeight, midpointRowPosition, registeredProjectedVertexSets);
		break;
	case 15:
		rotateRight(fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
			screenHeight, midpointRowPosition, registeredProjectedVertexSets);
		break;
	case 16:
		rotateTop(fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
			screenHeight, midpointRowPosition, registeredProjectedVertexSets);
		break;
	case 17:
		rotateBottom(fCameraAngle, fCameraPitch, fCameraZoom, vCameraPos, arbitraryAngleAmount, screenWidth,
			screenHeight, midpointRowPosition, registeredProjectedVertexSets);
		break;
	}
}

void RubiksCube::shuffleCube(std::stack<int>& randomMoves, std::unordered_map<int, std::vector<int>> moveNumbersAndOpposites, int times)
{
	srand(time(0));
	for (int i = 0; i < times; i++)
	{
		int theNumber = rand() % 18;

		if (!randomMoves.empty()) {
			//std::cout << "theNumebr = " << theNumber << std::endl;
			while (theNumber == moveNumbersAndOpposites[randomMoves.top()][0] || theNumber == moveNumbersAndOpposites[randomMoves.top()][2]
				|| theNumber == moveNumbersAndOpposites[randomMoves.top()][1] || theNumber == randomMoves.top())
			{
				theNumber = rand() % 18;
			}
		}

		randomMoves.push(theNumber);

		std::cout << randomMoves.top() << ",";
	}
}
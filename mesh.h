#pragma once
struct assimp_Vertex
{
	float x, y, z;
	float fx, fy, fz;
	float u, v;
	float r, g, b, a;
};

struct assimp_texture
{
	GLuint id;
	aiTextureType type;
	std::string path;
};

class Mesh
{
public :
	std::vector<assimp_Vertex> vertData;
	std::vector<GLuint> indices;
	std::vector<assimp_texture> textures;
};
class model
{
public:
	std::vector<Mesh> mymodel;
};
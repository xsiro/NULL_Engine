#ifndef __R_MODEL_H__
#define __R_MODEL_H__

#include "Resource.h"

struct	aiScene;
struct	aiNode;
struct	aiMesh;
struct	aiMaterial;
enum	aiTextureType;

class	R_Mesh;
//class R_Texture;

class R_Model : public Resource
{
public:
	R_Model();
	~R_Model();

	void Draw();

	void ProcessScene(const aiScene* scene);

private:
	void ProcessNode(aiNode* node, const aiScene* scene);
	void ProcessMesh(aiMesh* mesh, const aiScene* scene);
	void LoadMaterialTextures(aiMaterial* material, aiTextureType type, std::string type_name);

private:
	std::vector<R_Mesh*> meshes;
	std::string directory;

};

#endif // !__R_MODEL_H__
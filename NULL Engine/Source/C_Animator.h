#ifndef __C_ANIMATOR_H__
#define __C_ANIMATOR_H__

#include <string>
#include <vector>
#include <map>

#include "MathGeoTransform.h"

#include "Channel.h"
#include "AnimatorClip.h"

#include "Component.h"

namespace math
{
	class LineSegment;
}

class ParsonNode;

class GameObject;
class R_Animation;

typedef unsigned int uint;
typedef unsigned __int32 uint32;

struct BoneLink
{
	BoneLink();
	BoneLink(const Channel& channel, GameObject* game_object);
	
	const Channel channel;
	GameObject* game_object;
};

struct AnimationBones
{
	std::string name;
	std::vector<BoneLink> bones;
};

enum class INTERPOLATION_TYPE																								// WIP IDEA
{
	LINEAL,
	CUSTOM
};

class C_Animator : public Component																							// In charge of managing Skeletal Animation
{
public:
	C_Animator(GameObject* owner);
	~C_Animator();

	bool Update		() override;
	bool CleanUp	() override;

	bool SaveState	(ParsonNode& root) const override;
	bool LoadState	(ParsonNode& root) override;

	static inline COMPONENT_TYPE GetType() { return COMPONENT_TYPE::ANIMATOR; }

public:
	bool				StepToPrevKeyframe			();
	bool				StepToNextKeyframe			();
	bool				RefreshBoneDisplay			();

	void				AddAnimation				(R_Animation* r_animation);
	
	bool				Play						();
	bool				Pause						();
	bool				Step						();
	bool				Stop						();

public:																														// --- CURRENT/BLENDING ANIMATION METHODS
	R_Animation*		GetCurrentAnimation			() const;
	R_Animation*		GetBlendingAnimation		() const;

	void				SetCurrentAnimation			(R_Animation* r_animation, uint index = 0);
	void				SetBlendingAnimation		(R_Animation* r_animation_to_blend_to, uint blend_frames);

	void				ClearCurrentAnimation		();
	void				ClearBlendingAnimation		();

public:																														// --- GET/SET METHODS
	std::vector<LineSegment> GetDisplayBones		() const;
	
	float				GetPlaybackSpeed			() const;
	bool				GetInterpolate				() const;
	bool				GetLoopAnimation			() const;
	bool				GetPlayOnStart				() const;
	bool				GetCameraCulling			() const;
	bool				GetShowBones				() const;

	const char*			GetAnimationName			() const;
	float				GetAnimationTime			() const;
	uint				GetAnimationTicks			() const;
	float				GetCurrentTicksPerSecond	() const;
	float				GetCurrentDuration			() const;

	void				SetPlaybackSpeed			(const float& playback_speed);
	void				SetInterpolate				(const bool& set_to);
	void				SetLoopAnimation			(const bool& set_to);
	void				SetPlayOnStart				(const bool& set_to);
	void				SetCameraCulling			(const bool& set_to);
	void				SetShowBones				(const bool& set_to);

private:
	bool				StepAnimation				();
	bool				BlendAnimation				();

	const Transform		GetInterpolatedTransform	(const double& current_keyframe, const Channel& current_channel, const Transform& original_transform) const;
	const float3		GetInterpolatedPosition		(const double& current_keyframe, const Channel& current_channel, const float3& original_position) const;
	const Quat			GetInterpolatedRotation		(const double& current_keyframe, const Channel& current_channel, const Quat& original_rotation) const;
	const float3		GetInterpolatedScale		(const double& current_keyframe, const Channel& current_channel, const float3& original_scale) const;

	const Transform		GetPoseToPoseTransform		(const uint& current_tick, const Channel& current_channel, const Transform& original_transform) const;
	const float3		GetPoseToPosePosition		(const uint& current_tick, const Channel& current_channel, const float3& original_position) const;
	const Quat			GetPoseToPoseRotation		(const uint& current_tick, const Channel& current_channel, const Quat& original_rotation) const;
	const float3		GetPoseToPoseScale			(const uint& current_tick, const Channel& current_channel, const float3& original_scale) const;

	void				FindCurrentAnimationBones	();
	void				UpdateDisplayBones			();
	void				GenerateBoneSegments		(const GameObject* bone);

	void				SortBoneLinksByHierarchy	(const std::vector<BoneLink>& bone_links, const GameObject* root_bone, std::vector<BoneLink>& sorted);

private:
	std::vector<R_Animation*>					animations;																	// Animation Resources. Contain bone information (transforms...).
	std::map<uint32, std::vector<BoneLink>>		animation_bones;
	std::map<std::string, AnimatorClip>			clips;																		// Segments of animations. "Idle", "Walk", "Attack"...
	std::vector<BoneLink>				bones;																				// Multiple animations will have the same bones.

	std::vector<LineSegment>	display_bones;																				// Line Segments between GO bones. For debug purposes.

	AnimatorClip*	current_clip;
	AnimatorClip*	blending_clip;

	R_Animation*	current_animation;
	R_Animation*	blending_animation;

	GameObject*		current_root_bone;

private:																													// --- FUNCTIONALITY VARIABLES
	uint			blend_frames;

	bool			play;
	bool			pause;
	bool			step;
	bool			stop;

	float			animation_time;
	float			animation_frame;
	uint			animation_tick;

private:																													// --- GET/SET VARIABLES	
	float			playback_speed;
	bool			interpolate;
	bool			loop_animation;
	bool			play_on_start;
	bool			camera_culling;
	
	bool			show_bones;
};

#endif // !__C_ANIMATOR_H__
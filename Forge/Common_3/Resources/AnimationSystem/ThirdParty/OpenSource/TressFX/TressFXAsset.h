//---------------------------------------------------------------------------------------
// Loads and processes TressFX files.
// Inputs are binary files/streams/blobs
// Outputs are raw data that will mostly end up on the GPU.
//-------------------------------------------------------------------------------------
//
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef AMD_TRESSFX_ASSET_H
#define AMD_TRESSFX_ASSET_H

#include "../../../../../Utilities/Math/MathTypes.h"
#include "Forge/TF_FileSystem.h"

#include "TressFXFileFormat.h"

namespace AMD {
#define TRESSFX_MAX_INFLUENTIAL_BONE_COUNT 4

struct TressFXBoneSkinningData
{
	float boneIndex[TRESSFX_MAX_INFLUENTIAL_BONE_COUNT];
	float weight[TRESSFX_MAX_INFLUENTIAL_BONE_COUNT];
};

class TressFXAsset
{
	public:
	TressFXAsset();
	~TressFXAsset();

	// Hair data from *.tfx
	float4* m_positions;
	float2* m_strandUV;
	float4* m_refVectors;
	float4* m_globalRotations;
	float4* m_localRotations;
	float4* m_tangents;
	float4* m_followRootOffsets;
	int32_t*    m_strandTypes;
	float*  m_thicknessCoeffs;
	float*  m_restLengths;
	int32_t*    m_triangleIndices;

	// Bone skinning data from *.tfxbone
	TressFXBoneSkinningData* m_boneSkinningData;

	// counts on hair data
	int32_t m_numTotalStrands;
	int32_t m_numTotalVertices;
	int32_t m_numVerticesPerStrand;
	int32_t m_numGuideStrands;
	int32_t m_numGuideVertices;
	int32_t m_numFollowStrandsPerGuide;

	// Loads *.tfx hair data
	bool LoadHairData(FileStream* fh);

	//Generates follow hairs procedually.  If numFollowHairsPerGuideHair is zero, then this function won't do anything.
	bool GenerateFollowHairs(int32_t numFollowHairsPerGuideHair = 0, float tipSeparationFactor = 0, float maxRadiusAroundGuideHair = 0);

	// Computes various parameters for simulation and rendering. After calling this function, data is ready to be passed to hair object.
	bool ProcessAsset();

	inline uint32_t GetNumHairSegments() { return m_numTotalStrands * (m_numVerticesPerStrand - 1); }
	inline uint32_t GetNumHairTriangleIndices() { return 6 * GetNumHairSegments(); }
	inline uint32_t GetNumHairLineIndices() { return 2 * GetNumHairSegments(); }

	private:
	// Loads tfx files from TressFX version 4
	bool LoadV4(TressFXTFXFileHeader* header, FileStream* fh);

	// Loads tfx files from TressFX verion 3
	bool LoadV3(TressFXFileObject* header, FileStream* fh);

	// Resets variables and clears up allocate buffers.
	void Clear();

	// Helper functions for ProcessAsset.
	void ComputeTransforms();
	void ComputeThicknessCoeffs();
	void ComputeStrandTangent();
	void ComputeRestLengths();
	void FillTriangleIndexArray();
};

}    // namespace AMD

#endif

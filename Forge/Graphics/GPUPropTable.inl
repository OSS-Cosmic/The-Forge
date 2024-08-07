    GPU_CONFIG_PROPERTY("allowbuffertextureinsameheap", mGpuProperty.mAllowBufferTextureInSameHeap)
    GPU_CONFIG_PROPERTY("amdasicfamily", mGpuProperty.mAmdAsicFamily)
    GPU_CONFIG_PROPERTY("builtindrawid", mGpuProperty.mBuiltinDrawID)
#if defined(METAL)
    GPU_CONFIG_PROPERTY("cubemaptexturearraysupported", mGpuProperty.mCubeMapTextureArraySupported)
    GPU_CONFIG_PROPERTY("tessellationindirectdrawsupported", mGpuProperty.mTessellationIndirectDrawSupported)
#if !defined(TARGET_IOS)
    GPU_CONFIG_PROPERTY("isheadless", mGpuProperty.mIsHeadLess)
#endif
#endif
    GPU_CONFIG_PROPERTY_READ_ONLY("deviceid", mDeviceAdapter->mModelId)
#if defined(DIRECT3D11) || defined(DIRECT3D12)
    GPU_CONFIG_PROPERTY("directxfeaturelevel", mGpuProperty.mFeatureLevel)
    GPU_CONFIG_PROPERTY("suppressinvalidsubresourcestateafterexit", mGpuProperty.mSuppressInvalidSubresourceStateAfterExit)
#endif
    GPU_CONFIG_PROPERTY("geometryshadersupported", mGpuProperty.mGeometryShaderSupported)
    GPU_CONFIG_PROPERTY("gpupresetlevel", mPresetLevel)
    GPU_CONFIG_PROPERTY("graphicqueuesupported", mGpuProperty.mGraphicsQueueSupported)
    GPU_CONFIG_PROPERTY("hdrsupported", mGpuProperty.mHDRSupported)
#if defined(VULKAN)
    GPU_CONFIG_PROPERTY("dynamicrenderingenabled", mGpuProperty.mDynamicRenderingSupported)
    GPU_CONFIG_PROPERTY("xclipsetransferqueueworkaroundenabled", mGpuProperty.mXclipseTransferQueueWorkaround)
#endif
    GPU_CONFIG_PROPERTY("indirectcommandbuffer", mGpuProperty.mIndirectCommandBuffer)
    GPU_CONFIG_PROPERTY("indirectrootconstant", mGpuProperty.mIndirectRootConstant)
    GPU_CONFIG_PROPERTY("maxboundtextures", mGpuProperty.mMaxBoundTextures)
#if defined(DIRECT3D12)
    GPU_CONFIG_PROPERTY("maxrootsignaturedwords", mGpuProperty.mMaxRootSignatureDWORDS)
#endif
    GPU_CONFIG_PROPERTY("maxvertexinputbindings", mGpuProperty.mMaxVertexInputBindings)
    GPU_CONFIG_PROPERTY("multidrawindirect", mGpuProperty.mMultiDrawIndirect)
    GPU_CONFIG_PROPERTY("occlusionqueries", mGpuProperty.mOcclusionQueries)
    GPU_CONFIG_PROPERTY("pipelinestatsqueries", mGpuProperty.mPipelineStatsQueries)
    GPU_CONFIG_PROPERTY("primitiveidsupported", mGpuProperty.mPrimitiveIdSupported)
    GPU_CONFIG_PROPERTY("rasterorderviewsupport", mGpuProperty.mROVsSupported)
    GPU_CONFIG_PROPERTY("raytracingsupported", mGpuProperty.mRaytracingSupported)
    GPU_CONFIG_PROPERTY("rayquerysupported", mGpuProperty.mRayQuerySupported)
    GPU_CONFIG_PROPERTY("raypipelinesupported", mGpuProperty.mRayPipelineSupported)
    GPU_CONFIG_PROPERTY("softwarevrssupported", mGpuProperty.mSoftwareVRSSupported)
    GPU_CONFIG_PROPERTY("tessellationsupported", mGpuProperty.mTessellationSupported)
    GPU_CONFIG_PROPERTY("timestampqueries", mGpuProperty.mTimestampQueries)
    GPU_CONFIG_PROPERTY("uniformbufferalignment", mGpuProperty.mUniformBufferAlignment)
    GPU_CONFIG_PROPERTY("uploadbuffertexturealignment", mGpuProperty.mUploadBufferTextureAlignment)
    GPU_CONFIG_PROPERTY("uploadbuffertexturerowalignment", mGpuProperty.mUploadBufferTextureRowAlignment)
    GPU_CONFIG_PROPERTY_READ_ONLY("vendorid", mDeviceAdapter->mVendorId)
    GPU_CONFIG_PROPERTY("vram", mGpuProperty.mVRAM)
    GPU_CONFIG_PROPERTY("wavelanecount", mGpuProperty.mWaveLaneCount)
    GPU_CONFIG_PROPERTY("waveopssupport", mGpuProperty.mWaveOpsSupportFlags)


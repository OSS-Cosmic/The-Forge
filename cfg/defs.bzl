
DEFAULT_GRAPHICS_API = select({
    "config//os:linux": ["vulkan"],
    "config//os:windows": ["vulkan", "direct3d11", "direct3d11"],
    "config//os:macos": ["metal"],
  })


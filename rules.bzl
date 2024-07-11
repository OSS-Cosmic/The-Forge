load("@prelude//python:toolchain.bzl", "PythonToolchainInfo")
load("@prelude//paths.bzl", "paths")

def _fsl_impl(ctx: AnalysisContext) -> list[Provider]:
    #sources = ctx.attrs.srcs
    #extension = ".exe" if host_info().os.is_windows else ""
    #out = ctx.actions.declare_output("main" + extension)
    #out = ctx.actions.declare_output("main.fsl")
    
    shaders = ctx.actions.declare_output("Shaders", dir = True)
    shaders_compiled = ctx.actions.declare_output("CompiledShaders", dir = True)
    
    python_toolchain = ctx.attrs._python_toolchain[PythonToolchainInfo]
    cmd = cmd_args([python_toolchain.interpreter, ctx.attrs._fsl_compiler,
      "-l", "VULKAN",
      "-d", cmd_args(shaders.as_output(), format = "{}"),
      "-b", cmd_args(shaders_compiled .as_output(), format = "{}"),
      "--compile", ctx.attrs.input
    ])
    ctx.actions.run(cmd, category = "compile")

    return [
        DefaultInfo(
          default_outputs = [shaders, shaders_compiled]
        ),
        RunInfo(args = cmd_args([shaders, shaders_compiled])),
    ]

fsl_build = rule(
    impl = _fsl_impl,
    attrs = {
        "input": attrs.source(),
        "_python_toolchain": attrs.toolchain_dep(default = "toolchains//:python" , providers = [PythonToolchainInfo]),
        "_fsl_compiler": attrs.default_only(attrs.source(default = "//:fsl")),
    },
)

def _package_app(ctx: AnalysisContext) -> list[Provider]:
    files = ctx.attrs.files
    artifacts = []
    for f in files:
        dest = ctx.actions.declare_output(f)
        artifacts.append(dest)
        ctx.actions.copy_file(dest, files[f])
      
    for res in ctx.attrs.resources:
        info = res[DefaultInfo]
        for f in info.default_outputs:
          dest = ctx.actions.declare_output(f.basename)
          artifacts.append(dest)
          ctx.actions.copy_file(dest, f)
 
    return [DefaultInfo(default_outputs = artifacts)]


package_app = rule(
    impl = _package_app,
    attrs = {
        "resources": attrs.list(attrs.dep(), default = []),
        "files": attrs.named_set(attrs.source(), sorted = True, default = [])
    },
)

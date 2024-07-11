load("@prelude//python:toolchain.bzl", "PythonToolchainInfo")
load("@prelude//paths.bzl", "paths")

def _fsl_compile(ctx: AnalysisContext) -> list[Provider]:
    #sources = ctx.attrs.srcs
    #extension = ".exe" if host_info().os.is_windows else ""
    #out = ctx.actions.declare_output("main" + extension)
    #out = ctx.actions.declare_output("main.fsl")
    
    shaders = ctx.actions.declare_output("Shaders", dir = True)
    shaders_compiled = ctx.actions.declare_output("CompiledShaders", dir = True)
    script = ctx.actions.declare_output("fsl-script")
  
    python_toolchain = ctx.attrs._python_toolchain[PythonToolchainInfo]
    script_cmds = cmd_args([
        "#!/bin/sh",
    ])
    for src in ctx.attrs.srcs: 
      script_cmds.add(cmd_args([python_toolchain.interpreter, ctx.attrs._fsl_compiler,
        "-l", "VULKAN",
        "-d", cmd_args(shaders.as_output(), format = "{}"),
        "-b", cmd_args(shaders_compiled .as_output(), format = "{}"),
        "--compile", src 
      ], delimiter = " "))

    ctx.actions.write(
        script,
        script_cmds,
        is_executable = True,
        allow_args = True,
    )
    ctx.actions.run(
        cmd_args(script, hidden = script_cmds),
        category = "fsl_compiler",
        no_outputs_cleanup = True,
    )

    return [
        DefaultInfo(
          default_outputs = [shaders, shaders_compiled]
        )
    ]

fsl_compile = rule(
    impl = _fsl_compile,
    attrs = {
        "srcs": attrs.list(attrs.source(), default=[]),
        "_python_toolchain": attrs.toolchain_dep(default = "toolchains//:python" , providers = [PythonToolchainInfo]),
        "_fsl_compiler": attrs.default_only(attrs.source(default = "//:fsl")),
    },
)


def subpath_export_files(base: str,paths: list[str]):
  for p in paths:
    native.export_file(
      name = p,
      mode = "reference",
      src = "{}/{}".format(base, p),
      visibility = ['PUBLIC']
    )

def _package_app(ctx: AnalysisContext) -> list[Provider]:
    artifacts = []
    
    files = ctx.attrs.files
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

load("@prelude//python:toolchain.bzl", "PythonToolchainInfo")

def _fsl_compile(ctx: AnalysisContext) -> list[Provider]:
    script = ctx.actions.declare_output("fsl-script.bat")
  
    python_toolchain = ctx.attrs._python_toolchain[PythonToolchainInfo]
    script_cmds = cmd_args([])
    
    shaders = ctx.actions.declare_output("Shaders", dir = True)
    shaders_compiled = ctx.actions.declare_output("CompiledShaders", dir = True)
    
    for src in ctx.attrs.srcs: 
      script_cmds.add(cmd_args([python_toolchain.interpreter, ctx.attrs._fsl_compiler,
        "-l", "DIRECT3D12",
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
        "base_dir": attrs.option(attrs.string(), default = None),
        "srcs": attrs.list(attrs.source(), default=[]),
        "_python_toolchain": attrs.toolchain_dep(default = "toolchains//:python" , providers = [PythonToolchainInfo]),
        "_fsl_compiler": attrs.default_only(attrs.source(default = "//:fsl")),
    },
)

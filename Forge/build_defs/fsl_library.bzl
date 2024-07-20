load("@prelude//python:toolchain.bzl", "PythonToolchainInfo")
load("@prelude//os_lookup:defs.bzl", "OsLookup")
load("@prelude//decls:common.bzl", "buck")

def _fsl_library(ctx: AnalysisContext) -> list[Provider]:
   python_toolchain = ctx.attrs._python_toolchain[PythonToolchainInfo]
   script_cmds = cmd_args([])
    
   shaders = ctx.actions.declare_output("Shaders", dir = True)
   shaders_compiled = ctx.actions.declare_output("CompiledShaders", dir = True)

   if ctx.attrs._exec_os_type[OsLookup].platform == "windows": 
      fxc = read_config("tf", "fxc", None)
      if fxc:
        script_cmds.add("set FSL_COMPILER_FXC={}".format(fxc)) 

   for src in ctx.attrs.srcs: 
      for api in (["DIRECT3D12"] if ctx.attrs.D3D12 else []) + (["DIRECT3D11"] if ctx.attrs.D3D11 else []) + (["VULKAN"] if ctx.attrs.VULKAN else []) :
          script_cmds.add(cmd_args([python_toolchain.interpreter, ctx.attrs._fsl_compiler,
            "-l", api,
            "-d", cmd_args(shaders.as_output(), format = "{}"),
            "-b", cmd_args(shaders_compiled .as_output(), format = "{}"),
            "--compile", src,
          ] + (["|| exit /b !ERRORLEVEL!"] if (ctx.attrs._exec_os_type[OsLookup].platform == "windows") else []), delimiter = " "))

   if ctx.attrs._exec_os_type[OsLookup].platform == "windows":
      shim, _ = ctx.actions.write(
          "__fsl_shim.bat",
          cmd_args("@echo off", "@SETLOCAL EnableDelayedExpansion", script_cmds),
          is_executable = True,
          allow_args = True,
      )
   else:
      shim, _ = ctx.actions.write(
          "__fsl_shim.sh",
          cmd_args( "#!/usr/bin/env bash",script_cmds),
          is_executable = True,
          allow_args = True,
      )

   ctx.actions.run(
        cmd_args(shim, hidden = script_cmds),
        category = "fsl_compiler",
        no_outputs_cleanup = True,
    )

   return [
        DefaultInfo(
          default_outputs = [shaders, shaders_compiled]
        )
    ]

fsl_library = rule(
    impl = _fsl_library,
    attrs = {
        "base_dir": attrs.option(attrs.string(), default = None),
        "srcs": attrs.list(attrs.source(), default=[]),
        "_python_toolchain": attrs.toolchain_dep(default = "toolchains//:python" , providers = [PythonToolchainInfo]),
        "_fsl_compiler": attrs.default_only(attrs.source(default = "//:fsl")),
        "_exec_os_type": buck.exec_os_type_arg(),
        "D3D12": attrs.bool(default = select({
            "DEFAULT": False,
            "tf_platform//D3D12:supported":True, 
        })),
        "D3D11": attrs.bool(default = select({
            "DEFAULT": False,
            "tf_platform//D3D11:supported":True, 
        })),
        "VULKAN": attrs.bool(default = select({
            "DEFAULT": False,
            "tf_platform//VULKAN:supported":True, 
        })),
    },
)

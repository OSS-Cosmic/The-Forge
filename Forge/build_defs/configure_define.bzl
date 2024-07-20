
def _configure_define(ctx: AnalysisContext) -> list[Provider]:
  output = ctx.actions.declare_output(ctx.attrs.out)
  cmd = [
      ctx.attrs._configure_define_tool[RunInfo],
      cmd_args("--source_file=", ctx.attrs.file, delimiter = ""),
      cmd_args("--dest_file=", output.as_output(), delimiter = ""),
  ] + [
    cmd_args("--variable=", v,"=", ctx.attrs.variables[v], delimiter = "") for v in ctx.attrs.variables
  ]
  for feat in ctx.attrs.feature:
      if ctx.attrs.feature[feat]:
          cmd.append(cmd_args("--feature=", feat, delimiter = ""))
  ctx.actions.run(
      cmd,
      category = "configure",
      local_only = True,
      no_outputs_cleanup = True,
  )

  return [DefaultInfo(default_output = output)]


configure_define = rule(
    impl = _configure_define,
    attrs = {
        "file": attrs.source(),
        "out": attrs.string(),
        "variables": attrs.dict(key = attrs.string(), value = attrs.string(), default = {}),
        "feature": attrs.dict(key = attrs.string(), value = attrs.bool(), default = {}),
        "_configure_define_tool": attrs.default_only(attrs.exec_dep(providers = [RunInfo], default = "@tf//build_defs/tool:configure_define")),
    }
)

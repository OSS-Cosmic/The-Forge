load("@prelude//paths.bzl", "paths")

def _package_app(ctx: AnalysisContext) -> list[Provider]:
    artifacts = []
    
    files = ctx.attrs.files
    for f in files:
        dest = ctx.actions.declare_output(f)
        artifacts.append(dest)
        ctx.actions.copy_file(dest, files[f])
    
    for res in ctx.attrs.resources:
        info = res[1][DefaultInfo]
        for f in info.default_outputs:
          dest = ctx.actions.declare_output(paths.join(res[0], f.short_path))
          artifacts.append(dest)
          ctx.actions.copy_file(dest, f)
 
    return [DefaultInfo(default_outputs = artifacts)]


package_app = rule(
    impl = _package_app,
    attrs = {
        "resources": attrs.list(attrs.tuple(attrs.string(),attrs.dep()), default = []),
        "files": attrs.named_set(attrs.source(), sorted = True, default = [])
    },
)

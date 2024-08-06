
load("@prelude//paths.bzl", "paths")
load(
    "@prelude//linking:shared_libraries.bzl",
    "merge_shared_libraries",
)

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
    
    #for shared_dep in ctx.attrs.cxx_shared_deps:
    #    extra_shared_libs = traverse_shared_library_info(
    #        merge_shared_libraries(
    #            actions = ctx.actions,
    #            deps = [dep.get(SharedLibraryInfo) for dep in shared_dep],
    #        ),
    #    )

    return [DefaultInfo(default_outputs = artifacts)]


package_app = rule(
    impl = _package_app,
    attrs = {
        #"cxx_shared_deps": attrs.list(attrs.dep()),
        "resources": attrs.list(attrs.tuple(attrs.string(),attrs.dep()), default = []),
        "files": attrs.named_set(attrs.source(), sorted = True, default = [])
    },
)

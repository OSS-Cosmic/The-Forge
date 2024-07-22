load("@prelude//paths.bzl", "paths")

def constraint_boolean(setting):
  native.constraint_value(
    name = "enabled",
    constraint_setting = setting,
    visibility = ["PUBLIC"],
  )
  native.constraint_value(
    name = "disabled",
    constraint_setting = setting,
    visibility = ["PUBLIC"],
  )

def subpath_ref_export_files(base: str, paths: list[str]):
  for p in paths:
    native.export_file(
      name = p,
      mode = "reference",
      src = "{}/{}".format(base, p),
      visibility = ['PUBLIC']
    )


def export_resources(srcs: dict[str, str]):
  for src in srcs:
    native.export_file(
      name = paths.basename(src),
      src = srcs[src],
      out = src,
      visibility = ['PUBLIC']
    )

def select_has(constraints: list[str]):
  return select({
        "DEFAULT": False,
    } | { c: True for c in constraints})
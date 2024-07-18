
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

def subpath_export_files(base: str,paths: list[str]):
  for p in paths:
    native.export_file(
      name = p,
      mode = "reference",
      src = "{}/{}".format(base, p),
      visibility = ['PUBLIC']
    )



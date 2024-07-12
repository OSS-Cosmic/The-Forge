
def subpath_export_files(base: str,paths: list[str]):
  for p in paths:
    native.export_file(
      name = p,
      mode = "reference",
      src = "{}/{}".format(base, p),
      visibility = ['PUBLIC']
    )



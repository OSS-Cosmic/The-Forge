

#def avalaible_graphics_api():
#    selected_apis = read_config("tf", "apis", DEFAULT_GRAPHICS_API)
#    result = []
#    for api in selected_apis:
#        if api in DEFAULT_GRAPHICS_API:
#            result.append(api)
#    return result

def select_has(constraints: list[str]):
  return select({
        "DEFAULT": False,
    } | { c: True for c in constraints})

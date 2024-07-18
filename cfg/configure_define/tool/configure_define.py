# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under both the MIT license found in the
# LICENSE-MIT file in the root directory of this source tree and the Apache
# License, Version 2.0 found in the LICENSE-APACHE file in the root directory
# of this source tree.
#
# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
#   file Copyright.txt or https://cmake.org/licensing for details.  */

import argparse
import subprocess
import sys
from pathlib import Path
from typing import List, NamedTuple
import re
  
CONFIGURE_REGEX = "#([ \t]*)configure[ \t]+([A-Za-z_0-9]*)"
CONFIGURE_REGEX_10 = "#([ \t]*)configure01[ \t]+([A-Za-z_0-9]*)"

class Args(NamedTuple):
    source_file: Path
    dest_file: Path
    feature: list[str] 
    variable: list[str] 

def arg_parse() -> Args:
    parser = argparse.ArgumentParser()
    parser.add_argument("--source_file", type=Path, required=True)
    parser.add_argument("--dest_file", type=Path, required=True)
    parser.add_argument("--feature", action='append')
    parser.add_argument("--variable", action='append')
    return Args(**vars(parser.parse_args()))

def apply_features(features, line):
    reMatch = re.match(CONFIGURE_REGEX, line)
    if reMatch:
        indent = reMatch.group(1)
        if reMatch.group(2) in features:
            return line.replace("#" + indent +  "configure", "#" + indent + "define")
        return "/* #undef " + reMatch.group(2) + "*/" + "\n"
    reMatch = re.match(CONFIGURE_REGEX_10, line)
    if reMatch:
        indent = reMatch.group(1)
        return line.replace("#" + indent +  "configure01", "#" + indent + "define").strip() + (" 1" if (reMatch.group(2) in features) else " 0") + "\n"
    return line

def main() -> None:
    args = arg_parse()
    terms = {}
    if args.variable:
        for v in args.variable:
            keyValue =  v.split("=")
            terms[keyValue[0]] = keyValue[1]
    with open(args.source_file, "r") as source_file:
        with open(args.dest_file, "w") as dest_file:
            for line in source_file:
                line = apply_features([] if args.feature == None else args.feature, line)
                index = 0;
                while index < len(line):
                    if line[index] == '$':
                        start = index
                        if index + 1 < len(line) and line[index + 1] == '{':
                            while index < len(line):
                                if line[index] == '}':
                                    term = line[start + 2: index]
                                    if term in terms:
                                        line = line.replace(line[start:index + 1], terms[term])
                                        index = 0
                                    break
                                index += 1
                        else:
                            index += 1
                    else:
                        index += 1
                dest_file.write(line) 


if __name__ == "__main__":
    main()



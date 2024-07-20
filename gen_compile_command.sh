!#/bin/bash
cat $(buck2 bxl //compile_command.bxl:gen_compile_command -- --base_dir $(pwd))  > compile_commands.json

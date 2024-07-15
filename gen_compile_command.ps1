$CommandPath = buck2 bxl //compile_command.bxl:gen_compile_command -- --base_dir (Get-Location).Path

cat $CommandPath | Out-File compile_commands.json

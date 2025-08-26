echo off

call cmd\clean.bat

set "base=src\cpax\pax\base\export.c"
set "memory=src\cpax\pax\memory\export.c"
set "string=src\cpax\pax\string\export.c"
set "structure=src\cpax\pax\structure\export.c"

set "pax=%base% %memory% %string% %structure%"

set "src=%pax% src\message\export.c"
set "dir=src\message\test"

zig cc %src% "%dir%\broker.c" -o message_broker.exe

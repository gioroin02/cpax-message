echo off

cls

set "core=src/pax/core/exports.cpp"
set "memory=src/pax/memory/exports.cpp"
set "string=src/pax/string/exports.cpp"
set "container=src/pax/container/exports.cpp"

set "src=%core% %memory% %string% %container%"
set "dir=src\message\test"

zig c++ %src% "%dir%\broker.cpp" -o test_message_broker.exe

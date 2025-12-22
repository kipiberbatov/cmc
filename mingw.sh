# Cross-compile for Windows on Unix-like systems using MinGW
# Binaries are run by Wine
# Cairo and GTK will need to be installed for Windows; MinGW made aware of them

set -x

make OS=Windows_NT MODE=windows/release CC=x86_64-w64-mingw32-gcc obj_src
make OS=Windows_NT MODE=windows/release CC=x86_64-w64-mingw32-gcc obj_main_{array,algebra,region,mesh}
make OS=Windows_NT MODE=windows/release CC=x86_64-w64-mingw32-gcc obj_plugins_diffusion
make OS=Windows_NT MODE=windows/release AR=x86_64-w64-mingw32-ar lib_src
make OS=Windows_NT MODE=windows/release CC=x86_64-w64-mingw32-gcc lib_plugins_diffusion
make OS=Windows_NT MODE=windows/release CC=x86_64-w64-mingw32-gcc bin_{array,algebra,region,mesh,diffusion}
make OS=Windows_NT MODE=windows/release INTERPRETER=wine txt_{array,algebra,region,mesh,diffusion}

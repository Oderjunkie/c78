{ pkgs }: {
	deps = [
		pkgs.strace
  pkgs.ed
  pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}
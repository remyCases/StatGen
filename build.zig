const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});
    const exe = b.addExecutable(.{
        .name = "main",
        .root_module = b.createModule(.{
            .root_source_file = b.path("src/main.zig"),
            .target = target,
            .optimize = optimize,
        }),
    });
    exe.addIncludePath(b.path("src"));
    exe.addCSourceFiles(.{ .files = &[_][]const u8{ "src/processing.c", "src/utilsIO.c" } });
    exe.addObjectFile(b.path("src/linalg.o"));

    exe.linkLibC();
    exe.addObjectFile(std.Build.LazyPath{ .cwd_relative = "C:/msys64/mingw64/lib/libgfortran.a" });
    exe.addObjectFile(std.Build.LazyPath{ .cwd_relative = "C:/msys64/mingw64/lib/libquadmath.a" });
    exe.addObjectFile(std.Build.LazyPath{ .cwd_relative = "C:/msys64/mingw64/lib/libgcc_s.a" });

    b.installArtifact(exe);

    const fortran_compile = b.addSystemCommand(&.{ "gfortran", "-c", "src/linalg.f90", "-o", "src/linalg.o" });
    exe.step.dependOn(&fortran_compile.step);
}

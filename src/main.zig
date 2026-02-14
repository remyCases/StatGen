const std = @import("std");
const processing = @cImport({
    @cInclude("processing.h");
});

pub fn main() !void {
    var stdout_buf: [1024]u8 = undefined;
    var stdout_writer: std.fs.File.Writer = std.fs.File.stdout().writer(&stdout_buf);

    try stdout_writer.interface.print("Starting RNN\n", .{});
    try stdout_writer.interface.flush();
    const result: c_int = processing.run_rnn();

    try stdout_writer.interface.print("Return with code {}\n", .{result});
    try stdout_writer.interface.flush();
}
